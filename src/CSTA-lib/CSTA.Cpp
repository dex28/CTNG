/*
    Project: CSTALib

    Module: CSTA.Cpp

    Description: class member functions for ASN.1 module CSTA

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
    
    Wed Aug 29 14:26:23 2001
*/

#include "ASN1-Implementation.h"
#include "CSTA.h"

namespace // unnamed
{
    MemPool consts_pool( "CSTA ASN.1 constants" );
    MemBlock consts_mem( consts_pool );
    }

/////////////////////////////////////////////////////////////////////////////
namespace ASN
{

///////////////////////////////////////////////////////////////////////////////
// Constants' values definitions

    const AsnInt alternateCall ( &consts_mem, 1 );

    const AsnInt answerCall ( &consts_mem, 2 );

    const AsnInt callCompletion ( &consts_mem, 3 );

    const AsnInt clearCall ( &consts_mem, 4 );

    const AsnInt clearConnection ( &consts_mem, 5 );

    const AsnInt conferenceCall ( &consts_mem, 6 );

    const AsnInt consultationCall ( &consts_mem, 7 );

    const AsnInt divertCall ( &consts_mem, 8 );

    const AsnInt holdCall ( &consts_mem, 9 );

    const AsnInt makeCall ( &consts_mem, 10 );

    const AsnInt makePredictiveCall ( &consts_mem, 11 );

    const AsnInt queryDevice ( &consts_mem, 12 );

    const AsnInt reconnectCall ( &consts_mem, 13 );

    const AsnInt retrieveCall ( &consts_mem, 14 );

    const AsnInt setFeature ( &consts_mem, 15 );

    const AsnInt transferCall ( &consts_mem, 16 );

    const AsnInt cSTAEventReport ( &consts_mem, 21 );

    const AsnInt callCleared ( &consts_mem, 1 );

    const AsnInt conferenced ( &consts_mem, 2 );

    const AsnInt connectionCleared ( &consts_mem, 3 );

    const AsnInt delivered ( &consts_mem, 4 );

    const AsnInt diverted ( &consts_mem, 5 );

    const AsnInt established ( &consts_mem, 6 );

    const AsnInt failed ( &consts_mem, 7 );

    const AsnInt held ( &consts_mem, 8 );

    const AsnInt networkReached ( &consts_mem, 9 );

    const AsnInt originated ( &consts_mem, 10 );

    const AsnInt queued ( &consts_mem, 11 );

    const AsnInt retrieved ( &consts_mem, 12 );

    const AsnInt serviceInitiated ( &consts_mem, 13 );

    const AsnInt transferred ( &consts_mem, 14 );

    const AsnInt callInformation ( &consts_mem, 101 );

    const AsnInt doNotDisturb ( &consts_mem, 102 );

    const AsnInt forwarding ( &consts_mem, 103 );

    const AsnInt messageWaiting ( &consts_mem, 104 );

    const AsnInt loggedOn ( &consts_mem, 201 );

    const AsnInt loggedOff ( &consts_mem, 202 );

    const AsnInt notReady ( &consts_mem, 203 );

    const AsnInt ready ( &consts_mem, 204 );

    const AsnInt workNotReady ( &consts_mem, 205 );

    const AsnInt workReady ( &consts_mem, 206 );

    const AsnInt backInService ( &consts_mem, 301 );

    const AsnInt outOfService ( &consts_mem, 302 );

    const AsnInt privateEvt ( &consts_mem, 401 );

    const AsnInt routeRequest ( &consts_mem, 31 );

    const AsnInt reRouteRequest ( &consts_mem, 32 );

    const AsnInt routeSelectRequest ( &consts_mem, 33 );

    const AsnInt routeUsedRequest ( &consts_mem, 34 );

    const AsnInt routeEndRequest ( &consts_mem, 35 );

    const AsnInt escapeService ( &consts_mem, 51 );

    const AsnInt systemStatus ( &consts_mem, 52 );

    const AsnInt monitorStart ( &consts_mem, 71 );

    const AsnInt changeMonitorFilter ( &consts_mem, 72 );

    const AsnInt monitorStop ( &consts_mem, 73 );

    const AsnInt snapshotDevice ( &consts_mem, 74 );

    const AsnInt snapshotCall ( &consts_mem, 75 );

    const AsnInt universalFailure ( &consts_mem, 1 );

    const AsnOid escEnterDTMF ( &consts_mem, 1, 3, 12, 2, 1213, 21, 1 );

    const AsnOid escCancelCallBack ( &consts_mem, 1, 3, 12, 2, 1213, 21, 2 );

    const AsnOid escMessageDiversion ( &consts_mem, 1, 3, 12, 2, 1213, 21, 3 );

    const AsnOid escAccountCode ( &consts_mem, 1, 3, 12, 2, 1213, 21, 4 );

    const AsnOid escAuthorizationCode ( &consts_mem, 1, 3, 12, 2, 1213, 21, 5 );

    const AsnOid escPressProgrammableKey ( &consts_mem, 1, 3, 12, 2, 1213, 21, 8 );

    const AsnOid escAssociateData ( &consts_mem, 1, 3, 12, 2, 1213, 21, 9 );

    const AsnOid escForwardACDGroup ( &consts_mem, 1, 3, 12, 2, 1213, 21, 12 );

    const AsnOid escQueryMsgDiversionStrings ( &consts_mem, 1, 3, 12, 2, 1213, 21, 14 );

    const AsnOid escQueryFeatureAndResponse ( &consts_mem, 1, 3, 12, 2, 1213, 21, 15 );

    const AsnOid escSetFeatureAndResponse ( &consts_mem, 1, 3, 12, 2, 1213, 21, 16 );


///////////////////////////////////////////////////////////////////////////////
// Class member definitions

const char* GeneralProblem::EnumText( AsnIntType value )
  {
    switch( value )
    {
      case 0: return "unrecognisedAPDU"; break;
      case 1: return "mistypedAPDU"; break;
      case 2: return "badlyStructuredAPDU"; break;
      default: return "?"; break;
    };
  };

void GeneralProblem::Print ( CTsvcLIB::LOG& os ) const
{
  os << "INTEGER " << EnumText(value) << " (" << value << ")";
}


const char* InvokeProblem::EnumText( AsnIntType value )
  {
    switch( value )
    {
      case 0: return "duplicateInvocation"; break;
      case 1: return "unrecognisedOperation"; break;
      case 2: return "mistypedArgument"; break;
      case 3: return "resourceLimitation"; break;
      case 4: return "initiatorReleasing"; break;
      case 5: return "unrecognisedLinkedID"; break;
      case 6: return "linkedResponseUnexpected"; break;
      case 7: return "unexpectedChildOperation"; break;
      default: return "?"; break;
    };
  };

void InvokeProblem::Print ( CTsvcLIB::LOG& os ) const
{
  os << "INTEGER " << EnumText(value) << " (" << value << ")";
}


const char* ReturnResultProblem::EnumText( AsnIntType value )
  {
    switch( value )
    {
      case 0: return "unrecognisedInvocation"; break;
      case 1: return "resultResponseUnexpected"; break;
      case 2: return "mistypedResult"; break;
      default: return "?"; break;
    };
  };

void ReturnResultProblem::Print ( CTsvcLIB::LOG& os ) const
{
  os << "INTEGER " << EnumText(value) << " (" << value << ")";
}


const char* ReturnErrorProblem::EnumText( AsnIntType value )
  {
    switch( value )
    {
      case 0: return "unrecognisedInvocation"; break;
      case 1: return "errorResponseUnexpected"; break;
      case 2: return "unrecognisedError"; break;
      case 3: return "unexpectedError"; break;
      case 4: return "mistypedParameter"; break;
      default: return "?"; break;
    };
  };

void ReturnErrorProblem::Print ( CTsvcLIB::LOG& os ) const
{
  os << "INTEGER " << EnumText(value) << " (" << value << ")";
}


const char* Operations::EnumText( AsnIntType value )
  {
    switch( value )
    {
      case 1: return "generic"; break;
      case 2: return "requestIncompatibleWithObject"; break;
      case 3: return "valueOutOfRange"; break;
      case 4: return "objectNotKnown"; break;
      case 5: return "invalidCallingDevice"; break;
      case 6: return "invalidCalledDevice"; break;
      case 7: return "invalidForwardingDestination"; break;
      case 8: return "privilegeViolationOnSpecifiedDevice"; break;
      case 9: return "privilegeViolationOnCalledDevice"; break;
      case 10: return "privilegeViolationOnCallingDevice"; break;
      case 11: return "invalidCSTACallIdentifier"; break;
      case 12: return "invalidCSTADeviceIdentifier"; break;
      case 13: return "invalidCSTAConnectionIdentifier"; break;
      case 14: return "invalidDestination"; break;
      case 15: return "invalidFeature"; break;
      case 16: return "invalidAllocationState"; break;
      case 17: return "invalidCrossRefID"; break;
      case 18: return "invalidObjectType"; break;
      case 19: return "securityViolation"; break;
      default: return "?"; break;
    };
  };

void Operations::Print ( CTsvcLIB::LOG& os ) const
{
  os << "INTEGER " << EnumText(value) << " (" << value << ")";
}


const char* StateIncompatibility::EnumText( AsnIntType value )
  {
    switch( value )
    {
      case 1: return "generic"; break;
      case 2: return "invalidObjectState"; break;
      case 3: return "invalidConnectionID"; break;
      case 4: return "noActiveCall"; break;
      case 5: return "noHeldCall"; break;
      case 6: return "noCallToClear"; break;
      case 7: return "noConnectionToClear"; break;
      case 8: return "noCallToAnswer"; break;
      case 9: return "noCallToComplete"; break;
      default: return "?"; break;
    };
  };

void StateIncompatibility::Print ( CTsvcLIB::LOG& os ) const
{
  os << "INTEGER " << EnumText(value) << " (" << value << ")";
}


const char* SystemResourceAvailability::EnumText( AsnIntType value )
  {
    switch( value )
    {
      case 1: return "generic"; break;
      case 2: return "serviceBusy"; break;
      case 3: return "resourceBusy"; break;
      case 4: return "resourceOutOfService"; break;
      case 5: return "networkBusy"; break;
      case 6: return "networkOutOfService"; break;
      case 7: return "overallMonitorLimitExceeded"; break;
      case 8: return "conferenceMemberLimitExceeded"; break;
      default: return "?"; break;
    };
  };

void SystemResourceAvailability::Print ( CTsvcLIB::LOG& os ) const
{
  os << "INTEGER " << EnumText(value) << " (" << value << ")";
}


const char* SubscribedResourceAvailability::EnumText( AsnIntType value )
  {
    switch( value )
    {
      case 1: return "generic"; break;
      case 2: return "objectMonitorLimitExceeded"; break;
      case 3: return "externalTrunkLimitExceeded"; break;
      case 4: return "outstandingRequestLimitExceeded"; break;
      default: return "?"; break;
    };
  };

void SubscribedResourceAvailability::Print ( CTsvcLIB::LOG& os ) const
{
  os << "INTEGER " << EnumText(value) << " (" << value << ")";
}


const char* PerformanceManagement::EnumText( AsnIntType value )
  {
    switch( value )
    {
      case 1: return "generic"; break;
      case 2: return "performanceLimitExceeded"; break;
      default: return "?"; break;
    };
  };

void PerformanceManagement::Print ( CTsvcLIB::LOG& os ) const
{
  os << "INTEGER " << EnumText(value) << " (" << value << ")";
}


const char* SecurityError::EnumText( AsnIntType value )
  {
    switch( value )
    {
      case 0: return "unspecified"; break;
      case 1: return "sequenceNumberViolated"; break;
      case 2: return "timeStampViolated"; break;
      case 3: return "pACViolated"; break;
      case 4: return "sealViolated"; break;
      default: return "?"; break;
    };
  };

void SecurityError::Print ( CTsvcLIB::LOG& os ) const
{
  os << "INTEGER " << EnumText(value) << " (" << value << ")";
}


const char* EventCause::EnumText( AsnIntType value )
  {
    switch( value )
    {
      case 1: return "activeMonitor"; break;
      case 2: return "alternate"; break;
      case 3: return "busy"; break;
      case 4: return "callBack"; break;
      case 5: return "callCancelled"; break;
      case 6: return "callForwardAlways"; break;
      case 7: return "callForwardBusy"; break;
      case 8: return "callForwardNoAnswer"; break;
      case 9: return "callForward"; break;
      case 10: return "callNotAnswered"; break;
      case 11: return "callPickup"; break;
      case 12: return "campOn"; break;
      case 13: return "destNotObtainable"; break;
      case 14: return "doNotDisturb"; break;
      case 15: return "incompatibleDestination"; break;
      case 16: return "invalidAccountCode"; break;
      case 17: return "keyConference"; break;
      case 18: return "lockout"; break;
      case 19: return "maintenance"; break;
      case 20: return "networkCongestion"; break;
      case 21: return "networkNotObtainable"; break;
      case 22: return "newCall"; break;
      case 23: return "noAvailableAgents"; break;
      case 24: return "override"; break;
      case 25: return "park"; break;
      case 26: return "overflow"; break;
      case 27: return "recall"; break;
      case 28: return "redirected"; break;
      case 29: return "reorderTone"; break;
      case 30: return "resourcesNotAvailable"; break;
      case 31: return "silentParticipation"; break;
      case 32: return "transfer"; break;
      case 33: return "trunksBusy"; break;
      case 34: return "voiceUnitInitiator"; break;
      default: return "?"; break;
    };
  };

void EventCause::Print ( CTsvcLIB::LOG& os ) const
{
  os << "INTEGER " << EnumText(value) << " (" << value << ")";
}


const char* LocalConnectionState::EnumText( AsnIntType value )
  {
    switch( value )
    {
      case 0: return "null"; break;
      case 1: return "initiated"; break;
      case 2: return "alerting"; break;
      case 3: return "connected"; break;
      case 4: return "hold"; break;
      case 5: return "queued"; break;
      case 6: return "fail"; break;
      default: return "?"; break;
    };
  };

void LocalConnectionState::Print ( CTsvcLIB::LOG& os ) const
{
  os << "INTEGER " << EnumText(value) << " (" << value << ")";
}

AsnType *LocalConnectionState::Clone() const
{
  return new(memBlock) LocalConnectionState(memBlock);
}

AsnLen LocalConnectionState::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, PRIM, 14);
    return l;
}

void LocalConnectionState::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnTag tag;
    AsnLen elmtLen1;

    if (((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (APPL, PRIM, 14)) )
    {
        throw "ERROR C0100: LocalConnectionState.BDec(): Wrong tag";
    }
    elmtLen1 = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int LocalConnectionState::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int LocalConnectionState::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

AsnType *MonitorCrossRefID::Clone() const
{
  return new(memBlock) MonitorCrossRefID(memBlock);
}

AsnLen MonitorCrossRefID::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, APPL, PRIM, 21);
    return l;
}

void MonitorCrossRefID::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnTag tag;
    AsnLen elmtLen1;

    if (((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (APPL, PRIM, 21))
        && (tag != MAKE_TAG_ID (APPL, CONS, 21)))
    {
        throw "ERROR C0101: MonitorCrossRefID.BDec(): Wrong tag";
    }
    elmtLen1 = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int MonitorCrossRefID::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int MonitorCrossRefID::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void CallFilter::Print ( CTsvcLIB::LOG& os ) const
{
  AsnBits::Print( os );

  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "callCleared       : ";
  if ( ( bits[ 0 ] & 0x80 ) != 0 )
    os << "true  (1)," << CTsvcLIB::eline;
  else
    os << "false (0)," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "conferenced       : ";
  if ( ( bits[ 0 ] & 0x40 ) != 0 )
    os << "true  (1)," << CTsvcLIB::eline;
  else
    os << "false (0)," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "connectionCleared : ";
  if ( ( bits[ 0 ] & 0x20 ) != 0 )
    os << "true  (1)," << CTsvcLIB::eline;
  else
    os << "false (0)," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "delivered         : ";
  if ( ( bits[ 0 ] & 0x10 ) != 0 )
    os << "true  (1)," << CTsvcLIB::eline;
  else
    os << "false (0)," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "diverted          : ";
  if ( ( bits[ 0 ] & 0x08 ) != 0 )
    os << "true  (1)," << CTsvcLIB::eline;
  else
    os << "false (0)," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "established       : ";
  if ( ( bits[ 0 ] & 0x04 ) != 0 )
    os << "true  (1)," << CTsvcLIB::eline;
  else
    os << "false (0)," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "failed            : ";
  if ( ( bits[ 0 ] & 0x02 ) != 0 )
    os << "true  (1)," << CTsvcLIB::eline;
  else
    os << "false (0)," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "held              : ";
  if ( ( bits[ 0 ] & 0x01 ) != 0 )
    os << "true  (1)," << CTsvcLIB::eline;
  else
    os << "false (0)," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "networkReached    : ";
  if ( ( bits[ 1 ] & 0x80 ) != 0 )
    os << "true  (1)," << CTsvcLIB::eline;
  else
    os << "false (0)," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "originated        : ";
  if ( ( bits[ 1 ] & 0x40 ) != 0 )
    os << "true  (1)," << CTsvcLIB::eline;
  else
    os << "false (0)," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "queued            : ";
  if ( ( bits[ 1 ] & 0x20 ) != 0 )
    os << "true  (1)," << CTsvcLIB::eline;
  else
    os << "false (0)," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "retrieved         : ";
  if ( ( bits[ 1 ] & 0x10 ) != 0 )
    os << "true  (1)," << CTsvcLIB::eline;
  else
    os << "false (0)," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "serviceInitiated  : ";
  if ( ( bits[ 1 ] & 0x08 ) != 0 )
    os << "true  (1)," << CTsvcLIB::eline;
  else
    os << "false (0)," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "transferred       : ";
  if ( ( bits[ 1 ] & 0x04 ) != 0 )
    os << "true  (1)" << CTsvcLIB::eline;
  else
    os << "false (0)" << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
}

void FeatureFilter::Print ( CTsvcLIB::LOG& os ) const
{
  AsnBits::Print( os );

  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "callInformation : ";
  if ( ( bits[ 0 ] & 0x80 ) != 0 )
    os << "true  (1)," << CTsvcLIB::eline;
  else
    os << "false (0)," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "doNotDisturb    : ";
  if ( ( bits[ 0 ] & 0x40 ) != 0 )
    os << "true  (1)," << CTsvcLIB::eline;
  else
    os << "false (0)," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "forwarding      : ";
  if ( ( bits[ 0 ] & 0x20 ) != 0 )
    os << "true  (1)," << CTsvcLIB::eline;
  else
    os << "false (0)," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "messageWaiting  : ";
  if ( ( bits[ 0 ] & 0x10 ) != 0 )
    os << "true  (1)" << CTsvcLIB::eline;
  else
    os << "false (0)" << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
}

void AgentFilter::Print ( CTsvcLIB::LOG& os ) const
{
  AsnBits::Print( os );

  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "loggedOn     : ";
  if ( ( bits[ 0 ] & 0x80 ) != 0 )
    os << "true  (1)," << CTsvcLIB::eline;
  else
    os << "false (0)," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "loggedOff    : ";
  if ( ( bits[ 0 ] & 0x40 ) != 0 )
    os << "true  (1)," << CTsvcLIB::eline;
  else
    os << "false (0)," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "notReady     : ";
  if ( ( bits[ 0 ] & 0x20 ) != 0 )
    os << "true  (1)," << CTsvcLIB::eline;
  else
    os << "false (0)," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "ready        : ";
  if ( ( bits[ 0 ] & 0x10 ) != 0 )
    os << "true  (1)," << CTsvcLIB::eline;
  else
    os << "false (0)," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "workNotReady : ";
  if ( ( bits[ 0 ] & 0x08 ) != 0 )
    os << "true  (1)," << CTsvcLIB::eline;
  else
    os << "false (0)," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "workReady    : ";
  if ( ( bits[ 0 ] & 0x04 ) != 0 )
    os << "true  (1)" << CTsvcLIB::eline;
  else
    os << "false (0)" << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
}

void MaintenanceFilter::Print ( CTsvcLIB::LOG& os ) const
{
  AsnBits::Print( os );

  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "backInService : ";
  if ( ( bits[ 0 ] & 0x80 ) != 0 )
    os << "true  (1)," << CTsvcLIB::eline;
  else
    os << "false (0)," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "outOfService  : ";
  if ( ( bits[ 0 ] & 0x40 ) != 0 )
    os << "true  (1)" << CTsvcLIB::eline;
  else
    os << "false (0)" << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
}


const char* MonitorType::EnumText( AsnIntType value )
  {
    switch( value )
    {
      case 0: return "call"; break;
      case 1: return "device"; break;
      default: return "?"; break;
    };
  };

void MonitorType::Print ( CTsvcLIB::LOG& os ) const
{
  os << "INTEGER " << EnumText(value) << " (" << value << ")";
}


const char* SimpleCallState::EnumText( AsnIntType value )
  {
    switch( value )
    {
      case 0: return "callNull"; break;
      case 1: return "callPending"; break;
      case 3: return "callOriginated"; break;
      case 35: return "callDelivered"; break;
      case 36: return "callDeliveredHeld"; break;
      case 50: return "callReceived"; break;
      case 51: return "callEstablished"; break;
      case 52: return "callEstablishedHeld"; break;
      case 66: return "callReceivedOnHold"; break;
      case 67: return "callEstablishedOnHold"; break;
      case 83: return "callQueued"; break;
      case 84: return "callQueuedHeld"; break;
      case 99: return "callFailed"; break;
      case 100: return "callFailedHeld"; break;
      default: return "?"; break;
    };
  };

void SimpleCallState::Print ( CTsvcLIB::LOG& os ) const
{
  os << "INTEGER " << EnumText(value) << " (" << value << ")";
}


const char* AgentState::EnumText( AsnIntType value )
  {
    switch( value )
    {
      case 0: return "notReady"; break;
      case 1: return "null"; break;
      case 2: return "ready"; break;
      case 3: return "workNotReady"; break;
      case 4: return "workReady"; break;
      default: return "?"; break;
    };
  };

void AgentState::Print ( CTsvcLIB::LOG& os ) const
{
  os << "INTEGER " << EnumText(value) << " (" << value << ")";
}


const char* AllocationState::EnumText( AsnIntType value )
  {
    switch( value )
    {
      case 0: return "callDelivered"; break;
      case 1: return "callEstablished"; break;
      default: return "?"; break;
    };
  };

void AllocationState::Print ( CTsvcLIB::LOG& os ) const
{
  os << "INTEGER " << EnumText(value) << " (" << value << ")";
}

void DeviceClass::Print ( CTsvcLIB::LOG& os ) const
{
  AsnBits::Print( os );

  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "voice : ";
  if ( ( bits[ 0 ] & 0x80 ) != 0 )
    os << "true  (1)," << CTsvcLIB::eline;
  else
    os << "false (0)," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "data  : ";
  if ( ( bits[ 0 ] & 0x40 ) != 0 )
    os << "true  (1)," << CTsvcLIB::eline;
  else
    os << "false (0)," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "image : ";
  if ( ( bits[ 0 ] & 0x20 ) != 0 )
    os << "true  (1)," << CTsvcLIB::eline;
  else
    os << "false (0)," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "other : ";
  if ( ( bits[ 0 ] & 0x10 ) != 0 )
    os << "true  (1)" << CTsvcLIB::eline;
  else
    os << "false (0)" << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
}


const char* DeviceType::EnumText( AsnIntType value )
  {
    switch( value )
    {
      case 0: return "station"; break;
      case 1: return "line"; break;
      case 2: return "button"; break;
      case 3: return "aCD"; break;
      case 4: return "trunk"; break;
      case 5: return "operator1"; break;
      case 16: return "station_group"; break;
      case 17: return "line_group"; break;
      case 18: return "button_group"; break;
      case 19: return "aCD_group"; break;
      case 20: return "trunk_group"; break;
      case 21: return "operator_group"; break;
      case 255: return "other"; break;
      default: return "?"; break;
    };
  };

void DeviceType::Print ( CTsvcLIB::LOG& os ) const
{
  os << "INTEGER " << EnumText(value) << " (" << value << ")";
}


const char* ForwardingType::EnumText( AsnIntType value )
  {
    switch( value )
    {
      case 0: return "forwardImmediateOn"; break;
      case 1: return "forwardImmediateOff"; break;
      case 2: return "forwardBusyOn"; break;
      case 3: return "forwardBusyOff"; break;
      case 4: return "forwardNoAnsOn"; break;
      case 5: return "forwardNoAnsOff"; break;
      case 6: return "forwardBusyIntOn"; break;
      case 7: return "forwardBusyIntOff"; break;
      case 8: return "forwardBusyExtOn"; break;
      case 9: return "forwardBusyExtOff"; break;
      case 10: return "forwardNoAnsIntOn"; break;
      case 11: return "forwardNoAnsIntOff"; break;
      case 12: return "forwardNoAnsExtOn"; break;
      case 13: return "forwardNoAnsExtOff"; break;
      default: return "?"; break;
    };
  };

void ForwardingType::Print ( CTsvcLIB::LOG& os ) const
{
  os << "INTEGER " << EnumText(value) << " (" << value << ")";
}


const char* QueryDeviceFeature::EnumText( AsnIntType value )
  {
    switch( value )
    {
      case 0: return "msgWaitingOn"; break;
      case 1: return "doNotDisturbOn"; break;
      case 2: return "forward"; break;
      case 3: return "lastDialedNumber"; break;
      case 4: return "deviceInfo"; break;
      case 5: return "agentState"; break;
      case 6: return "routingEnabled"; break;
      case 7: return "autoAnswer"; break;
      case 8: return "microphoneMuteOn"; break;
      case 9: return "speakerMuteOn"; break;
      case 10: return "speakerVolume"; break;
      default: return "?"; break;
    };
  };

void QueryDeviceFeature::Print ( CTsvcLIB::LOG& os ) const
{
  os << "INTEGER " << EnumText(value) << " (" << value << ")";
}


const char* SystemStatus::EnumText( AsnIntType value )
  {
    switch( value )
    {
      case 0: return "initializing"; break;
      case 1: return "enabled"; break;
      case 2: return "normal"; break;
      case 3: return "messagesLost"; break;
      case 4: return "disabled"; break;
      case 5: return "overloadImminent"; break;
      case 6: return "overloadReached"; break;
      case 7: return "overloadRelieved"; break;
      default: return "?"; break;
    };
  };

void SystemStatus::Print ( CTsvcLIB::LOG& os ) const
{
  os << "INTEGER " << EnumText(value) << " (" << value << ")";
}


const char* SelectValue::EnumText( AsnIntType value )
  {
    switch( value )
    {
      case 0: return "normal"; break;
      case 1: return "leastCost"; break;
      case 2: return "emergency"; break;
      case 3: return "aCD"; break;
      case 4: return "userDefined"; break;
      default: return "?"; break;
    };
  };

void SelectValue::Print ( CTsvcLIB::LOG& os ) const
{
  os << "INTEGER " << EnumText(value) << " (" << value << ")";
}

AsnType *RoutingCrossRefID::Clone() const
{
  return new(memBlock) RoutingCrossRefID(memBlock);
}

AsnLen RoutingCrossRefID::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, APPL, PRIM, 24);
    return l;
}

void RoutingCrossRefID::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnTag tag;
    AsnLen elmtLen1;

    if (((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (APPL, PRIM, 24))
        && (tag != MAKE_TAG_ID (APPL, CONS, 24)))
    {
        throw "ERROR C0102: RoutingCrossRefID.BDec(): Wrong tag";
    }
    elmtLen1 = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int RoutingCrossRefID::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int RoutingCrossRefID::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}


const char* OperationIDType::EnumText( AsnIntType value )
  {
    switch( value )
    {
      case 1: return "alternateCall"; break;
      case 2: return "answerCall"; break;
      case 3: return "callCompletion"; break;
      case 4: return "clearCall"; break;
      case 5: return "clearConnection"; break;
      case 6: return "conferenceCall"; break;
      case 7: return "consultationCall"; break;
      case 8: return "divertCall"; break;
      case 9: return "holdCall"; break;
      case 10: return "makeCall"; break;
      case 11: return "makePredictiveCall"; break;
      case 12: return "queryDevice"; break;
      case 13: return "reconnectCall"; break;
      case 14: return "retrieveCall"; break;
      case 15: return "setFeature"; break;
      case 16: return "transferCall"; break;
      case 21: return "cSTAEventReport"; break;
      case 31: return "routeRequest"; break;
      case 32: return "reRouteRequest"; break;
      case 33: return "routeSelectRequest"; break;
      case 34: return "routeUsedRequest"; break;
      case 35: return "routeEndRequest"; break;
      case 51: return "escapeService"; break;
      case 52: return "systemStatus"; break;
      case 71: return "monitorStart"; break;
      case 72: return "changeMonitorFilter"; break;
      case 73: return "monitorStop"; break;
      case 74: return "snapshotDevice"; break;
      case 75: return "snapshotCall"; break;
      default: return "?"; break;
    };
  };

void OperationIDType::Print ( CTsvcLIB::LOG& os ) const
{
  os << "INTEGER " << EnumText(value) << " (" << value << ")";
}


const char* ErrorIDType::EnumText( AsnIntType value )
  {
    switch( value )
    {
      case 1: return "universalFailure"; break;
      default: return "?"; break;
    };
  };

void ErrorIDType::Print ( CTsvcLIB::LOG& os ) const
{
  os << "INTEGER " << EnumText(value) << " (" << value << ")";
}


const char* EventIDType::EnumText( AsnIntType value )
  {
    switch( value )
    {
      case 1: return "callCleared"; break;
      case 2: return "conferenced"; break;
      case 3: return "connectionCleared"; break;
      case 4: return "delivered"; break;
      case 5: return "diverted"; break;
      case 6: return "established"; break;
      case 7: return "failed"; break;
      case 8: return "held"; break;
      case 9: return "networkReached"; break;
      case 10: return "originated"; break;
      case 11: return "queued"; break;
      case 12: return "retrieved"; break;
      case 13: return "serviceInitiated"; break;
      case 14: return "transferred"; break;
      case 101: return "callInformation"; break;
      case 102: return "doNotDisturb"; break;
      case 103: return "forwarding"; break;
      case 104: return "messageWaiting"; break;
      case 201: return "loggedOn"; break;
      case 202: return "loggedOff"; break;
      case 203: return "notReady"; break;
      case 204: return "ready"; break;
      case 205: return "workNotReady"; break;
      case 206: return "workReady"; break;
      case 301: return "backInService"; break;
      case 302: return "outOfService"; break;
      case 401: return "privateEvt"; break;
      default: return "?"; break;
    };
  };

void EventIDType::Print ( CTsvcLIB::LOG& os ) const
{
  os << "INTEGER " << EnumText(value) << " (" << value << ")";
}

PublicTON::PublicTON( MemBlock* mb ) : AsnType( mb )
{
  choiceId = unknownCid;
  unknown = NULL; // incomplete initialization of mandatory element!
}

PublicTON::PublicTON( MemBlock* mb, const PublicTON & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined PublicTON::PublicTON (const PublicTON &)";
  abort();
}

PublicTON::~PublicTON()
{
} // end of destructor

AsnType *PublicTON::Clone() const
{
  return new(memBlock) PublicTON(memBlock);
}

PublicTON &PublicTON::operator = (const PublicTON &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case unknownCid:
        unknown = new(memBlock) IA5String(memBlock);
        *unknown = *that.unknown;
        break;
      case internationalCid:
        international = new(memBlock) IA5String(memBlock);
        *international = *that.international;
        break;
      case nationalCid:
        national = new(memBlock) IA5String(memBlock);
        *national = *that.national;
        break;
      case networkspecificCid:
        networkspecific = new(memBlock) IA5String(memBlock);
        *networkspecific = *that.networkspecific;
        break;
      case subscriberCid:
        subscriber = new(memBlock) IA5String(memBlock);
        *subscriber = *that.subscriber;
        break;
      case abbreviatedCid:
        abbreviated = new(memBlock) IA5String(memBlock);
        *abbreviated = *that.abbreviated;
        break;
    }
  }

  return *this;
}

AsnLen
PublicTON::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case unknownCid:
      l = unknown->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 0);
      break;

    case internationalCid:
      l = international->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 1);
      break;

    case nationalCid:
      l = national->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 2);
      break;

    case networkspecificCid:
      l = networkspecific->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 3);
      break;

    case subscriberCid:
      l = subscriber->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 4);
      break;

    case abbreviatedCid:
      l = abbreviated->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 5);
      break;

  } // end switch
  return l;
} // PublicTON::BEncContent


void PublicTON::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (CNTX, PRIM, 0):
    case MAKE_TAG_ID (CNTX, CONS, 0):
      choiceId = unknownCid;
      unknown = new(memBlock) IA5String(memBlock);
        unknown->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 1):
    case MAKE_TAG_ID (CNTX, CONS, 1):
      choiceId = internationalCid;
      international = new(memBlock) IA5String(memBlock);
        international->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 2):
    case MAKE_TAG_ID (CNTX, CONS, 2):
      choiceId = nationalCid;
      national = new(memBlock) IA5String(memBlock);
        national->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 3):
    case MAKE_TAG_ID (CNTX, CONS, 3):
      choiceId = networkspecificCid;
      networkspecific = new(memBlock) IA5String(memBlock);
        networkspecific->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 4):
    case MAKE_TAG_ID (CNTX, CONS, 4):
      choiceId = subscriberCid;
      subscriber = new(memBlock) IA5String(memBlock);
        subscriber->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 5):
    case MAKE_TAG_ID (CNTX, CONS, 5):
      choiceId = abbreviatedCid;
      abbreviated = new(memBlock) IA5String(memBlock);
        abbreviated->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0103: Unexpected tag in CHOICE";
      break;
  } // end switch
} // PublicTON::BDecContent


AsnLen PublicTON::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void PublicTON::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int PublicTON::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int PublicTON::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void PublicTON::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case unknownCid: os << "IA5String*"; break;
    case internationalCid: os << "IA5String*"; break;
    case nationalCid: os << "IA5String*"; break;
    case networkspecificCid: os << "IA5String*"; break;
    case subscriberCid: os << "IA5String*"; break;
    case abbreviatedCid: os << "IA5String*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case unknownCid:
      os << "unknown : ";
      if (unknown)
        os << *unknown;
      else
        os << "VOID";
      break;

    case internationalCid:
      os << "international : ";
      if (international)
        os << *international;
      else
        os << "VOID";
      break;

    case nationalCid:
      os << "national : ";
      if (national)
        os << *national;
      else
        os << "VOID";
      break;

    case networkspecificCid:
      os << "networkspecific : ";
      if (networkspecific)
        os << *networkspecific;
      else
        os << "VOID";
      break;

    case subscriberCid:
      os << "subscriber : ";
      if (subscriber)
        os << *subscriber;
      else
        os << "VOID";
      break;

    case abbreviatedCid:
      os << "abbreviated : ";
      if (abbreviated)
        os << *abbreviated;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // PublicTON::Print

PrivateTON::PrivateTON( MemBlock* mb ) : AsnType( mb )
{
  choiceId = unknownCid;
  unknown = NULL; // incomplete initialization of mandatory element!
}

PrivateTON::PrivateTON( MemBlock* mb, const PrivateTON & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined PrivateTON::PrivateTON (const PrivateTON &)";
  abort();
}

PrivateTON::~PrivateTON()
{
} // end of destructor

AsnType *PrivateTON::Clone() const
{
  return new(memBlock) PrivateTON(memBlock);
}

PrivateTON &PrivateTON::operator = (const PrivateTON &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case unknownCid:
        unknown = new(memBlock) IA5String(memBlock);
        *unknown = *that.unknown;
        break;
      case level3RegionalNumberCid:
        level3RegionalNumber = new(memBlock) IA5String(memBlock);
        *level3RegionalNumber = *that.level3RegionalNumber;
        break;
      case level2RegionalNumberCid:
        level2RegionalNumber = new(memBlock) IA5String(memBlock);
        *level2RegionalNumber = *that.level2RegionalNumber;
        break;
      case level1RegionalNumberCid:
        level1RegionalNumber = new(memBlock) IA5String(memBlock);
        *level1RegionalNumber = *that.level1RegionalNumber;
        break;
      case pTNSpecificNumberCid:
        pTNSpecificNumber = new(memBlock) IA5String(memBlock);
        *pTNSpecificNumber = *that.pTNSpecificNumber;
        break;
      case localNumberCid:
        localNumber = new(memBlock) IA5String(memBlock);
        *localNumber = *that.localNumber;
        break;
      case abbreviatedCid:
        abbreviated = new(memBlock) IA5String(memBlock);
        *abbreviated = *that.abbreviated;
        break;
    }
  }

  return *this;
}

AsnLen
PrivateTON::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case unknownCid:
      l = unknown->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 0);
      break;

    case level3RegionalNumberCid:
      l = level3RegionalNumber->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 1);
      break;

    case level2RegionalNumberCid:
      l = level2RegionalNumber->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 2);
      break;

    case level1RegionalNumberCid:
      l = level1RegionalNumber->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 3);
      break;

    case pTNSpecificNumberCid:
      l = pTNSpecificNumber->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 4);
      break;

    case localNumberCid:
      l = localNumber->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 5);
      break;

    case abbreviatedCid:
      l = abbreviated->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 6);
      break;

  } // end switch
  return l;
} // PrivateTON::BEncContent


void PrivateTON::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (CNTX, PRIM, 0):
    case MAKE_TAG_ID (CNTX, CONS, 0):
      choiceId = unknownCid;
      unknown = new(memBlock) IA5String(memBlock);
        unknown->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 1):
    case MAKE_TAG_ID (CNTX, CONS, 1):
      choiceId = level3RegionalNumberCid;
      level3RegionalNumber = new(memBlock) IA5String(memBlock);
        level3RegionalNumber->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 2):
    case MAKE_TAG_ID (CNTX, CONS, 2):
      choiceId = level2RegionalNumberCid;
      level2RegionalNumber = new(memBlock) IA5String(memBlock);
        level2RegionalNumber->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 3):
    case MAKE_TAG_ID (CNTX, CONS, 3):
      choiceId = level1RegionalNumberCid;
      level1RegionalNumber = new(memBlock) IA5String(memBlock);
        level1RegionalNumber->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 4):
    case MAKE_TAG_ID (CNTX, CONS, 4):
      choiceId = pTNSpecificNumberCid;
      pTNSpecificNumber = new(memBlock) IA5String(memBlock);
        pTNSpecificNumber->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 5):
    case MAKE_TAG_ID (CNTX, CONS, 5):
      choiceId = localNumberCid;
      localNumber = new(memBlock) IA5String(memBlock);
        localNumber->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 6):
    case MAKE_TAG_ID (CNTX, CONS, 6):
      choiceId = abbreviatedCid;
      abbreviated = new(memBlock) IA5String(memBlock);
        abbreviated->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0104: Unexpected tag in CHOICE";
      break;
  } // end switch
} // PrivateTON::BDecContent


AsnLen PrivateTON::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void PrivateTON::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int PrivateTON::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int PrivateTON::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void PrivateTON::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case unknownCid: os << "IA5String*"; break;
    case level3RegionalNumberCid: os << "IA5String*"; break;
    case level2RegionalNumberCid: os << "IA5String*"; break;
    case level1RegionalNumberCid: os << "IA5String*"; break;
    case pTNSpecificNumberCid: os << "IA5String*"; break;
    case localNumberCid: os << "IA5String*"; break;
    case abbreviatedCid: os << "IA5String*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case unknownCid:
      os << "unknown : ";
      if (unknown)
        os << *unknown;
      else
        os << "VOID";
      break;

    case level3RegionalNumberCid:
      os << "level3RegionalNumber : ";
      if (level3RegionalNumber)
        os << *level3RegionalNumber;
      else
        os << "VOID";
      break;

    case level2RegionalNumberCid:
      os << "level2RegionalNumber : ";
      if (level2RegionalNumber)
        os << *level2RegionalNumber;
      else
        os << "VOID";
      break;

    case level1RegionalNumberCid:
      os << "level1RegionalNumber : ";
      if (level1RegionalNumber)
        os << *level1RegionalNumber;
      else
        os << "VOID";
      break;

    case pTNSpecificNumberCid:
      os << "pTNSpecificNumber : ";
      if (pTNSpecificNumber)
        os << *pTNSpecificNumber;
      else
        os << "VOID";
      break;

    case localNumberCid:
      os << "localNumber : ";
      if (localNumber)
        os << *localNumber;
      else
        os << "VOID";
      break;

    case abbreviatedCid:
      os << "abbreviated : ";
      if (abbreviated)
        os << *abbreviated;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // PrivateTON::Print

RetryValue::RetryValue( MemBlock* mb ) : AsnType( mb )
{
  choiceId = noListAvailableCid;
  noListAvailable = NULL; // incomplete initialization of mandatory element!
}

RetryValue::RetryValue( MemBlock* mb, const RetryValue & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined RetryValue::RetryValue (const RetryValue &)";
  abort();
}

RetryValue::~RetryValue()
{
} // end of destructor

AsnType *RetryValue::Clone() const
{
  return new(memBlock) RetryValue(memBlock);
}

RetryValue &RetryValue::operator = (const RetryValue &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case noListAvailableCid:
        noListAvailable = new(memBlock) AsnBool(memBlock);
        *noListAvailable = *that.noListAvailable;
        break;
      case noCountAvailableCid:
        noCountAvailable = new(memBlock) AsnBool(memBlock);
        *noCountAvailable = *that.noCountAvailable;
        break;
      case retryCountCid:
        retryCount = new(memBlock) AsnInt(memBlock);
        *retryCount = *that.retryCount;
        break;
    }
  }

  return *this;
}

AsnLen
RetryValue::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case noListAvailableCid:
      l = noListAvailable->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 0);
      break;

    case noCountAvailableCid:
      l = noCountAvailable->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 1);
      break;

    case retryCountCid:
      l = retryCount->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 2);
      break;

  } // end switch
  return l;
} // RetryValue::BEncContent


void RetryValue::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (CNTX, PRIM, 0):
      choiceId = noListAvailableCid;
      noListAvailable = new(memBlock) AsnBool(memBlock);
        noListAvailable->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 1):
      choiceId = noCountAvailableCid;
      noCountAvailable = new(memBlock) AsnBool(memBlock);
        noCountAvailable->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 2):
      choiceId = retryCountCid;
      retryCount = new(memBlock) AsnInt(memBlock);
        retryCount->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0105: Unexpected tag in CHOICE";
      break;
  } // end switch
} // RetryValue::BDecContent


AsnLen RetryValue::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void RetryValue::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int RetryValue::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int RetryValue::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void RetryValue::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case noListAvailableCid: os << "AsnBool*"; break;
    case noCountAvailableCid: os << "AsnBool*"; break;
    case retryCountCid: os << "AsnInt*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case noListAvailableCid:
      os << "noListAvailable : ";
      if (noListAvailable)
        os << *noListAvailable;
      else
        os << "VOID";
      break;

    case noCountAvailableCid:
      os << "noCountAvailable : ";
      if (noCountAvailable)
        os << *noCountAvailable;
      else
        os << "VOID";
      break;

    case retryCountCid:
      os << "retryCount : ";
      if (retryCount)
        os << *retryCount;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // RetryValue::Print

Seal::Seal( MemBlock* mb ) : AsnType( mb )
    , algorithmIdentifier( mb )
    , keyIdentifier( mb )
    , seal( mb )
{
}

Seal::Seal( MemBlock* mb, const Seal & ) : AsnType( mb )
    , algorithmIdentifier( mb )
    , keyIdentifier( mb )
    , seal( mb )
{
  throw "ERROR C0099: Use of incompletely defined Seal::Seal (const Seal &)";
  abort();
}

Seal::~Seal()
{
}

AsnType *Seal::Clone() const
{
  return new(memBlock) Seal(memBlock);
}

Seal &Seal::operator = (const Seal &that)
{
  if (this != &that)
  {
    algorithmIdentifier = that.algorithmIdentifier;
    keyIdentifier = that.keyIdentifier;
    seal = that.seal;
  }

  return *this;
}

AsnLen
Seal::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

    l = seal.BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, UNIV, PRIM, OCTETSTRING_TAG_CODE);
    totalLen += l;

    l = keyIdentifier.BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, UNIV, PRIM, OCTETSTRING_TAG_CODE);
    totalLen += l;

    l = algorithmIdentifier.BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, UNIV, PRIM, OID_TAG_CODE);
    totalLen += l;

  return totalLen;
} // Seal::BEncContent


void Seal::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, OID_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    algorithmIdentifier.BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0106: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, OCTETSTRING_TAG_CODE))
    || (tag1 == MAKE_TAG_ID (UNIV, CONS, OCTETSTRING_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    keyIdentifier.BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0107: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, OCTETSTRING_TAG_CODE))
    || (tag1 == MAKE_TAG_ID (UNIV, CONS, OCTETSTRING_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    seal.BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0108: SEQUENCE is missing non-optional elmt.";
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0109: Length discrepancy on sequence.";
  }
  else
    return;
} // Seal::BDecContent

AsnLen Seal::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void Seal::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135077504: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int Seal::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int Seal::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void Seal::Print ( CTsvcLIB::LOG& os ) const
{
  os << "Seal SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "algorithmIdentifier : ";
  os << algorithmIdentifier;
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "keyIdentifier : ";
  os << keyIdentifier;
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "seal : ";
  os << seal;
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // Seal::Print


CSTAPrivateData::CSTAPrivateData( MemBlock* mb ) : AsnType( mb )
    , manufacturer( mb )
    , data( mb )
{
}

CSTAPrivateData::CSTAPrivateData( MemBlock* mb, const CSTAPrivateData & ) : AsnType( mb )
    , manufacturer( mb )
    , data( mb )
{
  throw "ERROR C0099: Use of incompletely defined CSTAPrivateData::CSTAPrivateData (const CSTAPrivateData &)";
  abort();
}

CSTAPrivateData::~CSTAPrivateData()
{
}

AsnType *CSTAPrivateData::Clone() const
{
  return new(memBlock) CSTAPrivateData(memBlock);
}

CSTAPrivateData &CSTAPrivateData::operator = (const CSTAPrivateData &that)
{
  if (this != &that)
  {
    manufacturer = that.manufacturer;
    data = that.data;
  }

  return *this;
}

AsnLen
CSTAPrivateData::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

    data.SetTypeBy( manufacturer );
    l = data.BEnc (b);
    totalLen += l;

    l = manufacturer.BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, UNIV, PRIM, OID_TAG_CODE);
    totalLen += l;

  return totalLen;
} // CSTAPrivateData::BEncContent


void CSTAPrivateData::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, OID_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    manufacturer.BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0110: SEQUENCE is missing non-optional elmt.";
  }

  // ANY type
    data.SetTypeBy( manufacturer );
    data.BDec (b, seqBytesDecoded);


  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0111: Length discrepancy on sequence.";
  }
  else
    return;
} // CSTAPrivateData::BDecContent

AsnLen CSTAPrivateData::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, APPL, CONS, 29);
  return l;
}

void CSTAPrivateData::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (APPL, CONS, 29))
  {
    throw "ERROR C135077664: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int CSTAPrivateData::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int CSTAPrivateData::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void CSTAPrivateData::Print ( CTsvcLIB::LOG& os ) const
{
  os << "CSTAPrivateData SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "manufacturer : ";
  os << manufacturer;
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "data : ";
  os << data;
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // CSTAPrivateData::Print


AsnType *CSTACommonArgumentsSeqOf::Clone() const
{
  return new(memBlock) CSTACommonArgumentsSeqOf(memBlock);
}

AsnLen CSTACommonArgumentsSeqOf::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void CSTACommonArgumentsSeqOf::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C0112: CSTACommonArgumentsSeqOf.BDec(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

CSTACommonArgumentsSeqOf::CSTACommonArgumentsSeqOf( MemBlock* mb, const CSTACommonArgumentsSeqOf & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined CSTACommonArgumentsSeqOf::CSTACommonArgumentsSeqOf (const CSTACommonArgumentsSeqOf &)";
  abort();
}

CSTACommonArgumentsSeqOf::~CSTACommonArgumentsSeqOf()
{
  SetCurrToFirst();
  for (; Curr() != NULL; RemoveCurrFromList())
    ;
} // end of destructor

CSTACommonArgumentsSeqOf &CSTACommonArgumentsSeqOf::operator = (const CSTACommonArgumentsSeqOf &that)
{
  if (this != &that)
  {
    SetCurrToFirst();
    for (; Curr(); RemoveCurrFromList())
      ;

    //that.SetCurrToFirst();
    //for (; that.Curr(); that.GoNext())
    //  AppendCopy (*that.Curr());
    for (const AsnListElmt *run=that.first; run; run=run->next)
      AppendCopy (*run->elmt);
  }

  return *this;
}

void CSTACommonArgumentsSeqOf::Print ( CTsvcLIB::LOG& os ) const
{
    os << "CSTACommonArgumentsSeqOf SEQUENCE/SET OF" << CTsvcLIB::eline;
    Indent (os, indentG);
    os << "{" << CTsvcLIB::eline;
    indentG += stdIndentG;
    for (const AsnListElmt *run=first; run; run=run->next)
    {
        Indent (os, indentG);
        os << *run->elmt;
        if (run != last)
            os << ",";
        os << CTsvcLIB::eline;
    }
    indentG -= stdIndentG;
    Indent (os, indentG);
    os << "}";
} // Print


void  CSTACommonArgumentsSeqOf::SetCurrElmt (unsigned long int index)
{
  unsigned long int i;
  curr = first;
  if (count)
    for (i = 0; (i < (count-1)) && (i < index); i++)
      curr = curr->next;
} // CSTACommonArgumentsSeqOf::SetCurrElmt


unsigned long int  CSTACommonArgumentsSeqOf::GetCurrElmtIndex()
{
    unsigned long int i;
    AsnListElmt *tmp;
    if (curr != NULL)
    {
        for (i = 0, tmp = first; tmp != NULL; i++)
        {
            if (tmp == curr)
                return i;
            else
                tmp = tmp->next;
        }
    }
    return count;
} // CSTACommonArgumentsSeqOf::GetCurrElmtIndex


// alloc new list elmt, put at end of list
//  and return the component type
CSTAPrivateData *CSTACommonArgumentsSeqOf::Append()
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt  = new(memBlock) CSTAPrivateData(memBlock);
    newElmt->next = NULL;
    if (last == NULL)
    {
        newElmt->prev = NULL;
        first = last  = newElmt;
    }
    else
    {
        newElmt->prev = last;
        last->next    = newElmt;
        last          = newElmt;
    }
    count++;
    return (curr = newElmt)->elmt;
} // CSTACommonArgumentsSeqOf::Append


// alloc new list elmt, put at begining of list
//  and return the component type
CSTAPrivateData  *CSTACommonArgumentsSeqOf::Prepend()
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) CSTAPrivateData(memBlock);
    newElmt->prev = NULL;
    if (first == NULL)
    {
        newElmt->next = NULL;
        first = last  = newElmt;
    }
    else
    {
        newElmt->next = first;
        first->prev   = newElmt;
        first         = newElmt;
    }
    count++;
    return (curr = newElmt)->elmt;
} // CSTACommonArgumentsSeqOf::Prepend


// alloc new list elmt, insert it before the
// current element and return the component type
// if the current element is null, the new element
// is placed at the beginning of the list.
CSTAPrivateData  *CSTACommonArgumentsSeqOf::InsertBefore()
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) CSTAPrivateData(memBlock);
    if (curr == NULL)
    {
        newElmt->next = first;
        newElmt->prev = NULL;
        first = newElmt;
        if (last == NULL)
            last = newElmt;
    }
    else
    {
        newElmt->next = curr;
        newElmt->prev = curr->prev;
        curr->prev = newElmt;
        if (curr == first)
            first = newElmt;
        else
            newElmt->prev->next = newElmt;
    }
    count++;
    return (curr = newElmt)->elmt;
} // CSTACommonArgumentsSeqOf::InsertBefore


// alloc new list elmt, insert it after the
// current element and return the component type
// if the current element is null, the new element
// is placed at the end of the list.
CSTAPrivateData *CSTACommonArgumentsSeqOf::InsertAfter()
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) CSTAPrivateData(memBlock);
    if (curr == NULL)
    {
        newElmt->prev = last;
        newElmt->next = NULL;
        last = newElmt;
        if (first == NULL)
            first = newElmt;
    }
    else
    {
        newElmt->prev = curr;
        newElmt->next = curr->next;
        curr->next = newElmt;
        if (curr == last)
            last = newElmt;
        else
            newElmt->next->prev = newElmt;
    }
    count++;
    return (curr = newElmt)->elmt;
} // CSTACommonArgumentsSeqOf::InsertAfter


CSTACommonArgumentsSeqOf  &CSTACommonArgumentsSeqOf::AppendCopy (CSTAPrivateData &elmt)
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) CSTAPrivateData(memBlock);
    *newElmt->elmt = elmt;
    newElmt->next = NULL;
    if (last == NULL)
    {
        newElmt->prev = NULL;
        first = last  = newElmt;
    }
    else
    {
        newElmt->prev = last;
        last->next    = newElmt;
        last          = newElmt;
    }
    count++;
    return *this;
} // AppendCopy


CSTACommonArgumentsSeqOf  &CSTACommonArgumentsSeqOf::PrependCopy (CSTAPrivateData &elmt)
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) CSTAPrivateData(memBlock);
    *newElmt->elmt = elmt;
    newElmt->prev = NULL;
    if (first == NULL)
    {
        newElmt->next = NULL;
        first = last  = newElmt;
    }
    else
    {
        newElmt->next = first;
        first->prev   = newElmt;
        first         = newElmt;
    }
    count++;
    return *this;
} // CSTACommonArgumentsSeqOf::PrependCopy


// alloc new list elmt, insert it before the
// current element, copy the given elmt into the new elmt
// and return the component type.
// if the current element is null, the new element
// is placed at the beginning of the list.
CSTACommonArgumentsSeqOf &CSTACommonArgumentsSeqOf::InsertBeforeAndCopy (CSTAPrivateData &elmt)
{
    AsnListElmt *newElmt;

    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) CSTAPrivateData(memBlock);
    *newElmt->elmt = elmt;

    if (curr == NULL)
    {
        newElmt->next = first;
        newElmt->prev = NULL;
        first = newElmt;
        if (last == NULL)
            last = newElmt;
    }
    else
    {
        newElmt->next = curr;
        newElmt->prev = curr->prev;
        curr->prev = newElmt;
        if (curr == first)
            first = newElmt;
        else
            newElmt->prev->next = newElmt;
    }
    count++;
    return *this;
} // CSTACommonArgumentsSeqOf::InsertBeforeAndCopy


// alloc new list elmt, insert it after the
// current element, copy given elmt in to new elmt
//  and return the component type
// if the current element is null, the new element
// is placed at the end of the list.
CSTACommonArgumentsSeqOf  &CSTACommonArgumentsSeqOf::InsertAfterAndCopy (CSTAPrivateData &elmt)
{
    AsnListElmt *newElmt;

    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) CSTAPrivateData(memBlock);
    *newElmt->elmt = elmt;
    if (curr == NULL)
    {
        newElmt->prev = last;
        newElmt->next = NULL;
        last = newElmt;
        if (first == NULL)
            first = newElmt;
    }
    else
    {
        newElmt->prev = curr;
        newElmt->next = curr->next;
        curr->next = newElmt;
        if (curr == last)
            last = newElmt;
        else
            newElmt->next->prev = newElmt;
    }
    count++;
    return *this;
} // CSTACommonArgumentsSeqOf::InsertAfterAndCopy


// remove current element from list if current element is not NULL 
// The new current element will be the next element.
// If the current element is the last element in the list
// the second but last element will become the new current element.
void CSTACommonArgumentsSeqOf::RemoveCurrFromList()
{
    AsnListElmt *del_elmt;

    if (curr != NULL)
    {
        del_elmt = curr;
        count--;

        if (count == 0)
            first = last = curr = NULL;
        else if (curr == first)
        {
            curr = first= first->next;
            first->prev = NULL;
        }
        else if (curr == last)
        {
            curr = last = last->prev;
            last->next = NULL;
        }
        else
        {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
        }

    }
}


AsnLen CSTACommonArgumentsSeqOf::BEncContent (AsnBuf& b)
{
    AsnListElmt *currElmt;
    AsnLen elmtLen;
    AsnLen totalLen = 0;
    for (currElmt = last; currElmt != NULL; currElmt = currElmt->prev)
    {
      BEncEocIfNec (b);
        elmtLen = currElmt->elmt->BEncContent (b);
    elmtLen += BEncConsLen (b, elmtLen);

    elmtLen += BEncTag1 (b, APPL, CONS, 29);
        totalLen += elmtLen;
    }
    return totalLen;
} // CSTACommonArgumentsSeqOf::BEncContent


void  CSTACommonArgumentsSeqOf::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0,
                                  AsnLen &bytesDecoded)
{
    CSTAPrivateData *listElmt;
    AsnTag tag1;
    AsnLen listBytesDecoded = 0;
    AsnLen elmtLen1;

    while ((listBytesDecoded < elmtLen0) || (elmtLen0 == INDEFINITE_LEN))
    {
        tag1 = BDecTag (b, listBytesDecoded);
        if ((tag1 == EOC_TAG_ID) && (elmtLen0 == INDEFINITE_LEN))
        {
            BDEC_2ND_EOC_OCTET (b, listBytesDecoded);
            break;
        }
        if ((tag1 != MAKE_TAG_ID (APPL, CONS, 29) ))
        {
            throw "ERROR C0113: Unexpected Tag";
        }

        elmtLen1 = BDecLen (b, listBytesDecoded);
        listElmt = Append();
        listElmt->BDecContent (b, tag1, elmtLen1, listBytesDecoded);
    }

    bytesDecoded += listBytesDecoded;
} // CSTACommonArgumentsSeqOf::BDecContent


ListForwardParametersSeq::ListForwardParametersSeq( MemBlock* mb ) : AsnType( mb )
    , forwardingType( mb )
    , forwardDN( mb )
{
}

ListForwardParametersSeq::ListForwardParametersSeq( MemBlock* mb, const ListForwardParametersSeq & ) : AsnType( mb )
    , forwardingType( mb )
    , forwardDN( mb )
{
  throw "ERROR C0099: Use of incompletely defined ListForwardParametersSeq::ListForwardParametersSeq (const ListForwardParametersSeq &)";
  abort();
}

ListForwardParametersSeq::~ListForwardParametersSeq()
{
}

AsnType *ListForwardParametersSeq::Clone() const
{
  return new(memBlock) ListForwardParametersSeq(memBlock);
}

ListForwardParametersSeq &ListForwardParametersSeq::operator = (const ListForwardParametersSeq &that)
{
  if (this != &that)
  {
    forwardingType = that.forwardingType;
    forwardDN = that.forwardDN;
  }

  return *this;
}

AsnLen
ListForwardParametersSeq::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

    l = forwardDN.BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, UNIV, PRIM, IA5STRING_TAG_CODE);
    totalLen += l;

    l = forwardingType.BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, ENUM_TAG_CODE);
    totalLen += l;

  return totalLen;
} // ListForwardParametersSeq::BEncContent


void ListForwardParametersSeq::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, ENUM_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    forwardingType.BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0114: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, IA5STRING_TAG_CODE))
    || (tag1 == MAKE_TAG_ID (UNIV, CONS, IA5STRING_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    forwardDN.BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0115: SEQUENCE is missing non-optional elmt.";
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0116: Length discrepancy on sequence.";
  }
  else
    return;
} // ListForwardParametersSeq::BDecContent

AsnLen ListForwardParametersSeq::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void ListForwardParametersSeq::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135061672: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int ListForwardParametersSeq::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ListForwardParametersSeq::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ListForwardParametersSeq::Print ( CTsvcLIB::LOG& os ) const
{
  os << "ListForwardParametersSeq SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "forwardingType : ";
  os << forwardingType;
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "forwardDN : ";
  os << forwardDN;
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // ListForwardParametersSeq::Print


RORJapduChoice1::RORJapduChoice1( MemBlock* mb ) : AsnType( mb )
{
  choiceId = generalProblemCid;
  generalProblem = NULL; // incomplete initialization of mandatory element!
}

RORJapduChoice1::RORJapduChoice1( MemBlock* mb, const RORJapduChoice1 & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined RORJapduChoice1::RORJapduChoice1 (const RORJapduChoice1 &)";
  abort();
}

RORJapduChoice1::~RORJapduChoice1()
{
} // end of destructor

AsnType *RORJapduChoice1::Clone() const
{
  return new(memBlock) RORJapduChoice1(memBlock);
}

RORJapduChoice1 &RORJapduChoice1::operator = (const RORJapduChoice1 &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case generalProblemCid:
        generalProblem = new(memBlock) GeneralProblem(memBlock);
        *generalProblem = *that.generalProblem;
        break;
      case invokeProblemCid:
        invokeProblem = new(memBlock) InvokeProblem(memBlock);
        *invokeProblem = *that.invokeProblem;
        break;
      case returnResultProblemCid:
        returnResultProblem = new(memBlock) ReturnResultProblem(memBlock);
        *returnResultProblem = *that.returnResultProblem;
        break;
      case returnErrorProblemCid:
        returnErrorProblem = new(memBlock) ReturnErrorProblem(memBlock);
        *returnErrorProblem = *that.returnErrorProblem;
        break;
    }
  }

  return *this;
}

AsnLen
RORJapduChoice1::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case generalProblemCid:
      l = generalProblem->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 0);
      break;

    case invokeProblemCid:
      l = invokeProblem->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 1);
      break;

    case returnResultProblemCid:
      l = returnResultProblem->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 2);
      break;

    case returnErrorProblemCid:
      l = returnErrorProblem->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 3);
      break;

  } // end switch
  return l;
} // RORJapduChoice1::BEncContent


void RORJapduChoice1::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (CNTX, PRIM, 0):
      choiceId = generalProblemCid;
      generalProblem = new(memBlock) GeneralProblem(memBlock);
        generalProblem->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 1):
      choiceId = invokeProblemCid;
      invokeProblem = new(memBlock) InvokeProblem(memBlock);
        invokeProblem->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 2):
      choiceId = returnResultProblemCid;
      returnResultProblem = new(memBlock) ReturnResultProblem(memBlock);
        returnResultProblem->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 3):
      choiceId = returnErrorProblemCid;
      returnErrorProblem = new(memBlock) ReturnErrorProblem(memBlock);
        returnErrorProblem->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0117: Unexpected tag in CHOICE";
      break;
  } // end switch
} // RORJapduChoice1::BDecContent


AsnLen RORJapduChoice1::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void RORJapduChoice1::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int RORJapduChoice1::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int RORJapduChoice1::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void RORJapduChoice1::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case generalProblemCid: os << "GeneralProblem*"; break;
    case invokeProblemCid: os << "InvokeProblem*"; break;
    case returnResultProblemCid: os << "ReturnResultProblem*"; break;
    case returnErrorProblemCid: os << "ReturnErrorProblem*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case generalProblemCid:
      if (generalProblem)
        os << *generalProblem;
      else
        os << "VOID";
      break;

    case invokeProblemCid:
      if (invokeProblem)
        os << *invokeProblem;
      else
        os << "VOID";
      break;

    case returnResultProblemCid:
      if (returnResultProblem)
        os << *returnResultProblem;
      else
        os << "VOID";
      break;

    case returnErrorProblemCid:
      if (returnErrorProblem)
        os << *returnErrorProblem;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // RORJapduChoice1::Print

RORJapduChoice::RORJapduChoice( MemBlock* mb ) : AsnType( mb )
{
  choiceId = invokeIDTypeCid;
  invokeIDType = NULL; // incomplete initialization of mandatory element!
}

RORJapduChoice::RORJapduChoice( MemBlock* mb, const RORJapduChoice & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined RORJapduChoice::RORJapduChoice (const RORJapduChoice &)";
  abort();
}

RORJapduChoice::~RORJapduChoice()
{
} // end of destructor

AsnType *RORJapduChoice::Clone() const
{
  return new(memBlock) RORJapduChoice(memBlock);
}

RORJapduChoice &RORJapduChoice::operator = (const RORJapduChoice &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case invokeIDTypeCid:
        invokeIDType = new(memBlock) InvokeIDType(memBlock);
        *invokeIDType = *that.invokeIDType;
        break;
      case nullCid:
        null = new(memBlock) AsnNull(memBlock);
        *null = *that.null;
        break;
    }
  }

  return *this;
}

AsnLen
RORJapduChoice::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case invokeIDTypeCid:
      l = invokeIDType->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, INTEGER_TAG_CODE);
      break;

    case nullCid:
      l = null->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, NULLTYPE_TAG_CODE);
      break;

  } // end switch
  return l;
} // RORJapduChoice::BEncContent


void RORJapduChoice::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (UNIV, PRIM, INTEGER_TAG_CODE):
      choiceId = invokeIDTypeCid;
      invokeIDType = new(memBlock) InvokeIDType(memBlock);
        invokeIDType->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, PRIM, NULLTYPE_TAG_CODE):
      choiceId = nullCid;
      null = new(memBlock) AsnNull(memBlock);
        null->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0118: Unexpected tag in CHOICE";
      break;
  } // end switch
} // RORJapduChoice::BDecContent


AsnLen RORJapduChoice::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void RORJapduChoice::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int RORJapduChoice::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int RORJapduChoice::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void RORJapduChoice::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case invokeIDTypeCid: os << "InvokeIDType*"; break;
    case nullCid: os << "AsnNull*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case invokeIDTypeCid:
      if (invokeIDType)
        os << *invokeIDType;
      else
        os << "VOID";
      break;

    case nullCid:
      if (null)
        os << *null;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // RORJapduChoice::Print

RORSapduSeq::RORSapduSeq( MemBlock* mb ) : AsnType( mb )
    , operationValue( mb )
{
  result = NULL;
}

RORSapduSeq::RORSapduSeq( MemBlock* mb, const RORSapduSeq & ) : AsnType( mb )
    , operationValue( mb )
{
  throw "ERROR C0099: Use of incompletely defined RORSapduSeq::RORSapduSeq (const RORSapduSeq &)";
  abort();
}

RORSapduSeq::~RORSapduSeq()
{
}

AsnType *RORSapduSeq::Clone() const
{
  return new(memBlock) RORSapduSeq(memBlock);
}

RORSapduSeq &RORSapduSeq::operator = (const RORSapduSeq &that)
{
  if (this != &that)
  {
    operationValue = that.operationValue;
    if (that.result)
    {
      if (!result)
        result = new(memBlock) OperationResult(memBlock);
      *result = *that.result;
    }
    else
    {
      result = NULL;
    }
  }

  return *this;
}

AsnLen
RORSapduSeq::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (result))
  {
    result->SetTypeBy( operationValue );
    l = result->BEnc (b);
    totalLen += l;
  }

    l = operationValue.BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, INTEGER_TAG_CODE);
    totalLen += l;

  return totalLen;
} // RORSapduSeq::BEncContent


void RORSapduSeq::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, INTEGER_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    operationValue.BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = b.PeekByte();

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDecEoc (b, seqBytesDecoded);

        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0119: SEQUENCE is missing non-optional elmt.";
  }

  // ANY type
    result = new(memBlock) OperationResult(memBlock);
    result->SetTypeBy( operationValue );
    result->BDec (b, seqBytesDecoded);


  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0120: Length discrepancy on sequence.";
  }
  else
    return;
} // RORSapduSeq::BDecContent

AsnLen RORSapduSeq::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void RORSapduSeq::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135064000: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int RORSapduSeq::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int RORSapduSeq::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void RORSapduSeq::Print ( CTsvcLIB::LOG& os ) const
{
  os << "RORSapduSeq SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "operationValue : ";
  os << operationValue;
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "result : ";
  if (NOT_NULL (result))
    os << *result;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // RORSapduSeq::Print


ROIVapdu::ROIVapdu( MemBlock* mb ) : AsnType( mb )
    , invokeID( mb )
    , operationValue( mb )
{
  linkedID = NULL;
  argument = NULL;
}

ROIVapdu::ROIVapdu( MemBlock* mb, const ROIVapdu & ) : AsnType( mb )
    , invokeID( mb )
    , operationValue( mb )
{
  throw "ERROR C0099: Use of incompletely defined ROIVapdu::ROIVapdu (const ROIVapdu &)";
  abort();
}

ROIVapdu::~ROIVapdu()
{
}

AsnType *ROIVapdu::Clone() const
{
  return new(memBlock) ROIVapdu(memBlock);
}

ROIVapdu &ROIVapdu::operator = (const ROIVapdu &that)
{
  if (this != &that)
  {
    invokeID = that.invokeID;
    if (that.linkedID)
    {
      if (!linkedID)
        linkedID = new(memBlock) InvokedIDType(memBlock);
      *linkedID = *that.linkedID;
    }
    else
    {
      linkedID = NULL;
    }
    operationValue = that.operationValue;
    if (that.argument)
    {
      if (!argument)
        argument = new(memBlock) OperationArgument(memBlock);
      *argument = *that.argument;
    }
    else
    {
      argument = NULL;
    }
  }

  return *this;
}

AsnLen
ROIVapdu::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (argument))
  {
    argument->SetTypeBy( operationValue );
    l = argument->BEnc (b);
    totalLen += l;
  }

    l = operationValue.BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, INTEGER_TAG_CODE);
    totalLen += l;

  if (NOT_NULL (linkedID))
  {
    l = linkedID->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 0);
    totalLen += l;
  }

    l = invokeID.BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, INTEGER_TAG_CODE);
    totalLen += l;

  return totalLen;
} // ROIVapdu::BEncContent


void ROIVapdu::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, INTEGER_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    invokeID.BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0121: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 0)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    linkedID = new(memBlock) InvokedIDType(memBlock);
    linkedID->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, INTEGER_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    operationValue.BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = b.PeekByte();

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDecEoc (b, seqBytesDecoded);

        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0122: SEQUENCE is missing non-optional elmt.";
  }

  // ANY type
    argument = new(memBlock) OperationArgument(memBlock);
    argument->SetTypeBy( operationValue );
    argument->BDec (b, seqBytesDecoded);


  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0123: Length discrepancy on sequence.";
  }
  else
    return;
} // ROIVapdu::BDecContent

AsnLen ROIVapdu::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void ROIVapdu::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135064304: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int ROIVapdu::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ROIVapdu::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ROIVapdu::Print ( CTsvcLIB::LOG& os ) const
{
  os << "ROIVapdu SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "invokeID : ";
  os << invokeID;
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "linkedID : ";
  if (NOT_NULL (linkedID))
    os << *linkedID;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "operationValue : ";
  os << operationValue;
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "argument : ";
  if (NOT_NULL (argument))
    os << *argument;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // ROIVapdu::Print


RORSapdu::RORSapdu( MemBlock* mb ) : AsnType( mb )
    , invokeID( mb )
{
  rORSapduSeq = NULL;
}

RORSapdu::RORSapdu( MemBlock* mb, const RORSapdu & ) : AsnType( mb )
    , invokeID( mb )
{
  throw "ERROR C0099: Use of incompletely defined RORSapdu::RORSapdu (const RORSapdu &)";
  abort();
}

RORSapdu::~RORSapdu()
{
}

AsnType *RORSapdu::Clone() const
{
  return new(memBlock) RORSapdu(memBlock);
}

RORSapdu &RORSapdu::operator = (const RORSapdu &that)
{
  if (this != &that)
  {
    invokeID = that.invokeID;
    if (that.rORSapduSeq)
    {
      if (!rORSapduSeq)
        rORSapduSeq = new(memBlock) RORSapduSeq(memBlock);
      *rORSapduSeq = *that.rORSapduSeq;
    }
    else
    {
      rORSapduSeq = NULL;
    }
  }

  return *this;
}

AsnLen
RORSapdu::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (rORSapduSeq))
  {
      BEncEocIfNec (b);
    l = rORSapduSeq->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
    totalLen += l;
  }

    l = invokeID.BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, INTEGER_TAG_CODE);
    totalLen += l;

  return totalLen;
} // RORSapdu::BEncContent


void RORSapdu::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, INTEGER_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    invokeID.BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0124: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    rORSapduSeq = new(memBlock) RORSapduSeq(memBlock);
    rORSapduSeq->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0125: Length discrepancy on sequence.";
  }
  else
    return;
} // RORSapdu::BDecContent

AsnLen RORSapdu::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void RORSapdu::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135064376: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int RORSapdu::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int RORSapdu::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void RORSapdu::Print ( CTsvcLIB::LOG& os ) const
{
  os << "RORSapdu SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "invokeID : ";
  os << invokeID;
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  if (NOT_NULL (rORSapduSeq))
    os << *rORSapduSeq;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // RORSapdu::Print


ROERapdu::ROERapdu( MemBlock* mb ) : AsnType( mb )
    , invokedID( mb )
    , errorValue( mb )
{
  parameter = NULL;
}

ROERapdu::ROERapdu( MemBlock* mb, const ROERapdu & ) : AsnType( mb )
    , invokedID( mb )
    , errorValue( mb )
{
  throw "ERROR C0099: Use of incompletely defined ROERapdu::ROERapdu (const ROERapdu &)";
  abort();
}

ROERapdu::~ROERapdu()
{
}

AsnType *ROERapdu::Clone() const
{
  return new(memBlock) ROERapdu(memBlock);
}

ROERapdu &ROERapdu::operator = (const ROERapdu &that)
{
  if (this != &that)
  {
    invokedID = that.invokedID;
    errorValue = that.errorValue;
    if (that.parameter)
    {
      if (!parameter)
        parameter = new(memBlock) ErrorParameter(memBlock);
      *parameter = *that.parameter;
    }
    else
    {
      parameter = NULL;
    }
  }

  return *this;
}

AsnLen
ROERapdu::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (parameter))
  {
    parameter->SetTypeBy( errorValue );
    l = parameter->BEnc (b);
    totalLen += l;
  }

    l = errorValue.BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, INTEGER_TAG_CODE);
    totalLen += l;

    l = invokedID.BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, INTEGER_TAG_CODE);
    totalLen += l;

  return totalLen;
} // ROERapdu::BEncContent


void ROERapdu::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, INTEGER_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    invokedID.BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0126: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, INTEGER_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    errorValue.BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = b.PeekByte();

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDecEoc (b, seqBytesDecoded);

        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0127: SEQUENCE is missing non-optional elmt.";
  }

  // ANY type
    parameter = new(memBlock) ErrorParameter(memBlock);
    parameter->SetTypeBy( errorValue );
    parameter->BDec (b, seqBytesDecoded);


  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0128: Length discrepancy on sequence.";
  }
  else
    return;
} // ROERapdu::BDecContent

AsnLen ROERapdu::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void ROERapdu::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135064448: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int ROERapdu::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ROERapdu::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ROERapdu::Print ( CTsvcLIB::LOG& os ) const
{
  os << "ROERapdu SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "invokedID : ";
  os << invokedID;
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "errorValue : ";
  os << errorValue;
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "parameter : ";
  if (NOT_NULL (parameter))
    os << *parameter;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // ROERapdu::Print


RORJapdu::RORJapdu( MemBlock* mb ) : AsnType( mb )
{
  invokeID = NULL; // incomplete initialization of mandatory element!
  problem = NULL; // incomplete initialization of mandatory element!
}

RORJapdu::RORJapdu( MemBlock* mb, const RORJapdu & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined RORJapdu::RORJapdu (const RORJapdu &)";
  abort();
}

RORJapdu::~RORJapdu()
{
}

AsnType *RORJapdu::Clone() const
{
  return new(memBlock) RORJapdu(memBlock);
}

RORJapdu &RORJapdu::operator = (const RORJapdu &that)
{
  if (this != &that)
  {
    if (that.invokeID)
    {
      if (!invokeID)
        invokeID = new(memBlock) RORJapduChoice(memBlock);
      *invokeID = *that.invokeID;
    }
    else
    {
      invokeID = NULL;
    }
    if (that.problem)
    {
      if (!problem)
        problem = new(memBlock) RORJapduChoice1(memBlock);
      *problem = *that.problem;
    }
    else
    {
      problem = NULL;
    }
  }

  return *this;
}

AsnLen
RORJapdu::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

    l = problem->BEncContent (b);
    totalLen += l;

    l = invokeID->BEncContent (b);
    totalLen += l;

  return totalLen;
} // RORJapdu::BEncContent


void RORJapdu::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, INTEGER_TAG_CODE))
    || (tag1 == MAKE_TAG_ID (UNIV, PRIM, NULLTYPE_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    invokeID = new(memBlock) RORJapduChoice(memBlock);
    invokeID->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0129: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 1))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 2))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 3)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    problem = new(memBlock) RORJapduChoice1(memBlock);
    problem->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0130: SEQUENCE is missing non-optional elmt.";
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0131: Length discrepancy on sequence.";
  }
  else
    return;
} // RORJapdu::BDecContent

AsnLen RORJapdu::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void RORJapdu::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135064520: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int RORJapdu::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int RORJapdu::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void RORJapdu::Print ( CTsvcLIB::LOG& os ) const
{
  os << "RORJapdu SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "invokeID : ";
  if (NOT_NULL (invokeID))
    os << *invokeID;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "problem : ";
  if (NOT_NULL (problem))
    os << *problem;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // RORJapdu::Print


AlternateCallResult::AlternateCallResult( MemBlock* mb ) : AsnType( mb )
{
  choiceId = extensionsCid;
  extensions = NULL; // incomplete initialization of mandatory element!
}

AlternateCallResult::AlternateCallResult( MemBlock* mb, const AlternateCallResult & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined AlternateCallResult::AlternateCallResult (const AlternateCallResult &)";
  abort();
}

AlternateCallResult::~AlternateCallResult()
{
} // end of destructor

AsnType *AlternateCallResult::Clone() const
{
  return new(memBlock) AlternateCallResult(memBlock);
}

AlternateCallResult &AlternateCallResult::operator = (const AlternateCallResult &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case extensionsCid:
        extensions = new(memBlock) CSTAPrivateData(memBlock);
        *extensions = *that.extensions;
        break;
      case noDataCid:
        noData = new(memBlock) AsnNull(memBlock);
        *noData = *that.noData;
        break;
    }
  }

  return *this;
}

AsnLen
AlternateCallResult::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case extensionsCid:
      BEncEocIfNec (b);
      l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 29);
      break;

    case noDataCid:
      l = noData->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, NULLTYPE_TAG_CODE);
      break;

  } // end switch
  return l;
} // AlternateCallResult::BEncContent


void AlternateCallResult::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (APPL, CONS, 29):
      choiceId = extensionsCid;
      extensions = new(memBlock) CSTAPrivateData(memBlock);
        extensions->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, PRIM, NULLTYPE_TAG_CODE):
      choiceId = noDataCid;
      noData = new(memBlock) AsnNull(memBlock);
        noData->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0132: Unexpected tag in CHOICE";
      break;
  } // end switch
} // AlternateCallResult::BDecContent


AsnLen AlternateCallResult::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void AlternateCallResult::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int AlternateCallResult::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int AlternateCallResult::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void AlternateCallResult::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case extensionsCid: os << "CSTAPrivateData*"; break;
    case noDataCid: os << "AsnNull*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case extensionsCid:
      os << "extensions : ";
      if (extensions)
        os << *extensions;
      else
        os << "VOID";
      break;

    case noDataCid:
      os << "noData : ";
      if (noData)
        os << *noData;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // AlternateCallResult::Print

AnswerCallResult::AnswerCallResult( MemBlock* mb ) : AsnType( mb )
{
  choiceId = extensionsCid;
  extensions = NULL; // incomplete initialization of mandatory element!
}

AnswerCallResult::AnswerCallResult( MemBlock* mb, const AnswerCallResult & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined AnswerCallResult::AnswerCallResult (const AnswerCallResult &)";
  abort();
}

AnswerCallResult::~AnswerCallResult()
{
} // end of destructor

AsnType *AnswerCallResult::Clone() const
{
  return new(memBlock) AnswerCallResult(memBlock);
}

AnswerCallResult &AnswerCallResult::operator = (const AnswerCallResult &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case extensionsCid:
        extensions = new(memBlock) CSTAPrivateData(memBlock);
        *extensions = *that.extensions;
        break;
      case noDataCid:
        noData = new(memBlock) AsnNull(memBlock);
        *noData = *that.noData;
        break;
    }
  }

  return *this;
}

AsnLen
AnswerCallResult::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case extensionsCid:
      BEncEocIfNec (b);
      l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 29);
      break;

    case noDataCid:
      l = noData->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, NULLTYPE_TAG_CODE);
      break;

  } // end switch
  return l;
} // AnswerCallResult::BEncContent


void AnswerCallResult::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (APPL, CONS, 29):
      choiceId = extensionsCid;
      extensions = new(memBlock) CSTAPrivateData(memBlock);
        extensions->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, PRIM, NULLTYPE_TAG_CODE):
      choiceId = noDataCid;
      noData = new(memBlock) AsnNull(memBlock);
        noData->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0133: Unexpected tag in CHOICE";
      break;
  } // end switch
} // AnswerCallResult::BDecContent


AsnLen AnswerCallResult::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void AnswerCallResult::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int AnswerCallResult::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int AnswerCallResult::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void AnswerCallResult::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case extensionsCid: os << "CSTAPrivateData*"; break;
    case noDataCid: os << "AsnNull*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case extensionsCid:
      os << "extensions : ";
      if (extensions)
        os << *extensions;
      else
        os << "VOID";
      break;

    case noDataCid:
      os << "noData : ";
      if (noData)
        os << *noData;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // AnswerCallResult::Print

CallCompletionResult::CallCompletionResult( MemBlock* mb ) : AsnType( mb )
{
  choiceId = extensionsCid;
  extensions = NULL; // incomplete initialization of mandatory element!
}

CallCompletionResult::CallCompletionResult( MemBlock* mb, const CallCompletionResult & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined CallCompletionResult::CallCompletionResult (const CallCompletionResult &)";
  abort();
}

CallCompletionResult::~CallCompletionResult()
{
} // end of destructor

AsnType *CallCompletionResult::Clone() const
{
  return new(memBlock) CallCompletionResult(memBlock);
}

CallCompletionResult &CallCompletionResult::operator = (const CallCompletionResult &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case extensionsCid:
        extensions = new(memBlock) CSTAPrivateData(memBlock);
        *extensions = *that.extensions;
        break;
      case noDataCid:
        noData = new(memBlock) AsnNull(memBlock);
        *noData = *that.noData;
        break;
    }
  }

  return *this;
}

AsnLen
CallCompletionResult::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case extensionsCid:
      BEncEocIfNec (b);
      l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 29);
      break;

    case noDataCid:
      l = noData->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, NULLTYPE_TAG_CODE);
      break;

  } // end switch
  return l;
} // CallCompletionResult::BEncContent


void CallCompletionResult::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (APPL, CONS, 29):
      choiceId = extensionsCid;
      extensions = new(memBlock) CSTAPrivateData(memBlock);
        extensions->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, PRIM, NULLTYPE_TAG_CODE):
      choiceId = noDataCid;
      noData = new(memBlock) AsnNull(memBlock);
        noData->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0134: Unexpected tag in CHOICE";
      break;
  } // end switch
} // CallCompletionResult::BDecContent


AsnLen CallCompletionResult::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void CallCompletionResult::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int CallCompletionResult::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int CallCompletionResult::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void CallCompletionResult::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case extensionsCid: os << "CSTAPrivateData*"; break;
    case noDataCid: os << "AsnNull*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case extensionsCid:
      os << "extensions : ";
      if (extensions)
        os << *extensions;
      else
        os << "VOID";
      break;

    case noDataCid:
      os << "noData : ";
      if (noData)
        os << *noData;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // CallCompletionResult::Print

ClearCallResult::ClearCallResult( MemBlock* mb ) : AsnType( mb )
{
  choiceId = extensionsCid;
  extensions = NULL; // incomplete initialization of mandatory element!
}

ClearCallResult::ClearCallResult( MemBlock* mb, const ClearCallResult & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined ClearCallResult::ClearCallResult (const ClearCallResult &)";
  abort();
}

ClearCallResult::~ClearCallResult()
{
} // end of destructor

AsnType *ClearCallResult::Clone() const
{
  return new(memBlock) ClearCallResult(memBlock);
}

ClearCallResult &ClearCallResult::operator = (const ClearCallResult &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case extensionsCid:
        extensions = new(memBlock) CSTAPrivateData(memBlock);
        *extensions = *that.extensions;
        break;
      case noDataCid:
        noData = new(memBlock) AsnNull(memBlock);
        *noData = *that.noData;
        break;
    }
  }

  return *this;
}

AsnLen
ClearCallResult::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case extensionsCid:
      BEncEocIfNec (b);
      l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 29);
      break;

    case noDataCid:
      l = noData->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, NULLTYPE_TAG_CODE);
      break;

  } // end switch
  return l;
} // ClearCallResult::BEncContent


void ClearCallResult::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (APPL, CONS, 29):
      choiceId = extensionsCid;
      extensions = new(memBlock) CSTAPrivateData(memBlock);
        extensions->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, PRIM, NULLTYPE_TAG_CODE):
      choiceId = noDataCid;
      noData = new(memBlock) AsnNull(memBlock);
        noData->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0135: Unexpected tag in CHOICE";
      break;
  } // end switch
} // ClearCallResult::BDecContent


AsnLen ClearCallResult::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void ClearCallResult::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int ClearCallResult::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ClearCallResult::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ClearCallResult::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case extensionsCid: os << "CSTAPrivateData*"; break;
    case noDataCid: os << "AsnNull*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case extensionsCid:
      os << "extensions : ";
      if (extensions)
        os << *extensions;
      else
        os << "VOID";
      break;

    case noDataCid:
      os << "noData : ";
      if (noData)
        os << *noData;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // ClearCallResult::Print

ClearConnectionResult::ClearConnectionResult( MemBlock* mb ) : AsnType( mb )
{
  choiceId = extensionsCid;
  extensions = NULL; // incomplete initialization of mandatory element!
}

ClearConnectionResult::ClearConnectionResult( MemBlock* mb, const ClearConnectionResult & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined ClearConnectionResult::ClearConnectionResult (const ClearConnectionResult &)";
  abort();
}

ClearConnectionResult::~ClearConnectionResult()
{
} // end of destructor

AsnType *ClearConnectionResult::Clone() const
{
  return new(memBlock) ClearConnectionResult(memBlock);
}

ClearConnectionResult &ClearConnectionResult::operator = (const ClearConnectionResult &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case extensionsCid:
        extensions = new(memBlock) CSTAPrivateData(memBlock);
        *extensions = *that.extensions;
        break;
      case noDataCid:
        noData = new(memBlock) AsnNull(memBlock);
        *noData = *that.noData;
        break;
    }
  }

  return *this;
}

AsnLen
ClearConnectionResult::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case extensionsCid:
      BEncEocIfNec (b);
      l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 29);
      break;

    case noDataCid:
      l = noData->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, NULLTYPE_TAG_CODE);
      break;

  } // end switch
  return l;
} // ClearConnectionResult::BEncContent


void ClearConnectionResult::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (APPL, CONS, 29):
      choiceId = extensionsCid;
      extensions = new(memBlock) CSTAPrivateData(memBlock);
        extensions->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, PRIM, NULLTYPE_TAG_CODE):
      choiceId = noDataCid;
      noData = new(memBlock) AsnNull(memBlock);
        noData->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0136: Unexpected tag in CHOICE";
      break;
  } // end switch
} // ClearConnectionResult::BDecContent


AsnLen ClearConnectionResult::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void ClearConnectionResult::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int ClearConnectionResult::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ClearConnectionResult::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ClearConnectionResult::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case extensionsCid: os << "CSTAPrivateData*"; break;
    case noDataCid: os << "AsnNull*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case extensionsCid:
      os << "extensions : ";
      if (extensions)
        os << *extensions;
      else
        os << "VOID";
      break;

    case noDataCid:
      os << "noData : ";
      if (noData)
        os << *noData;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // ClearConnectionResult::Print

DivertCallResult::DivertCallResult( MemBlock* mb ) : AsnType( mb )
{
  choiceId = extensionsCid;
  extensions = NULL; // incomplete initialization of mandatory element!
}

DivertCallResult::DivertCallResult( MemBlock* mb, const DivertCallResult & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined DivertCallResult::DivertCallResult (const DivertCallResult &)";
  abort();
}

DivertCallResult::~DivertCallResult()
{
} // end of destructor

AsnType *DivertCallResult::Clone() const
{
  return new(memBlock) DivertCallResult(memBlock);
}

DivertCallResult &DivertCallResult::operator = (const DivertCallResult &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case extensionsCid:
        extensions = new(memBlock) CSTAPrivateData(memBlock);
        *extensions = *that.extensions;
        break;
      case noDataCid:
        noData = new(memBlock) AsnNull(memBlock);
        *noData = *that.noData;
        break;
    }
  }

  return *this;
}

AsnLen
DivertCallResult::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case extensionsCid:
      BEncEocIfNec (b);
      l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 29);
      break;

    case noDataCid:
      l = noData->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, NULLTYPE_TAG_CODE);
      break;

  } // end switch
  return l;
} // DivertCallResult::BEncContent


void DivertCallResult::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (APPL, CONS, 29):
      choiceId = extensionsCid;
      extensions = new(memBlock) CSTAPrivateData(memBlock);
        extensions->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, PRIM, NULLTYPE_TAG_CODE):
      choiceId = noDataCid;
      noData = new(memBlock) AsnNull(memBlock);
        noData->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0137: Unexpected tag in CHOICE";
      break;
  } // end switch
} // DivertCallResult::BDecContent


AsnLen DivertCallResult::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void DivertCallResult::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int DivertCallResult::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int DivertCallResult::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void DivertCallResult::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case extensionsCid: os << "CSTAPrivateData*"; break;
    case noDataCid: os << "AsnNull*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case extensionsCid:
      os << "extensions : ";
      if (extensions)
        os << *extensions;
      else
        os << "VOID";
      break;

    case noDataCid:
      os << "noData : ";
      if (noData)
        os << *noData;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // DivertCallResult::Print

HoldCallResult::HoldCallResult( MemBlock* mb ) : AsnType( mb )
{
  choiceId = extensionsCid;
  extensions = NULL; // incomplete initialization of mandatory element!
}

HoldCallResult::HoldCallResult( MemBlock* mb, const HoldCallResult & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined HoldCallResult::HoldCallResult (const HoldCallResult &)";
  abort();
}

HoldCallResult::~HoldCallResult()
{
} // end of destructor

AsnType *HoldCallResult::Clone() const
{
  return new(memBlock) HoldCallResult(memBlock);
}

HoldCallResult &HoldCallResult::operator = (const HoldCallResult &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case extensionsCid:
        extensions = new(memBlock) CSTAPrivateData(memBlock);
        *extensions = *that.extensions;
        break;
      case noDataCid:
        noData = new(memBlock) AsnNull(memBlock);
        *noData = *that.noData;
        break;
    }
  }

  return *this;
}

AsnLen
HoldCallResult::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case extensionsCid:
      BEncEocIfNec (b);
      l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 29);
      break;

    case noDataCid:
      l = noData->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, NULLTYPE_TAG_CODE);
      break;

  } // end switch
  return l;
} // HoldCallResult::BEncContent


void HoldCallResult::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (APPL, CONS, 29):
      choiceId = extensionsCid;
      extensions = new(memBlock) CSTAPrivateData(memBlock);
        extensions->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, PRIM, NULLTYPE_TAG_CODE):
      choiceId = noDataCid;
      noData = new(memBlock) AsnNull(memBlock);
        noData->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0138: Unexpected tag in CHOICE";
      break;
  } // end switch
} // HoldCallResult::BDecContent


AsnLen HoldCallResult::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void HoldCallResult::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int HoldCallResult::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int HoldCallResult::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void HoldCallResult::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case extensionsCid: os << "CSTAPrivateData*"; break;
    case noDataCid: os << "AsnNull*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case extensionsCid:
      os << "extensions : ";
      if (extensions)
        os << *extensions;
      else
        os << "VOID";
      break;

    case noDataCid:
      os << "noData : ";
      if (noData)
        os << *noData;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // HoldCallResult::Print

ReconnectCallResult::ReconnectCallResult( MemBlock* mb ) : AsnType( mb )
{
  choiceId = extensionsCid;
  extensions = NULL; // incomplete initialization of mandatory element!
}

ReconnectCallResult::ReconnectCallResult( MemBlock* mb, const ReconnectCallResult & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined ReconnectCallResult::ReconnectCallResult (const ReconnectCallResult &)";
  abort();
}

ReconnectCallResult::~ReconnectCallResult()
{
} // end of destructor

AsnType *ReconnectCallResult::Clone() const
{
  return new(memBlock) ReconnectCallResult(memBlock);
}

ReconnectCallResult &ReconnectCallResult::operator = (const ReconnectCallResult &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case extensionsCid:
        extensions = new(memBlock) CSTAPrivateData(memBlock);
        *extensions = *that.extensions;
        break;
      case noDataCid:
        noData = new(memBlock) AsnNull(memBlock);
        *noData = *that.noData;
        break;
    }
  }

  return *this;
}

AsnLen
ReconnectCallResult::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case extensionsCid:
      BEncEocIfNec (b);
      l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 29);
      break;

    case noDataCid:
      l = noData->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, NULLTYPE_TAG_CODE);
      break;

  } // end switch
  return l;
} // ReconnectCallResult::BEncContent


void ReconnectCallResult::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (APPL, CONS, 29):
      choiceId = extensionsCid;
      extensions = new(memBlock) CSTAPrivateData(memBlock);
        extensions->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, PRIM, NULLTYPE_TAG_CODE):
      choiceId = noDataCid;
      noData = new(memBlock) AsnNull(memBlock);
        noData->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0139: Unexpected tag in CHOICE";
      break;
  } // end switch
} // ReconnectCallResult::BDecContent


AsnLen ReconnectCallResult::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void ReconnectCallResult::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int ReconnectCallResult::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ReconnectCallResult::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ReconnectCallResult::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case extensionsCid: os << "CSTAPrivateData*"; break;
    case noDataCid: os << "AsnNull*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case extensionsCid:
      os << "extensions : ";
      if (extensions)
        os << *extensions;
      else
        os << "VOID";
      break;

    case noDataCid:
      os << "noData : ";
      if (noData)
        os << *noData;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // ReconnectCallResult::Print

RetrieveCallResult::RetrieveCallResult( MemBlock* mb ) : AsnType( mb )
{
  choiceId = extensionsCid;
  extensions = NULL; // incomplete initialization of mandatory element!
}

RetrieveCallResult::RetrieveCallResult( MemBlock* mb, const RetrieveCallResult & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined RetrieveCallResult::RetrieveCallResult (const RetrieveCallResult &)";
  abort();
}

RetrieveCallResult::~RetrieveCallResult()
{
} // end of destructor

AsnType *RetrieveCallResult::Clone() const
{
  return new(memBlock) RetrieveCallResult(memBlock);
}

RetrieveCallResult &RetrieveCallResult::operator = (const RetrieveCallResult &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case extensionsCid:
        extensions = new(memBlock) CSTAPrivateData(memBlock);
        *extensions = *that.extensions;
        break;
      case noDataCid:
        noData = new(memBlock) AsnNull(memBlock);
        *noData = *that.noData;
        break;
    }
  }

  return *this;
}

AsnLen
RetrieveCallResult::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case extensionsCid:
      BEncEocIfNec (b);
      l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 29);
      break;

    case noDataCid:
      l = noData->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, NULLTYPE_TAG_CODE);
      break;

  } // end switch
  return l;
} // RetrieveCallResult::BEncContent


void RetrieveCallResult::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (APPL, CONS, 29):
      choiceId = extensionsCid;
      extensions = new(memBlock) CSTAPrivateData(memBlock);
        extensions->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, PRIM, NULLTYPE_TAG_CODE):
      choiceId = noDataCid;
      noData = new(memBlock) AsnNull(memBlock);
        noData->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0140: Unexpected tag in CHOICE";
      break;
  } // end switch
} // RetrieveCallResult::BDecContent


AsnLen RetrieveCallResult::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void RetrieveCallResult::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int RetrieveCallResult::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int RetrieveCallResult::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void RetrieveCallResult::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case extensionsCid: os << "CSTAPrivateData*"; break;
    case noDataCid: os << "AsnNull*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case extensionsCid:
      os << "extensions : ";
      if (extensions)
        os << *extensions;
      else
        os << "VOID";
      break;

    case noDataCid:
      os << "noData : ";
      if (noData)
        os << *noData;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // RetrieveCallResult::Print

SetFeatureResult::SetFeatureResult( MemBlock* mb ) : AsnType( mb )
{
  choiceId = extensionsCid;
  extensions = NULL; // incomplete initialization of mandatory element!
}

SetFeatureResult::SetFeatureResult( MemBlock* mb, const SetFeatureResult & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined SetFeatureResult::SetFeatureResult (const SetFeatureResult &)";
  abort();
}

SetFeatureResult::~SetFeatureResult()
{
} // end of destructor

AsnType *SetFeatureResult::Clone() const
{
  return new(memBlock) SetFeatureResult(memBlock);
}

SetFeatureResult &SetFeatureResult::operator = (const SetFeatureResult &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case extensionsCid:
        extensions = new(memBlock) CSTAPrivateData(memBlock);
        *extensions = *that.extensions;
        break;
      case noDataCid:
        noData = new(memBlock) AsnNull(memBlock);
        *noData = *that.noData;
        break;
    }
  }

  return *this;
}

AsnLen
SetFeatureResult::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case extensionsCid:
      BEncEocIfNec (b);
      l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 29);
      break;

    case noDataCid:
      l = noData->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, NULLTYPE_TAG_CODE);
      break;

  } // end switch
  return l;
} // SetFeatureResult::BEncContent


void SetFeatureResult::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (APPL, CONS, 29):
      choiceId = extensionsCid;
      extensions = new(memBlock) CSTAPrivateData(memBlock);
        extensions->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, PRIM, NULLTYPE_TAG_CODE):
      choiceId = noDataCid;
      noData = new(memBlock) AsnNull(memBlock);
        noData->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0141: Unexpected tag in CHOICE";
      break;
  } // end switch
} // SetFeatureResult::BDecContent


AsnLen SetFeatureResult::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void SetFeatureResult::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int SetFeatureResult::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int SetFeatureResult::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void SetFeatureResult::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case extensionsCid: os << "CSTAPrivateData*"; break;
    case noDataCid: os << "AsnNull*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case extensionsCid:
      os << "extensions : ";
      if (extensions)
        os << *extensions;
      else
        os << "VOID";
      break;

    case noDataCid:
      os << "noData : ";
      if (noData)
        os << *noData;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // SetFeatureResult::Print

EventTypeID::EventTypeID( MemBlock* mb ) : AsnType( mb )
{
  choiceId = cCSTAformCid;
  cCSTAform = NULL; // incomplete initialization of mandatory element!
}

EventTypeID::EventTypeID( MemBlock* mb, const EventTypeID & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined EventTypeID::EventTypeID (const EventTypeID &)";
  abort();
}

EventTypeID::~EventTypeID()
{
} // end of destructor

AsnType *EventTypeID::Clone() const
{
  return new(memBlock) EventTypeID(memBlock);
}

EventTypeID &EventTypeID::operator = (const EventTypeID &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case cCSTAformCid:
        cCSTAform = new(memBlock) EventIDType(memBlock);
        *cCSTAform = *that.cCSTAform;
        break;
    }
  }

  return *this;
}

AsnLen
EventTypeID::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case cCSTAformCid:
      l = cCSTAform->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 0);
      break;

  } // end switch
  return l;
} // EventTypeID::BEncContent


void EventTypeID::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (CNTX, PRIM, 0):
      choiceId = cCSTAformCid;
      cCSTAform = new(memBlock) EventIDType(memBlock);
        cCSTAform->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0142: Unexpected tag in CHOICE";
      break;
  } // end switch
} // EventTypeID::BDecContent


AsnLen EventTypeID::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void EventTypeID::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int EventTypeID::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int EventTypeID::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void EventTypeID::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case cCSTAformCid: os << "EventIDType*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case cCSTAformCid:
      os << "cCSTAform : ";
      if (cCSTAform)
        os << *cCSTAform;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // EventTypeID::Print

CSTAEventReportArgument::CSTAEventReportArgument( MemBlock* mb ) : AsnType( mb )
    , crossRefIdentifier( mb )
    , eventInfo( mb )
{
  eventType = NULL; // incomplete initialization of mandatory element!
  extensions = NULL;
}

CSTAEventReportArgument::CSTAEventReportArgument( MemBlock* mb, const CSTAEventReportArgument & ) : AsnType( mb )
    , crossRefIdentifier( mb )
    , eventInfo( mb )
{
  throw "ERROR C0099: Use of incompletely defined CSTAEventReportArgument::CSTAEventReportArgument (const CSTAEventReportArgument &)";
  abort();
}

CSTAEventReportArgument::~CSTAEventReportArgument()
{
}

AsnType *CSTAEventReportArgument::Clone() const
{
  return new(memBlock) CSTAEventReportArgument(memBlock);
}

CSTAEventReportArgument &CSTAEventReportArgument::operator = (const CSTAEventReportArgument &that)
{
  if (this != &that)
  {
    crossRefIdentifier = that.crossRefIdentifier;
    if (that.eventType)
    {
      if (!eventType)
        eventType = new(memBlock) EventTypeID(memBlock);
      *eventType = *that.eventType;
    }
    else
    {
      eventType = NULL;
    }
    eventInfo = that.eventInfo;
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTAPrivateData(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
CSTAEventReportArgument::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 29);
    totalLen += l;
  }

    eventInfo.SetTypeBy( *eventType );
    l = eventInfo.BEnc (b);
    totalLen += l;

    l = eventType->BEncContent (b);
    totalLen += l;

    l = crossRefIdentifier.BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, APPL, PRIM, 21);
    totalLen += l;

  return totalLen;
} // CSTAEventReportArgument::BEncContent


void CSTAEventReportArgument::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, PRIM, 21))
    || (tag1 == MAKE_TAG_ID (APPL, CONS, 21)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    crossRefIdentifier.BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0143: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 0)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    eventType = new(memBlock) EventTypeID(memBlock);
    eventType->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0144: SEQUENCE is missing non-optional elmt.";
  }

  // ANY type
    eventInfo.SetTypeBy( *eventType );
    eventInfo.BDec (b, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }


  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 29)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTAPrivateData(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0145: Length discrepancy on sequence.";
  }
  else
    return;
} // CSTAEventReportArgument::BDecContent

AsnLen CSTAEventReportArgument::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void CSTAEventReportArgument::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135067784: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int CSTAEventReportArgument::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int CSTAEventReportArgument::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void CSTAEventReportArgument::Print ( CTsvcLIB::LOG& os ) const
{
  os << "CSTAEventReportArgument SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "crossRefIdentifier : ";
  os << crossRefIdentifier;
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "eventType : ";
  if (NOT_NULL (eventType))
    os << *eventType;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "eventInfo : ";
  os << eventInfo;
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // CSTAEventReportArgument::Print


EscapeServiceResult::EscapeServiceResult( MemBlock* mb ) : AsnType( mb )
{
  choiceId = extensionsCid;
  extensions = NULL; // incomplete initialization of mandatory element!
}

EscapeServiceResult::EscapeServiceResult( MemBlock* mb, const EscapeServiceResult & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined EscapeServiceResult::EscapeServiceResult (const EscapeServiceResult &)";
  abort();
}

EscapeServiceResult::~EscapeServiceResult()
{
} // end of destructor

AsnType *EscapeServiceResult::Clone() const
{
  return new(memBlock) EscapeServiceResult(memBlock);
}

EscapeServiceResult &EscapeServiceResult::operator = (const EscapeServiceResult &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case extensionsCid:
        extensions = new(memBlock) CSTAPrivateData(memBlock);
        *extensions = *that.extensions;
        break;
      case noDataCid:
        noData = new(memBlock) AsnNull(memBlock);
        *noData = *that.noData;
        break;
    }
  }

  return *this;
}

AsnLen
EscapeServiceResult::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case extensionsCid:
      BEncEocIfNec (b);
      l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 29);
      break;

    case noDataCid:
      l = noData->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, NULLTYPE_TAG_CODE);
      break;

  } // end switch
  return l;
} // EscapeServiceResult::BEncContent


void EscapeServiceResult::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (APPL, CONS, 29):
      choiceId = extensionsCid;
      extensions = new(memBlock) CSTAPrivateData(memBlock);
        extensions->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, PRIM, NULLTYPE_TAG_CODE):
      choiceId = noDataCid;
      noData = new(memBlock) AsnNull(memBlock);
        noData->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0146: Unexpected tag in CHOICE";
      break;
  } // end switch
} // EscapeServiceResult::BDecContent


AsnLen EscapeServiceResult::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void EscapeServiceResult::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int EscapeServiceResult::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int EscapeServiceResult::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void EscapeServiceResult::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case extensionsCid: os << "CSTAPrivateData*"; break;
    case noDataCid: os << "AsnNull*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case extensionsCid:
      os << "extensions : ";
      if (extensions)
        os << *extensions;
      else
        os << "VOID";
      break;

    case noDataCid:
      os << "noData : ";
      if (noData)
        os << *noData;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // EscapeServiceResult::Print

SystemStatusResult::SystemStatusResult( MemBlock* mb ) : AsnType( mb )
{
  choiceId = extensionsCid;
  extensions = NULL; // incomplete initialization of mandatory element!
}

SystemStatusResult::SystemStatusResult( MemBlock* mb, const SystemStatusResult & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined SystemStatusResult::SystemStatusResult (const SystemStatusResult &)";
  abort();
}

SystemStatusResult::~SystemStatusResult()
{
} // end of destructor

AsnType *SystemStatusResult::Clone() const
{
  return new(memBlock) SystemStatusResult(memBlock);
}

SystemStatusResult &SystemStatusResult::operator = (const SystemStatusResult &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case extensionsCid:
        extensions = new(memBlock) CSTAPrivateData(memBlock);
        *extensions = *that.extensions;
        break;
      case noDataCid:
        noData = new(memBlock) AsnNull(memBlock);
        *noData = *that.noData;
        break;
    }
  }

  return *this;
}

AsnLen
SystemStatusResult::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case extensionsCid:
      BEncEocIfNec (b);
      l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 29);
      break;

    case noDataCid:
      l = noData->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, NULLTYPE_TAG_CODE);
      break;

  } // end switch
  return l;
} // SystemStatusResult::BEncContent


void SystemStatusResult::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (APPL, CONS, 29):
      choiceId = extensionsCid;
      extensions = new(memBlock) CSTAPrivateData(memBlock);
        extensions->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, PRIM, NULLTYPE_TAG_CODE):
      choiceId = noDataCid;
      noData = new(memBlock) AsnNull(memBlock);
        noData->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0147: Unexpected tag in CHOICE";
      break;
  } // end switch
} // SystemStatusResult::BDecContent


AsnLen SystemStatusResult::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void SystemStatusResult::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int SystemStatusResult::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int SystemStatusResult::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void SystemStatusResult::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case extensionsCid: os << "CSTAPrivateData*"; break;
    case noDataCid: os << "AsnNull*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case extensionsCid:
      os << "extensions : ";
      if (extensions)
        os << *extensions;
      else
        os << "VOID";
      break;

    case noDataCid:
      os << "noData : ";
      if (noData)
        os << *noData;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // SystemStatusResult::Print

MonitorStopResult::MonitorStopResult( MemBlock* mb ) : AsnType( mb )
{
  choiceId = extensionsCid;
  extensions = NULL; // incomplete initialization of mandatory element!
}

MonitorStopResult::MonitorStopResult( MemBlock* mb, const MonitorStopResult & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined MonitorStopResult::MonitorStopResult (const MonitorStopResult &)";
  abort();
}

MonitorStopResult::~MonitorStopResult()
{
} // end of destructor

AsnType *MonitorStopResult::Clone() const
{
  return new(memBlock) MonitorStopResult(memBlock);
}

MonitorStopResult &MonitorStopResult::operator = (const MonitorStopResult &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case extensionsCid:
        extensions = new(memBlock) CSTAPrivateData(memBlock);
        *extensions = *that.extensions;
        break;
      case noDataCid:
        noData = new(memBlock) AsnNull(memBlock);
        *noData = *that.noData;
        break;
    }
  }

  return *this;
}

AsnLen
MonitorStopResult::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case extensionsCid:
      BEncEocIfNec (b);
      l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 29);
      break;

    case noDataCid:
      l = noData->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, NULLTYPE_TAG_CODE);
      break;

  } // end switch
  return l;
} // MonitorStopResult::BEncContent


void MonitorStopResult::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (APPL, CONS, 29):
      choiceId = extensionsCid;
      extensions = new(memBlock) CSTAPrivateData(memBlock);
        extensions->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, PRIM, NULLTYPE_TAG_CODE):
      choiceId = noDataCid;
      noData = new(memBlock) AsnNull(memBlock);
        noData->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0148: Unexpected tag in CHOICE";
      break;
  } // end switch
} // MonitorStopResult::BDecContent


AsnLen MonitorStopResult::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void MonitorStopResult::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int MonitorStopResult::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int MonitorStopResult::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void MonitorStopResult::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case extensionsCid: os << "CSTAPrivateData*"; break;
    case noDataCid: os << "AsnNull*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case extensionsCid:
      os << "extensions : ";
      if (extensions)
        os << *extensions;
      else
        os << "VOID";
      break;

    case noDataCid:
      os << "noData : ";
      if (noData)
        os << *noData;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // MonitorStopResult::Print

UniversalFailure::UniversalFailure( MemBlock* mb ) : AsnType( mb )
{
  choiceId = operationalErrorsCid;
  operationalErrors = NULL; // incomplete initialization of mandatory element!
}

UniversalFailure::UniversalFailure( MemBlock* mb, const UniversalFailure & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined UniversalFailure::UniversalFailure (const UniversalFailure &)";
  abort();
}

UniversalFailure::~UniversalFailure()
{
} // end of destructor

AsnType *UniversalFailure::Clone() const
{
  return new(memBlock) UniversalFailure(memBlock);
}

UniversalFailure &UniversalFailure::operator = (const UniversalFailure &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case operationalErrorsCid:
        operationalErrors = new(memBlock) Operations(memBlock);
        *operationalErrors = *that.operationalErrors;
        break;
      case stateErrorsCid:
        stateErrors = new(memBlock) StateIncompatibility(memBlock);
        *stateErrors = *that.stateErrors;
        break;
      case systemResourceErrorsCid:
        systemResourceErrors = new(memBlock) SystemResourceAvailability(memBlock);
        *systemResourceErrors = *that.systemResourceErrors;
        break;
      case subscribedResourceAvailabilityErrorsCid:
        subscribedResourceAvailabilityErrors = new(memBlock) SubscribedResourceAvailability(memBlock);
        *subscribedResourceAvailabilityErrors = *that.subscribedResourceAvailabilityErrors;
        break;
      case performanceErrorsCid:
        performanceErrors = new(memBlock) PerformanceManagement(memBlock);
        *performanceErrors = *that.performanceErrors;
        break;
      case securityErrorsCid:
        securityErrors = new(memBlock) SecurityError(memBlock);
        *securityErrors = *that.securityErrors;
        break;
      case unspecifiedErrorsCid:
        unspecifiedErrors = new(memBlock) AsnNull(memBlock);
        *unspecifiedErrors = *that.unspecifiedErrors;
        break;
      case nonStandardErrorsCid:
        nonStandardErrors = new(memBlock) CSTAPrivateData(memBlock);
        *nonStandardErrors = *that.nonStandardErrors;
        break;
    }
  }

  return *this;
}

AsnLen
UniversalFailure::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case operationalErrorsCid:
      l = operationalErrors->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 1);
      break;

    case stateErrorsCid:
      l = stateErrors->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 2);
      break;

    case systemResourceErrorsCid:
      l = systemResourceErrors->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 3);
      break;

    case subscribedResourceAvailabilityErrorsCid:
      l = subscribedResourceAvailabilityErrors->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 4);
      break;

    case performanceErrorsCid:
      l = performanceErrors->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 5);
      break;

    case securityErrorsCid:
      l = securityErrors->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 6);
      break;

    case unspecifiedErrorsCid:
      l = unspecifiedErrors->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 7);
      break;

    case nonStandardErrorsCid:
      BEncEocIfNec (b);
      l = nonStandardErrors->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 29);
      break;

  } // end switch
  return l;
} // UniversalFailure::BEncContent


void UniversalFailure::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (CNTX, PRIM, 1):
      choiceId = operationalErrorsCid;
      operationalErrors = new(memBlock) Operations(memBlock);
        operationalErrors->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 2):
      choiceId = stateErrorsCid;
      stateErrors = new(memBlock) StateIncompatibility(memBlock);
        stateErrors->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 3):
      choiceId = systemResourceErrorsCid;
      systemResourceErrors = new(memBlock) SystemResourceAvailability(memBlock);
        systemResourceErrors->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 4):
      choiceId = subscribedResourceAvailabilityErrorsCid;
      subscribedResourceAvailabilityErrors = new(memBlock) SubscribedResourceAvailability(memBlock);
        subscribedResourceAvailabilityErrors->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 5):
      choiceId = performanceErrorsCid;
      performanceErrors = new(memBlock) PerformanceManagement(memBlock);
        performanceErrors->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 6):
      choiceId = securityErrorsCid;
      securityErrors = new(memBlock) SecurityError(memBlock);
        securityErrors->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 7):
      choiceId = unspecifiedErrorsCid;
      unspecifiedErrors = new(memBlock) AsnNull(memBlock);
        unspecifiedErrors->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (APPL, CONS, 29):
      choiceId = nonStandardErrorsCid;
      nonStandardErrors = new(memBlock) CSTAPrivateData(memBlock);
        nonStandardErrors->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0149: Unexpected tag in CHOICE";
      break;
  } // end switch
} // UniversalFailure::BDecContent


AsnLen UniversalFailure::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void UniversalFailure::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int UniversalFailure::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int UniversalFailure::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void UniversalFailure::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case operationalErrorsCid: os << "Operations*"; break;
    case stateErrorsCid: os << "StateIncompatibility*"; break;
    case systemResourceErrorsCid: os << "SystemResourceAvailability*"; break;
    case subscribedResourceAvailabilityErrorsCid: os << "SubscribedResourceAvailability*"; break;
    case performanceErrorsCid: os << "PerformanceManagement*"; break;
    case securityErrorsCid: os << "SecurityError*"; break;
    case unspecifiedErrorsCid: os << "AsnNull*"; break;
    case nonStandardErrorsCid: os << "CSTAPrivateData*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case operationalErrorsCid:
      os << "operationalErrors : ";
      if (operationalErrors)
        os << *operationalErrors;
      else
        os << "VOID";
      break;

    case stateErrorsCid:
      os << "stateErrors : ";
      if (stateErrors)
        os << *stateErrors;
      else
        os << "VOID";
      break;

    case systemResourceErrorsCid:
      os << "systemResourceErrors : ";
      if (systemResourceErrors)
        os << *systemResourceErrors;
      else
        os << "VOID";
      break;

    case subscribedResourceAvailabilityErrorsCid:
      os << "subscribedResourceAvailabilityErrors : ";
      if (subscribedResourceAvailabilityErrors)
        os << *subscribedResourceAvailabilityErrors;
      else
        os << "VOID";
      break;

    case performanceErrorsCid:
      os << "performanceErrors : ";
      if (performanceErrors)
        os << *performanceErrors;
      else
        os << "VOID";
      break;

    case securityErrorsCid:
      os << "securityErrors : ";
      if (securityErrors)
        os << *securityErrors;
      else
        os << "VOID";
      break;

    case unspecifiedErrorsCid:
      os << "unspecifiedErrors : ";
      if (unspecifiedErrors)
        os << *unspecifiedErrors;
      else
        os << "VOID";
      break;

    case nonStandardErrorsCid:
      os << "nonStandardErrors : ";
      if (nonStandardErrors)
        os << *nonStandardErrors;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // UniversalFailure::Print

DeviceID::DeviceID( MemBlock* mb ) : AsnType( mb )
{
  choiceId = dialingNumberCid;
  dialingNumber = NULL; // incomplete initialization of mandatory element!
}

DeviceID::DeviceID( MemBlock* mb, const DeviceID & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined DeviceID::DeviceID (const DeviceID &)";
  abort();
}

DeviceID::~DeviceID()
{
} // end of destructor

AsnType *DeviceID::Clone() const
{
  return new(memBlock) DeviceID(memBlock);
}

DeviceID &DeviceID::operator = (const DeviceID &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case dialingNumberCid:
        dialingNumber = new(memBlock) NumberDigits(memBlock);
        *dialingNumber = *that.dialingNumber;
        break;
      case deviceNumberCid:
        deviceNumber = new(memBlock) DeviceNumber(memBlock);
        *deviceNumber = *that.deviceNumber;
        break;
    }
  }

  return *this;
}

AsnLen
DeviceID::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case dialingNumberCid:
      l = dialingNumber->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 0);
      break;

    case deviceNumberCid:
      l = deviceNumber->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 1);
      break;

  } // end switch
  return l;
} // DeviceID::BEncContent


void DeviceID::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (CNTX, PRIM, 0):
    case MAKE_TAG_ID (CNTX, CONS, 0):
      choiceId = dialingNumberCid;
      dialingNumber = new(memBlock) NumberDigits(memBlock);
        dialingNumber->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 1):
      choiceId = deviceNumberCid;
      deviceNumber = new(memBlock) DeviceNumber(memBlock);
        deviceNumber->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0150: Unexpected tag in CHOICE";
      break;
  } // end switch
} // DeviceID::BDecContent


AsnLen DeviceID::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void DeviceID::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int DeviceID::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int DeviceID::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void DeviceID::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case dialingNumberCid: os << "NumberDigits*"; break;
    case deviceNumberCid: os << "DeviceNumber*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case dialingNumberCid:
      os << "dialingNumber : ";
      if (dialingNumber)
        os << *dialingNumber;
      else
        os << "VOID";
      break;

    case deviceNumberCid:
      os << "deviceNumber : ";
      if (deviceNumber)
        os << *deviceNumber;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // DeviceID::Print

ExtendedDeviceID::ExtendedDeviceID( MemBlock* mb ) : AsnType( mb )
{
  choiceId = dialingNumberCid;
  dialingNumber = NULL; // incomplete initialization of mandatory element!
}

ExtendedDeviceID::ExtendedDeviceID( MemBlock* mb, const ExtendedDeviceID & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined ExtendedDeviceID::ExtendedDeviceID (const ExtendedDeviceID &)";
  abort();
}

ExtendedDeviceID::~ExtendedDeviceID()
{
} // end of destructor

AsnType *ExtendedDeviceID::Clone() const
{
  return new(memBlock) ExtendedDeviceID(memBlock);
}

ExtendedDeviceID &ExtendedDeviceID::operator = (const ExtendedDeviceID &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case dialingNumberCid:
        dialingNumber = new(memBlock) NumberDigits(memBlock);
        *dialingNumber = *that.dialingNumber;
        break;
      case deviceNumberCid:
        deviceNumber = new(memBlock) DeviceNumber(memBlock);
        *deviceNumber = *that.deviceNumber;
        break;
      case implicitPublicCid:
        implicitPublic = new(memBlock) NumberDigits(memBlock);
        *implicitPublic = *that.implicitPublic;
        break;
      case explicitPublicCid:
        explicitPublic = new(memBlock) PublicTON(memBlock);
        *explicitPublic = *that.explicitPublic;
        break;
      case implicitPrivateCid:
        implicitPrivate = new(memBlock) NumberDigits(memBlock);
        *implicitPrivate = *that.implicitPrivate;
        break;
      case explicitPrivateCid:
        explicitPrivate = new(memBlock) PrivateTON(memBlock);
        *explicitPrivate = *that.explicitPrivate;
        break;
      case otherCid:
        other = new(memBlock) OtherPlan(memBlock);
        *other = *that.other;
        break;
    }
  }

  return *this;
}

AsnLen
ExtendedDeviceID::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case dialingNumberCid:
      l = dialingNumber->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 0);
      break;

    case deviceNumberCid:
      l = deviceNumber->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 1);
      break;

    case implicitPublicCid:
      l = implicitPublic->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 2);
      break;

    case explicitPublicCid:
      BEncEocIfNec (b);
      l = explicitPublic->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, CNTX, CONS, 3);
      break;

    case implicitPrivateCid:
      l = implicitPrivate->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 4);
      break;

    case explicitPrivateCid:
      BEncEocIfNec (b);
      l = explicitPrivate->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, CNTX, CONS, 5);
      break;

    case otherCid:
      l = other->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 6);
      break;

  } // end switch
  return l;
} // ExtendedDeviceID::BEncContent


void ExtendedDeviceID::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnLen elmtLen1;
  switch (tag)
  {
    case MAKE_TAG_ID (CNTX, PRIM, 0):
    case MAKE_TAG_ID (CNTX, CONS, 0):
      choiceId = dialingNumberCid;
      dialingNumber = new(memBlock) NumberDigits(memBlock);
        dialingNumber->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 1):
      choiceId = deviceNumberCid;
      deviceNumber = new(memBlock) DeviceNumber(memBlock);
        deviceNumber->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 2):
    case MAKE_TAG_ID (CNTX, CONS, 2):
      choiceId = implicitPublicCid;
      implicitPublic = new(memBlock) NumberDigits(memBlock);
        implicitPublic->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, CONS, 3):
      tag = BDecTag (b, bytesDecoded);
      elmtLen1 = BDecLen (b, bytesDecoded);
      choiceId = explicitPublicCid;
      explicitPublic = new(memBlock) PublicTON(memBlock);
        explicitPublic->BDecContent (b, tag, elmtLen1, bytesDecoded);
      if (elmtLen0 == INDEFINITE_LEN)
        BDecEoc (b, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 4):
    case MAKE_TAG_ID (CNTX, CONS, 4):
      choiceId = implicitPrivateCid;
      implicitPrivate = new(memBlock) NumberDigits(memBlock);
        implicitPrivate->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, CONS, 5):
      tag = BDecTag (b, bytesDecoded);
      elmtLen1 = BDecLen (b, bytesDecoded);
      choiceId = explicitPrivateCid;
      explicitPrivate = new(memBlock) PrivateTON(memBlock);
        explicitPrivate->BDecContent (b, tag, elmtLen1, bytesDecoded);
      if (elmtLen0 == INDEFINITE_LEN)
        BDecEoc (b, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 6):
    case MAKE_TAG_ID (CNTX, CONS, 6):
      choiceId = otherCid;
      other = new(memBlock) OtherPlan(memBlock);
        other->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0151: Unexpected tag in CHOICE";
      break;
  } // end switch
} // ExtendedDeviceID::BDecContent


AsnLen ExtendedDeviceID::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void ExtendedDeviceID::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int ExtendedDeviceID::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ExtendedDeviceID::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ExtendedDeviceID::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case dialingNumberCid: os << "NumberDigits*"; break;
    case deviceNumberCid: os << "DeviceNumber*"; break;
    case implicitPublicCid: os << "NumberDigits*"; break;
    case explicitPublicCid: os << "PublicTON*"; break;
    case implicitPrivateCid: os << "NumberDigits*"; break;
    case explicitPrivateCid: os << "PrivateTON*"; break;
    case otherCid: os << "OtherPlan*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case dialingNumberCid:
      os << "dialingNumber : ";
      if (dialingNumber)
        os << *dialingNumber;
      else
        os << "VOID";
      break;

    case deviceNumberCid:
      os << "deviceNumber : ";
      if (deviceNumber)
        os << *deviceNumber;
      else
        os << "VOID";
      break;

    case implicitPublicCid:
      os << "implicitPublic : ";
      if (implicitPublic)
        os << *implicitPublic;
      else
        os << "VOID";
      break;

    case explicitPublicCid:
      os << "explicitPublic : ";
      if (explicitPublic)
        os << *explicitPublic;
      else
        os << "VOID";
      break;

    case implicitPrivateCid:
      os << "implicitPrivate : ";
      if (implicitPrivate)
        os << *implicitPrivate;
      else
        os << "VOID";
      break;

    case explicitPrivateCid:
      os << "explicitPrivate : ";
      if (explicitPrivate)
        os << *explicitPrivate;
      else
        os << "VOID";
      break;

    case otherCid:
      os << "other : ";
      if (other)
        os << *other;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // ExtendedDeviceID::Print

CallingDeviceID::CallingDeviceID( MemBlock* mb ) : AsnType( mb )
{
  choiceId = deviceIdentifierCid;
  deviceIdentifier = NULL; // incomplete initialization of mandatory element!
}

CallingDeviceID::CallingDeviceID( MemBlock* mb, const CallingDeviceID & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined CallingDeviceID::CallingDeviceID (const CallingDeviceID &)";
  abort();
}

CallingDeviceID::~CallingDeviceID()
{
} // end of destructor

AsnType *CallingDeviceID::Clone() const
{
  return new(memBlock) CallingDeviceID(memBlock);
}

CallingDeviceID &CallingDeviceID::operator = (const CallingDeviceID &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case deviceIdentifierCid:
        deviceIdentifier = new(memBlock) ExtendedDeviceID(memBlock);
        *deviceIdentifier = *that.deviceIdentifier;
        break;
      case notKnownCid:
        notKnown = new(memBlock) AsnNull(memBlock);
        *notKnown = *that.notKnown;
        break;
      case notRequiredCid:
        notRequired = new(memBlock) AsnNull(memBlock);
        *notRequired = *that.notRequired;
        break;
    }
  }

  return *this;
}

AsnLen
CallingDeviceID::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case deviceIdentifierCid:
      l = deviceIdentifier->BEncContent (b);
      break;

    case notKnownCid:
      l = notKnown->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 7);
      break;

    case notRequiredCid:
      l = notRequired->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 8);
      break;

  } // end switch
  return l;
} // CallingDeviceID::BEncContent


void CallingDeviceID::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (CNTX, PRIM, 0):
    case MAKE_TAG_ID (CNTX, CONS, 0):
    case MAKE_TAG_ID (CNTX, PRIM, 1):
    case MAKE_TAG_ID (CNTX, PRIM, 2):
    case MAKE_TAG_ID (CNTX, CONS, 2):
    case MAKE_TAG_ID (CNTX, CONS, 3):
    case MAKE_TAG_ID (CNTX, PRIM, 4):
    case MAKE_TAG_ID (CNTX, CONS, 4):
    case MAKE_TAG_ID (CNTX, CONS, 5):
    case MAKE_TAG_ID (CNTX, PRIM, 6):
    case MAKE_TAG_ID (CNTX, CONS, 6):
      choiceId = deviceIdentifierCid;
      deviceIdentifier = new(memBlock) ExtendedDeviceID(memBlock);
        deviceIdentifier->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 7):
      choiceId = notKnownCid;
      notKnown = new(memBlock) AsnNull(memBlock);
        notKnown->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 8):
      choiceId = notRequiredCid;
      notRequired = new(memBlock) AsnNull(memBlock);
        notRequired->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0152: Unexpected tag in CHOICE";
      break;
  } // end switch
} // CallingDeviceID::BDecContent


AsnLen CallingDeviceID::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    l += BEncConsLen (b, l);
    l += BEncTag1 (b, APPL, CONS, 1);
    return l;
}

void CallingDeviceID::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;
    AsnLen extraLen1;

    if (BDecTag (b, bytesDecoded) != MAKE_TAG_ID (APPL, CONS, 1))    {
        throw "ERROR C0153: CallingDeviceID.BDec(): Wrong tag";
    }
    extraLen1 = BDecLen (b, bytesDecoded);
    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
    if (extraLen1 == INDEFINITE_LEN)
        BDecEoc (b, bytesDecoded);
}

int CallingDeviceID::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int CallingDeviceID::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void CallingDeviceID::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case deviceIdentifierCid: os << "ExtendedDeviceID*"; break;
    case notKnownCid: os << "AsnNull*"; break;
    case notRequiredCid: os << "AsnNull*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case deviceIdentifierCid:
      os << "deviceIdentifier : ";
      if (deviceIdentifier)
        os << *deviceIdentifier;
      else
        os << "VOID";
      break;

    case notKnownCid:
      os << "notKnown : ";
      if (notKnown)
        os << *notKnown;
      else
        os << "VOID";
      break;

    case notRequiredCid:
      os << "notRequired : ";
      if (notRequired)
        os << *notRequired;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // CallingDeviceID::Print

CalledDeviceID::CalledDeviceID( MemBlock* mb ) : AsnType( mb )
{
  choiceId = deviceIdentifierCid;
  deviceIdentifier = NULL; // incomplete initialization of mandatory element!
}

CalledDeviceID::CalledDeviceID( MemBlock* mb, const CalledDeviceID & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined CalledDeviceID::CalledDeviceID (const CalledDeviceID &)";
  abort();
}

CalledDeviceID::~CalledDeviceID()
{
} // end of destructor

AsnType *CalledDeviceID::Clone() const
{
  return new(memBlock) CalledDeviceID(memBlock);
}

CalledDeviceID &CalledDeviceID::operator = (const CalledDeviceID &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case deviceIdentifierCid:
        deviceIdentifier = new(memBlock) ExtendedDeviceID(memBlock);
        *deviceIdentifier = *that.deviceIdentifier;
        break;
      case notKnownCid:
        notKnown = new(memBlock) AsnNull(memBlock);
        *notKnown = *that.notKnown;
        break;
      case notRequiredCid:
        notRequired = new(memBlock) AsnNull(memBlock);
        *notRequired = *that.notRequired;
        break;
    }
  }

  return *this;
}

AsnLen
CalledDeviceID::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case deviceIdentifierCid:
      l = deviceIdentifier->BEncContent (b);
      break;

    case notKnownCid:
      l = notKnown->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 7);
      break;

    case notRequiredCid:
      l = notRequired->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 8);
      break;

  } // end switch
  return l;
} // CalledDeviceID::BEncContent


void CalledDeviceID::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (CNTX, PRIM, 0):
    case MAKE_TAG_ID (CNTX, CONS, 0):
    case MAKE_TAG_ID (CNTX, PRIM, 1):
    case MAKE_TAG_ID (CNTX, PRIM, 2):
    case MAKE_TAG_ID (CNTX, CONS, 2):
    case MAKE_TAG_ID (CNTX, CONS, 3):
    case MAKE_TAG_ID (CNTX, PRIM, 4):
    case MAKE_TAG_ID (CNTX, CONS, 4):
    case MAKE_TAG_ID (CNTX, CONS, 5):
    case MAKE_TAG_ID (CNTX, PRIM, 6):
    case MAKE_TAG_ID (CNTX, CONS, 6):
      choiceId = deviceIdentifierCid;
      deviceIdentifier = new(memBlock) ExtendedDeviceID(memBlock);
        deviceIdentifier->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 7):
      choiceId = notKnownCid;
      notKnown = new(memBlock) AsnNull(memBlock);
        notKnown->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 8):
      choiceId = notRequiredCid;
      notRequired = new(memBlock) AsnNull(memBlock);
        notRequired->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0154: Unexpected tag in CHOICE";
      break;
  } // end switch
} // CalledDeviceID::BDecContent


AsnLen CalledDeviceID::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    l += BEncConsLen (b, l);
    l += BEncTag1 (b, APPL, CONS, 2);
    return l;
}

void CalledDeviceID::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;
    AsnLen extraLen1;

    if (BDecTag (b, bytesDecoded) != MAKE_TAG_ID (APPL, CONS, 2))    {
        throw "ERROR C0155: CalledDeviceID.BDec(): Wrong tag";
    }
    extraLen1 = BDecLen (b, bytesDecoded);
    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
    if (extraLen1 == INDEFINITE_LEN)
        BDecEoc (b, bytesDecoded);
}

int CalledDeviceID::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int CalledDeviceID::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void CalledDeviceID::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case deviceIdentifierCid: os << "ExtendedDeviceID*"; break;
    case notKnownCid: os << "AsnNull*"; break;
    case notRequiredCid: os << "AsnNull*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case deviceIdentifierCid:
      os << "deviceIdentifier : ";
      if (deviceIdentifier)
        os << *deviceIdentifier;
      else
        os << "VOID";
      break;

    case notKnownCid:
      os << "notKnown : ";
      if (notKnown)
        os << *notKnown;
      else
        os << "VOID";
      break;

    case notRequiredCid:
      os << "notRequired : ";
      if (notRequired)
        os << *notRequired;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // CalledDeviceID::Print

SubjectDeviceID::SubjectDeviceID( MemBlock* mb ) : AsnType( mb )
{
  choiceId = deviceIdentifierCid;
  deviceIdentifier = NULL; // incomplete initialization of mandatory element!
}

SubjectDeviceID::SubjectDeviceID( MemBlock* mb, const SubjectDeviceID & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined SubjectDeviceID::SubjectDeviceID (const SubjectDeviceID &)";
  abort();
}

SubjectDeviceID::~SubjectDeviceID()
{
} // end of destructor

AsnType *SubjectDeviceID::Clone() const
{
  return new(memBlock) SubjectDeviceID(memBlock);
}

SubjectDeviceID &SubjectDeviceID::operator = (const SubjectDeviceID &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case deviceIdentifierCid:
        deviceIdentifier = new(memBlock) ExtendedDeviceID(memBlock);
        *deviceIdentifier = *that.deviceIdentifier;
        break;
      case notKnownCid:
        notKnown = new(memBlock) AsnNull(memBlock);
        *notKnown = *that.notKnown;
        break;
      case notRequiredCid:
        notRequired = new(memBlock) AsnNull(memBlock);
        *notRequired = *that.notRequired;
        break;
    }
  }

  return *this;
}

AsnLen
SubjectDeviceID::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case deviceIdentifierCid:
      l = deviceIdentifier->BEncContent (b);
      break;

    case notKnownCid:
      l = notKnown->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 7);
      break;

    case notRequiredCid:
      l = notRequired->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 8);
      break;

  } // end switch
  return l;
} // SubjectDeviceID::BEncContent


void SubjectDeviceID::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (CNTX, PRIM, 0):
    case MAKE_TAG_ID (CNTX, CONS, 0):
    case MAKE_TAG_ID (CNTX, PRIM, 1):
    case MAKE_TAG_ID (CNTX, PRIM, 2):
    case MAKE_TAG_ID (CNTX, CONS, 2):
    case MAKE_TAG_ID (CNTX, CONS, 3):
    case MAKE_TAG_ID (CNTX, PRIM, 4):
    case MAKE_TAG_ID (CNTX, CONS, 4):
    case MAKE_TAG_ID (CNTX, CONS, 5):
    case MAKE_TAG_ID (CNTX, PRIM, 6):
    case MAKE_TAG_ID (CNTX, CONS, 6):
      choiceId = deviceIdentifierCid;
      deviceIdentifier = new(memBlock) ExtendedDeviceID(memBlock);
        deviceIdentifier->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 7):
      choiceId = notKnownCid;
      notKnown = new(memBlock) AsnNull(memBlock);
        notKnown->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 8):
      choiceId = notRequiredCid;
      notRequired = new(memBlock) AsnNull(memBlock);
        notRequired->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0156: Unexpected tag in CHOICE";
      break;
  } // end switch
} // SubjectDeviceID::BDecContent


AsnLen SubjectDeviceID::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    l += BEncConsLen (b, l);
    l += BEncTag1 (b, APPL, CONS, 3);
    return l;
}

void SubjectDeviceID::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;
    AsnLen extraLen1;

    if (BDecTag (b, bytesDecoded) != MAKE_TAG_ID (APPL, CONS, 3))    {
        throw "ERROR C0157: SubjectDeviceID.BDec(): Wrong tag";
    }
    extraLen1 = BDecLen (b, bytesDecoded);
    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
    if (extraLen1 == INDEFINITE_LEN)
        BDecEoc (b, bytesDecoded);
}

int SubjectDeviceID::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int SubjectDeviceID::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void SubjectDeviceID::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case deviceIdentifierCid: os << "ExtendedDeviceID*"; break;
    case notKnownCid: os << "AsnNull*"; break;
    case notRequiredCid: os << "AsnNull*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case deviceIdentifierCid:
      os << "deviceIdentifier : ";
      if (deviceIdentifier)
        os << *deviceIdentifier;
      else
        os << "VOID";
      break;

    case notKnownCid:
      os << "notKnown : ";
      if (notKnown)
        os << *notKnown;
      else
        os << "VOID";
      break;

    case notRequiredCid:
      os << "notRequired : ";
      if (notRequired)
        os << *notRequired;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // SubjectDeviceID::Print

RedirectionDeviceID::RedirectionDeviceID( MemBlock* mb ) : AsnType( mb )
{
  choiceId = numberDialedCid;
  numberDialed = NULL; // incomplete initialization of mandatory element!
}

RedirectionDeviceID::RedirectionDeviceID( MemBlock* mb, const RedirectionDeviceID & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined RedirectionDeviceID::RedirectionDeviceID (const RedirectionDeviceID &)";
  abort();
}

RedirectionDeviceID::~RedirectionDeviceID()
{
} // end of destructor

AsnType *RedirectionDeviceID::Clone() const
{
  return new(memBlock) RedirectionDeviceID(memBlock);
}

RedirectionDeviceID &RedirectionDeviceID::operator = (const RedirectionDeviceID &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case numberDialedCid:
        numberDialed = new(memBlock) DeviceID(memBlock);
        *numberDialed = *that.numberDialed;
        break;
      case notKnownCid:
        notKnown = new(memBlock) AsnNull(memBlock);
        *notKnown = *that.notKnown;
        break;
      case notRequiredCid:
        notRequired = new(memBlock) AsnNull(memBlock);
        *notRequired = *that.notRequired;
        break;
    }
  }

  return *this;
}

AsnLen
RedirectionDeviceID::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case numberDialedCid:
      l = numberDialed->BEncContent (b);
      break;

    case notKnownCid:
      l = notKnown->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 7);
      break;

    case notRequiredCid:
      l = notRequired->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 8);
      break;

  } // end switch
  return l;
} // RedirectionDeviceID::BEncContent


void RedirectionDeviceID::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (CNTX, PRIM, 0):
    case MAKE_TAG_ID (CNTX, CONS, 0):
    case MAKE_TAG_ID (CNTX, PRIM, 1):
      choiceId = numberDialedCid;
      numberDialed = new(memBlock) DeviceID(memBlock);
        numberDialed->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 7):
      choiceId = notKnownCid;
      notKnown = new(memBlock) AsnNull(memBlock);
        notKnown->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 8):
      choiceId = notRequiredCid;
      notRequired = new(memBlock) AsnNull(memBlock);
        notRequired->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0158: Unexpected tag in CHOICE";
      break;
  } // end switch
} // RedirectionDeviceID::BDecContent


AsnLen RedirectionDeviceID::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    l += BEncConsLen (b, l);
    l += BEncTag1 (b, APPL, CONS, 4);
    return l;
}

void RedirectionDeviceID::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;
    AsnLen extraLen1;

    if (BDecTag (b, bytesDecoded) != MAKE_TAG_ID (APPL, CONS, 4))    {
        throw "ERROR C0159: RedirectionDeviceID.BDec(): Wrong tag";
    }
    extraLen1 = BDecLen (b, bytesDecoded);
    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
    if (extraLen1 == INDEFINITE_LEN)
        BDecEoc (b, bytesDecoded);
}

int RedirectionDeviceID::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int RedirectionDeviceID::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void RedirectionDeviceID::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case numberDialedCid: os << "DeviceID*"; break;
    case notKnownCid: os << "AsnNull*"; break;
    case notRequiredCid: os << "AsnNull*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case numberDialedCid:
      os << "numberDialed : ";
      if (numberDialed)
        os << *numberDialed;
      else
        os << "VOID";
      break;

    case notKnownCid:
      os << "notKnown : ";
      if (notKnown)
        os << *notKnown;
      else
        os << "VOID";
      break;

    case notRequiredCid:
      os << "notRequired : ";
      if (notRequired)
        os << *notRequired;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // RedirectionDeviceID::Print

MonitorFilter::MonitorFilter( MemBlock* mb ) : AsnType( mb )
{
  call = NULL;
  feature = NULL;
  agent = NULL;
  maintenance = NULL;
  private1 = NULL;
}

MonitorFilter::MonitorFilter( MemBlock* mb, const MonitorFilter & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined MonitorFilter::MonitorFilter (const MonitorFilter &)";
  abort();
}

MonitorFilter::~MonitorFilter()
{
}

AsnType *MonitorFilter::Clone() const
{
  return new(memBlock) MonitorFilter(memBlock);
}

MonitorFilter &MonitorFilter::operator = (const MonitorFilter &that)
{
  if (this != &that)
  {
    if (that.call)
    {
      if (!call)
        call = new(memBlock) CallFilter(memBlock);
      *call = *that.call;
    }
    else
    {
      call = NULL;
    }
    if (that.feature)
    {
      if (!feature)
        feature = new(memBlock) FeatureFilter(memBlock);
      *feature = *that.feature;
    }
    else
    {
      feature = NULL;
    }
    if (that.agent)
    {
      if (!agent)
        agent = new(memBlock) AgentFilter(memBlock);
      *agent = *that.agent;
    }
    else
    {
      agent = NULL;
    }
    if (that.maintenance)
    {
      if (!maintenance)
        maintenance = new(memBlock) MaintenanceFilter(memBlock);
      *maintenance = *that.maintenance;
    }
    else
    {
      maintenance = NULL;
    }
    if (that.private1)
    {
      if (!private1)
        private1 = new(memBlock) AsnBool(memBlock);
      *private1 = *that.private1;
    }
    else
    {
      private1 = NULL;
    }
  }

  return *this;
}

AsnLen
MonitorFilter::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (private1))
  {
    l = private1->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 4);
    totalLen += l;
  }

  if (NOT_NULL (maintenance))
  {
    l = maintenance->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 3);
    totalLen += l;
  }

  if (NOT_NULL (agent))
  {
    l = agent->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 2);
    totalLen += l;
  }

  if (NOT_NULL (feature))
  {
    l = feature->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 1);
    totalLen += l;
  }

  if (NOT_NULL (call))
  {
    l = call->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 0);
    totalLen += l;
  }

  return totalLen;
} // MonitorFilter::BEncContent


void MonitorFilter::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  if (elmtLen0 == 0)
    return;
  else
  {
    tag1 = BDecTag (b, seqBytesDecoded);

    if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
    {
      BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
      bytesDecoded += seqBytesDecoded;
      return;
    }
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 0)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    call = new(memBlock) CallFilter(memBlock);
    call->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 1))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 1)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    feature = new(memBlock) FeatureFilter(memBlock);
    feature->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 2))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 2)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    agent = new(memBlock) AgentFilter(memBlock);
    agent->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 3))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 3)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    maintenance = new(memBlock) MaintenanceFilter(memBlock);
    maintenance->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 4)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    private1 = new(memBlock) AsnBool(memBlock);
    private1->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0160: Length discrepancy on sequence.";
  }
  else
    return;
} // MonitorFilter::BDecContent

AsnLen MonitorFilter::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void MonitorFilter::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135073976: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int MonitorFilter::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int MonitorFilter::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void MonitorFilter::Print ( CTsvcLIB::LOG& os ) const
{
  os << "MonitorFilter SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "call : ";
  if (NOT_NULL (call))
    os << *call;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "feature : ";
  if (NOT_NULL (feature))
    os << *feature;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "agent : ";
  if (NOT_NULL (agent))
    os << *agent;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "maintenance : ";
  if (NOT_NULL (maintenance))
    os << *maintenance;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "private : ";
  if (NOT_NULL (private1))
    os << *private1;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // MonitorFilter::Print


AsnType *CompoundCallState::Clone() const
{
  return new(memBlock) CompoundCallState(memBlock);
}

AsnLen CompoundCallState::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void CompoundCallState::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C0161: CompoundCallState.BDec(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

CompoundCallState::CompoundCallState( MemBlock* mb, const CompoundCallState & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined CompoundCallState::CompoundCallState (const CompoundCallState &)";
  abort();
}

CompoundCallState::~CompoundCallState()
{
  SetCurrToFirst();
  for (; Curr() != NULL; RemoveCurrFromList())
    ;
} // end of destructor

CompoundCallState &CompoundCallState::operator = (const CompoundCallState &that)
{
  if (this != &that)
  {
    SetCurrToFirst();
    for (; Curr(); RemoveCurrFromList())
      ;

    //that.SetCurrToFirst();
    //for (; that.Curr(); that.GoNext())
    //  AppendCopy (*that.Curr());
    for (const AsnListElmt *run=that.first; run; run=run->next)
      AppendCopy (*run->elmt);
  }

  return *this;
}

void CompoundCallState::Print ( CTsvcLIB::LOG& os ) const
{
    os << "CompoundCallState SEQUENCE/SET OF" << CTsvcLIB::eline;
    Indent (os, indentG);
    os << "{" << CTsvcLIB::eline;
    indentG += stdIndentG;
    for (const AsnListElmt *run=first; run; run=run->next)
    {
        Indent (os, indentG);
        os << *run->elmt;
        if (run != last)
            os << ",";
        os << CTsvcLIB::eline;
    }
    indentG -= stdIndentG;
    Indent (os, indentG);
    os << "}";
} // Print


void  CompoundCallState::SetCurrElmt (unsigned long int index)
{
  unsigned long int i;
  curr = first;
  if (count)
    for (i = 0; (i < (count-1)) && (i < index); i++)
      curr = curr->next;
} // CompoundCallState::SetCurrElmt


unsigned long int  CompoundCallState::GetCurrElmtIndex()
{
    unsigned long int i;
    AsnListElmt *tmp;
    if (curr != NULL)
    {
        for (i = 0, tmp = first; tmp != NULL; i++)
        {
            if (tmp == curr)
                return i;
            else
                tmp = tmp->next;
        }
    }
    return count;
} // CompoundCallState::GetCurrElmtIndex


// alloc new list elmt, put at end of list
//  and return the component type
LocalConnectionState *CompoundCallState::Append()
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt  = new(memBlock) LocalConnectionState(memBlock);
    newElmt->next = NULL;
    if (last == NULL)
    {
        newElmt->prev = NULL;
        first = last  = newElmt;
    }
    else
    {
        newElmt->prev = last;
        last->next    = newElmt;
        last          = newElmt;
    }
    count++;
    return (curr = newElmt)->elmt;
} // CompoundCallState::Append


// alloc new list elmt, put at begining of list
//  and return the component type
LocalConnectionState  *CompoundCallState::Prepend()
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) LocalConnectionState(memBlock);
    newElmt->prev = NULL;
    if (first == NULL)
    {
        newElmt->next = NULL;
        first = last  = newElmt;
    }
    else
    {
        newElmt->next = first;
        first->prev   = newElmt;
        first         = newElmt;
    }
    count++;
    return (curr = newElmt)->elmt;
} // CompoundCallState::Prepend


// alloc new list elmt, insert it before the
// current element and return the component type
// if the current element is null, the new element
// is placed at the beginning of the list.
LocalConnectionState  *CompoundCallState::InsertBefore()
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) LocalConnectionState(memBlock);
    if (curr == NULL)
    {
        newElmt->next = first;
        newElmt->prev = NULL;
        first = newElmt;
        if (last == NULL)
            last = newElmt;
    }
    else
    {
        newElmt->next = curr;
        newElmt->prev = curr->prev;
        curr->prev = newElmt;
        if (curr == first)
            first = newElmt;
        else
            newElmt->prev->next = newElmt;
    }
    count++;
    return (curr = newElmt)->elmt;
} // CompoundCallState::InsertBefore


// alloc new list elmt, insert it after the
// current element and return the component type
// if the current element is null, the new element
// is placed at the end of the list.
LocalConnectionState *CompoundCallState::InsertAfter()
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) LocalConnectionState(memBlock);
    if (curr == NULL)
    {
        newElmt->prev = last;
        newElmt->next = NULL;
        last = newElmt;
        if (first == NULL)
            first = newElmt;
    }
    else
    {
        newElmt->prev = curr;
        newElmt->next = curr->next;
        curr->next = newElmt;
        if (curr == last)
            last = newElmt;
        else
            newElmt->next->prev = newElmt;
    }
    count++;
    return (curr = newElmt)->elmt;
} // CompoundCallState::InsertAfter


CompoundCallState  &CompoundCallState::AppendCopy (LocalConnectionState &elmt)
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) LocalConnectionState(memBlock);
    *newElmt->elmt = elmt;
    newElmt->next = NULL;
    if (last == NULL)
    {
        newElmt->prev = NULL;
        first = last  = newElmt;
    }
    else
    {
        newElmt->prev = last;
        last->next    = newElmt;
        last          = newElmt;
    }
    count++;
    return *this;
} // AppendCopy


CompoundCallState  &CompoundCallState::PrependCopy (LocalConnectionState &elmt)
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) LocalConnectionState(memBlock);
    *newElmt->elmt = elmt;
    newElmt->prev = NULL;
    if (first == NULL)
    {
        newElmt->next = NULL;
        first = last  = newElmt;
    }
    else
    {
        newElmt->next = first;
        first->prev   = newElmt;
        first         = newElmt;
    }
    count++;
    return *this;
} // CompoundCallState::PrependCopy


// alloc new list elmt, insert it before the
// current element, copy the given elmt into the new elmt
// and return the component type.
// if the current element is null, the new element
// is placed at the beginning of the list.
CompoundCallState &CompoundCallState::InsertBeforeAndCopy (LocalConnectionState &elmt)
{
    AsnListElmt *newElmt;

    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) LocalConnectionState(memBlock);
    *newElmt->elmt = elmt;

    if (curr == NULL)
    {
        newElmt->next = first;
        newElmt->prev = NULL;
        first = newElmt;
        if (last == NULL)
            last = newElmt;
    }
    else
    {
        newElmt->next = curr;
        newElmt->prev = curr->prev;
        curr->prev = newElmt;
        if (curr == first)
            first = newElmt;
        else
            newElmt->prev->next = newElmt;
    }
    count++;
    return *this;
} // CompoundCallState::InsertBeforeAndCopy


// alloc new list elmt, insert it after the
// current element, copy given elmt in to new elmt
//  and return the component type
// if the current element is null, the new element
// is placed at the end of the list.
CompoundCallState  &CompoundCallState::InsertAfterAndCopy (LocalConnectionState &elmt)
{
    AsnListElmt *newElmt;

    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) LocalConnectionState(memBlock);
    *newElmt->elmt = elmt;
    if (curr == NULL)
    {
        newElmt->prev = last;
        newElmt->next = NULL;
        last = newElmt;
        if (first == NULL)
            first = newElmt;
    }
    else
    {
        newElmt->prev = curr;
        newElmt->next = curr->next;
        curr->next = newElmt;
        if (curr == last)
            last = newElmt;
        else
            newElmt->next->prev = newElmt;
    }
    count++;
    return *this;
} // CompoundCallState::InsertAfterAndCopy


// remove current element from list if current element is not NULL 
// The new current element will be the next element.
// If the current element is the last element in the list
// the second but last element will become the new current element.
void CompoundCallState::RemoveCurrFromList()
{
    AsnListElmt *del_elmt;

    if (curr != NULL)
    {
        del_elmt = curr;
        count--;

        if (count == 0)
            first = last = curr = NULL;
        else if (curr == first)
        {
            curr = first= first->next;
            first->prev = NULL;
        }
        else if (curr == last)
        {
            curr = last = last->prev;
            last->next = NULL;
        }
        else
        {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
        }

    }
}


AsnLen CompoundCallState::BEncContent (AsnBuf& b)
{
    AsnListElmt *currElmt;
    AsnLen elmtLen;
    AsnLen totalLen = 0;
    for (currElmt = last; currElmt != NULL; currElmt = currElmt->prev)
    {
        elmtLen = currElmt->elmt->BEncContent (b);
    BEncDefLenTo127 (b, elmtLen);
    elmtLen++;

    elmtLen += BEncTag1 (b, APPL, PRIM, 14);
        totalLen += elmtLen;
    }
    return totalLen;
} // CompoundCallState::BEncContent


void  CompoundCallState::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0,
                                  AsnLen &bytesDecoded)
{
    LocalConnectionState *listElmt;
    AsnTag tag1;
    AsnLen listBytesDecoded = 0;
    AsnLen elmtLen1;

    while ((listBytesDecoded < elmtLen0) || (elmtLen0 == INDEFINITE_LEN))
    {
        tag1 = BDecTag (b, listBytesDecoded);
        if ((tag1 == EOC_TAG_ID) && (elmtLen0 == INDEFINITE_LEN))
        {
            BDEC_2ND_EOC_OCTET (b, listBytesDecoded);
            break;
        }
        if ((tag1 != MAKE_TAG_ID (APPL, PRIM, 14) ))
        {
            throw "ERROR C0162: Unexpected Tag";
        }

        elmtLen1 = BDecLen (b, listBytesDecoded);
        listElmt = Append();
        listElmt->BDecContent (b, tag1, elmtLen1, listBytesDecoded);
    }

    bytesDecoded += listBytesDecoded;
} // CompoundCallState::BDecContent


DeviceInfo::DeviceInfo( MemBlock* mb ) : AsnType( mb )
{
  deviceID = NULL;
  deviceType = NULL;
  deviceClass = NULL;
}

DeviceInfo::DeviceInfo( MemBlock* mb, const DeviceInfo & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined DeviceInfo::DeviceInfo (const DeviceInfo &)";
  abort();
}

DeviceInfo::~DeviceInfo()
{
}

AsnType *DeviceInfo::Clone() const
{
  return new(memBlock) DeviceInfo(memBlock);
}

DeviceInfo &DeviceInfo::operator = (const DeviceInfo &that)
{
  if (this != &that)
  {
    if (that.deviceID)
    {
      if (!deviceID)
        deviceID = new(memBlock) DeviceID(memBlock);
      *deviceID = *that.deviceID;
    }
    else
    {
      deviceID = NULL;
    }
    if (that.deviceType)
    {
      if (!deviceType)
        deviceType = new(memBlock) DeviceType(memBlock);
      *deviceType = *that.deviceType;
    }
    else
    {
      deviceType = NULL;
    }
    if (that.deviceClass)
    {
      if (!deviceClass)
        deviceClass = new(memBlock) DeviceClass(memBlock);
      *deviceClass = *that.deviceClass;
    }
    else
    {
      deviceClass = NULL;
    }
  }

  return *this;
}

AsnLen
DeviceInfo::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (deviceClass))
  {
    l = deviceClass->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, UNIV, PRIM, BITSTRING_TAG_CODE);
    totalLen += l;
  }

  if (NOT_NULL (deviceType))
  {
    l = deviceType->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, ENUM_TAG_CODE);
    totalLen += l;
  }

  if (NOT_NULL (deviceID))
  {
    l = deviceID->BEncContent (b);
    totalLen += l;
  }

  return totalLen;
} // DeviceInfo::BEncContent


void DeviceInfo::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  if (elmtLen0 == 0)
    return;
  else
  {
    tag1 = BDecTag (b, seqBytesDecoded);

    if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
    {
      BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
      bytesDecoded += seqBytesDecoded;
      return;
    }
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 1)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    deviceID = new(memBlock) DeviceID(memBlock);
    deviceID->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, ENUM_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    deviceType = new(memBlock) DeviceType(memBlock);
    deviceType->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, BITSTRING_TAG_CODE))
    || (tag1 == MAKE_TAG_ID (UNIV, CONS, BITSTRING_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    deviceClass = new(memBlock) DeviceClass(memBlock);
    deviceClass->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0163: Length discrepancy on sequence.";
  }
  else
    return;
} // DeviceInfo::BDecContent

AsnLen DeviceInfo::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void DeviceInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135075776: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int DeviceInfo::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int DeviceInfo::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void DeviceInfo::Print ( CTsvcLIB::LOG& os ) const
{
  os << "DeviceInfo SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "deviceID : ";
  if (NOT_NULL (deviceID))
    os << *deviceID;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "deviceType : ";
  if (NOT_NULL (deviceType))
    os << *deviceType;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "deviceClass : ";
  if (NOT_NULL (deviceClass))
    os << *deviceClass;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // DeviceInfo::Print


AsnType *ListForwardParameters::Clone() const
{
  return new(memBlock) ListForwardParameters(memBlock);
}

AsnLen ListForwardParameters::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void ListForwardParameters::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C0164: ListForwardParameters.BDec(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

ListForwardParameters::ListForwardParameters( MemBlock* mb, const ListForwardParameters & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined ListForwardParameters::ListForwardParameters (const ListForwardParameters &)";
  abort();
}

ListForwardParameters::~ListForwardParameters()
{
  SetCurrToFirst();
  for (; Curr() != NULL; RemoveCurrFromList())
    ;
} // end of destructor

ListForwardParameters &ListForwardParameters::operator = (const ListForwardParameters &that)
{
  if (this != &that)
  {
    SetCurrToFirst();
    for (; Curr(); RemoveCurrFromList())
      ;

    //that.SetCurrToFirst();
    //for (; that.Curr(); that.GoNext())
    //  AppendCopy (*that.Curr());
    for (const AsnListElmt *run=that.first; run; run=run->next)
      AppendCopy (*run->elmt);
  }

  return *this;
}

void ListForwardParameters::Print ( CTsvcLIB::LOG& os ) const
{
    os << "ListForwardParameters SEQUENCE/SET OF" << CTsvcLIB::eline;
    Indent (os, indentG);
    os << "{" << CTsvcLIB::eline;
    indentG += stdIndentG;
    for (const AsnListElmt *run=first; run; run=run->next)
    {
        Indent (os, indentG);
        os << *run->elmt;
        if (run != last)
            os << ",";
        os << CTsvcLIB::eline;
    }
    indentG -= stdIndentG;
    Indent (os, indentG);
    os << "}";
} // Print


void  ListForwardParameters::SetCurrElmt (unsigned long int index)
{
  unsigned long int i;
  curr = first;
  if (count)
    for (i = 0; (i < (count-1)) && (i < index); i++)
      curr = curr->next;
} // ListForwardParameters::SetCurrElmt


unsigned long int  ListForwardParameters::GetCurrElmtIndex()
{
    unsigned long int i;
    AsnListElmt *tmp;
    if (curr != NULL)
    {
        for (i = 0, tmp = first; tmp != NULL; i++)
        {
            if (tmp == curr)
                return i;
            else
                tmp = tmp->next;
        }
    }
    return count;
} // ListForwardParameters::GetCurrElmtIndex


// alloc new list elmt, put at end of list
//  and return the component type
ListForwardParametersSeq *ListForwardParameters::Append()
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt  = new(memBlock) ListForwardParametersSeq(memBlock);
    newElmt->next = NULL;
    if (last == NULL)
    {
        newElmt->prev = NULL;
        first = last  = newElmt;
    }
    else
    {
        newElmt->prev = last;
        last->next    = newElmt;
        last          = newElmt;
    }
    count++;
    return (curr = newElmt)->elmt;
} // ListForwardParameters::Append


// alloc new list elmt, put at begining of list
//  and return the component type
ListForwardParametersSeq  *ListForwardParameters::Prepend()
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) ListForwardParametersSeq(memBlock);
    newElmt->prev = NULL;
    if (first == NULL)
    {
        newElmt->next = NULL;
        first = last  = newElmt;
    }
    else
    {
        newElmt->next = first;
        first->prev   = newElmt;
        first         = newElmt;
    }
    count++;
    return (curr = newElmt)->elmt;
} // ListForwardParameters::Prepend


// alloc new list elmt, insert it before the
// current element and return the component type
// if the current element is null, the new element
// is placed at the beginning of the list.
ListForwardParametersSeq  *ListForwardParameters::InsertBefore()
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) ListForwardParametersSeq(memBlock);
    if (curr == NULL)
    {
        newElmt->next = first;
        newElmt->prev = NULL;
        first = newElmt;
        if (last == NULL)
            last = newElmt;
    }
    else
    {
        newElmt->next = curr;
        newElmt->prev = curr->prev;
        curr->prev = newElmt;
        if (curr == first)
            first = newElmt;
        else
            newElmt->prev->next = newElmt;
    }
    count++;
    return (curr = newElmt)->elmt;
} // ListForwardParameters::InsertBefore


// alloc new list elmt, insert it after the
// current element and return the component type
// if the current element is null, the new element
// is placed at the end of the list.
ListForwardParametersSeq *ListForwardParameters::InsertAfter()
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) ListForwardParametersSeq(memBlock);
    if (curr == NULL)
    {
        newElmt->prev = last;
        newElmt->next = NULL;
        last = newElmt;
        if (first == NULL)
            first = newElmt;
    }
    else
    {
        newElmt->prev = curr;
        newElmt->next = curr->next;
        curr->next = newElmt;
        if (curr == last)
            last = newElmt;
        else
            newElmt->next->prev = newElmt;
    }
    count++;
    return (curr = newElmt)->elmt;
} // ListForwardParameters::InsertAfter


ListForwardParameters  &ListForwardParameters::AppendCopy (ListForwardParametersSeq &elmt)
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) ListForwardParametersSeq(memBlock);
    *newElmt->elmt = elmt;
    newElmt->next = NULL;
    if (last == NULL)
    {
        newElmt->prev = NULL;
        first = last  = newElmt;
    }
    else
    {
        newElmt->prev = last;
        last->next    = newElmt;
        last          = newElmt;
    }
    count++;
    return *this;
} // AppendCopy


ListForwardParameters  &ListForwardParameters::PrependCopy (ListForwardParametersSeq &elmt)
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) ListForwardParametersSeq(memBlock);
    *newElmt->elmt = elmt;
    newElmt->prev = NULL;
    if (first == NULL)
    {
        newElmt->next = NULL;
        first = last  = newElmt;
    }
    else
    {
        newElmt->next = first;
        first->prev   = newElmt;
        first         = newElmt;
    }
    count++;
    return *this;
} // ListForwardParameters::PrependCopy


// alloc new list elmt, insert it before the
// current element, copy the given elmt into the new elmt
// and return the component type.
// if the current element is null, the new element
// is placed at the beginning of the list.
ListForwardParameters &ListForwardParameters::InsertBeforeAndCopy (ListForwardParametersSeq &elmt)
{
    AsnListElmt *newElmt;

    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) ListForwardParametersSeq(memBlock);
    *newElmt->elmt = elmt;

    if (curr == NULL)
    {
        newElmt->next = first;
        newElmt->prev = NULL;
        first = newElmt;
        if (last == NULL)
            last = newElmt;
    }
    else
    {
        newElmt->next = curr;
        newElmt->prev = curr->prev;
        curr->prev = newElmt;
        if (curr == first)
            first = newElmt;
        else
            newElmt->prev->next = newElmt;
    }
    count++;
    return *this;
} // ListForwardParameters::InsertBeforeAndCopy


// alloc new list elmt, insert it after the
// current element, copy given elmt in to new elmt
//  and return the component type
// if the current element is null, the new element
// is placed at the end of the list.
ListForwardParameters  &ListForwardParameters::InsertAfterAndCopy (ListForwardParametersSeq &elmt)
{
    AsnListElmt *newElmt;

    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) ListForwardParametersSeq(memBlock);
    *newElmt->elmt = elmt;
    if (curr == NULL)
    {
        newElmt->prev = last;
        newElmt->next = NULL;
        last = newElmt;
        if (first == NULL)
            first = newElmt;
    }
    else
    {
        newElmt->prev = curr;
        newElmt->next = curr->next;
        curr->next = newElmt;
        if (curr == last)
            last = newElmt;
        else
            newElmt->next->prev = newElmt;
    }
    count++;
    return *this;
} // ListForwardParameters::InsertAfterAndCopy


// remove current element from list if current element is not NULL 
// The new current element will be the next element.
// If the current element is the last element in the list
// the second but last element will become the new current element.
void ListForwardParameters::RemoveCurrFromList()
{
    AsnListElmt *del_elmt;

    if (curr != NULL)
    {
        del_elmt = curr;
        count--;

        if (count == 0)
            first = last = curr = NULL;
        else if (curr == first)
        {
            curr = first= first->next;
            first->prev = NULL;
        }
        else if (curr == last)
        {
            curr = last = last->prev;
            last->next = NULL;
        }
        else
        {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
        }

    }
}


AsnLen ListForwardParameters::BEncContent (AsnBuf& b)
{
    AsnListElmt *currElmt;
    AsnLen elmtLen;
    AsnLen totalLen = 0;
    for (currElmt = last; currElmt != NULL; currElmt = currElmt->prev)
    {
      BEncEocIfNec (b);
        elmtLen = currElmt->elmt->BEncContent (b);
    elmtLen += BEncConsLen (b, elmtLen);

    elmtLen += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
        totalLen += elmtLen;
    }
    return totalLen;
} // ListForwardParameters::BEncContent


void  ListForwardParameters::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0,
                                  AsnLen &bytesDecoded)
{
    ListForwardParametersSeq *listElmt;
    AsnTag tag1;
    AsnLen listBytesDecoded = 0;
    AsnLen elmtLen1;

    while ((listBytesDecoded < elmtLen0) || (elmtLen0 == INDEFINITE_LEN))
    {
        tag1 = BDecTag (b, listBytesDecoded);
        if ((tag1 == EOC_TAG_ID) && (elmtLen0 == INDEFINITE_LEN))
        {
            BDEC_2ND_EOC_OCTET (b, listBytesDecoded);
            break;
        }
        if ((tag1 != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE) ))
        {
            throw "ERROR C0165: Unexpected Tag";
        }

        elmtLen1 = BDecLen (b, listBytesDecoded);
        listElmt = Append();
        listElmt->BDecContent (b, tag1, elmtLen1, listBytesDecoded);
    }

    bytesDecoded += listBytesDecoded;
} // ListForwardParameters::BDecContent


LoggedOnInfo::LoggedOnInfo( MemBlock* mb ) : AsnType( mb )
{
  agentID = NULL;
  password = NULL;
  group = NULL;
}

LoggedOnInfo::LoggedOnInfo( MemBlock* mb, const LoggedOnInfo & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined LoggedOnInfo::LoggedOnInfo (const LoggedOnInfo &)";
  abort();
}

LoggedOnInfo::~LoggedOnInfo()
{
}

AsnType *LoggedOnInfo::Clone() const
{
  return new(memBlock) LoggedOnInfo(memBlock);
}

LoggedOnInfo &LoggedOnInfo::operator = (const LoggedOnInfo &that)
{
  if (this != &that)
  {
    if (that.agentID)
    {
      if (!agentID)
        agentID = new(memBlock) AgentID(memBlock);
      *agentID = *that.agentID;
    }
    else
    {
      agentID = NULL;
    }
    if (that.password)
    {
      if (!password)
        password = new(memBlock) AgentPassword(memBlock);
      *password = *that.password;
    }
    else
    {
      password = NULL;
    }
    if (that.group)
    {
      if (!group)
        group = new(memBlock) AgentGroup(memBlock);
      *group = *that.group;
    }
    else
    {
      group = NULL;
    }
  }

  return *this;
}

AsnLen
LoggedOnInfo::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (group))
  {
    l = group->BEncContent (b);
    totalLen += l;
  }

  if (NOT_NULL (password))
  {
    l = password->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 11);
    totalLen += l;
  }

  if (NOT_NULL (agentID))
  {
    l = agentID->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 10);
    totalLen += l;
  }

  return totalLen;
} // LoggedOnInfo::BEncContent


void LoggedOnInfo::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  if (elmtLen0 == 0)
    return;
  else
  {
    tag1 = BDecTag (b, seqBytesDecoded);

    if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
    {
      BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
      bytesDecoded += seqBytesDecoded;
      return;
    }
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 10))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 10)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    agentID = new(memBlock) AgentID(memBlock);
    agentID->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 11))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    password = new(memBlock) AgentPassword(memBlock);
    password->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 1)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    group = new(memBlock) AgentGroup(memBlock);
    group->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0166: Length discrepancy on sequence.";
  }
  else
    return;
} // LoggedOnInfo::BDecContent

AsnLen LoggedOnInfo::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void LoggedOnInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135076168: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int LoggedOnInfo::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int LoggedOnInfo::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void LoggedOnInfo::Print ( CTsvcLIB::LOG& os ) const
{
  os << "LoggedOnInfo SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "agentID : ";
  if (NOT_NULL (agentID))
    os << *agentID;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "password : ";
  if (NOT_NULL (password))
    os << *password;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "group : ";
  if (NOT_NULL (group))
    os << *group;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // LoggedOnInfo::Print


LoggedOffInfo::LoggedOffInfo( MemBlock* mb ) : AsnType( mb )
{
  agentID = NULL;
  group = NULL;
}

LoggedOffInfo::LoggedOffInfo( MemBlock* mb, const LoggedOffInfo & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined LoggedOffInfo::LoggedOffInfo (const LoggedOffInfo &)";
  abort();
}

LoggedOffInfo::~LoggedOffInfo()
{
}

AsnType *LoggedOffInfo::Clone() const
{
  return new(memBlock) LoggedOffInfo(memBlock);
}

LoggedOffInfo &LoggedOffInfo::operator = (const LoggedOffInfo &that)
{
  if (this != &that)
  {
    if (that.agentID)
    {
      if (!agentID)
        agentID = new(memBlock) AgentID(memBlock);
      *agentID = *that.agentID;
    }
    else
    {
      agentID = NULL;
    }
    if (that.group)
    {
      if (!group)
        group = new(memBlock) AgentGroup(memBlock);
      *group = *that.group;
    }
    else
    {
      group = NULL;
    }
  }

  return *this;
}

AsnLen
LoggedOffInfo::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (group))
  {
    l = group->BEncContent (b);
    totalLen += l;
  }

  if (NOT_NULL (agentID))
  {
    l = agentID->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 10);
    totalLen += l;
  }

  return totalLen;
} // LoggedOffInfo::BEncContent


void LoggedOffInfo::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  if (elmtLen0 == 0)
    return;
  else
  {
    tag1 = BDecTag (b, seqBytesDecoded);

    if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
    {
      BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
      bytesDecoded += seqBytesDecoded;
      return;
    }
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 10))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 10)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    agentID = new(memBlock) AgentID(memBlock);
    agentID->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 1)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    group = new(memBlock) AgentGroup(memBlock);
    group->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0167: Length discrepancy on sequence.";
  }
  else
    return;
} // LoggedOffInfo::BDecContent

AsnLen LoggedOffInfo::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void LoggedOffInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135076224: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int LoggedOffInfo::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int LoggedOffInfo::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void LoggedOffInfo::Print ( CTsvcLIB::LOG& os ) const
{
  os << "LoggedOffInfo SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "agentID : ";
  if (NOT_NULL (agentID))
    os << *agentID;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "group : ";
  if (NOT_NULL (group))
    os << *group;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // LoggedOffInfo::Print


ForwardParameter::ForwardParameter( MemBlock* mb ) : AsnType( mb )
    , forwardingType( mb )
{
  forwardDN = NULL;
}

ForwardParameter::ForwardParameter( MemBlock* mb, const ForwardParameter & ) : AsnType( mb )
    , forwardingType( mb )
{
  throw "ERROR C0099: Use of incompletely defined ForwardParameter::ForwardParameter (const ForwardParameter &)";
  abort();
}

ForwardParameter::~ForwardParameter()
{
}

AsnType *ForwardParameter::Clone() const
{
  return new(memBlock) ForwardParameter(memBlock);
}

ForwardParameter &ForwardParameter::operator = (const ForwardParameter &that)
{
  if (this != &that)
  {
    forwardingType = that.forwardingType;
    if (that.forwardDN)
    {
      if (!forwardDN)
        forwardDN = new(memBlock) NumberDigits(memBlock);
      *forwardDN = *that.forwardDN;
    }
    else
    {
      forwardDN = NULL;
    }
  }

  return *this;
}

AsnLen
ForwardParameter::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (forwardDN))
  {
    l = forwardDN->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, UNIV, PRIM, IA5STRING_TAG_CODE);
    totalLen += l;
  }

    l = forwardingType.BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, ENUM_TAG_CODE);
    totalLen += l;

  return totalLen;
} // ForwardParameter::BEncContent


void ForwardParameter::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, ENUM_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    forwardingType.BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0168: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, IA5STRING_TAG_CODE))
    || (tag1 == MAKE_TAG_ID (UNIV, CONS, IA5STRING_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    forwardDN = new(memBlock) NumberDigits(memBlock);
    forwardDN->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0169: Length discrepancy on sequence.";
  }
  else
    return;
} // ForwardParameter::BDecContent

AsnLen ForwardParameter::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void ForwardParameter::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135076304: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int ForwardParameter::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ForwardParameter::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ForwardParameter::Print ( CTsvcLIB::LOG& os ) const
{
  os << "ForwardParameter SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "forwardingType : ";
  os << forwardingType;
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "forwardDN : ";
  if (NOT_NULL (forwardDN))
    os << *forwardDN;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // ForwardParameter::Print


QueryDeviceInformation::QueryDeviceInformation( MemBlock* mb ) : AsnType( mb )
{
  choiceId = msgWaitingOnCid;
  msgWaitingOn = NULL; // incomplete initialization of mandatory element!
}

QueryDeviceInformation::QueryDeviceInformation( MemBlock* mb, const QueryDeviceInformation & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined QueryDeviceInformation::QueryDeviceInformation (const QueryDeviceInformation &)";
  abort();
}

QueryDeviceInformation::~QueryDeviceInformation()
{
} // end of destructor

AsnType *QueryDeviceInformation::Clone() const
{
  return new(memBlock) QueryDeviceInformation(memBlock);
}

QueryDeviceInformation &QueryDeviceInformation::operator = (const QueryDeviceInformation &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case msgWaitingOnCid:
        msgWaitingOn = new(memBlock) AsnBool(memBlock);
        *msgWaitingOn = *that.msgWaitingOn;
        break;
      case doNotDisturbOnCid:
        doNotDisturbOn = new(memBlock) AsnBool(memBlock);
        *doNotDisturbOn = *that.doNotDisturbOn;
        break;
      case forwardCid:
        forward = new(memBlock) ListForwardParameters(memBlock);
        *forward = *that.forward;
        break;
      case lastDialedCid:
        lastDialed = new(memBlock) NumberDigits(memBlock);
        *lastDialed = *that.lastDialed;
        break;
      case deviceInfoCid:
        deviceInfo = new(memBlock) DeviceInfo(memBlock);
        *deviceInfo = *that.deviceInfo;
        break;
      case agentStateCid:
        agentState = new(memBlock) AgentState(memBlock);
        *agentState = *that.agentState;
        break;
      case routingEnabledCid:
        routingEnabled = new(memBlock) AsnBool(memBlock);
        *routingEnabled = *that.routingEnabled;
        break;
      case autoAnswerOnCid:
        autoAnswerOn = new(memBlock) AsnBool(memBlock);
        *autoAnswerOn = *that.autoAnswerOn;
        break;
      case microphoneMuteOnCid:
        microphoneMuteOn = new(memBlock) AsnBool(memBlock);
        *microphoneMuteOn = *that.microphoneMuteOn;
        break;
      case speakerMuteOnCid:
        speakerMuteOn = new(memBlock) AsnBool(memBlock);
        *speakerMuteOn = *that.speakerMuteOn;
        break;
      case speakerVolumeCid:
        speakerVolume = new(memBlock) AsnInt(memBlock);
        *speakerVolume = *that.speakerVolume;
        break;
    }
  }

  return *this;
}

AsnLen
QueryDeviceInformation::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case msgWaitingOnCid:
      l = msgWaitingOn->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 0);
      break;

    case doNotDisturbOnCid:
      l = doNotDisturbOn->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 1);
      break;

    case forwardCid:
      BEncEocIfNec (b);
      l = forward->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, CNTX, CONS, 2);
      break;

    case lastDialedCid:
      l = lastDialed->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 3);
      break;

    case deviceInfoCid:
      BEncEocIfNec (b);
      l = deviceInfo->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, CNTX, CONS, 4);
      break;

    case agentStateCid:
      l = agentState->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 5);
      break;

    case routingEnabledCid:
      l = routingEnabled->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 6);
      break;

    case autoAnswerOnCid:
      l = autoAnswerOn->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 7);
      break;

    case microphoneMuteOnCid:
      l = microphoneMuteOn->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 8);
      break;

    case speakerMuteOnCid:
      l = speakerMuteOn->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 9);
      break;

    case speakerVolumeCid:
      l = speakerVolume->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 10);
      break;

  } // end switch
  return l;
} // QueryDeviceInformation::BEncContent


void QueryDeviceInformation::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (CNTX, PRIM, 0):
      choiceId = msgWaitingOnCid;
      msgWaitingOn = new(memBlock) AsnBool(memBlock);
        msgWaitingOn->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 1):
      choiceId = doNotDisturbOnCid;
      doNotDisturbOn = new(memBlock) AsnBool(memBlock);
        doNotDisturbOn->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, CONS, 2):
      choiceId = forwardCid;
      forward = new(memBlock) ListForwardParameters(memBlock);
        forward->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 3):
    case MAKE_TAG_ID (CNTX, CONS, 3):
      choiceId = lastDialedCid;
      lastDialed = new(memBlock) NumberDigits(memBlock);
        lastDialed->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, CONS, 4):
      choiceId = deviceInfoCid;
      deviceInfo = new(memBlock) DeviceInfo(memBlock);
        deviceInfo->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 5):
      choiceId = agentStateCid;
      agentState = new(memBlock) AgentState(memBlock);
        agentState->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 6):
      choiceId = routingEnabledCid;
      routingEnabled = new(memBlock) AsnBool(memBlock);
        routingEnabled->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 7):
      choiceId = autoAnswerOnCid;
      autoAnswerOn = new(memBlock) AsnBool(memBlock);
        autoAnswerOn->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 8):
      choiceId = microphoneMuteOnCid;
      microphoneMuteOn = new(memBlock) AsnBool(memBlock);
        microphoneMuteOn->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 9):
      choiceId = speakerMuteOnCid;
      speakerMuteOn = new(memBlock) AsnBool(memBlock);
        speakerMuteOn->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 10):
      choiceId = speakerVolumeCid;
      speakerVolume = new(memBlock) AsnInt(memBlock);
        speakerVolume->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0170: Unexpected tag in CHOICE";
      break;
  } // end switch
} // QueryDeviceInformation::BDecContent


AsnLen QueryDeviceInformation::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void QueryDeviceInformation::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int QueryDeviceInformation::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int QueryDeviceInformation::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void QueryDeviceInformation::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case msgWaitingOnCid: os << "AsnBool*"; break;
    case doNotDisturbOnCid: os << "AsnBool*"; break;
    case forwardCid: os << "ListForwardParameters*"; break;
    case lastDialedCid: os << "NumberDigits*"; break;
    case deviceInfoCid: os << "DeviceInfo*"; break;
    case agentStateCid: os << "AgentState*"; break;
    case routingEnabledCid: os << "AsnBool*"; break;
    case autoAnswerOnCid: os << "AsnBool*"; break;
    case microphoneMuteOnCid: os << "AsnBool*"; break;
    case speakerMuteOnCid: os << "AsnBool*"; break;
    case speakerVolumeCid: os << "AsnInt*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case msgWaitingOnCid:
      os << "msgWaitingOn : ";
      if (msgWaitingOn)
        os << *msgWaitingOn;
      else
        os << "VOID";
      break;

    case doNotDisturbOnCid:
      os << "doNotDisturbOn : ";
      if (doNotDisturbOn)
        os << *doNotDisturbOn;
      else
        os << "VOID";
      break;

    case forwardCid:
      os << "forward : ";
      if (forward)
        os << *forward;
      else
        os << "VOID";
      break;

    case lastDialedCid:
      os << "lastDialed : ";
      if (lastDialed)
        os << *lastDialed;
      else
        os << "VOID";
      break;

    case deviceInfoCid:
      os << "deviceInfo : ";
      if (deviceInfo)
        os << *deviceInfo;
      else
        os << "VOID";
      break;

    case agentStateCid:
      os << "agentState : ";
      if (agentState)
        os << *agentState;
      else
        os << "VOID";
      break;

    case routingEnabledCid:
      os << "routingEnabled : ";
      if (routingEnabled)
        os << *routingEnabled;
      else
        os << "VOID";
      break;

    case autoAnswerOnCid:
      os << "autoAnswerOn : ";
      if (autoAnswerOn)
        os << *autoAnswerOn;
      else
        os << "VOID";
      break;

    case microphoneMuteOnCid:
      os << "microphoneMuteOn : ";
      if (microphoneMuteOn)
        os << *microphoneMuteOn;
      else
        os << "VOID";
      break;

    case speakerMuteOnCid:
      os << "speakerMuteOn : ";
      if (speakerMuteOn)
        os << *speakerMuteOn;
      else
        os << "VOID";
      break;

    case speakerVolumeCid:
      os << "speakerVolume : ";
      if (speakerVolume)
        os << *speakerVolume;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // QueryDeviceInformation::Print

CSTASecurityData::CSTASecurityData( MemBlock* mb ) : AsnType( mb )
{
  messageSequenceNumber = NULL;
  timeStamp = NULL;
  seal = NULL;
}

CSTASecurityData::CSTASecurityData( MemBlock* mb, const CSTASecurityData & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined CSTASecurityData::CSTASecurityData (const CSTASecurityData &)";
  abort();
}

CSTASecurityData::~CSTASecurityData()
{
}

AsnType *CSTASecurityData::Clone() const
{
  return new(memBlock) CSTASecurityData(memBlock);
}

CSTASecurityData &CSTASecurityData::operator = (const CSTASecurityData &that)
{
  if (this != &that)
  {
    if (that.messageSequenceNumber)
    {
      if (!messageSequenceNumber)
        messageSequenceNumber = new(memBlock) AsnInt(memBlock);
      *messageSequenceNumber = *that.messageSequenceNumber;
    }
    else
    {
      messageSequenceNumber = NULL;
    }
    if (that.timeStamp)
    {
      if (!timeStamp)
        timeStamp = new(memBlock) UTCTime(memBlock);
      *timeStamp = *that.timeStamp;
    }
    else
    {
      timeStamp = NULL;
    }
    if (that.seal)
    {
      if (!seal)
        seal = new(memBlock) Seal(memBlock);
      *seal = *that.seal;
    }
    else
    {
      seal = NULL;
    }
  }

  return *this;
}

AsnLen
CSTASecurityData::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (seal))
  {
      BEncEocIfNec (b);
    l = seal->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
    totalLen += l;
  }

  if (NOT_NULL (timeStamp))
  {
    l = timeStamp->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, UNIV, PRIM, UTCTIME_TAG_CODE);
    totalLen += l;
  }

  if (NOT_NULL (messageSequenceNumber))
  {
    l = messageSequenceNumber->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, INTEGER_TAG_CODE);
    totalLen += l;
  }

  return totalLen;
} // CSTASecurityData::BEncContent


void CSTASecurityData::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  if (elmtLen0 == 0)
    return;
  else
  {
    tag1 = BDecTag (b, seqBytesDecoded);

    if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
    {
      BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
      bytesDecoded += seqBytesDecoded;
      return;
    }
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, INTEGER_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    messageSequenceNumber = new(memBlock) AsnInt(memBlock);
    messageSequenceNumber->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, UTCTIME_TAG_CODE))
    || (tag1 == MAKE_TAG_ID (UNIV, CONS, UTCTIME_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    timeStamp = new(memBlock) UTCTime(memBlock);
    timeStamp->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    seal = new(memBlock) Seal(memBlock);
    seal->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0171: Length discrepancy on sequence.";
  }
  else
    return;
} // CSTASecurityData::BDecContent

AsnLen CSTASecurityData::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void CSTASecurityData::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135077576: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int CSTASecurityData::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int CSTASecurityData::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void CSTASecurityData::Print ( CTsvcLIB::LOG& os ) const
{
  os << "CSTASecurityData SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "messageSequenceNumber : ";
  if (NOT_NULL (messageSequenceNumber))
    os << *messageSequenceNumber;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "timeStamp : ";
  if (NOT_NULL (timeStamp))
    os << *timeStamp;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "seal : ";
  if (NOT_NULL (seal))
    os << *seal;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // CSTASecurityData::Print


CSTACommonArguments::CSTACommonArguments( MemBlock* mb ) : AsnType( mb )
{
  security = NULL;
  privateData = NULL;
}

CSTACommonArguments::CSTACommonArguments( MemBlock* mb, const CSTACommonArguments & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined CSTACommonArguments::CSTACommonArguments (const CSTACommonArguments &)";
  abort();
}

CSTACommonArguments::~CSTACommonArguments()
{
}

AsnType *CSTACommonArguments::Clone() const
{
  return new(memBlock) CSTACommonArguments(memBlock);
}

CSTACommonArguments &CSTACommonArguments::operator = (const CSTACommonArguments &that)
{
  if (this != &that)
  {
    if (that.security)
    {
      if (!security)
        security = new(memBlock) CSTASecurityData(memBlock);
      *security = *that.security;
    }
    else
    {
      security = NULL;
    }
    if (that.privateData)
    {
      if (!privateData)
        privateData = new(memBlock) CSTACommonArgumentsSeqOf(memBlock);
      *privateData = *that.privateData;
    }
    else
    {
      privateData = NULL;
    }
  }

  return *this;
}

AsnLen
CSTACommonArguments::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (privateData))
  {
      BEncEocIfNec (b);
    l = privateData->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, CNTX, CONS, 1);
    totalLen += l;
  }

  if (NOT_NULL (security))
  {
      BEncEocIfNec (b);
    l = security->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, CNTX, CONS, 0);
    totalLen += l;
  }

  return totalLen;
} // CSTACommonArguments::BEncContent


void CSTACommonArguments::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  if (elmtLen0 == 0)
    return;
  else
  {
    tag1 = BDecTag (b, seqBytesDecoded);

    if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
    {
      BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
      bytesDecoded += seqBytesDecoded;
      return;
    }
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, CONS, 0)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    security = new(memBlock) CSTASecurityData(memBlock);
    security->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, CONS, 1)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    privateData = new(memBlock) CSTACommonArgumentsSeqOf(memBlock);
    privateData->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0172: Length discrepancy on sequence.";
  }
  else
    return;
} // CSTACommonArguments::BDecContent

AsnLen CSTACommonArguments::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, APPL, CONS, 30);
  return l;
}

void CSTACommonArguments::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (APPL, CONS, 30))
  {
    throw "ERROR C135070664: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int CSTACommonArguments::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int CSTACommonArguments::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void CSTACommonArguments::Print ( CTsvcLIB::LOG& os ) const
{
  os << "CSTACommonArguments SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "security : ";
  if (NOT_NULL (security))
    os << *security;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "privateData : ";
  if (NOT_NULL (privateData))
    os << *privateData;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // CSTACommonArguments::Print


ConnectionIDChoice::ConnectionIDChoice( MemBlock* mb ) : AsnType( mb )
{
  choiceId = staticIDCid;
  staticID = NULL; // incomplete initialization of mandatory element!
}

ConnectionIDChoice::ConnectionIDChoice( MemBlock* mb, const ConnectionIDChoice & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined ConnectionIDChoice::ConnectionIDChoice (const ConnectionIDChoice &)";
  abort();
}

ConnectionIDChoice::~ConnectionIDChoice()
{
} // end of destructor

AsnType *ConnectionIDChoice::Clone() const
{
  return new(memBlock) ConnectionIDChoice(memBlock);
}

ConnectionIDChoice &ConnectionIDChoice::operator = (const ConnectionIDChoice &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case staticIDCid:
        staticID = new(memBlock) DeviceID(memBlock);
        *staticID = *that.staticID;
        break;
      case dynamicIDCid:
        dynamicID = new(memBlock) AsnOcts(memBlock);
        *dynamicID = *that.dynamicID;
        break;
    }
  }

  return *this;
}

AsnLen
ConnectionIDChoice::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case staticIDCid:
      l = staticID->BEncContent (b);
      break;

    case dynamicIDCid:
      l = dynamicID->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 3);
      break;

  } // end switch
  return l;
} // ConnectionIDChoice::BEncContent


void ConnectionIDChoice::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (CNTX, PRIM, 0):
    case MAKE_TAG_ID (CNTX, CONS, 0):
    case MAKE_TAG_ID (CNTX, PRIM, 1):
      choiceId = staticIDCid;
      staticID = new(memBlock) DeviceID(memBlock);
        staticID->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 3):
    case MAKE_TAG_ID (CNTX, CONS, 3):
      choiceId = dynamicIDCid;
      dynamicID = new(memBlock) AsnOcts(memBlock);
        dynamicID->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0173: Unexpected tag in CHOICE";
      break;
  } // end switch
} // ConnectionIDChoice::BDecContent


AsnLen ConnectionIDChoice::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void ConnectionIDChoice::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int ConnectionIDChoice::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ConnectionIDChoice::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ConnectionIDChoice::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case staticIDCid: os << "DeviceID*"; break;
    case dynamicIDCid: os << "AsnOcts*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case staticIDCid:
      os << "staticID : ";
      if (staticID)
        os << *staticID;
      else
        os << "VOID";
      break;

    case dynamicIDCid:
      os << "dynamicID : ";
      if (dynamicID)
        os << *dynamicID;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // ConnectionIDChoice::Print

SnapshotDeviceArgumentSeq::SnapshotDeviceArgumentSeq( MemBlock* mb ) : AsnType( mb )
{
  snapshotObject = NULL; // incomplete initialization of mandatory element!
  extensions = NULL;
}

SnapshotDeviceArgumentSeq::SnapshotDeviceArgumentSeq( MemBlock* mb, const SnapshotDeviceArgumentSeq & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined SnapshotDeviceArgumentSeq::SnapshotDeviceArgumentSeq (const SnapshotDeviceArgumentSeq &)";
  abort();
}

SnapshotDeviceArgumentSeq::~SnapshotDeviceArgumentSeq()
{
}

AsnType *SnapshotDeviceArgumentSeq::Clone() const
{
  return new(memBlock) SnapshotDeviceArgumentSeq(memBlock);
}

SnapshotDeviceArgumentSeq &SnapshotDeviceArgumentSeq::operator = (const SnapshotDeviceArgumentSeq &that)
{
  if (this != &that)
  {
    if (that.snapshotObject)
    {
      if (!snapshotObject)
        snapshotObject = new(memBlock) DeviceID(memBlock);
      *snapshotObject = *that.snapshotObject;
    }
    else
    {
      snapshotObject = NULL;
    }
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTACommonArguments(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
SnapshotDeviceArgumentSeq::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 30);
    totalLen += l;
  }

    l = snapshotObject->BEncContent (b);
    totalLen += l;

  return totalLen;
} // SnapshotDeviceArgumentSeq::BEncContent


void SnapshotDeviceArgumentSeq::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 1)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    snapshotObject = new(memBlock) DeviceID(memBlock);
    snapshotObject->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0174: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 30)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTACommonArguments(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0175: Length discrepancy on sequence.";
  }
  else
    return;
} // SnapshotDeviceArgumentSeq::BDecContent

AsnLen SnapshotDeviceArgumentSeq::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void SnapshotDeviceArgumentSeq::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135062344: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int SnapshotDeviceArgumentSeq::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int SnapshotDeviceArgumentSeq::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void SnapshotDeviceArgumentSeq::Print ( CTsvcLIB::LOG& os ) const
{
  os << "SnapshotDeviceArgumentSeq SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "snapshotObject : ";
  if (NOT_NULL (snapshotObject))
    os << *snapshotObject;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // SnapshotDeviceArgumentSeq::Print


MonitorStopArgumentSeq::MonitorStopArgumentSeq( MemBlock* mb ) : AsnType( mb )
    , crossRefIdentifier( mb )
{
  extensions = NULL;
}

MonitorStopArgumentSeq::MonitorStopArgumentSeq( MemBlock* mb, const MonitorStopArgumentSeq & ) : AsnType( mb )
    , crossRefIdentifier( mb )
{
  throw "ERROR C0099: Use of incompletely defined MonitorStopArgumentSeq::MonitorStopArgumentSeq (const MonitorStopArgumentSeq &)";
  abort();
}

MonitorStopArgumentSeq::~MonitorStopArgumentSeq()
{
}

AsnType *MonitorStopArgumentSeq::Clone() const
{
  return new(memBlock) MonitorStopArgumentSeq(memBlock);
}

MonitorStopArgumentSeq &MonitorStopArgumentSeq::operator = (const MonitorStopArgumentSeq &that)
{
  if (this != &that)
  {
    crossRefIdentifier = that.crossRefIdentifier;
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTACommonArguments(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
MonitorStopArgumentSeq::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 30);
    totalLen += l;
  }

    l = crossRefIdentifier.BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, APPL, PRIM, 21);
    totalLen += l;

  return totalLen;
} // MonitorStopArgumentSeq::BEncContent


void MonitorStopArgumentSeq::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, PRIM, 21))
    || (tag1 == MAKE_TAG_ID (APPL, CONS, 21)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    crossRefIdentifier.BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0176: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 30)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTACommonArguments(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0177: Length discrepancy on sequence.";
  }
  else
    return;
} // MonitorStopArgumentSeq::BDecContent

AsnLen MonitorStopArgumentSeq::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void MonitorStopArgumentSeq::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135062416: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int MonitorStopArgumentSeq::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int MonitorStopArgumentSeq::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void MonitorStopArgumentSeq::Print ( CTsvcLIB::LOG& os ) const
{
  os << "MonitorStopArgumentSeq SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "crossRefIdentifier : ";
  os << crossRefIdentifier;
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // MonitorStopArgumentSeq::Print


ChangeMonitorFilterResultSeq::ChangeMonitorFilterResultSeq( MemBlock* mb ) : AsnType( mb )
{
  filterList = NULL;
  extensions = NULL;
}

ChangeMonitorFilterResultSeq::ChangeMonitorFilterResultSeq( MemBlock* mb, const ChangeMonitorFilterResultSeq & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined ChangeMonitorFilterResultSeq::ChangeMonitorFilterResultSeq (const ChangeMonitorFilterResultSeq &)";
  abort();
}

ChangeMonitorFilterResultSeq::~ChangeMonitorFilterResultSeq()
{
}

AsnType *ChangeMonitorFilterResultSeq::Clone() const
{
  return new(memBlock) ChangeMonitorFilterResultSeq(memBlock);
}

ChangeMonitorFilterResultSeq &ChangeMonitorFilterResultSeq::operator = (const ChangeMonitorFilterResultSeq &that)
{
  if (this != &that)
  {
    if (that.filterList)
    {
      if (!filterList)
        filterList = new(memBlock) MonitorFilter(memBlock);
      *filterList = *that.filterList;
    }
    else
    {
      filterList = NULL;
    }
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTAPrivateData(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
ChangeMonitorFilterResultSeq::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 29);
    totalLen += l;
  }

  if (NOT_NULL (filterList))
  {
      BEncEocIfNec (b);
    l = filterList->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
    totalLen += l;
  }

  return totalLen;
} // ChangeMonitorFilterResultSeq::BEncContent


void ChangeMonitorFilterResultSeq::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  if (elmtLen0 == 0)
    return;
  else
  {
    tag1 = BDecTag (b, seqBytesDecoded);

    if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
    {
      BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
      bytesDecoded += seqBytesDecoded;
      return;
    }
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    filterList = new(memBlock) MonitorFilter(memBlock);
    filterList->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 29)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTAPrivateData(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0178: Length discrepancy on sequence.";
  }
  else
    return;
} // ChangeMonitorFilterResultSeq::BDecContent

AsnLen ChangeMonitorFilterResultSeq::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void ChangeMonitorFilterResultSeq::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135062520: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int ChangeMonitorFilterResultSeq::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ChangeMonitorFilterResultSeq::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ChangeMonitorFilterResultSeq::Print ( CTsvcLIB::LOG& os ) const
{
  os << "ChangeMonitorFilterResultSeq SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "filterList : ";
  if (NOT_NULL (filterList))
    os << *filterList;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // ChangeMonitorFilterResultSeq::Print


SystemStatusArgumentSeq::SystemStatusArgumentSeq( MemBlock* mb ) : AsnType( mb )
    , systemStatus( mb )
{
  extensions = NULL;
}

SystemStatusArgumentSeq::SystemStatusArgumentSeq( MemBlock* mb, const SystemStatusArgumentSeq & ) : AsnType( mb )
    , systemStatus( mb )
{
  throw "ERROR C0099: Use of incompletely defined SystemStatusArgumentSeq::SystemStatusArgumentSeq (const SystemStatusArgumentSeq &)";
  abort();
}

SystemStatusArgumentSeq::~SystemStatusArgumentSeq()
{
}

AsnType *SystemStatusArgumentSeq::Clone() const
{
  return new(memBlock) SystemStatusArgumentSeq(memBlock);
}

SystemStatusArgumentSeq &SystemStatusArgumentSeq::operator = (const SystemStatusArgumentSeq &that)
{
  if (this != &that)
  {
    systemStatus = that.systemStatus;
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTACommonArguments(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
SystemStatusArgumentSeq::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 30);
    totalLen += l;
  }

    l = systemStatus.BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, ENUM_TAG_CODE);
    totalLen += l;

  return totalLen;
} // SystemStatusArgumentSeq::BEncContent


void SystemStatusArgumentSeq::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, ENUM_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    systemStatus.BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0179: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 30)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTACommonArguments(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0180: Length discrepancy on sequence.";
  }
  else
    return;
} // SystemStatusArgumentSeq::BDecContent

AsnLen SystemStatusArgumentSeq::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void SystemStatusArgumentSeq::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135062592: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int SystemStatusArgumentSeq::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int SystemStatusArgumentSeq::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void SystemStatusArgumentSeq::Print ( CTsvcLIB::LOG& os ) const
{
  os << "SystemStatusArgumentSeq SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "systemStatus : ";
  os << systemStatus;
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // SystemStatusArgumentSeq::Print


QueryDeviceResultSeq::QueryDeviceResultSeq( MemBlock* mb ) : AsnType( mb )
{
  deviceInformation = NULL; // incomplete initialization of mandatory element!
  extensions = NULL;
}

QueryDeviceResultSeq::QueryDeviceResultSeq( MemBlock* mb, const QueryDeviceResultSeq & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined QueryDeviceResultSeq::QueryDeviceResultSeq (const QueryDeviceResultSeq &)";
  abort();
}

QueryDeviceResultSeq::~QueryDeviceResultSeq()
{
}

AsnType *QueryDeviceResultSeq::Clone() const
{
  return new(memBlock) QueryDeviceResultSeq(memBlock);
}

QueryDeviceResultSeq &QueryDeviceResultSeq::operator = (const QueryDeviceResultSeq &that)
{
  if (this != &that)
  {
    if (that.deviceInformation)
    {
      if (!deviceInformation)
        deviceInformation = new(memBlock) QueryDeviceInformation(memBlock);
      *deviceInformation = *that.deviceInformation;
    }
    else
    {
      deviceInformation = NULL;
    }
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTAPrivateData(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
QueryDeviceResultSeq::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 29);
    totalLen += l;
  }

    l = deviceInformation->BEncContent (b);
    totalLen += l;

  return totalLen;
} // QueryDeviceResultSeq::BEncContent


void QueryDeviceResultSeq::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 1))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 2))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 3))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 3))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 4))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 5))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 6))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 7))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 8))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 9))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 10)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    deviceInformation = new(memBlock) QueryDeviceInformation(memBlock);
    deviceInformation->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0181: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 29)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTAPrivateData(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0182: Length discrepancy on sequence.";
  }
  else
    return;
} // QueryDeviceResultSeq::BDecContent

AsnLen QueryDeviceResultSeq::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void QueryDeviceResultSeq::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135062920: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int QueryDeviceResultSeq::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int QueryDeviceResultSeq::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void QueryDeviceResultSeq::Print ( CTsvcLIB::LOG& os ) const
{
  os << "QueryDeviceResultSeq SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "deviceInformation : ";
  if (NOT_NULL (deviceInformation))
    os << *deviceInformation;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // QueryDeviceResultSeq::Print


ROSEapdu::ROSEapdu( MemBlock* mb ) : AsnType( mb )
{
  choiceId = invokeApduCid;
  invokeApdu = NULL; // incomplete initialization of mandatory element!
}

ROSEapdu::ROSEapdu( MemBlock* mb, const ROSEapdu & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined ROSEapdu::ROSEapdu (const ROSEapdu &)";
  abort();
}

ROSEapdu::~ROSEapdu()
{
} // end of destructor

AsnType *ROSEapdu::Clone() const
{
  return new(memBlock) ROSEapdu(memBlock);
}

ROSEapdu &ROSEapdu::operator = (const ROSEapdu &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case invokeApduCid:
        invokeApdu = new(memBlock) ROIVapdu(memBlock);
        *invokeApdu = *that.invokeApdu;
        break;
      case resultApduCid:
        resultApdu = new(memBlock) RORSapdu(memBlock);
        *resultApdu = *that.resultApdu;
        break;
      case errorApduCid:
        errorApdu = new(memBlock) ROERapdu(memBlock);
        *errorApdu = *that.errorApdu;
        break;
      case rejectApduCid:
        rejectApdu = new(memBlock) RORJapdu(memBlock);
        *rejectApdu = *that.rejectApdu;
        break;
    }
  }

  return *this;
}

AsnLen
ROSEapdu::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case invokeApduCid:
      BEncEocIfNec (b);
      l = invokeApdu->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, CNTX, CONS, 1);
      break;

    case resultApduCid:
      BEncEocIfNec (b);
      l = resultApdu->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, CNTX, CONS, 2);
      break;

    case errorApduCid:
      BEncEocIfNec (b);
      l = errorApdu->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, CNTX, CONS, 3);
      break;

    case rejectApduCid:
      BEncEocIfNec (b);
      l = rejectApdu->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, CNTX, CONS, 4);
      break;

  } // end switch
  return l;
} // ROSEapdu::BEncContent


void ROSEapdu::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (CNTX, CONS, 1):
      choiceId = invokeApduCid;
      invokeApdu = new(memBlock) ROIVapdu(memBlock);
        invokeApdu->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, CONS, 2):
      choiceId = resultApduCid;
      resultApdu = new(memBlock) RORSapdu(memBlock);
        resultApdu->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, CONS, 3):
      choiceId = errorApduCid;
      errorApdu = new(memBlock) ROERapdu(memBlock);
        errorApdu->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, CONS, 4):
      choiceId = rejectApduCid;
      rejectApdu = new(memBlock) RORJapdu(memBlock);
        rejectApdu->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0183: Unexpected tag in CHOICE";
      break;
  } // end switch
} // ROSEapdu::BDecContent


AsnLen ROSEapdu::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void ROSEapdu::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int ROSEapdu::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ROSEapdu::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ROSEapdu::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case invokeApduCid: os << "ROIVapdu*"; break;
    case resultApduCid: os << "RORSapdu*"; break;
    case errorApduCid: os << "ROERapdu*"; break;
    case rejectApduCid: os << "RORJapdu*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case invokeApduCid:
      os << "invokeApdu : ";
      if (invokeApdu)
        os << *invokeApdu;
      else
        os << "VOID";
      break;

    case resultApduCid:
      os << "resultApdu : ";
      if (resultApdu)
        os << *resultApdu;
      else
        os << "VOID";
      break;

    case errorApduCid:
      os << "errorApdu : ";
      if (errorApdu)
        os << *errorApdu;
      else
        os << "VOID";
      break;

    case rejectApduCid:
      os << "rejectApdu : ";
      if (rejectApdu)
        os << *rejectApdu;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // ROSEapdu::Print

MakeCallArgument::MakeCallArgument( MemBlock* mb ) : AsnType( mb )
{
  callingDevice = NULL; // incomplete initialization of mandatory element!
  calledDirectoryNumber = NULL; // incomplete initialization of mandatory element!
  extensions = NULL;
}

MakeCallArgument::MakeCallArgument( MemBlock* mb, const MakeCallArgument & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined MakeCallArgument::MakeCallArgument (const MakeCallArgument &)";
  abort();
}

MakeCallArgument::~MakeCallArgument()
{
}

AsnType *MakeCallArgument::Clone() const
{
  return new(memBlock) MakeCallArgument(memBlock);
}

MakeCallArgument &MakeCallArgument::operator = (const MakeCallArgument &that)
{
  if (this != &that)
  {
    if (that.callingDevice)
    {
      if (!callingDevice)
        callingDevice = new(memBlock) DeviceID(memBlock);
      *callingDevice = *that.callingDevice;
    }
    else
    {
      callingDevice = NULL;
    }
    if (that.calledDirectoryNumber)
    {
      if (!calledDirectoryNumber)
        calledDirectoryNumber = new(memBlock) CalledDeviceID(memBlock);
      *calledDirectoryNumber = *that.calledDirectoryNumber;
    }
    else
    {
      calledDirectoryNumber = NULL;
    }
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTACommonArguments(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
MakeCallArgument::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 30);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = calledDirectoryNumber->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 2);
    totalLen += l;

    l = callingDevice->BEncContent (b);
    totalLen += l;

  return totalLen;
} // MakeCallArgument::BEncContent


void MakeCallArgument::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  AsnLen elmtLen2;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 1)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    callingDevice = new(memBlock) DeviceID(memBlock);
    callingDevice->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0184: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 2)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    calledDirectoryNumber = new(memBlock) CalledDeviceID(memBlock);
    calledDirectoryNumber->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0185: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 30)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTACommonArguments(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0186: Length discrepancy on sequence.";
  }
  else
    return;
} // MakeCallArgument::BDecContent

AsnLen MakeCallArgument::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void MakeCallArgument::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135066504: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int MakeCallArgument::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int MakeCallArgument::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void MakeCallArgument::Print ( CTsvcLIB::LOG& os ) const
{
  os << "MakeCallArgument SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "callingDevice : ";
  if (NOT_NULL (callingDevice))
    os << *callingDevice;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "calledDirectoryNumber : ";
  if (NOT_NULL (calledDirectoryNumber))
    os << *calledDirectoryNumber;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // MakeCallArgument::Print


MakePredictiveCallArgument::MakePredictiveCallArgument( MemBlock* mb ) : AsnType( mb )
{
  callingDevice = NULL; // incomplete initialization of mandatory element!
  calledDirectoryNumber = NULL; // incomplete initialization of mandatory element!
  allocation = NULL;
  extensions = NULL;
}

MakePredictiveCallArgument::MakePredictiveCallArgument( MemBlock* mb, const MakePredictiveCallArgument & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined MakePredictiveCallArgument::MakePredictiveCallArgument (const MakePredictiveCallArgument &)";
  abort();
}

MakePredictiveCallArgument::~MakePredictiveCallArgument()
{
}

AsnType *MakePredictiveCallArgument::Clone() const
{
  return new(memBlock) MakePredictiveCallArgument(memBlock);
}

MakePredictiveCallArgument &MakePredictiveCallArgument::operator = (const MakePredictiveCallArgument &that)
{
  if (this != &that)
  {
    if (that.callingDevice)
    {
      if (!callingDevice)
        callingDevice = new(memBlock) DeviceID(memBlock);
      *callingDevice = *that.callingDevice;
    }
    else
    {
      callingDevice = NULL;
    }
    if (that.calledDirectoryNumber)
    {
      if (!calledDirectoryNumber)
        calledDirectoryNumber = new(memBlock) CalledDeviceID(memBlock);
      *calledDirectoryNumber = *that.calledDirectoryNumber;
    }
    else
    {
      calledDirectoryNumber = NULL;
    }
    if (that.allocation)
    {
      if (!allocation)
        allocation = new(memBlock) AllocationState(memBlock);
      *allocation = *that.allocation;
    }
    else
    {
      allocation = NULL;
    }
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTACommonArguments(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
MakePredictiveCallArgument::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 30);
    totalLen += l;
  }

  if (NOT_NULL (allocation))
  {
    l = allocation->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, ENUM_TAG_CODE);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = calledDirectoryNumber->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 2);
    totalLen += l;

    l = callingDevice->BEncContent (b);
    totalLen += l;

  return totalLen;
} // MakePredictiveCallArgument::BEncContent


void MakePredictiveCallArgument::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  AsnLen elmtLen2;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 1)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    callingDevice = new(memBlock) DeviceID(memBlock);
    callingDevice->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0187: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 2)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    calledDirectoryNumber = new(memBlock) CalledDeviceID(memBlock);
    calledDirectoryNumber->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0188: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, ENUM_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    allocation = new(memBlock) AllocationState(memBlock);
    allocation->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 30)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTACommonArguments(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0189: Length discrepancy on sequence.";
  }
  else
    return;
} // MakePredictiveCallArgument::BDecContent

AsnLen MakePredictiveCallArgument::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void MakePredictiveCallArgument::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135066680: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int MakePredictiveCallArgument::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int MakePredictiveCallArgument::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void MakePredictiveCallArgument::Print ( CTsvcLIB::LOG& os ) const
{
  os << "MakePredictiveCallArgument SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "callingDevice : ";
  if (NOT_NULL (callingDevice))
    os << *callingDevice;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "calledDirectoryNumber : ";
  if (NOT_NULL (calledDirectoryNumber))
    os << *calledDirectoryNumber;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "allocation : ";
  if (NOT_NULL (allocation))
    os << *allocation;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // MakePredictiveCallArgument::Print


QueryDeviceArgument::QueryDeviceArgument( MemBlock* mb ) : AsnType( mb )
    , feature( mb )
{
  device = NULL; // incomplete initialization of mandatory element!
  extensions = NULL;
}

QueryDeviceArgument::QueryDeviceArgument( MemBlock* mb, const QueryDeviceArgument & ) : AsnType( mb )
    , feature( mb )
{
  throw "ERROR C0099: Use of incompletely defined QueryDeviceArgument::QueryDeviceArgument (const QueryDeviceArgument &)";
  abort();
}

QueryDeviceArgument::~QueryDeviceArgument()
{
}

AsnType *QueryDeviceArgument::Clone() const
{
  return new(memBlock) QueryDeviceArgument(memBlock);
}

QueryDeviceArgument &QueryDeviceArgument::operator = (const QueryDeviceArgument &that)
{
  if (this != &that)
  {
    if (that.device)
    {
      if (!device)
        device = new(memBlock) DeviceID(memBlock);
      *device = *that.device;
    }
    else
    {
      device = NULL;
    }
    feature = that.feature;
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTACommonArguments(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
QueryDeviceArgument::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 30);
    totalLen += l;
  }

    l = feature.BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, ENUM_TAG_CODE);
    totalLen += l;

    l = device->BEncContent (b);
    totalLen += l;

  return totalLen;
} // QueryDeviceArgument::BEncContent


void QueryDeviceArgument::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 1)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    device = new(memBlock) DeviceID(memBlock);
    device->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0190: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, ENUM_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    feature.BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0191: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 30)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTACommonArguments(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0192: Length discrepancy on sequence.";
  }
  else
    return;
} // QueryDeviceArgument::BDecContent

AsnLen QueryDeviceArgument::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void QueryDeviceArgument::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135066848: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int QueryDeviceArgument::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int QueryDeviceArgument::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void QueryDeviceArgument::Print ( CTsvcLIB::LOG& os ) const
{
  os << "QueryDeviceArgument SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "device : ";
  if (NOT_NULL (device))
    os << *device;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "feature : ";
  os << feature;
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // QueryDeviceArgument::Print


QueryDeviceResult::QueryDeviceResult( MemBlock* mb ) : AsnType( mb )
{
  choiceId = deviceInformationCid;
  deviceInformation = NULL; // incomplete initialization of mandatory element!
}

QueryDeviceResult::QueryDeviceResult( MemBlock* mb, const QueryDeviceResult & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined QueryDeviceResult::QueryDeviceResult (const QueryDeviceResult &)";
  abort();
}

QueryDeviceResult::~QueryDeviceResult()
{
} // end of destructor

AsnType *QueryDeviceResult::Clone() const
{
  return new(memBlock) QueryDeviceResult(memBlock);
}

QueryDeviceResult &QueryDeviceResult::operator = (const QueryDeviceResult &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case deviceInformationCid:
        deviceInformation = new(memBlock) QueryDeviceInformation(memBlock);
        *deviceInformation = *that.deviceInformation;
        break;
      case queryDeviceResultSeqCid:
        queryDeviceResultSeq = new(memBlock) QueryDeviceResultSeq(memBlock);
        *queryDeviceResultSeq = *that.queryDeviceResultSeq;
        break;
    }
  }

  return *this;
}

AsnLen
QueryDeviceResult::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case deviceInformationCid:
      l = deviceInformation->BEncContent (b);
      break;

    case queryDeviceResultSeqCid:
      BEncEocIfNec (b);
      l = queryDeviceResultSeq->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
      break;

  } // end switch
  return l;
} // QueryDeviceResult::BEncContent


void QueryDeviceResult::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (CNTX, PRIM, 0):
    case MAKE_TAG_ID (CNTX, PRIM, 1):
    case MAKE_TAG_ID (CNTX, CONS, 2):
    case MAKE_TAG_ID (CNTX, PRIM, 3):
    case MAKE_TAG_ID (CNTX, CONS, 3):
    case MAKE_TAG_ID (CNTX, CONS, 4):
    case MAKE_TAG_ID (CNTX, PRIM, 5):
    case MAKE_TAG_ID (CNTX, PRIM, 6):
    case MAKE_TAG_ID (CNTX, PRIM, 7):
    case MAKE_TAG_ID (CNTX, PRIM, 8):
    case MAKE_TAG_ID (CNTX, PRIM, 9):
    case MAKE_TAG_ID (CNTX, PRIM, 10):
      choiceId = deviceInformationCid;
      deviceInformation = new(memBlock) QueryDeviceInformation(memBlock);
        deviceInformation->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE):
      choiceId = queryDeviceResultSeqCid;
      queryDeviceResultSeq = new(memBlock) QueryDeviceResultSeq(memBlock);
        queryDeviceResultSeq->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0193: Unexpected tag in CHOICE";
      break;
  } // end switch
} // QueryDeviceResult::BDecContent


AsnLen QueryDeviceResult::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void QueryDeviceResult::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int QueryDeviceResult::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int QueryDeviceResult::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void QueryDeviceResult::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case deviceInformationCid: os << "QueryDeviceInformation*"; break;
    case queryDeviceResultSeqCid: os << "QueryDeviceResultSeq*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case deviceInformationCid:
      os << "deviceInformation : ";
      if (deviceInformation)
        os << *deviceInformation;
      else
        os << "VOID";
      break;

    case queryDeviceResultSeqCid:
      if (queryDeviceResultSeq)
        os << *queryDeviceResultSeq;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // QueryDeviceResult::Print

ReRouteRequestArgument::ReRouteRequestArgument( MemBlock* mb ) : AsnType( mb )
    , crossRefIdentifier( mb )
{
  extensions = NULL;
}

ReRouteRequestArgument::ReRouteRequestArgument( MemBlock* mb, const ReRouteRequestArgument & ) : AsnType( mb )
    , crossRefIdentifier( mb )
{
  throw "ERROR C0099: Use of incompletely defined ReRouteRequestArgument::ReRouteRequestArgument (const ReRouteRequestArgument &)";
  abort();
}

ReRouteRequestArgument::~ReRouteRequestArgument()
{
}

AsnType *ReRouteRequestArgument::Clone() const
{
  return new(memBlock) ReRouteRequestArgument(memBlock);
}

ReRouteRequestArgument &ReRouteRequestArgument::operator = (const ReRouteRequestArgument &that)
{
  if (this != &that)
  {
    crossRefIdentifier = that.crossRefIdentifier;
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTACommonArguments(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
ReRouteRequestArgument::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 30);
    totalLen += l;
  }

    l = crossRefIdentifier.BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, APPL, PRIM, 24);
    totalLen += l;

  return totalLen;
} // ReRouteRequestArgument::BEncContent


void ReRouteRequestArgument::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, PRIM, 24))
    || (tag1 == MAKE_TAG_ID (APPL, CONS, 24)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    crossRefIdentifier.BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0194: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 30)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTACommonArguments(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0195: Length discrepancy on sequence.";
  }
  else
    return;
} // ReRouteRequestArgument::BDecContent

AsnLen ReRouteRequestArgument::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void ReRouteRequestArgument::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135070240: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int ReRouteRequestArgument::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ReRouteRequestArgument::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ReRouteRequestArgument::Print ( CTsvcLIB::LOG& os ) const
{
  os << "ReRouteRequestArgument SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "crossRefIdentifier : ";
  os << crossRefIdentifier;
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // ReRouteRequestArgument::Print


RouteSelectRequestArgument::RouteSelectRequestArgument( MemBlock* mb ) : AsnType( mb )
    , crossRefIdentifier( mb )
{
  routeSelected = NULL; // incomplete initialization of mandatory element!
  remainRetry = NULL;
  setupInformation = NULL;
  routeUsedReq = NULL;
  extensions = NULL;
}

RouteSelectRequestArgument::RouteSelectRequestArgument( MemBlock* mb, const RouteSelectRequestArgument & ) : AsnType( mb )
    , crossRefIdentifier( mb )
{
  throw "ERROR C0099: Use of incompletely defined RouteSelectRequestArgument::RouteSelectRequestArgument (const RouteSelectRequestArgument &)";
  abort();
}

RouteSelectRequestArgument::~RouteSelectRequestArgument()
{
}

AsnType *RouteSelectRequestArgument::Clone() const
{
  return new(memBlock) RouteSelectRequestArgument(memBlock);
}

RouteSelectRequestArgument &RouteSelectRequestArgument::operator = (const RouteSelectRequestArgument &that)
{
  if (this != &that)
  {
    crossRefIdentifier = that.crossRefIdentifier;
    if (that.routeSelected)
    {
      if (!routeSelected)
        routeSelected = new(memBlock) CalledDeviceID(memBlock);
      *routeSelected = *that.routeSelected;
    }
    else
    {
      routeSelected = NULL;
    }
    if (that.remainRetry)
    {
      if (!remainRetry)
        remainRetry = new(memBlock) RetryValue(memBlock);
      *remainRetry = *that.remainRetry;
    }
    else
    {
      remainRetry = NULL;
    }
    if (that.setupInformation)
    {
      if (!setupInformation)
        setupInformation = new(memBlock) SetUpValues(memBlock);
      *setupInformation = *that.setupInformation;
    }
    else
    {
      setupInformation = NULL;
    }
    if (that.routeUsedReq)
    {
      if (!routeUsedReq)
        routeUsedReq = new(memBlock) RouteUsedFlag(memBlock);
      *routeUsedReq = *that.routeUsedReq;
    }
    else
    {
      routeUsedReq = NULL;
    }
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTACommonArguments(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
RouteSelectRequestArgument::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 30);
    totalLen += l;
  }

  if (NOT_NULL (routeUsedReq))
  {
    l = routeUsedReq->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, BOOLEAN_TAG_CODE);
    totalLen += l;
  }

  if (NOT_NULL (setupInformation))
  {
    l = setupInformation->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, UNIV, PRIM, OCTETSTRING_TAG_CODE);
    totalLen += l;
  }

  if (NOT_NULL (remainRetry))
  {
    l = remainRetry->BEncContent (b);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = routeSelected->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 2);
    totalLen += l;

    l = crossRefIdentifier.BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, APPL, PRIM, 24);
    totalLen += l;

  return totalLen;
} // RouteSelectRequestArgument::BEncContent


void RouteSelectRequestArgument::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  AsnLen elmtLen2;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, PRIM, 24))
    || (tag1 == MAKE_TAG_ID (APPL, CONS, 24)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    crossRefIdentifier.BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0196: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 2)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    routeSelected = new(memBlock) CalledDeviceID(memBlock);
    routeSelected->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0197: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 1))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 2)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    remainRetry = new(memBlock) RetryValue(memBlock);
    remainRetry->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, OCTETSTRING_TAG_CODE))
    || (tag1 == MAKE_TAG_ID (UNIV, CONS, OCTETSTRING_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    setupInformation = new(memBlock) SetUpValues(memBlock);
    setupInformation->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, BOOLEAN_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    routeUsedReq = new(memBlock) RouteUsedFlag(memBlock);
    routeUsedReq->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 30)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTACommonArguments(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0198: Length discrepancy on sequence.";
  }
  else
    return;
} // RouteSelectRequestArgument::BDecContent

AsnLen RouteSelectRequestArgument::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void RouteSelectRequestArgument::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135070336: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int RouteSelectRequestArgument::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int RouteSelectRequestArgument::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void RouteSelectRequestArgument::Print ( CTsvcLIB::LOG& os ) const
{
  os << "RouteSelectRequestArgument SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "crossRefIdentifier : ";
  os << crossRefIdentifier;
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "routeSelected : ";
  if (NOT_NULL (routeSelected))
    os << *routeSelected;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "remainRetry : ";
  if (NOT_NULL (remainRetry))
    os << *remainRetry;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "setupInformation : ";
  if (NOT_NULL (setupInformation))
    os << *setupInformation;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "routeUsedReq : ";
  if (NOT_NULL (routeUsedReq))
    os << *routeUsedReq;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // RouteSelectRequestArgument::Print


RouteUsedRequestArgument::RouteUsedRequestArgument( MemBlock* mb ) : AsnType( mb )
    , crossRefIdentifier( mb )
{
  routeUsed = NULL; // incomplete initialization of mandatory element!
  callingDevice = NULL;
  domain = NULL;
  extensions = NULL;
}

RouteUsedRequestArgument::RouteUsedRequestArgument( MemBlock* mb, const RouteUsedRequestArgument & ) : AsnType( mb )
    , crossRefIdentifier( mb )
{
  throw "ERROR C0099: Use of incompletely defined RouteUsedRequestArgument::RouteUsedRequestArgument (const RouteUsedRequestArgument &)";
  abort();
}

RouteUsedRequestArgument::~RouteUsedRequestArgument()
{
}

AsnType *RouteUsedRequestArgument::Clone() const
{
  return new(memBlock) RouteUsedRequestArgument(memBlock);
}

RouteUsedRequestArgument &RouteUsedRequestArgument::operator = (const RouteUsedRequestArgument &that)
{
  if (this != &that)
  {
    crossRefIdentifier = that.crossRefIdentifier;
    if (that.routeUsed)
    {
      if (!routeUsed)
        routeUsed = new(memBlock) CalledDeviceID(memBlock);
      *routeUsed = *that.routeUsed;
    }
    else
    {
      routeUsed = NULL;
    }
    if (that.callingDevice)
    {
      if (!callingDevice)
        callingDevice = new(memBlock) CallingDeviceID(memBlock);
      *callingDevice = *that.callingDevice;
    }
    else
    {
      callingDevice = NULL;
    }
    if (that.domain)
    {
      if (!domain)
        domain = new(memBlock) DomainValue(memBlock);
      *domain = *that.domain;
    }
    else
    {
      domain = NULL;
    }
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTACommonArguments(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
RouteUsedRequestArgument::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 30);
    totalLen += l;
  }

  if (NOT_NULL (domain))
  {
    l = domain->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, BOOLEAN_TAG_CODE);
    totalLen += l;
  }

  if (NOT_NULL (callingDevice))
  {
      BEncEocIfNec (b);
    l = callingDevice->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 1);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = routeUsed->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 2);
    totalLen += l;

    l = crossRefIdentifier.BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, APPL, PRIM, 24);
    totalLen += l;

  return totalLen;
} // RouteUsedRequestArgument::BEncContent


void RouteUsedRequestArgument::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  AsnLen elmtLen2;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, PRIM, 24))
    || (tag1 == MAKE_TAG_ID (APPL, CONS, 24)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    crossRefIdentifier.BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0199: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 2)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    routeUsed = new(memBlock) CalledDeviceID(memBlock);
    routeUsed->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0200: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 1)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    callingDevice = new(memBlock) CallingDeviceID(memBlock);
    callingDevice->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, BOOLEAN_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    domain = new(memBlock) DomainValue(memBlock);
    domain->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 30)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTACommonArguments(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0201: Length discrepancy on sequence.";
  }
  else
    return;
} // RouteUsedRequestArgument::BDecContent

AsnLen RouteUsedRequestArgument::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void RouteUsedRequestArgument::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135070408: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int RouteUsedRequestArgument::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int RouteUsedRequestArgument::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void RouteUsedRequestArgument::Print ( CTsvcLIB::LOG& os ) const
{
  os << "RouteUsedRequestArgument SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "crossRefIdentifier : ";
  os << crossRefIdentifier;
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "routeUsed : ";
  if (NOT_NULL (routeUsed))
    os << *routeUsed;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "callingDevice : ";
  if (NOT_NULL (callingDevice))
    os << *callingDevice;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "domain : ";
  if (NOT_NULL (domain))
    os << *domain;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // RouteUsedRequestArgument::Print


RouteEndRequestArgument::RouteEndRequestArgument( MemBlock* mb ) : AsnType( mb )
    , crossRefIdentifier( mb )
{
  errorValue = NULL;
  extensions = NULL;
}

RouteEndRequestArgument::RouteEndRequestArgument( MemBlock* mb, const RouteEndRequestArgument & ) : AsnType( mb )
    , crossRefIdentifier( mb )
{
  throw "ERROR C0099: Use of incompletely defined RouteEndRequestArgument::RouteEndRequestArgument (const RouteEndRequestArgument &)";
  abort();
}

RouteEndRequestArgument::~RouteEndRequestArgument()
{
}

AsnType *RouteEndRequestArgument::Clone() const
{
  return new(memBlock) RouteEndRequestArgument(memBlock);
}

RouteEndRequestArgument &RouteEndRequestArgument::operator = (const RouteEndRequestArgument &that)
{
  if (this != &that)
  {
    crossRefIdentifier = that.crossRefIdentifier;
    if (that.errorValue)
    {
      if (!errorValue)
        errorValue = new(memBlock) UniversalFailure(memBlock);
      *errorValue = *that.errorValue;
    }
    else
    {
      errorValue = NULL;
    }
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTACommonArguments(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
RouteEndRequestArgument::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 30);
    totalLen += l;
  }

  if (NOT_NULL (errorValue))
  {
    l = errorValue->BEncContent (b);
    totalLen += l;
  }

    l = crossRefIdentifier.BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, APPL, PRIM, 24);
    totalLen += l;

  return totalLen;
} // RouteEndRequestArgument::BEncContent


void RouteEndRequestArgument::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, PRIM, 24))
    || (tag1 == MAKE_TAG_ID (APPL, CONS, 24)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    crossRefIdentifier.BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0202: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 1))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 2))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 3))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 4))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 5))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 6))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 7))
    || (tag1 == MAKE_TAG_ID (APPL, CONS, 29)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    errorValue = new(memBlock) UniversalFailure(memBlock);
    errorValue->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 30)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTACommonArguments(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0203: Length discrepancy on sequence.";
  }
  else
    return;
} // RouteEndRequestArgument::BDecContent

AsnLen RouteEndRequestArgument::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void RouteEndRequestArgument::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135070512: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int RouteEndRequestArgument::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int RouteEndRequestArgument::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void RouteEndRequestArgument::Print ( CTsvcLIB::LOG& os ) const
{
  os << "RouteEndRequestArgument SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "crossRefIdentifier : ";
  os << crossRefIdentifier;
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "errorValue : ";
  if (NOT_NULL (errorValue))
    os << *errorValue;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // RouteEndRequestArgument::Print


SystemStatusArgument::SystemStatusArgument( MemBlock* mb ) : AsnType( mb )
{
  choiceId = systemStatusCid;
  systemStatus = NULL; // incomplete initialization of mandatory element!
}

SystemStatusArgument::SystemStatusArgument( MemBlock* mb, const SystemStatusArgument & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined SystemStatusArgument::SystemStatusArgument (const SystemStatusArgument &)";
  abort();
}

SystemStatusArgument::~SystemStatusArgument()
{
} // end of destructor

AsnType *SystemStatusArgument::Clone() const
{
  return new(memBlock) SystemStatusArgument(memBlock);
}

SystemStatusArgument &SystemStatusArgument::operator = (const SystemStatusArgument &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case systemStatusCid:
        systemStatus = new(memBlock) SystemStatus(memBlock);
        *systemStatus = *that.systemStatus;
        break;
      case systemStatusArgumentSeqCid:
        systemStatusArgumentSeq = new(memBlock) SystemStatusArgumentSeq(memBlock);
        *systemStatusArgumentSeq = *that.systemStatusArgumentSeq;
        break;
    }
  }

  return *this;
}

AsnLen
SystemStatusArgument::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case systemStatusCid:
      l = systemStatus->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, ENUM_TAG_CODE);
      break;

    case systemStatusArgumentSeqCid:
      BEncEocIfNec (b);
      l = systemStatusArgumentSeq->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
      break;

  } // end switch
  return l;
} // SystemStatusArgument::BEncContent


void SystemStatusArgument::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (UNIV, PRIM, ENUM_TAG_CODE):
      choiceId = systemStatusCid;
      systemStatus = new(memBlock) SystemStatus(memBlock);
        systemStatus->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE):
      choiceId = systemStatusArgumentSeqCid;
      systemStatusArgumentSeq = new(memBlock) SystemStatusArgumentSeq(memBlock);
        systemStatusArgumentSeq->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0204: Unexpected tag in CHOICE";
      break;
  } // end switch
} // SystemStatusArgument::BDecContent


AsnLen SystemStatusArgument::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void SystemStatusArgument::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int SystemStatusArgument::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int SystemStatusArgument::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void SystemStatusArgument::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case systemStatusCid: os << "SystemStatus*"; break;
    case systemStatusArgumentSeqCid: os << "SystemStatusArgumentSeq*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case systemStatusCid:
      os << "systemStatus : ";
      if (systemStatus)
        os << *systemStatus;
      else
        os << "VOID";
      break;

    case systemStatusArgumentSeqCid:
      if (systemStatusArgumentSeq)
        os << *systemStatusArgumentSeq;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // SystemStatusArgument::Print

MonitorStartResult::MonitorStartResult( MemBlock* mb ) : AsnType( mb )
    , crossRefIdentifier( mb )
{
  monitorFilter = NULL;
  extensions = NULL;
}

MonitorStartResult::MonitorStartResult( MemBlock* mb, const MonitorStartResult & ) : AsnType( mb )
    , crossRefIdentifier( mb )
{
  throw "ERROR C0099: Use of incompletely defined MonitorStartResult::MonitorStartResult (const MonitorStartResult &)";
  abort();
}

MonitorStartResult::~MonitorStartResult()
{
}

AsnType *MonitorStartResult::Clone() const
{
  return new(memBlock) MonitorStartResult(memBlock);
}

MonitorStartResult &MonitorStartResult::operator = (const MonitorStartResult &that)
{
  if (this != &that)
  {
    crossRefIdentifier = that.crossRefIdentifier;
    if (that.monitorFilter)
    {
      if (!monitorFilter)
        monitorFilter = new(memBlock) MonitorFilter(memBlock);
      *monitorFilter = *that.monitorFilter;
    }
    else
    {
      monitorFilter = NULL;
    }
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTAPrivateData(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
MonitorStartResult::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 29);
    totalLen += l;
  }

  if (NOT_NULL (monitorFilter))
  {
      BEncEocIfNec (b);
    l = monitorFilter->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
    totalLen += l;
  }

    l = crossRefIdentifier.BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, APPL, PRIM, 21);
    totalLen += l;

  return totalLen;
} // MonitorStartResult::BEncContent


void MonitorStartResult::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, PRIM, 21))
    || (tag1 == MAKE_TAG_ID (APPL, CONS, 21)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    crossRefIdentifier.BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0205: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    monitorFilter = new(memBlock) MonitorFilter(memBlock);
    monitorFilter->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 29)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTAPrivateData(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0206: Length discrepancy on sequence.";
  }
  else
    return;
} // MonitorStartResult::BDecContent

AsnLen MonitorStartResult::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void MonitorStartResult::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135071064: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int MonitorStartResult::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int MonitorStartResult::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void MonitorStartResult::Print ( CTsvcLIB::LOG& os ) const
{
  os << "MonitorStartResult SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "crossRefIdentifier : ";
  os << crossRefIdentifier;
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "monitorFilter : ";
  if (NOT_NULL (monitorFilter))
    os << *monitorFilter;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // MonitorStartResult::Print


ChangeMonitorFilterArgument::ChangeMonitorFilterArgument( MemBlock* mb ) : AsnType( mb )
    , monitorCrossRefID( mb )
{
  filterlist = NULL; // incomplete initialization of mandatory element!
  extensions = NULL;
}

ChangeMonitorFilterArgument::ChangeMonitorFilterArgument( MemBlock* mb, const ChangeMonitorFilterArgument & ) : AsnType( mb )
    , monitorCrossRefID( mb )
{
  throw "ERROR C0099: Use of incompletely defined ChangeMonitorFilterArgument::ChangeMonitorFilterArgument (const ChangeMonitorFilterArgument &)";
  abort();
}

ChangeMonitorFilterArgument::~ChangeMonitorFilterArgument()
{
}

AsnType *ChangeMonitorFilterArgument::Clone() const
{
  return new(memBlock) ChangeMonitorFilterArgument(memBlock);
}

ChangeMonitorFilterArgument &ChangeMonitorFilterArgument::operator = (const ChangeMonitorFilterArgument &that)
{
  if (this != &that)
  {
    monitorCrossRefID = that.monitorCrossRefID;
    if (that.filterlist)
    {
      if (!filterlist)
        filterlist = new(memBlock) MonitorFilter(memBlock);
      *filterlist = *that.filterlist;
    }
    else
    {
      filterlist = NULL;
    }
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTACommonArguments(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
ChangeMonitorFilterArgument::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 30);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = filterlist->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
    totalLen += l;

    l = monitorCrossRefID.BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, APPL, PRIM, 21);
    totalLen += l;

  return totalLen;
} // ChangeMonitorFilterArgument::BEncContent


void ChangeMonitorFilterArgument::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, PRIM, 21))
    || (tag1 == MAKE_TAG_ID (APPL, CONS, 21)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    monitorCrossRefID.BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0207: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    filterlist = new(memBlock) MonitorFilter(memBlock);
    filterlist->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0208: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 30)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTACommonArguments(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0209: Length discrepancy on sequence.";
  }
  else
    return;
} // ChangeMonitorFilterArgument::BDecContent

AsnLen ChangeMonitorFilterArgument::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void ChangeMonitorFilterArgument::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135071160: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int ChangeMonitorFilterArgument::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ChangeMonitorFilterArgument::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ChangeMonitorFilterArgument::Print ( CTsvcLIB::LOG& os ) const
{
  os << "ChangeMonitorFilterArgument SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "monitorCrossRefID : ";
  os << monitorCrossRefID;
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "filterlist : ";
  if (NOT_NULL (filterlist))
    os << *filterlist;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // ChangeMonitorFilterArgument::Print


ChangeMonitorFilterResult::ChangeMonitorFilterResult( MemBlock* mb ) : AsnType( mb )
{
  choiceId = filterListCid;
  filterList = NULL; // incomplete initialization of mandatory element!
}

ChangeMonitorFilterResult::ChangeMonitorFilterResult( MemBlock* mb, const ChangeMonitorFilterResult & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined ChangeMonitorFilterResult::ChangeMonitorFilterResult (const ChangeMonitorFilterResult &)";
  abort();
}

ChangeMonitorFilterResult::~ChangeMonitorFilterResult()
{
} // end of destructor

AsnType *ChangeMonitorFilterResult::Clone() const
{
  return new(memBlock) ChangeMonitorFilterResult(memBlock);
}

ChangeMonitorFilterResult &ChangeMonitorFilterResult::operator = (const ChangeMonitorFilterResult &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case filterListCid:
        filterList = new(memBlock) MonitorFilter(memBlock);
        *filterList = *that.filterList;
        break;
      case changeMonitorFilterResultSeqCid:
        changeMonitorFilterResultSeq = new(memBlock) ChangeMonitorFilterResultSeq(memBlock);
        *changeMonitorFilterResultSeq = *that.changeMonitorFilterResultSeq;
        break;
    }
  }

  return *this;
}

AsnLen
ChangeMonitorFilterResult::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case filterListCid:
      BEncEocIfNec (b);
      l = filterList->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, CNTX, CONS, 0);
      break;

    case changeMonitorFilterResultSeqCid:
      BEncEocIfNec (b);
      l = changeMonitorFilterResultSeq->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
      break;

  } // end switch
  return l;
} // ChangeMonitorFilterResult::BEncContent


void ChangeMonitorFilterResult::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (CNTX, CONS, 0):
      choiceId = filterListCid;
      filterList = new(memBlock) MonitorFilter(memBlock);
        filterList->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE):
      choiceId = changeMonitorFilterResultSeqCid;
      changeMonitorFilterResultSeq = new(memBlock) ChangeMonitorFilterResultSeq(memBlock);
        changeMonitorFilterResultSeq->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0210: Unexpected tag in CHOICE";
      break;
  } // end switch
} // ChangeMonitorFilterResult::BDecContent


AsnLen ChangeMonitorFilterResult::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void ChangeMonitorFilterResult::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int ChangeMonitorFilterResult::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ChangeMonitorFilterResult::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ChangeMonitorFilterResult::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case filterListCid: os << "MonitorFilter*"; break;
    case changeMonitorFilterResultSeqCid: os << "ChangeMonitorFilterResultSeq*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case filterListCid:
      os << "filterList : ";
      if (filterList)
        os << *filterList;
      else
        os << "VOID";
      break;

    case changeMonitorFilterResultSeqCid:
      if (changeMonitorFilterResultSeq)
        os << *changeMonitorFilterResultSeq;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // ChangeMonitorFilterResult::Print

MonitorStopArgument::MonitorStopArgument( MemBlock* mb ) : AsnType( mb )
{
  choiceId = crossRefIdentifierCid;
  crossRefIdentifier = NULL; // incomplete initialization of mandatory element!
}

MonitorStopArgument::MonitorStopArgument( MemBlock* mb, const MonitorStopArgument & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined MonitorStopArgument::MonitorStopArgument (const MonitorStopArgument &)";
  abort();
}

MonitorStopArgument::~MonitorStopArgument()
{
} // end of destructor

AsnType *MonitorStopArgument::Clone() const
{
  return new(memBlock) MonitorStopArgument(memBlock);
}

MonitorStopArgument &MonitorStopArgument::operator = (const MonitorStopArgument &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case crossRefIdentifierCid:
        crossRefIdentifier = new(memBlock) MonitorCrossRefID(memBlock);
        *crossRefIdentifier = *that.crossRefIdentifier;
        break;
      case monitorStopArgumentSeqCid:
        monitorStopArgumentSeq = new(memBlock) MonitorStopArgumentSeq(memBlock);
        *monitorStopArgumentSeq = *that.monitorStopArgumentSeq;
        break;
    }
  }

  return *this;
}

AsnLen
MonitorStopArgument::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case crossRefIdentifierCid:
      l = crossRefIdentifier->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, APPL, PRIM, 21);
      break;

    case monitorStopArgumentSeqCid:
      BEncEocIfNec (b);
      l = monitorStopArgumentSeq->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
      break;

  } // end switch
  return l;
} // MonitorStopArgument::BEncContent


void MonitorStopArgument::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (APPL, PRIM, 21):
    case MAKE_TAG_ID (APPL, CONS, 21):
      choiceId = crossRefIdentifierCid;
      crossRefIdentifier = new(memBlock) MonitorCrossRefID(memBlock);
        crossRefIdentifier->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE):
      choiceId = monitorStopArgumentSeqCid;
      monitorStopArgumentSeq = new(memBlock) MonitorStopArgumentSeq(memBlock);
        monitorStopArgumentSeq->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0211: Unexpected tag in CHOICE";
      break;
  } // end switch
} // MonitorStopArgument::BDecContent


AsnLen MonitorStopArgument::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void MonitorStopArgument::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int MonitorStopArgument::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int MonitorStopArgument::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void MonitorStopArgument::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case crossRefIdentifierCid: os << "MonitorCrossRefID*"; break;
    case monitorStopArgumentSeqCid: os << "MonitorStopArgumentSeq*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case crossRefIdentifierCid:
      os << "crossRefIdentifier : ";
      if (crossRefIdentifier)
        os << *crossRefIdentifier;
      else
        os << "VOID";
      break;

    case monitorStopArgumentSeqCid:
      if (monitorStopArgumentSeq)
        os << *monitorStopArgumentSeq;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // MonitorStopArgument::Print

SnapshotDeviceArgument::SnapshotDeviceArgument( MemBlock* mb ) : AsnType( mb )
{
  choiceId = snapshotObjectCid;
  snapshotObject = NULL; // incomplete initialization of mandatory element!
}

SnapshotDeviceArgument::SnapshotDeviceArgument( MemBlock* mb, const SnapshotDeviceArgument & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined SnapshotDeviceArgument::SnapshotDeviceArgument (const SnapshotDeviceArgument &)";
  abort();
}

SnapshotDeviceArgument::~SnapshotDeviceArgument()
{
} // end of destructor

AsnType *SnapshotDeviceArgument::Clone() const
{
  return new(memBlock) SnapshotDeviceArgument(memBlock);
}

SnapshotDeviceArgument &SnapshotDeviceArgument::operator = (const SnapshotDeviceArgument &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case snapshotObjectCid:
        snapshotObject = new(memBlock) DeviceID(memBlock);
        *snapshotObject = *that.snapshotObject;
        break;
      case snapshotDeviceArgumentSeqCid:
        snapshotDeviceArgumentSeq = new(memBlock) SnapshotDeviceArgumentSeq(memBlock);
        *snapshotDeviceArgumentSeq = *that.snapshotDeviceArgumentSeq;
        break;
    }
  }

  return *this;
}

AsnLen
SnapshotDeviceArgument::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case snapshotObjectCid:
      l = snapshotObject->BEncContent (b);
      break;

    case snapshotDeviceArgumentSeqCid:
      BEncEocIfNec (b);
      l = snapshotDeviceArgumentSeq->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
      break;

  } // end switch
  return l;
} // SnapshotDeviceArgument::BEncContent


void SnapshotDeviceArgument::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (CNTX, PRIM, 0):
    case MAKE_TAG_ID (CNTX, CONS, 0):
    case MAKE_TAG_ID (CNTX, PRIM, 1):
      choiceId = snapshotObjectCid;
      snapshotObject = new(memBlock) DeviceID(memBlock);
        snapshotObject->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE):
      choiceId = snapshotDeviceArgumentSeqCid;
      snapshotDeviceArgumentSeq = new(memBlock) SnapshotDeviceArgumentSeq(memBlock);
        snapshotDeviceArgumentSeq->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0212: Unexpected tag in CHOICE";
      break;
  } // end switch
} // SnapshotDeviceArgument::BDecContent


AsnLen SnapshotDeviceArgument::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void SnapshotDeviceArgument::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int SnapshotDeviceArgument::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int SnapshotDeviceArgument::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void SnapshotDeviceArgument::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case snapshotObjectCid: os << "DeviceID*"; break;
    case snapshotDeviceArgumentSeqCid: os << "SnapshotDeviceArgumentSeq*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case snapshotObjectCid:
      os << "snapshotObject : ";
      if (snapshotObject)
        os << *snapshotObject;
      else
        os << "VOID";
      break;

    case snapshotDeviceArgumentSeqCid:
      if (snapshotDeviceArgumentSeq)
        os << *snapshotDeviceArgumentSeq;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // SnapshotDeviceArgument::Print

ConnectionID::ConnectionID( MemBlock* mb ) : AsnType( mb )
{
  call = NULL;
  device = NULL;
}

ConnectionID::ConnectionID( MemBlock* mb, const ConnectionID & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined ConnectionID::ConnectionID (const ConnectionID &)";
  abort();
}

ConnectionID::~ConnectionID()
{
}

AsnType *ConnectionID::Clone() const
{
  return new(memBlock) ConnectionID(memBlock);
}

ConnectionID &ConnectionID::operator = (const ConnectionID &that)
{
  if (this != &that)
  {
    if (that.call)
    {
      if (!call)
        call = new(memBlock) AsnOcts(memBlock);
      *call = *that.call;
    }
    else
    {
      call = NULL;
    }
    if (that.device)
    {
      if (!device)
        device = new(memBlock) ConnectionIDChoice(memBlock);
      *device = *that.device;
    }
    else
    {
      device = NULL;
    }
  }

  return *this;
}

AsnLen
ConnectionID::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (device))
  {
    l = device->BEncContent (b);
    totalLen += l;
  }

  if (NOT_NULL (call))
  {
    l = call->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 2);
    totalLen += l;
  }

  return totalLen;
} // ConnectionID::BEncContent


void ConnectionID::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  if (elmtLen0 == 0)
    return;
  else
  {
    tag1 = BDecTag (b, seqBytesDecoded);

    if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
    {
      BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
      bytesDecoded += seqBytesDecoded;
      return;
    }
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 2))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 2)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    call = new(memBlock) AsnOcts(memBlock);
    call->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 1))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 3))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 3)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    device = new(memBlock) ConnectionIDChoice(memBlock);
    device->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0213: Length discrepancy on sequence.";
  }
  else
    return;
} // ConnectionID::BDecContent

AsnLen ConnectionID::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, APPL, CONS, 11);
  return l;
}

void ConnectionID::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (APPL, CONS, 11))
  {
    throw "ERROR C135073416: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int ConnectionID::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ConnectionID::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ConnectionID::Print ( CTsvcLIB::LOG& os ) const
{
  os << "ConnectionID SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "call : ";
  if (NOT_NULL (call))
    os << *call;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "device : ";
  if (NOT_NULL (device))
    os << *device;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // ConnectionID::Print


AsnType *ConnectionIDList::Clone() const
{
  return new(memBlock) ConnectionIDList(memBlock);
}

AsnLen ConnectionIDList::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, APPL, CONS, 12);
  return l;
}

void ConnectionIDList::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (APPL, CONS, 12))
  {
    throw "ERROR C0214: ConnectionIDList.BDec(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

ConnectionIDList::ConnectionIDList( MemBlock* mb, const ConnectionIDList & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined ConnectionIDList::ConnectionIDList (const ConnectionIDList &)";
  abort();
}

ConnectionIDList::~ConnectionIDList()
{
  SetCurrToFirst();
  for (; Curr() != NULL; RemoveCurrFromList())
    ;
} // end of destructor

ConnectionIDList &ConnectionIDList::operator = (const ConnectionIDList &that)
{
  if (this != &that)
  {
    SetCurrToFirst();
    for (; Curr(); RemoveCurrFromList())
      ;

    //that.SetCurrToFirst();
    //for (; that.Curr(); that.GoNext())
    //  AppendCopy (*that.Curr());
    for (const AsnListElmt *run=that.first; run; run=run->next)
      AppendCopy (*run->elmt);
  }

  return *this;
}

void ConnectionIDList::Print ( CTsvcLIB::LOG& os ) const
{
    os << "ConnectionIDList SEQUENCE/SET OF" << CTsvcLIB::eline;
    Indent (os, indentG);
    os << "{" << CTsvcLIB::eline;
    indentG += stdIndentG;
    for (const AsnListElmt *run=first; run; run=run->next)
    {
        Indent (os, indentG);
        os << *run->elmt;
        if (run != last)
            os << ",";
        os << CTsvcLIB::eline;
    }
    indentG -= stdIndentG;
    Indent (os, indentG);
    os << "}";
} // Print


void  ConnectionIDList::SetCurrElmt (unsigned long int index)
{
  unsigned long int i;
  curr = first;
  if (count)
    for (i = 0; (i < (count-1)) && (i < index); i++)
      curr = curr->next;
} // ConnectionIDList::SetCurrElmt


unsigned long int  ConnectionIDList::GetCurrElmtIndex()
{
    unsigned long int i;
    AsnListElmt *tmp;
    if (curr != NULL)
    {
        for (i = 0, tmp = first; tmp != NULL; i++)
        {
            if (tmp == curr)
                return i;
            else
                tmp = tmp->next;
        }
    }
    return count;
} // ConnectionIDList::GetCurrElmtIndex


// alloc new list elmt, put at end of list
//  and return the component type
ConnectionID *ConnectionIDList::Append()
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt  = new(memBlock) ConnectionID(memBlock);
    newElmt->next = NULL;
    if (last == NULL)
    {
        newElmt->prev = NULL;
        first = last  = newElmt;
    }
    else
    {
        newElmt->prev = last;
        last->next    = newElmt;
        last          = newElmt;
    }
    count++;
    return (curr = newElmt)->elmt;
} // ConnectionIDList::Append


// alloc new list elmt, put at begining of list
//  and return the component type
ConnectionID  *ConnectionIDList::Prepend()
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) ConnectionID(memBlock);
    newElmt->prev = NULL;
    if (first == NULL)
    {
        newElmt->next = NULL;
        first = last  = newElmt;
    }
    else
    {
        newElmt->next = first;
        first->prev   = newElmt;
        first         = newElmt;
    }
    count++;
    return (curr = newElmt)->elmt;
} // ConnectionIDList::Prepend


// alloc new list elmt, insert it before the
// current element and return the component type
// if the current element is null, the new element
// is placed at the beginning of the list.
ConnectionID  *ConnectionIDList::InsertBefore()
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) ConnectionID(memBlock);
    if (curr == NULL)
    {
        newElmt->next = first;
        newElmt->prev = NULL;
        first = newElmt;
        if (last == NULL)
            last = newElmt;
    }
    else
    {
        newElmt->next = curr;
        newElmt->prev = curr->prev;
        curr->prev = newElmt;
        if (curr == first)
            first = newElmt;
        else
            newElmt->prev->next = newElmt;
    }
    count++;
    return (curr = newElmt)->elmt;
} // ConnectionIDList::InsertBefore


// alloc new list elmt, insert it after the
// current element and return the component type
// if the current element is null, the new element
// is placed at the end of the list.
ConnectionID *ConnectionIDList::InsertAfter()
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) ConnectionID(memBlock);
    if (curr == NULL)
    {
        newElmt->prev = last;
        newElmt->next = NULL;
        last = newElmt;
        if (first == NULL)
            first = newElmt;
    }
    else
    {
        newElmt->prev = curr;
        newElmt->next = curr->next;
        curr->next = newElmt;
        if (curr == last)
            last = newElmt;
        else
            newElmt->next->prev = newElmt;
    }
    count++;
    return (curr = newElmt)->elmt;
} // ConnectionIDList::InsertAfter


ConnectionIDList  &ConnectionIDList::AppendCopy (ConnectionID &elmt)
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) ConnectionID(memBlock);
    *newElmt->elmt = elmt;
    newElmt->next = NULL;
    if (last == NULL)
    {
        newElmt->prev = NULL;
        first = last  = newElmt;
    }
    else
    {
        newElmt->prev = last;
        last->next    = newElmt;
        last          = newElmt;
    }
    count++;
    return *this;
} // AppendCopy


ConnectionIDList  &ConnectionIDList::PrependCopy (ConnectionID &elmt)
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) ConnectionID(memBlock);
    *newElmt->elmt = elmt;
    newElmt->prev = NULL;
    if (first == NULL)
    {
        newElmt->next = NULL;
        first = last  = newElmt;
    }
    else
    {
        newElmt->next = first;
        first->prev   = newElmt;
        first         = newElmt;
    }
    count++;
    return *this;
} // ConnectionIDList::PrependCopy


// alloc new list elmt, insert it before the
// current element, copy the given elmt into the new elmt
// and return the component type.
// if the current element is null, the new element
// is placed at the beginning of the list.
ConnectionIDList &ConnectionIDList::InsertBeforeAndCopy (ConnectionID &elmt)
{
    AsnListElmt *newElmt;

    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) ConnectionID(memBlock);
    *newElmt->elmt = elmt;

    if (curr == NULL)
    {
        newElmt->next = first;
        newElmt->prev = NULL;
        first = newElmt;
        if (last == NULL)
            last = newElmt;
    }
    else
    {
        newElmt->next = curr;
        newElmt->prev = curr->prev;
        curr->prev = newElmt;
        if (curr == first)
            first = newElmt;
        else
            newElmt->prev->next = newElmt;
    }
    count++;
    return *this;
} // ConnectionIDList::InsertBeforeAndCopy


// alloc new list elmt, insert it after the
// current element, copy given elmt in to new elmt
//  and return the component type
// if the current element is null, the new element
// is placed at the end of the list.
ConnectionIDList  &ConnectionIDList::InsertAfterAndCopy (ConnectionID &elmt)
{
    AsnListElmt *newElmt;

    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) ConnectionID(memBlock);
    *newElmt->elmt = elmt;
    if (curr == NULL)
    {
        newElmt->prev = last;
        newElmt->next = NULL;
        last = newElmt;
        if (first == NULL)
            first = newElmt;
    }
    else
    {
        newElmt->prev = curr;
        newElmt->next = curr->next;
        curr->next = newElmt;
        if (curr == last)
            last = newElmt;
        else
            newElmt->next->prev = newElmt;
    }
    count++;
    return *this;
} // ConnectionIDList::InsertAfterAndCopy


// remove current element from list if current element is not NULL 
// The new current element will be the next element.
// If the current element is the last element in the list
// the second but last element will become the new current element.
void ConnectionIDList::RemoveCurrFromList()
{
    AsnListElmt *del_elmt;

    if (curr != NULL)
    {
        del_elmt = curr;
        count--;

        if (count == 0)
            first = last = curr = NULL;
        else if (curr == first)
        {
            curr = first= first->next;
            first->prev = NULL;
        }
        else if (curr == last)
        {
            curr = last = last->prev;
            last->next = NULL;
        }
        else
        {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
        }

    }
}


AsnLen ConnectionIDList::BEncContent (AsnBuf& b)
{
    AsnListElmt *currElmt;
    AsnLen elmtLen;
    AsnLen totalLen = 0;
    for (currElmt = last; currElmt != NULL; currElmt = currElmt->prev)
    {
      BEncEocIfNec (b);
        elmtLen = currElmt->elmt->BEncContent (b);
    elmtLen += BEncConsLen (b, elmtLen);

    elmtLen += BEncTag1 (b, APPL, CONS, 11);
        totalLen += elmtLen;
    }
    return totalLen;
} // ConnectionIDList::BEncContent


void  ConnectionIDList::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0,
                                  AsnLen &bytesDecoded)
{
    ConnectionID *listElmt;
    AsnTag tag1;
    AsnLen listBytesDecoded = 0;
    AsnLen elmtLen1;

    while ((listBytesDecoded < elmtLen0) || (elmtLen0 == INDEFINITE_LEN))
    {
        tag1 = BDecTag (b, listBytesDecoded);
        if ((tag1 == EOC_TAG_ID) && (elmtLen0 == INDEFINITE_LEN))
        {
            BDEC_2ND_EOC_OCTET (b, listBytesDecoded);
            break;
        }
        if ((tag1 != MAKE_TAG_ID (APPL, CONS, 11) ))
        {
            throw "ERROR C0215: Unexpected Tag";
        }

        elmtLen1 = BDecLen (b, listBytesDecoded);
        listElmt = Append();
        listElmt->BDecContent (b, tag1, elmtLen1, listBytesDecoded);
    }

    bytesDecoded += listBytesDecoded;
} // ConnectionIDList::BDecContent


SnapshotCallResponseInfo::SnapshotCallResponseInfo( MemBlock* mb ) : AsnType( mb )
{
  deviceOnCall = NULL; // incomplete initialization of mandatory element!
  callIdentifier = NULL; // incomplete initialization of mandatory element!
  localConnectionState = NULL;
}

SnapshotCallResponseInfo::SnapshotCallResponseInfo( MemBlock* mb, const SnapshotCallResponseInfo & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined SnapshotCallResponseInfo::SnapshotCallResponseInfo (const SnapshotCallResponseInfo &)";
  abort();
}

SnapshotCallResponseInfo::~SnapshotCallResponseInfo()
{
}

AsnType *SnapshotCallResponseInfo::Clone() const
{
  return new(memBlock) SnapshotCallResponseInfo(memBlock);
}

SnapshotCallResponseInfo &SnapshotCallResponseInfo::operator = (const SnapshotCallResponseInfo &that)
{
  if (this != &that)
  {
    if (that.deviceOnCall)
    {
      if (!deviceOnCall)
        deviceOnCall = new(memBlock) SubjectDeviceID(memBlock);
      *deviceOnCall = *that.deviceOnCall;
    }
    else
    {
      deviceOnCall = NULL;
    }
    if (that.callIdentifier)
    {
      if (!callIdentifier)
        callIdentifier = new(memBlock) ConnectionID(memBlock);
      *callIdentifier = *that.callIdentifier;
    }
    else
    {
      callIdentifier = NULL;
    }
    if (that.localConnectionState)
    {
      if (!localConnectionState)
        localConnectionState = new(memBlock) LocalConnectionState(memBlock);
      *localConnectionState = *that.localConnectionState;
    }
    else
    {
      localConnectionState = NULL;
    }
  }

  return *this;
}

AsnLen
SnapshotCallResponseInfo::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (localConnectionState))
  {
    l = localConnectionState->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, APPL, PRIM, 14);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = callIdentifier->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;

      BEncEocIfNec (b);
    l = deviceOnCall->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 3);
    totalLen += l;

  return totalLen;
} // SnapshotCallResponseInfo::BEncContent


void SnapshotCallResponseInfo::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  AsnLen elmtLen2;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 3)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    deviceOnCall = new(memBlock) SubjectDeviceID(memBlock);
    deviceOnCall->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0216: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    callIdentifier = new(memBlock) ConnectionID(memBlock);
    callIdentifier->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0217: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, PRIM, 14)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    localConnectionState = new(memBlock) LocalConnectionState(memBlock);
    localConnectionState->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0218: Length discrepancy on sequence.";
  }
  else
    return;
} // SnapshotCallResponseInfo::BDecContent

AsnLen SnapshotCallResponseInfo::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void SnapshotCallResponseInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135074728: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int SnapshotCallResponseInfo::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int SnapshotCallResponseInfo::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void SnapshotCallResponseInfo::Print ( CTsvcLIB::LOG& os ) const
{
  os << "SnapshotCallResponseInfo SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "deviceOnCall : ";
  if (NOT_NULL (deviceOnCall))
    os << *deviceOnCall;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "callIdentifier : ";
  if (NOT_NULL (callIdentifier))
    os << *callIdentifier;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "localConnectionState : ";
  if (NOT_NULL (localConnectionState))
    os << *localConnectionState;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // SnapshotCallResponseInfo::Print


CallState::CallState( MemBlock* mb ) : AsnType( mb )
{
  choiceId = compoundCid;
  compound = NULL; // incomplete initialization of mandatory element!
}

CallState::CallState( MemBlock* mb, const CallState & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined CallState::CallState (const CallState &)";
  abort();
}

CallState::~CallState()
{
} // end of destructor

AsnType *CallState::Clone() const
{
  return new(memBlock) CallState(memBlock);
}

CallState &CallState::operator = (const CallState &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case compoundCid:
        compound = new(memBlock) CompoundCallState(memBlock);
        *compound = *that.compound;
        break;
      case simpleCid:
        simple = new(memBlock) SimpleCallState(memBlock);
        *simple = *that.simple;
        break;
      case unknownCid:
        unknown = new(memBlock) AsnNull(memBlock);
        *unknown = *that.unknown;
        break;
    }
  }

  return *this;
}

AsnLen
CallState::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case compoundCid:
      BEncEocIfNec (b);
      l = compound->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, CNTX, CONS, 0);
      break;

    case simpleCid:
      l = simple->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 1);
      break;

    case unknownCid:
      l = unknown->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 2);
      break;

  } // end switch
  return l;
} // CallState::BEncContent


void CallState::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (CNTX, CONS, 0):
      choiceId = compoundCid;
      compound = new(memBlock) CompoundCallState(memBlock);
        compound->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 1):
      choiceId = simpleCid;
      simple = new(memBlock) SimpleCallState(memBlock);
        simple->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 2):
      choiceId = unknownCid;
      unknown = new(memBlock) AsnNull(memBlock);
        unknown->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0219: Unexpected tag in CHOICE";
      break;
  } // end switch
} // CallState::BDecContent


AsnLen CallState::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void CallState::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int CallState::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int CallState::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void CallState::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case compoundCid: os << "CompoundCallState*"; break;
    case simpleCid: os << "SimpleCallState*"; break;
    case unknownCid: os << "AsnNull*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case compoundCid:
      os << "compound : ";
      if (compound)
        os << *compound;
      else
        os << "VOID";
      break;

    case simpleCid:
      os << "simple : ";
      if (simple)
        os << *simple;
      else
        os << "VOID";
      break;

    case unknownCid:
      os << "unknown : ";
      if (unknown)
        os << *unknown;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // CallState::Print

AgentParameter::AgentParameter( MemBlock* mb ) : AsnType( mb )
{
  choiceId = loggedInCid;
  loggedIn = NULL; // incomplete initialization of mandatory element!
}

AgentParameter::AgentParameter( MemBlock* mb, const AgentParameter & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined AgentParameter::AgentParameter (const AgentParameter &)";
  abort();
}

AgentParameter::~AgentParameter()
{
} // end of destructor

AsnType *AgentParameter::Clone() const
{
  return new(memBlock) AgentParameter(memBlock);
}

AgentParameter &AgentParameter::operator = (const AgentParameter &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case loggedInCid:
        loggedIn = new(memBlock) LoggedOnInfo(memBlock);
        *loggedIn = *that.loggedIn;
        break;
      case loggedOutCid:
        loggedOut = new(memBlock) LoggedOffInfo(memBlock);
        *loggedOut = *that.loggedOut;
        break;
      case notReadyCid:
        notReady = new(memBlock) AsnNull(memBlock);
        *notReady = *that.notReady;
        break;
      case readyCid:
        ready = new(memBlock) AsnNull(memBlock);
        *ready = *that.ready;
        break;
      case workNotReadyCid:
        workNotReady = new(memBlock) AsnNull(memBlock);
        *workNotReady = *that.workNotReady;
        break;
      case workReadyCid:
        workReady = new(memBlock) AsnNull(memBlock);
        *workReady = *that.workReady;
        break;
    }
  }

  return *this;
}

AsnLen
AgentParameter::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case loggedInCid:
      BEncEocIfNec (b);
      l = loggedIn->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, CNTX, CONS, 0);
      break;

    case loggedOutCid:
      BEncEocIfNec (b);
      l = loggedOut->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, CNTX, CONS, 1);
      break;

    case notReadyCid:
      l = notReady->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 2);
      break;

    case readyCid:
      l = ready->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 3);
      break;

    case workNotReadyCid:
      l = workNotReady->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 4);
      break;

    case workReadyCid:
      l = workReady->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 5);
      break;

  } // end switch
  return l;
} // AgentParameter::BEncContent


void AgentParameter::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (CNTX, CONS, 0):
      choiceId = loggedInCid;
      loggedIn = new(memBlock) LoggedOnInfo(memBlock);
        loggedIn->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, CONS, 1):
      choiceId = loggedOutCid;
      loggedOut = new(memBlock) LoggedOffInfo(memBlock);
        loggedOut->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 2):
      choiceId = notReadyCid;
      notReady = new(memBlock) AsnNull(memBlock);
        notReady->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 3):
      choiceId = readyCid;
      ready = new(memBlock) AsnNull(memBlock);
        ready->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 4):
      choiceId = workNotReadyCid;
      workNotReady = new(memBlock) AsnNull(memBlock);
        workNotReady->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 5):
      choiceId = workReadyCid;
      workReady = new(memBlock) AsnNull(memBlock);
        workReady->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0220: Unexpected tag in CHOICE";
      break;
  } // end switch
} // AgentParameter::BDecContent


AsnLen AgentParameter::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void AgentParameter::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int AgentParameter::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int AgentParameter::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void AgentParameter::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case loggedInCid: os << "LoggedOnInfo*"; break;
    case loggedOutCid: os << "LoggedOffInfo*"; break;
    case notReadyCid: os << "AsnNull*"; break;
    case readyCid: os << "AsnNull*"; break;
    case workNotReadyCid: os << "AsnNull*"; break;
    case workReadyCid: os << "AsnNull*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case loggedInCid:
      os << "loggedIn : ";
      if (loggedIn)
        os << *loggedIn;
      else
        os << "VOID";
      break;

    case loggedOutCid:
      os << "loggedOut : ";
      if (loggedOut)
        os << *loggedOut;
      else
        os << "VOID";
      break;

    case notReadyCid:
      os << "notReady : ";
      if (notReady)
        os << *notReady;
      else
        os << "VOID";
      break;

    case readyCid:
      os << "ready : ";
      if (ready)
        os << *ready;
      else
        os << "VOID";
      break;

    case workNotReadyCid:
      os << "workNotReady : ";
      if (workNotReady)
        os << *workNotReady;
      else
        os << "VOID";
      break;

    case workReadyCid:
      os << "workReady : ";
      if (workReady)
        os << *workReady;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // AgentParameter::Print

FeatureInfo::FeatureInfo( MemBlock* mb ) : AsnType( mb )
{
  choiceId = camponCid;
  campon = NULL; // incomplete initialization of mandatory element!
}

FeatureInfo::FeatureInfo( MemBlock* mb, const FeatureInfo & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined FeatureInfo::FeatureInfo (const FeatureInfo &)";
  abort();
}

FeatureInfo::~FeatureInfo()
{
} // end of destructor

AsnType *FeatureInfo::Clone() const
{
  return new(memBlock) FeatureInfo(memBlock);
}

FeatureInfo &FeatureInfo::operator = (const FeatureInfo &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case camponCid:
        campon = new(memBlock) ConnectionID(memBlock);
        *campon = *that.campon;
        break;
      case callbackCid:
        callback = new(memBlock) ConnectionID(memBlock);
        *callback = *that.callback;
        break;
      case intrudeCid:
        intrude = new(memBlock) ConnectionID(memBlock);
        *intrude = *that.intrude;
        break;
      case callbackMessageCid:
        callbackMessage = new(memBlock) ConnectionID(memBlock);
        *callbackMessage = *that.callbackMessage;
        break;
    }
  }

  return *this;
}

AsnLen
FeatureInfo::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case camponCid:
      BEncEocIfNec (b);
      l = campon->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, CNTX, CONS, 0);
      break;

    case callbackCid:
      BEncEocIfNec (b);
      l = callback->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, CNTX, CONS, 1);
      break;

    case intrudeCid:
      BEncEocIfNec (b);
      l = intrude->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, CNTX, CONS, 2);
      break;

    case callbackMessageCid:
      BEncEocIfNec (b);
      l = callbackMessage->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, CNTX, CONS, 3);
      break;

  } // end switch
  return l;
} // FeatureInfo::BEncContent


void FeatureInfo::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (CNTX, CONS, 0):
      choiceId = camponCid;
      campon = new(memBlock) ConnectionID(memBlock);
        campon->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, CONS, 1):
      choiceId = callbackCid;
      callback = new(memBlock) ConnectionID(memBlock);
        callback->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, CONS, 2):
      choiceId = intrudeCid;
      intrude = new(memBlock) ConnectionID(memBlock);
        intrude->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, CONS, 3):
      choiceId = callbackMessageCid;
      callbackMessage = new(memBlock) ConnectionID(memBlock);
        callbackMessage->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0221: Unexpected tag in CHOICE";
      break;
  } // end switch
} // FeatureInfo::BDecContent


AsnLen FeatureInfo::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void FeatureInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int FeatureInfo::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int FeatureInfo::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void FeatureInfo::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case camponCid: os << "ConnectionID*"; break;
    case callbackCid: os << "ConnectionID*"; break;
    case intrudeCid: os << "ConnectionID*"; break;
    case callbackMessageCid: os << "ConnectionID*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case camponCid:
      os << "campon : ";
      if (campon)
        os << *campon;
      else
        os << "VOID";
      break;

    case callbackCid:
      os << "callback : ";
      if (callback)
        os << *callback;
      else
        os << "VOID";
      break;

    case intrudeCid:
      os << "intrude : ";
      if (intrude)
        os << *intrude;
      else
        os << "VOID";
      break;

    case callbackMessageCid:
      os << "callbackMessage : ";
      if (callbackMessage)
        os << *callbackMessage;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // FeatureInfo::Print

SetDeviceFeature::SetDeviceFeature( MemBlock* mb ) : AsnType( mb )
{
  choiceId = msgWaitingOnCid;
  msgWaitingOn = NULL; // incomplete initialization of mandatory element!
}

SetDeviceFeature::SetDeviceFeature( MemBlock* mb, const SetDeviceFeature & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined SetDeviceFeature::SetDeviceFeature (const SetDeviceFeature &)";
  abort();
}

SetDeviceFeature::~SetDeviceFeature()
{
} // end of destructor

AsnType *SetDeviceFeature::Clone() const
{
  return new(memBlock) SetDeviceFeature(memBlock);
}

SetDeviceFeature &SetDeviceFeature::operator = (const SetDeviceFeature &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case msgWaitingOnCid:
        msgWaitingOn = new(memBlock) AsnBool(memBlock);
        *msgWaitingOn = *that.msgWaitingOn;
        break;
      case doNotDisturbOnCid:
        doNotDisturbOn = new(memBlock) AsnBool(memBlock);
        *doNotDisturbOn = *that.doNotDisturbOn;
        break;
      case forwardCid:
        forward = new(memBlock) ForwardParameter(memBlock);
        *forward = *that.forward;
        break;
      case requestedAgentStateCid:
        requestedAgentState = new(memBlock) AgentParameter(memBlock);
        *requestedAgentState = *that.requestedAgentState;
        break;
    }
  }

  return *this;
}

AsnLen
SetDeviceFeature::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case msgWaitingOnCid:
      l = msgWaitingOn->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 0);
      break;

    case doNotDisturbOnCid:
      l = doNotDisturbOn->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, CNTX, PRIM, 1);
      break;

    case forwardCid:
      BEncEocIfNec (b);
      l = forward->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, CNTX, CONS, 2);
      break;

    case requestedAgentStateCid:
      BEncEocIfNec (b);
      l = requestedAgentState->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, CNTX, CONS, 3);
      break;

  } // end switch
  return l;
} // SetDeviceFeature::BEncContent


void SetDeviceFeature::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnLen elmtLen1;
  switch (tag)
  {
    case MAKE_TAG_ID (CNTX, PRIM, 0):
      choiceId = msgWaitingOnCid;
      msgWaitingOn = new(memBlock) AsnBool(memBlock);
        msgWaitingOn->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 1):
      choiceId = doNotDisturbOnCid;
      doNotDisturbOn = new(memBlock) AsnBool(memBlock);
        doNotDisturbOn->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, CONS, 2):
      choiceId = forwardCid;
      forward = new(memBlock) ForwardParameter(memBlock);
        forward->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, CONS, 3):
      tag = BDecTag (b, bytesDecoded);
      elmtLen1 = BDecLen (b, bytesDecoded);
      choiceId = requestedAgentStateCid;
      requestedAgentState = new(memBlock) AgentParameter(memBlock);
        requestedAgentState->BDecContent (b, tag, elmtLen1, bytesDecoded);
      if (elmtLen0 == INDEFINITE_LEN)
        BDecEoc (b, bytesDecoded);
      break;

    default:
      throw "ERROR C0222: Unexpected tag in CHOICE";
      break;
  } // end switch
} // SetDeviceFeature::BDecContent


AsnLen SetDeviceFeature::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void SetDeviceFeature::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int SetDeviceFeature::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int SetDeviceFeature::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void SetDeviceFeature::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case msgWaitingOnCid: os << "AsnBool*"; break;
    case doNotDisturbOnCid: os << "AsnBool*"; break;
    case forwardCid: os << "ForwardParameter*"; break;
    case requestedAgentStateCid: os << "AgentParameter*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case msgWaitingOnCid:
      os << "msgWaitingOn : ";
      if (msgWaitingOn)
        os << *msgWaitingOn;
      else
        os << "VOID";
      break;

    case doNotDisturbOnCid:
      os << "doNotDisturbOn : ";
      if (doNotDisturbOn)
        os << *doNotDisturbOn;
      else
        os << "VOID";
      break;

    case forwardCid:
      os << "forward : ";
      if (forward)
        os << *forward;
      else
        os << "VOID";
      break;

    case requestedAgentStateCid:
      os << "requestedAgentState : ";
      if (requestedAgentState)
        os << *requestedAgentState;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // SetDeviceFeature::Print

DivertInfoSeq1::DivertInfoSeq1( MemBlock* mb ) : AsnType( mb )
{
  callToBePickedUp = NULL; // incomplete initialization of mandatory element!
  requestingDevice = NULL; // incomplete initialization of mandatory element!
}

DivertInfoSeq1::DivertInfoSeq1( MemBlock* mb, const DivertInfoSeq1 & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined DivertInfoSeq1::DivertInfoSeq1 (const DivertInfoSeq1 &)";
  abort();
}

DivertInfoSeq1::~DivertInfoSeq1()
{
}

AsnType *DivertInfoSeq1::Clone() const
{
  return new(memBlock) DivertInfoSeq1(memBlock);
}

DivertInfoSeq1 &DivertInfoSeq1::operator = (const DivertInfoSeq1 &that)
{
  if (this != &that)
  {
    if (that.callToBePickedUp)
    {
      if (!callToBePickedUp)
        callToBePickedUp = new(memBlock) ConnectionID(memBlock);
      *callToBePickedUp = *that.callToBePickedUp;
    }
    else
    {
      callToBePickedUp = NULL;
    }
    if (that.requestingDevice)
    {
      if (!requestingDevice)
        requestingDevice = new(memBlock) DeviceID(memBlock);
      *requestingDevice = *that.requestingDevice;
    }
    else
    {
      requestingDevice = NULL;
    }
  }

  return *this;
}

AsnLen
DivertInfoSeq1::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

    l = requestingDevice->BEncContent (b);
    totalLen += l;

      BEncEocIfNec (b);
    l = callToBePickedUp->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;

  return totalLen;
} // DivertInfoSeq1::BEncContent


void DivertInfoSeq1::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    callToBePickedUp = new(memBlock) ConnectionID(memBlock);
    callToBePickedUp->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0223: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 1)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    requestingDevice = new(memBlock) DeviceID(memBlock);
    requestingDevice->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0224: SEQUENCE is missing non-optional elmt.";
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0225: Length discrepancy on sequence.";
  }
  else
    return;
} // DivertInfoSeq1::BDecContent

AsnLen DivertInfoSeq1::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void DivertInfoSeq1::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135061736: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int DivertInfoSeq1::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int DivertInfoSeq1::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void DivertInfoSeq1::Print ( CTsvcLIB::LOG& os ) const
{
  os << "DivertInfoSeq1 SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "callToBePickedUp : ";
  if (NOT_NULL (callToBePickedUp))
    os << *callToBePickedUp;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "requestingDevice : ";
  if (NOT_NULL (requestingDevice))
    os << *requestingDevice;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // DivertInfoSeq1::Print


DivertInfoSeq::DivertInfoSeq( MemBlock* mb ) : AsnType( mb )
{
  callToBeDiverted = NULL; // incomplete initialization of mandatory element!
  newDestination = NULL; // incomplete initialization of mandatory element!
}

DivertInfoSeq::DivertInfoSeq( MemBlock* mb, const DivertInfoSeq & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined DivertInfoSeq::DivertInfoSeq (const DivertInfoSeq &)";
  abort();
}

DivertInfoSeq::~DivertInfoSeq()
{
}

AsnType *DivertInfoSeq::Clone() const
{
  return new(memBlock) DivertInfoSeq(memBlock);
}

DivertInfoSeq &DivertInfoSeq::operator = (const DivertInfoSeq &that)
{
  if (this != &that)
  {
    if (that.callToBeDiverted)
    {
      if (!callToBeDiverted)
        callToBeDiverted = new(memBlock) ConnectionID(memBlock);
      *callToBeDiverted = *that.callToBeDiverted;
    }
    else
    {
      callToBeDiverted = NULL;
    }
    if (that.newDestination)
    {
      if (!newDestination)
        newDestination = new(memBlock) CalledDeviceID(memBlock);
      *newDestination = *that.newDestination;
    }
    else
    {
      newDestination = NULL;
    }
  }

  return *this;
}

AsnLen
DivertInfoSeq::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

      BEncEocIfNec (b);
    l = newDestination->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 2);
    totalLen += l;

      BEncEocIfNec (b);
    l = callToBeDiverted->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;

  return totalLen;
} // DivertInfoSeq::BEncContent


void DivertInfoSeq::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  AsnLen elmtLen2;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    callToBeDiverted = new(memBlock) ConnectionID(memBlock);
    callToBeDiverted->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0226: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 2)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    newDestination = new(memBlock) CalledDeviceID(memBlock);
    newDestination->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

  }
  else
  {
    throw "ERROR C0227: SEQUENCE is missing non-optional elmt.";
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0228: Length discrepancy on sequence.";
  }
  else
    return;
} // DivertInfoSeq::BDecContent

AsnLen DivertInfoSeq::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void DivertInfoSeq::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135061792: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int DivertInfoSeq::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int DivertInfoSeq::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void DivertInfoSeq::Print ( CTsvcLIB::LOG& os ) const
{
  os << "DivertInfoSeq SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "callToBeDiverted : ";
  if (NOT_NULL (callToBeDiverted))
    os << *callToBeDiverted;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "newDestination : ";
  if (NOT_NULL (newDestination))
    os << *newDestination;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // DivertInfoSeq::Print


ConnectionDetailsSeq::ConnectionDetailsSeq( MemBlock* mb ) : AsnType( mb )
{
  heldCall = NULL; // incomplete initialization of mandatory element!
  activeCall = NULL; // incomplete initialization of mandatory element!
}

ConnectionDetailsSeq::ConnectionDetailsSeq( MemBlock* mb, const ConnectionDetailsSeq & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined ConnectionDetailsSeq::ConnectionDetailsSeq (const ConnectionDetailsSeq &)";
  abort();
}

ConnectionDetailsSeq::~ConnectionDetailsSeq()
{
}

AsnType *ConnectionDetailsSeq::Clone() const
{
  return new(memBlock) ConnectionDetailsSeq(memBlock);
}

ConnectionDetailsSeq &ConnectionDetailsSeq::operator = (const ConnectionDetailsSeq &that)
{
  if (this != &that)
  {
    if (that.heldCall)
    {
      if (!heldCall)
        heldCall = new(memBlock) ConnectionID(memBlock);
      *heldCall = *that.heldCall;
    }
    else
    {
      heldCall = NULL;
    }
    if (that.activeCall)
    {
      if (!activeCall)
        activeCall = new(memBlock) ConnectionID(memBlock);
      *activeCall = *that.activeCall;
    }
    else
    {
      activeCall = NULL;
    }
  }

  return *this;
}

AsnLen
ConnectionDetailsSeq::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

      BEncEocIfNec (b);
    l = activeCall->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;

      BEncEocIfNec (b);
    l = heldCall->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;

  return totalLen;
} // ConnectionDetailsSeq::BEncContent


void ConnectionDetailsSeq::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    heldCall = new(memBlock) ConnectionID(memBlock);
    heldCall->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0229: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    activeCall = new(memBlock) ConnectionID(memBlock);
    activeCall->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0230: SEQUENCE is missing non-optional elmt.";
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0231: Length discrepancy on sequence.";
  }
  else
    return;
} // ConnectionDetailsSeq::BDecContent

AsnLen ConnectionDetailsSeq::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void ConnectionDetailsSeq::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135061880: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int ConnectionDetailsSeq::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ConnectionDetailsSeq::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ConnectionDetailsSeq::Print ( CTsvcLIB::LOG& os ) const
{
  os << "ConnectionDetailsSeq SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "heldCall : ";
  if (NOT_NULL (heldCall))
    os << *heldCall;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "activeCall : ";
  if (NOT_NULL (activeCall))
    os << *activeCall;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // ConnectionDetailsSeq::Print


CallInfoSeq::CallInfoSeq( MemBlock* mb ) : AsnType( mb )
{
  endpoint = NULL; // incomplete initialization of mandatory element!
  staticEndpoint = NULL;
}

CallInfoSeq::CallInfoSeq( MemBlock* mb, const CallInfoSeq & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined CallInfoSeq::CallInfoSeq (const CallInfoSeq &)";
  abort();
}

CallInfoSeq::~CallInfoSeq()
{
}

AsnType *CallInfoSeq::Clone() const
{
  return new(memBlock) CallInfoSeq(memBlock);
}

CallInfoSeq &CallInfoSeq::operator = (const CallInfoSeq &that)
{
  if (this != &that)
  {
    if (that.endpoint)
    {
      if (!endpoint)
        endpoint = new(memBlock) ConnectionID(memBlock);
      *endpoint = *that.endpoint;
    }
    else
    {
      endpoint = NULL;
    }
    if (that.staticEndpoint)
    {
      if (!staticEndpoint)
        staticEndpoint = new(memBlock) DeviceID(memBlock);
      *staticEndpoint = *that.staticEndpoint;
    }
    else
    {
      staticEndpoint = NULL;
    }
  }

  return *this;
}

AsnLen
CallInfoSeq::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (staticEndpoint))
  {
    l = staticEndpoint->BEncContent (b);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = endpoint->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;

  return totalLen;
} // CallInfoSeq::BEncContent


void CallInfoSeq::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    endpoint = new(memBlock) ConnectionID(memBlock);
    endpoint->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0232: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 1)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    staticEndpoint = new(memBlock) DeviceID(memBlock);
    staticEndpoint->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0233: Length discrepancy on sequence.";
  }
  else
    return;
} // CallInfoSeq::BDecContent

AsnLen CallInfoSeq::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void CallInfoSeq::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135061912: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int CallInfoSeq::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int CallInfoSeq::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void CallInfoSeq::Print ( CTsvcLIB::LOG& os ) const
{
  os << "CallInfoSeq SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "endpoint : ";
  if (NOT_NULL (endpoint))
    os << *endpoint;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "staticEndpoint : ";
  if (NOT_NULL (staticEndpoint))
    os << *staticEndpoint;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // CallInfoSeq::Print


SnapshotCallArgumentSeq::SnapshotCallArgumentSeq( MemBlock* mb ) : AsnType( mb )
{
  snapshotObject = NULL; // incomplete initialization of mandatory element!
  extensions = NULL;
}

SnapshotCallArgumentSeq::SnapshotCallArgumentSeq( MemBlock* mb, const SnapshotCallArgumentSeq & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined SnapshotCallArgumentSeq::SnapshotCallArgumentSeq (const SnapshotCallArgumentSeq &)";
  abort();
}

SnapshotCallArgumentSeq::~SnapshotCallArgumentSeq()
{
}

AsnType *SnapshotCallArgumentSeq::Clone() const
{
  return new(memBlock) SnapshotCallArgumentSeq(memBlock);
}

SnapshotCallArgumentSeq &SnapshotCallArgumentSeq::operator = (const SnapshotCallArgumentSeq &that)
{
  if (this != &that)
  {
    if (that.snapshotObject)
    {
      if (!snapshotObject)
        snapshotObject = new(memBlock) ConnectionID(memBlock);
      *snapshotObject = *that.snapshotObject;
    }
    else
    {
      snapshotObject = NULL;
    }
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTACommonArguments(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
SnapshotCallArgumentSeq::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 30);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = snapshotObject->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;

  return totalLen;
} // SnapshotCallArgumentSeq::BEncContent


void SnapshotCallArgumentSeq::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    snapshotObject = new(memBlock) ConnectionID(memBlock);
    snapshotObject->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0234: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 30)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTACommonArguments(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0235: Length discrepancy on sequence.";
  }
  else
    return;
} // SnapshotCallArgumentSeq::BDecContent

AsnLen SnapshotCallArgumentSeq::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void SnapshotCallArgumentSeq::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135062184: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int SnapshotCallArgumentSeq::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int SnapshotCallArgumentSeq::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void SnapshotCallArgumentSeq::Print ( CTsvcLIB::LOG& os ) const
{
  os << "SnapshotCallArgumentSeq SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "snapshotObject : ";
  if (NOT_NULL (snapshotObject))
    os << *snapshotObject;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // SnapshotCallArgumentSeq::Print


RetrieveCallArgumentSeq::RetrieveCallArgumentSeq( MemBlock* mb ) : AsnType( mb )
{
  callToBeRetrieved = NULL; // incomplete initialization of mandatory element!
  extensions = NULL;
}

RetrieveCallArgumentSeq::RetrieveCallArgumentSeq( MemBlock* mb, const RetrieveCallArgumentSeq & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined RetrieveCallArgumentSeq::RetrieveCallArgumentSeq (const RetrieveCallArgumentSeq &)";
  abort();
}

RetrieveCallArgumentSeq::~RetrieveCallArgumentSeq()
{
}

AsnType *RetrieveCallArgumentSeq::Clone() const
{
  return new(memBlock) RetrieveCallArgumentSeq(memBlock);
}

RetrieveCallArgumentSeq &RetrieveCallArgumentSeq::operator = (const RetrieveCallArgumentSeq &that)
{
  if (this != &that)
  {
    if (that.callToBeRetrieved)
    {
      if (!callToBeRetrieved)
        callToBeRetrieved = new(memBlock) ConnectionID(memBlock);
      *callToBeRetrieved = *that.callToBeRetrieved;
    }
    else
    {
      callToBeRetrieved = NULL;
    }
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTACommonArguments(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
RetrieveCallArgumentSeq::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 30);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = callToBeRetrieved->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;

  return totalLen;
} // RetrieveCallArgumentSeq::BEncContent


void RetrieveCallArgumentSeq::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    callToBeRetrieved = new(memBlock) ConnectionID(memBlock);
    callToBeRetrieved->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0236: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 30)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTACommonArguments(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0237: Length discrepancy on sequence.";
  }
  else
    return;
} // RetrieveCallArgumentSeq::BDecContent

AsnLen RetrieveCallArgumentSeq::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void RetrieveCallArgumentSeq::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135062752: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int RetrieveCallArgumentSeq::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int RetrieveCallArgumentSeq::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void RetrieveCallArgumentSeq::Print ( CTsvcLIB::LOG& os ) const
{
  os << "RetrieveCallArgumentSeq SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "callToBeRetrieved : ";
  if (NOT_NULL (callToBeRetrieved))
    os << *callToBeRetrieved;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // RetrieveCallArgumentSeq::Print


MakePredictiveCallResultSeq::MakePredictiveCallResultSeq( MemBlock* mb ) : AsnType( mb )
{
  initiatedCall = NULL; // incomplete initialization of mandatory element!
  extensions = NULL;
}

MakePredictiveCallResultSeq::MakePredictiveCallResultSeq( MemBlock* mb, const MakePredictiveCallResultSeq & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined MakePredictiveCallResultSeq::MakePredictiveCallResultSeq (const MakePredictiveCallResultSeq &)";
  abort();
}

MakePredictiveCallResultSeq::~MakePredictiveCallResultSeq()
{
}

AsnType *MakePredictiveCallResultSeq::Clone() const
{
  return new(memBlock) MakePredictiveCallResultSeq(memBlock);
}

MakePredictiveCallResultSeq &MakePredictiveCallResultSeq::operator = (const MakePredictiveCallResultSeq &that)
{
  if (this != &that)
  {
    if (that.initiatedCall)
    {
      if (!initiatedCall)
        initiatedCall = new(memBlock) ConnectionID(memBlock);
      *initiatedCall = *that.initiatedCall;
    }
    else
    {
      initiatedCall = NULL;
    }
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTAPrivateData(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
MakePredictiveCallResultSeq::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 29);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = initiatedCall->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;

  return totalLen;
} // MakePredictiveCallResultSeq::BEncContent


void MakePredictiveCallResultSeq::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    initiatedCall = new(memBlock) ConnectionID(memBlock);
    initiatedCall->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0238: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 29)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTAPrivateData(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0239: Length discrepancy on sequence.";
  }
  else
    return;
} // MakePredictiveCallResultSeq::BDecContent

AsnLen MakePredictiveCallResultSeq::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void MakePredictiveCallResultSeq::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135063016: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int MakePredictiveCallResultSeq::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int MakePredictiveCallResultSeq::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void MakePredictiveCallResultSeq::Print ( CTsvcLIB::LOG& os ) const
{
  os << "MakePredictiveCallResultSeq SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "initiatedCall : ";
  if (NOT_NULL (initiatedCall))
    os << *initiatedCall;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // MakePredictiveCallResultSeq::Print


MakeCallResultSeq::MakeCallResultSeq( MemBlock* mb ) : AsnType( mb )
{
  initiatedCall = NULL; // incomplete initialization of mandatory element!
  extensions = NULL;
}

MakeCallResultSeq::MakeCallResultSeq( MemBlock* mb, const MakeCallResultSeq & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined MakeCallResultSeq::MakeCallResultSeq (const MakeCallResultSeq &)";
  abort();
}

MakeCallResultSeq::~MakeCallResultSeq()
{
}

AsnType *MakeCallResultSeq::Clone() const
{
  return new(memBlock) MakeCallResultSeq(memBlock);
}

MakeCallResultSeq &MakeCallResultSeq::operator = (const MakeCallResultSeq &that)
{
  if (this != &that)
  {
    if (that.initiatedCall)
    {
      if (!initiatedCall)
        initiatedCall = new(memBlock) ConnectionID(memBlock);
      *initiatedCall = *that.initiatedCall;
    }
    else
    {
      initiatedCall = NULL;
    }
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTAPrivateData(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
MakeCallResultSeq::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 29);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = initiatedCall->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;

  return totalLen;
} // MakeCallResultSeq::BEncContent


void MakeCallResultSeq::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    initiatedCall = new(memBlock) ConnectionID(memBlock);
    initiatedCall->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0240: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 29)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTAPrivateData(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0241: Length discrepancy on sequence.";
  }
  else
    return;
} // MakeCallResultSeq::BDecContent

AsnLen MakeCallResultSeq::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void MakeCallResultSeq::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135063080: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int MakeCallResultSeq::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int MakeCallResultSeq::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void MakeCallResultSeq::Print ( CTsvcLIB::LOG& os ) const
{
  os << "MakeCallResultSeq SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "initiatedCall : ";
  if (NOT_NULL (initiatedCall))
    os << *initiatedCall;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // MakeCallResultSeq::Print


ConsultationCallResultSeq::ConsultationCallResultSeq( MemBlock* mb ) : AsnType( mb )
{
  initiatedCall = NULL; // incomplete initialization of mandatory element!
  extensions = NULL;
}

ConsultationCallResultSeq::ConsultationCallResultSeq( MemBlock* mb, const ConsultationCallResultSeq & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined ConsultationCallResultSeq::ConsultationCallResultSeq (const ConsultationCallResultSeq &)";
  abort();
}

ConsultationCallResultSeq::~ConsultationCallResultSeq()
{
}

AsnType *ConsultationCallResultSeq::Clone() const
{
  return new(memBlock) ConsultationCallResultSeq(memBlock);
}

ConsultationCallResultSeq &ConsultationCallResultSeq::operator = (const ConsultationCallResultSeq &that)
{
  if (this != &that)
  {
    if (that.initiatedCall)
    {
      if (!initiatedCall)
        initiatedCall = new(memBlock) ConnectionID(memBlock);
      *initiatedCall = *that.initiatedCall;
    }
    else
    {
      initiatedCall = NULL;
    }
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTAPrivateData(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
ConsultationCallResultSeq::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 29);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = initiatedCall->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;

  return totalLen;
} // ConsultationCallResultSeq::BEncContent


void ConsultationCallResultSeq::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    initiatedCall = new(memBlock) ConnectionID(memBlock);
    initiatedCall->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0242: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 29)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTAPrivateData(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0243: Length discrepancy on sequence.";
  }
  else
    return;
} // ConsultationCallResultSeq::BDecContent

AsnLen ConsultationCallResultSeq::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void ConsultationCallResultSeq::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135063272: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int ConsultationCallResultSeq::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ConsultationCallResultSeq::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ConsultationCallResultSeq::Print ( CTsvcLIB::LOG& os ) const
{
  os << "ConsultationCallResultSeq SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "initiatedCall : ";
  if (NOT_NULL (initiatedCall))
    os << *initiatedCall;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // ConsultationCallResultSeq::Print


ClearConnectionArgumentSeq::ClearConnectionArgumentSeq( MemBlock* mb ) : AsnType( mb )
{
  connectionToBeCleared = NULL; // incomplete initialization of mandatory element!
  extensions = NULL;
}

ClearConnectionArgumentSeq::ClearConnectionArgumentSeq( MemBlock* mb, const ClearConnectionArgumentSeq & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined ClearConnectionArgumentSeq::ClearConnectionArgumentSeq (const ClearConnectionArgumentSeq &)";
  abort();
}

ClearConnectionArgumentSeq::~ClearConnectionArgumentSeq()
{
}

AsnType *ClearConnectionArgumentSeq::Clone() const
{
  return new(memBlock) ClearConnectionArgumentSeq(memBlock);
}

ClearConnectionArgumentSeq &ClearConnectionArgumentSeq::operator = (const ClearConnectionArgumentSeq &that)
{
  if (this != &that)
  {
    if (that.connectionToBeCleared)
    {
      if (!connectionToBeCleared)
        connectionToBeCleared = new(memBlock) ConnectionID(memBlock);
      *connectionToBeCleared = *that.connectionToBeCleared;
    }
    else
    {
      connectionToBeCleared = NULL;
    }
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTACommonArguments(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
ClearConnectionArgumentSeq::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 30);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = connectionToBeCleared->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;

  return totalLen;
} // ClearConnectionArgumentSeq::BEncContent


void ClearConnectionArgumentSeq::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    connectionToBeCleared = new(memBlock) ConnectionID(memBlock);
    connectionToBeCleared->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0244: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 30)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTACommonArguments(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0245: Length discrepancy on sequence.";
  }
  else
    return;
} // ClearConnectionArgumentSeq::BDecContent

AsnLen ClearConnectionArgumentSeq::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void ClearConnectionArgumentSeq::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135063448: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int ClearConnectionArgumentSeq::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ClearConnectionArgumentSeq::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ClearConnectionArgumentSeq::Print ( CTsvcLIB::LOG& os ) const
{
  os << "ClearConnectionArgumentSeq SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "connectionToBeCleared : ";
  if (NOT_NULL (connectionToBeCleared))
    os << *connectionToBeCleared;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // ClearConnectionArgumentSeq::Print


ClearCallArgumentSeq::ClearCallArgumentSeq( MemBlock* mb ) : AsnType( mb )
{
  callToBeCleared = NULL; // incomplete initialization of mandatory element!
  extensions = NULL;
}

ClearCallArgumentSeq::ClearCallArgumentSeq( MemBlock* mb, const ClearCallArgumentSeq & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined ClearCallArgumentSeq::ClearCallArgumentSeq (const ClearCallArgumentSeq &)";
  abort();
}

ClearCallArgumentSeq::~ClearCallArgumentSeq()
{
}

AsnType *ClearCallArgumentSeq::Clone() const
{
  return new(memBlock) ClearCallArgumentSeq(memBlock);
}

ClearCallArgumentSeq &ClearCallArgumentSeq::operator = (const ClearCallArgumentSeq &that)
{
  if (this != &that)
  {
    if (that.callToBeCleared)
    {
      if (!callToBeCleared)
        callToBeCleared = new(memBlock) ConnectionID(memBlock);
      *callToBeCleared = *that.callToBeCleared;
    }
    else
    {
      callToBeCleared = NULL;
    }
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTACommonArguments(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
ClearCallArgumentSeq::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 30);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = callToBeCleared->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;

  return totalLen;
} // ClearCallArgumentSeq::BEncContent


void ClearCallArgumentSeq::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    callToBeCleared = new(memBlock) ConnectionID(memBlock);
    callToBeCleared->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0246: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 30)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTACommonArguments(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0247: Length discrepancy on sequence.";
  }
  else
    return;
} // ClearCallArgumentSeq::BDecContent

AsnLen ClearCallArgumentSeq::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void ClearCallArgumentSeq::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135063520: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int ClearCallArgumentSeq::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ClearCallArgumentSeq::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ClearCallArgumentSeq::Print ( CTsvcLIB::LOG& os ) const
{
  os << "ClearCallArgumentSeq SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "callToBeCleared : ";
  if (NOT_NULL (callToBeCleared))
    os << *callToBeCleared;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // ClearCallArgumentSeq::Print


CallCompletionArgumentSeq::CallCompletionArgumentSeq( MemBlock* mb ) : AsnType( mb )
{
  featureInfo = NULL; // incomplete initialization of mandatory element!
  extensions = NULL;
}

CallCompletionArgumentSeq::CallCompletionArgumentSeq( MemBlock* mb, const CallCompletionArgumentSeq & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined CallCompletionArgumentSeq::CallCompletionArgumentSeq (const CallCompletionArgumentSeq &)";
  abort();
}

CallCompletionArgumentSeq::~CallCompletionArgumentSeq()
{
}

AsnType *CallCompletionArgumentSeq::Clone() const
{
  return new(memBlock) CallCompletionArgumentSeq(memBlock);
}

CallCompletionArgumentSeq &CallCompletionArgumentSeq::operator = (const CallCompletionArgumentSeq &that)
{
  if (this != &that)
  {
    if (that.featureInfo)
    {
      if (!featureInfo)
        featureInfo = new(memBlock) FeatureInfo(memBlock);
      *featureInfo = *that.featureInfo;
    }
    else
    {
      featureInfo = NULL;
    }
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTACommonArguments(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
CallCompletionArgumentSeq::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 30);
    totalLen += l;
  }

    l = featureInfo->BEncContent (b);
    totalLen += l;

  return totalLen;
} // CallCompletionArgumentSeq::BEncContent


void CallCompletionArgumentSeq::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (CNTX, CONS, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 1))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 2))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 3)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    featureInfo = new(memBlock) FeatureInfo(memBlock);
    featureInfo->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0248: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 30)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTACommonArguments(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0249: Length discrepancy on sequence.";
  }
  else
    return;
} // CallCompletionArgumentSeq::BDecContent

AsnLen CallCompletionArgumentSeq::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void CallCompletionArgumentSeq::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135063616: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int CallCompletionArgumentSeq::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int CallCompletionArgumentSeq::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void CallCompletionArgumentSeq::Print ( CTsvcLIB::LOG& os ) const
{
  os << "CallCompletionArgumentSeq SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "featureInfo : ";
  if (NOT_NULL (featureInfo))
    os << *featureInfo;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // CallCompletionArgumentSeq::Print


AnswerCallArgumentSeq::AnswerCallArgumentSeq( MemBlock* mb ) : AsnType( mb )
{
  callToBeAnswered = NULL; // incomplete initialization of mandatory element!
  extensions = NULL;
}

AnswerCallArgumentSeq::AnswerCallArgumentSeq( MemBlock* mb, const AnswerCallArgumentSeq & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined AnswerCallArgumentSeq::AnswerCallArgumentSeq (const AnswerCallArgumentSeq &)";
  abort();
}

AnswerCallArgumentSeq::~AnswerCallArgumentSeq()
{
}

AsnType *AnswerCallArgumentSeq::Clone() const
{
  return new(memBlock) AnswerCallArgumentSeq(memBlock);
}

AnswerCallArgumentSeq &AnswerCallArgumentSeq::operator = (const AnswerCallArgumentSeq &that)
{
  if (this != &that)
  {
    if (that.callToBeAnswered)
    {
      if (!callToBeAnswered)
        callToBeAnswered = new(memBlock) ConnectionID(memBlock);
      *callToBeAnswered = *that.callToBeAnswered;
    }
    else
    {
      callToBeAnswered = NULL;
    }
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTACommonArguments(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
AnswerCallArgumentSeq::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 30);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = callToBeAnswered->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;

  return totalLen;
} // AnswerCallArgumentSeq::BEncContent


void AnswerCallArgumentSeq::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    callToBeAnswered = new(memBlock) ConnectionID(memBlock);
    callToBeAnswered->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0250: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 30)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTACommonArguments(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0251: Length discrepancy on sequence.";
  }
  else
    return;
} // AnswerCallArgumentSeq::BDecContent

AsnLen AnswerCallArgumentSeq::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void AnswerCallArgumentSeq::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135063688: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int AnswerCallArgumentSeq::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int AnswerCallArgumentSeq::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void AnswerCallArgumentSeq::Print ( CTsvcLIB::LOG& os ) const
{
  os << "AnswerCallArgumentSeq SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "callToBeAnswered : ";
  if (NOT_NULL (callToBeAnswered))
    os << *callToBeAnswered;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // AnswerCallArgumentSeq::Print


AnswerCallArgument::AnswerCallArgument( MemBlock* mb ) : AsnType( mb )
{
  choiceId = callToBeAnsweredCid;
  callToBeAnswered = NULL; // incomplete initialization of mandatory element!
}

AnswerCallArgument::AnswerCallArgument( MemBlock* mb, const AnswerCallArgument & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined AnswerCallArgument::AnswerCallArgument (const AnswerCallArgument &)";
  abort();
}

AnswerCallArgument::~AnswerCallArgument()
{
} // end of destructor

AsnType *AnswerCallArgument::Clone() const
{
  return new(memBlock) AnswerCallArgument(memBlock);
}

AnswerCallArgument &AnswerCallArgument::operator = (const AnswerCallArgument &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case callToBeAnsweredCid:
        callToBeAnswered = new(memBlock) ConnectionID(memBlock);
        *callToBeAnswered = *that.callToBeAnswered;
        break;
      case answerCallArgumentSeqCid:
        answerCallArgumentSeq = new(memBlock) AnswerCallArgumentSeq(memBlock);
        *answerCallArgumentSeq = *that.answerCallArgumentSeq;
        break;
    }
  }

  return *this;
}

AsnLen
AnswerCallArgument::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case callToBeAnsweredCid:
      BEncEocIfNec (b);
      l = callToBeAnswered->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
      break;

    case answerCallArgumentSeqCid:
      BEncEocIfNec (b);
      l = answerCallArgumentSeq->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
      break;

  } // end switch
  return l;
} // AnswerCallArgument::BEncContent


void AnswerCallArgument::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (APPL, CONS, 11):
      choiceId = callToBeAnsweredCid;
      callToBeAnswered = new(memBlock) ConnectionID(memBlock);
        callToBeAnswered->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE):
      choiceId = answerCallArgumentSeqCid;
      answerCallArgumentSeq = new(memBlock) AnswerCallArgumentSeq(memBlock);
        answerCallArgumentSeq->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0252: Unexpected tag in CHOICE";
      break;
  } // end switch
} // AnswerCallArgument::BDecContent


AsnLen AnswerCallArgument::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void AnswerCallArgument::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int AnswerCallArgument::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int AnswerCallArgument::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void AnswerCallArgument::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case callToBeAnsweredCid: os << "ConnectionID*"; break;
    case answerCallArgumentSeqCid: os << "AnswerCallArgumentSeq*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case callToBeAnsweredCid:
      os << "callToBeAnswered : ";
      if (callToBeAnswered)
        os << *callToBeAnswered;
      else
        os << "VOID";
      break;

    case answerCallArgumentSeqCid:
      if (answerCallArgumentSeq)
        os << *answerCallArgumentSeq;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // AnswerCallArgument::Print

CallCompletionArgument::CallCompletionArgument( MemBlock* mb ) : AsnType( mb )
{
  choiceId = featureInfoCid;
  featureInfo = NULL; // incomplete initialization of mandatory element!
}

CallCompletionArgument::CallCompletionArgument( MemBlock* mb, const CallCompletionArgument & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined CallCompletionArgument::CallCompletionArgument (const CallCompletionArgument &)";
  abort();
}

CallCompletionArgument::~CallCompletionArgument()
{
} // end of destructor

AsnType *CallCompletionArgument::Clone() const
{
  return new(memBlock) CallCompletionArgument(memBlock);
}

CallCompletionArgument &CallCompletionArgument::operator = (const CallCompletionArgument &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case featureInfoCid:
        featureInfo = new(memBlock) FeatureInfo(memBlock);
        *featureInfo = *that.featureInfo;
        break;
      case callCompletionArgumentSeqCid:
        callCompletionArgumentSeq = new(memBlock) CallCompletionArgumentSeq(memBlock);
        *callCompletionArgumentSeq = *that.callCompletionArgumentSeq;
        break;
    }
  }

  return *this;
}

AsnLen
CallCompletionArgument::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case featureInfoCid:
      l = featureInfo->BEncContent (b);
      break;

    case callCompletionArgumentSeqCid:
      BEncEocIfNec (b);
      l = callCompletionArgumentSeq->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
      break;

  } // end switch
  return l;
} // CallCompletionArgument::BEncContent


void CallCompletionArgument::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (CNTX, CONS, 0):
    case MAKE_TAG_ID (CNTX, CONS, 1):
    case MAKE_TAG_ID (CNTX, CONS, 2):
    case MAKE_TAG_ID (CNTX, CONS, 3):
      choiceId = featureInfoCid;
      featureInfo = new(memBlock) FeatureInfo(memBlock);
        featureInfo->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE):
      choiceId = callCompletionArgumentSeqCid;
      callCompletionArgumentSeq = new(memBlock) CallCompletionArgumentSeq(memBlock);
        callCompletionArgumentSeq->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0253: Unexpected tag in CHOICE";
      break;
  } // end switch
} // CallCompletionArgument::BDecContent


AsnLen CallCompletionArgument::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void CallCompletionArgument::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int CallCompletionArgument::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int CallCompletionArgument::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void CallCompletionArgument::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case featureInfoCid: os << "FeatureInfo*"; break;
    case callCompletionArgumentSeqCid: os << "CallCompletionArgumentSeq*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case featureInfoCid:
      os << "featureInfo : ";
      if (featureInfo)
        os << *featureInfo;
      else
        os << "VOID";
      break;

    case callCompletionArgumentSeqCid:
      if (callCompletionArgumentSeq)
        os << *callCompletionArgumentSeq;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // CallCompletionArgument::Print

ClearCallArgument::ClearCallArgument( MemBlock* mb ) : AsnType( mb )
{
  choiceId = callToBeClearedCid;
  callToBeCleared = NULL; // incomplete initialization of mandatory element!
}

ClearCallArgument::ClearCallArgument( MemBlock* mb, const ClearCallArgument & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined ClearCallArgument::ClearCallArgument (const ClearCallArgument &)";
  abort();
}

ClearCallArgument::~ClearCallArgument()
{
} // end of destructor

AsnType *ClearCallArgument::Clone() const
{
  return new(memBlock) ClearCallArgument(memBlock);
}

ClearCallArgument &ClearCallArgument::operator = (const ClearCallArgument &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case callToBeClearedCid:
        callToBeCleared = new(memBlock) ConnectionID(memBlock);
        *callToBeCleared = *that.callToBeCleared;
        break;
      case clearCallArgumentSeqCid:
        clearCallArgumentSeq = new(memBlock) ClearCallArgumentSeq(memBlock);
        *clearCallArgumentSeq = *that.clearCallArgumentSeq;
        break;
    }
  }

  return *this;
}

AsnLen
ClearCallArgument::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case callToBeClearedCid:
      BEncEocIfNec (b);
      l = callToBeCleared->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
      break;

    case clearCallArgumentSeqCid:
      BEncEocIfNec (b);
      l = clearCallArgumentSeq->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
      break;

  } // end switch
  return l;
} // ClearCallArgument::BEncContent


void ClearCallArgument::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (APPL, CONS, 11):
      choiceId = callToBeClearedCid;
      callToBeCleared = new(memBlock) ConnectionID(memBlock);
        callToBeCleared->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE):
      choiceId = clearCallArgumentSeqCid;
      clearCallArgumentSeq = new(memBlock) ClearCallArgumentSeq(memBlock);
        clearCallArgumentSeq->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0254: Unexpected tag in CHOICE";
      break;
  } // end switch
} // ClearCallArgument::BDecContent


AsnLen ClearCallArgument::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void ClearCallArgument::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int ClearCallArgument::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ClearCallArgument::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ClearCallArgument::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case callToBeClearedCid: os << "ConnectionID*"; break;
    case clearCallArgumentSeqCid: os << "ClearCallArgumentSeq*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case callToBeClearedCid:
      os << "callToBeCleared : ";
      if (callToBeCleared)
        os << *callToBeCleared;
      else
        os << "VOID";
      break;

    case clearCallArgumentSeqCid:
      if (clearCallArgumentSeq)
        os << *clearCallArgumentSeq;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // ClearCallArgument::Print

ClearConnectionArgument::ClearConnectionArgument( MemBlock* mb ) : AsnType( mb )
{
  choiceId = connectionToBeClearedCid;
  connectionToBeCleared = NULL; // incomplete initialization of mandatory element!
}

ClearConnectionArgument::ClearConnectionArgument( MemBlock* mb, const ClearConnectionArgument & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined ClearConnectionArgument::ClearConnectionArgument (const ClearConnectionArgument &)";
  abort();
}

ClearConnectionArgument::~ClearConnectionArgument()
{
} // end of destructor

AsnType *ClearConnectionArgument::Clone() const
{
  return new(memBlock) ClearConnectionArgument(memBlock);
}

ClearConnectionArgument &ClearConnectionArgument::operator = (const ClearConnectionArgument &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case connectionToBeClearedCid:
        connectionToBeCleared = new(memBlock) ConnectionID(memBlock);
        *connectionToBeCleared = *that.connectionToBeCleared;
        break;
      case clearConnectionArgumentSeqCid:
        clearConnectionArgumentSeq = new(memBlock) ClearConnectionArgumentSeq(memBlock);
        *clearConnectionArgumentSeq = *that.clearConnectionArgumentSeq;
        break;
    }
  }

  return *this;
}

AsnLen
ClearConnectionArgument::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case connectionToBeClearedCid:
      BEncEocIfNec (b);
      l = connectionToBeCleared->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
      break;

    case clearConnectionArgumentSeqCid:
      BEncEocIfNec (b);
      l = clearConnectionArgumentSeq->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
      break;

  } // end switch
  return l;
} // ClearConnectionArgument::BEncContent


void ClearConnectionArgument::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (APPL, CONS, 11):
      choiceId = connectionToBeClearedCid;
      connectionToBeCleared = new(memBlock) ConnectionID(memBlock);
        connectionToBeCleared->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE):
      choiceId = clearConnectionArgumentSeqCid;
      clearConnectionArgumentSeq = new(memBlock) ClearConnectionArgumentSeq(memBlock);
        clearConnectionArgumentSeq->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0255: Unexpected tag in CHOICE";
      break;
  } // end switch
} // ClearConnectionArgument::BDecContent


AsnLen ClearConnectionArgument::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void ClearConnectionArgument::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int ClearConnectionArgument::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ClearConnectionArgument::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ClearConnectionArgument::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case connectionToBeClearedCid: os << "ConnectionID*"; break;
    case clearConnectionArgumentSeqCid: os << "ClearConnectionArgumentSeq*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case connectionToBeClearedCid:
      os << "connectionToBeCleared : ";
      if (connectionToBeCleared)
        os << *connectionToBeCleared;
      else
        os << "VOID";
      break;

    case clearConnectionArgumentSeqCid:
      if (clearConnectionArgumentSeq)
        os << *clearConnectionArgumentSeq;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // ClearConnectionArgument::Print

ConsultationCallArgument::ConsultationCallArgument( MemBlock* mb ) : AsnType( mb )
{
  existingCall = NULL; // incomplete initialization of mandatory element!
  calledDirectoryNumber = NULL; // incomplete initialization of mandatory element!
  extensions = NULL;
}

ConsultationCallArgument::ConsultationCallArgument( MemBlock* mb, const ConsultationCallArgument & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined ConsultationCallArgument::ConsultationCallArgument (const ConsultationCallArgument &)";
  abort();
}

ConsultationCallArgument::~ConsultationCallArgument()
{
}

AsnType *ConsultationCallArgument::Clone() const
{
  return new(memBlock) ConsultationCallArgument(memBlock);
}

ConsultationCallArgument &ConsultationCallArgument::operator = (const ConsultationCallArgument &that)
{
  if (this != &that)
  {
    if (that.existingCall)
    {
      if (!existingCall)
        existingCall = new(memBlock) ConnectionID(memBlock);
      *existingCall = *that.existingCall;
    }
    else
    {
      existingCall = NULL;
    }
    if (that.calledDirectoryNumber)
    {
      if (!calledDirectoryNumber)
        calledDirectoryNumber = new(memBlock) CalledDeviceID(memBlock);
      *calledDirectoryNumber = *that.calledDirectoryNumber;
    }
    else
    {
      calledDirectoryNumber = NULL;
    }
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTACommonArguments(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
ConsultationCallArgument::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 30);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = calledDirectoryNumber->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 2);
    totalLen += l;

      BEncEocIfNec (b);
    l = existingCall->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;

  return totalLen;
} // ConsultationCallArgument::BEncContent


void ConsultationCallArgument::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  AsnLen elmtLen2;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    existingCall = new(memBlock) ConnectionID(memBlock);
    existingCall->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0256: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 2)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    calledDirectoryNumber = new(memBlock) CalledDeviceID(memBlock);
    calledDirectoryNumber->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0257: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 30)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTACommonArguments(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0258: Length discrepancy on sequence.";
  }
  else
    return;
} // ConsultationCallArgument::BDecContent

AsnLen ConsultationCallArgument::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void ConsultationCallArgument::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135066000: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int ConsultationCallArgument::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ConsultationCallArgument::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ConsultationCallArgument::Print ( CTsvcLIB::LOG& os ) const
{
  os << "ConsultationCallArgument SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "existingCall : ";
  if (NOT_NULL (existingCall))
    os << *existingCall;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "calledDirectoryNumber : ";
  if (NOT_NULL (calledDirectoryNumber))
    os << *calledDirectoryNumber;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // ConsultationCallArgument::Print


ConsultationCallResult::ConsultationCallResult( MemBlock* mb ) : AsnType( mb )
{
  choiceId = initiatedCallCid;
  initiatedCall = NULL; // incomplete initialization of mandatory element!
}

ConsultationCallResult::ConsultationCallResult( MemBlock* mb, const ConsultationCallResult & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined ConsultationCallResult::ConsultationCallResult (const ConsultationCallResult &)";
  abort();
}

ConsultationCallResult::~ConsultationCallResult()
{
} // end of destructor

AsnType *ConsultationCallResult::Clone() const
{
  return new(memBlock) ConsultationCallResult(memBlock);
}

ConsultationCallResult &ConsultationCallResult::operator = (const ConsultationCallResult &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case initiatedCallCid:
        initiatedCall = new(memBlock) ConnectionID(memBlock);
        *initiatedCall = *that.initiatedCall;
        break;
      case consultationCallResultSeqCid:
        consultationCallResultSeq = new(memBlock) ConsultationCallResultSeq(memBlock);
        *consultationCallResultSeq = *that.consultationCallResultSeq;
        break;
    }
  }

  return *this;
}

AsnLen
ConsultationCallResult::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case initiatedCallCid:
      BEncEocIfNec (b);
      l = initiatedCall->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
      break;

    case consultationCallResultSeqCid:
      BEncEocIfNec (b);
      l = consultationCallResultSeq->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
      break;

  } // end switch
  return l;
} // ConsultationCallResult::BEncContent


void ConsultationCallResult::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (APPL, CONS, 11):
      choiceId = initiatedCallCid;
      initiatedCall = new(memBlock) ConnectionID(memBlock);
        initiatedCall->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE):
      choiceId = consultationCallResultSeqCid;
      consultationCallResultSeq = new(memBlock) ConsultationCallResultSeq(memBlock);
        consultationCallResultSeq->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0259: Unexpected tag in CHOICE";
      break;
  } // end switch
} // ConsultationCallResult::BDecContent


AsnLen ConsultationCallResult::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void ConsultationCallResult::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int ConsultationCallResult::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ConsultationCallResult::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ConsultationCallResult::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case initiatedCallCid: os << "ConnectionID*"; break;
    case consultationCallResultSeqCid: os << "ConsultationCallResultSeq*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case initiatedCallCid:
      os << "initiatedCall : ";
      if (initiatedCall)
        os << *initiatedCall;
      else
        os << "VOID";
      break;

    case consultationCallResultSeqCid:
      if (consultationCallResultSeq)
        os << *consultationCallResultSeq;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // ConsultationCallResult::Print

HoldCallArgument::HoldCallArgument( MemBlock* mb ) : AsnType( mb )
{
  callToBeHeld = NULL; // incomplete initialization of mandatory element!
  connectionReservation = NULL;
  extensions = NULL;
}

HoldCallArgument::HoldCallArgument( MemBlock* mb, const HoldCallArgument & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined HoldCallArgument::HoldCallArgument (const HoldCallArgument &)";
  abort();
}

HoldCallArgument::~HoldCallArgument()
{
}

AsnType *HoldCallArgument::Clone() const
{
  return new(memBlock) HoldCallArgument(memBlock);
}

HoldCallArgument &HoldCallArgument::operator = (const HoldCallArgument &that)
{
  if (this != &that)
  {
    if (that.callToBeHeld)
    {
      if (!callToBeHeld)
        callToBeHeld = new(memBlock) ConnectionID(memBlock);
      *callToBeHeld = *that.callToBeHeld;
    }
    else
    {
      callToBeHeld = NULL;
    }
    if (that.connectionReservation)
    {
      if (!connectionReservation)
        connectionReservation = new(memBlock) ReserveConnection(memBlock);
      *connectionReservation = *that.connectionReservation;
    }
    else
    {
      connectionReservation = NULL;
    }
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTACommonArguments(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
HoldCallArgument::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 30);
    totalLen += l;
  }

  if (NOT_NULL (connectionReservation))
  {
    l = connectionReservation->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, BOOLEAN_TAG_CODE);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = callToBeHeld->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;

  return totalLen;
} // HoldCallArgument::BEncContent


void HoldCallArgument::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    callToBeHeld = new(memBlock) ConnectionID(memBlock);
    callToBeHeld->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0260: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, BOOLEAN_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    connectionReservation = new(memBlock) ReserveConnection(memBlock);
    connectionReservation->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 30)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTACommonArguments(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0261: Length discrepancy on sequence.";
  }
  else
    return;
} // HoldCallArgument::BDecContent

AsnLen HoldCallArgument::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void HoldCallArgument::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135066336: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int HoldCallArgument::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int HoldCallArgument::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void HoldCallArgument::Print ( CTsvcLIB::LOG& os ) const
{
  os << "HoldCallArgument SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "callToBeHeld : ";
  if (NOT_NULL (callToBeHeld))
    os << *callToBeHeld;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "connectionReservation : ";
  if (NOT_NULL (connectionReservation))
    os << *connectionReservation;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // HoldCallArgument::Print


MakeCallResult::MakeCallResult( MemBlock* mb ) : AsnType( mb )
{
  choiceId = initiatedCallCid;
  initiatedCall = NULL; // incomplete initialization of mandatory element!
}

MakeCallResult::MakeCallResult( MemBlock* mb, const MakeCallResult & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined MakeCallResult::MakeCallResult (const MakeCallResult &)";
  abort();
}

MakeCallResult::~MakeCallResult()
{
} // end of destructor

AsnType *MakeCallResult::Clone() const
{
  return new(memBlock) MakeCallResult(memBlock);
}

MakeCallResult &MakeCallResult::operator = (const MakeCallResult &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case initiatedCallCid:
        initiatedCall = new(memBlock) ConnectionID(memBlock);
        *initiatedCall = *that.initiatedCall;
        break;
      case makeCallResultSeqCid:
        makeCallResultSeq = new(memBlock) MakeCallResultSeq(memBlock);
        *makeCallResultSeq = *that.makeCallResultSeq;
        break;
    }
  }

  return *this;
}

AsnLen
MakeCallResult::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case initiatedCallCid:
      BEncEocIfNec (b);
      l = initiatedCall->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
      break;

    case makeCallResultSeqCid:
      BEncEocIfNec (b);
      l = makeCallResultSeq->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
      break;

  } // end switch
  return l;
} // MakeCallResult::BEncContent


void MakeCallResult::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (APPL, CONS, 11):
      choiceId = initiatedCallCid;
      initiatedCall = new(memBlock) ConnectionID(memBlock);
        initiatedCall->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE):
      choiceId = makeCallResultSeqCid;
      makeCallResultSeq = new(memBlock) MakeCallResultSeq(memBlock);
        makeCallResultSeq->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0262: Unexpected tag in CHOICE";
      break;
  } // end switch
} // MakeCallResult::BDecContent


AsnLen MakeCallResult::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void MakeCallResult::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int MakeCallResult::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int MakeCallResult::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void MakeCallResult::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case initiatedCallCid: os << "ConnectionID*"; break;
    case makeCallResultSeqCid: os << "MakeCallResultSeq*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case initiatedCallCid:
      os << "initiatedCall : ";
      if (initiatedCall)
        os << *initiatedCall;
      else
        os << "VOID";
      break;

    case makeCallResultSeqCid:
      if (makeCallResultSeq)
        os << *makeCallResultSeq;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // MakeCallResult::Print

MakePredictiveCallResult::MakePredictiveCallResult( MemBlock* mb ) : AsnType( mb )
{
  choiceId = initiatedCallCid;
  initiatedCall = NULL; // incomplete initialization of mandatory element!
}

MakePredictiveCallResult::MakePredictiveCallResult( MemBlock* mb, const MakePredictiveCallResult & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined MakePredictiveCallResult::MakePredictiveCallResult (const MakePredictiveCallResult &)";
  abort();
}

MakePredictiveCallResult::~MakePredictiveCallResult()
{
} // end of destructor

AsnType *MakePredictiveCallResult::Clone() const
{
  return new(memBlock) MakePredictiveCallResult(memBlock);
}

MakePredictiveCallResult &MakePredictiveCallResult::operator = (const MakePredictiveCallResult &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case initiatedCallCid:
        initiatedCall = new(memBlock) ConnectionID(memBlock);
        *initiatedCall = *that.initiatedCall;
        break;
      case makePredictiveCallResultSeqCid:
        makePredictiveCallResultSeq = new(memBlock) MakePredictiveCallResultSeq(memBlock);
        *makePredictiveCallResultSeq = *that.makePredictiveCallResultSeq;
        break;
    }
  }

  return *this;
}

AsnLen
MakePredictiveCallResult::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case initiatedCallCid:
      BEncEocIfNec (b);
      l = initiatedCall->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
      break;

    case makePredictiveCallResultSeqCid:
      BEncEocIfNec (b);
      l = makePredictiveCallResultSeq->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
      break;

  } // end switch
  return l;
} // MakePredictiveCallResult::BEncContent


void MakePredictiveCallResult::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (APPL, CONS, 11):
      choiceId = initiatedCallCid;
      initiatedCall = new(memBlock) ConnectionID(memBlock);
        initiatedCall->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE):
      choiceId = makePredictiveCallResultSeqCid;
      makePredictiveCallResultSeq = new(memBlock) MakePredictiveCallResultSeq(memBlock);
        makePredictiveCallResultSeq->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0263: Unexpected tag in CHOICE";
      break;
  } // end switch
} // MakePredictiveCallResult::BDecContent


AsnLen MakePredictiveCallResult::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void MakePredictiveCallResult::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int MakePredictiveCallResult::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int MakePredictiveCallResult::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void MakePredictiveCallResult::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case initiatedCallCid: os << "ConnectionID*"; break;
    case makePredictiveCallResultSeqCid: os << "MakePredictiveCallResultSeq*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case initiatedCallCid:
      os << "initiatedCall : ";
      if (initiatedCall)
        os << *initiatedCall;
      else
        os << "VOID";
      break;

    case makePredictiveCallResultSeqCid:
      if (makePredictiveCallResultSeq)
        os << *makePredictiveCallResultSeq;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // MakePredictiveCallResult::Print

RetrieveCallArgument::RetrieveCallArgument( MemBlock* mb ) : AsnType( mb )
{
  choiceId = callToBeRetrievedCid;
  callToBeRetrieved = NULL; // incomplete initialization of mandatory element!
}

RetrieveCallArgument::RetrieveCallArgument( MemBlock* mb, const RetrieveCallArgument & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined RetrieveCallArgument::RetrieveCallArgument (const RetrieveCallArgument &)";
  abort();
}

RetrieveCallArgument::~RetrieveCallArgument()
{
} // end of destructor

AsnType *RetrieveCallArgument::Clone() const
{
  return new(memBlock) RetrieveCallArgument(memBlock);
}

RetrieveCallArgument &RetrieveCallArgument::operator = (const RetrieveCallArgument &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case callToBeRetrievedCid:
        callToBeRetrieved = new(memBlock) ConnectionID(memBlock);
        *callToBeRetrieved = *that.callToBeRetrieved;
        break;
      case retrieveCallArgumentSeqCid:
        retrieveCallArgumentSeq = new(memBlock) RetrieveCallArgumentSeq(memBlock);
        *retrieveCallArgumentSeq = *that.retrieveCallArgumentSeq;
        break;
    }
  }

  return *this;
}

AsnLen
RetrieveCallArgument::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case callToBeRetrievedCid:
      BEncEocIfNec (b);
      l = callToBeRetrieved->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
      break;

    case retrieveCallArgumentSeqCid:
      BEncEocIfNec (b);
      l = retrieveCallArgumentSeq->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
      break;

  } // end switch
  return l;
} // RetrieveCallArgument::BEncContent


void RetrieveCallArgument::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (APPL, CONS, 11):
      choiceId = callToBeRetrievedCid;
      callToBeRetrieved = new(memBlock) ConnectionID(memBlock);
        callToBeRetrieved->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE):
      choiceId = retrieveCallArgumentSeqCid;
      retrieveCallArgumentSeq = new(memBlock) RetrieveCallArgumentSeq(memBlock);
        retrieveCallArgumentSeq->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0264: Unexpected tag in CHOICE";
      break;
  } // end switch
} // RetrieveCallArgument::BDecContent


AsnLen RetrieveCallArgument::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void RetrieveCallArgument::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int RetrieveCallArgument::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int RetrieveCallArgument::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void RetrieveCallArgument::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case callToBeRetrievedCid: os << "ConnectionID*"; break;
    case retrieveCallArgumentSeqCid: os << "RetrieveCallArgumentSeq*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case callToBeRetrievedCid:
      os << "callToBeRetrieved : ";
      if (callToBeRetrieved)
        os << *callToBeRetrieved;
      else
        os << "VOID";
      break;

    case retrieveCallArgumentSeqCid:
      if (retrieveCallArgumentSeq)
        os << *retrieveCallArgumentSeq;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // RetrieveCallArgument::Print

SetFeatureArgument::SetFeatureArgument( MemBlock* mb ) : AsnType( mb )
{
  device = NULL; // incomplete initialization of mandatory element!
  feature = NULL; // incomplete initialization of mandatory element!
  extensions = NULL;
}

SetFeatureArgument::SetFeatureArgument( MemBlock* mb, const SetFeatureArgument & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined SetFeatureArgument::SetFeatureArgument (const SetFeatureArgument &)";
  abort();
}

SetFeatureArgument::~SetFeatureArgument()
{
}

AsnType *SetFeatureArgument::Clone() const
{
  return new(memBlock) SetFeatureArgument(memBlock);
}

SetFeatureArgument &SetFeatureArgument::operator = (const SetFeatureArgument &that)
{
  if (this != &that)
  {
    if (that.device)
    {
      if (!device)
        device = new(memBlock) DeviceID(memBlock);
      *device = *that.device;
    }
    else
    {
      device = NULL;
    }
    if (that.feature)
    {
      if (!feature)
        feature = new(memBlock) SetDeviceFeature(memBlock);
      *feature = *that.feature;
    }
    else
    {
      feature = NULL;
    }
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTACommonArguments(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
SetFeatureArgument::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 30);
    totalLen += l;
  }

    l = feature->BEncContent (b);
    totalLen += l;

    l = device->BEncContent (b);
    totalLen += l;

  return totalLen;
} // SetFeatureArgument::BEncContent


void SetFeatureArgument::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 1)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    device = new(memBlock) DeviceID(memBlock);
    device->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0265: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 1))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 2))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 3)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    feature = new(memBlock) SetDeviceFeature(memBlock);
    feature->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0266: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 30)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTACommonArguments(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0267: Length discrepancy on sequence.";
  }
  else
    return;
} // SetFeatureArgument::BDecContent

AsnLen SetFeatureArgument::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void SetFeatureArgument::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135067360: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int SetFeatureArgument::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int SetFeatureArgument::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void SetFeatureArgument::Print ( CTsvcLIB::LOG& os ) const
{
  os << "SetFeatureArgument SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "device : ";
  if (NOT_NULL (device))
    os << *device;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "feature : ";
  if (NOT_NULL (feature))
    os << *feature;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // SetFeatureArgument::Print


RouteRequestArgument::RouteRequestArgument( MemBlock* mb ) : AsnType( mb )
    , crossRefIdentifier( mb )
{
  currentRoute = NULL; // incomplete initialization of mandatory element!
  callingDevice = NULL;
  routedCall = NULL;
  routeSelAlgorithm = NULL;
  priority = NULL;
  setupInformation = NULL;
  extensions = NULL;
}

RouteRequestArgument::RouteRequestArgument( MemBlock* mb, const RouteRequestArgument & ) : AsnType( mb )
    , crossRefIdentifier( mb )
{
  throw "ERROR C0099: Use of incompletely defined RouteRequestArgument::RouteRequestArgument (const RouteRequestArgument &)";
  abort();
}

RouteRequestArgument::~RouteRequestArgument()
{
}

AsnType *RouteRequestArgument::Clone() const
{
  return new(memBlock) RouteRequestArgument(memBlock);
}

RouteRequestArgument &RouteRequestArgument::operator = (const RouteRequestArgument &that)
{
  if (this != &that)
  {
    crossRefIdentifier = that.crossRefIdentifier;
    if (that.currentRoute)
    {
      if (!currentRoute)
        currentRoute = new(memBlock) CalledDeviceID(memBlock);
      *currentRoute = *that.currentRoute;
    }
    else
    {
      currentRoute = NULL;
    }
    if (that.callingDevice)
    {
      if (!callingDevice)
        callingDevice = new(memBlock) CallingDeviceID(memBlock);
      *callingDevice = *that.callingDevice;
    }
    else
    {
      callingDevice = NULL;
    }
    if (that.routedCall)
    {
      if (!routedCall)
        routedCall = new(memBlock) ConnectionID(memBlock);
      *routedCall = *that.routedCall;
    }
    else
    {
      routedCall = NULL;
    }
    if (that.routeSelAlgorithm)
    {
      if (!routeSelAlgorithm)
        routeSelAlgorithm = new(memBlock) SelectValue(memBlock);
      *routeSelAlgorithm = *that.routeSelAlgorithm;
    }
    else
    {
      routeSelAlgorithm = NULL;
    }
    if (that.priority)
    {
      if (!priority)
        priority = new(memBlock) PriorityValue(memBlock);
      *priority = *that.priority;
    }
    else
    {
      priority = NULL;
    }
    if (that.setupInformation)
    {
      if (!setupInformation)
        setupInformation = new(memBlock) SetUpValues(memBlock);
      *setupInformation = *that.setupInformation;
    }
    else
    {
      setupInformation = NULL;
    }
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTACommonArguments(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
RouteRequestArgument::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 30);
    totalLen += l;
  }

  if (NOT_NULL (setupInformation))
  {
    l = setupInformation->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, UNIV, PRIM, OCTETSTRING_TAG_CODE);
    totalLen += l;
  }

  if (NOT_NULL (priority))
  {
    l = priority->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, BOOLEAN_TAG_CODE);
    totalLen += l;
  }

  if (NOT_NULL (routeSelAlgorithm))
  {
    l = routeSelAlgorithm->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, ENUM_TAG_CODE);
    totalLen += l;
  }

  if (NOT_NULL (routedCall))
  {
      BEncEocIfNec (b);
    l = routedCall->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;
  }

  if (NOT_NULL (callingDevice))
  {
      BEncEocIfNec (b);
    l = callingDevice->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 1);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = currentRoute->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 2);
    totalLen += l;

    l = crossRefIdentifier.BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, APPL, PRIM, 24);
    totalLen += l;

  return totalLen;
} // RouteRequestArgument::BEncContent


void RouteRequestArgument::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  AsnLen elmtLen2;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, PRIM, 24))
    || (tag1 == MAKE_TAG_ID (APPL, CONS, 24)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    crossRefIdentifier.BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0268: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 2)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    currentRoute = new(memBlock) CalledDeviceID(memBlock);
    currentRoute->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0269: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 1)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    callingDevice = new(memBlock) CallingDeviceID(memBlock);
    callingDevice->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    routedCall = new(memBlock) ConnectionID(memBlock);
    routedCall->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, ENUM_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    routeSelAlgorithm = new(memBlock) SelectValue(memBlock);
    routeSelAlgorithm->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, BOOLEAN_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    priority = new(memBlock) PriorityValue(memBlock);
    priority->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, OCTETSTRING_TAG_CODE))
    || (tag1 == MAKE_TAG_ID (UNIV, CONS, OCTETSTRING_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    setupInformation = new(memBlock) SetUpValues(memBlock);
    setupInformation->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 30)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTACommonArguments(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0270: Length discrepancy on sequence.";
  }
  else
    return;
} // RouteRequestArgument::BDecContent

AsnLen RouteRequestArgument::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void RouteRequestArgument::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135070176: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int RouteRequestArgument::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int RouteRequestArgument::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void RouteRequestArgument::Print ( CTsvcLIB::LOG& os ) const
{
  os << "RouteRequestArgument SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "crossRefIdentifier : ";
  os << crossRefIdentifier;
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "currentRoute : ";
  if (NOT_NULL (currentRoute))
    os << *currentRoute;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "callingDevice : ";
  if (NOT_NULL (callingDevice))
    os << *callingDevice;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "routedCall : ";
  if (NOT_NULL (routedCall))
    os << *routedCall;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "routeSelAlgorithm : ";
  if (NOT_NULL (routeSelAlgorithm))
    os << *routeSelAlgorithm;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "priority : ";
  if (NOT_NULL (priority))
    os << *priority;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "setupInformation : ";
  if (NOT_NULL (setupInformation))
    os << *setupInformation;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // RouteRequestArgument::Print


SnapshotCallArgument::SnapshotCallArgument( MemBlock* mb ) : AsnType( mb )
{
  choiceId = snapshotObjectCid;
  snapshotObject = NULL; // incomplete initialization of mandatory element!
}

SnapshotCallArgument::SnapshotCallArgument( MemBlock* mb, const SnapshotCallArgument & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined SnapshotCallArgument::SnapshotCallArgument (const SnapshotCallArgument &)";
  abort();
}

SnapshotCallArgument::~SnapshotCallArgument()
{
} // end of destructor

AsnType *SnapshotCallArgument::Clone() const
{
  return new(memBlock) SnapshotCallArgument(memBlock);
}

SnapshotCallArgument &SnapshotCallArgument::operator = (const SnapshotCallArgument &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case snapshotObjectCid:
        snapshotObject = new(memBlock) ConnectionID(memBlock);
        *snapshotObject = *that.snapshotObject;
        break;
      case snapshotCallArgumentSeqCid:
        snapshotCallArgumentSeq = new(memBlock) SnapshotCallArgumentSeq(memBlock);
        *snapshotCallArgumentSeq = *that.snapshotCallArgumentSeq;
        break;
    }
  }

  return *this;
}

AsnLen
SnapshotCallArgument::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case snapshotObjectCid:
      BEncEocIfNec (b);
      l = snapshotObject->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
      break;

    case snapshotCallArgumentSeqCid:
      BEncEocIfNec (b);
      l = snapshotCallArgumentSeq->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
      break;

  } // end switch
  return l;
} // SnapshotCallArgument::BEncContent


void SnapshotCallArgument::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (APPL, CONS, 11):
      choiceId = snapshotObjectCid;
      snapshotObject = new(memBlock) ConnectionID(memBlock);
        snapshotObject->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE):
      choiceId = snapshotCallArgumentSeqCid;
      snapshotCallArgumentSeq = new(memBlock) SnapshotCallArgumentSeq(memBlock);
        snapshotCallArgumentSeq->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0271: Unexpected tag in CHOICE";
      break;
  } // end switch
} // SnapshotCallArgument::BDecContent


AsnLen SnapshotCallArgument::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void SnapshotCallArgument::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int SnapshotCallArgument::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int SnapshotCallArgument::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void SnapshotCallArgument::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case snapshotObjectCid: os << "ConnectionID*"; break;
    case snapshotCallArgumentSeqCid: os << "SnapshotCallArgumentSeq*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case snapshotObjectCid:
      os << "snapshotObject : ";
      if (snapshotObject)
        os << *snapshotObject;
      else
        os << "VOID";
      break;

    case snapshotCallArgumentSeqCid:
      if (snapshotCallArgumentSeq)
        os << *snapshotCallArgumentSeq;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // SnapshotCallArgument::Print

CSTAObject::CSTAObject( MemBlock* mb ) : AsnType( mb )
{
  choiceId = deviceObjectCid;
  deviceObject = NULL; // incomplete initialization of mandatory element!
}

CSTAObject::CSTAObject( MemBlock* mb, const CSTAObject & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined CSTAObject::CSTAObject (const CSTAObject &)";
  abort();
}

CSTAObject::~CSTAObject()
{
} // end of destructor

AsnType *CSTAObject::Clone() const
{
  return new(memBlock) CSTAObject(memBlock);
}

CSTAObject &CSTAObject::operator = (const CSTAObject &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case deviceObjectCid:
        deviceObject = new(memBlock) DeviceID(memBlock);
        *deviceObject = *that.deviceObject;
        break;
      case callObjectCid:
        callObject = new(memBlock) ConnectionID(memBlock);
        *callObject = *that.callObject;
        break;
    }
  }

  return *this;
}

AsnLen
CSTAObject::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case deviceObjectCid:
      l = deviceObject->BEncContent (b);
      break;

    case callObjectCid:
      BEncEocIfNec (b);
      l = callObject->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
      break;

  } // end switch
  return l;
} // CSTAObject::BEncContent


void CSTAObject::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (CNTX, PRIM, 0):
    case MAKE_TAG_ID (CNTX, CONS, 0):
    case MAKE_TAG_ID (CNTX, PRIM, 1):
      choiceId = deviceObjectCid;
      deviceObject = new(memBlock) DeviceID(memBlock);
        deviceObject->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (APPL, CONS, 11):
      choiceId = callObjectCid;
      callObject = new(memBlock) ConnectionID(memBlock);
        callObject->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0272: Unexpected tag in CHOICE";
      break;
  } // end switch
} // CSTAObject::BDecContent


AsnLen CSTAObject::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void CSTAObject::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int CSTAObject::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int CSTAObject::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void CSTAObject::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case deviceObjectCid: os << "DeviceID*"; break;
    case callObjectCid: os << "ConnectionID*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case deviceObjectCid:
      os << "deviceObject : ";
      if (deviceObject)
        os << *deviceObject;
      else
        os << "VOID";
      break;

    case callObjectCid:
      os << "callObject : ";
      if (callObject)
        os << *callObject;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // CSTAObject::Print

AsnType *CallInfo::Clone() const
{
  return new(memBlock) CallInfo(memBlock);
}

AsnLen CallInfo::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, APPL, CONS, 13);
  return l;
}

void CallInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (APPL, CONS, 13))
  {
    throw "ERROR C0273: CallInfo.BDec(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

CallInfo::CallInfo( MemBlock* mb, const CallInfo & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined CallInfo::CallInfo (const CallInfo &)";
  abort();
}

CallInfo::~CallInfo()
{
  SetCurrToFirst();
  for (; Curr() != NULL; RemoveCurrFromList())
    ;
} // end of destructor

CallInfo &CallInfo::operator = (const CallInfo &that)
{
  if (this != &that)
  {
    SetCurrToFirst();
    for (; Curr(); RemoveCurrFromList())
      ;

    //that.SetCurrToFirst();
    //for (; that.Curr(); that.GoNext())
    //  AppendCopy (*that.Curr());
    for (const AsnListElmt *run=that.first; run; run=run->next)
      AppendCopy (*run->elmt);
  }

  return *this;
}

void CallInfo::Print ( CTsvcLIB::LOG& os ) const
{
    os << "CallInfo SEQUENCE/SET OF" << CTsvcLIB::eline;
    Indent (os, indentG);
    os << "{" << CTsvcLIB::eline;
    indentG += stdIndentG;
    for (const AsnListElmt *run=first; run; run=run->next)
    {
        Indent (os, indentG);
        os << *run->elmt;
        if (run != last)
            os << ",";
        os << CTsvcLIB::eline;
    }
    indentG -= stdIndentG;
    Indent (os, indentG);
    os << "}";
} // Print


void  CallInfo::SetCurrElmt (unsigned long int index)
{
  unsigned long int i;
  curr = first;
  if (count)
    for (i = 0; (i < (count-1)) && (i < index); i++)
      curr = curr->next;
} // CallInfo::SetCurrElmt


unsigned long int  CallInfo::GetCurrElmtIndex()
{
    unsigned long int i;
    AsnListElmt *tmp;
    if (curr != NULL)
    {
        for (i = 0, tmp = first; tmp != NULL; i++)
        {
            if (tmp == curr)
                return i;
            else
                tmp = tmp->next;
        }
    }
    return count;
} // CallInfo::GetCurrElmtIndex


// alloc new list elmt, put at end of list
//  and return the component type
CallInfoSeq *CallInfo::Append()
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt  = new(memBlock) CallInfoSeq(memBlock);
    newElmt->next = NULL;
    if (last == NULL)
    {
        newElmt->prev = NULL;
        first = last  = newElmt;
    }
    else
    {
        newElmt->prev = last;
        last->next    = newElmt;
        last          = newElmt;
    }
    count++;
    return (curr = newElmt)->elmt;
} // CallInfo::Append


// alloc new list elmt, put at begining of list
//  and return the component type
CallInfoSeq  *CallInfo::Prepend()
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) CallInfoSeq(memBlock);
    newElmt->prev = NULL;
    if (first == NULL)
    {
        newElmt->next = NULL;
        first = last  = newElmt;
    }
    else
    {
        newElmt->next = first;
        first->prev   = newElmt;
        first         = newElmt;
    }
    count++;
    return (curr = newElmt)->elmt;
} // CallInfo::Prepend


// alloc new list elmt, insert it before the
// current element and return the component type
// if the current element is null, the new element
// is placed at the beginning of the list.
CallInfoSeq  *CallInfo::InsertBefore()
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) CallInfoSeq(memBlock);
    if (curr == NULL)
    {
        newElmt->next = first;
        newElmt->prev = NULL;
        first = newElmt;
        if (last == NULL)
            last = newElmt;
    }
    else
    {
        newElmt->next = curr;
        newElmt->prev = curr->prev;
        curr->prev = newElmt;
        if (curr == first)
            first = newElmt;
        else
            newElmt->prev->next = newElmt;
    }
    count++;
    return (curr = newElmt)->elmt;
} // CallInfo::InsertBefore


// alloc new list elmt, insert it after the
// current element and return the component type
// if the current element is null, the new element
// is placed at the end of the list.
CallInfoSeq *CallInfo::InsertAfter()
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) CallInfoSeq(memBlock);
    if (curr == NULL)
    {
        newElmt->prev = last;
        newElmt->next = NULL;
        last = newElmt;
        if (first == NULL)
            first = newElmt;
    }
    else
    {
        newElmt->prev = curr;
        newElmt->next = curr->next;
        curr->next = newElmt;
        if (curr == last)
            last = newElmt;
        else
            newElmt->next->prev = newElmt;
    }
    count++;
    return (curr = newElmt)->elmt;
} // CallInfo::InsertAfter


CallInfo  &CallInfo::AppendCopy (CallInfoSeq &elmt)
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) CallInfoSeq(memBlock);
    *newElmt->elmt = elmt;
    newElmt->next = NULL;
    if (last == NULL)
    {
        newElmt->prev = NULL;
        first = last  = newElmt;
    }
    else
    {
        newElmt->prev = last;
        last->next    = newElmt;
        last          = newElmt;
    }
    count++;
    return *this;
} // AppendCopy


CallInfo  &CallInfo::PrependCopy (CallInfoSeq &elmt)
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) CallInfoSeq(memBlock);
    *newElmt->elmt = elmt;
    newElmt->prev = NULL;
    if (first == NULL)
    {
        newElmt->next = NULL;
        first = last  = newElmt;
    }
    else
    {
        newElmt->next = first;
        first->prev   = newElmt;
        first         = newElmt;
    }
    count++;
    return *this;
} // CallInfo::PrependCopy


// alloc new list elmt, insert it before the
// current element, copy the given elmt into the new elmt
// and return the component type.
// if the current element is null, the new element
// is placed at the beginning of the list.
CallInfo &CallInfo::InsertBeforeAndCopy (CallInfoSeq &elmt)
{
    AsnListElmt *newElmt;

    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) CallInfoSeq(memBlock);
    *newElmt->elmt = elmt;

    if (curr == NULL)
    {
        newElmt->next = first;
        newElmt->prev = NULL;
        first = newElmt;
        if (last == NULL)
            last = newElmt;
    }
    else
    {
        newElmt->next = curr;
        newElmt->prev = curr->prev;
        curr->prev = newElmt;
        if (curr == first)
            first = newElmt;
        else
            newElmt->prev->next = newElmt;
    }
    count++;
    return *this;
} // CallInfo::InsertBeforeAndCopy


// alloc new list elmt, insert it after the
// current element, copy given elmt in to new elmt
//  and return the component type
// if the current element is null, the new element
// is placed at the end of the list.
CallInfo  &CallInfo::InsertAfterAndCopy (CallInfoSeq &elmt)
{
    AsnListElmt *newElmt;

    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) CallInfoSeq(memBlock);
    *newElmt->elmt = elmt;
    if (curr == NULL)
    {
        newElmt->prev = last;
        newElmt->next = NULL;
        last = newElmt;
        if (first == NULL)
            first = newElmt;
    }
    else
    {
        newElmt->prev = curr;
        newElmt->next = curr->next;
        curr->next = newElmt;
        if (curr == last)
            last = newElmt;
        else
            newElmt->next->prev = newElmt;
    }
    count++;
    return *this;
} // CallInfo::InsertAfterAndCopy


// remove current element from list if current element is not NULL 
// The new current element will be the next element.
// If the current element is the last element in the list
// the second but last element will become the new current element.
void CallInfo::RemoveCurrFromList()
{
    AsnListElmt *del_elmt;

    if (curr != NULL)
    {
        del_elmt = curr;
        count--;

        if (count == 0)
            first = last = curr = NULL;
        else if (curr == first)
        {
            curr = first= first->next;
            first->prev = NULL;
        }
        else if (curr == last)
        {
            curr = last = last->prev;
            last->next = NULL;
        }
        else
        {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
        }

    }
}


AsnLen CallInfo::BEncContent (AsnBuf& b)
{
    AsnListElmt *currElmt;
    AsnLen elmtLen;
    AsnLen totalLen = 0;
    for (currElmt = last; currElmt != NULL; currElmt = currElmt->prev)
    {
      BEncEocIfNec (b);
        elmtLen = currElmt->elmt->BEncContent (b);
    elmtLen += BEncConsLen (b, elmtLen);

    elmtLen += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
        totalLen += elmtLen;
    }
    return totalLen;
} // CallInfo::BEncContent


void  CallInfo::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0,
                                  AsnLen &bytesDecoded)
{
    CallInfoSeq *listElmt;
    AsnTag tag1;
    AsnLen listBytesDecoded = 0;
    AsnLen elmtLen1;

    while ((listBytesDecoded < elmtLen0) || (elmtLen0 == INDEFINITE_LEN))
    {
        tag1 = BDecTag (b, listBytesDecoded);
        if ((tag1 == EOC_TAG_ID) && (elmtLen0 == INDEFINITE_LEN))
        {
            BDEC_2ND_EOC_OCTET (b, listBytesDecoded);
            break;
        }
        if ((tag1 != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE) ))
        {
            throw "ERROR C0274: Unexpected Tag";
        }

        elmtLen1 = BDecLen (b, listBytesDecoded);
        listElmt = Append();
        listElmt->BDecContent (b, tag1, elmtLen1, listBytesDecoded);
    }

    bytesDecoded += listBytesDecoded;
} // CallInfo::BDecContent


ConnectionList::ConnectionList( MemBlock* mb ) : AsnType( mb )
{
  choiceId = connectionsCid;
  connections = NULL; // incomplete initialization of mandatory element!
}

ConnectionList::ConnectionList( MemBlock* mb, const ConnectionList & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined ConnectionList::ConnectionList (const ConnectionList &)";
  abort();
}

ConnectionList::~ConnectionList()
{
} // end of destructor

AsnType *ConnectionList::Clone() const
{
  return new(memBlock) ConnectionList(memBlock);
}

ConnectionList &ConnectionList::operator = (const ConnectionList &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case connectionsCid:
        connections = new(memBlock) ConnectionIDList(memBlock);
        *connections = *that.connections;
        break;
      case callinformationCid:
        callinformation = new(memBlock) CallInfo(memBlock);
        *callinformation = *that.callinformation;
        break;
    }
  }

  return *this;
}

AsnLen
ConnectionList::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case connectionsCid:
      BEncEocIfNec (b);
      l = connections->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 12);
      break;

    case callinformationCid:
      BEncEocIfNec (b);
      l = callinformation->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 13);
      break;

  } // end switch
  return l;
} // ConnectionList::BEncContent


void ConnectionList::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (APPL, CONS, 12):
      choiceId = connectionsCid;
      connections = new(memBlock) ConnectionIDList(memBlock);
        connections->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (APPL, CONS, 13):
      choiceId = callinformationCid;
      callinformation = new(memBlock) CallInfo(memBlock);
        callinformation->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0275: Unexpected tag in CHOICE";
      break;
  } // end switch
} // ConnectionList::BDecContent


AsnLen ConnectionList::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void ConnectionList::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int ConnectionList::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ConnectionList::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ConnectionList::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case connectionsCid: os << "ConnectionIDList*"; break;
    case callinformationCid: os << "CallInfo*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case connectionsCid:
      os << "connections : ";
      if (connections)
        os << *connections;
      else
        os << "VOID";
      break;

    case callinformationCid:
      os << "callinformation : ";
      if (callinformation)
        os << *callinformation;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // ConnectionList::Print

SnapshotDeviceResponseInfo::SnapshotDeviceResponseInfo( MemBlock* mb ) : AsnType( mb )
{
  callIdentifier = NULL; // incomplete initialization of mandatory element!
  localCallState = NULL; // incomplete initialization of mandatory element!
}

SnapshotDeviceResponseInfo::SnapshotDeviceResponseInfo( MemBlock* mb, const SnapshotDeviceResponseInfo & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined SnapshotDeviceResponseInfo::SnapshotDeviceResponseInfo (const SnapshotDeviceResponseInfo &)";
  abort();
}

SnapshotDeviceResponseInfo::~SnapshotDeviceResponseInfo()
{
}

AsnType *SnapshotDeviceResponseInfo::Clone() const
{
  return new(memBlock) SnapshotDeviceResponseInfo(memBlock);
}

SnapshotDeviceResponseInfo &SnapshotDeviceResponseInfo::operator = (const SnapshotDeviceResponseInfo &that)
{
  if (this != &that)
  {
    if (that.callIdentifier)
    {
      if (!callIdentifier)
        callIdentifier = new(memBlock) ConnectionID(memBlock);
      *callIdentifier = *that.callIdentifier;
    }
    else
    {
      callIdentifier = NULL;
    }
    if (that.localCallState)
    {
      if (!localCallState)
        localCallState = new(memBlock) CallState(memBlock);
      *localCallState = *that.localCallState;
    }
    else
    {
      localCallState = NULL;
    }
  }

  return *this;
}

AsnLen
SnapshotDeviceResponseInfo::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

    l = localCallState->BEncContent (b);
    totalLen += l;

      BEncEocIfNec (b);
    l = callIdentifier->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;

  return totalLen;
} // SnapshotDeviceResponseInfo::BEncContent


void SnapshotDeviceResponseInfo::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    callIdentifier = new(memBlock) ConnectionID(memBlock);
    callIdentifier->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0276: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, CONS, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 1))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 2)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    localCallState = new(memBlock) CallState(memBlock);
    localCallState->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0277: SEQUENCE is missing non-optional elmt.";
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0278: Length discrepancy on sequence.";
  }
  else
    return;
} // SnapshotDeviceResponseInfo::BDecContent

AsnLen SnapshotDeviceResponseInfo::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void SnapshotDeviceResponseInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135074536: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int SnapshotDeviceResponseInfo::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int SnapshotDeviceResponseInfo::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void SnapshotDeviceResponseInfo::Print ( CTsvcLIB::LOG& os ) const
{
  os << "SnapshotDeviceResponseInfo SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "callIdentifier : ";
  if (NOT_NULL (callIdentifier))
    os << *callIdentifier;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "localCallState : ";
  if (NOT_NULL (localCallState))
    os << *localCallState;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // SnapshotDeviceResponseInfo::Print


AsnType *SnapshotCallData::Clone() const
{
  return new(memBlock) SnapshotCallData(memBlock);
}

AsnLen SnapshotCallData::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, APPL, CONS, 23);
  return l;
}

void SnapshotCallData::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (APPL, CONS, 23))
  {
    throw "ERROR C0279: SnapshotCallData.BDec(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

SnapshotCallData::SnapshotCallData( MemBlock* mb, const SnapshotCallData & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined SnapshotCallData::SnapshotCallData (const SnapshotCallData &)";
  abort();
}

SnapshotCallData::~SnapshotCallData()
{
  SetCurrToFirst();
  for (; Curr() != NULL; RemoveCurrFromList())
    ;
} // end of destructor

SnapshotCallData &SnapshotCallData::operator = (const SnapshotCallData &that)
{
  if (this != &that)
  {
    SetCurrToFirst();
    for (; Curr(); RemoveCurrFromList())
      ;

    //that.SetCurrToFirst();
    //for (; that.Curr(); that.GoNext())
    //  AppendCopy (*that.Curr());
    for (const AsnListElmt *run=that.first; run; run=run->next)
      AppendCopy (*run->elmt);
  }

  return *this;
}

void SnapshotCallData::Print ( CTsvcLIB::LOG& os ) const
{
    os << "SnapshotCallData SEQUENCE/SET OF" << CTsvcLIB::eline;
    Indent (os, indentG);
    os << "{" << CTsvcLIB::eline;
    indentG += stdIndentG;
    for (const AsnListElmt *run=first; run; run=run->next)
    {
        Indent (os, indentG);
        os << *run->elmt;
        if (run != last)
            os << ",";
        os << CTsvcLIB::eline;
    }
    indentG -= stdIndentG;
    Indent (os, indentG);
    os << "}";
} // Print


void  SnapshotCallData::SetCurrElmt (unsigned long int index)
{
  unsigned long int i;
  curr = first;
  if (count)
    for (i = 0; (i < (count-1)) && (i < index); i++)
      curr = curr->next;
} // SnapshotCallData::SetCurrElmt


unsigned long int  SnapshotCallData::GetCurrElmtIndex()
{
    unsigned long int i;
    AsnListElmt *tmp;
    if (curr != NULL)
    {
        for (i = 0, tmp = first; tmp != NULL; i++)
        {
            if (tmp == curr)
                return i;
            else
                tmp = tmp->next;
        }
    }
    return count;
} // SnapshotCallData::GetCurrElmtIndex


// alloc new list elmt, put at end of list
//  and return the component type
SnapshotCallResponseInfo *SnapshotCallData::Append()
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt  = new(memBlock) SnapshotCallResponseInfo(memBlock);
    newElmt->next = NULL;
    if (last == NULL)
    {
        newElmt->prev = NULL;
        first = last  = newElmt;
    }
    else
    {
        newElmt->prev = last;
        last->next    = newElmt;
        last          = newElmt;
    }
    count++;
    return (curr = newElmt)->elmt;
} // SnapshotCallData::Append


// alloc new list elmt, put at begining of list
//  and return the component type
SnapshotCallResponseInfo  *SnapshotCallData::Prepend()
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) SnapshotCallResponseInfo(memBlock);
    newElmt->prev = NULL;
    if (first == NULL)
    {
        newElmt->next = NULL;
        first = last  = newElmt;
    }
    else
    {
        newElmt->next = first;
        first->prev   = newElmt;
        first         = newElmt;
    }
    count++;
    return (curr = newElmt)->elmt;
} // SnapshotCallData::Prepend


// alloc new list elmt, insert it before the
// current element and return the component type
// if the current element is null, the new element
// is placed at the beginning of the list.
SnapshotCallResponseInfo  *SnapshotCallData::InsertBefore()
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) SnapshotCallResponseInfo(memBlock);
    if (curr == NULL)
    {
        newElmt->next = first;
        newElmt->prev = NULL;
        first = newElmt;
        if (last == NULL)
            last = newElmt;
    }
    else
    {
        newElmt->next = curr;
        newElmt->prev = curr->prev;
        curr->prev = newElmt;
        if (curr == first)
            first = newElmt;
        else
            newElmt->prev->next = newElmt;
    }
    count++;
    return (curr = newElmt)->elmt;
} // SnapshotCallData::InsertBefore


// alloc new list elmt, insert it after the
// current element and return the component type
// if the current element is null, the new element
// is placed at the end of the list.
SnapshotCallResponseInfo *SnapshotCallData::InsertAfter()
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) SnapshotCallResponseInfo(memBlock);
    if (curr == NULL)
    {
        newElmt->prev = last;
        newElmt->next = NULL;
        last = newElmt;
        if (first == NULL)
            first = newElmt;
    }
    else
    {
        newElmt->prev = curr;
        newElmt->next = curr->next;
        curr->next = newElmt;
        if (curr == last)
            last = newElmt;
        else
            newElmt->next->prev = newElmt;
    }
    count++;
    return (curr = newElmt)->elmt;
} // SnapshotCallData::InsertAfter


SnapshotCallData  &SnapshotCallData::AppendCopy (SnapshotCallResponseInfo &elmt)
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) SnapshotCallResponseInfo(memBlock);
    *newElmt->elmt = elmt;
    newElmt->next = NULL;
    if (last == NULL)
    {
        newElmt->prev = NULL;
        first = last  = newElmt;
    }
    else
    {
        newElmt->prev = last;
        last->next    = newElmt;
        last          = newElmt;
    }
    count++;
    return *this;
} // AppendCopy


SnapshotCallData  &SnapshotCallData::PrependCopy (SnapshotCallResponseInfo &elmt)
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) SnapshotCallResponseInfo(memBlock);
    *newElmt->elmt = elmt;
    newElmt->prev = NULL;
    if (first == NULL)
    {
        newElmt->next = NULL;
        first = last  = newElmt;
    }
    else
    {
        newElmt->next = first;
        first->prev   = newElmt;
        first         = newElmt;
    }
    count++;
    return *this;
} // SnapshotCallData::PrependCopy


// alloc new list elmt, insert it before the
// current element, copy the given elmt into the new elmt
// and return the component type.
// if the current element is null, the new element
// is placed at the beginning of the list.
SnapshotCallData &SnapshotCallData::InsertBeforeAndCopy (SnapshotCallResponseInfo &elmt)
{
    AsnListElmt *newElmt;

    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) SnapshotCallResponseInfo(memBlock);
    *newElmt->elmt = elmt;

    if (curr == NULL)
    {
        newElmt->next = first;
        newElmt->prev = NULL;
        first = newElmt;
        if (last == NULL)
            last = newElmt;
    }
    else
    {
        newElmt->next = curr;
        newElmt->prev = curr->prev;
        curr->prev = newElmt;
        if (curr == first)
            first = newElmt;
        else
            newElmt->prev->next = newElmt;
    }
    count++;
    return *this;
} // SnapshotCallData::InsertBeforeAndCopy


// alloc new list elmt, insert it after the
// current element, copy given elmt in to new elmt
//  and return the component type
// if the current element is null, the new element
// is placed at the end of the list.
SnapshotCallData  &SnapshotCallData::InsertAfterAndCopy (SnapshotCallResponseInfo &elmt)
{
    AsnListElmt *newElmt;

    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) SnapshotCallResponseInfo(memBlock);
    *newElmt->elmt = elmt;
    if (curr == NULL)
    {
        newElmt->prev = last;
        newElmt->next = NULL;
        last = newElmt;
        if (first == NULL)
            first = newElmt;
    }
    else
    {
        newElmt->prev = curr;
        newElmt->next = curr->next;
        curr->next = newElmt;
        if (curr == last)
            last = newElmt;
        else
            newElmt->next->prev = newElmt;
    }
    count++;
    return *this;
} // SnapshotCallData::InsertAfterAndCopy


// remove current element from list if current element is not NULL 
// The new current element will be the next element.
// If the current element is the last element in the list
// the second but last element will become the new current element.
void SnapshotCallData::RemoveCurrFromList()
{
    AsnListElmt *del_elmt;

    if (curr != NULL)
    {
        del_elmt = curr;
        count--;

        if (count == 0)
            first = last = curr = NULL;
        else if (curr == first)
        {
            curr = first= first->next;
            first->prev = NULL;
        }
        else if (curr == last)
        {
            curr = last = last->prev;
            last->next = NULL;
        }
        else
        {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
        }

    }
}


AsnLen SnapshotCallData::BEncContent (AsnBuf& b)
{
    AsnListElmt *currElmt;
    AsnLen elmtLen;
    AsnLen totalLen = 0;
    for (currElmt = last; currElmt != NULL; currElmt = currElmt->prev)
    {
      BEncEocIfNec (b);
        elmtLen = currElmt->elmt->BEncContent (b);
    elmtLen += BEncConsLen (b, elmtLen);

    elmtLen += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
        totalLen += elmtLen;
    }
    return totalLen;
} // SnapshotCallData::BEncContent


void  SnapshotCallData::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0,
                                  AsnLen &bytesDecoded)
{
    SnapshotCallResponseInfo *listElmt;
    AsnTag tag1;
    AsnLen listBytesDecoded = 0;
    AsnLen elmtLen1;

    while ((listBytesDecoded < elmtLen0) || (elmtLen0 == INDEFINITE_LEN))
    {
        tag1 = BDecTag (b, listBytesDecoded);
        if ((tag1 == EOC_TAG_ID) && (elmtLen0 == INDEFINITE_LEN))
        {
            BDEC_2ND_EOC_OCTET (b, listBytesDecoded);
            break;
        }
        if ((tag1 != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE) ))
        {
            throw "ERROR C0280: Unexpected Tag";
        }

        elmtLen1 = BDecLen (b, listBytesDecoded);
        listElmt = Append();
        listElmt->BDecContent (b, tag1, elmtLen1, listBytesDecoded);
    }

    bytesDecoded += listBytesDecoded;
} // SnapshotCallData::BDecContent


ConnectionDetails::ConnectionDetails( MemBlock* mb ) : AsnType( mb )
{
  choiceId = heldCallCid;
  heldCall = NULL; // incomplete initialization of mandatory element!
}

ConnectionDetails::ConnectionDetails( MemBlock* mb, const ConnectionDetails & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined ConnectionDetails::ConnectionDetails (const ConnectionDetails &)";
  abort();
}

ConnectionDetails::~ConnectionDetails()
{
} // end of destructor

AsnType *ConnectionDetails::Clone() const
{
  return new(memBlock) ConnectionDetails(memBlock);
}

ConnectionDetails &ConnectionDetails::operator = (const ConnectionDetails &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case heldCallCid:
        heldCall = new(memBlock) ConnectionID(memBlock);
        *heldCall = *that.heldCall;
        break;
      case activeCallCid:
        activeCall = new(memBlock) ConnectionID(memBlock);
        *activeCall = *that.activeCall;
        break;
      case bothCallsCid:
        bothCalls = new(memBlock) ConnectionDetailsSeq(memBlock);
        *bothCalls = *that.bothCalls;
        break;
    }
  }

  return *this;
}

AsnLen
ConnectionDetails::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case heldCallCid:
      BEncEocIfNec (b);
      l = heldCall->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, CNTX, CONS, 0);
      break;

    case activeCallCid:
      BEncEocIfNec (b);
      l = activeCall->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, CNTX, CONS, 1);
      break;

    case bothCallsCid:
      BEncEocIfNec (b);
      l = bothCalls->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, CNTX, CONS, 2);
      break;

  } // end switch
  return l;
} // ConnectionDetails::BEncContent


void ConnectionDetails::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (CNTX, CONS, 0):
      choiceId = heldCallCid;
      heldCall = new(memBlock) ConnectionID(memBlock);
        heldCall->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, CONS, 1):
      choiceId = activeCallCid;
      activeCall = new(memBlock) ConnectionID(memBlock);
        activeCall->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, CONS, 2):
      choiceId = bothCallsCid;
      bothCalls = new(memBlock) ConnectionDetailsSeq(memBlock);
        bothCalls->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0281: Unexpected tag in CHOICE";
      break;
  } // end switch
} // ConnectionDetails::BDecContent


AsnLen ConnectionDetails::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void ConnectionDetails::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int ConnectionDetails::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ConnectionDetails::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ConnectionDetails::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case heldCallCid: os << "ConnectionID*"; break;
    case activeCallCid: os << "ConnectionID*"; break;
    case bothCallsCid: os << "ConnectionDetailsSeq*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case heldCallCid:
      os << "heldCall : ";
      if (heldCall)
        os << *heldCall;
      else
        os << "VOID";
      break;

    case activeCallCid:
      os << "activeCall : ";
      if (activeCall)
        os << *activeCall;
      else
        os << "VOID";
      break;

    case bothCallsCid:
      os << "bothCalls : ";
      if (bothCalls)
        os << *bothCalls;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // ConnectionDetails::Print

DivertInfo::DivertInfo( MemBlock* mb ) : AsnType( mb )
{
  choiceId = deflectCid;
  deflect = NULL; // incomplete initialization of mandatory element!
}

DivertInfo::DivertInfo( MemBlock* mb, const DivertInfo & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined DivertInfo::DivertInfo (const DivertInfo &)";
  abort();
}

DivertInfo::~DivertInfo()
{
} // end of destructor

AsnType *DivertInfo::Clone() const
{
  return new(memBlock) DivertInfo(memBlock);
}

DivertInfo &DivertInfo::operator = (const DivertInfo &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case deflectCid:
        deflect = new(memBlock) DivertInfoSeq(memBlock);
        *deflect = *that.deflect;
        break;
      case pickupCid:
        pickup = new(memBlock) DivertInfoSeq1(memBlock);
        *pickup = *that.pickup;
        break;
      case groupCid:
        group = new(memBlock) DeviceID(memBlock);
        *group = *that.group;
        break;
    }
  }

  return *this;
}

AsnLen
DivertInfo::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case deflectCid:
      BEncEocIfNec (b);
      l = deflect->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, CNTX, CONS, 0);
      break;

    case pickupCid:
      BEncEocIfNec (b);
      l = pickup->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, CNTX, CONS, 1);
      break;

    case groupCid:
      BEncEocIfNec (b);
      l = group->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, CNTX, CONS, 2);
      break;

  } // end switch
  return l;
} // DivertInfo::BEncContent


void DivertInfo::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnLen elmtLen1;
  switch (tag)
  {
    case MAKE_TAG_ID (CNTX, CONS, 0):
      choiceId = deflectCid;
      deflect = new(memBlock) DivertInfoSeq(memBlock);
        deflect->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, CONS, 1):
      choiceId = pickupCid;
      pickup = new(memBlock) DivertInfoSeq1(memBlock);
        pickup->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, CONS, 2):
      tag = BDecTag (b, bytesDecoded);
      elmtLen1 = BDecLen (b, bytesDecoded);
      choiceId = groupCid;
      group = new(memBlock) DeviceID(memBlock);
        group->BDecContent (b, tag, elmtLen1, bytesDecoded);
      if (elmtLen0 == INDEFINITE_LEN)
        BDecEoc (b, bytesDecoded);
      break;

    default:
      throw "ERROR C0282: Unexpected tag in CHOICE";
      break;
  } // end switch
} // DivertInfo::BDecContent


AsnLen DivertInfo::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void DivertInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int DivertInfo::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int DivertInfo::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void DivertInfo::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case deflectCid: os << "DivertInfoSeq*"; break;
    case pickupCid: os << "DivertInfoSeq1*"; break;
    case groupCid: os << "DeviceID*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case deflectCid:
      os << "deflect : ";
      if (deflect)
        os << *deflect;
      else
        os << "VOID";
      break;

    case pickupCid:
      os << "pickup : ";
      if (pickup)
        os << *pickup;
      else
        os << "VOID";
      break;

    case groupCid:
      os << "group : ";
      if (group)
        os << *group;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // DivertInfo::Print

SnapshotCallResultSeq::SnapshotCallResultSeq( MemBlock* mb ) : AsnType( mb )
    , snapshotData( mb )
{
  extensions = NULL;
}

SnapshotCallResultSeq::SnapshotCallResultSeq( MemBlock* mb, const SnapshotCallResultSeq & ) : AsnType( mb )
    , snapshotData( mb )
{
  throw "ERROR C0099: Use of incompletely defined SnapshotCallResultSeq::SnapshotCallResultSeq (const SnapshotCallResultSeq &)";
  abort();
}

SnapshotCallResultSeq::~SnapshotCallResultSeq()
{
}

AsnType *SnapshotCallResultSeq::Clone() const
{
  return new(memBlock) SnapshotCallResultSeq(memBlock);
}

SnapshotCallResultSeq &SnapshotCallResultSeq::operator = (const SnapshotCallResultSeq &that)
{
  if (this != &that)
  {
    snapshotData = that.snapshotData;
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTAPrivateData(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
SnapshotCallResultSeq::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 29);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = snapshotData.BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 23);
    totalLen += l;

  return totalLen;
} // SnapshotCallResultSeq::BEncContent


void SnapshotCallResultSeq::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 23)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    snapshotData.BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0283: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 29)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTAPrivateData(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0284: Length discrepancy on sequence.";
  }
  else
    return;
} // SnapshotCallResultSeq::BDecContent

AsnLen SnapshotCallResultSeq::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void SnapshotCallResultSeq::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135062088: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int SnapshotCallResultSeq::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int SnapshotCallResultSeq::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void SnapshotCallResultSeq::Print ( CTsvcLIB::LOG& os ) const
{
  os << "SnapshotCallResultSeq SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "snapshotData : ";
  os << snapshotData;
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // SnapshotCallResultSeq::Print


TransferCallArgumentSeq::TransferCallArgumentSeq( MemBlock* mb ) : AsnType( mb )
{
  transferInfo = NULL; // incomplete initialization of mandatory element!
  extensions = NULL;
}

TransferCallArgumentSeq::TransferCallArgumentSeq( MemBlock* mb, const TransferCallArgumentSeq & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined TransferCallArgumentSeq::TransferCallArgumentSeq (const TransferCallArgumentSeq &)";
  abort();
}

TransferCallArgumentSeq::~TransferCallArgumentSeq()
{
}

AsnType *TransferCallArgumentSeq::Clone() const
{
  return new(memBlock) TransferCallArgumentSeq(memBlock);
}

TransferCallArgumentSeq &TransferCallArgumentSeq::operator = (const TransferCallArgumentSeq &that)
{
  if (this != &that)
  {
    if (that.transferInfo)
    {
      if (!transferInfo)
        transferInfo = new(memBlock) ConnectionDetails(memBlock);
      *transferInfo = *that.transferInfo;
    }
    else
    {
      transferInfo = NULL;
    }
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTACommonArguments(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
TransferCallArgumentSeq::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 30);
    totalLen += l;
  }

    l = transferInfo->BEncContent (b);
    totalLen += l;

  return totalLen;
} // TransferCallArgumentSeq::BEncContent


void TransferCallArgumentSeq::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (CNTX, CONS, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 1))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 2)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    transferInfo = new(memBlock) ConnectionDetails(memBlock);
    transferInfo->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0285: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 30)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTACommonArguments(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0286: Length discrepancy on sequence.";
  }
  else
    return;
} // TransferCallArgumentSeq::BDecContent

AsnLen TransferCallArgumentSeq::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void TransferCallArgumentSeq::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135062688: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int TransferCallArgumentSeq::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int TransferCallArgumentSeq::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void TransferCallArgumentSeq::Print ( CTsvcLIB::LOG& os ) const
{
  os << "TransferCallArgumentSeq SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "transferInfo : ";
  if (NOT_NULL (transferInfo))
    os << *transferInfo;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // TransferCallArgumentSeq::Print


ReconnectCallArgumentSeq::ReconnectCallArgumentSeq( MemBlock* mb ) : AsnType( mb )
{
  reconnectInfo = NULL; // incomplete initialization of mandatory element!
  extensions = NULL;
}

ReconnectCallArgumentSeq::ReconnectCallArgumentSeq( MemBlock* mb, const ReconnectCallArgumentSeq & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined ReconnectCallArgumentSeq::ReconnectCallArgumentSeq (const ReconnectCallArgumentSeq &)";
  abort();
}

ReconnectCallArgumentSeq::~ReconnectCallArgumentSeq()
{
}

AsnType *ReconnectCallArgumentSeq::Clone() const
{
  return new(memBlock) ReconnectCallArgumentSeq(memBlock);
}

ReconnectCallArgumentSeq &ReconnectCallArgumentSeq::operator = (const ReconnectCallArgumentSeq &that)
{
  if (this != &that)
  {
    if (that.reconnectInfo)
    {
      if (!reconnectInfo)
        reconnectInfo = new(memBlock) ConnectionDetails(memBlock);
      *reconnectInfo = *that.reconnectInfo;
    }
    else
    {
      reconnectInfo = NULL;
    }
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTACommonArguments(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
ReconnectCallArgumentSeq::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 30);
    totalLen += l;
  }

    l = reconnectInfo->BEncContent (b);
    totalLen += l;

  return totalLen;
} // ReconnectCallArgumentSeq::BEncContent


void ReconnectCallArgumentSeq::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (CNTX, CONS, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 1))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 2)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    reconnectInfo = new(memBlock) ConnectionDetails(memBlock);
    reconnectInfo->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0287: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 30)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTACommonArguments(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0288: Length discrepancy on sequence.";
  }
  else
    return;
} // ReconnectCallArgumentSeq::BDecContent

AsnLen ReconnectCallArgumentSeq::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void ReconnectCallArgumentSeq::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135062848: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int ReconnectCallArgumentSeq::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ReconnectCallArgumentSeq::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ReconnectCallArgumentSeq::Print ( CTsvcLIB::LOG& os ) const
{
  os << "ReconnectCallArgumentSeq SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "reconnectInfo : ";
  if (NOT_NULL (reconnectInfo))
    os << *reconnectInfo;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // ReconnectCallArgumentSeq::Print


DivertCallArgumentSeq::DivertCallArgumentSeq( MemBlock* mb ) : AsnType( mb )
{
  deivertInfo = NULL; // incomplete initialization of mandatory element!
  extensions = NULL;
}

DivertCallArgumentSeq::DivertCallArgumentSeq( MemBlock* mb, const DivertCallArgumentSeq & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined DivertCallArgumentSeq::DivertCallArgumentSeq (const DivertCallArgumentSeq &)";
  abort();
}

DivertCallArgumentSeq::~DivertCallArgumentSeq()
{
}

AsnType *DivertCallArgumentSeq::Clone() const
{
  return new(memBlock) DivertCallArgumentSeq(memBlock);
}

DivertCallArgumentSeq &DivertCallArgumentSeq::operator = (const DivertCallArgumentSeq &that)
{
  if (this != &that)
  {
    if (that.deivertInfo)
    {
      if (!deivertInfo)
        deivertInfo = new(memBlock) DivertInfo(memBlock);
      *deivertInfo = *that.deivertInfo;
    }
    else
    {
      deivertInfo = NULL;
    }
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTACommonArguments(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
DivertCallArgumentSeq::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 30);
    totalLen += l;
  }

    l = deivertInfo->BEncContent (b);
    totalLen += l;

  return totalLen;
} // DivertCallArgumentSeq::BEncContent


void DivertCallArgumentSeq::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (CNTX, CONS, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 1))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 2)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    deivertInfo = new(memBlock) DivertInfo(memBlock);
    deivertInfo->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0289: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 30)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTACommonArguments(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0290: Length discrepancy on sequence.";
  }
  else
    return;
} // DivertCallArgumentSeq::BDecContent

AsnLen DivertCallArgumentSeq::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void DivertCallArgumentSeq::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135063176: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int DivertCallArgumentSeq::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int DivertCallArgumentSeq::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void DivertCallArgumentSeq::Print ( CTsvcLIB::LOG& os ) const
{
  os << "DivertCallArgumentSeq SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "deivertInfo : ";
  if (NOT_NULL (deivertInfo))
    os << *deivertInfo;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // DivertCallArgumentSeq::Print


ConferenceCallArgumentSeq::ConferenceCallArgumentSeq( MemBlock* mb ) : AsnType( mb )
{
  callsInvolved = NULL; // incomplete initialization of mandatory element!
  extensions = NULL;
}

ConferenceCallArgumentSeq::ConferenceCallArgumentSeq( MemBlock* mb, const ConferenceCallArgumentSeq & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined ConferenceCallArgumentSeq::ConferenceCallArgumentSeq (const ConferenceCallArgumentSeq &)";
  abort();
}

ConferenceCallArgumentSeq::~ConferenceCallArgumentSeq()
{
}

AsnType *ConferenceCallArgumentSeq::Clone() const
{
  return new(memBlock) ConferenceCallArgumentSeq(memBlock);
}

ConferenceCallArgumentSeq &ConferenceCallArgumentSeq::operator = (const ConferenceCallArgumentSeq &that)
{
  if (this != &that)
  {
    if (that.callsInvolved)
    {
      if (!callsInvolved)
        callsInvolved = new(memBlock) ConnectionDetails(memBlock);
      *callsInvolved = *that.callsInvolved;
    }
    else
    {
      callsInvolved = NULL;
    }
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTACommonArguments(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
ConferenceCallArgumentSeq::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 30);
    totalLen += l;
  }

    l = callsInvolved->BEncContent (b);
    totalLen += l;

  return totalLen;
} // ConferenceCallArgumentSeq::BEncContent


void ConferenceCallArgumentSeq::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (CNTX, CONS, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 1))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 2)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    callsInvolved = new(memBlock) ConnectionDetails(memBlock);
    callsInvolved->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0291: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 30)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTACommonArguments(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0292: Length discrepancy on sequence.";
  }
  else
    return;
} // ConferenceCallArgumentSeq::BDecContent

AsnLen ConferenceCallArgumentSeq::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void ConferenceCallArgumentSeq::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135063344: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int ConferenceCallArgumentSeq::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ConferenceCallArgumentSeq::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ConferenceCallArgumentSeq::Print ( CTsvcLIB::LOG& os ) const
{
  os << "ConferenceCallArgumentSeq SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "callsInvolved : ";
  if (NOT_NULL (callsInvolved))
    os << *callsInvolved;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // ConferenceCallArgumentSeq::Print


AlternateCallArgumentSeq::AlternateCallArgumentSeq( MemBlock* mb ) : AsnType( mb )
{
  callsInvolved = NULL; // incomplete initialization of mandatory element!
  extensions = NULL;
}

AlternateCallArgumentSeq::AlternateCallArgumentSeq( MemBlock* mb, const AlternateCallArgumentSeq & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined AlternateCallArgumentSeq::AlternateCallArgumentSeq (const AlternateCallArgumentSeq &)";
  abort();
}

AlternateCallArgumentSeq::~AlternateCallArgumentSeq()
{
}

AsnType *AlternateCallArgumentSeq::Clone() const
{
  return new(memBlock) AlternateCallArgumentSeq(memBlock);
}

AlternateCallArgumentSeq &AlternateCallArgumentSeq::operator = (const AlternateCallArgumentSeq &that)
{
  if (this != &that)
  {
    if (that.callsInvolved)
    {
      if (!callsInvolved)
        callsInvolved = new(memBlock) ConnectionDetails(memBlock);
      *callsInvolved = *that.callsInvolved;
    }
    else
    {
      callsInvolved = NULL;
    }
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTACommonArguments(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
AlternateCallArgumentSeq::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 30);
    totalLen += l;
  }

    l = callsInvolved->BEncContent (b);
    totalLen += l;

  return totalLen;
} // AlternateCallArgumentSeq::BEncContent


void AlternateCallArgumentSeq::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (CNTX, CONS, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 1))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 2)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    callsInvolved = new(memBlock) ConnectionDetails(memBlock);
    callsInvolved->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0293: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 30)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTACommonArguments(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0294: Length discrepancy on sequence.";
  }
  else
    return;
} // AlternateCallArgumentSeq::BDecContent

AsnLen AlternateCallArgumentSeq::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void AlternateCallArgumentSeq::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135063784: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int AlternateCallArgumentSeq::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int AlternateCallArgumentSeq::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void AlternateCallArgumentSeq::Print ( CTsvcLIB::LOG& os ) const
{
  os << "AlternateCallArgumentSeq SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "callsInvolved : ";
  if (NOT_NULL (callsInvolved))
    os << *callsInvolved;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // AlternateCallArgumentSeq::Print


AlternateCallArgument::AlternateCallArgument( MemBlock* mb ) : AsnType( mb )
{
  choiceId = callsInvolvedCid;
  callsInvolved = NULL; // incomplete initialization of mandatory element!
}

AlternateCallArgument::AlternateCallArgument( MemBlock* mb, const AlternateCallArgument & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined AlternateCallArgument::AlternateCallArgument (const AlternateCallArgument &)";
  abort();
}

AlternateCallArgument::~AlternateCallArgument()
{
} // end of destructor

AsnType *AlternateCallArgument::Clone() const
{
  return new(memBlock) AlternateCallArgument(memBlock);
}

AlternateCallArgument &AlternateCallArgument::operator = (const AlternateCallArgument &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case callsInvolvedCid:
        callsInvolved = new(memBlock) ConnectionDetails(memBlock);
        *callsInvolved = *that.callsInvolved;
        break;
      case alternateCallArgumentSeqCid:
        alternateCallArgumentSeq = new(memBlock) AlternateCallArgumentSeq(memBlock);
        *alternateCallArgumentSeq = *that.alternateCallArgumentSeq;
        break;
    }
  }

  return *this;
}

AsnLen
AlternateCallArgument::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case callsInvolvedCid:
      l = callsInvolved->BEncContent (b);
      break;

    case alternateCallArgumentSeqCid:
      BEncEocIfNec (b);
      l = alternateCallArgumentSeq->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
      break;

  } // end switch
  return l;
} // AlternateCallArgument::BEncContent


void AlternateCallArgument::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (CNTX, CONS, 0):
    case MAKE_TAG_ID (CNTX, CONS, 1):
    case MAKE_TAG_ID (CNTX, CONS, 2):
      choiceId = callsInvolvedCid;
      callsInvolved = new(memBlock) ConnectionDetails(memBlock);
        callsInvolved->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE):
      choiceId = alternateCallArgumentSeqCid;
      alternateCallArgumentSeq = new(memBlock) AlternateCallArgumentSeq(memBlock);
        alternateCallArgumentSeq->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0295: Unexpected tag in CHOICE";
      break;
  } // end switch
} // AlternateCallArgument::BDecContent


AsnLen AlternateCallArgument::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void AlternateCallArgument::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int AlternateCallArgument::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int AlternateCallArgument::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void AlternateCallArgument::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case callsInvolvedCid: os << "ConnectionDetails*"; break;
    case alternateCallArgumentSeqCid: os << "AlternateCallArgumentSeq*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case callsInvolvedCid:
      os << "callsInvolved : ";
      if (callsInvolved)
        os << *callsInvolved;
      else
        os << "VOID";
      break;

    case alternateCallArgumentSeqCid:
      if (alternateCallArgumentSeq)
        os << *alternateCallArgumentSeq;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // AlternateCallArgument::Print

ConferenceCallArgument::ConferenceCallArgument( MemBlock* mb ) : AsnType( mb )
{
  choiceId = callsInvolvedCid;
  callsInvolved = NULL; // incomplete initialization of mandatory element!
}

ConferenceCallArgument::ConferenceCallArgument( MemBlock* mb, const ConferenceCallArgument & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined ConferenceCallArgument::ConferenceCallArgument (const ConferenceCallArgument &)";
  abort();
}

ConferenceCallArgument::~ConferenceCallArgument()
{
} // end of destructor

AsnType *ConferenceCallArgument::Clone() const
{
  return new(memBlock) ConferenceCallArgument(memBlock);
}

ConferenceCallArgument &ConferenceCallArgument::operator = (const ConferenceCallArgument &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case callsInvolvedCid:
        callsInvolved = new(memBlock) ConnectionDetails(memBlock);
        *callsInvolved = *that.callsInvolved;
        break;
      case conferenceCallArgumentSeqCid:
        conferenceCallArgumentSeq = new(memBlock) ConferenceCallArgumentSeq(memBlock);
        *conferenceCallArgumentSeq = *that.conferenceCallArgumentSeq;
        break;
    }
  }

  return *this;
}

AsnLen
ConferenceCallArgument::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case callsInvolvedCid:
      l = callsInvolved->BEncContent (b);
      break;

    case conferenceCallArgumentSeqCid:
      BEncEocIfNec (b);
      l = conferenceCallArgumentSeq->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
      break;

  } // end switch
  return l;
} // ConferenceCallArgument::BEncContent


void ConferenceCallArgument::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (CNTX, CONS, 0):
    case MAKE_TAG_ID (CNTX, CONS, 1):
    case MAKE_TAG_ID (CNTX, CONS, 2):
      choiceId = callsInvolvedCid;
      callsInvolved = new(memBlock) ConnectionDetails(memBlock);
        callsInvolved->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE):
      choiceId = conferenceCallArgumentSeqCid;
      conferenceCallArgumentSeq = new(memBlock) ConferenceCallArgumentSeq(memBlock);
        conferenceCallArgumentSeq->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0296: Unexpected tag in CHOICE";
      break;
  } // end switch
} // ConferenceCallArgument::BDecContent


AsnLen ConferenceCallArgument::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void ConferenceCallArgument::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int ConferenceCallArgument::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ConferenceCallArgument::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ConferenceCallArgument::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case callsInvolvedCid: os << "ConnectionDetails*"; break;
    case conferenceCallArgumentSeqCid: os << "ConferenceCallArgumentSeq*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case callsInvolvedCid:
      os << "callsInvolved : ";
      if (callsInvolved)
        os << *callsInvolved;
      else
        os << "VOID";
      break;

    case conferenceCallArgumentSeqCid:
      if (conferenceCallArgumentSeq)
        os << *conferenceCallArgumentSeq;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // ConferenceCallArgument::Print

ConferenceCallResult::ConferenceCallResult( MemBlock* mb ) : AsnType( mb )
{
  conferenceCall = NULL; // incomplete initialization of mandatory element!
  connections = NULL;
  extensions = NULL;
}

ConferenceCallResult::ConferenceCallResult( MemBlock* mb, const ConferenceCallResult & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined ConferenceCallResult::ConferenceCallResult (const ConferenceCallResult &)";
  abort();
}

ConferenceCallResult::~ConferenceCallResult()
{
}

AsnType *ConferenceCallResult::Clone() const
{
  return new(memBlock) ConferenceCallResult(memBlock);
}

ConferenceCallResult &ConferenceCallResult::operator = (const ConferenceCallResult &that)
{
  if (this != &that)
  {
    if (that.conferenceCall)
    {
      if (!conferenceCall)
        conferenceCall = new(memBlock) ConnectionID(memBlock);
      *conferenceCall = *that.conferenceCall;
    }
    else
    {
      conferenceCall = NULL;
    }
    if (that.connections)
    {
      if (!connections)
        connections = new(memBlock) ConnectionList(memBlock);
      *connections = *that.connections;
    }
    else
    {
      connections = NULL;
    }
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTAPrivateData(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
ConferenceCallResult::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 29);
    totalLen += l;
  }

  if (NOT_NULL (connections))
  {
    l = connections->BEncContent (b);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = conferenceCall->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;

  return totalLen;
} // ConferenceCallResult::BEncContent


void ConferenceCallResult::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    conferenceCall = new(memBlock) ConnectionID(memBlock);
    conferenceCall->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0297: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 12))
    || (tag1 == MAKE_TAG_ID (APPL, CONS, 13)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    connections = new(memBlock) ConnectionList(memBlock);
    connections->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 29)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTAPrivateData(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0298: Length discrepancy on sequence.";
  }
  else
    return;
} // ConferenceCallResult::BDecContent

AsnLen ConferenceCallResult::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void ConferenceCallResult::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135065936: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int ConferenceCallResult::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ConferenceCallResult::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ConferenceCallResult::Print ( CTsvcLIB::LOG& os ) const
{
  os << "ConferenceCallResult SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "conferenceCall : ";
  if (NOT_NULL (conferenceCall))
    os << *conferenceCall;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "connections : ";
  if (NOT_NULL (connections))
    os << *connections;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // ConferenceCallResult::Print


DivertCallArgument::DivertCallArgument( MemBlock* mb ) : AsnType( mb )
{
  choiceId = divertInfoCid;
  divertInfo = NULL; // incomplete initialization of mandatory element!
}

DivertCallArgument::DivertCallArgument( MemBlock* mb, const DivertCallArgument & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined DivertCallArgument::DivertCallArgument (const DivertCallArgument &)";
  abort();
}

DivertCallArgument::~DivertCallArgument()
{
} // end of destructor

AsnType *DivertCallArgument::Clone() const
{
  return new(memBlock) DivertCallArgument(memBlock);
}

DivertCallArgument &DivertCallArgument::operator = (const DivertCallArgument &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case divertInfoCid:
        divertInfo = new(memBlock) DivertInfo(memBlock);
        *divertInfo = *that.divertInfo;
        break;
      case divertCallArgumentSeqCid:
        divertCallArgumentSeq = new(memBlock) DivertCallArgumentSeq(memBlock);
        *divertCallArgumentSeq = *that.divertCallArgumentSeq;
        break;
    }
  }

  return *this;
}

AsnLen
DivertCallArgument::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case divertInfoCid:
      l = divertInfo->BEncContent (b);
      break;

    case divertCallArgumentSeqCid:
      BEncEocIfNec (b);
      l = divertCallArgumentSeq->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
      break;

  } // end switch
  return l;
} // DivertCallArgument::BEncContent


void DivertCallArgument::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (CNTX, CONS, 0):
    case MAKE_TAG_ID (CNTX, CONS, 1):
    case MAKE_TAG_ID (CNTX, CONS, 2):
      choiceId = divertInfoCid;
      divertInfo = new(memBlock) DivertInfo(memBlock);
        divertInfo->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE):
      choiceId = divertCallArgumentSeqCid;
      divertCallArgumentSeq = new(memBlock) DivertCallArgumentSeq(memBlock);
        divertCallArgumentSeq->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0299: Unexpected tag in CHOICE";
      break;
  } // end switch
} // DivertCallArgument::BDecContent


AsnLen DivertCallArgument::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void DivertCallArgument::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int DivertCallArgument::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int DivertCallArgument::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void DivertCallArgument::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case divertInfoCid: os << "DivertInfo*"; break;
    case divertCallArgumentSeqCid: os << "DivertCallArgumentSeq*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case divertInfoCid:
      os << "divertInfo : ";
      if (divertInfo)
        os << *divertInfo;
      else
        os << "VOID";
      break;

    case divertCallArgumentSeqCid:
      if (divertCallArgumentSeq)
        os << *divertCallArgumentSeq;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // DivertCallArgument::Print

ReconnectCallArgument::ReconnectCallArgument( MemBlock* mb ) : AsnType( mb )
{
  choiceId = reconnectInfoCid;
  reconnectInfo = NULL; // incomplete initialization of mandatory element!
}

ReconnectCallArgument::ReconnectCallArgument( MemBlock* mb, const ReconnectCallArgument & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined ReconnectCallArgument::ReconnectCallArgument (const ReconnectCallArgument &)";
  abort();
}

ReconnectCallArgument::~ReconnectCallArgument()
{
} // end of destructor

AsnType *ReconnectCallArgument::Clone() const
{
  return new(memBlock) ReconnectCallArgument(memBlock);
}

ReconnectCallArgument &ReconnectCallArgument::operator = (const ReconnectCallArgument &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case reconnectInfoCid:
        reconnectInfo = new(memBlock) ConnectionDetails(memBlock);
        *reconnectInfo = *that.reconnectInfo;
        break;
      case reconnectCallArgumentSeqCid:
        reconnectCallArgumentSeq = new(memBlock) ReconnectCallArgumentSeq(memBlock);
        *reconnectCallArgumentSeq = *that.reconnectCallArgumentSeq;
        break;
    }
  }

  return *this;
}

AsnLen
ReconnectCallArgument::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case reconnectInfoCid:
      l = reconnectInfo->BEncContent (b);
      break;

    case reconnectCallArgumentSeqCid:
      BEncEocIfNec (b);
      l = reconnectCallArgumentSeq->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
      break;

  } // end switch
  return l;
} // ReconnectCallArgument::BEncContent


void ReconnectCallArgument::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (CNTX, CONS, 0):
    case MAKE_TAG_ID (CNTX, CONS, 1):
    case MAKE_TAG_ID (CNTX, CONS, 2):
      choiceId = reconnectInfoCid;
      reconnectInfo = new(memBlock) ConnectionDetails(memBlock);
        reconnectInfo->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE):
      choiceId = reconnectCallArgumentSeqCid;
      reconnectCallArgumentSeq = new(memBlock) ReconnectCallArgumentSeq(memBlock);
        reconnectCallArgumentSeq->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0300: Unexpected tag in CHOICE";
      break;
  } // end switch
} // ReconnectCallArgument::BDecContent


AsnLen ReconnectCallArgument::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void ReconnectCallArgument::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int ReconnectCallArgument::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ReconnectCallArgument::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ReconnectCallArgument::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case reconnectInfoCid: os << "ConnectionDetails*"; break;
    case reconnectCallArgumentSeqCid: os << "ReconnectCallArgumentSeq*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case reconnectInfoCid:
      os << "reconnectInfo : ";
      if (reconnectInfo)
        os << *reconnectInfo;
      else
        os << "VOID";
      break;

    case reconnectCallArgumentSeqCid:
      if (reconnectCallArgumentSeq)
        os << *reconnectCallArgumentSeq;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // ReconnectCallArgument::Print

TransferCallArgument::TransferCallArgument( MemBlock* mb ) : AsnType( mb )
{
  choiceId = transferInfoCid;
  transferInfo = NULL; // incomplete initialization of mandatory element!
}

TransferCallArgument::TransferCallArgument( MemBlock* mb, const TransferCallArgument & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined TransferCallArgument::TransferCallArgument (const TransferCallArgument &)";
  abort();
}

TransferCallArgument::~TransferCallArgument()
{
} // end of destructor

AsnType *TransferCallArgument::Clone() const
{
  return new(memBlock) TransferCallArgument(memBlock);
}

TransferCallArgument &TransferCallArgument::operator = (const TransferCallArgument &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case transferInfoCid:
        transferInfo = new(memBlock) ConnectionDetails(memBlock);
        *transferInfo = *that.transferInfo;
        break;
      case transferCallArgumentSeqCid:
        transferCallArgumentSeq = new(memBlock) TransferCallArgumentSeq(memBlock);
        *transferCallArgumentSeq = *that.transferCallArgumentSeq;
        break;
    }
  }

  return *this;
}

AsnLen
TransferCallArgument::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case transferInfoCid:
      l = transferInfo->BEncContent (b);
      break;

    case transferCallArgumentSeqCid:
      BEncEocIfNec (b);
      l = transferCallArgumentSeq->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
      break;

  } // end switch
  return l;
} // TransferCallArgument::BEncContent


void TransferCallArgument::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (CNTX, CONS, 0):
    case MAKE_TAG_ID (CNTX, CONS, 1):
    case MAKE_TAG_ID (CNTX, CONS, 2):
      choiceId = transferInfoCid;
      transferInfo = new(memBlock) ConnectionDetails(memBlock);
        transferInfo->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE):
      choiceId = transferCallArgumentSeqCid;
      transferCallArgumentSeq = new(memBlock) TransferCallArgumentSeq(memBlock);
        transferCallArgumentSeq->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0301: Unexpected tag in CHOICE";
      break;
  } // end switch
} // TransferCallArgument::BDecContent


AsnLen TransferCallArgument::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void TransferCallArgument::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int TransferCallArgument::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int TransferCallArgument::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void TransferCallArgument::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case transferInfoCid: os << "ConnectionDetails*"; break;
    case transferCallArgumentSeqCid: os << "TransferCallArgumentSeq*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case transferInfoCid:
      os << "transferInfo : ";
      if (transferInfo)
        os << *transferInfo;
      else
        os << "VOID";
      break;

    case transferCallArgumentSeqCid:
      if (transferCallArgumentSeq)
        os << *transferCallArgumentSeq;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // TransferCallArgument::Print

TransferCallResult::TransferCallResult( MemBlock* mb ) : AsnType( mb )
{
  transferredCall = NULL;
  connections = NULL;
  extensions = NULL;
}

TransferCallResult::TransferCallResult( MemBlock* mb, const TransferCallResult & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined TransferCallResult::TransferCallResult (const TransferCallResult &)";
  abort();
}

TransferCallResult::~TransferCallResult()
{
}

AsnType *TransferCallResult::Clone() const
{
  return new(memBlock) TransferCallResult(memBlock);
}

TransferCallResult &TransferCallResult::operator = (const TransferCallResult &that)
{
  if (this != &that)
  {
    if (that.transferredCall)
    {
      if (!transferredCall)
        transferredCall = new(memBlock) ConnectionID(memBlock);
      *transferredCall = *that.transferredCall;
    }
    else
    {
      transferredCall = NULL;
    }
    if (that.connections)
    {
      if (!connections)
        connections = new(memBlock) ConnectionList(memBlock);
      *connections = *that.connections;
    }
    else
    {
      connections = NULL;
    }
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTAPrivateData(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
TransferCallResult::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 29);
    totalLen += l;
  }

  if (NOT_NULL (connections))
  {
    l = connections->BEncContent (b);
    totalLen += l;
  }

  if (NOT_NULL (transferredCall))
  {
      BEncEocIfNec (b);
    l = transferredCall->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;
  }

  return totalLen;
} // TransferCallResult::BEncContent


void TransferCallResult::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  if (elmtLen0 == 0)
    return;
  else
  {
    tag1 = BDecTag (b, seqBytesDecoded);

    if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
    {
      BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
      bytesDecoded += seqBytesDecoded;
      return;
    }
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    transferredCall = new(memBlock) ConnectionID(memBlock);
    transferredCall->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 12))
    || (tag1 == MAKE_TAG_ID (APPL, CONS, 13)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    connections = new(memBlock) ConnectionList(memBlock);
    connections->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 29)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTAPrivateData(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0302: Length discrepancy on sequence.";
  }
  else
    return;
} // TransferCallResult::BDecContent

AsnLen TransferCallResult::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void TransferCallResult::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135067632: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int TransferCallResult::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int TransferCallResult::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void TransferCallResult::Print ( CTsvcLIB::LOG& os ) const
{
  os << "TransferCallResult SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "transferredCall : ";
  if (NOT_NULL (transferredCall))
    os << *transferredCall;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "connections : ";
  if (NOT_NULL (connections))
    os << *connections;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // TransferCallResult::Print


MonitorStartArgument::MonitorStartArgument( MemBlock* mb ) : AsnType( mb )
{
  monitorObject = NULL; // incomplete initialization of mandatory element!
  monitorFilter = NULL;
  monitorType = NULL;
  extensions = NULL;
}

MonitorStartArgument::MonitorStartArgument( MemBlock* mb, const MonitorStartArgument & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined MonitorStartArgument::MonitorStartArgument (const MonitorStartArgument &)";
  abort();
}

MonitorStartArgument::~MonitorStartArgument()
{
}

AsnType *MonitorStartArgument::Clone() const
{
  return new(memBlock) MonitorStartArgument(memBlock);
}

MonitorStartArgument &MonitorStartArgument::operator = (const MonitorStartArgument &that)
{
  if (this != &that)
  {
    if (that.monitorObject)
    {
      if (!monitorObject)
        monitorObject = new(memBlock) MonitorObject(memBlock);
      *monitorObject = *that.monitorObject;
    }
    else
    {
      monitorObject = NULL;
    }
    if (that.monitorFilter)
    {
      if (!monitorFilter)
        monitorFilter = new(memBlock) MonitorFilter(memBlock);
      *monitorFilter = *that.monitorFilter;
    }
    else
    {
      monitorFilter = NULL;
    }
    if (that.monitorType)
    {
      if (!monitorType)
        monitorType = new(memBlock) MonitorType(memBlock);
      *monitorType = *that.monitorType;
    }
    else
    {
      monitorType = NULL;
    }
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTACommonArguments(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
MonitorStartArgument::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 30);
    totalLen += l;
  }

  if (NOT_NULL (monitorType))
  {
    l = monitorType->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, ENUM_TAG_CODE);
    totalLen += l;
  }

  if (NOT_NULL (monitorFilter))
  {
      BEncEocIfNec (b);
    l = monitorFilter->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
    totalLen += l;
  }

    l = monitorObject->BEncContent (b);
    totalLen += l;

  return totalLen;
} // MonitorStartArgument::BEncContent


void MonitorStartArgument::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 1))
    || (tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    monitorObject = new(memBlock) MonitorObject(memBlock);
    monitorObject->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0303: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    monitorFilter = new(memBlock) MonitorFilter(memBlock);
    monitorFilter->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, ENUM_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    monitorType = new(memBlock) MonitorType(memBlock);
    monitorType->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 30)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTACommonArguments(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0304: Length discrepancy on sequence.";
  }
  else
    return;
} // MonitorStartArgument::BDecContent

AsnLen MonitorStartArgument::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void MonitorStartArgument::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135071008: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int MonitorStartArgument::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int MonitorStartArgument::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void MonitorStartArgument::Print ( CTsvcLIB::LOG& os ) const
{
  os << "MonitorStartArgument SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "monitorObject : ";
  if (NOT_NULL (monitorObject))
    os << *monitorObject;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "monitorFilter : ";
  if (NOT_NULL (monitorFilter))
    os << *monitorFilter;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "monitorType : ";
  if (NOT_NULL (monitorType))
    os << *monitorType;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // MonitorStartArgument::Print


SnapshotCallResult::SnapshotCallResult( MemBlock* mb ) : AsnType( mb )
{
  choiceId = snapshotDataCid;
  snapshotData = NULL; // incomplete initialization of mandatory element!
}

SnapshotCallResult::SnapshotCallResult( MemBlock* mb, const SnapshotCallResult & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined SnapshotCallResult::SnapshotCallResult (const SnapshotCallResult &)";
  abort();
}

SnapshotCallResult::~SnapshotCallResult()
{
} // end of destructor

AsnType *SnapshotCallResult::Clone() const
{
  return new(memBlock) SnapshotCallResult(memBlock);
}

SnapshotCallResult &SnapshotCallResult::operator = (const SnapshotCallResult &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case snapshotDataCid:
        snapshotData = new(memBlock) SnapshotCallData(memBlock);
        *snapshotData = *that.snapshotData;
        break;
      case snapshotCallResultSeqCid:
        snapshotCallResultSeq = new(memBlock) SnapshotCallResultSeq(memBlock);
        *snapshotCallResultSeq = *that.snapshotCallResultSeq;
        break;
    }
  }

  return *this;
}

AsnLen
SnapshotCallResult::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case snapshotDataCid:
      BEncEocIfNec (b);
      l = snapshotData->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 23);
      break;

    case snapshotCallResultSeqCid:
      BEncEocIfNec (b);
      l = snapshotCallResultSeq->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
      break;

  } // end switch
  return l;
} // SnapshotCallResult::BEncContent


void SnapshotCallResult::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (APPL, CONS, 23):
      choiceId = snapshotDataCid;
      snapshotData = new(memBlock) SnapshotCallData(memBlock);
        snapshotData->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE):
      choiceId = snapshotCallResultSeqCid;
      snapshotCallResultSeq = new(memBlock) SnapshotCallResultSeq(memBlock);
        snapshotCallResultSeq->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0305: Unexpected tag in CHOICE";
      break;
  } // end switch
} // SnapshotCallResult::BDecContent


AsnLen SnapshotCallResult::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void SnapshotCallResult::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int SnapshotCallResult::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int SnapshotCallResult::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void SnapshotCallResult::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case snapshotDataCid: os << "SnapshotCallData*"; break;
    case snapshotCallResultSeqCid: os << "SnapshotCallResultSeq*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case snapshotDataCid:
      os << "snapshotData : ";
      if (snapshotData)
        os << *snapshotData;
      else
        os << "VOID";
      break;

    case snapshotCallResultSeqCid:
      if (snapshotCallResultSeq)
        os << *snapshotCallResultSeq;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // SnapshotCallResult::Print

AsnType *SnapshotDeviceData::Clone() const
{
  return new(memBlock) SnapshotDeviceData(memBlock);
}

AsnLen SnapshotDeviceData::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, APPL, CONS, 22);
  return l;
}

void SnapshotDeviceData::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (APPL, CONS, 22))
  {
    throw "ERROR C0306: SnapshotDeviceData.BDec(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

SnapshotDeviceData::SnapshotDeviceData( MemBlock* mb, const SnapshotDeviceData & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined SnapshotDeviceData::SnapshotDeviceData (const SnapshotDeviceData &)";
  abort();
}

SnapshotDeviceData::~SnapshotDeviceData()
{
  SetCurrToFirst();
  for (; Curr() != NULL; RemoveCurrFromList())
    ;
} // end of destructor

SnapshotDeviceData &SnapshotDeviceData::operator = (const SnapshotDeviceData &that)
{
  if (this != &that)
  {
    SetCurrToFirst();
    for (; Curr(); RemoveCurrFromList())
      ;

    //that.SetCurrToFirst();
    //for (; that.Curr(); that.GoNext())
    //  AppendCopy (*that.Curr());
    for (const AsnListElmt *run=that.first; run; run=run->next)
      AppendCopy (*run->elmt);
  }

  return *this;
}

void SnapshotDeviceData::Print ( CTsvcLIB::LOG& os ) const
{
    os << "SnapshotDeviceData SEQUENCE/SET OF" << CTsvcLIB::eline;
    Indent (os, indentG);
    os << "{" << CTsvcLIB::eline;
    indentG += stdIndentG;
    for (const AsnListElmt *run=first; run; run=run->next)
    {
        Indent (os, indentG);
        os << *run->elmt;
        if (run != last)
            os << ",";
        os << CTsvcLIB::eline;
    }
    indentG -= stdIndentG;
    Indent (os, indentG);
    os << "}";
} // Print


void  SnapshotDeviceData::SetCurrElmt (unsigned long int index)
{
  unsigned long int i;
  curr = first;
  if (count)
    for (i = 0; (i < (count-1)) && (i < index); i++)
      curr = curr->next;
} // SnapshotDeviceData::SetCurrElmt


unsigned long int  SnapshotDeviceData::GetCurrElmtIndex()
{
    unsigned long int i;
    AsnListElmt *tmp;
    if (curr != NULL)
    {
        for (i = 0, tmp = first; tmp != NULL; i++)
        {
            if (tmp == curr)
                return i;
            else
                tmp = tmp->next;
        }
    }
    return count;
} // SnapshotDeviceData::GetCurrElmtIndex


// alloc new list elmt, put at end of list
//  and return the component type
SnapshotDeviceResponseInfo *SnapshotDeviceData::Append()
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt  = new(memBlock) SnapshotDeviceResponseInfo(memBlock);
    newElmt->next = NULL;
    if (last == NULL)
    {
        newElmt->prev = NULL;
        first = last  = newElmt;
    }
    else
    {
        newElmt->prev = last;
        last->next    = newElmt;
        last          = newElmt;
    }
    count++;
    return (curr = newElmt)->elmt;
} // SnapshotDeviceData::Append


// alloc new list elmt, put at begining of list
//  and return the component type
SnapshotDeviceResponseInfo  *SnapshotDeviceData::Prepend()
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) SnapshotDeviceResponseInfo(memBlock);
    newElmt->prev = NULL;
    if (first == NULL)
    {
        newElmt->next = NULL;
        first = last  = newElmt;
    }
    else
    {
        newElmt->next = first;
        first->prev   = newElmt;
        first         = newElmt;
    }
    count++;
    return (curr = newElmt)->elmt;
} // SnapshotDeviceData::Prepend


// alloc new list elmt, insert it before the
// current element and return the component type
// if the current element is null, the new element
// is placed at the beginning of the list.
SnapshotDeviceResponseInfo  *SnapshotDeviceData::InsertBefore()
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) SnapshotDeviceResponseInfo(memBlock);
    if (curr == NULL)
    {
        newElmt->next = first;
        newElmt->prev = NULL;
        first = newElmt;
        if (last == NULL)
            last = newElmt;
    }
    else
    {
        newElmt->next = curr;
        newElmt->prev = curr->prev;
        curr->prev = newElmt;
        if (curr == first)
            first = newElmt;
        else
            newElmt->prev->next = newElmt;
    }
    count++;
    return (curr = newElmt)->elmt;
} // SnapshotDeviceData::InsertBefore


// alloc new list elmt, insert it after the
// current element and return the component type
// if the current element is null, the new element
// is placed at the end of the list.
SnapshotDeviceResponseInfo *SnapshotDeviceData::InsertAfter()
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) SnapshotDeviceResponseInfo(memBlock);
    if (curr == NULL)
    {
        newElmt->prev = last;
        newElmt->next = NULL;
        last = newElmt;
        if (first == NULL)
            first = newElmt;
    }
    else
    {
        newElmt->prev = curr;
        newElmt->next = curr->next;
        curr->next = newElmt;
        if (curr == last)
            last = newElmt;
        else
            newElmt->next->prev = newElmt;
    }
    count++;
    return (curr = newElmt)->elmt;
} // SnapshotDeviceData::InsertAfter


SnapshotDeviceData  &SnapshotDeviceData::AppendCopy (SnapshotDeviceResponseInfo &elmt)
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) SnapshotDeviceResponseInfo(memBlock);
    *newElmt->elmt = elmt;
    newElmt->next = NULL;
    if (last == NULL)
    {
        newElmt->prev = NULL;
        first = last  = newElmt;
    }
    else
    {
        newElmt->prev = last;
        last->next    = newElmt;
        last          = newElmt;
    }
    count++;
    return *this;
} // AppendCopy


SnapshotDeviceData  &SnapshotDeviceData::PrependCopy (SnapshotDeviceResponseInfo &elmt)
{
    AsnListElmt *newElmt;
    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) SnapshotDeviceResponseInfo(memBlock);
    *newElmt->elmt = elmt;
    newElmt->prev = NULL;
    if (first == NULL)
    {
        newElmt->next = NULL;
        first = last  = newElmt;
    }
    else
    {
        newElmt->next = first;
        first->prev   = newElmt;
        first         = newElmt;
    }
    count++;
    return *this;
} // SnapshotDeviceData::PrependCopy


// alloc new list elmt, insert it before the
// current element, copy the given elmt into the new elmt
// and return the component type.
// if the current element is null, the new element
// is placed at the beginning of the list.
SnapshotDeviceData &SnapshotDeviceData::InsertBeforeAndCopy (SnapshotDeviceResponseInfo &elmt)
{
    AsnListElmt *newElmt;

    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) SnapshotDeviceResponseInfo(memBlock);
    *newElmt->elmt = elmt;

    if (curr == NULL)
    {
        newElmt->next = first;
        newElmt->prev = NULL;
        first = newElmt;
        if (last == NULL)
            last = newElmt;
    }
    else
    {
        newElmt->next = curr;
        newElmt->prev = curr->prev;
        curr->prev = newElmt;
        if (curr == first)
            first = newElmt;
        else
            newElmt->prev->next = newElmt;
    }
    count++;
    return *this;
} // SnapshotDeviceData::InsertBeforeAndCopy


// alloc new list elmt, insert it after the
// current element, copy given elmt in to new elmt
//  and return the component type
// if the current element is null, the new element
// is placed at the end of the list.
SnapshotDeviceData  &SnapshotDeviceData::InsertAfterAndCopy (SnapshotDeviceResponseInfo &elmt)
{
    AsnListElmt *newElmt;

    newElmt  = new(memBlock) AsnListElmt;
    newElmt->elmt = new(memBlock) SnapshotDeviceResponseInfo(memBlock);
    *newElmt->elmt = elmt;
    if (curr == NULL)
    {
        newElmt->prev = last;
        newElmt->next = NULL;
        last = newElmt;
        if (first == NULL)
            first = newElmt;
    }
    else
    {
        newElmt->prev = curr;
        newElmt->next = curr->next;
        curr->next = newElmt;
        if (curr == last)
            last = newElmt;
        else
            newElmt->next->prev = newElmt;
    }
    count++;
    return *this;
} // SnapshotDeviceData::InsertAfterAndCopy


// remove current element from list if current element is not NULL 
// The new current element will be the next element.
// If the current element is the last element in the list
// the second but last element will become the new current element.
void SnapshotDeviceData::RemoveCurrFromList()
{
    AsnListElmt *del_elmt;

    if (curr != NULL)
    {
        del_elmt = curr;
        count--;

        if (count == 0)
            first = last = curr = NULL;
        else if (curr == first)
        {
            curr = first= first->next;
            first->prev = NULL;
        }
        else if (curr == last)
        {
            curr = last = last->prev;
            last->next = NULL;
        }
        else
        {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
        }

    }
}


AsnLen SnapshotDeviceData::BEncContent (AsnBuf& b)
{
    AsnListElmt *currElmt;
    AsnLen elmtLen;
    AsnLen totalLen = 0;
    for (currElmt = last; currElmt != NULL; currElmt = currElmt->prev)
    {
      BEncEocIfNec (b);
        elmtLen = currElmt->elmt->BEncContent (b);
    elmtLen += BEncConsLen (b, elmtLen);

    elmtLen += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
        totalLen += elmtLen;
    }
    return totalLen;
} // SnapshotDeviceData::BEncContent


void  SnapshotDeviceData::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0,
                                  AsnLen &bytesDecoded)
{
    SnapshotDeviceResponseInfo *listElmt;
    AsnTag tag1;
    AsnLen listBytesDecoded = 0;
    AsnLen elmtLen1;

    while ((listBytesDecoded < elmtLen0) || (elmtLen0 == INDEFINITE_LEN))
    {
        tag1 = BDecTag (b, listBytesDecoded);
        if ((tag1 == EOC_TAG_ID) && (elmtLen0 == INDEFINITE_LEN))
        {
            BDEC_2ND_EOC_OCTET (b, listBytesDecoded);
            break;
        }
        if ((tag1 != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE) ))
        {
            throw "ERROR C0307: Unexpected Tag";
        }

        elmtLen1 = BDecLen (b, listBytesDecoded);
        listElmt = Append();
        listElmt->BDecContent (b, tag1, elmtLen1, listBytesDecoded);
    }

    bytesDecoded += listBytesDecoded;
} // SnapshotDeviceData::BDecContent


SnapshotDeviceResultSeq::SnapshotDeviceResultSeq( MemBlock* mb ) : AsnType( mb )
    , snapshotData( mb )
{
  extensions = NULL;
}

SnapshotDeviceResultSeq::SnapshotDeviceResultSeq( MemBlock* mb, const SnapshotDeviceResultSeq & ) : AsnType( mb )
    , snapshotData( mb )
{
  throw "ERROR C0099: Use of incompletely defined SnapshotDeviceResultSeq::SnapshotDeviceResultSeq (const SnapshotDeviceResultSeq &)";
  abort();
}

SnapshotDeviceResultSeq::~SnapshotDeviceResultSeq()
{
}

AsnType *SnapshotDeviceResultSeq::Clone() const
{
  return new(memBlock) SnapshotDeviceResultSeq(memBlock);
}

SnapshotDeviceResultSeq &SnapshotDeviceResultSeq::operator = (const SnapshotDeviceResultSeq &that)
{
  if (this != &that)
  {
    snapshotData = that.snapshotData;
    if (that.extensions)
    {
      if (!extensions)
        extensions = new(memBlock) CSTAPrivateData(memBlock);
      *extensions = *that.extensions;
    }
    else
    {
      extensions = NULL;
    }
  }

  return *this;
}

AsnLen
SnapshotDeviceResultSeq::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (extensions))
  {
      BEncEocIfNec (b);
    l = extensions->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 29);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = snapshotData.BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 22);
    totalLen += l;

  return totalLen;
} // SnapshotDeviceResultSeq::BEncContent


void SnapshotDeviceResultSeq::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 22)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    snapshotData.BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0308: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 29)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    extensions = new(memBlock) CSTAPrivateData(memBlock);
    extensions->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0309: Length discrepancy on sequence.";
  }
  else
    return;
} // SnapshotDeviceResultSeq::BDecContent

AsnLen SnapshotDeviceResultSeq::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void SnapshotDeviceResultSeq::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135062248: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int SnapshotDeviceResultSeq::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int SnapshotDeviceResultSeq::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void SnapshotDeviceResultSeq::Print ( CTsvcLIB::LOG& os ) const
{
  os << "SnapshotDeviceResultSeq SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "snapshotData : ";
  os << snapshotData;
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "extensions : ";
  if (NOT_NULL (extensions))
    os << *extensions;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // SnapshotDeviceResultSeq::Print


SnapshotDeviceResult::SnapshotDeviceResult( MemBlock* mb ) : AsnType( mb )
{
  choiceId = snapshotDataCid;
  snapshotData = NULL; // incomplete initialization of mandatory element!
}

SnapshotDeviceResult::SnapshotDeviceResult( MemBlock* mb, const SnapshotDeviceResult & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined SnapshotDeviceResult::SnapshotDeviceResult (const SnapshotDeviceResult &)";
  abort();
}

SnapshotDeviceResult::~SnapshotDeviceResult()
{
} // end of destructor

AsnType *SnapshotDeviceResult::Clone() const
{
  return new(memBlock) SnapshotDeviceResult(memBlock);
}

SnapshotDeviceResult &SnapshotDeviceResult::operator = (const SnapshotDeviceResult &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case snapshotDataCid:
        snapshotData = new(memBlock) SnapshotDeviceData(memBlock);
        *snapshotData = *that.snapshotData;
        break;
      case snapshotDeviceResultSeqCid:
        snapshotDeviceResultSeq = new(memBlock) SnapshotDeviceResultSeq(memBlock);
        *snapshotDeviceResultSeq = *that.snapshotDeviceResultSeq;
        break;
    }
  }

  return *this;
}

AsnLen
SnapshotDeviceResult::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case snapshotDataCid:
      BEncEocIfNec (b);
      l = snapshotData->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 22);
      break;

    case snapshotDeviceResultSeqCid:
      BEncEocIfNec (b);
      l = snapshotDeviceResultSeq->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
      break;

  } // end switch
  return l;
} // SnapshotDeviceResult::BEncContent


void SnapshotDeviceResult::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  switch (tag)
  {
    case MAKE_TAG_ID (APPL, CONS, 22):
      choiceId = snapshotDataCid;
      snapshotData = new(memBlock) SnapshotDeviceData(memBlock);
        snapshotData->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE):
      choiceId = snapshotDeviceResultSeqCid;
      snapshotDeviceResultSeq = new(memBlock) SnapshotDeviceResultSeq(memBlock);
        snapshotDeviceResultSeq->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0310: Unexpected tag in CHOICE";
      break;
  } // end switch
} // SnapshotDeviceResult::BDecContent


AsnLen SnapshotDeviceResult::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void SnapshotDeviceResult::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int SnapshotDeviceResult::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int SnapshotDeviceResult::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void SnapshotDeviceResult::Print ( CTsvcLIB::LOG& os ) const
{
  switch (choiceId)
  {
    case snapshotDataCid: os << "SnapshotDeviceData*"; break;
    case snapshotDeviceResultSeqCid: os << "SnapshotDeviceResultSeq*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case snapshotDataCid:
      os << "snapshotData : ";
      if (snapshotData)
        os << *snapshotData;
      else
        os << "VOID";
      break;

    case snapshotDeviceResultSeqCid:
      if (snapshotDeviceResultSeq)
        os << *snapshotDeviceResultSeq;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // SnapshotDeviceResult::Print

CallClearedEventInfo::CallClearedEventInfo( MemBlock* mb ) : AsnType( mb )
{
  clearedCall = NULL; // incomplete initialization of mandatory element!
  localConnectionInfo = NULL;
  cause = NULL;
}

CallClearedEventInfo::CallClearedEventInfo( MemBlock* mb, const CallClearedEventInfo & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined CallClearedEventInfo::CallClearedEventInfo (const CallClearedEventInfo &)";
  abort();
}

CallClearedEventInfo::~CallClearedEventInfo()
{
}

AsnType *CallClearedEventInfo::Clone() const
{
  return new(memBlock) CallClearedEventInfo(memBlock);
}

CallClearedEventInfo &CallClearedEventInfo::operator = (const CallClearedEventInfo &that)
{
  if (this != &that)
  {
    if (that.clearedCall)
    {
      if (!clearedCall)
        clearedCall = new(memBlock) ConnectionID(memBlock);
      *clearedCall = *that.clearedCall;
    }
    else
    {
      clearedCall = NULL;
    }
    if (that.localConnectionInfo)
    {
      if (!localConnectionInfo)
        localConnectionInfo = new(memBlock) LocalConnectionState(memBlock);
      *localConnectionInfo = *that.localConnectionInfo;
    }
    else
    {
      localConnectionInfo = NULL;
    }
    if (that.cause)
    {
      if (!cause)
        cause = new(memBlock) EventCause(memBlock);
      *cause = *that.cause;
    }
    else
    {
      cause = NULL;
    }
  }

  return *this;
}

AsnLen
CallClearedEventInfo::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (cause))
  {
    l = cause->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, ENUM_TAG_CODE);
    totalLen += l;
  }

  if (NOT_NULL (localConnectionInfo))
  {
    l = localConnectionInfo->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, APPL, PRIM, 14);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = clearedCall->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;

  return totalLen;
} // CallClearedEventInfo::BEncContent


void CallClearedEventInfo::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    clearedCall = new(memBlock) ConnectionID(memBlock);
    clearedCall->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0311: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, PRIM, 14)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    localConnectionInfo = new(memBlock) LocalConnectionState(memBlock);
    localConnectionInfo->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, ENUM_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    cause = new(memBlock) EventCause(memBlock);
    cause->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0312: Length discrepancy on sequence.";
  }
  else
    return;
} // CallClearedEventInfo::BDecContent

AsnLen CallClearedEventInfo::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void CallClearedEventInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135067928: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int CallClearedEventInfo::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int CallClearedEventInfo::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void CallClearedEventInfo::Print ( CTsvcLIB::LOG& os ) const
{
  os << "CallClearedEventInfo SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "clearedCall : ";
  if (NOT_NULL (clearedCall))
    os << *clearedCall;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "localConnectionInfo : ";
  if (NOT_NULL (localConnectionInfo))
    os << *localConnectionInfo;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "cause : ";
  if (NOT_NULL (cause))
    os << *cause;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // CallClearedEventInfo::Print


ConferencedEventInfo::ConferencedEventInfo( MemBlock* mb ) : AsnType( mb )
{
  primaryOldCall = NULL; // incomplete initialization of mandatory element!
  secondaryOldCall = NULL;
  confController = NULL; // incomplete initialization of mandatory element!
  addedParty = NULL; // incomplete initialization of mandatory element!
  conferenceConnections = NULL;
  localConnectionInfo = NULL;
  cause = NULL;
}

ConferencedEventInfo::ConferencedEventInfo( MemBlock* mb, const ConferencedEventInfo & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined ConferencedEventInfo::ConferencedEventInfo (const ConferencedEventInfo &)";
  abort();
}

ConferencedEventInfo::~ConferencedEventInfo()
{
}

AsnType *ConferencedEventInfo::Clone() const
{
  return new(memBlock) ConferencedEventInfo(memBlock);
}

ConferencedEventInfo &ConferencedEventInfo::operator = (const ConferencedEventInfo &that)
{
  if (this != &that)
  {
    if (that.primaryOldCall)
    {
      if (!primaryOldCall)
        primaryOldCall = new(memBlock) ConnectionID(memBlock);
      *primaryOldCall = *that.primaryOldCall;
    }
    else
    {
      primaryOldCall = NULL;
    }
    if (that.secondaryOldCall)
    {
      if (!secondaryOldCall)
        secondaryOldCall = new(memBlock) ConnectionID(memBlock);
      *secondaryOldCall = *that.secondaryOldCall;
    }
    else
    {
      secondaryOldCall = NULL;
    }
    if (that.confController)
    {
      if (!confController)
        confController = new(memBlock) SubjectDeviceID(memBlock);
      *confController = *that.confController;
    }
    else
    {
      confController = NULL;
    }
    if (that.addedParty)
    {
      if (!addedParty)
        addedParty = new(memBlock) SubjectDeviceID(memBlock);
      *addedParty = *that.addedParty;
    }
    else
    {
      addedParty = NULL;
    }
    if (that.conferenceConnections)
    {
      if (!conferenceConnections)
        conferenceConnections = new(memBlock) ConnectionList(memBlock);
      *conferenceConnections = *that.conferenceConnections;
    }
    else
    {
      conferenceConnections = NULL;
    }
    if (that.localConnectionInfo)
    {
      if (!localConnectionInfo)
        localConnectionInfo = new(memBlock) LocalConnectionState(memBlock);
      *localConnectionInfo = *that.localConnectionInfo;
    }
    else
    {
      localConnectionInfo = NULL;
    }
    if (that.cause)
    {
      if (!cause)
        cause = new(memBlock) EventCause(memBlock);
      *cause = *that.cause;
    }
    else
    {
      cause = NULL;
    }
  }

  return *this;
}

AsnLen
ConferencedEventInfo::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (cause))
  {
    l = cause->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, ENUM_TAG_CODE);
    totalLen += l;
  }

  if (NOT_NULL (localConnectionInfo))
  {
    l = localConnectionInfo->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, APPL, PRIM, 14);
    totalLen += l;
  }

  if (NOT_NULL (conferenceConnections))
  {
    l = conferenceConnections->BEncContent (b);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = addedParty->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 3);
    totalLen += l;

      BEncEocIfNec (b);
    l = confController->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 3);
    totalLen += l;

  if (NOT_NULL (secondaryOldCall))
  {
      BEncEocIfNec (b);
    l = secondaryOldCall->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = primaryOldCall->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;

  return totalLen;
} // ConferencedEventInfo::BEncContent


void ConferencedEventInfo::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  AsnLen elmtLen2;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    primaryOldCall = new(memBlock) ConnectionID(memBlock);
    primaryOldCall->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0313: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    secondaryOldCall = new(memBlock) ConnectionID(memBlock);
    secondaryOldCall->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 3)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    confController = new(memBlock) SubjectDeviceID(memBlock);
    confController->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0314: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 3)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    addedParty = new(memBlock) SubjectDeviceID(memBlock);
    addedParty->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0315: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 12))
    || (tag1 == MAKE_TAG_ID (APPL, CONS, 13)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    conferenceConnections = new(memBlock) ConnectionList(memBlock);
    conferenceConnections->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (APPL, PRIM, 14)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    localConnectionInfo = new(memBlock) LocalConnectionState(memBlock);
    localConnectionInfo->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, ENUM_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    cause = new(memBlock) EventCause(memBlock);
    cause->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0316: Length discrepancy on sequence.";
  }
  else
    return;
} // ConferencedEventInfo::BDecContent

AsnLen ConferencedEventInfo::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void ConferencedEventInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135068024: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int ConferencedEventInfo::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ConferencedEventInfo::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ConferencedEventInfo::Print ( CTsvcLIB::LOG& os ) const
{
  os << "ConferencedEventInfo SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "primaryOldCall : ";
  if (NOT_NULL (primaryOldCall))
    os << *primaryOldCall;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "secondaryOldCall : ";
  if (NOT_NULL (secondaryOldCall))
    os << *secondaryOldCall;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "confController : ";
  if (NOT_NULL (confController))
    os << *confController;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "addedParty : ";
  if (NOT_NULL (addedParty))
    os << *addedParty;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "conferenceConnections : ";
  if (NOT_NULL (conferenceConnections))
    os << *conferenceConnections;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "localConnectionInfo : ";
  if (NOT_NULL (localConnectionInfo))
    os << *localConnectionInfo;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "cause : ";
  if (NOT_NULL (cause))
    os << *cause;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // ConferencedEventInfo::Print


ConnectionClearedEventInfo::ConnectionClearedEventInfo( MemBlock* mb ) : AsnType( mb )
{
  droppedConnection = NULL; // incomplete initialization of mandatory element!
  releasingDevice = NULL; // incomplete initialization of mandatory element!
  localConnectionInfo = NULL;
  cause = NULL;
}

ConnectionClearedEventInfo::ConnectionClearedEventInfo( MemBlock* mb, const ConnectionClearedEventInfo & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined ConnectionClearedEventInfo::ConnectionClearedEventInfo (const ConnectionClearedEventInfo &)";
  abort();
}

ConnectionClearedEventInfo::~ConnectionClearedEventInfo()
{
}

AsnType *ConnectionClearedEventInfo::Clone() const
{
  return new(memBlock) ConnectionClearedEventInfo(memBlock);
}

ConnectionClearedEventInfo &ConnectionClearedEventInfo::operator = (const ConnectionClearedEventInfo &that)
{
  if (this != &that)
  {
    if (that.droppedConnection)
    {
      if (!droppedConnection)
        droppedConnection = new(memBlock) ConnectionID(memBlock);
      *droppedConnection = *that.droppedConnection;
    }
    else
    {
      droppedConnection = NULL;
    }
    if (that.releasingDevice)
    {
      if (!releasingDevice)
        releasingDevice = new(memBlock) SubjectDeviceID(memBlock);
      *releasingDevice = *that.releasingDevice;
    }
    else
    {
      releasingDevice = NULL;
    }
    if (that.localConnectionInfo)
    {
      if (!localConnectionInfo)
        localConnectionInfo = new(memBlock) LocalConnectionState(memBlock);
      *localConnectionInfo = *that.localConnectionInfo;
    }
    else
    {
      localConnectionInfo = NULL;
    }
    if (that.cause)
    {
      if (!cause)
        cause = new(memBlock) EventCause(memBlock);
      *cause = *that.cause;
    }
    else
    {
      cause = NULL;
    }
  }

  return *this;
}

AsnLen
ConnectionClearedEventInfo::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (cause))
  {
    l = cause->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, ENUM_TAG_CODE);
    totalLen += l;
  }

  if (NOT_NULL (localConnectionInfo))
  {
    l = localConnectionInfo->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, APPL, PRIM, 14);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = releasingDevice->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 3);
    totalLen += l;

      BEncEocIfNec (b);
    l = droppedConnection->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;

  return totalLen;
} // ConnectionClearedEventInfo::BEncContent


void ConnectionClearedEventInfo::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  AsnLen elmtLen2;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    droppedConnection = new(memBlock) ConnectionID(memBlock);
    droppedConnection->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0317: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 3)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    releasingDevice = new(memBlock) SubjectDeviceID(memBlock);
    releasingDevice->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0318: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, PRIM, 14)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    localConnectionInfo = new(memBlock) LocalConnectionState(memBlock);
    localConnectionInfo->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, ENUM_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    cause = new(memBlock) EventCause(memBlock);
    cause->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0319: Length discrepancy on sequence.";
  }
  else
    return;
} // ConnectionClearedEventInfo::BDecContent

AsnLen ConnectionClearedEventInfo::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void ConnectionClearedEventInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135068088: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int ConnectionClearedEventInfo::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ConnectionClearedEventInfo::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ConnectionClearedEventInfo::Print ( CTsvcLIB::LOG& os ) const
{
  os << "ConnectionClearedEventInfo SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "droppedConnection : ";
  if (NOT_NULL (droppedConnection))
    os << *droppedConnection;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "releasingDevice : ";
  if (NOT_NULL (releasingDevice))
    os << *releasingDevice;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "localConnectionInfo : ";
  if (NOT_NULL (localConnectionInfo))
    os << *localConnectionInfo;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "cause : ";
  if (NOT_NULL (cause))
    os << *cause;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // ConnectionClearedEventInfo::Print


DeliveredEventInfo::DeliveredEventInfo( MemBlock* mb ) : AsnType( mb )
{
  connection = NULL; // incomplete initialization of mandatory element!
  alertingDevice = NULL; // incomplete initialization of mandatory element!
  callingDevice = NULL; // incomplete initialization of mandatory element!
  calledDevice = NULL; // incomplete initialization of mandatory element!
  lastRedirectionDevice = NULL; // incomplete initialization of mandatory element!
  localConnectionInfo = NULL;
  cause = NULL;
}

DeliveredEventInfo::DeliveredEventInfo( MemBlock* mb, const DeliveredEventInfo & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined DeliveredEventInfo::DeliveredEventInfo (const DeliveredEventInfo &)";
  abort();
}

DeliveredEventInfo::~DeliveredEventInfo()
{
}

AsnType *DeliveredEventInfo::Clone() const
{
  return new(memBlock) DeliveredEventInfo(memBlock);
}

DeliveredEventInfo &DeliveredEventInfo::operator = (const DeliveredEventInfo &that)
{
  if (this != &that)
  {
    if (that.connection)
    {
      if (!connection)
        connection = new(memBlock) ConnectionID(memBlock);
      *connection = *that.connection;
    }
    else
    {
      connection = NULL;
    }
    if (that.alertingDevice)
    {
      if (!alertingDevice)
        alertingDevice = new(memBlock) SubjectDeviceID(memBlock);
      *alertingDevice = *that.alertingDevice;
    }
    else
    {
      alertingDevice = NULL;
    }
    if (that.callingDevice)
    {
      if (!callingDevice)
        callingDevice = new(memBlock) CallingDeviceID(memBlock);
      *callingDevice = *that.callingDevice;
    }
    else
    {
      callingDevice = NULL;
    }
    if (that.calledDevice)
    {
      if (!calledDevice)
        calledDevice = new(memBlock) CalledDeviceID(memBlock);
      *calledDevice = *that.calledDevice;
    }
    else
    {
      calledDevice = NULL;
    }
    if (that.lastRedirectionDevice)
    {
      if (!lastRedirectionDevice)
        lastRedirectionDevice = new(memBlock) RedirectionDeviceID(memBlock);
      *lastRedirectionDevice = *that.lastRedirectionDevice;
    }
    else
    {
      lastRedirectionDevice = NULL;
    }
    if (that.localConnectionInfo)
    {
      if (!localConnectionInfo)
        localConnectionInfo = new(memBlock) LocalConnectionState(memBlock);
      *localConnectionInfo = *that.localConnectionInfo;
    }
    else
    {
      localConnectionInfo = NULL;
    }
    if (that.cause)
    {
      if (!cause)
        cause = new(memBlock) EventCause(memBlock);
      *cause = *that.cause;
    }
    else
    {
      cause = NULL;
    }
  }

  return *this;
}

AsnLen
DeliveredEventInfo::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (cause))
  {
    l = cause->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, ENUM_TAG_CODE);
    totalLen += l;
  }

  if (NOT_NULL (localConnectionInfo))
  {
    l = localConnectionInfo->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, APPL, PRIM, 14);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = lastRedirectionDevice->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 4);
    totalLen += l;

      BEncEocIfNec (b);
    l = calledDevice->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 2);
    totalLen += l;

      BEncEocIfNec (b);
    l = callingDevice->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 1);
    totalLen += l;

      BEncEocIfNec (b);
    l = alertingDevice->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 3);
    totalLen += l;

      BEncEocIfNec (b);
    l = connection->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;

  return totalLen;
} // DeliveredEventInfo::BEncContent


void DeliveredEventInfo::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  AsnLen elmtLen2;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    connection = new(memBlock) ConnectionID(memBlock);
    connection->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0320: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 3)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    alertingDevice = new(memBlock) SubjectDeviceID(memBlock);
    alertingDevice->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0321: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 1)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    callingDevice = new(memBlock) CallingDeviceID(memBlock);
    callingDevice->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0322: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 2)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    calledDevice = new(memBlock) CalledDeviceID(memBlock);
    calledDevice->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0323: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 4)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    lastRedirectionDevice = new(memBlock) RedirectionDeviceID(memBlock);
    lastRedirectionDevice->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0324: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, PRIM, 14)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    localConnectionInfo = new(memBlock) LocalConnectionState(memBlock);
    localConnectionInfo->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, ENUM_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    cause = new(memBlock) EventCause(memBlock);
    cause->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0325: Length discrepancy on sequence.";
  }
  else
    return;
} // DeliveredEventInfo::BDecContent

AsnLen DeliveredEventInfo::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void DeliveredEventInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135068184: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int DeliveredEventInfo::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int DeliveredEventInfo::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void DeliveredEventInfo::Print ( CTsvcLIB::LOG& os ) const
{
  os << "DeliveredEventInfo SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "connection : ";
  if (NOT_NULL (connection))
    os << *connection;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "alertingDevice : ";
  if (NOT_NULL (alertingDevice))
    os << *alertingDevice;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "callingDevice : ";
  if (NOT_NULL (callingDevice))
    os << *callingDevice;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "calledDevice : ";
  if (NOT_NULL (calledDevice))
    os << *calledDevice;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "lastRedirectionDevice : ";
  if (NOT_NULL (lastRedirectionDevice))
    os << *lastRedirectionDevice;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "localConnectionInfo : ";
  if (NOT_NULL (localConnectionInfo))
    os << *localConnectionInfo;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "cause : ";
  if (NOT_NULL (cause))
    os << *cause;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // DeliveredEventInfo::Print


DivertedEventInfo::DivertedEventInfo( MemBlock* mb ) : AsnType( mb )
{
  connection = NULL;
  divertingDevice = NULL; // incomplete initialization of mandatory element!
  newDestination = NULL; // incomplete initialization of mandatory element!
  localConnectionInfo = NULL;
  cause = NULL;
}

DivertedEventInfo::DivertedEventInfo( MemBlock* mb, const DivertedEventInfo & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined DivertedEventInfo::DivertedEventInfo (const DivertedEventInfo &)";
  abort();
}

DivertedEventInfo::~DivertedEventInfo()
{
}

AsnType *DivertedEventInfo::Clone() const
{
  return new(memBlock) DivertedEventInfo(memBlock);
}

DivertedEventInfo &DivertedEventInfo::operator = (const DivertedEventInfo &that)
{
  if (this != &that)
  {
    if (that.connection)
    {
      if (!connection)
        connection = new(memBlock) ConnectionID(memBlock);
      *connection = *that.connection;
    }
    else
    {
      connection = NULL;
    }
    if (that.divertingDevice)
    {
      if (!divertingDevice)
        divertingDevice = new(memBlock) SubjectDeviceID(memBlock);
      *divertingDevice = *that.divertingDevice;
    }
    else
    {
      divertingDevice = NULL;
    }
    if (that.newDestination)
    {
      if (!newDestination)
        newDestination = new(memBlock) CalledDeviceID(memBlock);
      *newDestination = *that.newDestination;
    }
    else
    {
      newDestination = NULL;
    }
    if (that.localConnectionInfo)
    {
      if (!localConnectionInfo)
        localConnectionInfo = new(memBlock) LocalConnectionState(memBlock);
      *localConnectionInfo = *that.localConnectionInfo;
    }
    else
    {
      localConnectionInfo = NULL;
    }
    if (that.cause)
    {
      if (!cause)
        cause = new(memBlock) EventCause(memBlock);
      *cause = *that.cause;
    }
    else
    {
      cause = NULL;
    }
  }

  return *this;
}

AsnLen
DivertedEventInfo::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (cause))
  {
    l = cause->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, ENUM_TAG_CODE);
    totalLen += l;
  }

  if (NOT_NULL (localConnectionInfo))
  {
    l = localConnectionInfo->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, APPL, PRIM, 14);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = newDestination->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 2);
    totalLen += l;

      BEncEocIfNec (b);
    l = divertingDevice->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 3);
    totalLen += l;

  if (NOT_NULL (connection))
  {
      BEncEocIfNec (b);
    l = connection->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;
  }

  return totalLen;
} // DivertedEventInfo::BEncContent


void DivertedEventInfo::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  AsnLen elmtLen2;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    connection = new(memBlock) ConnectionID(memBlock);
    connection->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 3)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    divertingDevice = new(memBlock) SubjectDeviceID(memBlock);
    divertingDevice->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0326: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 2)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    newDestination = new(memBlock) CalledDeviceID(memBlock);
    newDestination->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0327: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, PRIM, 14)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    localConnectionInfo = new(memBlock) LocalConnectionState(memBlock);
    localConnectionInfo->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, ENUM_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    cause = new(memBlock) EventCause(memBlock);
    cause->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0328: Length discrepancy on sequence.";
  }
  else
    return;
} // DivertedEventInfo::BDecContent

AsnLen DivertedEventInfo::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void DivertedEventInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135068248: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int DivertedEventInfo::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int DivertedEventInfo::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void DivertedEventInfo::Print ( CTsvcLIB::LOG& os ) const
{
  os << "DivertedEventInfo SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "connection : ";
  if (NOT_NULL (connection))
    os << *connection;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "divertingDevice : ";
  if (NOT_NULL (divertingDevice))
    os << *divertingDevice;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "newDestination : ";
  if (NOT_NULL (newDestination))
    os << *newDestination;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "localConnectionInfo : ";
  if (NOT_NULL (localConnectionInfo))
    os << *localConnectionInfo;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "cause : ";
  if (NOT_NULL (cause))
    os << *cause;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // DivertedEventInfo::Print


EstablishedEventInfo::EstablishedEventInfo( MemBlock* mb ) : AsnType( mb )
{
  establishedConnection = NULL; // incomplete initialization of mandatory element!
  answeringDevice = NULL; // incomplete initialization of mandatory element!
  callingDevice = NULL; // incomplete initialization of mandatory element!
  calledDevice = NULL; // incomplete initialization of mandatory element!
  lastRedirectionDevice = NULL; // incomplete initialization of mandatory element!
  localConnectionInfo = NULL;
  cause = NULL;
}

EstablishedEventInfo::EstablishedEventInfo( MemBlock* mb, const EstablishedEventInfo & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined EstablishedEventInfo::EstablishedEventInfo (const EstablishedEventInfo &)";
  abort();
}

EstablishedEventInfo::~EstablishedEventInfo()
{
}

AsnType *EstablishedEventInfo::Clone() const
{
  return new(memBlock) EstablishedEventInfo(memBlock);
}

EstablishedEventInfo &EstablishedEventInfo::operator = (const EstablishedEventInfo &that)
{
  if (this != &that)
  {
    if (that.establishedConnection)
    {
      if (!establishedConnection)
        establishedConnection = new(memBlock) ConnectionID(memBlock);
      *establishedConnection = *that.establishedConnection;
    }
    else
    {
      establishedConnection = NULL;
    }
    if (that.answeringDevice)
    {
      if (!answeringDevice)
        answeringDevice = new(memBlock) SubjectDeviceID(memBlock);
      *answeringDevice = *that.answeringDevice;
    }
    else
    {
      answeringDevice = NULL;
    }
    if (that.callingDevice)
    {
      if (!callingDevice)
        callingDevice = new(memBlock) CallingDeviceID(memBlock);
      *callingDevice = *that.callingDevice;
    }
    else
    {
      callingDevice = NULL;
    }
    if (that.calledDevice)
    {
      if (!calledDevice)
        calledDevice = new(memBlock) CalledDeviceID(memBlock);
      *calledDevice = *that.calledDevice;
    }
    else
    {
      calledDevice = NULL;
    }
    if (that.lastRedirectionDevice)
    {
      if (!lastRedirectionDevice)
        lastRedirectionDevice = new(memBlock) RedirectionDeviceID(memBlock);
      *lastRedirectionDevice = *that.lastRedirectionDevice;
    }
    else
    {
      lastRedirectionDevice = NULL;
    }
    if (that.localConnectionInfo)
    {
      if (!localConnectionInfo)
        localConnectionInfo = new(memBlock) LocalConnectionState(memBlock);
      *localConnectionInfo = *that.localConnectionInfo;
    }
    else
    {
      localConnectionInfo = NULL;
    }
    if (that.cause)
    {
      if (!cause)
        cause = new(memBlock) EventCause(memBlock);
      *cause = *that.cause;
    }
    else
    {
      cause = NULL;
    }
  }

  return *this;
}

AsnLen
EstablishedEventInfo::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (cause))
  {
    l = cause->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, ENUM_TAG_CODE);
    totalLen += l;
  }

  if (NOT_NULL (localConnectionInfo))
  {
    l = localConnectionInfo->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, APPL, PRIM, 14);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = lastRedirectionDevice->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 4);
    totalLen += l;

      BEncEocIfNec (b);
    l = calledDevice->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 2);
    totalLen += l;

      BEncEocIfNec (b);
    l = callingDevice->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 1);
    totalLen += l;

      BEncEocIfNec (b);
    l = answeringDevice->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 3);
    totalLen += l;

      BEncEocIfNec (b);
    l = establishedConnection->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;

  return totalLen;
} // EstablishedEventInfo::BEncContent


void EstablishedEventInfo::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  AsnLen elmtLen2;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    establishedConnection = new(memBlock) ConnectionID(memBlock);
    establishedConnection->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0329: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 3)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    answeringDevice = new(memBlock) SubjectDeviceID(memBlock);
    answeringDevice->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0330: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 1)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    callingDevice = new(memBlock) CallingDeviceID(memBlock);
    callingDevice->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0331: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 2)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    calledDevice = new(memBlock) CalledDeviceID(memBlock);
    calledDevice->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0332: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 4)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    lastRedirectionDevice = new(memBlock) RedirectionDeviceID(memBlock);
    lastRedirectionDevice->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0333: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, PRIM, 14)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    localConnectionInfo = new(memBlock) LocalConnectionState(memBlock);
    localConnectionInfo->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, ENUM_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    cause = new(memBlock) EventCause(memBlock);
    cause->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0334: Length discrepancy on sequence.";
  }
  else
    return;
} // EstablishedEventInfo::BDecContent

AsnLen EstablishedEventInfo::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void EstablishedEventInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135068344: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int EstablishedEventInfo::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int EstablishedEventInfo::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void EstablishedEventInfo::Print ( CTsvcLIB::LOG& os ) const
{
  os << "EstablishedEventInfo SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "establishedConnection : ";
  if (NOT_NULL (establishedConnection))
    os << *establishedConnection;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "answeringDevice : ";
  if (NOT_NULL (answeringDevice))
    os << *answeringDevice;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "callingDevice : ";
  if (NOT_NULL (callingDevice))
    os << *callingDevice;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "calledDevice : ";
  if (NOT_NULL (calledDevice))
    os << *calledDevice;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "lastRedirectionDevice : ";
  if (NOT_NULL (lastRedirectionDevice))
    os << *lastRedirectionDevice;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "localConnectionInfo : ";
  if (NOT_NULL (localConnectionInfo))
    os << *localConnectionInfo;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "cause : ";
  if (NOT_NULL (cause))
    os << *cause;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // EstablishedEventInfo::Print


FailedEventInfo::FailedEventInfo( MemBlock* mb ) : AsnType( mb )
{
  failedConnection = NULL; // incomplete initialization of mandatory element!
  failingDevice = NULL; // incomplete initialization of mandatory element!
  calledDevice = NULL; // incomplete initialization of mandatory element!
  localConnectionInfo = NULL;
  cause = NULL;
}

FailedEventInfo::FailedEventInfo( MemBlock* mb, const FailedEventInfo & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined FailedEventInfo::FailedEventInfo (const FailedEventInfo &)";
  abort();
}

FailedEventInfo::~FailedEventInfo()
{
}

AsnType *FailedEventInfo::Clone() const
{
  return new(memBlock) FailedEventInfo(memBlock);
}

FailedEventInfo &FailedEventInfo::operator = (const FailedEventInfo &that)
{
  if (this != &that)
  {
    if (that.failedConnection)
    {
      if (!failedConnection)
        failedConnection = new(memBlock) ConnectionID(memBlock);
      *failedConnection = *that.failedConnection;
    }
    else
    {
      failedConnection = NULL;
    }
    if (that.failingDevice)
    {
      if (!failingDevice)
        failingDevice = new(memBlock) SubjectDeviceID(memBlock);
      *failingDevice = *that.failingDevice;
    }
    else
    {
      failingDevice = NULL;
    }
    if (that.calledDevice)
    {
      if (!calledDevice)
        calledDevice = new(memBlock) CalledDeviceID(memBlock);
      *calledDevice = *that.calledDevice;
    }
    else
    {
      calledDevice = NULL;
    }
    if (that.localConnectionInfo)
    {
      if (!localConnectionInfo)
        localConnectionInfo = new(memBlock) LocalConnectionState(memBlock);
      *localConnectionInfo = *that.localConnectionInfo;
    }
    else
    {
      localConnectionInfo = NULL;
    }
    if (that.cause)
    {
      if (!cause)
        cause = new(memBlock) EventCause(memBlock);
      *cause = *that.cause;
    }
    else
    {
      cause = NULL;
    }
  }

  return *this;
}

AsnLen
FailedEventInfo::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (cause))
  {
    l = cause->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, ENUM_TAG_CODE);
    totalLen += l;
  }

  if (NOT_NULL (localConnectionInfo))
  {
    l = localConnectionInfo->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, APPL, PRIM, 14);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = calledDevice->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 2);
    totalLen += l;

      BEncEocIfNec (b);
    l = failingDevice->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 3);
    totalLen += l;

      BEncEocIfNec (b);
    l = failedConnection->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;

  return totalLen;
} // FailedEventInfo::BEncContent


void FailedEventInfo::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  AsnLen elmtLen2;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    failedConnection = new(memBlock) ConnectionID(memBlock);
    failedConnection->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0335: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 3)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    failingDevice = new(memBlock) SubjectDeviceID(memBlock);
    failingDevice->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0336: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 2)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    calledDevice = new(memBlock) CalledDeviceID(memBlock);
    calledDevice->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0337: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, PRIM, 14)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    localConnectionInfo = new(memBlock) LocalConnectionState(memBlock);
    localConnectionInfo->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, ENUM_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    cause = new(memBlock) EventCause(memBlock);
    cause->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0338: Length discrepancy on sequence.";
  }
  else
    return;
} // FailedEventInfo::BDecContent

AsnLen FailedEventInfo::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void FailedEventInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135068432: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int FailedEventInfo::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int FailedEventInfo::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void FailedEventInfo::Print ( CTsvcLIB::LOG& os ) const
{
  os << "FailedEventInfo SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "failedConnection : ";
  if (NOT_NULL (failedConnection))
    os << *failedConnection;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "failingDevice : ";
  if (NOT_NULL (failingDevice))
    os << *failingDevice;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "calledDevice : ";
  if (NOT_NULL (calledDevice))
    os << *calledDevice;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "localConnectionInfo : ";
  if (NOT_NULL (localConnectionInfo))
    os << *localConnectionInfo;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "cause : ";
  if (NOT_NULL (cause))
    os << *cause;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // FailedEventInfo::Print


HeldEventInfo::HeldEventInfo( MemBlock* mb ) : AsnType( mb )
{
  heldConnection = NULL; // incomplete initialization of mandatory element!
  holdingDevice = NULL; // incomplete initialization of mandatory element!
  localConnectionInfo = NULL;
  cause = NULL;
}

HeldEventInfo::HeldEventInfo( MemBlock* mb, const HeldEventInfo & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined HeldEventInfo::HeldEventInfo (const HeldEventInfo &)";
  abort();
}

HeldEventInfo::~HeldEventInfo()
{
}

AsnType *HeldEventInfo::Clone() const
{
  return new(memBlock) HeldEventInfo(memBlock);
}

HeldEventInfo &HeldEventInfo::operator = (const HeldEventInfo &that)
{
  if (this != &that)
  {
    if (that.heldConnection)
    {
      if (!heldConnection)
        heldConnection = new(memBlock) ConnectionID(memBlock);
      *heldConnection = *that.heldConnection;
    }
    else
    {
      heldConnection = NULL;
    }
    if (that.holdingDevice)
    {
      if (!holdingDevice)
        holdingDevice = new(memBlock) SubjectDeviceID(memBlock);
      *holdingDevice = *that.holdingDevice;
    }
    else
    {
      holdingDevice = NULL;
    }
    if (that.localConnectionInfo)
    {
      if (!localConnectionInfo)
        localConnectionInfo = new(memBlock) LocalConnectionState(memBlock);
      *localConnectionInfo = *that.localConnectionInfo;
    }
    else
    {
      localConnectionInfo = NULL;
    }
    if (that.cause)
    {
      if (!cause)
        cause = new(memBlock) EventCause(memBlock);
      *cause = *that.cause;
    }
    else
    {
      cause = NULL;
    }
  }

  return *this;
}

AsnLen
HeldEventInfo::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (cause))
  {
    l = cause->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, ENUM_TAG_CODE);
    totalLen += l;
  }

  if (NOT_NULL (localConnectionInfo))
  {
    l = localConnectionInfo->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, APPL, PRIM, 14);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = holdingDevice->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 3);
    totalLen += l;

      BEncEocIfNec (b);
    l = heldConnection->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;

  return totalLen;
} // HeldEventInfo::BEncContent


void HeldEventInfo::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  AsnLen elmtLen2;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    heldConnection = new(memBlock) ConnectionID(memBlock);
    heldConnection->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0339: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 3)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    holdingDevice = new(memBlock) SubjectDeviceID(memBlock);
    holdingDevice->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0340: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, PRIM, 14)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    localConnectionInfo = new(memBlock) LocalConnectionState(memBlock);
    localConnectionInfo->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, ENUM_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    cause = new(memBlock) EventCause(memBlock);
    cause->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0341: Length discrepancy on sequence.";
  }
  else
    return;
} // HeldEventInfo::BDecContent

AsnLen HeldEventInfo::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void HeldEventInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135068488: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int HeldEventInfo::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int HeldEventInfo::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void HeldEventInfo::Print ( CTsvcLIB::LOG& os ) const
{
  os << "HeldEventInfo SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "heldConnection : ";
  if (NOT_NULL (heldConnection))
    os << *heldConnection;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "holdingDevice : ";
  if (NOT_NULL (holdingDevice))
    os << *holdingDevice;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "localConnectionInfo : ";
  if (NOT_NULL (localConnectionInfo))
    os << *localConnectionInfo;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "cause : ";
  if (NOT_NULL (cause))
    os << *cause;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // HeldEventInfo::Print


NetworkReachedEventInfo::NetworkReachedEventInfo( MemBlock* mb ) : AsnType( mb )
{
  connection = NULL; // incomplete initialization of mandatory element!
  trunkUsed = NULL; // incomplete initialization of mandatory element!
  calledDevice = NULL; // incomplete initialization of mandatory element!
  localConnectionInfo = NULL;
  cause = NULL;
}

NetworkReachedEventInfo::NetworkReachedEventInfo( MemBlock* mb, const NetworkReachedEventInfo & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined NetworkReachedEventInfo::NetworkReachedEventInfo (const NetworkReachedEventInfo &)";
  abort();
}

NetworkReachedEventInfo::~NetworkReachedEventInfo()
{
}

AsnType *NetworkReachedEventInfo::Clone() const
{
  return new(memBlock) NetworkReachedEventInfo(memBlock);
}

NetworkReachedEventInfo &NetworkReachedEventInfo::operator = (const NetworkReachedEventInfo &that)
{
  if (this != &that)
  {
    if (that.connection)
    {
      if (!connection)
        connection = new(memBlock) ConnectionID(memBlock);
      *connection = *that.connection;
    }
    else
    {
      connection = NULL;
    }
    if (that.trunkUsed)
    {
      if (!trunkUsed)
        trunkUsed = new(memBlock) SubjectDeviceID(memBlock);
      *trunkUsed = *that.trunkUsed;
    }
    else
    {
      trunkUsed = NULL;
    }
    if (that.calledDevice)
    {
      if (!calledDevice)
        calledDevice = new(memBlock) CalledDeviceID(memBlock);
      *calledDevice = *that.calledDevice;
    }
    else
    {
      calledDevice = NULL;
    }
    if (that.localConnectionInfo)
    {
      if (!localConnectionInfo)
        localConnectionInfo = new(memBlock) LocalConnectionState(memBlock);
      *localConnectionInfo = *that.localConnectionInfo;
    }
    else
    {
      localConnectionInfo = NULL;
    }
    if (that.cause)
    {
      if (!cause)
        cause = new(memBlock) EventCause(memBlock);
      *cause = *that.cause;
    }
    else
    {
      cause = NULL;
    }
  }

  return *this;
}

AsnLen
NetworkReachedEventInfo::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (cause))
  {
    l = cause->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, ENUM_TAG_CODE);
    totalLen += l;
  }

  if (NOT_NULL (localConnectionInfo))
  {
    l = localConnectionInfo->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, APPL, PRIM, 14);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = calledDevice->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 2);
    totalLen += l;

      BEncEocIfNec (b);
    l = trunkUsed->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 3);
    totalLen += l;

      BEncEocIfNec (b);
    l = connection->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;

  return totalLen;
} // NetworkReachedEventInfo::BEncContent


void NetworkReachedEventInfo::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  AsnLen elmtLen2;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    connection = new(memBlock) ConnectionID(memBlock);
    connection->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0342: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 3)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    trunkUsed = new(memBlock) SubjectDeviceID(memBlock);
    trunkUsed->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0343: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 2)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    calledDevice = new(memBlock) CalledDeviceID(memBlock);
    calledDevice->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0344: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, PRIM, 14)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    localConnectionInfo = new(memBlock) LocalConnectionState(memBlock);
    localConnectionInfo->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, ENUM_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    cause = new(memBlock) EventCause(memBlock);
    cause->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0345: Length discrepancy on sequence.";
  }
  else
    return;
} // NetworkReachedEventInfo::BDecContent

AsnLen NetworkReachedEventInfo::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void NetworkReachedEventInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135068576: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int NetworkReachedEventInfo::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int NetworkReachedEventInfo::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void NetworkReachedEventInfo::Print ( CTsvcLIB::LOG& os ) const
{
  os << "NetworkReachedEventInfo SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "connection : ";
  if (NOT_NULL (connection))
    os << *connection;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "trunkUsed : ";
  if (NOT_NULL (trunkUsed))
    os << *trunkUsed;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "calledDevice : ";
  if (NOT_NULL (calledDevice))
    os << *calledDevice;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "localConnectionInfo : ";
  if (NOT_NULL (localConnectionInfo))
    os << *localConnectionInfo;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "cause : ";
  if (NOT_NULL (cause))
    os << *cause;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // NetworkReachedEventInfo::Print


OriginatedEventInfo::OriginatedEventInfo( MemBlock* mb ) : AsnType( mb )
{
  originatedConnection = NULL; // incomplete initialization of mandatory element!
  callingDevice = NULL; // incomplete initialization of mandatory element!
  calledDevice = NULL; // incomplete initialization of mandatory element!
  localConnectionInfo = NULL;
  cause = NULL;
}

OriginatedEventInfo::OriginatedEventInfo( MemBlock* mb, const OriginatedEventInfo & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined OriginatedEventInfo::OriginatedEventInfo (const OriginatedEventInfo &)";
  abort();
}

OriginatedEventInfo::~OriginatedEventInfo()
{
}

AsnType *OriginatedEventInfo::Clone() const
{
  return new(memBlock) OriginatedEventInfo(memBlock);
}

OriginatedEventInfo &OriginatedEventInfo::operator = (const OriginatedEventInfo &that)
{
  if (this != &that)
  {
    if (that.originatedConnection)
    {
      if (!originatedConnection)
        originatedConnection = new(memBlock) ConnectionID(memBlock);
      *originatedConnection = *that.originatedConnection;
    }
    else
    {
      originatedConnection = NULL;
    }
    if (that.callingDevice)
    {
      if (!callingDevice)
        callingDevice = new(memBlock) SubjectDeviceID(memBlock);
      *callingDevice = *that.callingDevice;
    }
    else
    {
      callingDevice = NULL;
    }
    if (that.calledDevice)
    {
      if (!calledDevice)
        calledDevice = new(memBlock) CalledDeviceID(memBlock);
      *calledDevice = *that.calledDevice;
    }
    else
    {
      calledDevice = NULL;
    }
    if (that.localConnectionInfo)
    {
      if (!localConnectionInfo)
        localConnectionInfo = new(memBlock) LocalConnectionState(memBlock);
      *localConnectionInfo = *that.localConnectionInfo;
    }
    else
    {
      localConnectionInfo = NULL;
    }
    if (that.cause)
    {
      if (!cause)
        cause = new(memBlock) EventCause(memBlock);
      *cause = *that.cause;
    }
    else
    {
      cause = NULL;
    }
  }

  return *this;
}

AsnLen
OriginatedEventInfo::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (cause))
  {
    l = cause->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, ENUM_TAG_CODE);
    totalLen += l;
  }

  if (NOT_NULL (localConnectionInfo))
  {
    l = localConnectionInfo->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, APPL, PRIM, 14);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = calledDevice->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 2);
    totalLen += l;

      BEncEocIfNec (b);
    l = callingDevice->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 3);
    totalLen += l;

      BEncEocIfNec (b);
    l = originatedConnection->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;

  return totalLen;
} // OriginatedEventInfo::BEncContent


void OriginatedEventInfo::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  AsnLen elmtLen2;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    originatedConnection = new(memBlock) ConnectionID(memBlock);
    originatedConnection->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0346: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 3)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    callingDevice = new(memBlock) SubjectDeviceID(memBlock);
    callingDevice->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0347: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 2)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    calledDevice = new(memBlock) CalledDeviceID(memBlock);
    calledDevice->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0348: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, PRIM, 14)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    localConnectionInfo = new(memBlock) LocalConnectionState(memBlock);
    localConnectionInfo->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, ENUM_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    cause = new(memBlock) EventCause(memBlock);
    cause->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0349: Length discrepancy on sequence.";
  }
  else
    return;
} // OriginatedEventInfo::BDecContent

AsnLen OriginatedEventInfo::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void OriginatedEventInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135068664: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int OriginatedEventInfo::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int OriginatedEventInfo::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void OriginatedEventInfo::Print ( CTsvcLIB::LOG& os ) const
{
  os << "OriginatedEventInfo SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "originatedConnection : ";
  if (NOT_NULL (originatedConnection))
    os << *originatedConnection;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "callingDevice : ";
  if (NOT_NULL (callingDevice))
    os << *callingDevice;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "calledDevice : ";
  if (NOT_NULL (calledDevice))
    os << *calledDevice;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "localConnectionInfo : ";
  if (NOT_NULL (localConnectionInfo))
    os << *localConnectionInfo;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "cause : ";
  if (NOT_NULL (cause))
    os << *cause;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // OriginatedEventInfo::Print


QueuedEventInfo::QueuedEventInfo( MemBlock* mb ) : AsnType( mb )
{
  queuedConnection = NULL; // incomplete initialization of mandatory element!
  queue = NULL; // incomplete initialization of mandatory element!
  callingDevice = NULL; // incomplete initialization of mandatory element!
  calledDevice = NULL; // incomplete initialization of mandatory element!
  lastRedirectionDevice = NULL; // incomplete initialization of mandatory element!
  numberedQueued = NULL;
  localConnectionInfo = NULL;
  cause = NULL;
}

QueuedEventInfo::QueuedEventInfo( MemBlock* mb, const QueuedEventInfo & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined QueuedEventInfo::QueuedEventInfo (const QueuedEventInfo &)";
  abort();
}

QueuedEventInfo::~QueuedEventInfo()
{
}

AsnType *QueuedEventInfo::Clone() const
{
  return new(memBlock) QueuedEventInfo(memBlock);
}

QueuedEventInfo &QueuedEventInfo::operator = (const QueuedEventInfo &that)
{
  if (this != &that)
  {
    if (that.queuedConnection)
    {
      if (!queuedConnection)
        queuedConnection = new(memBlock) ConnectionID(memBlock);
      *queuedConnection = *that.queuedConnection;
    }
    else
    {
      queuedConnection = NULL;
    }
    if (that.queue)
    {
      if (!queue)
        queue = new(memBlock) SubjectDeviceID(memBlock);
      *queue = *that.queue;
    }
    else
    {
      queue = NULL;
    }
    if (that.callingDevice)
    {
      if (!callingDevice)
        callingDevice = new(memBlock) CallingDeviceID(memBlock);
      *callingDevice = *that.callingDevice;
    }
    else
    {
      callingDevice = NULL;
    }
    if (that.calledDevice)
    {
      if (!calledDevice)
        calledDevice = new(memBlock) CalledDeviceID(memBlock);
      *calledDevice = *that.calledDevice;
    }
    else
    {
      calledDevice = NULL;
    }
    if (that.lastRedirectionDevice)
    {
      if (!lastRedirectionDevice)
        lastRedirectionDevice = new(memBlock) RedirectionDeviceID(memBlock);
      *lastRedirectionDevice = *that.lastRedirectionDevice;
    }
    else
    {
      lastRedirectionDevice = NULL;
    }
    if (that.numberedQueued)
    {
      if (!numberedQueued)
        numberedQueued = new(memBlock) NoOfCallsInQueue(memBlock);
      *numberedQueued = *that.numberedQueued;
    }
    else
    {
      numberedQueued = NULL;
    }
    if (that.localConnectionInfo)
    {
      if (!localConnectionInfo)
        localConnectionInfo = new(memBlock) LocalConnectionState(memBlock);
      *localConnectionInfo = *that.localConnectionInfo;
    }
    else
    {
      localConnectionInfo = NULL;
    }
    if (that.cause)
    {
      if (!cause)
        cause = new(memBlock) EventCause(memBlock);
      *cause = *that.cause;
    }
    else
    {
      cause = NULL;
    }
  }

  return *this;
}

AsnLen
QueuedEventInfo::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (cause))
  {
    l = cause->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, ENUM_TAG_CODE);
    totalLen += l;
  }

  if (NOT_NULL (localConnectionInfo))
  {
    l = localConnectionInfo->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, APPL, PRIM, 14);
    totalLen += l;
  }

  if (NOT_NULL (numberedQueued))
  {
    l = numberedQueued->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, INTEGER_TAG_CODE);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = lastRedirectionDevice->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 4);
    totalLen += l;

      BEncEocIfNec (b);
    l = calledDevice->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 2);
    totalLen += l;

      BEncEocIfNec (b);
    l = callingDevice->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 1);
    totalLen += l;

      BEncEocIfNec (b);
    l = queue->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 3);
    totalLen += l;

      BEncEocIfNec (b);
    l = queuedConnection->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;

  return totalLen;
} // QueuedEventInfo::BEncContent


void QueuedEventInfo::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  AsnLen elmtLen2;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    queuedConnection = new(memBlock) ConnectionID(memBlock);
    queuedConnection->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0350: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 3)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    queue = new(memBlock) SubjectDeviceID(memBlock);
    queue->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0351: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 1)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    callingDevice = new(memBlock) CallingDeviceID(memBlock);
    callingDevice->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0352: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 2)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    calledDevice = new(memBlock) CalledDeviceID(memBlock);
    calledDevice->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0353: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 4)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    lastRedirectionDevice = new(memBlock) RedirectionDeviceID(memBlock);
    lastRedirectionDevice->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0354: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, INTEGER_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    numberedQueued = new(memBlock) NoOfCallsInQueue(memBlock);
    numberedQueued->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (APPL, PRIM, 14)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    localConnectionInfo = new(memBlock) LocalConnectionState(memBlock);
    localConnectionInfo->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, ENUM_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    cause = new(memBlock) EventCause(memBlock);
    cause->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0355: Length discrepancy on sequence.";
  }
  else
    return;
} // QueuedEventInfo::BDecContent

AsnLen QueuedEventInfo::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void QueuedEventInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135068728: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int QueuedEventInfo::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int QueuedEventInfo::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void QueuedEventInfo::Print ( CTsvcLIB::LOG& os ) const
{
  os << "QueuedEventInfo SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "queuedConnection : ";
  if (NOT_NULL (queuedConnection))
    os << *queuedConnection;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "queue : ";
  if (NOT_NULL (queue))
    os << *queue;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "callingDevice : ";
  if (NOT_NULL (callingDevice))
    os << *callingDevice;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "calledDevice : ";
  if (NOT_NULL (calledDevice))
    os << *calledDevice;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "lastRedirectionDevice : ";
  if (NOT_NULL (lastRedirectionDevice))
    os << *lastRedirectionDevice;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "numberedQueued : ";
  if (NOT_NULL (numberedQueued))
    os << *numberedQueued;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "localConnectionInfo : ";
  if (NOT_NULL (localConnectionInfo))
    os << *localConnectionInfo;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "cause : ";
  if (NOT_NULL (cause))
    os << *cause;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // QueuedEventInfo::Print


RetrievedEventInfo::RetrievedEventInfo( MemBlock* mb ) : AsnType( mb )
{
  retrievedConnection = NULL; // incomplete initialization of mandatory element!
  retrievingDevice = NULL; // incomplete initialization of mandatory element!
  localConnectionInfo = NULL;
  cause = NULL;
}

RetrievedEventInfo::RetrievedEventInfo( MemBlock* mb, const RetrievedEventInfo & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined RetrievedEventInfo::RetrievedEventInfo (const RetrievedEventInfo &)";
  abort();
}

RetrievedEventInfo::~RetrievedEventInfo()
{
}

AsnType *RetrievedEventInfo::Clone() const
{
  return new(memBlock) RetrievedEventInfo(memBlock);
}

RetrievedEventInfo &RetrievedEventInfo::operator = (const RetrievedEventInfo &that)
{
  if (this != &that)
  {
    if (that.retrievedConnection)
    {
      if (!retrievedConnection)
        retrievedConnection = new(memBlock) ConnectionID(memBlock);
      *retrievedConnection = *that.retrievedConnection;
    }
    else
    {
      retrievedConnection = NULL;
    }
    if (that.retrievingDevice)
    {
      if (!retrievingDevice)
        retrievingDevice = new(memBlock) SubjectDeviceID(memBlock);
      *retrievingDevice = *that.retrievingDevice;
    }
    else
    {
      retrievingDevice = NULL;
    }
    if (that.localConnectionInfo)
    {
      if (!localConnectionInfo)
        localConnectionInfo = new(memBlock) LocalConnectionState(memBlock);
      *localConnectionInfo = *that.localConnectionInfo;
    }
    else
    {
      localConnectionInfo = NULL;
    }
    if (that.cause)
    {
      if (!cause)
        cause = new(memBlock) EventCause(memBlock);
      *cause = *that.cause;
    }
    else
    {
      cause = NULL;
    }
  }

  return *this;
}

AsnLen
RetrievedEventInfo::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (cause))
  {
    l = cause->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, ENUM_TAG_CODE);
    totalLen += l;
  }

  if (NOT_NULL (localConnectionInfo))
  {
    l = localConnectionInfo->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, APPL, PRIM, 14);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = retrievingDevice->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 3);
    totalLen += l;

      BEncEocIfNec (b);
    l = retrievedConnection->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;

  return totalLen;
} // RetrievedEventInfo::BEncContent


void RetrievedEventInfo::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  AsnLen elmtLen2;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    retrievedConnection = new(memBlock) ConnectionID(memBlock);
    retrievedConnection->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0356: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 3)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    retrievingDevice = new(memBlock) SubjectDeviceID(memBlock);
    retrievingDevice->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0357: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, PRIM, 14)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    localConnectionInfo = new(memBlock) LocalConnectionState(memBlock);
    localConnectionInfo->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, ENUM_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    cause = new(memBlock) EventCause(memBlock);
    cause->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0358: Length discrepancy on sequence.";
  }
  else
    return;
} // RetrievedEventInfo::BDecContent

AsnLen RetrievedEventInfo::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void RetrievedEventInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135068808: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int RetrievedEventInfo::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int RetrievedEventInfo::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void RetrievedEventInfo::Print ( CTsvcLIB::LOG& os ) const
{
  os << "RetrievedEventInfo SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "retrievedConnection : ";
  if (NOT_NULL (retrievedConnection))
    os << *retrievedConnection;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "retrievingDevice : ";
  if (NOT_NULL (retrievingDevice))
    os << *retrievingDevice;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "localConnectionInfo : ";
  if (NOT_NULL (localConnectionInfo))
    os << *localConnectionInfo;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "cause : ";
  if (NOT_NULL (cause))
    os << *cause;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // RetrievedEventInfo::Print


ServiceInitiatedEventInfo::ServiceInitiatedEventInfo( MemBlock* mb ) : AsnType( mb )
{
  initiatedConnection = NULL; // incomplete initialization of mandatory element!
  localConnectionInfo = NULL;
  cause = NULL;
}

ServiceInitiatedEventInfo::ServiceInitiatedEventInfo( MemBlock* mb, const ServiceInitiatedEventInfo & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined ServiceInitiatedEventInfo::ServiceInitiatedEventInfo (const ServiceInitiatedEventInfo &)";
  abort();
}

ServiceInitiatedEventInfo::~ServiceInitiatedEventInfo()
{
}

AsnType *ServiceInitiatedEventInfo::Clone() const
{
  return new(memBlock) ServiceInitiatedEventInfo(memBlock);
}

ServiceInitiatedEventInfo &ServiceInitiatedEventInfo::operator = (const ServiceInitiatedEventInfo &that)
{
  if (this != &that)
  {
    if (that.initiatedConnection)
    {
      if (!initiatedConnection)
        initiatedConnection = new(memBlock) ConnectionID(memBlock);
      *initiatedConnection = *that.initiatedConnection;
    }
    else
    {
      initiatedConnection = NULL;
    }
    if (that.localConnectionInfo)
    {
      if (!localConnectionInfo)
        localConnectionInfo = new(memBlock) LocalConnectionState(memBlock);
      *localConnectionInfo = *that.localConnectionInfo;
    }
    else
    {
      localConnectionInfo = NULL;
    }
    if (that.cause)
    {
      if (!cause)
        cause = new(memBlock) EventCause(memBlock);
      *cause = *that.cause;
    }
    else
    {
      cause = NULL;
    }
  }

  return *this;
}

AsnLen
ServiceInitiatedEventInfo::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (cause))
  {
    l = cause->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, ENUM_TAG_CODE);
    totalLen += l;
  }

  if (NOT_NULL (localConnectionInfo))
  {
    l = localConnectionInfo->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, APPL, PRIM, 14);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = initiatedConnection->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;

  return totalLen;
} // ServiceInitiatedEventInfo::BEncContent


void ServiceInitiatedEventInfo::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    initiatedConnection = new(memBlock) ConnectionID(memBlock);
    initiatedConnection->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0359: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, PRIM, 14)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    localConnectionInfo = new(memBlock) LocalConnectionState(memBlock);
    localConnectionInfo->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, ENUM_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    cause = new(memBlock) EventCause(memBlock);
    cause->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0360: Length discrepancy on sequence.";
  }
  else
    return;
} // ServiceInitiatedEventInfo::BDecContent

AsnLen ServiceInitiatedEventInfo::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void ServiceInitiatedEventInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135068904: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int ServiceInitiatedEventInfo::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ServiceInitiatedEventInfo::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ServiceInitiatedEventInfo::Print ( CTsvcLIB::LOG& os ) const
{
  os << "ServiceInitiatedEventInfo SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "initiatedConnection : ";
  if (NOT_NULL (initiatedConnection))
    os << *initiatedConnection;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "localConnectionInfo : ";
  if (NOT_NULL (localConnectionInfo))
    os << *localConnectionInfo;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "cause : ";
  if (NOT_NULL (cause))
    os << *cause;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // ServiceInitiatedEventInfo::Print


TransferredEventInfo::TransferredEventInfo( MemBlock* mb ) : AsnType( mb )
{
  primaryOldCall = NULL; // incomplete initialization of mandatory element!
  secondaryOldCall = NULL;
  transferringDevice = NULL; // incomplete initialization of mandatory element!
  transferredDevice = NULL; // incomplete initialization of mandatory element!
  transferredConnections = NULL;
  localConnectionInfo = NULL;
  cause = NULL;
}

TransferredEventInfo::TransferredEventInfo( MemBlock* mb, const TransferredEventInfo & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined TransferredEventInfo::TransferredEventInfo (const TransferredEventInfo &)";
  abort();
}

TransferredEventInfo::~TransferredEventInfo()
{
}

AsnType *TransferredEventInfo::Clone() const
{
  return new(memBlock) TransferredEventInfo(memBlock);
}

TransferredEventInfo &TransferredEventInfo::operator = (const TransferredEventInfo &that)
{
  if (this != &that)
  {
    if (that.primaryOldCall)
    {
      if (!primaryOldCall)
        primaryOldCall = new(memBlock) ConnectionID(memBlock);
      *primaryOldCall = *that.primaryOldCall;
    }
    else
    {
      primaryOldCall = NULL;
    }
    if (that.secondaryOldCall)
    {
      if (!secondaryOldCall)
        secondaryOldCall = new(memBlock) ConnectionID(memBlock);
      *secondaryOldCall = *that.secondaryOldCall;
    }
    else
    {
      secondaryOldCall = NULL;
    }
    if (that.transferringDevice)
    {
      if (!transferringDevice)
        transferringDevice = new(memBlock) SubjectDeviceID(memBlock);
      *transferringDevice = *that.transferringDevice;
    }
    else
    {
      transferringDevice = NULL;
    }
    if (that.transferredDevice)
    {
      if (!transferredDevice)
        transferredDevice = new(memBlock) SubjectDeviceID(memBlock);
      *transferredDevice = *that.transferredDevice;
    }
    else
    {
      transferredDevice = NULL;
    }
    if (that.transferredConnections)
    {
      if (!transferredConnections)
        transferredConnections = new(memBlock) ConnectionList(memBlock);
      *transferredConnections = *that.transferredConnections;
    }
    else
    {
      transferredConnections = NULL;
    }
    if (that.localConnectionInfo)
    {
      if (!localConnectionInfo)
        localConnectionInfo = new(memBlock) LocalConnectionState(memBlock);
      *localConnectionInfo = *that.localConnectionInfo;
    }
    else
    {
      localConnectionInfo = NULL;
    }
    if (that.cause)
    {
      if (!cause)
        cause = new(memBlock) EventCause(memBlock);
      *cause = *that.cause;
    }
    else
    {
      cause = NULL;
    }
  }

  return *this;
}

AsnLen
TransferredEventInfo::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (cause))
  {
    l = cause->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, ENUM_TAG_CODE);
    totalLen += l;
  }

  if (NOT_NULL (localConnectionInfo))
  {
    l = localConnectionInfo->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, APPL, PRIM, 14);
    totalLen += l;
  }

  if (NOT_NULL (transferredConnections))
  {
    l = transferredConnections->BEncContent (b);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = transferredDevice->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 3);
    totalLen += l;

      BEncEocIfNec (b);
    l = transferringDevice->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 3);
    totalLen += l;

  if (NOT_NULL (secondaryOldCall))
  {
      BEncEocIfNec (b);
    l = secondaryOldCall->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = primaryOldCall->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;

  return totalLen;
} // TransferredEventInfo::BEncContent


void TransferredEventInfo::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  AsnLen elmtLen2;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    primaryOldCall = new(memBlock) ConnectionID(memBlock);
    primaryOldCall->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0361: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    secondaryOldCall = new(memBlock) ConnectionID(memBlock);
    secondaryOldCall->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 3)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    transferringDevice = new(memBlock) SubjectDeviceID(memBlock);
    transferringDevice->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0362: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 3)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    transferredDevice = new(memBlock) SubjectDeviceID(memBlock);
    transferredDevice->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0363: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 12))
    || (tag1 == MAKE_TAG_ID (APPL, CONS, 13)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    transferredConnections = new(memBlock) ConnectionList(memBlock);
    transferredConnections->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (APPL, PRIM, 14)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    localConnectionInfo = new(memBlock) LocalConnectionState(memBlock);
    localConnectionInfo->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, ENUM_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    cause = new(memBlock) EventCause(memBlock);
    cause->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0364: Length discrepancy on sequence.";
  }
  else
    return;
} // TransferredEventInfo::BDecContent

AsnLen TransferredEventInfo::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void TransferredEventInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135069008: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int TransferredEventInfo::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int TransferredEventInfo::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void TransferredEventInfo::Print ( CTsvcLIB::LOG& os ) const
{
  os << "TransferredEventInfo SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "primaryOldCall : ";
  if (NOT_NULL (primaryOldCall))
    os << *primaryOldCall;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "secondaryOldCall : ";
  if (NOT_NULL (secondaryOldCall))
    os << *secondaryOldCall;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "transferringDevice : ";
  if (NOT_NULL (transferringDevice))
    os << *transferringDevice;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "transferredDevice : ";
  if (NOT_NULL (transferredDevice))
    os << *transferredDevice;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "transferredConnections : ";
  if (NOT_NULL (transferredConnections))
    os << *transferredConnections;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "localConnectionInfo : ";
  if (NOT_NULL (localConnectionInfo))
    os << *localConnectionInfo;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "cause : ";
  if (NOT_NULL (cause))
    os << *cause;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // TransferredEventInfo::Print


CallInformationEventInfo::CallInformationEventInfo( MemBlock* mb ) : AsnType( mb )
{
  connection = NULL; // incomplete initialization of mandatory element!
  device = NULL; // incomplete initialization of mandatory element!
  accountInfo = NULL;
  authorisationCode = NULL;
}

CallInformationEventInfo::CallInformationEventInfo( MemBlock* mb, const CallInformationEventInfo & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined CallInformationEventInfo::CallInformationEventInfo (const CallInformationEventInfo &)";
  abort();
}

CallInformationEventInfo::~CallInformationEventInfo()
{
}

AsnType *CallInformationEventInfo::Clone() const
{
  return new(memBlock) CallInformationEventInfo(memBlock);
}

CallInformationEventInfo &CallInformationEventInfo::operator = (const CallInformationEventInfo &that)
{
  if (this != &that)
  {
    if (that.connection)
    {
      if (!connection)
        connection = new(memBlock) ConnectionID(memBlock);
      *connection = *that.connection;
    }
    else
    {
      connection = NULL;
    }
    if (that.device)
    {
      if (!device)
        device = new(memBlock) SubjectDeviceID(memBlock);
      *device = *that.device;
    }
    else
    {
      device = NULL;
    }
    if (that.accountInfo)
    {
      if (!accountInfo)
        accountInfo = new(memBlock) AccountInfo(memBlock);
      *accountInfo = *that.accountInfo;
    }
    else
    {
      accountInfo = NULL;
    }
    if (that.authorisationCode)
    {
      if (!authorisationCode)
        authorisationCode = new(memBlock) AuthCode(memBlock);
      *authorisationCode = *that.authorisationCode;
    }
    else
    {
      authorisationCode = NULL;
    }
  }

  return *this;
}

AsnLen
CallInformationEventInfo::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (authorisationCode))
  {
    l = authorisationCode->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 11);
    totalLen += l;
  }

  if (NOT_NULL (accountInfo))
  {
    l = accountInfo->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 10);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = device->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 3);
    totalLen += l;

      BEncEocIfNec (b);
    l = connection->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 11);
    totalLen += l;

  return totalLen;
} // CallInformationEventInfo::BEncContent


void CallInformationEventInfo::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  AsnLen elmtLen2;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    connection = new(memBlock) ConnectionID(memBlock);
    connection->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0365: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 3)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    device = new(memBlock) SubjectDeviceID(memBlock);
    device->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0366: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 10))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 10)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    accountInfo = new(memBlock) AccountInfo(memBlock);
    accountInfo->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 11))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    authorisationCode = new(memBlock) AuthCode(memBlock);
    authorisationCode->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0367: Length discrepancy on sequence.";
  }
  else
    return;
} // CallInformationEventInfo::BDecContent

AsnLen CallInformationEventInfo::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void CallInformationEventInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135069072: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int CallInformationEventInfo::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int CallInformationEventInfo::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void CallInformationEventInfo::Print ( CTsvcLIB::LOG& os ) const
{
  os << "CallInformationEventInfo SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "connection : ";
  if (NOT_NULL (connection))
    os << *connection;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "device : ";
  if (NOT_NULL (device))
    os << *device;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "accountInfo : ";
  if (NOT_NULL (accountInfo))
    os << *accountInfo;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "authorisationCode : ";
  if (NOT_NULL (authorisationCode))
    os << *authorisationCode;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // CallInformationEventInfo::Print


DoNotDisturbEventInfo::DoNotDisturbEventInfo( MemBlock* mb ) : AsnType( mb )
    , doNotDisturbOn( mb )
{
  device = NULL; // incomplete initialization of mandatory element!
}

DoNotDisturbEventInfo::DoNotDisturbEventInfo( MemBlock* mb, const DoNotDisturbEventInfo & ) : AsnType( mb )
    , doNotDisturbOn( mb )
{
  throw "ERROR C0099: Use of incompletely defined DoNotDisturbEventInfo::DoNotDisturbEventInfo (const DoNotDisturbEventInfo &)";
  abort();
}

DoNotDisturbEventInfo::~DoNotDisturbEventInfo()
{
}

AsnType *DoNotDisturbEventInfo::Clone() const
{
  return new(memBlock) DoNotDisturbEventInfo(memBlock);
}

DoNotDisturbEventInfo &DoNotDisturbEventInfo::operator = (const DoNotDisturbEventInfo &that)
{
  if (this != &that)
  {
    if (that.device)
    {
      if (!device)
        device = new(memBlock) SubjectDeviceID(memBlock);
      *device = *that.device;
    }
    else
    {
      device = NULL;
    }
    doNotDisturbOn = that.doNotDisturbOn;
  }

  return *this;
}

AsnLen
DoNotDisturbEventInfo::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

    l = doNotDisturbOn.BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, BOOLEAN_TAG_CODE);
    totalLen += l;

      BEncEocIfNec (b);
    l = device->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 3);
    totalLen += l;

  return totalLen;
} // DoNotDisturbEventInfo::BEncContent


void DoNotDisturbEventInfo::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  AsnLen elmtLen2;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 3)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    device = new(memBlock) SubjectDeviceID(memBlock);
    device->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0368: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, BOOLEAN_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    doNotDisturbOn.BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0369: SEQUENCE is missing non-optional elmt.";
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0370: Length discrepancy on sequence.";
  }
  else
    return;
} // DoNotDisturbEventInfo::BDecContent

AsnLen DoNotDisturbEventInfo::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void DoNotDisturbEventInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135069176: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int DoNotDisturbEventInfo::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int DoNotDisturbEventInfo::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void DoNotDisturbEventInfo::Print ( CTsvcLIB::LOG& os ) const
{
  os << "DoNotDisturbEventInfo SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "device : ";
  if (NOT_NULL (device))
    os << *device;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "doNotDisturbOn : ";
  os << doNotDisturbOn;
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // DoNotDisturbEventInfo::Print


ForwardingEventInfo::ForwardingEventInfo( MemBlock* mb ) : AsnType( mb )
{
  device = NULL; // incomplete initialization of mandatory element!
  forwardingInformation = NULL; // incomplete initialization of mandatory element!
  forwardedTo = NULL;
}

ForwardingEventInfo::ForwardingEventInfo( MemBlock* mb, const ForwardingEventInfo & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined ForwardingEventInfo::ForwardingEventInfo (const ForwardingEventInfo &)";
  abort();
}

ForwardingEventInfo::~ForwardingEventInfo()
{
}

AsnType *ForwardingEventInfo::Clone() const
{
  return new(memBlock) ForwardingEventInfo(memBlock);
}

ForwardingEventInfo &ForwardingEventInfo::operator = (const ForwardingEventInfo &that)
{
  if (this != &that)
  {
    if (that.device)
    {
      if (!device)
        device = new(memBlock) SubjectDeviceID(memBlock);
      *device = *that.device;
    }
    else
    {
      device = NULL;
    }
    if (that.forwardingInformation)
    {
      if (!forwardingInformation)
        forwardingInformation = new(memBlock) ForwardParameter(memBlock);
      *forwardingInformation = *that.forwardingInformation;
    }
    else
    {
      forwardingInformation = NULL;
    }
    if (that.forwardedTo)
    {
      if (!forwardedTo)
        forwardedTo = new(memBlock) SubjectDeviceID(memBlock);
      *forwardedTo = *that.forwardedTo;
    }
    else
    {
      forwardedTo = NULL;
    }
  }

  return *this;
}

AsnLen
ForwardingEventInfo::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (forwardedTo))
  {
      BEncEocIfNec (b);
    l = forwardedTo->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 3);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = forwardingInformation->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
    totalLen += l;

      BEncEocIfNec (b);
    l = device->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 3);
    totalLen += l;

  return totalLen;
} // ForwardingEventInfo::BEncContent


void ForwardingEventInfo::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  AsnLen elmtLen2;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 3)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    device = new(memBlock) SubjectDeviceID(memBlock);
    device->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0371: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    forwardingInformation = new(memBlock) ForwardParameter(memBlock);
    forwardingInformation->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0372: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 3)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    forwardedTo = new(memBlock) SubjectDeviceID(memBlock);
    forwardedTo->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0373: Length discrepancy on sequence.";
  }
  else
    return;
} // ForwardingEventInfo::BDecContent

AsnLen ForwardingEventInfo::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void ForwardingEventInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135069232: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int ForwardingEventInfo::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ForwardingEventInfo::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ForwardingEventInfo::Print ( CTsvcLIB::LOG& os ) const
{
  os << "ForwardingEventInfo SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "device : ";
  if (NOT_NULL (device))
    os << *device;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "forwardingInformation : ";
  if (NOT_NULL (forwardingInformation))
    os << *forwardingInformation;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "forwardedTo : ";
  if (NOT_NULL (forwardedTo))
    os << *forwardedTo;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // ForwardingEventInfo::Print


MessageWaitingEventInfo::MessageWaitingEventInfo( MemBlock* mb ) : AsnType( mb )
    , messageWaitingOn( mb )
{
  deviceForMessage = NULL; // incomplete initialization of mandatory element!
  invokingDevice = NULL; // incomplete initialization of mandatory element!
}

MessageWaitingEventInfo::MessageWaitingEventInfo( MemBlock* mb, const MessageWaitingEventInfo & ) : AsnType( mb )
    , messageWaitingOn( mb )
{
  throw "ERROR C0099: Use of incompletely defined MessageWaitingEventInfo::MessageWaitingEventInfo (const MessageWaitingEventInfo &)";
  abort();
}

MessageWaitingEventInfo::~MessageWaitingEventInfo()
{
}

AsnType *MessageWaitingEventInfo::Clone() const
{
  return new(memBlock) MessageWaitingEventInfo(memBlock);
}

MessageWaitingEventInfo &MessageWaitingEventInfo::operator = (const MessageWaitingEventInfo &that)
{
  if (this != &that)
  {
    if (that.deviceForMessage)
    {
      if (!deviceForMessage)
        deviceForMessage = new(memBlock) CalledDeviceID(memBlock);
      *deviceForMessage = *that.deviceForMessage;
    }
    else
    {
      deviceForMessage = NULL;
    }
    if (that.invokingDevice)
    {
      if (!invokingDevice)
        invokingDevice = new(memBlock) SubjectDeviceID(memBlock);
      *invokingDevice = *that.invokingDevice;
    }
    else
    {
      invokingDevice = NULL;
    }
    messageWaitingOn = that.messageWaitingOn;
  }

  return *this;
}

AsnLen
MessageWaitingEventInfo::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

    l = messageWaitingOn.BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, BOOLEAN_TAG_CODE);
    totalLen += l;

      BEncEocIfNec (b);
    l = invokingDevice->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 3);
    totalLen += l;

      BEncEocIfNec (b);
    l = deviceForMessage->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 2);
    totalLen += l;

  return totalLen;
} // MessageWaitingEventInfo::BEncContent


void MessageWaitingEventInfo::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  AsnLen elmtLen2;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 2)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    deviceForMessage = new(memBlock) CalledDeviceID(memBlock);
    deviceForMessage->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0374: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 3)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    invokingDevice = new(memBlock) SubjectDeviceID(memBlock);
    invokingDevice->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    tag1 = BDecTag (b, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0375: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, BOOLEAN_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    messageWaitingOn.BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0376: SEQUENCE is missing non-optional elmt.";
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0377: Length discrepancy on sequence.";
  }
  else
    return;
} // MessageWaitingEventInfo::BDecContent

AsnLen MessageWaitingEventInfo::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void MessageWaitingEventInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135069328: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int MessageWaitingEventInfo::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int MessageWaitingEventInfo::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void MessageWaitingEventInfo::Print ( CTsvcLIB::LOG& os ) const
{
  os << "MessageWaitingEventInfo SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "deviceForMessage : ";
  if (NOT_NULL (deviceForMessage))
    os << *deviceForMessage;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "invokingDevice : ";
  if (NOT_NULL (invokingDevice))
    os << *invokingDevice;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "messageWaitingOn : ";
  os << messageWaitingOn;
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // MessageWaitingEventInfo::Print


LoggedOnEventInfo::LoggedOnEventInfo( MemBlock* mb ) : AsnType( mb )
{
  agentDevice = NULL; // incomplete initialization of mandatory element!
  agentID = NULL;
  agentGroup = NULL;
  password = NULL;
}

LoggedOnEventInfo::LoggedOnEventInfo( MemBlock* mb, const LoggedOnEventInfo & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined LoggedOnEventInfo::LoggedOnEventInfo (const LoggedOnEventInfo &)";
  abort();
}

LoggedOnEventInfo::~LoggedOnEventInfo()
{
}

AsnType *LoggedOnEventInfo::Clone() const
{
  return new(memBlock) LoggedOnEventInfo(memBlock);
}

LoggedOnEventInfo &LoggedOnEventInfo::operator = (const LoggedOnEventInfo &that)
{
  if (this != &that)
  {
    if (that.agentDevice)
    {
      if (!agentDevice)
        agentDevice = new(memBlock) SubjectDeviceID(memBlock);
      *agentDevice = *that.agentDevice;
    }
    else
    {
      agentDevice = NULL;
    }
    if (that.agentID)
    {
      if (!agentID)
        agentID = new(memBlock) AgentID(memBlock);
      *agentID = *that.agentID;
    }
    else
    {
      agentID = NULL;
    }
    if (that.agentGroup)
    {
      if (!agentGroup)
        agentGroup = new(memBlock) AgentGroup(memBlock);
      *agentGroup = *that.agentGroup;
    }
    else
    {
      agentGroup = NULL;
    }
    if (that.password)
    {
      if (!password)
        password = new(memBlock) AgentPassword(memBlock);
      *password = *that.password;
    }
    else
    {
      password = NULL;
    }
  }

  return *this;
}

AsnLen
LoggedOnEventInfo::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (password))
  {
    l = password->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 11);
    totalLen += l;
  }

  if (NOT_NULL (agentGroup))
  {
    l = agentGroup->BEncContent (b);
    totalLen += l;
  }

  if (NOT_NULL (agentID))
  {
    l = agentID->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 10);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = agentDevice->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 3);
    totalLen += l;

  return totalLen;
} // LoggedOnEventInfo::BEncContent


void LoggedOnEventInfo::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  AsnLen elmtLen2;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 3)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    agentDevice = new(memBlock) SubjectDeviceID(memBlock);
    agentDevice->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0378: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 10))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 10)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    agentID = new(memBlock) AgentID(memBlock);
    agentID->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 1)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    agentGroup = new(memBlock) AgentGroup(memBlock);
    agentGroup->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 11))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 11)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    password = new(memBlock) AgentPassword(memBlock);
    password->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0379: Length discrepancy on sequence.";
  }
  else
    return;
} // LoggedOnEventInfo::BDecContent

AsnLen LoggedOnEventInfo::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void LoggedOnEventInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135069416: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int LoggedOnEventInfo::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int LoggedOnEventInfo::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void LoggedOnEventInfo::Print ( CTsvcLIB::LOG& os ) const
{
  os << "LoggedOnEventInfo SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "agentDevice : ";
  if (NOT_NULL (agentDevice))
    os << *agentDevice;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "agentID : ";
  if (NOT_NULL (agentID))
    os << *agentID;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "agentGroup : ";
  if (NOT_NULL (agentGroup))
    os << *agentGroup;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "password : ";
  if (NOT_NULL (password))
    os << *password;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // LoggedOnEventInfo::Print


LoggedOffEventInfo::LoggedOffEventInfo( MemBlock* mb ) : AsnType( mb )
{
  agentDevice = NULL; // incomplete initialization of mandatory element!
  agentID = NULL;
  agentGroup = NULL;
}

LoggedOffEventInfo::LoggedOffEventInfo( MemBlock* mb, const LoggedOffEventInfo & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined LoggedOffEventInfo::LoggedOffEventInfo (const LoggedOffEventInfo &)";
  abort();
}

LoggedOffEventInfo::~LoggedOffEventInfo()
{
}

AsnType *LoggedOffEventInfo::Clone() const
{
  return new(memBlock) LoggedOffEventInfo(memBlock);
}

LoggedOffEventInfo &LoggedOffEventInfo::operator = (const LoggedOffEventInfo &that)
{
  if (this != &that)
  {
    if (that.agentDevice)
    {
      if (!agentDevice)
        agentDevice = new(memBlock) SubjectDeviceID(memBlock);
      *agentDevice = *that.agentDevice;
    }
    else
    {
      agentDevice = NULL;
    }
    if (that.agentID)
    {
      if (!agentID)
        agentID = new(memBlock) AgentID(memBlock);
      *agentID = *that.agentID;
    }
    else
    {
      agentID = NULL;
    }
    if (that.agentGroup)
    {
      if (!agentGroup)
        agentGroup = new(memBlock) AgentGroup(memBlock);
      *agentGroup = *that.agentGroup;
    }
    else
    {
      agentGroup = NULL;
    }
  }

  return *this;
}

AsnLen
LoggedOffEventInfo::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (agentGroup))
  {
    l = agentGroup->BEncContent (b);
    totalLen += l;
  }

  if (NOT_NULL (agentID))
  {
    l = agentID->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 10);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = agentDevice->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 3);
    totalLen += l;

  return totalLen;
} // LoggedOffEventInfo::BEncContent


void LoggedOffEventInfo::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  AsnLen elmtLen2;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 3)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    agentDevice = new(memBlock) SubjectDeviceID(memBlock);
    agentDevice->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0380: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 10))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 10)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    agentID = new(memBlock) AgentID(memBlock);
    agentID->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 1)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    agentGroup = new(memBlock) AgentGroup(memBlock);
    agentGroup->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0381: Length discrepancy on sequence.";
  }
  else
    return;
} // LoggedOffEventInfo::BDecContent

AsnLen LoggedOffEventInfo::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void LoggedOffEventInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135069480: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int LoggedOffEventInfo::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int LoggedOffEventInfo::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void LoggedOffEventInfo::Print ( CTsvcLIB::LOG& os ) const
{
  os << "LoggedOffEventInfo SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "agentDevice : ";
  if (NOT_NULL (agentDevice))
    os << *agentDevice;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "agentID : ";
  if (NOT_NULL (agentID))
    os << *agentID;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "agentGroup : ";
  if (NOT_NULL (agentGroup))
    os << *agentGroup;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // LoggedOffEventInfo::Print


NotReadyEventInfo::NotReadyEventInfo( MemBlock* mb ) : AsnType( mb )
{
  agentDevice = NULL; // incomplete initialization of mandatory element!
  agentID = NULL;
}

NotReadyEventInfo::NotReadyEventInfo( MemBlock* mb, const NotReadyEventInfo & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined NotReadyEventInfo::NotReadyEventInfo (const NotReadyEventInfo &)";
  abort();
}

NotReadyEventInfo::~NotReadyEventInfo()
{
}

AsnType *NotReadyEventInfo::Clone() const
{
  return new(memBlock) NotReadyEventInfo(memBlock);
}

NotReadyEventInfo &NotReadyEventInfo::operator = (const NotReadyEventInfo &that)
{
  if (this != &that)
  {
    if (that.agentDevice)
    {
      if (!agentDevice)
        agentDevice = new(memBlock) SubjectDeviceID(memBlock);
      *agentDevice = *that.agentDevice;
    }
    else
    {
      agentDevice = NULL;
    }
    if (that.agentID)
    {
      if (!agentID)
        agentID = new(memBlock) AgentID(memBlock);
      *agentID = *that.agentID;
    }
    else
    {
      agentID = NULL;
    }
  }

  return *this;
}

AsnLen
NotReadyEventInfo::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (agentID))
  {
    l = agentID->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 10);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = agentDevice->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 3);
    totalLen += l;

  return totalLen;
} // NotReadyEventInfo::BEncContent


void NotReadyEventInfo::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  AsnLen elmtLen2;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 3)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    agentDevice = new(memBlock) SubjectDeviceID(memBlock);
    agentDevice->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0382: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 10))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 10)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    agentID = new(memBlock) AgentID(memBlock);
    agentID->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0383: Length discrepancy on sequence.";
  }
  else
    return;
} // NotReadyEventInfo::BDecContent

AsnLen NotReadyEventInfo::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void NotReadyEventInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135069568: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int NotReadyEventInfo::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int NotReadyEventInfo::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void NotReadyEventInfo::Print ( CTsvcLIB::LOG& os ) const
{
  os << "NotReadyEventInfo SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "agentDevice : ";
  if (NOT_NULL (agentDevice))
    os << *agentDevice;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "agentID : ";
  if (NOT_NULL (agentID))
    os << *agentID;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // NotReadyEventInfo::Print


ReadyEventInfo::ReadyEventInfo( MemBlock* mb ) : AsnType( mb )
{
  agentDevice = NULL; // incomplete initialization of mandatory element!
  agentID = NULL;
}

ReadyEventInfo::ReadyEventInfo( MemBlock* mb, const ReadyEventInfo & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined ReadyEventInfo::ReadyEventInfo (const ReadyEventInfo &)";
  abort();
}

ReadyEventInfo::~ReadyEventInfo()
{
}

AsnType *ReadyEventInfo::Clone() const
{
  return new(memBlock) ReadyEventInfo(memBlock);
}

ReadyEventInfo &ReadyEventInfo::operator = (const ReadyEventInfo &that)
{
  if (this != &that)
  {
    if (that.agentDevice)
    {
      if (!agentDevice)
        agentDevice = new(memBlock) SubjectDeviceID(memBlock);
      *agentDevice = *that.agentDevice;
    }
    else
    {
      agentDevice = NULL;
    }
    if (that.agentID)
    {
      if (!agentID)
        agentID = new(memBlock) AgentID(memBlock);
      *agentID = *that.agentID;
    }
    else
    {
      agentID = NULL;
    }
  }

  return *this;
}

AsnLen
ReadyEventInfo::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (agentID))
  {
    l = agentID->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 10);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = agentDevice->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 3);
    totalLen += l;

  return totalLen;
} // ReadyEventInfo::BEncContent


void ReadyEventInfo::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  AsnLen elmtLen2;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 3)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    agentDevice = new(memBlock) SubjectDeviceID(memBlock);
    agentDevice->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0384: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 10))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 10)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    agentID = new(memBlock) AgentID(memBlock);
    agentID->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0385: Length discrepancy on sequence.";
  }
  else
    return;
} // ReadyEventInfo::BDecContent

AsnLen ReadyEventInfo::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void ReadyEventInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135069656: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int ReadyEventInfo::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ReadyEventInfo::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void ReadyEventInfo::Print ( CTsvcLIB::LOG& os ) const
{
  os << "ReadyEventInfo SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "agentDevice : ";
  if (NOT_NULL (agentDevice))
    os << *agentDevice;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "agentID : ";
  if (NOT_NULL (agentID))
    os << *agentID;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // ReadyEventInfo::Print


WorkNotReadyEventInfo::WorkNotReadyEventInfo( MemBlock* mb ) : AsnType( mb )
{
  agentDevice = NULL; // incomplete initialization of mandatory element!
  agentID = NULL;
}

WorkNotReadyEventInfo::WorkNotReadyEventInfo( MemBlock* mb, const WorkNotReadyEventInfo & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined WorkNotReadyEventInfo::WorkNotReadyEventInfo (const WorkNotReadyEventInfo &)";
  abort();
}

WorkNotReadyEventInfo::~WorkNotReadyEventInfo()
{
}

AsnType *WorkNotReadyEventInfo::Clone() const
{
  return new(memBlock) WorkNotReadyEventInfo(memBlock);
}

WorkNotReadyEventInfo &WorkNotReadyEventInfo::operator = (const WorkNotReadyEventInfo &that)
{
  if (this != &that)
  {
    if (that.agentDevice)
    {
      if (!agentDevice)
        agentDevice = new(memBlock) SubjectDeviceID(memBlock);
      *agentDevice = *that.agentDevice;
    }
    else
    {
      agentDevice = NULL;
    }
    if (that.agentID)
    {
      if (!agentID)
        agentID = new(memBlock) AgentID(memBlock);
      *agentID = *that.agentID;
    }
    else
    {
      agentID = NULL;
    }
  }

  return *this;
}

AsnLen
WorkNotReadyEventInfo::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (agentID))
  {
    l = agentID->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 10);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = agentDevice->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 3);
    totalLen += l;

  return totalLen;
} // WorkNotReadyEventInfo::BEncContent


void WorkNotReadyEventInfo::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  AsnLen elmtLen2;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 3)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    agentDevice = new(memBlock) SubjectDeviceID(memBlock);
    agentDevice->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0386: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 10))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 10)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    agentID = new(memBlock) AgentID(memBlock);
    agentID->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0387: Length discrepancy on sequence.";
  }
  else
    return;
} // WorkNotReadyEventInfo::BDecContent

AsnLen WorkNotReadyEventInfo::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void WorkNotReadyEventInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135069744: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int WorkNotReadyEventInfo::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int WorkNotReadyEventInfo::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void WorkNotReadyEventInfo::Print ( CTsvcLIB::LOG& os ) const
{
  os << "WorkNotReadyEventInfo SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "agentDevice : ";
  if (NOT_NULL (agentDevice))
    os << *agentDevice;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "agentID : ";
  if (NOT_NULL (agentID))
    os << *agentID;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // WorkNotReadyEventInfo::Print


WorkReadyEventInfo::WorkReadyEventInfo( MemBlock* mb ) : AsnType( mb )
{
  agentDevice = NULL; // incomplete initialization of mandatory element!
  agentID = NULL;
}

WorkReadyEventInfo::WorkReadyEventInfo( MemBlock* mb, const WorkReadyEventInfo & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined WorkReadyEventInfo::WorkReadyEventInfo (const WorkReadyEventInfo &)";
  abort();
}

WorkReadyEventInfo::~WorkReadyEventInfo()
{
}

AsnType *WorkReadyEventInfo::Clone() const
{
  return new(memBlock) WorkReadyEventInfo(memBlock);
}

WorkReadyEventInfo &WorkReadyEventInfo::operator = (const WorkReadyEventInfo &that)
{
  if (this != &that)
  {
    if (that.agentDevice)
    {
      if (!agentDevice)
        agentDevice = new(memBlock) SubjectDeviceID(memBlock);
      *agentDevice = *that.agentDevice;
    }
    else
    {
      agentDevice = NULL;
    }
    if (that.agentID)
    {
      if (!agentID)
        agentID = new(memBlock) AgentID(memBlock);
      *agentID = *that.agentID;
    }
    else
    {
      agentID = NULL;
    }
  }

  return *this;
}

AsnLen
WorkReadyEventInfo::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (agentID))
  {
    l = agentID->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 10);
    totalLen += l;
  }

      BEncEocIfNec (b);
    l = agentDevice->BEncContent (b);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, APPL, CONS, 3);
    totalLen += l;

  return totalLen;
} // WorkReadyEventInfo::BEncContent


void WorkReadyEventInfo::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  AsnLen elmtLen2;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (APPL, CONS, 3)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
    elmtLen2 = BDecLen (b, seqBytesDecoded);
    agentDevice = new(memBlock) SubjectDeviceID(memBlock);
    agentDevice->BDecContent (b, tag1, elmtLen2, seqBytesDecoded);
    if (elmtLen1 == INDEFINITE_LEN)
      BDecEoc (b, seqBytesDecoded);

    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0388: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 10))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 10)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    agentID = new(memBlock) AgentID(memBlock);
    agentID->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0389: Length discrepancy on sequence.";
  }
  else
    return;
} // WorkReadyEventInfo::BDecContent

AsnLen WorkReadyEventInfo::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void WorkReadyEventInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135069832: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int WorkReadyEventInfo::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int WorkReadyEventInfo::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void WorkReadyEventInfo::Print ( CTsvcLIB::LOG& os ) const
{
  os << "WorkReadyEventInfo SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "agentDevice : ";
  if (NOT_NULL (agentDevice))
    os << *agentDevice;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "agentID : ";
  if (NOT_NULL (agentID))
    os << *agentID;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // WorkReadyEventInfo::Print


BackInServiceEventInfo::BackInServiceEventInfo( MemBlock* mb ) : AsnType( mb )
{
  device = NULL; // incomplete initialization of mandatory element!
  cause = NULL;
}

BackInServiceEventInfo::BackInServiceEventInfo( MemBlock* mb, const BackInServiceEventInfo & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined BackInServiceEventInfo::BackInServiceEventInfo (const BackInServiceEventInfo &)";
  abort();
}

BackInServiceEventInfo::~BackInServiceEventInfo()
{
}

AsnType *BackInServiceEventInfo::Clone() const
{
  return new(memBlock) BackInServiceEventInfo(memBlock);
}

BackInServiceEventInfo &BackInServiceEventInfo::operator = (const BackInServiceEventInfo &that)
{
  if (this != &that)
  {
    if (that.device)
    {
      if (!device)
        device = new(memBlock) DeviceID(memBlock);
      *device = *that.device;
    }
    else
    {
      device = NULL;
    }
    if (that.cause)
    {
      if (!cause)
        cause = new(memBlock) EventCause(memBlock);
      *cause = *that.cause;
    }
    else
    {
      cause = NULL;
    }
  }

  return *this;
}

AsnLen
BackInServiceEventInfo::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (cause))
  {
    l = cause->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, ENUM_TAG_CODE);
    totalLen += l;
  }

    l = device->BEncContent (b);
    totalLen += l;

  return totalLen;
} // BackInServiceEventInfo::BEncContent


void BackInServiceEventInfo::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 1)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    device = new(memBlock) DeviceID(memBlock);
    device->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0390: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, ENUM_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    cause = new(memBlock) EventCause(memBlock);
    cause->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0391: Length discrepancy on sequence.";
  }
  else
    return;
} // BackInServiceEventInfo::BDecContent

AsnLen BackInServiceEventInfo::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void BackInServiceEventInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135069928: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int BackInServiceEventInfo::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int BackInServiceEventInfo::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void BackInServiceEventInfo::Print ( CTsvcLIB::LOG& os ) const
{
  os << "BackInServiceEventInfo SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "device : ";
  if (NOT_NULL (device))
    os << *device;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "cause : ";
  if (NOT_NULL (cause))
    os << *cause;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // BackInServiceEventInfo::Print


OutOfServiceEventInfo::OutOfServiceEventInfo( MemBlock* mb ) : AsnType( mb )
{
  device = NULL; // incomplete initialization of mandatory element!
  cause = NULL;
}

OutOfServiceEventInfo::OutOfServiceEventInfo( MemBlock* mb, const OutOfServiceEventInfo & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined OutOfServiceEventInfo::OutOfServiceEventInfo (const OutOfServiceEventInfo &)";
  abort();
}

OutOfServiceEventInfo::~OutOfServiceEventInfo()
{
}

AsnType *OutOfServiceEventInfo::Clone() const
{
  return new(memBlock) OutOfServiceEventInfo(memBlock);
}

OutOfServiceEventInfo &OutOfServiceEventInfo::operator = (const OutOfServiceEventInfo &that)
{
  if (this != &that)
  {
    if (that.device)
    {
      if (!device)
        device = new(memBlock) DeviceID(memBlock);
      *device = *that.device;
    }
    else
    {
      device = NULL;
    }
    if (that.cause)
    {
      if (!cause)
        cause = new(memBlock) EventCause(memBlock);
      *cause = *that.cause;
    }
    else
    {
      cause = NULL;
    }
  }

  return *this;
}

AsnLen
OutOfServiceEventInfo::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

  if (NOT_NULL (cause))
  {
    l = cause->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, ENUM_TAG_CODE);
    totalLen += l;
  }

    l = device->BEncContent (b);
    totalLen += l;

  return totalLen;
} // OutOfServiceEventInfo::BEncContent


void OutOfServiceEventInfo::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (CNTX, PRIM, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 1)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    device = new(memBlock) DeviceID(memBlock);
    device->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    if (seqBytesDecoded == elmtLen0)
    {
      bytesDecoded += seqBytesDecoded;
      return;
    }
    else
    {
      tag1 = BDecTag (b, seqBytesDecoded);

      if ((elmtLen0 == INDEFINITE_LEN) && (tag1 == EOC_TAG_ID))
      {
        BDEC_2ND_EOC_OCTET (b, seqBytesDecoded)
        bytesDecoded += seqBytesDecoded;
        return;
      }
    }
  }
  else
  {
    throw "ERROR C0392: SEQUENCE is missing non-optional elmt.";
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, ENUM_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    cause = new(memBlock) EventCause(memBlock);
    cause->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0393: Length discrepancy on sequence.";
  }
  else
    return;
} // OutOfServiceEventInfo::BDecContent

AsnLen OutOfServiceEventInfo::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, SEQ_TAG_CODE);
  return l;
}

void OutOfServiceEventInfo::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, SEQ_TAG_CODE))
  {
    throw "ERROR C135069992: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int OutOfServiceEventInfo::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int OutOfServiceEventInfo::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void OutOfServiceEventInfo::Print ( CTsvcLIB::LOG& os ) const
{
  os << "OutOfServiceEventInfo SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "device : ";
  if (NOT_NULL (device))
    os << *device;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "cause : ";
  if (NOT_NULL (cause))
    os << *cause;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";

} // OutOfServiceEventInfo::Print

//////////////////////////////////////////////////////////////////////////////
} // namespace ASN
