
#include "CTsvcLIB.h"

using namespace std;
using namespace CTsvcLIB;

class Telnet_Protocol : public CTsvcLIB::ProtocolClass
{
    QCPortPool* portPool;
    char remote_ip_addr[ 256 ];
    unsigned short remote_tcp_port;

    static TCP_Listener_Parameters params;

    char inputData[ 10240 ]; // receive buffer
    size_t inputDataPtr;

    char outputData[ 1024 ]; // transmitt buffer
    size_t outputDataLen;

    Telnet_Protocol* passthru;

public:

    Telnet_Protocol( QCPortPool* pool, unsigned short local_tcp_port = 23 )
    {
        params.local_IP_address = INADDR_ANY;
        params.local_TCP_port = local_tcp_port;
        params.pool = pool;
        params.seed = this; // this is the master copy that will be cloned

        pool->Start_TCP_Listener( params );

        portPool = pool;

        strcpy( remote_ip_addr, "" );
        remote_tcp_port = 0;
        inputDataPtr = 0;
        outputDataLen = 0;

        passthru = NULL;
        }

    void SetPassthru( char* addr )
    {
        strcpy( remote_ip_addr, addr );
        }

    Telnet_Protocol( QCPortPool* pool, char* addr, unsigned short port = 23 )
    {
        strcpy( remote_ip_addr, addr );
        remote_tcp_port = port;
        portPool = pool;

        inputDataPtr = 0;
        outputDataLen = 0;

        passthru = NULL;
        }

    Telnet_Protocol( void ) // used by clone
    {
        strcpy( remote_ip_addr, "" );
        remote_tcp_port = 0;

        inputDataPtr = 0;
        outputDataLen = 0;

        passthru = NULL;
        }

    ~Telnet_Protocol( void )
    {
        if ( passthru )
        {
            passthru->passthru = NULL;
            delete passthru;
            passthru = NULL;
            }
        }

    void Initiate(  )
    {
        for ( ;; )
        {
            QCPort_TCP* p = new CTsvcLIB::QCPort_TCP( portPool, this );
            if ( p->OpenConnection( remote_ip_addr, remote_tcp_port ) )
                break;
            Sleep( 1000 );
            }
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


TCP_Listener_Parameters Telnet_Protocol::params;

ProtocolClass* Telnet_Protocol::Clone()
{
    Telnet_Protocol* srv = new Telnet_Protocol ();
    strcpy( srv->remote_ip_addr, remote_ip_addr );
    srv->remote_tcp_port = remote_tcp_port;
    srv->portPool = portPool;
    return srv;
    }

bool Telnet_Protocol::OnError( DWORD dwErrorCode )
{
    DebugRC( dwErrorCode );
    LOG( DBG_ERROR ) << "-> Error code " << dwErrorCode << eline;

    delete this;

    return true;
    }

bool Telnet_Protocol::OnConnect ()
{
    LOG( DBG_TRACE ) << "OnConnect" << eline;

    inputDataPtr = 0;

    if ( ! port->PostRead( inputData, sizeof( inputData ) ) )
    {
        delete this;
        return false;
        }

    if ( remote_tcp_port == 0 && remote_ip_addr[ 0 ] != '\0' )
    {
        // Passthru connections
        LOG( DBG_TRACE ) << "Connecting to remote server" << eline;
        passthru = new Telnet_Protocol( params.pool, remote_ip_addr, params.local_TCP_port );
        passthru->passthru = this;
        passthru->Initiate ();
        }

    return true;
    }

bool Telnet_Protocol::OnRemoteDisconnect ()
{
    LOG( DBG_TRACE ) << "OnRemoteDisconnect" << eline;

    if ( remote_tcp_port == 0 )
    {
        if ( port->IsConnected () )
            delete this;    
        }
    else
    {
        delete port;

        Sleep( 1000 );

        Initiate ();
        }

    return true;
    }

bool Telnet_Protocol::OnReadCompleted( DWORD dwIoSize )
{
    inputDataPtr += dwIoSize;
    inputData[ inputDataPtr ] = 0;

    for ( unsigned i = 0; i < inputDataPtr; i++ )
        printf( " %02X", inputData[ i ] & 0xFF );

    if ( passthru )
    {
        if ( remote_tcp_port == 0 ) // server
        {
            LOG( DBG_TRACE ) << ">>> [" << inputData << "]" << eline;
            }
        else
        {
            LOG( DBG_TRACE ) << "<<< [" << inputData << "]" << eline;
            }

        memcpy( passthru->outputData, inputData, inputDataPtr );
        passthru->outputDataLen = inputDataPtr;

        // syncrhonous send
        ::send( ((QCPort_TCP*)passthru->port)->hsock, passthru->outputData, passthru->outputDataLen, 0 );
        }
/*
    memcpy( outputData, inputData, inputDataPtr );
    outputDataLen = inputDataPtr;

    if ( ! port->PostWrite( outputData, outputDataLen ) )
    {
        LOG ( DBG_TRACE ) << "PostWrite failed" << eline;
        }
*/
    inputDataPtr = 0;

    // Post overlapped read on socket...
    //
    if ( ! port->PostRead( inputData + inputDataPtr, sizeof( inputData ) - inputDataPtr ) )
    {
        LOG ( DBG_TRACE ) << "Postread failed" << eline;
        delete port;
        return false;
        }

    return true;
    }

bool Telnet_Protocol::OnWriteCompleted( DWORD dwIoSize )
{
    return true;
    }

static QCPortPool pool;

void main
(
    int argc,
    char* argv []
    )
{
    unsigned short PORT = argc >= 2 ? (unsigned short)atol( argv[ 1 ] ) : 23;
    if ( PORT == 0 ) PORT = 23;

    LOG::UseHandle( GetStdHandle( STD_OUTPUT_HANDLE ) );

    LOG( DBG_TRACE ) << eline << eline << eline << "I live" << eline;

    pool.Initialize( 4 );

    if ( argc <= 2 )
    {
        Telnet_Protocol* seed = new Telnet_Protocol( &pool, PORT );
        // seed->SetPassthru( "213.131.141.131" );
        }
    else
    {
        Telnet_Protocol* client = new Telnet_Protocol( &pool, argv[2], PORT );
        client->Initiate ();
        }

    for ( ;; )
    {
        DWORD dwRead;
        INPUT_RECORD inp;
        ::ReadConsoleInput( ::GetStdHandle( STD_INPUT_HANDLE ), &inp, 1, &dwRead );

        if ( inp.EventType == KEY_EVENT && inp.Event.KeyEvent.bKeyDown )
        {
            if ( inp.Event.KeyEvent.uChar.AsciiChar == 27 )
            {
                pool.SignalTerminate ();
                break;
                }
            else if ( inp.Event.KeyEvent.uChar.AsciiChar == 13 )
            {
/*
                for ( List<QCPort>::Iterator i = pool.ports; i; i++ )
                {
                    ::send( ((QCPort_TCP*)i.GetElement())->hsock, "\r\n", 2, 0 );
                    }
*/
                }
            else if ( inp.Event.KeyEvent.uChar.AsciiChar != 0 )
            {
                static char x[10];
                x[0] = inp.Event.KeyEvent.uChar.AsciiChar;
/*
                for ( List<QCPort>::Iterator i = pool.ports; i; i++ )
                {
                    i->PostWrite( x, 1 );
                    }
*/
                }

            //LOG( DBG_TRACE ) << "Got " << inp.Event.KeyEvent.uChar.AsciiChar << eline;
            }
        }

    pool.WaitTerminate ();
    }

