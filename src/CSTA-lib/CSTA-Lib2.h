class CallbackQueue;
class CallbackProcedure;
class CallbackInfo;

//============================================================================
//                         CSTA object's identifiers types
//============================================================================

class deviceIdType 
    : public USTR
{
    // If binary, it is originated from dynamic device id.
    // If ascii, it is originated from static device id, it can be:
    // - <IA5String>
    // - "notKnown"
    // - "notRequred"
    // - "?"
public:

    deviceIdType( void ) {}

    deviceIdType( const USTR& str )
        : USTR( str ) {}

    deviceIdType( ASN::DeviceID* asn );

    deviceIdType( ASN::ExtendedDeviceID* asn );

    deviceIdType( ASN::CalledDeviceID* asn );

    deviceIdType( ASN::CallingDeviceID* asn );

    deviceIdType( ASN::RedirectionDeviceID* asn );

    deviceIdType( ASN::SubjectDeviceID* asn );

    operator USTR () const
        { return *this; }

    ASN::DeviceID* BuildDeviceID( MemBlock* mem ) const;
    };

class connectionIdType
{
    deviceIdType devId;
    USTR callId;

public:

    connectionIdType( void )
        {}

    connectionIdType( const connectionIdType& cn )
        { devId = cn.devId; callId = cn.callId; }

    connectionIdType( const deviceIdType& d, const USTR& c )
        : devId( d ), callId( c ) {}

    connectionIdType( ASN::ConnectionID* asn );

    connectionIdType( const USTR& ustr );

    void operator = ( const connectionIdType& cn )
        { devId = cn.devId; callId = cn.callId; }

    const deviceIdType& DevID( void ) const
        { return devId; }

    const USTR& CallID( void ) const
        { return callId; }

    bool operator == ( const connectionIdType& cn ) const
        { return devId == cn.devId && callId == cn.callId; }

    void Print( CTsvcLIB::LOG& os ) const
        { os << devId << ":" << callId; }

    operator USTR () const;

    ASN::ConnectionID* BuildConnectionID( MemBlock* mem ) const;
    };

inline CTsvcLIB::LOG& operator << ( CTsvcLIB::LOG& os, const connectionIdType& cn )
{
    cn.Print( os ); return os;
    }

// CSTA extensions structure
// contains outbound OID&Data and inbound OID&Data extensions for the service
//
struct CSTA_Extensions
{
    USTR outOID;
    USTR outData;
    USTR inOID;
    USTR inData;
    };

//============================================================================
//                               PBX
//============================================================================

struct PBX
{
    USTR                  pbxID;
    USTR                  ip_address;
    unsigned short        tcp_port;

    PBX( void )
        : pbxID ()
        , ip_address ()
        , tcp_port( 0 )
    {}

    PBX( const char* id, const char* addr, const unsigned short port )
        : pbxID( id )
        , ip_address( addr )
        , tcp_port( port )
    {}

    PBX( const PBX& params )
        : pbxID ( params.pbxID )
        , ip_address( params.ip_address )
        , tcp_port( params.tcp_port )
    {}

    PBX& operator= ( const PBX& params )
    {
        pbxID = params.pbxID;
        ip_address = params.ip_address;
        tcp_port = params.tcp_port;
        return *this;
        }

    void SetConnParams( const char* addr, const unsigned short port )
    {
        ip_address = addr;
        tcp_port = port;
        }
    };

//============================================================================
//                               Callback Queue
//============================================================================

class CallbackQueue
{
    struct Msg
    {
        CallbackInfo*       info;
        };

    // Attributes:
    Mutex                   procMutex;
    CallbackProcedure*      cbProc;
    volatile bool           isTerminating;
    long                    dispatcherCount;

    Mutex                   mutex;
    Semaphore               semaFull;
    Semaphore               semaEmpty;

    Msg*                    MQue; // Circular array
    long                    maxQueueLen;
    long                    queueLen;
    long                    putPtr;
    long                    getPtr;

    bool Get( CallbackInfo*&, DWORD dwTimeout = INFINITE );

    // Static:
    static unsigned int __stdcall Dispatcher_Thread( void* thisCBQ );

public:

    CallbackQueue( long size = 128 );
    ~CallbackQueue ();

    void SetCallbackProcedure( CallbackProcedure* proc )
    {
        procMutex.Lock ();
        cbProc = proc;
        procMutex.Unlock ();
        }

