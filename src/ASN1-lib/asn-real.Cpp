/*
    Project: ASN1Lib

    Module: asn-real.Cpp

    Description: AsnReal (ASN.1 REAL) type

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "ASN1-Implementation.h"

using namespace std;

// define IEEE_REAL_FMT if your system/compiler uses the native ieee double
// this should improve the performance of encoding reals.
// If your system has the IEEE library routines (iszero, isinf etc)
// then define IEEE_REAL_LIB.  If neither are defined then
// frexp is used.  Performance is probaby best for IEEE_REAL_FMT.
//
// #define IEEE_REAL_FMT
// #define IEEE_REAL_LIB
 
//////////////////////////////////////////////////////////////////////////////
// The number of bytes in a long.  
#define SIZEOF_LONG 4

namespace // unnamed
{

MemPool consts_pool( "ASN.1 Lib REAL constants" );
MemBlock consts_mem( consts_pool );

enum
{
    ENC_PLUS_INFINITY   = 0x40,
    ENC_MINUS_INFINITY  = 0x41,

    REAL_BINARY         = 0x80,
    REAL_SIGN           = 0x40,
    REAL_EXPLEN_MASK    = 0x03,
    REAL_EXPLEN_1       = 0x00,
    REAL_EXPLEN_2       = 0x01,
    REAL_EXPLEN_3       = 0x02,
    REAL_EXPLEN_LONG    = 0x03,
    REAL_FACTOR_MASK    = 0x0c,
    REAL_BASE_MASK      = 0x30,
    REAL_BASE_2         = 0x00,
    REAL_BASE_8         = 0x10,
    REAL_BASE_16        = 0x20
};

// Returns the PLUS INFINITY in double format
// This assumes that a C++ double is an IEEE double.
// The bits for IEEE double PLUS INFINITY are
// 0x7ff0000000000000
// NOTE: this is a guess - you should set this up for
// your architecture
double AsnPlusInfinity()
{
    double d;
    uint8 *c;
    int i;

    c = (uint8*)&d;
    c[0] = 0x7f;
    c[1] = 0xf0;
    for (i = 2; i < sizeof (double); i++)
        c[i] = 0;
    return d;
} // AsnPlusInfinity

double AsnMinusInfinity()
{
    return -AsnPlusInfinity();
}

} // namespace unnamed

//
// Declare and init the PLUS and MINUS INFINITY values.
//
const AsnReal PLUS_INFINITY( &consts_mem, AsnPlusInfinity() );
const AsnReal MINUS_INFINITY( &consts_mem, AsnMinusInfinity() );

AsnType *AsnReal::Clone() const
{
  return new(memBlock) AsnReal(memBlock);
}

// Returns the smallest octet length needed to hold the given long int value
unsigned int
SignedIntOctetLen (long int val)
{
    unsigned long int mask = (0x7f80L << ((sizeof (long int) - 2) * 8));
    unsigned int retVal = sizeof (long int);

    if (val < 0)
        val = val ^ (~0L);  // XOR val with all 1's

    while ((retVal > 1) && ((val & mask) == 0))
    {
        mask >>= 8;
        retVal--;
    }

    return retVal;

} // SignedIntOctetLen



#ifdef IEEE_REAL_FMT

// Returns the PLUS INFINITY in double format
// This assumes that a C++ double is an IEEE double.
// The bits for IEEE double PLUS INFINITY are
// 0x7ff0000000000000
double AsnPlusInfinity()
{
/*
    // oops: doubles are expected to be 8 bytes in size!
    assert( sizeof(double) == 8 );
    double d;
    uint8 *c = (uint8 *)&d;

#if WORDS_BIGENDIAN
    c[0] = 0x7f;
    c[1] = 0xf0;
    c[2] = 0x0;
    c[3] = 0x0;
    c[4] = 0x0;
    c[5] = 0x0;
    c[6] = 0x0;
    c[7] = 0x0;
#else
    c[7] = 0x7f;
    c[6] = 0xf0;
    c[5] = 0x0;
    c[4] = 0x0;
    c[3] = 0x0;
    c[2] = 0x0;
    c[1] = 0x0;
    c[0] = 0x0;
#endif

    return d;
*/
     return 1.7976931348623158e+308;
} // AsnPlusInfinity

double AsnMinusInfinity()
{
    return -AsnPlusInfinity();
}

