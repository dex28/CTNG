/*
    Project: CSTALib

    Module: VerboseEnums.Cpp

    Description: Enumerated constants verbose lookup

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "CSTA-Lib.h"

using namespace ASN;

/////////////////////////////////////////////////////////////////////////////
namespace MidCSTA
{

const char* System::VerboseCategory( ErrorCode rc )
{
    switch( rc & 0xFF00 )
    {
        case CSER_INTERNAL_ERROR:
            return "Internal error";

        case CSER_REJECT_GENERAL_PROBLEM:
            return "ROSE-Reject general problem";

        case CSER_REJECT_INVOKE_PROBLEM:
            return "ROSE-Reject invoke problem";

        case CSER_REJECT_RETURN_RESULT_PROBLEM:
            return "ROSE-Reject return result problem";

        case CSER_REJECT_RETURN_ERROR_PROBLEM:
            return "ROSE-Reject return error problem";

        case CSER_OPERATIONAL_ERROR:
            return "CSTA operational error";

        case CSER_STATE_ERROR:
            return "CSTA state error";

        case CSER_SYSTEM_RESOURCE_ERROR:
            return "CSTA system resource error";

        case CSER_SUBSCRIBED_RESOURCE_AVAILABILITY_ERROR:
            return "CSTA subscribed resource availability error";

        case CSER_PERFORMANCE_ERROR:
            return "CSTA performance error";

        case CSER_SECURITY_ERROR:
            return "CSTA security error";

        case CSER_UNSPECIFIED_ERROR:
            return "CSTA unspecified error";

        case CSER_NON_STANDARD_ERROR:
            return "CSTA non standard error";

        }

    return "*UnknownErrorClass*";
    }

const char* System::Verbose( ErrorCode rc )
{
    switch( rc )
    {
        case CTNG_NO_ERROR:
            return "No error";


        case CSTA_ERROR_CODE_NOT_SET:
            return "Error code is not set";

        case CSTA_ERROR_TIMEOUT:
            return "Timeout";

        case CSTA_NOT_CONNECTED:
            return "Connection is not open";

        case CSTA_NOT_IMPLEMENTED:
            return "Not implemented service";

        case CSTA_INVALID_PABX_ID:
            return "Invalid PABX identifier";

        case CSTA_INVALID_DEVICE_ID:
            return "Invalide Device identifier";
    
        case CSTA_INVALID_CONNECTION_ID:
            return "Invalid Connection identifier";
    
        case CSTA_RECEIVED_INVALID_APDU:
            return "Received invalid CSTA APDU";

        case CSTA_MONITOR_ALREADY_OPEN:
            return "Montior is already open";

        case CSTA_MONITOR_NOT_STARTED:
            return "Montior is not started";

        case CTNG_NO_MEMORY:
            return "No memory";

        case CTNG_EXCEPTION_ERROR:
            return "Exception error";

        case CTNG_OPEN_CONNECTION_FAILED:
            return "Open Connection failed";

        case CTNG_INVALID_POINTER:
            return "Invalid pointer";

        case CSTA_DISCONNECTED:
            return "CSTA Disconnected";

        case RJGP_unrecognisedAPDU:
            return "Unrecognized APDU";

        case RJGP_mistypedAPDU:
            return "Mistyped APDU";

        case RJGP_badlyStructuredAPDU:
            return "Badly structured APDU";

        case RJIP_duplicateInvocation:
            return "Duplicate invocation";


        case RJIP_unrecognisedOperation:
            return "Unrecognized operation";

        case RJIP_mistypedArgument:
            return "Mistyped argument";

        case RJIP_resourceLimitation:
            return "Resource limitation";

        case RJIP_initiatorReleasing:
            return "Initiator is releasing";

        case RJIP_unrecognisedLinkedID:
            return "Unrecognized linked identifier";

        case RJIP_linkedResponseUnexpected:
            return "Linked response is unexpected";

        case RJIP_unexpectedChildOperation:
            return "Unexpected child operation";


        case RJRRP_unrecognisedInvocation:
            return "Unercognized invocation";

        case RJRRP_resultResponseUnexpected:
            return "Result response is unexpected";

        case RJRRP_mistypedResult:
            return "Mistyped result";


        case RJREP_unrecognisedInvocation:
            return "Unrecognized invocation";

        case RJREP_errorResponseUnexpected:
            return "Error response is unexpected";

        case RJREP_unrecognisedError:
            return "Unrecognized error";

        case RJREP_unexpectedError:
            return "Unexpected error";

        case RJREP_mistypedParameter:
            return "Mistyped parameter";


        case ERUFOP_generic:
            return "Generic error";

        case ERUFOP_requestIncompatibleWithObject:
            return "Request incompatibile with object";

        case ERUFOP_valueOutOfRange:
            return "value out of range";

        case ERUFOP_objectNotKnown:
            return "Object is not known";

        case ERUFOP_invalidCallingDevice:
            return "Invalid calling device";

        case ERUFOP_invalidCalledDevice:
            return "Invalid called device";

        case ERUFOP_invalidForwardingDestination:
            return "Invalid forwarding destination";

        case ERUFOP_privilegeViolationOnSpecifiedDevice:
            return "Privilege violation on specified device";

        case ERUFOP_privilegeViolationOnCalledDevice:
            return "Privilege violation on called device";

        case ERUFOP_privilegeViolationOnCallingDevice:
            return "Privilege violation on calling device";

        case ERUFOP_invalidCSTACallIdentifier:
            return "Invalid call identifier";

        case ERUFOP_invalidCSTADeviceIdentifier:
            return "Invalid device identifier";

        case ERUFOP_invalidCSTAConnectionIdentifier:
            return "Invalid connection identifier";

        case ERUFOP_invalidDestination:
            return "Invalid destination";

        case ERUFOP_invalidFeature:
            return "Invalid feature";

        case ERUFOP_invalidAllocationState:
            return "Invalid allocation state";

        case ERUFOP_invalidCrossRefID:
            return "Invalid cross reference identifier";

        case ERUFOP_invalidObjectType:
            return "Invalid object type";

        case ERUFOP_securityViolation:
            return "Security violation";


        case ERUFSI_generic:
            return "Generic error";

        case ERUFSI_invalidObjectState:
            return "Invalid object stat";

        case ERUFSI_invalidConnectionID:
            return "Invalid connection identifier";

        case ERUFSI_noActiveCall:
            return "No active call";

        case ERUFSI_noHeldCall:
            return "No held call";

        case ERUFSI_noCallToClear:
            return "No call to clear";

        case ERUFSI_noConnectionToClear:
            return "No connection to clear";

        case ERUFSI_noCallToAnswer:
            return "No call to answer";

        case ERUFSI_noCallToComplete:
            return "No call to complete";


        case ERUFSYRA_generic:
            return "Generic error";

        case ERUFSYRA_serviceBusy:
            return "Servic is busy";

        case ERUFSYRA_resourceBusy:
            return "Resource is busy";

        case ERUFSYRA_resourceOutOfService:
            return "Resource is out of service";

        case ERUFSYRA_networkBusy:
            return "Network is busy";

        case ERUFSYRA_networkOutOfService:
            return "Network is out of service";

        case ERUFSYRA_overallMonitorLimitExceeded:
            return "Overall monitor limit is exceeded";

        case ERUFSYRA_conferenceMemberLimitExceeded:
            return "Conference member limit is exceeded";


        case ERUFSCRA_generic:
            return "Generic error";

        case ERUFSCRA_objectMonitorLimitExceeded:
            return "Object monitor limit is exceeded";

        case ERUFSCRA_externalTrunkLimitExceeded:
            return "External trunk limit is exceeded";

        case ERUFSCRA_outstandingRequestLimitExceeded:
            return "Outstanding request limit is exceeded";


        case ERUFPM_generic:
            return "Generic error";

        case ERUFPM_performanceLimitExceeded:
            return "Performance limt is exceeded";


        case ERUFSE_unspecified:
            return "Unspecified";

        case ERUFSE_sequenceNumberViolated:
            return "Sequence number is violated";

        case ERUFSE_timeStampViolated:
            return "Time stamp is violated";

        case ERUFSE_pACViolated:
            return "pAC is violated";

        case ERUFSE_sealViolated:
            return "Seal is violated";


        case ERUFUE_unspecified:
            return "Unspecified";


        case ERUFNSE_unspecified:
            return "Unspecified";

        }

    return "*UnknownError*";
    }

const char* System::Verbose( SystemStatusType ss )
{
    switch( ss )
    {
        case ss_disabled:         return "Disabled";
        case ss_enabled:          return "Enabled";
        case ss_initializing:     return "Initializing";
        case ss_messagesLost:     return "Message Lost";
        case ss_normal:           return "Normal";
        case ss_overloadImminent: return "Overload Imminent";
        case ss_overloadReached:  return "Overload Reached";
        case ss_overloadRelieved: return "Overload Relieved";
        case ss_unknown:          return "Unknown";
        }
    return "*Unknown*";
    }

const char* System::Verbose( LocalConnectionStateType lcs )
{
    switch( lcs )
    {
        case lcs_alerting:        return "Alerting";
        case lcs_connected:       return "Connected";
        case lcs_fail:            return "Fail";
        case lcs_hold:            return "Hold";
        case lcs_initiated:       return "Initiated";
        case lcs_null:            return "Null";
        case lcs_queued:          return "Queued";
        case lcs_unknown:         return "Unknown";
        }

    return "*Unknown*";
    }

const char* System::Verbose( EventCauseType ec )
{
    switch( ec )
    {
        case ec_activeMonitor:           return "Active Monitor";
        case ec_alternate:               return "Alternate";
        case ec_busy:                    return "Busy";
        case ec_callBack:                return "Call Back";
        case ec_callCancelled:           return "Cancelled";
        case ec_callForward:             return "Call Forward";
        case ec_callForwardAlways:       return "Call Forward Always";
        case ec_callForwardBusy:         return "Call Forward Busy";
        case ec_callForwardNoAnswer:     return "Call Forward No Answer";
        case ec_callNotAnswered:         return "Call Not Answered";
        case ec_callPickup:              return "Call Pickup";
        case ec_campOn:                  return "Camp On";
        case ec_destNotObtainable:       return "Destination Not Obtainable";
        case ec_doNotDisturb:            return "Do Not Disturb";
        case ec_incompatibleDestination: return "Incompatible Destination";
        case ec_invalidAccountCode:      return "Invalid Account Code";
        case ec_keyConference:           return "Key Conference";
        case ec_lockout:                 return "Lockout";
        case ec_maintenance:             return "Maintenance";
        case ec_networkCongestion:       return "Network Congestion";
        case ec_networkNotObtainable:    return "Network Not Obtainable";
        case ec_newCall:                 return "New Call";
        case ec_noAvailableAgents:       return "No Available Agents";
        case ec_overflow:                return "Overflow";
        case ec_override:                return "Override";
        case ec_park:                    return "Park";
        case ec_recall:                  return "Recall";
        case ec_redirected:              return "Redirected";
        case ec_reorderTone:             return "Reorder Tone";
        case ec_resourcesNotAvailable:   return "Resources Not Available";
        case ec_silentParticipation:     return "Silent Participation";
        case ec_transfer:                return "Transfer";
        case ec_trunksBusy:              return "Trunks Busy";
        case ec_unknown:                 return "Unknown";
        case ec_voiceUnitInitiator:      return "Voice Unit Initiator";
        }

    return "*Unknown*";
    }

//////////////////////////////////////////////////////////////////////////////
} // namespace MidCSTA