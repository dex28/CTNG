/*
    Project: CSTALib

    Module: CSTA.h

    Description: class definitions for ASN.1 module CSTA

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB

    Wed Aug 29 14:26:23 2001
    Sun Mar 24 14:05    2002 -- AsnBits default size set according to enum max value
*/

#ifndef _CSTA_h_
#define _CSTA_h_

#include "CSTA-Any.h"

namespace ASN
{

///////////////////////////////////////////////////////////////////////////////
// Class declarations

class GeneralProblem;
class InvokeProblem;
class ReturnResultProblem;
class ReturnErrorProblem;
class Operations;
class StateIncompatibility;
class SystemResourceAvailability;
class SubscribedResourceAvailability;
class PerformanceManagement;
class SecurityError;
class EventCause;
class LocalConnectionState;
class MonitorCrossRefID;
class CallFilter;
class FeatureFilter;
class AgentFilter;
class MaintenanceFilter;
class MonitorType;
class SimpleCallState;
class AgentState;
class AllocationState;
class DeviceClass;
class DeviceType;
class ForwardingType;
class QueryDeviceFeature;
class SystemStatus;
class SelectValue;
class RoutingCrossRefID;
class OperationIDType;
class ErrorIDType;
class EventIDType;
class PublicTON;
class PrivateTON;
class RetryValue;
class Seal;
class CSTAPrivateData;
class CSTACommonArgumentsSeqOf;
class ListForwardParametersSeq;
class RORJapduChoice1;
class RORJapduChoice;
class RORSapduSeq;
class ROIVapdu;
class RORSapdu;
class ROERapdu;
class RORJapdu;
class AlternateCallResult;
class AnswerCallResult;
class CallCompletionResult;
class ClearCallResult;
class ClearConnectionResult;
class DivertCallResult;
class HoldCallResult;
class ReconnectCallResult;
class RetrieveCallResult;
class SetFeatureResult;
class EventTypeID;
class CSTAEventReportArgument;
class EscapeServiceResult;
class SystemStatusResult;
class MonitorStopResult;
class UniversalFailure;
class DeviceID;
class ExtendedDeviceID;
class CallingDeviceID;
class CalledDeviceID;
class SubjectDeviceID;
class RedirectionDeviceID;
class MonitorFilter;
class CompoundCallState;
class DeviceInfo;
class ListForwardParameters;
class LoggedOnInfo;
class LoggedOffInfo;
class ForwardParameter;
class QueryDeviceInformation;
class CSTASecurityData;
class CSTACommonArguments;
class ConnectionIDChoice;
class SnapshotDeviceArgumentSeq;
class MonitorStopArgumentSeq;
class ChangeMonitorFilterResultSeq;
class SystemStatusArgumentSeq;
class QueryDeviceResultSeq;
class ROSEapdu;
class MakeCallArgument;
class MakePredictiveCallArgument;
class QueryDeviceArgument;
class QueryDeviceResult;
class ReRouteRequestArgument;
class RouteSelectRequestArgument;
class RouteUsedRequestArgument;
class RouteEndRequestArgument;
class SystemStatusArgument;
class MonitorStartResult;
class ChangeMonitorFilterArgument;
class ChangeMonitorFilterResult;
class MonitorStopArgument;
class SnapshotDeviceArgument;
class ConnectionID;
class ConnectionIDList;
class SnapshotCallResponseInfo;
class CallState;
class AgentParameter;
class FeatureInfo;
class SetDeviceFeature;
class DivertInfoSeq1;
class DivertInfoSeq;
class ConnectionDetailsSeq;
class CallInfoSeq;
class SnapshotCallArgumentSeq;
class RetrieveCallArgumentSeq;
class MakePredictiveCallResultSeq;
class MakeCallResultSeq;
class ConsultationCallResultSeq;
class ClearConnectionArgumentSeq;
class ClearCallArgumentSeq;
class CallCompletionArgumentSeq;
class AnswerCallArgumentSeq;
class AnswerCallArgument;
class CallCompletionArgument;
class ClearCallArgument;
class ClearConnectionArgument;
class ConsultationCallArgument;
class ConsultationCallResult;
class HoldCallArgument;
class MakeCallResult;
class MakePredictiveCallResult;
class RetrieveCallArgument;
class SetFeatureArgument;
class RouteRequestArgument;
class SnapshotCallArgument;
class CSTAObject;
class CallInfo;
class ConnectionList;
class SnapshotDeviceResponseInfo;
class SnapshotCallData;
class ConnectionDetails;
class DivertInfo;
class SnapshotCallResultSeq;
class TransferCallArgumentSeq;
class ReconnectCallArgumentSeq;
class DivertCallArgumentSeq;
class ConferenceCallArgumentSeq;
class AlternateCallArgumentSeq;
class AlternateCallArgument;
class ConferenceCallArgument;
class ConferenceCallResult;
class DivertCallArgument;
class ReconnectCallArgument;
class TransferCallArgument;
class TransferCallResult;
class MonitorStartArgument;
class SnapshotCallResult;
class SnapshotDeviceData;
class SnapshotDeviceResultSeq;
class SnapshotDeviceResult;
class CallClearedEventInfo;
class ConferencedEventInfo;
class ConnectionClearedEventInfo;
class DeliveredEventInfo;
class DivertedEventInfo;
class EstablishedEventInfo;
class FailedEventInfo;
class HeldEventInfo;
class NetworkReachedEventInfo;
class OriginatedEventInfo;
class QueuedEventInfo;
class RetrievedEventInfo;
class ServiceInitiatedEventInfo;
class TransferredEventInfo;
class CallInformationEventInfo;
class DoNotDisturbEventInfo;
class ForwardingEventInfo;
class MessageWaitingEventInfo;
class LoggedOnEventInfo;
class LoggedOffEventInfo;
class NotReadyEventInfo;
class ReadyEventInfo;
class WorkNotReadyEventInfo;
class WorkReadyEventInfo;
class BackInServiceEventInfo;
class OutOfServiceEventInfo;

///////////////////////////////////////////////////////////////////////////////
// Class definitions

/* INTEGER*/
typedef AsnInt InvokeIDType;

/* INTEGER*/
typedef AsnInt InvokedIDType;

/* INTEGER { unrecognisedAPDU (0), mistypedAPDU (1), badlyStructuredAPDU (2) } */
class GeneralProblem: public AsnInt
{
public:
  GeneralProblem( MemBlock* mb ): AsnInt( mb ) {}
  GeneralProblem( MemBlock* mb, int i ): AsnInt( mb, i ) {}
  enum
  {
    unrecognisedAPDU = 0,
    mistypedAPDU = 1,
    badlyStructuredAPDU = 2
  };

    static const char* EnumText( AsnIntType value );

  void Print ( CTsvcLIB::LOG& os ) const;
};


/* INTEGER { duplicateInvocation (0), unrecognisedOperation (1), mistypedArgument (2), resourceLimitation (3), initiatorReleasing (4), unrecognisedLinkedID (5), linkedResponseUnexpected (6), unexpectedChildOperation (7) } */
class InvokeProblem: public AsnInt
{
public:
  InvokeProblem( MemBlock* mb ): AsnInt( mb ) {}
  InvokeProblem( MemBlock* mb, int i ): AsnInt( mb, i ) {}
  enum
  {
    duplicateInvocation = 0,
    unrecognisedOperation = 1,
    mistypedArgument = 2,
    resourceLimitation = 3,
    initiatorReleasing = 4,
    unrecognisedLinkedID = 5,
    linkedResponseUnexpected = 6,
    unexpectedChildOperation = 7
  };

    static const char* EnumText( AsnIntType value );

  void Print ( CTsvcLIB::LOG& os ) const;
};


/* INTEGER { unrecognisedInvocation (0), resultResponseUnexpected (1), mistypedResult (2) } */
class ReturnResultProblem: public AsnInt
{
public:
  ReturnResultProblem( MemBlock* mb ): AsnInt( mb ) {}
  ReturnResultProblem( MemBlock* mb, int i ): AsnInt( mb, i ) {}
  enum
  {
    unrecognisedInvocation = 0,
    resultResponseUnexpected = 1,
    mistypedResult = 2
  };

    static const char* EnumText( AsnIntType value );

  void Print ( CTsvcLIB::LOG& os ) const;
};


/* INTEGER { unrecognisedInvocation (0), errorResponseUnexpected (1), unrecognisedError (2), unexpectedError (3), mistypedParameter (4) } */
class ReturnErrorProblem: public AsnInt
{
public:
  ReturnErrorProblem( MemBlock* mb ): AsnInt( mb ) {}
  ReturnErrorProblem( MemBlock* mb, int i ): AsnInt( mb, i ) {}
  enum
  {
    unrecognisedInvocation = 0,
    errorResponseUnexpected = 1,
    unrecognisedError = 2,
    unexpectedError = 3,
    mistypedParameter = 4
  };

    static const char* EnumText( AsnIntType value );

  void Print ( CTsvcLIB::LOG& os ) const;
};


/* NULL*/
typedef AsnNull PrivateEventInfo;

/* ENUMERATED { generic (1), requestIncompatibleWithObject (2), valueOutOfRange (3), objectNotKnown (4), invalidCallingDevice (5), invalidCalledDevice (6), invalidForwardingDestination (7), privilegeViolationOnSpecifiedDevice (8), privilegeViolationOnCalledDevice (9), privilegeViolationOnCallingDevice (10), invalidCSTACallIdentifier (11), invalidCSTADeviceIdentifier (12), invalidCSTAConnectionIdentifier (13), invalidDestination (14), invalidFeature (15), invalidAllocationState (16), invalidCrossRefID (17), invalidObjectType (18), securityViolation (19) } */
class Operations: public AsnEnum
{
public:
  Operations( MemBlock* mb ): AsnEnum( mb ) {}
  Operations( MemBlock* mb, int i ): AsnEnum( mb, i ) {}
  enum
  {
    generic = 1,
    requestIncompatibleWithObject = 2,
    valueOutOfRange = 3,
    objectNotKnown = 4,
    invalidCallingDevice = 5,
    invalidCalledDevice = 6,
    invalidForwardingDestination = 7,
    privilegeViolationOnSpecifiedDevice = 8,
    privilegeViolationOnCalledDevice = 9,
    privilegeViolationOnCallingDevice = 10,
    invalidCSTACallIdentifier = 11,
    invalidCSTADeviceIdentifier = 12,
    invalidCSTAConnectionIdentifier = 13,
    invalidDestination = 14,
    invalidFeature = 15,
    invalidAllocationState = 16,
    invalidCrossRefID = 17,
    invalidObjectType = 18,
    securityViolation = 19
  };

    static const char* EnumText( AsnIntType value );

  void Print ( CTsvcLIB::LOG& os ) const;
};


/* ENUMERATED { generic (1), invalidObjectState (2), invalidConnectionID (3), noActiveCall (4), noHeldCall (5), noCallToClear (6), noConnectionToClear (7), noCallToAnswer (8), noCallToComplete (9) } */
class StateIncompatibility: public AsnEnum
{
public:
  StateIncompatibility( MemBlock* mb ): AsnEnum( mb ) {}
  StateIncompatibility( MemBlock* mb, int i ): AsnEnum( mb, i ) {}
  enum
  {
    generic = 1,
    invalidObjectState = 2,
    invalidConnectionID = 3,
    noActiveCall = 4,
    noHeldCall = 5,
    noCallToClear = 6,
    noConnectionToClear = 7,
    noCallToAnswer = 8,
    noCallToComplete = 9
  };

    static const char* EnumText( AsnIntType value );

  void Print ( CTsvcLIB::LOG& os ) const;
};


/* ENUMERATED { generic (1), serviceBusy (2), resourceBusy (3), resourceOutOfService (4), networkBusy (5), networkOutOfService (6), overallMonitorLimitExceeded (7), conferenceMemberLimitExceeded (8) } */
class SystemResourceAvailability: public AsnEnum
{
public:
  SystemResourceAvailability( MemBlock* mb ): AsnEnum( mb ) {}
  SystemResourceAvailability( MemBlock* mb, int i ): AsnEnum( mb, i ) {}
  enum
  {
    generic = 1,
    serviceBusy = 2,
    resourceBusy = 3,
    resourceOutOfService = 4,
    networkBusy = 5,
    networkOutOfService = 6,
    overallMonitorLimitExceeded = 7,
    conferenceMemberLimitExceeded = 8
  };

    static const char* EnumText( AsnIntType value );

  void Print ( CTsvcLIB::LOG& os ) const;
};


/* ENUMERATED { generic (1), objectMonitorLimitExceeded (2), externalTrunkLimitExceeded (3), outstandingRequestLimitExceeded (4) } */
class SubscribedResourceAvailability: public AsnEnum
{
public:
  SubscribedResourceAvailability( MemBlock* mb ): AsnEnum( mb ) {}
  SubscribedResourceAvailability( MemBlock* mb, int i ): AsnEnum( mb, i ) {}
  enum
  {
    generic = 1,
    objectMonitorLimitExceeded = 2,
    externalTrunkLimitExceeded = 3,
    outstandingRequestLimitExceeded = 4
  };

    static const char* EnumText( AsnIntType value );

  void Print ( CTsvcLIB::LOG& os ) const;
};


/* ENUMERATED { generic (1), performanceLimitExceeded (2) } */
class PerformanceManagement: public AsnEnum
{
public:
  PerformanceManagement( MemBlock* mb ): AsnEnum( mb ) {}
  PerformanceManagement( MemBlock* mb, int i ): AsnEnum( mb, i ) {}
  enum
  {
    generic = 1,
    performanceLimitExceeded = 2
  };

    static const char* EnumText( AsnIntType value );

  void Print ( CTsvcLIB::LOG& os ) const;
};


/* ENUMERATED { unspecified (0), sequenceNumberViolated (1), timeStampViolated (2), pACViolated (3), sealViolated (4) } */
class SecurityError: public AsnEnum
{
public:
  SecurityError( MemBlock* mb ): AsnEnum( mb ) {}
  SecurityError( MemBlock* mb, int i ): AsnEnum( mb, i ) {}
  enum
  {
    unspecified = 0,
    sequenceNumberViolated = 1,
    timeStampViolated = 2,
    pACViolated = 3,
    sealViolated = 4
  };

    static const char* EnumText( AsnIntType value );

  void Print ( CTsvcLIB::LOG& os ) const;
};


/* ENUMERATED { activeMonitor (1), alternate (2), busy (3), callBack (4), callCancelled (5), callForwardAlways (6), callForwardBusy (7), callForwardNoAnswer (8), callForward (9), callNotAnswered (10), callPickup (11), campOn (12), destNotObtainable (13), doNotDisturb (14), incompatibleDestination (15), invalidAccountCode (16), keyConference (17), lockout (18), maintenance (19), networkCongestion (20), networkNotObtainable (21), newCall (22), noAvailableAgents (23), override (24), park (25), overflow (26), recall (27), redirected (28), reorderTone (29), resourcesNotAvailable (30), silentParticipation (31), transfer (32), trunksBusy (33), voiceUnitInitiator (34) } */
class EventCause: public AsnEnum
{
public:
  EventCause( MemBlock* mb ): AsnEnum( mb ) {}
  EventCause( MemBlock* mb, int i ): AsnEnum( mb, i ) {}
  enum
  {
    activeMonitor = 1,
    alternate = 2,
    busy = 3,
    callBack = 4,
    callCancelled = 5,
    callForwardAlways = 6,
    callForwardBusy = 7,
    callForwardNoAnswer = 8,
    callForward = 9,
    callNotAnswered = 10,
    callPickup = 11,
    campOn = 12,
    destNotObtainable = 13,
    doNotDisturb = 14,
    incompatibleDestination = 15,
    invalidAccountCode = 16,
    keyConference = 17,
    lockout = 18,
    maintenance = 19,
    networkCongestion = 20,
    networkNotObtainable = 21,
    newCall = 22,
    noAvailableAgents = 23,
    override = 24,
    park = 25,
    overflow = 26,
    recall = 27,
    redirected = 28,
    reorderTone = 29,
    resourcesNotAvailable = 30,
    silentParticipation = 31,
    transfer = 32,
    trunksBusy = 33,
    voiceUnitInitiator = 34
  };

