#ifndef _asn_incl_h_included
#define _asn_incl_h_included

/*
    Project: ASN1Lib

    Module: ASN1-Lib.h

    Description: ASN1 library declarations

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include <CTsvcLIB.h>

//////////////////////////////////////////////////////////////////////////////

#define PDU_MEMBER_MACROS /*nothing*/

typedef long          AsnIntType;
typedef unsigned long AsnUIntType;

typedef unsigned long AsnTag;
typedef size_t        AsnLen;

typedef unsigned char uint8;

//////////////////////////////////////////////////////////////////////////////

inline char TO_HEX( int fourBits )
{
    return "0123456789ABCDEF"[ fourBits & 0x0F ];
    }

inline int FROM_HEX( int ch )
{
    return
        ( ch >= '0' && ch <= '9' ) ? ch - '0' 
        : ( ch >= 'A' && ch <= 'F' ) ? ch - 'A' + 10 
        : ( ch >= 'a' && ch <= 'f' ) ? ch - 'a' + 10 
        : 0;
    }

//////////////////////////////////////////////////////////////////////////////
// AsnBuf class
//////////////////////////////////////////////////////////////////////////////

class AsnBuf
{
    uint8* dataStart;
    uint8* dataEnd;
    uint8* blkStart;
    uint8* blkEnd;
    uint8* readLoc;
    bool writeError;
    bool readError;

public:

    uint8* DataPtr () const    { return dataStart; }
    size_t DataLen () const    { return dataEnd - dataStart; }

    uint8* BlkPtr () const     { return blkStart; }
    size_t BlkLen () const     { return blkEnd - blkStart; }

    bool   Eod () const        { return readLoc >= dataEnd; }
    bool   ReadError () const  { return readError; }
    bool   WriteError () const { return writeError; }

    // install data for reading or blank blk for writing in buffer
    // must be followed by 'mode' setting method call
    //
    void Init( uint8* data, size_t dataLen )
    {
        readError = writeError = 1;
        blkStart = data;
        blkEnd = data + dataLen;
        dataStart = dataEnd = readLoc = blkEnd;
        }

    void InstallData( uint8* data, size_t dataLen )
    {
        Init( data, dataLen );
        dataStart = blkStart;
        ResetInReadMode();
        }

    void ResetInReadMode ()
    {
        readLoc = dataStart;
        readError = false;
        writeError = true;
        }

    void ResetInWriteRvsMode ()
    {
        dataStart = dataEnd = blkEnd;
        writeError = false;
        readError = true;
        }

    void Skip (size_t skipLen)
    {
        if ( (readLoc + skipLen) > dataEnd )
        {
            readLoc = dataEnd;
            readError = true;
            }
        else
        {
            readLoc += skipLen;
            }
        }

    size_t CopyOut( uint8 *dst, size_t copyLen )
    {
        if (readLoc + copyLen > dataEnd)
        {
            copyLen = dataEnd - readLoc;
            readError = 1;
            }

        memcpy (dst, readLoc, copyLen);
        readLoc += copyLen;
        return copyLen;
        }

    int PeekByte()
    {
        if (Eod())
        {
            readError = true;
            return 0;
            }
        else
        {
            return *readLoc;
            }
        }

    uint8* GetSeg (size_t *lenPtr)
    {
        uint8 *retVal = readLoc;
        if ((readLoc + *lenPtr) > dataEnd)
        {
            *lenPtr = dataEnd - readLoc;
            readLoc = dataEnd;
            return retVal;
            }
        else
        {
            readLoc += *lenPtr;
            return retVal;
            }
        }

    void PutSegRvs( uint8 *seg, size_t segLen)
    {
        if ((dataStart - segLen) < blkStart)
            writeError = true;
        else
        {
            dataStart -= segLen;
            memcpy (dataStart, seg, segLen);
            }
        }

    int GetByte()
    {
        if (Eod())
        {
            readError = true;
            return 0;
            }
        else
        {
            return *(readLoc++);
            }
        }

    void PutByteRvs ( int byte )
    {
        if ( dataStart <= blkStart )
            writeError = true;
        else
            *(--dataStart) = (uint8)byte;
        }

    void Dump( CTsvcLIB::LOG& os, bool show_readLoc = true ) const;
    };

