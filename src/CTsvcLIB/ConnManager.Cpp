/*
    Project: CTsvcLIB

    Module: ConnManager.Cpp

    Description: Queued Completion Serial/Socket Port connection manager classes

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "CTsvcLIB.h"

using namespace std;

namespace CTsvcLIB
{

QCPortPool:: QCPortPool( void )
    : hCompletionPort( NULL )
    , isTerminating( false )
    , dispatcherCount( 0 )
{
    }

QCPortPool:: ~QCPortPool( void )
{
    }

void QCPortPool:: SignalTerminate( void )
{
    isTerminating = true;

    for ( List<QCPort>::Iterator i = ports; i; i++ )
    {
        TRACE( this << " QCPortPool::SignalTerminat; Killing Connection " << i.GetElement () );
        delete i;
        //::PostQueuedCompletionStatus( i->hCP, 0, DWORD( i.GetElement () ), NULL );
        }

    for ( int j = dispatcherCount; j > 0; j-- )
    {
        ::PostQueuedCompletionStatus( hCompletionPort, 0, 0, NULL );
        }
    }

void QCPortPool:: WaitTerminate( void )
{
    while ( dispatcherCount > 0 )
        Sleep( 100 );
    }

void QCPortPool:: Dump( void )
{
    TRACE( this << " QCPortPool:: Dump / Total " << dispatcherCount );

    for ( List<QCPort>::Iterator i = ports; i; i++ )
    {
        TRACE( "Connection " << i.GetElement () );
        }
    }

void QCPortPool:: Initialize( int cDispatchers )
{
    // Confirm that the WinSock DLL supports VER = wVersionRequested
    // Note that if the DLL supports versions greater
    // than VER in addition to VER, it will still return
    // VER in wVersion since that is the version we
    // requested.
    //
    WORD wVersionRequested = MAKEWORD( 1, 1 ); // version 1.1

    static WSADATA wsaData;
    if ( SOCKET_ERROR == ::WSAStartup( wVersionRequested, &wsaData ) )
    {
        TRACE( "WSAStartup failed" );
        return;
        }

    // Determine how many processors are on the system.
    //
    SYSTEM_INFO systemInfo;
    GetSystemInfo( &systemInfo );

    // Create the completion port that will be used by all the worker
    // threads.
    //
    hCompletionPort = ::CreateIoCompletionPort (
        INVALID_HANDLE_VALUE, // handle to a file; here, port without associated file
        NULL,     // handle to I/O completion port
        0,        // completion key
        systemInfo.dwNumberOfProcessors * 8  // number of threads to execute concurrently
        );

    if ( hCompletionPort == NULL )
    {
        DebugRC( ::GetLastError () );
        TRACE( "-> Create IO completition port failed." );
        return;
        }

    // Create worker threads that will service the actual overlapped
    // I/O requests.  Create a number of worker threads for each processor
    // on the system.
    //
    for ( unsigned int i = 0; i < systemInfo.dwNumberOfProcessors * cDispatchers; i++ )
    {
        HANDLE
        hThreadHandle = ::CreateThread
        (
            NULL,                          // pointer to thread security attributes  
            0,                             // initial thread stack size, in bytes 
            QCPortPool:: QIO_Dispatcher_Thread, // pointer to thread function 
            this,                          // argument for new thread 
            0,                             // creation flags 
            NULL                           // pointer to returned thread identifier 
            );

        if ( hThreadHandle == NULL || hThreadHandle == INVALID_HANDLE_VALUE )
        {
            DebugRC( ::GetLastError () );
            TRACE( "-> Create QIO worker thread failed." );

            ::CloseHandle( hCompletionPort );
            return;
            }

        // Close each thread handle as we open them.  We do not need
        // the thread handles.  Note that each thread will continue
        // executing.
        //
        ::CloseHandle( hThreadHandle );
        }
    }

//  Function:   System:: QIO_Dispatcher_Thread
//
//  Synopsis:   
//      This is the main worker routine for the QIO worker threads.
//      Worker threads wait on a completion port for I/O to complete. When 
//      it completes, the worker thread processes the I/O, then either pends 
//      new I/O or closes the peer's connection. When the service shuts 
//      down, other code closes the completion port which causes 
//      GetQueuedCompletionStatus() to wake up and the worker thread then 
//      exits.  
//
//  Arguments:  
//      workContext - the completion port handle that will get I/O completion
//      notifications.
//
//  Return value:
//      DWORD - status of the thread.
//
DWORD WINAPI
QCPortPool:: QIO_Dispatcher_Thread
(
    LPVOID thisPortPool
    )
{
    QCPortPool* pool = (QCPortPool*) thisPortPool;
    HANDLE hCompletionPort = pool->hCompletionPort;

    // TRACE( "QIO dispatcher thread started" );

    pool->dispatcherCount++;

    // Loop servicing I/O completions.
    //
    for( ;; )
    {
        // Get a completed IO request.
        //
        DWORD dwIoSize;
        QCPort* port;
        OVERLAPPED* lpOverlapped;
        BOOL bSuccess = ::GetQueuedCompletionStatus(
                       hCompletionPort,  // handle to completion port
                       &dwIoSize,        // bytes transferred
                       LPDWORD( &port ), // file completion key
                       &lpOverlapped,    // buffer
                       INFINITE          // optional timeout value
                       );

        DWORD rc = ::GetLastError ();

        // If the service is terminating, exit this thread.
        if ( pool->isTerminating )
        {
            break;
            }

        // If the IO failed, close the socket and free CSTAClient.
        if ( ! bSuccess )
        {
            if ( port && port->HasMagic () )
                port->DispatchError( rc );
            else
            {
                DebugRC( rc );
                TRACE( "::GetQueuedCompletionStatus failed, and port == NULL" );
                }
            }
        // Process last IO command depending on connection state
        else if ( port && port->HasMagic () )
        {
            // lpOverlapped == NULL; if close request is dispatched
            port->DispatchIO( dwIoSize, lpOverlapped );
            }

        // Loop around to get another completed IO request.
        }

    pool->dispatcherCount--;

    TRACE( "QIO dispatcher thread done." );

    return 0;
    }

//////////////////////////////////////////////////////////////////////////////
// TCP Port Listener

DWORD WINAPI QCPortPool:: TCP_Listener_Thread( LPVOID context )
{
    if ( ! context )
        return 0;

    TCP_Listener_Parameters params = *(TCP_Listener_Parameters*)context;

    if ( ! params.pool )
        return 0;
    if ( ! params.seed )
        return 0;

    unsigned long local_address = params.local_IP_address;
    unsigned short local_port = params.local_TCP_port;

    // Start accepting and processing clients.
    //
    // Create a listening socket that we'll use to accept incoming
    // conections.
    //
    SOCKET
    sListener = ::socket( AF_INET, SOCK_STREAM, 0 );
    if ( sListener == INVALID_SOCKET )
    {
        DebugRC( ::WSAGetLastError () );
        TRACE( "Error openning socket" );

        return FALSE;
        }

    // Bind the socket to the service well-known port.
    //
    SOCKADDR_IN sin;
    sin.sin_family = AF_INET;
    sin.sin_port = ::htons( local_port );
    sin.sin_addr.s_addr = local_address;

    int err = ::bind( sListener, (LPSOCKADDR)&sin, sizeof( sin ) );
    if ( err == SOCKET_ERROR )
    {
        ::closesocket( sListener );
        return FALSE;
        }

    // Listen for incoming connections on the socket.
    //
    err = ::listen( sListener, 5 );

    if ( err == SOCKET_ERROR )
    {
        ::closesocket( sListener );
        return FALSE;
        }

    TRACE( "TCP Listener started, Port=" << local_port );

    // Loop forever accepting connections from clients.
    //
    for( ;; )
    {
        SOCKET s = ::accept( sListener, NULL, NULL );

        if ( s == INVALID_SOCKET )
        {
            ::closesocket( sListener );
            break;
            }

        // If the service if terminating, exit this thread.
        //
        if ( params.pool->isTerminating )
        {
            break;
            }

        // Create ProtocolClass Instance
        ProtocolClass* protocol = params.seed->Clone ();

        // Create QCPort_TCP and bind ProtocolInstance to Port
        QCPort_TCP* port = new QCPort_TCP( params.pool, protocol );

        // OpenConnection on the Port
        port->OpenConnection( s );
        }

    return 0;
    }

//////////////////////////////////////////////////////////////////////////////
//
//  QCPort_TCP Implementation
//

bool QCPort_TCP:: OpenConnection( SOCKET hSocket )
{
    hsock = hSocket;

    // Associate the new socket with a completion port.
    //
    hCP = ::CreateIoCompletionPort (
        HANDLE( hsock ),                // handle to file
        pool->hCompletionPort,          // handle to I/O completion port
        DWORD( this ),                  // completion key
        0                               // number of threads to execute concurrently; 0 -- unlimited
        );
    if ( hCP == NULL || hCP == INVALID_HANDLE_VALUE )
    {
        DebugRC( ::GetLastError () );
        TRACE( "CreateIoCompletionPort failed" );
        ::closesocket( hsock );
        return false;
        }

    // Disable send bufferring on the socket. Setting SO_SNDBUF
    // to 0 causes winsock to stop bufferring sends and perform
    // sends directly from our buffers, thereby reducing CPU
    // usage.
    //
    int zero = 0;
    int err = ::setsockopt( hsock, SOL_SOCKET, SO_SNDBUF, (char*)&zero, sizeof( zero ) );

    if ( err == SOCKET_ERROR )
    {
        TRACE( "::setsockopt failed SO_SNDBUF" );
        ::closesocket( hsock );
        return false;
        }
/*
    int timeout = 10;
    err = setsockopt( hsock, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout) );
    if (err != NO_ERROR)
    {
        TRACE( "::setsockopt failed SO_SNDTIMEO" );
        ::closesocket( hsock );
        return false;
        }

    err = setsockopt( hsock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout) );
    if (err != NO_ERROR)
    {
        TRACE( "::setsockopt failed SO_RCVTIMEO" );
        ::closesocket( hsock );
        return false;
        }
*/
    TRACE( this << " QCPort_TCP::OpenConnection; ... connected." );

    fConnected = true;

    if ( protocol )
        return protocol->OnConnect ();

    return true;
    }