    static const char* EnumText( AsnIntType value );

  void Print ( CTsvcLIB::LOG& os ) const;
};


/* INTEGER*/
typedef AsnInt DeviceNumber;

/* OCTET STRING*/
typedef AsnOcts OtherPlan;

/* [APPLICATION 14] IMPLICIT ENUMERATED { null (0), initiated (1), alerting (2), connected (3), hold (4), queued (5), fail (6) } */
class LocalConnectionState: public AsnEnum
{
public:
  LocalConnectionState( MemBlock* mb ): AsnEnum( mb ) {}
  LocalConnectionState( MemBlock* mb, int i ): AsnEnum( mb, i ) {}
  enum
  {
    null = 0,
    initiated = 1,
    alerting = 2,
    connected = 3,
    hold = 4,
    queued = 5,
    fail = 6
  };

    static const char* EnumText( AsnIntType value );

  void Print ( CTsvcLIB::LOG& os ) const;
  AsnType *Clone() const;

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

};


/* [APPLICATION 21] IMPLICIT OCTET STRING*/
class MonitorCrossRefID: public AsnOcts
{
public:
  MonitorCrossRefID( MemBlock* mb ): AsnOcts( mb ) {}
  MonitorCrossRefID( MemBlock* mb, const uint8* str ): AsnOcts( mb, str ) {}
  MonitorCrossRefID( MemBlock* mb, const uint8* str, const size_t len): AsnOcts( mb, str, len ) {}
  MonitorCrossRefID( MemBlock* mb, const AsnOcts &o ): AsnOcts( mb, o) {}
  MonitorCrossRefID &operator = (const MonitorCrossRefID &o) { ReSet (o); return *this; }
  MonitorCrossRefID &operator = (const uint8* str) { ReSet (str); return *this; }
  MonitorCrossRefID &operator = (const char* str) { ReSet ((uint8*)str); return *this; }
  AsnType *Clone() const;

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

};


/* BIT STRING { callCleared (0), conferenced (1), connectionCleared (2), delivered (3), diverted (4), established (5), failed (6), held (7), networkReached (8), originated (9), queued (10), retrieved (11), serviceInitiated (12), transferred (13) } */
class CallFilter: public AsnBits
{
public:
  //CallFilter( MemBlock* mb ): AsnBits( mb ) {}
  CallFilter( MemBlock* mb, const size_t bits = 14 ): AsnBits( mb, bits ) {}
  CallFilter( MemBlock* mb, const uint8* str, const size_t bitLen ): AsnBits( mb, str, bitLen ) {}
  CallFilter( MemBlock* mb, const AsnBits &b ): AsnBits( mb, b ) {}
  enum
  {
    callCleared = 0,
    conferenced = 1,
    connectionCleared = 2,
    delivered = 3,
    diverted = 4,
    established = 5,
    failed = 6,
    held = 7,
    networkReached = 8,
    originated = 9,
    queued = 10,
    retrieved = 11,
    serviceInitiated = 12,
    transferred = 13
  };
  void Print ( CTsvcLIB::LOG& os ) const;
};


/* BIT STRING { callInformation (0), doNotDisturb (1), forwarding (2), messageWaiting (3) } */
class FeatureFilter: public AsnBits
{
public:
  //FeatureFilter( MemBlock* mb ): AsnBits( mb ) {}
  FeatureFilter( MemBlock* mb, const size_t bits = 4 ): AsnBits( mb, bits ) {}
  FeatureFilter( MemBlock* mb, const uint8* str, const size_t bitLen ): AsnBits( mb, str, bitLen ) {}
  FeatureFilter( MemBlock* mb, const AsnBits &b ): AsnBits( mb, b ) {}
  enum
  {
    callInformation = 0,
    doNotDisturb = 1,
    forwarding = 2,
    messageWaiting = 3
  };
  void Print ( CTsvcLIB::LOG& os ) const;
};


/* BIT STRING { loggedOn (0), loggedOff (1), notReady (2), ready (3), workNotReady (4), workReady (5) } */
class AgentFilter: public AsnBits
{
public:
  //AgentFilter( MemBlock* mb ): AsnBits( mb ) {}
  AgentFilter( MemBlock* mb, const size_t bits = 6 ): AsnBits( mb, bits ) {}
  AgentFilter( MemBlock* mb, const uint8* str, const size_t bitLen ): AsnBits( mb, str, bitLen ) {}
  AgentFilter( MemBlock* mb, const AsnBits &b ): AsnBits( mb, b ) {}
  enum
  {
    loggedOn = 0,
    loggedOff = 1,
    notReady = 2,
    ready = 3,
    workNotReady = 4,
    workReady = 5
  };
  void Print ( CTsvcLIB::LOG& os ) const;
};


/* BIT STRING { backInService (0), outOfService (1) } */
class MaintenanceFilter: public AsnBits
{
public:
  //MaintenanceFilter( MemBlock* mb ): AsnBits( mb ) {}
  MaintenanceFilter( MemBlock* mb, const size_t bits = 2 ): AsnBits( mb, bits ) {}
  MaintenanceFilter( MemBlock* mb, const uint8* str, const size_t bitLen ): AsnBits( mb, str, bitLen ) {}
  MaintenanceFilter( MemBlock* mb, const AsnBits &b ): AsnBits( mb, b ) {}
  enum
  {
    backInService = 0,
    outOfService = 1
  };
  void Print ( CTsvcLIB::LOG& os ) const;
};


/* ENUMERATED { call (0), device (1) } */
class MonitorType: public AsnEnum
{
public:
  MonitorType( MemBlock* mb ): AsnEnum( mb ) {}
  MonitorType( MemBlock* mb, int i ): AsnEnum( mb, i ) {}
  enum
  {
    call = 0,
    device = 1
  };

    static const char* EnumText( AsnIntType value );

  void Print ( CTsvcLIB::LOG& os ) const;
};


/* ENUMERATED { callNull (0), callPending (1), callOriginated (3), callDelivered (35), callDeliveredHeld (36), callReceived (50), callEstablished (51), callEstablishedHeld (52), callReceivedOnHold (66), callEstablishedOnHold (67), callQueued (83), callQueuedHeld (84), callFailed (99), callFailedHeld (100) } */
class SimpleCallState: public AsnEnum
{
public:
  SimpleCallState( MemBlock* mb ): AsnEnum( mb ) {}
  SimpleCallState( MemBlock* mb, int i ): AsnEnum( mb, i ) {}
  enum
  {
    callNull = 0,
    callPending = 1,
    callOriginated = 3,
    callDelivered = 35,
    callDeliveredHeld = 36,
    callReceived = 50,
    callEstablished = 51,
    callEstablishedHeld = 52,
    callReceivedOnHold = 66,
    callEstablishedOnHold = 67,
    callQueued = 83,
    callQueuedHeld = 84,
    callFailed = 99,
    callFailedHeld = 100
  };

    static const char* EnumText( AsnIntType value );

  void Print ( CTsvcLIB::LOG& os ) const;
};


/* OCTET STRING*/
typedef AsnOcts AccountInfo;

/* OCTET STRING*/
typedef AsnOcts AgentID;

/* OCTET STRING*/
typedef AsnOcts AgentPassword;

/* ENUMERATED { notReady (0), null (1), ready (2), workNotReady (3), workReady (4) } */
class AgentState: public AsnEnum
{
public:
  AgentState( MemBlock* mb ): AsnEnum( mb ) {}
  AgentState( MemBlock* mb, int i ): AsnEnum( mb, i ) {}
  enum
  {
    notReady = 0,
    null = 1,
    ready = 2,
    workNotReady = 3,
    workReady = 4
  };

    static const char* EnumText( AsnIntType value );

  void Print ( CTsvcLIB::LOG& os ) const;
};


/* ENUMERATED { callDelivered (0), callEstablished (1) } */
class AllocationState: public AsnEnum
{
public:
  AllocationState( MemBlock* mb ): AsnEnum( mb ) {}
  AllocationState( MemBlock* mb, int i ): AsnEnum( mb, i ) {}
  enum
  {
    callDelivered = 0,
    callEstablished = 1
  };

    static const char* EnumText( AsnIntType value );

  void Print ( CTsvcLIB::LOG& os ) const;
};


/* OCTET STRING*/
typedef AsnOcts AuthCode;

/* BIT STRING { voice (0), data (1), image (2), other (3) } */
class DeviceClass: public AsnBits
{
public:
  //DeviceClass( MemBlock* mb ): AsnBits( mb ) {}
  DeviceClass( MemBlock* mb, const size_t bits = 4 ): AsnBits( mb, bits ) {}
  DeviceClass( MemBlock* mb, const uint8* str, const size_t bitLen ): AsnBits( mb, str, bitLen ) {}
  DeviceClass( MemBlock* mb, const AsnBits &b ): AsnBits( mb, b ) {}
  enum
  {
    voice = 0,
    data = 1,
    image = 2,
    other = 3
  };
  void Print ( CTsvcLIB::LOG& os ) const;
};


/* ENUMERATED { station (0), line (1), button (2), aCD (3), trunk (4), operator1 (5), station_group (16), line_group (17), button_group (18), aCD_group (19), trunk_group (20), operator_group (21), other (255) } */
class DeviceType: public AsnEnum
{
public:
  DeviceType( MemBlock* mb ): AsnEnum( mb ) {}
  DeviceType( MemBlock* mb, int i ): AsnEnum( mb, i ) {}
  enum
  {
    station = 0,
    line = 1,
    button = 2,
    aCD = 3,
    trunk = 4,
    operator1 = 5,
    station_group = 16,
    line_group = 17,
    button_group = 18,
    aCD_group = 19,
    trunk_group = 20,
    operator_group = 21,
    other = 255
  };

    static const char* EnumText( AsnIntType value );

  void Print ( CTsvcLIB::LOG& os ) const;
};


/* ENUMERATED { forwardImmediateOn (0), forwardImmediateOff (1), forwardBusyOn (2), forwardBusyOff (3), forwardNoAnsOn (4), forwardNoAnsOff (5), forwardBusyIntOn (6), forwardBusyIntOff (7), forwardBusyExtOn (8), forwardBusyExtOff (9), forwardNoAnsIntOn (10), forwardNoAnsIntOff (11), forwardNoAnsExtOn (12), forwardNoAnsExtOff (13) } */
class ForwardingType: public AsnEnum
{
public:
  ForwardingType( MemBlock* mb ): AsnEnum( mb ) {}
  ForwardingType( MemBlock* mb, int i ): AsnEnum( mb, i ) {}
  enum
  {
    forwardImmediateOn = 0,
    forwardImmediateOff = 1,
    forwardBusyOn = 2,
    forwardBusyOff = 3,
    forwardNoAnsOn = 4,
    forwardNoAnsOff = 5,
    forwardBusyIntOn = 6,
    forwardBusyIntOff = 7,
    forwardBusyExtOn = 8,
    forwardBusyExtOff = 9,
    forwardNoAnsIntOn = 10,
    forwardNoAnsIntOff = 11,
    forwardNoAnsExtOn = 12,
    forwardNoAnsExtOff = 13
  };

    static const char* EnumText( AsnIntType value );

  void Print ( CTsvcLIB::LOG& os ) const;
};


/* INTEGER*/
typedef AsnInt NoOfCallsInQueue;

/* ENUMERATED { msgWaitingOn (0), doNotDisturbOn (1), forward (2), lastDialedNumber (3), deviceInfo (4), agentState (5), routingEnabled (6), autoAnswer (7), microphoneMuteOn (8), speakerMuteOn (9), speakerVolume (10) } */
class QueryDeviceFeature: public AsnEnum
{
public:
  QueryDeviceFeature( MemBlock* mb ): AsnEnum( mb ) {}
  QueryDeviceFeature( MemBlock* mb, int i ): AsnEnum( mb, i ) {}
  enum
  {
    msgWaitingOn = 0,
    doNotDisturbOn = 1,
    forward = 2,
    lastDialedNumber = 3,
    deviceInfo = 4,
    agentState = 5,
    routingEnabled = 6,
    autoAnswer = 7,
    microphoneMuteOn = 8,
    speakerMuteOn = 9,
    speakerVolume = 10
  };

    static const char* EnumText( AsnIntType value );

  void Print ( CTsvcLIB::LOG& os ) const;
};


/* BOOLEAN*/
typedef AsnBool ReserveConnection;

/* ENUMERATED { initializing (0), enabled (1), normal (2), messagesLost (3), disabled (4), overloadImminent (5), overloadReached (6), overloadRelieved (7) } */
class SystemStatus: public AsnEnum
{
public:
  SystemStatus( MemBlock* mb ): AsnEnum( mb ) {}
  SystemStatus( MemBlock* mb, int i ): AsnEnum( mb, i ) {}
  enum
  {
    initializing = 0,
    enabled = 1,
    normal = 2,
    messagesLost = 3,
    disabled = 4,
    overloadImminent = 5,
    overloadReached = 6,
    overloadRelieved = 7
  };

    static const char* EnumText( AsnIntType value );

  void Print ( CTsvcLIB::LOG& os ) const;
};


/* ENUMERATED { normal (0), leastCost (1), emergency (2), aCD (3), userDefined (4) } */
class SelectValue: public AsnEnum
{
public:
  SelectValue( MemBlock* mb ): AsnEnum( mb ) {}
  SelectValue( MemBlock* mb, int i ): AsnEnum( mb, i ) {}
  enum
  {
    normal = 0,
    leastCost = 1,
    emergency = 2,
    aCD = 3,
    userDefined = 4
  };

    static const char* EnumText( AsnIntType value );

  void Print ( CTsvcLIB::LOG& os ) const;
};


/* BOOLEAN*/
typedef AsnBool PriorityValue;

/* OCTET STRING*/
typedef AsnOcts SetUpValues;

/* BOOLEAN*/
typedef AsnBool RouteUsedFlag;

/* BOOLEAN*/
typedef AsnBool DomainValue;

/* [APPLICATION 24] IMPLICIT OCTET STRING*/
class RoutingCrossRefID: public AsnOcts
{
public:
  RoutingCrossRefID( MemBlock* mb ): AsnOcts( mb ) {}
  RoutingCrossRefID( MemBlock* mb, const uint8* str ): AsnOcts( mb, str ) {}
  RoutingCrossRefID( MemBlock* mb, const uint8* str, const size_t len): AsnOcts( mb, str, len ) {}
  RoutingCrossRefID( MemBlock* mb, const AsnOcts &o ): AsnOcts( mb, o) {}
  RoutingCrossRefID &operator = (const RoutingCrossRefID &o) { ReSet (o); return *this; }
  RoutingCrossRefID &operator = (const uint8* str) { ReSet (str); return *this; }
  RoutingCrossRefID &operator = (const char* str) { ReSet ((uint8*)str); return *this; }
  AsnType *Clone() const;

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

};


/* INTEGER { alternateCall (1), answerCall (2), callCompletion (3), clearCall (4), clearConnection (5), conferenceCall (6), consultationCall (7), divertCall (8), holdCall (9), makeCall (10), makePredictiveCall (11), queryDevice (12), reconnectCall (13), retrieveCall (14), setFeature (15), transferCall (16), cSTAEventReport (21), routeRequest (31), reRouteRequest (32), routeSelectRequest (33), routeUsedRequest (34), routeEndRequest (35), escapeService (51), systemStatus (52), monitorStart (71), changeMonitorFilter (72), monitorStop (73), snapshotDevice (74), snapshotCall (75) } */
class OperationIDType: public AsnInt
{
public:
  OperationIDType( MemBlock* mb ): AsnInt( mb ) {}
  OperationIDType( MemBlock* mb, int i ): AsnInt( mb, i ) {}
  enum
  {
    alternateCall = 1,
    answerCall = 2,
    callCompletion = 3,
    clearCall = 4,
    clearConnection = 5,
    conferenceCall = 6,
    consultationCall = 7,
    divertCall = 8,
    holdCall = 9,
    makeCall = 10,
    makePredictiveCall = 11,
    queryDevice = 12,
    reconnectCall = 13,
    retrieveCall = 14,
    setFeature = 15,
    transferCall = 16,
    cSTAEventReport = 21,
    routeRequest = 31,
    reRouteRequest = 32,
    routeSelectRequest = 33,
    routeUsedRequest = 34,
    routeEndRequest = 35,
    escapeService = 51,
    systemStatus = 52,
    monitorStart = 71,
    changeMonitorFilter = 72,
    monitorStop = 73,
    snapshotDevice = 74,
    snapshotCall = 75
  };

