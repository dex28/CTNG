/*
    Project: CTNG COM ATL

    Module: Device_CB.cpp

    Description: Implementation of CDevice_CB_Proc

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "stdafx.h"
#include "CTNG.h"
#include "Device.h"

class ToVariantByteSafeArray
{
    SAFEARRAY* psa;
public:
    ToVariantByteSafeArray( USTR& str )
    {
        psa = str.CreateSafeByteArray ();
        }
    operator SAFEARRAY** ()
    {
        return &psa;
        }
    ~ToVariantByteSafeArray( void )
    {
        ::SafeArrayDestroy( psa );
        }
    };

STAT_COUNTERS stat = { 0 };

CDevice_CB_Proc::CDevice_CB_Proc( CDevice* obj )
    : CallbackProcedure()
{
    object = obj;
    }

CDevice_CB_Proc::~CDevice_CB_Proc( void )
{
    object = NULL;
    }

void CDevice_CB_Proc::OnRefCountZero( void )
{
    ReleaseDevice ();
    delete this;
    }

void CDevice_CB_Proc::Procedure( MidCSTA::CallbackInfo* cbi )
{
    if ( ! object || ! cbi ) return;

    switch( cbi->GetType () )
    {
        case ASN::EventIDType::callCleared:
        {
            MidCSTA::CBI_CallCleared* info = (MidCSTA::CBI_CallCleared*)cbi;

            object->Fire_OnCallCleared
            (
                CComBSTR( info->clearedCall ),
                LocalConnectionStateType( info->localConnectionInfo ),
                EventCauseType( info->cause ),
                ToVariantByteSafeArray( info->manufacturerOID ), 
                ToVariantByteSafeArray( info->privateData )
                );

            }
            break;

        case ASN::EventIDType::conferenced:
        {
            MidCSTA::CBI_Conferenced* info = (MidCSTA::CBI_Conferenced*)cbi;

            char idlist[ 4096 ]; // size is 50 times more than we need
            idlist[ 0 ] = 0;

            for ( int i = 0; i < info->conferenceConnectionsCount; i++ )
            {
                strcat( idlist, info->conferenceConnections[ i ] );
                strcat( idlist, ";" );
                }

            object->Fire_OnConferenced
            (
                CComBSTR( info->primaryOldCall ),
                CComBSTR( info->secondaryOldCall ),
                CComBSTR( info->confController ),
                CComBSTR( info->addedParty ),
                CComBSTR( idlist ),
                LocalConnectionStateType( info->localConnectionInfo ),
                EventCauseType( info->cause ),
                ToVariantByteSafeArray( info->manufacturerOID ),
                ToVariantByteSafeArray( info->privateData )
                );
            }
            break;

        case ASN::EventIDType::connectionCleared:
        {
            ::InterlockedIncrement( &stat.countOfConnectionCleared );

            MidCSTA::CBI_ConnectionCleared* info = (MidCSTA::CBI_ConnectionCleared*)cbi;

            object->Fire_OnConnectionCleared
            (
                CComBSTR( info->droppedConnection ),
                CComBSTR( info->releasingDevice ),
                LocalConnectionStateType( info->localConnectionInfo ),
                EventCauseType( info->cause ),
                ToVariantByteSafeArray( info->manufacturerOID ),
                ToVariantByteSafeArray( info->privateData )
                );
            }
            break;

        case ASN::EventIDType::delivered:
        {
            MidCSTA::CBI_Delivered* info = (MidCSTA::CBI_Delivered*)cbi;

            object->Fire_OnDelivered
            (
                CComBSTR( info->connection ),
                CComBSTR( info->alertingDevice ),
                CComBSTR( info->callingDevice ),
                CComBSTR( info->calledDevice ),
                CComBSTR( info->lastRedirectionDevice ),
                LocalConnectionStateType( info->localConnectionInfo ),
                EventCauseType( info->cause ),
                ToVariantByteSafeArray( info->manufacturerOID ),
                ToVariantByteSafeArray( info->privateData )
                );
            }
            break;

        case ASN::EventIDType::diverted:
        {
            MidCSTA::CBI_Diverted* info = (MidCSTA::CBI_Diverted*)cbi;

            object->Fire_OnDiverted
            (
                CComBSTR( info->connection ),
                CComBSTR( info->divertingDevice ),
                CComBSTR( info->newDestination ),
                LocalConnectionStateType( info->localConnectionInfo ),
                EventCauseType( info->cause ),
                ToVariantByteSafeArray( info->manufacturerOID ),
                ToVariantByteSafeArray( info->privateData )
                );
            }
            break;

        case ASN::EventIDType::established:
        {
            ::InterlockedIncrement( &stat.countOfEstablished );

            MidCSTA::CBI_Established* info = (MidCSTA::CBI_Established*)cbi;

            object->Fire_OnEstablished
            (
                CComBSTR( info->establishedConnection ),
                CComBSTR( info->answeringDevice ),
                CComBSTR( info->callingDevice ),
                CComBSTR( info->calledDevice ),
                CComBSTR( info->lastRedirectionDevice ),
                LocalConnectionStateType( info->localConnectionInfo ),
                EventCauseType( info->cause ),
                ToVariantByteSafeArray( info->manufacturerOID ),
                ToVariantByteSafeArray( info->privateData )
                );
            }
            break;

        case ASN::EventIDType::failed:
        {
            MidCSTA::CBI_Failed* info = (MidCSTA::CBI_Failed*)cbi;

            object->Fire_OnFailed
            (
                CComBSTR( info->failedConnection ),
                CComBSTR( info->failingDevice ),
                CComBSTR( info->calledDevice ),
                LocalConnectionStateType( info->localConnectionInfo ),
                EventCauseType( info->cause ),
                ToVariantByteSafeArray( info->manufacturerOID ),
                ToVariantByteSafeArray( info->privateData )
                );
            }
            break;

        case ASN::EventIDType::held:
        {
            MidCSTA::CBI_Held* info = (MidCSTA::CBI_Held*)cbi;

            object->Fire_OnHeld
            (
                CComBSTR( info->heldConnection ),
                CComBSTR( info->holdingDevice ),
                LocalConnectionStateType( info->localConnectionInfo ),
                EventCauseType( info->cause ),
                ToVariantByteSafeArray( info->manufacturerOID ),
                ToVariantByteSafeArray( info->privateData )
                );
            }
            break;

        case ASN::EventIDType::networkReached:
        {
            MidCSTA::CBI_NetworkReached* info = (MidCSTA::CBI_NetworkReached*)cbi;

            object->Fire_OnNetworkReached
            (
                CComBSTR( info->connection ),
                CComBSTR( info->trunkUsed ),
                CComBSTR( info->calledDevice ),
                LocalConnectionStateType( info->localConnectionInfo ),
                EventCauseType( info->cause ),
                ToVariantByteSafeArray( info->manufacturerOID ),
                ToVariantByteSafeArray( info->privateData )
                );
            }
            break;

        case ASN::EventIDType::originated:
        {
            MidCSTA::CBI_Originated* info = (MidCSTA::CBI_Originated*)cbi;

            object->Fire_OnOriginated
            (
                CComBSTR( info->originatedConnection ),
                CComBSTR( info->callingDevice ),
                CComBSTR( info->calledDevice ),
                LocalConnectionStateType( info->localConnectionInfo ),
                EventCauseType( info->cause ),
                ToVariantByteSafeArray( info->manufacturerOID ),
                ToVariantByteSafeArray( info->privateData )
                );
            }
            break;

        case ASN::EventIDType::queued:
        {
            MidCSTA::CBI_Queued* info = (MidCSTA::CBI_Queued*)cbi;

            object->Fire_OnQueued
            (
                CComBSTR( info->queuedConnection ),
                CComBSTR( info->queue ),
                CComBSTR( info->callingDevice ),
                CComBSTR( info->calledDevice ),
                CComBSTR( info->lastRedirectionDevice ),
                info->numberedQueued,
                LocalConnectionStateType( info->localConnectionInfo ),
                EventCauseType( info->cause ),
                ToVariantByteSafeArray( info->manufacturerOID ),
                ToVariantByteSafeArray( info->privateData )
                );
            }
            break;

        case ASN::EventIDType::retrieved:
        {
            MidCSTA::CBI_Retrieved* info = (MidCSTA::CBI_Retrieved*)cbi;

            object->Fire_OnRetrieved
            (
                CComBSTR( info->retrievedConnection ),
                CComBSTR( info->retrievingDevice ),
                LocalConnectionStateType( info->localConnectionInfo ),
                EventCauseType( info->cause ),
                ToVariantByteSafeArray( info->manufacturerOID ),
                ToVariantByteSafeArray( info->privateData )
                );
            }
            break;

        case ASN::EventIDType::serviceInitiated:
        {
            MidCSTA::CBI_ServiceInitiated* info = (MidCSTA::CBI_ServiceInitiated*)cbi;

            object->Fire_OnServiceInitiated
            (
                CComBSTR( info->initiatedConnection ),
                LocalConnectionStateType( info->localConnectionInfo ),
                EventCauseType( info->cause ),
                ToVariantByteSafeArray( info->manufacturerOID ),
                ToVariantByteSafeArray( info->privateData )
                );
            }
            break;

        case ASN::EventIDType::transferred:
        {
            MidCSTA::CBI_Transferred* info = (MidCSTA::CBI_Transferred*)cbi;

            char idlist[ 4096 ]; // size is 50 times more than we need
            idlist[ 0 ] = 0;

            for ( int i = 0; i < info->transferredConnectionsCount; i++ )
            {
                strcat( idlist, info->transferredConnections[ i ] );
                strcat( idlist, ";" );
                }

            object->Fire_OnTransferred
            (
                CComBSTR( info->primaryOldCall ),
                CComBSTR( info->secondaryOldCall ),
                CComBSTR( info->transferringDevice ),
                CComBSTR( info->transferredDevice ),
                CComBSTR( idlist ),
                LocalConnectionStateType( info->localConnectionInfo ),
                EventCauseType( info->cause ),
                ToVariantByteSafeArray( info->manufacturerOID ),
                ToVariantByteSafeArray( info->privateData )
                );
            }
            break;

        case ASN::EventIDType::outOfService:
        {
            ::InterlockedIncrement( &stat.countOfOutOfService );

            MidCSTA::CBI_OutOfService* info = (MidCSTA::CBI_OutOfService*)cbi;

            object->Fire_OnOutOfService
            (
                CComBSTR( info->device ),
                EventCauseType( info->cause ),
                ToVariantByteSafeArray( info->manufacturerOID ),
                ToVariantByteSafeArray( info->privateData )
                );
            }
            break;

        case ASN::EventIDType::backInService:
        {
            ::InterlockedIncrement( &stat.countOfBackInService );

            MidCSTA::CBI_BackInService* info = (MidCSTA::CBI_BackInService*)cbi;

            object->Fire_OnBackInService
            (
                CComBSTR( info->device ),
                EventCauseType( info->cause ),
                ToVariantByteSafeArray( info->manufacturerOID ),
                ToVariantByteSafeArray( info->privateData )
                );
            }
            break;

        case ASN::EventIDType::loggedOn:
        {
            MidCSTA::CBI_LoggedOn* info = (MidCSTA::CBI_LoggedOn*)cbi;

            object->Fire_OnLoggedOn
            (
                CComBSTR( info->agentDevice ),
                CComBSTR( info->agentID ),
                CComBSTR( info->agentGroup ),
                CComBSTR( info->agentPassword ),
                ToVariantByteSafeArray( info->manufacturerOID ),
                ToVariantByteSafeArray( info->privateData )
                );
            }
            break;

        case ASN::EventIDType::loggedOff:
        {
            MidCSTA::CBI_LoggedOff* info = (MidCSTA::CBI_LoggedOff*)cbi;

            object->Fire_OnLoggedOff
            (
                CComBSTR( info->agentDevice ),
                CComBSTR( info->agentID ),
                CComBSTR( info->agentGroup ),
                ToVariantByteSafeArray( info->manufacturerOID ),
                ToVariantByteSafeArray( info->privateData )
                );
            }
            break;

        case ASN::EventIDType::notReady:
        {
            MidCSTA::CBI_NotReady* info = (MidCSTA::CBI_NotReady*)cbi;

            object->Fire_OnNotReady
            (
                CComBSTR( info->agentDevice ),
                CComBSTR( info->agentID ),
                ToVariantByteSafeArray( info->manufacturerOID ),
                ToVariantByteSafeArray( info->privateData )
                );
            }
            break;

        case ASN::EventIDType::ready:
        {
            MidCSTA::CBI_Ready* info = (MidCSTA::CBI_Ready*)cbi;

            object->Fire_OnReady
            (
                CComBSTR( info->agentDevice ),
                CComBSTR( info->agentID ),
                ToVariantByteSafeArray( info->manufacturerOID ),
                ToVariantByteSafeArray( info->privateData )
                );
            }
            break;

        case ASN::EventIDType::workNotReady:
        {
            MidCSTA::CBI_WorkNotReady* info = (MidCSTA::CBI_WorkNotReady*)cbi;

            object->Fire_OnWorkNotReady
            (
                CComBSTR( info->agentDevice ),
                CComBSTR( info->agentID ),
                ToVariantByteSafeArray( info->manufacturerOID ),
                ToVariantByteSafeArray( info->privateData )
                );
            }
            break;

        case ASN::EventIDType::workReady:
        {
            MidCSTA::CBI_WorkReady* info = (MidCSTA::CBI_WorkReady*)cbi;

            object->Fire_OnWorkReady
            (
                CComBSTR( info->agentDevice ),
                CComBSTR( info->agentID ),
                ToVariantByteSafeArray( info->manufacturerOID ),
                ToVariantByteSafeArray( info->privateData )
                );
            }
            break;

        case ASN::EventIDType::callInformation:
        {
            MidCSTA::CBI_CallInformation* info = (MidCSTA::CBI_CallInformation*)cbi;

            object->Fire_OnCallInformation
            (
                CComBSTR( info->connection ),
                CComBSTR( info->device ),
                CComBSTR( info->accountInfo ),
                CComBSTR( info->authorisationCode ),
                ToVariantByteSafeArray( info->manufacturerOID ),
                ToVariantByteSafeArray( info->privateData )
                );
            }
            break;

        case ASN::EventIDType::doNotDisturb:
        {
            MidCSTA::CBI_DoNotDisturb* info = (MidCSTA::CBI_DoNotDisturb*)cbi;

            object->Fire_OnDoNotDisturb
            (
                CComBSTR( info->device ),
                info->doNotDisturbFlag,
                ToVariantByteSafeArray( info->manufacturerOID ),
                ToVariantByteSafeArray( info->privateData )
                );
            }
            break;

        case ASN::EventIDType::forwarding:
        {
            MidCSTA::CBI_Forwarding* info = (MidCSTA::CBI_Forwarding*)cbi;

            object->Fire_OnForwarding
            (
                CComBSTR( info->device ),
                info->type,
                CComBSTR( info->forwardDN ),
                CComBSTR( info->forwardedTo ),
                ToVariantByteSafeArray( info->manufacturerOID ),
                ToVariantByteSafeArray( info->privateData )
                );
            }
            break;

        case ASN::EventIDType::messageWaiting:
        {
            MidCSTA::CBI_MessageWaiting* info = (MidCSTA::CBI_MessageWaiting*)cbi;

            object->Fire_OnMessageWaiting
            (
                CComBSTR( info->deviceForMessage ),
                CComBSTR( info->invokingDevice ),
                info->messageWaitingFlag,
                ToVariantByteSafeArray( info->manufacturerOID ),
                ToVariantByteSafeArray( info->privateData )
                );
            }
            break;

        case ASN::EventIDType::privateEvt:
        {
            MidCSTA::CBI_PrivateEvent* info = (MidCSTA::CBI_PrivateEvent*)cbi;

            object->Fire_OnPrivateEvent
            (
                ToVariantByteSafeArray( info->data )
                );
            }
            break;

        ////////////////////////////////////////////////////////////////////////
        // Invoke notifications
        ////////////////////////////////////////////////////////////////////////

        case 0x1001: // system status invoked
        {
            MidCSTA::CBI_SystemStatus* info = (MidCSTA::CBI_SystemStatus*)cbi;

            object->Fire_OnSystemStatus
            (
                SystemStatusType( info->status ),
                ToVariantByteSafeArray( info->manufacturerOID ),
                ToVariantByteSafeArray( info->privateData )
                );

            }
            break;

        case 0x1002: // system status invoked
        {
            MidCSTA::CBI_MonitorStarted* info = (MidCSTA::CBI_MonitorStarted*)cbi;

            object->Fire_OnMonitorStarted
            (
                info->errCode
                );
            }
            break;

        case 0x1003: // remote disconnected
        {
            while( CTNG_NO_ERROR != GetDev()->Initialize () )
                Sleep( 1000 );
            }
            break;
        }
    }