    void Put( CallbackInfo* info, DWORD dwTimeout = INFINITE );
    };

//============================================================================
//                            Callback Procedure
//============================================================================

class CallbackProcedure 
    : public RefCount
{
    Ptr<Device> device; // we sink events from this device

public:

    CallbackProcedure( void )
    {
        TRACE( this << " CallbackProcedure::CallbackProcedure" );
        }

    virtual ~CallbackProcedure( void )
    {
        TRACE( this << " CallbackProcedure::~CallbackProcedure" );
        device = NULL; // release device
        }

    void ReleaseDevice( void )
    {
        TRACE( this << " CallbackProcedure::ReleaseDevice; Device " << device );
        device = NULL;
        }

    void SetDevice( Device* dev )
    {
        TRACE( this << " CallbackProcedure::SetDevice; Device " << dev );
        device = dev;
        }

    Device* GetDev( void )
    { 
        return device; 
        }

    virtual void Procedure( CallbackInfo* info ) = 0;
    };

//============================================================================
//                            Callback Info
//============================================================================

class CallbackInfo 
    : public RefCount
{
    ASN::CSTAapdu* apdu;     // APDU this callback info originated from
    int type;                // callback info type

    void OnRefCountZero( void )
    {
        delete this;
        }
    
public:

    CallbackInfo( ASN::CSTAapdu* a, int t )
        : apdu( a )
        , type( t )
    {
        if ( t <= 0x1000 )
            TRACE( this << " CallbackInfo::CallbackInfo; " << ASN::EventIDType::EnumText( type ) );
        else
            TRACE( this << " CallbackInfo::CallbackInfo; type " << type );
        }

    virtual ~CallbackInfo( void )
    {
        TRACE( this << " CallbackInfo::~CallbackInfo" );
        if ( apdu && apdu->GetMemBlock () )
            delete apdu->GetMemBlock ();
        }

    int GetType( void ) const
        { return type; }
    };

//////////////////////////////////////////////////////////////////////////////

// Invoked EventReport service events

// call information events

struct CBI_CallCleared 
    : public CallbackInfo
{
    USTR clearedCall;
    LocalConnectionStateType localConnectionInfo;
    EventCauseType cause;
    USTR manufacturerOID;
    USTR privateData;

    CBI_CallCleared( ASN::CSTAapdu* a = NULL )
        : CallbackInfo( a, ASN::EventIDType::callCleared )
        , localConnectionInfo( lcs_unknown )
        , cause( ec_unknown )
    {
        }

    ~CBI_CallCleared ()
    {
        }
    };

struct CBI_Conferenced
    : public CallbackInfo
{
    USTR primaryOldCall;
    USTR secondaryOldCall;
    USTR confController;
    USTR addedParty;

    int conferenceConnectionsCount;
    USTR* conferenceConnections;

    LocalConnectionStateType localConnectionInfo;
    EventCauseType cause;
    USTR manufacturerOID;
    USTR privateData;

    CBI_Conferenced( ASN::CSTAapdu* a = NULL )
        : CallbackInfo( a, ASN::EventIDType::conferenced )
        , conferenceConnectionsCount( 0 )
        , conferenceConnections( NULL )
        , localConnectionInfo( lcs_unknown )
        , cause( ec_unknown )
    {
        }

    ~CBI_Conferenced ()
    {
        for ( int i = 0; i < conferenceConnectionsCount; i++ )
            conferenceConnections[ i ].SetNULL ();

        if ( conferenceConnections )
            delete[] conferenceConnections;
        }
    };

struct CBI_ConnectionCleared 
    : public CallbackInfo
{
    USTR droppedConnection;
    USTR releasingDevice;
    LocalConnectionStateType localConnectionInfo;
    EventCauseType cause;
    USTR manufacturerOID;
    USTR privateData;

    CBI_ConnectionCleared( ASN::CSTAapdu* a = NULL )
        : CallbackInfo( a, ASN::EventIDType::connectionCleared )
        , localConnectionInfo( lcs_unknown )
        , cause( ec_unknown )
    {
        }

    ~CBI_ConnectionCleared ()
    {
        }
    };

