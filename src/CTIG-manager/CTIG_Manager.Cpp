
#include "CSTA-Lib.h"

const int AVQTVc = 7; // population
const double AVQTVinit = 180; // 3 minutes default value

using namespace ASN;
using namespace MidCSTA;

struct GParams
{
    char    APPLINK[256];           // Application Link IP address
    char    DNIS_prefix[32];        // IVR prefix
    time_t  tOVERFLOW;              // max time in queue
    time_t  tREPEATED;              // time between repeated messages
    time_t  tDIVERTRETRY;           // minimum time between failed diversions

    char QUEUE_DN[16][32];          // list of ACD group DNs

    GParams ();
    };

GParams::GParams ()
{
    char* sect = "CTIG_Manager";
    char* szINI = "CallSrv.INI";

    GetPrivateProfileString(
        sect,                  // points to section name
        "AppLink",             // points to key name
        "localhost",           // points to default string
        APPLINK,               // points to destination buffer 
        sizeof( APPLINK ),     // size of destination buffer 
        szINI                  // points to initialization filename 
        );

    GetPrivateProfileString(
        sect,                  // points to section name
        "DNIS_prefix",         // points to key name
        "96",                  // points to default string
        DNIS_prefix,           // points to destination buffer 
        sizeof( DNIS_prefix ), // size of destination buffer 
        szINI                  // points to initialization filename 
        );

    tOVERFLOW = GetPrivateProfileInt(
        sect,           // points to section name 
        "tOverflow",     // points to key name
        3600,           // points to default int
        szINI       // points to initialization filename 
        );

    tREPEATED = GetPrivateProfileInt(
        sect,           // points to section name 
        "tRepeated",     // points to key name
        60,             // points to default int
        szINI       // points to initialization filename 
        );

    tDIVERTRETRY = GetPrivateProfileInt(
        sect,           // points to section name 
        "tDivertRetry",     // points to key name
        30,           // points to default int
        szINI       // points to initialization filename 
        );

    for ( int i = 0; i < 16; i++ )
    {
        char key[ 32 ];
        sprintf( key, "ACDQ_%d", i + 1 );

        GetPrivateProfileString(
            sect,                  // points to section name
            key,             // points to key name
            "",           // points to default string
            QUEUE_DN[i],               // points to destination buffer 
            sizeof( QUEUE_DN[i] ),     // size of destination buffer 
            szINI                  // points to initialization filename 
            );
        }
    }

GParams gParams;

///////////////////////////////////////////////////////////////////////////////
// CTIG_Manager Service definition
///////////////////////////////////////////////////////////////////////////////

class CTIG_Manager_Service : public SERVICE
{
    static void WINAPI Main( DWORD argc, LPTSTR  argv[] );
    static BOOL WINAPI ConsoleControlHandler( DWORD dwCtrlType );
    static VOID WINAPI ServiceControlHandler( DWORD fdwControl );

public:

    CTIG_Manager_Service ()
    : SERVICE
    (
        "CTIG_Manager",           // Service Name
        "CTI Group Manager",      // Service Display Name
        NULL,                     // Module Path
        Main                      // Service Main
        )
    {
        }
    };

static QCPortPool pool;
static CTIG_Manager_Service Service;

///////////////////////////////////////////////////////////////////////////////

class CTIG_CB_Proc;
class Queue;

class CallDataRecord
{
    friend class Queue;

    enum State
    {
        DELIVERED,
        QUEUED,
        DIVERTED
        };

    List<CallDataRecord>::Anchor<Queue> queue;

    State state;
    USTR connectionId;

    USTR A_number;
    USTR B_number;
    USTR C_number;

    time_t arrived_tstamp;
    int position_in_Q;
    int found_calls_in_Q; // how many calls there were in queue when the call were place in queue

    int divert2ivr_count;
    int divert2ivr_failedCount;
    time_t scheduled_to_ivr_tstamp;
    time_t scheduled_to_overflow;

    bool overflowed;

    CallDataRecord( Queue* q );
    ~CallDataRecord( void );

    void Dump( void );

    time_t GetElapsedTime() { return time( NULL ) - arrived_tstamp; }
    };

class Queue
{
    bool                      OK;

    List<CallDataRecord>      deliveredCalls;
    List<CallDataRecord>      queuedCalls;
    List<CallDataRecord>      watchdogCalls;
    USTR                      device_id;
    Ptr<CTIG_CB_Proc>         proc;
    Device*                   device;

    Mutex                     mutex;

    volatile int              arrivedTag;

    // Statistics
    int                       total_calls_dispatched;
    time_t                    lastTimeCallDispatched;
    int                       AVQTVp;
    double                    AVQTVsum; // Avarage Queueing Time Value
    double                    AVQTV[AVQTVc];

