/*
    Project: CTsvcLIB

    Module: DbgLog.Cpp

    Description: Debug/Log class Library

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "CTsvcLIB.h"

using namespace std;

namespace CTsvcLIB
{

int DBG_SYSRC = -1;
int DBG_ERROR = -1;
int DBG_WARN = -1;
int DBG_TRACE = -1;
int DBG_ODBC = -1;

void LOGf( char* fmt ... )
{
    va_list marker;
    va_start( marker, fmt );

    char buffer[ 1024 ];
    vsprintf( buffer, fmt, marker );

    va_end( marker );

    LOG( DBG_TRACE, FALSE ) << buffer;
    }

void DebugRC( DWORD retCode )
{
    CHAR lpMsgBuf[ 512 ] = { 0 };

    DWORD len = ::FormatMessage
    (
        FORMAT_MESSAGE_FROM_SYSTEM, // source and processing options
        NULL,                       // pointer to  message source
        retCode,                    // requested message identifier
        0,                          // language identifier for requested message
        lpMsgBuf,                   // pointer to message buffer
        sizeof( lpMsgBuf ) - 1,     // maximum size of message buffer
        NULL                        // address of array of message inserts
        );

    if ( len > 0 )
    {
        if ( lpMsgBuf[ len - 1 ] == '\n' )
            LOG( DBG_SYSRC ) << lpMsgBuf;
        else
            LOG( DBG_SYSRC ) << lpMsgBuf << eline;
        }
    else
    {
        LOG( DBG_SYSRC )
            << "Return Code = " << retCode
            << " (0x" << hex << retCode << ")"
            << eline;
        }
    }

LOG&
eline( LOG& log )
{
    return log << "\r\n";
    }

LOG&
dec( LOG& log )
{
    return log.setflags( LOG::dec );
    }

LOG&
hex( LOG& log )
{
    return log.setflags( LOG::hex );
    }

LOG&
oct( LOG& log )
{
    return log.setflags( LOG::oct );
    }

LOG&
chr( LOG& log )
{
    return log.setflags( LOG::chr );
    }

LOG&
bol( LOG& log )
{
    return log.setflags( LOG::bol );
    }

LOG&
fix( LOG& log )
{
    return log.setflags( LOG::fix );
    }

LOG&
sci( LOG& log )
{
    return log.setflags( LOG::sci );
    }

//----------------------------------------------------- LOG class

enum
{
    MAXLOGFCNT = 4,
    MAXLOGCHCNT = 16
    };

LOG::Initializer LOG::defaultSignOn;

Mutex LOG:: logMutex;

HANDLE LOG:: hLogFile[ MAXLOGFCNT ] = { NULL };

int LOG:: channelCount = 0;
char* LOG:: channelName[ MAXLOGCHCNT ] = { NULL };
char LOG:: channelFlag[ MAXLOGCHCNT ] = { 0 };

LOG::Initializer::Initializer( void )
{
    LOG::SignOn( DBG_SYSRC, "SysRC" );
    LOG::SignOn( DBG_ERROR, "Error" );
    LOG::SignOn( DBG_WARN,  "Warn" );
    LOG::SignOn( DBG_TRACE, "Trace" );
    LOG::SignOn( DBG_ODBC,  "ODBC" );
    LOG::SetOn( "SysRC,Error,Warn,Trace,ODBC" );
    }

void LOG:: SignOn( int& chn, char* chnName )
{
    if ( channelCount >= MAXLOGCHCNT )
    {
        chn = -1;
        return;
        }

    chn = channelCount;
    channelName[ channelCount ] = chnName;
    channelFlag[ channelCount ] = 0;
    channelCount++;
    }

void LOG:: SetOn( char* channelp )
{
    while ( channelp )
    {
        char chnName[ 64 ];
        char* endp = strchr( channelp, ',' );
        if ( endp )
        {
            int len = endp - channelp;
            strncpy( chnName, channelp, len );
            chnName[ len ] = 0;
            channelp = endp + 1;
            }
        else
        {
            strcpy( chnName, channelp );
            channelp = NULL;
            }

        for ( int i = 0; i < channelCount; i ++ )
        {
            if ( stricmp( channelName[ i ], chnName ) == 0 )
            {
                channelFlag[ i ] = 1;
                break;
                }
            }
        }
    }

void LOG:: SetOff( char* channelp )
{
    while ( channelp )
    {
        char chnName[ 64 ];
        char* endp = strchr( channelp, ',' );
        if ( endp )
        {
            int len = endp - channelp;
            strncpy( chnName, channelp, len );
            chnName[ len ] = 0;
            channelp = endp + 1;
            }
        else
        {
            strcpy( chnName, channelp );
            channelp = NULL;
            }

        for ( int i = 0; i < channelCount; i ++ )
        {
            if ( stricmp( channelName[ i ], chnName ) == 0 )
            {
                channelFlag[ i ] = 0;
                break;
                }
            }
        }
    }

void LOG:: UseHandle( HANDLE hFile )
{
    for ( int i = 0; i < MAXLOGFCNT; i++ )
        if ( hLogFile[ i ] == hFile )
            return;

    for ( i = 0; i < MAXLOGFCNT; i++ )
        if ( ! hLogFile[ i ] )
            break;

    if ( i < MAXLOGFCNT )
        hLogFile[ i ] = hFile;
    }

void LOG:: ReleaseHandle( HANDLE hFile )
{
    for ( int i = 0; i < MAXLOGFCNT; i++ )
        if ( hLogFile[ i ] == hFile )
            hLogFile[ i ] = NULL;
    }

//
// Per thread defined User-Writebuf; see TLS
//

_declspec(thread) static LOG::PFOO_WRITEBUF user_writebuf = NULL;
_declspec(thread) static void* user_writebuf_object = NULL;

void
LOG:: UseWriteBuf(
    PFOO_WRITEBUF pFoo,
    void* pObj
    )
{
    user_writebuf = pFoo;
    user_writebuf_object = pObj;
    }

LOG:: LOG( int chn, BOOL fStamps )
    : field( 0 )
{
    channel = chn;
    i_flags = dec;
    f_flags = fix;

    if ( channel < 0 || channel >= channelCount )
    {
        channel = -1;
        return;
        }

    if ( ! channelFlag[ channel ] )
    {
        channel = -1;
        return;
        }

    logMutex.Lock ();

    if ( ! fStamps )
        return;

#if 0
    // Start overwriting file if size excedes limit
    //
    for ( int i = 0; i < MAXLOGFCNT; i++ )
    {
        if ( ! hLogFile[ i ] )
            continue;

        DWORD curPos = ::SetFilePointer( hLogFile[ i ], 0, NULL, FILE_CURRENT );
        if ( curPos >= 10240000 && curPos <= 0x7FffFFff )
            ::SetFilePointer( hLogFile[ i ], 0, NULL, FILE_BEGIN );
        }
#endif

    // Write prefix

    char prefix[ 80 ];

    sprintf( prefix, "%s [%05X] %s: ", 
        (char*)aTimestamp(), 
        ::GetCurrentThreadId (),
        channelName[ channel ]
        );

    (*this) << prefix;
    }

LOG:: ~LOG ()
{
    if ( channel < 0 )
        return;

    logMutex.Unlock ();
    }

LOG&
LOG:: setflags( int_flags f )
{
    i_flags = f;
    return *this;
    }

LOG&
LOG:: setflags( float_flags f )
{
    f_flags = f;
    return *this;
    }

LOG&
LOG:: operator << ( fld& f )
{
    field = f;
    return *this;
    }

void
LOG:: writebuf( void* lpBuffer, int len )
{
    if ( channel < 0 )
        return;

    if ( ! lpBuffer )
        return;

    for ( int i = 0; i < MAXLOGFCNT; i++ )
    {
        if ( hLogFile[ i ] )
        {
            DWORD cchWritten;
            ::WriteFile( hLogFile[ i ], lpBuffer, len, &cchWritten, NULL );
            }
        }

    //
    // additional userhandler (defined on per-thread basis)
    //
    if ( user_writebuf )
    {
        user_writebuf( user_writebuf_object, lpBuffer, len );
        }
    }

void
LOG:: writebuf( int ch )
{
    char v = int( ch );

    writebuf( &ch, 1 );
    }

void
LOG:: writefld( void* lpBuffer, int len )
{
    if ( channel < 0 )
        return;

    if ( field.width <= 0 )
    {
        writebuf( lpBuffer, len );
        return;
        }

    if ( field.fill_ch == 0 )
        field.fill_ch = ' ';

    if ( field.align == 'L' || field.align == 'l' )
    {
        int rightpad = field.width - len;

        writebuf( lpBuffer, rightpad <= 0 ? field.width : len );

        for ( int i = 0; i < rightpad; i++ )
            writebuf( int( field.fill_ch ) );

        field = 0;
        }

    else
    {
        int leftpad = field.width - len;

        for ( int i = 0; i < leftpad; i++ )
            writebuf( int( field.fill_ch ) );

        writebuf( lpBuffer, leftpad <= 0 ? field.width : len );

        field = 0;
        }
    }

LOG& LOG:: operator << ( LOG& (* pManip)( LOG& ) )
{
    return pManip( *this );
    }

LOG& LOG:: operator << ( VSTR& str )
{
    if ( ! str.data )
    {
        writefld( "(null)", 6 );
        return *this;
        }

    for ( int len = 0; len < str.len; len ++ )
        if ( str.data[ len ] == '\0' )
            break;

    writefld( str.data, len );

    return *this;
    }

LOG& LOG:: operator << ( char* str )
{
    if ( ! str )
    {
        writefld( "(null)", 6 );
        return *this;
        }

    writefld( str, strlen( str ) );
    return *this;
    }

LOG& LOG:: operator << ( const char* str )
{
    if ( ! str )
    {
        writefld( "(null)", 6 );
        return *this;
        }

    writefld( (char*)str, strlen( str ) );
    return *this;
    }

LOG& LOG:: operator << ( volatile char* str )
{
    if ( ! str )
    {
        writefld( "(null)", 6 );
        return *this;
        }

    writefld( (char*)str, strlen( (char*)str ) );
    return *this;
    }

LOG& LOG:: operator << ( unsigned char* str )
{
    if ( ! str )
    {
        writefld( "(null)", 6 );
        return *this;
        }

    writefld( str, strlen( (char*)str ) );
    return *this;
    }

LOG& LOG:: operator << ( const void* ptr )
{
    char str[ 40 ];
    int len = sprintf( str, "%p", ptr );
        
    writefld( str, len );
    return *this;
    }

LOG& LOG:: operator << ( char x )
{
    char str[ 40 ];
    int len = sprintf( str, "%c", int( x ) );
    writefld( str, len );
    return *this;
    }

LOG& LOG:: operator << ( unsigned char x )
{
    char str[ 40 ];
    int len = sprintf( str, "%c", int( x ) );
    writefld( str, len );
    return *this;
    }

LOG& LOG:: operator << ( int x )
{
    char str[ 40 ];
    int len = 0;
    
    switch( i_flags )
    {
        case hex:
            len = sprintf( str, "%X", x );
            break;
        case oct:
            len = sprintf( str, "%o", x );
            break;
        case bol:
            len = sprintf( str, "%s", x ? "true" : "false" );
            break;
        case chr:
            len = sprintf( str, "%c", x );
            break;
        default:
            len = sprintf( str, "%d", x );
        }
        
    writefld( str, len );
    i_flags = dec;
    return *this;
    }

LOG& LOG:: operator << ( unsigned int x )
{
    char str[ 40 ];
    int len = 0;
    
    switch( i_flags )
    {
        case hex:
            len = sprintf( str, "%X", x );
            break;
        case oct:
            len = sprintf( str, "%o", x );
            break;
        case bol:
            len = sprintf( str, "%s", x ? "true" : "false" );
            break;
        case chr:
            len = sprintf( str, "%c", x );
            break;
        default:
            len = sprintf( str, "%u", x );
        }
        
    writefld( str, len );
    i_flags = dec;
    return *this;
    }

LOG& LOG:: operator << ( short x )
{
    char str[ 40 ];
    int len = 0;
    
    switch( i_flags )
    {
        case hex:
            len = sprintf( str, "%hx", x );
            break;
        case oct:
            len = sprintf( str, "%ho", x );
            break;
        case bol:
            len = sprintf( str, "%s", x ? "true" : "false" );
            break;
        case chr:
            len = sprintf( str, "%hc", x );
            break;
        default:
            len = sprintf( str, "%hd", x );
        }
        
    writefld( str, len );
    i_flags = dec;
    return *this;
    }

LOG& LOG:: operator << ( unsigned short x )
{
    char str[ 40 ];
    int len = 0;
    
    switch( i_flags )
    {
        case hex:
            len = sprintf( str, "%hx", x );
            break;
        case oct:
            len = sprintf( str, "%ho", x );
            break;
        case bol:
            len = sprintf( str, "%s", x ? "true" : "false" );
            break;
        case chr:
            len = sprintf( str, "%hc", x );
            break;
        default:
            len = sprintf( str, "%hu", x );
        }
        
    writefld( str, len );
    i_flags = dec;
    return *this;
    }

LOG& LOG:: operator << ( long x )
{
    char str[ 40 ];
    int len = 0;
    
    switch( i_flags )
    {
        case hex:
            len = sprintf( str, "%lx", x );
            break;
        case oct:
            len = sprintf( str, "%lo", x );
            break;
        case bol:
            len = sprintf( str, "%s", x ? "true" : "false" );
            break;
        case chr:
            len = sprintf( str, "%lc", x );
            break;
        default:
            len = sprintf( str, "%ld", x );
        }
        
    writefld( str, len );
    i_flags = dec;
    return *this;
    }

LOG& LOG:: operator << ( unsigned long x )
{
    char str[ 40 ];
    int len = 0;
    
    switch( i_flags )
    {
        case hex:
            len = sprintf( str, "%lx", x );
            break;
        case oct:
            len = sprintf( str, "%lo", x );
            break;
        case bol:
            len = sprintf( str, "%ls", x ? "true" : "false" );
            break;
        case chr:
            len = sprintf( str, "%lc", x );
            break;
        default:
            len = sprintf( str, "%lu", x );
        }
        
    writefld( str, len );
    i_flags = dec;
    return *this;
    }

LOG& LOG:: operator << ( double x )
{
    char str[ 50 ];
    int len = 0;
    
    switch( f_flags )
    {
        case sci:
            len = sprintf( str, "%le", x );
            break;
        case fix:
            len = sprintf( str, "%.2lf", x );
            break;
        default:
            len = sprintf( str, "%lg", x );
        }
        
    writefld( str, len );
    f_flags = fix;
    return *this;
    }

LOG& LOG:: operator << ( float x )
{
    char str[ 50 ];
    int len = 0;
    
    switch( f_flags )
    {
        case sci:
            len = sprintf( str, "%e", x );
            break;
        case fix:
            len = sprintf( str, "%f", x );
            break;
        default:
            len = sprintf( str, "%g", x );
        }
        
    writefld( str, len );
    f_flags = fix;
    return *this;
    }

} // namespace CTsvcLIB