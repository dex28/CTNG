#ifndef _PROTOCOLS_H_INCLUDED
#define _PROTOCOLS_H_INCLUDED

#include "CTsvcLIB.h"

#include <ctime>
#include <cstdio>

using namespace CTsvcLIB;

///////////////////////////////////////////////////////////////////////////////

/*
    +---------------------------------------------------------------+
    | 00 NUL| 01 SOH| 02 STX| 03 ETX| 04 EOT| 05 ENQ| 06 ACK| 07 BEL|
    | 08 BS | 09 HT | 0A NL | 0B VT | 0C NP | 0D CR | 0E SO | 0F SI |
    | 10 DLE| 11 DC1| 12 DC2| 13 DC3| 14 DC4| 15 NAK| 16 SYN| 17 ETB|
    | 18 CAN| 19 EM | 1A SUB| 1B ESC| 1C FS | 1D GS | 1E RS | 1F US |
    +---------------------------------------------------------------+
    | 20 SP | 21  ! | 22  " | 23  # | 24  $ | 25  % | 26  & | 27  ' |
    | 28  ( | 29  ) | 2A  * | 2B  + | 2C  , | 2D  - | 2E  . | 2F  / |
    | 30  0 | 31  1 | 32  2 | 33  3 | 34  4 | 35  5 | 36  6 | 37  7 |
    | 38  8 | 39  9 | 3A  : | 3B  ; | 3C  < | 3D  = | 3E  > | 3F  ? |
    +---------------------------------------------------------------+
    | 40  @ | 41  A | 42  B | 43  C | 44  D | 45  E | 46  F | 47  G |
    | 48  H | 49  I | 4A  J | 4B  K | 4C  L | 4D  M | 4E  N | 4F  O |
    | 50  P | 51  Q | 52  R | 53  S | 54  T | 55  U | 56  V | 57  W |
    | 58  X | 59  Y | 5A  Z | 5B  [ | 5C  \ | 5D  ] | 5E  ^ | 5F  _ |
    +---------------------------------------------------------------+
    | 60  ` | 61  a | 62  b | 63  c | 64  d | 65  e | 66  f | 67  g |
    | 68  h | 69  i | 6A  j | 6B  k | 6C  l | 6D  m | 6E  n | 6F  o |
    | 70  p | 71  q | 72  r | 73  s | 74  t | 75  u | 76  v | 77  w |
    | 78  x | 79  y | 7A  z | 7B  { | 7C  | | 7D  } | 7E  ~ | 7F DEL|
    +---------------------------------------------------------------+
*/
#define SOH "\x01"
#define STX "\x02"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// MD110 CIL Protocol
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// CIL Record

/*
    CMDR 
    ASB 501 standard format                       Bytes
    ------------------------------------------- ---------
    Space                                         0 -   2 
    End date                                      3 -   6
    End time                                      7 -  10
    Space                                        11
    Call duration time                           12 -  16
    Space                                        17
    Call metering pulses                         18 -  21
    Space                                        22
    Condition code                               23 -  24
    Space                                        25
    Access Code 1                                26 -  30
    Access Code 2                                31 -  32
    Access Code 2/ISDN CBC                       33 -  35
    Space                                        36
    Dialled number (may include Op.Que.Time)     37 -  56
    Space                                        57
    Calling number                               58 -  67
    Space                                        68
    Account code                                 69 -  83
    Space                                        84
    Authorization code                           85 -  90
    Space                                        91
    Transit Network Selection code (ISDN)        92 -  94
    Space                                        95
    Operator System Access code (ISDN)           96 -  97
    Space                                        98
    Queue time to busy external line             99 - 100
    Space                                       101
    External Line ID                            102 - 110
    Carriage return                             111  
    Line feed                                   112
    Space                                       113 - 115
*/

class CIL_Record
{
    union
    {
        char line[ 256 ]; // max 113 bytes + '\0' in length

        struct
        {
            char Space1        [ 2 ];
            char NewMonth      [ 2 ];
            char Space2        [ 2 ];
            char NewDate       [ 2 ];
            };