    static DWORD WINAPI Deflector_Thread( LPVOID thisQueue );
    static DWORD WINAPI Watchdog_Thread( LPVOID thisQueue );

public:

    Queue( void );
    ~Queue( void );

    void Initialize( System& sys, USTR pabx_id, USTR dev_id );

    bool IsOK( void ) const { return OK; }

    void Dump ();

    void OnDelivered( MidCSTA::CBI_Delivered* info );
    void OnQueued( MidCSTA::CBI_Queued* info );
    void OnDiverted( MidCSTA::CBI_Diverted* info );
    void OnConnectionCleared( MidCSTA::CBI_ConnectionCleared* info );

    void Stat_CallDispatched( CallDataRecord* cdr );

    double GetAVQTV() { return AVQTVsum / AVQTVc; }

    int GetBeforeInQueue( int position_in_Q )
    {
        int before_in_q = 0;

        for ( List<CallDataRecord>::Iterator i = watchdogCalls; i; i++ )
            if ( i->position_in_Q < position_in_Q )
                before_in_q++;

        for ( i = queuedCalls; i; i++ )
            if ( i->position_in_Q < position_in_Q )
                before_in_q++;

        return before_in_q;
        }
    };

///////////////////////////////////////////////////////////////////////////////

class CTIG_CB_Proc : public MidCSTA::CallbackProcedure 
{
    friend class Queue;

    class Queue* queue;

    void OnRefCountZero( void );
    void OnDeleteMonitor( void );

public:

    CTIG_CB_Proc( Queue* obj );
    ~CTIG_CB_Proc( void );

    void Procedure( MidCSTA::CallbackInfo* info );
    };

CTIG_CB_Proc::CTIG_CB_Proc( Queue* q )
    : CallbackProcedure()
    , queue( q )
{
    }

CTIG_CB_Proc:: ~CTIG_CB_Proc()
{
    }

void CTIG_CB_Proc::OnRefCountZero( void )
{
    delete this;
    }

void CTIG_CB_Proc::OnDeleteMonitor( void )
{
    }

void CTIG_CB_Proc::Procedure( MidCSTA::CallbackInfo* cbi )
{
    if ( ! queue ) return;

    TRACE( GetDev()->ID() );

    switch( cbi->GetType () )
    {
        case ASN::EventIDType::callCleared:
        {
            MidCSTA::CBI_CallCleared* info = (MidCSTA::CBI_CallCleared*)cbi;
            }
            break;

        case ASN::EventIDType::connectionCleared:
        {
            MidCSTA::CBI_ConnectionCleared* info = (MidCSTA::CBI_ConnectionCleared*)cbi;

            queue->OnConnectionCleared( info );
            }
            break;

        case ASN::EventIDType::delivered:
        {
            MidCSTA::CBI_Delivered* info = (MidCSTA::CBI_Delivered*)cbi;

            queue->OnDelivered( info );
            }
            break;

        case ASN::EventIDType::diverted:
        {
            MidCSTA::CBI_Diverted* info = (MidCSTA::CBI_Diverted*)cbi;

            queue->OnDiverted( info );
            }
            break;

        case ASN::EventIDType::established:
        {
            MidCSTA::CBI_Established* info = (MidCSTA::CBI_Established*)cbi;
            }
            break;

        case ASN::EventIDType::failed:
        {
            MidCSTA::CBI_Failed* info = (MidCSTA::CBI_Failed*)cbi;
            }
            break;

        case ASN::EventIDType::queued:
        {
            MidCSTA::CBI_Queued* info = (MidCSTA::CBI_Queued*)cbi;

            queue->OnQueued( info );
            }
            break;

        case ASN::EventIDType::outOfService:
        {
            MidCSTA::CBI_OutOfService* info = (MidCSTA::CBI_OutOfService*)cbi;
            }
            break;

        case ASN::EventIDType::backInService:
        {
            MidCSTA::CBI_BackInService* info = (MidCSTA::CBI_BackInService*)cbi;
            }
            break;
        }
    }

///////////////////////////////////////////////////////////////////////////////

Queue::Queue( void )
{
    OK = false;

    arrivedTag = 0;
    total_calls_dispatched = 0;
    lastTimeCallDispatched = 0;

    AVQTVsum = 0;
    AVQTVp = 0;

    for ( int i = 0; i < AVQTVc; i++ )
        AVQTVsum += ( AVQTV[ i ] = AVQTVinit );
    }

Queue::~Queue( void )
{
    // Remove all Call Data Records
    //
    mutex.Lock ();

    for ( List<CallDataRecord>::Iterator i = deliveredCalls; i; i++ )
        delete i.GetElement ();

    for ( i = queuedCalls; i; i++ )
        delete i.GetElement ();

    for ( i = watchdogCalls; i; i++ )
        delete i.GetElement ();

    mutex.Unlock ();
    }

