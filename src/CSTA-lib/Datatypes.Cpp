/*
    Project: CSTALib

    Module: Datatypes.Cpp

    Description: Ddata types implementation:
        classes callIdType, devIdType, connectionIdType

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "CSTA-Lib.h"

using namespace ASN;

/////////////////////////////////////////////////////////////////////////////
namespace MidCSTA
{

/////////////////////////////////////////////////////////////////////////////
// deviceIdType class implementation

deviceIdType:: deviceIdType( DeviceID* asn )
{
    if ( ! asn )
        return;

    switch( asn->choiceId )
    {
        case DeviceID::dialingNumberCid:
            *this = USTR( asn->dialingNumber );
            break;
        case DeviceID::deviceNumberCid:
            char num[ 32 ];
            num[ 0 ] = 'd';
            ::ltoa( (AsnUIntType) asn->deviceNumber, num + 1, 10 );
            *this = USTR( num );
            break;
        default:
            *this = USTR( "?" );
            break;
        }
    }

deviceIdType:: deviceIdType( ExtendedDeviceID* asn )
{
    if ( ! asn )
        return;

    switch( asn->choiceId )
    {
        case ExtendedDeviceID::dialingNumberCid:
            *this = USTR( asn->dialingNumber );
            break;
        case ExtendedDeviceID::deviceNumberCid:
            char num[ 32 ];
            num[ 0 ] = 'd';
            ::ltoa( (AsnUIntType) asn->deviceNumber, num + 1, 10 );
            *this = USTR( num );
            break;
        default:
            *this = USTR( "?" );
            break;
        }
    }

deviceIdType:: deviceIdType( CallingDeviceID* asn )
{
    if ( ! asn )
        return;

    switch( asn->choiceId )
    {
        case CallingDeviceID::deviceIdentifierCid:
            *this = asn->deviceIdentifier;
            return;
        case CallingDeviceID::notKnownCid:
            *this = USTR( "notKnown" );
            break;
        case CallingDeviceID::notRequiredCid:
            *this = USTR( "notRequired" );
            break;
        }
    }

deviceIdType:: deviceIdType( CalledDeviceID* asn )
{
    if ( ! asn )
        return;

    switch( asn->choiceId )
    {
        case CalledDeviceID::deviceIdentifierCid:
            *this = asn->deviceIdentifier;
            return;
        case CalledDeviceID::notKnownCid:
            *this = USTR( "notKnown" );
            break;
        case CalledDeviceID::notRequiredCid:
            *this = USTR( "notRequired" );
            break;
        }
    }

deviceIdType:: deviceIdType( RedirectionDeviceID* asn )
{
    if ( ! asn )
        return;

    switch( asn->choiceId )
    {
        case RedirectionDeviceID::numberDialedCid:
            *this = asn->numberDialed;
            return;
        case RedirectionDeviceID::notKnownCid:
            *this = USTR( "notKnown" );
            break;
        case RedirectionDeviceID::notRequiredCid:
            *this = USTR( "notRequired" );
            break;
        }
    }

deviceIdType:: deviceIdType( SubjectDeviceID* asn )
{
    if ( ! asn )
        return;

    switch( asn->choiceId )
    {
        case SubjectDeviceID::deviceIdentifierCid:
            *this = asn->deviceIdentifier;
            return;
        case SubjectDeviceID::notKnownCid:
            *this = USTR( "notKnown" );
            break;
        case SubjectDeviceID::notRequiredCid:
            *this = USTR( "notRequired" );
            break;
        }
    }

DeviceID* deviceIdType:: BuildDeviceID( MemBlock* mem ) const
{
    ASN::DeviceID* dev = new(mem) ASN::DeviceID(mem);

    IA5String* digits = new(mem) IA5String(mem);
        digits->Set( Ptr(), Len () );

    dev->choiceId = ASN::DeviceID::dialingNumberCid;
    dev->dialingNumber = digits;

    return dev;
    }

/////////////////////////////////////////////////////////////////////////////
// connectionIdType class implementation

connectionIdType:: connectionIdType( ConnectionID* asn )
{
    if ( ! asn )
        return;

    if ( asn->call )
        callId = USTR( asn->call );

    if ( ! asn->device )
        return;

    switch( asn->device->choiceId )
    {
        case ConnectionIDChoice::staticIDCid:
            devId = deviceIdType( asn->device->staticID );
            break;
        case ConnectionIDChoice::dynamicIDCid:
            devId = USTR( asn->device->dynamicID );
            break;
        }
    }

connectionIdType:: connectionIdType( const USTR& ustr )
{
    // create conn_id from "dev:call" ustr

    if ( ustr.IsNULL () )
        return;

    char device_id[ 256 ] = {0};
    char call_id[ 256 ] = {0};

    sscanf( (const char*)ustr, "%[^:]:%s", device_id, call_id );

    devId = USTR( device_id );

    if ( call_id[ 0 ] == 'x' )
    {
        uint8 call_id_bin[ 256 ];
        uint8* chp = call_id_bin;
        for ( int i = 1; call_id[ i ] && call_id[ i + 1 ]; i += 2 )
        {
            *chp++ = ( FROM_HEX( call_id[ i ] ) << 4 ) | FROM_HEX( call_id[ i + 1 ] );
            }
        callId = USTR( call_id_bin, chp - call_id_bin );
        };
    }

connectionIdType:: operator USTR () const
{
    char buf[ 256 ];
    sprintf( buf, "%s:%s", (const char*)devId, (const char*)callId.toHex() );
    return USTR( buf );
    }

ConnectionID* connectionIdType:: BuildConnectionID( MemBlock* mem ) const
{
    if ( devId.IsBinary () ) // dynamic device id
    {
        AsnOcts* dev = new(mem) AsnOcts(mem);
            dev->Set( devId.Ptr(), devId.Len() );

        ASN::ConnectionIDChoice* choice = new(mem) ASN::ConnectionIDChoice(mem);
            choice->choiceId = ASN::ConnectionIDChoice::dynamicIDCid;
            choice->dynamicID = dev;

        AsnOcts* call = new(mem) AsnOcts(mem);
            call->Set( callId.Ptr(), callId.Len() );

        ASN::ConnectionID* cn = new(mem) ASN::ConnectionID(mem);
            cn->call = call;
            cn->device = choice;

        return cn;
        }
    else // static device id: dialingNumber or deviceNumber
    {
        ASN::ConnectionIDChoice* choice = new(mem) ASN::ConnectionIDChoice(mem);
            choice->choiceId = ASN::ConnectionIDChoice::staticIDCid;
            choice->staticID = devId.BuildDeviceID(mem);

        AsnOcts* call = new(mem) AsnOcts(mem);
            call->Set( callId.Ptr(), callId.Len() );

        ASN::ConnectionID* cn = new(mem) ASN::ConnectionID(mem);
            cn->call = call;
            cn->device = choice;

        return cn;
        }
    }

//////////////////////////////////////////////////////////////////////////////
} // namespace MidCSTA