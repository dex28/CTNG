#ifndef _CSTA_LIB_H_INCLUDED
#define _CSTA_LIB_H_INCLUDED

/*
    Project: CSTALib

    Module: CSTA-Lib.h

    Description: CSTA Library declarations

    Copyright (c) 2002,2003 By Mikica B Kocic
    Copyright (c) 2002,2003 By IPTC Technology Communication AB
*/

#include "ASN1-Lib.h"
#include "CTsvcLIB.h"
#include "CSTA-EnumTypes.h"
#include "CSTA.h"

namespace MidCSTA
{
using namespace CTsvcLIB;

//============================================================================
//                              CSTA object classes
//============================================================================

class System;
class Device;

#include "CSTA-Lib2.h"

//============================================================================
//                               System
//============================================================================

class System
{
    friend Device;

    Mutex                   mutex; // protects object's structure
    std::list<PBX*>         pbxs;  // list of PBXs known to the System

    // Statistics
    volatile unsigned long  tot_dev_constructed;
    volatile unsigned long  tot_dev_destructed;

    // Devices Watchdog
    std::list<Device*>      devices;       // list of devices known to the System
    Semaphore               sema_watchdog; // triggers watchdog

    // Devices Garbage Collector
    std::list<Device*>      gc_devices;      // list of devices deferred to be deleted
    Semaphore               sema_gc_devices; // contains number of gc_devices

    // Queued IO Completion pool & QIO Dispatcher
    WSADATA                 wsaData;
    HANDLE                  hCompletionPort;

    // ASN memory block pools
    MemPool                 inboundMemPool;
    MemPool                 outboundMemPool;

    // Thread management
    volatile bool           isTerminating;
    long                    qioDispatcherThreadCount;
    long                    gcThreadCount;
    long                    watchdogThreadCount;
    long                    simultaneousQIO;
    long                    maxSimultaneousQIO;

    // Class Level Operations: Threads
    static unsigned int __stdcall QIO_Dispatcher_Thread( void* theSystem );
    static unsigned int __stdcall GC_Thread( void* theSystem );
    static unsigned int __stdcall Watchdog_Thread( void* theSystem );

    // Class Level Attributes:
    static volatile bool    hasConsole;

    MemBlock* AllocateInboundMemBlock( void )
    {
        return new(inboundMemPool) MemBlock(inboundMemPool);
        }

    MemBlock* AllocateOutboundMemBlock( void )
    {
        return new(outboundMemPool) MemBlock(outboundMemPool);
        }

public:

    System( void );
    ~System( void );

    void Initialize( int cQIODispatchers = 8, int cGC = 2, int cWatchdog = 2 );
    void DumpStatistics( void );
    void Destroy( void );

    HANDLE GetCompletionPort() const { return hCompletionPort; }

    void AddPABX( const char* pbxID, const char* ip_address, unsigned short tcp_port );

    ErrorCode OpenDevice( CallbackProcedure* cbProc, const char* pbxID, const char* devID, bool asyncConnect = false );

    // Class Level Operations:
    //
    static bool HasConsole( void ) { return hasConsole; }
    static void OpenLogFile( const char* filename );
    static void OpenConsole ();
    static void CloseConsole ();