void Queue::Initialize( System& sys, USTR pabx_id, USTR dev_id )
{
    device_id = dev_id;

    proc = new CTIG_CB_Proc( this );

    ErrorCode ec = sys.OpenDevice( proc, pabx_id, dev_id );

    if ( ec != CTNG_NO_ERROR )
        return;

    device = proc->GetDev ();

    // Start deflector thread
    //
    HANDLE
    hThreadHandle = ::CreateThread
    (
        NULL,                          // pointer to thread security attributes  
        0,                             // initial thread stack size, in bytes 
        Deflector_Thread,              // pointer to thread function 
        this,                          // argument for new thread 
        0,                             // creation flags 
        NULL                           // pointer to returned thread identifier 
        );
    ::CloseHandle( hThreadHandle );

    // Start watchdog thread
    //
    hThreadHandle = ::CreateThread
    (
        NULL,                          // pointer to thread security attributes  
        0,                             // initial thread stack size, in bytes 
        Watchdog_Thread,               // pointer to thread function 
        this,                          // argument for new thread 
        0,                             // creation flags 
        NULL                           // pointer to returned thread identifier 
        );
    ::CloseHandle( hThreadHandle );

    OK = true;
    }

void Queue:: OnDelivered( MidCSTA::CBI_Delivered* info )
{
    mutex.Lock ();

    LOG ( DBG_TRACE ) << info->connection << ": OnDelivered; -------------- Event" << eline;

    // find out if there is CDR with the same connection id in watchdogList

    CallDataRecord* cdr = NULL;
    for( List<CallDataRecord>::Iterator i = watchdogCalls; i; i++ )
    {
        if ( i->connectionId == info->connection )
        {
            cdr = i.GetElement ();
            break;
            }
        }

    if ( cdr )
    {
        // if there is CDR connection in watchdogList, it is probably call comming
        // back from IVR, so we should reuse it

        cdr->queue.Unlink ();

        cdr->state = CallDataRecord::DELIVERED;
        cdr->queue.LinkAsLast( deliveredCalls );

        LOG( DBG_TRACE ) << cdr->connectionId << ": OnDelivered: Reused CDR from watchdog list." << eline;
        }
    else
    {
        // if we didn't find CDR in watchdogList, then it is new connection, and we
        // should create CDR for it
        cdr = new CallDataRecord( this );

        cdr->state = CallDataRecord::DELIVERED;
        cdr->connectionId = info->connection;

        cdr->arrived_tstamp = time( NULL );
        cdr->position_in_Q = arrivedTag++;
        cdr->found_calls_in_Q = 1 + queuedCalls.GetCount() + watchdogCalls.GetCount();

        cdr->B_number = info->calledDevice;
        cdr->A_number = info->callingDevice;
        cdr->C_number = info->alertingDevice;

        cdr->divert2ivr_count = 0;
        cdr->divert2ivr_failedCount = 0;
        cdr->scheduled_to_ivr_tstamp = time(NULL) + 3600;
        cdr->scheduled_to_overflow = time(NULL) + 3600;
        cdr->overflowed = false;

        cdr->queue.LinkAsLast( deliveredCalls );

        LOG( DBG_TRACE ) << cdr->connectionId << ": OnDelivered: Created CDR." << eline;
        }

    mutex.Unlock ();
    }

