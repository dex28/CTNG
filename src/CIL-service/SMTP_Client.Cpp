
#include "Protocols.h"

using namespace CTsvcLIB;

ProtocolClass* SMTP_Client_Protocol::Clone()
{
    return NULL;
    }

bool SMTP_Client_Protocol::OnError( DWORD dwErrorCode )
{
    DebugRC( dwErrorCode );
    LOG( DBG_ERROR ) << "-> Error code " << dwErrorCode << eline;
    return true;
    }

bool SMTP_Client_Protocol::OnConnect ()
{
    LOG( DBG_TRACE ) << "OnConnect" << eline;

    inputDataPtr = 0;
    state = WAITING_220;

    if ( ! port->PostRead( inputData, sizeof( inputData ) ) )
        return false;

    return true;
    }

bool SMTP_Client_Protocol::OnRemoteDisconnect ()
{
    LOG( DBG_TRACE ) << "OnRemoteDisconnect" << eline;

    // we are client; should we reconnect !?
    if ( port )
    {
        // Remove connection
        delete port;

        Sleep( 1000 );

        // Create new connection
        QCPort_TCP* p = new CTsvcLIB::QCPort_TCP( portPool, this );
        p->OpenConnection( remote_ip_addr, remote_tcp_port );
        }

    return true;
    }

bool SMTP_Client_Protocol::OnReadCompleted( DWORD dwIoSize )
{
    inputDataPtr += dwIoSize;
    inputData[ inputDataPtr ] = 0;

    char* eolP = strstr( (const char*)inputData, "\r\n" );
    if ( eolP )
    {
        *eolP = 0;
        DWORD eolP1 = eolP - inputData + 2;

        LOG( DBG_TRACE ) << "SMTP_Client Got: [" << inputData << "] "
            << eolP1 << " / " << inputDataPtr << eline;

        if ( state == WAITING_220 && memcmp( inputData, "220", 3 ) == 0 )
        {
            state = HELO_SENT;

            outputDataLen = sprintf( outputData, "HELO\r\n" );

            port->PostWrite( outputData, outputDataLen );
            }
        else if ( state == HELO_SENT && memcmp( inputData, "250", 3 ) == 0 )
        {
            state = MAIL_FROM_SENT;

            outputDataLen = sprintf( outputData, "MAIL FROM: mikica@dssab.com\r\n" );

            port->PostWrite( outputData, outputDataLen );
            }
        else if ( state == MAIL_FROM_SENT && memcmp( inputData, "250", 3 ) == 0 )
        {
            state = RCPT_TO_SENT;

            outputDataLen = sprintf( outputData, "RCPT TO: mikica@dssab.com\r\n" );

            port->PostWrite( outputData, outputDataLen );
            }
        else if ( state == RCPT_TO_SENT && memcmp( inputData, "250", 3 ) == 0 )
        {
            state = DATA_SENT;

            outputDataLen = sprintf( outputData, "DATA\r\n" );

            port->PostWrite( outputData, outputDataLen );
            }
        else if ( state == DATA_SENT && memcmp( inputData, "354", 3 ) == 0 )
        {
            state = DATA_SENT;

            outputDataLen = sprintf( outputData,
                "Subject: %s\r\n"
                "From: %s\r\n"
                "To: %s\r\n"
                "\r\n"
                "%s\r\n"
                ".\r\n",
                "---subject---",
                "---from---",
                "---to----",
                "Message text"
                );

            port->PostWrite( outputData, outputDataLen );
            }
        else if ( state == DATA_SENT && memcmp( inputData, "250", 3 ) == 0 )
        {
            state = QUIT_SENT;

            outputDataLen = sprintf( outputData, "QUIT\r\n" );

            port->PostWrite( outputData, outputDataLen );
            }
        else if ( state == QUIT_SENT && memcmp( inputData, "221", 3 ) == 0 )
        {
            delete this;
            return false;
            }

        if ( eolP1 > inputDataPtr )
        {
            memmove( inputData, inputData + eolP1, inputDataPtr - eolP1 );
            inputDataPtr = inputDataPtr - eolP1;
            }
        else
        {
            inputDataPtr = 0;
            }
        }

    // Post overlapped read on socket...
    //
    bool rc = port->PostRead( inputData + inputDataPtr, sizeof( inputData ) - inputDataPtr );

    return rc;
    }

bool SMTP_Client_Protocol::OnWriteCompleted( DWORD dwIoSize )
{
    return true;
    }

