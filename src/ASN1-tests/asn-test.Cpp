/*
    Project: ASN1Test

    Module: asn-test.Cpp

    Description: ASN1Lib functionality integrity tests

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "ASN1-Implementation.h"
#include "asn-test.h"

#include <cfloat>

using namespace std;
using namespace CTsvcLIB;

enum { bufSize = 256 };

namespace // unnamed
{
    MemPool testPool( "TestAsn module" );
}

//
// returns true if passes tests
//
int
TestAsn::USTRs( void )
{
    USTR t;

    {
        USTR x;
        }

    {
        USTR y = "34";
        t = y;
        }

    {
        USTR z( (uint8*)"3434", 4 );
        t = z;
        }

    USTR b;
    b.CopyTo( t ); // the same as nullify

    MemBlock mem( testPool );
    USTR z = USTR( &mem, "test22" );

    return true;
    }

//
// returns true if passes tests
//
int
TestAsn::Buffers()
{
    bool noErr = true;

    // initialize buffer
    AsnBuf  b;
    uint8   bufData[ bufSize ];
    b.Init (bufData, bufSize);
    b.ResetInWriteRvsMode();

    // write whole range of byte (0..255)
    // remember, write works in reverse
    //
    for ( int i = 0; i < bufSize; i++ )
        b.PutByteRvs (i);

    if (b.WriteError())
    {
        LOG( DBG_ERROR ) << "Error writing to buffer." << eline;
        noErr = false;
    }

    // read in values & verify
    b.ResetInReadMode();
    for (i = 255; i >= 0; i--)
        if (b.GetByte() != i)
        {
            LOG( DBG_ERROR ) << "Error verifying data written to buffer." << eline;
            noErr = false;
        }

    if ( b.ReadError() )
    {
        LOG( DBG_ERROR ) << "Error reading from buffer." << eline;
        noErr = false;
    }


    // now make sure errors are detected 
    b.ResetInWriteRvsMode();

    for (i = 0; i < 257; i++) // write past end of buffer
        b.PutByteRvs (0);

    if (!b.WriteError())
    {
        LOG( DBG_ERROR ) << "Buffers failed to report buffer write overflow." << eline;
        noErr = false;
    }


    b.ResetInReadMode();
    for (i = bufSize; i >= 0; i--)  // read past end of buffer
        b.GetByte();

    if (!b.ReadError())
    {
        LOG( DBG_ERROR ) << "Buffers failed to report buffer read overflow." << eline;
        noErr = false;
    }

    return noErr;
}


//
// returns true if passes encode/decode tests
//
int
TestAsn::Tag()
{
    AsnTag aTag1;
    AsnTag aTag2;
    int i;
    AsnLen len1;
    AsnLen len2;
    int noErr = true;
    AsnBuf  b;
    uint8 bufData[bufSize];
    BER_CLASS tagClass;
    BER_FORM form;
    BER_UNIV_CODE code;

    // initialize buffer 
    b.Init (bufData, bufSize);

    // encode a TRUE value and verify 
    tagClass = UNIV;
    form = PRIM;
    code = INTEGER_TAG_CODE;
    aTag1 = MAKE_TAG_ID (tagClass, form, code);

    for (i = 0; i < 2; i++)
    {
        b.ResetInWriteRvsMode();
        len1 = BEncTag1 (b, tagClass, form, code);

        if (b.WriteError())
        {
            noErr = false;
            LOG( DBG_ERROR ) << "Error encoding a Tag." << eline;
        }

        b.ResetInReadMode();

        aTag2 = 0;

        // make sure no decode errors and that it decodes to same tag 
        len2 = 0;
        try
        {
            aTag2 = BDecTag (b, len2);
        }
        catch( int val )
        {
            noErr = false;
            LOG( DBG_ERROR ) << "Error decoding a Tag - error number " << val << eline;
        }
        if (noErr && ((aTag2 != aTag1) || (len1 != len2)))
        {
            noErr = false;
            LOG( DBG_ERROR ) << "Error decoded Tag does not match encoded Tag." << eline;
        }
        // set a new test tag value 
        tagClass = CNTX;
        form = CONS;
        code = (BER_UNIV_CODE) 29;
        aTag1 = MAKE_TAG_ID (tagClass, form, code);
    }
    return noErr;
}  // TestAsn::Tag 


//
// returns true if passes encode/decode tests
//
int
TestAsn::Len()
{
    AsnLen aLen1;
    AsnLen aLen2;
    int i;
    AsnLen len1;
    AsnLen len2;
    int noErr = true;
    AsnBuf  b;
    uint8 bufData[bufSize];

    // initialize buffer 
    b.Init (bufData, bufSize);


    // encode a TRUE value and verify 
    aLen1 = 99999;
    for (i = 0; i < 2; i++)
    {
        b.ResetInWriteRvsMode();
        len1 = BEncDefLen (b, aLen1);

        if (b.WriteError())
        {
            noErr = false;
            LOG( DBG_ERROR ) <<  "Error encoding Length." << eline;
        }

        b.ResetInReadMode();

        aLen2 = 0;

        // make sure no decode errors and that it decodes to true 
        len2 = 0;
        try
        {
            aLen2 = BDecLen (b, len2);
        }
        catch( int val )
        {
            noErr = false;
            LOG( DBG_ERROR ) << "Error decoding Length - error number " << val << eline;
        }


        if (noErr && ((aLen2 != aLen1) || (len1 != len2)))
        {
            noErr = false;
            LOG( DBG_ERROR ) << "Error - decoded length does not match encoded length" << eline;
        }
        aLen1 = 2;
    }


    // test indef len 
    b.ResetInWriteRvsMode();
    len1 = BEncIndefLen (b);

    if (b.WriteError())
    {
        noErr = false;
        LOG( DBG_ERROR ) << "Error encoding indefinite Length." << eline;
    }

    b.ResetInReadMode();

    aLen2 = 0;

    // make sure no decode errors 
    len2 = 0;
    try
    {
        aLen2 = BDecLen (b, len2);
    }
    catch( int val )
    {
        noErr = false;
        LOG( DBG_ERROR ) << "Error decoding Length - error number " << val << eline;
    }


    if (noErr && ((aLen2 != INDEFINITE_LEN) || (len1 != len2)))
    {
        noErr = false;
        LOG( DBG_ERROR ) << "Error - decoded length does not match encoded length" << eline;
    }

    // test EOC 
    b.ResetInWriteRvsMode();
    len1 = BEncEoc (b);

    if (b.WriteError())
    {
        noErr = false;
        LOG( DBG_ERROR ) << "Error encoding indefinite Length." << eline;
    }

    b.ResetInReadMode();

    aLen2 = 0;

    // make sure no decode errors 
    len2 = 0;
    try
    {
        BDecEoc (b, len2);
    }
    catch( int val )
    {
        noErr = false;
        LOG( DBG_ERROR ) << "Error decoding Length - error number " <<  val << eline;
    }


    if (noErr && (len1 != len2))
    {
        noErr = false;
        LOG( DBG_ERROR ) << "Error - decoded EOC length error" << eline;
    }

    return noErr;
}  // TestAsn::Len 



//
// returns true if passes encode/decode tests
//
int
TestAsn::Bool()
{
    MemBlock mem( testPool );

    AsnBuf  b;
    uint8 bufData[bufSize];
    AsnBool aBool1(&mem);
    AsnBool aBool2(&mem);
    AsnLen len1;
    AsnLen len2;
    int noErr = true;

    // initialize a small buffer
    b.Init (bufData, bufSize);
    b.ResetInWriteRvsMode();

    // encode a true value and verify
    aBool1 = true;

    if (!aBool1.BEncPdu (b, len1))
    {
        noErr = false;
        LOG( DBG_ERROR ) << "Error encoding TRUE BOOLEAN value." << eline;
    }

    b.ResetInReadMode();

    aBool2 = false; // set to opposite of expected value

    // make sure no decode errors and that it decodes to true
    if (!aBool2.BDecPdu (b, len2) || !aBool2 || (len1 != len2))
    {
        noErr = false;
        LOG( DBG_ERROR ) << "Error decoding TRUE BOOLEAN value." << eline;
    }

    // now encode a false value and verify
    b.ResetInWriteRvsMode();
    aBool1 = false;

    if (!aBool1.BEncPdu (b, len1))
    {
        noErr = false;
        LOG( DBG_ERROR ) << "Error encoding FALSE BOOLEAN value." << eline;
    }

    b.ResetInReadMode();

    aBool2 = true; // set to opposite of expected value

    // make sure no decode errors and that it decodes to false
    if (!aBool2.BDecPdu (b, len2) || aBool2 || (len1 != len2))
    {
        noErr = false;
        LOG( DBG_ERROR ) << "Error decoding FALSE BOOLEAN value." << eline;
    }

    return noErr;
}  // TestAsn::Bool 


//
// returns true if passes encode/decode tests
//
int
TestAsn::Int()
{
    MemBlock mem( testPool );

    AsnBuf  b;
    uint8 bufData[bufSize];
    AsnInt a1(&mem);
    AsnInt a2(&mem);
    int i,j, sign;
    AsnLen len1;
    AsnLen len2;
    int noErr = true;

    // initialize a small buffer
    b.Init (bufData, bufSize);

    //
    // Encode a range of integers: negative & positive in
    //  the 1 to sizeof (long int) range
    //

    sign = 1;
    for (j = 0; j < 2; j++)
    {
        for (i = 0; i < sizeof (long int); i++)
        {
            b.ResetInWriteRvsMode();

            a1 = sign * (17 << (i * 8)); // 17 is a random choice
            if (!a1.BEncPdu (b, len1))
            {
                noErr = false;
                LOG( DBG_ERROR ) << "Error encoding INTEGER value " << a1 << "." << eline;
            }

            b.ResetInReadMode();
            a2 = 0;

            // make sure no decode errors and that it decodes to the correc val
            if (!a2.BDecPdu (b, len2) || (a2 != a1) || (len1 != len2))
            {
                noErr = false;
                LOG( DBG_ERROR ) << "Error decoding INTEGER value " << a1 << "." << eline;
            }
        }
        sign = -1;
    }

    return noErr;

} // TestAsn::Int 


//
// returns true if passes encode/decode tests
//
int
TestAsn::Octs()
{
    MemBlock mem( testPool );

    AsnBuf  b;
    uint8 bufData[bufSize];
    AsnOcts a1(&mem);
    AsnOcts a2(&mem);
    int j;
    AsnLen len1;
    AsnLen len2;
    int noErr = true;

    // initialize a small buffer
    b.Init (bufData, bufSize);

    a1 = (uint8*)"Hello Gumby?";
    for (j = 0; j < 2; j++)
    {
        b.ResetInWriteRvsMode();

        if (!a1.BEncPdu (b, len1))
        {
            noErr = false;
            LOG( DBG_ERROR ) << "Error encoding OCTET STRING value " << a1 << "." << eline;
        }

        b.ResetInReadMode();

        // make sure no decode errors and that it decodes to the correc val
        if (!a2.BDecPdu (b, len2) || (a2 != a1) || (len1 != len2))
        {
            noErr = false;
            LOG( DBG_ERROR ) << "Error decoding OCTET STRING value " << a1 << "." << eline;
        }
        a1 = (uint8*)""; // try an empty string
    }

    return noErr;

} // TestAsn::Octs 



//
// returns true if passes encode/decode tests
//
int
TestAsn::Bits()
{
    MemBlock mem( testPool );

    AsnBuf  b;
    uint8 bufData[bufSize];
    AsnBits a1(&mem, 32);
    AsnBits a2(&mem, 32);
    short bitsToSet[32] = { 0, 1, 0, 0, 1, 1, 0, 1,
                            0, 1, 0, 0, 1, 1, 0, 1,
                            0, 1, 0, 0, 1, 1, 0, 1,
                            0, 1, 0, 0, 1, 1, 0, 1 };
    int i;
    AsnLen len1;
    AsnLen len2;
    int noErr = true;

    // initialize a small buffer
    b.Init (bufData, bufSize);


    // set some bits
    for (i = 0; i < 32; i++)
    {
        if (bitsToSet[i])
            a1.SetBit (i);
        else
            a1.ClrBit (i);

    }

    b.ResetInWriteRvsMode();
    if (!a1.BEncPdu (b, len1))
    {
        noErr = false;
        LOG( DBG_ERROR ) << "Error encoding BIT STRING value " << a1 << "." << eline;
    }

    b.ResetInReadMode();

    // make sure no decode errors and that it decodes to the correc val
    if (!a2.BDecPdu (b, len2) || (a2 != a1) || (len1 != len2))
    {
        noErr = false;
        LOG( DBG_ERROR ) << "Error decoding BIT STRING value " << a1 << "." << eline;
    }


    return noErr;

} // TestAsn::Bits 



//
// returns true if passes encode/decode tests
//
int
TestAsn::Oid()
{
    MemBlock mem( testPool );

    AsnBuf  b;
    uint8 bufData[bufSize];
    AsnOid a1(&mem, 0,1,2,3,4,5,6);
    AsnOid a2(&mem);
    AsnOid a3(&mem,2,38,29,40,200,10,4000);
    int i;
    AsnLen len1;
    AsnLen len2;
    int noErr = true;

    // initialize a small buffer
    b.Init (bufData, bufSize);

    for (i = 0; i < 2; i++)
    {
        b.ResetInWriteRvsMode();

        if (!a1.BEncPdu (b, len1))
        {
            noErr = false;
            LOG( DBG_ERROR ) << "Error encoding OBJECT IDENTIFIER value " << a1 << "." << eline;
        }

        b.ResetInReadMode();

        // make sure no decode errors and that it decodes to the correc val
        if (!a2.BDecPdu (b, len2) || (a2 != a1) || (len1 != len2))
        {
            noErr = false;
            LOG( DBG_ERROR ) << "Error decoding OBJECT IDENTIFIER value " << a1 << "." << eline;
        }

        a1 = a3;
    }
    return noErr;

} // TestAsn::Oid 



//
// returns true if passes encode/decode tests
//
int
TestAsn::Real()
{
    MemBlock mem( testPool );

    AsnBuf  b;
    uint8 bufData[bufSize];
    AsnReal a2(&mem);
    AsnReal a[] =
    { 
        AsnReal(&mem,0.0),
        AsnReal(&mem,0.8),
        AsnReal(&mem,-22.484848),
        PLUS_INFINITY,
        MINUS_INFINITY
        };
    int i;
    AsnLen len1;
    AsnLen len2;
    int noErr = true;


    //
    // if you do not have the ieee_functions in your math lib,
    // this will not link.  Comment it out and cross you fingers.
    // (or check/set the +/-infinity values for you architecture)
    //
    if ( _finite ((double)PLUS_INFINITY) || _finite ((double)MINUS_INFINITY))
    {
        //LOG( DBG_ERROR ) << "WARNING: PLUS_INFINITY and MINUS_INFINITY in .../c++-lib/src/asn-real.C are" << eline;
        //LOG( DBG_ERROR ) << "not correct for this architecture.  Modify the AsnPlusInfinity() routine." << eline;
    }


    // initialize a small buffer
    b.Init (bufData, bufSize);

    for (i = 0; i < 5; i++)
    {
        b.ResetInWriteRvsMode();

        if (!a[i].BEncPdu (b, len1))
        {
            noErr = false;
            LOG( DBG_ERROR ) << "Error encoding REAL value " << a[i] << "." << eline;
        }

        b.ResetInReadMode();

        // make sure no decode errors and that it decodes to the correc val
        if (!a2.BDecPdu (b, len2) || (a2 != a[i]) || (len1 != len2))
        {
            noErr = false;
            LOG( DBG_ERROR ) << "Error decoding REAL value " << a[i] << "." << eline;
        }
    }

    return noErr;

} // TestAsn::Real 


int TestAsn::Run()
{
    int isErr = false;

    if (!TestAsn::Buffers())
    {
        LOG( DBG_ERROR ) << "Failed buffer tests, no point in proceeding ... bye!" << eline;
        return 1;
    }

    if (!TestAsn::Tag())
    {
        LOG( DBG_ERROR ) << "Failed Tag test." << eline;
        isErr = true;
    }

    if (!TestAsn::Len())
    {
        LOG( DBG_ERROR ) << "Failed Length test." << eline;
        isErr = true;
    }

    if (!TestAsn::Bool())
    {
        LOG( DBG_ERROR ) << "Failed BOOLEAN test." << eline;
        isErr = true;
    }


    if (!TestAsn::Int())
    {
        LOG( DBG_ERROR ) << "Failed INTEGER test." << eline;
        isErr = true;
    }

    if (!TestAsn::Octs())
    {
        LOG( DBG_ERROR ) << "Failed OCTET STRING test." << eline;
        isErr = true;
    }


    if (!TestAsn::Bits())
    {
        LOG( DBG_ERROR ) << "Failed BIT STRING test." << eline;
        isErr = true;
    }


    if (!TestAsn::Oid())
    {
        LOG( DBG_ERROR ) << "Failed OBJECT IDENTIFIER test." << eline;
        isErr = true;
    }


    if (!TestAsn::Real())
    {
        LOG( DBG_ERROR ) << "Failed REAL test." << eline;
        isErr = true;
    }

    if (!TestAsn().USTRs())
    {
        LOG( DBG_ERROR ) << "Failed USTR test." << eline;
        isErr = true;
    }

    if (isErr)
    {
        LOG( DBG_ERROR ) << "There are errors in the primitive type encoding/decoding" << eline;
        LOG( DBG_ERROR ) << "library for this architecture.  Time for debugger..." << eline;
        LOG( DBG_ERROR ) << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << eline;
    }
    else
    {
        LOG( DBG_TRACE ) << "The primitive type encoding/decoding library passed simple tests." << eline;
        LOG( DBG_TRACE ) << "It should be safe to use..." << eline;
        LOG( DBG_TRACE ) << "--------------------------------------------------------" << eline;
    }

    return isErr;
}