void Queue:: OnQueued( MidCSTA::CBI_Queued* info )
{
    mutex.Lock ();

    LOG ( DBG_TRACE ) << info->queuedConnection << ": OnQueued; -------------- Event" << eline;

    // Search for the call in deliveredList; if there is no call in delivered list
    // then make a warning.
    //
    CallDataRecord* cdr = NULL;
    for( List<CallDataRecord>::Iterator i = deliveredCalls; i; i++ )
    {
        if ( i->connectionId == info->queuedConnection )
        {
            cdr = i.GetElement ();
            break;
            }
        LOG(DBG_TRACE) << "Not equal " << i->connectionId << " and " << info->queuedConnection << eline;
        }

    if ( cdr )
    {
        LOG( DBG_TRACE ) << cdr->connectionId << ": OnQueued: Found in delivered list" << eline;
        // continue and put call back into Queued list
        }
    else
    {
        // The call is not in Delivered list. Check wether is it in Watchdog list.

        for ( i = watchdogCalls; i; i++ )
        {
            if ( i->connectionId == info->queuedConnection )
            {
                cdr = i.GetElement ();
                break;
                }
            }

        if ( cdr )
        {
            LOG( DBG_TRACE ) << cdr->connectionId << ": OnQueued: Found in watchdog list" << eline;
            // continue and put call back into Queued list
            }
        else
        {
            // Not found either in Delivered nor in Watchdog list. Check wether is it in Queued list.

            for ( i = queuedCalls; i; i++ )
            {
                if ( i->connectionId == info->queuedConnection )
                {
                    cdr = i.GetElement ();
                    break;
                    }
                }

            mutex.Unlock ();

            // Queued call not found in either of Delivered, Watchdog or Queued list!
            //
            if ( ! cdr )
            {
                LOG( DBG_WARN ) << info->queuedConnection
                    << ": OnQueued: Received Queued event without previous Delivered event!"
                    << eline;
                }
            else
            {
                LOG( DBG_WARN ) << info->queuedConnection
                    << ": OnQueued: Probably failed Divert request; failure count = "
                    << cdr->divert2ivr_failedCount
                    << eline;
                }

            return;
            }
        }

    cdr->state = CallDataRecord::QUEUED;

    cdr->queue.Unlink ();

    bool inserted = false;
    for ( i = queuedCalls; i; i++ )
    {
        if ( cdr->position_in_Q < i->position_in_Q )
        {
            inserted = true;
            cdr->queue.LinkBefore( *i.GetAnchor () );
            break;
            }
        }
    if ( ! inserted )
    {
        cdr->queue.LinkAsLast( queuedCalls );
        }

    if ( cdr->divert2ivr_count == 0 )
    {
        cdr->scheduled_to_ivr_tstamp = time( NULL ) - 1; // delfect immediate
        cdr->scheduled_to_overflow = time( NULL ) + gParams.tOVERFLOW;
        }
    else
    {
        cdr->scheduled_to_ivr_tstamp = time( NULL ) + gParams.tREPEATED;
        }

    LOG( DBG_TRACE ) << cdr->connectionId << ": OnQueued: Put into queued list." << eline;

    mutex.Unlock ();
    }

void Queue:: OnDiverted( MidCSTA::CBI_Diverted* info )
{
    mutex.Lock ();

    LOG ( DBG_TRACE ) << info->connection << ": OnDiverted; -------------- Event" << eline;

    // find out call in delivered list; if there is a call in delivered list,
    // than this means that it is going directly to an agent, so we destroy call
    //
    CallDataRecord* cdr = NULL;
    for( List<CallDataRecord>::Iterator i = deliveredCalls; i; i++ )
    {
        if ( i->connectionId == info->connection )
        {
            cdr = i.GetElement ();
            break;
            }
        }

    if ( cdr )
    {
        LOG( DBG_TRACE ) << cdr->connectionId << ": OnDiverted: Found in delivered list; to Agent: "
            << info->newDestination << eline;

        Stat_CallDispatched( cdr ); // update Queue statistics

        cdr->queue.Unlink ();
        delete cdr;
        mutex.Unlock ();
        return;
        }

    // if there is no call with the same id in delivered list, then search queued list.
    // if the call exists then depending on destination, check if the call is going to
    // be destroyed (it came to an agent) or put in watchdog list (it came to ivr)
    //
    for( i = queuedCalls; i; i++ )
    {
        if ( i->connectionId == info->connection )
        {
            cdr = i.GetElement ();
            break;
            }
        }

    if ( cdr )
    {
        const char* d = info->newDestination;

        if ( info->newDestination.Len () >= 3 && strncmp( d, gParams.DNIS_prefix, strlen( gParams.DNIS_prefix ) ) == 0 )
        {
            if ( cdr->overflowed )
            {
                LOG( DBG_TRACE ) << cdr->connectionId << ": OnDiverted: Found in delivered list; to IVR: "
                    << info->newDestination << eline;

                cdr->queue.Unlink ();
                delete cdr;
                }
            else
            {
                LOG( DBG_TRACE ) << cdr->connectionId << ": OnDiverted: Found in delivered list; w/MQPOS to IVR: "
                    << info->newDestination << eline;

                cdr->queue.Unlink ();

                cdr->divert2ivr_count++;
                cdr->state = CallDataRecord::DIVERTED;
                cdr->queue.LinkAsLast( watchdogCalls );
                }
            }
        else
        {
            LOG( DBG_TRACE ) << cdr->connectionId << ": OnDiverted: Found in queued list; to Agent: "
                << info->newDestination << eline;

            Stat_CallDispatched( cdr ); // update Queue statistics

            cdr->queue.Unlink ();
            delete cdr;
            }
        }

    mutex.Unlock ();
    }

