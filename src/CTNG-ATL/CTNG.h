

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Sat May 10 02:16:40 2003
 */
/* Compiler settings for D:\Documents and Settings\Administrator\Desktop\CTNG Project Repository\02. Source Code\CTNG ATL\CTNG.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __CTNG_h__
#define __CTNG_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ISystem_FWD_DEFINED__
#define __ISystem_FWD_DEFINED__
typedef interface ISystem ISystem;
#endif 	/* __ISystem_FWD_DEFINED__ */


#ifndef ___ISystemEvents_FWD_DEFINED__
#define ___ISystemEvents_FWD_DEFINED__
typedef interface _ISystemEvents _ISystemEvents;
#endif 	/* ___ISystemEvents_FWD_DEFINED__ */


#ifndef __System_FWD_DEFINED__
#define __System_FWD_DEFINED__

#ifdef __cplusplus
typedef class System System;
#else
typedef struct System System;
#endif /* __cplusplus */

#endif 	/* __System_FWD_DEFINED__ */


#ifndef __IPABX_FWD_DEFINED__
#define __IPABX_FWD_DEFINED__
typedef interface IPABX IPABX;
#endif 	/* __IPABX_FWD_DEFINED__ */


#ifndef ___IPABXEvents_FWD_DEFINED__
#define ___IPABXEvents_FWD_DEFINED__
typedef interface _IPABXEvents _IPABXEvents;
#endif 	/* ___IPABXEvents_FWD_DEFINED__ */


#ifndef __PABX_FWD_DEFINED__
#define __PABX_FWD_DEFINED__

#ifdef __cplusplus
typedef class PABX PABX;
#else
typedef struct PABX PABX;
#endif /* __cplusplus */

#endif 	/* __PABX_FWD_DEFINED__ */


#ifndef __IDevice_FWD_DEFINED__
#define __IDevice_FWD_DEFINED__
typedef interface IDevice IDevice;
#endif 	/* __IDevice_FWD_DEFINED__ */


#ifndef ___IDeviceEvents_FWD_DEFINED__
#define ___IDeviceEvents_FWD_DEFINED__
typedef interface _IDeviceEvents _IDeviceEvents;
#endif 	/* ___IDeviceEvents_FWD_DEFINED__ */


#ifndef __Device_FWD_DEFINED__
#define __Device_FWD_DEFINED__

#ifdef __cplusplus
typedef class Device Device;
#else
typedef struct Device Device;
#endif /* __cplusplus */

#endif 	/* __Device_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __CTNGLib_LIBRARY_DEFINED__
#define __CTNGLib_LIBRARY_DEFINED__

/* library CTNGLib */
/* [helpstring][version][uuid] */ 

#ifndef _CSTA_ENUM_TYPES_H_INCLUDED

enum ErrorClass
    {	CSER_INTERNAL_ERROR	= 0,
	CSER_REJECT_GENERAL_PROBLEM	= 0x100,
	CSER_REJECT_INVOKE_PROBLEM	= 0x200,
	CSER_REJECT_RETURN_RESULT_PROBLEM	= 0x300,
	CSER_REJECT_RETURN_ERROR_PROBLEM	= 0x400,
	CSER_OPERATIONAL_ERROR	= 0x500,
	CSER_STATE_ERROR	= 0x600,
	CSER_SYSTEM_RESOURCE_ERROR	= 0x700,
	CSER_SUBSCRIBED_RESOURCE_AVAILABILITY_ERROR	= 0x800,
	CSER_PERFORMANCE_ERROR	= 0x900,
	CSER_SECURITY_ERROR	= 0xa00,
	CSER_UNSPECIFIED_ERROR	= 0xb00,
	CSER_NON_STANDARD_ERROR	= 0xc00
    } ;

enum ErrorCode
    {	CTNG_NO_ERROR	= 0,
	CSTA_ERROR_CODE_NOT_SET	= 0x1,
	CSTA_ERROR_TIMEOUT	= 0x2,
	CSTA_NOT_CONNECTED	= 0x3,
	CSTA_NOT_IMPLEMENTED	= 0x4,
	CSTA_INVALID_PABX_ID	= 0x5,
	CSTA_INVALID_DEVICE_ID	= 0x6,
	CSTA_INVALID_CONNECTION_ID	= 0x7,
	CSTA_RECEIVED_INVALID_APDU	= 0x8,
	CSTA_MONITOR_NOT_STARTED	= 0x9,
	CSTA_MONITOR_ALREADY_OPEN	= 0xa,
	CTNG_NO_MEMORY	= 0xb,
	CTNG_EXCEPTION_ERROR	= 0xc,
	CTNG_OPEN_CONNECTION_FAILED	= 0xd,
	CTNG_INVALID_POINTER	= 0xe,
	CSTA_DISCONNECTED	= 0xf,
	CTNG_SEND_APDU_FAILED	= 0x10,
	RJGP_unrecognisedAPDU	= 0x100,
	RJGP_mistypedAPDU	= 0x101,
	RJGP_badlyStructuredAPDU	= 0x102,
	RJIP_duplicateInvocation	= 0x200,
	RJIP_unrecognisedOperation	= 0x201,
	RJIP_mistypedArgument	= 0x202,
	RJIP_resourceLimitation	= 0x203,
	RJIP_initiatorReleasing	= 0x204,
	RJIP_unrecognisedLinkedID	= 0x205,
	RJIP_linkedResponseUnexpected	= 0x206,
	RJIP_unexpectedChildOperation	= 0x207,
	RJRRP_unrecognisedInvocation	= 0x300,
	RJRRP_resultResponseUnexpected	= 0x301,
	RJRRP_mistypedResult	= 0x302,
	RJREP_unrecognisedInvocation	= 0x400,
	RJREP_errorResponseUnexpected	= 0x401,
	RJREP_unrecognisedError	= 0x402,
	RJREP_unexpectedError	= 0x403,
	RJREP_mistypedParameter	= 0x404,
	ERUFOP_generic	= 0x501,
	ERUFOP_requestIncompatibleWithObject	= 0x502,
	ERUFOP_valueOutOfRange	= 0x503,
	ERUFOP_objectNotKnown	= 0x504,
	ERUFOP_invalidCallingDevice	= 0x505,
	ERUFOP_invalidCalledDevice	= 0x506,
	ERUFOP_invalidForwardingDestination	= 0x507,
	ERUFOP_privilegeViolationOnSpecifiedDevice	= 0x508,
	ERUFOP_privilegeViolationOnCalledDevice	= 0x509,
	ERUFOP_privilegeViolationOnCallingDevice	= 0x50a,
	ERUFOP_invalidCSTACallIdentifier	= 0x50b,
	ERUFOP_invalidCSTADeviceIdentifier	= 0x50c,
	ERUFOP_invalidCSTAConnectionIdentifier	= 0x50d,
	ERUFOP_invalidDestination	= 0x50e,
	ERUFOP_invalidFeature	= 0x50f,
	ERUFOP_invalidAllocationState	= 0x510,
	ERUFOP_invalidCrossRefID	= 0x511,
	ERUFOP_invalidObjectType	= 0x512,
	ERUFOP_securityViolation	= 0x513,
	ERUFSI_generic	= 0x601,
	ERUFSI_invalidObjectState	= 0x602,
	ERUFSI_invalidConnectionID	= 0x603,
	ERUFSI_noActiveCall	= 0x604,
	ERUFSI_noHeldCall	= 0x605,
	ERUFSI_noCallToClear	= 0x606,
	ERUFSI_noConnectionToClear	= 0x607,
	ERUFSI_noCallToAnswer	= 0x608,
	ERUFSI_noCallToComplete	= 0x609,
	ERUFSYRA_generic	= 0x701,
	ERUFSYRA_serviceBusy	= 0x702,
	ERUFSYRA_resourceBusy	= 0x703,
	ERUFSYRA_resourceOutOfService	= 0x704,
	ERUFSYRA_networkBusy	= 0x705,
	ERUFSYRA_networkOutOfService	= 0x706,
	ERUFSYRA_overallMonitorLimitExceeded	= 0x707,
	ERUFSYRA_conferenceMemberLimitExceeded	= 0x708,
	ERUFSCRA_generic	= 0x801,
	ERUFSCRA_objectMonitorLimitExceeded	= 0x802,
	ERUFSCRA_externalTrunkLimitExceeded	= 0x803,
	ERUFSCRA_outstandingRequestLimitExceeded	= 0x804,
	ERUFPM_generic	= 0x901,
	ERUFPM_performanceLimitExceeded	= 0x902,
	ERUFSE_unspecified	= 0xa00,
	ERUFSE_sequenceNumberViolated	= 0xa01,
	ERUFSE_timeStampViolated	= 0xa02,
	ERUFSE_pACViolated	= 0xa03,
	ERUFSE_sealViolated	= 0xa04,
	ERUFUE_unspecified	= 0xb00,
	ERUFNSE_unspecified	= 0xc00
    } ;