bool QCPort_TCP:: OpenConnection( const char* remote_addr, unsigned short remote_port )
{
    CloseConnection();

    memset( &Overlapped_Read, 0, sizeof( Overlapped_Read ) );
    memset( &Overlapped_Write, 0, sizeof( Overlapped_Write ) );

    IP_address = remote_addr;
    TCP_port = remote_port;

	sockaddr_in server;
	memset( &server, 0, sizeof(server) );

	// Initialize socket address by name or by nnn.nnn format.
    //
    if ( ::isalpha( IP_address[0] ) )
    {
        // server address is a name 
        hostent* hp = ::gethostbyname( IP_address );

	    if ( hp == NULL )
        {
            DebugRC( ::WSAGetLastError () );
            TRACE( "--> Cannot resolve address " << IP_address );
            return false;
	        }

	    // Copy the resolved information into the sockaddr_in structure
        //
	    memcpy( &server.sin_addr, hp->h_addr, hp->h_length );
	    server.sin_family = hp->h_addrtype;
	    server.sin_port = htons(TCP_port);
	    }
	else 
    {
        // Convert nnn.nnn.nnn.nnn address to a usable one 
        unsigned long addr = ::inet_addr( IP_address );
        //
	    // Copy the resolved information into the sockaddr_in structure
	    memcpy( &server.sin_addr, &addr, 4 );
	    server.sin_family = AF_INET;
	    server.sin_port = htons(TCP_port);
	    }

    SOCKET s = ::socket( AF_INET, SOCK_STREAM, 0 ); // Open a socket
	if ( s < 0 )
    {
        DebugRC( ::WSAGetLastError () );
        TRACE( "--> Open socket failed" );
		return false;
	    }

    hostent* hp = NULL; //::gethostbyaddr( (const char*)&server.sin_addr, 4, AF_INET );
    if ( hp )
    {
	    TRACE( this << " QCPort_TCP::OpenConnection; Connecting to " 
            << hp->h_name << "(" << IP_address << "):" << TCP_port );
        }
    else
    {
	    TRACE( this << " QCPort_TCP::OpenConnection; Connecting to " 
	        << IP_address << ":" << TCP_port );
        }

    if ( ::connect( s, (struct sockaddr*)&server,sizeof(server) )
		== SOCKET_ERROR)
    {
        DebugRC( ::WSAGetLastError () );
        TRACE( "--> Connect failed" );
		return false;
	    }

    return OpenConnection( s );
    }

