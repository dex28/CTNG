/*
    Project: CSTALib

    Module: CSTA-Any.Cpp

    Description: ROSE linkage to CSTA / ANY datatypes.

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "ASN1-Implementation.h"
#include "CSTA.h"

/////////////////////////////////////////////////////////////////////////////
namespace ASN
{

///////////////////////////////////////////////////////////////////////////////
// class OperationArgument

AsnLen
OperationArgument::BEnc( AsnBuf& b )
{
    if ( ! value )
        throw "ERROR I1001: OperationArgument.BEnc(): Value is NULL";

    return value->BEnc (b);
}

void
OperationArgument::BDec( AsnBuf& b, AsnLen &bytesDecoded )
{
    value = NULL;

    switch( intId )
    {
        case OperationIDType::alternateCall :
            value = new(memBlock) AlternateCallArgument (memBlock);
            break;
        case OperationIDType::answerCall :
            value = new(memBlock) AnswerCallArgument (memBlock);
            break;
        case OperationIDType::callCompletion :
            value = new(memBlock) CallCompletionArgument (memBlock);
            break;
        case OperationIDType::clearCall :
            value = new(memBlock) ClearCallArgument (memBlock);
            break;
        case OperationIDType::clearConnection :
            value = new(memBlock) ClearConnectionArgument (memBlock);
            break;
        case OperationIDType::conferenceCall :
            value = new(memBlock) ConferenceCallArgument (memBlock);
            break;
        case OperationIDType::consultationCall :
            value = new(memBlock) ConsultationCallArgument (memBlock);
            break;
        case OperationIDType::divertCall :
            value = new(memBlock) DivertCallArgument (memBlock);
            break;
        case OperationIDType::holdCall :
            value = new(memBlock) HoldCallArgument (memBlock);
            break;
        case OperationIDType::makeCall :
            value = new(memBlock) MakeCallArgument (memBlock);
            break;
        case OperationIDType::makePredictiveCall :
            value = new(memBlock) MakePredictiveCallArgument (memBlock);
            break;
        case OperationIDType::queryDevice :
            value = new(memBlock) QueryDeviceArgument (memBlock);
            break;
        case OperationIDType::reconnectCall :
            value = new(memBlock) ReconnectCallArgument (memBlock);
            break;
        case OperationIDType::retrieveCall :
            value = new(memBlock) RetrieveCallArgument (memBlock);
            break;
        case OperationIDType::setFeature :
            value = new(memBlock) SetFeatureArgument (memBlock);
            break;
        case OperationIDType::transferCall :
            value = new(memBlock) TransferCallArgument (memBlock);
            break;
        case OperationIDType::cSTAEventReport :
            value = new(memBlock) CSTAEventReportArgument (memBlock);
            break;
        case OperationIDType::routeRequest :
            value = new(memBlock) RouteRequestArgument (memBlock);
            break;
        case OperationIDType::reRouteRequest :
            value = new(memBlock) ReRouteRequestArgument (memBlock);
            break;
        case OperationIDType::routeSelectRequest :
            value = new(memBlock) RouteSelectRequestArgument (memBlock);
            break;
        case OperationIDType::routeUsedRequest :
            value = new(memBlock) RouteUsedRequestArgument (memBlock);
            break;
        case OperationIDType::routeEndRequest :
            value = new(memBlock) RouteEndRequestArgument (memBlock);
            break;
        case OperationIDType::escapeService :
            value = new(memBlock) EscapeServiceArgument (memBlock);
            break;
        case OperationIDType::systemStatus :
            value = new(memBlock) SystemStatusArgument (memBlock);
            break;
        case OperationIDType::monitorStart :
            value = new(memBlock) MonitorStartArgument (memBlock);
            break;
        case OperationIDType::changeMonitorFilter :
            value = new(memBlock) ChangeMonitorFilterArgument (memBlock);
            break;
        case OperationIDType::monitorStop :
            value = new(memBlock) MonitorStopArgument (memBlock);
            break;
        case OperationIDType::snapshotDevice :
            value = new(memBlock) SnapshotDeviceArgument (memBlock);
            break;
        case OperationIDType::snapshotCall :
            value = new(memBlock) SnapshotCallArgument (memBlock);
            break;
        }

    if ( value == NULL )
        throw "ERROR I1002: OperationArgument.BDec(): ANY id not decoded";

    value->BDec( b, bytesDecoded );
}

///////////////////////////////////////////////////////////////////////////////
// class OperationResult

AsnLen
OperationResult::BEnc( AsnBuf& b )
{
    if ( ! value )
        throw "ERROR I1003: OperationResult.BEnc(): Value is NULL";

    return value->BEnc (b);
}

void
OperationResult::BDec( AsnBuf& b, AsnLen &bytesDecoded )
{
    value = NULL;

    switch( intId )
    {
        case OperationIDType::alternateCall :
            value = new(memBlock) AlternateCallResult (memBlock);
            break;
        case OperationIDType::answerCall :
            value = new(memBlock) AnswerCallResult (memBlock);
            break;
        case OperationIDType::callCompletion :
            value = new(memBlock) CallCompletionResult (memBlock);
            break;
        case OperationIDType::clearCall :
            value = new(memBlock) ClearCallResult (memBlock);
            break;
        case OperationIDType::clearConnection :
            value = new(memBlock) ClearConnectionResult (memBlock);
            break;
        case OperationIDType::conferenceCall :
            value = new(memBlock) ConferenceCallResult (memBlock);
            break;
        case OperationIDType::consultationCall :
            value = new(memBlock) ConsultationCallResult (memBlock);
            break;
        case OperationIDType::divertCall :
            value = new(memBlock) DivertCallResult (memBlock);
            break;
        case OperationIDType::holdCall :
            value = new(memBlock) HoldCallResult (memBlock);
            break;
        case OperationIDType::makeCall :
            value = new(memBlock) MakeCallResult (memBlock);
            break;
        case OperationIDType::makePredictiveCall :
            value = new(memBlock) MakePredictiveCallResult (memBlock);
            break;
        case OperationIDType::queryDevice :
            value = new(memBlock) QueryDeviceResult (memBlock);
            break;
        case OperationIDType::reconnectCall :
            value = new(memBlock) ReconnectCallResult (memBlock);
            break;
        case OperationIDType::retrieveCall :
            value = new(memBlock) RetrieveCallResult (memBlock);
            break;
        case OperationIDType::setFeature :
            value = new(memBlock) SetFeatureResult (memBlock);
            break;
        case OperationIDType::transferCall :
            value = new(memBlock) TransferCallResult (memBlock);
            break;
        case OperationIDType::escapeService :
            value = new(memBlock) EscapeServiceResult (memBlock);
            break;
        case OperationIDType::systemStatus :
            value = new(memBlock) SystemStatusResult (memBlock);
            break;
        case OperationIDType::monitorStart :
            value = new(memBlock) MonitorStartResult (memBlock);
            break;
        case OperationIDType::changeMonitorFilter :
            value = new(memBlock) ChangeMonitorFilterResult (memBlock);
            break;
        case OperationIDType::monitorStop :
            value = new(memBlock) MonitorStopResult (memBlock);
            break;
        case OperationIDType::snapshotDevice :
            value = new(memBlock) SnapshotDeviceResult (memBlock);
            break;
        case OperationIDType::snapshotCall :
            value = new(memBlock) SnapshotCallResult (memBlock);
            break;
        }

    if ( value == NULL )
        throw "ERROR I1004: OperationArgument.BDec(): ANY data is not decoded";

    value->BDec( b, bytesDecoded );
}

///////////////////////////////////////////////////////////////////////////////
// class EventInfo

void EventInfo:: SetTypeBy( const EventTypeID& id )
{
    if ( id.cCSTAform )
        intId = *id.cCSTAform;
    else
        throw "ERROR I1201: EventInfo.SetTypeBy(): cCSTAform is NULL";
    }

AsnLen
EventInfo::BEnc( AsnBuf& b )
{
    if ( ! value )
        throw "ERROR I1005: EventInfo.BEnc(): Value is NULL";

    return value->BEnc (b);
}

void
EventInfo::BDec( AsnBuf& b, AsnLen &bytesDecoded )
{
    value = NULL;

    switch( intId )
    {
        // call events
        //
        case EventIDType::callCleared :
            value = new(memBlock) CallClearedEventInfo (memBlock);
            break;
        case EventIDType::conferenced :
            value = new(memBlock) ConferencedEventInfo (memBlock);
            break;
        case EventIDType::connectionCleared :
            value = new(memBlock) ConnectionClearedEventInfo (memBlock);
            break;
        case EventIDType::delivered :
            value = new(memBlock) DeliveredEventInfo (memBlock);
            break;
        case EventIDType::diverted :
            value = new(memBlock) DivertedEventInfo (memBlock);
            break;
        case EventIDType::established :
            value = new(memBlock) EstablishedEventInfo (memBlock);
            break;
        case EventIDType::failed :
            value = new(memBlock) FailedEventInfo (memBlock);
            break;
        case EventIDType::held :
            value = new(memBlock) HeldEventInfo (memBlock);
            break;
        case EventIDType::networkReached :
            value = new(memBlock) NetworkReachedEventInfo (memBlock);
            break;
        case EventIDType::originated :
            value = new(memBlock) OriginatedEventInfo (memBlock);
            break;
        case EventIDType::queued :
            value = new(memBlock) QueuedEventInfo (memBlock);
            break;
        case EventIDType::retrieved :
            value = new(memBlock) RetrievedEventInfo (memBlock);
            break;
        case EventIDType::serviceInitiated :
            value = new(memBlock) ServiceInitiatedEventInfo (memBlock);
            break;
        case EventIDType::transferred :
            value = new(memBlock) TransferredEventInfo (memBlock);
            break;

        // feature events
        //
        case EventIDType::callInformation :
            value = new(memBlock) CallInformationEventInfo (memBlock);
            break;
        case EventIDType::doNotDisturb :
            value = new(memBlock) DoNotDisturbEventInfo (memBlock);
            break;
        case EventIDType::forwarding :
            value = new(memBlock) ForwardingEventInfo (memBlock);
            break;
        case EventIDType::messageWaiting :
            value = new(memBlock) MessageWaitingEventInfo (memBlock);
            break;

        // agent state events
        //
        case EventIDType::loggedOn :
            value = new(memBlock) LoggedOnEventInfo (memBlock);
            break;
        case EventIDType::loggedOff :
            value = new(memBlock) LoggedOffEventInfo (memBlock);
            break;
        case EventIDType::notReady :
            value = new(memBlock) NotReadyEventInfo (memBlock);
            break;
        case EventIDType::ready :
            value = new(memBlock) ReadyEventInfo (memBlock);
            break;
        case EventIDType::workNotReady :
            value = new(memBlock) WorkNotReadyEventInfo (memBlock);
            break;
        case EventIDType::workReady :
            value = new(memBlock) WorkReadyEventInfo (memBlock);
            break;

        // maintenance events
        //
        case EventIDType::backInService:
            value = new(memBlock) BackInServiceEventInfo (memBlock);
            break;
        case EventIDType::outOfService:
            value = new(memBlock) OutOfServiceEventInfo (memBlock);
            break;

        // private events
        //
        case EventIDType::privateEvt :
            value = new(memBlock) PrivateEventInfo (memBlock);
            break;
        };

    if ( value == NULL )
        throw "ERROR I1006: EventInfo.BDec(): ANY data is not decoded";

    value->BDec( b, bytesDecoded );
}


///////////////////////////////////////////////////////////////////////////////
// class ErrorParameter

AsnLen
ErrorParameter::BEnc( AsnBuf& b )
{
    if ( ! value )
        throw "ERROR I1007: ErrorParameter.BEnc(): Value is NULL";

    return value->BEnc (b);
}

void
ErrorParameter::BDec( AsnBuf& b, AsnLen &bytesDecoded )
{
    value = NULL;

    switch( intId )
    {
        case ErrorIDType::universalFailure:
            value = new(memBlock) UniversalFailure (memBlock);
            break;
        }

    if ( value == NULL )
        throw "ERROR I1008: ErrorParameter.BDec(): ANY data is not decoded";

    value->BDec( b, bytesDecoded );
}

///////////////////////////////////////////////////////////////////////////////
// class PrivateAnyData

AsnLen
PrivateAnyData::BEnc( AsnBuf& b )
{
    AsnLen len = octetLen;

    // Encode private data bytes
    //
    b.PutSegRvs( octs, octetLen );

    if ( encodeLenAsEric )
    {
        // Encode 2-byte length (required by Ericsson)
        //
        b.PutByteRvs( len );
        b.PutByteRvs( len >> 8 );
        b.PutByteRvs( 0x82 );
        len += 3;
        }
    else
    {
        // Encode length
        //
        len += BEncDefLen( b, octetLen );
        }

    // Encode Universal / Constructed / Sequence TAG
    //
    len += BEncTag1( b, UNIV, CONS, SEQ_TAG_CODE );

    return len;
}

void
PrivateAnyData::BDec( AsnBuf& b, AsnLen &bytesDecoded )
{
    // read header: 4 bytes
    // should be 0x38, 0x82, len2, len1
    //
    AsnTag tag = BDecTag (b, bytesDecoded);
    if ( tag != MAKE_TAG_ID( UNIV, CONS, SEQ_TAG_CODE ) )
    {
	    throw "ERROR I1009: PrivateAnyData.BDec(): Expected SEQUENCE tag in Ericsson";
    }

    AsnLen bytesDec1 = bytesDecoded;
    AsnLen elmtLen = BDecLen (b, bytesDecoded);
    encodeLenAsEric = ( bytesDec1 + 3 == bytesDecoded ); // if it is 0x82 00 <len>

    // TRACE( "------------------ len = " << bytesDecoded - bytesDec1 );

    octetLen = elmtLen;
    octs =  new(memBlock) uint8[ elmtLen + 1 ];
    b.CopyOut( octs, elmtLen );

    if (b.ReadError())
    {
        throw "ERROR I1010: PrivateAnyData::BDec(): Decoded past end of data";
    }

    // add null terminator - this is not included in the str's len
    octs[elmtLen] = '\0';
    bytesDecoded += elmtLen;
}

void PrivateAnyData::Print (CTsvcLIB::LOG &os) const
{
    os << "SEQUENCE" << CTsvcLIB::eline;
    Indent (os, indentG);
    os << "{" << CTsvcLIB::eline;
    indentG += stdIndentG;

    Indent (os, indentG);
    for ( size_t i = 0; i < octetLen; i++ )
    {
        os << TO_HEX (octs[i] >> 4) << TO_HEX (octs[i]);
        if ( i % 16 == 15 )
        {
            os << CTsvcLIB::eline;
            Indent (os, indentG );
            }
        else
            os << " ";
        }

    os << "," << CTsvcLIB::eline;
    Indent (os, indentG );
    os << "\"";

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
    os << "\"" << CTsvcLIB::eline;

    indentG -= stdIndentG;
    Indent (os, indentG);
    os << "}";
}

USTR PrivateAnyData::toUSTR( void ) const
{
    return USTR( octs, octetLen );
    }

//////////////////////////////////////////////////////////////////////////////
} // namespace ASN