enum SystemStatusType
    {	ss_unknown	= -1,
	ss_initializing	= 0,
	ss_enabled	= 1,
	ss_normal	= 2,
	ss_messagesLost	= 3,
	ss_disabled	= 4,
	ss_overloadImminent	= 5,
	ss_overloadReached	= 6,
	ss_overloadRelieved	= 7
    } ;

enum EventCauseType
    {	ec_unknown	= -1,
	ec_activeMonitor	= 1,
	ec_alternate	= 2,
	ec_busy	= 3,
	ec_callBack	= 4,
	ec_callCancelled	= 5,
	ec_callForwardAlways	= 6,
	ec_callForwardBusy	= 7,
	ec_callForwardNoAnswer	= 8,
	ec_callForward	= 9,
	ec_callNotAnswered	= 10,
	ec_callPickup	= 11,
	ec_campOn	= 12,
	ec_destNotObtainable	= 13,
	ec_doNotDisturb	= 14,
	ec_incompatibleDestination	= 15,
	ec_invalidAccountCode	= 16,
	ec_keyConference	= 17,
	ec_lockout	= 18,
	ec_maintenance	= 19,
	ec_networkCongestion	= 20,
	ec_networkNotObtainable	= 21,
	ec_newCall	= 22,
	ec_noAvailableAgents	= 23,
	ec_override	= 24,
	ec_park	= 25,
	ec_overflow	= 26,
	ec_recall	= 27,
	ec_redirected	= 28,
	ec_reorderTone	= 29,
	ec_resourcesNotAvailable	= 30,
	ec_silentParticipation	= 31,
	ec_transfer	= 32,
	ec_trunksBusy	= 33,
	ec_voiceUnitInitiator	= 34
    } ;

enum LocalConnectionStateType
    {	lcs_unknown	= -1,
	lcs_null	= 0,
	lcs_initiated	= 1,
	lcs_alerting	= 2,
	lcs_connected	= 3,
	lcs_hold	= 4,
	lcs_queued	= 5,
	lcs_fail	= 6
    } ;

enum FeatureInfoType
    {	fi_unknown	= -1,
	fi_campon	= 0,
	fi_callback	= 1,
	fi_intrude	= 2,
	fi_callbackMessage	= 3
    } ;

enum QueryDeviceFeatureType
    {	qdf_unknown	= -1,
	qdf_msgWaitingOn	= 0,
	qdf_doNotDisturbOn	= 1,
	qdf_forward	= 2,
	qdf_lastDialedNumber	= 3,
	qdf_deviceInfo	= 4,
	qdf_agentState	= 5,
	qdf_routingEnabled	= 6,
	qdf_autoAnswer	= 7,
	qdf_microphoneMuteOn	= 8,
	qdf_speakerMuteOn	= 9,
	qdf_speakerVolume	= 10
    } ;

enum ForwardingType
    {	ft_unknown	= -1,
	ft_forwardImmediateOn	= 0,
	ft_forwardImmediateOff	= 1,
	ft_forwardBusyOn	= 2,
	ft_forwardBusyOff	= 3,
	ft_forwardNoAnsOn	= 4,
	ft_forwardNoAnsOff	= 5,
	ft_forwardBusyIntOn	= 6,
	ft_forwardBusyIntOff	= 7,
	ft_forwardBusyExtOn	= 8,
	ft_forwardBusyExtOff	= 9,
	ft_forwardNoAnsIntOn	= 10,
	ft_forwardNoAnsIntOff	= 11,
	ft_forwardNoAnsExtOn	= 12,
	ft_forwardNoAnsExtOff	= 13
    } ;

enum AgentStateType
    {	ast_unknown	= -1,
	ast_notReady	= 0,
	ast_null	= 1,
	ast_ready	= 2,
	ast_workNotReady	= 3,
	ast_workReady	= 4
    } ;

