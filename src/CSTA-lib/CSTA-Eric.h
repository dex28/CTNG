#ifndef _CSTA_ERIC_H_INCLUDED
#define _CSTA_ERIC_H_INCLUDED

/*
    Project: CSTALib

    Module: CSTA-Eric.h

    Description: CSTA Private Data Structures for Ericsson MD110 

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

//////////////////////////////////////////////////////////////////////////////
// Ericsson Application Link Escape Services' data structures

#pragma pack(push)
#pragma pack(1)

// Escape Service: Enter DTMF

struct EricConnectionID
{
    char                deviceID[ 12 ];     // 12 bytes
    unsigned long       callID;             //  4 bytes
    };

struct EricEnterDTMF
{
    char                dtmf2Send[ 12 ];    // 12 bytes - DTMF string to send
    EricConnectionID    connectionID;       // 16 bytes - connection id to send DTMF on
    };

// Escape Service: QueryMsgDiversionStrings

typedef unsigned long EricTimeDateCode;

struct EricQueryMessageDiversionStringsResponse
{
    unsigned char       cMsgDivCode;        //  1 byte - 0..9
    char                notUsed[ 3 ];       //  3 bytes - not used
    EricTimeDateCode    enumTimeDataFormat; //  4 bytes
    char                strMsg[ 21 ];       // 21 bytes
    char                notUsed2[ 3 ];      //  3 bytes
    char                strings[ 10 ];      // 10 bytes
    };

// Escape Service: Query Feature and Response

enum EricFeatureCode
{
    MessageDiversion      = 0,
    FreeOn2ndLine         = 1,
    CancelAllDiversions   = 2               // not valid for Query Feature service
    };

struct EricQueryDeviceReq
{
    char                deviceID[ 12 ];     // 12 bytes
    EricFeatureCode     featureCode;        //  4 bytes
    };

enum EricDiversionType
{
    CASN1messageDiversion0  = 0,
    CASN1messageDiversion1  = 1,
    CASN1messageDiversion2  = 2,
    CASN1messageDiversion3  = 3,
    CASN1messageDiversion4  = 4,
    CASN1messageDiversion5  = 5,
    CASN1messageDiversion6  = 6,
    CASN1messageDiversion7  = 7,
    CASN1messageDiversion8  = 8,
    CASN1messageDiversion9  = 9
    };

struct EricMessageDiversion2
{
    unsigned long       mode;               // 4 bytes -- boolean: ON/OFF
    EricDiversionType   diversionType;      // 4 bytes
    char                szTimeordate[ 5 ];  // 5 bytes
    char                NotUsed[ 3 ];       // 3 bytes -- not used
    };                                      // Total: 16 bytes

struct EricFreeOn2ndLine
{
    unsigned long       mode;               // 4 bytes, 0 false, 1 true
    unsigned char       keynum;             // 1 byte
    };                                      // Total:  5 bytes

union EricFeatureU
{
    EricMessageDiversion2   msgDiversion;
    EricFreeOn2ndLine       F2L;
    };

struct EricQueryDevice
{
    char                deviceID[ 12 ];     // 12 bytes
    EricFeatureCode     featureCode;        // 4 bytes
    EricFeatureU        featureData;        // max of the union, which is 16 bytes
    };

// Escape Service: Set Feature and Response

    // see Query Feature and Response

// Escape Service: Cancel CallBack

#define CASN1callBackToCancel_present 0x01

struct EricCancelCB
{
    unsigned char       bit_mask;           // 1 byte
    char                deviceID[ 12 ];     // 12 bytes
    char                callbackToCancel[ 12 ]; // 12 bytes
    };

// Escape Service: Message Diversion

#define CASN1timeOrdate_present 0x01

struct EricMessageDiversion
{
    unsigned char       bit_mask;           // 1 byte
    char                deviceID[ 12 ];     // 12 bytes
    char                notUsed[ 3 ];       // 3 bytes -- not used
    unsigned long       mode;               // 4 bytes -- boolean: ON/OFF
    EricDiversionType   diversionType;      // 4 bytes
    char                ASN1timeOrdate[ 5 ]; // 5 bytes optionally included as entered on the telephone keypad
    };

// Escape Service: Account Code

#define ConnectionID_choosen 1
#define DeviceID_choosen     2

struct EricAccountCode
{
    unsigned short      choice;             // 2 bytes
    char                accountCode[ 14 ];  // 14 bytes
    EricConnectionID    connectionID;       // 16 bytes
    };


// Escape Service: Authorization Code

struct EricAuthorizationCode
{
    char                deviceID[ 12 ];     // 12 bytes
    char                authorizationCode[ 11 ]; // 11 bytes
    };

// Escape Service: Press Programmable Key

struct EricPressProgrammableKey
{
    char                deviceID[ 12 ];     // 12 bytes
    unsigned char       keyNumber;          // 1 byte
    char                notUsed[ 3 ];       // 3 bytes
    };

// Escape Service: Associate Data

struct EricAssociateData
{
    EricConnectionID    connectionID;       // 16 bytes
    char                associateData[ 24 ]; // 24 bytes -- correlator data
    };

// Escape Service: Forward ACD Group

struct EricForwardACDGroup
{
    char                deviceID[ 12 ];     // 12 bytes;
    unsigned long       mode;               // 4 bytes -- boolean: ON/OFF
    char                acdDevice[ 12 ];    // 12 bytes
    char                fwdToDevice[ 12 ];  // 12 bytes
    };

#pragma pack(pop)

//////////////////////////////////////////////////////////////////////////////
// Ericsson Application Link Escape Services' data structures
// size integrity test

inline void EricTestIntegrity( void )
{
    // base structures
    TRASSERT( sizeof( EricConnectionID ) == 16 );
    TRASSERT( sizeof( EricTimeDateCode ) == 4 );
    TRASSERT( sizeof( EricFeatureCode ) == 4 );
    TRASSERT( sizeof( EricDiversionType ) == 4 );
    TRASSERT( sizeof( EricFeatureU ) == 16 );

    // escape service structures
    TRASSERT( sizeof( EricEnterDTMF ) == 0x1C );
    TRASSERT( sizeof( EricQueryMessageDiversionStringsResponse ) == 0x2A );
    TRASSERT( sizeof( EricQueryDeviceReq ) == 0x10 );
    TRASSERT( sizeof( EricMessageDiversion2 ) == 16 );
    TRASSERT( sizeof( EricFreeOn2ndLine ) == 5 );
    TRASSERT( sizeof( EricQueryDevice ) == 0x20 );
    TRASSERT( sizeof( EricCancelCB ) == 0x19 );
    TRASSERT( sizeof( EricMessageDiversion ) == 0x1D );
    TRASSERT( sizeof( EricAccountCode ) == 0x20 );
    TRASSERT( sizeof( EricAuthorizationCode ) == 0x17 );
    TRASSERT( sizeof( EricPressProgrammableKey ) == 0x10 );
    TRASSERT( sizeof( EricAssociateData ) == 0x28 );
    TRASSERT( sizeof( EricForwardACDGroup ) == 0x28 );
    }

#endif // _CSTA_ERIC_H_INCLUDED