        struct
        {
            char Space1        [ 3 ];
            char EndDate       [ 4 ]; // MMDD
            char EndTime       [ 4 ]; // HHMM
            char Space2;
            char CallDuration  [ 5 ];
            char Space3;
            char CallMeteringPulses [ 4 ];
            char Space4;
            char CondCode      [ 2 ];
            char Space5;
            char AccessCode1   [ 5 ];
            char AccessCode2   [ 5 ];
            char Space6;
            char DialedNumber  [ 20 ];
            char Space7;
            char CallingNumber [ 10 ];
            char Space8;
            char AccountCode   [ 15 ];
            char Space9;
            char AuthorCode    [ 6 ];
            char Space10;
            char TNSC          [ 3 ];
            char Space11;
            char OSAC          [ 2 ];
            char Space12;
            char QueTime       [ 2 ];
            char Space13;
            char ExtLineID     [ 6 ];
            char Ending        [ 5 ];
            } CDR;
        };

    void TrimStr( char* chpFrom, int len )
    {
        char* chpTo = chpFrom;

        // skip spaces
        //
        while( len > 0 && *chpFrom && *chpFrom == ' ' )
        {
            chpFrom++;
            len--;
            }

        // copy non-spaces
        //
        while( len > 0 && *chpFrom && *chpFrom != ' ' )
        {
            *chpTo++ = *chpFrom++;
            len--;
            }

        // terminate result
        *chpTo = 0;
        }

public:

    bool ParseAndValidate( void* buf, int size )
    {
        memcpy( line, buf, size );
        line[ size ] = 0;

        if ( size != sizeof( CDR ) )
            return false;

        line[ sizeof( CDR ) ] = 0;

        if ( CDR.Space2 != ' ' ) return false;
	    CDR.Space2 = 0;

        if ( CDR.Space3 != ' ' ) return false;
	    CDR.Space3 = 0;

        if ( CDR.Space4 != ' ' ) return false;
	    CDR.Space4 = 0;

        if ( CDR.Space5 != ' ' ) return false;
        CDR.Space5 = 0;

        if ( CDR.Space6 != ' ' ) return false;
        CDR.Space6 = 0;

        if ( CDR.Space7 != ' ' ) return false;
	    CDR.Space7 = 0;

        if ( CDR.Space8 != ' ' ) return false;
        CDR.Space8 = 0;

        if ( CDR.Space9 != ' ' ) return false;
	    CDR.Space9 = 0;

        if ( CDR.Space10 != ' ' ) return false;
	    CDR.Space10 = 0;

        if ( CDR.Space11 != ' ' ) return false;
	    CDR.Space11 = 0;

        if ( CDR.Space12 != ' ' ) return false;
	    CDR.Space12 = 0;

        if ( CDR.Space13 != ' ' ) return false;
	    CDR.Space13 = 0;

        TrimStr( CDR.CondCode,    2  );
        TrimStr( CDR.AccessCode1, 5  );
        TrimStr( CDR.AccessCode2, 5  );
        TrimStr( CDR.AuthorCode,  6  );
        TrimStr( CDR.AccountCode, 15 );
        TrimStr( CDR.DialedNumber,    20 );
        TrimStr( CDR.CallingNumber,   10 );
        TrimStr( CDR.ExtLineID,   6  );

        return true;
        }

    time_t GetOEndTime( void )
    {
	    time_t ltime = time( NULL );

	    tm* today = localtime( &ltime );

	    sscanf( CDR.EndDate, "%2d", &today->tm_mon );
	    today->tm_mon -= 1;

	    sscanf( CDR.EndDate+2,"%2d", &today->tm_mday );

	    sscanf( CDR.EndTime,"%2d", &today->tm_hour );
	    sscanf( CDR.EndTime+2,"%2d", &today->tm_min );

	    today->tm_sec = 0;

	    ltime = mktime(today);
	    if(ltime == -1)
		    time( &ltime );

	    return ltime;
        }

    double GetCallDuration( void )
    {
	    char* stopstring;
	    return strtod( CDR.CallDuration, &stopstring ) / 10.0;
        }

