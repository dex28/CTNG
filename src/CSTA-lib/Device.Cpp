/*
    Project: CSTALib

    Module: Device.Cpp

    Description: Device class implementation

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "CSTA-Lib.h"

using namespace ASN;
using namespace CTsvcLIB;

/////////////////////////////////////////////////////////////////////////////
namespace MidCSTA
{

///////////////////////////////////////////////////////////////////////////////
// TestFireAllEvents

ErrorCode Device:: TestFireAllEvents( void )
{
    try
    {
        {
            // Allocate Callback information object
            Ptr<CBI_CallCleared> cbi = new CBI_CallCleared;

            // Fill parameters
            cbi->clearedCall = "clearedCall";
            cbi->cause = ec_unknown;
            cbi->localConnectionInfo = lcs_unknown;
            cbi->manufacturerOID = "manufacturerOID";
            cbi->privateData = "privateData";

            // Enqueue event for dispatching to callback procedures...
            cbQueue.Put( cbi );
            }
        {
            // Allocate Callback information object
            Ptr<CBI_Conferenced> cbi = new CBI_Conferenced;

            // Fill parameters
            cbi->primaryOldCall = "primaryOldCall";
            cbi->secondaryOldCall = "secondaryOldCall";
            cbi->confController = "confController";
            cbi->addedParty = "addedParty";
            cbi->conferenceConnectionsCount = 100;
            cbi->conferenceConnections = new USTR[ 100 ];
            for ( int i = 0; i < 100; i++ )
                cbi->conferenceConnections[ i ] = "conferenceConnection";
            cbi->cause = ec_unknown;
            cbi->localConnectionInfo = lcs_unknown;
            cbi->manufacturerOID = "manufacturerOID";
            cbi->privateData = "privateData";

            // Enqueue event for dispatching to callback procedures...
            cbQueue.Put( cbi );
            }
        {
            // Allocate Callback information object
            Ptr<CBI_ConnectionCleared> cbi = new CBI_ConnectionCleared;

            // Fill parameters
            cbi->droppedConnection = "droppedConnection";
            cbi->releasingDevice = "releasingDevice";
            cbi->cause = ec_unknown;
            cbi->localConnectionInfo = lcs_unknown;
            cbi->manufacturerOID = "manufacturerOID";
            cbi->privateData = "privateData";

            // Enqueue event for dispatching to callback procedures...
            cbQueue.Put( cbi );
            }
        {
            // Allocate Callback information object
            Ptr<CBI_Delivered> cbi = new CBI_Delivered;

            // Fill parameters
            cbi->connection = "connection";
            cbi->alertingDevice = "alertingDevice";
            cbi->callingDevice = "callingDevice";
            cbi->calledDevice = "calledDevice";
            cbi->lastRedirectionDevice = "lastRedirectionDevice";
            cbi->cause = ec_unknown;
            cbi->localConnectionInfo = lcs_unknown;
            cbi->manufacturerOID = "manufacturerOID";
            cbi->privateData = "privateData";

            // Enqueue event for dispatching to callback procedures...
            cbQueue.Put( cbi );
            }
        {
            // Allocate Callback information object
            Ptr<CBI_Diverted> cbi = new CBI_Diverted;

            // Fill parameters
            cbi->connection = "connection";
            cbi->divertingDevice = "divertingDevice";
            cbi->newDestination = "newDestination";
            cbi->cause = ec_unknown;
            cbi->localConnectionInfo = lcs_unknown;
            cbi->manufacturerOID = "manufacturerOID";
            cbi->privateData = "privateData";

            // Enqueue event for dispatching to callback procedures...
            cbQueue.Put( cbi );
            }
        {
            // Allocate Callback information object
            Ptr<CBI_Established> cbi = new CBI_Established;

            // Fill parameters
            cbi->establishedConnection = "establishedConnection";
            cbi->answeringDevice = "answeringDevice";
            cbi->callingDevice = "callingDevice";
            cbi->calledDevice = "calledDevice";
            cbi->lastRedirectionDevice = "lastRedirectionDevice";
            cbi->cause = ec_unknown;
            cbi->localConnectionInfo = lcs_unknown;
            cbi->manufacturerOID = "manufacturerOID";
            cbi->privateData = "privateData";

            // Enqueue event for dispatching to callback procedures...
            cbQueue.Put( cbi );
            }
        {
            // Allocate Callback information object
            Ptr<CBI_Failed> cbi = new CBI_Failed;

            // Fill parameters
            cbi->failedConnection = "failedConnection";
            cbi->failingDevice = "failingDevice";
            cbi->calledDevice = "calledDevice";
            cbi->cause = ec_unknown;
            cbi->localConnectionInfo = lcs_unknown;
            cbi->manufacturerOID = "manufacturerOID";
            cbi->privateData = "privateData";

            // Enqueue event for dispatching to callback procedures...
            cbQueue.Put( cbi );
            }
        {
            // Allocate Callback information object
            Ptr<CBI_Held> cbi = new CBI_Held;

            // Fill parameters
            cbi->heldConnection = "heldConnection";
            cbi->holdingDevice = "holdingDevice";
            cbi->cause = ec_unknown;
            cbi->localConnectionInfo = lcs_unknown;
            cbi->manufacturerOID = "manufacturerOID";
            cbi->privateData = "privateData";

            // Enqueue event for dispatching to callback procedures...
            cbQueue.Put( cbi );
            }
        {
            // Allocate Callback information object
            Ptr<CBI_NetworkReached> cbi = new CBI_NetworkReached;

            // Fill parameters
            cbi->connection = "connection";
            cbi->trunkUsed = "trunkUsed";
            cbi->calledDevice = "calledDevice";
            cbi->cause = ec_unknown;
            cbi->localConnectionInfo = lcs_unknown;
            cbi->manufacturerOID = "manufacturerOID";
            cbi->privateData = "privateData";

            // Enqueue event for dispatching to callback procedures...
            cbQueue.Put( cbi );
            }
        {
            // Allocate Callback information object
            Ptr<CBI_Originated> cbi = new CBI_Originated;

            // Fill parameters
            cbi->originatedConnection = "originatedConnection";
            cbi->callingDevice = "callingDevice";
            cbi->calledDevice = "calledDevice";
            cbi->cause = ec_unknown;
            cbi->localConnectionInfo = lcs_unknown;
            cbi->manufacturerOID = "manufacturerOID";
            cbi->privateData = "privateData";

            // Enqueue event for dispatching to callback procedures...
            cbQueue.Put( cbi );
            }
        {
            // Allocate Callback information object
            Ptr<CBI_Queued> cbi = new CBI_Queued;

            // Fill parameters
            cbi->queuedConnection = "queuedConnection";
            cbi->queue = "queue";
            cbi->callingDevice = "callingDevice";
            cbi->calledDevice = "calledDevice";
            cbi->lastRedirectionDevice = "lastRedirectionDevice";
            cbi->numberedQueued = 0;
            cbi->cause = ec_unknown;
            cbi->localConnectionInfo = lcs_unknown;
            cbi->manufacturerOID = "manufacturerOID";
            cbi->privateData = "privateData";

            // Enqueue event for dispatching to callback procedures...
            cbQueue.Put( cbi );
            }
        {
            // Allocate Callback information object
            Ptr<CBI_Retrieved> cbi = new CBI_Retrieved;

            // Fill parameters
            cbi->retrievedConnection = "retrievedConnection";
            cbi->retrievingDevice = deviceIdType( cbi->retrievingDevice );
            cbi->cause = ec_unknown;
            cbi->localConnectionInfo = lcs_unknown;
            cbi->manufacturerOID = "manufacturerOID";
            cbi->privateData = "privateData";

            // Enqueue event for dispatching to callback procedures...
            cbQueue.Put( cbi );
            }
        {
            // Allocate Callback information object
            Ptr<CBI_ServiceInitiated> cbi = new CBI_ServiceInitiated;

            // Fill parameters
            cbi->initiatedConnection = "initiatedConnection";
            cbi->cause = ec_unknown;
            cbi->localConnectionInfo = lcs_unknown;
            cbi->manufacturerOID = "manufacturerOID";
            cbi->privateData = "privateData";

            // Enqueue event for dispatching to callback procedures...
            cbQueue.Put( cbi );
            }
        {
            // Allocate Callback information object
            Ptr<CBI_Transferred> cbi = new CBI_Transferred;

            // Fill parameters
            cbi->primaryOldCall = "primaryOldCall";
            cbi->secondaryOldCall = "secondaryOldCall";
            cbi->transferringDevice = "transferringDevice";
            cbi->transferredDevice = "transferredDevice";
            cbi->transferredConnectionsCount = 100;
            cbi->transferredConnections = new USTR[ 100 ];
            for ( int i = 0; i < 100; i++ )
                cbi->transferredConnections[ i ] = "transferredConnection";
            cbi->cause = ec_unknown;
            cbi->localConnectionInfo = lcs_unknown;
            cbi->manufacturerOID = "manufacturerOID";
            cbi->privateData = "privateData";

            // Enqueue event for dispatching to callback procedures...
            cbQueue.Put( cbi );
            }
        {
            // Allocate Callback information object
            Ptr<CBI_OutOfService> cbi = new CBI_OutOfService;

            // Fill parameters
            cbi->device = "device";
            cbi->cause = ec_unknown;
            cbi->manufacturerOID = "manufacturerOID";
            cbi->privateData = "privateData";

            // Enqueue event for dispatching to callback procedures...
            cbQueue.Put( cbi );
            }
        {
            // Allocate Callback information object
            Ptr<CBI_BackInService> cbi = new CBI_BackInService;

            // Fill parameters
            cbi->device = "device";
            cbi->cause = ec_unknown;
            cbi->manufacturerOID = "manufacturerOID";
            cbi->privateData = "privateData";

            // Enqueue event for dispatching to callback procedures...
            cbQueue.Put( cbi );
            }
        {
            // Allocate Callback information object
            Ptr<CBI_LoggedOn> cbi = new CBI_LoggedOn;

            // Fill parameters
            cbi->agentDevice = "agentDevice";
            cbi->agentID = "agentID";
            cbi->agentGroup = "agentGroup";
            cbi->agentPassword = "agentPassword";
            cbi->manufacturerOID = "manufacturerOID";
            cbi->privateData = "privateData";

            // Enqueue event for dispatching to callback procedures...
            cbQueue.Put( cbi );
            }
        {
            // Allocate Callback information object
            Ptr<CBI_LoggedOff> cbi = new CBI_LoggedOff;

            // Fill parameters
            cbi->agentDevice = "agentDevice";
            cbi->agentID = "agentID";
            cbi->agentGroup = "agentGroup";
            cbi->manufacturerOID = "manufacturerOID";
            cbi->privateData = "privateData";

            // Enqueue event for dispatching to callback procedures...
            cbQueue.Put( cbi );
            }
        {
            // Allocate Callback information object
            Ptr<CBI_NotReady> cbi = new CBI_NotReady;

            // Fill parameters
            cbi->agentDevice = "agentDevice";
            cbi->agentID = "agentID";
            cbi->manufacturerOID = "manufacturerOID";
            cbi->privateData = "privateData";

            // Enqueue event for dispatching to callback procedures...
            cbQueue.Put( cbi );
            }
        {
            // Allocate Callback information object
            Ptr<CBI_Ready> cbi = new CBI_Ready;

            // Fill parameters
            cbi->agentDevice = "agentDevice";
            cbi->agentID = "agentID";
            cbi->manufacturerOID = "manufacturerOID";
            cbi->privateData = "privateData";

            // Enqueue event for dispatching to callback procedures...
            cbQueue.Put( cbi );
            }
        {
            // Allocate Callback information object
            Ptr<CBI_WorkNotReady> cbi = new CBI_WorkNotReady;

            // Fill parameters
            cbi->agentDevice = "agentDevice";
            cbi->agentID = "agentID";
            cbi->manufacturerOID = "manufacturerOID";
            cbi->privateData = "privateData";

            // Enqueue event for dispatching to callback procedures...
            cbQueue.Put( cbi );
            }
        {
            // Allocate Callback information object
            Ptr<CBI_WorkReady> cbi = new CBI_WorkReady;

            // Fill parameters
            cbi->agentDevice = "agentDevice";
            cbi->agentID = "agentID";
            cbi->manufacturerOID = "manufacturerOID";
            cbi->privateData = "privateData";

            // Enqueue event for dispatching to callback procedures...
            cbQueue.Put( cbi );
            }
        {
            // Allocate Callback information object
            Ptr<CBI_CallInformation> cbi = new CBI_CallInformation;

            // Fill parameters
            cbi->connection = "connection";
            cbi->device = "device";
            cbi->accountInfo = "accountInfo";
            cbi->authorisationCode = "authorisationCode";
            cbi->manufacturerOID = "manufacturerOID";
            cbi->privateData = "privateData";

            // Enqueue event for dispatching to callback procedures...
            cbQueue.Put( cbi );
            }
        {
            // Allocate Callback information object
            Ptr<CBI_DoNotDisturb> cbi = new CBI_DoNotDisturb;

            // Fill parameters
            cbi->device = "device";
            cbi->doNotDisturbFlag = 0;
            cbi->manufacturerOID = "manufacturerOID";
            cbi->privateData = "privateData";

            // Enqueue event for dispatching to callback procedures...
            cbQueue.Put( cbi );
            }
        {
            // Allocate Callback information object
            Ptr<CBI_Forwarding> cbi = new CBI_Forwarding;

            // Fill parameters
            cbi->device = "device";
            cbi->type = ft_unknown;
            cbi->forwardDN = "forwardDN";
            cbi->forwardedTo = "forwardedTo";
            cbi->manufacturerOID = "manufacturerOID";
            cbi->privateData = "privateData";

            // Enqueue event for dispatching to callback procedures...
            cbQueue.Put( cbi );
            }
        {
            // Allocate Callback information object
            Ptr<CBI_MessageWaiting> cbi = new CBI_MessageWaiting;

            // Fill parameters
            cbi->deviceForMessage = "deviceForMessage";
            cbi->invokingDevice = "invokingDevice";
            cbi->messageWaitingFlag = 0;
            cbi->manufacturerOID = "manufacturerOID";
            cbi->privateData = "privateData";

            // Enqueue event for dispatching to callback procedures...
            cbQueue.Put( cbi );
            }
        {
            // Allocate Callback information object
            Ptr<CBI_PrivateEvent> cbi = new CBI_PrivateEvent;

            // Fill parameters
            cbi->data = "data";

            // Enqueue event for dispatching to callback procedures...
            cbQueue.Put( cbi );
            }
        {
            Ptr<CBI_SystemStatus> cbi = new CBI_SystemStatus;

            // Fill parameters
            cbi->status = ss_unknown;

            // Enqueue event for dispatching to callback procedures...
            cbQueue.Put( cbi );
            }
        {
            Ptr<CBI_MonitorStarted> cbi = new CBI_MonitorStarted;

            // Fill parameters
            cbi->errCode = CTNG_NO_ERROR;

            // Enqueue event for dispatching to callback procedures...
            cbQueue.Put( cbi );
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