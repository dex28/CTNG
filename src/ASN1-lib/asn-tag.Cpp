/*
    Project: ASN1Lib

    Module: asn-tag.Cpp

    Description: ASN.1 tag manipulation routines

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "ASN1-Implementation.h"

using namespace std;

//
// Decode a BER Tag from the given buffer.  Error is
// flagged if the tag is too long or if a read error occurs.
//
AsnTag
BDecTag (AsnBuf&  b, AsnLen &bytesDecoded)
{
    AsnTag tagId;
    AsnTag tmpTagId;
    int i;

    tagId = ((AsnTag) b.GetByte()) << ((sizeof (AsnTag)-1) *8);
    bytesDecoded++;

    // check if long tag format (ie code > 31)
    if ((tagId & (((AsnTag) 0x1f) << ((sizeof (AsnTag)-1)*8))) == (((AsnTag)0x1f) << ((sizeof (AsnTag)-1)*8)))
    {
        i = 2;
        do
        {
            tmpTagId = (AsnTag) b.GetByte();
            tagId |= (tmpTagId << ((sizeof (AsnTag)-i)*8));
            bytesDecoded++;
            i++;
        }
        while ((tmpTagId & (AsnTag)0x80) && (i <= sizeof (AsnTag)));

        //
        // check for too long a tag
        //
        if (i > (sizeof (AsnTag)+1))
        {
            throw "ERROR I0043: BDecTag(): Tag value overflow";
        }
    }

    if (b.ReadError())
    {
        throw "ERROR I0044: BDecTag(): Decoded past the end of data";
    }

    return tagId;

} // BDecTag