inline CTsvcLIB::LOG& operator << ( CTsvcLIB::LOG& os, AsnBuf& b )
{
    b.Dump( os, /* don't show readLoc */ false );
    return os;
    }

//////////////////////////////////////////////////////////////////////////////
// Memory Manager
//////////////////////////////////////////////////////////////////////////////

class MemPool;
class MemBlock;

struct MemBlockStd
{
    unsigned long signature;
    MemPool* basePool;
    MemBlockStd* next;
    size_t nextFreePtr;
    };

struct MemBlockSpec
{
    unsigned long signature;
    MemBlockSpec* next;
    };

class MemPool
{
    const char* name;

    MemBlockStd* freeList;

    // Statistics
    volatile unsigned long std_allocate_count;
    volatile unsigned long std_free_count;
    volatile unsigned long nstd_allocate_count;
    volatile unsigned long nstd_free_count;

    // Mutex
    CTsvcLIB::Mutex mutex;

public:

    MemPool( const char* verbose_name, int initial_count = 0 );
    ~MemPool( void );

    MemBlockStd* Allocate ();
    void Free( void* ptr );

    void DumpStatistics( CTsvcLIB::LOG& os );
    const char* GetName () const { return name; }
    };

class MemBlock
{
public:
    struct StrStack
    {
        struct Element
        {
            Element* next;
            uint8* str;
            size_t len;
            };

        Element* first;
        Element* lastUsed;
        size_t totalByteLen;
        size_t unusedBits;
        };

    unsigned long signature;
    MemPool* basePool;
    MemBlockStd* stdList;
    MemBlockSpec* specList;
    size_t nextFreePtr;

    // Structure part that is preallocated and exists only in MemBlock i.e.
    // the heading MemBlockInChain structure of the MemBlockInChain list
    struct _G
    {
        // Current indentation
        unsigned int curIndent;

        // Maintains a stack of the components of a bit string or octet string so
        // they can be copied into a single chunk.
        StrStack stk;
        } G;

    // The size of the whole object should be MEMQUANT i.e. 512 bytes\
    // so it can be both allocated on stack or from MemPool
    uint8 arena[ 512 - sizeof(_G) - 5 * sizeof(void*) ];

    MemBlock( MemPool* mp );
    MemBlock( MemPool& mp );

    ~MemBlock( void );

    void* Allocate( size_t n );

    // StrStack methods
    //
    void strStk_Reset();

    void strStk_Push( uint8* str, size_t strLen );

    // copy string pieces (buffer refs) into single block.
    // assumes that the buf is at least totalByteLen byte long.
    //
    void strStk_CopyOut( uint8* buf );

    void* operator new( size_t n, MemPool& mpool ) { return mpool.Allocate (); }
    void operator delete( void* p, MemPool& mpool ) { mpool.Free( p ); }
    void operator delete( void* p ) { ( (MemBlock*)p )->basePool->Free( p ); }

    void* operator new[]( size_t n, MemPool& mpool ) { return mpool.Allocate (); }
    void operator delete[]( void* p, MemPool& mpool ) { mpool.Free( p ); }
    void operator delete[]( void* p ) { ( (MemBlock*)p )->basePool->Free( p ); }
    };

// Usage:
// a) MemBlock m( MemPool& ); ...; destruct m
// b) MemBlock* m = new(MemPool&) MemBlock( MemPool& ); ...; delete m;

inline void* operator new( size_t n, MemBlock* memblock ) { return memblock->Allocate( n ); }
inline void operator delete( void* p, MemBlock* memblock ) { /* nothing to do */ }

#if _MSC_VER >= 1300 // must exist starting MS VS .Net; Error if found in MSVS6.0
inline void* operator new[]( size_t n, MemBlock* memblock ) { return memblock->Allocate( n ); }
inline void operator delete[]( void* p, MemBlock* memblock ) { /* nothing to do */ }
#endif

//////////////////////////////////////////////////////////////////////////////
// AsnType class, all ASN.1 types and objects originate from this class
//////////////////////////////////////////////////////////////////////////////

class AsnType
{
protected:

    MemBlock* memBlock;

public:

    AsnType( MemBlock* mb ) { memBlock = mb; }
    virtual ~AsnType();

    virtual AsnType *Clone() const;

