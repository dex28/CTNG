
#include "Protocols.h"

using namespace CTsvcLIB;

ProtocolClass* HTTP_Client_Protocol::Clone()
{
    return NULL;
    }

bool HTTP_Client_Protocol::OnError( DWORD dwErrorCode )
{
    DebugRC( dwErrorCode );
    LOG( DBG_ERROR ) << "-> Error code " << dwErrorCode << eline;
    return true;
    }

bool HTTP_Client_Protocol::OnConnect ()
{
    LOG( DBG_TRACE ) << "OnConnect" << eline;

    inputDataPtr = 0;
    state = WAITING_RESULT;

    if ( ! port->PostRead( inputData, sizeof( inputData ) ) )
        return false;

    static char response [] = "GET / HTTP/1.0\r\n\r\n";
    if ( ! port->PostWrite( response, sizeof( response ) - 1 ) )
        return false;

    return true;
    }

bool HTTP_Client_Protocol::OnRemoteDisconnect ()
{
    LOG( DBG_TRACE ) << "OnRemoteDisconnect" << eline;

    delete this;

    return true;
    }

bool HTTP_Client_Protocol::OnReadCompleted( DWORD dwIoSize )
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

        LOG( DBG_TRACE ) << "HTTP_Client Got: [" << inputData << "] "
            << eolP1 << " / " << inputDataPtr << eline;

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

bool HTTP_Client_Protocol::OnWriteCompleted( DWORD dwIoSize )
{
    return true;
    }

