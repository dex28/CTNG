/*
    Project: CTsvcLIB

    Module: CTsvcLIB.h

    Description: Common application library for NT service/console CT applications

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#ifndef _CT_SVC_LIB_H_INCLUDED
#define _CT_SVC_LIB_H_INCLUDED

//============================================================================
// TRACE is used to conditional intensive trace program execution to 
// LOG( DBG_TRACE ) stream. Accepted values: 1= active, 0= inactive
//
#define TRACE_OK 1

#if TRACE_OK
#define TRACE(msg) \
do \
{ \
    CTsvcLIB::LOG( CTsvcLIB::DBG_TRACE ) << msg << CTsvcLIB::eline; \
    } while(0)
#else
#define TRACE(msg) ((void)0)
#endif

//============================================================================

#define PRINTERR(msg) \
do \
{ \
    CTsvcLIB::LOG( CTsvcLIB::DBG_ERROR ) << msg << CTsvcLIB::eline; \
    } while(0)

//============================================================================

#define TRASSERT(exp) \
do \
{ \
    if ( ! (exp) ) \
    { \
        CTsvcLIB::LOG( CTsvcLIB::DBG_ERROR ) \
            << "Assertion failed" << CTsvcLIB::eline \
            << "Expression: " << #exp << CTsvcLIB::eline \
            << "File: " << __FILE__ << CTsvcLIB::eline \
            << "Line: " << __LINE__ << CTsvcLIB::eline; \
        throw "ASSERTION FAILED"; \
        } \
    } while(0)

//============================================================================

#undef DllDecl

#ifdef CTSVCLIB_IMPLEMENTATION
#define DllDecl __declspec(dllexport)
#elif CTSVCLIB
#define DllDecl __declspec(dllimport)
#else
#define DllDecl
#endif

//============================================================================

#include <cstdio>
#include <ctime>

#include <list>

#include <winsock2.h>
#include <windows.h>
#include <sqlext.h>

namespace CTsvcLIB
{
//============================================================================
//            T e m p l a t e s   &   I n l i n e   C l a s s e s
//============================================================================

//////////////////////////////////////////////////////////////////////////////
// Ptr<RefCnt> template

template <class T>
class Ptr
{
    T* ptr;

public:

    Ptr( void )
        : ptr( NULL )
    {}

    Ptr( T* p_ )
    {
        ptr = p_;
        if ( ptr ) ptr->AddRef ();
        }

    Ptr( const Ptr<T>& p_ )
    {
        ptr = p_.ptr;
        if ( ptr ) ptr->AddRef ();
        }

    Ptr& operator = ( T* p_ )
    {
        if ( ptr == p_ )
            return *this; // nothing to do
        if ( ptr ) ptr->RemoveRef();
        ptr = p_;
        if ( ptr ) ptr->AddRef();
        return *this;
        }

    Ptr& operator = ( const Ptr<T>& p_ )
    {
        if ( ptr == p_.ptr )
            return *this; // nothing to do
        if ( ptr ) ptr->RemoveRef();
        ptr = p_.ptr;
        if ( ptr ) ptr->AddRef();
        return *this;
        }

    bool operator == ( const Ptr<T>& p_ )
    {
        return ptr && p_.ptr ? *ptr == *(p_.ptr) : false;
        }

    ~Ptr( void ) { if ( ptr ) ptr->RemoveRef(); }

    operator T* ( void ) { return ptr; }

    T& operator* ( void ) { return *ptr; }

    T* operator-> ( void ) { return ptr; }
    };

//////////////////////////////////////////////////////////////////////////////

class Mutex
{
    CRITICAL_SECTION cs;
public:

    Mutex() { ::InitializeCriticalSection( &cs ); }

    ~Mutex() { ::DeleteCriticalSection( &cs ); }

    void Lock() { ::EnterCriticalSection( &cs ); }

    void Unlock() { ::LeaveCriticalSection( &cs ); }
    };

class MutexBlock
{
    Mutex& mutex;

public:

    MutexBlock( Mutex& m ) : mutex( m ) { mutex.Lock (); }
    ~MutexBlock( void ) { mutex.Unlock (); }
    };

//////////////////////////////////////////////////////////////////////////////

class Semaphore
{
    HANDLE hSema;

public:

    Semaphore()
    {
        hSema = NULL;
        }

    Semaphore( long initialCount, long maximumCount )
    {
        hSema = ::CreateSemaphore(
            NULL,                   // pointer to security attributes 
            initialCount,           // initial count
            maximumCount,           // maximum count
            NULL                    // pointer to semaphore-object name  
            );
        }

    ~Semaphore()
    {
        if ( hSema )
            ::CloseHandle( hSema );
        }

    bool Create( long initialCount, long maximumCount )
    {
        if ( hSema )
        {
            ::CloseHandle( hSema );
            }

        hSema = ::CreateSemaphore(
            NULL,                   // pointer to security attributes 
            initialCount,           // initial count
            maximumCount,           // maximum count
            NULL                    // pointer to semaphore-object name  
            );

        return hSema != NULL;
        }

    void Destroy( void )
    {
        if ( hSema )
            ::CloseHandle( hSema );
        hSema = NULL;
        }

    bool Wait( DWORD dwTimeout = INFINITE )
    {
        if ( ! hSema ) return false;
        return WAIT_OBJECT_0 == ::WaitForSingleObject( hSema, dwTimeout );
        }

    void Release( long releaseCount, long* previousCount = NULL )
    {
        if ( ! hSema ) return;
        ::ReleaseSemaphore( hSema, releaseCount, previousCount );
        }
    };

//////////////////////////////////////////////////////////////////////////////

class RefCount
{
    long count;

    virtual void OnRefCountZero( void ) = 0; // Pure virtual

protected:

    RefCount( void )
        : count( 0 )
    {}

public:

    long GetRefCount( void )
    {
        return ::InterlockedExchangeAdd( &count, 0 );
        }

    long AddRef( void ) 
    {
        return ::InterlockedIncrement( &count ); 
        }

    long RemoveRef( void ) 
    {
        if ( long newCount = ::InterlockedDecrement( &count ) )
            return newCount;

        OnRefCountZero();
        return 0;
        }
    };

//////////////////////////////////////////////////////////////////////////////
// List<Element> template

template <typename Element>
class List
{
public:

    class AnchorBase
    {
    protected:

        List<Element>* list;
        AnchorBase* next;
        AnchorBase* prev;

        Element* element;

    public:

        AnchorBase( void )
            : list( NULL )
            , prev( NULL )
            , next( NULL )
            , element( NULL )
        {}

        void Initialize( Element* pelement )
        {
            element = pelement;
            };

        void LinkAsFirst( List<Element>& plist )
        {
            assert( element != NULL );

            list = &plist;
            next = list->first;
            prev = NULL;

            if ( list->first )
            {
                list->first->prev = this;
                list->first = this;
                }
            else
            {
                list->first = this;
                list->last = this;
                }

            list->count ++;
            }

        void LinkAsLast( List<Element>& plist )
        {
            list = &plist;
            prev = list->last;
            next = NULL;

            if ( list->last )
            {
                list->last->next = this;
                list->last = this;
                }
            else
            {
                list->first = this;
                list->last = this;
                }

            list->count ++;
            }

        void LinkBefore( AnchorBase& ank )
        {
            list = ank.list;
            next = &ank;
            prev = ank.prev;

            if ( ank.prev )
            {
                ank.prev->next = this;
                ank.prev = this;
                }
            else
            {
                ank.list->first = this;
                ank.prev = this;
                }

            list->count ++;
            }

        void LinkAfter( AnchorBase& ank )
        {
            list = ank.list;
            next = &ank;
            prev = ank.prev;

            if ( ank.next )
            {
                ank.next->prev = this;
                ank.next = this;
                }
            else
            {
                ank.list->last = this;
                ank.next = this;
                }

            list->count ++;
            }

        void Unlink ()
        {
            if ( ! list )
                return;

            list->count --;

            if ( prev )
                prev->next = next;
            else
                list->first = next;

            if ( next )
                next->prev = prev;
            else
                list->last = prev;

            list = NULL;
            next = NULL;
            prev = NULL;
            }

        ~AnchorBase ()
        {
            Unlink ();
            }

        bool HasElement () const
            { return element != NULL; }

        Element* GetElement () const
            { return element; }

        AnchorBase* GetNext () const
            { return next; }

        AnchorBase* GetPrev () const
            { return prev; }

        List<Element>* GetList () const
            { return list; }
        };

    template <typename Owner>
    class Anchor : public List<Element>::AnchorBase
    {
        Owner* partOf;
    public:

        Anchor( void )
            : partOf( NULL )
        {}

        void Initialize( Element* pelement, Owner* powner )
        {
            element = pelement;
            partOf = powner;
            };

        operator Owner* ( void ) const { return partOf; }

        Owner& operator* ( void ) { return *partOf; }

        Owner* operator-> ( void ) { return partOf; }
        };

    class Iterator
    {
        List* list;
        AnchorBase* current;
        AnchorBase* next;
        AnchorBase* prev;

    public:

        Iterator( List<Element>& plist )
        {
            list = &plist;
            current = list->GetFirst ();
            if ( current )
            {
                next = current->GetNext ();
                prev = current->GetPrev ();
                }
            }

        Iterator( AnchorBase& ank )
        {
            list = ank.GetList ();
            current = &ank;
            if ( current )
            {
                next = current->GetNext ();
                prev = current->GetPrev ();
                }
            }

        Iterator& operator = ( List<Element>& plist )
        {
            list = &plist;
            current = list->GetFirst ();
            if ( current )
            {
                next = current->GetNext ();
                prev = current->GetPrev ();
                }
            return *this;
            }

        Iterator& operator = ( AnchorBase& ank )
        {
            list = ank.GetList ();
            current = &ank;
            if ( current )
            {
                next = current->GetNext ();
                prev = current->GetPrev ();
                }
            return *this;
            }

        Iterator& operator ++ ()
        {
            current = next;
            if ( current )
                next = current->GetNext ();
            return *this;
            }

        Iterator& operator ++ ( int )
        {
            current = next;
            if ( current )
                next = current->GetNext ();
            return *this;
            }

        operator bool ()
            { return current != NULL; }

        Element* operator -> ()
            { return current ? current->GetElement() : NULL; }

        operator Element* ()
            { return current ? current->GetElement() : NULL; }

        AnchorBase* GetAnchor () const
            { return current; }

        Element* GetElement () const
            { return current ? current->GetElement() : NULL; }
        };

private:

    friend AnchorBase;

    long count;
    AnchorBase* first;
    AnchorBase* last;

public:

    List( void )
        : count( 0 )
        , first( NULL )
        , last( NULL )
    {}

    ~List( void )
    {
        for ( Iterator i = *this; i; i++ )
            i.GetAnchor()->Unlink ();
        }

    AnchorBase* GetFirst () const
        { return first; }

    AnchorBase* GetLast () const
        { return last; }

    long GetCount () const
        { return count; }
    };

//////////////////////////////////////////////////////////////////////////////
// aTime ...

class aTimestamp
{
    char str[ 40 ];

public:

    aTimestamp( void )
    {
        SYSTEMTIME st;
        ::GetLocalTime( &st );
        sprintf( str,
            "%04hd-%02hd-%02hd %02hd:%02hd:%02hd.%03hd",
            st.wYear, st.wMonth, st.wDay,
            st.wHour, st.wMinute, st.wSecond,
            st.wMilliseconds
            );
        }

    aTimestamp( SYSTEMTIME& st )
    {
        sprintf( str,
            "%04hd-%02hd-%02hd %02hd:%02hd:%02hd.%03hd",
            st.wYear, st.wMonth, st.wDay,
            st.wHour, st.wMinute, st.wSecond,
            st.wMilliseconds
            );
        }

    operator char* () { return str; }
    };

class aTime
{
    char str[ 40 ];

public:

    aTime( time_t t )
    {
        tm* tm = ::localtime( &t );

        sprintf( str,
            "%02hd:%02hd:%02hd",
            tm->tm_hour, tm->tm_min, tm->tm_sec
            );
        };

    aTime( SYSTEMTIME& st )
    {
        sprintf( str,
            "%02hd:%02hd:%02hd",
            st.wHour, st.wMinute, st.wSecond
            );
        };

    operator char* () { return str; }
    };

class aTimeMilli
{
    char str[ 40 ];

public:

    aTimeMilli( void )
    {
        SYSTEMTIME st;
        ::GetLocalTime( &st );
        sprintf( str,
            "%02hd:%02hd:%02hd.%03hd",
            st.wHour, st.wMinute, st.wSecond, st.wMilliseconds
            );
        }

    aTimeMilli( SYSTEMTIME& st )
    {
        sprintf( str,
            "%02hd:%02hd:%02hd.%03hd",
            st.wHour, st.wMinute, st.wSecond, st.wMilliseconds
            );
        }

    aTimeMilli( DWORD dwMilliseconds )
    {
        sprintf( str,
            "%02hd:%02hd:%02hd.%03hd",
            ( dwMilliseconds / 3600000 ) % 100,
            ( dwMilliseconds / 60000 ) % 60,
            ( dwMilliseconds / 1000 ) % 60,
            dwMilliseconds % 1000
            );
        }

    operator char* () { return str; }
    };

class aDate
{
    char str[ 40 ];

public:

    aDate( SYSTEMTIME& st )
    {
        sprintf( str,
            "%02hd.%02hd.%04hd",
            st.wDay, st.wMonth, st.wYear
            );
        }

    operator char* () { return str; }
    };

//////////////////////////////////////////////////////////////////////////////
// DbgLog classes

class DllDecl LOG
{
    class Initializer
    {
    public:
        Initializer( void );
        };

public:

    struct DllDecl VSTR
    {
        char* data;
        int len;

        VSTR( char* ptr, int size )
            : data( ptr )
            , len( size )
        {}

        VSTR( unsigned char* ptr, int size )
            : data( reinterpret_cast<char*>( ptr ) )
            , len( size )
        {}
        };

    struct DllDecl fld
    {
        unsigned short width;
        char align;
        char fill_ch;

        fld( int pwidth = 0, char* flags = NULL )
            : width( static_cast<unsigned short>( pwidth ) )
            , align( 0 )
            , fill_ch( 0 )
        {
            if ( ! flags )
                return;

            align = flags[ 0 ];
            if ( align )
                fill_ch = flags[ 1 ];
            }
        };

    typedef void (* PFOO_WRITEBUF ) ( void*, void*, int );

    enum int_flags { dec, bol, hex, oct, chr };
    enum float_flags { sci, fix };

private:

    static Initializer defaultSignOn;

    static Mutex logMutex;
    
    static HANDLE hLogFile [];

    static int channelCount;
    static char* channelName [];
    static char channelFlag [];

    int channel;
    int_flags i_flags;
    float_flags f_flags;
    fld field;

public:

    int Disabled () { return channel < 0 || channel >= channelCount; }

    static void SignOn( int& chn, char* chnName );
    static void SetOn( char* channels );
    static void SetOff( char* channels );
    static void UseHandle( HANDLE hFile );
    static void ReleaseHandle( HANDLE hFile );

    static void UseWriteBuf( PFOO_WRITEBUF pFoo, void* pObj );

    LOG( int chn, BOOL fStamps = TRUE );
    ~LOG ();

    LOG& setflags( int_flags f = dec );
    LOG& setflags( float_flags f );

    void writebuf( void* lpBuffer, int len );
    void writebuf( int ch );

    void writefld( void* lpBuffer, int len );

    LOG& operator << ( LOG& (* pManip) ( LOG& ) );
    LOG& operator << ( LOG& (LOG::* pManip) () );
    LOG& operator << ( fld& field );

    LOG& operator << ( VSTR& str );
    LOG& operator << ( char* str );
    LOG& operator << ( const char* str );
    LOG& operator << ( volatile char* str );
    LOG& operator << ( unsigned char* str );

    LOG& operator << ( char x );
    LOG& operator << ( unsigned char x );
    LOG& operator << ( int x );
    LOG& operator << ( unsigned int x );
    LOG& operator << ( short x );
    LOG& operator << ( unsigned short x );
    LOG& operator << ( long x );
    LOG& operator << ( unsigned long x );

    LOG& operator << ( double x );
    LOG& operator << ( float x );

    LOG& operator << ( const void* );
    };

// LOG stream manipulators

DllDecl extern LOG& eline( LOG& log );

DllDecl extern LOG& dec( LOG& log );
DllDecl extern LOG& hex( LOG& log );
DllDecl extern LOG& oct( LOG& log );
DllDecl extern LOG& chr( LOG& log );
DllDecl extern LOG& bol( LOG& log );

DllDecl extern LOG& fix( LOG& log );
DllDecl extern LOG& sci( LOG& log );

// common defined LOG channels

DllDecl extern int DBG_SYSRC;
DllDecl extern int DBG_ERROR;
DllDecl extern int DBG_WARN;
DllDecl extern int DBG_TRACE;
DllDecl extern int DBG_ODBC;

// LOG
DllDecl extern void DebugRC( DWORD retCode );
DllDecl extern void LOGf( char* fmt ... );

//////////////////////////////////////////////////////////////////////////////
// ODBCC

struct DllDecl ODBC_FIELD
{
    SQLSMALLINT fCType;
    SQLPOINTER rgbValue;
    SQLINTEGER cbValueMax;
    SQLINTEGER cbValue;
    SQLUINTEGER cbColDef;
    SQLSMALLINT ibScale;

    ODBC_FIELD( void )
    {
        }

    ODBC_FIELD( void* pValue, int cbSize )
    {
        fCType = SQL_C_BINARY;
        rgbValue = pValue;
        cbValueMax = cbSize;
        cbValue = cbSize;
        cbColDef = cbSize;
        ibScale = 0;
        }

    ODBC_FIELD( char* szValue, int cMaxSize )
    {
        fCType = SQL_C_CHAR;
        rgbValue = szValue;
        cbValueMax = cMaxSize;
        cbValue = SQL_NTS;
        cbColDef = cMaxSize;
        ibScale = 0;
        }

    ODBC_FIELD( int* pValue )
    {
        fCType = SQL_C_SLONG; // fixme: or SQL_C_SSHORT
        rgbValue = pValue;
        cbValueMax = sizeof( *pValue );
        cbValue = sizeof( *pValue );
        cbColDef = sizeof( *pValue );
        ibScale = 0;
        }

    ODBC_FIELD( long* pValue )
    {
        fCType = SQL_C_SLONG;
        rgbValue = pValue;
        cbValueMax = sizeof( *pValue );
        cbValue = sizeof( *pValue );
        cbColDef = sizeof( *pValue );
        ibScale = 0;
        }

    ODBC_FIELD( unsigned long* pValue )
    {
        fCType = SQL_C_ULONG;
        rgbValue = pValue;
        cbValueMax = sizeof( *pValue );
        cbValue = sizeof( *pValue );
        cbColDef = sizeof( *pValue );
        ibScale = 0;
        }

    void SetNull( void ) 
        { cbValue = SQL_NULL_DATA; }

    void SetDefault( void ) 
        { cbValue = SQL_DEFAULT_PARAM; }

    BOOL IsNull( void ) 
        { return cbValue == SQL_NULL_DATA; }

    void SetNotNull( void ) 
        { cbValue = ( fCType == SQL_C_CHAR ) ? SQL_NTS : cbValueMax; }
    };

// You should declare ODBC_<char[40]>
//
template <typename Element>
struct DllDecl ODBC_ : public ODBC_FIELD
{
    Element value;

    ODBC_( void )
    {
        value[ 0 ] = '\0';
        fCType = SQL_C_CHAR;
        rgbValue = value;
        cbValueMax = sizeof( value );
        cbValue = SQL_NTS;
        cbColDef = sizeof( value );
        ibScale = 0;
        }

    char* operator= ( char* string ) 
        { strcpy( value, ( string ? string : "" ) ); cbValue = SQL_NTS; return value; }
    char* operator= ( const char* string ) 
        { strcpy( value, ( string ? string : "" ) ); cbValue = SQL_NTS; return value; }
    operator char*( void ) 
        { return value; }
    };

struct DllDecl ODBC_LONGVARCHAR : public ODBC_FIELD
{
    CHAR value[ 1024 ];

    ODBC_LONGVARCHAR( int fld_size )
    {
        value[ 0 ] = '\0';
        fCType = SQL_C_CHAR;
        rgbValue = value;
        cbValueMax = sizeof( value );
        cbValue = SQL_NTS;
        cbColDef = sizeof( value );
        ibScale = 0;
        }

    char* operator= ( char* string ) 
        { strcpy( value, ( string ? string : "" ) ); cbValue = SQL_NTS; return value; }
    operator char*( void ) 
        { return value; }
    };

struct DllDecl ODBC_ULONG : public ODBC_FIELD
{
    SQLUINTEGER value;

    ODBC_ULONG( void )
    {
        fCType = SQL_C_ULONG;
        rgbValue = &value;
        cbValueMax = sizeof( value );
        cbValue = sizeof( value );
        cbColDef = sizeof( value );
        ibScale = 0;
        }

    SQLUINTEGER operator= ( SQLUINTEGER p ) 
        { return value = p; }

    operator SQLUINTEGER( void ) 
        { return value; }
    };

struct DllDecl ODBC_SLONG : public ODBC_FIELD
{
    SQLINTEGER value;

    ODBC_SLONG( void )
    {
        fCType = SQL_C_SLONG;
        rgbValue = &value;
        cbValueMax = sizeof( value );
        cbValue = sizeof( value );
        cbColDef = sizeof( value );
        ibScale = 0;
        }

    SQLINTEGER operator= ( SQLINTEGER p ) { return value = p; }
    operator SQLINTEGER( void ) { return value; }
    };

struct DllDecl ODBC_USHORT : public ODBC_FIELD
{
    SQLUSMALLINT value;

    ODBC_USHORT( void )
    {
        fCType = SQL_C_USHORT;
        rgbValue = &value;
        cbValueMax = sizeof( value );
        cbValue = sizeof( value );
        cbColDef = sizeof( value );
        ibScale = 0;
        }

    SQLUSMALLINT operator= ( SQLUSMALLINT p ) { return value = p; }
    operator SQLUSMALLINT( void ) { return value; }
    };

struct DllDecl ODBC_SSHORT : public ODBC_FIELD
{
    SQLSMALLINT value;

    ODBC_SSHORT( void )
    {
        fCType = SQL_C_SSHORT;
        rgbValue = &value;
        cbValueMax = sizeof( value );
        cbValue = sizeof( value );
        cbColDef = sizeof( value );
        ibScale = 0;
        }

    SQLSMALLINT operator= ( SQLSMALLINT p ) { return value = p; }
    operator SQLSMALLINT( void ) { return value; }
    };

struct DllDecl ODBC_DOUBLE : public ODBC_FIELD
{
    SQLDOUBLE value;

    ODBC_DOUBLE( void )
    {
        fCType = SQL_C_DOUBLE;
        rgbValue = &value;
        cbValueMax = sizeof( value );
        cbValue = sizeof( value );
        cbColDef = sizeof( value );
        ibScale = 0;
        }

    SQLDOUBLE operator= ( SQLDOUBLE p ) { return value = p; }
    operator SQLDOUBLE( void ) { return value; }
    };

struct DllDecl ODBC_FLOAT : public ODBC_FIELD
{
    SQLREAL value;

    ODBC_FLOAT( void )
    {
        fCType = SQL_C_FLOAT;
        rgbValue = &value;
        cbValueMax = sizeof( value );
        cbValue = sizeof( value );
        cbColDef = sizeof( value );
        ibScale = 0;
        }

    SQLREAL operator= ( SQLREAL p ) { return value = p; }
    operator SQLREAL( void ) { return value; }
    };

struct DllDecl ODBC_TIME : public ODBC_FIELD
{
    TIME_STRUCT value;

    ODBC_TIME( void )
    {
        memset( &value, 0, sizeof( value ) );
        fCType = SQL_C_TIME;
        rgbValue = &value;
        cbValueMax = sizeof( value );
        cbValue = sizeof( value );
        cbColDef = sizeof( value );
        ibScale = 0;
        }
    };

struct DllDecl ODBC_DATE : public ODBC_FIELD
{
    DATE_STRUCT value;

    ODBC_DATE( void )
    {
        memset( &value, 0, sizeof( value ) );
        fCType = SQL_C_DATE;
        rgbValue = &value;
        cbValueMax = sizeof( value );
        cbValue = sizeof( value );
        cbColDef = sizeof( value );
        ibScale = 0;
        }
    };

struct DllDecl ODBC_TIMESTAMP : public ODBC_FIELD
{
    TIMESTAMP_STRUCT value;

    ODBC_TIMESTAMP( void )
    {
        memset( &value, 0, sizeof( value ) );
        fCType = SQL_C_TIMESTAMP;
        rgbValue = &value;
        cbValueMax = sizeof( value );
        cbValue = sizeof( value );
        cbColDef = sizeof( value );
        ibScale = 0;
        }

    SQLINTEGER operator - ( ODBC_TIMESTAMP& t );
    };

class DllDecl ODBC_SESSION
{
    friend class ODBC_STATEMENT;

    SQLRETURN retcode;
    SQLHENV henv;
    SQLHDBC hdbc;

public:

    ODBC_SESSION( void );
    ~ODBC_SESSION( void );

    BOOL AnyError( void );
    BOOL Error( void );
    void Perror( char* where = NULL );

    ODBC_SESSION& Connect( char* datasource, char* username, char* password,
                           int timeout = 0 );
    ODBC_SESSION& Disconnect( void );

    ODBC_SESSION& AutoCommitOn( void );
    ODBC_SESSION& AutoCommitOff( void );

    ODBC_SESSION& Commit( void );
    ODBC_SESSION& Rollback( void );
    };

class DllDecl ODBC_STATEMENT
{
    ODBC_SESSION* pSess;

    SQLRETURN retcode;
    SQLHSTMT hstmt;
    char* last_stmt;

    int icol;
    int ipar;

    ODBC_STATEMENT& BindColumn( SQLUSMALLINT icol, ODBC_FIELD& field );

    ODBC_STATEMENT& BindParameter( SQLUSMALLINT ipar, ODBC_FIELD& field,
        SQLSMALLINT fSqlType, SQLSMALLINT fParamType = SQL_PARAM_INPUT );

public:

    ODBC_STATEMENT( ODBC_SESSION* p_sess, char* cursor_name = NULL );
    ~ODBC_STATEMENT( void );

    BOOL AnyError( void );
    BOOL Error( void );
    void Perror( char* where = NULL );

    ODBC_STATEMENT& Reconstruct( void );

    ODBC_STATEMENT& SetConcurrency( SQLUINTEGER option );

    ODBC_STATEMENT& ExecuteDirect( char* statement );

    ODBC_STATEMENT& Prepare( char* statement );
    ODBC_STATEMENT& Execute( void );

    ODBC_STATEMENT& operator << ( ODBC_FIELD& field );
    ODBC_STATEMENT& operator >> ( ODBC_FIELD& field );

    ODBC_STATEMENT& Fetch( void );
    ODBC_STATEMENT& Cancel( void );
    };

//////////////////////////////////////////////////////////////////////////////
// Connection Manager

class QCPortPool;
class QCPort;
class QCPort_TCP;
class QCPort_Serial;
class ProtocolClass;

template List<QCPort>;

struct TCP_Listener_Parameters
{
    QCPortPool* pool;
    unsigned long local_IP_address; // should be INADDR_ANY;
    unsigned short local_TCP_port;
    ProtocolClass* seed;
    };

class QCPortPool
{
    friend QCPort;
    friend QCPort_TCP;
    friend QCPort_Serial;

    HANDLE                     hCompletionPort;
    volatile bool              isTerminating;
    volatile int               dispatcherCount;

    List<QCPort>               ports;
    List<QCPort>               inactivePorts;

    static DWORD WINAPI QIO_Dispatcher_Thread ( LPVOID thisPortPool );
    static DWORD WINAPI TCP_Listener_Thread( LPVOID thisPortPool );

public:

    QCPortPool( void );
    ~QCPortPool( void );

    void Initialize( int cDispatchers );
    void SignalTerminate( void );
    void WaitTerminate( void );

    void Dump( void );

    int GetDispatcherCount( void ) const { return dispatcherCount; }

    void Start_TCP_Listener( TCP_Listener_Parameters& params )
    {
        HANDLE h = ::CreateThread( NULL, 0, TCP_Listener_Thread, &params, 0, NULL );
        ::CloseHandle( h );
        }
    };

class ProtocolClass // abstract class
{
    friend QCPort;
    friend QCPort_TCP;
    friend QCPort_Serial;

protected:

    QCPort*                    port;

public:

    Mutex                      mutex;

    ProtocolClass( void )
        : port( NULL )
    {}

    // Pure virtual methods

    // Clone() is used by the Listener thread to create protocol
    // instance dynamically by the given seed.
    virtual ProtocolClass* Clone () = 0;

    virtual bool OnReadCompleted( DWORD dwIoSize ) = 0;
    virtual bool OnWriteCompleted( DWORD dwIoSize ) = 0;
    virtual bool OnError( DWORD dwErrorCode ) = 0;
    virtual bool OnConnect () = 0;
    virtual bool OnRemoteDisconnect () = 0;

    virtual ~ProtocolClass( void )
    {
        TRACE( this << " ProtocolClass::~ProtocolClass" );
        }
    };

class QCPort // abstract class
{
    friend ProtocolClass;
    friend QCPortPool;

protected:

    enum PortType
    {
        Serial_Port = 0,
        TCP_Port    = 1,
        UDP_Port    = 2
        };

    unsigned long              magic;
    PortType                   type;

    List<QCPort>::Anchor<QCPortPool> pool;

    volatile bool              fConnected;
    HANDLE                     hCP;              // completion port
    OVERLAPPED                 Overlapped_Read;  // asynchronous I/O Read
    OVERLAPPED                 Overlapped_Write; // asynchronous I/O Write

public:

    ProtocolClass*             protocol;

    bool IsConnected () { return fConnected; }

    bool IsTCP () { return type == TCP_Port; }
    bool IsUDP () { return type == UDP_Port; }
    bool IsSerial () { return type == Serial_Port; }

    // Pure virtual methods
    virtual bool DispatchIO( DWORD dwIoSize, OVERLAPPED* lpOverlapped ) = 0;
    virtual void DispatchError( DWORD rc ) = 0;
    virtual bool PostRead( void* inputDataBuf, DWORD maxInputDataLen ) = 0;
    virtual bool PostWrite( void* outputDataBuf, DWORD outputDataLen ) = 0;

    // Constructor

    QCPort( PortType t, QCPortPool* ownedBy, ProtocolClass* protocolInstance  )
    {
        magic = 0x30421134;
        type = t;

        hCP = NULL;
        memset( &Overlapped_Read, 0, sizeof( Overlapped_Read ) );
        memset( &Overlapped_Write, 0, sizeof( Overlapped_Write ) );

        pool.Initialize( this, ownedBy );
        pool.LinkAsLast( pool->ports );

        protocol = protocolInstance;
        protocol->port = this;

        fConnected = false;
        }

    virtual ~QCPort( void )
    {
        magic = 0;
        TRACE( this << " QCPort::~QCPort" );
        }

    // Port is valid?

    bool HasMagic ()
    {
        return magic == 0x30421134 
        && type >= Serial_Port && type <= UDP_Port; 
        }
    };

class QCPort_TCP : public QCPort
{
public:

    const char*                IP_address;
    unsigned short             TCP_port;

    SOCKET                     hsock;            // connection socket

public:

    QCPort_TCP( QCPortPool* ownedBy, ProtocolClass* protocolInstance  )
        : QCPort( QCPort::TCP_Port, ownedBy, protocolInstance )
    {
        hsock = NULL;
        }

    virtual ~QCPort_TCP( void )
    {
        TRACE( this << " QCPort_TCP::~QCPort_TCP" );

        CloseConnection ();
        }

    bool OpenConnection( SOCKET hSocket );
    bool OpenConnection( const char* remote_addr, unsigned short remote_port );
    void CloseConnection( bool graceful = true );

    // virtual methods
    virtual bool DispatchIO( DWORD dwIoSize, OVERLAPPED* lpOverlapped );
    virtual void DispatchError( DWORD rc );
    virtual bool PostRead( void* inputDataBuf, DWORD maxInputDataLen );
    virtual bool PostWrite( void* outputDataBuf, DWORD outputDataLen );
    };

class QCPort_Serial : public QCPort
{
    HANDLE                     hComPort;         // handle to com port

public:

    QCPort_Serial( QCPortPool* ownedBy, ProtocolClass* protocolInstance  )
        : QCPort( QCPort::Serial_Port, ownedBy, protocolInstance )
    {
        hComPort = NULL;
        }

    virtual ~QCPort_Serial( void )
    {
        TRACE( this << " QCPort_Serial::~QCPort_Serial" );

        CloseConnection ();
        }

    bool OpenConnection
    (
        const char* port_name,
        DWORD p_baud_rate = CBR_9600,
        BYTE p_byte_size  = 8,
        BYTE p_parity     = NOPARITY,
        BYTE p_stop_bits  = ONESTOPBIT
        );

    void CloseConnection( void );

    // virtual methods
    virtual bool DispatchIO( DWORD dwIoSize, OVERLAPPED* lpOverlapped );
    virtual void DispatchError( DWORD rc );
    virtual bool PostRead( void* inputDataBuf, DWORD maxInputDataLen );
    virtual bool PostWrite( void* outputDataBuf, DWORD outputDataLen );
    };

/*
    ProtocolClass* csta = new CSTA_ProtocolClass ();
    QCPort_TCP* port = new QCPort_TCP( pool, csta );
    port->OpenConnection( addr, port );
    // everything here happens auto-magically
    port->CloseConnection ();
*/

