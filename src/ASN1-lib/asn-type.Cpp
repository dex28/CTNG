/*
    Project: ASN1Lib

    Module: asn-type.Cpp

    Description: Base ASN.1 Type abstract class

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "ASN1-Implementation.h"

using namespace std;

AsnType::~AsnType()
{
    }

AsnType	 *AsnType::Clone() const
{
    return NULL;
    }

void AsnType::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    throw "ERROR I0045: AsnType.BDec(): Attempt to decode an improperly formed ANY type (programming error).";
    }

AsnLen AsnType::BEnc (AsnBuf& b)
{
    throw "ERROR I0046: AsnType.BDec(): Attempt to decode an improperly formed ANY type (programming error).";
    return 0;
    }

int AsnType::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
    }

int AsnType::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
        BDec (b, bytesDecoded);
        return !b.ReadError();
        }
    catch( const char* )
    {
        return false;
        }
    }

void AsnType::Print (CTsvcLIB::LOG &os) const
{
    os << "ERROR - Attempt to print an improperly formed ANY type (programming error)." << CTsvcLIB::eline;
    }

