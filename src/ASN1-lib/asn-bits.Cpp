/*
    Project: ASN1Lib

    Module: asn-bits.Cpp

    Description: AsnBits (ASN.1 BIT STRING) Type

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "ASN1-Implementation.h"

using namespace std;

AsnBits::~AsnBits()
{
    }

AsnType *AsnBits::Clone() const
{
    return new(memBlock) AsnBits(memBlock);
    }

// Initializes the bits string with a bit string numBits in length.
// All bits are zeroed.
void AsnBits::Set (size_t numBits)
{
    bitLen = numBits;
    size_t octetLen = (bitLen+7)/8;

    bits = new(memBlock) uint8[ octetLen ];
    memset (bits, 0, octetLen); // init to zeros
    }

// initializes a BIT STRING with the given string and bit length
// Copies the bits from bitsOcts.
void AsnBits::Set (const uint8 *bitOcts, size_t numBits)
{
    if (bitOcts != bits)
    {
        bitLen = numBits;
        size_t octetLen = (bitLen+7)/8;
        bits = new(memBlock) uint8[octetLen];
        memcpy (bits, bitOcts, octetLen);
        }
    }

// initializes a BIT STRING by copying another BIT STRING's bits
void AsnBits::Set (const AsnBits &b)
{
    if (&b != this)
    {
        bitLen = b.bitLen;
        size_t octetLen = (bitLen+7)/8;
        bits = new(memBlock) uint8[octetLen];
        memcpy (bits, b.bits, octetLen);
        }
    }

// Initializes the bits string with a bit string numBits in length.
// All bits are zeroed.
void AsnBits::ReSet (size_t numBits)
{
    Set (numBits);
    }

// frees old bits value and then re-initializes the
// BIT STRING with the given string and bit length
// Copies the bitOcts into bits.
void AsnBits::ReSet (const uint8 *bitOcts, size_t numBits)
{
    if (bitOcts != bits)
    {
        Set (bitOcts, numBits);
        }
    }

// frees old bits value and then re-initializes the
// BIT STRING by copying another BIT STRING's bits
void AsnBits::ReSet (const AsnBits &b)
{
    if (&b != this)  // avoid b = b; probs
    {
        Set (b);
        }
    }

// Returns true if the given BIT STRING is the same as this one
bool AsnBits::BitsEquiv (const AsnBits &ab) const
{
    size_t octetsLessOne = (bitLen-1)/8;
    size_t octetBits = 7 - (bitLen % 8);

    if (!bitLen && !ab.bitLen)
        return true;

    // trailing bits may not be significant
    return bitLen == ab.bitLen
        && !memcmp (bits, ab.bits, octetsLessOne)
        && (bits[octetsLessOne] & (0xFF << octetBits)) 
            == (ab.bits[octetsLessOne] & (0xFF << octetBits));
    }  // AsnBits::BitsEquiv


// set given bit to 1. Most signif. bit is bit 0, least signif bit is bitLen-1
void AsnBits::SetBit (size_t bit)
{
    if (bit < bitLen)
    {
        size_t octet = bit/8;
        size_t octetsBit = 7 - (bit % 8); // bit zero is first/most sig bit in octet
        bits[octet] |= 1 << octetsBit;
        }
    else
    {
        throw "ERROR I0003: AsnBits.SetBit(): Bit larger than bit string";
        }
} // AsnBits::SetBit

// Clr bit. Most signif. bit is bit 0, least signif bit is bitLen-1
void AsnBits::ClrBit (size_t bit)
{
  if (bit < bitLen)
  {
    size_t octet = bit/8;
    size_t octetsBit = 7 - (bit % 8);   // bit zero is first/most sig bit in octet
    bits[octet] &= ~(1 << octetsBit);
  }
#ifdef DEBUG
  else
    throw "ERROR I0004: AsnBits.ClrBit(): Bit larger than bit string";
#endif
} // AsnBits::ClrBit

// returns given bit. Most signif. bit is bit 0, least signif bit is bitLen-1.
// Returns false if the givnen bit index is out of range.
bool AsnBits::GetBit (size_t bit) const
{
  if (bit < bitLen)
  {
    size_t octet = bit/8;
    size_t octetsBit = 7 - (bit % 8);   // bit zero is first/most sig bit in octet
    return !!(bits[octet] & (1 << octetsBit));
  }
#ifdef DEBUG
  else
    throw "ERROR I0005: AsnBits.GetBit(): Bit larger than bit string";
#endif

  return false;
}  // AsnBits::GetBit


// Encoded the content (included unused bits octet) of the BIT STRING
// to the given buffer.
AsnLen AsnBits::BEncContent (AsnBuf& b)
{
    size_t byteLen = (bitLen+7)/8;
    b.PutSegRvs (bits, byteLen);

    size_t unusedBits = (bitLen % 8);
    if (unusedBits != 0)
        unusedBits = 8 - unusedBits;
    b.PutByteRvs (unusedBits);

    return byteLen + 1;

} // AsnBits::BEncContent


// Decodes a BER BIT STRING from the given buffer and stores
// the value in this object.
void AsnBits::BDecContent (AsnBuf& b, AsnTag tagId, AsnLen elmtLen, AsnLen &bytesDecoded)
{
    //
    // tagId is encoded tag shifted into long int.
    // if CONS bit is set then constructed bit string
    //
    if (tagId & 0x20000000)
        BDecConsBits (b, elmtLen, bytesDecoded);

    else // primitive octet string
    {
        bytesDecoded += elmtLen;
        elmtLen--;
        bitLen = (elmtLen * 8) - (unsigned int)b.GetByte();
        bits =  new(memBlock) uint8 [ elmtLen ];
        b.CopyOut (bits, elmtLen);
        if (b.ReadError())
        {
            throw "ERROR I0006: AsnBits.BDecContent(): Decoded past end of data";
        }
    }

} // AsnBits::BDecContent

AsnLen AsnBits::BEnc (AsnBuf& b)
{
    AsnLen l;
    l =  BEncContent (b);
    l += BEncDefLen (b, l);
    l += BEncTag1 (b, UNIV, PRIM, BITSTRING_TAG_CODE);
    return l;
}

void AsnBits::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    tag = BDecTag (b, bytesDecoded);
    if ((tag != MAKE_TAG_ID (UNIV, PRIM, BITSTRING_TAG_CODE))
      && (tag != MAKE_TAG_ID (UNIV, CONS, BITSTRING_TAG_CODE)))
    {
        throw "ERROR I0007: AsnBits.BDec(): Tag on BIT STRING is wrong.";
    }
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

//
// Used to concatentate constructed bit strings when decoding.
//
// fills string stack with references to the pieces of a
// construced bit string. sets memBlock->G.stk->unusedBits appropriately.
// and memBlock->G.stk->totalByteLenG to bytelen needed to hold the bitstring
//
void AsnBits::FillBitStringStk (AsnBuf& b, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
    size_t refdLen;
    size_t totalRefdLen;
    uint8 *strPtr;
    AsnLen totalElmtsLen1 = 0;
    unsigned long int tagId1;
    AsnLen elmtLen1;
    size_t lenToRef;

    for (; (totalElmtsLen1 < elmtLen0) || (elmtLen0 == INDEFINITE_LEN); )
    {
        tagId1 = BDecTag (b, totalElmtsLen1);

        if ((tagId1 == EOC_TAG_ID) && (elmtLen0 == INDEFINITE_LEN))
        {
            BDEC_2ND_EOC_OCTET (b, totalElmtsLen1);
            break;
        }

        elmtLen1 = BDecLen (b, totalElmtsLen1);
        if (tagId1 == MAKE_TAG_ID (UNIV, PRIM, BITSTRING_TAG_CODE))
        {
            // primitive part of string, put references to piece (s) in
            // str stack
            //

            // get unused bits octet
            //
            if ( memBlock->G.stk.unusedBits != 0)
            {
                // whoa - only allowed non-octed aligned bits on
                // on last piece of bits string
                //
                throw "ERROR I0008: AsnBits.BDecConsBitString(): A component of a constructed BIT STRING that is not the last has non-zero unused bits";
            }

            if (elmtLen1 != 0)
                memBlock->G.stk.unusedBits = b.GetByte();

            totalRefdLen = 0;
            lenToRef =elmtLen1-1; // remove one octet for the unused bits oct*/
            refdLen = lenToRef;
            while (1)
            {
                strPtr = b.GetSeg (&refdLen);

                memBlock->strStk_Push (strPtr, refdLen);
                totalRefdLen += refdLen;
                if (totalRefdLen == lenToRef)
                    break; // exit this while loop

                if (refdLen == 0) // end of data
                {
                    throw "ERROR I0009: AsnBits.BDecConsOctetString(): Expecting more data";
                }
                refdLen = lenToRef - totalRefdLen;
            }
            totalElmtsLen1 += elmtLen1;
        }


        else if (tagId1 == MAKE_TAG_ID (UNIV, CONS, BITSTRING_TAG_CODE))
        {
            // constructed octets string embedding in this constructed
            // octet string. decode it.
            //
            FillBitStringStk (b, elmtLen1, totalElmtsLen1);
        }
        else  // wrong tag
        {
            throw "ERROR I0010: AsnBits.BDecConsBitString(): Decoded non-BIT STRING tag inside a constructed BIT STRING";
        }
    } // end of for

    bytesDecoded += totalElmtsLen1;

}  // FillBitStringStk

//
// decodes a seq of universally tagged bits until either EOC is
// encountered or the given len decoded.  Return them in a
// single concatenated bit string
//
void AsnBits::BDecConsBits (AsnBuf& b, AsnLen elmtLen, AsnLen &bytesDecoded)
{
    memBlock->strStk_Reset();

    // decode each piece of the octet string, puting
    // an entry in the octet/bit string stack for each
    //
    FillBitStringStk (b, elmtLen, bytesDecoded);

    // alloc single str long enough for combined bitstring
    bitLen = memBlock->G.stk.totalByteLen * 8 - memBlock->G.stk.unusedBits;

    bits = new(memBlock) uint8[ memBlock->G.stk.totalByteLen ];

    memBlock->strStk_CopyOut (bits);

    }  // BDecConsBits

// prints the BIT STRING to the given log stream.
//
void AsnBits::Print (CTsvcLIB::LOG &os) const
{
    size_t octetLen = ( bitLen + 7 ) / 8;

    os << "BITS '";

    for ( size_t i = 0; i < octetLen; i++ )
        os << TO_HEX (bits[i] >> 4) << TO_HEX (bits[i]);

    os << "'H, len = " << bitLen << CTsvcLIB::eline;
    }
