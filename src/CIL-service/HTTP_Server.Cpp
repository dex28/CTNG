
#include "Protocols.h"

#include <mswsock.h>

using namespace CTsvcLIB;

TCP_Listener_Parameters HTTP_Server_Protocol::params;

ProtocolClass* HTTP_Server_Protocol::Clone()
{
    return new HTTP_Server_Protocol ();
    }

bool HTTP_Server_Protocol::OnError( DWORD dwErrorCode )
{
    DebugRC( dwErrorCode );
    LOG( DBG_ERROR ) << "-> Error code " << dwErrorCode << eline;

    delete this;

    return true;
    }

bool HTTP_Server_Protocol::OnConnect ()
{
    LOG( DBG_TRACE ) << "OnConnect" << eline;

    State = Rcv_HTTP_Header;
    XmtBufLen = 0;
    BufP = Buffer;
    BufLen = 0;

    if ( ! port->PostRead( BufP, sizeof( Buffer ) ) )
    {
        delete this;
        return false;
        }

    return true;
    }

bool HTTP_Server_Protocol::OnRemoteDisconnect ()
{
    LOG( DBG_TRACE ) << "OnRemoteDisconnect" << eline;

    if ( port->IsConnected () )
        delete this;

    return true;
    }

bool HTTP_Server_Protocol::OnReadCompleted( DWORD dwIoSize )
{
    if ( State == Rcv_HTTP_Header )
    {
        BufLen += dwIoSize;
        BufP += dwIoSize;
        *BufP = 0;

        // LOG( DBG_TRACE ) << "HTTP Got: [" << Buffer << "] " << eline;

        for ( iHeadLen = 0; iHeadLen < int(BufLen); iHeadLen++ )
        {
            // Search for HTTP header that ends with CR LF CR LF
            //
            if ( Buffer[ iHeadLen ] == 0x0D && Buffer[ iHeadLen + 1 ] == 0x0A
            && Buffer[ iHeadLen + 2 ] == 0x0D && Buffer[ iHeadLen + 3 ] == 0x0A
                )
            {
                //
                // Replace last CR LF sequence with zeroes
                //
                Buffer[ iHeadLen + 2 ] = 0;
                Buffer[ iHeadLen + 3 ] = 0;

                //
                // From now on iHeadLen is header length
                //
                iHeadLen += 2;

                goto HEADER_COMPLETED;
                }
            }

        iHeadLen = -1; // unknown yet

        State = Rcv_HTTP_Header;
        goto READ_PACKET;
        }

    else if ( State == Rcv_HTTP_Body )
    {
        BufLen += dwIoSize;
        BufP += dwIoSize;
        *BufP = 0;

        // LOG( DBG_TRACE ) << "HTTP Got: [" << Buffer << "] " << eline;

        if ( BufLen < pktSize )
        {
            //
            // Pend another read request for the rest packet body
            //
            State = Rcv_HTTP_Body;
            goto READ_PACKET;
            }
        else
        {
            goto PACKET_COMPLETED;
            }
        }
        
    LOG( DBG_ERROR )
        << "Should never rich this place."
        << eline;

    return false;

HEADER_COMPLETED:
{     
    LOG( DBG_TRACE ) << "Header (length = " << iHeadLen << "):" << eline
        << Buffer << eline;

    //
    // Now parse header and its fields ...
    //

    method = Buffer;
    PCHAR chp = Buffer;

    if ( strncmp( method, "GET", 3 ) == 0 )
    {
        chp += 3; // skip "GET"
        }
    else if ( strncmp( method, "HEAD", 4 ) == 0 )
    {
        chp += 4; // skip "HEAD"
        }
    else if ( strncmp( method, "POST", 4 ) == 0 )
    {
        chp += 4; // skip "POST"
        }
    else
    {
        LOG( DBG_TRACE ) << "Unknown method." << eline;

        PrintfLn( "HTTP/1.1 501 Not Implemented" );
        PrintfLn( "Content-Type: text/html" );
        PrintfLn( "" );
        PrintfLn( "Unknown method." );

        FlushXmtBuffer ();
        delete port;
        return FALSE;
        }

    if ( chp[ 0 ] != ' ' )
    {
        PrintfLn( "HTTP/1.1 501 Not Implemented" );
        PrintfLn( "Content-Type: text/html" );
        PrintfLn( "" );
        PrintfLn( "SP needed after method." );

        FlushXmtBuffer ();
        delete port;
        return FALSE;
        }

    *chp ++ = 0; // nullify and skip space

    requested_uri = chp;
    PCHAR dest = chp;

    for ( ;; )
    {
        if ( ! chp[0] )
        {
            LOG( DBG_ERROR )
                << "Requested_uri is not SP or CRLF terminated."
                << eline;
            break;
            }

        else if ( chp[0] == ' ' ) 
        {
            *dest ++ = 0;
            chp ++;
            version = chp;
            break;
            }

        else if ( chp[0] == 0x0D && chp[1] == 0x0A )
        {
            // version does not exist
            version = NULL;

            *dest ++ = 0; // nullify and skip CRLF
            chp += 2;
            break;
            }

        else if ( chp[0] == '%' )
        {
            chp ++;
            *dest++ = x2c( chp );
            chp += 2;
            }

        else
            *dest ++ = *chp ++;
        }

    if ( ! version )
    {
        version = "HTTP/1.generic";
        }
    else
    {
        for ( ;; ) 
        {
            if ( ! chp[0] )
            {
                LOG( DBG_ERROR )
                    << "Version is not CRLF terminated."
                    << eline;
                version = "not CRLF terminated";
                chp ++;
                break;
                }

            else if ( chp[0] == ' ' ) 
            {
                LOG( DBG_WARN )
                    << "Version is SP terminated."
                    << eline;

                *chp ++ = 0; // nullify and skip SP
                break;
                }

            else if ( chp[0] == 0x0D && chp[1] == 0x0A )
            {
                *chp ++ = 0; // nullify and skip CRLF
                *chp ++ = 0;
                break;
                }

            else
                chp ++;
            }
        }

    if ( strncmp( version, "HTTP/1", 6 ) != 0 )
    {
        LOG( DBG_TRACE ) << "Invalid version '" << version << "'." << eline;

        PrintfLn( "HTTP/1.1 501 Not Implemented" );
        PrintfLn( "Content-Type: text/html" );
        PrintfLn( "" );
        PrintfLn( "Invalid version '%s'.", version );

        FlushXmtBuffer ();
        delete port;
        return FALSE;
        }

    //
    // now parse header fields
    //

    // translate fields contents to lowercase
    strlwr( chp );

    content_type = strstr( chp, "content-type:" );
    content_length = strstr( chp, "content-length:" );
    keep_alive = strstr( chp, "connection:" );
    referer = strstr( chp, "referer:" );

    if ( content_type ) 
    {
        // find out beginning of field

        content_type += sizeof( "content-type:" );
        while ( content_type[0] && content_type[0] == ' ')
            content_type ++;

        // now, terminate end of field with null

        for ( chp = content_type; chp[0]; chp++ )
        {
            if ( chp[0] == ' ' 
            || ( chp[0] == 0x0D && chp[1] == 0x0A ) )
                break;
            }
        chp[0] = 0;
        }

    if ( content_length )
    {   
        // find out beginning of field

        content_length += sizeof( "content-length:" );
        while ( content_length[0] && content_length[0] == ' ')
            content_length ++;

        // now, terminate end of field with null

        for ( chp = content_length; chp[0]; chp++ )
        {
            if ( chp[0] == ' ' 
            || ( chp[0] == 0x0D && chp[1] == 0x0A ) )
                break;
            }
        chp[0] = 0;
        }

    if ( keep_alive )
    {   
        // find out beginning of field

        keep_alive += sizeof( "connection:" );
        while ( keep_alive[0] && keep_alive[0] == ' ' )
            keep_alive ++;

        // now, terminate end of field with null

        for ( chp = keep_alive; chp[0]; chp++ )
        {
            if ( chp[0] == ' ' 
            || ( chp[0] == 0x0D && chp[1] == 0x0A ) )
                break;
            }
        chp[0] = 0;
        }

    if ( referer )
    {   
        // find out beginning of field

        referer += sizeof( "referer:" );
        while ( referer[0] && referer[0] == ' ')
            referer ++;

        // now, terminate end of field with null

        for ( chp = referer; chp[0]; chp++ )
        {
            if ( chp[0] == ' ' 
            || ( chp[0] == 0x0D && chp[1] == 0x0A ) )
                break;
            }
        chp[0] = 0;
        }

    LOG( DBG_TRACE ) << "method=" << method
        << ", requested_uri=\"" << requested_uri
        << "\", version=\"" << version
        << "\"" << eline;

    LOG( DBG_TRACE ) << "content_type=\"" << ( content_type ? content_type : "<null>" ) << "\""
        << ", content_length=\"" << ( content_length ? content_length : "<null>" ) << "\""
        << ", connection=\"" << ( keep_alive ? keep_alive : "<null>" ) << "\""
        << ", referer=\"" << ( referer ? referer : "<null>" ) << "\"" << eline;

    if ( strcmp( method, "POST" ) == 0 )
    {
        // Find out length of posted data.
        //
        if ( content_length )
            iContentLen = atoi( content_length );
        else
            iContentLen = -1;

        // POST method must have ContentLength in header!
        //
        if ( iContentLen <= 0 )
        {
            LOG( DBG_ERROR )
                << "Content length missing in method POST."
                << eline;

            PrintfLn( "HTTP/1.1 400 Bad Request" );
            PrintfLn( "Content-Type: text/html" );
            PrintfLn( "" );
            PrintfLn( "Content length missing in method POST." );

            FlushXmtBuffer ();
            delete port;
            return FALSE;
            }
        else
        {
            LOG( DBG_TRACE ) << "Expecting " << iContentLen << " bytes." << eline;

            pContentData = Buffer + iHeadLen + 2; // skip zeroed CRLF
            pktSize = iHeadLen + 2 + iContentLen;

            if ( BufLen < pktSize )
            {
                // We need to complete whole body
                //
                State = Rcv_HTTP_Body;
                goto READ_PACKET;
                }
            else
            {
                // We have whole body, so ...
                //
                goto PACKET_COMPLETED;
                }
            }
        }
    }

    // In case of GET or HEAD fall out here ...
    // (packet contains only header)
    //
PACKET_COMPLETED:
{
    if ( strcmp( method, "GET" ) == 0
        || strcmp( method, "HEAD" ) == 0 )
    {
        if ( strcmp( requested_uri, "/" ) == 0 )
        {
            char filename[ 128 ];
            strcpy( filename, "./" );
            strcat( filename, "index.htm" );
            WriteMime( method, "text/html", filename );
            }
        else
        {
            char* datap = strchr( requested_uri, '?' );
            char empty[ 1 ] = { 0 };

            if ( ! datap )
            {
                pContentData = empty;
                iContentLen = 0;
                }
            else
            {
                *datap++ = '\0';
                pContentData = datap;
                iContentLen = strlen( datap );
                }
            
            if ( is_filetype( requested_uri, ".jsc" ) )
            {
                }
            else
            {
                struct
                {
                    char* extension;
                    char* mime_enc;
                    } known_types [] =
                {
                    { ".html",   "text/html" },
                    { ".htm",    "text/html" },
                    { ".gif",    "image/gif" },
                    { ".jpg",    "image/jpeg" },
                    { ".wav",    "audio/wav" },
                    { ".au",     "audio/basic" },
                    { ".class",  "application/octet-stream" },
                    { ".txt",    "text/plain" },
                    { ".java",   "text/plain" },
                    { ".tiff",   "image/tiff" },
                    { ".tif",    "image/tiff" },
                    { NULL, NULL }
                    };

                bool fOK = false;

                for ( int i = 0; known_types[ i ].extension; i++ )
                {
                    if ( is_filetype( requested_uri, known_types[ i ].extension ) )
                    {
                        char filename[ 1024 ];
                        strcpy( filename, "./" );
                        strcat( filename, requested_uri );
                        WriteMime( method, known_types[ i ].mime_enc, filename );
                        fOK = true;
                        break;
                        }
                    }

                if ( ! fOK )
                {
                    PrintfLn( "HTTP/1.1 404 Not Found" );
                    PrintfLn( "Content-Type: text/html" );
                    PrintfLn( "" );
                    PrintfLn( "URI [%s] not found.", requested_uri );
                    }
                }
            }
        }

    else if ( iContentLen > 0 )
    {
        pContentData[ iContentLen ] = 0;

        LOG( DBG_TRACE ) << "Posted data (length = " << iContentLen << "): "
            << eline
            << pContentData << eline;

        if ( content_type && strcmp( content_type, "application/x-www-form-urlencoded" ) )
        {
            LOG( DBG_ERROR )
                << "Invalid content type: "
                << ( content_type ? content_type : "<null>" )
                << eline;

            PrintfLn( "HTTP/1.1 200 OK" );
            PrintfLn( "Content-Type: text/html" );
            PrintfLn( "" );
            }
        else
        {
            PrintfLn( "HTTP/1.1 404 Not Found" );
            PrintfLn( "Content-Type: text/html" );
            PrintfLn( "" );
            PrintfLn( "URI [%s] not found.", requested_uri );
            }
        }

    FlushXmtBuffer ();

    if ( 1 ) // ! keep_alive )
    {
        delete port;
        return false;
        }
    else
    {
        State = Rcv_HTTP_Header;
        XmtBufLen = 0;
        BufP = Buffer;
        BufLen = 0;

        goto READ_PACKET;
        }

    return true;
    }

//---- Continue with Read Packet
//
READ_PACKET:

    //
    // Set up context information and perform an overlapped 
    // read on the socket.  
    //
    if ( ! port->PostRead( BufP, sizeof( Buffer ) - BufLen ) )
    {
        delete port;
        }

    return true;
    }