    char* GetCondCode( void )
    {
        return CDR.CondCode;
        }

    char* GetAC1( void )
    {
	    return CDR.AccessCode1;
        }

    char* GetAC2( void )
    {
        return CDR.AccessCode2;
        }

    char* GetAuthorizationCode( void )
    {
        return CDR.AuthorCode;
        }

    char* GetAccountCode( void )
    {
	    return CDR.AccountCode;
        }

    char* GetDialedNum( void )
    {
        return CDR.DialedNumber;
        }

    char* GetCallingNum( void )
    {
        return CDR.CallingNumber;
        }

    char* GetLineID( void )
    {
        return CDR.ExtLineID;
        }
    };

class MD110_CMDR_Protocol : public CTsvcLIB::ProtocolClass
{
	ODBC_SESSION sess;

    char inputData[ 1024 ]; // receive buffer
    size_t inputDataPtr;

public:

    MD110_CMDR_Protocol( void )
    {
        inputDataPtr = 0;
        }

    ~MD110_CMDR_Protocol( void )
    {
        }

private:

    bool InsertIntoDatabase( char* buf, int len );
    
    // ProtocolClass implementation
    ProtocolClass* Clone ();
    bool OnReadCompleted( DWORD dwIoSize );
    bool OnWriteCompleted( DWORD dwIoSize );
    bool OnError( DWORD dwErrorCode );
    bool OnConnect ();
    bool OnRemoteDisconnect();
    };

//////////////////////////////////////////////////////////////////////////////
// MD110 MIS Protocol

class MD110_MIS_Protocol : public CTsvcLIB::ProtocolClass
{
    char* identity;

    char inputData[ 1024 ]; // receive buffer
    size_t inputDataPtr;

    char outputData[ 1024 ]; // transmitt buffer
    size_t outputDataLen;

public:

    MD110_MIS_Protocol( void )
    {
        identity = "MIS";

        inputDataPtr = 0;
        outputDataLen = 0;
        }

    ~MD110_MIS_Protocol( void )
    {
        }

private:

    // ProtocolClass implementation
    ProtocolClass* Clone ();
    bool OnReadCompleted( DWORD dwIoSize );
    bool OnWriteCompleted( DWORD dwIoSize );
    bool OnError( DWORD dwErrorCode );
    bool OnConnect ();
    bool OnRemoteDisconnect ();
    };

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// MD110 ICU Protocol (can be ICS or VM)
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

// Signal              Non Ethernet format     Ethernet format  
// ---------------------------------------------------------------
// Initial update      STX 54 CR LF            SOH K STX 54 CR LF  
//
// and the acknowledgement
// signal from the receiving side is:  
//                     none                    SOH K STX 93 CR LF
//

class MD110_ICU_Protocol : public CTsvcLIB::ProtocolClass
{
    char inputData[ 1024 ]; // receive buffer
    size_t inputDataPtr;

    char outputData[ 1024 ]; // transmitt buffer
    size_t outputDataLen;

public:

    MD110_ICU_Protocol( void )
    {
        inputDataPtr = 0;
        outputDataLen = 0;
        }

    ~MD110_ICU_Protocol( void )
    {
        }

private:

    // ProtocolClass implementation
    ProtocolClass* Clone ();
    bool OnReadCompleted( DWORD dwIoSize );
    bool OnWriteCompleted( DWORD dwIoSize );
    bool OnError( DWORD dwErrorCode );
    bool OnConnect ();
    bool OnRemoteDisconnect ();
    };

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// MD110 MML Protocol
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

class MD110_MML_Protocol : public CTsvcLIB::ProtocolClass
{
    char inputData[ 1024 ]; // receive buffer
    size_t inputDataPtr;

    char outputData[ 1024 ]; // transmitt buffer
    size_t outputDataLen;

public:

    MD110_MML_Protocol( void )
    {
        inputDataPtr = 0;
        outputDataLen = 0;
        }

    ~MD110_MML_Protocol( void )
    {
        }

private:

