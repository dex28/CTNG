
#include "Protocols.h"

using namespace CTsvcLIB;

ProtocolClass* MD110_MIS_Protocol::Clone()
{
    return new MD110_MIS_Protocol ();
    }

bool MD110_MIS_Protocol::OnError( DWORD dwErrorCode )
{
    DebugRC( dwErrorCode );
    LOG( DBG_ERROR ) << "-> Error code " << dwErrorCode << eline;
    return true;
    }

bool MD110_MIS_Protocol::OnConnect ()
{
    LOG( DBG_TRACE ) << "OnConnect" << eline;

    inputDataPtr = 0;

    if ( ! port->PostRead( inputData, sizeof( inputData ) ) )
        return false;

    return true;
    }

bool MD110_MIS_Protocol::OnRemoteDisconnect ()
{
    LOG( DBG_TRACE ) << "OnRemoteDisconnect" << eline;

    // we are client; should we reconnect !?

    return true;
    }

bool MD110_MIS_Protocol::OnReadCompleted( DWORD dwIoSize )
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

        LOG( DBG_TRACE ) << "MIS Got: [" << inputData << "] "
            << eolP1 << " / " << inputDataPtr << eline;

        if ( memcmp( inputData, STX "12", 3 ) == 0 )
        {
            // IDENTITITY REQUEST
            //      [STX] 12 [CR] [LF]
            // IDENTITIY RESPONSE
            //      AA BB 15 G*14
            //
            LOG( DBG_TRACE ) << "IDENTITITY REQUEST" << eline;

            static const unsigned char response [] =
            {
                0xCD, 0xDC, 0x00, 0x0F, // header: AA BB
                0x0F,                   // 15
                0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, // G*14
                0x20, 0x20, 0x20, 0x20, 0x20, 0x20              // -"-
                };

            // Send response
            outputDataLen = sizeof( response );
            memcpy( outputData, response, outputDataLen );
            memcpy( outputData + 5, identity, strlen( identity ) );
            port->PostWrite( outputData, outputDataLen );
            }
        else if ( memcmp( inputData, STX "13", 3 ) == 0 )
        {
            // STAREQ
            //      [STX] 13 [CR] [LF]
            // STAANS
            //      AA BB 14
            //
            LOG( DBG_TRACE ) << "STAREQ" << eline;

            static unsigned char response [] =
            {
                0xCD, 0xDC, 0x00, 0x01, // header: AA BB
                0x0E                    // 14
                };

            // Send response
            port->PostWrite( response, sizeof( response ) );
            }
        else if ( memcmp( inputData, STX "11", 3 ) == 0 )
        {
            // CLOSE REQUEST
            //      [STX] 11 C [CR] [LF]
            //
            LOG( DBG_TRACE ) << "CLOSE REQUEST" << eline;

            delete this;
            return false;
            }
        else if ( memcmp( inputData, STX "14", 3 ) == 0 )
        {
            // STAANS
            //      [STX] 14 [CR] [LF]
            //
            LOG( DBG_TRACE ) << "STAANS" << eline;
            }
        else if ( memcmp( inputData, STX "10", 3 ) == 0 )
        {
            // ASB INFORMATION
            //      [STX] 10 RRR LLL [CR] [LF]
            //
            LOG( DBG_TRACE ) << "ASB INFORMATION" << eline;
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

bool MD110_MIS_Protocol::OnWriteCompleted( DWORD dwIoSize )
{
    return true;
    }