bool HTTP_Server_Protocol::OnWriteCompleted( DWORD dwIoSize )
{
    return true;
    }

void
HTTP_Server_Protocol:: WriteMime( char* method, char* type, char* filename )
{
    HANDLE hFile = CreateFile(
         filename,        // pointer to name of the file 
         GENERIC_READ,    // access (read-write) mode 
         FILE_SHARE_READ, // share mode 
         NULL,            // pointer to security descriptor, NULL means default
         OPEN_EXISTING,   // how to create 
         FILE_ATTRIBUTE_NORMAL, // file attributes 
         NULL             // handle to file with attributes to copy
         );

    if ( hFile == INVALID_HANDLE_VALUE )
    {
        DebugRC( GetLastError () );
        LOG( DBG_ERROR )
            << "-> Send File: cannot Open: " << filename
            << eline;

        if ( method )
        {
            PrintfLn( "HTTP/1.1 404 Not Found" );
            PrintfLn( "Content-Type: text/html" );
            PrintfLn( "" );
            }

        PrintfLn( "Mishap. File not found." );
        return;
        }

    if ( method )
    {
        BY_HANDLE_FILE_INFORMATION info;

        if ( ! GetFileInformationByHandle( hFile, &info ) )
        {
            DebugRC( GetLastError () );
            LOG( DBG_ERROR )
                << "Send File: cannot get file information: "
                << filename
                << eline;

            if ( method )
            {
                PrintfLn( "HTTP/1.1 404 Not Found" );
                PrintfLn( "Content-Type: text/html" );
                PrintfLn( "" );
                }

            PrintfLn( "Mishap. File not found." );
            return;
            }

        DWORD file_length = info.nFileSizeLow;

        SYSTEMTIME t;
        FileTimeToSystemTime( &info.ftLastWriteTime, &t );

        // modified_date contains last modification of file
        // expressed in RFC 1123 date format
        //
        char modified_date[ 80 ];

        static char* week_days[ 7 ]
            = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sut" };

        static char* year_months[ 12 ]
            = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",
                "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

        sprintf( modified_date,
            "%s, %02d %s %04d %02d:%02d:%02d GMT",
            week_days[ t.wDayOfWeek % 8 ],
            int( t.wDay ),
            year_months[ ( t.wMonth - 1 ) % 12 ],
            int( t.wYear ),
            int( t.wHour ), int( t.wMinute ), int( t.wSecond )
            );
    
        PrintfLn( "HTTP/1.1 200 OK" );
        PrintfLn( "Content-Type: %s", type );
        PrintfLn( "Content-Length: %lu", file_length );
        PrintfLn( "Last-Modified: %s", modified_date );
        PrintfLn( "" );

        FlushXmtBuffer ();

        if ( strcmp( method, "HEAD" ) == 0 )
            return;
        }

    LOG( DBG_TRACE ) << "-----------------Sending file" << eline;

    if ( ! TransmitFile(
        ( (QCPort_TCP*)port )->hsock, // SOCKET hSocket,                   
        hFile, // HANDLE hFile,                               
        0, // entire file; DWORD nNumberOfBytesToWrite,                
        0, // default size; DWORD nNumberOfBytesPerSend,                
        NULL, // Overlapped_Write, // LPOVERLAPPED lpOverlapped,                  
        NULL, // LPTRANSMIT_FILE_BUFFERS lpTransmitBuffers,  
        0 // DWORD dwFlags                               
        ) )
    {
        DebugRC( WSAGetLastError () );
        LOG( DBG_ERROR ) << " Transmit file failed" << eline;
        }
/*
    for ( ;; ) 
    {
        char buf[ 1000 ];

        DWORD bytes_read;

        if ( ! ReadFile( hFile, buf, sizeof( buf ), &bytes_read, NULL ) )
        {
            break;
            }

        if ( bytes_read > 0 )
        {
            if ( ! Write( buf, bytes_read ) )
                break;
            }
        else
            break;
        }
*/
    CloseHandle( hFile );
    }

