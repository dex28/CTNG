/*
    Project: CSTALib

    Module: CSTAConnServices.Cpp

    Description: Device class implementation -- CSTA Services methods

    Copyright (c) 2002,2003 By Mikica B Kocic
    Copyright (c) 2002,2003 By IPTC Technology Communication AB
*/

#include "CSTA-Lib.h"

using namespace ASN;
using namespace CTsvcLIB;

/////////////////////////////////////////////////////////////////////////////
namespace MidCSTA
{

static CalledDeviceID* BuildCalledDevice( MemBlock* mem, const char* devId2Call )
{
    IA5String* digits2call = new(mem) IA5String(mem);
        *digits2call = devId2Call;

    ExtendedDeviceID* dev2call = new(mem) ExtendedDeviceID(mem);
        dev2call->choiceId = ExtendedDeviceID::dialingNumberCid;
        dev2call->dialingNumber = digits2call;

    CalledDeviceID* calledDev = new(mem) CalledDeviceID(mem);
        calledDev->choiceId = CalledDeviceID::deviceIdentifierCid;
        calledDev->deviceIdentifier = dev2call;

    return calledDev;
    }

static CSTACommonArguments* BuildCommonArgs( MemBlock* mem, CSTA_Extensions* exts )
{
    if ( ! exts || exts->outOID.Len() == 0 )
        return NULL;

    CSTACommonArgumentsSeqOf* comargsSeq = new(mem) CSTACommonArgumentsSeqOf(mem);

    CSTAPrivateData* extensions = comargsSeq->Append ();

    extensions->manufacturer.Set( exts->outOID.Ptr (), exts->outOID.Len () );
    extensions->data.SetTypeBy( extensions->manufacturer );
    extensions->data.encodeLenAsEric = true;
    extensions->data.octetLen = exts->outData.Len ();
    extensions->data.octs = new(mem) uint8[ exts->outData.Len () ];
    ::memcpy( extensions->data.octs, exts->outData.Ptr (), exts->outData.Len () );

    CSTACommonArguments* comargs = new(mem) CSTACommonArguments(mem);
        comargs->security = NULL;
        comargs->privateData = comargsSeq;

    return comargs;
    }

static void ParsePrivateData( CSTAPrivateData* privateData, CSTA_Extensions* exts )
{
    if ( ! privateData || ! exts )
        return;

    exts->inOID = privateData->manufacturer;
    exts->inData = privateData->data.toUSTR ();
    }

/////////////////////////////////////////////////////////////////////////////
// Device class CSTA Services implementation

ErrorCode Device::MonitorStart( CSTA_Extensions* exts )
{
    connMutex.Lock ();

    if ( ! monitorID.IsNULL () )
    {
        connMutex.Unlock ();
        return CSTA_MONITOR_ALREADY_OPEN;
        }

    connMutex.Unlock ();

    TRACE( this << " ----- Device::MonitorStart; Device " << devID );

    try
    {
        MemBlock* mem = system->AllocateOutboundMemBlock ();
        InvokeResponse response( mem );

        // Construct CSTAapdu, bottom up.
        //
        MonitorObject* obj = new(mem) MonitorObject(mem);
            obj->choiceId = CSTAObject::deviceObjectCid;
            obj->deviceObject = devID.BuildDeviceID(mem);

        MonitorStartArgument* arg = new(mem) MonitorStartArgument(mem);
            arg->monitorObject = obj;
            arg->monitorFilter = NULL;

        ErrorCode rc = ROSE_Invoke( response, OperationIDType::monitorStart, arg );

        if ( rc != CTNG_NO_ERROR )
        {
            Ptr<CBI_MonitorStarted> cbi = new CBI_MonitorStarted;
            cbi->errCode = rc;
            cbQueue.Put( cbi );
            return rc;
            }

        CSTAapdu* resp = response.GetAPDU ();
        TRASSERT( resp->choiceId == ROSEapdu::resultApduCid );
        TRASSERT( resp->resultApdu->rORSapduSeq->result->intId == OperationIDType::monitorStart );

        MonitorStartResult* result = (MonitorStartResult*) resp->resultApdu->rORSapduSeq->result->value;

        connMutex.Lock ();

        monitorID = USTR( result->crossRefIdentifier );

        connMutex.Unlock ();

        Ptr<CBI_MonitorStarted> cbi = new CBI_MonitorStarted;
        cbi->errCode = rc;
        cbQueue.Put( cbi );

        TRACE( this << " ----- Device::MonitorStart; Got Cross Reference ID " 
            << USTR( result->crossRefIdentifier ) );
        }
    catch( ... )
    {
        return CTNG_EXCEPTION_ERROR;
        }

    return CTNG_NO_ERROR;
    }

ErrorCode Device::ChangeMonitorFilter( CSTA_Extensions* exts )
{
    connMutex.Lock ();

    if ( monitorID.IsNULL () )
    {
        connMutex.Unlock ();
        return CSTA_MONITOR_NOT_STARTED;
        }

    USTR crossRef;
    monitorID.CopyTo( crossRef );

    connMutex.Unlock ();

    TRACE( this << " ----- Device::ChangeMonitorFilter; Device " << devID 
            << ", Monitor " << crossRef );

    try
    {
        MemBlock* mem = system->AllocateOutboundMemBlock ();
        InvokeResponse response( mem );

        // Construct CSTAapdu, bottom up.
        //
        CallFilter* call = new(mem) CallFilter(mem);
            call->SetBit( CallFilter::callCleared );
            call->SetBit( CallFilter::conferenced );
            call->SetBit( CallFilter::connectionCleared );
            call->SetBit( CallFilter::delivered );
            call->SetBit( CallFilter::diverted );
            call->SetBit( CallFilter::established );
            call->SetBit( CallFilter::failed );
            call->SetBit( CallFilter::held );
            call->SetBit( CallFilter::networkReached );
            call->SetBit( CallFilter::originated );
            call->SetBit( CallFilter::queued );
            call->SetBit( CallFilter::retrieved );
            call->SetBit( CallFilter::serviceInitiated );
            call->SetBit( CallFilter::transferred );

        FeatureFilter* feature = new(mem) FeatureFilter(mem);
            feature->SetBit( FeatureFilter::callInformation );
            feature->SetBit( FeatureFilter::doNotDisturb );
            feature->SetBit( FeatureFilter::forwarding );
            feature->SetBit( FeatureFilter::messageWaiting );

        AgentFilter* agent = new(mem) AgentFilter(mem);
            agent->SetBit( AgentFilter::loggedOn );
            agent->SetBit( AgentFilter::loggedOff );
            agent->SetBit( AgentFilter::notReady );
            agent->SetBit( AgentFilter::ready );
            agent->SetBit( AgentFilter::workNotReady );
            agent->SetBit( AgentFilter::workReady );

        MaintenanceFilter* maintenance = new(mem) MaintenanceFilter(mem);
            maintenance->SetBit( MaintenanceFilter::backInService );
            maintenance->SetBit( MaintenanceFilter::outOfService );

        MonitorFilter* filter = new(mem) MonitorFilter(mem);
            filter->call = call;
            filter->feature = feature;
            filter->agent = agent;
            filter->maintenance = maintenance;
            filter->private1 = new(mem) AsnBool(mem);

        ChangeMonitorFilterArgument* arg = new(mem) ChangeMonitorFilterArgument(mem);
            arg->monitorCrossRefID.Set( crossRef.Ptr(), crossRef.Len () );
            arg->filterlist = filter;
            arg->extensions = BuildCommonArgs( mem, exts );
    
        OperationArgument* oparg = new(mem) OperationArgument(mem);
            oparg->intId = OperationIDType::changeMonitorFilter;
            oparg->value = arg;

        ErrorCode rc = ROSE_Invoke( response, OperationIDType::changeMonitorFilter, arg );

        if ( rc != CTNG_NO_ERROR )
            return rc;

        CSTAapdu* resp = response.GetAPDU ();
        TRASSERT( resp->choiceId == ROSEapdu::resultApduCid );

        ChangeMonitorFilterResult* result = (ChangeMonitorFilterResult*) resp->resultApdu->rORSapduSeq->result->value;
        }
    catch( ... )
    {
        return CTNG_EXCEPTION_ERROR;
        }

    return CTNG_NO_ERROR;
    }

ErrorCode Device::MonitorStop( CSTA_Extensions* exts )
{
    connMutex.Lock ();

    if ( monitorID.IsNULL () )
    {
        connMutex.Unlock ();
        return CSTA_MONITOR_NOT_STARTED;
        }

    USTR crossRef;
    monitorID.CopyTo( crossRef );
    monitorID.SetNULL ();

    connMutex.Unlock ();

    TRACE( this << " ----- Device::MonitorStop; Device " << devID 
            << ", Monitor " << crossRef );

    try
    {
        MemBlock* mem = system->AllocateOutboundMemBlock ();
        InvokeResponse response( mem );

        // Construct CSTAapdu, bottom up.
        //
        MonitorCrossRefID* crossRefId = new(mem) MonitorCrossRefID( mem );
            crossRefId->Set( crossRef.Ptr(), crossRef.Len () );

        MonitorStopArgument* arg = new(mem) MonitorStopArgument(mem);
            arg->choiceId = MonitorStopArgument::crossRefIdentifierCid;
            arg->crossRefIdentifier = crossRefId;
    
        OperationArgument* oparg = new(mem) OperationArgument(mem);
            oparg->intId = OperationIDType::monitorStop;
            oparg->value = arg;

        ErrorCode rc = ROSE_Invoke( response, OperationIDType::monitorStop, arg );

        if ( rc != CTNG_NO_ERROR )
            return rc;

        CSTAapdu* resp = response.GetAPDU ();
        TRASSERT( resp->choiceId == ROSEapdu::resultApduCid );

        MonitorStopResult* result = (MonitorStopResult*) resp->resultApdu->rORSapduSeq->result->value;
        }
    catch( ... )
    {
        return CTNG_EXCEPTION_ERROR;
        }

    return CTNG_NO_ERROR;
    }

ErrorCode Device::EscapeService( CSTA_Extensions& exts )
{
    TRACE( this << " ----- Device::EscapeService; Device " << devID
        << ", outOID [" << exts.outOID << "], outData [" << exts.outData 
        << "]" );

    try
    {
        MemBlock* mem = system->AllocateOutboundMemBlock ();
        InvokeResponse response( mem );

        // EscapeServiceArgument is by definition the same as CSTACommonArguments !
        //
        EscapeServiceArgument* arg = BuildCommonArgs( mem, &exts );

        ErrorCode rc = ROSE_Invoke( response, OperationIDType::escapeService, arg );

        if ( rc != CTNG_NO_ERROR )
            return rc;

        CSTAapdu* resp = response.GetAPDU ();
        TRASSERT( resp->choiceId == ROSEapdu::resultApduCid );
        TRASSERT( resp->resultApdu->rORSapduSeq->result->intId == OperationIDType::escapeService ); 

        EscapeServiceResult* result = (EscapeServiceResult*) resp->resultApdu->rORSapduSeq->result->value;

        if ( result->choiceId == EscapeServiceResult::extensionsCid )
        {
            ParsePrivateData( result->extensions, &exts );
            }

        TRACE( this << " ----- Device::EscapeService; Got "
            << " inOID [" << exts.inOID << "], inData [" << exts.inData 
            << "]" );
        }
    catch( ... )
    {
        return CTNG_EXCEPTION_ERROR;
        }

    return CTNG_NO_ERROR;
    }

ErrorCode Device::SystemStatus( const SystemStatusType systemStatusId, CSTA_Extensions* exts )
{
    TRACE( this << " ----- Device::SystemStatus; Status " << System::Verbose( systemStatusId ) );

    try
    {
        MemBlock* mem = system->AllocateOutboundMemBlock ();
        InvokeResponse response( mem );

        // Construct CSTAapdu, bottom up.
        //
        ASN::SystemStatus* sysStat = new(mem) ASN::SystemStatus(mem);
            sysStat->Set( systemStatusId );

        SystemStatusArgument* arg = new(mem) SystemStatusArgument(mem);
            arg->choiceId = SystemStatusArgument::systemStatusCid;
            arg->systemStatus = sysStat;
    
        ErrorCode rc = ROSE_Invoke( response, OperationIDType::systemStatus, arg );

        if ( rc != CTNG_NO_ERROR )
            return rc;

        CSTAapdu* resp = response.GetAPDU ();
        TRASSERT( resp->choiceId == ROSEapdu::resultApduCid );

        SystemStatusResult* result = (SystemStatusResult*) resp->resultApdu->rORSapduSeq->result->value;
        }
    catch( ... )
    {
        return CTNG_EXCEPTION_ERROR;
        }

    return CTNG_NO_ERROR;
    }

ErrorCode Device::SnapshotDevice( CSTA_Extensions* exts )
{
    TRACE( this << " ----- Device::SnapshotDevice; Device " << devID );

    try
    {
        MemBlock* mem = system->AllocateOutboundMemBlock ();
        InvokeResponse response( mem );

        // Construct CSTAapdu, bottom up.
        //
        SnapshotDeviceArgument* arg = new(mem) SnapshotDeviceArgument(mem);
            arg->choiceId = SnapshotDeviceArgument::snapshotObjectCid;
            arg->snapshotObject = devID.BuildDeviceID(mem);
    
        ErrorCode rc = ROSE_Invoke( response, OperationIDType::snapshotDevice, arg );

        if ( rc != CTNG_NO_ERROR )
            return rc;

        CSTAapdu* resp = response.GetAPDU ();
        TRASSERT( resp->choiceId == ROSEapdu::resultApduCid );

        SnapshotDeviceResult* result = (SnapshotDeviceResult*) resp->resultApdu->rORSapduSeq->result->value;

        TRASSERT( result->choiceId == SnapshotDeviceResult::snapshotDataCid );
        SnapshotDeviceData* data = result->snapshotData;

        result->snapshotData->SetCurrToFirst();

        while ( result->snapshotData->Curr () )
        {
            SnapshotDeviceResponseInfo* info = result->snapshotData->Curr();

            TRASSERT( info->callIdentifier->device->choiceId == ConnectionIDChoice::staticIDCid );
            TRASSERT( info->localCallState->choiceId == CallState::simpleCid );
            TRASSERT( info->callIdentifier->device->staticID->choiceId == DeviceID::dialingNumberCid );

            if ( info->callIdentifier->call )
            {
                USTR callId( info->callIdentifier->call );
                deviceIdType devID( info->callIdentifier->device->staticID->dialingNumber );
                AsnIntType state = (AsnIntType)*info->localCallState->simple;

                TRACE( this 
                    << " SnapshotDevice: devID: " << devID 
                    << ", callId: " << callId 
                    << ", state: " << state 
                    );
                }

            result->snapshotData->GoNext ();
            }
        }
    catch( ... )
    {
        return CTNG_EXCEPTION_ERROR;
        }

    return CTNG_NO_ERROR;
    }

ErrorCode Device::SnapshotCall( const connectionIdType& connId, CSTA_Extensions* exts )
{
    TRACE( this << " ----- Device::SnapshotCall; Call " << connId );

    try
    {
        MemBlock* mem = system->AllocateOutboundMemBlock ();
        InvokeResponse response( mem );

        // Construct CSTAapdu, bottom up.
        //
        SnapshotCallArgument* arg = new(mem) SnapshotCallArgument(mem);
            arg->choiceId = SnapshotCallArgument::snapshotObjectCid;
            arg->snapshotObject = connId.BuildConnectionID(mem);
    
        ErrorCode rc = ROSE_Invoke( response, OperationIDType::snapshotCall, arg );

        if ( rc != CTNG_NO_ERROR )
            return rc;

        CSTAapdu* resp = response.GetAPDU ();
        TRASSERT( resp->choiceId == ROSEapdu::resultApduCid );

        SnapshotCallResult* result = (SnapshotCallResult*) resp->resultApdu->rORSapduSeq->result->value;
        }
    catch( ... )
    {
        return CTNG_EXCEPTION_ERROR;
        }

    return CTNG_NO_ERROR;
    }

ErrorCode Device::AlternateCall( const connectionIdType& held, const connectionIdType& active, CSTA_Extensions* exts )
{
    TRACE( this << " ----- Device::AlternateCall; Held " << held << ", Active " << active );

    try
    {
        MemBlock* mem = system->AllocateOutboundMemBlock ();
        InvokeResponse response( mem );

        // Construct CSTAapdu, bottom up.
        //
        ConnectionDetailsSeq* bothCalls = new(mem) ConnectionDetailsSeq(mem);
            bothCalls->activeCall = active.BuildConnectionID(mem);
            bothCalls->heldCall = held.BuildConnectionID(mem);

        ConnectionDetails* callsInvolved = new(mem) ConnectionDetails(mem);
            callsInvolved->choiceId = ConnectionDetails::bothCallsCid;
            callsInvolved->bothCalls = bothCalls;

        AlternateCallArgument* arg = new(mem) AlternateCallArgument(mem);

        // Provide CSTA extensions

        CSTACommonArguments* comargs = BuildCommonArgs( mem, exts );

        if ( ! comargs )
        {
            // WITHOUT CSTACommonArguments
            arg->choiceId = AlternateCallArgument::callsInvolvedCid;
            arg->callsInvolved = callsInvolved;
            }
        else
        {
            AlternateCallArgumentSeq* argSeq = new(mem) AlternateCallArgumentSeq(mem);
                argSeq->callsInvolved = callsInvolved;
                argSeq->extensions = comargs;

            arg->choiceId = AlternateCallArgument::alternateCallArgumentSeqCid;
            arg->alternateCallArgumentSeq = argSeq;
            }

        ErrorCode rc = ROSE_Invoke( response, OperationIDType::alternateCall, arg );

        if ( rc != CTNG_NO_ERROR )
            return rc;

        CSTAapdu* resp = response.GetAPDU ();
        TRASSERT( resp->choiceId == ROSEapdu::resultApduCid );

        AlternateCallResult* result = (AlternateCallResult*) resp->resultApdu->rORSapduSeq->result->value;

        // Check for CSTA extensions in result
        //
        if ( result->choiceId == AlternateCallResult::extensionsCid )
        {
            ParsePrivateData( result->extensions, exts );
            }
        }
    catch( ... )
    {
        return CTNG_EXCEPTION_ERROR;
        }

    return CTNG_NO_ERROR;
    }

ErrorCode Device::AnswerCall( const connectionIdType& connId, CSTA_Extensions* exts )
{
    TRACE( this << " ----- Device::AnswerCall; Connection " << connId );

    try
    {
        MemBlock* mem = system->AllocateOutboundMemBlock ();
        InvokeResponse response( mem );

        // Construct CSTAapdu, bottom up.
        //
        AnswerCallArgument* arg = new(mem) AnswerCallArgument(mem);

        // Provide CSTA extensions

        CSTACommonArguments* comargs = BuildCommonArgs( mem, exts );

        if ( ! comargs )
        {
            // WITHOUT CSTACommonArguments
            arg->choiceId = AnswerCallArgument::callToBeAnsweredCid;
            arg->callToBeAnswered = connId.BuildConnectionID(mem);
            }
        else
        {
            AnswerCallArgumentSeq* argSeq = new(mem) AnswerCallArgumentSeq(mem);
                argSeq->callToBeAnswered = connId.BuildConnectionID(mem);
                argSeq->extensions = comargs;

            arg->choiceId = AnswerCallArgument::answerCallArgumentSeqCid;
            arg->answerCallArgumentSeq = argSeq;
            }

        ErrorCode rc = ROSE_Invoke( response, OperationIDType::answerCall, arg );

        if ( rc != CTNG_NO_ERROR )
            return rc;

        CSTAapdu* resp = response.GetAPDU ();
        TRASSERT( resp->choiceId == ROSEapdu::resultApduCid );

        AnswerCallResult* result = (AnswerCallResult*) resp->resultApdu->rORSapduSeq->result->value;

        // Check for CSTA extensions in result
        //
        if ( result->choiceId == AnswerCallResult::extensionsCid )
        {
            ParsePrivateData( result->extensions, exts );
            }
        }
    catch( ... )
    {
        return CTNG_EXCEPTION_ERROR;
        }

    return CTNG_NO_ERROR;
    }

ErrorCode Device::CallCompletion( const connectionIdType& connId, FeatureInfoType featureId, CSTA_Extensions* exts )
{
    TRACE( this << " ----- Device::CallCompletion; Connection " << connId );

    try
    {
        MemBlock* mem = system->AllocateOutboundMemBlock ();
        InvokeResponse response( mem );

        // Construct CSTAapdu, bottom up.
        //
        FeatureInfo* featureInfo = new(mem) FeatureInfo(mem);

        switch( featureId )
        {
            default:
            case fi_campon:
                featureInfo->choiceId = FeatureInfo::camponCid;
                featureInfo->campon = connId.BuildConnectionID(mem);
                break;
            case fi_callback:
                featureInfo->choiceId = FeatureInfo::callbackCid;
                featureInfo->callback = connId.BuildConnectionID(mem);
                break;
            case fi_intrude:
                featureInfo->choiceId = FeatureInfo::intrudeCid;
                featureInfo->intrude = connId.BuildConnectionID(mem);
                break;
            case fi_callbackMessage:
                featureInfo->choiceId = FeatureInfo::callbackMessageCid;
                featureInfo->callbackMessage = connId.BuildConnectionID(mem);
                break;
            }

        CallCompletionArgument* arg = new(mem) CallCompletionArgument(mem);
    
        // Provide CSTA extensions

        CSTACommonArguments* comargs = BuildCommonArgs( mem, exts );

        if ( ! comargs )
        {
            // WITHOUT CSTACommonArguments
            arg->choiceId = CallCompletionArgument::featureInfoCid;
            arg->featureInfo = featureInfo;
            }
        else
        {
            CallCompletionArgumentSeq* argSeq = new(mem) CallCompletionArgumentSeq(mem);
                argSeq->featureInfo = featureInfo;
                argSeq->extensions = comargs;

            arg->choiceId = CallCompletionArgument::callCompletionArgumentSeqCid;
            arg->callCompletionArgumentSeq = argSeq;
            }

        ErrorCode rc = ROSE_Invoke( response, OperationIDType::callCompletion, arg );

        if ( rc != CTNG_NO_ERROR )
            return rc;

        CSTAapdu* resp = response.GetAPDU ();
        TRASSERT( resp->choiceId == ROSEapdu::resultApduCid );

        CallCompletionResult* result = (CallCompletionResult*) resp->resultApdu->rORSapduSeq->result->value;

        // Check for CSTA extensions in result
        //
        if ( result->choiceId == CallCompletionResult::extensionsCid )
        {
            ParsePrivateData( result->extensions, exts );
            }
        }
    catch( ... )
    {
        return CTNG_EXCEPTION_ERROR;
        }

    return CTNG_NO_ERROR;
    }

ErrorCode Device::ClearConnection( const connectionIdType& connId, CSTA_Extensions* exts )
{
    TRACE( this << " ----- Device::ClearConnection; Connection " << connId );

    try
    {
        MemBlock* mem = system->AllocateOutboundMemBlock ();
        InvokeResponse response( mem );

        // Construct CSTAapdu, bottom up.
        //
        ClearConnectionArgument* arg = new(mem) ClearConnectionArgument(mem);
            arg->choiceId = ClearConnectionArgument::connectionToBeClearedCid;
            arg->connectionToBeCleared = connId.BuildConnectionID( mem );
    
        ErrorCode rc = ROSE_Invoke( response, OperationIDType::clearConnection, arg );

        if ( rc != CTNG_NO_ERROR )
            return rc;

        CSTAapdu* resp = response.GetAPDU ();
        TRASSERT( resp->choiceId == ROSEapdu::resultApduCid );

        ClearConnectionResult* result = (ClearConnectionResult*) resp->resultApdu->rORSapduSeq->result->value;
        }
    catch( ... )
    {
        return CTNG_EXCEPTION_ERROR;
        }

    return CTNG_NO_ERROR;
    }

ErrorCode Device::ClearCall( const connectionIdType& connId, CSTA_Extensions* exts )
{
    TRACE( this << " ----- Device::ClearCall; Connection " << connId );

    try
    {
        MemBlock* mem = system->AllocateOutboundMemBlock ();
        InvokeResponse response( mem );

        // Construct CSTAapdu, bottom up.
        //
        ClearCallArgument* arg = new(mem) ClearCallArgument(mem);
            arg->choiceId = ClearCallArgument::callToBeClearedCid;
            arg->callToBeCleared = connId.BuildConnectionID(mem);
    
        ErrorCode rc = ROSE_Invoke( response, OperationIDType::clearCall, arg );

        if ( rc != CTNG_NO_ERROR )
            return rc;

        CSTAapdu* resp = response.GetAPDU ();
        TRASSERT( resp->choiceId == ROSEapdu::resultApduCid );

        ClearCallResult* result = (ClearCallResult*) resp->resultApdu->rORSapduSeq->result->value;
        }
    catch( ... )
    {
        return CTNG_EXCEPTION_ERROR;
        }

    return CTNG_NO_ERROR;
    }

ErrorCode Device::ConferenceCall( const connectionIdType& held, const connectionIdType& active, connectionIdType& conferenceCall, CSTA_Extensions* exts )
{
    TRACE( this << " ----- Device::ConferenceCall; Held " << held << ", Active " << active );

    try
    {
        MemBlock* mem = system->AllocateOutboundMemBlock ();
        InvokeResponse response( mem );

        // Construct CSTAapdu, bottom up.
        //
        ConnectionDetailsSeq* bothCalls = new(mem) ConnectionDetailsSeq(mem);
            bothCalls->activeCall = active.BuildConnectionID(mem);
            bothCalls->heldCall = held.BuildConnectionID(mem);

        ConnectionDetails* callsInvolved = new(mem) ConnectionDetails(mem);
            callsInvolved->choiceId = ConnectionDetails::bothCallsCid;
            callsInvolved->bothCalls = bothCalls;

        ConferenceCallArgument* arg = new(mem) ConferenceCallArgument(mem);

        // Provide CSTA extensions

        CSTACommonArguments* comargs = BuildCommonArgs( mem, exts );

        if ( ! comargs )
        {
            // WITHOUT CSTACommonArguments
            arg->choiceId = ConferenceCallArgument::callsInvolvedCid;
            arg->callsInvolved = callsInvolved;
            }
        else
        {
            ConferenceCallArgumentSeq* argSeq = new(mem) ConferenceCallArgumentSeq(mem);
                argSeq->callsInvolved = callsInvolved;
                argSeq->extensions = comargs;

            arg->choiceId = ConferenceCallArgument::conferenceCallArgumentSeqCid;
            arg->conferenceCallArgumentSeq = argSeq;
            }

        ErrorCode rc = ROSE_Invoke( response, OperationIDType::conferenceCall, arg );

        if ( rc != CTNG_NO_ERROR )
            return rc;

        CSTAapdu* resp = response.GetAPDU ();
        TRASSERT( resp->choiceId == ROSEapdu::resultApduCid );

        ConferenceCallResult* result = (ConferenceCallResult*) resp->resultApdu->rORSapduSeq->result->value;

        // Check for CSTA extensions in result
        //
        ParsePrivateData( result->extensions, exts );

        if ( result->conferenceCall )
            conferenceCall = connectionIdType( result->conferenceCall );

        // TODO: parse connection list. Anyhow, we will get it in Conferencered event!
        }
    catch( ... )
    {
        return CTNG_EXCEPTION_ERROR;
        }

    return CTNG_NO_ERROR;
    }

ErrorCode Device::ConsultationCall( const connectionIdType& connId, const char* deviceId2call, connectionIdType& initiatedConnId, CSTA_Extensions* exts )
{
    TRACE( this << " ----- Device::ConsultationCall; Connection " << connId );

    try
    {
        MemBlock* mem = system->AllocateOutboundMemBlock ();
        InvokeResponse response( mem );

        // Construct CSTAapdu, bottom up.
        //
        ConsultationCallArgument* arg = new(mem) ConsultationCallArgument(mem);
            arg->existingCall = connId.BuildConnectionID(mem);
            arg->calledDirectoryNumber = BuildCalledDevice( mem, deviceId2call );
            arg->extensions = BuildCommonArgs( mem, exts );
    
        ErrorCode rc = ROSE_Invoke( response, OperationIDType::consultationCall, arg );

        if ( rc != CTNG_NO_ERROR )
            return rc;

        CSTAapdu* resp = response.GetAPDU ();
        TRASSERT( resp->choiceId == ROSEapdu::resultApduCid );

        ConsultationCallResult* result = (ConsultationCallResult*) resp->resultApdu->rORSapduSeq->result->value;

        ConnectionID* initiatedCall = NULL;

        // Check for CSTA extensions in result
        //
        if ( result->choiceId == ConsultationCallResult::initiatedCallCid )
        {
            initiatedCall = result->initiatedCall;
            }
        else // Extensions found
        {
            initiatedCall = result->consultationCallResultSeq->initiatedCall;
            ParsePrivateData( result->consultationCallResultSeq->extensions, exts );
            }

        if ( initiatedCall )
        {
            TRASSERT( initiatedCall->device->choiceId == ConnectionIDChoice::staticIDCid );
            TRASSERT( initiatedCall->device->staticID->choiceId == DeviceID::dialingNumberCid );

            if ( initiatedCall->call )
                initiatedConnId = connectionIdType( initiatedCall );
            }

        TRACE( this << " ----- Device::ConsultationCall; Got Connection " << connId );
        }
    catch( ... )
    {
        return CTNG_EXCEPTION_ERROR;
        }

    return CTNG_NO_ERROR;
    }

ErrorCode Device::DivertCall_Deflect( const connectionIdType& conn, const char* newDestination, CSTA_Extensions* exts )
{
    TRACE( this << " ----- Device::DivertCall_Deflect; Connection " << conn
        << ", newDestination " << newDestination );

    try
    {
        MemBlock* mem = system->AllocateOutboundMemBlock ();
        InvokeResponse response( mem );

        // Construct CSTAapdu, bottom up.
        //
        DivertInfoSeq* deflinfo = new(mem) DivertInfoSeq(mem);
            deflinfo->callToBeDiverted = conn.BuildConnectionID( mem );
            deflinfo->newDestination = BuildCalledDevice( mem, newDestination );

        DivertInfo* dinfo = new(mem) DivertInfo(mem);
            dinfo->choiceId = DivertInfo::deflectCid;
            dinfo->deflect = deflinfo;

        DivertCallArgument* arg = new(mem) DivertCallArgument(mem);

        // Provide CSTA extensions

        CSTACommonArguments* comargs = BuildCommonArgs( mem, exts );

        if ( ! comargs )
        {
            // WITHOUT CSTACommonArguments
            arg->choiceId = DivertCallArgument::divertInfoCid;
            arg->divertInfo = dinfo;
            }
        else
        {
            DivertCallArgumentSeq* argSeq = new(mem) DivertCallArgumentSeq(mem);
                argSeq->deivertInfo = dinfo;
                argSeq->extensions = comargs;

            arg->choiceId = DivertCallArgument::divertCallArgumentSeqCid;
            arg->divertCallArgumentSeq = argSeq;
            }

        ErrorCode rc = ROSE_Invoke( response, OperationIDType::divertCall, arg );

        if ( rc != CTNG_NO_ERROR )
            return rc;

        CSTAapdu* resp = response.GetAPDU ();
        TRASSERT( resp->choiceId == ROSEapdu::resultApduCid );
        TRASSERT( resp->resultApdu->rORSapduSeq->result->intId == OperationIDType::divertCall ); 

        DivertCallResult* result = (DivertCallResult*) resp->resultApdu->rORSapduSeq->result->value;

        // Check for CSTA extensions in result
        //
        if ( result->choiceId == DivertCallResult::extensionsCid )
        {
            ParsePrivateData( result->extensions, exts );
            }
        }
    catch( ... )
    {
        return CTNG_EXCEPTION_ERROR;
        }

    return CTNG_NO_ERROR;
    }

ErrorCode Device::DivertCall_DirectedPickup( const connectionIdType& conn, const char* requestingDevice, CSTA_Extensions* exts )
{
    TRACE( this << " ----- Device::DivertCall_DirectedPickup; Connection " << conn
        << ", requestingDevice " << requestingDevice );

    try
    {
        MemBlock* mem = system->AllocateOutboundMemBlock ();
        InvokeResponse response( mem );

        // Construct CSTAapdu, bottom up.
        //
        DivertInfoSeq1* deflinfo = new(mem) DivertInfoSeq1(mem);
            deflinfo->callToBePickedUp = conn.BuildConnectionID( mem );
            deflinfo->requestingDevice = deviceIdType( requestingDevice ).BuildDeviceID(mem);

        DivertInfo* dinfo = new(mem) DivertInfo(mem);
            dinfo->choiceId = DivertInfo::pickupCid;
            dinfo->pickup = deflinfo;

        DivertCallArgument* arg = new(mem) DivertCallArgument(mem);

        // Provide CSTA extensions

        CSTACommonArguments* comargs = BuildCommonArgs( mem, exts );

        if ( ! comargs )
        {
            // WITHOUT CSTACommonArguments
            arg->choiceId = DivertCallArgument::divertInfoCid;
            arg->divertInfo = dinfo;
            }
        else
        {
            DivertCallArgumentSeq* argSeq = new(mem) DivertCallArgumentSeq(mem);
                argSeq->deivertInfo = dinfo;
                argSeq->extensions = comargs;

            arg->choiceId = DivertCallArgument::divertCallArgumentSeqCid;
            arg->divertCallArgumentSeq = argSeq;
            }

        ErrorCode rc = ROSE_Invoke( response, OperationIDType::divertCall, arg );

        if ( rc != CTNG_NO_ERROR )
            return rc;

        CSTAapdu* resp = response.GetAPDU ();
        TRASSERT( resp->choiceId == ROSEapdu::resultApduCid );
        TRASSERT( resp->resultApdu->rORSapduSeq->result->intId == OperationIDType::divertCall ); 

        DivertCallResult* result = (DivertCallResult*) resp->resultApdu->rORSapduSeq->result->value;

        // Check for CSTA extensions in result
        //
        if ( result->choiceId == DivertCallResult::extensionsCid )
        {
            ParsePrivateData( result->extensions, exts );
            }
        }
    catch( ... )
    {
        return CTNG_EXCEPTION_ERROR;
        }

    return CTNG_NO_ERROR;
    }

ErrorCode Device::DivertCall_GroupPickup( const char* groupDevice, CSTA_Extensions* exts )
{
    TRACE( this << " ----- Device::DivertCall_GroupPickup; Group " << groupDevice );

    try
    {
        MemBlock* mem = system->AllocateOutboundMemBlock ();
        InvokeResponse response( mem );

        // Construct CSTAapdu, bottom up.
        //
        DivertInfo* dinfo = new(mem) DivertInfo(mem);
            dinfo->choiceId = DivertInfo::groupCid;
            dinfo->group = deviceIdType( groupDevice ).BuildDeviceID(mem);

        DivertCallArgument* arg = new(mem) DivertCallArgument(mem);

        // Provide CSTA extensions

        CSTACommonArguments* comargs = BuildCommonArgs( mem, exts );

        if ( ! comargs )
        {
            // WITHOUT CSTACommonArguments
            arg->choiceId = DivertCallArgument::divertInfoCid;
            arg->divertInfo = dinfo;
            }
        else
        {
            DivertCallArgumentSeq* argSeq = new(mem) DivertCallArgumentSeq(mem);
                argSeq->deivertInfo = dinfo;
                argSeq->extensions = comargs;

            arg->choiceId = DivertCallArgument::divertCallArgumentSeqCid;
            arg->divertCallArgumentSeq = argSeq;
            }

        ErrorCode rc = ROSE_Invoke( response, OperationIDType::divertCall, arg );

        if ( rc != CTNG_NO_ERROR )
            return rc;

        CSTAapdu* resp = response.GetAPDU ();
        TRASSERT( resp->choiceId == ROSEapdu::resultApduCid );
        TRASSERT( resp->resultApdu->rORSapduSeq->result->intId == OperationIDType::divertCall ); 

        DivertCallResult* result = (DivertCallResult*) resp->resultApdu->rORSapduSeq->result->value;

        // Check for CSTA extensions in result
        //
        if ( result->choiceId == DivertCallResult::extensionsCid )
        {
            ParsePrivateData( result->extensions, exts );
            }
        }
    catch( ... )
    {
        return CTNG_EXCEPTION_ERROR;
        }

    return CTNG_NO_ERROR;
    }

ErrorCode Device::HoldCall( const connectionIdType& connId, bool connectionReservation, CSTA_Extensions* exts )
{
    TRACE( this << " ----- Device::HoldCall; Connection " << connId );

    try
    {
        MemBlock* mem = system->AllocateOutboundMemBlock ();
        InvokeResponse response( mem );

        // Construct CSTAapdu, bottom up.
        //
        HoldCallArgument* arg = new(mem) HoldCallArgument(mem);
            arg->callToBeHeld = connId.BuildConnectionID(mem);
            arg->connectionReservation = new(mem) AsnBool( mem, connectionReservation );
            arg->extensions = BuildCommonArgs( mem, exts );
    
        ErrorCode rc = ROSE_Invoke( response, OperationIDType::holdCall, arg );

        if ( rc != CTNG_NO_ERROR )
            return rc;

        CSTAapdu* resp = response.GetAPDU ();
        TRASSERT( resp->choiceId == ROSEapdu::resultApduCid );

        HoldCallResult* result = (HoldCallResult*) resp->resultApdu->rORSapduSeq->result->value;

        // Check for CSTA extensions in result
        //
        if ( result->choiceId == HoldCallResult::extensionsCid )
        {
            ParsePrivateData( result->extensions, exts );
            }
        }
    catch( ... )
    {
        return CTNG_EXCEPTION_ERROR;
        }

    return CTNG_NO_ERROR;
    }

ErrorCode Device::MakeCall( const char* deviceId2call, connectionIdType& connId, CSTA_Extensions* exts )
{
    TRACE( this << " ----- Device::MakeCall; Device "
        << devID << ", dev2call " << deviceId2call );

    try
    {
        MemBlock* mem = system->AllocateOutboundMemBlock ();
        InvokeResponse response( mem );

        // Construct CSTAapdu, bottom up.
        //
        MakeCallArgument* arg = new(mem) MakeCallArgument(mem);
            arg->callingDevice = devID.BuildDeviceID(mem);
            arg->calledDirectoryNumber = BuildCalledDevice( mem, deviceId2call );
            arg->extensions = BuildCommonArgs( mem, exts );
    
        ErrorCode rc = ROSE_Invoke( response, OperationIDType::makeCall, arg );

        if ( rc != CTNG_NO_ERROR )
            return rc;

        CSTAapdu* resp = response.GetAPDU ();
        TRASSERT( resp->choiceId == ROSEapdu::resultApduCid );
        TRASSERT( resp->resultApdu->rORSapduSeq->result->intId == OperationIDType::makeCall ); 

        MakeCallResult* result = (MakeCallResult*) resp->resultApdu->rORSapduSeq->result->value;

        ConnectionID* initiatedCall = NULL;

        // Check for CSTA extensions in result
        //
        if ( result->choiceId == MakeCallResult::initiatedCallCid )
        {
            initiatedCall = result->initiatedCall;
            }
        else // Extensions found
        {
            initiatedCall = result->makeCallResultSeq->initiatedCall;
            ParsePrivateData( result->makeCallResultSeq->extensions, exts );
            }

        if ( initiatedCall )
        {
            TRASSERT( initiatedCall->device->choiceId == ConnectionIDChoice::staticIDCid );
            TRASSERT( initiatedCall->device->staticID->choiceId == DeviceID::dialingNumberCid );

            if ( initiatedCall->call )
                connId = connectionIdType( initiatedCall );
            }

        TRACE( this << " ----- Device::MakeCall; Got Connection " << connId );
        }
    catch( ... )
    {
        return CTNG_EXCEPTION_ERROR;
        }

    return CTNG_NO_ERROR;
    }

ErrorCode Device::ReconnectCall( const connectionIdType& held, const connectionIdType& active, CSTA_Extensions* exts )
{
    TRACE( this << " ----- Device::ReconnectCall; Held " << held << ", Active " << active );

    try
    {
        MemBlock* mem = system->AllocateOutboundMemBlock ();
        InvokeResponse response( mem );

        // Construct CSTAapdu, bottom up.
        //
        ConnectionDetailsSeq* bothCalls = new(mem) ConnectionDetailsSeq(mem);
            bothCalls->activeCall = active.BuildConnectionID(mem);
            bothCalls->heldCall = held.BuildConnectionID(mem);

        ConnectionDetails* reconnectInfo = new(mem) ConnectionDetails(mem);
            reconnectInfo->choiceId = ConnectionDetails::bothCallsCid;
            reconnectInfo->bothCalls = bothCalls;

        ReconnectCallArgument* arg = new(mem) ReconnectCallArgument(mem);

        // Provide CSTA extensions

        CSTACommonArguments* comargs = BuildCommonArgs( mem, exts );

        if ( ! comargs )
        {
            // WITHOUT CSTACommonArguments
            arg->choiceId = ReconnectCallArgument::reconnectInfoCid;
            arg->reconnectInfo = reconnectInfo;
            }
        else
        {
            ReconnectCallArgumentSeq* argSeq = new(mem) ReconnectCallArgumentSeq(mem);
                argSeq->reconnectInfo = reconnectInfo;
                argSeq->extensions = comargs;

            arg->choiceId = ReconnectCallArgument::reconnectCallArgumentSeqCid;
            arg->reconnectCallArgumentSeq = argSeq;
            }

        ErrorCode rc = ROSE_Invoke( response, OperationIDType::reconnectCall, arg );

        if ( rc != CTNG_NO_ERROR )
            return rc;

        CSTAapdu* resp = response.GetAPDU ();
        TRASSERT( resp->choiceId == ROSEapdu::resultApduCid );

        ReconnectCallResult* result = (ReconnectCallResult*) resp->resultApdu->rORSapduSeq->result->value;

        // Check for CSTA extensions in result
        //
        if ( result->choiceId == ReconnectCallResult::extensionsCid )
        {
            ParsePrivateData( result->extensions, exts );
            }
        }
    catch( ... )
    {
        return CTNG_EXCEPTION_ERROR;
        }

    return CTNG_NO_ERROR;
    }

ErrorCode Device::RetrieveCall( const connectionIdType& connId, CSTA_Extensions* exts )
{
    TRACE( this << " ----- Device::RetrieveCall; Connection " << connId );

    try
    {
        MemBlock* mem = system->AllocateOutboundMemBlock ();
        InvokeResponse response( mem );

        // Construct CSTAapdu, bottom up.
        //
        RetrieveCallArgument* arg = new(mem) RetrieveCallArgument(mem);
    
        // Provide CSTA extensions

        CSTACommonArguments* comargs = BuildCommonArgs( mem, exts );

        if ( ! comargs )
        {
            // WITHOUT CSTACommonArguments
            arg->choiceId = RetrieveCallArgument::callToBeRetrievedCid;
            arg->callToBeRetrieved = connId.BuildConnectionID(mem);
            }
        else
        {
            RetrieveCallArgumentSeq* argSeq = new(mem) RetrieveCallArgumentSeq(mem);
                argSeq->callToBeRetrieved = connId.BuildConnectionID(mem);
                argSeq->extensions = comargs;

            arg->choiceId = RetrieveCallArgument::retrieveCallArgumentSeqCid;
            arg->retrieveCallArgumentSeq = argSeq;
            }

        ErrorCode rc = ROSE_Invoke( response, OperationIDType::retrieveCall, arg );

        if ( rc != CTNG_NO_ERROR )
            return rc;

        CSTAapdu* resp = response.GetAPDU ();
        TRASSERT( resp->choiceId == ROSEapdu::resultApduCid );

        RetrieveCallResult* result = (RetrieveCallResult*) resp->resultApdu->rORSapduSeq->result->value;

        // Check for CSTA extensions in result
        //
        if ( result->choiceId == RetrieveCallResult::extensionsCid )
        {
            ParsePrivateData( result->extensions, exts );
            }
        }
    catch( ... )
    {
        return CTNG_EXCEPTION_ERROR;
        }

    return CTNG_NO_ERROR;
    }

ErrorCode Device::TransferCall( const connectionIdType& held, const connectionIdType& active, connectionIdType& transferredCall, CSTA_Extensions* exts )
{
    TRACE( this << " ----- Device::TransferCall; Held " << held << ", Active " << active );

    try
    {
        MemBlock* mem = system->AllocateOutboundMemBlock ();
        InvokeResponse response( mem );

        // Construct CSTAapdu, bottom up.
        //
        ConnectionDetailsSeq* bothCalls = new(mem) ConnectionDetailsSeq(mem);
            bothCalls->activeCall = active.BuildConnectionID(mem);
            bothCalls->heldCall = held.BuildConnectionID(mem);

        ConnectionDetails* transferInfo = new(mem) ConnectionDetails(mem);
            transferInfo->choiceId = ConnectionDetails::bothCallsCid;
            transferInfo->bothCalls = bothCalls;

        TransferCallArgument* arg = new(mem) TransferCallArgument(mem);

        // Provide CSTA extensions

        CSTACommonArguments* comargs = BuildCommonArgs( mem, exts );

        if ( ! comargs )
        {
            // WITHOUT CSTACommonArguments
            arg->choiceId = TransferCallArgument::transferInfoCid;
            arg->transferInfo = transferInfo;
            }
        else
        {
            TransferCallArgumentSeq* argSeq = new(mem) TransferCallArgumentSeq(mem);
                argSeq->transferInfo = transferInfo;
                argSeq->extensions = comargs;

            arg->choiceId = TransferCallArgument::transferCallArgumentSeqCid;
            arg->transferCallArgumentSeq = argSeq;
            }

        ErrorCode rc = ROSE_Invoke( response, OperationIDType::transferCall, arg );

        if ( rc != CTNG_NO_ERROR )
            return rc;

        CSTAapdu* resp = response.GetAPDU ();
        TRASSERT( resp->choiceId == ROSEapdu::resultApduCid );

        TransferCallResult* result = (TransferCallResult*) resp->resultApdu->rORSapduSeq->result->value;

        // Check for CSTA extensions in result
        //
        ParsePrivateData( result->extensions, exts );

        if ( result->transferredCall )
            transferredCall = connectionIdType( result->transferredCall );

        // TODO: parse connection list. Anyhow, we will get it in Transferred event!
        }
    catch( ... )
    {
        return CTNG_EXCEPTION_ERROR;
        }

    return CTNG_NO_ERROR;
    }

ErrorCode Device::QueryDevice_MessageWaiting( bool& indicator, CSTA_Extensions* exts )
{
    TRACE( this << " ----- Device::QueryDevice_MessageWaiting; Device " << devID );

    try
    {
        MemBlock* mem = system->AllocateOutboundMemBlock ();
        InvokeResponse response( mem );

        // Construct CSTAapdu, bottom up.
        //
        QueryDeviceArgument* arg = new(mem) QueryDeviceArgument(mem);
            arg->device = devID.BuildDeviceID(mem);
            arg->feature.Set( QueryDeviceFeature::msgWaitingOn );
            arg->extensions = BuildCommonArgs( mem, exts );
    
        ErrorCode rc = ROSE_Invoke( response, OperationIDType::queryDevice, arg );

        if ( rc != CTNG_NO_ERROR )
            return rc;

        CSTAapdu* resp = response.GetAPDU ();
        TRASSERT( resp->choiceId == ROSEapdu::resultApduCid );
        TRASSERT( resp->resultApdu->rORSapduSeq->result->intId == OperationIDType::queryDevice ); 

        QueryDeviceResult* result = (QueryDeviceResult*) resp->resultApdu->rORSapduSeq->result->value;

        QueryDeviceInformation* deviceInformation = NULL;

        // Check for CSTA extensions in result
        //
        if ( result->choiceId == QueryDeviceResult::deviceInformationCid )
        {
            deviceInformation = result->deviceInformation;
            }
        else // Extensions found
        {
            deviceInformation = result->queryDeviceResultSeq->deviceInformation;
            ParsePrivateData( result->queryDeviceResultSeq->extensions, exts );
            }

        if ( deviceInformation 
            && deviceInformation->choiceId == QueryDeviceInformation::msgWaitingOnCid
            && deviceInformation->msgWaitingOn
            )
        {
            indicator = *deviceInformation->msgWaitingOn;
            }
        else
        {
            indicator = false; // FIXME unknown; or return error.
            }

        TRACE( this << " ----- Device::QueryDevice; MessageWaiting " << indicator );
        }
    catch( ... )
    {
        return CTNG_EXCEPTION_ERROR;
        }

    return CTNG_NO_ERROR;
    }

ErrorCode Device::QueryDevice_DoNotDisturb( bool& indicator, CSTA_Extensions* exts )
{
    TRACE( this << " ----- Device::QueryDevice_DoNotDistrub; Device " << devID );

    try
    {
        MemBlock* mem = system->AllocateOutboundMemBlock ();
        InvokeResponse response( mem );

        // Construct CSTAapdu, bottom up.
        //
        QueryDeviceArgument* arg = new(mem) QueryDeviceArgument(mem);
            arg->device = devID.BuildDeviceID(mem);
            arg->feature.Set( QueryDeviceFeature::doNotDisturbOn );
            arg->extensions = BuildCommonArgs( mem, exts );
    
        ErrorCode rc = ROSE_Invoke( response, OperationIDType::queryDevice, arg );

        if ( rc != CTNG_NO_ERROR )
            return rc;

        CSTAapdu* resp = response.GetAPDU ();
        TRASSERT( resp->choiceId == ROSEapdu::resultApduCid );
        TRASSERT( resp->resultApdu->rORSapduSeq->result->intId == OperationIDType::queryDevice ); 

        QueryDeviceResult* result = (QueryDeviceResult*) resp->resultApdu->rORSapduSeq->result->value;

        QueryDeviceInformation* deviceInformation = NULL;

        // Check for CSTA extensions in result
        //
        if ( result->choiceId == QueryDeviceResult::deviceInformationCid )
        {
            deviceInformation = result->deviceInformation;
            }
        else // Extensions found
        {
            deviceInformation = result->queryDeviceResultSeq->deviceInformation;
            ParsePrivateData( result->queryDeviceResultSeq->extensions, exts );
            }

        if ( deviceInformation 
            && deviceInformation->choiceId == QueryDeviceInformation::doNotDisturbOnCid
            && deviceInformation->doNotDisturbOn
            )
        {
            indicator = *deviceInformation->doNotDisturbOn;
            }
        else
        {
            indicator = false; // FIXME unknown; or return error.
            }

        TRACE( this << " ----- Device::QueryDevice; DoNotDisturb " << indicator );
        }
    catch( ... )
    {
        return CTNG_EXCEPTION_ERROR;
        }

    return CTNG_NO_ERROR;
    }

ErrorCode Device::QueryDevice_Forward( USTR& forwardInfo, CSTA_Extensions* exts )
{
    TRACE( this << " ----- Device::QueryDevice_Forward; Device " << devID );

    try
    {
        MemBlock* mem = system->AllocateOutboundMemBlock ();
        InvokeResponse response( mem );

        forwardInfo = USTR("");
        }
    catch( ... )
    {
        return CTNG_EXCEPTION_ERROR;
        }

    return CTNG_NO_ERROR;
    }

ErrorCode Device::QueryDevice_DeviceInfo( DeviceClassType& cls, DeviceTypeType& typ, CSTA_Extensions* exts )
{
    TRACE( this << " ----- Device::QueryDevice_DeviceInfo; Device " << devID );

    try
    {
        MemBlock* mem = system->AllocateOutboundMemBlock ();
        InvokeResponse response( mem );

        // Construct CSTAapdu, bottom up.
        //
        QueryDeviceArgument* arg = new(mem) QueryDeviceArgument(mem);
            arg->device = devID.BuildDeviceID(mem);
            arg->feature.Set( QueryDeviceFeature::deviceInfo );
            arg->extensions = BuildCommonArgs( mem, exts );
    
        ErrorCode rc = ROSE_Invoke( response, OperationIDType::queryDevice, arg );

        if ( rc != CTNG_NO_ERROR )
            return rc;

        CSTAapdu* resp = response.GetAPDU ();
        TRASSERT( resp->choiceId == ROSEapdu::resultApduCid );
        TRASSERT( resp->resultApdu->rORSapduSeq->result->intId == OperationIDType::queryDevice ); 

        QueryDeviceResult* result = (QueryDeviceResult*) resp->resultApdu->rORSapduSeq->result->value;

        QueryDeviceInformation* deviceInformation = NULL;

        // Check for CSTA extensions in result
        //
        if ( result->choiceId == QueryDeviceResult::deviceInformationCid )
        {
            deviceInformation = result->deviceInformation;
            }
        else // Extensions found
        {
            deviceInformation = result->queryDeviceResultSeq->deviceInformation;
            ParsePrivateData( result->queryDeviceResultSeq->extensions, exts );
            }

        cls = dct_unknown;
        typ = dtt_unknown;

        if ( deviceInformation 
            && deviceInformation->choiceId == QueryDeviceInformation::deviceInfoCid
            && deviceInformation->deviceInfo
            )
        {
            //if ( deviceInformation->deviceInfo->deviceClass )
                // cls = (AsnIntType) *deviceInformation->deviceInfo->deviceClass;

            if ( deviceInformation->deviceInfo->deviceType )
                typ = DeviceTypeType( (AsnIntType) *deviceInformation->deviceInfo->deviceType );
            }

        TRACE( this << " ----- Device::QueryDevice; DeviceInfo " << cls << ", " << typ );
        }
    catch( ... )
    {
        return CTNG_EXCEPTION_ERROR;
        }

    return CTNG_NO_ERROR;
    }

ErrorCode Device::QueryDevice_AgentState( AgentStateType& state, CSTA_Extensions* exts )
{
    TRACE( this << " ----- Device::QueryDevice_AgentState; Device " << devID );

    try
    {
        MemBlock* mem = system->AllocateOutboundMemBlock ();
        InvokeResponse response( mem );

        // Construct CSTAapdu, bottom up.
        //
        QueryDeviceArgument* arg = new(mem) QueryDeviceArgument(mem);
            arg->device = devID.BuildDeviceID(mem);
            arg->feature.Set( QueryDeviceFeature::agentState );
            arg->extensions = BuildCommonArgs( mem, exts );
    
        ErrorCode rc = ROSE_Invoke( response, OperationIDType::queryDevice, arg );

        if ( rc != CTNG_NO_ERROR )
            return rc;

        CSTAapdu* resp = response.GetAPDU ();
        TRASSERT( resp->choiceId == ROSEapdu::resultApduCid );
        TRASSERT( resp->resultApdu->rORSapduSeq->result->intId == OperationIDType::queryDevice ); 

        QueryDeviceResult* result = (QueryDeviceResult*) resp->resultApdu->rORSapduSeq->result->value;

        QueryDeviceInformation* deviceInformation = NULL;

        // Check for CSTA extensions in result
        //
        if ( result->choiceId == QueryDeviceResult::deviceInformationCid )
        {
            deviceInformation = result->deviceInformation;
            }
        else // Extensions found
        {
            deviceInformation = result->queryDeviceResultSeq->deviceInformation;
            ParsePrivateData( result->queryDeviceResultSeq->extensions, exts );
            }

        state = ast_unknown;

        if ( deviceInformation 
            && deviceInformation->choiceId == QueryDeviceInformation::agentStateCid
            && deviceInformation->agentState
            )
        {
            state = AgentStateType( (AsnIntType) *deviceInformation->agentState );
            }

        TRACE( this << " ----- Device::QueryDevice; AgentState " << state );
        }
    catch( ... )
    {
        return CTNG_EXCEPTION_ERROR;
        }

    return CTNG_NO_ERROR;
    }

ErrorCode Device::SetFeature_MessageWaiting( const bool indicator, CSTA_Extensions* exts )
{
    TRACE( this << " ----- Device::SetFeature_MessageWaiting; Device " 
        << devID << ", indicator " << indicator );

    try
    {
        MemBlock* mem = system->AllocateOutboundMemBlock ();
        InvokeResponse response( mem );

        // Construct CSTAapdu, bottom up.
        //
        SetDeviceFeature* feature = new(mem) SetDeviceFeature(mem);
            feature->choiceId = SetDeviceFeature::msgWaitingOnCid;
            feature->msgWaitingOn = new(mem) AsnBool( mem, indicator );

        SetFeatureArgument* arg = new(mem) SetFeatureArgument(mem);
            arg->device = devID.BuildDeviceID(mem);
            arg->feature = feature;
            arg->extensions = BuildCommonArgs( mem, exts );
    
        ErrorCode rc = ROSE_Invoke( response, OperationIDType::setFeature, arg );

        if ( rc != CTNG_NO_ERROR )
            return rc;

        CSTAapdu* resp = response.GetAPDU ();
        TRASSERT( resp->choiceId == ROSEapdu::resultApduCid );

        SetFeatureResult* result = (SetFeatureResult*) resp->resultApdu->rORSapduSeq->result->value;

        // Check for CSTA extensions in result
        //
        if ( result->choiceId == SetFeatureResult::extensionsCid )
        {
            ParsePrivateData( result->extensions, exts );
            }
        }
    catch( ... )
    {
        return CTNG_EXCEPTION_ERROR;
        }

    return CTNG_NO_ERROR;
    }

ErrorCode Device::SetFeature_DoNotDisturb( const bool indicator, CSTA_Extensions* exts )
{
    TRACE( this << " ----- Device::SetFeature_DoNotDisturb; Device " 
        << devID << ", indicator " << indicator );

    try
    {
        MemBlock* mem = system->AllocateOutboundMemBlock ();
        InvokeResponse response( mem );

        // Construct CSTAapdu, bottom up.
        //
        SetDeviceFeature* feature = new(mem) SetDeviceFeature(mem);
            feature->choiceId = SetDeviceFeature::doNotDisturbOnCid;
            feature->doNotDisturbOn = new(mem) AsnBool( mem, indicator );

        SetFeatureArgument* arg = new(mem) SetFeatureArgument(mem);
            arg->device = devID.BuildDeviceID(mem);
            arg->feature = feature;
            arg->extensions = BuildCommonArgs( mem, exts );
    
        ErrorCode rc = ROSE_Invoke( response, OperationIDType::setFeature, arg );

        if ( rc != CTNG_NO_ERROR )
            return rc;

        CSTAapdu* resp = response.GetAPDU ();
        TRASSERT( resp->choiceId == ROSEapdu::resultApduCid );

        SetFeatureResult* result = (SetFeatureResult*) resp->resultApdu->rORSapduSeq->result->value;

        // Check for CSTA extensions in result
        //
        if ( result->choiceId == SetFeatureResult::extensionsCid )
        {
            ParsePrivateData( result->extensions, exts );
            }
        }
    catch( ... )
    {
        return CTNG_EXCEPTION_ERROR;
        }

    return CTNG_NO_ERROR;
    }

ErrorCode Device::SetFeature_Forward( const ::ForwardingType forwardType, const USTR forwardDN, CSTA_Extensions* exts )
{
    TRACE( this << " ----- Device::SetFeature_Forward; Device " 
        << devID << ", forwardType " << forwardType << ", forwardDN " << forwardDN );

    try
    {
        MemBlock* mem = system->AllocateOutboundMemBlock ();
        InvokeResponse response( mem );

        // Construct CSTAapdu, both top down and bottom up.
        //
        IA5String* destDN = new(mem) IA5String(mem);
            *destDN = forwardDN;

        ForwardParameter* fparm = new(mem) ForwardParameter(mem);
            fparm->forwardDN = destDN;
            fparm->forwardingType.Set( forwardType );

        SetDeviceFeature* feature = new(mem) SetDeviceFeature(mem);
            feature->choiceId = SetDeviceFeature::forwardCid;
            feature->forward = fparm;

        SetFeatureArgument* arg = new(mem) SetFeatureArgument(mem);
            arg->device = devID.BuildDeviceID(mem);
            arg->feature = feature;
            arg->extensions = BuildCommonArgs( mem, exts );
    
        ErrorCode rc = ROSE_Invoke( response, OperationIDType::setFeature, arg );

        if ( rc != CTNG_NO_ERROR )
            return rc;

        CSTAapdu* resp = response.GetAPDU ();
        TRASSERT( resp->choiceId == ROSEapdu::resultApduCid );

        SetFeatureResult* result = (SetFeatureResult*) resp->resultApdu->rORSapduSeq->result->value;

        // Check for CSTA extensions in result
        //
        if ( result->choiceId == SetFeatureResult::extensionsCid )
        {
            ParsePrivateData( result->extensions, exts );
            }
        }
    catch( ... )
    {
        return CTNG_EXCEPTION_ERROR;
        }

    return CTNG_NO_ERROR;
    }

ErrorCode Device::SetFeature_RequestAgentState( const AgentParameterType apt, const USTR& agentId, const USTR& agentGroup, const USTR& agentPassword, CSTA_Extensions* exts )
{
    TRACE( this << " ----- Device::SetFeature_RequestAgentState; Device " 
        << devID << ", param " << apt << ", agentID " << agentId
        << ", agentGroup " << agentGroup << ", agentPassword " << agentPassword );

    try
    {
        MemBlock* mem = system->AllocateOutboundMemBlock ();
        InvokeResponse response( mem );

        // Construct CSTAapdu, both top down and bottom up.
        //
        AgentParameter* agparam = new(mem) AgentParameter(mem);

        switch( apt )
        {
            default:
            case apt_loggedIn:
                agparam->choiceId = AgentParameter::loggedInCid;
                agparam->loggedIn = new(mem) LoggedOnInfo(mem);
                agparam->loggedIn->agentID = new(mem) AsnOcts(mem);
                agparam->loggedIn->agentID->Set( agentId.Ptr (), agentId.Len () );
                agparam->loggedIn->group = deviceIdType( agentGroup ).BuildDeviceID(mem);
                agparam->loggedIn->password = new(mem) AsnOcts(mem);
                agparam->loggedIn->password->Set( agentPassword.Ptr (), agentPassword.Len () );
                break;

            case apt_loggedOut:
                agparam->choiceId = AgentParameter::loggedOutCid;
                agparam->loggedOut = new(mem) LoggedOffInfo(mem);
                agparam->loggedOut->agentID = new(mem) AsnOcts(mem);
                agparam->loggedOut->agentID->Set( agentId.Ptr (), agentId.Len () );
                agparam->loggedOut->group = deviceIdType( agentGroup ).BuildDeviceID(mem);
                break;

            case apt_notReady:
                agparam->choiceId = AgentParameter::notReadyCid;
                agparam->notReady = new(mem) AsnNull(mem);
                break;

            case apt_ready:
                agparam->choiceId = AgentParameter::readyCid;
                agparam->ready = new(mem) AsnNull(mem);
                break;

            case apt_workNotReady:
                agparam->choiceId = AgentParameter::workNotReadyCid;
                agparam->workNotReady = new(mem) AsnNull(mem);
                break;

            case apt_workReady:
                agparam->choiceId = AgentParameter::workReadyCid;
                agparam->workReady = new(mem) AsnNull(mem);
                break;
            }

        SetDeviceFeature* feature = new(mem) SetDeviceFeature(mem);
            feature->choiceId = SetDeviceFeature::requestedAgentStateCid;
            feature->requestedAgentState = agparam;

        SetFeatureArgument* arg = new(mem) SetFeatureArgument(mem);
            arg->device = devID.BuildDeviceID(mem);
            arg->feature = feature;
            arg->extensions = BuildCommonArgs( mem, exts );
    
        ErrorCode rc = ROSE_Invoke( response, OperationIDType::setFeature, arg );

        if ( rc != CTNG_NO_ERROR )
            return rc;

        CSTAapdu* resp = response.GetAPDU ();
        TRASSERT( resp->choiceId == ROSEapdu::resultApduCid );

        SetFeatureResult* result = (SetFeatureResult*) resp->resultApdu->rORSapduSeq->result->value;

        // Check for CSTA extensions in result
        //
        if ( result->choiceId == SetFeatureResult::extensionsCid )
        {
            ParsePrivateData( result->extensions, exts );
            }
        }
    catch( ... )
    {
        return CTNG_EXCEPTION_ERROR;
        }

    return CTNG_NO_ERROR;
    }

//////////////////////////////////////////////////////////////////////////////
} // namespace MidCSTA