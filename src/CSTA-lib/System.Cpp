/*
    Project: CSTALib

    Module: System.Cpp

    Description: System object

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "CSTA-Lib.h"

#include <process.h> // _beginthreadex()

using namespace ASN;
using namespace CTsvcLIB;

/////////////////////////////////////////////////////////////////////////////
namespace MidCSTA
{

///////////////////////////////////////////////////////////////////////////////
// System class implementation; static members

volatile bool System:: hasConsole = false;

void System:: OpenLogFile( const char* filename )
{
    // LOG file setup
    //
    HANDLE hLogFile = ::CreateFile(
         filename,          // pointer to name of the file 
         GENERIC_WRITE,    // access (read-write) mode 
         FILE_SHARE_READ,  // share mode 
         NULL,             // pointer to security descriptor, NULL means default
         OPEN_ALWAYS,      // how to create 
         FILE_ATTRIBUTE_NORMAL, // file attributes 
         NULL              // handle to file with attributes to copy
         );

    if ( hLogFile == INVALID_HANDLE_VALUE )
        return;

    //
    // seek end of log file
    //
    DWORD rc = ::SetFilePointer(
        hLogFile,   // handle of file 
        0L,         // number of bytes to move file pointer 
        NULL,       // address of high-order word of distance to move  
        FILE_END    // how to move 
        );

    LOG::UseHandle( hLogFile );

    if ( ::GetStdHandle( STD_OUTPUT_HANDLE ) == NULL )
    {
        if ( ! ::SetStdHandle( STD_OUTPUT_HANDLE, hLogFile ) )
        {
            DebugRC( GetLastError () );
            LOG( DBG_ERROR ) << "-> Set standard output handle." << eline;
            }

        if ( ! ::SetStdHandle( STD_ERROR_HANDLE, hLogFile ) )
        {
            DebugRC( GetLastError () );
            LOG( DBG_ERROR ) << "-> Set standard error handle." << eline;
            }
        }

    LOG( DBG_WARN ) << eline << eline
        << "        ----------------------------------------------------" << eline
        << "        ----------------- (LogFile) I live! ----------------" << eline
        << "        ----------------------------------------------------" << eline
        << eline;
    }

void System:: OpenConsole( void )
{
    if ( hasConsole )
        return;

    if ( ! ::AllocConsole () )
        return;

    hasConsole = true;

    LOG::UseHandle( ::GetStdHandle( STD_OUTPUT_HANDLE ) );

    LOG( DBG_WARN ) << eline << eline
        << "        ----------------------------------------------------" << eline
        << "        ----------------- (Console) I live! ----------------" << eline
        << "        ----------------------------------------------------" << eline
        << eline;
    }

void System:: CloseConsole( void )
{
    if ( ! hasConsole )
        return;

    LOG::ReleaseHandle( ::GetStdHandle( STD_OUTPUT_HANDLE ) );

    ::FreeConsole ();

    hasConsole = false;
    }

///////////////////////////////////////////////////////////////////////////////
// System class implementation

System:: System( void )
    : hCompletionPort( NULL )
    , isTerminating( false )
    , qioDispatcherThreadCount( 0 )
    , watchdogThreadCount( 0 )
    , gcThreadCount( 0 )
    , simultaneousQIO( 0 )
    , maxSimultaneousQIO( 0 )
    , tot_dev_constructed( 0 )
    , tot_dev_destructed( 0 )
    , inboundMemPool( "Inbound CSTA APDU" )
    , outboundMemPool( "Outbound CSTA APDU" )
{
    }

System:: ~System( void )
{
    }

void System:: Initialize( int cDispatchers, int cGC, int cWatchdog )
{
    TRACE( this << " System::Initialize" );

    isTerminating = false;
    qioDispatcherThreadCount = 0;
    watchdogThreadCount = 0;
    gcThreadCount = 0;
    simultaneousQIO = 0;
    maxSimultaneousQIO = 0;

    tot_dev_constructed = 0;
    tot_dev_destructed = 0;

    sema_gc_devices.Create( 0, 10000 );
    sema_watchdog.Create( 0, 10000 );

    // Confirm that the WinSock DLL supports VER = wVersionRequested
    // Note that if the DLL supports versions greater
    // than VER in addition to VER, it will still return
    // VER in wVersion since that is the version we
    // requested.
    //
    WORD wVersionRequested = MAKEWORD( 2, 0 ); // version 2.0

    if ( SOCKET_ERROR == ::WSAStartup( wVersionRequested, &wsaData ) )
    {
        DebugRC( ::WSAGetLastError () );
        LOG( DBG_ERROR ) << this << " System:: Initialize: -> WSAStartup failed" << eline;
        return;
        }

    // Determine how many processors are on the system.
    //
    SYSTEM_INFO systemInfo;
    ::GetSystemInfo( &systemInfo );

    // Create the completion port that will be used by all the worker
    // threads.
    //
    hCompletionPort = ::CreateIoCompletionPort (
        INVALID_HANDLE_VALUE, // handle to a file; here, port without associated file
        NULL,     // handle to I/O completion port
        0,        // completion key
        systemInfo.dwNumberOfProcessors * cDispatchers  // number of threads to execute concurrently
        );

    if ( hCompletionPort == NULL )
    {
        DebugRC( ::GetLastError () );
        LOG( DBG_ERROR ) << this << " System:: Initialize: -> CreateIOCompletitionPort failed." << eline;
        return;
        }

    // Create worker threads that will service the actual overlapped
    // I/O requests.  Create a number of worker threads for each processor
    // on the system.
    //
    for ( int i = 0; i < (int)systemInfo.dwNumberOfProcessors * cDispatchers; i++ )
    {
        unsigned int threadId;

        HANDLE
        hThreadHandle = (HANDLE) _beginthreadex
        (
            NULL,                          // pointer to thread security attributes  
            0,                             // initial thread stack size, in bytes 
            System:: QIO_Dispatcher_Thread, // pointer to thread function 
            this,                          // argument for new thread 
            0,                             // creation flags 
            &threadId                      // pointer to returned thread identifier 
            );

        if ( hThreadHandle == NULL || hThreadHandle == INVALID_HANDLE_VALUE )
        {
            DebugRC( ::GetLastError () );
            LOG( DBG_ERROR ) << this << " System:: Initialize: -> Create QIO worker thread failed." << eline;
            continue;
            }

        ::CloseHandle( hThreadHandle );
        ::Sleep( 0 ); // yield CPU
        }

    for ( i = 0; i < cGC; i++ )
    {
        unsigned int threadId;

        HANDLE
        hThreadHandle = (HANDLE) _beginthreadex
        (
            NULL,                          // pointer to thread security attributes  
            0,                             // initial thread stack size, in bytes 
            System:: GC_Thread,            // pointer to thread function 
            this,                          // argument for new thread 
            0,                             // creation flags 
            &threadId                      // pointer to returned thread identifier 
            );

        if ( hThreadHandle == NULL || hThreadHandle == INVALID_HANDLE_VALUE )
        {
            DebugRC( ::GetLastError () );
            LOG( DBG_ERROR ) << this << " System:: Initialize: -> Create GC thread failed." << eline;
            continue;
            }

        ::CloseHandle( hThreadHandle );
        ::Sleep( 0 ); // yield CPU
        }

    for ( i = 0; i < cWatchdog; i++ )
    {
        unsigned int threadId;

        HANDLE
        hThreadHandle = (HANDLE) _beginthreadex
        (
            NULL,                          // pointer to thread security attributes  
            0,                             // initial thread stack size, in bytes 
            System:: Watchdog_Thread,      // pointer to thread function 
            this,                          // argument for new thread 
            0,                             // creation flags 
            &threadId                      // pointer to returned thread identifier 
            );

        if ( hThreadHandle == NULL || hThreadHandle == INVALID_HANDLE_VALUE )
        {
            DebugRC( ::GetLastError () );
            LOG( DBG_ERROR ) << this << " System:: Initialize: -> Create Watchdog thread failed." << eline;
            continue;
            }

        ::CloseHandle( hThreadHandle );
        ::Sleep( 0 ); // yield CPU
        }
    }

void System::Destroy( void )
{
    TRACE( this << " System::Destroy" );

    // Wait until all devices are deleted
    //
    for ( ;; )
    {
        mutex.Lock ();
        bool no_devices = devices.empty () && gc_devices.empty ();
        mutex.Unlock ();

        if ( no_devices )
            break;
        Sleep( 100 );
        }

    isTerminating = true;

    // Signal and wait all Watchdog threads to exit.
    //
    while( ::InterlockedExchangeAdd( &watchdogThreadCount, 0 ) > 0 )
    {
        sema_watchdog.Release( 1 );
        Sleep( 10 ); // Give chance threads to exit
        }

    // Signal and wait all GC threads to exit.
    //
    while( ::InterlockedExchangeAdd( &gcThreadCount, 0 ) > 0 )
    {
        sema_gc_devices.Release( 1 );
        Sleep( 10 ); // Give chance threads to exit
        }

    // Signal and wait all QIO dispatchers threads to exit.
    //
    while( ::InterlockedExchangeAdd( &qioDispatcherThreadCount, 0 ) > 0 )
    {
        ::PostQueuedCompletionStatus( hCompletionPort, 0, 0, NULL );
        Sleep( 10 ); // Give chance threads to exit
        }

    ::CloseHandle( hCompletionPort );

    WSACleanup ();

    sema_watchdog.Destroy ();
    sema_gc_devices.Destroy ();

    DumpStatistics ();
    }

void System::DumpStatistics( void )
{
    LOG log( DBG_TRACE );
    log << this << " System::Statistics follows..." << eline
        << "Devices:" << eline
        << "    Constructed devices.....: " << tot_dev_constructed << eline
        << "    Destructed devices......: " << tot_dev_destructed << eline
        << "QIO:" << eline
        << "    Max. concurrent threads.: " << maxSimultaneousQIO << eline;

    inboundMemPool.DumpStatistics( log );
    outboundMemPool.DumpStatistics( log );
    }

//  Function:   System:: QIO_Dispatcher_Thread
//
//  Synopsis:   
//      This is the main worker routine for the QIO worker threads.
//      Worker threads wait on a completion port for I/O to complete. When 
//      it completes, the worker thread processes the I/O, then either pends 
//      new I/O or closes the peer's connection. When the service shuts 
//      down, other code closes the completion port which causes 
//      GetQueuedCompletionStatus() to wake up and the worker thread then 
//      exits.  
//
//  Arguments:  
//      workContext - the completion port handle that will get I/O completion
//      notifications.
//
//  Return value:
//      DWORD - status of the thread.
//
unsigned int __stdcall 
System:: QIO_Dispatcher_Thread
(
    void* theSystem
    )
{
    System* sys = (System*) theSystem;

    ::InterlockedIncrement( &sys->qioDispatcherThreadCount );

    TRACE( sys << " System::QIO_Dispatcher_Thread: BEGIN" );

    DWORD threadRC = 1;

    try
    {
        // Loop servicing I/O completions, until system runs.
        //
        while( ! sys->isTerminating )
        {
            // Get a completed IO request.
            //
            DWORD ioSize;
            Device* dev;
            OVERLAPPED* overlapped;
            BOOL bSuccess = ::GetQueuedCompletionStatus 
            (
                sys->hCompletionPort, // handle to completion port
                &ioSize,          // bytes transferred
                LPDWORD( &dev ),  // file completion key
                &overlapped,      // buffer that receives pointer to OVERLAPPED
                INFINITE          // optional timeout value
                );
            DWORD rc = ::GetLastError ();

            // Calculate number of maximum simultaneous QIO
            long qioCount = ::InterlockedIncrement( &sys->simultaneousQIO );
            if ( qioCount > sys->maxSimultaneousQIO )
                sys->maxSimultaneousQIO = qioCount;

            if ( dev )
            {
                try
                {
                    dev->DispatchIO( bSuccess, rc, ioSize, overlapped );
                    }
                catch( ... )
                {
                    LOG( DBG_ERROR ) << sys << " System::QIO_Dispatcher_Thread: "
                        "MISHAP: While dispatchig QIO to device " << dev << eline;
                    }
                }
            else if ( ! bSuccess )
            {
                DebugRC( rc );
                LOG( DBG_ERROR ) << sys << " System::QIO_Dispatcher_Thread: GetQueuedCompletionStatus failed for unknown object" << eline;
                }

            ::InterlockedDecrement( &sys->simultaneousQIO );

            // Loop around to get another completed IO request.
            }

        threadRC = 0;
        }
    catch( ... )
    {
        LOG( DBG_ERROR ) << sys << " System::QIO_Dispatcher_Thread: MISHAP: Severe exception catched." << eline;
        threadRC = 1;
        }

    TRACE( sys << " System::QIO_Dispatcher_Thread: END" );

    ::InterlockedDecrement( &sys->qioDispatcherThreadCount );

    return threadRC; // 0 means OK
    }

//  Function:   System:: GC_Thread
//
//  Synopsis:   
//      This is the thread that monitors devices deferred to be deleted.
//      It tries regulary to purge all dereferenced objects.
//    
//  Arguments:  
//      workContext - 'this' pointer to the System object
//
//  Return value:
//      DWORD - status of the thread.
//
unsigned int __stdcall System:: GC_Thread( void* theSystem )
{
    System* sys = (System*)theSystem;

    ::InterlockedIncrement( &sys->gcThreadCount );

    TRACE( sys << " System::GC_Thread: BEGIN" );

    DWORD threadRC = 1;

    try
    {
        while( ! sys->isTerminating )
        {
            sys->sema_gc_devices.Wait ();

            Device* device = NULL;
            sys->mutex.Lock ();
            if ( ! sys->gc_devices.empty () )
            {
                // Get and remove head of gc_devices list
                device = *sys->gc_devices.begin ();
                sys->gc_devices.remove( device );
                }
            sys->mutex.Unlock ();

            // If gc_devices list is empty and semaphore is signaled,
            // then try to exit thread
            if ( device == NULL )
                continue;

            TRACE( sys << " System::GC_Thread:: Deleting device " << device 
                       << " (" << device->ID() << ")" );

            try
            {
                delete device;
                }
            catch ( ... )
            {
                TRACE( sys << " System::GC_Thread: MISHAP: "
                    << "Catched exception while deleting device " << device
                    );
                }
            }

        threadRC = 0;
        }
    catch( ... )
    {
        LOG( DBG_ERROR ) << sys << " System::GC_Thread: MISHAP: Severe exception catched." << eline;
        threadRC = 1;
        }

    TRACE( sys << " System::GC_Thread: END" );

    ::InterlockedDecrement( &sys->gcThreadCount );
    
    return threadRC;
    }

//  Function:   System:: Watchdog_Thread
//
//  Synopsis:   
//      This thread is used to watchdog systems' devices' 
//      CSTA connection aliveness.
//      It finds all devices with expired watchdog and
//      a) if device is connected, it will issue SystemStatus()
//      b) if device is disconnected, it will issue Initialize()
//    
//  Arguments:  
//      workContext - 'this' pointer to the System object
//
//  Return value:
//      DWORD - status of the thread.
//
unsigned int __stdcall System:: Watchdog_Thread( void* theSystem )
{
    System* sys = (System*)theSystem;

    int seqNo = ::InterlockedIncrement( &sys->watchdogThreadCount );

    TRACE( sys << " System::Watchdog_Thread: BEGIN" );

    DWORD threadRC = 1;

    int counter0 = 0;

    try
    {
        while( ! sys->isTerminating )
        {
            sys->sema_watchdog.Wait( 1000 ); // On idle, each second perform loop

            if ( sys->isTerminating )
                break;

            // Find first device with watchdog elapsed
            // if device is connected, issue SystemStatus watchdog
            // else try to connect it

            if ( ++counter0 >= 60 )
            {
                counter0 = 0; // every 60 seconds try this:

                if ( seqNo == 1 )
                    sys->DumpStatistics ();
                }
            }

        threadRC = 0;
        }
    catch( ... )
    {
        LOG( DBG_ERROR ) << sys << " System::Watchdog_Thread: MISHAP: Severe exception catched." << eline;
        threadRC = 1;
        }

    TRACE( sys << " System::Watchdog_Thread: END" );

    ::InterlockedDecrement( &sys->watchdogThreadCount );

    return 0;
    }

//////////////////////////////////////////////////////////////////////////////
// Open Device

void System:: AddPABX( const char* pbxID, const char* ip_address, unsigned short tcp_port )
{
    TRACE( this << " System::AddPABX; PBX " << pbxID << ", ip addr " << ip_address << ", tcp port " << tcp_port );

    mutex.Lock ();

    // Find PBX with specified ID
    //
    PBX* pbx = NULL;
    for ( std::list<PBX*>::iterator i = pbxs.begin(); i != pbxs.end(); ++i )
    {
        if ( (*i)->pbxID == pbxID )
        {
            pbx = *i;
            break;
            }
        }

    if ( ! pbx )
    {
        // Just create PABX and forget it
        pbx = new PBX( pbxID, ip_address, tcp_port );
        pbxs.push_back( pbx );
        }
    else
    {
        // Update CSTA connection information
        pbx->SetConnParams( ip_address, tcp_port );
        }

    mutex.Unlock ();
    }

ErrorCode System:: OpenDevice( CallbackProcedure* cbProc, const char* pbxID, const char* devId, bool asyncConnect )
{
    TRACE( this << " System::OpenDevice; PBX " << pbxID << ", Device " << devId );

    mutex.Lock ();

    // Find PBX with specified id.
    PBX* pbx = NULL;
    for ( std::list<PBX*>::iterator i = pbxs.begin(); i != pbxs.end(); ++i )
    {
        if ( (*i)->pbxID == pbxID )
        {
            pbx = *i;
            break;
            }
        }

    if ( ! pbx )
    {
        mutex.Unlock ();
        return CSTA_INVALID_PABX_ID;
        }

    // Create new device
    //
    Ptr<Device> dev = new Device( this, pbx, devId, cbProc );

    if ( ! dev )
    {
        mutex.Unlock ();
        return CTNG_NO_MEMORY;
        }

    mutex.Unlock ();

    // If asyncConnect is indicated, then leave to Watchdog_Thread
    // to open CSTA connection and start monitor on device
    //
    if ( asyncConnect )
        return CTNG_NO_ERROR;

    // Othewise, open CSTA connection and start Monitor on device
    //
    return dev->Initialize ();
    }

/////////////////////////////////////////////////////////////////////////////
} // namespace MidCSTA