enum AgentParameterType
    {	apt_unknown	= -1,
	apt_loggedIn	= 0,
	apt_loggedOut	= 1,
	apt_notReady	= 2,
	apt_ready	= 3,
	apt_workNotReady	= 4,
	apt_workReady	= 5
    } ;

enum DeviceClassType
    {	dct_unknown	= -1,
	dct_voice	= 0,
	dct_data	= 1,
	dct_image	= 2,
	dct_other	= 3
    } ;

enum DeviceTypeType
    {	dtt_unknown	= -1,
	dtt_station	= 0,
	dtt_line	= 1,
	dtt_button	= 2,
	dtt_ACD	= 3,
	dtt_trunk	= 4,
	dtt_operator	= 5,
	dtt_station_group	= 16,
	dtt_line_group	= 17,
	dtt_button_group	= 18,
	dtt_ACD_group	= 19,
	dtt_trunk_group	= 20,
	dtt_operator_group	= 21,
	dtt_other	= 255
    } ;
#endif // _CSTA_ENUM_TYPES_H_INCLUDED
typedef enum ErrorClass ErrorClass;

typedef enum ErrorCode ErrorCode;

typedef enum SystemStatusType SystemStatusType;

typedef enum EventCauseType EventCauseType;

typedef enum LocalConnectionStateType LocalConnectionStateType;

typedef enum FeatureInfoType FeatureInfoType;

typedef enum QueryDeviceFeatureType QueryDeviceFeatureType;

typedef enum ForwardingType ForwardingType;

typedef enum DeviceClassType DeviceClassType;

typedef enum DeviceTypeType DeviceTypeType;

typedef enum AgentStateType AgentStateType;

typedef enum AgentParameterType AgentParameterType;

typedef struct STAT_COUNTERS
    {
    long countOfEstablished;
    long countOfConnectionCleared;
    long countOfOutOfService;
    long countOfBackInService;
    } 	STAT_COUNTERS;


EXTERN_C const IID LIBID_CTNGLib;

#ifndef __ISystem_INTERFACE_DEFINED__
#define __ISystem_INTERFACE_DEFINED__