BOOL
HTTP_Server_Protocol:: FlushXmtBuffer ()
{
    LOG( DBG_TRACE )
        << "FlushXmtBuffer - size " << XmtBufLen
        << eline;

    int ioSize = 0;

    for ( DWORD bufp = 0; bufp < XmtBufLen; bufp += ioSize )
    {
        ioSize = ::send( ((QCPort_TCP*)port)->hsock, XmtBuffer + bufp, XmtBufLen - bufp, 0 );

        if ( ioSize == SOCKET_ERROR )
        {
            int rc = WSAGetLastError ();

            if ( rc == WSAECONNRESET )
            {
                // HTTP client has closed connection
                //
                XmtBufLen = 0;
                return FALSE;
                }

            LOG( DBG_ERROR )
                << "FlushXmtBuffer: send: rc = "
                << rc << ", sent " << bufp << " of " << XmtBufLen << "."
                << eline;

            XmtBufLen = 0;
            return FALSE;
            }
        }

    XmtBufLen = 0;
    return TRUE;
    }

BOOL
HTTP_Server_Protocol:: Printf( char* Format, ... )
{
    va_list ArgList;
    va_start( ArgList, Format );

    int rc = _vsnprintf( &XmtBuffer[ XmtBufLen ], sizeof( XmtBuffer ) - XmtBufLen,
                     Format, ArgList );

    if ( rc >= 0 )
    {
        XmtBufLen += rc;
        }
    else 
    {
        // Less than zero indicates that the string could not be
        // fitted into the buffer. Output a special message indicating
        // that:
        //
        LOG( DBG_ERROR )
            << "Could not pack string into XmtBuffer."
            << eline;
        }

    if ( XmtBufLen >= sizeof( XmtBuffer ) - 1100 )
    {
        // Flush buffer on high watter mark
        //
        return FlushXmtBuffer ();
        }

    return TRUE;
    }

