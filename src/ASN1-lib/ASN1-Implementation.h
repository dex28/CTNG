#ifndef _asn_impl_h_included
#define _asn_impl_h_included

/*
    Project: ASN1Lib

    Module: ASN1-Implementation.h

    Description: ASN.1 implementation. It should be included in protocol
        implementation instead of ASN1-Lib.h.

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

//////////////////////////////////////////////////////////////////////////////

#include "ASN1-Lib.h"

#include <cstdlib>
#include <cstring>
#include <cctype>  // for isprint() in << op on AsnOcts
#include <cmath> // to get ieee conversion functions & pow

//////////////////////////////////////////////////////////////////////////////

// Indentation. 'Global' variable for MemBlock decoded data.
//
#define indentG      (memBlock->G.curIndent)
const int stdIndentG = 4;

inline CTsvcLIB::LOG& Indent( CTsvcLIB::LOG& os, unsigned int i )
{
    while( i-- > 0 )
        if ( i % 4 == 2 ) os << "|";
        else os << " ";

    return os;
    }

//////////////////////////////////////////////////////////////////////////////

// used to test if optionals are present
//
inline bool NOT_NULL( void* ptr ) 
{
    return ptr != NULL; 
    }

//////////////////////////////////////////////////////////////////////////////
// Asn-Len: handle ASN.1 length encoding/decoding etc.
//////////////////////////////////////////////////////////////////////////////

const unsigned long INDEFINITE_LEN = ~0UL; // max unsigned value used for indef rep

#ifdef USE_INDEF_LEN

#define BEncEocIfNec(b) \
    BEncEoc (b)

#define BEncConsLen(b, len) \
    2 + BEncIndefLen (b) /* include len for EOC */

#else // default -- use definite length -- usually faster (for encoders) and smaller encodings

#define BEncEocIfNec(b)  /* do nothing */

#define BEncConsLen(b, len)\
    BEncDefLen (b, len)

#endif

#define BEncIndefLen( b)\
    1;\
    b.PutByteRvs (0x80)

/*
 * Use if you know the encoded length will be in [0,127]
 * E.g. for booleans, nulls, any resonable integers and reals.
 *
 * NOTE: this particular Encode Routine does NOT return the length
 * encoded (1).  The length counter must be explicity incremented
 */
#define BEncDefLenTo127( b, len)\
    b.PutByteRvs( (uint8)len )

#define BDEC_2ND_EOC_OCTET( b, bytesDecoded)\
{\
    if ((b.GetByte() != 0) || b.ReadError())\
    TRACE( "ASN.1 Warning: Second octet of EOC not zero" );\
    (bytesDecoded)++;\
}

extern AsnLen BDecLen (AsnBuf& b, AsnLen &bytesDecoded);

extern AsnLen BEncDefLen ( AsnBuf& b, AsnLen len);

extern AsnLen BEncEoc (AsnBuf& b);

extern void   BDecEoc (AsnBuf& b, AsnLen &bytesDecoded);

//////////////////////////////////////////////////////////////////////////////
// Asn-Tag: stuff for dealing with tags
//////////////////////////////////////////////////////////////////////////////

// Tag Id's byte len
//
#define TB  sizeof(AsnTag)

// The MAKE_TAG_ID macro generates the TAG_ID rep for the
// the given class/form/code (rep'd in long integer form)
// if the class/form/code are constants the compiler (should)
// calculate the tag completely --> zero runtime overhead.
// This is good for efficiently comparing tags in switch statements
// (decoding) etc.  because run-time bit fiddling (eliminated) minimized
//
#define MAKE_TAG_ID(cls,fmt,code) \
    ( ( static_cast<AsnTag>(cls) << ( 8 * (TB-1)) ) \
    | ( static_cast<AsnTag>(fmt) << ( 8 * (TB-1)) ) \
    | MAKE_TAG_ID_CODE( static_cast<AsnTag>(code) ) \
    )

#define MAKE_TAG_ID_CODE(cd) \
    ( (cd) < 31    ? MAKE_TAG_ID_CODE1( cd ) \
    : (cd) < 128   ? MAKE_TAG_ID_CODE2( cd ) \
    : (cd) < 16384 ? MAKE_TAG_ID_CODE3( cd ) \
    : MAKE_TAG_ID_CODE4( cd ) )

#define MAKE_TAG_ID_CODE1(cd) \
    ( (cd) << 8 * (TB-1) )