void Queue:: OnConnectionCleared( MidCSTA::CBI_ConnectionCleared* info )
{
    mutex.Lock ();

    LOG ( DBG_TRACE ) << info->droppedConnection << ": OnConnectionCleared; -------------- Event" << eline;

    // find out call in delivered list; if there is a call in delivered list,
    // than this means that it is going directly to an agent, so we destroy call
    //
    CallDataRecord* cdr = NULL;
    for( List<CallDataRecord>::Iterator i = deliveredCalls; i; i++ )
    {
        if ( i->connectionId == info->droppedConnection )
        {
            cdr = i.GetElement ();
            break;
            }
        }

    if ( cdr )
    {
        LOG( DBG_TRACE ) << cdr->connectionId << ": OnCleared: Found in delivered list; Cleared." << eline;

        cdr->queue.Unlink ();
        delete cdr;
        mutex.Unlock ();
        return;
        }

    // if there is no call with the same id in delivered list, then search queued list.
    // if the call exists then depending on destination, check if the call is going to
    // be destroyed (it came to an agent) or put in watchdog list (it came to ivr)
    //
    for( i = queuedCalls; i; i++ )
    {
        if ( i->connectionId == info->droppedConnection )
        {
            cdr = i.GetElement ();
            break;
            }
        }

    if ( cdr )
    {
        LOG( DBG_TRACE ) << cdr->connectionId << ": OnCleared: Found in queued list; Cleared." << eline;

        cdr->queue.Unlink ();
        delete cdr;
        }
    else
    {
        // find out if there is CDR with the same connection id in watchdogList
        //
        for( i = watchdogCalls; i; i++ )
        {
            if ( i->connectionId == info->droppedConnection )
            {
                cdr = i.GetElement ();
                break;
                }
            }

        if ( cdr )
        {
            LOG( DBG_TRACE ) << cdr->connectionId << ": OnCleared: Found in watchdog list; Cleared." << eline;

            cdr->queue.Unlink ();
            delete cdr;
            }
        }

    mutex.Unlock ();
    }

DWORD WINAPI Queue::Deflector_Thread( LPVOID thisQueue )
{
    Sleep( 1000 );

    Queue* queue = (Queue*)thisQueue;

    LOG( DBG_TRACE ) << "Queue " << queue->device_id << ": Deflector thread started" << eline;

    for ( ;; )
    {
        time_t now = time( NULL );

        queue->mutex.Lock ();

        // find a first call scheduled for deflection
        //
        CallDataRecord* cdr = NULL;

        for ( List<CallDataRecord>::Iterator i = queue->queuedCalls; i; i++ )
        {
            if ( i->scheduled_to_ivr_tstamp <= now
                || i->scheduled_to_overflow <= now )
            {
                cdr = i.GetElement ();
                break;
                }
            }

        USTR connId;
        MidCSTA::connectionIdType conn_id;

        int pos_in_q = 0;

        if ( cdr )
        {
            connId = cdr->connectionId;
            conn_id = connId;

            pos_in_q = 1 + queue->GetBeforeInQueue( cdr->position_in_Q );
            }

        queue->mutex.Unlock (); // unlock list structures; we have conn_id of the call, now

        if ( cdr )
        {
            bool fOverflow = cdr->scheduled_to_overflow <= now;

            double ewt = queue->GetAVQTV() * pos_in_q / 60;

            if ( ewt <= 1 )
                ewt = 1;
            else if ( ewt >= 99 )
                ewt = 99;

            LOG( DBG_TRACE ) << "------- AVQTV = " << queue->GetAVQTV ()
                << ", Queue Pos = " << pos_in_q
                << ", EQT = " << ewt
                << eline;

            char dest[128];
            sprintf( dest, "%s%01d%02d%03.0lf",
                gParams.DNIS_prefix,
                fOverflow ? 0 : cdr->divert2ivr_count > 8 ? 9 : cdr->divert2ivr_count + 1,
                pos_in_q,
                ewt
                );

            if ( fOverflow )
            {
                cdr->overflowed = true;

                // Divert call to IVR

                LOG( DBG_TRACE ) << connId << ": Deflector: Deflect to " << dest << eline;

                ErrorCode ec = queue->device->DivertCall_Deflect( conn_id, USTR( dest ), NULL );

                // in case of failure retry after some time
                cdr->scheduled_to_overflow = time( NULL ) + gParams.tDIVERTRETRY;
                cdr->scheduled_to_ivr_tstamp = time( NULL ) + gParams.tDIVERTRETRY + 10;

                if ( ec != CTNG_NO_ERROR )
                    cdr->divert2ivr_failedCount++;
                }
            else
            {
                // Divert call to IVR and maintain queue position
                static const unsigned char DATA[1] = { 0x01 };

                static const unsigned char OID[7] = { 0x2B, 0x0C, 0x02, 0x89, 0x3D, 0x15, 0x0B };
                CSTA_Extensions ext;
                ext.outData = USTR( DATA, sizeof( DATA ) );
                ext.outOID = USTR( OID, sizeof( OID ) );

                LOG( DBG_TRACE ) << connId << ": Deflector: Deflect w/MQPOS to " << dest << eline;

                ErrorCode ec = queue->device->DivertCall_Deflect( conn_id, USTR( dest ), &ext );

                // in case of failure retry after some time
                cdr->scheduled_to_ivr_tstamp = time( NULL ) + gParams.tDIVERTRETRY;

                if ( ec != CTNG_NO_ERROR )
                    cdr->divert2ivr_failedCount++;
                else
                {
                    // Call is successfully diverted to IVR with maintaining queue position.
                    // 
                    queue->mutex.Lock ();

                    cdr->queue.Unlink ();

                    cdr->divert2ivr_count++;
                    cdr->state = CallDataRecord::DIVERTED;
                    cdr->queue.LinkAsLast( queue->watchdogCalls );

                    queue->mutex.Unlock ();
                    }
                }
/*
            if ( CTNG_NO_ERROR != ec )
            {
                // remove call from the queue

                queue->mutex.Lock ();

                for ( List<CallDataRecord>::Iterator i = queue->queuedCalls; i; i++ )
                {
                    if ( i->connectionId == connId )
                    {
                        cdr->queue.Unlink ();
                        delete cdr;
                        break;
                        }
                    }

                queue->mutex.Unlock ();
                }
*/
            }

        Sleep( 1200 );
        }

    return 0;
    }