BOOL
HTTP_Server_Protocol:: PrintfLn( char* Format, ... )
{
    va_list ArgList;
    va_start( ArgList, Format );

    int rc = _vsnprintf( &XmtBuffer[ XmtBufLen ], sizeof( XmtBuffer ) - XmtBufLen - 2,
                     Format, ArgList );

    if ( rc >= 0 )
    {
        strncpy( XmtBuffer + XmtBufLen + rc, "\r\n", 2 );
        XmtBufLen += rc + 2;
        }
    else 
    {
        // Less than zero indicates that the string could not be
        // fitted into the buffer. Output a special message indicating
        // that:
        //
        LOG( DBG_ERROR )
            << "Could not pack string into XmtBuffer."
            << eline;
        }

    if ( XmtBufLen >= sizeof( XmtBuffer ) - 1100 )
    {
        // Flush buffer on high watter mark
        //
        return FlushXmtBuffer ();
        }

    return TRUE;
    }

BOOL
HTTP_Server_Protocol:: Write( void* buffer, size_t len )
{
    memcpy( XmtBuffer + XmtBufLen, buffer, len );
    XmtBufLen += len;

    if ( XmtBufLen >= sizeof( XmtBuffer ) - 1100 )
    {
        // Flush buffer on high watter mark
        //
        return FlushXmtBuffer ();
        }

    return TRUE;
    }

