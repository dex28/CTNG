/*
    Project: CSTALib

    Module: CSTA-Svcs.Cpp

    Description: Device object CSTA services methods

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "CSTA-Lib.h"

using namespace ASN;

static MemPool memPool( "CSTA-Svcs module" );

namespace MidCSTA
{

//////////////////////////////////////////////////////////////////////////////

ErrorCode Device:: MonitorStart( const deviceIdType& devId, monitorCrossRefIdType& monId )
{
    Invoke* invoke = AllocateInvoke ();

    // Construct CSTAapdu, bottom up.
    //
    MemBlock* mem = new(memPool) MemBlock( memPool );

    MonitorObject* obj = new(mem) MonitorObject(mem);
        obj->choiceId = CSTAObject::deviceObjectCid;
        obj->deviceObject = devId.BuildDeviceID(mem);

    MonitorStartArgument* arg = new(mem) MonitorStartArgument(mem);
        arg->monitorObject = obj;
        arg->monitorFilter = NULL;

    ErrorCode rc = invoke->PerformInvoke( OperationIDType::monitorStart, arg );
    ASN::CSTAapdu* resp = invoke->GetResponse ();

    if ( rc == CTNG_NO_ERROR )
    {
        MonitorStartResult* result = (MonitorStartResult*) resp->resultApdu->rORSapduSeq->result->value;

        monId = USTR( result->crossRefIdentifier );
        }

    if ( resp )
        delete resp->GetMemBlock ();

    delete mem;

    // Release invoke back to free invoke pool
    //
    ReleaseInvoke( invoke );

    return rc;
    }

ErrorCode Device:: MonitorStop( const monitorCrossRefIdType& monId )
{
    Invoke* invoke = AllocateInvoke ();

    // Construct CSTAapdu, bottom up.
    //
    MemBlock* mem = new(memPool) MemBlock( memPool );

    MonitorCrossRefID* crossRefId = new(mem) MonitorCrossRefID( mem );
        crossRefId->Set( monId.Ptr(), monId.Len () );

    MonitorStopArgument* arg = new(mem) MonitorStopArgument(mem);
        arg->choiceId = MonitorStopArgument::crossRefIdentifierCid;
        arg->crossRefIdentifier = crossRefId;
    
    OperationArgument* oparg = new(mem) OperationArgument(mem);
        oparg->intId = OperationIDType::monitorStop;
        oparg->value = arg;

    ErrorCode rc = invoke->PerformInvoke( OperationIDType::monitorStop, arg );
    CSTAapdu* resp = invoke->GetResponse ();

    if ( rc == CTNG_NO_ERROR )
    {
        MonitorStopResult* result = (MonitorStopResult*) resp->resultApdu->rORSapduSeq->result->value;
        // OK
        }

    if ( resp )
        delete resp->GetMemBlock ();

    delete mem;

    // Release invoke back to free invoke pool
    //
    ReleaseInvoke( invoke );

    return rc;
    }

ErrorCode Device:: MakeCall( const char* deviceId2call, connectionIdType& connId  )
{
    Invoke* invoke = AllocateInvoke ();

    // Construct CSTAapdu, bottom up.
    //
    MemBlock* mem = new(memPool) MemBlock( memPool );

    IA5String* digits2call = new(mem) IA5String(mem);
        *digits2call = deviceId2call;

    ExtendedDeviceID* dev2call = new(mem) ExtendedDeviceID(mem);
        dev2call->choiceId = ExtendedDeviceID::dialingNumberCid;
        dev2call->dialingNumber = digits2call;

    CalledDeviceID* calledDev = new(mem) CalledDeviceID(mem);
        calledDev->choiceId = CalledDeviceID::deviceIdentifierCid;
        calledDev->deviceIdentifier = dev2call;

    MakeCallArgument* arg = new(mem) MakeCallArgument(mem);
        arg->callingDevice = devId.BuildDeviceID(mem);
        arg->calledDirectoryNumber = calledDev;
    
    ErrorCode rc = invoke->PerformInvoke( OperationIDType::makeCall, arg );
    CSTAapdu* resp = invoke->GetResponse ();

    if ( rc == CTNG_NO_ERROR )
    {
        MakeCallResult* result = (MakeCallResult*) resp->resultApdu->rORSapduSeq->result->value;

        TRASSERT( result->choiceId == MakeCallResult::initiatedCallCid );
        TRASSERT( result->initiatedCall->device->choiceId == ConnectionIDChoice::staticIDCid );
        TRASSERT( result->initiatedCall->device->staticID->choiceId == DeviceID::dialingNumberCid );

        if ( result->initiatedCall->call )
        {
            connId = connectionIdType( result->initiatedCall );
            }
        }

    if ( resp )
        delete resp->GetMemBlock ();

    delete mem;

    // Release invoke back to free invoke pool
    //
    ReleaseInvoke( invoke );

    return rc;
    }

ErrorCode Device:: ClearConnection( const connectionIdType& connId )
{
    Invoke* invoke = AllocateInvoke ();

    // Construct CSTAapdu, bottom up.
    //
    MemBlock* mem = new(memPool) MemBlock( memPool );

    ConnectionID* cn = connId.BuildConnectionID( mem );

    ClearConnectionArgument* arg = new(mem) ClearConnectionArgument(mem);
        arg->choiceId = ClearConnectionArgument::connectionToBeClearedCid;
        arg->connectionToBeCleared = cn;
    
    ErrorCode rc = invoke->PerformInvoke( OperationIDType::clearConnection, arg );
    CSTAapdu* resp = invoke->GetResponse ();

    if ( rc == CTNG_NO_ERROR )
    {
        ClearConnectionResult* result = (ClearConnectionResult*) resp->resultApdu->rORSapduSeq->result->value;
        }

    if ( resp )
        delete resp->GetMemBlock ();

    delete mem;

    // Release invoke back to free invoke pool
    //
    ReleaseInvoke( invoke );

    return rc;
    }

ErrorCode Device:: ClearCall( const connectionIdType& connId )
{
    Invoke* invoke = AllocateInvoke ();

    // Construct CSTAapdu, bottom up.
    //
    MemBlock* mem = new(memPool) MemBlock( memPool );

    ConnectionID* cn = connId.BuildConnectionID( mem );

    ClearCallArgument* arg = new(mem) ClearCallArgument(mem);
        arg->choiceId = ClearCallArgument::callToBeClearedCid;
        arg->callToBeCleared = cn;
    
    ErrorCode rc = invoke->PerformInvoke( OperationIDType::clearCall, arg );
    CSTAapdu* resp = invoke->GetResponse ();

    if ( rc == CTNG_NO_ERROR )
    {
        ClearCallResult* result = (ClearCallResult*) resp->resultApdu->rORSapduSeq->result->value;
        }

    if ( resp )
        delete resp->GetMemBlock ();

    delete mem;

    // Release invoke back to free invoke pool
    //
    ReleaseInvoke( invoke );

    return rc;
    }

ErrorCode Device:: AnswerCall( const connectionIdType& connId )
{
    Invoke* invoke = AllocateInvoke ();

    // Construct CSTAapdu, bottom up.
    //
    MemBlock* mem = new(memPool) MemBlock( memPool );

    ConnectionID* cn = connId.BuildConnectionID( mem );

    AnswerCallArgument* arg = new(mem) AnswerCallArgument(mem);
        arg->choiceId = AnswerCallArgument::callToBeAnsweredCid;
        arg->callToBeAnswered = cn;
    
    ErrorCode rc = invoke->PerformInvoke( OperationIDType::answerCall, arg );
    CSTAapdu* resp = invoke->GetResponse ();

    if ( rc == CTNG_NO_ERROR )
    {
        AnswerCallResult* result = (AnswerCallResult*) resp->resultApdu->rORSapduSeq->result->value;
        }

    if ( resp )
        delete resp->GetMemBlock ();

    delete mem;

    // Release invoke back to free invoke pool
    //
    ReleaseInvoke( invoke );
 
    return rc;
    }

ErrorCode Device:: SystemStatus( const SystemStatusType systemStatusId )
{
    Invoke* invoke = AllocateInvoke ();

    // Construct CSTAapdu, bottom up.
    //
    MemBlock* mem = new(memPool) MemBlock( memPool );

    ASN::SystemStatus* sysStat = new(mem) ASN::SystemStatus(mem);
        sysStat->Set( systemStatusId );

    SystemStatusArgument* arg = new(mem) SystemStatusArgument(mem);
        arg->choiceId = SystemStatusArgument::systemStatusCid;
        arg->systemStatus = sysStat;
    
    ErrorCode rc = invoke->PerformInvoke( OperationIDType::systemStatus, arg );
    CSTAapdu* resp = invoke->GetResponse ();

    if ( rc == CTNG_NO_ERROR )
    {
        SystemStatusResult* result = (SystemStatusResult*) resp->resultApdu->rORSapduSeq->result->value;
        }

    if ( resp )
        delete resp->GetMemBlock ();

    delete mem;

    // Release invoke back to free invoke pool
    //
    ReleaseInvoke( invoke );
 
    return rc;
    }

ErrorCode Device:: DivertCall_Deflect( const connectionIdType& conn, const char* deviceIdTo )
{
    Invoke* invoke = AllocateInvoke ();

    // Construct CSTAapdu, bottom up.
    //
    MemBlock* mem = new(memPool) MemBlock( memPool );

    ConnectionID* cn = conn.BuildConnectionID( mem );

    IA5String* digits2call = new(mem) IA5String(mem);
        *digits2call = deviceIdTo;

    ExtendedDeviceID* dev2call = new(mem) ExtendedDeviceID(mem);
        dev2call->choiceId = ExtendedDeviceID::dialingNumberCid;
        dev2call->dialingNumber = digits2call;

    CalledDeviceID* calledDev = new(mem) CalledDeviceID(mem);
        calledDev->choiceId = CalledDeviceID::deviceIdentifierCid;
        calledDev->deviceIdentifier = dev2call;

    DivertInfoSeq* deflinfo = new(mem) DivertInfoSeq(mem);
        deflinfo->callToBeDiverted = cn;
        deflinfo->newDestination = calledDev;

    DivertInfo* dinfo = new(mem) DivertInfo(mem);
        dinfo->choiceId = DivertInfo::deflectCid;
        dinfo->deflect = deflinfo;

    DivertCallArgument* arg = new(mem) DivertCallArgument(mem);

    if ( 0 )
    {
        arg->choiceId = DivertCallArgument::divertInfoCid;
        arg->divertInfo = dinfo;
        }
    else
    {
        CSTACommonArgumentsSeqOf* comargs1 = new(mem) CSTACommonArgumentsSeqOf(mem);
        CSTAPrivateData* extensions = comargs1->Append ();
            extensions->manufacturer.Set( 1, 3, 13, 2, 1213, 21, 11 );
            extensions->data.SetTypeBy( extensions->manufacturer );
            extensions->data.encodeLenAsEric = true;
            extensions->data.octetLen = 1;
            extensions->data.octs = new(mem) uint8[1];
            extensions->data.octs[0]= 0x01;

        CSTACommonArguments* comargs = new(mem) CSTACommonArguments(mem);
            comargs->security = NULL;
            comargs->privateData = comargs1;

        DivertCallArgumentSeq* arg1 = new(mem) DivertCallArgumentSeq(mem);
            arg1->deivertInfo = dinfo;
            arg1->extensions = comargs;

        arg->choiceId = DivertCallArgument::divertCallArgumentSeqCid;
        arg->divertCallArgumentSeq = arg1;
        }

    ErrorCode rc = invoke->PerformInvoke( OperationIDType::divertCall, arg );
    CSTAapdu* resp = invoke->GetResponse ();

    if ( rc == CTNG_NO_ERROR )
    {
        DivertCallResult* result = (DivertCallResult*) resp->resultApdu->rORSapduSeq->result->value;
        }

    if ( resp )
        delete resp->GetMemBlock ();

    delete mem;

    // Release invoke back to free invoke pool
    //
    ReleaseInvoke( invoke );
 
    return rc;
    }

//////////////////////////////////////////////////////////////////////////////
}