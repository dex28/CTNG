/*
    Project: ASN1Lib

    Module: asn-bool.Cpp

    Description: AsnBool (ASN.1 BOOLEAN) class

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "ASN1-Implementation.h"

using namespace std;

AsnType *AsnBool::Clone() const
{
    return new(memBlock) AsnBool(memBlock);
}

AsnLen AsnBool::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;
    l += BEncTag1 (b, UNIV, PRIM, BOOLEAN_TAG_CODE);
    return l;
}

void AsnBool::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    if (BDecTag (b, bytesDecoded) != MAKE_TAG_ID (UNIV, PRIM, BOOLEAN_TAG_CODE))
    {
	    throw "ERROR I0011: AsnBool.BDec(): Tag on BOOLEAN wrong.";
    }
    elmtLen = BDecLen (b, bytesDecoded);

    BDecContent (b, MAKE_TAG_ID (UNIV, PRIM, BOOLEAN_TAG_CODE), elmtLen, bytesDecoded);
}

// Decodes the content of a BOOLEAN and sets this object's value
// to the decoded value. Flags an error if the length is wrong
// or a read error occurs.
void AsnBool::BDecContent (AsnBuf& b, AsnTag tagId, AsnLen elmtLen, AsnLen &bytesDecoded)
{
    if (elmtLen != 1)
    {
        throw "ERROR I0012: AsnBool.BDecContent(): Boolean value too long";
    }

    value = (b.GetByte() != 0);
    bytesDecoded++;

    if (b.ReadError())
    {
        throw "ERROR I0013: AsnBool.BDecContent(): Decoded past end of data";
    }
}

AsnLen AsnBool::BEncContent (AsnBuf& b)
{
    b.PutByteRvs (value ? 0xFF : 0);
    return 1;
}

// print the BOOLEAN's value in ASN.1 value notation to the given log stream
void AsnBool::Print (CTsvcLIB::LOG &os) const
{
    os << "BOOL " << (value ? "true" : "false");
}
