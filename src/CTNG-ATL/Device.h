/*
    Project: CTNG COM ATL

    Module: Device.h

    Description: Declaration of the CDevice

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#ifndef __DEVICE_H_
#define __DEVICE_H_

#include "resource.h"       // main symbols

#define LITE_CONTROL 0

#if LITE_CONTROL
#include <atlctl.h>
#endif

#include "CTNGCP.h"

/////////////////////////////////////////////////////////////////////////////
// CDevice_CB_Proc
class CDevice_CB_Proc : public MidCSTA::CallbackProcedure 
{
    friend class CDevice;
    class CDevice* object;

    void OnRefCountZero( void );

public:

    CDevice_CB_Proc( CDevice* obj );
    ~CDevice_CB_Proc( void );

    void Procedure( MidCSTA::CallbackInfo* info );
    };

/////////////////////////////////////////////////////////////////////////////
// CDevice
class ATL_NO_VTABLE CDevice : 
	public CComObjectRootEx<CComMultiThreadModel>,
#if LITE_CONTROL
    public CComControl<CDevice>,
	public IViewObjectExImpl<CDevice>,
	public IOleControlImpl<CDevice>,
	public IOleObjectImpl<CDevice>,
	public IOleInPlaceActiveObjectImpl<CDevice>,
	public IOleInPlaceObjectWindowlessImpl<CDevice>,
#endif
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CDevice>,
	public IDispatchImpl<IDevice, &IID_IDevice, &LIBID_CTNGLib>,
	public CComCoClass<CDevice, &CLSID_Device>,
	public IProvideClassInfo2Impl<&CLSID_Device, &DIID__IDeviceEvents, &LIBID_CTNGLib>,
	public CProxy_IDeviceEvents<CDevice>
{
    friend CDevice_CB_Proc;
    CTsvcLIB::Ptr<CDevice_CB_Proc> cbProc;
    CTsvcLIB::Ptr<MidCSTA::Device> dev;

    MidCSTA::CSTA_Extensions ext; // CSTA extensions (private data); both oubound and inbound

public:
	CDevice()
	{
	}

    ~CDevice()
    {
        dev = NULL;
        cbProc = NULL;
    }

DECLARE_REGISTRY_RESOURCEID(IDR_DEVICE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDevice)
	COM_INTERFACE_ENTRY(IDevice)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
#if LITE_CONTROL
	COM_INTERFACE_ENTRY(IViewObjectEx) 
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
#endif
	COM_INTERFACE_ENTRY(IProvideClassInfo) //MBK-HtmlEvent
	COM_INTERFACE_ENTRY(IProvideClassInfo2) //MBK-HtmlEvent
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CDevice)
    CONNECTION_POINT_ENTRY(DIID__IDeviceEvents)
END_CONNECTION_POINT_MAP()

#if LITE_CONTROL
BEGIN_PROP_MAP(CDevice)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
END_PROP_MAP()

BEGIN_MSG_MAP(CDevice)
	CHAIN_MSG_MAP(CComControl<CDevice>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
#endif

//  Handler prototypes:
//  -------------------
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

#if LITE_CONTROL
// IViewObjectEx
	DECLARE_VIEW_STATUS(0)
#endif

// IDevice
public:
	//STDMETHOD(Open)(/*[in]*/ IPABX* pabx, /*[in]*/ BSTR id, /*[out,retval]*/ ErrorCode* errCode );
	STDMETHOD(Open)(/*[in]*/ BSTR pabxID, /*[in]*/ BSTR deviceID, /*[out,retval]*/ ErrorCode* errCode );
	STDMETHOD(Close)(/*[out,retval]*/ ErrorCode* errCode );
    STDMETHOD(TestFireAllEvents)();
    STDMETHOD(PutExtension)(/*[in]*/ VARIANT* outOID, /*[in]*/ VARIANT* outData );
    STDMETHOD(GetExtension)(/*[out]*/ SAFEARRAY** inOID, /*[out]*/ SAFEARRAY** inData);
	STDMETHOD(SystemStatus)(/*[in]*/ SystemStatusType status, /*[out,retval]*/ ErrorCode* errCode);
	STDMETHOD(EscapeService)(/*[in]*/ VARIANT* outOID, /*[in]*/ VARIANT* outData, /*[out]*/ SAFEARRAY** inOID, /*[out]*/ SAFEARRAY** inData, /*[out,retval]*/ ErrorCode* errCode);
    STDMETHOD(AlternateCall)(/*[in]*/ BSTR heldCall, /*[in]*/ BSTR activeCall, /*[out,retval]*/ ErrorCode* errCode );
	STDMETHOD(AnswerCall)(/*[in]*/ BSTR connectionId, /*[out,retval]*/ ErrorCode* errCode );
    STDMETHOD(CallCompletion)(/*[in]*/ BSTR connectionId, /*[in]*/ FeatureInfoType feature, /*[out,retval]*/ ErrorCode* errCode );
	STDMETHOD(ClearCall)(/*[in]*/ BSTR callToBeCleared, /*[out,retval]*/ ErrorCode* errCode );
	STDMETHOD(ClearConnection)(/*[in]*/ BSTR connectionId, /*[out,retval]*/ ErrorCode* errCode );
	STDMETHOD(ConferenceCall)(/*[in]*/ BSTR heldCall, /*[in]*/ BSTR activeCall, /*[out]*/ VARIANT* connectionId, /*[out,retval]*/ ErrorCode* errCode );
	STDMETHOD(ConsultationCall)(/*[in]*/ BSTR existingCall, /*[in]*/ BSTR calledDirectoryNumber, /*[out]*/ VARIANT* connectionId, /*[out,retval]*/ ErrorCode* errCode );
	STDMETHOD(DivertCall_Deflect)(/*[in]*/ BSTR connectionId, /*[in]*/ BSTR newDestination, /*[out,retval]*/ ErrorCode* errCode );
	STDMETHOD(DivertCall_DirectedPickup)(/*[in]*/ BSTR connectionId, /*[in]*/ BSTR requestingDevice, /*[out,retval]*/ ErrorCode* errCode );
	STDMETHOD(DivertCall_GroupPickup)(/*[in]*/ BSTR groupDevice, /*[out,retval]*/ ErrorCode* errCode );
	STDMETHOD(HoldCall)(/*[in]*/ BSTR connectionId, /*[in]*/ BOOL reserveConnection, /*[out,retval]*/ ErrorCode* errCode );
	STDMETHOD(MakeCall)(/*[in]*/ BSTR deviceToCall, /*[out]*/ VARIANT* connectionId, /*[out,retval]*/ ErrorCode* errCode );
	STDMETHOD(MakePredictiveCall)(/*[in]*/ BSTR calledDirectoryNumber, /*[out]*/ VARIANT* connectionId, /*[out,retval]*/ ErrorCode* errCode );
    STDMETHOD(ReconnectCall)(/*[in]*/ BSTR heldCall, /*[in]*/ BSTR activeCall, /*[out,retval]*/ ErrorCode* errCode );
    STDMETHOD(RetrieveCall)(/*[in]*/ BSTR connectionId, /*[out,retval]*/ ErrorCode* errCode );
    STDMETHOD(TransferCall)(/*[in]*/ BSTR heldCall, /*[in]*/ BSTR activeCall, /*[out]*/ VARIANT* connectionId, /*[out,retval]*/ ErrorCode* errCode );
    STDMETHOD(QueryDevice_MessageWaiting)(/*[out]*/ BOOL* indicator, /*[out,retval]*/ ErrorCode* errCode );
    STDMETHOD(QueryDevice_DoNotDisturb)(/*[out]*/ BOOL* indicator, /*[out,retval]*/ ErrorCode* errCode );
    STDMETHOD(QueryDevice_Forward)(/*[out]*/ VARIANT* forwardInfo, /*[out,retval]*/ ErrorCode* errCode );
    STDMETHOD(QueryDevice_DeviceInfo)(/*[out]*/ DeviceClassType* devClass, /*[out]*/ DeviceTypeType* devType, /*[out,retval]*/ ErrorCode* errCode );
    STDMETHOD(QueryDevice_AgentState)(/*[out]*/ AgentStateType* agentState, /*[out,retval]*/ ErrorCode* errCode );
    STDMETHOD(SetFature_MessageWaiting)(/*[in]*/ BOOL indicator, /*[out,retval]*/ ErrorCode* errCode );
    STDMETHOD(SetFature_DoNotDisturb)(/*[in]*/ BOOL indicator, /*[out,retval]*/ ErrorCode* errCode );
    STDMETHOD(SetFature_Forward)(/*[in]*/ ForwardingType forwardingType, /*[in]*/ BSTR forwardDN, /*[out,retval]*/ ErrorCode* errCode );
    STDMETHOD(SetFature_RequestAgentState)(/*[in]*/ AgentParameterType state, /*[in]*/ BSTR agentID, /*[in]*/ BSTR agentGroup, /*[in]*/ BSTR agentPassword, /*[out,retval]*/ ErrorCode* errCode );
	STDMETHOD(WaitOpen)(/*[in]*/ double timeoutSeconds, /*[out,retval]*/ ErrorCode* errCode);

#if LITE_CONTROL
	HRESULT OnDraw( ATL_DRAWINFO& di ) // MBK-Control
	{
		RECT& rc = *(RECT*)di.prcBounds;
		Rectangle( di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom );

		SetTextAlign(di.hdcDraw, TA_CENTER|TA_BASELINE);
		LPCTSTR pszText = _T("CTNG.Device");
		TextOut(di.hdcDraw, 
			(rc.left + rc.right) / 2, 
			(rc.top + rc.bottom) / 2, 
			pszText, 
			lstrlen(pszText));

		return S_OK;
	}
#endif
};

#endif //__DEVICE_H_
