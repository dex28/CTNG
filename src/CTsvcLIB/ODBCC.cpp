/*
    Project: CTsvcLIB

    Module: ODBCC.Cpp

    Description: ODBC 3.0 wrapper classes

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "CTsvcLIB.h"

using namespace std;

namespace CTsvcLIB
{

SLONG
ODBC_TIMESTAMP:: operator -
(
    ODBC_TIMESTAMP& t
    )
{
    static const int yearDays [2][12] =
       {
         { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 },
         { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 }
       };

    SLONG delta_days = 0;

    {
        SLONG yy1 = value.year;

        int spec1 = (yy1 % 4L == 0L) && (yy1 % 400L != 0L);

        yy1 = value.day - 1 + yearDays [ spec1 ] [ value.month - 1 ]
            + yy1 * 365L + (yy1 - 1L) / 4 - (yy1 - 1L) / 400;
           

        delta_days = yy1;
        }

    {
        SLONG yy2 = t.value.year;

        int spec2 = (yy2 % 4L == 0L) && (yy2 % 400L != 0L);

        yy2 = t.value.day - 1 + yearDays [ spec2 ] [ t.value.month - 1 ]
            + yy2 * 365L + (yy2 - 1L) / 4 - (yy2 - 1L) / 400;

        delta_days -= yy2;
        }

    return delta_days * 24L * 3600L
           + ( value.hour - t.value.hour ) * 3600L
           + ( value.minute - t.value.minute ) * 60L
           + ( value.second - t.value.second );
    }

///////////////////////////////////////////////////////////////////////////////
// ODBC_SESSION class implementation

ODBC_SESSION:: ODBC_SESSION
(
    void
    )
{
    LOG( DBG_ODBC )
        << "ODBC_SESSION: Construct."
        << eline;

    henv = SQL_NULL_HENV;
    hdbc = SQL_NULL_HDBC;

    retcode = SQLAllocHandle( SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv );

    if ( Error () )
        return;

    retcode = SQLSetEnvAttr(
        henv,                        // SQLHENV EnvironmentHandle
        SQL_ATTR_ODBC_VERSION,       // SQLINTEGER Attribute
        SQLPOINTER( SQL_OV_ODBC3 ),  // SQLPOINTER Value
        SQL_IS_INTEGER               // SQLINTEGER StringLength
        );
    }

ODBC_SESSION:: ~ODBC_SESSION
(
    void
    )
{
    LOG( DBG_ODBC )
        << "ODBC_SESSION: Destruct."
        << eline;

    if ( hdbc == SQL_NULL_HDBC )
        return;

    Disconnect ();

    retcode = SQLFreeHandle( SQL_HANDLE_ENV, henv );
    }

BOOL
ODBC_SESSION:: AnyError
(
    void
    )
{
    return retcode != SQL_SUCCESS;
    }

BOOL
ODBC_SESSION:: Error
(
    void
    )
{
    return retcode != SQL_SUCCESS
        && retcode != SQL_SUCCESS_WITH_INFO;
    }

void
ODBC_SESSION:: Perror
(
    char* where
    )
{
    if ( SQL_SUCCESS == retcode )
        return;

    int log_chn = retcode == SQL_SUCCESS_WITH_INFO ? DBG_WARN : DBG_ERROR;

    SQLSMALLINT htype = SQL_HANDLE_ENV;
    SQLHANDLE handle = henv;

    if ( hdbc != SQL_NULL_HDBC )
    {
        htype = SQL_HANDLE_DBC;
        handle = hdbc;
        }

    for ( int i = 1 ;; i++ )
    {
        SQLCHAR errorMsg[ SQL_MAX_MESSAGE_LENGTH ];
        SQLCHAR sqlState[ 6 ];
        SQLINTEGER nativeError;
        SQLSMALLINT MsgLen = sizeof( errorMsg ) - 1;

        SQLRETURN rc = SQLGetDiagRec(
                htype,                 // SQLSMALLINT  fHandleType
                handle,                // SQLHANDLE    handle
                i,                     // SQLSMALLINT  iRecord
                sqlState,              // SQLTCHAR*    szSqlState
                &nativeError,          // SQLINTEGER*  pfNativeError
                errorMsg,              // SQLTCHAR*    szErrorMsg
                MsgLen,                // SQLSMALLINT  cbErrorMsgMax
                &MsgLen                // SQLSMALLINT* pcbErrorMsg
                );

        if ( rc == SQL_NO_DATA )
        {
            if ( i == 1 )
            {
                if ( where )
                {
                    LOG( log_chn ) << where << ": <unknown odbc error>" << eline;
                    }
                else
                {
                    LOG( log_chn ) << "<unknown odbc error>" << eline;
                    }
                }
            break;
            }

        errorMsg[ MsgLen ] = 0;

        if ( where )
        {
            LOG( log_chn )
                << where << ": " << errorMsg
                << eline;
            }
        else
        {
            LOG( log_chn )
                << errorMsg
                << eline;
            }
        }
    }

ODBC_SESSION&
ODBC_SESSION:: Connect
(
    char* datasource,
    char* username,
    char* password,
    int timeout
    )
{
    LOG( DBG_ODBC )
        << "ODBC_SESSION: Connect " << datasource
        << " [" << username << "/" << password << "]."
        << eline;

    retcode = SQLAllocHandle( SQL_HANDLE_DBC, henv, &hdbc );
    Perror( "SQLAllocHandle(DBC)" );
    if ( Error () )
        return *this;

    if ( timeout > 0 )
    {
        // Set login timeout
        //
        retcode = SQLSetConnectAttr(
            hdbc,                      // SQLHDBC hdbc
            SQL_ATTR_LOGIN_TIMEOUT,    // SQLINTEGER fAttribute
            SQLPOINTER( timeout ),     // SQLPOINTER rgbValue
            NULL                       // SQLINTEGER cbValue
            );

        Perror( "SQLSetConnectAttr" );
        }

    // Connect to data source
    //
    retcode = SQLConnect(
        hdbc,                    // SQLHDBC hdbc
        (SQLCHAR*) datasource,   // SQLTCHAR* szDSN
        SQL_NTS,                 // SQLSMALLING cbDSN
        (SQLCHAR*) username,     // SQLTCHAR* szUID
        SQL_NTS,                 // SQLSMALLINT cbUID
        (SQLCHAR*) password,     // SQLTCHAR* szAuthStr
        SQL_NTS                  // SQLSMALLINT cbAuthStr
        );

    Perror( "SQLConnect" );
    if ( Error () )
        return *this;

    return *this;
    }

ODBC_SESSION&
ODBC_SESSION:: Disconnect
(
    void
    )
{
    LOG( DBG_ODBC )
        << "ODBC_SESSION: Disconnect."
        << eline;

    // Disconnect and clean up handles
    //
    retcode = SQLDisconnect( hdbc );
    Perror( "SQLDisconnect" );

    retcode = SQLFreeHandle( SQL_HANDLE_DBC, hdbc );
    hdbc = SQL_NULL_HDBC;
    Perror( "SQLFreeHandle(DBC)" );

    return *this;
    }

ODBC_SESSION&
ODBC_SESSION:: AutoCommitOn
(
    void
    )
{
    LOG( DBG_ODBC )
        << "ODBC_SESSION: AutoCommitOn."
        << eline;

    retcode = SQLSetConnectAttr(
        hdbc,                             // SQLHDBC hdbc
        SQL_ATTR_AUTOCOMMIT,              // SQLINTEGER fAttribute
        SQLPOINTER( SQL_AUTOCOMMIT_ON ),  // SQLPOINTER rgbValue
        NULL                              // SQLINTEGER cbValue
        );
    Perror( "AutoCommitOn" );

    return *this;
    }

ODBC_SESSION&
ODBC_SESSION:: AutoCommitOff
(
    void
    )
{
    LOG( DBG_ODBC )
        << "ODBC_SESSION: AutoCommitOff."
        << eline;

    retcode = SQLSetConnectAttr(
        hdbc,                             // SQLHDBC hdbc
        SQL_ATTR_AUTOCOMMIT,              // SQLINTEGER fAttribute
        SQLPOINTER( SQL_AUTOCOMMIT_OFF ), // SQLPOINTER rgbValue
        NULL                              // SQLINTEGER cbValue
        );
    Perror( "AutoCommitOn" );

    return *this;
    }

ODBC_SESSION&
ODBC_SESSION:: Commit
(
    void
    )
{
    LOG( DBG_ODBC )
        << "ODBC_SESSION: Commit."
        << eline;

    retcode = SQLEndTran( SQL_HANDLE_DBC, hdbc, SQL_COMMIT );
    Perror( "SQLEndTran(COMMIT)" );

    return *this;
    }

ODBC_SESSION&
ODBC_SESSION:: Rollback
(
    void
    )
{
    LOG( DBG_ODBC )
        << "ODBC_SESSION: Rollback."
        << eline;

    retcode = SQLEndTran( SQL_HANDLE_DBC, hdbc, SQL_ROLLBACK );
    Perror( "SQLEndTran(ROLLBACK)" );

    return *this;
    }

///////////////////////////////////////////////////////////////////////////////
// ODBC_STATEMENT class implementation

ODBC_STATEMENT:: ODBC_STATEMENT
(
    ODBC_SESSION* p_sess,
    char* cursor_name
    )
{
    LOG( DBG_ODBC )
        << "ODBC_STATEMENT: Construct."
        << eline;

    pSess = p_sess;
    hstmt = SQL_NULL_HSTMT;

    retcode = SQLAllocHandle( SQL_HANDLE_STMT, pSess->hdbc, &hstmt );
    Perror( "SQLAllocHandle(STMT)" );
    if ( Error () )
        return;

    if ( cursor_name )
    {
        // Specify an updatable static cursor with 20 rows of data. Set
        // the cursor name, execute the SELECT statement, and bind the
        // rowset buffers to result set columns in column-wise fashion.
        //
        retcode = SQLSetStmtAttr( hstmt,
            SQL_ATTR_CONCURRENCY, SQLPOINTER( SQL_CONCUR_VALUES ),
            NULL );
        Perror( "SQLSetStmtAttr(CONCURENCY)" );
        if ( Error() ) 
            return;

        retcode = SQLSetStmtAttr( hstmt,
            SQL_ATTR_CURSOR_TYPE, SQLPOINTER( SQL_CURSOR_STATIC ),
            NULL );
        Perror( "SQLSetStmtAttr(CURSOR_TYPE)" );
        if ( Error() ) 
            return;

        //SQLSetStmtAttr( hstmt, SQL_ATTR_ROW_ARRAY_SIZE, ROWS, NULL );
        //SQLSetStmtAttr( hstmt, SQL_ATTR_ROW_STATUS_PTR, RowStatusArray, NULL );
        //SQLSetStmtAttr( hstmt, SQL_ATTR_ROWS_FETCHED_PTR, &crow, NULL );

        retcode = SQLSetCursorName(
               hstmt,                 // SQLHSTMT  StatementHandle
               (SQLCHAR*)cursor_name, // SQLCHAR* CursorName
               SQL_NTS                // SQLSMALLINT NameLength
               );

        Perror( "SQLSetCursorName" );
        if ( Error() ) 
            return;
        }

    last_stmt = NULL;
    icol = 0;
    ipar = 0;
    }

ODBC_STATEMENT:: ~ODBC_STATEMENT
(
    void
    )
{
    LOG( DBG_ODBC )
        << "ODBC_STATEMENT: Destruct."
        << eline;

    retcode = SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    hstmt = SQL_NULL_HSTMT;
    Perror( "SQLFreeStmt" );
    }

ODBC_STATEMENT&
ODBC_STATEMENT:: Reconstruct
(
    void
    )
{
    LOG( DBG_ODBC )
        << "ODBC_STATEMENT: Reconstruct."
        << eline;

    retcode = SQLFreeStmt( hstmt, SQL_CLOSE );
    Perror( "SQLFreeStmt(CLOSE)" );

    // FIXME: do we need this ?

    retcode = SQLFreeStmt( hstmt, SQL_UNBIND );
    Perror( "SQLFreeStmt(UNBIND)" );

    retcode = SQLFreeStmt( hstmt, SQL_RESET_PARAMS );
    Perror( "SQLFreeStmt(RESET_PARAMS)" );

    last_stmt = NULL;
    icol = 0;
    ipar = 0;

    return *this;
    }

BOOL
ODBC_STATEMENT:: AnyError
(
    void
    )
{
    return retcode != SQL_SUCCESS;
    }

BOOL
ODBC_STATEMENT:: Error
(
    void
    )
{
    return retcode != SQL_SUCCESS
        && retcode != SQL_SUCCESS_WITH_INFO;
    }

void
ODBC_STATEMENT:: Perror
(
    char* where
    )
{
    if ( SQL_SUCCESS == retcode )
        return;

    if ( SQL_NO_DATA == retcode )
    {
        if ( where )
        {
            LOG( DBG_TRACE ) << where << ": <no data found>" << eline;
            }
        else
        {
            LOG( DBG_TRACE ) << "<no data found" << eline;
            }
        return;
        }

    int log_chn = retcode == SQL_SUCCESS_WITH_INFO ? DBG_WARN : DBG_ERROR;

    SQLSMALLINT htype = SQL_HANDLE_ENV;
    SQLHANDLE handle = pSess->henv;

    if ( hstmt != SQL_NULL_HSTMT )
    {
        htype = SQL_HANDLE_STMT;
        handle = hstmt;
        }
    else if ( pSess->hdbc != SQL_NULL_HDBC )
    {
        htype = SQL_HANDLE_DBC;
        handle = pSess->hdbc;
        }

    for ( int i = 1 ;; i++ )
    {
        SQLCHAR errorMsg[ SQL_MAX_MESSAGE_LENGTH ];
        SQLCHAR sqlState[ 6 ];
        SQLINTEGER nativeError;
        SQLSMALLINT MsgLen = sizeof( errorMsg ) - 1;

        SQLRETURN rc = SQLGetDiagRec(
                htype,                 // SQLSMALLINT  fHandleType
                handle,                // SQLHANDLE    handle
                i,                     // SQLSMALLINT  iRecord
                sqlState,              // SQLTCHAR*    szSqlState
                &nativeError,          // SQLINTEGER*  pfNativeError
                errorMsg,              // SQLTCHAR*    szErrorMsg
                MsgLen,                // SQLSMALLINT  cbErrorMsgMax
                &MsgLen                // SQLSMALLINT* pcbErrorMsg
                );

        if ( rc == SQL_NO_DATA )
        {
            if ( i == 1 )
            {
                if ( where )
                {
                    LOG( log_chn ) << where << ": <unknown odbc error>" << eline;
                    }
                else
                {
                    LOG( log_chn ) << "<unknown odbc error>" << eline;
                    }
                }
            break;
            }

        errorMsg[ MsgLen ] = 0;

        if ( where )
        {
            LOG( log_chn )
                << where << ": " << errorMsg
                << eline;
            }
        else
        {
            LOG( log_chn )
                << errorMsg
                << eline;
            }
        }
    }

ODBC_STATEMENT&
ODBC_STATEMENT:: SetConcurrency
(
    SQLUINTEGER option
    )
{
    retcode = SQLSetStmtAttr( hstmt, SQL_ATTR_CONCURRENCY, SQLPOINTER( option ), NULL );
    Perror( "SQLSetStmtOption[concurency]" );

    return *this;
    }

ODBC_STATEMENT&
ODBC_STATEMENT:: Prepare
(
    char* statement
    )
{
    if ( Error() )
        return *this;

    LOG( DBG_ODBC )
        << "ODBC_STATEMENT: Prepare " << statement
        << eline;

    last_stmt = statement;     
    icol = 0;
    ipar = 0;

    retcode = SQLPrepare( hstmt, (SQLCHAR*) statement, SQL_NTS );
    Perror( "SQLPrepare" );

    return *this;
    }

ODBC_STATEMENT&
ODBC_STATEMENT:: Execute
(
    void
    )
{
    if ( Error() )
        return *this;

    LOG( DBG_ODBC )
        << "ODBC_STATEMENT: Execute."
        << eline;

    SQLSMALLINT ccol = 0;
    retcode = SQLNumResultCols( hstmt, &ccol );
    Perror( "SQLNumResultCols" );

    LOG( DBG_ODBC )
        << "We have " << ccol << " column(s)."
        << eline; 

    SQLSMALLINT cpar = 0;
    retcode = SQLNumParams( hstmt, &cpar );
    if ( Error () )
    {
        Perror( "SQLNumParams" );
        }
    else
    {
        LOG( DBG_ODBC )
            << "We have " << cpar << " parameter(s)."
            << eline;
        }

    if ( icol != ccol || ipar != cpar )
    {
        LOG( DBG_ODBC )
            << "ODBC ERROR: Column/Parameter count mismatch."
            << eline;
        }

    retcode = SQLExecute( hstmt );
    Perror( "SQLExecute" );

    return *this;
    }

ODBC_STATEMENT&
ODBC_STATEMENT:: ExecuteDirect
(
    char* statement
    )
{
    if ( Error() )
        return *this;

    last_stmt = statement;

    LOG( DBG_ODBC )
        << "ODBC_STATEMENT: ExecuteDirect " << statement
        << eline;

    retcode = SQLExecDirect( hstmt, (SQLCHAR*) statement, SQL_NTS );
    Perror( "SQLExecDirect" );

    return *this;
    }

ODBC_STATEMENT&
ODBC_STATEMENT:: Fetch
(
    void
    )
{
    if ( Error() )
        return *this;

    LOG( DBG_ODBC )
        << "ODBC_STATEMENT: Fetch."
        << eline;

    retcode = SQLFetch( hstmt );

    if ( retcode != SQL_NO_DATA && Error () )
        Perror( "SQLFetch" );

    return *this;
    }

ODBC_STATEMENT&
ODBC_STATEMENT:: BindColumn
(
    SQLUSMALLINT i,
    ODBC_FIELD& field
    )
{
    if ( Error() )
        return *this;

    LOG( DBG_ODBC )
        << "ODBC_STATEMENT: BindColumn " << i << "."
        << eline;

    retcode = SQLBindCol(
        hstmt,              // SQLHSTMT StatementHandle
        i,                  // SQLUSMALLINT ColumnNumer
        field.fCType,       // SQLSMALLINT TargetType
        field.rgbValue,     // SQLPOINTER TargetValue
        field.cbValueMax,   // SQLINTEGER BufferLength
        &field.cbValue      // SQLINTEGER* StrLen_or_ind
        );
    Perror( "SQLBindCol" );

    return *this;
    }

ODBC_STATEMENT&
ODBC_STATEMENT:: BindParameter
(
    SQLUSMALLINT i,
    ODBC_FIELD& field,
    SQLSMALLINT fSqlType,
    SQLSMALLINT fParamType
    )
{
    if ( Error() )
        return *this;

    LOG( DBG_ODBC )
        << "ODBC_STATEMENT: BindParameter " << i << "."
        << eline;

    retcode = SQLBindParameter(
        hstmt,            // SQLHSTMT StatementHandle
        i,                // SQLUSMALLINT ParameterNumber
        fParamType,       // SQLSMALLINT InputOutputType
        field.fCType,     // SQLSMALLINT ValueType
        fSqlType,         // SQLSMALLINT ParameterType
        field.cbColDef,   // SQLUINTEGER ColumnSize
        field.ibScale,    // SQLSMALLINT DecimalDigits
        field.rgbValue,   // SQLPOINTER ParameterValuePtr
        field.cbValueMax, // SQLINTEGER BufferLength
        &field.cbValue    // SQLINTEGER* StrLen_or_IndPtr
        );
    Perror( "SQLBindParameter" );

    return *this;
    }

ODBC_STATEMENT&
ODBC_STATEMENT:: operator >>
(
    ODBC_FIELD& field
    )
{
    if ( Error() )
        return *this;

    icol++;

    LOG( DBG_ODBC )
        << "ODBC_STATEMENT: operator >> " << icol << "."
        << eline;

    retcode = SQLBindCol(
        hstmt,              // SQLHSTMT StatementHandle
        icol,               // SQLUSMALLINT ColumnNumer
        field.fCType,       // SQLSMALLINT TargetType
        field.rgbValue,     // SQLPOINTER TargetValue
        field.cbValueMax,   // SQLINTEGER BufferLength
        &field.cbValue      // SQLINTEGER* StrLen_or_ind
        );
    Perror( "SQLBindCol" );

    return *this;
    }

ODBC_STATEMENT&
ODBC_STATEMENT:: operator <<
(
    ODBC_FIELD& field
    )
{
    if ( Error() )
        return *this;

    ipar++;

    LOG( DBG_ODBC )
        << "ODBC_STATEMENT: operator << " << ipar << "."
        << eline;

    SQLSMALLINT fParamType = SQL_PARAM_INPUT;
    SQLSMALLINT fSqlType = SQL_CHAR;

    switch( field.fCType )
    {
        case SQL_C_CHAR:
            if ( field.cbValueMax >= 254 )
            {
                fSqlType = SQL_LONGVARCHAR;
			    field.cbColDef = strlen( (char*)field.rgbValue );
			    field.cbValue = SQL_NTS;
                }
            else
            {
                fSqlType = SQL_CHAR;
			    field.cbValue = SQL_NTS;
                }
            break;

        case SQL_C_ULONG:
        case SQL_C_SLONG:
        case SQL_C_USHORT:
        case SQL_C_SSHORT:
            fSqlType = SQL_INTEGER;
            break;

        case SQL_C_DOUBLE:
        case SQL_C_FLOAT:
            fSqlType = SQL_DOUBLE;
            break;

        case SQL_C_DATE:
            fSqlType = SQL_DATE;
            break;

        case SQL_C_TIME:
            fSqlType = SQL_TIME;
            break;

        case SQL_C_TIMESTAMP:
            fSqlType = SQL_TIMESTAMP;
            break;

        case SQL_C_BINARY:
            fSqlType = SQL_BINARY;
            break;

        default:
            TRASSERT(false);
            break;
        }

    retcode = SQLBindParameter(
        hstmt,            // SQLHSTMT StatementHandle
        ipar,             // SQLUSMALLINT ParameterNumber
        fParamType,       // SQLSMALLINT InputOutputType
        field.fCType,     // SQLSMALLINT ValueType
        fSqlType,         // SQLSMALLINT ParameterType
        field.cbColDef,   // SQLUINTEGER ColumnSize
        field.ibScale,    // SQLSMALLINT DecimalDigits
        field.rgbValue,   // SQLPOINTER ParameterValuePtr
        field.cbValueMax, // SQLINTEGER BufferLength
        &field.cbValue    // SQLINTEGER* StrLen_or_IndPtr
        );

    if ( AnyError () )
    {
        LOG( DBG_ODBC )
            << "InputOutputType: " << fParamType
            << ", ValueType: " << field.fCType
            << ", ParameterType: " << fSqlType
            << ", ColumnSize: " << field.cbColDef
            << ", DecimalDigits: " << field.ibScale
            << ", BufferLength: " << field.cbValueMax
            << ", StrLen_or_IndPtr: " << field.cbValue
            << eline;
        }

    Perror( "SQLBindParameter" );

    return *this;
    }

} // namespace CTsvcLIB