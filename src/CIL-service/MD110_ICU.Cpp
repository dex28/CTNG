
#include "Protocols.h"

using namespace CTsvcLIB;

ProtocolClass* MD110_ICU_Protocol::Clone()
{
    return new MD110_ICU_Protocol ();
    }

bool MD110_ICU_Protocol::OnError( DWORD dwErrorCode )
{
    DebugRC( dwErrorCode );
    LOG( DBG_ERROR ) << "-> Error code " << dwErrorCode << eline;
    return true;
    }

bool MD110_ICU_Protocol::OnConnect ()
{
    LOG( DBG_TRACE ) << "OnConnect" << eline;

    inputDataPtr = 0;

    if ( ! port->PostRead( inputData, sizeof( inputData ) ) )
        return false;

    return true;
    }

bool MD110_ICU_Protocol::OnRemoteDisconnect ()
{
    LOG( DBG_TRACE ) << "OnRemoteDisconnect" << eline;

    if ( port->IsConnected () )
        delete this;

    return true;
    }

bool MD110_ICU_Protocol::OnReadCompleted( DWORD dwIoSize )
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

        LOG( DBG_TRACE ) << "ICU Got: [" << inputData << "] "
            << eolP1 << " / " << inputDataPtr << eline;

        // Ethernet packet start with [SOH] K, where K is 3 byte ascii seq. code.
        // Ethernet packet must to be acknowledged.
        //
        if ( inputData[ 0 ] == 0x01 ) // begins with [SOH]
        {
            if ( memcmp( inputData + 4, STX "98", 3 ) == 0 )
            {
                // Heartbeat check received
                //      [STX] 98 [CR] [LF]
                //
                static const unsigned char response [] =
                {
                    0x01, 0x30, 0x30, 0x30, // SOH K
                    0x02,  '9',  '3', 0x0D, 0x0A // STX 93 CR LF
                    //0x01, 0x32, 0x31, 0x32, // SOH K
                    //0x02,  '9',  '9', 0x0D, 0x0A // STX 99 CR LF
                    };

                // Send response
                outputDataLen = sizeof( response );
                memcpy( outputData, response, outputDataLen );
                memcpy( outputData + 1, inputData + 1, 3 ); // put the same K in response
                port->PostWrite( outputData, outputDataLen );
                }
            else
            {
                // Acknowledge received information
                //
                static const unsigned char response [] =
                {
                    0x01, 0x30, 0x30, 0x30, // SOH K
                    0x02,  '9',  '3', 0x0D, 0x0A // STX 93 CR LF
                    };

                // Send response
                outputDataLen = sizeof( response );
                memcpy( outputData, response, outputDataLen );
                memcpy( outputData + 1, inputData + 1, 3 ); // put the same K in response
                port->PostWrite( outputData, outputDataLen );
                }
            }
        else
        {
            char response [] = "Are you nuts?\r\n";
            port->PostWrite( response, sizeof( response ) - 1 );
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

bool MD110_ICU_Protocol::OnWriteCompleted( DWORD dwIoSize )
{
    return true;
    }

