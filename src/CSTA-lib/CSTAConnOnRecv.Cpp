/*
    Project: CSTALib

    Module: CSTAConnOnRecv.Cpp

    Description: Device class implementation
                 OnRecv_SystemStatus
                 OnRecv_EventReport

    Copyright (c) 2002,2003 By Mikica B Kocic
    Copyright (c) 2002,2003 By IPTC Technology Communication AB
*/

#include "CSTA-Lib.h"

using namespace ASN;
using namespace CTsvcLIB;

/////////////////////////////////////////////////////////////////////////////
namespace MidCSTA
{

///////////////////////////////////////////////////////////////////////////////
// Device class implementation, CSTA incoming Invokes handling

void Device:: OnRecv_SystemStatus( ASN::CSTAapdu* apdu )
{
    TRACE( this << " Device::OnRecv_SystemStatus; APDU " << apdu );

    SystemStatusArgument* sysStat = (SystemStatusArgument*)apdu->invokeApdu->argument->value;

    // Build result and send it back.
    //
    MemBlock* mem = apdu->GetMemBlock ();

    SystemStatusResult* result = new(mem) SystemStatusResult(mem);
        result->choiceId = SystemStatusResult::noDataCid;
        result->noData = new(mem) AsnNull(mem);

    ROSE_SendResult(
        apdu->invokeApdu->operationValue,
        apdu->invokeApdu->invokeID,
        result
        );

    Ptr<CBI_SystemStatus> cbi = new CBI_SystemStatus( apdu );

    if ( sysStat->choiceId == SystemStatusArgument::systemStatusCid )
        cbi->status = SystemStatusType( (int) *sysStat->systemStatus );
    else
        cbi->status = SystemStatusType( (int) sysStat->systemStatusArgumentSeq->systemStatus );

    // Enqueue event for dispatching to callback procedures.
    //
    // Memory block 'mem' associated to APDU will be associated to
    // cbInfo and it will be released when cbInfo reference count comes to zero.
    //
    cbQueue.Put( cbi );
    }

///////////////////////////////////////////////////////////////////////////////

void Device:: OnRecv_EscapeService( ASN::CSTAapdu* apdu )
{
    TRACE( this << " Device::OnRecv_EscapeService; APDU " << apdu );

    delete apdu->GetMemBlock ();
    }

///////////////////////////////////////////////////////////////////////////////

void Device:: OnRecv_EventReport( ASN::CSTAapdu* apdu )
{
    TRACE( this << " Device::OnRecv_EventReport; APDU " << apdu );

    MemBlock* mem = apdu->GetMemBlock ();

    AsnIntType invoke_id = apdu->invokeApdu->invokeID;

    CSTAEventReportArgument* eventRep = (CSTAEventReportArgument*)apdu->invokeApdu->argument->value;
    
    // Check monitor identifier by cross reference ID
    //
    connMutex.Lock ();

    if ( ! ( monitorID == USTR( mem, eventRep->crossRefIdentifier ) ) )
    {
        connMutex.Unlock ();

        LOG( DBG_WARN ) << this << " Device::OnRecv_EventReport: Monitor not found by cross ref id!" << eline;
        delete mem;
        return;
        }

    connMutex.Unlock ();

    USTR manufacturerOID;
    USTR privateData;

    if ( eventRep->extensions )
    {
        manufacturerOID = eventRep->extensions->manufacturer;
        privateData = eventRep->extensions->data.toUSTR ();

        TRACE( this << " Device::OnRecv_EventReport: Private Data:" << eline
            << "OID: " << manufacturerOID.toHex () << eline
            << "Data: " << privateData.toHex ()
            );
        }

    Ptr<CallbackInfo> cbInfo = NULL;

    // Parse event
    //
    switch( eventRep->eventInfo.intId )
    {
        case ASN::EventIDType::callCleared:
        {
            ASN::CallClearedEventInfo* ei = (ASN::CallClearedEventInfo*)eventRep->eventInfo.value;
            CBI_CallCleared* cbi = new CBI_CallCleared( apdu );
            cbInfo = cbi;

            cbi->clearedCall = connectionIdType( ei->clearedCall );
            cbi->cause = ei->cause ? EventCauseType( (AsnIntType)*ei->cause ): ec_unknown;
            cbi->localConnectionInfo = ei->localConnectionInfo ? LocalConnectionStateType( (AsnIntType)*ei->localConnectionInfo ) : lcs_unknown;
            cbi->manufacturerOID = manufacturerOID;
            cbi->privateData = privateData;

            break;
            }

        case ASN::EventIDType::conferenced:
        {
            ASN::ConferencedEventInfo* ei = (ASN::ConferencedEventInfo*)eventRep->eventInfo.value;
            CBI_Conferenced* cbi = new CBI_Conferenced( apdu );
            cbInfo = cbi;

            cbi->primaryOldCall = connectionIdType( ei->primaryOldCall );
            cbi->secondaryOldCall = connectionIdType( ei->secondaryOldCall );
            cbi->confController = deviceIdType( ei->confController );
            cbi->addedParty = deviceIdType( ei->addedParty );
            cbi->manufacturerOID = manufacturerOID;
            cbi->privateData = privateData;

            // Create list of conferenced connections
            //
            if ( ei->conferenceConnections )
            {
                if ( ei->conferenceConnections->choiceId == ConnectionList::connectionsCid )
                {
                    ASN::ConnectionIDList* connections = ei->conferenceConnections->connections;
                    connections->SetCurrToFirst();

                    cbi->conferenceConnectionsCount = connections->Count ();
                    cbi->conferenceConnections = new USTR[ connections->Count () ];

                    int cni = 0;

                    while ( connections->Curr () )
                    {
                        cbi->conferenceConnections[ cni++ ] = connectionIdType( connections->Curr () );

                        connections->GoNext ();
                        }
                    }
                else if ( ei->conferenceConnections->choiceId == ConnectionList::callinformationCid )
                {
                    }
                }

            cbi->cause = ei->cause ? EventCauseType( (AsnIntType)*ei->cause ): ec_unknown;
            cbi->localConnectionInfo = ei->localConnectionInfo ? LocalConnectionStateType( (AsnIntType)*ei->localConnectionInfo ) : lcs_unknown;

            break;
            }

        case ASN::EventIDType::connectionCleared:
        {
            ASN::ConnectionClearedEventInfo* ei = (ASN::ConnectionClearedEventInfo*)eventRep->eventInfo.value;
            CBI_ConnectionCleared* cbi = new CBI_ConnectionCleared( apdu );
            cbInfo = cbi;

            cbi->droppedConnection = connectionIdType( ei->droppedConnection );
            cbi->releasingDevice = deviceIdType( ei->releasingDevice );
            cbi->cause = ei->cause ? EventCauseType( (AsnIntType)*ei->cause ): ec_unknown;
            cbi->localConnectionInfo = ei->localConnectionInfo ? LocalConnectionStateType( (AsnIntType)*ei->localConnectionInfo ) : lcs_unknown;
            cbi->manufacturerOID = manufacturerOID;
            cbi->privateData = privateData;

            break;
            }

        case ASN::EventIDType::delivered:
        {
            ASN::DeliveredEventInfo* ei = (ASN::DeliveredEventInfo*)eventRep->eventInfo.value;
            CBI_Delivered* cbi = new CBI_Delivered( apdu );
            cbInfo = cbi;

            cbi->connection = connectionIdType( ei->connection );
            cbi->alertingDevice = deviceIdType( ei->alertingDevice );
            cbi->callingDevice = deviceIdType( ei->callingDevice );
            cbi->calledDevice = deviceIdType( ei->calledDevice );
            cbi->lastRedirectionDevice = deviceIdType( ei->lastRedirectionDevice );
            cbi->cause = ei->cause ? EventCauseType( (AsnIntType)*ei->cause ): ec_unknown;
            cbi->localConnectionInfo = ei->localConnectionInfo ? LocalConnectionStateType( (AsnIntType)*ei->localConnectionInfo ) : lcs_unknown;
            cbi->manufacturerOID = manufacturerOID;
            cbi->privateData = privateData;

            break;
            }

        case ASN::EventIDType::diverted:
        {
            ASN::DivertedEventInfo* ei = (ASN::DivertedEventInfo*)eventRep->eventInfo.value;
            CBI_Diverted* cbi = new CBI_Diverted( apdu );
            cbInfo = cbi;

            cbi->connection = connectionIdType( ei->connection );
            cbi->divertingDevice = deviceIdType( ei->divertingDevice );
            cbi->newDestination = deviceIdType( ei->newDestination );
            cbi->cause = ei->cause ? EventCauseType( (AsnIntType)*ei->cause ): ec_unknown;
            cbi->localConnectionInfo = ei->localConnectionInfo ? LocalConnectionStateType( (AsnIntType)*ei->localConnectionInfo ) : lcs_unknown;
            cbi->manufacturerOID = manufacturerOID;
            cbi->privateData = privateData;

            break;
            }

        case ASN::EventIDType::established:
        {
            ASN::EstablishedEventInfo* ei = (ASN::EstablishedEventInfo*)eventRep->eventInfo.value;
            CBI_Established* cbi = new CBI_Established( apdu );
            cbInfo = cbi;

            cbi->establishedConnection = connectionIdType( ei->establishedConnection );
            cbi->answeringDevice = deviceIdType( ei->answeringDevice );
            cbi->callingDevice = deviceIdType( ei->callingDevice );
            cbi->calledDevice = deviceIdType( ei->calledDevice );
            cbi->lastRedirectionDevice = deviceIdType( ei->lastRedirectionDevice );
            cbi->cause = ei->cause ? EventCauseType( (AsnIntType)*ei->cause ): ec_unknown;
            cbi->localConnectionInfo = ei->localConnectionInfo ? LocalConnectionStateType( (AsnIntType)*ei->localConnectionInfo ) : lcs_unknown;
            cbi->manufacturerOID = manufacturerOID;
            cbi->privateData = privateData;

            break;
            }

        case ASN::EventIDType::failed:
        {
            ASN::FailedEventInfo* ei = (ASN::FailedEventInfo*)eventRep->eventInfo.value;
            CBI_Failed* cbi = new CBI_Failed( apdu );
            cbInfo = cbi;

            cbi->failedConnection = connectionIdType( ei->failedConnection );
            cbi->failingDevice = deviceIdType( ei->failingDevice );
            cbi->calledDevice = deviceIdType( ei->calledDevice );
            cbi->cause = ei->cause ? EventCauseType( (AsnIntType)*ei->cause ): ec_unknown;
            cbi->localConnectionInfo = ei->localConnectionInfo ? LocalConnectionStateType( (AsnIntType)*ei->localConnectionInfo ) : lcs_unknown;
            cbi->manufacturerOID = manufacturerOID;
            cbi->privateData = privateData;

            break;
            }

        case ASN::EventIDType::held:
        {
            ASN::HeldEventInfo* ei = (ASN::HeldEventInfo*)eventRep->eventInfo.value;
            CBI_Held* cbi = new CBI_Held( apdu );
            cbInfo = cbi;

            cbi->heldConnection = connectionIdType( ei->heldConnection );
            cbi->holdingDevice = deviceIdType( ei->holdingDevice );
            cbi->cause = ei->cause ? EventCauseType( (AsnIntType)*ei->cause ): ec_unknown;
            cbi->localConnectionInfo = ei->localConnectionInfo ? LocalConnectionStateType( (AsnIntType)*ei->localConnectionInfo ) : lcs_unknown;
            cbi->manufacturerOID = manufacturerOID;
            cbi->privateData = privateData;

            break;
            }

        case ASN::EventIDType::networkReached:
        {
            ASN::NetworkReachedEventInfo* ei = (ASN::NetworkReachedEventInfo*)eventRep->eventInfo.value;
            CBI_NetworkReached* cbi = new CBI_NetworkReached( apdu );
            cbInfo = cbi;

            cbi->connection = connectionIdType( ei->connection );
            cbi->trunkUsed = deviceIdType( ei->trunkUsed );
            cbi->calledDevice = deviceIdType( ei->calledDevice );
            cbi->cause = ei->cause ? EventCauseType( (AsnIntType)*ei->cause ): ec_unknown;
            cbi->localConnectionInfo = ei->localConnectionInfo ? LocalConnectionStateType( (AsnIntType)*ei->localConnectionInfo ) : lcs_unknown;
            cbi->manufacturerOID = manufacturerOID;
            cbi->privateData = privateData;

            break;
            }

        case ASN::EventIDType::originated:
        {
            ASN::OriginatedEventInfo* ei = (ASN::OriginatedEventInfo*)eventRep->eventInfo.value;
            CBI_Originated* cbi = new CBI_Originated( apdu );
            cbInfo = cbi;

            cbi->originatedConnection = connectionIdType( ei->originatedConnection );
            cbi->callingDevice = deviceIdType( ei->callingDevice );
            cbi->calledDevice = deviceIdType( ei->calledDevice );
            cbi->cause = ei->cause ? EventCauseType( (AsnIntType)*ei->cause ): ec_unknown;
            cbi->localConnectionInfo = ei->localConnectionInfo ? LocalConnectionStateType( (AsnIntType)*ei->localConnectionInfo ) : lcs_unknown;
            cbi->manufacturerOID = manufacturerOID;
            cbi->privateData = privateData;

            break;
            }

        case ASN::EventIDType::queued:
        {
            ASN::QueuedEventInfo* ei = (ASN::QueuedEventInfo*)eventRep->eventInfo.value;
            CBI_Queued* cbi = new CBI_Queued( apdu );
            cbInfo = cbi;

            cbi->queuedConnection = connectionIdType( ei->queuedConnection );
            cbi->queue = deviceIdType( ei->queue );
            cbi->callingDevice = deviceIdType( ei->callingDevice );
            cbi->calledDevice = deviceIdType( ei->calledDevice );
            cbi->lastRedirectionDevice = deviceIdType( ei->lastRedirectionDevice );
            cbi->numberedQueued = ei->numberedQueued ? AsnIntType( *ei->numberedQueued ) : -1;
            cbi->cause = ei->cause ? EventCauseType( (AsnIntType)*ei->cause ): ec_unknown;
            cbi->localConnectionInfo = ei->localConnectionInfo ? LocalConnectionStateType( (AsnIntType)*ei->localConnectionInfo ) : lcs_unknown;
            cbi->manufacturerOID = manufacturerOID;
            cbi->privateData = privateData;

            break;
            }

        case ASN::EventIDType::retrieved:
        {
            ASN::RetrievedEventInfo* ei = (ASN::RetrievedEventInfo*)eventRep->eventInfo.value;
            CBI_Retrieved* cbi = new CBI_Retrieved( apdu );
            cbInfo = cbi;

            cbi->retrievedConnection = connectionIdType( ei->retrievedConnection );
            cbi->retrievingDevice = deviceIdType( cbi->retrievingDevice );
            cbi->cause = ei->cause ? EventCauseType( (AsnIntType)*ei->cause ): ec_unknown;
            cbi->localConnectionInfo = ei->localConnectionInfo ? LocalConnectionStateType( (AsnIntType)*ei->localConnectionInfo ) : lcs_unknown;
            cbi->manufacturerOID = manufacturerOID;
            cbi->privateData = privateData;

            break;
            }

        case ASN::EventIDType::serviceInitiated:
        {
            ASN::ServiceInitiatedEventInfo* ei = (ASN::ServiceInitiatedEventInfo*)eventRep->eventInfo.value;
            CBI_ServiceInitiated* cbi = new CBI_ServiceInitiated( apdu );
            cbInfo = cbi;

            cbi->initiatedConnection = connectionIdType( ei->initiatedConnection );
            cbi->cause = ei->cause ? EventCauseType( (AsnIntType)*ei->cause ): ec_unknown;
            cbi->localConnectionInfo = ei->localConnectionInfo ? LocalConnectionStateType( (AsnIntType)*ei->localConnectionInfo ) : lcs_unknown;
            cbi->manufacturerOID = manufacturerOID;
            cbi->privateData = privateData;

            break;
            }

        case ASN::EventIDType::transferred:
        {
            ASN::TransferredEventInfo* ei = (ASN::TransferredEventInfo*)eventRep->eventInfo.value;
            CBI_Transferred* cbi = new CBI_Transferred( apdu );
            cbInfo = cbi;

            cbi->primaryOldCall = connectionIdType( ei->primaryOldCall );
            cbi->secondaryOldCall = connectionIdType( ei->secondaryOldCall );
            cbi->transferringDevice = deviceIdType( ei->transferringDevice );
            cbi->transferredDevice = deviceIdType( ei->transferredDevice );

            // Create list of transferred connections
            //
            if ( ei->transferredConnections )
            {
                if ( ei->transferredConnections->choiceId == ConnectionList::connectionsCid )
                {
                    ASN::ConnectionIDList* connections = ei->transferredConnections->connections;
                    connections->SetCurrToFirst();

                    cbi->transferredConnectionsCount = connections->Count ();
                    cbi->transferredConnections = new USTR[ connections->Count () ];

                    int cni = 0;

                    while ( connections->Curr () )
                    {
                        cbi->transferredConnections[ cni++ ] = connectionIdType( connections->Curr () );

                        connections->GoNext ();
                        }
                    }
                else if ( ei->transferredConnections->choiceId == ConnectionList::callinformationCid )
                {
                    }
                }

            cbi->cause = ei->cause ? EventCauseType( (AsnIntType)*ei->cause ): ec_unknown;
            cbi->localConnectionInfo = ei->localConnectionInfo ? LocalConnectionStateType( (AsnIntType)*ei->localConnectionInfo ) : lcs_unknown;
            cbi->manufacturerOID = manufacturerOID;
            cbi->privateData = privateData;

            break;
            }

        case ASN::EventIDType::outOfService:
        {
            ASN::OutOfServiceEventInfo* ei = (ASN::OutOfServiceEventInfo*)eventRep->eventInfo.value;
            CBI_OutOfService* cbi = new CBI_OutOfService( apdu );
            cbInfo = cbi;

            cbi->device = deviceIdType( ei->device );
            cbi->cause = ei->cause ? EventCauseType( (AsnIntType)*ei->cause ): ec_unknown;
            cbi->manufacturerOID = manufacturerOID;
            cbi->privateData = privateData;

            break;
            }

        case ASN::EventIDType::backInService:
        {
            ASN::BackInServiceEventInfo* ei = (ASN::BackInServiceEventInfo*)eventRep->eventInfo.value;
            CBI_BackInService* cbi = new CBI_BackInService( apdu );
            cbInfo = cbi;

            cbi->device = deviceIdType( ei->device );
            cbi->cause = ei->cause ? EventCauseType( (AsnIntType)*ei->cause ): ec_unknown;
            cbi->manufacturerOID = manufacturerOID;
            cbi->privateData = privateData;

            break;
            }

        case ASN::EventIDType::loggedOn:
        {
            ASN::LoggedOnEventInfo* ei = (ASN::LoggedOnEventInfo*)eventRep->eventInfo.value;
            CBI_LoggedOn* cbi = new CBI_LoggedOn( apdu );
            cbInfo = cbi;

            cbi->agentDevice = deviceIdType( ei->agentDevice );
            cbi->agentID = USTR( ei->agentID );
            cbi->agentGroup = deviceIdType( ei->agentGroup );
            cbi->agentPassword = USTR( ei->password );
            cbi->manufacturerOID = manufacturerOID;
            cbi->privateData = privateData;

            break;
            }

        case ASN::EventIDType::loggedOff:
        {
            ASN::LoggedOffEventInfo* ei = (ASN::LoggedOffEventInfo*)eventRep->eventInfo.value;
            CBI_LoggedOff* cbi = new CBI_LoggedOff( apdu );
            cbInfo = cbi;

            cbi->agentDevice = deviceIdType( ei->agentDevice );
            cbi->agentID = USTR( ei->agentID );
            cbi->agentGroup = deviceIdType( ei->agentGroup );
            cbi->manufacturerOID = manufacturerOID;
            cbi->privateData = privateData;

            break;
            }

        case ASN::EventIDType::notReady:
        {
            ASN::NotReadyEventInfo* ei = (ASN::NotReadyEventInfo*)eventRep->eventInfo.value;
            CBI_NotReady* cbi = new CBI_NotReady( apdu );
            cbInfo = cbi;

            cbi->agentDevice = deviceIdType( ei->agentDevice );
            cbi->agentID = USTR( ei->agentID );
            cbi->manufacturerOID = manufacturerOID;
            cbi->privateData = privateData;

            break;
            }

        case ASN::EventIDType::ready:
        {
            ASN::ReadyEventInfo* ei = (ASN::ReadyEventInfo*)eventRep->eventInfo.value;
            CBI_Ready* cbi = new CBI_Ready( apdu );
            cbInfo = cbi;

            cbi->agentDevice = deviceIdType( ei->agentDevice );
            cbi->agentID = USTR( ei->agentID );
            cbi->manufacturerOID = manufacturerOID;
            cbi->privateData = privateData;

            break;
            }

        case ASN::EventIDType::workNotReady:
        {
            ASN::WorkNotReadyEventInfo* ei = (ASN::WorkNotReadyEventInfo*)eventRep->eventInfo.value;
            CBI_WorkNotReady* cbi = new CBI_WorkNotReady( apdu );
            cbInfo = cbi;

            cbi->agentDevice = deviceIdType( ei->agentDevice );
            cbi->agentID = USTR( ei->agentID );
            cbi->manufacturerOID = manufacturerOID;
            cbi->privateData = privateData;

            break;
            }

        case ASN::EventIDType::workReady:
        {
            ASN::WorkReadyEventInfo* ei = (ASN::WorkReadyEventInfo*)eventRep->eventInfo.value;
            CBI_WorkReady* cbi = new CBI_WorkReady( apdu );
            cbInfo = cbi;

            cbi->agentDevice = deviceIdType( ei->agentDevice );
            cbi->agentID = USTR( ei->agentID );
            cbi->manufacturerOID = manufacturerOID;
            cbi->privateData = privateData;

            break;
            }

        case ASN::EventIDType::callInformation:
        {
            ASN::CallInformationEventInfo* ei = (ASN::CallInformationEventInfo*)eventRep->eventInfo.value;
            CBI_CallInformation* cbi = new CBI_CallInformation( apdu );
            cbInfo = cbi;

            cbi->connection = connectionIdType( ei->connection );
            cbi->device = deviceIdType( ei->device );
            cbi->accountInfo = USTR( ei->accountInfo );
            cbi->authorisationCode = USTR( ei->authorisationCode );
            cbi->manufacturerOID = manufacturerOID;
            cbi->privateData = privateData;

            break;
            }

        case ASN::EventIDType::doNotDisturb:
        {
            ASN::DoNotDisturbEventInfo* ei = (ASN::DoNotDisturbEventInfo*)eventRep->eventInfo.value;
            CBI_DoNotDisturb* cbi = new CBI_DoNotDisturb( apdu );
            cbInfo = cbi;

            cbi->device = deviceIdType( ei->device );
            cbi->doNotDisturbFlag = ei->doNotDisturbOn;
            cbi->manufacturerOID = manufacturerOID;
            cbi->privateData = privateData;

            break;
            }

        case ASN::EventIDType::forwarding:
        {
            ASN::ForwardingEventInfo* ei = (ASN::ForwardingEventInfo*)eventRep->eventInfo.value;
            CBI_Forwarding* cbi = new CBI_Forwarding( apdu );
            cbInfo = cbi;

            cbi->device = deviceIdType( ei->device );
            if ( ei->forwardingInformation )
            {
                cbi->type = ::ForwardingType( (AsnIntType)ei->forwardingInformation->forwardingType );
                cbi->forwardDN = deviceIdType( ei->forwardingInformation->forwardDN );
                }
            else
            {
                cbi->type = ft_unknown;
                }
            cbi->forwardedTo = deviceIdType( ei->forwardedTo );
            cbi->manufacturerOID = manufacturerOID;
            cbi->privateData = privateData;

            break;
            }

        case ASN::EventIDType::messageWaiting:
        {
            ASN::MessageWaitingEventInfo* ei = (ASN::MessageWaitingEventInfo*)eventRep->eventInfo.value;
            CBI_MessageWaiting* cbi = new CBI_MessageWaiting( apdu );
            cbInfo = cbi;

            cbi->deviceForMessage = deviceIdType( ei->deviceForMessage );
            cbi->invokingDevice = deviceIdType( ei->invokingDevice );
            cbi->messageWaitingFlag = ei->messageWaitingOn;
            cbi->manufacturerOID = manufacturerOID;
            cbi->privateData = privateData;

            break;
            }

        case ASN::EventIDType::privateEvt:
        {
            ASN::PrivateEventInfo* ei = (ASN::PrivateEventInfo*)eventRep->eventInfo.value;
            CBI_PrivateEvent* cbi = new CBI_PrivateEvent( apdu );
            cbInfo = cbi;

            cbi->data = USTR( "" );

            break;
            }
        }

    if ( ! cbInfo )
    {
        delete mem;
        return;
        }

    // Enqueue event for dispatching to callback procedures.
    // APDU Memory Block will be released when cbInfo reference count 
    // comes to zero.
    //
    cbQueue.Put( cbInfo );
    }

//////////////////////////////////////////////////////////////////////////////
} // namespace MidCSTA