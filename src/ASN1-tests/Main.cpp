/*
    Project: ASN1Test

    Module: Main.Cpp

    Description: ASN1Lib and CSTALib test module

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

//
// This program is used for testing of:
// 1. ASN.1 library memory management
// 2. ASN.1 Library ASN integral data types encode/decode integrity
// 3. CSTA Library encode/decode/encode/compare test drive on real data
// 4. CSTA encode/decode speed
// 5. MidCSTA layer performance (speed and memory
//

#include <fstream>
#include <iomanip>
#include <ctime>

#include "CSTA-Lib.h"
#include "asn-test.h"

using namespace std;
using namespace ASN;
using namespace CTsvcLIB;

namespace
{
    MemPool testPool( "Main module" );
}

int main( int argc, char* argv[] )
{
    LOG::UseHandle( ::GetStdHandle( STD_OUTPUT_HANDLE ) );

    const char* log_file = "D:\\Test.log";

    ::DeleteFile( log_file );
    extern MidCSTA::System cstaSys;
    cstaSys.OpenLogFile( log_file );

    extern int TestSampleBER( const char* filename, const char* out_filename );
    extern int TestSpeed( const char* filename, long loop_count );
    extern int TestMidCSTA( void );

    // Test ASN.1 Core Library encoding/decoding integrity
    TestAsn().Run();

    for( ;; )
        TestMidCSTA ();
    return 0;
    
#ifndef NDEBUG
    // Test CSTA encode/decode/encode/compare integrity
    TestSampleBER( "sample.BER", "output.BER" );
#else
    // Test CSTA encode/decode speed
    TestSpeed( "input.BER", /*loop count*/ 10000000 );
#endif

    // ... done, show final memory manager statistics.
    testPool.DumpStatistics( LOG( DBG_TRACE ) );

    return 0;
    }

int EncDecCSTA( uint8* outputData, size_t& encodedLen, uint8* data, size_t dataSize )
{
    MemBlock* mem = new(testPool) MemBlock(testPool);

    // Put the BER data read from the file
    // into buffer format, ready for reading from the
    // beginning.
    //
    AsnBuf inputBuf;
    inputBuf.InstallData( data, dataSize );

    CSTAapdu pr( mem );
    size_t decodedLen;
    if ( !pr.BDecPdu( inputBuf, decodedLen ) )
    {
        LOG( DBG_TRACE ) << "--- ERROR - Decode routines failed, exiting..." << eline;
        return -1;
        }

    AsnBuf outputBuf;
    outputBuf.Init( outputData, encodedLen );
    outputBuf.ResetInWriteRvsMode();

    if (!pr.BEncPdu (outputBuf, encodedLen))
    {
        LOG( DBG_TRACE ) << "--- ERROR - Encode routines failed" << eline;
        }

    delete mem;

    return 0;
    }

//////////////////////////////////////////////////////
// Test CSTA encode/decode speed
//
int TestSpeed( const char* filename, long loop_count )
{
    // Open the input BER data file.
    //
    ifstream dataFile;
    dataFile.open ( "input.ber" );

    if ( ! dataFile )
    {
        perror( "ifstream::open" );
        return 1;
        }

    // get size of the data file file
    dataFile.seekg( 0, ios::end );
    size_t dataSize = dataFile.tellg();
    dataFile.seekg( 0 );

    // read data from file into contiguous block for a buffer
    //
    MemBlock mem( testPool );
    uint8 *data = new(&mem) uint8[dataSize];
    if ( ! data )
        return 1;

    dataFile.read ( reinterpret_cast<char*>( data ), dataSize);
    dataFile.close();

    // Allocate a new buffer set up for writing to it.
    //
    size_t encodedLen = 0;
    uint8 *outputData = new(&mem) uint8[ dataSize + 512 ];
    if ( ! outputData )
	    return 1;

    // Timing ROSE enc/dec test.
    //
    time_t t1= time( NULL );
    for ( int i = 0; i < loop_count; i++ )
    {
        encodedLen = dataSize + 512; // put max size
        EncDecCSTA( outputData, encodedLen, data, dataSize );
        }
    time_t t2 = time( NULL );
    LOG( DBG_TRACE ) << "Elapsed: " << ( t2 - t1 )
        << " sec, T = " << ( t2 - t1 ) / double( loop_count )
        << " sec" << eline;

    return 0;
    }