    virtual void BDec( AsnBuf& b, AsnLen &bytesDecoded );
    virtual AsnLen BEnc( AsnBuf& b );

    virtual void Print( CTsvcLIB::LOG & ) const;

    int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);

    int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

    void* operator new( size_t n, MemBlock* memblock )
        { return memblock->Allocate( n ); }

    void operator delete( void* p, MemBlock* memblock )
        { /* nothing to do: MemBlock will garbage collect */ }

    void operator delete( void* p )
        { /* nothing to do: MemBlock will garbage collect */ }

    void* operator new[] ( size_t n, MemBlock* memblock )
        { return memblock->Allocate( n ); }

    void operator delete[] ( void* p, MemBlock* memblock )
        { /* nothing to do: MemBlock will garbage collect */ }

    void operator delete[] ( void* p )
        { /* nothing to do: MemBlock will garbage collect */ }

    MemBlock* GetMemBlock()
        { return memBlock; }
    };

inline CTsvcLIB::LOG& operator << ( CTsvcLIB::LOG& os, const AsnType& v )
{
    v.Print( os );
    return os;
    }

//////////////////////////////////////////////////////////////////////////////
// AsnInt class, ASN.1 INTEGER type
//////////////////////////////////////////////////////////////////////////////

class AsnInt: public AsnType
{
protected:

    AsnIntType value;

public:

    AsnInt( MemBlock* mb )
        : AsnType( mb )
        {}

    AsnInt( MemBlock* mb, AsnIntType val)
        : AsnType( mb )
        , value (val)
        {}

    AsnType* Clone() const;

    operator AsnIntType () const { return value; }
    AsnInt& operator = ( AsnIntType newvalue ) { value = newvalue; return *this; }

    void Set( AsnIntType i )   { value = i; }
    void ReSet( AsnIntType i ) { value = i; }

    AsnLen BEncContent( AsnBuf& b );
    void BDecContent( AsnBuf& b, AsnTag tagId, AsnLen elmtLen, AsnLen& bytesDecoded );
    AsnLen BEnc( AsnBuf& b );
    void BDec( AsnBuf& b, AsnLen& bytesDecoded );

    PDU_MEMBER_MACROS

    void Print( CTsvcLIB::LOG& os ) const;
    };

//////////////////////////////////////////////////////////////////////////////
// AsnBool class, ASN.1 BOOLEAN type
//////////////////////////////////////////////////////////////////////////////

class AsnBool: public AsnType
{
protected:

    bool value;

public:

    AsnBool( MemBlock* mb, const bool val )
        : AsnType( mb )
        , value (val)
        {}

    AsnBool( MemBlock* mb )
        : AsnType( mb )
        {}

    AsnType* Clone() const;

    operator bool() const { return value; }

    AsnBool& operator = ( bool newvalue )
        { value = newvalue; return *this; }

    AsnLen BEnc( AsnBuf& b );
    void BDec( AsnBuf& b, AsnLen& bytesDecoded );

    AsnLen BEncContent( AsnBuf& b );
    void BDecContent( AsnBuf& b, AsnTag tagId, AsnLen elmtLen, AsnLen& bytesDecoded );

    PDU_MEMBER_MACROS

    void Print( CTsvcLIB::LOG& ) const;
    };

//////////////////////////////////////////////////////////////////////////////
// AsnReal class, ASN.1 REAL type
//////////////////////////////////////////////////////////////////////////////

class AsnReal: public AsnType
{
protected:

    double value;

public:

    AsnReal( MemBlock* mb )
        : AsnType( mb )
        , value (0.0)
        {}

    AsnReal ( MemBlock* mb, double val)
        : AsnType( mb )
        , value (val)
        {}

    AsnType* Clone() const;

    operator double() const
        { return value; }

    AsnReal& operator = ( double newvalue )
        { value = newvalue; return *this; }

    AsnLen BEncContent (AsnBuf& b);
    void   BDecContent (AsnBuf& b, AsnTag tagId, AsnLen elmtLen, AsnLen &bytesDecoded);
    AsnLen BEnc (AsnBuf& b);
    void   BDec (AsnBuf& b, AsnLen &bytesDecoded);

    void Print( CTsvcLIB::LOG& os ) const;

    PDU_MEMBER_MACROS
    };

