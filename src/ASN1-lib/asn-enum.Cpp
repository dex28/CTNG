/*
    Project: ASN1Lib

    Module: asn-enum.Cpp

    Description: AsnEnum (ASN.1 ENUMERATED) class

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "ASN1-Implementation.h"

using namespace std;

AsnType *AsnEnum::Clone() const
{
    PRINTERR( "ASN.1 Error: AsnEnum::Clone() called" );
    abort();
    return NULL;
}

AsnLen AsnEnum::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;
    l += BEncTag1 (b, UNIV, PRIM, ENUM_TAG_CODE);
    return l;
}

void AsnEnum::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    if (BDecTag (b, bytesDecoded) != MAKE_TAG_ID (UNIV, PRIM, ENUM_TAG_CODE))
    {
	    throw "ERROR I0014: AsnEnum.BDec(): Tag on ENUMERATED is wrong.";
    }

    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, MAKE_TAG_ID (UNIV, PRIM, ENUM_TAG_CODE), elmtLen, bytesDecoded);
}

