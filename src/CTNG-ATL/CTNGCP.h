/*
    Project: CTNG COM ATL

    Module: CTNGCP.h

    Description: Connection points' implementations

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#ifndef _CTNGCP_H_INCLUDED
#define _CTNGCP_H_INCLUDED

class ToVariant
{
    VARIANT variant;
public:
    ToVariant( SAFEARRAY** psa )
    {
        ::VariantInit( &variant );
        variant.vt = VT_ARRAY | VT_UI1;
        variant.parray = *psa;
        }
    operator VARIANT& ()
    {
        return variant;
        }
    };

template <class T>
class CProxy_IPABXEvents : public IConnectionPointImpl<T, &DIID__IPABXEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnSystemStatus(SystemStatusType status)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[1];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				pvars[0] = status;
				DISPPARAMS disp = { pvars, NULL, 1, 0 };
				pDispatch->Invoke(0x1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
		}
		delete[] pvars;
	
	}
};

template <class T>
class CProxy_ISystemEvents : public IConnectionPointImpl<T, &DIID__ISystemEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
};



template <class T>
class CProxy_IDeviceEvents : public IConnectionPointImpl<T, &DIID__IDeviceEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnCallCleared(BSTR clearedCall, LocalConnectionStateType localConnectionInfo, EventCauseType cause, SAFEARRAY * * manufacturerOID, SAFEARRAY * * privateData)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[5];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				pvars[4] = clearedCall;
				pvars[3] = localConnectionInfo;
				pvars[2] = cause;
				pvars[1] = ToVariant( manufacturerOID );
				pvars[0] = ToVariant( privateData );
				DISPPARAMS disp = { pvars, NULL, 5, 0 };
				pDispatch->Invoke(0x1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
		}
		delete[] pvars;
	
	}
	VOID Fire_OnConferenced(BSTR primaryOldCall, BSTR secondaryOldCall, BSTR confController, BSTR addedParty, BSTR conferenceConnections, LocalConnectionStateType localConnectionInfo, EventCauseType cause, SAFEARRAY * * manufacturerOID, SAFEARRAY * * privateData)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[9];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				pvars[8] = primaryOldCall;
				pvars[7] = secondaryOldCall;
				pvars[6] = confController;
				pvars[5] = addedParty;
				pvars[4] = conferenceConnections;
				pvars[3] = localConnectionInfo;
				pvars[2] = cause;
				pvars[1] = ToVariant( manufacturerOID );
				pvars[0] = ToVariant( privateData );
				DISPPARAMS disp = { pvars, NULL, 9, 0 };
				pDispatch->Invoke(0x2, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
		}
		delete[] pvars;
	
	}
	VOID Fire_OnConnectionCleared(BSTR droppedConnection, BSTR releasingDevice, LocalConnectionStateType localConnectionInfo, EventCauseType cause, SAFEARRAY * * manufacturerOID, SAFEARRAY * * privateData)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[6];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				pvars[5] = droppedConnection;
				pvars[4] = releasingDevice;
				pvars[3] = localConnectionInfo;
				pvars[2] = cause;
				pvars[1] = ToVariant( manufacturerOID );
				pvars[0] = ToVariant( privateData );
				DISPPARAMS disp = { pvars, NULL, 6, 0 };
				pDispatch->Invoke(0x3, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
		}
		delete[] pvars;
	
	}
	VOID Fire_OnDelivered(BSTR connection, BSTR alertingDevice, BSTR callingDevice, BSTR calledDevice, BSTR lastRedirectionDevice, LocalConnectionStateType localConnectionInfo, EventCauseType cause, SAFEARRAY * * manufacturerOID, SAFEARRAY * * privateData)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[9];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				pvars[8] = connection;
				pvars[7] = alertingDevice;
				pvars[6] = callingDevice;
				pvars[5] = calledDevice;
				pvars[4] = lastRedirectionDevice;
				pvars[3] = localConnectionInfo;
				pvars[2] = cause;
				pvars[1] = ToVariant( manufacturerOID );
				pvars[0] = ToVariant( privateData );
				DISPPARAMS disp = { pvars, NULL, 9, 0 };
				pDispatch->Invoke(0x4, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
		}
		delete[] pvars;
	
	}
	VOID Fire_OnDiverted(BSTR connection, BSTR divertingDevice, BSTR newDestination, LocalConnectionStateType localConnectionInfo, EventCauseType cause, SAFEARRAY * * manufacturerOID, SAFEARRAY * * privateData)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[7];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				pvars[6] = connection;
				pvars[5] = divertingDevice;
				pvars[4] = newDestination;
				pvars[3] = localConnectionInfo;
				pvars[2] = cause;
				pvars[1] = ToVariant( manufacturerOID );
				pvars[0] = ToVariant( privateData );
				DISPPARAMS disp = { pvars, NULL, 7, 0 };
				pDispatch->Invoke(0x5, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
		}
		delete[] pvars;
	
	}
	VOID Fire_OnEstablished(BSTR establishedConnection, BSTR answeredDevice, BSTR callingDevice, BSTR calledDevice, BSTR lastRedirectionDevice, LocalConnectionStateType localConnectionInfo, EventCauseType cause, SAFEARRAY * * manufacturerOID, SAFEARRAY * * privateData)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[9];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				pvars[8] = establishedConnection;
				pvars[7] = answeredDevice;
				pvars[6] = callingDevice;
				pvars[5] = calledDevice;
				pvars[4] = lastRedirectionDevice;
				pvars[3] = localConnectionInfo;
				pvars[2] = cause;
				pvars[1] = ToVariant( manufacturerOID );
				pvars[0] = ToVariant( privateData );
				DISPPARAMS disp = { pvars, NULL, 9, 0 };
				pDispatch->Invoke(0x6, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
		}
		delete[] pvars;
	
	}
	VOID Fire_OnFailed(BSTR failedConnection, BSTR failingDevice, BSTR calledDevice, LocalConnectionStateType localConnectionInfo, EventCauseType cause, SAFEARRAY * * manufacturerOID, SAFEARRAY * * privateData)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[7];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				pvars[6] = failedConnection;
				pvars[5] = failingDevice;
				pvars[4] = calledDevice;
				pvars[3] = localConnectionInfo;
				pvars[2] = cause;
				pvars[1] = ToVariant( manufacturerOID );
				pvars[0] = ToVariant( privateData );
				DISPPARAMS disp = { pvars, NULL, 7, 0 };
				pDispatch->Invoke(0x7, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
		}
		delete[] pvars;
	
	}
	VOID Fire_OnHeld(BSTR heldConnection, BSTR holdingDevice, LocalConnectionStateType localConnectionInfo, EventCauseType cause, SAFEARRAY * * manufacturerOID, SAFEARRAY * * privateData)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[6];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				pvars[5] = heldConnection;
				pvars[4] = holdingDevice;
				pvars[3] = localConnectionInfo;
				pvars[2] = cause;
				pvars[1] = ToVariant( manufacturerOID );
				pvars[0] = ToVariant( privateData );
				DISPPARAMS disp = { pvars, NULL, 6, 0 };
				pDispatch->Invoke(0x8, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
		}
		delete[] pvars;
	
	}
	VOID Fire_OnNetworkReached(BSTR connection, BSTR trunkUsed, BSTR calledDevice, LocalConnectionStateType localConnectionInfo, EventCauseType cause, SAFEARRAY * * manufacturerOID, SAFEARRAY * * privateData)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[7];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				pvars[6] = connection;
				pvars[5] = trunkUsed;
				pvars[4] = calledDevice;
				pvars[3] = localConnectionInfo;
				pvars[2] = cause;
				pvars[1] = ToVariant( manufacturerOID );
				pvars[0] = ToVariant( privateData );
				DISPPARAMS disp = { pvars, NULL, 7, 0 };
				pDispatch->Invoke(0x9, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
		}
		delete[] pvars;
	
	}
	VOID Fire_OnOriginated(BSTR originatingConnection, BSTR callingDevice, BSTR calledDevice, LocalConnectionStateType localConnectionInfo, EventCauseType cause, SAFEARRAY * * manufacturerOID, SAFEARRAY * * privateData)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[7];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				pvars[6] = originatingConnection;
				pvars[5] = callingDevice;
				pvars[4] = calledDevice;
				pvars[3] = localConnectionInfo;
				pvars[2] = cause;
				pvars[1] = ToVariant( manufacturerOID );
				pvars[0] = ToVariant( privateData );
				DISPPARAMS disp = { pvars, NULL, 7, 0 };
				pDispatch->Invoke(0xa, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
		}
		delete[] pvars;
	
	}
	VOID Fire_OnQueued(BSTR queuedConnection, BSTR queue, BSTR callingDevice, BSTR calledDevice, BSTR lastRedirectionDevice, LONG numberedQueued, LocalConnectionStateType localConnectionInfo, EventCauseType cause, SAFEARRAY * * manufacturerOID, SAFEARRAY * * privateData)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[10];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				pvars[9] = queuedConnection;
				pvars[8] = queue;
				pvars[7] = callingDevice;
				pvars[6] = calledDevice;
				pvars[5] = lastRedirectionDevice;
				pvars[4] = numberedQueued;
				pvars[3] = localConnectionInfo;
				pvars[2] = cause;
				pvars[1] = ToVariant( manufacturerOID );
				pvars[0] = ToVariant( privateData );
				DISPPARAMS disp = { pvars, NULL, 10, 0 };
				pDispatch->Invoke(0xb, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
		}
		delete[] pvars;
	
	}
	VOID Fire_OnRetrieved(BSTR retrievedConnection, BSTR retrievingDevice, LocalConnectionStateType localConnectionInfo, EventCauseType cause, SAFEARRAY * * manufacturerOID, SAFEARRAY * * privateData)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[6];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				pvars[5] = retrievedConnection;
				pvars[4] = retrievingDevice;
				pvars[3] = localConnectionInfo;
				pvars[2] = cause;
				pvars[1] = ToVariant( manufacturerOID );
				pvars[0] = ToVariant( privateData );
				DISPPARAMS disp = { pvars, NULL, 6, 0 };
				pDispatch->Invoke(0xc, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
		}
		delete[] pvars;
	
	}
	VOID Fire_OnServiceInitiated(BSTR initiatedConnection, LocalConnectionStateType localConnectionInfo, EventCauseType cause, SAFEARRAY * * manufacturerOID, SAFEARRAY * * privateData)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[5];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				pvars[4] = initiatedConnection;
				pvars[3] = localConnectionInfo;
				pvars[2] = cause;
				pvars[1] = ToVariant( manufacturerOID );
				pvars[0] = ToVariant( privateData );
				DISPPARAMS disp = { pvars, NULL, 5, 0 };
				pDispatch->Invoke(0xd, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
		}
		delete[] pvars;
	
	}
	VOID Fire_OnTransferred(BSTR primaryOldCall, BSTR secondaryOldCall, BSTR transferringDevice, BSTR transferredDevice, BSTR transferredConnections, LocalConnectionStateType localConnectionInfo, EventCauseType cause, SAFEARRAY * * manufacturerOID, SAFEARRAY * * privateData)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[9];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				pvars[8] = primaryOldCall;
				pvars[7] = secondaryOldCall;
				pvars[6] = transferringDevice;
				pvars[5] = transferredDevice;
				pvars[4] = transferredConnections;
				pvars[3] = localConnectionInfo;
				pvars[2] = cause;
				pvars[1] = ToVariant( manufacturerOID );
				pvars[0] = ToVariant( privateData );
				DISPPARAMS disp = { pvars, NULL, 9, 0 };
				pDispatch->Invoke(0xe, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
		}
		delete[] pvars;
	
	}
	VOID Fire_OnOutOfService(BSTR device, EventCauseType cause, SAFEARRAY * * manufacturerOID, SAFEARRAY * * privateData)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[4];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				pvars[3] = device;
				pvars[2] = cause;
				pvars[1] = ToVariant( manufacturerOID );
				pvars[0] = ToVariant( privateData );
				DISPPARAMS disp = { pvars, NULL, 4, 0 };
				pDispatch->Invoke(0xf, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
		}
		delete[] pvars;
	
	}
	VOID Fire_OnBackInService(BSTR device, EventCauseType cause, SAFEARRAY * * manufacturerOID, SAFEARRAY * * privateData)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[4];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				pvars[3] = device;
				pvars[2] = cause;
				pvars[1] = ToVariant( manufacturerOID );
				pvars[0] = ToVariant( privateData );
				DISPPARAMS disp = { pvars, NULL, 4, 0 };
				pDispatch->Invoke(0x10, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
		}
		delete[] pvars;
	
	}
	VOID Fire_OnSystemStatus(SystemStatusType status, SAFEARRAY * * manufacturerOID, SAFEARRAY * * privateData)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[3];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				pvars[2] = status;
				pvars[1] = ToVariant( manufacturerOID );
				pvars[0] = ToVariant( privateData );
				DISPPARAMS disp = { pvars, NULL, 3, 0 };
				pDispatch->Invoke(0x11, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
		}
		delete[] pvars;
	
	}
	VOID Fire_OnLoggedOn(BSTR agentDevice, BSTR agentID, BSTR agentGroup, BSTR agentPassword, SAFEARRAY * * manufacturerOID, SAFEARRAY * * privateData)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[6];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				pvars[5] = agentDevice;
				pvars[4] = agentID;
				pvars[3] = agentGroup;
				pvars[2] = agentPassword;
				pvars[1] = ToVariant( manufacturerOID );
				pvars[0] = ToVariant( privateData );
				DISPPARAMS disp = { pvars, NULL, 6, 0 };
				pDispatch->Invoke(0x12, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
		}
		delete[] pvars;
	
	}
	VOID Fire_OnLoggedOff(BSTR agentDevice, BSTR agentID, BSTR agentGroup, SAFEARRAY * * manufacturerOID, SAFEARRAY * * privateData)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[5];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				pvars[4] = agentDevice;
				pvars[3] = agentID;
				pvars[2] = agentGroup;
				pvars[1] = ToVariant( manufacturerOID );
				pvars[0] = ToVariant( privateData );
				DISPPARAMS disp = { pvars, NULL, 5, 0 };
				pDispatch->Invoke(0x13, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
		}
		delete[] pvars;
	
	}
	VOID Fire_OnNotReady(BSTR agentDevice, BSTR agentID, SAFEARRAY * * manufacturerOID, SAFEARRAY * * privateData)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[4];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				pvars[3] = agentDevice;
				pvars[2] = agentID;
				pvars[1] = ToVariant( manufacturerOID );
				pvars[0] = ToVariant( privateData );
				DISPPARAMS disp = { pvars, NULL, 4, 0 };
				pDispatch->Invoke(0x14, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
		}
		delete[] pvars;
	
	}
	VOID Fire_OnReady(BSTR agentDevice, BSTR agentID, SAFEARRAY * * manufacturerOID, SAFEARRAY * * privateData)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[4];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				pvars[3] = agentDevice;
				pvars[2] = agentID;
				pvars[1] = ToVariant( manufacturerOID );
				pvars[0] = ToVariant( privateData );
				DISPPARAMS disp = { pvars, NULL, 4, 0 };
				pDispatch->Invoke(0x15, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
		}
		delete[] pvars;
	
	}
	VOID Fire_OnWorkNotReady(BSTR agentDevice, BSTR agentID, SAFEARRAY * * manufacturerOID, SAFEARRAY * * privateData)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[4];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				pvars[3] = agentDevice;
				pvars[2] = agentID;
				pvars[1] = ToVariant( manufacturerOID );
				pvars[0] = ToVariant( privateData );
				DISPPARAMS disp = { pvars, NULL, 4, 0 };
				pDispatch->Invoke(0x16, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
		}
		delete[] pvars;
	
	}
	VOID Fire_OnWorkReady(BSTR agentDevice, BSTR agentID, SAFEARRAY * * manufacturerOID, SAFEARRAY * * privateData)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[4];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				pvars[3] = agentDevice;
				pvars[2] = agentID;
				pvars[1] = ToVariant( manufacturerOID );
				pvars[0] = ToVariant( privateData );
				DISPPARAMS disp = { pvars, NULL, 4, 0 };
				pDispatch->Invoke(0x17, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
		}
		delete[] pvars;
	
	}
	VOID Fire_OnCallInformation(BSTR connection, BSTR device, BSTR accountInfo, BSTR authorisationCode, SAFEARRAY * * manufacturerOID, SAFEARRAY * * privateData)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[6];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				pvars[5] = connection;
				pvars[4] = device;
				pvars[3] = accountInfo;
				pvars[2] = authorisationCode;
				pvars[1] = ToVariant( manufacturerOID );
				pvars[0] = ToVariant( privateData );
				DISPPARAMS disp = { pvars, NULL, 6, 0 };
				pDispatch->Invoke(0x18, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
		}
		delete[] pvars;
	
	}
	VOID Fire_OnDoNotDisturb(BSTR device, LONG doNotDisturbFlag, SAFEARRAY * * manufacturerOID, SAFEARRAY * * privateData)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[4];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				pvars[3] = device;
				pvars[2] = doNotDisturbFlag;
				pvars[1] = ToVariant( manufacturerOID );
				pvars[0] = ToVariant( privateData );
				DISPPARAMS disp = { pvars, NULL, 4, 0 };
				pDispatch->Invoke(0x19, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
		}
		delete[] pvars;
	
	}
	VOID Fire_OnForwarding(BSTR device, ForwardingType type, BSTR forwardDN, BSTR forwardedTo, SAFEARRAY * * manufacturerOID, SAFEARRAY * * privateData)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[6];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				pvars[5] = device;
				pvars[4] = type;
				pvars[3] = forwardDN;
				pvars[2] = forwardedTo;
				pvars[1] = ToVariant( manufacturerOID );
				pvars[0] = ToVariant( privateData );
				DISPPARAMS disp = { pvars, NULL, 6, 0 };
				pDispatch->Invoke(0x1a, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
		}
		delete[] pvars;
	
	}
	VOID Fire_OnMessageWaiting(BSTR deviceForMessage, BSTR invokingDevice, LONG messageWaitingFlag, SAFEARRAY * * manufacturerOID, SAFEARRAY * * privateData)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[5];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				pvars[4] = deviceForMessage;
				pvars[3] = invokingDevice;
				pvars[2] = messageWaitingFlag;
				pvars[1] = ToVariant( manufacturerOID );
				pvars[0] = ToVariant( privateData );
				DISPPARAMS disp = { pvars, NULL, 5, 0 };
				pDispatch->Invoke(0x1b, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
		}
		delete[] pvars;
	
	}
	VOID Fire_OnPrivateEvent(SAFEARRAY * * data)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[1];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				pvars[0] = ToVariant( data );
				DISPPARAMS disp = { pvars, NULL, 1, 0 };
				pDispatch->Invoke(0x1c, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
		}
		delete[] pvars;
	
	}
	VOID Fire_OnMonitorStarted(ErrorCode errCode)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[1];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				pvars[0] = errCode;
				DISPPARAMS disp = { pvars, NULL, 1, 0 };
				pDispatch->Invoke(0x1d, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
			}
		}
		delete[] pvars;
	
	}
};
#endif // _CTNGCP_H_INCLUDED