extern const AsnReal PLUS_INFINITY;
extern const AsnReal MINUS_INFINITY;

//////////////////////////////////////////////////////////////////////////////
// AsnOid class, ASN.1 OBJECT IDENTIFIER type
//////////////////////////////////////////////////////////////////////////////

class AsnOid: public AsnType
{
private:

    bool OidEquiv (const AsnOid &o) const;

protected:

    size_t octetLen;
    uint8* oid;

public:

    AsnOid( MemBlock* mb )
        : AsnType( mb )
        , octetLen (0)
        , oid (NULL)
        {}

    AsnOid ( MemBlock* mb, const uint8 *encOid, size_t len)
        : AsnType( mb )
        { Set (encOid, len); }

    AsnOid ( MemBlock* mb, const AsnOid &o)
        : AsnType( mb )
        { Set (o); }

    AsnOid ( MemBlock* mb, unsigned long int a1, unsigned long int a2, long int a3 = -1, long int a4 = -1, long int a5 = -1, long int a6 = -1, long int a7 = -1, long int a8 = -1, long int a9 = -1, long int a10 = -1, long int a11 = -1)
        : AsnType( mb )
        { Set (a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11); }

    ~AsnOid();

    AsnType* Clone() const;

    AsnOid& operator = (const AsnOid &o)
        { ReSet (o); return *this; }

    size_t Len() const
        { return octetLen; }

    const uint8* Str() const
        { return oid; }

    operator uint8* ()
        { return oid; }

    operator const uint8 * () const
        { return oid; }

    unsigned long int NumArcs() const;

    bool operator == (const AsnOid &o) const
        { return OidEquiv( o ); }

    bool operator != (const AsnOid &o) const
        { return ! OidEquiv( o ); }

    // Set methods overwrite oid and octetLen values
    void Set (const uint8 *encOid, size_t len);
    void Set (const AsnOid &o);

    // first two arc numbers are mandatory.  rest are optional since negative arc nums are not allowed in the
    // encodings, use them to indicate the 'end of arc numbers' in the optional parameters
    void Set (unsigned long int a1, unsigned long int a2, long int a3 = -1, long int a4 = -1, long int a5 = -1, long int a6 = -1, long int a7 = -1, long int a8 = -1, long int a9 = -1, long int a10 = -1, long int a11 = -1);


    // ReSet routines are like Set except the old oid value is freed
    void ReSet (const uint8 *encOid, size_t len);
    void ReSet (const AsnOid &o);
    void ReSet (unsigned long int a1, unsigned long int a2, long int a3 = -1, long int a4 = -1, long int a5 = -1, long int a6 = -1, long int a7 = -1, long int a8 = -1, long int a9 = -1, long int a10 = -1, long int a11 = -1);

    AsnLen BEncContent (AsnBuf& b);
    void   BDecContent (AsnBuf& b, AsnTag tagId, AsnLen elmtLen, AsnLen &bytesDecoded);
    AsnLen BEnc (AsnBuf& b);
    void   BDec (AsnBuf& b, AsnLen &bytesDecoded);

    PDU_MEMBER_MACROS

    void Print( CTsvcLIB::LOG& os ) const;
    };

//////////////////////////////////////////////////////////////////////////////
// AsnOcts class, ASN.1 OCTET STRING type
//////////////////////////////////////////////////////////////////////////////

class AsnOcts: public AsnType
{
private:

    int OctsEquiv (const AsnOcts &o) const;

    void FillBitStringStk (AsnBuf& b, AsnLen elmtLen0, AsnLen& bytesDecoded);

    void BDecConsOcts (AsnBuf& b, AsnLen elmtLen, AsnLen &bytesDecoded);

    void FillOctetStringStk (AsnBuf& b, AsnLen elmtLen0, AsnLen &bytesDecoded );

protected:

    size_t octetLen;
    uint8* octs;

public:

    // constructor and Set alway copy strings so destructor can always delete
    AsnOcts( MemBlock* mb )
        : AsnType( mb )
        , octetLen (0)
        , octs (NULL)
        {}

    AsnOcts ( MemBlock* mb, const uint8 *str)
        : AsnType( mb )
        { Set (str); }

    AsnOcts (MemBlock* mb, const uint8 *str, const size_t len)
        : AsnType( mb )
        { Set (str, len); }