///////////////////////////////////////////////////////////////////////////////
// class HTTP_Server_Protocol::CGI_fields implementation
//
void
HTTP_Server_Protocol::CGI_fields:: Create
(
    char* pContentData
    )
{
    data = pContentData;

    ed_count = 0;

    int eofchar = '=';
    PCHAR src = data;
    PCHAR dest = data;

    while ( *src )
    {
        if ( *src == '=' && eofchar == '=' )
        {
            *dest ++ = 0;
            src ++;
            eofchar = '&'; // expect end of A=V with '&'
            }
        else if ( *src == '&' && eofchar == '&' )
        {
            *dest ++ = 0;
            src ++;
            ed_count ++;
            eofchar = '='; // expect end of A with '='
            }
        else if ( *src == '+' )
        {
            *dest ++ = ' ';
            src ++;
            }
        else if ( *src == '%' )
        {
            src ++;
            *dest ++ = x2c( src );
            src += 2;
            }
        else
        {
            *dest ++ = *src;
            src ++;
            }
        }

    *dest ++ = 0;

    //
    // If we are expecting '&' but we have found
    // premature end of data, assume that '&' i.e.
    // end of A=V field is found, so increment total
    // number of fields we have.
    //
    if ( eofchar == '&' )
        ed_count ++;
    }

