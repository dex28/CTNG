
#include "Protocols.h"

using namespace CTsvcLIB;

TCP_Listener_Parameters SMTP_Server_Protocol::params;

ProtocolClass* SMTP_Server_Protocol::Clone()
{
    return new SMTP_Server_Protocol ();
    }

bool SMTP_Server_Protocol::OnError( DWORD dwErrorCode )
{
    DebugRC( dwErrorCode );
    LOG( DBG_ERROR ) << "-> Error code " << dwErrorCode << eline;

    delete this;

    return true;
    }

bool SMTP_Server_Protocol::OnConnect ()
{
    LOG( DBG_TRACE ) << "OnConnect" << eline;

    state = WAITING_MAIL_FROM;
    inputDataPtr = 0;
    strcpy( eoFrame, "\r\n" );
    eoFrameLen = 2;

    if ( ! port->PostRead( inputData, sizeof( inputData ) ) )
    {
        delete this;
        return false;
        }

    static unsigned char response []
        = "220 SMTP Server ready\r\n";

    port->PostWrite( response, sizeof( response ) - 1 );

    return true;
    }

bool SMTP_Server_Protocol::OnRemoteDisconnect ()
{
    LOG( DBG_TRACE ) << "OnRemoteDisconnect" << eline;

    if ( port->IsConnected () )
        delete this;

    return true;
    }

bool SMTP_Server_Protocol::OnReadCompleted( DWORD dwIoSize )
{
    DWORD eolP1 = 0;

    // Compare just epsilon area arround inputDataPtr - eoFrameLen, inputDataPtr + dwIoSize
    // for the eoFrame
    for ( size_t beg = inputDataPtr > eoFrameLen ? inputDataPtr - eoFrameLen : 0,
          end = inputDataPtr + dwIoSize > eoFrameLen ? inputDataPtr + dwIoSize - eoFrameLen : 0;
        beg <= end;
        beg++
        )
    {
        if ( memcmp( inputData + beg, eoFrame, eoFrameLen ) == 0 )
        {
            eolP1 = beg + eoFrameLen;
            inputData[ beg ] = 0;
            }
        }

    inputDataPtr += dwIoSize;
    inputData[ inputDataPtr ] = 0;

    if ( eolP1 == 0 )
    {
        // Post another async. read; We don't have eoFrame, yet.
        //
        if ( ! port->PostRead( inputData + inputDataPtr, sizeof( inputData ) - inputDataPtr ) )
        {
            delete port;
            return false;
            }
        return true;
        }

    LOG( DBG_TRACE ) << "SMTP_Server Got: [" << inputData << "] "
        << eolP1 << " / " << inputDataPtr << eline;

    if ( state == WAITING_CRLF_DOT_CRLF )
    {
        strcpy( eoFrame, "\r\n" );
        eoFrameLen = 2;

        state = WAITING_MAIL_FROM;

        static unsigned char response []
            = "250 Message accepted.\r\n";

        port->PostWrite( response, sizeof( response ) - 1 );
        }
    else if ( memcmp( inputData, "HELO", 4 ) == 0 )
    {
        static unsigned char response []
            = "250 Hello, there!\r\n";

        port->PostWrite( response, sizeof( response ) - 1 );
        }
    else if ( memcmp( inputData, "MAIL FROM:", 10 ) == 0 )
    {
        state = WAITING_RCPT_TO;

        static unsigned char response []
            = "250 OK\r\n";

        port->PostWrite( response, sizeof( response ) - 1 );
        }
    else if ( memcmp( inputData, "RCPT TO:", 8 ) == 0 )
    {
        state = WAITING_DATA;

        static unsigned char response []
            = "250 OK\r\n";

        port->PostWrite( response, sizeof( response ) - 1 );
        }
    else if ( memcmp( inputData, "DATA", 4 ) == 0 )
    {
        strcpy( eoFrame, "\r\n.\r\n" );
        eoFrameLen = 5;

        state = WAITING_CRLF_DOT_CRLF;

        static unsigned char response []
            = "354 Waiting data ended with CRLF.CRLF\r\n";

        port->PostWrite( response, sizeof( response ) - 1 );
        }
    else if ( memcmp( inputData, "QUIT", 4 ) == 0 )
    {
        state = WAITING_221_TO_COMPLETE;

        static unsigned char response []
            = "221 Closing connection\r\n";

        port->PostWrite( response, sizeof( response ) - 1 );
        }
    else
    {
        static unsigned char response []
            = "500 Command not recognized\r\n";

        port->PostWrite( response, sizeof( response ) - 1 );
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

    // Post overlapped read on socket...
    //
    if ( ! port->PostRead( inputData + inputDataPtr, sizeof( inputData ) - inputDataPtr ) )
    {
        delete port;
        return false;
        }

    return true;
    }

bool SMTP_Server_Protocol::OnWriteCompleted( DWORD dwIoSize )
{
    if ( state == WAITING_221_TO_COMPLETE )
    {
        delete this;
        return false;
        }

    return true;
    }

