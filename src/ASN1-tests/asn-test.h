/*
    Project: ASN1Test

    Module: asn-test.h

    Description: ASN1Lib integrity test class

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#ifndef _testasn_h_inlcuded
#define _testasn_h_included

class TestAsn
{
    int Buffers();
    int Tag();
    int Len();
    int Bool();
    int Int();
    int Octs();
    int Bits();
    int Oid();
    int Real();
public:
    int USTRs();
    int Run();
    };

#endif // _testasn_h_included