void QCPort_TCP:: CloseConnection( bool graceful )
{
    if ( ! fConnected || hsock == NULL )
        return;

    protocol->mutex.Lock ();

    TRACE( this << " QCPort_TCP::CloseConnection; graceful " << graceful );

    // If we're supposed to abort the connection, set the linger value
    // on the socket to 0.
    //
    if ( ! graceful )
    {
        LINGER lingerStruct;
        lingerStruct.l_onoff = 1;
        lingerStruct.l_linger = 0;
        ::setsockopt( hsock, SOL_SOCKET, SO_LINGER,
                    (char*)&lingerStruct, sizeof( lingerStruct ) );
        }

    // Now close the socket handle.  This will do an abortive or 
    // graceful close, as requested.  
    //
    ::closesocket( hsock );
    hsock = NULL;

    protocol->mutex.Unlock ();

    // Wait "net name deleted" on DispatchIO to happen
    //
    for ( int i = 0; fConnected && i < 40; i++ ) // up to 40*50 ms
        Sleep( 50 );

    fConnected = false;
    }

///////////////////////////////////////////////////////////////////////////////
//  Function:   QCPort_TCP:: DispatchIO
//
//  Synopsis:   
//      Dispatches last asynchronus IO request to connection
//      depending on connection previous context.
//
//  Arguments:  
//      LastIoSize contains number of bytes in last I/O
//
//  Return value:
//      TRUE if Dispatch IO was successfull, FALSE otherwise
//      (Note that caller should do CloseClient or delete it
//      if DispatchIO was unsuccessfull)
//
bool
QCPort_TCP:: DispatchIO
(
    DWORD dwLastIoSize,
    OVERLAPPED* lpOverlapped
    )
{
    if ( lpOverlapped == &Overlapped_Read )
    {
        if ( protocol )
            if ( dwLastIoSize == 0 )
                protocol->OnRemoteDisconnect ();
            else
                protocol->OnReadCompleted( dwLastIoSize );
        }
    else if ( lpOverlapped == &Overlapped_Write )
    {
        if ( protocol )
            if ( dwLastIoSize == 0 )
                protocol->OnRemoteDisconnect ();
            else
                protocol->OnWriteCompleted( dwLastIoSize );
        }
    else if ( lpOverlapped == NULL )
    {
        delete this;
        }

    return false;
    }

