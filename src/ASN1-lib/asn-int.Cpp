/*
    Project: ASN1Lib

    Module: asn-int.Cpp

    Description: AsnInt (ASN.1 INTEGER) class

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "ASN1-Implementation.h"

using namespace std;

AsnType *AsnInt::Clone() const
{
    return new(memBlock) AsnInt(memBlock);
}

// Encodes BER content of this AsnInt to the given buffer.
// Returns the number of octets written to the buffer.
AsnLen AsnInt::BEncContent (AsnBuf& b)
{
    AsnLen		len;
    AsnUIntType	mask;
    AsnUIntType	dataCpy;

#define MASK	(0x7f80L << ((sizeof (AsnIntType) - 2) * 8))

    dataCpy = value;

    //
    // calculate encoded length of the integer (content)
    //
    mask = MASK;

    if ( (AsnIntType)dataCpy < 0 )
    {
        for (len = sizeof (AsnIntType); len > 1; --len)
        {
            if ((dataCpy & mask) == mask)
                mask >>= 8;
            else
                break;
        }
    }
    else
    {
        for (len = sizeof (AsnIntType); len > 1; --len)
        {
            if ((dataCpy & mask) == 0)
                mask >>= 8;
            else
                break;
        }
    }

    //
    // write the BER integer
    //
    for ( size_t i = 0; i < len; i++)
    {
        b.PutByteRvs (dataCpy);
        dataCpy >>= 8;
    }

    return len;
}

// Decodes the content of a BER INTEGER from the given buffer.
// The value is placed in this object.  tagId is ignored.
// bytesDecoded is incremented by the number of bytes read for this
// integer value.
void AsnInt::BDecContent (AsnBuf& b, AsnTag tagId, AsnLen elmtLen, AsnLen &bytesDecoded)
{
    AsnUIntType byte;

    if (elmtLen > sizeof (AsnIntType))
    {
        throw "ERROR I0015: AsnInt.BDecContent(): Integer is too big to decode.";
    }

    //
    // look at integer value
    //
    byte =  (AsnUIntType) b.GetByte();

    if (byte & 0x80)   // top bit of first byte is sign bit
        value = (-1 << 8) | byte;
    else
        value = byte;

    //
    // write from buffer into AsnIntType
    //
    for ( size_t i = 1; i < elmtLen; i++)
        value = (value << 8) | (AsnUIntType)(b.GetByte());

    bytesDecoded += elmtLen;

    if (b.ReadError())
    {
        throw "ERROR I0016: AsnInt.BDecContent(): Decoded past end of data.";
    }


}  // AsnInt::BDecContent

AsnLen AsnInt::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;
    l += BEncTag1 (b, UNIV, PRIM, INTEGER_TAG_CODE);
    return l;
}

void AsnInt::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    if (BDecTag (b, bytesDecoded) != MAKE_TAG_ID (UNIV, PRIM, INTEGER_TAG_CODE))
    {
	    throw "ERROR I0017: AsnInt.BDec(): Tag on INTEGER is wrong.";
    }

    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, MAKE_TAG_ID (UNIV, PRIM, INTEGER_TAG_CODE), elmtLen, bytesDecoded);
}

void AsnInt::Print (CTsvcLIB::LOG &os) const
{
    os << "INTEGER " << value;
}


