
#include "Protocols.h"

using namespace CTsvcLIB;

ProtocolClass* MD110_CMDR_Protocol::Clone()
{
    return new MD110_CMDR_Protocol ();
    }

bool MD110_CMDR_Protocol::OnError( DWORD dwErrorCode )
{
    DebugRC( dwErrorCode );
    LOG( DBG_ERROR ) << "-> Error code " << dwErrorCode << eline;
    return true;
    }

bool MD110_CMDR_Protocol::OnConnect ()
{
    LOG( DBG_TRACE ) << "OnConnect" << eline;

    extern char sa_password[];
    sess.Connect( "CIL", "sa", sa_password );

    inputDataPtr = 0;

    if ( ! port->PostRead( inputData, sizeof( inputData ) ) )
        return false;

    return true;
    }

bool MD110_CMDR_Protocol::OnRemoteDisconnect ()
{
    LOG( DBG_TRACE ) << "OnRemoteDisconnect" << eline;

    if ( port->IsConnected () )
        delete this;

    return true;
    }

bool MD110_CMDR_Protocol::OnReadCompleted( DWORD dwIoSize )
{
    inputDataPtr += dwIoSize;
    inputData[ inputDataPtr ] = 0;

    for ( ;; )
    {
        char* eolP = strstr( (const char*)inputData, "\r\n" );
        if ( ! eolP )
            break;

        *eolP = 0;
        DWORD eolP1 = eolP - inputData + 2;

        LOG( DBG_TRACE ) << "CIL Got: [" << inputData << "] "
            << eolP1 << " / " << inputDataPtr << eline;

        if ( ! InsertIntoDatabase( inputData, eolP1 ) )
        {
            if ( eolP1 == 8 )
            {
                delete port;
                return false;
                }
            }

        if ( inputDataPtr <= eolP1 )
        {
            inputDataPtr = 0;
            break;
            }

        memmove( inputData, inputData + eolP1, inputDataPtr - eolP1 );
        inputDataPtr = inputDataPtr - eolP1;
        }

    // Post overlapped read on socket...
    //
    bool rc = port->PostRead( inputData + inputDataPtr, sizeof( inputData ) - inputDataPtr );

    return rc;
    }

bool MD110_CMDR_Protocol::OnWriteCompleted( DWORD dwIoSize )
{
    return true;
    }

bool MD110_CMDR_Protocol::InsertIntoDatabase( char* buf, int len )
{
    ODBC_STATEMENT stmt( &sess );

    CIL_Record cdr;

    if ( ! cdr.ParseAndValidate( buf, len ) )
    {
        LOG( DBG_ERROR ) << "Invalid record received: " << buf << eline;
        return false;
        }

	ODBC_TIMESTAMP tEndTime;
	ODBC_DOUBLE fCallDuration;
	ODBC_<char[40]> fCondCode;
	ODBC_<char[40]> fAC1;
	ODBC_<char[40]> fAC2;
	ODBC_<char[40]> fDialdNum;
	ODBC_<char[40]> fCallingNum;
	ODBC_<char[40]> fLineID;
	ODBC_<char[40]> fAuthCode;
	ODBC_<char[40]> fAccCode;

	time_t ETime            = cdr.GetOEndTime();
	tm* EndTime             = localtime(&ETime);
	tEndTime.value.year     = EndTime->tm_year+1900;
	tEndTime.value.month    = EndTime->tm_mon+1;
	tEndTime.value.day      = EndTime->tm_mday;
	tEndTime.value.hour     = EndTime->tm_hour;
	tEndTime.value.minute   = EndTime->tm_min;
	tEndTime.value.second   = EndTime->tm_sec;
	tEndTime.value.fraction = 0;

	fCallDuration   = cdr.GetCallDuration();
	fCondCode       = cdr.GetCondCode();
	fAC1            = cdr.GetAC1();
	fAC2            = cdr.GetAC2();
	fDialdNum       = cdr.GetDialedNum();
	fCallingNum     = cdr.GetCallingNum();
	fLineID         = cdr.GetLineID();
	fAuthCode       = cdr.GetAuthorizationCode();
	fAccCode        = cdr.GetAccountCode();

    stmt.Prepare(
        "INSERT INTO dbo.CIL ("
        "    Call_end, Call_dur, Cond_code, Access1, Access2, "
        "    Dialed_num, Calling_num, LineID, Author_code, Account_code "
        "    ) VALUES ( ?,?,?,?,?,?,?,?,?,? )"
        );

    stmt << tEndTime
        << fCallDuration
        << fCondCode
        << fAC1
        << fAC2
        << fDialdNum
        << fCallingNum
        << fLineID
        << fAuthCode
        << fAccCode;

    stmt.Execute();

    return true;
    }
