//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//


//
// Define the severity codes
//


//
// MessageId: MC_SERVICE_STARTED
//
// MessageText:
//
//  The CTNG Service started sucessfully.
//
#define MC_SERVICE_STARTED               0x00001000L

//
// MessageId: MC_SERVICE_STOPPED
//
// MessageText:
//
//  The CTNG Service stopped.
//
#define MC_SERVICE_STOPPED               0x00001001L

//
// MessageId: MC_HANDLER_NOT_INSTALLED
//
// MessageText:
//
//  Handler not installed.
//
#define MC_HANDLER_NOT_INSTALLED         0x00001002L

//
// MessageId: MC_BAD_SERVICE_REQUEST
//
// MessageText:
//
//  Bad service request.
//
#define MC_BAD_SERVICE_REQUEST           0x00001003L

