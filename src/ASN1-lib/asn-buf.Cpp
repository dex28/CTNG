/*
    Project: ASN1Lib

    Module: asn-buf.Cpp

    Description: AsnBuf implementation

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "ASN1-Lib.h"

using namespace std;

void AsnBuf::Dump( CTsvcLIB::LOG& os, bool show_readLoc ) const
{
    os << "(len = " << size_t( dataEnd - dataStart )
        << ") ASN.1 data:" << CTsvcLIB::eline;

    int count = 0;
    for ( uint8* p = dataStart; p < dataEnd; p++, count++ )
    {
        if ( count % 16 == 0 )
            os << "   ";

        if ( show_readLoc && p + 1 == readLoc )
            os << " -> ";
        else
            os << " ";

        os << TO_HEX( *p >> 4 ) << TO_HEX( *p );

        if ( ( count % 16 ) == 15 && p + 1 != dataEnd )
            os << CTsvcLIB::eline;
        }

    os << CTsvcLIB::eline;
    }
