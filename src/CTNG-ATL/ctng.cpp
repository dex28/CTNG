/*
    Project: CTNG COM ATL

    Module: CTNG.cpp

    Description: Implementation of CCTNG_ServiceModule, and WinMain()

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "StdAfx.h"
#include "Resource.h"

#include <initguid.h>
#include <cstdio>

#include "CTNG.h"

#include "CTNG-EventLog.h"

#include "CTNG_i.c"

#include "System.h"
#include "PABX.h"
#include "Device.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Parameters:

const TCHAR APP_ID[] = _T("{7D5492A9-D3CF-4123-9193-9F8B5E3920F9}");

const TCHAR* SAFE_CLSID_LIST [] =
{
    _T("CLSID\\{B63AC033-0B40-4FD1-9BE1-5276FED1A5A1}"), // System
    _T("CLSID\\{155E8B8C-6C03-470E-82F7-16F99C417A5F}"), // PABX
    _T("CLSID\\{2BE420EA-C378-40F8-BF73-B19CFF854186}")  // Device
    };

const TCHAR HKEY_EVENTLOG[] = _T("System\\CurrentControlSet\\Services\\EventLog\\System");

const TCHAR szTokens[] = _T("-/");

const DWORD dwPause = 1000; // time to wait for threads to finish up

///////////////////////////////////////////////////////////////////////////////
// Global objects:

CCTNG_ServiceModule _Module;

MidCSTA::System cstaSys;

BEGIN_OBJECT_MAP(ObjectMap)
    OBJECT_ENTRY(CLSID_System, CSystem)
    OBJECT_ENTRY(CLSID_PABX, CPABX)
    OBJECT_ENTRY(CLSID_Device, CDevice)
END_OBJECT_MAP()

///////////////////////////////////////////////////////////////////////////////
// CCTNG_ServiceModule Implementation:

namespace // unnamed
{

LPCTSTR FindOneOf( LPCTSTR p1, LPCTSTR p2 )
{
    for ( ; p1 && *p1; p1 = CharNext(p1) )
    {
        for ( LPCTSTR p = p2; p && *p; p = CharNext(p) )
        {
            if ( *p1 == *p )
                return CharNext(p1);
        }
    }
    return NULL;
}

}

// Although some of these functions are big they are declared inline since they are only used once

inline HRESULT CCTNG_ServiceModule::RegisterServer(BOOL bRegTypeLib, BOOL bService)
{
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr))
        return hr;

    // Get the executable file path
    TCHAR szFilePath[_MAX_PATH];
    ::GetModuleFileName(NULL, szFilePath, _MAX_PATH);

    // Create EventLog service entry
    {
        CRegKey keyEvLog;
        LONG lRes = keyEvLog.Open( HKEY_LOCAL_MACHINE, HKEY_EVENTLOG, KEY_WRITE );
        if ( lRes == ERROR_SUCCESS )
        {
            // Remove previous EventLog entry
            keyEvLog.DeleteSubKey( m_szDisplayName );

            // Add EvengLog entry
            CRegKey keyEvLogSvc;
            keyEvLogSvc.Create( keyEvLog, m_szDisplayName );
			DWORD dwTypesSupported = 0x7;
#if _MSC_VER < 1300 // Depricated starting from MS VS.Net
            keyEvLogSvc.SetValue( dwTypesSupported, _T("TypesSupported") );
            keyEvLogSvc.SetValue( szFilePath, _T("EventMessageFile") );
#else
            keyEvLogSvc.SetValue( _T("TypesSupported"), REG_DWORD, &dwTypesSupported, dwTypesSupported );
            keyEvLogSvc.SetValue( _T("EventMessageFile"), REG_SZ, szFilePath, _tcslen( szFilePath ) + sizeof(TCHAR) );
#endif
            }
        }

    // Remove any previous service since it may point to
    // the incorrect file
    Uninstall();

    // Add service entries
    UpdateRegistryFromResource(IDR_CTNG, TRUE);

    // Adjust the AppID for Local Server or Service
    {
        CRegKey keyAppID;
        LONG lRes = keyAppID.Open(HKEY_CLASSES_ROOT, _T("AppID"), KEY_WRITE);
        if (lRes != ERROR_SUCCESS)
            return lRes;

        CRegKey key;
        lRes = key.Open(keyAppID, APP_ID, KEY_WRITE);
        if (lRes != ERROR_SUCCESS)
            return lRes;

        key.DeleteValue( _T("LocalService") );
    
        if ( bService )
        {
			TCHAR szLocalService[] = _T("CTNG");
			TCHAR szServiceParams[] = _T("-Service");
#if _MSC_VER < 1300 // Depricated starting from MS VS.Net
            key.SetValue( szLocalService, _T("LocalService") );
            key.SetValue( szServiceParams, _T("ServiceParameters") );
#else
            key.SetValue( _T("LocalService"), REG_SZ, szLocalService, sizeof( szLocalService ) );
            key.SetValue( _T("ServiceParameters"), REG_SZ, szServiceParams, sizeof( szServiceParams ) );
#endif
            }
        }

    if ( bService )
    {
        // Create service
        Install ();
        }

    // Add object entries
    hr = CComModule::RegisterServer(bRegTypeLib);

    // Mark that CLSID's can be used safely 
    for ( int i = 0; i < sizeof( SAFE_CLSID_LIST ) / sizeof( SAFE_CLSID_LIST[0] ); i++ )
    {
        CRegKey keyCLSID;
        LONG lRes = keyCLSID.Open( HKEY_CLASSES_ROOT, SAFE_CLSID_LIST[ i ], KEY_WRITE );
        if ( lRes == ERROR_SUCCESS )
        {
            // Remove previous implemented categories key
            keyCLSID.DeleteSubKey( _T("Implemented Categories") );

            // Create new subkeys stating safely scripting
            CRegKey key1;
            key1.Create( keyCLSID, _T("Implemented Categories\\{7DD95801-9882-11CF-9FA9-00AA006C42C4}") );

            // Create new subkeys stating safely initialization from persistence data
            CRegKey key2;
            key2.Create( keyCLSID, _T("Implemented Categories\\{7DD95802-9882-11CF-9FA9-00AA006C42C4}") );
            }
        }

    CoUninitialize();
    return hr;
}

inline HRESULT CCTNG_ServiceModule::UnregisterServer()
{
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr))
        return hr;

    // Remove service entries
    UpdateRegistryFromResource(IDR_CTNG, FALSE);

    // Remove service
    Uninstall();

    // Remove object entries
    CComModule::UnregisterServer(TRUE);
    CoUninitialize();

    // Remove EventLog entries
    CRegKey keyEvLog;
    LONG lRes = keyEvLog.Open( HKEY_LOCAL_MACHINE, HKEY_EVENTLOG, KEY_WRITE );
    if ( lRes == ERROR_SUCCESS )
        keyEvLog.DeleteSubKey( m_szDisplayName );

    return S_OK;
}

inline HRESULT CCTNG_ServiceModule::ServiceStart( void )
{
    TRACE( "Starting service ..." );

    return S_OK;
    }

inline HRESULT CCTNG_ServiceModule::ServiceStop( void )
{
    return S_OK;
    }

inline HRESULT CCTNG_ServiceModule::ServiceShowStatus( void )
{
    return S_OK;
    }

HRESULT CCTNG_ServiceModule::RunInDebugMode( void )
{
    _Module.m_bService = FALSE;

    _Module.Run();

    // When we get here, the service has been stopped
    return _Module.m_status.dwWin32ExitCode;
    }

inline void CCTNG_ServiceModule::Init(_ATL_OBJMAP_ENTRY* p, HINSTANCE h, UINT nServiceNameID, UINT nDisplayNameID, UINT nServiceDescID, const GUID* plibid)
{
    CComModule::Init(p, h, plibid);

    m_bService = TRUE;

    LoadString(h, nServiceNameID, m_szServiceName, sizeof(m_szServiceName) / sizeof(TCHAR));
    LoadString(h, nDisplayNameID, m_szDisplayName, sizeof(m_szDisplayName) / sizeof(TCHAR));
    LoadString(h, nServiceDescID, m_szServiceDesc, sizeof(m_szServiceDesc) / sizeof(TCHAR));

    // set up the initial service status 
    m_hServiceStatus = NULL;
    m_status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    m_status.dwCurrentState = SERVICE_STOPPED;
    m_status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    m_status.dwWin32ExitCode = 0;
    m_status.dwServiceSpecificExitCode = 0;
    m_status.dwCheckPoint = 0;
    m_status.dwWaitHint = 0;
}

LONG CCTNG_ServiceModule::Unlock()
{
    LONG l = CComModule::Unlock();
    if (l == 0 && !m_bService)
        PostThreadMessage(dwThreadID, WM_QUIT, 0, 0);
    return l;
}

BOOL CCTNG_ServiceModule::IsInstalled()
{
    BOOL bResult = FALSE;

    SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

    if (hSCM != NULL)
    {
        SC_HANDLE hService = ::OpenService(hSCM, m_szServiceName, SERVICE_QUERY_CONFIG);
        if (hService != NULL)
        {
            bResult = TRUE;
            ::CloseServiceHandle(hService);
        }
        ::CloseServiceHandle(hSCM);
    }
    return bResult;
}

inline BOOL CCTNG_ServiceModule::Install()
{
    if (IsInstalled())
        return TRUE;

    SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (hSCM == NULL)
    {
        MessageBox(NULL, _T("Couldn't open service manager"), m_szServiceName, MB_OK);
        return FALSE;
    }

    // Get the executable file path
    TCHAR szFilePath[_MAX_PATH];
    ::GetModuleFileName(NULL, szFilePath, _MAX_PATH);

    // Create the service object and add it to the SCM database hSCM
    SC_HANDLE hService = ::CreateService
    (
        hSCM,                          // handle to SCM database 
        m_szServiceName,               // name of service to start
        m_szDisplayName,               // display name
        SERVICE_ALL_ACCESS,            // type of access to service
        SERVICE_WIN32_OWN_PROCESS      // type of service
        | SERVICE_INTERACTIVE_PROCESS ,
        SERVICE_AUTO_START,            // when to start service SERVICE_DEMAND_START
        SERVICE_ERROR_NORMAL,          // severity of service failure
        szFilePath,                    // name of binary file
        NULL,                          // name of load ordering group
        NULL,                          // tag identifier
        _T("RPCSS\0"),                 // array of dependency names
        NULL,                          // account name 
        NULL                           // account password
        );

    if (hService == NULL)
    {
        ::CloseServiceHandle(hSCM);
        MessageBox(NULL, _T("Couldn't create service"), m_szServiceName, MB_OK);
        return FALSE;
    }
/*
    SERVICE_DESCRIPTION svc_desc = { m_szServiceDesc };

    ::ChangeServiceConfig2(
        hService,  // handle to service
        SERVICE_CONFIG_DESCRIPTION, // information level
        &svc_desc ); // new data
*/    
    ::CloseServiceHandle(hService);
    ::CloseServiceHandle(hSCM);

    return TRUE;
}