    // ProtocolClass implementation
    ProtocolClass* Clone ();
    bool OnReadCompleted( DWORD dwIoSize );
    bool OnWriteCompleted( DWORD dwIoSize );
    bool OnError( DWORD dwErrorCode );
    bool OnConnect ();
    bool OnRemoteDisconnect ();
    };

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// CIMD2 Protocol
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

enum CIMD2_Command_ID
{
    idLogon                 = 0x01,
    idLogoff                = 0x02,
    idSubmitMessage         = 0x03
    };

enum CIMD2_Param_ID
{
    idUnknown               = -1,
    idUserIdentity          = 0x010,
    idPassword              = 0x011,
    idDestinationAddress    = 0x021,
    idOriginatingAddress    = 0x023,
    idUserData              = 0x033,
    idStatusReportRequest   = 0x056,
    idCancelEnabled         = 0x058
    };

class CIMD2_Message
{
    unsigned char msg[ 1024 ];
    int msgLen;
    CIMD2_Param_ID lastId;

public:

    static int GetChecksum( const unsigned char* msg, int msgLen )
    {
        int checksum = 0;

        for ( int i = 0; i < msgLen; i++ )
            checksum = ( checksum + msg[ i ] ) & 0xFF;

        return checksum;
        }

    int Len () const
        { return msgLen; }

    unsigned char* Data ()
        { return msg; }

    CIMD2_Message()
    {
        lastId = idUnknown;
        msgLen = 0;
        }
    
    CIMD2_Message& Begin( const CIMD2_Command_ID cmd, int seqNo )
    {
        // Create header:
        //   [STX] <cmdId> : <seqNo> [TAB]
        //
        lastId = idUnknown;
        msgLen = sprintf( (char*)msg, "\x02" "%02d:%03d\t", cmd, seqNo );
        return *this;
        }

    CIMD2_Message& End( void )
    {
        // Calculate checksum
        int checksum = GetChecksum( msg, msgLen );

        // Append trailer:
        //   <checksum> [ETX]
        //
        msgLen += sprintf( (char*)msg + msgLen, "%02X\x03", checksum );
        return *this;
        }

    CIMD2_Message& operator << ( const CIMD2_Param_ID id )
    {
        // Append parameter id with null value; end with [TAB]
        //
        lastId = id;
        msgLen += sprintf( (char*)msg + msgLen, "%03X:\t", id );
        return *this;
        }

    CIMD2_Message& operator << ( const int value )
    {
        // Append value to parameter; overwrite [TAB] with value + [TAB]
        //
        msgLen += sprintf( (char*)msg + msgLen - 1, "%d\t", value ) - 1;
        return *this;
        }

    CIMD2_Message& operator << ( const char* value )
    {
        // Append value to parameter; overwrite [TAB] with value + [TAB]
        //
        msgLen += sprintf( (char*)msg + msgLen - 1, "%s\t", value ) - 1;
        return *this;
        }
    };

class CIMD2_Protocol : public CTsvcLIB::ProtocolClass
{
    char inputData[ 1024 ]; // receive buffer
    size_t inputDataPtr;

    char outputData[ 1024 ]; // transmitt buffer
    size_t outputDataLen;

    CIMD2_Message msg;

public:

    CIMD2_Protocol( void )
    {
        inputDataPtr = 0;
        outputDataLen = 0;
        }

    ~CIMD2_Protocol( void )
    {
        }

private:

    // ProtocolClass implementation
    ProtocolClass* Clone ();
    bool OnReadCompleted( DWORD dwIoSize );
    bool OnWriteCompleted( DWORD dwIoSize );
    bool OnError( DWORD dwErrorCode );
    bool OnConnect ();
    bool OnRemoteDisconnect ();
    };

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// SMTP Client Protocol
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

class SMTP_Client_Protocol : public CTsvcLIB::ProtocolClass
{
    QCPortPool* portPool;
    char remote_ip_addr[ 256 ];
    unsigned short remote_tcp_port;

    char inputData[ 1024 ]; // receive buffer
    size_t inputDataPtr;

