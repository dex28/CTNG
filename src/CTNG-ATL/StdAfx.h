/*
    Project: CTNG COM ATL

    Module: StdAfx.h

    Description: include file for standard system include files,
        or project specific include files that are used frequently,
        but are changed infrequently

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#ifndef AFX_STDAFX_H_CTNG_INCLUDED
#define AFX_STDAFX_H_CTNG_INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
//#define _ATL_APARTMENT_THREADED
#define _ATL_FREE_THREADED

#include <atlbase.h>

///////////////////////////////////////////////////////////////////////////////

class CCTNG_ServiceModule : public CComModule
{
public:
	HRESULT RegisterServer(BOOL bRegTypeLib, BOOL bService);
	HRESULT UnregisterServer();
	void Init(_ATL_OBJMAP_ENTRY* p, HINSTANCE h, UINT nServiceNameID, UINT nDisplayNameID, UINT nServiceDescID, const GUID* plibid = NULL);
    void Start();
	void ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
    void Handler(DWORD dwOpcode);
    void Run();
    BOOL IsInstalled();
    BOOL Install();
    BOOL Uninstall();
	LONG Unlock();
	void LogEvent( WORD wType, DWORD dwMesgId, LPCTSTR pFormat = NULL, ... );
    void SetServiceStatus(DWORD dwState);
    void SetupAsLocalServer();

    HRESULT ServiceStart( void );
    HRESULT ServiceStop( void );
    HRESULT ServiceShowStatus( void );
    HRESULT RunInDebugMode( void );

//Implementation
private:
	static void WINAPI _ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
    static void WINAPI _Handler(DWORD dwOpcode);

// data members
public:
    TCHAR m_szServiceName[256];
    TCHAR m_szDisplayName[256];
    TCHAR m_szServiceDesc[256];
    SERVICE_STATUS_HANDLE m_hServiceStatus;
    SERVICE_STATUS m_status;
	DWORD dwThreadID;
	BOOL m_bService;
};

// Do not change the name of _Module. It is used in <atlcom.h>!
//
extern CCTNG_ServiceModule _Module;

#include <atlcom.h>

///////////////////////////////////////////////////////////////////////////////
//
#include <CSTA-Lib.h>

extern MidCSTA::System cstaSys;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H_CTNG_INCLUDED)