inline BOOL CCTNG_ServiceModule::Uninstall()
{
    if (!IsInstalled())
        return TRUE;

    SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

    if (hSCM == NULL)
    {
        MessageBox(NULL, _T("Couldn't open service manager"), m_szServiceName, MB_OK);
        return FALSE;
    }

    SC_HANDLE hService = ::OpenService(hSCM, m_szServiceName, SERVICE_STOP | DELETE);

    if (hService == NULL)
    {
        ::CloseServiceHandle(hSCM);
        MessageBox(NULL, _T("Couldn't open service"), m_szServiceName, MB_OK);
        return FALSE;
    }

    SERVICE_STATUS status;
    ::ControlService(hService, SERVICE_CONTROL_STOP, &status);

    BOOL bDelete = ::DeleteService(hService);

    ::CloseServiceHandle(hService);
    ::CloseServiceHandle(hSCM);

    if (bDelete)
        return TRUE;

    MessageBox(NULL, _T("Service could not be deleted"), m_szServiceName, MB_OK);

    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////////////
// Logging functions
void CCTNG_ServiceModule::LogEvent( WORD wType, DWORD dwMesgId, LPCTSTR pFormat, ... )
{
    return; // Disabled

    // Get a handle to use with ReportEvent().
    HANDLE  hEventSource = ::RegisterEventSource( NULL, m_szDisplayName );
    if ( hEventSource == NULL )
        return;

    // Depending on pFormat we write to event log with one string or without strings.
    //
    if ( pFormat == NULL )
    {
        // Write to event log without strings.
        ::ReportEvent( hEventSource, wType, 0, dwMesgId, NULL, 0, 0, NULL, NULL);
        }
    else
    {
        // Write to event log having one string.
        TCHAR   chMsg[256];

        va_list pArg;
        va_start( pArg, pFormat );
        _vstprintf( chMsg, pFormat, pArg );
        va_end( pArg );

        LPTSTR lpszStrings[ 1 ];
        lpszStrings[ 0 ] = chMsg;

        ::ReportEvent( hEventSource, wType, 0, dwMesgId, NULL, 1, 0, (LPCTSTR*)lpszStrings, NULL );
        }

    // Close event source handle.
    ::DeregisterEventSource( hEventSource );
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Service startup and registration
inline void CCTNG_ServiceModule::Start()
{
    SERVICE_TABLE_ENTRY st[] =
    {
        { m_szServiceName, _ServiceMain },
        { NULL, NULL }
    };
    if (m_bService && !::StartServiceCtrlDispatcher(st))
    {
        m_bService = FALSE;
    }
    if (m_bService == FALSE)
        Run();
}

inline void CCTNG_ServiceModule::ServiceMain(DWORD /* dwArgc */, LPTSTR* /* lpszArgv */)
{
    // Register the control request handler
    //
    m_status.dwCurrentState = SERVICE_START_PENDING;
    m_hServiceStatus = RegisterServiceCtrlHandler(m_szServiceName, _Handler);
    if (m_hServiceStatus == NULL)
    {
        LogEvent( EVENTLOG_ERROR_TYPE, MC_HANDLER_NOT_INSTALLED );
        return;
    }
    SetServiceStatus(SERVICE_START_PENDING);

    m_status.dwWin32ExitCode = S_OK;
    m_status.dwCheckPoint = 0;
    m_status.dwWaitHint = 0;

    // When the Run function returns, the service has stopped.
    //
    Run();

    LogEvent( EVENTLOG_WARNING_TYPE, MC_SERVICE_STOPPED );

    SetServiceStatus( SERVICE_STOPPED );
}

inline void CCTNG_ServiceModule::Handler(DWORD dwOpcode)
{
    switch (dwOpcode)
    {
        case SERVICE_CONTROL_STOP:
            SetServiceStatus(SERVICE_STOP_PENDING);
            PostThreadMessage(dwThreadID, WM_QUIT, 0, 0);
            break;
        case SERVICE_CONTROL_PAUSE:
            break;
        case SERVICE_CONTROL_CONTINUE:
            break;
        case SERVICE_CONTROL_INTERROGATE:
            break;
        case SERVICE_CONTROL_SHUTDOWN:
            break;
        default:
            LogEvent( EVENTLOG_ERROR_TYPE, MC_BAD_SERVICE_REQUEST );
    }
}

void WINAPI CCTNG_ServiceModule::_ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv)
{
    _Module.ServiceMain(dwArgc, lpszArgv);
}

void WINAPI CCTNG_ServiceModule::_Handler(DWORD dwOpcode)
{
    _Module.Handler(dwOpcode); 
}

void CCTNG_ServiceModule::SetServiceStatus(DWORD dwState)
{
    m_status.dwCurrentState = dwState;
    ::SetServiceStatus(m_hServiceStatus, &m_status);
}

void CCTNG_ServiceModule::Run()
{
    _Module.dwThreadID = GetCurrentThreadId();

    // NOTE: If you are running on NT 4.0 or higher you can use the following call
    //       instead the CoInitialize(NULL) to make the EXE free threaded (i.e. MTA model).
    //       This means that calls come in on a random RPC thread.
    //
    HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    //HRESULT hr = CoInitialize(NULL);

    _ASSERTE(SUCCEEDED(hr));

    // This provides a NULL DACL which will allow access to everyone.
    CSecurityDescriptor sd;
    sd.InitializeFromThreadToken();
    hr = CoInitializeSecurity(sd, -1, NULL, NULL,
        RPC_C_AUTHN_LEVEL_PKT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);

    _ASSERTE(SUCCEEDED(hr));

    hr = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER | CLSCTX_REMOTE_SERVER, REGCLS_MULTIPLEUSE);

    _ASSERTE(SUCCEEDED(hr));

    LogEvent( EVENTLOG_INFORMATION_TYPE, MC_SERVICE_STARTED );

    if (m_bService)
        SetServiceStatus(SERVICE_START_PENDING);

    // Initialize CSTALib::System
    //
    cstaSys.Initialize ();

    if (m_bService)
        SetServiceStatus(SERVICE_RUNNING);

    MSG msg;
    while (GetMessage(&msg, 0, 0, 0))
    {
        DispatchMessage(&msg);
        }

    _Module.RevokeClassObjects ();

    // Destroy CSTALib::System
    //
    cstaSys.Destroy ();

    // Wait for any threads to finish
    ::Sleep(dwPause);

    ::CoUninitialize();
}