DWORD WINAPI Queue::Watchdog_Thread( LPVOID thisQueue )
{
    Sleep( 3000 );

    Queue* queue = (Queue*)thisQueue;

    LOG( DBG_TRACE ) << "Queue " << queue->device_id << ": Watchdog thread started" << eline;

    for ( ;; )
    {
        queue->mutex.Lock ();

        // scan all calls to see if they are too long sitting on IVR
        //
        CallDataRecord* cdr = NULL;
        for ( List<CallDataRecord>::Iterator i = queue->watchdogCalls; i; i++ )
        {
            if ( time( NULL ) >= i->scheduled_to_ivr_tstamp + 360 ) // more then 360 seconds on IVR
            {
                // remove call
                LOG( DBG_TRACE ) << i->connectionId << ": Watchdog: Call purged." << eline;
                delete i.GetElement ();
                }
            }

        queue->mutex.Unlock (); // unlock list structures; we have conn_id of the call, now

        Sleep( 1000 );
        }

    return 0;
    }

void Queue::Stat_CallDispatched( CallDataRecord* cdr )
{
    mutex.Lock ();

    total_calls_dispatched ++;
/*
    double avq = cdr->GetElapsedTime () / cdr->found_calls_in_Q;

    for ( List<CallDataRecord>::Iterator i = watchdogCalls; i; i++ )
        avq += double( i->GetElapsedTime() ) / double( i->found_calls_in_Q );

    for ( i = queuedCalls; i; i++ )
        avq += double( i->GetElapsedTime() ) / double( i->found_calls_in_Q );
*/
/*
    double avq = cdr->GetElapsedTime ();
*/

    time_t tNow = time( NULL );

    double qtv = tNow - lastTimeCallDispatched; // queueing time value

    if ( qtv > 100*60 ) // above 100 mintues between dispatched calls
        qtv = cdr->GetElapsedTime (); // qtv is last call elapsed time

    lastTimeCallDispatched = tNow;

    AVQTVsum -= AVQTV[ AVQTVp ];
    AVQTV[ AVQTVp ]  = qtv;
    AVQTVsum += qtv;
    AVQTVp = ( AVQTVp + 1 ) % AVQTVc;

    LOG( DBG_TRACE ) << "----- AVQTV Updated: QTV = "
        << qtv << ", New AVQTV = " << AVQTVsum / AVQTVc << eline;

    mutex.Unlock ();
    }