    static const char* VerboseCategory( ErrorCode rc );
    static const char* Verbose( ErrorCode rc );
    static const char* Verbose( SystemStatusType value );
    static const char* Verbose( LocalConnectionStateType value );
    static const char* Verbose( EventCauseType value );
    };

//============================================================================
//                               Device class
//============================================================================

class Device
    : public RefCount
{
    friend unsigned int System::QIO_Dispatcher_Thread( void* );

private:

    enum ReceiverState
    {
        RECEIVING_CSTA_HEADER,
        RECEIVING_CSTA_APDU_BODY
        };

    class InvokeResponse // ROSE Invoke and its Response APDU holder
    {
        MemBlock*           mem;       // memory block used to allocate Invoke APDU
        ASN::CSTAapdu*      response;  // result, reject or error APDU types

    public:

        InvokeResponse( MemBlock* memBlock )
            : mem( memBlock )
        {
            }

        ~InvokeResponse( void )
        {
            if ( mem )
                delete mem;

            if ( response )
                delete response->GetMemBlock ();
            }

        // MemBlock* GetMemBlock( void ) { return mem; }

        ASN::CSTAapdu* GetAPDU( void ) { return response; }

        void SetAPDU( ASN::CSTAapdu* apdu ) { response = apdu; }
        };

    // Attributes
    System*                    system;
    PBX*                       pbx;

    CallbackQueue              cbQueue; // event callback queue

    // CSTA Connection
    Mutex                      connMutex;   // protects connection status context
    SOCKET                     hSocket;     // connection socket
    HANDLE                     hCP;         // completion port
    volatile bool              isConnected;
    // Monitor
    deviceIdType               devID;
    USTR                       monitorID;   // monitor cross reference id; qualifies cstaConn
                                            // always BINARY USTR

    // CSTA Receiver Context
    Mutex                      ioMutex;     // protects receiver context
    volatile ReceiverState     recvState;
    OVERLAPPED                 Overlapped_Read;  // asynchronous I/O Read
    uint8                      inputData[ 4096 ]; // receive buffer
    size_t                     inputDataLen;
    size_t                     inputDataPtr;

    // CSTA Transmitter Context
    Mutex                      serviceMutex;  // only one outbound ROSE should be issued at time
    Mutex                      responseMutex; // protects currentResponse..responseEvent
    InvokeResponse*            currentResponse;
    AsnIntType                 currentInvokeID;
    HANDLE                     responseEvent;  // event that will be signaled when invoke completes
    DWORD                      invokeTimeout; // timeout parameter

// Private Methods

    // RefCount implementation

    void OnRefCountZero( void )
    {
        cbQueue.SetCallbackProcedure( NULL );

        if ( 1 ) // Synchronous delete; Imeddiate delete device
        {
            // Remove from system's devices
            system->mutex.Lock ();
            system->devices.remove( this );
            system->gc_devices.push_back( this );
            system->mutex.Unlock ();

            delete this;
            }
        else // Asynchronous delete; System::GC_Thread will delete this device
        {
            // Move from system's devices to gc_devices list
            system->mutex.Lock ();
            system->devices.remove( this );
            system->gc_devices.push_back( this );
            system->sema_gc_devices.Release( 1 );
            system->mutex.Unlock ();
            }
        }

    // QIO
    //
    bool PostRead( void* inputDataBuf, DWORD maxInputDataLen );
    void PostNullQIO( void );
    bool DispatchIO( BOOL bSuccess, DWORD error, DWORD ioSize, OVERLAPPED* overlapped );
    bool OnReadCompleted( DWORD ioSize );
    bool OnNullQIO( void );
    bool OnErrorQIO( DWORD errorCode );
    bool OnDisconnected( void );

    // Inbound CSTA
    //
    void DecodeReceivedAPDU( uint8* data, unsigned long len );
    void OnRecv_EventReport( ASN::CSTAapdu* apdu );
    void OnRecv_SystemStatus( ASN::CSTAapdu* apdu );
    void OnRecv_EscapeService( ASN::CSTAapdu* apdu );

    // Outbound CSTA
    //
    ErrorCode EncodeAndSendAPDU( ASN::CSTAapdu* apdu );
    ErrorCode ROSE_SendResult( AsnIntType op_id, AsnIntType remote_invoke_id, AsnType* result );
    ErrorCode ROSE_SendReject( AsnIntType remote_invoke_id, ASN::RORJapduChoice1* problem );
    // Outbound Invoke
    ErrorCode ROSE_Invoke( InvokeResponse& response, AsnIntType op_id, AsnType* arg );
    void ROSE_CancelInvoke( void );
    void ROSE_SignalResponse( ASN::CSTAapdu* apdu, AsnIntType got_invoke_id = 0 );

    // Private CSTA operations
    ErrorCode OpenConnection( void );
    ErrorCode CloseConnection( bool graceful = true );

    ErrorCode MonitorStart( CSTA_Extensions* exts = NULL );
    ErrorCode MonitorStop( CSTA_Extensions* exts = NULL );
    ErrorCode ChangeMonitorFilter( CSTA_Extensions* exts = NULL );

public:

    const deviceIdType& ID () const { return devID; }

    Device( System* pSystem, PBX* pPBX, const char* device_id, CallbackProcedure* cbProc )
        : system( pSystem )
        , pbx( pPBX )
        , devID( device_id )
        , cbQueue()
        , isConnected( false )
        , hSocket( NULL )
        , hCP( NULL )
        , inputDataPtr( 0 )
        , inputDataLen( 0 )
        , currentResponse( NULL )
        , currentInvokeID( 0 )
        , invokeTimeout( 3000 ) // milliseconds
    {
        memset( &Overlapped_Read, 0, sizeof( Overlapped_Read ) );

        responseEvent = ::CreateEvent( NULL, /*manualreset*/TRUE, /*initialstate*/FALSE, NULL );
        TRASSERT( responseEvent != NULL );

        system->mutex.Lock ();
        system->tot_dev_constructed++;
        system->devices.push_back( this );
        system->sema_watchdog.Release( 1 );
        system->mutex.Unlock ();

        cbProc->SetDevice( this );
        cbQueue.SetCallbackProcedure( cbProc );

        TRACE( this << " Device::Device: ID " << devID );
        }

    virtual ~Device( void )
    {
        TRACE( this << " Device::~Device: ID " << devID );

        MonitorStop ();
        CloseConnection ();

        connMutex.Lock ();

        if ( hSocket )
            ::closesocket( hSocket );

        connMutex.Unlock ();

        ::CloseHandle( responseEvent );

        system->mutex.Lock ();
        system->tot_dev_destructed++;
        system->gc_devices.remove( this );
        system->mutex.Unlock ();
        }

    // Public CSTA Operations

    ErrorCode Initialize( const char* newDevId = NULL );

    ErrorCode SnapshotDevice( CSTA_Extensions* exts = NULL );
    ErrorCode SnapshotCall( const connectionIdType& connId, CSTA_Extensions* exts = NULL );

    ErrorCode EscapeService( CSTA_Extensions& exts );
    ErrorCode SystemStatus( const SystemStatusType status, CSTA_Extensions* exts = NULL );

    ErrorCode AnswerCall( const connectionIdType& connId, CSTA_Extensions* exts = NULL );
    ErrorCode AlternateCall( const connectionIdType& held, const connectionIdType& active, CSTA_Extensions* exts = NULL );
    ErrorCode CallCompletion( const connectionIdType& connId, FeatureInfoType featureId, CSTA_Extensions* exts = NULL );
    ErrorCode ClearCall( const connectionIdType& connId, CSTA_Extensions* exts = NULL );
    ErrorCode ClearConnection( const connectionIdType& connId, CSTA_Extensions* exts = NULL );
    ErrorCode ConferenceCall( const connectionIdType& held, const connectionIdType& active, connectionIdType& conferenceCall, CSTA_Extensions* exts = NULL );
    ErrorCode ConsultationCall( const connectionIdType& connId, const char* deviceId2call, connectionIdType& initiatedConnId, CSTA_Extensions* exts = NULL );

    ErrorCode DivertCall_Deflect( const connectionIdType& connId, const char* newDestination, CSTA_Extensions* exts = NULL );
    ErrorCode DivertCall_DirectedPickup( const connectionIdType& connId, const char* requestingDevice, CSTA_Extensions* exts = NULL );
    ErrorCode DivertCall_GroupPickup( const char* groupDevice, CSTA_Extensions* exts = NULL );

    ErrorCode HoldCall( const connectionIdType& connId, bool connectionReservation, CSTA_Extensions* exts = NULL );
    ErrorCode MakeCall( const char* deviceId2call, connectionIdType& connId, CSTA_Extensions* exts = NULL );
    ErrorCode ReconnectCall( const connectionIdType& held, const connectionIdType& active, CSTA_Extensions* exts = NULL );
    ErrorCode RetrieveCall( const connectionIdType& connId, CSTA_Extensions* exts = NULL );
    ErrorCode TransferCall( const connectionIdType& held, const connectionIdType& active, connectionIdType& transferredCall, CSTA_Extensions* exts = NULL );

    ErrorCode QueryDevice_MessageWaiting( bool& indicator, CSTA_Extensions* exts = NULL );
    ErrorCode QueryDevice_DoNotDisturb( bool& indicator, CSTA_Extensions* exts = NULL );
    ErrorCode QueryDevice_Forward( USTR& forwardInfo, CSTA_Extensions* exts = NULL );
    ErrorCode QueryDevice_DeviceInfo( DeviceClassType& cls, DeviceTypeType& typ, CSTA_Extensions* exts = NULL );
    ErrorCode QueryDevice_AgentState( AgentStateType& state, CSTA_Extensions* exts = NULL );

    ErrorCode SetFeature_MessageWaiting( const bool indicator, CSTA_Extensions* exts = NULL );
    ErrorCode SetFeature_DoNotDisturb( const bool indicator, CSTA_Extensions* exts = NULL );
    ErrorCode SetFeature_Forward( const ForwardingType forwardingType, const USTR forwardDN, CSTA_Extensions* exts = NULL );
    ErrorCode SetFeature_RequestAgentState( const AgentParameterType apt, const USTR& agentId, const USTR& agentGroup, const USTR& agentPassword, CSTA_Extensions* exts = NULL );

    ErrorCode TestFireAllEvents( void );
    };

//============================================================================
//                           Inline method definitions
//============================================================================

//////////////////////////////////////////////////////////////////////////////
} // namsepace MidCSTA

#endif // _CSTA_LIB_H_INCLUDED
