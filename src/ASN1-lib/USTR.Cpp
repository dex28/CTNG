/*
    Project: ASN1Lib

    Module: USTR.Cpp

    Description: USTR (yet another String) class

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "ASN1-Lib.h"

using namespace std;

void USTR:: AllocHeader( Type t, int len, MemBlock* mem )
{
    if ( mem )
        datap = (Header*) new(mem) uint8[ sizeof( Header ) + len + 1 ];
    else
        datap = (Header*) new uint8[ sizeof( Header ) + len + 1 ];

    datap++;

    datap[-1].ind = t;
    datap[-1].length = len;
    datap[-1].refCount = 1;

    // If USTR is allocated in Garbage Collected MemBlock, then
    // we must not be able to destruct it ever, so one is added to
    // initial reference count calculating MemPool that is refering to it.
    //
    if ( mem )
        datap[-1].refCount++;
    }

void USTR:: IncRefCount( void )
{
    if ( ! datap )
        return;

    ::InterlockedIncrement( &datap[-1].refCount );
    }

void USTR:: DecRefCount( void )
{
    if ( ! datap )
        return;

    long refCount = ::InterlockedDecrement( &datap[-1].refCount );

    if ( refCount > 0 )
        return;

    // refCount became zero. It is on us to destroy allocated area.
    //
    datap--;
    delete[] (uint8*) datap;
    datap = NULL;
    }

USTR:: USTR( const USTR& str )
{
    datap = str.datap;
    IncRefCount ();
    }

USTR:: USTR( const uint8* ptr, int len )
{
    datap = NULL;

    if ( ! ptr )
        return;

    AllocHeader( Binary, len );
    memcpy( vbin, ptr, len );
    vbin[ len ] = 0;
    }

USTR:: USTR( const char* ptr )
{
    datap = NULL;

    if ( ! ptr )
        return;

    int len = strlen( ptr );
    AllocHeader( Ascii, len );
    memcpy( vstr, ptr, len );
    vstr[ len ] = 0;
    }

USTR:: USTR( const AsnOcts& ptr )
{
    datap = NULL;

    int len = ptr.Len ();
    AllocHeader( Binary, len );
    memcpy( vbin, (const uint8*)ptr, len );
    vbin[ len ] = 0;
    }

USTR:: USTR( const AsnOcts* ptr )
{
    datap = NULL;

    if ( ! ptr )
        return;

    int len = ptr->Len ();
    AllocHeader( Binary, len );
    memcpy( vbin, (const uint8*)*ptr, len );
    vbin[ len ] = 0;
    }

USTR:: USTR( const AsnOid& ptr )
{
    datap = NULL;

    int len = ptr.Len ();
    AllocHeader( Binary, len );
    memcpy( vbin, (const uint8*)ptr, len );
    vbin[ len ] = 0;
    }

USTR:: USTR( const AsnOid* ptr )
{
    datap = NULL;

    if ( ! ptr )
        return;

    int len = ptr->Len ();
    AllocHeader( Binary, len );
    memcpy( vbin, (const uint8*)*ptr, len );
    vbin[ len ] = 0;
    }

USTR:: USTR( MemBlock* memBlock, const char* ptr )
{
    datap = NULL;

    if ( ! ptr )
        return;

    int len = strlen( ptr );
    AllocHeader( Ascii, len, memBlock );
    memcpy( vstr, ptr, len );
    vstr[ len ] = 0;
    }

USTR:: USTR( MemBlock* memBlock, const AsnOcts& ptr )
{
    datap = NULL;

    int len = ptr.Len ();
    AllocHeader( Binary, len, memBlock );
    memcpy( vbin, (const uint8*)ptr, len );
    vbin[ len ] = 0;
    }

USTR:: USTR( MemBlock* memBlock, const AsnOcts* ptr )
{
    datap = NULL;

    if ( ! ptr )
        return;

    int len = ptr->Len ();
    AllocHeader( Binary, len, memBlock );
    memcpy( vbin, (const uint8*)*ptr, len );
    vbin[ len ] = 0;
    }

void USTR:: SetNULL( void )
{
    DecRefCount ();
    datap = NULL;
    }

void USTR:: operator = ( const USTR& str )
{
    if ( this == &str )
        return; // nothing to do

    DecRefCount ();
    datap = str.datap;
    IncRefCount ();
    }

void USTR:: operator = ( const char* ptr )
{
    DecRefCount ();

    if ( ! ptr )
        return;

    int len = strlen( ptr );
    AllocHeader( Ascii, len );
    memcpy( vstr, ptr, len );
    vstr[ len ] = 0;
    }

void USTR:: operator = ( const AsnOcts* ptr )
{
    DecRefCount ();

    if ( ! ptr )
        return;

    int len = ptr->Len ();
    AllocHeader( Binary, len );
    memcpy( vbin, (const uint8*)*ptr, len );
    vbin[ len ] = 0;
    }

USTR:: ~USTR( void )
{
    DecRefCount ();
    }

USTR USTR:: toHex() const
{
    if ( datap == NULL )
        return *this;

    char buf[ 256 ];

    char* chp2 = buf;
    uint8* chp = vbin;
    *chp2++ = 'x';

    for ( int j = 0; j < datap[-1].length; j++, chp++ )
    {
        *chp2++ = TO_HEX( *chp >> 4 );
        *chp2++ = TO_HEX( *chp );
        }

    *chp2 = 0;

    return USTR( buf );
    }

void USTR:: CopyTo( USTR& out )
{
    if ( datap )
    {
        out = USTR( vbin, datap[-1].length );
        }
    else
    {
        out.SetNULL ();
        }
    }

bool USTR:: operator == ( const USTR& str ) const
{
    return datap && str.datap
        && datap[-1].length == str.datap[-1].length
        && memcmp( vbin, str.vbin, datap[-1].length ) == 0;
    }

bool USTR:: operator == ( const char* str ) const
{
    return datap && str
        && datap[-1].length == strlen( str )
        && memcmp( vbin, str, datap[-1].length ) == 0;
    }

void USTR:: Print( CTsvcLIB::LOG& os ) const
{
    if ( datap == NULL )
    {
        os << "<null>";
        }
    else if ( datap[-1].ind == Ascii )
    {
        os << "\"";
        char* chp = vstr;
        for ( int j = 0; j < datap[-1].length; j++, chp++ )
            os << char( isprint( *chp ) ? *chp : '.' );
        os << "\"";
        }
    else
    {
        os << "\'";
        uint8* chp = vbin;
        for ( int j = 0; j < datap[-1].length; j++, chp++ )
            os << TO_HEX( *chp >> 4 ) << TO_HEX( *chp );
        os << "\'H";
        }
    }

///////////////////////////////////////////////////////////////////////////////

#ifdef _WIN32

USTR:: USTR( const BSTR bstr )
{
    datap = NULL;

    if ( ! bstr )
        return;

    int len = ::SysStringLen( bstr );
    AllocHeader( Ascii, len );

    wcstombs( vstr, bstr, len );
    vbin[ len ] = 0;
    }

USTR::USTR( SAFEARRAY* psaArray )
{
    datap = NULL;

    if ( ! psaArray )
        return;

    // Checking if it is an one-dimensional array.
    if ( psaArray->cDims != 1 )
        return;

    // Checking if it is an array of bytes.
    if ( psaArray->cbElements != 1 )
        return;

    // Get how many elements are there in the array
    // and allocate USTR area to suit it.
    long len = psaArray->rgsabound[0].cElements;
    AllocHeader( Binary, len );

    if (len > 0 )
    {
        // Locking the array before using its elements.
        ::SafeArrayLock( psaArray );

        // Create USTR based on array data.
        ::memcpy( vbin, (const uint8*)psaArray->pvData, len );

        // Releaseg the array.
        ::SafeArrayUnlock( psaArray );
        }
    }

SAFEARRAY* USTR:: CreateSafeByteArray( void )
{
    // Create one-dimensional array of VT_UI1
    //
    SAFEARRAYBOUND saBound[ 1 ];
    saBound[ 0 ].cElements = Len ();
    saBound[ 0 ].lLbound = 0;

    SAFEARRAY* psaArray = ::SafeArrayCreate( VT_UI1, 1, saBound );

    if ( psaArray == NULL )
        return NULL;

    if ( ! datap )
        return psaArray;

    // Locking the array before using its elements.
    ::SafeArrayLock( psaArray );

    // Fill array data based on USTR.
    ::memcpy( (uint8*)psaArray->pvData, Ptr (), Len () );

    // Releaseg the array.
    ::SafeArrayUnlock( psaArray );

    return psaArray;
    }

#endif // _WIN32