void Queue:: Dump ()
{
    return;

    mutex.Lock ();

    LOG( DBG_TRACE, FALSE )
        << "---------------------------------------------------------------" << eline
        << "    Queue: " << device_id << eline
        << "    Total dispatched calls: " << total_calls_dispatched << eline
        << "    Calls waiting in queue: " << queuedCalls.GetCount () << eline
        << "    Calls waiting in ivr: " << watchdogCalls.GetCount () << eline
        << "    AVQTV: " << AVQTVsum / AVQTVc << " /";

    for ( int i = 0; i < AVQTVc; i++ )
        LOG( DBG_TRACE, FALSE ) << " " << AVQTV[ i ];

    LOG( DBG_TRACE, FALSE ) << eline;

    if ( deliveredCalls.GetCount () > 0 )
    {
        LOG( DBG_TRACE, FALSE ) << "------------------------------------------- delivered" << eline;
        for ( List<CallDataRecord>::Iterator i = deliveredCalls; i; i++ )
            i->Dump ();
        }

    if ( queuedCalls.GetCount () > 0 )
    {
        LOG( DBG_TRACE, FALSE ) << "------------------------------------------- queued" << eline;
        for ( List<CallDataRecord>::Iterator i = queuedCalls; i; i++ )
            i->Dump ();
        }

    if ( watchdogCalls.GetCount () > 0 )
    {
        LOG( DBG_TRACE, FALSE ) << "------------------------------------------- watchdog" << eline;
        for ( List<CallDataRecord>::Iterator i = watchdogCalls; i; i++ )
            i->Dump ();
        }

    mutex.Unlock ();
    }

CallDataRecord:: CallDataRecord( Queue* q )
{
    queue.Initialize( this, q );

    state = DELIVERED;
    arrived_tstamp = 0;
    position_in_Q = 0;

    divert2ivr_count = 0;
    divert2ivr_failedCount = 0;
    scheduled_to_ivr_tstamp = 0;
    scheduled_to_overflow = 0;
    }

CallDataRecord:: ~CallDataRecord( void )
{
    LOG( DBG_TRACE ) << connectionId << ": Destructed CDR." << eline;
    }

void CallDataRecord:: Dump( void )
{
    int pos_in_q = 1 + queue->GetBeforeInQueue( position_in_Q );

    LOG( DBG_TRACE, FALSE )
        << "ID: " << position_in_Q << "-" << connectionId
        << ", pos: " << pos_in_q
        << ", arrived: " << (const char*)aTime( arrived_tstamp )
        << ", state: " << state << eline
        << "    A: " << A_number
        << ", B: " << B_number
        << ", C: " << C_number << eline
        << "    elapsed: " << GetElapsedTime ()
        << ", EWT: " << pos_in_q * queue->GetAVQTV() / 60.0
        << ", divCnt: " << divert2ivr_count
        << ", sched: " << (const char*)aTime( scheduled_to_ivr_tstamp )
        << eline;
    }

//////////////////////////////////////////////////////////////////////////////

//  Function:   ServiceControlHandler
//
//  Synopsis:   Handles requests from the service controller.
//
//  Arguments:  [fdwControl] -- Request code
//
VOID WINAPI
CTIG_Manager_Service:: ServiceControlHandler
(
    DWORD fdwControl
    )
{
    switch ( fdwControl )
    {
        case SERVICE_CONTROL_SHUTDOWN:
        case SERVICE_CONTROL_STOP:

            Service.UpdateStatus( SERVICE_STOP_PENDING, 25000L ); // expected stop in 25 seconds

            LOG( DBG_WARN ) << "Termination request: SCM control stop." << eline;
            Service.SetTerminating ();
            pool.SignalTerminate ();
            return;

        case SERVICE_CONTROL_INTERROGATE:

            Service.UpdateStatusInterrogate ();
            return;

        default:
            return;
        }
    }

//  Function: ConsoleControlHandler
//
//  Synopsis: Handled console control events
//      makes service to terminate.
//
//  Arguments:
//      dwCtrlType - type of control event
//
//  Return Value:
//    TRUE if handled, FALSE if unhandled
//
BOOL WINAPI 
CTIG_Manager_Service:: ConsoleControlHandler
(
    DWORD dwCtrlType 
    )
{
    switch ( dwCtrlType )
    {
        case CTRL_BREAK_EVENT:
        case CTRL_C_EVENT:
        case CTRL_CLOSE_EVENT:
        case CTRL_LOGOFF_EVENT:
        case CTRL_SHUTDOWN_EVENT:

            LOG( DBG_WARN ) << "Termination request: console control event." << eline;
            Service.SetTerminating ();
            pool.SignalTerminate ();

            return TRUE;
        }

    return FALSE;
    }