/////////////////////////////////////////////////////////////////////////////
//
extern "C"
int WINAPI _tWinMain
(
    HINSTANCE hInstance,
    HINSTANCE /*hPrevInstance*/,
    LPTSTR lpCmdLine,
    int /*nShowCmd*/
    )
{
    lpCmdLine = GetCommandLine(); // this line necessary for _ATL_MIN_CRT

    _Module.Init
    (
        ObjectMap,          // _ATL_OBJMAP_ENTRY* p
        hInstance,          // HINSTANCE h
        IDS_SERVICENAME,    // UINT nServiceNameID
        IDS_SVCDISPLAYNAME, // UINT nDisplayNameID
        IDS_SERVICEDESC,    // UINT nServiceDescID
        &LIBID_CTNGLib      // const GUID* plibid
        );

    // Parse command line for command line parameters:
    //
    LPCTSTR lpszToken = FindOneOf( lpCmdLine, szTokens );
    while (lpszToken != NULL)
    {
        // Register as Local Server
        if (lstrcmpi(lpszToken, _T("RegServer"))==0)
            return _Module.RegisterServer(TRUE, FALSE);
        
        // Unregister Local Server
        else if (lstrcmpi(lpszToken, _T("UnregServer"))==0)
            return _Module.UnregisterServer();

        // Register as Service
        else if (lstrcmpi(lpszToken, _T("Install"))==0)
            return _Module.RegisterServer(TRUE, TRUE);
        
        // Unregister Service
        else if (lstrcmpi(lpszToken, _T("Remove"))==0)
            return _Module.UnregisterServer();

        // Start service
        else if (lstrcmpi(lpszToken, _T("Start"))==0)
            return _Module.ServiceStart ();
        
        // Stop service
        else if (lstrcmpi(lpszToken, _T("Stop"))==0)
            return _Module.ServiceStop ();

        // Show service status
        else if (lstrcmpi(lpszToken, _T("Status"))==0)
            return _Module.ServiceShowStatus ();

        // Start service in debug mode
        else if (lstrcmpi(lpszToken, _T("Debug"))==0)
            return _Module.RunInDebugMode ();

        lpszToken = FindOneOf( lpszToken, szTokens );
    }

    // Who am I: service or out-of-process server?
    // ...answer: see _Module.m_bService
    {
        CRegKey keyAppID;
        LONG lRes = keyAppID.Open(HKEY_CLASSES_ROOT, _T("AppID"), KEY_READ);
        if (lRes != ERROR_SUCCESS)
            return lRes;

        CRegKey key;
        lRes = key.Open(keyAppID, APP_ID, KEY_READ);
        if (lRes != ERROR_SUCCESS)
            return lRes;

        TCHAR szValue[_MAX_PATH];
        DWORD dwLen = _MAX_PATH;
#if _MSC_VER < 1300 // Depricated starting from MS VS.Net
        lRes = key.QueryValue( _T("LocalService"), szValue, &dwLen );
#else
		DWORD dwType;
        lRes = key.QueryValue( _T("LocalService"), &dwType, szValue, &dwLen );
#endif
        _Module.m_bService = ( lRes == ERROR_SUCCESS ) ? TRUE : FALSE;
    }

    _Module.Start();

    // When we get here, the service has been stopped
    //
    return _Module.m_status.dwWin32ExitCode;
}