struct CBI_Delivered 
    : public CallbackInfo
{
    USTR connection;
    USTR alertingDevice;
    USTR callingDevice;
    USTR calledDevice;
    USTR lastRedirectionDevice;
    LocalConnectionStateType localConnectionInfo;
    EventCauseType cause;
    USTR manufacturerOID;
    USTR privateData;

    CBI_Delivered( ASN::CSTAapdu* a = NULL )
        : CallbackInfo( a, ASN::EventIDType::delivered )
        , localConnectionInfo( lcs_unknown )
        , cause( ec_unknown )
    {
        }

    ~CBI_Delivered ()
    {
        }
    };

struct CBI_Diverted 
    : public CallbackInfo
{
    USTR connection;
    USTR divertingDevice;
    USTR newDestination;
    LocalConnectionStateType localConnectionInfo;
    EventCauseType cause;
    USTR manufacturerOID;
    USTR privateData;

    CBI_Diverted( ASN::CSTAapdu* a = NULL )
        : CallbackInfo( a, ASN::EventIDType::diverted )
        , localConnectionInfo( lcs_unknown )
        , cause( ec_unknown )
    {
        }

    ~CBI_Diverted ()
    {
        }
    };

struct CBI_Established 
    : public CallbackInfo
{
    USTR establishedConnection;
    USTR answeringDevice;
    USTR callingDevice;
    USTR calledDevice;
    USTR lastRedirectionDevice;
    LocalConnectionStateType localConnectionInfo;
    EventCauseType cause;
    USTR manufacturerOID;
    USTR privateData;

    CBI_Established( ASN::CSTAapdu* a = NULL )
        : CallbackInfo( a, ASN::EventIDType::established )
        , localConnectionInfo( lcs_unknown )
        , cause( ec_unknown )
    {
        }

    ~CBI_Established ()
    {
        }
    };

struct CBI_Failed
    : public CallbackInfo
{
    USTR failedConnection;
    USTR failingDevice;
    USTR calledDevice;
    LocalConnectionStateType localConnectionInfo;
    EventCauseType cause;
    USTR manufacturerOID;
    USTR privateData;

    CBI_Failed( ASN::CSTAapdu* a = NULL )
        : CallbackInfo( a, ASN::EventIDType::failed )
        , localConnectionInfo( lcs_unknown )
        , cause( ec_unknown )
    {
        }

    ~CBI_Failed ()
    {
        }
    };

struct CBI_Held
    : public CallbackInfo
{
    USTR heldConnection;
    USTR holdingDevice;
    LocalConnectionStateType localConnectionInfo;
    EventCauseType cause;
    USTR manufacturerOID;
    USTR privateData;

    CBI_Held( ASN::CSTAapdu* a = NULL )
        : CallbackInfo( a, ASN::EventIDType::held )
        , localConnectionInfo( lcs_unknown )
        , cause( ec_unknown )
    {
        }

    ~CBI_Held ()
    {
        }
    };

struct CBI_NetworkReached
    : public CallbackInfo
{
    USTR connection;
    USTR trunkUsed;
    USTR calledDevice;
    LocalConnectionStateType localConnectionInfo;
    EventCauseType cause;
    USTR manufacturerOID;
    USTR privateData;

    CBI_NetworkReached( ASN::CSTAapdu* a = NULL )
        : CallbackInfo( a, ASN::EventIDType::networkReached )
        , localConnectionInfo( lcs_unknown )
        , cause( ec_unknown )
    {
        }

    ~CBI_NetworkReached ()
    {
        }
    };

struct CBI_Originated
    : public CallbackInfo
{
    USTR originatedConnection;
    USTR callingDevice;
    USTR calledDevice;
    LocalConnectionStateType localConnectionInfo;
    EventCauseType cause;
    USTR manufacturerOID;
    USTR privateData;

    CBI_Originated( ASN::CSTAapdu* a = NULL )
        : CallbackInfo( a, ASN::EventIDType::originated )
        , localConnectionInfo( lcs_unknown )
        , cause( ec_unknown )
    {
        }

    ~CBI_Originated ()
    {
        }
    };

struct CBI_Queued
    : public CallbackInfo
{
    USTR queuedConnection;
    USTR queue;
    USTR callingDevice;
    USTR calledDevice;
    USTR lastRedirectionDevice;
    int  numberedQueued;
    LocalConnectionStateType localConnectionInfo;
    EventCauseType cause;
    USTR manufacturerOID;
    USTR privateData;

    CBI_Queued( ASN::CSTAapdu* a = NULL )
        : CallbackInfo( a, ASN::EventIDType::queued )
        , localConnectionInfo( lcs_unknown )
        , cause( ec_unknown )
    {
        }

    ~CBI_Queued ()
    {
        }
    };

