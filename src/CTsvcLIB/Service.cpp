/*
    Project: CTsvcLIB

    Module: Service.Cpp

    Description: WinNT Service proxy class

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "CTsvcLIB.h"

using namespace std;

namespace CTsvcLIB
{

//  Function:   SERVICE:: construct
//
//  Synopsis:   Method setups service parameters.
//
SERVICE:: SERVICE
(
    LPSTR name,
    LPSTR displayname,
    LPSTR modulepath,
    LPSERVICE_MAIN_FUNCTION main_foo
    )
{
    sz_ServiceName = name;
    sz_ServiceDisplayName = displayname;

    strcpy( sz_ModulePath, modulepath ? modulepath : "" );

    pMain = main_foo;

    fServiceTerminating = FALSE;
    fService = TRUE;
    hService = NULL;

    if ( sz_ServiceDisplayName && pMain )
    {
        //
        // Ignore specified module path
        //
        if ( GetModuleFileName( NULL, sz_ModulePath, sizeof( sz_ModulePath ) ) == 0 )
        {
            DebugRC( GetLastError () );
            LOG( DBG_ERROR )
                << "-> Cannot get module filename."
                << eline;
            }
        }
    }

//  Function:   Install
//
//  Synopsis:   Installs service into SCManager registry.
//
//  Arguments:
//    none
//
BOOL
SERVICE:: Install
(
    LPSTR sz_Dependencies,
    LPSTR sz_UserName,
    LPSTR sz_Password
    )
{
    if ( ! sz_ServiceDisplayName )
    {
        LOG( DBG_ERROR )
            << "Service " << sz_ServiceName
            << " trying to install w/o display name specified."
            << eline;
        return FALSE;
        }

    if ( strlen( sz_ModulePath ) == 0 )
    {
        LOG( DBG_ERROR )
            << "Service " << sz_ServiceName
            << " trying to install w/o module path specified."
            << eline;
        return FALSE;
        }

    SC_HANDLE
    schSCManager = OpenSCManager(
                        NULL,                   // machine (NULL == local)
                        NULL,                   // database (NULL == default)
                        SC_MANAGER_ALL_ACCESS   // access required
                        );

    if ( ! schSCManager )
    {
        DebugRC( GetLastError () );
        LOG( DBG_ERROR )
            << "-> Open SCManager failed."
            << eline;
        return FALSE;
        }

    SC_HANDLE 
    schService = CreateService(
        schSCManager,              // SCManager database
        sz_ServiceName,            // name of service
        sz_ServiceDisplayName,     // name to display
        SERVICE_ALL_ACCESS,        // desired access
        SERVICE_WIN32_OWN_PROCESS, // service type
        SERVICE_DEMAND_START,      // start type
        SERVICE_ERROR_NORMAL,      // error control type
        sz_ModulePath,             // service's binary
        NULL,                      // no load ordering group
        NULL,                      // no tag identifier
        sz_Dependencies,           // dependencies (may be NULL)
        sz_UserName,               // account name of service
        sz_Password                // password for service account
        );

    if ( ! schService )
    {
        DebugRC( GetLastError () );
        LOG( DBG_ERROR )
            << "-> Create service failed."
            << eline;
        CloseServiceHandle( schSCManager );
        return FALSE;
        }

    LOG( DBG_TRACE )
        << "Service " << sz_ServiceName << " is installed."
        << eline;

    CloseServiceHandle( schService );
    CloseServiceHandle( schSCManager );

    return TRUE;
    }

//  Function:   Remove
//
//  Synopsis:   Stops and removes the service
//
//  Arguments:
//    none
//
BOOL
SERVICE:: Remove
(
    VOID
    )
{
    SERVICE_STATUS ssStatus;

    if ( ! QueryStatus( ssStatus ) )
        return FALSE;

    if ( ssStatus.dwCurrentState != SERVICE_STOPPED )
        Stop ();

    SC_HANDLE
    schSCManager = OpenSCManager(
                        NULL,                   // machine (NULL == local)
                        NULL,                   // database (NULL == default)
                        SC_MANAGER_ALL_ACCESS   // access required
                        );

    if ( ! schSCManager )
    {
        DebugRC( GetLastError () );
        LOG( DBG_ERROR )
            << "-> Open SCManager failed."
            << eline;
        return FALSE;
        }

    SC_HANDLE
    schService = OpenService( 
                        schSCManager,       // handle to service control manager database
                        sz_ServiceName,     // pointer to name of service to start
                        SERVICE_ALL_ACCESS  // type of access to service
                        );

    if ( ! schService )
    {
        DebugRC( GetLastError () );
        LOG( DBG_ERROR )
            << "-> Open service " << sz_ServiceName << " failed."
            << eline;
        CloseServiceHandle( schSCManager );
        return FALSE;
        }

    if( ! DeleteService( schService ) )
    {
        DebugRC( GetLastError () );
        LOG( DBG_ERROR )
            << "-> Delete service failed."
            << eline;
        CloseServiceHandle( schService );
        CloseServiceHandle( schSCManager );
        return FALSE;
        }

    LOG( DBG_TRACE )
        << "Service " << sz_ServiceName << " is removed."
        << eline;

    CloseServiceHandle( schService );
    CloseServiceHandle( schSCManager );

    return TRUE;
    }

//  Function:   Stop
//
//  Synopsis:   Stops the service
//
//  Arguments:
//    none
//
//  Return Value:
//    none
//
BOOL 
SERVICE:: Stop
(
    VOID
    )
{
    SC_HANDLE
    schSCManager = OpenSCManager(
                        NULL,                   // machine (NULL == local)
                        NULL,                   // database (NULL == default)
                        SC_MANAGER_ALL_ACCESS   // access required
                        );

    if ( ! schSCManager )
    {
        DebugRC( GetLastError () );
        LOG( DBG_ERROR )
            << "-> Open SCManager failed."
            << eline;
        return FALSE;
        }

    SC_HANDLE 
    schService = OpenService(
        schSCManager,          // SCManager database
        sz_ServiceName,        // name of service
        SERVICE_ALL_ACCESS     // type of access to service
        );

    if ( ! schService )
    {
        DebugRC( GetLastError () );
        LOG( DBG_ERROR )
            << "-> Service " << sz_ServiceName << " open failed."
            << eline;
        CloseServiceHandle( schSCManager );
        return FALSE;
        }
    
    // try to stop the service
    //
    SERVICE_STATUS ssStatus;

    if ( ! ControlService( schService,         // handle to service 
                         SERVICE_CONTROL_STOP, // control code 
                         &ssStatus             // pointer to service status structure  
                         )
        )
    {
        DebugRC( GetLastError () );
        LOG( DBG_ERROR )
            << "-> Service " << sz_ServiceName << " control stop failed."
            << eline;
        CloseServiceHandle( schService );
        CloseServiceHandle( schSCManager );
        return FALSE;
        }

    Sleep( 1000 ); // 1 second sleep

    if ( ! QueryServiceStatus( schService, &ssStatus ) )
    {
        DebugRC( GetLastError () );
        LOG( DBG_ERROR )
            << "-> Service " << sz_ServiceName << " query status failed."
            << eline;
        CloseServiceHandle( schService );
        CloseServiceHandle( schSCManager );
        return FALSE;
        }

    long timeout = long( ssStatus.dwWaitHint );
    DWORD checkpoint = ssStatus.dwCheckPoint;

    while( ssStatus.dwCurrentState != SERVICE_STOPPED && timeout >= 0 )
    {
        LOG( DBG_TRACE )
            << "Service " << sz_ServiceName
            << " stop checkpoint " << checkpoint
            << ", waiting " << timeout / 1000
            << eline;

        if ( ssStatus.dwCurrentState == SERVICE_STOP_PENDING )
        {
            Sleep( 2000 );
            timeout -= 2000;
            }
        else
        {
            LOG( DBG_ERROR )
                << "-> Service " << sz_ServiceName
                << " unexpected service state."
                << eline;
            CloseServiceHandle( schService );
            CloseServiceHandle( schSCManager );
            return FALSE;
            }

        if ( ! QueryServiceStatus( schService, &ssStatus ) )
        {
            DebugRC( GetLastError () );
            LOG( DBG_ERROR )
                << "-> Service " << sz_ServiceName << " query status failed."
                << eline;
            CloseServiceHandle( schService );
            CloseServiceHandle( schSCManager );
            return FALSE;
            }

        if ( checkpoint != ssStatus.dwCheckPoint )
        {
            checkpoint = ssStatus.dwCheckPoint;
            timeout = long( ssStatus.dwWaitHint );
            }
        }

    if ( ssStatus.dwCurrentState != SERVICE_STOPPED )
    {
        LOG( DBG_ERROR )
            << "Service " << sz_ServiceName << " timeout while stopping."
            << eline;
        CloseServiceHandle( schService );
        CloseServiceHandle( schSCManager );
        return FALSE;
        }

    CloseServiceHandle( schService );
    CloseServiceHandle( schSCManager );

    LOG( DBG_TRACE )
        << "Service " << sz_ServiceName << " is stopped."
        << eline;

    return TRUE;
    }

//  Function:   Start
//
//  Synopsis:   Starts the service
//
//  Arguments:
//    none
//
//  Return Value:
//    none
//
BOOL 
SERVICE:: Start
(
    VOID
    )
{
    SC_HANDLE
    schSCManager = OpenSCManager(
                        NULL,                   // machine (NULL == local)
                        NULL,                   // database (NULL == default)
                        SC_MANAGER_ALL_ACCESS   // access required
                        );

    if ( ! schSCManager )
    {
        DebugRC( GetLastError () );
        LOG( DBG_ERROR )
            << "-> Open SCManager failed."
            << eline;
        return FALSE;
        }

    SC_HANDLE 
    schService = OpenService(
        schSCManager,              // SCManager database
        sz_ServiceName,            // name of service
        SERVICE_ALL_ACCESS         // type of access to service
        );

    if ( ! schService )
    {
        DebugRC( GetLastError () );
        LOG( DBG_ERROR )
            << "-> Service " << sz_ServiceName << " open failed."
            << eline;
        CloseServiceHandle( schSCManager );
        return FALSE;
        }
    
	SERVICE_STATUS ssStatus;

	if ( ! QueryServiceStatus( schService, &ssStatus ) )
    {
        DebugRC( GetLastError () );
        LOG( DBG_ERROR )
            << "-> Service " << sz_ServiceName << " query status failed."
            << eline;
        CloseServiceHandle( schService );
        CloseServiceHandle( schSCManager );
        return FALSE;
        }

    if ( ssStatus.dwCurrentState == SERVICE_RUNNING )
    {
        LOG( DBG_TRACE )
            << "Service " << sz_ServiceName << " is running."
            << eline;
        CloseServiceHandle( schService );
        CloseServiceHandle( schSCManager );
        return TRUE;
        }

    if ( ssStatus.dwCurrentState == SERVICE_STOPPED )
    {
        // try to start the service
        //
        LOG( DBG_WARN )
            << "Starting service " << sz_ServiceName << " ..."
            << eline;

        if ( ! StartService( schService, 0, NULL ) )
        {
            DebugRC( GetLastError () );
            LOG( DBG_ERROR )
                << "-> Service " << sz_ServiceName << " start failed."
                << eline;
            CloseServiceHandle( schService );
            CloseServiceHandle( schSCManager );
            return FALSE;
            }
        }
    else if ( ssStatus.dwCurrentState == SERVICE_START_PENDING )
    {
        }

    Sleep( 1000 ); // 1 second sleep

    if ( ! QueryServiceStatus( schService, &ssStatus ) )
    {
        DebugRC( GetLastError () );
        LOG( DBG_ERROR )
            << "-> Service " << sz_ServiceName << " query status failed."
            << eline;
        CloseServiceHandle( schService );
        CloseServiceHandle( schSCManager );
        return FALSE;
        }

    long timeout = long( ssStatus.dwWaitHint );
    DWORD checkpoint = ssStatus.dwCheckPoint;

    while( ssStatus.dwCurrentState != SERVICE_RUNNING && timeout >= 0 )
    {
        LOG( DBG_TRACE )
            << "Service " << sz_ServiceName
            << " start checkpoint " << checkpoint
            << ", waiting " << timeout / 1000
            << eline;

        if ( ssStatus.dwCurrentState == SERVICE_START_PENDING )
        {
            Sleep( 2000 ); // 2 seconds
            timeout -= 2000;
            }
        else
        {
            LOG( DBG_ERROR )
                << "-> Service " << sz_ServiceName
                << " unexpected service state."
                << eline;
            CloseServiceHandle( schService );
            CloseServiceHandle( schSCManager );
            return FALSE;
            }

        if ( ! QueryServiceStatus( schService, &ssStatus ) )
        {
            DebugRC( GetLastError () );
            LOG( DBG_ERROR )
                << "-> Service " << sz_ServiceName << " query status failed."
                << eline;
            CloseServiceHandle( schService );
            CloseServiceHandle( schSCManager );
            return FALSE;
            }

        if ( checkpoint != ssStatus.dwCheckPoint )
        {
            checkpoint = ssStatus.dwCheckPoint;
            timeout = long( ssStatus.dwWaitHint );
            }
        }

    if ( ssStatus.dwCurrentState != SERVICE_RUNNING )
    {
        LOG( DBG_ERROR )
            << "Service " << sz_ServiceName << " timeout while starting."
            << eline;
        CloseServiceHandle( schService );
        CloseServiceHandle( schSCManager );
        return FALSE;
        }

    CloseServiceHandle( schService );
    CloseServiceHandle( schSCManager );

    LOG( DBG_TRACE )
        << "Service " << sz_ServiceName << " is running."
        << eline;

    return TRUE;
    }

//  Function:   QueryStatus
//
//  Synopsis:   Returns service status
//
BOOL 
SERVICE:: QueryStatus
(
    SERVICE_STATUS& ssStatus
    )
{
    SC_HANDLE
    schSCManager = OpenSCManager(
                        NULL,                   // machine (NULL == local)
                        NULL,                   // database (NULL == default)
                        SC_MANAGER_ALL_ACCESS   // access required
                        );

    if ( ! schSCManager )
    {
        DebugRC( GetLastError () );
        LOG( DBG_ERROR )
            << "-> Open SCManager failed."
            << eline;
        return 0;
        }

    SC_HANDLE 
    schService = OpenService(
        schSCManager,              // SCManager database
        sz_ServiceName,            // name of service
        SERVICE_ALL_ACCESS         // type of access to service
        );

    if ( ! schService )
    {
        DebugRC( GetLastError () );
        LOG( DBG_ERROR )
            << "-> Service " << sz_ServiceName << " open failed."
            << eline;
        CloseServiceHandle( schSCManager );
        return FALSE;
        }

    // get service status
    //
    if ( ! QueryServiceStatus( schService, &ssStatus ) )
    {
        DebugRC( GetLastError () );
        LOG( DBG_ERROR )
            << "-> Service " << sz_ServiceName << " query status failed."
            << eline;
        CloseServiceHandle( schService );
        CloseServiceHandle( schSCManager );
        return FALSE;
        }

    if ( ! QueryServiceStatus(
            schService,    // handle of service
            &ssStatus       // address of service status structure
            )
        )
    {
        DebugRC( GetLastError () );
        LOG( DBG_ERROR )
            << "Service " << sz_ServiceName << " query status failed."
            << eline;
        CloseServiceHandle( schService );
        CloseServiceHandle( schSCManager );
        return FALSE;
        }

    CloseServiceHandle( schService );
    CloseServiceHandle( schSCManager );

    return TRUE;
    }

BOOL
SERVICE:: DebugStatus
(
    VOID
    )
{
    SERVICE_STATUS ssStatus;

    if ( ! QueryStatus( ssStatus ) )
        return FALSE;

    DebugStatus( ssStatus );

    return TRUE;
    }

VOID
SERVICE:: DebugStatus
(
    SERVICE_STATUS& ssStatus
    )
{
    switch( ssStatus.dwCurrentState )
    {
        case SERVICE_STOPPED:
            LOG( DBG_TRACE )
                << "Service " << sz_ServiceName << " is stopped."
                << eline;
            break;

        case SERVICE_START_PENDING:
            LOG( DBG_TRACE )
                << "Service " << sz_ServiceName << " is starting."
                << eline;
            break;

        case SERVICE_STOP_PENDING:
            LOG( DBG_TRACE )
                << "Service " << sz_ServiceName << " is stapping."
                << eline;
            break;

        case SERVICE_RUNNING:
            LOG( DBG_TRACE )
                << "Service " << sz_ServiceName << " is running."
                << eline;
            break;

        case SERVICE_CONTINUE_PENDING:
            LOG( DBG_TRACE )
                << "Service " << sz_ServiceName << " is continue pending."
                << eline;
            break;

        case SERVICE_PAUSE_PENDING:
            LOG( DBG_TRACE )
                << "Service " << sz_ServiceName << " is pause pending."
                << eline;
            break;

        case SERVICE_PAUSED:
            LOG( DBG_TRACE )
                << "Service " << sz_ServiceName << " is paused."
                << eline;
            break;

        default:
            LOG( DBG_WARN )
                << "Service " << sz_ServiceName << " unknown current state."
                << eline;
        }
    }

BOOL
SERVICE:: IsRunning( VOID )
{
    SERVICE_STATUS ssStatus;

    if ( ! QueryStatus( ssStatus ) )
        return FALSE;

    return ssStatus.dwCurrentState == SERVICE_RUNNING;
    } 

BOOL
SERVICE:: IsStarting( VOID )
{
    SERVICE_STATUS ssStatus;

    if ( ! QueryStatus( ssStatus ) )
        return FALSE;

    return ssStatus.dwCurrentState == SERVICE_START_PENDING;
    } 

BOOL
SERVICE:: IsStopped( VOID )
{
    SERVICE_STATUS ssStatus;

    if ( ! QueryStatus( ssStatus ) )
        return FALSE;

    return ssStatus.dwCurrentState == SERVICE_STOPPED;
    } 

//  Function:   SERVICE:: Dispatch
//
//  Synopsis:   This method starts service control dispatcher
//              regarding pMain.
//
//  Arguments:  (none)
//
//
VOID
SERVICE:: Dispatch
(
    VOID
    )
{
    if ( ! pMain )
    {
        LOG( DBG_ERROR )
            << "Dispatch failed on reference service " << sz_ServiceName
            << eline;
        return;
        }

    //
    // If we're a service, go to the service controller,
    // otherwise start the service immediately.
    //

    if ( fService )
    {
        //
        // This table is the service dispatch table. It lists the services in
        // this process by name, and the entry point to invoke to start them.
        //
        SERVICE_TABLE_ENTRY dispatchTable [] = {
            { sz_ServiceName, pMain },
            { NULL, NULL } 
            };

        StartServiceCtrlDispatcher( dispatchTable );
        }

    else
    {
        ::SetConsoleTitle( sz_ServiceDisplayName );
        pMain( 0, NULL );
        }
    }

//  Function:   NotifyServiceController
//
//  Synopsis:   Notifies the service controller of our control entry point,
//              and tells it that we're trying to start up.
//
//
BOOL
SERVICE:: NotifyController(
    LPHANDLER_FUNCTION ServiceControlHandler
    )
{
    if ( ! fService )
        return TRUE;

    ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    ServiceStatus.dwCurrentState = SERVICE_STOPPED;
    ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    ServiceStatus.dwWin32ExitCode = 0;
    ServiceStatus.dwServiceSpecificExitCode = 0;
    ServiceStatus.dwCheckPoint = 0;
    ServiceStatus.dwWaitHint = 0;

    hService = RegisterServiceCtrlHandler( sz_ServiceName, ServiceControlHandler );

    if ( hService )
    {
        UpdateStatus( SERVICE_START_PENDING );
        return TRUE;
        }

    return FALSE;
    }

BOOL
SERVICE:: UpdateStatus
(
    DWORD Status,
    DWORD waithint
    )
{
    if ( hService )
    {
        ServiceStatus.dwCurrentState = Status;

        if ( Status == SERVICE_START_PENDING 
        || Status == SERVICE_STOP_PENDING )
        {
            ServiceStatus.dwCheckPoint ++;
            ServiceStatus.dwWaitHint = waithint;
            }
        else
        {
            ServiceStatus.dwCheckPoint = 0;
            ServiceStatus.dwWaitHint = 0;
            }

        return SetServiceStatus( hService, &ServiceStatus );
        }

    return FALSE;
    }

BOOL
SERVICE:: UpdateStatusInterrogate
(
    DWORD waithint
    )
{
    if ( hService )
    {
        DWORD Status = ServiceStatus.dwCurrentState;

        if ( Status == SERVICE_START_PENDING 
        || Status == SERVICE_STOP_PENDING )
        {
            ServiceStatus.dwCheckPoint ++;
            ServiceStatus.dwWaitHint = waithint;
            }
        else
        {
            ServiceStatus.dwCheckPoint = 0;
            ServiceStatus.dwWaitHint = 0;
            }

        return SetServiceStatus( hService, &ServiceStatus );
        }

    return FALSE;
    }

VOID
SERVICE:: FailStart
(
    DWORD Win32Code,
    DWORD PrivateCode
    )
{
    if ( hService )
    {
        ServiceStatus.dwWin32ExitCode = Win32Code;
        ServiceStatus.dwServiceSpecificExitCode = PrivateCode;
        UpdateStatus( SERVICE_STOPPED );
        }
    }

} // namespace CTsvcLIB