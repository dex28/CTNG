/*
    Project: CTNG COM ATL

    Module: System.cpp

    Description: Implementation of CSystem

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "stdafx.h"
#include "CTNG.h"
#include "System.h"

/////////////////////////////////////////////////////////////////////////////
// CSystem

STDMETHODIMP CSystem::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISystem
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
        //if (::ATL::InlineIsEqualGUID(*arr[i],riid))
        if ( InlineIsEqualGUID(*arr[i],riid) )
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////

using namespace MidCSTA;

STDMETHODIMP CSystem::OpenConsole()
{
    cstaSys.OpenConsole ();
    // cstaSys.OpenLogFile( "C:/x.log" );
	return S_OK;
}

STDMETHODIMP CSystem::CloseConsole()
{
    cstaSys.CloseConsole ();
	return S_OK;
}

STDMETHODIMP CSystem::HasConsole( BOOL* pResult )
{
    *pResult = cstaSys.HasConsole ();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CSystem::Dump()
{
/*
    ICreateErrorInfo *pcerrinfo;
    HRESULT hr = CreateErrorInfo(&pcerrinfo);

    // set fields here by calling ICreateErrorInfo methods on pcerrinfo
    pcerrinfo->SetGUID( IID_ISystem );
    pcerrinfo->SetDescription( L"Error !!!" );
    //pcerrinfo->SetHelpContext( dwhelpcontext );  // and so forth

    IErrorInfo *perrinfo;
    hr = pcerrinfo->QueryInterface(IID_IErrorInfo, (LPVOID FAR*) &perrinfo);
    if (SUCCEEDED(hr))
    {
        SetErrorInfo(0, perrinfo);
        perrinfo->Release();
        }

    pcerrinfo->Release();

    // then, eventually...
    return E_FAIL;  // E_FAIL or other appropriate failure code
*/
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CSystem::AddPABX( BSTR pabxId, BSTR ip_address, long tcp_port )
{
    if ( ! pabxId )
        return S_OK;

    if ( ! ip_address )
        return S_OK;

    cstaSys.AddPABX( USTR( pabxId ), USTR( ip_address ), (unsigned short) tcp_port );

	return S_OK;
}

STDMETHODIMP CSystem::Sleep( long milliseconds )
{
    ::Sleep( milliseconds );
	return S_OK;
}

STDMETHODIMP CSystem::VerboseErrorCategory( ErrorCode rc, BSTR* pVal )
{
    *pVal = CComBSTR( MidCSTA::System::VerboseCategory( rc ) );
    return S_OK;
    }

STDMETHODIMP CSystem::VerboseErrorCode( ErrorCode rc, BSTR* pVal )
{
    *pVal = CComBSTR( MidCSTA::System::Verbose( rc ) );
    return S_OK;
    }

STDMETHODIMP CSystem::VerboseSystemStatus( SystemStatusType ss, BSTR* pVal )
{
    *pVal = CComBSTR( MidCSTA::System::Verbose( ss ) );
    return S_OK;
    }

STDMETHODIMP CSystem::VerboseEventCause( EventCauseType ec, BSTR* pVal )
{
    *pVal = CComBSTR( MidCSTA::System::Verbose( ec ) );
    return S_OK;
    }

STDMETHODIMP CSystem::VerboseLocalConnectionState( LocalConnectionStateType lcs, BSTR* pVal )
{
    *pVal = CComBSTR( MidCSTA::System::Verbose( lcs ) );
    return S_OK;
    }

STDMETHODIMP CSystem::GetCounters( STAT_COUNTERS* sysCounters )
{
    extern STAT_COUNTERS stat;
    *sysCounters = stat;
    return S_OK;
    }

/*    
    *result = NULL;

    SAFEARRAYBOUND sabound[ 2 ]; // two-dimensional array
    sabound[0].cElements = 0;
    sabound[0].lLbound = 0;
    sabound[1].cElements = 0;
    sabound[1].lLbound = 0;

    SAFEARRAY FAR* psa = ::SafeArrayCreate( VT_BSTR, 2, sabound );

    if ( psa == NULL )
        return ResultFromScode( E_OUTOFMEMORY );

    *result = psa;

    return S_OK;

    // Create an array of size 20
    //
    SAFEARRAYBOUND sabound[ 1 ];
    sabound[0].cElements = 20;
    sabound[0].lLbound = 0;    

    SAFEARRAY FAR* psa = ::SafeArrayCreate( VT_BSTR, 1, sabound );

    if ( psa == NULL )
        return ResultFromScode( E_OUTOFMEMORY );
    
    // Fill each array element with the same string, "contents"
    //
    BSTR bstr = ::SysAllocString(OLESTR("contents")); 

    for ( long i = 0; i < 20; i++ ) 
    {
        HRESULT hr = ::SafeArrayPutElement( psa, &i, bstr );
        if ( FAILED( hr ) )
        {
            if ( bstr ) ::SysFreeString( bstr );
            if ( psa ) ::SafeArrayDestroy( psa );
            return hr;
            }
        }  

    ::SysFreeString( bstr );   // The caller must free all parameters & return values.   
    *result = psa;
    return S_OK;
*/