struct CBI_Retrieved
    : public CallbackInfo
{
    USTR retrievedConnection;
    USTR retrievingDevice;
    LocalConnectionStateType localConnectionInfo;
    EventCauseType cause;
    USTR manufacturerOID;
    USTR privateData;

    CBI_Retrieved( ASN::CSTAapdu* a = NULL )
        : CallbackInfo( a, ASN::EventIDType::retrieved )
        , localConnectionInfo( lcs_unknown )
        , cause( ec_unknown )
    {
        }

    ~CBI_Retrieved ()
    {
        }
    };

struct CBI_ServiceInitiated
    : public CallbackInfo
{
    USTR initiatedConnection;
    LocalConnectionStateType localConnectionInfo;
    EventCauseType cause;
    USTR manufacturerOID;
    USTR privateData;

    CBI_ServiceInitiated( ASN::CSTAapdu* a = NULL )
        : CallbackInfo( a, ASN::EventIDType::serviceInitiated )
        , localConnectionInfo( lcs_unknown )
        , cause( ec_unknown )
    {
        }

    ~CBI_ServiceInitiated ()
    {
        }
    };

struct CBI_Transferred
    : public CallbackInfo
{
    USTR primaryOldCall;
    USTR secondaryOldCall;
    USTR transferringDevice;
    USTR transferredDevice;

    int transferredConnectionsCount;
    USTR* transferredConnections;

    LocalConnectionStateType localConnectionInfo;
    EventCauseType cause;
    USTR manufacturerOID;
    USTR privateData;

    CBI_Transferred( ASN::CSTAapdu* a = NULL )
        : CallbackInfo( a, ASN::EventIDType::transferred )
        , transferredConnectionsCount( 0 )
        , transferredConnections( NULL )
        , localConnectionInfo( lcs_unknown )
        , cause( ec_unknown )
    {
        }

    ~CBI_Transferred ()
    {
        for ( int i = 0; i < transferredConnectionsCount; i++ )
            transferredConnections[ i ].SetNULL ();

        if ( transferredConnections )
            delete[] transferredConnections;
        }
    };

// feature events

struct CBI_CallInformation
    : public CallbackInfo
{
    USTR connection;
    USTR device;
    USTR accountInfo;
    USTR authorisationCode;
    USTR manufacturerOID;
    USTR privateData;

    CBI_CallInformation( ASN::CSTAapdu* a = NULL )
        : CallbackInfo( a, ASN::EventIDType::callInformation )
    {
        }

    ~CBI_CallInformation ()
    {
        }
    };

struct CBI_DoNotDisturb
    : public CallbackInfo
{
    USTR device;
    bool doNotDisturbFlag;
    USTR manufacturerOID;
    USTR privateData;

    CBI_DoNotDisturb( ASN::CSTAapdu* a = NULL )
        : CallbackInfo( a, ASN::EventIDType::doNotDisturb )
        , doNotDisturbFlag( false )
    {
        }

    ~CBI_DoNotDisturb ()
    {
        }
    };

struct CBI_Forwarding
    : public CallbackInfo
{
    USTR device;
    ::ForwardingType type;
    USTR forwardDN;
    USTR forwardedTo;
    USTR manufacturerOID;
    USTR privateData;

    CBI_Forwarding( ASN::CSTAapdu* a = NULL )
        : CallbackInfo( a, ASN::EventIDType::forwarding )
        , type( ft_unknown )
    {
        }

    ~CBI_Forwarding ()
    {
        }
    };

struct CBI_MessageWaiting
    : public CallbackInfo
{
    USTR deviceForMessage;
    USTR invokingDevice;
    bool messageWaitingFlag;
    USTR manufacturerOID;
    USTR privateData;

    CBI_MessageWaiting( ASN::CSTAapdu* a = NULL )
        : CallbackInfo( a, ASN::EventIDType::messageWaiting )
        , messageWaitingFlag( false )
    {
        }

    ~CBI_MessageWaiting ()
    {
        }
    };

// private events

struct CBI_PrivateEvent
    : public CallbackInfo
{
    USTR data;

    CBI_PrivateEvent( ASN::CSTAapdu* a = NULL )
        : CallbackInfo( a, ASN::EventIDType::privateEvt )
    {
        }

    ~CBI_PrivateEvent ()
    {
        }
    };

