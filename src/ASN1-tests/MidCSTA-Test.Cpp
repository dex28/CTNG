/*
    Project: ASN1Test

    Module: MidCSTA-Test.Cpp

    Description: ASN1Lib and CSTALib test module

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "CSTA-Lib.h"

using namespace std;
using namespace MidCSTA;

#include "CSTA-Eric.h"

#include <process.h> // _beginthreadex()

//////////////////////////////////////////////////////////////////////////////

System cstaSys;

//////////////////////////////////////////////////////////////////////////////

long numberOfCSTAConnections = 0;
long countOfSystemService = 0;
long errorCount = 0;
long threadCount = 0;

//////////////////////////////////////////////////////////////////////////////
// Callback procedure (empty)

class Empty_CB : public CallbackProcedure 
{
    void OnRefCountZero( void )
    {
        TRACE( this << " Empty_CB::OnRefCountZero" );
        ReleaseDevice ();
        delete this;
        }

public:

    Empty_CB()
    {
        TRACE( this << " Empty_CB::Empty_CB" );
        }

    ~Empty_CB( void )
    {
        TRACE( this << " Empty_CB::~Empty_CB" );
        }

    void Procedure( CallbackInfo* info );
    };

    void Empty_CB::Procedure( CallbackInfo* cbi )
    {
        if ( ! GetDev () )
            return;

        switch( cbi->GetType () )
        {
        case ASN::EventIDType::callCleared:
        {
            CBI_CallCleared* info = (CBI_CallCleared*)cbi;
            }
            break;

        case ASN::EventIDType::conferenced:
        {
            CBI_Conferenced* info = (CBI_Conferenced*)cbi;
            }
            break;

        case ASN::EventIDType::connectionCleared:
        {
            CBI_ConnectionCleared* info = (CBI_ConnectionCleared*)cbi;
            }
            break;

        case ASN::EventIDType::delivered:
        {
            CBI_Delivered* info = (CBI_Delivered*)cbi;
            }
            break;

        case ASN::EventIDType::diverted:
        {
            CBI_Diverted* info = (CBI_Diverted*)cbi;
            }
            break;

        case ASN::EventIDType::established:
        {
            CBI_Established* info = (CBI_Established*)cbi;
            }
            break;

        case ASN::EventIDType::failed:
        {
            CBI_Failed* info = (CBI_Failed*)cbi;
            }
            break;

        case ASN::EventIDType::held:
        {
            CBI_Held* info = (CBI_Held*)cbi;
            }
            break;

        case ASN::EventIDType::networkReached:
        {
            CBI_NetworkReached* info = (CBI_NetworkReached*)cbi;
            }
            break;

        case ASN::EventIDType::originated:
        {
            CBI_Originated* info = (CBI_Originated*)cbi;
            }
            break;

        case ASN::EventIDType::queued:
        {
            CBI_Queued* info = (CBI_Queued*)cbi;
            }
            break;

        case ASN::EventIDType::retrieved:
        {
            CBI_Retrieved* info = (CBI_Retrieved*)cbi;
            }
            break;

        case ASN::EventIDType::serviceInitiated:
        {
            CBI_ServiceInitiated* info = (CBI_ServiceInitiated*)cbi;
            }
            break;

        case ASN::EventIDType::transferred:
        {
            CBI_Transferred* info = (CBI_Transferred*)cbi;
            }
            break;

        case ASN::EventIDType::outOfService:
        {
            CBI_OutOfService* info = (CBI_OutOfService*)cbi;
            }
            break;

        case ASN::EventIDType::backInService:
        {
            CBI_BackInService* info = (CBI_BackInService*)cbi;
            }
            break;

        case 0x1001: // System Status
        {
            CBI_SystemStatus* info = (CBI_SystemStatus*)cbi;
            ::InterlockedIncrement( &countOfSystemService );
            }
            break;

        case 0x1002: // Monitor Started
        {
            CBI_MonitorStarted* info = (CBI_MonitorStarted*)cbi;
            ::InterlockedIncrement( &numberOfCSTAConnections );
            }
            break;

        case 0x1003: // Remote Disconnected
        {
            CBI_RemoteDisconnected* info = (CBI_RemoteDisconnected*)cbi;
            }
            break;

        default:
            break;
        }
    }

//////////////////////////////////////////////////////////////////////////////

#define COUNT_ERROR(ec) \
    ( ec != CTNG_NO_ERROR && ::InterlockedIncrement( &errorCount ) )

static unsigned int __stdcall TestRun( void* device_id )
{
    ::InterlockedIncrement( &threadCount );

    const char* devId = (const char*)device_id;

    LOG( DBG_TRACE ) << "TestRun started " << devId << " -----------------" << eline;

    Ptr<Empty_CB> proc;

    for ( int i = 0; i < 5; i++ )
    {
        proc = new Empty_CB();

        // Open Device
        ErrorCode error = cstaSys.OpenDevice( proc, USTR( "myPBX" ), USTR( devId ) );
        COUNT_ERROR( error );
        if ( ! error )
        {
            for ( int j = 0; j < 5; j++ )
            {
                ::Sleep( 20 );
                error = proc->GetDev()->SystemStatus( ss_normal, NULL );
                COUNT_ERROR( error );
                }
            }

        Sleep( 1000 );

        error = proc->GetDev()->Initialize (); // Restart Monitor
        COUNT_ERROR( error );
        if ( ! error )
        {
            for ( int j = 0; j < 5; j++ )
            {
                ::Sleep( 20 );
                error = proc->GetDev()->SystemStatus( ss_normal, NULL );
                COUNT_ERROR( error );
                }
            }

        Sleep( 1000 );
        }

    proc = NULL;

    LOG( DBG_TRACE ) << "TestRun Completed " << devId << " -----------------" << eline;

    ::InterlockedDecrement( &threadCount );

    return 0;
    }

static void TestRun2( const char* devId )
{
    Ptr<Empty_CB> proc = new Empty_CB();

    // Open Device
    ErrorCode error = cstaSys.OpenDevice( proc, USTR( "myPBX" ), USTR( devId ) );
    if ( ! error )
        error = proc->GetDev()->SystemStatus( ss_normal, NULL );

    Sleep( 1000 );
    LOG( DBG_TRACE ) << "Press RETURN to continue (2)... ";
    getchar ();

    proc = NULL; // This will delete proc and device

    Sleep( 1000 );
    LOG( DBG_TRACE ) << "Press RETURN to continue (3)... ";
    getchar ();
    }

int TestMidCSTA( void )
{
    LOG( DBG_TRACE ) << "Press RETURN to start test... ";
    getchar ();

    cstaSys.Initialize( 16 ); // number of QIO threads 16

    cstaSys.AddPABX( "myPBX", "10.0.1.98", 2555 );

#if 0
    TestRun2( "755" );
#else
    char devId[100][20]; // Device IDs to start TestRun on

    for ( int i = 0; i < 100; i++ )
    {
        sprintf( devId[ i ], "%d", 801 + i % 10 ); // Devices 801-810

        HANDLE hT = (HANDLE) _beginthreadex( NULL, 0, 
            TestRun, 
            (void*)( devId[ i ] ), 
            0, NULL 
            );
        ::CloseHandle( hT );
        Sleep( 500 ); // 0.5s between thread creation
        }

    // Wait all threds to complete
    //
    while ( ::InterlockedExchangeAdd( &threadCount, 0 ) > 0 )
        ::Sleep( 100 );
#endif

    cstaSys.Destroy ();

    LOG( DBG_TRACE ) << "Error Count " << errorCount 
        << ", System Services Count " << countOfSystemService 
        << ", CSTA Connection Count " << numberOfCSTAConnections 
        << eline;

    return 0;
    }