void WINAPI
CTIG_Manager_Service:: Main
(
    DWORD   argc,       // arguments passed to main
    LPTSTR  argv []
    )
{
    // Set current directory to path where this module is found
    // (not started from)
    //
    {
        char ModuleDir[ 512 ];
        strcpy( ModuleDir, Service.ModulePath () );
        char* chp = ModuleDir + strlen( ModuleDir ) - 1;
        for ( ; chp >= ModuleDir; chp-- )
        {
            if ( *chp == '\\' )
            {
                *chp = '\0';
                break;
                }
            }

        if ( ! SetCurrentDirectory( ModuleDir ) )
        {
            LOG( DBG_ERROR )
                << "Cannot set current directory: " << ModuleDir << eline;
            }
        else
        {
            LOG( DBG_TRACE )
                << "Service default directory set to: " << ModuleDir << eline;
            }
        }

    if ( ! SetPriorityClass( GetCurrentProcess (), HIGH_PRIORITY_CLASS ) )
    {
        DebugRC( GetLastError () );
        LOG( DBG_ERROR )
            << "-> SetPriorityClass HIGH failed."
            << eline;
        }

    if ( ! Service.IsService () )
    {
        ::SetConsoleCtrlHandler( ConsoleControlHandler, TRUE );
        }

    if ( ! Service.NotifyController( ServiceControlHandler ) )
    {
        LOG( DBG_ERROR )
            << "Could not contact service controller."
            << eline;
        return;
        }

    Service.UpdateStatus( SERVICE_START_PENDING );

    // LOG file setup
    //
    {
        HANDLE hLogFile = CreateFile(
             "CTIG_Manager.log", // pointer to name of the file 
             GENERIC_WRITE,    // access (read-write) mode 
             FILE_SHARE_READ,  // share mode 
             NULL,             // pointer to security descriptor, NULL means default
             OPEN_ALWAYS,      // how to create 
             FILE_ATTRIBUTE_NORMAL, // file attributes 
             NULL              // handle to file with attributes to copy
             );

        if ( hLogFile != INVALID_HANDLE_VALUE )
        {
            //
            // seek end of log file
            //
            DWORD rc = SetFilePointer(
                hLogFile,   // handle of file 
                0L,         // number of bytes to move file pointer 
                NULL,       // address of high-order word of distance to move  
                FILE_END    // how to move 
                );

            LOG::UseHandle( hLogFile );

            if ( GetStdHandle( STD_OUTPUT_HANDLE ) == NULL )
            {
                if ( ! SetStdHandle( STD_OUTPUT_HANDLE, hLogFile ) )
                {
                    DebugRC( GetLastError () );
                    LOG( DBG_ERROR ) << "-> Set standard output handle." << eline;
                    }

                if ( ! SetStdHandle( STD_ERROR_HANDLE, hLogFile ) )
                {
                    DebugRC( GetLastError () );
                    LOG( DBG_ERROR ) << "-> Set standard error handle." << eline;
                    }
                }
            }
        }

    LOG( DBG_WARN )
        << "Starting [" << Service.FullName ()
        << "] Release [" << __DATE__ << " " << __TIME__ << "]"
        << eline;

    Service.UpdateStatus( SERVICE_START_PENDING );

    System cstaSys;
    cstaSys.Initialize ();

    cstaSys.AddPABX( USTR( "md110" ), gParams.APPLINK, 2555 );

    Service.UpdateStatus( SERVICE_RUNNING );

    //////////////////////////////////////////////////////////////////////////
    // Running...

    LOG( DBG_WARN ) << "Running." << eline;

    {
        Queue q[ 16 ];

        for ( int i = 0; i < 16; i++ )
        {
            if ( gParams.QUEUE_DN[ i ][ 0 ] != '\0' )
            {
                q[ i ].Initialize( cstaSys, "md110", gParams.QUEUE_DN[ i ] );
                }
            }

        while( ! Service.IsTerminating () )
        {
            if ( ! Service.IsService () )
            {
                for ( int i = 0; i < 16; i++ )
                    if( q[ i ].IsOK () )
                        q[ i ].Dump ();
                }

            Sleep( 1000 );
            }
        }

    //////////////////////////////////////////////////////////////////////////
    // We are stopped...
    //
    LOG( DBG_WARN )
        << "Stopped " << Service.Name () << " service."
        << eline;

    Service.UpdateStatus( SERVICE_STOPPED );
    }

void main
(
    int argc,
    char* argv []
    )
{
    //
    // Parse the arguments
    //
    if ( argc > 1 )
    {
        char* arg = argv[ 1 ];

        LOG::UseHandle( GetStdHandle( STD_OUTPUT_HANDLE ) );

        if ( stricmp( arg, "-install" ) == 0 )
        {
            Service.Install ();
            return;
            }

        if ( stricmp( arg, "-remove" ) == 0 )
        {
            Service.Remove ();
            return;
            }

        if ( stricmp( arg, "-start" ) == 0 )
        {
            Service.Start ();
            return;
            }

        if ( stricmp( arg, "-stop" ) == 0 )
        {
            Service.Stop ();
            return;
            }

        if ( stricmp( arg, "-status" ) == 0 )
        {
            Service.DebugStatus ();
            return;
            }

        if ( stricmp( arg, "-noservice" ) == 0 || strcmp( arg, "-" ) == 0 )
        {
            Service.SetNotService ();
            }
        }

    Service.Dispatch ();
    }