//////////////////////////////////////////////////////////////////////////////
// NT Service Manager

class DllDecl SERVICE
{
    BOOL fService; // flag indicating 'is this process a service?'

    volatile BOOL fServiceTerminating;

    SERVICE_STATUS_HANDLE hService;
    SERVICE_STATUS ServiceStatus;

    LPSTR sz_ServiceName;
    LPSTR sz_ServiceDisplayName;
    TCHAR sz_ModulePath[ 512 ];

    LPSERVICE_MAIN_FUNCTION pMain;

public:

    SERVICE(
        LPSTR name,
        LPSTR displayname = NULL,
        LPSTR modulepath = NULL,
        LPSERVICE_MAIN_FUNCTION main_foo = NULL
        );

    LPSTR Name ()
        { return sz_ServiceName; }

    LPSTR FullName ()
        { return sz_ServiceDisplayName; }

    LPSTR ModulePath ()
        { return sz_ModulePath; }

    BOOL IsService ()
        { return fService; }

    VOID SetNotService ()
        { fService = FALSE; }

    BOOL IsTerminating ()
        { return fServiceTerminating; }

    VOID SetTerminating ()
        { fServiceTerminating = TRUE; }

    BOOL Install(
        LPSTR dependencies = NULL,
        LPSTR username = NULL,
        LPSTR password = NULL
        );

    BOOL Remove( VOID );

    BOOL Start( VOID );
    BOOL Stop( VOID );

    BOOL QueryStatus( SERVICE_STATUS& );
    VOID DebugStatus( SERVICE_STATUS& );
    BOOL DebugStatus( VOID );

    BOOL IsRunning( VOID );
    BOOL IsStarting( VOID );
    BOOL IsStopped( VOID );
    BOOL StartNow( VOID );
    BOOL EnsureServiceIsStarted( long timeOut, BOOL fTryStart );
        
//
// Service Controller interaction:
//
    VOID Dispatch( VOID );

    BOOL
    NotifyController(
        LPHANDLER_FUNCTION ServiceControlHandler
        );

    BOOL
    UpdateStatus(
        DWORD Status,
        DWORD waithint = 5000L    // 5 seconds
        );

    BOOL
    UpdateStatusInterrogate(
        DWORD waithint = 5000L    // 5 seconds
        );

    VOID
    FailStart(
        DWORD Win32Code,
        DWORD PrivateCode
        );
    };

} // namespace CTsvcLIB


#endif // _CT_SVC_LIB_H_INCLUDED