/*
    Project: CTNG COM ATL

    Module: Device.cpp

    Description: Implementation of CDevice

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "stdafx.h"
#include "CTNG.h"
#include "Device.h"

/////////////////////////////////////////////////////////////////////////////
// CDevice

STDMETHODIMP CDevice::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IDevice
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
        // if ( ::ATL::InlineIsEqualGUID(*arr[i],riid))
        if ( InlineIsEqualGUID(*arr[i],riid) )
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CDevice::Open( BSTR pabxID, BSTR deviceID, ErrorCode* errCode )
{
    *errCode = CTNG_NO_ERROR;

    if ( ! pabxID )
    {
        *errCode = CSTA_INVALID_PABX_ID;
        return S_OK;
        }

    if ( ! deviceID )
    {
        *errCode = CSTA_INVALID_DEVICE_ID;
        return S_OK;
        }

    dev = NULL;
    cbProc = NULL;

    cbProc = new CDevice_CB_Proc( this );

    *errCode = cstaSys.OpenDevice( cbProc, USTR( pabxID ), USTR( deviceID ) );

    if ( *errCode == CTNG_NO_ERROR )
        dev = cbProc->GetDev ();
    else
        cbProc = NULL;

    return S_OK;
}

STDMETHODIMP CDevice::Close( ErrorCode* errCode )
{
    *errCode = CTNG_NO_ERROR;

    TRACE( this << " CDevice::Close" );
    dev = NULL;
    cbProc = NULL;

	return S_OK;
}

STDMETHODIMP CDevice::TestFireAllEvents( void )
{
    if ( ! cbProc || ! dev )
        return S_OK;

    dev->TestFireAllEvents ();

    return S_OK;
    }

STDMETHODIMP CDevice::PutExtension( VARIANT* outOID, VARIANT* outData )
{
    if ( ! cbProc || ! dev )
    {
        return S_OK;
        }

    // Get only if outOID is SafeArray of Bytes
    if ( outOID && ( outOID->vt & ( VT_BYREF | VT_ARRAY | VT_UI1 ) ) == ( VT_BYREF | VT_ARRAY | VT_UI1 ) )
        ext.outOID = *outOID->pparray;
    else if ( outOID && ( outOID->vt & ( VT_ARRAY | VT_UI1 ) ) == ( VT_ARRAY | VT_UI1 ) )
        ext.outOID = outOID->parray;
    else
        ext.outOID.SetNULL ();

    // Get only if outData is ByRef Array of Bytes
    if ( outData && ( outData->vt & ( VT_BYREF | VT_ARRAY | VT_UI1 ) ) == ( VT_BYREF | VT_ARRAY | VT_UI1 ) )
        ext.outData = *outData->pparray;
    else if ( outData && ( outData->vt & ( VT_ARRAY | VT_UI1 ) ) == ( VT_ARRAY | VT_UI1 ) )
        ext.outData = outData->parray;
    else
        ext.outData.SetNULL ();

    return S_OK;
    }

STDMETHODIMP CDevice::GetExtension( SAFEARRAY** inOID, SAFEARRAY** inData )
{
    if ( ! cbProc || ! dev )
    {
        return S_OK;
        }

    *inOID = ext.inOID.CreateSafeByteArray ();
    *inData = ext.inData.CreateSafeByteArray ();

    return S_OK;
    }

STDMETHODIMP CDevice::SystemStatus( SystemStatusType status, ErrorCode* errCode )
{
    *errCode = CTNG_NO_ERROR;

    if ( ! cbProc || ! dev )
    {
        *errCode = CSTA_INVALID_DEVICE_ID;
        return S_OK;
        }

    *errCode = dev->SystemStatus( status, &ext );

    ext.outOID.SetNULL ();
    ext.outData.SetNULL ();

	return S_OK;
}

STDMETHODIMP CDevice::EscapeService( VARIANT* outOID, VARIANT* outData, SAFEARRAY** inOID, SAFEARRAY** inData, ErrorCode* errCode)
{
    *errCode = CTNG_NO_ERROR;

    if ( ! cbProc || ! dev )
    {
        *errCode = CSTA_INVALID_DEVICE_ID;
        return S_OK;
        }

    // Get only if outOID is ByRef Array of Bytes
    if ( outOID && ( outOID->vt & ( VT_BYREF | VT_ARRAY | VT_UI1 ) ) == ( VT_BYREF | VT_ARRAY | VT_UI1 ) )
        ext.outOID = *outOID->pparray;
    else
        ext.outOID.SetNULL ();

    // Get only if outData is ByRef Array of Bytes
    if ( outData && ( outData->vt & ( VT_BYREF | VT_ARRAY | VT_UI1 ) ) == ( VT_BYREF | VT_ARRAY | VT_UI1 ) )
        ext.outData = *outData->pparray;
    else
        ext.outData.SetNULL ();

    *errCode = dev->EscapeService( ext );

    *inOID = ext.inOID.CreateSafeByteArray ();
    *inData = ext.inData.CreateSafeByteArray ();

    // Reset sent values after usage
    ext.outOID.SetNULL ();
    ext.outData.SetNULL ();

    // return ResultFromScode( E_OUTOFMEMORY );

	return S_OK;
    }

STDMETHODIMP CDevice::AlternateCall( BSTR heldCall, BSTR activeCall, ErrorCode* errCode )
{
    *errCode = CTNG_NO_ERROR;

    if ( ! cbProc || ! dev )
    {
        *errCode = CSTA_INVALID_DEVICE_ID;
        return S_OK;
        }

    MidCSTA::connectionIdType held = heldCall;
    MidCSTA::connectionIdType active = activeCall;

    *errCode = dev->AlternateCall( held, active, &ext );

    ext.outOID.SetNULL ();
    ext.outData.SetNULL ();

	return S_OK;
}

STDMETHODIMP CDevice::AnswerCall( BSTR connectionId, ErrorCode* errCode )
{
    *errCode = CTNG_NO_ERROR;

    if ( ! cbProc || ! dev )
    {
        *errCode = CSTA_INVALID_DEVICE_ID;
        return S_OK;
        }

    MidCSTA::connectionIdType conn_id = connectionId;
    *errCode = dev->AnswerCall( conn_id, &ext );

    ext.outOID.SetNULL ();
    ext.outData.SetNULL ();

	return S_OK;
}

STDMETHODIMP CDevice::CallCompletion( BSTR connectionId, FeatureInfoType feature, ErrorCode* errCode )
{
    *errCode = CTNG_NO_ERROR;

    if ( ! cbProc || ! dev )
    {
        *errCode = CSTA_INVALID_DEVICE_ID;
        return S_OK;
        }

    MidCSTA::connectionIdType conn_id = connectionId;
    *errCode = dev->CallCompletion( conn_id, feature, &ext );

    ext.outOID.SetNULL ();
    ext.outData.SetNULL ();

	return S_OK;
}

STDMETHODIMP CDevice::ClearCall( BSTR callToBeCleared, ErrorCode* errCode )
{
    *errCode = CTNG_NO_ERROR;

    if ( ! cbProc || ! dev )
    {
        *errCode = CSTA_INVALID_DEVICE_ID;
        return S_OK;
        }

    if ( ! callToBeCleared )
    {
        *errCode = CSTA_INVALID_CONNECTION_ID;
        return S_OK;
        }

    MidCSTA::connectionIdType call_id = callToBeCleared;
    *errCode = dev->ClearCall( call_id, &ext );

    ext.outOID.SetNULL ();
    ext.outData.SetNULL ();

	return S_OK;
}

STDMETHODIMP CDevice::ClearConnection( BSTR connectionId, ErrorCode* errCode )
{
    *errCode = CTNG_NO_ERROR;

    if ( ! cbProc || ! dev )
    {
        *errCode = CSTA_INVALID_DEVICE_ID;
        return S_OK;
        }

    if ( ! connectionId )
    {
        *errCode = CSTA_INVALID_CONNECTION_ID;
        return S_OK;
        }

    MidCSTA::connectionIdType conn_id = connectionId;
    *errCode = dev->ClearConnection( conn_id, &ext );

    ext.outOID.SetNULL ();
    ext.outData.SetNULL ();

	return S_OK;
}

STDMETHODIMP CDevice::ConferenceCall( BSTR heldCall, BSTR activeCall, VARIANT* connectionId, ErrorCode* errCode )
{
    *errCode = CTNG_NO_ERROR;

    if ( ! cbProc || ! dev )
    {
        *errCode = CSTA_INVALID_DEVICE_ID;
        return S_OK;
        }

    MidCSTA::connectionIdType held = heldCall;
    MidCSTA::connectionIdType active = activeCall;
    MidCSTA::connectionIdType connResult;

    *errCode = dev->ConferenceCall( held, active, connResult, &ext );

    *connectionId = CComVariant( CComBSTR( USTR( connResult ) ) );

    ext.outOID.SetNULL ();
    ext.outData.SetNULL ();

	return S_OK;
}

STDMETHODIMP CDevice::ConsultationCall( BSTR existingCall, BSTR calledDirectoryNumber, VARIANT* connectionId, ErrorCode* errCode )
{
    *errCode = CTNG_NO_ERROR;

    if ( ! cbProc || ! dev )
    {
        *errCode = CSTA_INVALID_DEVICE_ID;
        return S_OK;
        }

    MidCSTA::connectionIdType conn;
    *errCode = dev->ConsultationCall( USTR( existingCall ), USTR( calledDirectoryNumber ), conn, &ext );

    *connectionId = CComVariant( CComBSTR( USTR( conn ) ) );

    ext.outOID.SetNULL ();
    ext.outData.SetNULL ();

	return S_OK;
}

STDMETHODIMP CDevice::DivertCall_Deflect( BSTR connectionId, BSTR newDestination, ErrorCode* errCode )
{
    *errCode = CTNG_NO_ERROR;

    if ( ! cbProc || ! dev )
    {
        *errCode = CSTA_INVALID_DEVICE_ID;
        return S_OK;
        }

    MidCSTA::connectionIdType conn_id = connectionId;
    *errCode = dev->DivertCall_Deflect( conn_id, USTR( newDestination ), &ext );

    ext.outOID.SetNULL ();
    ext.outData.SetNULL ();

	return S_OK;
}

STDMETHODIMP CDevice::DivertCall_DirectedPickup( BSTR connectionId, BSTR requestingDevice, ErrorCode* errCode )
{
    *errCode = CTNG_NO_ERROR;

    if ( ! cbProc || ! dev )
    {
        *errCode = CSTA_INVALID_DEVICE_ID;
        return S_OK;
        }

    MidCSTA::connectionIdType conn_id = connectionId;
    *errCode = dev->DivertCall_DirectedPickup( conn_id, USTR( requestingDevice ), &ext );

    ext.outOID.SetNULL ();
    ext.outData.SetNULL ();

	return S_OK;
}

STDMETHODIMP CDevice::DivertCall_GroupPickup( BSTR groupDevice, ErrorCode* errCode )
{
    *errCode = CTNG_NO_ERROR;

    if ( ! cbProc || ! dev )
    {
        *errCode = CSTA_INVALID_DEVICE_ID;
        return S_OK;
        }

    *errCode = dev->DivertCall_GroupPickup( USTR( groupDevice ), &ext );

    ext.outOID.SetNULL ();
    ext.outData.SetNULL ();

	return S_OK;
}

STDMETHODIMP CDevice::HoldCall( BSTR connectionId, BOOL reserveConnection, ErrorCode* errCode )
{
    *errCode = CTNG_NO_ERROR;

    if ( ! cbProc || ! dev )
    {
        *errCode = CSTA_INVALID_DEVICE_ID;
        return S_OK;
        }

    MidCSTA::connectionIdType conn_id = connectionId;
    *errCode = dev->HoldCall( conn_id, ( reserveConnection != 0 ), &ext );

    ext.outOID.SetNULL ();
    ext.outData.SetNULL ();

	return S_OK;
}

STDMETHODIMP CDevice::MakeCall( BSTR deviceToCall, VARIANT* connectionId, ErrorCode* errCode )
{
    *errCode = CTNG_NO_ERROR;

    if ( ! cbProc || ! dev )
    {
        *errCode = CSTA_INVALID_DEVICE_ID;
        return S_OK;
        }

    MidCSTA::connectionIdType connResult;
    *errCode = dev->MakeCall( USTR( deviceToCall ), connResult, &ext );

    *connectionId = CComVariant( CComBSTR( USTR( connResult ) ) );

    ext.outOID.SetNULL ();
    ext.outData.SetNULL ();

	return S_OK;
}

STDMETHODIMP CDevice::MakePredictiveCall( BSTR calledDirectoryNumber, VARIANT* connectionId, ErrorCode* errCode )
{
    *errCode = CSTA_NOT_IMPLEMENTED;

    ext.outOID.SetNULL ();
    ext.outData.SetNULL ();

	return S_OK;
}

STDMETHODIMP CDevice::ReconnectCall( BSTR heldCall, BSTR activeCall, ErrorCode* errCode )
{
    *errCode = CTNG_NO_ERROR;

    if ( ! cbProc || ! dev )
    {
        *errCode = CSTA_INVALID_DEVICE_ID;
        return S_OK;
        }

    MidCSTA::connectionIdType held = heldCall;
    MidCSTA::connectionIdType active = activeCall;

    *errCode = dev->ReconnectCall( held, active, &ext );

    ext.outOID.SetNULL ();
    ext.outData.SetNULL ();

	return S_OK;
}

STDMETHODIMP CDevice::RetrieveCall( BSTR connectionId, ErrorCode* errCode )
{
    *errCode = CTNG_NO_ERROR;

    if ( ! cbProc || ! dev )
    {
        *errCode = CSTA_INVALID_DEVICE_ID;
        return S_OK;
        }

    MidCSTA::connectionIdType conn_id = connectionId;
    *errCode = dev->RetrieveCall( conn_id, &ext );

    ext.outOID.SetNULL ();
    ext.outData.SetNULL ();

	return S_OK;
}

STDMETHODIMP CDevice::TransferCall( BSTR heldCall, BSTR activeCall, VARIANT* connectionId, ErrorCode* errCode )
{
    *errCode = CTNG_NO_ERROR;

    if ( ! cbProc || ! dev )
    {
        *errCode = CSTA_INVALID_DEVICE_ID;
        return S_OK;
        }

    MidCSTA::connectionIdType held = heldCall;
    MidCSTA::connectionIdType active = activeCall;
    MidCSTA::connectionIdType connResult;

    *errCode = dev->TransferCall( held, active, connResult, &ext );

    *connectionId = CComVariant( CComBSTR( USTR( connResult ) ) );

    ext.outOID.SetNULL ();
    ext.outData.SetNULL ();

	return S_OK;
}

STDMETHODIMP CDevice::QueryDevice_MessageWaiting( BOOL* indicator,  ErrorCode* errCode )
{
    *errCode = CTNG_NO_ERROR;

    if ( ! cbProc || ! dev )
    {
        *errCode = CSTA_INVALID_DEVICE_ID;
        return S_OK;
        }

    bool value;
    *errCode = dev->QueryDevice_MessageWaiting( value, &ext );

    *indicator = value;

    ext.outOID.SetNULL ();
    ext.outData.SetNULL ();

	return S_OK;
    }

STDMETHODIMP CDevice::QueryDevice_DoNotDisturb( BOOL* indicator,  ErrorCode* errCode )
{
    *errCode = CTNG_NO_ERROR;

    if ( ! cbProc || ! dev )
    {
        *errCode = CSTA_INVALID_DEVICE_ID;
        return S_OK;
        }

    bool value;
    *errCode = dev->QueryDevice_DoNotDisturb( value, &ext );

    *indicator = value;

    ext.outOID.SetNULL ();
    ext.outData.SetNULL ();

	return S_OK;
    }

STDMETHODIMP CDevice::QueryDevice_Forward( VARIANT* forwardInfo,  ErrorCode* errCode )
{
    *errCode = CTNG_NO_ERROR;

    if ( ! cbProc || ! dev )
    {
        *errCode = CSTA_INVALID_DEVICE_ID;
        return S_OK;
        }

    USTR value;
    *errCode = dev->QueryDevice_Forward( value, &ext );

    *forwardInfo = CComVariant( CComBSTR( value ) );

    ext.outOID.SetNULL ();
    ext.outData.SetNULL ();

	return S_OK;
    }

STDMETHODIMP CDevice::QueryDevice_DeviceInfo( DeviceClassType* devClass,  DeviceTypeType* devType,  ErrorCode* errCode )
{
    *errCode = CTNG_NO_ERROR;

    if ( ! cbProc || ! dev )
    {
        *errCode = CSTA_INVALID_DEVICE_ID;
        return S_OK;
        }

    DeviceClassType cls;
    DeviceTypeType typ;
    *errCode = dev->QueryDevice_DeviceInfo( cls, typ, &ext );

    *devClass = cls;
    *devType = typ;

    ext.outOID.SetNULL ();
    ext.outData.SetNULL ();

    return S_OK;
    }

STDMETHODIMP CDevice::QueryDevice_AgentState( AgentStateType* agentState,  ErrorCode* errCode )
{
    *errCode = CTNG_NO_ERROR;

    if ( ! cbProc || ! dev )
    {
        *errCode = CSTA_INVALID_DEVICE_ID;
        return S_OK;
        }

    AgentStateType state;
    *errCode = dev->QueryDevice_AgentState( state, &ext );

    *agentState = state;

    ext.outOID.SetNULL ();
    ext.outData.SetNULL ();

    return S_OK;
    }

STDMETHODIMP CDevice::SetFature_MessageWaiting( BOOL indicator,  ErrorCode* errCode )
{
    *errCode = CTNG_NO_ERROR;

    if ( ! cbProc || ! dev )
    {
        *errCode = CSTA_INVALID_DEVICE_ID;
        return S_OK;
        }

    *errCode = dev->SetFeature_MessageWaiting( indicator != 0, &ext );

    ext.outOID.SetNULL ();
    ext.outData.SetNULL ();

	return S_OK;
    }

STDMETHODIMP CDevice::SetFature_DoNotDisturb( BOOL indicator,  ErrorCode* errCode )
{
    *errCode = CTNG_NO_ERROR;

    if ( ! cbProc || ! dev )
    {
        *errCode = CSTA_INVALID_DEVICE_ID;
        return S_OK;
        }

    *errCode = dev->SetFeature_DoNotDisturb( indicator != 0, &ext );

    ext.outOID.SetNULL ();
    ext.outData.SetNULL ();

	return S_OK;
    }

STDMETHODIMP CDevice::SetFature_Forward( ForwardingType forwardingType,  BSTR forwardDN,  ErrorCode* errCode )
{
    *errCode = CTNG_NO_ERROR;

    if ( ! cbProc || ! dev )
    {
        *errCode = CSTA_INVALID_DEVICE_ID;
        return S_OK;
        }

    *errCode = dev->SetFeature_Forward( forwardingType, USTR( forwardDN ), &ext );

    ext.outOID.SetNULL ();
    ext.outData.SetNULL ();

	return S_OK;
    }

STDMETHODIMP CDevice::SetFature_RequestAgentState( AgentParameterType state,  BSTR agentID,  BSTR agentGroup,  BSTR agentPassword, ErrorCode* errCode )
{
    *errCode = CTNG_NO_ERROR;

    if ( ! cbProc || ! dev )
    {
        *errCode = CSTA_INVALID_DEVICE_ID;
        return S_OK;
        }

    *errCode = dev->SetFeature_RequestAgentState( state, USTR( agentID ), USTR( agentGroup ), USTR( agentPassword ), &ext );

    ext.outOID.SetNULL ();
    ext.outData.SetNULL ();

	return S_OK;
    }

STDMETHODIMP CDevice::WaitOpen( double timeoutSeconds, ErrorCode* errCode )
{
    *errCode = CTNG_NO_ERROR;

    if ( ! cbProc || ! dev )
    {
        *errCode = CSTA_INVALID_DEVICE_ID;
        return S_OK;
        }
/*
    if ( dev->IsMonitorStarted () )
        *errCode = CTNG_NO_ERROR;
    else
        *errCode = CSTA_NOT_CONNECTED;

    return S_OK;

    // Poll 'is monitor started' status each 100ms, up to the given
    // timeout 'timeoutSeconds'.
    //
    while( ! dev->IsMonitorStarted () && timeoutSeconds >= 0 )
    {
        if ( timeoutSeconds < 0.1 )
        {
            ::Sleep( DWORD( timeoutSeconds * 1000 ) );
            timeoutSeconds = -1;
            }
        else
        {
            ::Sleep( 100 );
            timeoutSeconds -= 0.1;
            }
        }

    if ( timeoutSeconds < 0 ) // there was timeout
        *errCode = CSTA_ERROR_TIMEOUT;
*/
	return S_OK;
    }
