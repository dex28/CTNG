/*
    Project: ASN1Lib

    Module: asn-oid.Cpp

    Description: ASN.1 OBJECT IDENTIFIER

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "ASN1-Implementation.h"

using namespace std;

AsnOid::~AsnOid()
{
    // MEMMGR delete oid;
}

AsnType *AsnOid::Clone() const
{
  return new(memBlock) AsnOid(memBlock);
}

// Initializes an AsnOid with a string and it's length.
// The string should hold the encoded OID.
// The string is copied
void AsnOid::Set (const uint8 *encOid, size_t len)
{
    if (encOid != oid)
    {
        octetLen = len;
        oid = new(memBlock) uint8[octetLen];
        memcpy (oid, encOid, octetLen);
    }
}

// Inits an AsnOid from another OID.
// The oid string is copied.
void AsnOid::Set (const AsnOid &o)
{
    if (&o != this)
    {
        octetLen = o.octetLen;
        oid = new(memBlock) uint8[octetLen];
        memcpy (oid, o.oid, octetLen);
    }
}

// Given some arc numbers, an AsnOid is built.
// Set (1, 2, 3, 4, 5, -1, -1, -1, -1, -1, -1) results in
// oid { 1 2 3 4 5 }.  The first negative arc number represnts
// the end of the arc numbers - at least 2 are required.
// The prototype in the AsnOid class provides default -1 parameters
// so you only need to provide the number of arc number in the oid
// as params. (eg Set (1,2,3,4,5))
void AsnOid::Set( unsigned long int a1, unsigned long int a2, long int a3, long int a4, long int a5, long int a6, long int a7, long int a8, long int a9, long int a10, long int a11 )
{
    long int arcNumArr[ 11 ];
    uint8 buf[16*5];  // make big enough for max oid with 11 arcs
    uint8 *tmpBuf;
    size_t totalLen;
    size_t elmtLen;
    long int tmpArcNum;
    long int headArcNum;

    tmpBuf = buf;

    arcNumArr[0] = a1;
    arcNumArr[1] = a2;
    arcNumArr[2] = a3;
    arcNumArr[3] = a4;
    arcNumArr[4] = a5;
    arcNumArr[5] = a6;
    arcNumArr[6] = a7;
    arcNumArr[7] = a8;
    arcNumArr[8] = a9;
    arcNumArr[9] = a10;
    arcNumArr[10] = a11;

    // munge together first oid arc numbers
    headArcNum = tmpArcNum = (arcNumArr[0] * 40) + arcNumArr[1];

    // figure encoded length for this arc number
    for (elmtLen = 1; (tmpArcNum >>= 7) != 0; elmtLen++)
	;

    // write bytes except the last/least significant of the head arc number
    // more bit is on
    totalLen = elmtLen;
    for (size_t i = 1; i < elmtLen; i++)
    {
        *(tmpBuf++) = (uint8)( 0x80 | (headArcNum >> ((elmtLen-i)*7)) );
    }

    // write least significant (more bit is off)
    *(tmpBuf++) = (uint8)( 0x7f & headArcNum );

    // repeat for the rest of the arc numbers
    for ( i = 2; (i < 11) && (arcNumArr[i] > 0); i++)
    {
        tmpArcNum = arcNumArr[i];
        for (elmtLen = 1; (tmpArcNum >>= 7) != 0; elmtLen++)
	    ;
        totalLen += elmtLen;
        tmpArcNum = arcNumArr[i];
        for (size_t j = 1; j < elmtLen; j++)
        {
            *(tmpBuf++) = (uint8)( 0x80 | (tmpArcNum >> ((elmtLen-j)*7)) );
        }
        *(tmpBuf++) = (uint8)( 0x7f & tmpArcNum );
    }

    oid = new(memBlock) uint8[ totalLen ];
    memcpy (oid, buf, totalLen);
    octetLen = totalLen;

}  // AsnOid::Set



// Like Set except frees old oid value first
void AsnOid::ReSet (const uint8 *encOid, size_t len)
{
    if (encOid != oid)
    {
        // MEMMGR delete oid;
        Set (encOid, len);
    }
}

// Like Set except frees old oid value first
void AsnOid::ReSet (const AsnOid &o)
{
    if (&o != this)
    {
        // MEMMGR delete oid;
        Set (o);
    }
}

void AsnOid::ReSet (unsigned long int a1, unsigned long int a2, long int a3, long int a4, long int a5, long int a6, long int a7, long int a8, long int a9, long int a10, long int a11)
{
    // MEMMGR delete oid;
    Set (a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
}


// returns the number of arc numbers in the OID value
unsigned long int AsnOid::NumArcs() const
{
    unsigned long int numArcs = 0;

    for ( size_t i=0; i < octetLen; )
    {
        // skip octets in this arc num with the 'more' bit set
        for (; (i < octetLen) && (oid[i] & 0x80); i++)
	    ;

        // skip last octet in this arc num (no more bit)
        i++;

        numArcs++;
    }

    // add one to return value because the first two arcs are
    // crunched together into a single one.
    return numArcs +1;

}  // AsnOid::NumArcs

bool AsnOid::OidEquiv (const AsnOid &o) const
{
    return o.octetLen == octetLen && ! memcmp( o.oid, oid, octetLen );
}


// Decodes the content of a BER OBJECT IDENTIFIER value and puts
// the results in this AsnOid object.
void AsnOid::BDecContent (AsnBuf& b, AsnTag tagId, AsnLen elmtLen, AsnLen &bytesDecoded)
{
    // treat like primitive octet string
    octetLen = elmtLen;
    oid =  new(memBlock) uint8[ elmtLen ];
    b.CopyOut (oid, elmtLen);

    if (b.ReadError())
    {
        throw "ERROR I0037: AsnOid.BDecOctetString(): Decoded past end of data";
    }
    bytesDecoded += elmtLen;
} // AsnOid::BDecContent

AsnLen AsnOid::BEnc (AsnBuf& b)
{
    AsnLen l;
    l =  BEncContent (b);
    l += BEncDefLen (b, l);
    l += BEncTag1 (b, UNIV, PRIM, OID_TAG_CODE);
    return l;
}

void AsnOid::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    if (BDecTag (b, bytesDecoded) != MAKE_TAG_ID (UNIV, PRIM, OID_TAG_CODE))
    {
	    throw "ERROR I0038: AsnOid.BDec(): Tag on OBJECT IDENTIFIER is wrong.";
    }
    elmtLen = BDecLen (b, bytesDecoded);

    BDecContent (b, MAKE_TAG_ID (UNIV, PRIM, OID_TAG_CODE), elmtLen, bytesDecoded);
}

AsnLen AsnOid::BEncContent (AsnBuf& b)
{
    b.PutSegRvs (oid, octetLen);
    return octetLen;
}

// Prints an AsnOid in ASN.1 Value Notation.
// Decodes the oid to get the individual arc numbers
void AsnOid::Print (CTsvcLIB::LOG &os) const
{
    // print oid in
    os << "OBJECT ID { ";

    if ( ! oid )
        os << "VOID";
    else
    {
        unsigned int i = 0;

        // un-munge first two arc numbers
        for ( unsigned long arcNum = 0; (i < octetLen) && (oid[i] & 0x80); i++)
            arcNum = (arcNum << 7) + (oid[i] & 0x7f);

        arcNum = (arcNum << 7) + (oid[i] & 0x7f);
        i++;
        unsigned long firstArcNum = arcNum / 40;
        if ( firstArcNum > 2 )
            firstArcNum = 2;

        os << firstArcNum  << ", " << arcNum - ( firstArcNum * 40 );

        for (; i < octetLen; )
        {
            for (arcNum = 0; (i < octetLen) && (oid[i] & 0x80); i++)
                arcNum = (arcNum << 7) + (oid[i] & 0x7f);

            arcNum = (arcNum << 7) + (oid[i] & 0x7f);
            i++;
            os << ", " << arcNum;
            }
        }

    os << " }";

    } // AsnOid::Print
