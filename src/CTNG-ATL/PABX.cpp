/*
    Project: CTNG COM ATL

    Module: PABX.cpp

    Description: Implementation of CPABX

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "stdafx.h"
#include "CTNG.h"
#include "PABX.h"

/////////////////////////////////////////////////////////////////////////////
// CPABX

STDMETHODIMP CPABX::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPABX
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		// if (::ATL::InlineIsEqualGUID(*arr[i],riid))
		if ( InlineIsEqualGUID(*arr[i],riid) )
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CPABX::Open(BSTR id)
{
	return S_OK;
}

STDMETHODIMP CPABX::Close()
{
	return S_OK;
}

STDMETHODIMP CPABX::get_ID(BSTR *pVal)
{
    *pVal = CComBSTR( "" );
	return S_OK;
}

STDMETHODIMP CPABX::put_ID(BSTR newVal)
{
	return S_OK;
}