/* interface ISystem */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISystem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("74041709-2558-4C76-9614-63FF8E5E5452")
    ISystem : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenConsole( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CloseConsole( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE HasConsole( 
            /* [retval][out] */ BOOL *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddPABX( 
            /* [in] */ BSTR pabxId,
            /* [in] */ BSTR ip_address,
            /* [in] */ long tcp_port) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Dump( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Sleep( 
            /* [in] */ long milliseconds) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VerboseErrorCategory( 
            /* [in] */ ErrorCode rc,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VerboseErrorCode( 
            /* [in] */ ErrorCode rc,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VerboseSystemStatus( 
            /* [in] */ SystemStatusType ss,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VerboseEventCause( 
            /* [in] */ EventCauseType ec,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VerboseLocalConnectionState( 
            /* [in] */ LocalConnectionStateType lcs,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCounters( 
            /* [out] */ STAT_COUNTERS *sysCounters) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISystemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISystem * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISystem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISystem * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISystem * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISystem * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISystem * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISystem * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OpenConsole )( 
            ISystem * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CloseConsole )( 
            ISystem * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *HasConsole )( 
            ISystem * This,
            /* [retval][out] */ BOOL *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddPABX )( 
            ISystem * This,
            /* [in] */ BSTR pabxId,
            /* [in] */ BSTR ip_address,
            /* [in] */ long tcp_port);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Dump )( 
            ISystem * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Sleep )( 
            ISystem * This,
            /* [in] */ long milliseconds);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VerboseErrorCategory )( 
            ISystem * This,
            /* [in] */ ErrorCode rc,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VerboseErrorCode )( 
            ISystem * This,
            /* [in] */ ErrorCode rc,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VerboseSystemStatus )( 
            ISystem * This,
            /* [in] */ SystemStatusType ss,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VerboseEventCause )( 
            ISystem * This,
            /* [in] */ EventCauseType ec,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VerboseLocalConnectionState )( 
            ISystem * This,
            /* [in] */ LocalConnectionStateType lcs,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCounters )( 
            ISystem * This,
            /* [out] */ STAT_COUNTERS *sysCounters);
        
        END_INTERFACE
    } ISystemVtbl;

    interface ISystem
    {
        CONST_VTBL struct ISystemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISystem_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISystem_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISystem_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISystem_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISystem_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISystem_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISystem_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISystem_OpenConsole(This)	\
    (This)->lpVtbl -> OpenConsole(This)

#define ISystem_CloseConsole(This)	\
    (This)->lpVtbl -> CloseConsole(This)

#define ISystem_HasConsole(This,pResult)	\
    (This)->lpVtbl -> HasConsole(This,pResult)

#define ISystem_AddPABX(This,pabxId,ip_address,tcp_port)	\
    (This)->lpVtbl -> AddPABX(This,pabxId,ip_address,tcp_port)

#define ISystem_Dump(This)	\
    (This)->lpVtbl -> Dump(This)

#define ISystem_Sleep(This,milliseconds)	\
    (This)->lpVtbl -> Sleep(This,milliseconds)

#define ISystem_VerboseErrorCategory(This,rc,pVal)	\
    (This)->lpVtbl -> VerboseErrorCategory(This,rc,pVal)

#define ISystem_VerboseErrorCode(This,rc,pVal)	\
    (This)->lpVtbl -> VerboseErrorCode(This,rc,pVal)

#define ISystem_VerboseSystemStatus(This,ss,pVal)	\
    (This)->lpVtbl -> VerboseSystemStatus(This,ss,pVal)

#define ISystem_VerboseEventCause(This,ec,pVal)	\
    (This)->lpVtbl -> VerboseEventCause(This,ec,pVal)

#define ISystem_VerboseLocalConnectionState(This,lcs,pVal)	\
    (This)->lpVtbl -> VerboseLocalConnectionState(This,lcs,pVal)

#define ISystem_GetCounters(This,sysCounters)	\
    (This)->lpVtbl -> GetCounters(This,sysCounters)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISystem_OpenConsole_Proxy( 
    ISystem * This);


void __RPC_STUB ISystem_OpenConsole_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISystem_CloseConsole_Proxy( 
    ISystem * This);


void __RPC_STUB ISystem_CloseConsole_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISystem_HasConsole_Proxy( 
    ISystem * This,
    /* [retval][out] */ BOOL *pResult);


void __RPC_STUB ISystem_HasConsole_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISystem_AddPABX_Proxy( 
    ISystem * This,
    /* [in] */ BSTR pabxId,
    /* [in] */ BSTR ip_address,
    /* [in] */ long tcp_port);


void __RPC_STUB ISystem_AddPABX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISystem_Dump_Proxy( 
    ISystem * This);


void __RPC_STUB ISystem_Dump_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISystem_Sleep_Proxy( 
    ISystem * This,
    /* [in] */ long milliseconds);


void __RPC_STUB ISystem_Sleep_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISystem_VerboseErrorCategory_Proxy( 
    ISystem * This,
    /* [in] */ ErrorCode rc,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ISystem_VerboseErrorCategory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISystem_VerboseErrorCode_Proxy( 
    ISystem * This,
    /* [in] */ ErrorCode rc,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ISystem_VerboseErrorCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISystem_VerboseSystemStatus_Proxy( 
    ISystem * This,
    /* [in] */ SystemStatusType ss,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ISystem_VerboseSystemStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISystem_VerboseEventCause_Proxy( 
    ISystem * This,
    /* [in] */ EventCauseType ec,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ISystem_VerboseEventCause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISystem_VerboseLocalConnectionState_Proxy( 
    ISystem * This,
    /* [in] */ LocalConnectionStateType lcs,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ISystem_VerboseLocalConnectionState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISystem_GetCounters_Proxy( 
    ISystem * This,
    /* [out] */ STAT_COUNTERS *sysCounters);


void __RPC_STUB ISystem_GetCounters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISystem_INTERFACE_DEFINED__ */


#ifndef ___ISystemEvents_DISPINTERFACE_DEFINED__
#define ___ISystemEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ISystemEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ISystemEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("F5FC4EFE-74B6-48D5-B48C-AE162F6B1A0B")
    _ISystemEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ISystemEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ISystemEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ISystemEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ISystemEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ISystemEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ISystemEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ISystemEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ISystemEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _ISystemEventsVtbl;

    interface _ISystemEvents
    {
        CONST_VTBL struct _ISystemEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ISystemEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ISystemEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ISystemEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ISystemEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ISystemEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ISystemEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ISystemEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ISystemEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_System;

#ifdef __cplusplus

class DECLSPEC_UUID("B63AC033-0B40-4FD1-9BE1-5276FED1A5A1")
System;
#endif

#ifndef __IPABX_INTERFACE_DEFINED__
#define __IPABX_INTERFACE_DEFINED__

/* interface IPABX */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPABX;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AE0C8561-63DD-4C52-9023-A0CCBC9EE3B3")
    IPABX : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Open( 
            /* [in] */ BSTR id) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ID( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPABXVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPABX * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPABX * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPABX * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPABX * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPABX * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPABX * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPABX * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Open )( 
            IPABX * This,
            /* [in] */ BSTR id);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Close )( 
            IPABX * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            IPABX * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ID )( 
            IPABX * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } IPABXVtbl;

    interface IPABX
    {
        CONST_VTBL struct IPABXVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPABX_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPABX_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPABX_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPABX_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPABX_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPABX_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPABX_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPABX_Open(This,id)	\
    (This)->lpVtbl -> Open(This,id)

#define IPABX_Close(This)	\
    (This)->lpVtbl -> Close(This)

#define IPABX_get_ID(This,pVal)	\
    (This)->lpVtbl -> get_ID(This,pVal)

#define IPABX_put_ID(This,newVal)	\
    (This)->lpVtbl -> put_ID(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPABX_Open_Proxy( 
    IPABX * This,
    /* [in] */ BSTR id);


void __RPC_STUB IPABX_Open_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPABX_Close_Proxy( 
    IPABX * This);


void __RPC_STUB IPABX_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPABX_get_ID_Proxy( 
    IPABX * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IPABX_get_ID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPABX_put_ID_Proxy( 
    IPABX * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IPABX_put_ID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPABX_INTERFACE_DEFINED__ */


#ifndef ___IPABXEvents_DISPINTERFACE_DEFINED__
#define ___IPABXEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IPABXEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IPABXEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("35588776-0A0A-4731-9C59-FD30740D6C60")
    _IPABXEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IPABXEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IPABXEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IPABXEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IPABXEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IPABXEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IPABXEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IPABXEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IPABXEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IPABXEventsVtbl;

    interface _IPABXEvents
    {
        CONST_VTBL struct _IPABXEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IPABXEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IPABXEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IPABXEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IPABXEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IPABXEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IPABXEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IPABXEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IPABXEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PABX;

#ifdef __cplusplus

class DECLSPEC_UUID("155E8B8C-6C03-470E-82F7-16F99C417A5F")
PABX;
#endif

#ifndef __IDevice_INTERFACE_DEFINED__
#define __IDevice_INTERFACE_DEFINED__

/* interface IDevice */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IDevice;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C391A2ED-B56A-469E-B0E3-F51D8BE88713")
    IDevice : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Open( 
            /* [in] */ BSTR pabxID,
            /* [in] */ BSTR deviceID,
            /* [retval][out] */ ErrorCode *errCode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( 
            /* [retval][out] */ ErrorCode *errCode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TestFireAllEvents( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PutExtension( 
            /* [in] */ VARIANT *outOID,
            /* [in] */ VARIANT *outData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetExtension( 
            /* [out] */ SAFEARRAY * *inOID,
            /* [out] */ SAFEARRAY * *inData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AlternateCall( 
            /* [in] */ BSTR heldCall,
            /* [in] */ BSTR activeCall,
            /* [retval][out] */ ErrorCode *errCode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AnswerCall( 
            /* [in] */ BSTR connectionId,
            /* [retval][out] */ ErrorCode *errCode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CallCompletion( 
            /* [in] */ BSTR connectionId,
            /* [in] */ FeatureInfoType feature,
            /* [retval][out] */ ErrorCode *errCode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClearCall( 
            /* [in] */ BSTR callToBeCleared,
            /* [retval][out] */ ErrorCode *errCode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClearConnection( 
            /* [in] */ BSTR connectionId,
            /* [retval][out] */ ErrorCode *errCode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConferenceCall( 
            /* [in] */ BSTR heldCall,
            /* [in] */ BSTR activeCall,
            /* [out] */ VARIANT *connectionId,
            /* [retval][out] */ ErrorCode *errCode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConsultationCall( 
            /* [in] */ BSTR existingCall,
            /* [in] */ BSTR calledDirectoryNumber,
            /* [out] */ VARIANT *initiatedConnectionId,
            /* [retval][out] */ ErrorCode *errCode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DivertCall_Deflect( 
            /* [in] */ BSTR connectionId,
            /* [in] */ BSTR newDestination,
            /* [retval][out] */ ErrorCode *errCode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DivertCall_DirectedPickup( 
            /* [in] */ BSTR connectionId,
            /* [in] */ BSTR requestingDevice,
            /* [retval][out] */ ErrorCode *errCode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DivertCall_GroupPickup( 
            /* [in] */ BSTR groupDevice,
            /* [retval][out] */ ErrorCode *errCode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE HoldCall( 
            /* [in] */ BSTR connectionId,
            /* [in] */ BOOL reserveConnection,
            /* [retval][out] */ ErrorCode *errCode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MakeCall( 
            /* [in] */ BSTR calledDirectoryNumber,
            /* [out] */ VARIANT *connectionId,
            /* [retval][out] */ ErrorCode *errCode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MakePredictiveCall( 
            /* [in] */ BSTR calledDirectoryNumber,
            /* [out] */ VARIANT *connectionId,
            /* [retval][out] */ ErrorCode *errCode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReconnectCall( 
            /* [in] */ BSTR heldCall,
            /* [in] */ BSTR activeCall,
            /* [retval][out] */ ErrorCode *errCode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RetrieveCall( 
            /* [in] */ BSTR connectionId,
            /* [retval][out] */ ErrorCode *errCode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TransferCall( 
            /* [in] */ BSTR heldCall,
            /* [in] */ BSTR activeCall,
            /* [out] */ VARIANT *connectionId,
            /* [retval][out] */ ErrorCode *errCode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SystemStatus( 
            /* [in] */ SystemStatusType status,
            /* [retval][out] */ ErrorCode *errCode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EscapeService( 
            /* [in] */ VARIANT *outOID,
            /* [in] */ VARIANT *outData,
            /* [out] */ SAFEARRAY * *inOID,
            /* [out] */ SAFEARRAY * *inData,
            /* [retval][out] */ ErrorCode *errCode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE QueryDevice_MessageWaiting( 
            /* [out] */ BOOL *indicator,
            /* [retval][out] */ ErrorCode *errCode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE QueryDevice_DoNotDisturb( 
            /* [out] */ BOOL *indicator,
            /* [retval][out] */ ErrorCode *errCode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE QueryDevice_Forward( 
            /* [out] */ VARIANT *forwardInfo,
            /* [retval][out] */ ErrorCode *errCode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE QueryDevice_DeviceInfo( 
            /* [out] */ DeviceClassType *devClass,
            /* [out] */ DeviceTypeType *devType,
            /* [retval][out] */ ErrorCode *errCode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE QueryDevice_AgentState( 
            /* [out] */ AgentStateType *agentState,
            /* [retval][out] */ ErrorCode *errCode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetFature_MessageWaiting( 
            /* [in] */ BOOL indicator,
            /* [retval][out] */ ErrorCode *errCode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetFature_DoNotDisturb( 
            /* [in] */ BOOL indicator,
            /* [retval][out] */ ErrorCode *errCode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetFature_Forward( 
            /* [in] */ ForwardingType forwadType,
            /* [in] */ BSTR forwardDN,
            /* [retval][out] */ ErrorCode *errCode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetFature_RequestAgentState( 
            /* [in] */ AgentParameterType state,
            /* [in] */ BSTR agentID,
            /* [in] */ BSTR agentGroup,
            /* [in] */ BSTR agentPassword,
            /* [retval][out] */ ErrorCode *errCode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WaitOpen( 
            double timeoutSeconds,
            /* [retval][out] */ ErrorCode *errCode) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDeviceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDevice * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDevice * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDevice * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDevice * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDevice * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDevice * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDevice * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Open )( 
            IDevice * This,
            /* [in] */ BSTR pabxID,
            /* [in] */ BSTR deviceID,
            /* [retval][out] */ ErrorCode *errCode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Close )( 
            IDevice * This,
            /* [retval][out] */ ErrorCode *errCode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *TestFireAllEvents )( 
            IDevice * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PutExtension )( 
            IDevice * This,
            /* [in] */ VARIANT *outOID,
            /* [in] */ VARIANT *outData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetExtension )( 
            IDevice * This,
            /* [out] */ SAFEARRAY * *inOID,
            /* [out] */ SAFEARRAY * *inData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AlternateCall )( 
            IDevice * This,
            /* [in] */ BSTR heldCall,
            /* [in] */ BSTR activeCall,
            /* [retval][out] */ ErrorCode *errCode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AnswerCall )( 
            IDevice * This,
            /* [in] */ BSTR connectionId,
            /* [retval][out] */ ErrorCode *errCode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CallCompletion )( 
            IDevice * This,
            /* [in] */ BSTR connectionId,
            /* [in] */ FeatureInfoType feature,
            /* [retval][out] */ ErrorCode *errCode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ClearCall )( 
            IDevice * This,
            /* [in] */ BSTR callToBeCleared,
            /* [retval][out] */ ErrorCode *errCode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ClearConnection )( 
            IDevice * This,
            /* [in] */ BSTR connectionId,
            /* [retval][out] */ ErrorCode *errCode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ConferenceCall )( 
            IDevice * This,
            /* [in] */ BSTR heldCall,
            /* [in] */ BSTR activeCall,
            /* [out] */ VARIANT *connectionId,
            /* [retval][out] */ ErrorCode *errCode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ConsultationCall )( 
            IDevice * This,
            /* [in] */ BSTR existingCall,
            /* [in] */ BSTR calledDirectoryNumber,
            /* [out] */ VARIANT *initiatedConnectionId,
            /* [retval][out] */ ErrorCode *errCode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DivertCall_Deflect )( 
            IDevice * This,
            /* [in] */ BSTR connectionId,
            /* [in] */ BSTR newDestination,
            /* [retval][out] */ ErrorCode *errCode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DivertCall_DirectedPickup )( 
            IDevice * This,
            /* [in] */ BSTR connectionId,
            /* [in] */ BSTR requestingDevice,
            /* [retval][out] */ ErrorCode *errCode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DivertCall_GroupPickup )( 
            IDevice * This,
            /* [in] */ BSTR groupDevice,
            /* [retval][out] */ ErrorCode *errCode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *HoldCall )( 
            IDevice * This,
            /* [in] */ BSTR connectionId,
            /* [in] */ BOOL reserveConnection,
            /* [retval][out] */ ErrorCode *errCode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MakeCall )( 
            IDevice * This,
            /* [in] */ BSTR calledDirectoryNumber,
            /* [out] */ VARIANT *connectionId,
            /* [retval][out] */ ErrorCode *errCode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MakePredictiveCall )( 
            IDevice * This,
            /* [in] */ BSTR calledDirectoryNumber,
            /* [out] */ VARIANT *connectionId,
            /* [retval][out] */ ErrorCode *errCode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReconnectCall )( 
            IDevice * This,
            /* [in] */ BSTR heldCall,
            /* [in] */ BSTR activeCall,
            /* [retval][out] */ ErrorCode *errCode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RetrieveCall )( 
            IDevice * This,
            /* [in] */ BSTR connectionId,
            /* [retval][out] */ ErrorCode *errCode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *TransferCall )( 
            IDevice * This,
            /* [in] */ BSTR heldCall,
            /* [in] */ BSTR activeCall,
            /* [out] */ VARIANT *connectionId,
            /* [retval][out] */ ErrorCode *errCode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SystemStatus )( 
            IDevice * This,
            /* [in] */ SystemStatusType status,
            /* [retval][out] */ ErrorCode *errCode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EscapeService )( 
            IDevice * This,
            /* [in] */ VARIANT *outOID,
            /* [in] */ VARIANT *outData,
            /* [out] */ SAFEARRAY * *inOID,
            /* [out] */ SAFEARRAY * *inData,
            /* [retval][out] */ ErrorCode *errCode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *QueryDevice_MessageWaiting )( 
            IDevice * This,
            /* [out] */ BOOL *indicator,
            /* [retval][out] */ ErrorCode *errCode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *QueryDevice_DoNotDisturb )( 
            IDevice * This,
            /* [out] */ BOOL *indicator,
            /* [retval][out] */ ErrorCode *errCode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *QueryDevice_Forward )( 
            IDevice * This,
            /* [out] */ VARIANT *forwardInfo,
            /* [retval][out] */ ErrorCode *errCode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *QueryDevice_DeviceInfo )( 
            IDevice * This,
            /* [out] */ DeviceClassType *devClass,
            /* [out] */ DeviceTypeType *devType,
            /* [retval][out] */ ErrorCode *errCode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *QueryDevice_AgentState )( 
            IDevice * This,
            /* [out] */ AgentStateType *agentState,
            /* [retval][out] */ ErrorCode *errCode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetFature_MessageWaiting )( 
            IDevice * This,
            /* [in] */ BOOL indicator,
            /* [retval][out] */ ErrorCode *errCode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetFature_DoNotDisturb )( 
            IDevice * This,
            /* [in] */ BOOL indicator,
            /* [retval][out] */ ErrorCode *errCode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetFature_Forward )( 
            IDevice * This,
            /* [in] */ ForwardingType forwadType,
            /* [in] */ BSTR forwardDN,
            /* [retval][out] */ ErrorCode *errCode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetFature_RequestAgentState )( 
            IDevice * This,
            /* [in] */ AgentParameterType state,
            /* [in] */ BSTR agentID,
            /* [in] */ BSTR agentGroup,
            /* [in] */ BSTR agentPassword,
            /* [retval][out] */ ErrorCode *errCode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *WaitOpen )( 
            IDevice * This,
            double timeoutSeconds,
            /* [retval][out] */ ErrorCode *errCode);
        
        END_INTERFACE
    } IDeviceVtbl;

    interface IDevice
    {
        CONST_VTBL struct IDeviceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDevice_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDevice_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDevice_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDevice_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDevice_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDevice_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDevice_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDevice_Open(This,pabxID,deviceID,errCode)	\
    (This)->lpVtbl -> Open(This,pabxID,deviceID,errCode)

#define IDevice_Close(This,errCode)	\
    (This)->lpVtbl -> Close(This,errCode)

#define IDevice_TestFireAllEvents(This)	\
    (This)->lpVtbl -> TestFireAllEvents(This)

#define IDevice_PutExtension(This,outOID,outData)	\
    (This)->lpVtbl -> PutExtension(This,outOID,outData)

#define IDevice_GetExtension(This,inOID,inData)	\
    (This)->lpVtbl -> GetExtension(This,inOID,inData)

#define IDevice_AlternateCall(This,heldCall,activeCall,errCode)	\
    (This)->lpVtbl -> AlternateCall(This,heldCall,activeCall,errCode)

#define IDevice_AnswerCall(This,connectionId,errCode)	\
    (This)->lpVtbl -> AnswerCall(This,connectionId,errCode)

#define IDevice_CallCompletion(This,connectionId,feature,errCode)	\
    (This)->lpVtbl -> CallCompletion(This,connectionId,feature,errCode)

#define IDevice_ClearCall(This,callToBeCleared,errCode)	\
    (This)->lpVtbl -> ClearCall(This,callToBeCleared,errCode)

#define IDevice_ClearConnection(This,connectionId,errCode)	\
    (This)->lpVtbl -> ClearConnection(This,connectionId,errCode)

#define IDevice_ConferenceCall(This,heldCall,activeCall,connectionId,errCode)	\
    (This)->lpVtbl -> ConferenceCall(This,heldCall,activeCall,connectionId,errCode)

#define IDevice_ConsultationCall(This,existingCall,calledDirectoryNumber,initiatedConnectionId,errCode)	\
    (This)->lpVtbl -> ConsultationCall(This,existingCall,calledDirectoryNumber,initiatedConnectionId,errCode)

#define IDevice_DivertCall_Deflect(This,connectionId,newDestination,errCode)	\
    (This)->lpVtbl -> DivertCall_Deflect(This,connectionId,newDestination,errCode)

#define IDevice_DivertCall_DirectedPickup(This,connectionId,requestingDevice,errCode)	\
    (This)->lpVtbl -> DivertCall_DirectedPickup(This,connectionId,requestingDevice,errCode)

#define IDevice_DivertCall_GroupPickup(This,groupDevice,errCode)	\
    (This)->lpVtbl -> DivertCall_GroupPickup(This,groupDevice,errCode)

#define IDevice_HoldCall(This,connectionId,reserveConnection,errCode)	\
    (This)->lpVtbl -> HoldCall(This,connectionId,reserveConnection,errCode)

#define IDevice_MakeCall(This,calledDirectoryNumber,connectionId,errCode)	\
    (This)->lpVtbl -> MakeCall(This,calledDirectoryNumber,connectionId,errCode)

#define IDevice_MakePredictiveCall(This,calledDirectoryNumber,connectionId,errCode)	\
    (This)->lpVtbl -> MakePredictiveCall(This,calledDirectoryNumber,connectionId,errCode)

#define IDevice_ReconnectCall(This,heldCall,activeCall,errCode)	\
    (This)->lpVtbl -> ReconnectCall(This,heldCall,activeCall,errCode)

#define IDevice_RetrieveCall(This,connectionId,errCode)	\
    (This)->lpVtbl -> RetrieveCall(This,connectionId,errCode)

#define IDevice_TransferCall(This,heldCall,activeCall,connectionId,errCode)	\
    (This)->lpVtbl -> TransferCall(This,heldCall,activeCall,connectionId,errCode)

#define IDevice_SystemStatus(This,status,errCode)	\
    (This)->lpVtbl -> SystemStatus(This,status,errCode)

#define IDevice_EscapeService(This,outOID,outData,inOID,inData,errCode)	\
    (This)->lpVtbl -> EscapeService(This,outOID,outData,inOID,inData,errCode)

#define IDevice_QueryDevice_MessageWaiting(This,indicator,errCode)	\
    (This)->lpVtbl -> QueryDevice_MessageWaiting(This,indicator,errCode)

#define IDevice_QueryDevice_DoNotDisturb(This,indicator,errCode)	\
    (This)->lpVtbl -> QueryDevice_DoNotDisturb(This,indicator,errCode)

#define IDevice_QueryDevice_Forward(This,forwardInfo,errCode)	\
    (This)->lpVtbl -> QueryDevice_Forward(This,forwardInfo,errCode)

#define IDevice_QueryDevice_DeviceInfo(This,devClass,devType,errCode)	\
    (This)->lpVtbl -> QueryDevice_DeviceInfo(This,devClass,devType,errCode)

#define IDevice_QueryDevice_AgentState(This,agentState,errCode)	\
    (This)->lpVtbl -> QueryDevice_AgentState(This,agentState,errCode)

#define IDevice_SetFature_MessageWaiting(This,indicator,errCode)	\
    (This)->lpVtbl -> SetFature_MessageWaiting(This,indicator,errCode)

#define IDevice_SetFature_DoNotDisturb(This,indicator,errCode)	\
    (This)->lpVtbl -> SetFature_DoNotDisturb(This,indicator,errCode)

#define IDevice_SetFature_Forward(This,forwadType,forwardDN,errCode)	\
    (This)->lpVtbl -> SetFature_Forward(This,forwadType,forwardDN,errCode)

#define IDevice_SetFature_RequestAgentState(This,state,agentID,agentGroup,agentPassword,errCode)	\
    (This)->lpVtbl -> SetFature_RequestAgentState(This,state,agentID,agentGroup,agentPassword,errCode)

#define IDevice_WaitOpen(This,timeoutSeconds,errCode)	\
    (This)->lpVtbl -> WaitOpen(This,timeoutSeconds,errCode)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDevice_Open_Proxy( 
    IDevice * This,
    /* [in] */ BSTR pabxID,
    /* [in] */ BSTR deviceID,
    /* [retval][out] */ ErrorCode *errCode);


void __RPC_STUB IDevice_Open_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDevice_Close_Proxy( 
    IDevice * This,
    /* [retval][out] */ ErrorCode *errCode);


void __RPC_STUB IDevice_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDevice_TestFireAllEvents_Proxy( 
    IDevice * This);


void __RPC_STUB IDevice_TestFireAllEvents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDevice_PutExtension_Proxy( 
    IDevice * This,
    /* [in] */ VARIANT *outOID,
    /* [in] */ VARIANT *outData);


void __RPC_STUB IDevice_PutExtension_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDevice_GetExtension_Proxy( 
    IDevice * This,
    /* [out] */ SAFEARRAY * *inOID,
    /* [out] */ SAFEARRAY * *inData);


void __RPC_STUB IDevice_GetExtension_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDevice_AlternateCall_Proxy( 
    IDevice * This,
    /* [in] */ BSTR heldCall,
    /* [in] */ BSTR activeCall,
    /* [retval][out] */ ErrorCode *errCode);


void __RPC_STUB IDevice_AlternateCall_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDevice_AnswerCall_Proxy( 
    IDevice * This,
    /* [in] */ BSTR connectionId,
    /* [retval][out] */ ErrorCode *errCode);


void __RPC_STUB IDevice_AnswerCall_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDevice_CallCompletion_Proxy( 
    IDevice * This,
    /* [in] */ BSTR connectionId,
    /* [in] */ FeatureInfoType feature,
    /* [retval][out] */ ErrorCode *errCode);


void __RPC_STUB IDevice_CallCompletion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDevice_ClearCall_Proxy( 
    IDevice * This,
    /* [in] */ BSTR callToBeCleared,
    /* [retval][out] */ ErrorCode *errCode);


void __RPC_STUB IDevice_ClearCall_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDevice_ClearConnection_Proxy( 
    IDevice * This,
    /* [in] */ BSTR connectionId,
    /* [retval][out] */ ErrorCode *errCode);


void __RPC_STUB IDevice_ClearConnection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDevice_ConferenceCall_Proxy( 
    IDevice * This,
    /* [in] */ BSTR heldCall,
    /* [in] */ BSTR activeCall,
    /* [out] */ VARIANT *connectionId,
    /* [retval][out] */ ErrorCode *errCode);


void __RPC_STUB IDevice_ConferenceCall_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDevice_ConsultationCall_Proxy( 
    IDevice * This,
    /* [in] */ BSTR existingCall,
    /* [in] */ BSTR calledDirectoryNumber,
    /* [out] */ VARIANT *initiatedConnectionId,
    /* [retval][out] */ ErrorCode *errCode);


void __RPC_STUB IDevice_ConsultationCall_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDevice_DivertCall_Deflect_Proxy( 
    IDevice * This,
    /* [in] */ BSTR connectionId,
    /* [in] */ BSTR newDestination,
    /* [retval][out] */ ErrorCode *errCode);


void __RPC_STUB IDevice_DivertCall_Deflect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDevice_DivertCall_DirectedPickup_Proxy( 
    IDevice * This,
    /* [in] */ BSTR connectionId,
    /* [in] */ BSTR requestingDevice,
    /* [retval][out] */ ErrorCode *errCode);


void __RPC_STUB IDevice_DivertCall_DirectedPickup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDevice_DivertCall_GroupPickup_Proxy( 
    IDevice * This,
    /* [in] */ BSTR groupDevice,
    /* [retval][out] */ ErrorCode *errCode);


void __RPC_STUB IDevice_DivertCall_GroupPickup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDevice_HoldCall_Proxy( 
    IDevice * This,
    /* [in] */ BSTR connectionId,
    /* [in] */ BOOL reserveConnection,
    /* [retval][out] */ ErrorCode *errCode);


void __RPC_STUB IDevice_HoldCall_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDevice_MakeCall_Proxy( 
    IDevice * This,
    /* [in] */ BSTR calledDirectoryNumber,
    /* [out] */ VARIANT *connectionId,
    /* [retval][out] */ ErrorCode *errCode);


void __RPC_STUB IDevice_MakeCall_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDevice_MakePredictiveCall_Proxy( 
    IDevice * This,
    /* [in] */ BSTR calledDirectoryNumber,
    /* [out] */ VARIANT *connectionId,
    /* [retval][out] */ ErrorCode *errCode);


void __RPC_STUB IDevice_MakePredictiveCall_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDevice_ReconnectCall_Proxy( 
    IDevice * This,
    /* [in] */ BSTR heldCall,
    /* [in] */ BSTR activeCall,
    /* [retval][out] */ ErrorCode *errCode);


void __RPC_STUB IDevice_ReconnectCall_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDevice_RetrieveCall_Proxy( 
    IDevice * This,
    /* [in] */ BSTR connectionId,
    /* [retval][out] */ ErrorCode *errCode);


void __RPC_STUB IDevice_RetrieveCall_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDevice_TransferCall_Proxy( 
    IDevice * This,
    /* [in] */ BSTR heldCall,
    /* [in] */ BSTR activeCall,
    /* [out] */ VARIANT *connectionId,
    /* [retval][out] */ ErrorCode *errCode);


void __RPC_STUB IDevice_TransferCall_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDevice_SystemStatus_Proxy( 
    IDevice * This,
    /* [in] */ SystemStatusType status,
    /* [retval][out] */ ErrorCode *errCode);


void __RPC_STUB IDevice_SystemStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDevice_EscapeService_Proxy( 
    IDevice * This,
    /* [in] */ VARIANT *outOID,
    /* [in] */ VARIANT *outData,
    /* [out] */ SAFEARRAY * *inOID,
    /* [out] */ SAFEARRAY * *inData,
    /* [retval][out] */ ErrorCode *errCode);


void __RPC_STUB IDevice_EscapeService_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDevice_QueryDevice_MessageWaiting_Proxy( 
    IDevice * This,
    /* [out] */ BOOL *indicator,
    /* [retval][out] */ ErrorCode *errCode);


void __RPC_STUB IDevice_QueryDevice_MessageWaiting_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDevice_QueryDevice_DoNotDisturb_Proxy( 
    IDevice * This,
    /* [out] */ BOOL *indicator,
    /* [retval][out] */ ErrorCode *errCode);


void __RPC_STUB IDevice_QueryDevice_DoNotDisturb_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDevice_QueryDevice_Forward_Proxy( 
    IDevice * This,
    /* [out] */ VARIANT *forwardInfo,
    /* [retval][out] */ ErrorCode *errCode);


void __RPC_STUB IDevice_QueryDevice_Forward_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDevice_QueryDevice_DeviceInfo_Proxy( 
    IDevice * This,
    /* [out] */ DeviceClassType *devClass,
    /* [out] */ DeviceTypeType *devType,
    /* [retval][out] */ ErrorCode *errCode);


void __RPC_STUB IDevice_QueryDevice_DeviceInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDevice_QueryDevice_AgentState_Proxy( 
    IDevice * This,
    /* [out] */ AgentStateType *agentState,
    /* [retval][out] */ ErrorCode *errCode);


void __RPC_STUB IDevice_QueryDevice_AgentState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDevice_SetFature_MessageWaiting_Proxy( 
    IDevice * This,
    /* [in] */ BOOL indicator,
    /* [retval][out] */ ErrorCode *errCode);


void __RPC_STUB IDevice_SetFature_MessageWaiting_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDevice_SetFature_DoNotDisturb_Proxy( 
    IDevice * This,
    /* [in] */ BOOL indicator,
    /* [retval][out] */ ErrorCode *errCode);


void __RPC_STUB IDevice_SetFature_DoNotDisturb_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDevice_SetFature_Forward_Proxy( 
    IDevice * This,
    /* [in] */ ForwardingType forwadType,
    /* [in] */ BSTR forwardDN,
    /* [retval][out] */ ErrorCode *errCode);


void __RPC_STUB IDevice_SetFature_Forward_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDevice_SetFature_RequestAgentState_Proxy( 
    IDevice * This,
    /* [in] */ AgentParameterType state,
    /* [in] */ BSTR agentID,
    /* [in] */ BSTR agentGroup,
    /* [in] */ BSTR agentPassword,
    /* [retval][out] */ ErrorCode *errCode);


void __RPC_STUB IDevice_SetFature_RequestAgentState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDevice_WaitOpen_Proxy( 
    IDevice * This,
    double timeoutSeconds,
    /* [retval][out] */ ErrorCode *errCode);


void __RPC_STUB IDevice_WaitOpen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDevice_INTERFACE_DEFINED__ */


#ifndef ___IDeviceEvents_DISPINTERFACE_DEFINED__
#define ___IDeviceEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IDeviceEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IDeviceEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("DF33386D-07F2-40F2-8775-E136A4DFEFB0")
    _IDeviceEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IDeviceEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IDeviceEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IDeviceEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IDeviceEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IDeviceEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IDeviceEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IDeviceEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IDeviceEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IDeviceEventsVtbl;

    interface _IDeviceEvents
    {
        CONST_VTBL struct _IDeviceEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IDeviceEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IDeviceEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IDeviceEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IDeviceEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IDeviceEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IDeviceEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IDeviceEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IDeviceEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Device;

#ifdef __cplusplus

class DECLSPEC_UUID("2BE420EA-C378-40F8-BF73-B19CFF854186")
Device;
#endif
#endif /* __CTNGLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


