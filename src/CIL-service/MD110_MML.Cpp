
#include "Protocols.h"

using namespace CTsvcLIB;

ProtocolClass* MD110_MML_Protocol::Clone()
{
    return new MD110_MML_Protocol ();
    }

bool MD110_MML_Protocol::OnError( DWORD dwErrorCode )
{
    DebugRC( dwErrorCode );
    LOG( DBG_ERROR ) << "-> Error code " << dwErrorCode << eline;
    return true;
    }

bool MD110_MML_Protocol::OnConnect ()
{
    LOG( DBG_TRACE ) << "OnConnect" << eline;

    inputDataPtr = 0;

    if ( ! port->PostRead( inputData, sizeof( inputData ) ) )
        return false;

    return true;
    }

bool MD110_MML_Protocol::OnRemoteDisconnect ()
{
    LOG( DBG_TRACE ) << "OnRemoteDisconnect" << eline;

    // we are client; should we reconnect !?

    return true;
    }

bool MD110_MML_Protocol::OnReadCompleted( DWORD dwIoSize )
{
    inputDataPtr += dwIoSize;
    inputData[ inputDataPtr ] = 0;

AGAIN:
    char* eolP = strstr( (const char*)inputData, "<\x1C" );
    if ( eolP )
    {
        *eolP = 0;
        DWORD eolP1 = eolP - inputData + 2;

        LOG( DBG_TRACE ) << "MML Got: [" << inputData << "] "
            << eolP1 << " / " << inputDataPtr << eline;

        if ( memcmp( inputData, "SSS;", 4 ) == 0 )
        {
            static char response [] = "MDUSER\r\n";
            port->PostWrite( response, sizeof( response ) - 1 );
            }
        else if ( memcmp( inputData, "MDUSER", 6 ) == 0 )
        {
            static char response [] = "HELP\r\n";
            port->PostWrite( response, sizeof( response ) - 1 );
            }
        else if ( strstr( (const char*)inputData, "AUTHORITY CLASS" ) )
        {
            Sleep( 1000 );
            static char response [] = "ACCSP:GRP=ALL;\r\n";
            port->PostWrite( response, sizeof( response ) - 1 );
            }
        else if ( strstr( (const char*)inputData, "ACCSP:GRP=ALL;" ) )
        {
            Sleep( 1000 );
            static char response [] = "ACCSP:GRP=ALL;\r\n";
            port->PostWrite( response, sizeof( response ) - 1 );
            }

        if ( inputDataPtr <= eolP1 )
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
        eolP = strstr( (const char*)inputData, "\xFF\xFB\x01\xFF\xFB\x03\xFF\xFD\x03" );
        if ( eolP && memcmp( inputData, ">login:", 7 ) == 0 )
        {
            inputDataPtr = 0;
            LOG( DBG_TRACE ) << "Got login / sending SSS;" << eline;
            static char response [] = "SSS;\r\n";
            port->PostWrite( response, sizeof( response ) - 1 );
            }
        }


    // Post overlapped read on socket...
    //
    bool rc = port->PostRead( inputData + inputDataPtr, sizeof( inputData ) - inputDataPtr );

    return rc;
    }

bool MD110_MML_Protocol::OnWriteCompleted( DWORD dwIoSize )
{
    return true;
    }

