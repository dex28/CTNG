/*
    Project: CTNG COM ATL

    Module: System.h

    Description: Declaration of the CSystem

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

#include "resource.h"       // main symbols
#include "CTNGCP.h"

/////////////////////////////////////////////////////////////////////////////
// CSystem
class ATL_NO_VTABLE CSystem : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CSystem, &CLSID_System>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CSystem>,
	public IDispatchImpl<ISystem, &IID_ISystem, &LIBID_CTNGLib>,
	public CProxy_ISystemEvents< CSystem >
{
public:
	CSystem()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SYSTEM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSystem)
	COM_INTERFACE_ENTRY(ISystem)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CSystem)
    CONNECTION_POINT_ENTRY(DIID__ISystemEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISystem
public:
	STDMETHOD(OpenConsole)();
	STDMETHOD(CloseConsole)();
    STDMETHOD(HasConsole)( /*[out,retval]*/ BOOL* pResult );
	STDMETHOD(AddPABX)(/*[in]*/ BSTR pabxId, /*[in]*/ BSTR ip_address, /*[in]*/ long tcp_port);
	STDMETHOD(Dump)();
	STDMETHOD(Sleep)(/*[in]*/ long milliseconds);
    STDMETHOD(VerboseErrorCategory)(/*[in]*/ ErrorCode rc, /*[out,retval]*/ BSTR* pVal );
    STDMETHOD(VerboseErrorCode)(/*[in]*/ ErrorCode rc, /*[out,retval]*/ BSTR* pVal );
    STDMETHOD(VerboseSystemStatus)(/*[in]*/ SystemStatusType ss, /*[out,retval]*/ BSTR* pVal );
    STDMETHOD(VerboseEventCause)(/*[in]*/ EventCauseType ec, /*[out,retval]*/ BSTR* pVal );
    STDMETHOD(VerboseLocalConnectionState)(/*[in]*/ LocalConnectionStateType lcs, /*[out,retval]*/ BSTR* pVal );
    STDMETHOD(GetCounters)(/*[out]*/ STAT_COUNTERS* sysCounters );
};

#endif //__SYSTEM_H_
