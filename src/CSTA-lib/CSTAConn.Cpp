/*
    Project: CSTALib

    Module: Device.Cpp

    Description: Device class implementation

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "CSTA-Lib.h"

using namespace ASN;
using namespace CTsvcLIB;

/////////////////////////////////////////////////////////////////////////////
namespace MidCSTA
{

///////////////////////////////////////////////////////////////////////////////
// Device implementation

ErrorCode Device:: Initialize( const char* newDevId )
{
    // Try to purge previous connection
    MonitorStop ();
    CloseConnection();

    // Set up new device identifier
    connMutex.Lock ();

        if ( newDevId )
            devID = deviceIdType( newDevId );

    connMutex.Unlock ();

    // Open CSTA connection
    ErrorCode errorCode = OpenConnection ();
    if ( errorCode != CTNG_NO_ERROR )
        return errorCode;

    // Start monitoring device
    return MonitorStart ();
    }

ErrorCode Device:: OpenConnection( void )
{
    TRASSERT( ! isConnected );
    TRASSERT( pbx != NULL );
    const char* IP_address = pbx->ip_address;
    unsigned short TCP_port = pbx->tcp_port;

	TRACE( this << " Device::OpenConnection; Connecting to " 
	    << IP_address << ":" << TCP_port );

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
            LOG( DBG_ERROR ) << " Device::OpenConnection: -> Cannot resolve address " << IP_address << eline;
            return CTNG_OPEN_CONNECTION_FAILED;
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
	    memcpy( &server.sin_addr, &addr, sizeof( addr ) );
	    server.sin_family = AF_INET;
	    server.sin_port = htons(TCP_port);
	    }

    SOCKET s = ::socket( AF_INET, SOCK_STREAM, 0 ); // Create socket
	if ( s == INVALID_SOCKET )
    {
        DebugRC( ::WSAGetLastError () );
        LOG( DBG_ERROR ) << this << " Device::OpenConnection: -> Open socket failed" << eline;
		return CTNG_OPEN_CONNECTION_FAILED;
	    }

    if ( ::connect( s, (struct sockaddr*)&server,sizeof(server) )
		== SOCKET_ERROR )
    {
        DebugRC( ::WSAGetLastError () );
        LOG( DBG_ERROR ) << this << " Device::OpenConnection -> Connect failed; socket = " << s << eline;
        ::closesocket( s );
		return CTNG_OPEN_CONNECTION_FAILED;
	    }

    // Associate the new socket with a completion port.
    //
    hCP = ::CreateIoCompletionPort (
        HANDLE( s ),                  // handle to file
        system->GetCompletionPort(),  // handle to I/O completion port
        DWORD( this ),                // completion key
        0                             // number of threads to execute concurrently; 0 -- unlimited
        );
    if ( hCP == NULL )
    {
        DebugRC( ::GetLastError () );
        LOG( DBG_ERROR ) << this << " Device::OpenConnection: CreateIoCompletionPort failed" << eline;
        ::closesocket( s );
        return CTNG_OPEN_CONNECTION_FAILED;
        }

    // Reset QIO context variables

    recvState = RECEIVING_CSTA_HEADER;
    memset( &Overlapped_Read, 0, sizeof( Overlapped_Read ) );
    inputDataPtr = 0;
    inputDataLen = 0;

    // Reset response context variables

    responseMutex.Lock ();

        currentResponse = NULL;
        currentInvokeID = 0;

    responseMutex.Unlock ();

    // Set connection variables

    connMutex.Lock ();

        hSocket = s;
        isConnected = true;
        monitorID.SetNULL ();

    connMutex.Unlock ();

    TRACE( this << " Device::OpenConnection: Connected." );

    // Post Initial Read
    //
    if ( ! PostRead( inputData, sizeof( inputData ) ) )
    {
        connMutex.Lock ();

            hSocket = NULL;
            isConnected = false;

        connMutex.Unlock ();

        ::closesocket( s );
        return CTNG_OPEN_CONNECTION_FAILED;
        }

    return CTNG_NO_ERROR;
    }

ErrorCode Device:: CloseConnection( bool graceful )
{
    if ( ! isConnected )
        return CSTA_NOT_CONNECTED;

    // Wait PostRead to be issued
    ::Sleep( 200 );

    MutexBlock _MB( serviceMutex ); // mutex until function returns

    TRACE( this << " Device::CloseConnection; graceful " << graceful );

    // If we're supposed to abort the connection, set the linger value
    // on the socket to 0.
    //
    if ( ! graceful )
    {
        LINGER lingerStruct;
        lingerStruct.l_onoff = 1;
        lingerStruct.l_linger = 0;
        ::setsockopt( hSocket, SOL_SOCKET, SO_LINGER,
            (char*)&lingerStruct, sizeof( lingerStruct ) );
        }

    // Now close the socket handle. This will do an abortive or 
    // graceful close, as requested.  
    //
    ::closesocket( hSocket );

    // Wait on disconnected event
    ::WaitForSingleObject( responseEvent, invokeTimeout );

    connMutex.Lock ();

        isConnected = false;
        monitorID.SetNULL ();
        hSocket = NULL;

    connMutex.Unlock ();

    return CTNG_NO_ERROR;
    }

///////////////////////////////////////////////////////////////////////////////

bool Device:: PostRead( void* inputDataBuf, DWORD maxInputDataLen )
{
    if ( ! isConnected )
        return false;

    DWORD dwBytesRead;
    BOOL bSuccess = ::ReadFile (
        HANDLE( hSocket ),          // handle to file
        inputDataBuf,               // data buffer
        maxInputDataLen,            // number of bytes to read
        &dwBytesRead,               // number of bytes read
        &Overlapped_Read            // overlapped buffer
        );

    if ( ! bSuccess &&::GetLastError( ) != ERROR_IO_PENDING )
    {
        DebugRC( ::GetLastError () );
        LOG( DBG_ERROR ) << this << " Device::PostRead: ReadFile failed" << eline;
        return false;
        }

    return true;
    }

void Device:: PostNullQIO( void )
{
    ::PostQueuedCompletionStatus( hCP, 0, DWORD( this ), NULL );
    }

bool
Device:: DispatchIO
(
    BOOL bSuccess,
    DWORD error,
    DWORD ioSize,
    OVERLAPPED* overlapped
    )
{
    ioMutex.Lock ();

    if ( ! bSuccess )
    {
        OnErrorQIO( error );
        }
    else // Successfull IO
    {
        if ( overlapped == &Overlapped_Read ) // Posted Read completed
        {
            OnReadCompleted( ioSize );
            }
        else if ( overlapped == NULL ) // Posted QIO message
        {
            OnNullQIO ();
            }
        }

    ioMutex.Unlock ();

    return true;
    }

///////////////////////////////////////////////////////////////////////////////

bool Device:: OnErrorQIO( DWORD errorCode )
{
    DebugRC( errorCode );
    LOG( DBG_ERROR ) << this << " Device::OnErrorQIO: Device " << devID << ", GetQueuedCompletionStatus failed; RC = " 
        << errorCode << eline;

    // ERROR_NETNAME_DELETED
    // ERROR_OPERATION_ABORTED

    // Generate callback event. Note that it will not be dispatched
    // if device is dereferenced and under destruction.
    //
    Ptr<CBI_RemoteDisconnected> cbi = new CBI_RemoteDisconnected;
    cbQueue.Put( cbi );

    connMutex.Lock ();

        if ( hSocket )
        {
            ::closesocket( hSocket );
            hSocket = NULL;
            }

        isConnected = false;
        monitorID.SetNULL ();

    connMutex.Unlock ();

    // Cancel any service invoke or Signal CloseConnection() to continue
    //
    ROSE_CancelInvoke (); 

    return true;
    }

bool Device:: OnNullQIO( void )
{
    TRACE( this << " Device::OnNullQIO" );
    return true;
    }

bool
Device:: OnReadCompleted( DWORD ioSize )
{
    TRACE( this << " Device::OnReadCompleted; Received " << ioSize << " bytes" );

    inputDataPtr += ioSize;

    for ( ;; )
    {
        if ( recvState == RECEIVING_CSTA_HEADER )
        {
            if ( inputDataPtr >= 2 )
            {
                // Get APDU size from header.
                inputDataLen = ( inputData[ 0 ] << 8 ) + inputData[ 1 ];
                recvState = RECEIVING_CSTA_APDU_BODY;

                if ( inputDataPtr >= 2 + inputDataLen )
                {
                    // We have received complete APDU!
                    DecodeReceivedAPDU( inputData + 2, inputDataLen );

                    // Move remaining bytes that follows after APDU,
                    // to the front position in buffer.
                    inputDataPtr -= inputDataLen + 2;
                    recvState = RECEIVING_CSTA_HEADER;

                    if ( inputDataPtr > 0 )
                    {
                        memmove( inputData, inputData + 2 + inputDataLen, inputDataPtr );
                        continue; // There are still inputData to process
                        }
                    }
                }
            }
        else if ( recvState == RECEIVING_CSTA_APDU_BODY )
        {
            if ( inputDataPtr >= 2 + inputDataLen )
            {
                // We have received complete APDU!
                DecodeReceivedAPDU( inputData + 2, inputDataLen );

                // Move remaining bytes that follows after APDU,
                // to the front position in buffer.
                inputDataPtr -= inputDataLen + 2;
                recvState = RECEIVING_CSTA_HEADER;

                if ( inputDataPtr > 0 )
                {
                    memmove( inputData, inputData + 2 + inputDataLen, inputDataPtr );
                    continue; // There are still inputData to process
                    }
                }
            }

        break; // We need more data in input buffer
        }

    // Post overlapped read on socket...
    //
    bool rc = PostRead( inputData + inputDataPtr, sizeof( inputData ) - inputDataPtr );
            
    if ( ! rc )
        ROSE_CancelInvoke (); // Signal Disconnect

    return rc;
    }

///////////////////////////////////////////////////////////////////////////////

ErrorCode Device:: EncodeAndSendAPDU( CSTAapdu* apdu )
{
    TRACE( this << " Device::EncodeAndSendAPDU; Device " << devID << ", apdu " << apdu );

    if ( ! isConnected )
        return CSTA_NOT_CONNECTED;

    uint8 outputData[ 2048 ]; // transmit buffer
    size_t outputDataLen = 0;

    AsnBuf outputBuf;
    outputBuf.Init( outputData + 2, sizeof( outputData ) - 2 );
    outputBuf.ResetInWriteRvsMode();

    if ( ! apdu->BEncPdu( outputBuf, outputDataLen ) )
    {
        LOG( DBG_ERROR ) << this << " Device::EncodeAndSendAPDU: Encode routines failed" << eline;
        return CTNG_SEND_APDU_FAILED;
        }

    outputBuf.ResetInReadMode();
    outputBuf.CopyOut( outputData + 2, outputDataLen );

    // Format CSTA packet header
    outputData[ 0 ] = ( outputDataLen >> 8 ) & 0xFF;
    outputData[ 1 ] = ( outputDataLen ) & 0xFF;

#if 1
    //AsnBuf dumpBuf;
    //dumpBuf.InstallData( outputData + 2, outputDataLen );
    TRACE( this << " Device::EncodeAndSendAPDU:" << eline
        //<< "========================================================" << eline
        //<< "Sent APDU: " << dumpBuf
        //<< "--------------------------------------------------------" << eline
        << "encodedValue : " << *apdu
        );
#endif

    if ( ! isConnected )
        return CSTA_NOT_CONNECTED;

    // Synchronous send of the CSTA APDU
    int sentLen = ::send( hSocket, (char*)outputData, outputDataLen + 2, 0 );
    DWORD rc = ::WSAGetLastError ();
    if ( sentLen == SOCKET_ERROR )
    {
        DebugRC( rc );
        LOG( DBG_ERROR ) << this << " Device::EncodeAndSendAPDU; ::send on socket failed; rc = " << rc << eline;
        }

    if ( sentLen != outputDataLen + 2 )
        return CTNG_SEND_APDU_FAILED;

    return CTNG_NO_ERROR;
    }

ErrorCode Device:: ROSE_Invoke( InvokeResponse& response, AsnIntType op_id, AsnType* arg )
{
    TRACE( this << " Device::ROSE_Invoke; Device " << devID << ", op " << op_id << ", arg " << arg );

    MemBlock* mem = arg->GetMemBlock ();

    OperationArgument* oparg = new(mem) OperationArgument(mem);
        oparg->intId = op_id;
        oparg->value = arg;

    ROIVapdu* invokeApdu = new(mem) ROIVapdu( mem );
        invokeApdu->invokeID = 0;
        invokeApdu->linkedID = NULL;
        invokeApdu->operationValue.Set( oparg->intId );
        invokeApdu->argument = oparg;

    CSTAapdu* request = new(mem) CSTAapdu( mem );
        request->choiceId = CSTAapdu::invokeApduCid;
        request->invokeApdu = invokeApdu;
        // request->invokeApdu->invokeID = ... later defined

    serviceMutex.Lock ();

        responseMutex.Lock ();

            // Acquire next invoke ID

            if ( ++currentInvokeID == 0 )
                currentInvokeID = 1; // loop arround

            request->invokeApdu->invokeID = currentInvokeID;

            // Set current response
            currentResponse = &response;

            // Make sure that event is not signaled!
            ::ResetEvent( responseEvent );

        responseMutex.Unlock ();

        // Send APDU with invoke
        ErrorCode errorCode = EncodeAndSendAPDU( request );
        if ( errorCode != CTNG_NO_ERROR )
        {
            serviceMutex.Unlock ();
            return errorCode;
            }

        // Wait ROSE response (i.e. APDU with Result/Error/Reject).
        // This will block until timeout or ROSE response arrived.
        DWORD rc = ::WaitForSingleObject( responseEvent, invokeTimeout );

        responseMutex.Lock ();
            currentResponse = NULL;
        responseMutex.Unlock ();

    serviceMutex.Unlock ();

    if ( rc != WAIT_OBJECT_0 )
    {
        LOG( DBG_WARN ) << this << " Device::ROSE_Invoke: Got TIMEOUT" << eline;

        if ( rc == WAIT_FAILED )
        {
            DebugRC( GetLastError () );
            LOG( DBG_ERROR ) << this << " -> Device::ROSE_Invoke: WaitForSingleObject failed" << eline;
            }

        return CSTA_ERROR_TIMEOUT;
        }

    CSTAapdu* resp = response.GetAPDU ();
    if ( ! resp ) // this will happen if the connection is disconnected
    {
        TRACE( this << " Device::ROSE_Invoke: Got NULL response; Socket disconnected." );

        connMutex.Lock ();

            if ( hSocket )
                ::closesocket( hSocket );

            hSocket = NULL;
            isConnected = false;
            monitorID.SetNULL ();

        connMutex.Unlock ();

        return CSTA_NOT_CONNECTED;
        }

    errorCode = CSTA_ERROR_CODE_NOT_SET;

    // hEvent is properly signaled, so ROSE is completed on time.
    // We should check received response ROSE APDU on our invoke.
    //
    switch( resp->choiceId )
    {
        case ROSEapdu::resultApduCid:
        {
            TRASSERT( resp->resultApdu->rORSapduSeq->operationValue == request->invokeApdu->argument->intId );
            TRASSERT( resp->resultApdu->invokeID == request->invokeApdu->invokeID );
            errorCode = CTNG_NO_ERROR;
            break;
            }

        case ROSEapdu::errorApduCid:
        {
            TRASSERT( resp->errorApdu->invokedID == request->invokeApdu->invokeID );
            TRASSERT( resp->errorApdu->errorValue == ErrorIDType::universalFailure );
            UniversalFailure* ufail = (UniversalFailure*) resp->errorApdu->parameter->value;
            switch( ufail->choiceId )
            {
                case UniversalFailure::operationalErrorsCid:
                    errorCode = ErrorCode( CSER_OPERATIONAL_ERROR 
                        + (int)*ufail->operationalErrors );
                    break;
                case UniversalFailure::stateErrorsCid:
                    errorCode = ErrorCode( CSER_STATE_ERROR
                        + (int)*ufail->stateErrors );
                    break;
                case UniversalFailure::systemResourceErrorsCid:
                    errorCode = ErrorCode( CSER_SYSTEM_RESOURCE_ERROR
                        + (int)*ufail->systemResourceErrors );
                    break;
                case UniversalFailure::subscribedResourceAvailabilityErrorsCid:
                    errorCode = ErrorCode( CSER_SUBSCRIBED_RESOURCE_AVAILABILITY_ERROR
                        + (int)*ufail->subscribedResourceAvailabilityErrors );
                    break;
                case UniversalFailure::performanceErrorsCid:
                    errorCode = ErrorCode( CSER_PERFORMANCE_ERROR
                        + (int)*ufail->performanceErrors );
                    break;
                case UniversalFailure::securityErrorsCid:
                    errorCode = ErrorCode( CSER_SECURITY_ERROR
                        + (int)*ufail->securityErrors );
                    break;
                case UniversalFailure::unspecifiedErrorsCid:
                    errorCode = ErrorCode( ERUFUE_unspecified );
                    break;
                case UniversalFailure::nonStandardErrorsCid:
                    errorCode = ErrorCode( ERUFNSE_unspecified );
                    // ufail->nonStandardErrors; // FIXME: private data here
                    break;
                };
            break;
            }

        case ROSEapdu::rejectApduCid:
        {
            switch( resp->rejectApdu->problem->choiceId )
            {
                case RORJapduChoice1::generalProblemCid:
                    errorCode = ErrorCode( CSER_REJECT_GENERAL_PROBLEM
                        + (int)*resp->rejectApdu->problem->generalProblem );
                    break;
                case RORJapduChoice1::invokeProblemCid:
                    errorCode = ErrorCode( CSER_REJECT_INVOKE_PROBLEM
                        + (int)*resp->rejectApdu->problem->invokeProblem );
                    break;
                case RORJapduChoice1::returnResultProblemCid:
                    errorCode = ErrorCode( CSER_REJECT_RETURN_RESULT_PROBLEM
                        + (int)*resp->rejectApdu->problem->returnResultProblem );
                    break;
                case RORJapduChoice1::returnErrorProblemCid:
                    errorCode = ErrorCode( CSER_REJECT_RETURN_ERROR_PROBLEM
                        + (int)*resp->rejectApdu->problem->returnErrorProblem );
                    break;
                }
            break;
            }

        default:
            TRASSERT( false ); // This should not ever happen!
            break;
        }

    if ( errorCode )
        TRACE( this << " Device::ROSE_Invoke: Error: " << System::Verbose( errorCode ) );
    else
        TRACE( this << " Device::ROSE_Invoke: Succeded." );

    return errorCode;
    }

///////////////////////////////////////////////////////////////////////////////

void Device::ROSE_CancelInvoke( void )
{
    responseMutex.Lock ();

        if ( currentResponse )
            currentResponse->SetAPDU( NULL ); 

        ::PulseEvent( responseEvent ); 

    responseMutex.Unlock ();

    return;
    }

void Device::ROSE_SignalResponse( CSTAapdu* apdu, AsnIntType got_invoke_id )
{
    responseMutex.Lock ();

    if ( ! currentResponse )
    {
        responseMutex.Unlock ();
        LOG( DBG_WARN ) << this << " Device::SignalResult: There is no current ROSE/Invoke waiting being signaled" << eline;
        delete apdu->GetMemBlock ();
        return;
        }
    else if ( got_invoke_id == 0 ) // missing invoke id
    {
        responseMutex.Unlock ();
        LOG( DBG_WARN ) << this << " Device::SignalResult: Received Invoke ID missing" << eline;
        delete apdu->GetMemBlock ();
        return;
        }
    else if ( got_invoke_id != currentInvokeID )
    {
        AsnIntType expected_id = currentInvokeID;
        responseMutex.Unlock ();
        LOG( DBG_WARN ) << this << " Device::SignalResult: Received Invoke ID " 
            << got_invoke_id << " differs from expected " << expected_id << eline;
        delete apdu->GetMemBlock ();
        return;
        }

    // Set response APDU, and release all waiting threads.
    // Note that currentInvoke.~Invoke() will destroy apdu!
    //
    currentResponse->SetAPDU( apdu ); 
    ::PulseEvent( responseEvent ); 

    responseMutex.Unlock ();
    }
    
///////////////////////////////////////////////////////////////////////////////

ErrorCode Device:: ROSE_SendResult( AsnIntType op_id, AsnIntType remote_invoke_id, AsnType* res )
{
    MemBlock* mem = res->GetMemBlock ();

    OperationResult* opRes = new(mem) OperationResult(mem);
        opRes->SetTypeBy( op_id );
        opRes->value = res;

    RORSapduSeq* resApduSeq = new(mem) RORSapduSeq(mem);
        resApduSeq->operationValue.Set( op_id );
        resApduSeq->result = opRes;

    RORSapdu* resApdu = new(mem) RORSapdu(mem);
        resApdu->invokeID.Set( remote_invoke_id );
        resApdu->rORSapduSeq = resApduSeq;

    ROSEapdu* apdu = new(mem) ROSEapdu(mem);
        apdu->choiceId = ROSEapdu::resultApduCid;
        apdu->resultApdu = resApdu;

    return EncodeAndSendAPDU( apdu );
    }

///////////////////////////////////////////////////////////////////////////////

ErrorCode Device:: ROSE_SendReject(AsnIntType remote_invoke_id, RORJapduChoice1* problem )
{
    MemBlock* mem = problem->GetMemBlock ();

    ROSEapdu* apdu = new(mem) ROSEapdu(mem);
    apdu->choiceId = ROSEapdu::rejectApduCid;
    apdu->rejectApdu = new(mem) RORJapdu(mem);
    apdu->rejectApdu->problem = problem;

    // Build apdu->rejectApdu->invokeID.
    // Set to AsnNull, if remote_invoke_id is invalid i.e. == 0.
    //
    RORJapduChoice* invokeID = new(mem) RORJapduChoice(mem);
    apdu->rejectApdu->invokeID = invokeID;

    if ( remote_invoke_id == 0 )
    {
        invokeID->choiceId = RORJapduChoice::nullCid;
        invokeID->null = new(mem) AsnNull(mem);
        }
    else
    {
        invokeID->choiceId = RORJapduChoice::invokeIDTypeCid;
        invokeID->invokeIDType = new(mem) InvokeIDType(mem);
        invokeID->invokeIDType->Set( remote_invoke_id );
        }

    return EncodeAndSendAPDU( apdu );
    }

///////////////////////////////////////////////////////////////////////////////

void
Device:: DecodeReceivedAPDU( uint8* data, unsigned long len )
{
    MemBlock* mem = system->AllocateInboundMemBlock ();

    AsnBuf inputBuf;
    inputBuf.InstallData( data, len );

    CSTAapdu* apdu = new(mem) CSTAapdu( mem );
    size_t decodedLen;
    if ( ! apdu->BDecPdu( inputBuf, decodedLen ) )
    {
        LOG( DBG_ERROR ) 
            << this << " Device::DecodeReceivedAPDU: Encoungered General Problem: Badly Structured APDU" << eline
            << "========================================================" << eline
            << "in Received APDU: " << inputBuf
            << "--------------------------------------------------------" << eline
            << "decodedValue : " << *apdu
            << eline;

        // ROSE REJECT: General Problem: Badly structured APDU

        RORJapduChoice1* problem = new(mem) RORJapduChoice1(mem);
        problem->choiceId = RORJapduChoice1::generalProblemCid;
        problem->generalProblem = new(mem) GeneralProblem(mem);
        problem->generalProblem->Set( GeneralProblem::badlyStructuredAPDU );

        ROSE_SendReject( 0, problem );

        delete mem;
        return;
        }

#if 1
    TRACE( this << " Device::DecodeReceivedAPDU:" << eline
        //<< "========================================================" << eline
        //<< "Received APDU: " << inputBuf
        //<< "--------------------------------------------------------" << eline
        << "decodedValue : " << *apdu
        );
#endif

    switch( apdu->choiceId )
    {
        case CSTAapdu::invokeApduCid:

            switch( apdu->invokeApdu->operationValue )
            {
                case OperationIDType::cSTAEventReport:
                    OnRecv_EventReport( apdu );
                    break;

                case OperationIDType::systemStatus:
                    OnRecv_SystemStatus( apdu );
                    break;

                case OperationIDType::escapeService:
                    OnRecv_EscapeService( apdu );
                    break;

                // TODO: Implement Computer Function invokes here

                default:
                {
                    LOG( DBG_WARN ) << this << " Device::DecodeReceivedAPDU: Encountered Invoke Problem: Unrecognized Operation." << eline;

                    // ROSE REJECT: Invoke Problem: Unrecognized operation

                    RORJapduChoice1* problem = new(mem) RORJapduChoice1(mem);
                    problem->choiceId = RORJapduChoice1::invokeProblemCid;
                    problem->invokeProblem = new(mem) InvokeProblem(mem);
                    problem->invokeProblem->Set( InvokeProblem::unrecognisedOperation );

                    ROSE_SendReject( apdu->invokeApdu->invokeID, problem );

                    delete mem;
                    }
                    break;
                }
            return;

        case CSTAapdu::resultApduCid:
            ROSE_SignalResponse( apdu, apdu->resultApdu->invokeID );
            break;

        case CSTAapdu::errorApduCid:
            ROSE_SignalResponse( apdu, apdu->errorApdu->invokedID );
            break;

        case CSTAapdu::rejectApduCid:

            if ( apdu->rejectApdu->invokeID 
                && apdu->rejectApdu->invokeID->choiceId == RORJapduChoice::invokeIDTypeCid )
            {
                ROSE_SignalResponse( apdu, *apdu->rejectApdu->invokeID->invokeIDType );
                }
            else
            {
                ROSE_SignalResponse( apdu ); // Missing invoke id
                }
            break;

        default:
        {
            LOG( DBG_ERROR ) << this << " Device::DecodeReceivedAPDU: Encountered General Problem: Mistyped APDU" << eline;

            // Send ROSE REJECT: General Problem: Mistyped APDU

            RORJapduChoice1* problem = new(mem) RORJapduChoice1(mem);
            problem->choiceId = RORJapduChoice1::generalProblemCid;
            problem->generalProblem = new(mem) GeneralProblem(mem);
            problem->generalProblem->Set( GeneralProblem::mistypedAPDU );

            ROSE_SendReject( 0, problem );

            delete mem;
            }
            break;
        }
    }

//////////////////////////////////////////////////////////////////////////////
} // namespace MidCSTA