void QCPort_TCP:: DispatchError( DWORD rc )
{
    if ( ! protocol )
        return;

    if ( rc == ERROR_NETNAME_DELETED )
    {
        protocol->OnRemoteDisconnect ();
        fConnected = false;
        }
    else
    {
        protocol->OnError( rc );
        }
    }

bool QCPort_TCP:: PostRead( void* inputDataBuf, DWORD maxInputDataLen )
{
    if ( ! fConnected )
    {
        TRACE( "PostRead::ReadFile failed; Not connected" );
        return false;
        }

    DWORD dwBytesRead;
    BOOL bSuccess = ::ReadFile (
        HANDLE( hsock ),            // handle to file
        inputDataBuf,               // data buffer
        maxInputDataLen,            // number of bytes to read
        &dwBytesRead,               // number of bytes read
        &Overlapped_Read            // overlapped buffer
        );

    if ( ! bSuccess &&::GetLastError( ) != ERROR_IO_PENDING )
    {
        DebugRC( ::GetLastError () );
        TRACE( "ReadFile failed" );
        return false;
        }

    return true;
    }

bool QCPort_TCP:: PostWrite( void* outputDataBuf, DWORD outputDataLen )
{
    if ( ! fConnected )
        return false;

    DWORD dwWritten;
    BOOL bSuccess = ::WriteFile(
        HANDLE( hsock ),            // handle to file
        outputDataBuf,              // data buffer
        outputDataLen,              // number of bytes to write
        &dwWritten,                 // number of bytes written
        &Overlapped_Write           // overlapped buffer
        );

    if ( ! bSuccess &&::GetLastError( ) != ERROR_IO_PENDING )
    {
        DebugRC( ::GetLastError () );
        TRACE( "Write failed" );
        return false;
        }

    return true;
    }

