
#include "Protocols.h"


ProtocolClass* CIMD2_Protocol::Clone()
{
    return new CIMD2_Protocol ();
    }

bool CIMD2_Protocol::OnError( DWORD dwErrorCode )
{
    DebugRC( dwErrorCode );
    LOG( DBG_ERROR ) << "-> Error code " << dwErrorCode << eline;
    return true;
    }

bool CIMD2_Protocol::OnConnect ()
{
    LOG( DBG_TRACE ) << "OnConnect" << eline;

    inputDataPtr = 0;

    if ( ! port->PostRead( inputData, sizeof( inputData ) ) )
        return false;

    return true;
    }

bool CIMD2_Protocol::OnRemoteDisconnect ()
{
    LOG( DBG_TRACE ) << "OnRemoteDisconnect" << eline;

    // we are client; should we reconnect !?

    return true;
    }

bool CIMD2_Protocol::OnReadCompleted( DWORD dwIoSize )
{
    inputDataPtr += dwIoSize;
    inputData[ inputDataPtr ] = 0;

AGAIN:
    char* eolP = strstr( (const char*)inputData, "\x03" );
    if ( eolP )
    {
        *eolP = 0;
        DWORD eolP1 = eolP - inputData + 1;

        LOG( DBG_TRACE ) << "CIMD2 Got: [" << inputData << "] "
            << eolP1 << " / " << inputDataPtr << eline;

        if ( memcmp( inputData, "\x02" "51", 3 ) == 0 )
        {
            LOG( DBG_TRACE ) << "logon was successfull" << eline;

            msg.Begin( idSubmitMessage, 3 )
                << idDestinationAddress  << "46701832806"
                << idOriginatingAddress  << "7777"
                << idUserData            << "DDTPV-TXMX7-BBGJ9-WGY8K-B9GHM"
                << idStatusReportRequest << 31
                << idCancelEnabled       << 1;
            msg.End ();

            LOG( DBG_TRACE ) << "Sent: " << msg.Data() << eline;

            port->PostWrite( msg.Data (), msg.Len () );
            }

        if ( inputDataPtr > eolP1 )
        {
            memmove( inputData, inputData + eolP1, inputDataPtr - eolP1 );
            inputDataPtr = inputDataPtr - eolP1;
            goto AGAIN;
            }
        else
        {
            inputDataPtr = 0;
            }
        }
    else
    {
        eolP = strstr( (const char*)inputData, "\n" );
        if ( eolP )
        {
            LOG( DBG_TRACE ) << "hello received, sent password!" << eline;

            msg.Begin( idLogon, 1 )
                << idUserIdentity << "DSSABTEST"
                << idPassword     << "1234";
            msg.End ();

            LOG( DBG_TRACE ) << "Sent: " << msg.Data () << eline;

            port->PostWrite( msg.Data (), msg.Len () );

            inputDataPtr = 0;
            }
        }

    // Post overlapped read on socket...
    //
    bool rc = port->PostRead( inputData + inputDataPtr, sizeof( inputData ) - inputDataPtr );

    return rc;
    }

bool CIMD2_Protocol::OnWriteCompleted( DWORD dwIoSize )
{
    return true;
    }


