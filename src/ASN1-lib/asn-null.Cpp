/*
    Project: ASN1Lib

    Module: asn-null.Cpp

    Description: ASN.1 NULL datatype

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "ASN1-Implementation.h"

using namespace std;

AsnType *AsnNull::Clone() const
{
    return new(memBlock) AsnNull(memBlock);
}

void AsnNull::BDecContent (AsnBuf& b, AsnTag tagId, AsnLen elmtLen, AsnLen &bytesDecoded)
{
    if (elmtLen != 0)
    {
        throw "ERROR I0031: AsnNull.BDecContent(): ERROR - NULL values len is non-zero";
    }
} // AsnNull::BDecContent

AsnLen AsnNull::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;
    l += BEncTag1 (b, UNIV, PRIM, NULLTYPE_TAG_CODE);
    return l;
}

void AsnNull::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    if (BDecTag (b, bytesDecoded) != MAKE_TAG_ID (UNIV, PRIM, NULLTYPE_TAG_CODE))
    {
	    throw "ERROR I0032: AsnNull.BDec(): Tag on NULL is wrong.";
    }

    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, MAKE_TAG_ID (UNIV, PRIM, NULLTYPE_TAG_CODE), elmtLen, bytesDecoded);
}

void AsnNull::Print (CTsvcLIB::LOG &os) const
{
    os << "NULL";
}