//
// Use this routine if you system/compiler represents doubles in the IEEE format.
//
AsnLen AsnReal::BEncContent (AsnBuf& b)
{
    int	exponent;
    int isNeg;
#if SIZEOF_LONG == 8
    unsigned long mantissa, val, *p;
    int i;
#elif SIZEOF_LONG == 4
    uint8 *dbl;
    unsigned long int *first4;
    unsigned long int *second4;
#else
  #error long neither 8 nor 4 bytes in size?
#endif

    // no contents for 0.0 reals
    if (value == 0.0) // all bits zero, disregarding top/sign bit
        return 0;

#if SIZEOF_LONG == 8
    //
    // this part assumes that sizeof (long) == sizeof (double) == 8
    // It shouldn't be endian-dependent but I haven't verified that
    //

    p = (unsigned long*) &value;
    val = *p;

    isNeg = (val >> 63) & 1;
    // special real values for +/- oo
    if (!finite (value))
    {
        if (isNeg)
            b.PutByteRvs(ENC_MINUS_INFINITY);
        else
            b.PutByteRvs(ENC_PLUS_INFINITY);
        return 1;
    }
    else // encode a binary real value
    {
	exponent = (val >> 52) & 0x7ff;
	mantissa = (val & 0xfffffffffffffL) | 0x10000000000000L;

	for (i = 0; i < 7; i++)
	{
          b.PutByteRvs(mantissa & 0xff);
	  mantissa >>= 8;
        }
        exponent -= (1023 + 52);

#elif SIZEOF_LONG == 4
    //
    // this part assumes that sizeof (long) == 4 and
    // that sizeof (double) == 8
    //
    // sign  exponent
    //  b    2-12 incl
    //  Sv--------v----- rest is mantissa
    // -------------------------------------------
    // |         |
    // -------------------------------------------
    //  123456878 1234
    //
    // sign bit is 1 if real is < 0
    // exponent is an 11 bit unsigned value (subtract 1023 to get correct exp value)
    // decimal pt implied before mantissa (ie mantissa is all fractional)
    // and implicit 1 bit to left of decimal
    //
    // when given NaN (not a number - ie oo/oo) it encodes the wrong value
    // instead of checking for the error. If you want to check for it,
    //  a NaN is any sign bit with a max exponent (all bits a 1) followed
    //  by any non-zero mantissa. (a zero mantissa is used for infinity)
    //
    
    first4 = (unsigned long int*) (dbl = (uint8*) &value);
    second4 = (unsigned long int *) (dbl + sizeof (long int));

    // no contents for 0.0 reals
    if (value == 0.0) // all bits zero, disregarding top/sign bit
        return 0;

    isNeg = dbl[0] & 0x80;

    // special real values for +/- oo
    if (((*first4 & 0x7fffffff) == 0x7ff00000) && (*second4 == 0))
    {
        if (isNeg)
            b.PutByteRvs (ENC_MINUS_INFINITY);
        else
            b.PutByteRvs (ENC_PLUS_INFINITY);

        return 1;
    }
    else  // encode a binary real value
    {
        exponent = (((*first4) >> 20) & 0x07ff);

        // write the mantissa (N value)
        b.PutSegRvs ((char*)(dbl+2), sizeof (double)-2);

        //
        // The rightmost 4 bits of a double 2nd octet are the
        // most sig bits of the mantissa.
        // write the most signficant byte of the asn1 real manitssa,
        // adding implicit bit to 'left of decimal' if not de-normalized
        // (de normalized if exponent == 0)
        //
        // if the double is not in de-normalized form subtract 1023
        // from the exponent to get proper signed exponent.
        //
        // for both the normalized and de-norm forms
        // correct the exponent by subtracting 52 since:
        //   1. mantissa is 52 bits in the double (56 in ASN.1 REAL form)
        //   2. implicit decimal at the beginning of double's mantissa
        //   3. ASN.1 REAL's implicit decimal is after its mantissa
        // so converting the double mantissa to the ASN.1 form has the
        // effect of multiplying it by 2^52. Subtracting 52 from the
        // exponent corrects this.
        //
        if (exponent == 0) // de-normalized - no implicit 1 to left of dec.*/
        {
            b.PutByteRvs (dbl[1] & 0x0f);
            exponent -= 52;
        }
        else
        {
            b.PutByteRvs ((dbl[1] & 0x0f) | 0x10); // 0x10 adds implicit bit
            exponent -= (1023 + 52);
        }

#else
  #error long neither 8 nor 4 bytes in size?
#endif

        //  write the exponent 
        b.PutByteRvs (exponent & 0xff);
        b.PutByteRvs (exponent >> 8);

        // write format octet
        // bb is 00 since base is 2 so do nothing
        // ff is 00 since no other shifting is nec
        if (isNeg)
            b.PutByteRvs (REAL_BINARY | REAL_EXPLEN_2 | REAL_SIGN);
        else
            b.PutByteRvs (REAL_BINARY | REAL_EXPLEN_2);

        return sizeof (double) + 2;
    }

    // not reached

}  //  AsnReal::BEncContent

#else  // IEEE_REAL_FMT not def

#ifdef IEEE_REAL_LIB

// Returns the PLUS INFINITY in double format
// this assumes you have the IEEE functions in
// the math lib
double AsnPlusInfinity()
{
    return infinity();
} // AsnPlusInfinity

double AsnMinusInfinity()
{
    return -AsnPlusInfinity();
}

// This routine uses the ieee library routines to encode
// this AsnReal's double value
AsnLen AsnReal::BEncContent (AsnBuf& b)
{
    AsnLen encLen;
    double mantissa;
    double tmpMantissa;
    unsigned int truncatedMantissa;
    int exponent;
    unsigned int expLen;
    int sign;
    uint8 buf[sizeof (double)];
    int i, mantissaLen;
    uint8 firstOctet;

    // no contents for 0.0 reals
    if (iszero (value))
        return 0;

    // special real values for +/- oo
    if (isinf (value))
    {
        if (signbit (value)) // neg
            b.PutByteRvs (ENC_MINUS_INFINITY);
        else
            b.PutByteRvs (ENC_PLUS_INFINITY);

        encLen = 1;
    }
    else  // encode a binary real value
    {
        if (signbit (value))
            sign = -1;
        else
            sign = 1;

        exponent =  ilogb (value);

        // get the absolute value of the mantissa (subtract 1 to make < 1)
        mantissa = scalbn (fabs (value), -exponent-1);


        tmpMantissa = mantissa;

        // convert mantissa into an unsigned integer
        for (i = 0; i < sizeof (double); i++)
        {
            // normalizied so shift 8 bits worth to the left of the decimal
            tmpMantissa *= (1<<8);

            // grab only (octet sized) the integer part
            truncatedMantissa = (unsigned int) tmpMantissa;

            // remove part to left of decimal now for next iteration
            tmpMantissa -= truncatedMantissa;

            // write into tmp buffer
            buf[i] = truncatedMantissa;

            // keep track of last non zero octet so can zap trailing zeros
            if (truncatedMantissa)
                mantissaLen = i+1;
        }

        //
        // write format octet  (first octet of content)
        //  field  1 S bb ff ee
        //  bit#   8 7 65 43 21
        //
        // 1 in bit#1 means binary rep
        // 1 in bit#2 means the mantissa is neg, 0 pos
        // bb is the base:    65  base
        //                    00    2
        //                    01    8
        //                    10    16
        //                    11    future ext.
        //
        // ff is the Value of F where  Mantissa = sign x N x 2^F
        //    FF can be one of 0 to 3 inclusive. (used to save re-alignment)
        //
        // ee is the length of the exponent:  21   length
        //                                    00     1
        //                                    01     2
        //                                    10     3
        //                                    11     long form
        //
        //
        // encoded binary real value looks like
        //
        //     fmt oct
        //   --------------------------------------------------------
        //   |1Sbbffee|  exponent (2's comp)  |   N (unsigned int)  |
        //   --------------------------------------------------------
        //    87654321
        //
        firstOctet = REAL_BINARY;
        if (signbit (value))
            firstOctet |= REAL_SIGN;

        // bb is 00 since base is 2 so do nothing
        // ff is 00 since no other shifting is nec

        //
        // get exponent calculate its encoded length
        // Note that the process of converting the mantissa
        // double to an int shifted the decimal mantissaLen * 8
        // to the right - so correct that here
        //
        exponent++; // compensate for trick to put mantissa < 1
        exponent -= (mantissaLen * 8);
        expLen = SignedIntOctetLen (exponent);

        switch (expLen)
        {
            case 1:
                firstOctet |= REAL_EXPLEN_1;
                break;
            case 2:
                firstOctet |= REAL_EXPLEN_2;
                break;
            case 3:
                firstOctet |= REAL_EXPLEN_3;
                break;
            default:
                firstOctet |= REAL_EXPLEN_LONG;
                break;
        }

        encLen = mantissaLen + expLen + 1;

        // write the mantissa (N value)
        b.PutSegRvs ((char*)buf, mantissaLen);

        // write the exponent
        for (i = expLen; i > 0; i--)
        {
            b.PutByteRvs (exponent);
            exponent >> 8;
        }

        // write the exponents length if nec
        if (expLen > 3)
        {
            encLen++;
            b.PutByteRvs (expLen);
        }

        // write the format octet
        b.PutByteRvs (firstOctet);

    }
    return encLen;

}  //  AsnReal::BEncContent

#else  // neither IEEE_REAL_FMT or IEEE_REAL_LIB are def


//
// Encodes the content of an ASN.1 REAL value to the given buffer.
// This version of the routine does not assume an IEEE double rep.
// or the existence of the IEEE library routines.  Uses old style
// UNIX frexp etc.
//
AsnLen AsnReal::BEncContent (AsnBuf& b)
{
    unsigned long int encLen;
    double mantissa;
    double tmpMantissa;
    unsigned int truncatedMantissa;
    int exponent;
    unsigned int expLen;
    int sign;
    uint8 buf[sizeof (double)];
    int i, mantissaLen;
    uint8 firstOctet;

    // no contents for 0.0 reals
    if (value == 0.0)
        return 0;

    // special real values for +/- oo
    if (value == MINUS_INFINITY)
    {
        b.PutByteRvs (ENC_MINUS_INFINITY);
        encLen = 1;
    }
    else if (value == PLUS_INFINITY)
    {
        b.PutByteRvs (ENC_PLUS_INFINITY);
        encLen = 1;
    }
    else  // encode a binary real value
    {
        //
        // this is what frexp gets from value
        // value == mantissa * 2^exponent
        // where 0.5 <= |manitissa| < 1.0
        //
        mantissa = frexp (value, &exponent);

        // set sign and make mantissa = | mantissa |
        if (mantissa < 0.0)
        {
            sign = -1;
            mantissa *= -1;
        }
        else
            sign = 1;


        tmpMantissa = mantissa;

        // convert mantissa into an unsigned integer
        for (i = 0; i < sizeof (double); i++)
        {
            // normalizied so shift 8 bits worth to the left of the decimal
            tmpMantissa *= (1<<8);

            // grab only (octet sized) the integer part
            truncatedMantissa = (unsigned int) tmpMantissa;

            // remove part to left of decimal now for next iteration
            tmpMantissa -= truncatedMantissa;

            // write into tmp buffer
            buf[i] = truncatedMantissa;

            // keep track of last non zero octet so can zap trailing zeros
            if (truncatedMantissa)
                mantissaLen = i+1;
        }

        //
        // write format octet  (first octet of content)
        //  field  1 S bb ff ee
        //  bit#   8 7 65 43 21
        //
        // 1 in bit#1 means binary rep
        // 1 in bit#2 means the mantissa is neg, 0 pos
        // bb is the base:    65  base
        //                    00    2
        //                    01    8
        //                    10    16
        //                    11    future ext.
        //
        // ff is the Value of F where  Mantissa = sign x N x 2^F
        //    FF can be one of 0 to 3 inclusive. (used to save re-alignment)
        //
        // ee is the length of the exponent:  21   length
        //                                    00     1
        //                                    01     2
        //                                    10     3
        //                                    11     long form
        //
        //
        // encoded binary real value looks like
        //
        //     fmt oct
        //   --------------------------------------------------------
        //   |1Sbbffee|  exponent (2's comp)  |   N (unsigned int)  |
        //   --------------------------------------------------------
        //    87654321
        //
        firstOctet = REAL_BINARY;
        if (sign == -1)
            firstOctet |= REAL_SIGN;

        // bb is 00 since base is 2 so do nothing
        // ff is 00 since no other shifting is nec

        //
        // get exponent calculate its encoded length
        // Note that the process of converting the mantissa
        // double to an int shifted the decimal mantissaLen * 8
        // to the right - so correct that here
        //
        exponent -= (mantissaLen * 8);
        expLen = SignedIntOctetLen (exponent);

        switch (expLen)
        {
            case 1:
                firstOctet |= REAL_EXPLEN_1;
                break;
            case 2:
                firstOctet |= REAL_EXPLEN_2;
                break;
            case 3:
                firstOctet |= REAL_EXPLEN_3;
                break;
            default:
                firstOctet |= REAL_EXPLEN_LONG;
                break;
        }

        encLen = mantissaLen + expLen + 1;

        // write the mantissa (N value)
        b.PutSegRvs( buf, mantissaLen );

        // write the exponent
        for (i = expLen; i > 0; i--)
        {
            b.PutByteRvs (exponent);
            exponent >>= 8;
        }

        // write the exponents length if nec
        if (expLen > 3)
        {
            encLen++;
            b.PutByteRvs (expLen);
        }

        // write the format octet
        b.PutByteRvs (firstOctet);

    }
    return encLen;

}  //  AsnReal:BEncContent



#endif
#endif


// Decode a REAL value's content from the given buffer.
// places the result in this object.
void AsnReal::BDecContent (AsnBuf& b, AsnTag tagId, AsnLen elmtLen, AsnLen &bytesDecoded)
{
    uint8 firstOctet;
    uint8 firstExpOctet;
    unsigned int expLen;
    double mantissa;
    unsigned short base;
    long int exponent = 0;
    double tmpBase;
    double tmpExp;


    if (elmtLen == 0)
    {
        value = 0.0;
        return;
    }

    firstOctet = b.GetByte();
    if (elmtLen == 1)
    {
        bytesDecoded += 1;
        if (firstOctet == ENC_PLUS_INFINITY)
            value = PLUS_INFINITY;
        else if (firstOctet == ENC_MINUS_INFINITY)
            value = MINUS_INFINITY;
        else
        {
            throw "ERROR I0039: AsnReal.BDecContent(): Unrecognized 1 octet length real number";
        }
    }
    else
    {
        if (firstOctet & REAL_BINARY)
        {
            firstExpOctet = b.GetByte();
            if (firstExpOctet & 0x80)
                exponent = -1;
            switch (firstOctet & REAL_EXPLEN_MASK)
            {
                case REAL_EXPLEN_1:
                    expLen = 1;
                    exponent =  (exponent << 8) | firstExpOctet;
                    break;

                case REAL_EXPLEN_2:
                    expLen = 2;
                    exponent =  (exponent << 16) | (((unsigned long int) firstExpOctet) << 8) | b.GetByte();
                    break;

                case REAL_EXPLEN_3:
                    expLen = 3;
                    exponent =  (exponent << 16) | (((unsigned long int) firstExpOctet) << 8) | b.GetByte();
                    exponent =  (exponent << 8) | b.GetByte();
                    break;

                default:  // long form
                {
                    expLen = firstExpOctet +1;
                    size_t i = firstExpOctet-1;
                    firstExpOctet =  b.GetByte();
                    if (firstExpOctet & 0x80)
                        exponent = (-1 <<8) | firstExpOctet;
                    else
                        exponent = firstExpOctet;
                    for (;i > 0; firstExpOctet--)
                        exponent = (exponent << 8) | b.GetByte();
                    }
                    break;
            }

            mantissa = 0.0;
            for (size_t i = 1 + expLen; i < elmtLen; i++)
            {
                mantissa *= (1<<8);
                mantissa +=  b.GetByte();
            }

            // adjust N by scaling factor
            mantissa *= (1<<((firstOctet & REAL_FACTOR_MASK) >> 2));

            switch (firstOctet & REAL_BASE_MASK)
            {
                case REAL_BASE_2:
                    base = 2;
                    break;

                case REAL_BASE_8:
                    base = 8;
                    break;

                case REAL_BASE_16:
                    base = 16;
                    break;

                default:
                    throw "ERROR I0040: AsnReal.BDecContent(): Unsupported base for a binary real number.";
                   break;

            }

            tmpBase = base;
            tmpExp = exponent;

            value =  mantissa * pow ((double)base, (double)exponent);

            if (firstOctet & REAL_SIGN)
                value = -value;

            bytesDecoded += elmtLen;
        }
        else // decimal version
        {
            throw "ERROR I0041: AsnReal.BDecContent(): Decimal REAL form is not currently supported";
        }
    }

} // AsnInt::BDecContent

AsnLen AsnReal::BEnc (AsnBuf& b)
{
    AsnLen l;
    l =  BEncContent (b);
    l += BEncDefLen (b, l);
    l += BEncTag1 (b, UNIV, PRIM, REAL_TAG_CODE);
    return l;
}

void AsnReal::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    if (BDecTag (b, bytesDecoded) != MAKE_TAG_ID (UNIV, PRIM, REAL_TAG_CODE))
    {
	    throw "ERROR I0042: AsnReal.BDec(): Tag on REAL is wrong.";
    }
    elmtLen = BDecLen (b, bytesDecoded);

    BDecContent (b, MAKE_TAG_ID (UNIV, PRIM, REAL_TAG_CODE), elmtLen, bytesDecoded);
}

void AsnReal::Print (CTsvcLIB::LOG &os) const
{
    os << "REAL " << value;
}