    char outputData[ 1024 ]; // transmitt buffer
    size_t outputDataLen;

    enum
    {
        WAITING_220,
        HELO_SENT,
        MAIL_FROM_SENT,
        RCPT_TO_SENT,
        DATA_SENT,
        QUIT_SENT
        } state;

public:

    SMTP_Client_Protocol( QCPortPool* pool, char* addr, unsigned short port = 25 )
    {
        strcpy( remote_ip_addr, addr );
        remote_tcp_port = port;
        portPool = pool;

        inputDataPtr = 0;
        outputDataLen = 0;
        }

    ~SMTP_Client_Protocol( void )
    {
        }

    void Initiate( void )
    {
        QCPort_TCP* p = new CTsvcLIB::QCPort_TCP( portPool, this );
        p->OpenConnection( remote_ip_addr, remote_tcp_port );
        }

private:

    // ProtocolClass implementation
    ProtocolClass* Clone ();
    bool OnReadCompleted( DWORD dwIoSize );
    bool OnWriteCompleted( DWORD dwIoSize );
    bool OnError( DWORD dwErrorCode );
    bool OnConnect ();
    bool OnRemoteDisconnect ();
    };

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// SMTP Server Protocol
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

class SMTP_Server_Protocol : public CTsvcLIB::ProtocolClass
{
    static TCP_Listener_Parameters params;

    char eoFrame[ 16 ];
    size_t eoFrameLen;

    char inputData[ 10240 ]; // receive buffer
    size_t inputDataPtr;

    char outputData[ 1024 ]; // transmitt buffer
    size_t outputDataLen;

    enum
    {
        NOT_CONNECTED,
        WAITING_MAIL_FROM,
        WAITING_RCPT_TO,
        WAITING_DATA,
        WAITING_CRLF_DOT_CRLF,
        WAITING_221_TO_COMPLETE
        } state;

public:

    SMTP_Server_Protocol( QCPortPool* pool, unsigned short local_tcp_port = 25 )
    {
        params.local_IP_address = INADDR_ANY;
        params.local_TCP_port = local_tcp_port;
        params.pool = pool;
        params.seed = this; // this is the master copy that will be cloned

        pool->Start_TCP_Listener( params );

        eoFrameLen = 0;
        inputDataPtr = 0;
        outputDataLen = 0;
        state = NOT_CONNECTED;
        }

    SMTP_Server_Protocol( void ) // used by clone
    {
        eoFrameLen = 0;
        inputDataPtr = 0;
        outputDataLen = 0;
        state = NOT_CONNECTED;
        }

    ~SMTP_Server_Protocol( void )
    {
        }

private:

    // ProtocolClass implementation
    ProtocolClass* Clone ();
    bool OnReadCompleted( DWORD dwIoSize );
    bool OnWriteCompleted( DWORD dwIoSize );
    bool OnError( DWORD dwErrorCode );
    bool OnConnect ();
    bool OnRemoteDisconnect ();
    };

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// HTTP Server Protocol
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Miscellaneous inlines
//
static inline int
x2c( PCHAR src )
{
    int digit =  src[ 0 ] >= 'A' ?
             ( ( src[ 0 ] & 0xdf ) - 'A' ) + 10 : ( src[ 0 ] - '0' );
    digit *= 16;
    digit += src[ 1 ] >= 'A' ? 
             ( ( src[ 1 ] & 0xdf ) - 'A' ) + 10 : ( src[ 1 ] - '0' );
    return digit;
    }

static inline BOOL
is_filetype( char* url, char* ftype )
{
    int len1 = strlen( url );
    int len2 = strlen( ftype );

    if ( len1 < len2 )
        return FALSE;

    return strnicmp( url + len1 - len2, ftype, len2 ) == 0;
    }

class HTTP_Server_Protocol : public CTsvcLIB::ProtocolClass
{
    static TCP_Listener_Parameters params;