//////////////////////////////////////////////////////
// Test CSTA encode/decode/encode integrity
//
int TestSampleBER( const char* filename, const char* out_filename )
{
    // Open the input BER data file.
    //
    ifstream dataFile;
    dataFile.open( filename, ios::binary );

    if ( ! dataFile )
    {
        perror( "ifstream::open" );
        return 1;
        }

    // open the output BER data file
    //
    ofstream odataFile;
    odataFile.open( out_filename, ios::binary );

    if ( ! odataFile)
    {
        perror ("ifstream::open" );
        return 1;
        }

    size_t apduOffset = 0;

    for ( ;; )
    {
        MemBlock mem( testPool );

        // Get next APDU
        //
        uint8 bl[ 2 ];
        
        if ( ! dataFile.read( reinterpret_cast<char*>( bl ), 2 ) )
            break;

        size_t dataSize = ( bl[ 0 ] << 8 ) + bl[ 1 ];

        apduOffset = dataFile.tellg ();

        // Read BER data from file.
        //
        uint8* data = ::new(&mem) uint8[ dataSize ];
        dataFile.read( reinterpret_cast<char*>( data ), dataSize );

        // Put the BER data read from the file
        // into buffer, ready for reading from the beginning.
        //
        AsnBuf inputBuf;
        inputBuf.InstallData( data, dataSize );

        LOG( DBG_TRACE ) << "======================================================== first pass" << eline;

        CSTAapdu apdu( &mem );
        size_t decodedLen;
        if ( ! apdu.BDecPdu( inputBuf, decodedLen ) )
        {
            LOG( DBG_TRACE ) << "at Offset 0x" << hex << apduOffset << dec << ", in APDU: ";
            inputBuf.Dump( LOG( DBG_TRACE ) );
            LOG( DBG_TRACE ) << "--------------------------------------------------------" << eline;
            LOG( DBG_TRACE ) << "decodedValue : " << apdu << eline;
            return -1;
            }

        LOG( DBG_TRACE ) << "APDU: " << inputBuf;
        LOG( DBG_TRACE ) << "--------------------------------------------------------" << eline;
        LOG( DBG_TRACE ) << "decodedValue : " << apdu << eline;

        // Allocate a new buffer set up for writing to it.
        //
        size_t encodedLen = 0;
        uint8 *outputData = new(&mem) uint8[ dataSize + 512 ];
        if ( ! outputData )
	        return 1;

        AsnBuf outputBuf;
        outputBuf.Init( outputData, 512 );
        outputBuf.ResetInWriteRvsMode();

        if ( ! apdu.BEncPdu( outputBuf, encodedLen ) )
        {
            LOG( DBG_TRACE ) << "--- ERROR: Encode routines failed" << eline;
            return -1;
            }

        if ( encodedLen != outputBuf.DataLen () )
        {
            LOG( DBG_TRACE ) << "--- ERROR: different encodedLen and outputBuf.DataLen() !!" << eline;
            return -1;
            }

        // Transfer data from outputBuf to inputBuf2
        //
        uint8* data2 = ::new(&mem) uint8[ encodedLen ];
        outputBuf.ResetInReadMode();
        for ( size_t i = 0; i < encodedLen; i++ )
            data2[ i ] =  outputBuf.GetByte();

        AsnBuf inputBuf2;
        inputBuf2.InstallData( data2, encodedLen );
        inputBuf2.ResetInReadMode ();

        // Now decode what we've encoded...
        //
        LOG( DBG_TRACE ) << "======================================================== second pass" << eline;

        size_t decodedLen2;
        CSTAapdu apdu2( &mem );
        if ( ! apdu2.BDecPdu( inputBuf2, decodedLen2 ) )
        {
            LOG( DBG_TRACE ) << "in reencoded APDU: ";
            inputBuf2.Dump( LOG( DBG_TRACE ) );
            LOG( DBG_TRACE ) << "--------------------------------------------------------" << eline;
            LOG( DBG_TRACE ) << "decodedValue : " << apdu2 << eline;
            return -1;
            }

        LOG( DBG_TRACE ) << "APDU: " << inputBuf2;
        LOG( DBG_TRACE ) << "--------------------------------------------------------" << eline;
        LOG( DBG_TRACE ) << "decodedValue : " << apdu2 << eline;

        // Write the BER value to odataFile
        //
        odataFile.put( (uint8)( encodedLen >> 8 ) );
        odataFile.put( (uint8)( encodedLen & 0xFF ) );
        outputBuf.ResetInReadMode();
        for ( size_t cnt = encodedLen; cnt > 0; cnt-- )
            odataFile.put( (uint8)outputBuf.GetByte() );

        if ( encodedLen != decodedLen )
        {
            LOG( DBG_TRACE ) << "---- WARNING: different decoded/encoded lengths! "
                << decodedLen << " vs. " << encodedLen << eline;
            }
        else
        {
            // compare data and final outputData
            for ( size_t i = 0; i < encodedLen; i++ )
            {
                if ( data[ i ] == data2[ i ] )
                    continue;

                LOG( DBG_TRACE ) << "---- WARNING: pos: "
                    << i << " different original and encoded bytes "
                    << TO_HEX( data[ i ] >> 8 ) << TO_HEX( data[ i ] )
                    << " vs. "
                    << TO_HEX( data2[ i ] >> 8 ) << TO_HEX( data2[ i ] )
                    << eline;
                }
            }
        }

    dataFile.close();
    odataFile.close();

    return 0;
    }


