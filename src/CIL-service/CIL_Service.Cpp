
#include "CTsvcLIB.h"
#include "Protocols.h"

using namespace std;
using namespace CTsvcLIB;

///////////////////////////////////////////////////////////////////////////////
// CIL Service definition
///////////////////////////////////////////////////////////////////////////////

class CIL_Service : public SERVICE
{
    static void WINAPI Main( DWORD argc, LPTSTR  argv[] );
    static BOOL WINAPI ConsoleControlHandler( DWORD dwCtrlType );
    static VOID WINAPI ServiceControlHandler( DWORD fdwControl );

public:

    CIL_Service ()
    : SERVICE
    (
        "CIL_Service",            // Service Name
        "CMDR Logging Service",   // Service Display Name
        NULL,                     // Module Path
        Main                      // Service Main
        )
    {
        }
    };

namespace
{
    QCPortPool pool;
    CIL_Service Service;
}

char sa_password[ 256 ];
 

///////////////////////////////////////////////////////////////////////////////

//  Function:   ServiceControlHandler
//
//  Synopsis:   Handles requests from the service controller.
//
//  Arguments:  [fdwControl] -- Request code
//
VOID WINAPI
CIL_Service:: ServiceControlHandler
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
CIL_Service:: ConsoleControlHandler
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
CIL_Service:: Main
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
             "CIL_Service.log", // pointer to name of the file 
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

    //////////////////////////////////////////////////////////////////////////

    pool.Initialize( 4 );

    if(0)// Start CIL server
    {

        ::GetPrivateProfileString(
            "CIL",                   // points to section name
            "sa_password",         // points to key name
            "",               // points to default string
            (char*)sa_password,            // points to destination buffer 
            sizeof( sa_password ),         // size of destination buffer 
            "CallSrv.INI"             // points to initialization filename 
            );

        int port = ::GetPrivateProfileInt(
            "CIL",                   // points to section name
            "port",         // points to key name
            2112,              // points to default value
            "CallSrv.INI"             // points to initialization filename 
            );

        static CTsvcLIB::TCP_Listener_Parameters params;
        params.local_IP_address = INADDR_ANY;
        params.local_TCP_port = port;
        params.pool = &pool;
        params.seed = new MD110_CMDR_Protocol ();

        TRACE( "Password " << sa_password << ", port " << port );

        pool.Start_TCP_Listener( params );
        }

    if(1)// Start ICU-ICS server
    {
        static CTsvcLIB::TCP_Listener_Parameters params;
        params.local_IP_address = INADDR_ANY;
        params.local_TCP_port = 4060; //2501;
        params.pool = &pool;
        params.seed = new MD110_ICU_Protocol ();

        pool.Start_TCP_Listener( params );
        }

    if(0)// Start ICU-VM server
    {
        static CTsvcLIB::TCP_Listener_Parameters params;
        params.local_IP_address = INADDR_ANY;
        params.local_TCP_port = 2502;
        params.pool = &pool;
        params.seed = new MD110_ICU_Protocol ();

        pool.Start_TCP_Listener( params );
        }

    if(0)// Start MIS client
    {
        MD110_MIS_Protocol* protocol = new MD110_MIS_Protocol ();
        CTsvcLIB::QCPort_TCP* port = new CTsvcLIB::QCPort_TCP( &pool, protocol );
        port->OpenConnection( "bc11.dssab.com", 2000 );
        //port->OpenConnection( "127.0.0.1", 2000 );
        }

    if(0)// Start MML client
    {
        MD110_MML_Protocol* protocol = new MD110_MML_Protocol ();
        CTsvcLIB::QCPort_TCP* port = new CTsvcLIB::QCPort_TCP( &pool, protocol );
        port->OpenConnection( "bc11.dssab.com", 23 );
        }

    if(0)// Start CIMD2 client
    {
        CIMD2_Protocol* protocol = new CIMD2_Protocol ();
        CTsvcLIB::QCPort_TCP* port = new CTsvcLIB::QCPort_TCP( &pool, protocol );
        port->OpenConnection( "smsc.europolitan.se", 9971 );
        }

    if(0)// Start SMTP server
    {
        new SMTP_Server_Protocol( &pool );
        }

    if(0)// Start SMTP client
    {
        SMTP_Client_Protocol* client = new SMTP_Client_Protocol( &pool, "213.131.141.131" );
        client->Initiate ();
        }

    if(0)// Start HTTP server
    {
        new HTTP_Server_Protocol( &pool );
        }

    if(0)// Start HTTP client
    {
        HTTP_Client_Protocol* client = new HTTP_Client_Protocol( &pool, "213.131.141.141" );
        client->Initiate ();
        }

    // We are running...
    //
    Service.UpdateStatus( SERVICE_RUNNING );

    LOG( DBG_WARN )
        << "Running " << Service.Name () << " service."
        << eline;

    for ( ;; )
    {
        if ( Service.IsTerminating () )
            break;
        // pool.Dump ();
        Sleep( 1000 );
        }

    pool.WaitTerminate ();

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

        LOG::UseHandle( ::GetStdHandle( STD_OUTPUT_HANDLE ) );

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