    AsnOcts (MemBlock* mb, const AsnOcts &o)
        : AsnType( mb )
        { Set (o); }

    ~AsnOcts();

    AsnType* Clone() const;

    AsnOcts& operator = ( const AsnOcts& o )
        { ReSet (o); return *this; }

    AsnOcts& operator = ( const uint8* str )
        { ReSet (str); return *this; }

    AsnOcts& operator = ( const char* str )
        { ReSet( (uint8*)str ); return *this; }

    // these set the octs and octetLen values
    void Set( const uint8* str, size_t len );
    void Set( const AsnOcts& o );
    void Set( const uint8* str );

    // these free the old octs value and
    // then reset the octs and octetLen values
    void ReSet (const uint8 *str, size_t len);
    void ReSet (const AsnOcts &o);
    void ReSet (const uint8 *str);

    size_t Len() const
        { return octetLen; }

    operator const uint8* () const
        { return octs; }

    operator uint8* ()
        { return octs; }

    bool operator == (const AsnOcts &o) const
        { return OctsEquiv (o) != 0; }

    bool operator != (const AsnOcts &o) const
        { return OctsEquiv (o) == 0; }

    AsnLen BEncContent (AsnBuf& b);
    void   BDecContent (AsnBuf& b, AsnTag tagId, AsnLen elmtLen, AsnLen &bytesDecoded);
    AsnLen BEnc (AsnBuf& b);
    void   BDec (AsnBuf& b, AsnLen &bytesDecoded);

    PDU_MEMBER_MACROS

    void Print (CTsvcLIB::LOG &os) const;
    };

//////////////////////////////////////////////////////////////////////////////
// AsnBits class, ASN.1 BIT STRING type
//////////////////////////////////////////////////////////////////////////////

class AsnBits: public AsnType
{
private:

    bool BitsEquiv( const AsnBits& ab ) const;
    void BDecConsBits( AsnBuf& b, AsnLen elmtLen, AsnLen &bytesDecoded );
    void FillBitStringStk( AsnBuf& b, AsnLen elmtLen0, AsnLen &bytesDecoded );

protected:

    size_t bitLen;
    uint8* bits;

public:

    AsnBits( MemBlock* mb )
        : AsnType( mb )
        { bits = NULL; bitLen = 0; }

    AsnBits( MemBlock* mb, size_t numBits )
        : AsnType( mb )
        { Set (numBits); }

    AsnBits( MemBlock* mb, const uint8 *bitOcts, size_t numBits)
        : AsnType( mb )
        { Set (bitOcts, numBits); }

    AsnBits( MemBlock* mb, const AsnBits& b )
        : AsnType( mb )
        { Set (b); }

    ~AsnBits();

    AsnType* Clone() const;

    AsnBits& operator = ( const AsnBits& b )
        { ReSet (b); return *this; }

    // overwrite existing bits and bitLen values
    void Set( size_t numBits );
    void Set( const uint8* bitOcts, size_t numBits );
    void Set( const AsnBits& b );

    // free old bits value, the reset bits and bitLen values
    void ReSet( size_t numBits );
    void ReSet( const uint8* bitOcts, size_t numBits );
    void ReSet( const AsnBits& b );

    bool operator == ( const AsnBits& ab ) const
        { return BitsEquiv( ab ); }

    bool operator != ( const AsnBits& ab ) const
        { return ! BitsEquiv( ab ); }

    void SetBit( size_t );
    void ClrBit( size_t );
    bool GetBit( size_t ) const;

    size_t BitLen() const              { return bitLen; }

    AsnLen BEncContent( AsnBuf& b );
    void BDecContent( AsnBuf& b, AsnTag tagId, AsnLen elmtLen, AsnLen &bytesDecoded );
    AsnLen BEnc( AsnBuf& b );
    void BDec( AsnBuf& b, AsnLen &bytesDecoded );

    PDU_MEMBER_MACROS

    void Print( CTsvcLIB::LOG& ) const;
    };

//////////////////////////////////////////////////////////////////////////////
// AsnEnum class, ASN.1 ENUMERATED
//////////////////////////////////////////////////////////////////////////////

class AsnEnum: public AsnInt
{
public:

    AsnEnum( MemBlock* mb )
        : AsnInt( mb )
        {}