#define MAKE_TAG_ID_CODE2(cd) \
    ( ( 31UL << ((TB-1) * 8) ) \
    | ( (cd) << ((TB-2) * 8) ) \
    )

#define MAKE_TAG_ID_CODE3(cd) \
    ((31UL << ((TB-1) * 8))\
    | (((cd) & 0x3f80) << 9)\
    | ( 0x0080 << ((TB-2) * 8))\
    | (((cd) & 0x007F) << ((TB-3)* 8)) \
    )

#define MAKE_TAG_ID_CODE4(cd) \
    ((31UL << ((TB-1) * 8))\
    | (((cd) & 0x1fc000) << 2)\
    | ( 0x0080 << ((TB-2) * 8))\
    | (((cd) & 0x3f80) << 1)\
    | ( 0x0080 << ((TB-3) * 8))\
    | (((cd) & 0x007F) << ((TB-4)*8)) \
    )

enum BER_CLASS
{
    ANY_CLASS       = -2,
    NULL_CLASS      = -1,
    UNIV            = 0,
    APPL            = (1 << 6),
    CNTX            = (2 << 6),
    PRIV            = (3 << 6)
};

enum BER_FORM
{
    ANY_FORM        = -2,
    NULL_FORM       = -1,
    PRIM            = 0,
    CONS            = (1 << 5)
};

enum BER_UNIV_CODE
{
    NO_TAG_CODE                 = 0,
    BOOLEAN_TAG_CODE            = 1,
    INTEGER_TAG_CODE            = 2,
    BITSTRING_TAG_CODE          = 3,
    OCTETSTRING_TAG_CODE        = 4,
    NULLTYPE_TAG_CODE           = 5,
    OID_TAG_CODE                = 6,
    OD_TAG_CODE                 = 7,
    EXTERNAL_TAG_CODE           = 8,
    REAL_TAG_CODE               = 9,
    ENUM_TAG_CODE               = 10,
    SEQ_TAG_CODE                = 16,
    SET_TAG_CODE                = 17,
    NUMERICSTRING_TAG_CODE      = 18,
    PRINTABLESTRING_TAG_CODE    = 19,
    TELETEXSTRING_TAG_CODE      = 20,
    TT61STRING_TAG_CODE         = 20, // the same as TELETEXSTRING_TAG_CODE
    VIDEOTEXSTRING_TAG_CODE     = 21,
    IA5STRING_TAG_CODE          = 22,
    UTCTIME_TAG_CODE            = 23,
    GENERALIZEDTIME_TAG_CODE    = 24,
    GRAPHICSTRING_TAG_CODE      = 25,
    VISIBLESTRING_TAG_CODE      = 26,
    ISO646STRING_TAG_CODE       = 26, // the same as VISIBLESTRING_TAG_CODE
    GENERALSTRING_TAG_CODE      = 27
};

enum
{
    EOC_TAG_ID = 0
    };

// Tag encoders.  given constant exprs for class form & code in the
// source, these can be optimized by the compiler (eg
// do the shifts and bitwise ors etc)
//
#define BEncTag1( b, class, form, code)\
    1;\
    b.PutByteRvs ((class) | (form) | (code))

#define BEncTag2( b, class, form, code)\
    2;\
    b.PutByteRvs (code);\
    b.PutByteRvs ((class) | (form) | 31)

#define BEncTag3( b, class, form, code)\
    3;\
    b.PutByteRvs ((code) & 0x7F);\
    b.PutByteRvs (0x80 | ((code) >> 7));\
    b.PutByteRvs ((class) | (form) | 31)

#define BEncTag4( b, class, form, code)\
    4;\
    b.PutByteRvs ((code) & 0x7F);\
    b.PutByteRvs (0x80 | ((code) >> 7));\
    b.PutByteRvs (0x80 | ((code) >> 14));\
    b.PutByteRvs ((class) | (form) | 31)

#define BEncTag5( b, class, form, code)\
    5;\
    b.PutByteRvs ((code) & 0x7F);\
    b.PutByteRvs (0x80 | ((code) >> 7));\
    b.PutByteRvs (0x80 | ((code) >> 14));\
    b.PutByteRvs (0x80 | ((code) >> 21));\
    b.PutByteRvs ((class) | (form) | 31)

extern AsnTag BDecTag (AsnBuf& b, AsnLen &bytesDecoded);

#endif // _asn_impl_h_included