    static const char* EnumText( AsnIntType value );

  void Print ( CTsvcLIB::LOG& os ) const;
};


/* INTEGER { universalFailure (1) } */
class ErrorIDType: public AsnInt
{
public:
  ErrorIDType( MemBlock* mb ): AsnInt( mb ) {}
  ErrorIDType( MemBlock* mb, int i ): AsnInt( mb, i ) {}
  enum
  {
    universalFailure = 1
  };

    static const char* EnumText( AsnIntType value );

  void Print ( CTsvcLIB::LOG& os ) const;
};


/* INTEGER { callCleared (1), conferenced (2), connectionCleared (3), delivered (4), diverted (5), established (6), failed (7), held (8), networkReached (9), originated (10), queued (11), retrieved (12), serviceInitiated (13), transferred (14), callInformation (101), doNotDisturb (102), forwarding (103), messageWaiting (104), loggedOn (201), loggedOff (202), notReady (203), ready (204), workNotReady (205), workReady (206), backInService (301), outOfService (302), privateEvt (401) } */
class EventIDType: public AsnInt
{
public:
  EventIDType( MemBlock* mb ): AsnInt( mb ) {}
  EventIDType( MemBlock* mb, int i ): AsnInt( mb, i ) {}
  enum
  {
    callCleared = 1,
    conferenced = 2,
    connectionCleared = 3,
    delivered = 4,
    diverted = 5,
    established = 6,
    failed = 7,
    held = 8,
    networkReached = 9,
    originated = 10,
    queued = 11,
    retrieved = 12,
    serviceInitiated = 13,
    transferred = 14,
    callInformation = 101,
    doNotDisturb = 102,
    forwarding = 103,
    messageWaiting = 104,
    loggedOn = 201,
    loggedOff = 202,
    notReady = 203,
    ready = 204,
    workNotReady = 205,
    workReady = 206,
    backInService = 301,
    outOfService = 302,
    privateEvt = 401
  };

    static const char* EnumText( AsnIntType value );