// agent state events

struct CBI_LoggedOn
    : public CallbackInfo
{
    USTR agentDevice;
    USTR agentID;
    USTR agentGroup;
    USTR agentPassword;
    USTR manufacturerOID;
    USTR privateData;

    CBI_LoggedOn( ASN::CSTAapdu* a = NULL )
        : CallbackInfo( a, ASN::EventIDType::loggedOn )
    {
        }

    ~CBI_LoggedOn ()
    {
        }
    };

struct CBI_LoggedOff
    : public CallbackInfo
{
    USTR agentDevice;
    USTR agentID;
    USTR agentGroup;
    USTR manufacturerOID;
    USTR privateData;

    CBI_LoggedOff( ASN::CSTAapdu* a = NULL )
        : CallbackInfo( a, ASN::EventIDType::loggedOff )
    {
        }

    ~CBI_LoggedOff ()
    {
        }
    };

struct CBI_NotReady
    : public CallbackInfo
{
    USTR agentDevice;
    USTR agentID;
    USTR manufacturerOID;
    USTR privateData;

    CBI_NotReady( ASN::CSTAapdu* a = NULL )
        : CallbackInfo( a, ASN::EventIDType::notReady )
    {
        }

    ~CBI_NotReady ()
    {
        }
    };

struct CBI_Ready
    : public CallbackInfo
{
    USTR agentDevice;
    USTR agentID;
    USTR manufacturerOID;
    USTR privateData;

    CBI_Ready( ASN::CSTAapdu* a = NULL )
        : CallbackInfo( a, ASN::EventIDType::ready )
    {
        }

    ~CBI_Ready ()
    {
        }
    };

struct CBI_WorkNotReady
    : public CallbackInfo
{
    USTR agentDevice;
    USTR agentID;
    USTR manufacturerOID;
    USTR privateData;

    CBI_WorkNotReady( ASN::CSTAapdu* a = NULL )
        : CallbackInfo( a, ASN::EventIDType::workNotReady )
    {
        }

    ~CBI_WorkNotReady ()
    {
        }
    };

struct CBI_WorkReady
    : public CallbackInfo
{
    USTR agentDevice;
    USTR agentID;
    USTR manufacturerOID;
    USTR privateData;

    CBI_WorkReady( ASN::CSTAapdu* a = NULL )
        : CallbackInfo( a, ASN::EventIDType::workReady )
    {
        }

    ~CBI_WorkReady ()
    {
        }
    };

// status events

struct CBI_OutOfService
    : public CallbackInfo
{
    USTR device;
    EventCauseType cause;
    USTR manufacturerOID;
    USTR privateData;

    CBI_OutOfService( ASN::CSTAapdu* a = NULL )
        : CallbackInfo( a, ASN::EventIDType::outOfService )
        , cause( ec_unknown )
    {
        }

    ~CBI_OutOfService ()
    {
        }
    };

struct CBI_BackInService
    : public CallbackInfo
{
    USTR device;
    EventCauseType cause;
    USTR manufacturerOID;
    USTR privateData;

    CBI_BackInService( ASN::CSTAapdu* a = NULL )
        : CallbackInfo( a, ASN::EventIDType::backInService )
        , cause( ec_unknown )
    {
        }

    ~CBI_BackInService ()
    {
        }
    };

// INVOKEd service events

struct CBI_SystemStatus
    : public CallbackInfo
{
    SystemStatusType status;
    USTR manufacturerOID;
    USTR privateData;

    CBI_SystemStatus( ASN::CSTAapdu* a = NULL )
        : CallbackInfo( a, 0x1001 )
        , status( ss_unknown )
    {
        }

    ~CBI_SystemStatus ()
    {
        }
    };

// Internally generated system Events

struct CBI_MonitorStarted
    : public CallbackInfo
{
    ErrorCode errCode;

    CBI_MonitorStarted( ASN::CSTAapdu* a = NULL )
        : CallbackInfo( a, 0x1002 )
        , errCode( CSTA_ERROR_CODE_NOT_SET )
    {
        }

    ~CBI_MonitorStarted ()
    {
        }
    };

struct CBI_RemoteDisconnected
    : public CallbackInfo
{
    CBI_RemoteDisconnected( ASN::CSTAapdu* a = NULL )
        : CallbackInfo( a, 0x1003 )
    {
        }

    ~CBI_RemoteDisconnected ()
    {
        }
    };