void
HTTP_Server_Protocol::CGI_fields:: Dump ()
{
    PCHAR src = data;

    LOG( DBG_TRACE ) << "CGI fields: " << ed_count << eline;

    //
    // scan A '\0' V '\0' pairs
    //

    for ( int i = 0; i < ed_count; i++ )
    {
        LOG dbg( DBG_TRACE );

        dbg << "   [" << src << "]=";

        while ( *src ++ ) // skip A
            ;

        dbg << "\"" << src << "\""
            << eline;

        while ( *src ++ ) // skip V
            ;
        }
    }

char*
HTTP_Server_Protocol::CGI_fields:: operator[] ( char* field_name )
{
    PCHAR src = data;

    for ( int i = 0; i < ed_count; i++ )
    {
        // src points to Attribute

        if ( stricmp( src, field_name ) == 0 )
        {
            // skip Attribute
            while ( *src ++ )
                ;

            // return Value
            return src;
            }

        // skip Attribute

        while ( *src ++ )
            ;

        // skip Value

        while ( *src ++ )
            ;
        }

    return NULL;
    }

char*
HTTP_Server_Protocol::CGI_fields:: A( int n )
{
    if ( n < 0 || n >= ed_count )
        return NULL;

    PCHAR src = data;

    for ( int i = 0; i < ed_count; i++ )
    {
        // src points to Attribute

        if ( i == n )
        {
            // return Attribute
            return src;
            }

        // skip Attribute

        while ( *src ++ )
            ;

        // skip Value

        while ( *src ++ )
            ;
        }

    return NULL;
    }

char*
HTTP_Server_Protocol::CGI_fields:: V( int n )
{
    if ( n < 0 || n >= ed_count )
        return NULL;

    PCHAR src = data;

    for ( int i = 0; i < ed_count; i++ )
    {
        // src points to Attribute

        if ( i == n )
        {
            // skip Attribute
            while ( *src ++ )
                ;

            // return Value
            return src;
            }

        // skip Attribute

        while ( *src ++ )
            ;

        // skip Value

        while ( *src ++ )
            ;
        }

    return NULL;
    }

