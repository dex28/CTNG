/*
    Project: ASN1Lib

    Module: asn-octs.Cpp

    Description: ASN.1 OCTET STRING methods for AsnOcts Class

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "ASN1-Implementation.h"

using namespace std;

AsnOcts::~AsnOcts()
{
    // MEMMGR delete octs;
}

AsnType *AsnOcts::Clone() const
{
    return new(memBlock) AsnOcts(memBlock);
}

// Initialize the AsnOcts with a char * and length.
// copies the string str.
void AsnOcts::Set (const uint8 *str, size_t len)
{
    octetLen = len;
    octs = new(memBlock) uint8[octetLen + 1];
    memcpy (octs, str, octetLen);
    octs[ octetLen ] = 0;
}

// Initialize the AsnOcts from another AsnOcts
// copies the string from o.
void AsnOcts::Set (const AsnOcts &o)
{
    if (&o != this) // avoid o = o;
    {
        octetLen = o.octetLen;
        octs = new(memBlock) uint8[octetLen + 1];
        memcpy (octs, o.octs, octetLen);
        octs[ octetLen ] = 0;
    }
}

// Initialize the AsnOcts from a Null terminated string.
// copies the string str.
void AsnOcts::Set (const uint8 *str)
{
    octetLen = strlen( (const char*)str );
    octs = new(memBlock) uint8[octetLen + 1];
    memcpy (octs, str, octetLen);
    octs[ octetLen ] = 0;
}


// free old octs value and tehn set the new
// octs and octetLen values with the given char *and length.
// copies the string str.
void AsnOcts::ReSet (const uint8 *str, size_t len)
{
    if (str != octs)
    {
        // MEMMGR delete octs;
        Set (str, len);
    }
}

// Free old octs value and then set the new
// octs and octetLen from the given AsnOcts
// copies the string in o.
void AsnOcts::ReSet (const AsnOcts &o)
{
    if (&o != this) // avoid s = s;
    {
        // MEMMGR delete octs;
        Set (o);
    }
}

// Free old octs value and then set the new
// octs and octetLen values from a null terminated string.
// copies the string str.
void AsnOcts::ReSet (const uint8 *str)
{
    if (str != octs)
    {
        // MEMMGR delete octs;
        Set (str);
    }
}


// Prints the AsnOcts to the given log stream in Value Notation.
void AsnOcts::Print (CTsvcLIB::LOG &os) const
{
    os << "OCTS '";

    for ( size_t i = 0; i < octetLen; i++ )
        os << TO_HEX (octs[i] >> 4) << TO_HEX (octs[i]);

    os << "'H / \"";

    // put printable parts in ASN.1 comment
    for (i = 0; i < octetLen; i++)
    {
        if (isspace (octs[i]))
            os << " ";  // newlines->space (so don't screw up ASN.1 comment)
        else if (isprint (octs[i]))
            os << octs[ i ];
        else
            os << ".";
    }
    os << "\"";

} // AsnOcts::Print


AsnLen AsnOcts::BEncContent (AsnBuf& b)
{
    b.PutSegRvs (octs, octetLen);
    return octetLen;
}

// Decodes a BER OCTET STRING value and puts it in this object.
// Constructed OCTET STRINGs are always concatenated into primitive ones.
void AsnOcts::BDecContent (AsnBuf& b, AsnTag tagId, AsnLen elmtLen, AsnLen &bytesDecoded)
{
    //
    // tagId is encoded tag shifted into long int.
    // if CONS bit is set then constructed octet string
    //
    if (tagId & 0x20000000)
        BDecConsOcts (b, elmtLen, bytesDecoded);

    else // primitive octet string
    {
        octetLen = elmtLen;
        octs =  new(memBlock) uint8[ elmtLen + 1 ];
        b.CopyOut (octs, elmtLen);

        if (b.ReadError())
        {
            throw "ERROR I0033: AsnOcts.BDecOctetString(): Decoded past end of data";
        }

        // add null terminator - this is not included in the str's len
        octs[elmtLen] = '\0';
        bytesDecoded += elmtLen;
    }

} // AsnOcts::BDecContent

AsnLen AsnOcts::BEnc (AsnBuf& b)
{
    AsnLen l;
    l =  BEncContent (b);
    l += BEncDefLen (b, l);
    l += BEncTag1 (b, UNIV, PRIM, OCTETSTRING_TAG_CODE);
    return l;
}

void AsnOcts::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    tag = BDecTag (b, bytesDecoded);
    if ((tag != MAKE_TAG_ID (UNIV, PRIM, OCTETSTRING_TAG_CODE)) &&
	    (tag != MAKE_TAG_ID (UNIV, CONS, OCTETSTRING_TAG_CODE)))
    {
	    throw "ERROR I0034: AsnOcts.BDec(): Tag on OCTET STRING is wrong.";
    }
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}



//
// Used for concatenating constructed OCTET STRING values when decoding
//
// fills string stack with references to the pieces of a
// construced octet string
//
void
AsnOcts:: FillOctetStringStk (AsnBuf& b, AsnLen elmtLen0, AsnLen &bytesDecoded )
{
    size_t refdLen;
    size_t totalRefdLen;
    uint8 *strPtr;
    AsnLen totalElmtsLen1 = 0;
    unsigned long int tagId1;
    AsnLen elmtLen1;

    for (; (totalElmtsLen1 < elmtLen0) || (elmtLen0 == INDEFINITE_LEN);)
    {
        tagId1 = BDecTag (b, totalElmtsLen1);

        if ((tagId1 == EOC_TAG_ID) && (elmtLen0 == INDEFINITE_LEN))
        {
            BDEC_2ND_EOC_OCTET (b, totalElmtsLen1);
            break;
        }

        elmtLen1 = BDecLen (b, totalElmtsLen1);
        if (tagId1 == MAKE_TAG_ID (UNIV, PRIM, OCTETSTRING_TAG_CODE))
        {
            //
            // primitive part of string, put references to piece (s) in
            // str stack
            //
            totalRefdLen = 0;
            refdLen = elmtLen1;
            while (1)
            {
                strPtr = b.GetSeg (&refdLen);

                memBlock->strStk_Push (strPtr, refdLen);
                totalRefdLen += refdLen;
                if (totalRefdLen == elmtLen1)
                    break; // exit this while loop

                if (refdLen == 0) // end of data
                {
                    throw "ERROR I0035: AsnOcts.BDecConsOctetString(): Attempt to decode past end of data";
                }
                refdLen = elmtLen1 - totalRefdLen;
            }
            totalElmtsLen1 += elmtLen1;
        }


        else if (tagId1 == MAKE_TAG_ID (UNIV, CONS, OCTETSTRING_TAG_CODE))
        {
            //
            // constructed octets string embedding in this constructed
            // octet string. decode it.
            //
            FillOctetStringStk (b, elmtLen1, totalElmtsLen1 );
        }
        else  // wrong tag
        {
            throw "ERROR I0036: AsnOcts.BDecConsOctetString(): Decoded non-OCTET STRING tag inside a constructed OCTET STRING";
        }
    } // end of for

    bytesDecoded += totalElmtsLen1;

}  // AsnOcts::FillOctetStringStk



//
// decodes a seq of universally tagged octets until either EOC is
// encountered or the given len decoded.  Return them in a
// single concatenated octet string
//
void AsnOcts::BDecConsOcts (AsnBuf& b, AsnLen elmtLen, AsnLen &bytesDecoded)
{
    memBlock->strStk_Reset();

    //
    // decode each piece of the octet string, puting
    // an entry in the octet/bit string stack for each
    //
    FillOctetStringStk (b, elmtLen, bytesDecoded );

    // alloc single str long enough for combined octetstring
    octetLen = memBlock->G.stk.totalByteLen;

    octs = new(memBlock) uint8[ octetLen + 1 ];

    memBlock->strStk_CopyOut( octs );

    octs[ octetLen ] = 0;

}  // BDecConsOcts

int AsnOcts::OctsEquiv (const AsnOcts &o) const
{
    return o.octetLen == octetLen && ! memcmp (o.octs, octs, octetLen);
}

