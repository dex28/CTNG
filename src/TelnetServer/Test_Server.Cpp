
#include "Protocols.h"

using namespace CTsvcLIB;

TCP_Listener_Parameters Test_Server_Protocol::params;

ProtocolClass* Test_Server_Protocol::Clone()
{
    return new Test_Server_Protocol ();
    }

bool Test_Server_Protocol::OnError( DWORD dwErrorCode )
{
    DebugRC( dwErrorCode );
    LOG( DBG_ERROR ) << "-> Error code " << dwErrorCode << eline;

    delete this;

    return true;
    }

bool Test_Server_Protocol::OnConnect ()
{
    LOG( DBG_TRACE ) << "OnConnect" << eline;

    inputDataPtr = 0;
    strcpy( eoFrame, "\r\n" );
    eoFrameLen = 2;

    if ( ! port->PostRead( inputData, sizeof( inputData ) ) )
    {
        delete this;
        return false;
        }

    static unsigned char response []
        = "Test Server ready\r\n";

    port->PostWrite( response, sizeof( response ) - 1 );

    return true;
    }

bool Test_Server_Protocol::OnRemoteDisconnect ()
{
    LOG( DBG_TRACE ) << "OnRemoteDisconnect" << eline;

    if ( port->IsConnected () )
        delete this;

    return true;
    }

bool Test_Server_Protocol::OnReadCompleted( DWORD dwIoSize )
{
    inputDataPtr += dwIoSize;
    inputData[ inputDataPtr ] = 0;

    LOG( DBG_TRACE ) << inputData;

    inputDataPtr = 0;

    // Post overlapped read on socket...
    //
    if ( ! port->PostRead( inputData + inputDataPtr, sizeof( inputData ) - inputDataPtr ) )
    {
        delete port;
        return false;
        }

    return true;
    }

bool Test_Server_Protocol::OnWriteCompleted( DWORD dwIoSize )
{
    return true;
    }

