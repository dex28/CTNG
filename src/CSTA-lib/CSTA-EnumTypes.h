#ifndef _CSTA_ENUM_TYPES_H_INCLUDED
#define _CSTA_ENUM_TYPES_H_INCLUDED

/*
    Project: CSTALib

    Module: CSTA-EnumTypes.h

    Description: CSTA error codes and enumerated types declarations

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

enum ErrorClass
{
    CSER_INTERNAL_ERROR                         = 0x0000, // Internal
    CSER_REJECT_GENERAL_PROBLEM                 = 0x0100, // ROSE
    CSER_REJECT_INVOKE_PROBLEM                  = 0x0200, // ROSE
    CSER_REJECT_RETURN_RESULT_PROBLEM           = 0x0300, // ROSE
    CSER_REJECT_RETURN_ERROR_PROBLEM            = 0x0400, // ROSE
    CSER_OPERATIONAL_ERROR                      = 0x0500, // CSTA
    CSER_STATE_ERROR                            = 0x0600, // CSTA
    CSER_SYSTEM_RESOURCE_ERROR                  = 0x0700, // CSTA
    CSER_SUBSCRIBED_RESOURCE_AVAILABILITY_ERROR = 0x0800, // CSTA
    CSER_PERFORMANCE_ERROR                      = 0x0900, // CSTA
    CSER_SECURITY_ERROR                         = 0x0A00, // CSTA
    CSER_UNSPECIFIED_ERROR                      = 0x0B00, // CSTA
    CSER_NON_STANDARD_ERROR                     = 0x0C00  // CSTA
    };

//
// Policy: there is an error, if ErrorCode <> 0.
//
enum ErrorCode
{
    // No Error
    CTNG_NO_ERROR                               = 0x0000,

    // Internal error
    CSTA_ERROR_CODE_NOT_SET                     = 0x0001,
    CSTA_ERROR_TIMEOUT                          = 0x0002,
    CSTA_NOT_CONNECTED                          = 0x0003,
    CSTA_NOT_IMPLEMENTED                        = 0x0004,
    CSTA_INVALID_PABX_ID                        = 0x0005,
    CSTA_INVALID_DEVICE_ID                      = 0x0006,
    CSTA_INVALID_CONNECTION_ID                  = 0x0007,
    CSTA_RECEIVED_INVALID_APDU                  = 0x0008,
    CSTA_MONITOR_NOT_STARTED                    = 0x0009,
    CSTA_MONITOR_ALREADY_OPEN                   = 0x000A,
    CTNG_NO_MEMORY                              = 0x000B,
    CTNG_EXCEPTION_ERROR                        = 0x000C,
    CTNG_OPEN_CONNECTION_FAILED                 = 0x000D,
    CTNG_INVALID_POINTER                        = 0x000E,
    CSTA_DISCONNECTED                           = 0x000F,
    CTNG_SEND_APDU_FAILED                       = 0x0010,

    // ROSE Reject, General Problem
    RJGP_unrecognisedAPDU                       = 0x0100,
    RJGP_mistypedAPDU                           = 0x0101,
    RJGP_badlyStructuredAPDU                    = 0x0102,
    RJIP_duplicateInvocation                    = 0x0200,

    // ROSE Reject, Invoke Problem
    RJIP_unrecognisedOperation                  = 0x0201,
    RJIP_mistypedArgument                       = 0x0202,
    RJIP_resourceLimitation                     = 0x0203,
    RJIP_initiatorReleasing                     = 0x0204,
    RJIP_unrecognisedLinkedID                   = 0x0205,
    RJIP_linkedResponseUnexpected               = 0x0206,
    RJIP_unexpectedChildOperation               = 0x0207,

    // ROSE Reject, Return Result Problem
    RJRRP_unrecognisedInvocation                = 0x0300,
    RJRRP_resultResponseUnexpected              = 0x0301,
    RJRRP_mistypedResult                        = 0x0302,

    // ROSE Reject, Return Error Problem
    RJREP_unrecognisedInvocation                = 0x0400,
    RJREP_errorResponseUnexpected               = 0x0401,
    RJREP_unrecognisedError                     = 0x0402,
    RJREP_unexpectedError                       = 0x0403,
    RJREP_mistypedParameter                     = 0x0404,

    // CSTA Error, UniversalFailure, Operations
    ERUFOP_generic                              = 0x0501,
    ERUFOP_requestIncompatibleWithObject        = 0x0502,
    ERUFOP_valueOutOfRange                      = 0x0503,
    ERUFOP_objectNotKnown                       = 0x0504, 
    ERUFOP_invalidCallingDevice                 = 0x0505,
    ERUFOP_invalidCalledDevice                  = 0x0506,
    ERUFOP_invalidForwardingDestination         = 0x0507,
    ERUFOP_privilegeViolationOnSpecifiedDevice  = 0x0508,
    ERUFOP_privilegeViolationOnCalledDevice     = 0x0509,
    ERUFOP_privilegeViolationOnCallingDevice    = 0x050A,
    ERUFOP_invalidCSTACallIdentifier            = 0x050B,
    ERUFOP_invalidCSTADeviceIdentifier          = 0x050C,
    ERUFOP_invalidCSTAConnectionIdentifier      = 0x050D,
    ERUFOP_invalidDestination                   = 0x050E,
    ERUFOP_invalidFeature                       = 0x050F,
    ERUFOP_invalidAllocationState               = 0x0510,
    ERUFOP_invalidCrossRefID                    = 0x0511,
    ERUFOP_invalidObjectType                    = 0x0512,
    ERUFOP_securityViolation                    = 0x0513,

    // CSTA Error, UniversalFailure, StateIncompatibility
    ERUFSI_generic                              = 0x0601,
    ERUFSI_invalidObjectState                   = 0x0602,
    ERUFSI_invalidConnectionID                  = 0x0603,
    ERUFSI_noActiveCall                         = 0x0604,
    ERUFSI_noHeldCall                           = 0x0605,
    ERUFSI_noCallToClear                        = 0x0606,
    ERUFSI_noConnectionToClear                  = 0x0607,
    ERUFSI_noCallToAnswer                       = 0x0608,
    ERUFSI_noCallToComplete                     = 0x0609,

    // CSTA Error, UniversalFailure, SystemResourceAvailability
    ERUFSYRA_generic                            = 0x0701,
    ERUFSYRA_serviceBusy                        = 0x0702,
    ERUFSYRA_resourceBusy                       = 0x0703,
    ERUFSYRA_resourceOutOfService               = 0x0704,
    ERUFSYRA_networkBusy                        = 0x0705,
    ERUFSYRA_networkOutOfService                = 0x0706,
    ERUFSYRA_overallMonitorLimitExceeded        = 0x0707,
    ERUFSYRA_conferenceMemberLimitExceeded      = 0x0708,

    // CSTA Error, UniversalFailure, SubscribedResourceAvailability
    ERUFSCRA_generic                            = 0x0801,
    ERUFSCRA_objectMonitorLimitExceeded         = 0x0802,
    ERUFSCRA_externalTrunkLimitExceeded         = 0x0803,
    ERUFSCRA_outstandingRequestLimitExceeded    = 0x0804,

    // CSTA Error, UniversalFailure, PerformanceManagement
    ERUFPM_generic                              = 0x0901,
    ERUFPM_performanceLimitExceeded             = 0x0902,

    // CSTA Error, UniversalFailure, SecurityError
    ERUFSE_unspecified                          = 0x0A00,
    ERUFSE_sequenceNumberViolated               = 0x0A01,
    ERUFSE_timeStampViolated                    = 0x0A02,
    ERUFSE_pACViolated                          = 0x0A03,
    ERUFSE_sealViolated                         = 0x0A04,

    // CSTA Error, UniversalFailure, UnspecifiedError
    ERUFUE_unspecified                          = 0x0B00,

    // CSTA Error, UniversalFailure, NonStandardError
    ERUFNSE_unspecified                         = 0x0C00

    };

enum SystemStatusType
{
    ss_unknown                  = -1,
    ss_initializing             = 0,
    ss_enabled                  = 1,
    ss_normal                   = 2,
    ss_messagesLost             = 3,
    ss_disabled                 = 4,
    ss_overloadImminent         = 5,
    ss_overloadReached          = 6,
    ss_overloadRelieved         = 7
    };

enum EventCauseType
{
    ec_unknown                  = -1,
    ec_activeMonitor            = 1,
    ec_alternate                = 2,
    ec_busy                     = 3,
    ec_callBack                 = 4,
    ec_callCancelled            = 5,
    ec_callForwardAlways        = 6,
    ec_callForwardBusy          = 7,
    ec_callForwardNoAnswer      = 8,
    ec_callForward              = 9,
    ec_callNotAnswered          = 10,
    ec_callPickup               = 11,
    ec_campOn                   = 12,
    ec_destNotObtainable        = 13,
    ec_doNotDisturb             = 14,
    ec_incompatibleDestination  = 15,
    ec_invalidAccountCode       = 16,
    ec_keyConference            = 17,
    ec_lockout                  = 18,
    ec_maintenance              = 19,
    ec_networkCongestion        = 20,
    ec_networkNotObtainable     = 21,
    ec_newCall                  = 22,
    ec_noAvailableAgents        = 23,
    ec_override                 = 24,
    ec_park                     = 25,
    ec_overflow                 = 26,
    ec_recall                   = 27,
    ec_redirected               = 28,
    ec_reorderTone              = 29,
    ec_resourcesNotAvailable    = 30,
    ec_silentParticipation      = 31,
    ec_transfer                 = 32,
    ec_trunksBusy               = 33,
    ec_voiceUnitInitiator       = 34
    };

enum LocalConnectionStateType
{
    lcs_unknown                 = -1,
    lcs_null                    = 0,
    lcs_initiated               = 1,
    lcs_alerting                = 2,
    lcs_connected               = 3,
    lcs_hold                    = 4,
    lcs_queued                  = 5,
    lcs_fail                    = 6
    };

enum FeatureInfoType
{
    fi_unknown                  = -1,
    fi_campon                   = 0,
    fi_callback                 = 1,
    fi_intrude                  = 2,
    fi_callbackMessage          = 3
    };

enum QueryDeviceFeatureType
{
    qdf_unknown                 = -1,
    qdf_msgWaitingOn            = 0,
    qdf_doNotDisturbOn          = 1,
    qdf_forward                 = 2,
    qdf_lastDialedNumber        = 3,
    qdf_deviceInfo              = 4,
    qdf_agentState              = 5,
    qdf_routingEnabled          = 6,
    qdf_autoAnswer              = 7,
    qdf_microphoneMuteOn        = 8,
    qdf_speakerMuteOn           = 9,
    qdf_speakerVolume           = 10
    };

enum ForwardingType
{
    ft_unknown                  = -1,
    ft_forwardImmediateOn       = 0,
    ft_forwardImmediateOff      = 1,
    ft_forwardBusyOn            = 2,
    ft_forwardBusyOff           = 3,
    ft_forwardNoAnsOn           = 4,
    ft_forwardNoAnsOff          = 5,
    ft_forwardBusyIntOn         = 6,
    ft_forwardBusyIntOff        = 7,
    ft_forwardBusyExtOn         = 8,
    ft_forwardBusyExtOff        = 9,
    ft_forwardNoAnsIntOn        = 10,
    ft_forwardNoAnsIntOff       = 11,
    ft_forwardNoAnsExtOn        = 12,
    ft_forwardNoAnsExtOff       = 13
    };

enum AgentStateType
{
    ast_unknown                 = -1,
    ast_notReady                = 0,
    ast_null                    = 1,
    ast_ready                   = 2,
    ast_workNotReady            = 3,
    ast_workReady               = 4
    };

enum AgentParameterType
{
    apt_unknown                 = -1,
    apt_loggedIn                = 0,
    apt_loggedOut               = 1,
    apt_notReady                = 2,
    apt_ready                   = 3,
    apt_workNotReady            = 4,
    apt_workReady               = 5
    };

enum DeviceClassType
{
    dct_unknown                 = -1,
    dct_voice                   = 0,
    dct_data                    = 1,
    dct_image                   = 2,
    dct_other                   = 3
    };

enum DeviceTypeType
{
    dtt_unknown                 = -1,
    dtt_station                 = 0,
    dtt_line                    = 1,
    dtt_button                  = 2,
    dtt_ACD                     = 3,
    dtt_trunk                   = 4,
    dtt_operator                = 5,
    dtt_station_group           = 16,
    dtt_line_group              = 17,
    dtt_button_group            = 18,
    dtt_ACD_group               = 19,
    dtt_trunk_group             = 20,
    dtt_operator_group          = 21,
    dtt_other                   = 255
    };

#endif // _CSTA_ENUM_TYPES_H_INCLUDED