//////////////////////////////////////////////////////////////////////////////
//
//  QCPort_Serial Implementation
//

bool QCPort_Serial:: OpenConnection
(
    const char* port_name,
    DWORD p_baud_rate, // 9600
    BYTE p_byte_size,  // 8
    BYTE p_parity,     // NOPARITY
    BYTE p_stop_bits   // ONESTOPBIT
    )
{
    CloseConnection();

    hComPort = :: CreateFile(
        port_name,          // filename
        GENERIC_READ | GENERIC_WRITE, // desired access - R/W
        0,                  // comm devices must be opened with exclusive-access
        NULL,               // no security attrs
        OPEN_EXISTING,      // comm devices must use OPEN_EXISTING
        FILE_FLAG_OVERLAPPED, // file attributes
        NULL                // hTemplate must be NULL for comm devices
        );

    if ( hComPort == INVALID_HANDLE_VALUE ) 
    {
        DebugRC( ::GetLastError () );
        TRACE( "-> CreateFile " << port_name << " failed." );

        return 0L;
        }

    // Omit the call to SetupComm to use the default queue sizes.
    //
    BOOL fSuccess = ::SetupComm( hComPort, 1024, 1024 );
    if ( ! fSuccess )
    {
        DebugRC( ::GetLastError () );
        TRACE( "-> SetupComm " << port_name << " failed." );
        }
  
    // Get the current configuration.
    //
    DCB dcb;
    fSuccess = ::GetCommState( hComPort, &dcb);

    if ( ! fSuccess ) 
    {
        DebugRC( ::GetLastError () );
        TRACE( "-> GetCommState " << port_name << " failed." );

        return 0L;
        }

    // DWORD BaudRate;            // current baud rate 
    // DWORD fBinary: 1;          // binary mode, no EOF check 
    // DWORD fParity: 1;          // enable parity checking 
    // DWORD fOutxCtsFlow:1;      // CTS output flow control 
    // DWORD fOutxDsrFlow:1;      // DSR output flow control 
    // DWORD fDtrControl:2;       // DTR flow control type 
    // DWORD fDsrSensitivity:1;   // DSR sensitivity 
    // DWORD fTXContinueOnXoff:1; // XOFF continues Tx 
    // DWORD fOutX: 1;          // XON/XOFF out flow control 
    // DWORD fInX: 1;           // XON/XOFF in flow control 
    // DWORD fErrorChar: 1;     // enable error replacement 
    // DWORD fNull: 1;          // enable null stripping 
    // DWORD fRtsControl:2;     // RTS flow control 
    // DWORD fAbortOnError:1;   // abort on error 
    // WORD XonLim;             // transmit XON threshold 
    // WORD XoffLim;            // transmit XOFF threshold 
    // BYTE ByteSize;           // number of bits/byte, 4-8 
    // BYTE Parity;             // 0-4=no,odd,even,mark,space 
    // BYTE StopBits;           // 0,1,2 = 1, 1.5, 2 
    // char XonChar;            // Tx and Rx XON character 
    // char XoffChar;           // Tx and Rx XOFF character 
    // char ErrorChar;          // error replacement character 
    // char EofChar;            // end of input character 
    // char EvtChar;            // received event character 

    // Serial Port parameters:
    //
    dcb.fBinary = TRUE; // binary mode
    dcb.fParity = FALSE; // check parity
    //
    // - baud rate, data bits, parity, stop bits
    //
    dcb.BaudRate = p_baud_rate;
    dcb.ByteSize = p_byte_size;
    dcb.Parity   = p_parity; // NOPARITY;
    dcb.StopBits = p_stop_bits; // ONESTOPBIT;
    //
    // - Input flow control.
    //
    dcb.fInX = FALSE;
    dcb.fRtsControl = RTS_CONTROL_ENABLE;
    dcb.fDtrControl = DTR_CONTROL_ENABLE;
    //
    // - Output flow control.
    //
    dcb.fOutX = FALSE;
    dcb.fOutxCtsFlow = FALSE;
    dcb.fOutxDsrFlow = FALSE;

    fSuccess = ::SetCommState( hComPort, &dcb );

    if ( ! fSuccess ) 
    {
        DebugRC( ::GetLastError () );
        TRACE( "-> SetCommState " << port_name << " failed." );

        return 0L;
        }

    COMMTIMEOUTS ctout = { 0 };
    ctout.ReadIntervalTimeout = 0;
    ctout.ReadTotalTimeoutMultiplier = 0;
    ctout.ReadTotalTimeoutConstant = 0; // 2000; // 2 seconds
    ctout.WriteTotalTimeoutMultiplier = 0;
    ctout.WriteTotalTimeoutConstant = 0;
 
    // Setup comport timeouts.
    //
    fSuccess = ::SetCommTimeouts( hComPort, &ctout );

    if ( ! fSuccess ) 
    {
        DebugRC( ::GetLastError () );
        TRACE( "-> SetCommTimeouts " << port_name << " failed." );

        return 0L;
        }

    // Associate the new socket with a completion port.
    //
    hCP = ::CreateIoCompletionPort (
        hComPort,                // handle to file
        pool->hCompletionPort,          // handle to I/O completion port
        DWORD( this ),                  // completion key
        0                               // number of threads to execute concurrently; 0 -- unlimitted
        );
    if ( hCP == NULL || hCP == INVALID_HANDLE_VALUE )
    {
        DebugRC( GetLastError () );
        TRACE( "CreateIoCompletionPort failed" );
        ::CloseHandle( hComPort );
        return false;
        }

    TRACE( "Com port " << port_name << " connected." );

    fConnected = true;

    if ( protocol )
        return protocol->OnConnect ();

    return true;
    }