    class CGI_fields
    {
        char* data;
        int ed_count;
    public:
        CGI_fields( void) { data = NULL; ed_count = 0; }
        void Create( char* pContentData );
        void Dump ();
        const char* Data( void ) { return data; }
        char* A( int n );
        char* V( int n );
        char* operator[] ( char* field_name );
        int FieldCount () { return ed_count; }
        };

    DWORD XmtBufLen;              // transmitt buffer length
    CHAR XmtBuffer[ 8192 ];       // transmitt buffer

    DWORD BufLen;                 // receive buffer length
    PCHAR BufP;                   // current pointer in receive buffer
    CHAR Buffer[ 8192 ];          // receive buffer

    enum STATE
    {
        Rcv_HTTP_Header,
        Rcv_HTTP_Body
        } State;                  // connection state

    DWORD pktSize;                // last HTTP packet size

    int iHeadLen;                 // header length
    int iContentLen;              // contents length
    PCHAR pContentData;           // posted contents data

                                  // parsed header values
    PCHAR method;                 // method:
    PCHAR requested_uri;          // requested URI
    PCHAR version;                // version
    PCHAR content_type;           // content type
    PCHAR content_length;         // content length
    PCHAR keep_alive;             // keep alive
    PCHAR referer;                // referer

    CGI_fields cf;                // parsed cgi-fields (created in jsp_handler)
    
    void WriteMime( char* method, char* type, char* filename );

    // buffered synchronous write
    //
    BOOL Write( void* buffer, size_t buffer_length );
    BOOL Printf( char* fmt, ... );
    BOOL PrintfLn( char* fmt, ... ); // print terminated with CRLF
    BOOL FlushXmtBuffer ();

public:

    HTTP_Server_Protocol( QCPortPool* pool, unsigned short local_tcp_port = 80 )
    {
        params.local_IP_address = INADDR_ANY;
        params.local_TCP_port = local_tcp_port;
        params.pool = pool;
        params.seed = this; // this is the master copy that will be cloned

        pool->Start_TCP_Listener( params );

        XmtBufLen = 0;
        BufP = Buffer;
        BufLen = 0;
        State = Rcv_HTTP_Header;
        }

    HTTP_Server_Protocol( void ) // used by clone
    {
        XmtBufLen = 0;
        BufP = Buffer;
        BufLen = 0;
        State = Rcv_HTTP_Header;
        }

    ~HTTP_Server_Protocol( void )
    {
        }

private:

    // ProtocolClass implementation
    ProtocolClass* Clone ();
    bool OnReadCompleted( DWORD dwIoSize );
    bool OnWriteCompleted( DWORD dwIoSize );
    bool OnError( DWORD dwErrorCode );
    bool OnConnect ();
    bool OnRemoteDisconnect ();
    };

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// HTTP Client Protocol
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

class HTTP_Client_Protocol : public CTsvcLIB::ProtocolClass
{
    QCPortPool* portPool;
     char remote_ip_addr[ 256 ];
    unsigned short remote_tcp_port;

    char inputData[ 1024 ]; // receive buffer
    size_t inputDataPtr;

    char outputData[ 1024 ]; // transmitt buffer
    size_t outputDataLen;

    enum
    {
        WAITING_RESULT
        } state;

public:

    HTTP_Client_Protocol( QCPortPool* pool, char* addr, unsigned short port = 80 )
    {
        strcpy( remote_ip_addr, addr );
        remote_tcp_port = port;
        portPool = pool;

        inputDataPtr = 0;
        outputDataLen = 0;
        }

    ~HTTP_Client_Protocol( void )
    {
        }

    void Initiate( void )
    {
        QCPort_TCP* p = new CTsvcLIB::QCPort_TCP( portPool, this );
        p->OpenConnection( remote_ip_addr, remote_tcp_port );
        }

private:

    // ProtocolClass implementation
    ProtocolClass* Clone ();
    bool OnReadCompleted( DWORD dwIoSize );
    bool OnWriteCompleted( DWORD dwIoSize );
    bool OnError( DWORD dwErrorCode );
    bool OnConnect ();
    bool OnRemoteDisconnect ();
    };

#endif // _PROTOCOLS_H_INCLUDED