/*
    Project: CTNG COM ATL

    Module: PABX.h

    Description: Declaration of the CPABX

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#ifndef __PABX_H_
#define __PABX_H_

#include "resource.h"       // main symbols
#include "CTNGCP.h"

/////////////////////////////////////////////////////////////////////////////
// CPABX
class ATL_NO_VTABLE CPABX : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CPABX, &CLSID_PABX>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CPABX>,
	public IDispatchImpl<IPABX, &IID_IPABX, &LIBID_CTNGLib>,
	public CProxy_IPABXEvents< CPABX >
{
    // MidCSTA::PABX* pabx;

public:
	CPABX()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_PABX)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPABX)
	COM_INTERFACE_ENTRY(IPABX)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CPABX)
    CONNECTION_POINT_ENTRY(DIID__IPABXEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPABX
public:
	STDMETHOD(get_ID)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ID)(/*[in]*/ BSTR newVal);
	STDMETHOD(Close)();
	STDMETHOD(Open)(/*[in]*/ BSTR id);
};

#endif //__PABX_H_
