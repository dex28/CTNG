/*
    Project: ASN1Lib

    Module: asn-len.Cpp

    Description: ASN.1 Length manipluation routines

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "ASN1-Implementation.h"

using namespace std;

//
// Encodes the given length to the given buffer.
// returns the number of octets written to the buffer.
//
AsnLen
BEncDefLen (AsnBuf&  b, AsnLen len)
{
    // unrolled for efficiency
    // (check each possibitlity of the 4 byte integer)
    //
    if (len < 128)
    {
        b.PutByteRvs (len);
        return 1;
    }
    else if (len < 256)
    {
        b.PutByteRvs (len);
        b.PutByteRvs (0x81);
        return 2;
    }
    else if (len < 65536)
    {
        b.PutByteRvs (len);
        b.PutByteRvs (len >> 8);
        b.PutByteRvs (0x82);
        return 3;
    }
    else if (len < 16777126)
    {
        b.PutByteRvs (len);
        b.PutByteRvs (len >> 8);
        b.PutByteRvs (len >> 16);
        b.PutByteRvs (0x83);
        return 4;
    }
    else
    {
        b.PutByteRvs (len);
        b.PutByteRvs (len >> 8);
        b.PutByteRvs (len >> 16);
        b.PutByteRvs (len >> 24);
        b.PutByteRvs (0x84);
        return 5;
    }
} //  EncodeDefLen

//
// Decode a BER length from the given buffer. Increments bytesDecoded
// by the number of octets of the encoded length.  Flags an
// error if the length is too large or a read error occurs
//
AsnLen
BDecLen (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen  len;
    int byte;
    int lenBytes;

    byte = b.GetByte();

    if (b.ReadError())
    {
        throw "ERROR I0018: BDecLen(): Decoded past end of data";
    }

    bytesDecoded++;
    if (byte < 128)   // short length
        return byte;

    else if ( byte == 0x80 )  // indef len indicator
        return INDEFINITE_LEN;

    else  // long len form
    {
        // strip high bit to get # bytes left in len
        //
        lenBytes = byte & 0x7F;

        if (lenBytes > sizeof (long int))
        {
            throw "ERROR I0019: BDecLen(): Length overflow";
        }

        bytesDecoded += lenBytes;

        for (len = 0; lenBytes > 0; lenBytes--)
            len = (len << 8) | (unsigned long int) b.GetByte();


        if (b.ReadError())
        {
            throw "ERROR I0020: BDecLen(): Decoded past end of data";
        }

        return len;
    }
    // not reached
}


// Encodes an End of Contents (EOC) to the given buffer.
// Returns the encoded length.
//
AsnLen
BEncEoc (AsnBuf& b)
{

    b.PutByteRvs (0);
    b.PutByteRvs (0);
    return 2;
}  // BEncEoc

// Decodes an EOC from the given buffer.  flags an error if the
// octets are non-zero or if read error occured.
//
void
BDecEoc (AsnBuf& b, AsnLen &bytesDecoded)
{

    if ((b.GetByte() != 0) || (b.GetByte() != 0) || b.ReadError())
    {
        throw "ERROR I0030: BDecEoc(): Non zero byte in EOC or end of data reached";
    }
    bytesDecoded += 2;
}  // BDecEoc