    AsnEnum ( MemBlock* mb, int i)
        : AsnInt ( mb,  i)
        {}

    AsnType* Clone() const;

    AsnLen BEnc( AsnBuf& b );
    void BDec( AsnBuf& b, AsnLen& bytesDecoded );

    PDU_MEMBER_MACROS
    };

//////////////////////////////////////////////////////////////////////////////
// AsnNull class, ASN.1 NULL
//////////////////////////////////////////////////////////////////////////////

class AsnNull: public AsnType
{
public:

    AsnNull( MemBlock* mb )
        : AsnType( mb )
        {}

    AsnType* Clone() const;

    AsnLen BEncContent( AsnBuf& /*b*/)
        { return 0; }

    void BDecContent( AsnBuf& b, AsnTag tagId, AsnLen elmtLen, AsnLen& bytesDecoded );

    AsnLen BEnc( AsnBuf& b );

    void BDec( AsnBuf& b, AsnLen& bytesDecoded );

    PDU_MEMBER_MACROS

    void Print( CTsvcLIB::LOG& os ) const;
    };

//////////////////////////////////////////////////////////////////////////////
// class USTR
//////////////////////////////////////////////////////////////////////////////

extern CTsvcLIB::LOG& operator << ( CTsvcLIB::LOG& os, const class USTR& str );
// NOTE: inline definition of operator<< follows USTR declaration!

class USTR
{
protected:

    enum Type { Binary, Ascii };

    struct Header
    {
        Type ind;
        long refCount;
        int length;
        };

    union
    {
        Header* datap;
        uint8* vbin;
        char* vstr;
        };

    void AllocHeader( Type t, int len, MemBlock* memBlock = NULL );
    void IncRefCount( void );
    void DecRefCount( void );

public:

    USTR( void )
        : datap( NULL )
    {}

    USTR( const USTR& str );
    USTR( const uint8* ptr, int len );
    USTR( const char* ptr );
    USTR( const AsnOcts& ptr );
    USTR( const AsnOcts* ptr );
    USTR( const AsnOid& ptr );
    USTR( const AsnOid* ptr );

    USTR( MemBlock* memBlock, const uint8* ptr, int len );
    USTR( MemBlock* memBlock, const char* ptr );
    USTR( MemBlock* memBlock, const AsnOcts& ptr );
    USTR( MemBlock* memBlock, const AsnOcts* ptr );

#ifdef _WIN32
    USTR( const BSTR bstr );
    USTR( SAFEARRAY* psaArray );
    SAFEARRAY* CreateSafeByteArray( void );
#endif

    void operator= ( const USTR& str );
    void operator= ( const char* ptr );
    void operator= ( const AsnOcts* ptr );

    ~USTR( void );

    USTR toHex( void ) const;

    void CopyTo( USTR& out );

    operator const char* () const
        { return datap ? vstr : NULL; }

    operator char* ()
        { return datap ? vstr : NULL; }

    const uint8* Ptr () const
        { return datap ? vbin : NULL; }

    unsigned int Len () const
        { return datap ? datap[-1].length : 0; }

    void SetNULL( void );

    bool IsNULL () const
        { return datap == NULL; }

    bool IsBinary () const
        { return datap && datap[-1].ind == Binary; }

    bool operator == ( const USTR& str ) const;

    bool operator == ( const char* str ) const;

    void Print( CTsvcLIB::LOG& os ) const;
/*
    // It is forbidden to allocate USTR on the heap!!!
    void* operator new( size_t n ) { assert(false); return NULL; }
    void operator delete( void* p ) { assert(false); }
    void* operator new[] ( size_t n ) { assert(false); return NULL; }
    void operator delete[] ( void* p ) { assert(false); }
*/
    };

inline CTsvcLIB::LOG& operator << ( CTsvcLIB::LOG& os, const USTR& str )
{
    str.Print( os );
    return os;
    }

#ifdef _WIN32

class ASTR
{
    char str[ 256 ];
public:
    ASTR( BSTR bstr )
        { ::wcstombs( str, bstr, 256 ); }
    operator const char* ()
        { return str; }
    };

#endif

//////////////////////////////////////////////////////////////////////////////

#include "asn-useful.h"

#endif // _asn_incl_h_included