  void Print ( CTsvcLIB::LOG& os ) const;
};


/* IA5String*/
typedef IA5String NumberDigits;

class PublicTON : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     unknownCid = 0,
     internationalCid = 1,
     nationalCid = 2,
     networkspecificCid = 3,
     subscriberCid = 4,
     abbreviatedCid = 5
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     IA5String* unknown;
     IA5String* international;
     IA5String* national;
     IA5String* networkspecific;
     IA5String* subscriber;
     IA5String* abbreviated;
  };


  PublicTON( MemBlock* mb );
  PublicTON( MemBlock* mb, const PublicTON &);
  ~PublicTON();

  AsnType *Clone() const;

  PublicTON &operator = (const PublicTON &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class PrivateTON : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     unknownCid = 0,
     level3RegionalNumberCid = 1,
     level2RegionalNumberCid = 2,
     level1RegionalNumberCid = 3,
     pTNSpecificNumberCid = 4,
     localNumberCid = 5,
     abbreviatedCid = 6
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     IA5String* unknown;
     IA5String* level3RegionalNumber;
     IA5String* level2RegionalNumber;
     IA5String* level1RegionalNumber;
     IA5String* pTNSpecificNumber;
     IA5String* localNumber;
     IA5String* abbreviated;
  };


  PrivateTON( MemBlock* mb );
  PrivateTON( MemBlock* mb, const PrivateTON &);
  ~PrivateTON();

  AsnType *Clone() const;

  PrivateTON &operator = (const PrivateTON &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class RetryValue : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     noListAvailableCid = 0,
     noCountAvailableCid = 1,
     retryCountCid = 2
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     AsnBool* noListAvailable;
     AsnBool* noCountAvailable;
     AsnInt* retryCount;
  };


  RetryValue( MemBlock* mb );
  RetryValue( MemBlock* mb, const RetryValue &);
  ~RetryValue();

  AsnType *Clone() const;

  RetryValue &operator = (const RetryValue &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class Seal : public AsnType
{
public:
  AsnOid algorithmIdentifier;
  AsnOcts keyIdentifier;
  AsnOcts seal;

 Seal( MemBlock* mb );
 Seal ( MemBlock* mb, const Seal & );
 ~Seal();
  AsnType *Clone() const;

  Seal &operator = (const Seal &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class CSTAPrivateData : public AsnType
{
public:
  AsnOid manufacturer;
  PrivateAnyData data;

 CSTAPrivateData( MemBlock* mb );
 CSTAPrivateData ( MemBlock* mb, const CSTAPrivateData & );
 ~CSTAPrivateData();
  AsnType *Clone() const;

  CSTAPrivateData &operator = (const CSTAPrivateData &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class CSTACommonArgumentsSeqOf : public AsnType
{
protected:
  unsigned long int count;
  struct AsnListElmt
  {
    AsnListElmt *next;
    AsnListElmt *prev;
    CSTAPrivateData *elmt;
    void* operator new( size_t n, MemBlock* memblock ) { return memblock->Allocate( n ); }
    void operator delete( void* p, MemBlock* memblock ) { /* nothing to do */ }
    void operator delete( void* p ) { /* nothing to do */ }
  } *first, *curr, *last;

public:
  CSTACommonArgumentsSeqOf( MemBlock* mb ) : AsnType( mb ) { count = 0; first = curr = last = NULL; }
  CSTACommonArgumentsSeqOf( MemBlock* mb, const CSTACommonArgumentsSeqOf &);
  ~CSTACommonArgumentsSeqOf();
  AsnType *Clone() const;

  CSTACommonArgumentsSeqOf &operator = (const CSTACommonArgumentsSeqOf &);
  void SetCurrElmt (unsigned long int index);
  unsigned long int GetCurrElmtIndex();
  void SetCurrToFirst() { curr = first; }
  void SetCurrToLast()  { curr = last; }
  // reading member fcns
  int Count() const { return count; }
  CSTAPrivateData *First() const { return count > 0 ? first->elmt : NULL; }
  CSTAPrivateData *Last() const { return count > 0 ? last->elmt : NULL; }
  CSTAPrivateData *Curr() const { return curr ? curr->elmt : NULL; }
  CSTAPrivateData *Next() const { return curr && curr->next ? curr->next->elmt : NULL; }
  CSTAPrivateData *Prev() const { return curr && curr->prev ? curr->prev->elmt : NULL; }

  // routines that move the curr elmt
  CSTAPrivateData *GoNext() { if (curr) curr = curr->next; return Curr(); }
  CSTAPrivateData *GoPrev() { if (curr) curr = curr->prev; return Curr(); }

  // write & alloc fcns - returns new elmt
  CSTAPrivateData *Append();  // add elmt to end of list
  CSTAPrivateData *Prepend(); // add elmt to beginning of list
  CSTAPrivateData *InsertBefore(); //insert elmt before current elmt
  CSTAPrivateData *InsertAfter(); //insert elmt after current elmt

  // write & alloc & copy - returns list after copying elmt
  CSTACommonArgumentsSeqOf &AppendCopy (CSTAPrivateData &elmt);  // add elmt to end of list
  CSTACommonArgumentsSeqOf &PrependCopy (CSTAPrivateData &elmt); // add elmt to beginning of list
  CSTACommonArgumentsSeqOf &InsertBeforeAndCopy (CSTAPrivateData &elmt); //insert elmt before current elmt
  CSTACommonArgumentsSeqOf &InsertAfterAndCopy (CSTAPrivateData &elmt); //insert elmt after current elmt

  // removing the current elmt from the list
  void RemoveCurrFromList();

  // encode and decode routines    
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  PDU_MEMBER_MACROS
  void Print ( CTsvcLIB::LOG& os ) const;
};


class ListForwardParametersSeq : public AsnType
{
public:
  ForwardingType forwardingType;
  NumberDigits forwardDN;

 ListForwardParametersSeq( MemBlock* mb );
 ListForwardParametersSeq ( MemBlock* mb, const ListForwardParametersSeq & );
 ~ListForwardParametersSeq();
  AsnType *Clone() const;

  ListForwardParametersSeq &operator = (const ListForwardParametersSeq &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class RORJapduChoice1 : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     generalProblemCid = 0,
     invokeProblemCid = 1,
     returnResultProblemCid = 2,
     returnErrorProblemCid = 3
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     GeneralProblem* generalProblem;
     InvokeProblem* invokeProblem;
     ReturnResultProblem* returnResultProblem;
     ReturnErrorProblem* returnErrorProblem;
  };


  RORJapduChoice1( MemBlock* mb );
  RORJapduChoice1( MemBlock* mb, const RORJapduChoice1 &);
  ~RORJapduChoice1();

  AsnType *Clone() const;

  RORJapduChoice1 &operator = (const RORJapduChoice1 &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class RORJapduChoice : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     invokeIDTypeCid = 0,
     nullCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     InvokeIDType* invokeIDType;
     AsnNull* null;
  };


  RORJapduChoice( MemBlock* mb );
  RORJapduChoice( MemBlock* mb, const RORJapduChoice &);
  ~RORJapduChoice();

  AsnType *Clone() const;

  RORJapduChoice &operator = (const RORJapduChoice &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class RORSapduSeq : public AsnType
{
public:
  OperationIDType operationValue;
  OperationResult* result;

 RORSapduSeq( MemBlock* mb );
 RORSapduSeq ( MemBlock* mb, const RORSapduSeq & );
 ~RORSapduSeq();
  AsnType *Clone() const;

  RORSapduSeq &operator = (const RORSapduSeq &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ROIVapdu : public AsnType
{
public:
  InvokeIDType invokeID;
  InvokedIDType* linkedID;
  OperationIDType operationValue;
  OperationArgument* argument;

 ROIVapdu( MemBlock* mb );
 ROIVapdu ( MemBlock* mb, const ROIVapdu & );
 ~ROIVapdu();
  AsnType *Clone() const;

  ROIVapdu &operator = (const ROIVapdu &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class RORSapdu : public AsnType
{
public:
  InvokeIDType invokeID;
  RORSapduSeq* rORSapduSeq;

 RORSapdu( MemBlock* mb );
 RORSapdu ( MemBlock* mb, const RORSapdu & );
 ~RORSapdu();
  AsnType *Clone() const;

  RORSapdu &operator = (const RORSapdu &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ROERapdu : public AsnType
{
public:
  InvokedIDType invokedID;
  ErrorIDType errorValue;
  ErrorParameter* parameter;

 ROERapdu( MemBlock* mb );
 ROERapdu ( MemBlock* mb, const ROERapdu & );
 ~ROERapdu();
  AsnType *Clone() const;

  ROERapdu &operator = (const ROERapdu &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class RORJapdu : public AsnType
{
public:
  RORJapduChoice* invokeID;
  RORJapduChoice1* problem;

 RORJapdu( MemBlock* mb );
 RORJapdu ( MemBlock* mb, const RORJapdu & );
 ~RORJapdu();
  AsnType *Clone() const;

  RORJapdu &operator = (const RORJapdu &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class AlternateCallResult : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     extensionsCid = 0,
     noDataCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     CSTAPrivateData* extensions;
     AsnNull* noData;
  };


  AlternateCallResult( MemBlock* mb );
  AlternateCallResult( MemBlock* mb, const AlternateCallResult &);
  ~AlternateCallResult();

  AsnType *Clone() const;

  AlternateCallResult &operator = (const AlternateCallResult &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class AnswerCallResult : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     extensionsCid = 0,
     noDataCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     CSTAPrivateData* extensions;
     AsnNull* noData;
  };


  AnswerCallResult( MemBlock* mb );
  AnswerCallResult( MemBlock* mb, const AnswerCallResult &);
  ~AnswerCallResult();

  AsnType *Clone() const;

  AnswerCallResult &operator = (const AnswerCallResult &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class CallCompletionResult : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     extensionsCid = 0,
     noDataCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     CSTAPrivateData* extensions;
     AsnNull* noData;
  };


  CallCompletionResult( MemBlock* mb );
  CallCompletionResult( MemBlock* mb, const CallCompletionResult &);
  ~CallCompletionResult();

  AsnType *Clone() const;

  CallCompletionResult &operator = (const CallCompletionResult &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ClearCallResult : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     extensionsCid = 0,
     noDataCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     CSTAPrivateData* extensions;
     AsnNull* noData;
  };


  ClearCallResult( MemBlock* mb );
  ClearCallResult( MemBlock* mb, const ClearCallResult &);
  ~ClearCallResult();

  AsnType *Clone() const;

  ClearCallResult &operator = (const ClearCallResult &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ClearConnectionResult : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     extensionsCid = 0,
     noDataCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     CSTAPrivateData* extensions;
     AsnNull* noData;
  };


  ClearConnectionResult( MemBlock* mb );
  ClearConnectionResult( MemBlock* mb, const ClearConnectionResult &);
  ~ClearConnectionResult();

  AsnType *Clone() const;

  ClearConnectionResult &operator = (const ClearConnectionResult &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class DivertCallResult : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     extensionsCid = 0,
     noDataCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     CSTAPrivateData* extensions;
     AsnNull* noData;
  };


  DivertCallResult( MemBlock* mb );
  DivertCallResult( MemBlock* mb, const DivertCallResult &);
  ~DivertCallResult();

  AsnType *Clone() const;

  DivertCallResult &operator = (const DivertCallResult &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class HoldCallResult : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     extensionsCid = 0,
     noDataCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     CSTAPrivateData* extensions;
     AsnNull* noData;
  };


  HoldCallResult( MemBlock* mb );
  HoldCallResult( MemBlock* mb, const HoldCallResult &);
  ~HoldCallResult();

  AsnType *Clone() const;

  HoldCallResult &operator = (const HoldCallResult &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ReconnectCallResult : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     extensionsCid = 0,
     noDataCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     CSTAPrivateData* extensions;
     AsnNull* noData;
  };


  ReconnectCallResult( MemBlock* mb );
  ReconnectCallResult( MemBlock* mb, const ReconnectCallResult &);
  ~ReconnectCallResult();

  AsnType *Clone() const;

  ReconnectCallResult &operator = (const ReconnectCallResult &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class RetrieveCallResult : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     extensionsCid = 0,
     noDataCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     CSTAPrivateData* extensions;
     AsnNull* noData;
  };


  RetrieveCallResult( MemBlock* mb );
  RetrieveCallResult( MemBlock* mb, const RetrieveCallResult &);
  ~RetrieveCallResult();

  AsnType *Clone() const;

  RetrieveCallResult &operator = (const RetrieveCallResult &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class SetFeatureResult : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     extensionsCid = 0,
     noDataCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     CSTAPrivateData* extensions;
     AsnNull* noData;
  };


  SetFeatureResult( MemBlock* mb );
  SetFeatureResult( MemBlock* mb, const SetFeatureResult &);
  ~SetFeatureResult();

  AsnType *Clone() const;

  SetFeatureResult &operator = (const SetFeatureResult &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class EventTypeID : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     cCSTAformCid = 0
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     EventIDType* cCSTAform;
  };


  EventTypeID( MemBlock* mb );
  EventTypeID( MemBlock* mb, const EventTypeID &);
  ~EventTypeID();

  AsnType *Clone() const;

  EventTypeID &operator = (const EventTypeID &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class CSTAEventReportArgument : public AsnType
{
public:
  MonitorCrossRefID crossRefIdentifier;
  EventTypeID* eventType;
  EventInfo eventInfo;
  CSTAPrivateData* extensions;

 CSTAEventReportArgument( MemBlock* mb );
 CSTAEventReportArgument ( MemBlock* mb, const CSTAEventReportArgument & );
 ~CSTAEventReportArgument();
  AsnType *Clone() const;

  CSTAEventReportArgument &operator = (const CSTAEventReportArgument &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class EscapeServiceResult : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     extensionsCid = 0,
     noDataCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     CSTAPrivateData* extensions;
     AsnNull* noData;
  };


  EscapeServiceResult( MemBlock* mb );
  EscapeServiceResult( MemBlock* mb, const EscapeServiceResult &);
  ~EscapeServiceResult();

  AsnType *Clone() const;

  EscapeServiceResult &operator = (const EscapeServiceResult &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class SystemStatusResult : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     extensionsCid = 0,
     noDataCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     CSTAPrivateData* extensions;
     AsnNull* noData;
  };


  SystemStatusResult( MemBlock* mb );
  SystemStatusResult( MemBlock* mb, const SystemStatusResult &);
  ~SystemStatusResult();

  AsnType *Clone() const;

  SystemStatusResult &operator = (const SystemStatusResult &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class MonitorStopResult : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     extensionsCid = 0,
     noDataCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     CSTAPrivateData* extensions;
     AsnNull* noData;
  };


  MonitorStopResult( MemBlock* mb );
  MonitorStopResult( MemBlock* mb, const MonitorStopResult &);
  ~MonitorStopResult();

  AsnType *Clone() const;

  MonitorStopResult &operator = (const MonitorStopResult &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class UniversalFailure : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     operationalErrorsCid = 0,
     stateErrorsCid = 1,
     systemResourceErrorsCid = 2,
     subscribedResourceAvailabilityErrorsCid = 3,
     performanceErrorsCid = 4,
     securityErrorsCid = 5,
     unspecifiedErrorsCid = 6,
     nonStandardErrorsCid = 7
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     Operations* operationalErrors;
     StateIncompatibility* stateErrors;
     SystemResourceAvailability* systemResourceErrors;
     SubscribedResourceAvailability* subscribedResourceAvailabilityErrors;
     PerformanceManagement* performanceErrors;
     SecurityError* securityErrors;
     AsnNull* unspecifiedErrors;
     CSTAPrivateData* nonStandardErrors;
  };


  UniversalFailure( MemBlock* mb );
  UniversalFailure( MemBlock* mb, const UniversalFailure &);
  ~UniversalFailure();

  AsnType *Clone() const;

  UniversalFailure &operator = (const UniversalFailure &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class DeviceID : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     dialingNumberCid = 0,
     deviceNumberCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     NumberDigits* dialingNumber;
     DeviceNumber* deviceNumber;
  };


  DeviceID( MemBlock* mb );
  DeviceID( MemBlock* mb, const DeviceID &);
  ~DeviceID();

  AsnType *Clone() const;

  DeviceID &operator = (const DeviceID &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ExtendedDeviceID : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     dialingNumberCid = 0,
     deviceNumberCid = 1,
     implicitPublicCid = 2,
     explicitPublicCid = 3,
     implicitPrivateCid = 4,
     explicitPrivateCid = 5,
     otherCid = 6
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     NumberDigits* dialingNumber;
     DeviceNumber* deviceNumber;
     NumberDigits* implicitPublic;
     PublicTON* explicitPublic;
     NumberDigits* implicitPrivate;
     PrivateTON* explicitPrivate;
     OtherPlan* other;
  };


  ExtendedDeviceID( MemBlock* mb );
  ExtendedDeviceID( MemBlock* mb, const ExtendedDeviceID &);
  ~ExtendedDeviceID();

  AsnType *Clone() const;

  ExtendedDeviceID &operator = (const ExtendedDeviceID &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class CallingDeviceID : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     deviceIdentifierCid = 0,
     notKnownCid = 1,
     notRequiredCid = 2
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     ExtendedDeviceID* deviceIdentifier;
     AsnNull* notKnown;
     AsnNull* notRequired;
  };


  CallingDeviceID( MemBlock* mb );
  CallingDeviceID( MemBlock* mb, const CallingDeviceID &);
  ~CallingDeviceID();

  AsnType *Clone() const;

  CallingDeviceID &operator = (const CallingDeviceID &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class CalledDeviceID : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     deviceIdentifierCid = 0,
     notKnownCid = 1,
     notRequiredCid = 2
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     ExtendedDeviceID* deviceIdentifier;
     AsnNull* notKnown;
     AsnNull* notRequired;
  };


  CalledDeviceID( MemBlock* mb );
  CalledDeviceID( MemBlock* mb, const CalledDeviceID &);
  ~CalledDeviceID();

  AsnType *Clone() const;

  CalledDeviceID &operator = (const CalledDeviceID &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class SubjectDeviceID : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     deviceIdentifierCid = 0,
     notKnownCid = 1,
     notRequiredCid = 2
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     ExtendedDeviceID* deviceIdentifier;
     AsnNull* notKnown;
     AsnNull* notRequired;
  };


  SubjectDeviceID( MemBlock* mb );
  SubjectDeviceID( MemBlock* mb, const SubjectDeviceID &);
  ~SubjectDeviceID();

  AsnType *Clone() const;

  SubjectDeviceID &operator = (const SubjectDeviceID &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class RedirectionDeviceID : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     numberDialedCid = 0,
     notKnownCid = 1,
     notRequiredCid = 2
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     DeviceID* numberDialed;
     AsnNull* notKnown;
     AsnNull* notRequired;
  };


  RedirectionDeviceID( MemBlock* mb );
  RedirectionDeviceID( MemBlock* mb, const RedirectionDeviceID &);
  ~RedirectionDeviceID();

  AsnType *Clone() const;

  RedirectionDeviceID &operator = (const RedirectionDeviceID &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class MonitorFilter : public AsnType
{
public:
  CallFilter* call;
  FeatureFilter* feature;
  AgentFilter* agent;
  MaintenanceFilter* maintenance;
  AsnBool* private1;

 MonitorFilter( MemBlock* mb );
 MonitorFilter ( MemBlock* mb, const MonitorFilter & );
 ~MonitorFilter();
  AsnType *Clone() const;

  MonitorFilter &operator = (const MonitorFilter &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class CompoundCallState : public AsnType
{
protected:
  unsigned long int count;
  struct AsnListElmt
  {
    AsnListElmt *next;
    AsnListElmt *prev;
    LocalConnectionState *elmt;
    void* operator new( size_t n, MemBlock* memblock ) { return memblock->Allocate( n ); }
    void operator delete( void* p, MemBlock* memblock ) { /* nothing to do */ }
    void operator delete( void* p ) { /* nothing to do */ }
  } *first, *curr, *last;

public:
  CompoundCallState( MemBlock* mb ) : AsnType( mb ) { count = 0; first = curr = last = NULL; }
  CompoundCallState( MemBlock* mb, const CompoundCallState &);
  ~CompoundCallState();
  AsnType *Clone() const;

  CompoundCallState &operator = (const CompoundCallState &);
  void SetCurrElmt (unsigned long int index);
  unsigned long int GetCurrElmtIndex();
  void SetCurrToFirst() { curr = first; }
  void SetCurrToLast()  { curr = last; }
  // reading member fcns
  int Count() const { return count; }
  LocalConnectionState *First() const { return count > 0 ? first->elmt : NULL; }
  LocalConnectionState *Last() const { return count > 0 ? last->elmt : NULL; }
  LocalConnectionState *Curr() const { return curr ? curr->elmt : NULL; }
  LocalConnectionState *Next() const { return curr && curr->next ? curr->next->elmt : NULL; }
  LocalConnectionState *Prev() const { return curr && curr->prev ? curr->prev->elmt : NULL; }

  // routines that move the curr elmt
  LocalConnectionState *GoNext() { if (curr) curr = curr->next; return Curr(); }
  LocalConnectionState *GoPrev() { if (curr) curr = curr->prev; return Curr(); }

  // write & alloc fcns - returns new elmt
  LocalConnectionState *Append();  // add elmt to end of list
  LocalConnectionState *Prepend(); // add elmt to beginning of list
  LocalConnectionState *InsertBefore(); //insert elmt before current elmt
  LocalConnectionState *InsertAfter(); //insert elmt after current elmt

  // write & alloc & copy - returns list after copying elmt
  CompoundCallState &AppendCopy (LocalConnectionState &elmt);  // add elmt to end of list
  CompoundCallState &PrependCopy (LocalConnectionState &elmt); // add elmt to beginning of list
  CompoundCallState &InsertBeforeAndCopy (LocalConnectionState &elmt); //insert elmt before current elmt
  CompoundCallState &InsertAfterAndCopy (LocalConnectionState &elmt); //insert elmt after current elmt

  // removing the current elmt from the list
  void RemoveCurrFromList();

  // encode and decode routines    
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  PDU_MEMBER_MACROS
  void Print ( CTsvcLIB::LOG& os ) const;
};


/* DeviceID*/
typedef DeviceID AgentGroup;

class DeviceInfo : public AsnType
{
public:
  DeviceID* deviceID;
  DeviceType* deviceType;
  DeviceClass* deviceClass;

 DeviceInfo( MemBlock* mb );
 DeviceInfo ( MemBlock* mb, const DeviceInfo & );
 ~DeviceInfo();
  AsnType *Clone() const;

  DeviceInfo &operator = (const DeviceInfo &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ListForwardParameters : public AsnType
{
protected:
  unsigned long int count;
  struct AsnListElmt
  {
    AsnListElmt *next;
    AsnListElmt *prev;
    ListForwardParametersSeq *elmt;
    void* operator new( size_t n, MemBlock* memblock ) { return memblock->Allocate( n ); }
    void operator delete( void* p, MemBlock* memblock ) { /* nothing to do */ }
    void operator delete( void* p ) { /* nothing to do */ }
  } *first, *curr, *last;

public:
  ListForwardParameters( MemBlock* mb ) : AsnType( mb ) { count = 0; first = curr = last = NULL; }
  ListForwardParameters( MemBlock* mb, const ListForwardParameters &);
  ~ListForwardParameters();
  AsnType *Clone() const;

  ListForwardParameters &operator = (const ListForwardParameters &);
  void SetCurrElmt (unsigned long int index);
  unsigned long int GetCurrElmtIndex();
  void SetCurrToFirst() { curr = first; }
  void SetCurrToLast()  { curr = last; }
  // reading member fcns
  int Count() const { return count; }
  ListForwardParametersSeq *First() const { return count > 0 ? first->elmt : NULL; }
  ListForwardParametersSeq *Last() const { return count > 0 ? last->elmt : NULL; }
  ListForwardParametersSeq *Curr() const { return curr ? curr->elmt : NULL; }
  ListForwardParametersSeq *Next() const { return curr && curr->next ? curr->next->elmt : NULL; }
  ListForwardParametersSeq *Prev() const { return curr && curr->prev ? curr->prev->elmt : NULL; }

  // routines that move the curr elmt
  ListForwardParametersSeq *GoNext() { if (curr) curr = curr->next; return Curr(); }
  ListForwardParametersSeq *GoPrev() { if (curr) curr = curr->prev; return Curr(); }

  // write & alloc fcns - returns new elmt
  ListForwardParametersSeq *Append();  // add elmt to end of list
  ListForwardParametersSeq *Prepend(); // add elmt to beginning of list
  ListForwardParametersSeq *InsertBefore(); //insert elmt before current elmt
  ListForwardParametersSeq *InsertAfter(); //insert elmt after current elmt

  // write & alloc & copy - returns list after copying elmt
  ListForwardParameters &AppendCopy (ListForwardParametersSeq &elmt);  // add elmt to end of list
  ListForwardParameters &PrependCopy (ListForwardParametersSeq &elmt); // add elmt to beginning of list
  ListForwardParameters &InsertBeforeAndCopy (ListForwardParametersSeq &elmt); //insert elmt before current elmt
  ListForwardParameters &InsertAfterAndCopy (ListForwardParametersSeq &elmt); //insert elmt after current elmt

  // removing the current elmt from the list
  void RemoveCurrFromList();

  // encode and decode routines    
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  PDU_MEMBER_MACROS
  void Print ( CTsvcLIB::LOG& os ) const;
};


class LoggedOnInfo : public AsnType
{
public:
  AgentID* agentID;
  AgentPassword* password;
  AgentGroup* group;

 LoggedOnInfo( MemBlock* mb );
 LoggedOnInfo ( MemBlock* mb, const LoggedOnInfo & );
 ~LoggedOnInfo();
  AsnType *Clone() const;

  LoggedOnInfo &operator = (const LoggedOnInfo &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class LoggedOffInfo : public AsnType
{
public:
  AgentID* agentID;
  AgentGroup* group;

 LoggedOffInfo( MemBlock* mb );
 LoggedOffInfo ( MemBlock* mb, const LoggedOffInfo & );
 ~LoggedOffInfo();
  AsnType *Clone() const;

  LoggedOffInfo &operator = (const LoggedOffInfo &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ForwardParameter : public AsnType
{
public:
  ForwardingType forwardingType;
  NumberDigits* forwardDN;

 ForwardParameter( MemBlock* mb );
 ForwardParameter ( MemBlock* mb, const ForwardParameter & );
 ~ForwardParameter();
  AsnType *Clone() const;

  ForwardParameter &operator = (const ForwardParameter &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class QueryDeviceInformation : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     msgWaitingOnCid = 0,
     doNotDisturbOnCid = 1,
     forwardCid = 2,
     lastDialedCid = 3,
     deviceInfoCid = 4,
     agentStateCid = 5,
     routingEnabledCid = 6,
     autoAnswerOnCid = 7,
     microphoneMuteOnCid = 8,
     speakerMuteOnCid = 9,
     speakerVolumeCid = 10
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     AsnBool* msgWaitingOn;
     AsnBool* doNotDisturbOn;
     ListForwardParameters* forward;
     NumberDigits* lastDialed;
     DeviceInfo* deviceInfo;
     AgentState* agentState;
     AsnBool* routingEnabled;
     AsnBool* autoAnswerOn;
     AsnBool* microphoneMuteOn;
     AsnBool* speakerMuteOn;
     AsnInt* speakerVolume;
  };


  QueryDeviceInformation( MemBlock* mb );
  QueryDeviceInformation( MemBlock* mb, const QueryDeviceInformation &);
  ~QueryDeviceInformation();

  AsnType *Clone() const;

  QueryDeviceInformation &operator = (const QueryDeviceInformation &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class CSTASecurityData : public AsnType
{
public:
  AsnInt* messageSequenceNumber;
  UTCTime* timeStamp;
  Seal* seal;

 CSTASecurityData( MemBlock* mb );
 CSTASecurityData ( MemBlock* mb, const CSTASecurityData & );
 ~CSTASecurityData();
  AsnType *Clone() const;

  CSTASecurityData &operator = (const CSTASecurityData &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class CSTACommonArguments : public AsnType
{
public:
  CSTASecurityData* security;
  CSTACommonArgumentsSeqOf* privateData;

 CSTACommonArguments( MemBlock* mb );
 CSTACommonArguments ( MemBlock* mb, const CSTACommonArguments & );
 ~CSTACommonArguments();
  AsnType *Clone() const;

  CSTACommonArguments &operator = (const CSTACommonArguments &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ConnectionIDChoice : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     staticIDCid = 0,
     dynamicIDCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     DeviceID* staticID;
     AsnOcts* dynamicID;
  };


  ConnectionIDChoice( MemBlock* mb );
  ConnectionIDChoice( MemBlock* mb, const ConnectionIDChoice &);
  ~ConnectionIDChoice();

  AsnType *Clone() const;

  ConnectionIDChoice &operator = (const ConnectionIDChoice &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class SnapshotDeviceArgumentSeq : public AsnType
{
public:
  DeviceID* snapshotObject;
  CSTACommonArguments* extensions;

 SnapshotDeviceArgumentSeq( MemBlock* mb );
 SnapshotDeviceArgumentSeq ( MemBlock* mb, const SnapshotDeviceArgumentSeq & );
 ~SnapshotDeviceArgumentSeq();
  AsnType *Clone() const;

  SnapshotDeviceArgumentSeq &operator = (const SnapshotDeviceArgumentSeq &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class MonitorStopArgumentSeq : public AsnType
{
public:
  MonitorCrossRefID crossRefIdentifier;
  CSTACommonArguments* extensions;

 MonitorStopArgumentSeq( MemBlock* mb );
 MonitorStopArgumentSeq ( MemBlock* mb, const MonitorStopArgumentSeq & );
 ~MonitorStopArgumentSeq();
  AsnType *Clone() const;

  MonitorStopArgumentSeq &operator = (const MonitorStopArgumentSeq &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ChangeMonitorFilterResultSeq : public AsnType
{
public:
  MonitorFilter* filterList;
  CSTAPrivateData* extensions;

 ChangeMonitorFilterResultSeq( MemBlock* mb );
 ChangeMonitorFilterResultSeq ( MemBlock* mb, const ChangeMonitorFilterResultSeq & );
 ~ChangeMonitorFilterResultSeq();
  AsnType *Clone() const;

  ChangeMonitorFilterResultSeq &operator = (const ChangeMonitorFilterResultSeq &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class SystemStatusArgumentSeq : public AsnType
{
public:
  SystemStatus systemStatus;
  CSTACommonArguments* extensions;

 SystemStatusArgumentSeq( MemBlock* mb );
 SystemStatusArgumentSeq ( MemBlock* mb, const SystemStatusArgumentSeq & );
 ~SystemStatusArgumentSeq();
  AsnType *Clone() const;

  SystemStatusArgumentSeq &operator = (const SystemStatusArgumentSeq &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class QueryDeviceResultSeq : public AsnType
{
public:
  QueryDeviceInformation* deviceInformation;
  CSTAPrivateData* extensions;

 QueryDeviceResultSeq( MemBlock* mb );
 QueryDeviceResultSeq ( MemBlock* mb, const QueryDeviceResultSeq & );
 ~QueryDeviceResultSeq();
  AsnType *Clone() const;

  QueryDeviceResultSeq &operator = (const QueryDeviceResultSeq &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ROSEapdu : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     invokeApduCid = 0,
     resultApduCid = 1,
     errorApduCid = 2,
     rejectApduCid = 3
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     ROIVapdu* invokeApdu;
     RORSapdu* resultApdu;
     ROERapdu* errorApdu;
     RORJapdu* rejectApdu;
  };


  ROSEapdu( MemBlock* mb );
  ROSEapdu( MemBlock* mb, const ROSEapdu &);
  ~ROSEapdu();

  AsnType *Clone() const;

  ROSEapdu &operator = (const ROSEapdu &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class MakeCallArgument : public AsnType
{
public:
  DeviceID* callingDevice;
  CalledDeviceID* calledDirectoryNumber;
  CSTACommonArguments* extensions;

 MakeCallArgument( MemBlock* mb );
 MakeCallArgument ( MemBlock* mb, const MakeCallArgument & );
 ~MakeCallArgument();
  AsnType *Clone() const;

  MakeCallArgument &operator = (const MakeCallArgument &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class MakePredictiveCallArgument : public AsnType
{
public:
  DeviceID* callingDevice;
  CalledDeviceID* calledDirectoryNumber;
  AllocationState* allocation;
  CSTACommonArguments* extensions;

 MakePredictiveCallArgument( MemBlock* mb );
 MakePredictiveCallArgument ( MemBlock* mb, const MakePredictiveCallArgument & );
 ~MakePredictiveCallArgument();
  AsnType *Clone() const;

  MakePredictiveCallArgument &operator = (const MakePredictiveCallArgument &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class QueryDeviceArgument : public AsnType
{
public:
  DeviceID* device;
  QueryDeviceFeature feature;
  CSTACommonArguments* extensions;

 QueryDeviceArgument( MemBlock* mb );
 QueryDeviceArgument ( MemBlock* mb, const QueryDeviceArgument & );
 ~QueryDeviceArgument();
  AsnType *Clone() const;

  QueryDeviceArgument &operator = (const QueryDeviceArgument &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class QueryDeviceResult : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     deviceInformationCid = 0,
     queryDeviceResultSeqCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     QueryDeviceInformation* deviceInformation;
     QueryDeviceResultSeq* queryDeviceResultSeq;
  };


  QueryDeviceResult( MemBlock* mb );
  QueryDeviceResult( MemBlock* mb, const QueryDeviceResult &);
  ~QueryDeviceResult();

  AsnType *Clone() const;

  QueryDeviceResult &operator = (const QueryDeviceResult &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ReRouteRequestArgument : public AsnType
{
public:
  RoutingCrossRefID crossRefIdentifier;
  CSTACommonArguments* extensions;

 ReRouteRequestArgument( MemBlock* mb );
 ReRouteRequestArgument ( MemBlock* mb, const ReRouteRequestArgument & );
 ~ReRouteRequestArgument();
  AsnType *Clone() const;

  ReRouteRequestArgument &operator = (const ReRouteRequestArgument &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class RouteSelectRequestArgument : public AsnType
{
public:
  RoutingCrossRefID crossRefIdentifier;
  CalledDeviceID* routeSelected;
  RetryValue* remainRetry;
  SetUpValues* setupInformation;
  RouteUsedFlag* routeUsedReq;
  CSTACommonArguments* extensions;

 RouteSelectRequestArgument( MemBlock* mb );
 RouteSelectRequestArgument ( MemBlock* mb, const RouteSelectRequestArgument & );
 ~RouteSelectRequestArgument();
  AsnType *Clone() const;

  RouteSelectRequestArgument &operator = (const RouteSelectRequestArgument &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class RouteUsedRequestArgument : public AsnType
{
public:
  RoutingCrossRefID crossRefIdentifier;
  CalledDeviceID* routeUsed;
  CallingDeviceID* callingDevice;
  DomainValue* domain;
  CSTACommonArguments* extensions;

 RouteUsedRequestArgument( MemBlock* mb );
 RouteUsedRequestArgument ( MemBlock* mb, const RouteUsedRequestArgument & );
 ~RouteUsedRequestArgument();
  AsnType *Clone() const;

  RouteUsedRequestArgument &operator = (const RouteUsedRequestArgument &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class RouteEndRequestArgument : public AsnType
{
public:
  RoutingCrossRefID crossRefIdentifier;
  UniversalFailure* errorValue;
  CSTACommonArguments* extensions;

 RouteEndRequestArgument( MemBlock* mb );
 RouteEndRequestArgument ( MemBlock* mb, const RouteEndRequestArgument & );
 ~RouteEndRequestArgument();
  AsnType *Clone() const;

  RouteEndRequestArgument &operator = (const RouteEndRequestArgument &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


/* CSTACommonArguments*/
typedef CSTACommonArguments EscapeServiceArgument;

class SystemStatusArgument : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     systemStatusCid = 0,
     systemStatusArgumentSeqCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     SystemStatus* systemStatus;
     SystemStatusArgumentSeq* systemStatusArgumentSeq;
  };


  SystemStatusArgument( MemBlock* mb );
  SystemStatusArgument( MemBlock* mb, const SystemStatusArgument &);
  ~SystemStatusArgument();

  AsnType *Clone() const;

  SystemStatusArgument &operator = (const SystemStatusArgument &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class MonitorStartResult : public AsnType
{
public:
  MonitorCrossRefID crossRefIdentifier;
  MonitorFilter* monitorFilter;
  CSTAPrivateData* extensions;

 MonitorStartResult( MemBlock* mb );
 MonitorStartResult ( MemBlock* mb, const MonitorStartResult & );
 ~MonitorStartResult();
  AsnType *Clone() const;

  MonitorStartResult &operator = (const MonitorStartResult &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ChangeMonitorFilterArgument : public AsnType
{
public:
  MonitorCrossRefID monitorCrossRefID;
  MonitorFilter* filterlist;
  CSTACommonArguments* extensions;

 ChangeMonitorFilterArgument( MemBlock* mb );
 ChangeMonitorFilterArgument ( MemBlock* mb, const ChangeMonitorFilterArgument & );
 ~ChangeMonitorFilterArgument();
  AsnType *Clone() const;

  ChangeMonitorFilterArgument &operator = (const ChangeMonitorFilterArgument &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ChangeMonitorFilterResult : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     filterListCid = 0,
     changeMonitorFilterResultSeqCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     MonitorFilter* filterList;
     ChangeMonitorFilterResultSeq* changeMonitorFilterResultSeq;
  };


  ChangeMonitorFilterResult( MemBlock* mb );
  ChangeMonitorFilterResult( MemBlock* mb, const ChangeMonitorFilterResult &);
  ~ChangeMonitorFilterResult();

  AsnType *Clone() const;

  ChangeMonitorFilterResult &operator = (const ChangeMonitorFilterResult &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class MonitorStopArgument : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     crossRefIdentifierCid = 0,
     monitorStopArgumentSeqCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     MonitorCrossRefID* crossRefIdentifier;
     MonitorStopArgumentSeq* monitorStopArgumentSeq;
  };


  MonitorStopArgument( MemBlock* mb );
  MonitorStopArgument( MemBlock* mb, const MonitorStopArgument &);
  ~MonitorStopArgument();

  AsnType *Clone() const;

  MonitorStopArgument &operator = (const MonitorStopArgument &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class SnapshotDeviceArgument : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     snapshotObjectCid = 0,
     snapshotDeviceArgumentSeqCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     DeviceID* snapshotObject;
     SnapshotDeviceArgumentSeq* snapshotDeviceArgumentSeq;
  };


  SnapshotDeviceArgument( MemBlock* mb );
  SnapshotDeviceArgument( MemBlock* mb, const SnapshotDeviceArgument &);
  ~SnapshotDeviceArgument();

  AsnType *Clone() const;

  SnapshotDeviceArgument &operator = (const SnapshotDeviceArgument &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ConnectionID : public AsnType
{
public:
  AsnOcts* call;
  ConnectionIDChoice* device;

 ConnectionID( MemBlock* mb );
 ConnectionID ( MemBlock* mb, const ConnectionID & );
 ~ConnectionID();
  AsnType *Clone() const;

  ConnectionID &operator = (const ConnectionID &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ConnectionIDList : public AsnType
{
protected:
  unsigned long int count;
  struct AsnListElmt
  {
    AsnListElmt *next;
    AsnListElmt *prev;
    ConnectionID *elmt;
    void* operator new( size_t n, MemBlock* memblock ) { return memblock->Allocate( n ); }
    void operator delete( void* p, MemBlock* memblock ) { /* nothing to do */ }
    void operator delete( void* p ) { /* nothing to do */ }
  } *first, *curr, *last;

public:
  ConnectionIDList( MemBlock* mb ) : AsnType( mb ) { count = 0; first = curr = last = NULL; }
  ConnectionIDList( MemBlock* mb, const ConnectionIDList &);
  ~ConnectionIDList();
  AsnType *Clone() const;

  ConnectionIDList &operator = (const ConnectionIDList &);
  void SetCurrElmt (unsigned long int index);
  unsigned long int GetCurrElmtIndex();
  void SetCurrToFirst() { curr = first; }
  void SetCurrToLast()  { curr = last; }
  // reading member fcns
  int Count() const { return count; }
  ConnectionID *First() const { return count > 0 ? first->elmt : NULL; }
  ConnectionID *Last() const { return count > 0 ? last->elmt : NULL; }
  ConnectionID *Curr() const { return curr ? curr->elmt : NULL; }
  ConnectionID *Next() const { return curr && curr->next ? curr->next->elmt : NULL; }
  ConnectionID *Prev() const { return curr && curr->prev ? curr->prev->elmt : NULL; }

  // routines that move the curr elmt
  ConnectionID *GoNext() { if (curr) curr = curr->next; return Curr(); }
  ConnectionID *GoPrev() { if (curr) curr = curr->prev; return Curr(); }

  // write & alloc fcns - returns new elmt
  ConnectionID *Append();  // add elmt to end of list
  ConnectionID *Prepend(); // add elmt to beginning of list
  ConnectionID *InsertBefore(); //insert elmt before current elmt
  ConnectionID *InsertAfter(); //insert elmt after current elmt

  // write & alloc & copy - returns list after copying elmt
  ConnectionIDList &AppendCopy (ConnectionID &elmt);  // add elmt to end of list
  ConnectionIDList &PrependCopy (ConnectionID &elmt); // add elmt to beginning of list
  ConnectionIDList &InsertBeforeAndCopy (ConnectionID &elmt); //insert elmt before current elmt
  ConnectionIDList &InsertAfterAndCopy (ConnectionID &elmt); //insert elmt after current elmt

  // removing the current elmt from the list
  void RemoveCurrFromList();

  // encode and decode routines    
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  PDU_MEMBER_MACROS
  void Print ( CTsvcLIB::LOG& os ) const;
};


class SnapshotCallResponseInfo : public AsnType
{
public:
  SubjectDeviceID* deviceOnCall;
  ConnectionID* callIdentifier;
  LocalConnectionState* localConnectionState;

 SnapshotCallResponseInfo( MemBlock* mb );
 SnapshotCallResponseInfo ( MemBlock* mb, const SnapshotCallResponseInfo & );
 ~SnapshotCallResponseInfo();
  AsnType *Clone() const;

  SnapshotCallResponseInfo &operator = (const SnapshotCallResponseInfo &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class CallState : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     compoundCid = 0,
     simpleCid = 1,
     unknownCid = 2
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     CompoundCallState* compound;
     SimpleCallState* simple;
     AsnNull* unknown;
  };


  CallState( MemBlock* mb );
  CallState( MemBlock* mb, const CallState &);
  ~CallState();

  AsnType *Clone() const;

  CallState &operator = (const CallState &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class AgentParameter : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     loggedInCid = 0,
     loggedOutCid = 1,
     notReadyCid = 2,
     readyCid = 3,
     workNotReadyCid = 4,
     workReadyCid = 5
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     LoggedOnInfo* loggedIn;
     LoggedOffInfo* loggedOut;
     AsnNull* notReady;
     AsnNull* ready;
     AsnNull* workNotReady;
     AsnNull* workReady;
  };


  AgentParameter( MemBlock* mb );
  AgentParameter( MemBlock* mb, const AgentParameter &);
  ~AgentParameter();

  AsnType *Clone() const;

  AgentParameter &operator = (const AgentParameter &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class FeatureInfo : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     camponCid = 0,
     callbackCid = 1,
     intrudeCid = 2,
     callbackMessageCid = 3
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     ConnectionID* campon;
     ConnectionID* callback;
     ConnectionID* intrude;
     ConnectionID* callbackMessage;
  };


  FeatureInfo( MemBlock* mb );
  FeatureInfo( MemBlock* mb, const FeatureInfo &);
  ~FeatureInfo();

  AsnType *Clone() const;

  FeatureInfo &operator = (const FeatureInfo &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class SetDeviceFeature : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     msgWaitingOnCid = 0,
     doNotDisturbOnCid = 1,
     forwardCid = 2,
     requestedAgentStateCid = 3
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     AsnBool* msgWaitingOn;
     AsnBool* doNotDisturbOn;
     ForwardParameter* forward;
     AgentParameter* requestedAgentState;
  };


  SetDeviceFeature( MemBlock* mb );
  SetDeviceFeature( MemBlock* mb, const SetDeviceFeature &);
  ~SetDeviceFeature();

  AsnType *Clone() const;

  SetDeviceFeature &operator = (const SetDeviceFeature &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class DivertInfoSeq1 : public AsnType
{
public:
  ConnectionID* callToBePickedUp;
  DeviceID* requestingDevice;

 DivertInfoSeq1( MemBlock* mb );
 DivertInfoSeq1 ( MemBlock* mb, const DivertInfoSeq1 & );
 ~DivertInfoSeq1();
  AsnType *Clone() const;

  DivertInfoSeq1 &operator = (const DivertInfoSeq1 &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class DivertInfoSeq : public AsnType
{
public:
  ConnectionID* callToBeDiverted;
  CalledDeviceID* newDestination;

 DivertInfoSeq( MemBlock* mb );
 DivertInfoSeq ( MemBlock* mb, const DivertInfoSeq & );
 ~DivertInfoSeq();
  AsnType *Clone() const;

  DivertInfoSeq &operator = (const DivertInfoSeq &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ConnectionDetailsSeq : public AsnType
{
public:
  ConnectionID* heldCall;
  ConnectionID* activeCall;

 ConnectionDetailsSeq( MemBlock* mb );
 ConnectionDetailsSeq ( MemBlock* mb, const ConnectionDetailsSeq & );
 ~ConnectionDetailsSeq();
  AsnType *Clone() const;

  ConnectionDetailsSeq &operator = (const ConnectionDetailsSeq &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class CallInfoSeq : public AsnType
{
public:
  ConnectionID* endpoint;
  DeviceID* staticEndpoint;

 CallInfoSeq( MemBlock* mb );
 CallInfoSeq ( MemBlock* mb, const CallInfoSeq & );
 ~CallInfoSeq();
  AsnType *Clone() const;

  CallInfoSeq &operator = (const CallInfoSeq &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class SnapshotCallArgumentSeq : public AsnType
{
public:
  ConnectionID* snapshotObject;
  CSTACommonArguments* extensions;

 SnapshotCallArgumentSeq( MemBlock* mb );
 SnapshotCallArgumentSeq ( MemBlock* mb, const SnapshotCallArgumentSeq & );
 ~SnapshotCallArgumentSeq();
  AsnType *Clone() const;

  SnapshotCallArgumentSeq &operator = (const SnapshotCallArgumentSeq &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class RetrieveCallArgumentSeq : public AsnType
{
public:
  ConnectionID* callToBeRetrieved;
  CSTACommonArguments* extensions;

 RetrieveCallArgumentSeq( MemBlock* mb );
 RetrieveCallArgumentSeq ( MemBlock* mb, const RetrieveCallArgumentSeq & );
 ~RetrieveCallArgumentSeq();
  AsnType *Clone() const;

  RetrieveCallArgumentSeq &operator = (const RetrieveCallArgumentSeq &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class MakePredictiveCallResultSeq : public AsnType
{
public:
  ConnectionID* initiatedCall;
  CSTAPrivateData* extensions;

 MakePredictiveCallResultSeq( MemBlock* mb );
 MakePredictiveCallResultSeq ( MemBlock* mb, const MakePredictiveCallResultSeq & );
 ~MakePredictiveCallResultSeq();
  AsnType *Clone() const;

  MakePredictiveCallResultSeq &operator = (const MakePredictiveCallResultSeq &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class MakeCallResultSeq : public AsnType
{
public:
  ConnectionID* initiatedCall;
  CSTAPrivateData* extensions;

 MakeCallResultSeq( MemBlock* mb );
 MakeCallResultSeq ( MemBlock* mb, const MakeCallResultSeq & );
 ~MakeCallResultSeq();
  AsnType *Clone() const;

  MakeCallResultSeq &operator = (const MakeCallResultSeq &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ConsultationCallResultSeq : public AsnType
{
public:
  ConnectionID* initiatedCall;
  CSTAPrivateData* extensions;

 ConsultationCallResultSeq( MemBlock* mb );
 ConsultationCallResultSeq ( MemBlock* mb, const ConsultationCallResultSeq & );
 ~ConsultationCallResultSeq();
  AsnType *Clone() const;

  ConsultationCallResultSeq &operator = (const ConsultationCallResultSeq &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ClearConnectionArgumentSeq : public AsnType
{
public:
  ConnectionID* connectionToBeCleared;
  CSTACommonArguments* extensions;

 ClearConnectionArgumentSeq( MemBlock* mb );
 ClearConnectionArgumentSeq ( MemBlock* mb, const ClearConnectionArgumentSeq & );
 ~ClearConnectionArgumentSeq();
  AsnType *Clone() const;

  ClearConnectionArgumentSeq &operator = (const ClearConnectionArgumentSeq &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ClearCallArgumentSeq : public AsnType
{
public:
  ConnectionID* callToBeCleared;
  CSTACommonArguments* extensions;

 ClearCallArgumentSeq( MemBlock* mb );
 ClearCallArgumentSeq ( MemBlock* mb, const ClearCallArgumentSeq & );
 ~ClearCallArgumentSeq();
  AsnType *Clone() const;

  ClearCallArgumentSeq &operator = (const ClearCallArgumentSeq &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class CallCompletionArgumentSeq : public AsnType
{
public:
  FeatureInfo* featureInfo;
  CSTACommonArguments* extensions;

 CallCompletionArgumentSeq( MemBlock* mb );
 CallCompletionArgumentSeq ( MemBlock* mb, const CallCompletionArgumentSeq & );
 ~CallCompletionArgumentSeq();
  AsnType *Clone() const;

  CallCompletionArgumentSeq &operator = (const CallCompletionArgumentSeq &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class AnswerCallArgumentSeq : public AsnType
{
public:
  ConnectionID* callToBeAnswered;
  CSTACommonArguments* extensions;

 AnswerCallArgumentSeq( MemBlock* mb );
 AnswerCallArgumentSeq ( MemBlock* mb, const AnswerCallArgumentSeq & );
 ~AnswerCallArgumentSeq();
  AsnType *Clone() const;

  AnswerCallArgumentSeq &operator = (const AnswerCallArgumentSeq &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class AnswerCallArgument : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     callToBeAnsweredCid = 0,
     answerCallArgumentSeqCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     ConnectionID* callToBeAnswered;
     AnswerCallArgumentSeq* answerCallArgumentSeq;
  };


  AnswerCallArgument( MemBlock* mb );
  AnswerCallArgument( MemBlock* mb, const AnswerCallArgument &);
  ~AnswerCallArgument();

  AsnType *Clone() const;

  AnswerCallArgument &operator = (const AnswerCallArgument &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class CallCompletionArgument : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     featureInfoCid = 0,
     callCompletionArgumentSeqCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     FeatureInfo* featureInfo;
     CallCompletionArgumentSeq* callCompletionArgumentSeq;
  };


  CallCompletionArgument( MemBlock* mb );
  CallCompletionArgument( MemBlock* mb, const CallCompletionArgument &);
  ~CallCompletionArgument();

  AsnType *Clone() const;

  CallCompletionArgument &operator = (const CallCompletionArgument &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ClearCallArgument : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     callToBeClearedCid = 0,
     clearCallArgumentSeqCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     ConnectionID* callToBeCleared;
     ClearCallArgumentSeq* clearCallArgumentSeq;
  };


  ClearCallArgument( MemBlock* mb );
  ClearCallArgument( MemBlock* mb, const ClearCallArgument &);
  ~ClearCallArgument();

  AsnType *Clone() const;

  ClearCallArgument &operator = (const ClearCallArgument &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ClearConnectionArgument : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     connectionToBeClearedCid = 0,
     clearConnectionArgumentSeqCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     ConnectionID* connectionToBeCleared;
     ClearConnectionArgumentSeq* clearConnectionArgumentSeq;
  };


  ClearConnectionArgument( MemBlock* mb );
  ClearConnectionArgument( MemBlock* mb, const ClearConnectionArgument &);
  ~ClearConnectionArgument();

  AsnType *Clone() const;

  ClearConnectionArgument &operator = (const ClearConnectionArgument &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ConsultationCallArgument : public AsnType
{
public:
  ConnectionID* existingCall;
  CalledDeviceID* calledDirectoryNumber;
  CSTACommonArguments* extensions;

 ConsultationCallArgument( MemBlock* mb );
 ConsultationCallArgument ( MemBlock* mb, const ConsultationCallArgument & );
 ~ConsultationCallArgument();
  AsnType *Clone() const;

  ConsultationCallArgument &operator = (const ConsultationCallArgument &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ConsultationCallResult : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     initiatedCallCid = 0,
     consultationCallResultSeqCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     ConnectionID* initiatedCall;
     ConsultationCallResultSeq* consultationCallResultSeq;
  };


  ConsultationCallResult( MemBlock* mb );
  ConsultationCallResult( MemBlock* mb, const ConsultationCallResult &);
  ~ConsultationCallResult();

  AsnType *Clone() const;

  ConsultationCallResult &operator = (const ConsultationCallResult &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class HoldCallArgument : public AsnType
{
public:
  ConnectionID* callToBeHeld;
  ReserveConnection* connectionReservation;
  CSTACommonArguments* extensions;

 HoldCallArgument( MemBlock* mb );
 HoldCallArgument ( MemBlock* mb, const HoldCallArgument & );
 ~HoldCallArgument();
  AsnType *Clone() const;

  HoldCallArgument &operator = (const HoldCallArgument &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class MakeCallResult : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     initiatedCallCid = 0,
     makeCallResultSeqCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     ConnectionID* initiatedCall;
     MakeCallResultSeq* makeCallResultSeq;
  };


  MakeCallResult( MemBlock* mb );
  MakeCallResult( MemBlock* mb, const MakeCallResult &);
  ~MakeCallResult();

  AsnType *Clone() const;

  MakeCallResult &operator = (const MakeCallResult &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class MakePredictiveCallResult : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     initiatedCallCid = 0,
     makePredictiveCallResultSeqCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     ConnectionID* initiatedCall;
     MakePredictiveCallResultSeq* makePredictiveCallResultSeq;
  };


  MakePredictiveCallResult( MemBlock* mb );
  MakePredictiveCallResult( MemBlock* mb, const MakePredictiveCallResult &);
  ~MakePredictiveCallResult();

  AsnType *Clone() const;

  MakePredictiveCallResult &operator = (const MakePredictiveCallResult &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class RetrieveCallArgument : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     callToBeRetrievedCid = 0,
     retrieveCallArgumentSeqCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     ConnectionID* callToBeRetrieved;
     RetrieveCallArgumentSeq* retrieveCallArgumentSeq;
  };


  RetrieveCallArgument( MemBlock* mb );
  RetrieveCallArgument( MemBlock* mb, const RetrieveCallArgument &);
  ~RetrieveCallArgument();

  AsnType *Clone() const;

  RetrieveCallArgument &operator = (const RetrieveCallArgument &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class SetFeatureArgument : public AsnType
{
public:
  DeviceID* device;
  SetDeviceFeature* feature;
  CSTACommonArguments* extensions;

 SetFeatureArgument( MemBlock* mb );
 SetFeatureArgument ( MemBlock* mb, const SetFeatureArgument & );
 ~SetFeatureArgument();
  AsnType *Clone() const;

  SetFeatureArgument &operator = (const SetFeatureArgument &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class RouteRequestArgument : public AsnType
{
public:
  RoutingCrossRefID crossRefIdentifier;
  CalledDeviceID* currentRoute;
  CallingDeviceID* callingDevice;
  ConnectionID* routedCall;
  SelectValue* routeSelAlgorithm;
  PriorityValue* priority;
  SetUpValues* setupInformation;
  CSTACommonArguments* extensions;

 RouteRequestArgument( MemBlock* mb );
 RouteRequestArgument ( MemBlock* mb, const RouteRequestArgument & );
 ~RouteRequestArgument();
  AsnType *Clone() const;

  RouteRequestArgument &operator = (const RouteRequestArgument &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class SnapshotCallArgument : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     snapshotObjectCid = 0,
     snapshotCallArgumentSeqCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     ConnectionID* snapshotObject;
     SnapshotCallArgumentSeq* snapshotCallArgumentSeq;
  };


  SnapshotCallArgument( MemBlock* mb );
  SnapshotCallArgument( MemBlock* mb, const SnapshotCallArgument &);
  ~SnapshotCallArgument();

  AsnType *Clone() const;

  SnapshotCallArgument &operator = (const SnapshotCallArgument &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class CSTAObject : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     deviceObjectCid = 0,
     callObjectCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     DeviceID* deviceObject;
     ConnectionID* callObject;
  };


  CSTAObject( MemBlock* mb );
  CSTAObject( MemBlock* mb, const CSTAObject &);
  ~CSTAObject();

  AsnType *Clone() const;

  CSTAObject &operator = (const CSTAObject &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class CallInfo : public AsnType
{
protected:
  unsigned long int count;
  struct AsnListElmt
  {
    AsnListElmt *next;
    AsnListElmt *prev;
    CallInfoSeq *elmt;
    void* operator new( size_t n, MemBlock* memblock ) { return memblock->Allocate( n ); }
    void operator delete( void* p, MemBlock* memblock ) { /* nothing to do */ }
    void operator delete( void* p ) { /* nothing to do */ }
  } *first, *curr, *last;

public:
  CallInfo( MemBlock* mb ) : AsnType( mb ) { count = 0; first = curr = last = NULL; }
  CallInfo( MemBlock* mb, const CallInfo &);
  ~CallInfo();
  AsnType *Clone() const;

  CallInfo &operator = (const CallInfo &);
  void SetCurrElmt (unsigned long int index);
  unsigned long int GetCurrElmtIndex();
  void SetCurrToFirst() { curr = first; }
  void SetCurrToLast()  { curr = last; }
  // reading member fcns
  int Count() const { return count; }
  CallInfoSeq *First() const { return count > 0 ? first->elmt : NULL; }
  CallInfoSeq *Last() const { return count > 0 ? last->elmt : NULL; }
  CallInfoSeq *Curr() const { return curr ? curr->elmt : NULL; }
  CallInfoSeq *Next() const { return curr && curr->next ? curr->next->elmt : NULL; }
  CallInfoSeq *Prev() const { return curr && curr->prev ? curr->prev->elmt : NULL; }

  // routines that move the curr elmt
  CallInfoSeq *GoNext() { if (curr) curr = curr->next; return Curr(); }
  CallInfoSeq *GoPrev() { if (curr) curr = curr->prev; return Curr(); }

  // write & alloc fcns - returns new elmt
  CallInfoSeq *Append();  // add elmt to end of list
  CallInfoSeq *Prepend(); // add elmt to beginning of list
  CallInfoSeq *InsertBefore(); //insert elmt before current elmt
  CallInfoSeq *InsertAfter(); //insert elmt after current elmt

  // write & alloc & copy - returns list after copying elmt
  CallInfo &AppendCopy (CallInfoSeq &elmt);  // add elmt to end of list
  CallInfo &PrependCopy (CallInfoSeq &elmt); // add elmt to beginning of list
  CallInfo &InsertBeforeAndCopy (CallInfoSeq &elmt); //insert elmt before current elmt
  CallInfo &InsertAfterAndCopy (CallInfoSeq &elmt); //insert elmt after current elmt

  // removing the current elmt from the list
  void RemoveCurrFromList();

  // encode and decode routines    
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  PDU_MEMBER_MACROS
  void Print ( CTsvcLIB::LOG& os ) const;
};


class ConnectionList : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     connectionsCid = 0,
     callinformationCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     ConnectionIDList* connections;
     CallInfo* callinformation;
  };


  ConnectionList( MemBlock* mb );
  ConnectionList( MemBlock* mb, const ConnectionList &);
  ~ConnectionList();

  AsnType *Clone() const;

  ConnectionList &operator = (const ConnectionList &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


/* CSTAObject*/
typedef CSTAObject MonitorObject;

class SnapshotDeviceResponseInfo : public AsnType
{
public:
  ConnectionID* callIdentifier;
  CallState* localCallState;

 SnapshotDeviceResponseInfo( MemBlock* mb );
 SnapshotDeviceResponseInfo ( MemBlock* mb, const SnapshotDeviceResponseInfo & );
 ~SnapshotDeviceResponseInfo();
  AsnType *Clone() const;

  SnapshotDeviceResponseInfo &operator = (const SnapshotDeviceResponseInfo &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class SnapshotCallData : public AsnType
{
protected:
  unsigned long int count;
  struct AsnListElmt
  {
    AsnListElmt *next;
    AsnListElmt *prev;
    SnapshotCallResponseInfo *elmt;
    void* operator new( size_t n, MemBlock* memblock ) { return memblock->Allocate( n ); }
    void operator delete( void* p, MemBlock* memblock ) { /* nothing to do */ }
    void operator delete( void* p ) { /* nothing to do */ }
  } *first, *curr, *last;

public:
  SnapshotCallData( MemBlock* mb ) : AsnType( mb ) { count = 0; first = curr = last = NULL; }
  SnapshotCallData( MemBlock* mb, const SnapshotCallData &);
  ~SnapshotCallData();
  AsnType *Clone() const;

  SnapshotCallData &operator = (const SnapshotCallData &);
  void SetCurrElmt (unsigned long int index);
  unsigned long int GetCurrElmtIndex();
  void SetCurrToFirst() { curr = first; }
  void SetCurrToLast()  { curr = last; }
  // reading member fcns
  int Count() const { return count; }
  SnapshotCallResponseInfo *First() const { return count > 0 ? first->elmt : NULL; }
  SnapshotCallResponseInfo *Last() const { return count > 0 ? last->elmt : NULL; }
  SnapshotCallResponseInfo *Curr() const { return curr ? curr->elmt : NULL; }
  SnapshotCallResponseInfo *Next() const { return curr && curr->next ? curr->next->elmt : NULL; }
  SnapshotCallResponseInfo *Prev() const { return curr && curr->prev ? curr->prev->elmt : NULL; }

  // routines that move the curr elmt
  SnapshotCallResponseInfo *GoNext() { if (curr) curr = curr->next; return Curr(); }
  SnapshotCallResponseInfo *GoPrev() { if (curr) curr = curr->prev; return Curr(); }

  // write & alloc fcns - returns new elmt
  SnapshotCallResponseInfo *Append();  // add elmt to end of list
  SnapshotCallResponseInfo *Prepend(); // add elmt to beginning of list
  SnapshotCallResponseInfo *InsertBefore(); //insert elmt before current elmt
  SnapshotCallResponseInfo *InsertAfter(); //insert elmt after current elmt

  // write & alloc & copy - returns list after copying elmt
  SnapshotCallData &AppendCopy (SnapshotCallResponseInfo &elmt);  // add elmt to end of list
  SnapshotCallData &PrependCopy (SnapshotCallResponseInfo &elmt); // add elmt to beginning of list
  SnapshotCallData &InsertBeforeAndCopy (SnapshotCallResponseInfo &elmt); //insert elmt before current elmt
  SnapshotCallData &InsertAfterAndCopy (SnapshotCallResponseInfo &elmt); //insert elmt after current elmt

  // removing the current elmt from the list
  void RemoveCurrFromList();

  // encode and decode routines    
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  PDU_MEMBER_MACROS
  void Print ( CTsvcLIB::LOG& os ) const;
};


class ConnectionDetails : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     heldCallCid = 0,
     activeCallCid = 1,
     bothCallsCid = 2
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     ConnectionID* heldCall;
     ConnectionID* activeCall;
     ConnectionDetailsSeq* bothCalls;
  };


  ConnectionDetails( MemBlock* mb );
  ConnectionDetails( MemBlock* mb, const ConnectionDetails &);
  ~ConnectionDetails();

  AsnType *Clone() const;

  ConnectionDetails &operator = (const ConnectionDetails &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class DivertInfo : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     deflectCid = 0,
     pickupCid = 1,
     groupCid = 2
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     DivertInfoSeq* deflect;
     DivertInfoSeq1* pickup;
     DeviceID* group;
  };


  DivertInfo( MemBlock* mb );
  DivertInfo( MemBlock* mb, const DivertInfo &);
  ~DivertInfo();

  AsnType *Clone() const;

  DivertInfo &operator = (const DivertInfo &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class SnapshotCallResultSeq : public AsnType
{
public:
  SnapshotCallData snapshotData;
  CSTAPrivateData* extensions;

 SnapshotCallResultSeq( MemBlock* mb );
 SnapshotCallResultSeq ( MemBlock* mb, const SnapshotCallResultSeq & );
 ~SnapshotCallResultSeq();
  AsnType *Clone() const;

  SnapshotCallResultSeq &operator = (const SnapshotCallResultSeq &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class TransferCallArgumentSeq : public AsnType
{
public:
  ConnectionDetails* transferInfo;
  CSTACommonArguments* extensions;

 TransferCallArgumentSeq( MemBlock* mb );
 TransferCallArgumentSeq ( MemBlock* mb, const TransferCallArgumentSeq & );
 ~TransferCallArgumentSeq();
  AsnType *Clone() const;

  TransferCallArgumentSeq &operator = (const TransferCallArgumentSeq &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ReconnectCallArgumentSeq : public AsnType
{
public:
  ConnectionDetails* reconnectInfo;
  CSTACommonArguments* extensions;

 ReconnectCallArgumentSeq( MemBlock* mb );
 ReconnectCallArgumentSeq ( MemBlock* mb, const ReconnectCallArgumentSeq & );
 ~ReconnectCallArgumentSeq();
  AsnType *Clone() const;

  ReconnectCallArgumentSeq &operator = (const ReconnectCallArgumentSeq &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class DivertCallArgumentSeq : public AsnType
{
public:
  DivertInfo* deivertInfo;
  CSTACommonArguments* extensions;

 DivertCallArgumentSeq( MemBlock* mb );
 DivertCallArgumentSeq ( MemBlock* mb, const DivertCallArgumentSeq & );
 ~DivertCallArgumentSeq();
  AsnType *Clone() const;

  DivertCallArgumentSeq &operator = (const DivertCallArgumentSeq &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ConferenceCallArgumentSeq : public AsnType
{
public:
  ConnectionDetails* callsInvolved;
  CSTACommonArguments* extensions;

 ConferenceCallArgumentSeq( MemBlock* mb );
 ConferenceCallArgumentSeq ( MemBlock* mb, const ConferenceCallArgumentSeq & );
 ~ConferenceCallArgumentSeq();
  AsnType *Clone() const;

  ConferenceCallArgumentSeq &operator = (const ConferenceCallArgumentSeq &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class AlternateCallArgumentSeq : public AsnType
{
public:
  ConnectionDetails* callsInvolved;
  CSTACommonArguments* extensions;

 AlternateCallArgumentSeq( MemBlock* mb );
 AlternateCallArgumentSeq ( MemBlock* mb, const AlternateCallArgumentSeq & );
 ~AlternateCallArgumentSeq();
  AsnType *Clone() const;

  AlternateCallArgumentSeq &operator = (const AlternateCallArgumentSeq &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class AlternateCallArgument : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     callsInvolvedCid = 0,
     alternateCallArgumentSeqCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     ConnectionDetails* callsInvolved;
     AlternateCallArgumentSeq* alternateCallArgumentSeq;
  };


  AlternateCallArgument( MemBlock* mb );
  AlternateCallArgument( MemBlock* mb, const AlternateCallArgument &);
  ~AlternateCallArgument();

  AsnType *Clone() const;

  AlternateCallArgument &operator = (const AlternateCallArgument &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ConferenceCallArgument : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     callsInvolvedCid = 0,
     conferenceCallArgumentSeqCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     ConnectionDetails* callsInvolved;
     ConferenceCallArgumentSeq* conferenceCallArgumentSeq;
  };


  ConferenceCallArgument( MemBlock* mb );
  ConferenceCallArgument( MemBlock* mb, const ConferenceCallArgument &);
  ~ConferenceCallArgument();

  AsnType *Clone() const;

  ConferenceCallArgument &operator = (const ConferenceCallArgument &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ConferenceCallResult : public AsnType
{
public:
  ConnectionID* conferenceCall;
  ConnectionList* connections;
  CSTAPrivateData* extensions;

 ConferenceCallResult( MemBlock* mb );
 ConferenceCallResult ( MemBlock* mb, const ConferenceCallResult & );
 ~ConferenceCallResult();
  AsnType *Clone() const;

  ConferenceCallResult &operator = (const ConferenceCallResult &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class DivertCallArgument : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     divertInfoCid = 0,
     divertCallArgumentSeqCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     DivertInfo* divertInfo;
     DivertCallArgumentSeq* divertCallArgumentSeq;
  };


  DivertCallArgument( MemBlock* mb );
  DivertCallArgument( MemBlock* mb, const DivertCallArgument &);
  ~DivertCallArgument();

  AsnType *Clone() const;

  DivertCallArgument &operator = (const DivertCallArgument &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ReconnectCallArgument : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     reconnectInfoCid = 0,
     reconnectCallArgumentSeqCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     ConnectionDetails* reconnectInfo;
     ReconnectCallArgumentSeq* reconnectCallArgumentSeq;
  };


  ReconnectCallArgument( MemBlock* mb );
  ReconnectCallArgument( MemBlock* mb, const ReconnectCallArgument &);
  ~ReconnectCallArgument();

  AsnType *Clone() const;

  ReconnectCallArgument &operator = (const ReconnectCallArgument &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class TransferCallArgument : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     transferInfoCid = 0,
     transferCallArgumentSeqCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     ConnectionDetails* transferInfo;
     TransferCallArgumentSeq* transferCallArgumentSeq;
  };


  TransferCallArgument( MemBlock* mb );
  TransferCallArgument( MemBlock* mb, const TransferCallArgument &);
  ~TransferCallArgument();

  AsnType *Clone() const;

  TransferCallArgument &operator = (const TransferCallArgument &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class TransferCallResult : public AsnType
{
public:
  ConnectionID* transferredCall;
  ConnectionList* connections;
  CSTAPrivateData* extensions;

 TransferCallResult( MemBlock* mb );
 TransferCallResult ( MemBlock* mb, const TransferCallResult & );
 ~TransferCallResult();
  AsnType *Clone() const;

  TransferCallResult &operator = (const TransferCallResult &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class MonitorStartArgument : public AsnType
{
public:
  MonitorObject* monitorObject;
  MonitorFilter* monitorFilter;
  MonitorType* monitorType;
  CSTACommonArguments* extensions;

 MonitorStartArgument( MemBlock* mb );
 MonitorStartArgument ( MemBlock* mb, const MonitorStartArgument & );
 ~MonitorStartArgument();
  AsnType *Clone() const;

  MonitorStartArgument &operator = (const MonitorStartArgument &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class SnapshotCallResult : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     snapshotDataCid = 0,
     snapshotCallResultSeqCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     SnapshotCallData* snapshotData;
     SnapshotCallResultSeq* snapshotCallResultSeq;
  };


  SnapshotCallResult( MemBlock* mb );
  SnapshotCallResult( MemBlock* mb, const SnapshotCallResult &);
  ~SnapshotCallResult();

  AsnType *Clone() const;

  SnapshotCallResult &operator = (const SnapshotCallResult &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class SnapshotDeviceData : public AsnType
{
protected:
  unsigned long int count;
  struct AsnListElmt
  {
    AsnListElmt *next;
    AsnListElmt *prev;
    SnapshotDeviceResponseInfo *elmt;
    void* operator new( size_t n, MemBlock* memblock ) { return memblock->Allocate( n ); }
    void operator delete( void* p, MemBlock* memblock ) { /* nothing to do */ }
    void operator delete( void* p ) { /* nothing to do */ }
  } *first, *curr, *last;

public:
  SnapshotDeviceData( MemBlock* mb ) : AsnType( mb ) { count = 0; first = curr = last = NULL; }
  SnapshotDeviceData( MemBlock* mb, const SnapshotDeviceData &);
  ~SnapshotDeviceData();
  AsnType *Clone() const;

  SnapshotDeviceData &operator = (const SnapshotDeviceData &);
  void SetCurrElmt (unsigned long int index);
  unsigned long int GetCurrElmtIndex();
  void SetCurrToFirst() { curr = first; }
  void SetCurrToLast()  { curr = last; }
  // reading member fcns
  int Count() const { return count; }
  SnapshotDeviceResponseInfo *First() const { return count > 0 ? first->elmt : NULL; }
  SnapshotDeviceResponseInfo *Last() const { return count > 0 ? last->elmt : NULL; }
  SnapshotDeviceResponseInfo *Curr() const { return curr ? curr->elmt : NULL; }
  SnapshotDeviceResponseInfo *Next() const { return curr && curr->next ? curr->next->elmt : NULL; }
  SnapshotDeviceResponseInfo *Prev() const { return curr && curr->prev ? curr->prev->elmt : NULL; }

  // routines that move the curr elmt
  SnapshotDeviceResponseInfo *GoNext() { if (curr) curr = curr->next; return Curr(); }
  SnapshotDeviceResponseInfo *GoPrev() { if (curr) curr = curr->prev; return Curr(); }

  // write & alloc fcns - returns new elmt
  SnapshotDeviceResponseInfo *Append();  // add elmt to end of list
  SnapshotDeviceResponseInfo *Prepend(); // add elmt to beginning of list
  SnapshotDeviceResponseInfo *InsertBefore(); //insert elmt before current elmt
  SnapshotDeviceResponseInfo *InsertAfter(); //insert elmt after current elmt

  // write & alloc & copy - returns list after copying elmt
  SnapshotDeviceData &AppendCopy (SnapshotDeviceResponseInfo &elmt);  // add elmt to end of list
  SnapshotDeviceData &PrependCopy (SnapshotDeviceResponseInfo &elmt); // add elmt to beginning of list
  SnapshotDeviceData &InsertBeforeAndCopy (SnapshotDeviceResponseInfo &elmt); //insert elmt before current elmt
  SnapshotDeviceData &InsertAfterAndCopy (SnapshotDeviceResponseInfo &elmt); //insert elmt after current elmt

  // removing the current elmt from the list
  void RemoveCurrFromList();

  // encode and decode routines    
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  PDU_MEMBER_MACROS
  void Print ( CTsvcLIB::LOG& os ) const;
};


class SnapshotDeviceResultSeq : public AsnType
{
public:
  SnapshotDeviceData snapshotData;
  CSTAPrivateData* extensions;

 SnapshotDeviceResultSeq( MemBlock* mb );
 SnapshotDeviceResultSeq ( MemBlock* mb, const SnapshotDeviceResultSeq & );
 ~SnapshotDeviceResultSeq();
  AsnType *Clone() const;

  SnapshotDeviceResultSeq &operator = (const SnapshotDeviceResultSeq &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class SnapshotDeviceResult : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     snapshotDataCid = 0,
     snapshotDeviceResultSeqCid = 1
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     SnapshotDeviceData* snapshotData;
     SnapshotDeviceResultSeq* snapshotDeviceResultSeq;
  };


  SnapshotDeviceResult( MemBlock* mb );
  SnapshotDeviceResult( MemBlock* mb, const SnapshotDeviceResult &);
  ~SnapshotDeviceResult();

  AsnType *Clone() const;

  SnapshotDeviceResult &operator = (const SnapshotDeviceResult &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


/* ROSEapdu*/
typedef ROSEapdu CSTAapdu;

class CallClearedEventInfo : public AsnType
{
public:
  ConnectionID* clearedCall;
  LocalConnectionState* localConnectionInfo;
  EventCause* cause;

 CallClearedEventInfo( MemBlock* mb );
 CallClearedEventInfo ( MemBlock* mb, const CallClearedEventInfo & );
 ~CallClearedEventInfo();
  AsnType *Clone() const;

  CallClearedEventInfo &operator = (const CallClearedEventInfo &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ConferencedEventInfo : public AsnType
{
public:
  ConnectionID* primaryOldCall;
  ConnectionID* secondaryOldCall;
  SubjectDeviceID* confController;
  SubjectDeviceID* addedParty;
  ConnectionList* conferenceConnections;
  LocalConnectionState* localConnectionInfo;
  EventCause* cause;

 ConferencedEventInfo( MemBlock* mb );
 ConferencedEventInfo ( MemBlock* mb, const ConferencedEventInfo & );
 ~ConferencedEventInfo();
  AsnType *Clone() const;

  ConferencedEventInfo &operator = (const ConferencedEventInfo &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ConnectionClearedEventInfo : public AsnType
{
public:
  ConnectionID* droppedConnection;
  SubjectDeviceID* releasingDevice;
  LocalConnectionState* localConnectionInfo;
  EventCause* cause;

 ConnectionClearedEventInfo( MemBlock* mb );
 ConnectionClearedEventInfo ( MemBlock* mb, const ConnectionClearedEventInfo & );
 ~ConnectionClearedEventInfo();
  AsnType *Clone() const;

  ConnectionClearedEventInfo &operator = (const ConnectionClearedEventInfo &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class DeliveredEventInfo : public AsnType
{
public:
  ConnectionID* connection;
  SubjectDeviceID* alertingDevice;
  CallingDeviceID* callingDevice;
  CalledDeviceID* calledDevice;
  RedirectionDeviceID* lastRedirectionDevice;
  LocalConnectionState* localConnectionInfo;
  EventCause* cause;

 DeliveredEventInfo( MemBlock* mb );
 DeliveredEventInfo ( MemBlock* mb, const DeliveredEventInfo & );
 ~DeliveredEventInfo();
  AsnType *Clone() const;

  DeliveredEventInfo &operator = (const DeliveredEventInfo &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class DivertedEventInfo : public AsnType
{
public:
  ConnectionID* connection;
  SubjectDeviceID* divertingDevice;
  CalledDeviceID* newDestination;
  LocalConnectionState* localConnectionInfo;
  EventCause* cause;

 DivertedEventInfo( MemBlock* mb );
 DivertedEventInfo ( MemBlock* mb, const DivertedEventInfo & );
 ~DivertedEventInfo();
  AsnType *Clone() const;

  DivertedEventInfo &operator = (const DivertedEventInfo &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class EstablishedEventInfo : public AsnType
{
public:
  ConnectionID* establishedConnection;
  SubjectDeviceID* answeringDevice;
  CallingDeviceID* callingDevice;
  CalledDeviceID* calledDevice;
  RedirectionDeviceID* lastRedirectionDevice;
  LocalConnectionState* localConnectionInfo;
  EventCause* cause;

 EstablishedEventInfo( MemBlock* mb );
 EstablishedEventInfo ( MemBlock* mb, const EstablishedEventInfo & );
 ~EstablishedEventInfo();
  AsnType *Clone() const;

  EstablishedEventInfo &operator = (const EstablishedEventInfo &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class FailedEventInfo : public AsnType
{
public:
  ConnectionID* failedConnection;
  SubjectDeviceID* failingDevice;
  CalledDeviceID* calledDevice;
  LocalConnectionState* localConnectionInfo;
  EventCause* cause;

 FailedEventInfo( MemBlock* mb );
 FailedEventInfo ( MemBlock* mb, const FailedEventInfo & );
 ~FailedEventInfo();
  AsnType *Clone() const;

  FailedEventInfo &operator = (const FailedEventInfo &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class HeldEventInfo : public AsnType
{
public:
  ConnectionID* heldConnection;
  SubjectDeviceID* holdingDevice;
  LocalConnectionState* localConnectionInfo;
  EventCause* cause;

 HeldEventInfo( MemBlock* mb );
 HeldEventInfo ( MemBlock* mb, const HeldEventInfo & );
 ~HeldEventInfo();
  AsnType *Clone() const;

  HeldEventInfo &operator = (const HeldEventInfo &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class NetworkReachedEventInfo : public AsnType
{
public:
  ConnectionID* connection;
  SubjectDeviceID* trunkUsed;
  CalledDeviceID* calledDevice;
  LocalConnectionState* localConnectionInfo;
  EventCause* cause;

 NetworkReachedEventInfo( MemBlock* mb );
 NetworkReachedEventInfo ( MemBlock* mb, const NetworkReachedEventInfo & );
 ~NetworkReachedEventInfo();
  AsnType *Clone() const;

  NetworkReachedEventInfo &operator = (const NetworkReachedEventInfo &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class OriginatedEventInfo : public AsnType
{
public:
  ConnectionID* originatedConnection;
  SubjectDeviceID* callingDevice;
  CalledDeviceID* calledDevice;
  LocalConnectionState* localConnectionInfo;
  EventCause* cause;

 OriginatedEventInfo( MemBlock* mb );
 OriginatedEventInfo ( MemBlock* mb, const OriginatedEventInfo & );
 ~OriginatedEventInfo();
  AsnType *Clone() const;

  OriginatedEventInfo &operator = (const OriginatedEventInfo &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class QueuedEventInfo : public AsnType
{
public:
  ConnectionID* queuedConnection;
  SubjectDeviceID* queue;
  CallingDeviceID* callingDevice;
  CalledDeviceID* calledDevice;
  RedirectionDeviceID* lastRedirectionDevice;
  NoOfCallsInQueue* numberedQueued;
  LocalConnectionState* localConnectionInfo;
  EventCause* cause;

 QueuedEventInfo( MemBlock* mb );
 QueuedEventInfo ( MemBlock* mb, const QueuedEventInfo & );
 ~QueuedEventInfo();
  AsnType *Clone() const;

  QueuedEventInfo &operator = (const QueuedEventInfo &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class RetrievedEventInfo : public AsnType
{
public:
  ConnectionID* retrievedConnection;
  SubjectDeviceID* retrievingDevice;
  LocalConnectionState* localConnectionInfo;
  EventCause* cause;

 RetrievedEventInfo( MemBlock* mb );
 RetrievedEventInfo ( MemBlock* mb, const RetrievedEventInfo & );
 ~RetrievedEventInfo();
  AsnType *Clone() const;

  RetrievedEventInfo &operator = (const RetrievedEventInfo &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ServiceInitiatedEventInfo : public AsnType
{
public:
  ConnectionID* initiatedConnection;
  LocalConnectionState* localConnectionInfo;
  EventCause* cause;

 ServiceInitiatedEventInfo( MemBlock* mb );
 ServiceInitiatedEventInfo ( MemBlock* mb, const ServiceInitiatedEventInfo & );
 ~ServiceInitiatedEventInfo();
  AsnType *Clone() const;

  ServiceInitiatedEventInfo &operator = (const ServiceInitiatedEventInfo &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class TransferredEventInfo : public AsnType
{
public:
  ConnectionID* primaryOldCall;
  ConnectionID* secondaryOldCall;
  SubjectDeviceID* transferringDevice;
  SubjectDeviceID* transferredDevice;
  ConnectionList* transferredConnections;
  LocalConnectionState* localConnectionInfo;
  EventCause* cause;

 TransferredEventInfo( MemBlock* mb );
 TransferredEventInfo ( MemBlock* mb, const TransferredEventInfo & );
 ~TransferredEventInfo();
  AsnType *Clone() const;

  TransferredEventInfo &operator = (const TransferredEventInfo &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class CallInformationEventInfo : public AsnType
{
public:
  ConnectionID* connection;
  SubjectDeviceID* device;
  AccountInfo* accountInfo;
  AuthCode* authorisationCode;

 CallInformationEventInfo( MemBlock* mb );
 CallInformationEventInfo ( MemBlock* mb, const CallInformationEventInfo & );
 ~CallInformationEventInfo();
  AsnType *Clone() const;

  CallInformationEventInfo &operator = (const CallInformationEventInfo &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class DoNotDisturbEventInfo : public AsnType
{
public:
  SubjectDeviceID* device;
  AsnBool doNotDisturbOn;

 DoNotDisturbEventInfo( MemBlock* mb );
 DoNotDisturbEventInfo ( MemBlock* mb, const DoNotDisturbEventInfo & );
 ~DoNotDisturbEventInfo();
  AsnType *Clone() const;

  DoNotDisturbEventInfo &operator = (const DoNotDisturbEventInfo &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ForwardingEventInfo : public AsnType
{
public:
  SubjectDeviceID* device;
  ForwardParameter* forwardingInformation;
  SubjectDeviceID* forwardedTo;

 ForwardingEventInfo( MemBlock* mb );
 ForwardingEventInfo ( MemBlock* mb, const ForwardingEventInfo & );
 ~ForwardingEventInfo();
  AsnType *Clone() const;

  ForwardingEventInfo &operator = (const ForwardingEventInfo &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class MessageWaitingEventInfo : public AsnType
{
public:
  CalledDeviceID* deviceForMessage;
  SubjectDeviceID* invokingDevice;
  AsnBool messageWaitingOn;

 MessageWaitingEventInfo( MemBlock* mb );
 MessageWaitingEventInfo ( MemBlock* mb, const MessageWaitingEventInfo & );
 ~MessageWaitingEventInfo();
  AsnType *Clone() const;

  MessageWaitingEventInfo &operator = (const MessageWaitingEventInfo &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class LoggedOnEventInfo : public AsnType
{
public:
  SubjectDeviceID* agentDevice;
  AgentID* agentID;
  AgentGroup* agentGroup;
  AgentPassword* password;

 LoggedOnEventInfo( MemBlock* mb );
 LoggedOnEventInfo ( MemBlock* mb, const LoggedOnEventInfo & );
 ~LoggedOnEventInfo();
  AsnType *Clone() const;

  LoggedOnEventInfo &operator = (const LoggedOnEventInfo &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class LoggedOffEventInfo : public AsnType
{
public:
  SubjectDeviceID* agentDevice;
  AgentID* agentID;
  AgentGroup* agentGroup;

 LoggedOffEventInfo( MemBlock* mb );
 LoggedOffEventInfo ( MemBlock* mb, const LoggedOffEventInfo & );
 ~LoggedOffEventInfo();
  AsnType *Clone() const;

  LoggedOffEventInfo &operator = (const LoggedOffEventInfo &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class NotReadyEventInfo : public AsnType
{
public:
  SubjectDeviceID* agentDevice;
  AgentID* agentID;

 NotReadyEventInfo( MemBlock* mb );
 NotReadyEventInfo ( MemBlock* mb, const NotReadyEventInfo & );
 ~NotReadyEventInfo();
  AsnType *Clone() const;

  NotReadyEventInfo &operator = (const NotReadyEventInfo &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class ReadyEventInfo : public AsnType
{
public:
  SubjectDeviceID* agentDevice;
  AgentID* agentID;

 ReadyEventInfo( MemBlock* mb );
 ReadyEventInfo ( MemBlock* mb, const ReadyEventInfo & );
 ~ReadyEventInfo();
  AsnType *Clone() const;

  ReadyEventInfo &operator = (const ReadyEventInfo &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class WorkNotReadyEventInfo : public AsnType
{
public:
  SubjectDeviceID* agentDevice;
  AgentID* agentID;

 WorkNotReadyEventInfo( MemBlock* mb );
 WorkNotReadyEventInfo ( MemBlock* mb, const WorkNotReadyEventInfo & );
 ~WorkNotReadyEventInfo();
  AsnType *Clone() const;

  WorkNotReadyEventInfo &operator = (const WorkNotReadyEventInfo &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class WorkReadyEventInfo : public AsnType
{
public:
  SubjectDeviceID* agentDevice;
  AgentID* agentID;

 WorkReadyEventInfo( MemBlock* mb );
 WorkReadyEventInfo ( MemBlock* mb, const WorkReadyEventInfo & );
 ~WorkReadyEventInfo();
  AsnType *Clone() const;

  WorkReadyEventInfo &operator = (const WorkReadyEventInfo &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class BackInServiceEventInfo : public AsnType
{
public:
  DeviceID* device;
  EventCause* cause;

 BackInServiceEventInfo( MemBlock* mb );
 BackInServiceEventInfo ( MemBlock* mb, const BackInServiceEventInfo & );
 ~BackInServiceEventInfo();
  AsnType *Clone() const;

  BackInServiceEventInfo &operator = (const BackInServiceEventInfo &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};


class OutOfServiceEventInfo : public AsnType
{
public:
  DeviceID* device;
  EventCause* cause;

 OutOfServiceEventInfo( MemBlock* mb );
 OutOfServiceEventInfo ( MemBlock* mb, const OutOfServiceEventInfo & );
 ~OutOfServiceEventInfo();
  AsnType *Clone() const;

  OutOfServiceEventInfo &operator = (const OutOfServiceEventInfo &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print ( CTsvcLIB::LOG& os ) const;
};

///////////////////////////////////////////////////////////////////////////////
// Constants' values declarations namespace

   extern const AsnInt alternateCall;
   extern const AsnInt answerCall;
   extern const AsnInt callCompletion;
   extern const AsnInt clearCall;
   extern const AsnInt clearConnection;
   extern const AsnInt conferenceCall;
   extern const AsnInt consultationCall;
   extern const AsnInt divertCall;
   extern const AsnInt holdCall;
   extern const AsnInt makeCall;
   extern const AsnInt makePredictiveCall;
   extern const AsnInt queryDevice;
   extern const AsnInt reconnectCall;
   extern const AsnInt retrieveCall;
   extern const AsnInt setFeature;
   extern const AsnInt transferCall;
   extern const AsnInt cSTAEventReport;
   extern const AsnInt callCleared;
   extern const AsnInt conferenced;
   extern const AsnInt connectionCleared;
   extern const AsnInt delivered;
   extern const AsnInt diverted;
   extern const AsnInt established;
   extern const AsnInt failed;
   extern const AsnInt held;
   extern const AsnInt networkReached;
   extern const AsnInt originated;
   extern const AsnInt queued;
   extern const AsnInt retrieved;
   extern const AsnInt serviceInitiated;
   extern const AsnInt transferred;
   extern const AsnInt callInformation;
   extern const AsnInt doNotDisturb;
   extern const AsnInt forwarding;
   extern const AsnInt messageWaiting;
   extern const AsnInt loggedOn;
   extern const AsnInt loggedOff;
   extern const AsnInt notReady;
   extern const AsnInt ready;
   extern const AsnInt workNotReady;
   extern const AsnInt workReady;
   extern const AsnInt backInService;
   extern const AsnInt outOfService;
   extern const AsnInt privateEvt;
   extern const AsnInt routeRequest;
   extern const AsnInt reRouteRequest;
   extern const AsnInt routeSelectRequest;
   extern const AsnInt routeUsedRequest;
   extern const AsnInt routeEndRequest;
   extern const AsnInt escapeService;
   extern const AsnInt systemStatus;
   extern const AsnInt monitorStart;
   extern const AsnInt changeMonitorFilter;
   extern const AsnInt monitorStop;
   extern const AsnInt snapshotDevice;
   extern const AsnInt snapshotCall;
   extern const AsnInt universalFailure;
   extern const AsnOid escEnterDTMF;
   extern const AsnOid escCancelCallBack;
   extern const AsnOid escMessageDiversion;
   extern const AsnOid escAccountCode;
   extern const AsnOid escAuthorizationCode;
   extern const AsnOid escPressProgrammableKey;
   extern const AsnOid escAssociateData;
   extern const AsnOid escForwardACDGroup;
   extern const AsnOid escQueryMsgDiversionStrings;
   extern const AsnOid escQueryFeatureAndResponse;
   extern const AsnOid escSetFeatureAndResponse;

///////////////////////////////////////////////////////////////////////////////
} // namespace ASN

#endif /* conditional include of CSTA.h */