void QCPort_Serial:: CloseConnection( void )
{
    if ( ! fConnected || hComPort == NULL )
        return;

    TRACE( "Com port closing connection" );

    // Now close the socket handle.  This will do an abortive or 
    // graceful close, as requested.  
    //
    ::CloseHandle( hComPort );
    hComPort = NULL;

    // Wait all pending QIO to complete
    Sleep( 100 );

    fConnected = false;
    }

bool
QCPort_Serial:: DispatchIO
(
    DWORD dwLastIoSize,
    OVERLAPPED* lpOverlapped
    )
{
    if ( lpOverlapped == &Overlapped_Read )
    {
        if ( protocol )
            protocol->OnReadCompleted( dwLastIoSize );
        }
    else if ( lpOverlapped == &Overlapped_Write )
    {
        if ( protocol )
            protocol->OnWriteCompleted( dwLastIoSize );
        }
    else if ( lpOverlapped == NULL )
    {
        delete this;
        }

    return false;
    }

void QCPort_Serial:: DispatchError( DWORD rc )
{
    if ( ! protocol )
        return;

    if ( rc == ERROR_NETNAME_DELETED )
        protocol->OnRemoteDisconnect ();
    else
        protocol->OnError( rc );
    }

bool QCPort_Serial:: PostRead( void* inputDataBuf, DWORD maxInputDataLen )
{
    if ( ! fConnected )
    {
        TRACE( "PostRead::ReadFile failed; Not connected" );
        return false;
        }

    DWORD dwBytesRead;
    BOOL bSuccess = ::ReadFile (
        hComPort,                   // handle to file
        inputDataBuf,               // data buffer
        1,                          // number of bytes to read; should be allways 1
        &dwBytesRead,               // number of bytes read
        &Overlapped_Read            // overlapped buffer
        );

    DWORD rc = ::GetLastError ();
    if ( ! bSuccess && rc != ERROR_IO_PENDING )
    {
        DebugRC( rc );
        TRACE( "QCPort_Serial::ReadFile failed" );
        return false;
        }

    return true;
    }

bool QCPort_Serial:: PostWrite( void* outputDataBuf, DWORD outputDataLen )
{
    if ( ! fConnected )
        return false;

    DWORD dwWritten;
    BOOL bSuccess = ::WriteFile(
        hComPort,                   // handle to file
        outputDataBuf,              // data buffer
        outputDataLen,              // number of bytes to write
        &dwWritten,                 // number of bytes written
        &Overlapped_Write           // overlapped buffer
        );

    if ( ! bSuccess &&::GetLastError( ) != ERROR_IO_PENDING )
    {
        DebugRC( ::GetLastError () );
        TRACE( "QCPort_Serial::Write failed" );
        return false;
        }

    return true;
    }

} // namespace CTsvcLIB