#ifndef _CSTA_any_h_included
#define _CSTA_any_h_included

/*
    Project: CSTALib

    Module: CSTA-Any.h

    Description: ROSE linkage to CSTA / ANY datatypes.

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

namespace ASN
{

///////////////////////////////////////////////////////////////////////////////
// forward declarations to ASN namespace types:
//
class EventTypeID;

///////////////////////////////////////////////////////////////////////////////
// argument ANY DEFINED BY OPERATION
//
class OperationArgument : public AsnType
{
public:
  
    AsnIntType  intId;
    AsnType*    value;

    OperationArgument( MemBlock* mb )
        : AsnType( mb )
        { intId = -1; value = NULL; }

    ~OperationArgument()
        {}

    void SetTypeBy( const AsnIntType id )
        { intId = id; }

    AsnLen BEnc( AsnBuf& b );

    void BDec( AsnBuf& b, AsnLen &bytesDecoded );

    PDU_MEMBER_MACROS

    void Print (CTsvcLIB::LOG &os) const
    {
        if ( value )
            os << *value;
        else
            os << "VOID";
        }
};          

///////////////////////////////////////////////////////////////////////////////
// result ANY DEFINED BY OPERATION
//
class OperationResult : public AsnType
{
public:
  
    AsnIntType  intId;
    AsnType*    value;

    OperationResult( MemBlock* mb )
        : AsnType( mb )
        { intId = -1; value = NULL; }

    ~OperationResult()
        {}

    void SetTypeBy( const AsnIntType id )
        { intId = id; }

    AsnLen BEnc( AsnBuf& b );

    void BDec( AsnBuf& b, AsnLen &bytesDecoded );

    PDU_MEMBER_MACROS

    void Print (CTsvcLIB::LOG &os) const
    {
        if ( value )
            os << *value;
        else
            os << "VOID";
        }
};

///////////////////////////////////////////////////////////////////////////////
// parameter ANY DEFINED BY ERROR
//
class ErrorParameter : public AsnType
{
public:
  
    AsnIntType  intId;
    AsnType*    value;

    ErrorParameter( MemBlock* mb )
        : AsnType( mb )
        { intId = -1; value = NULL; }

    ~ErrorParameter()
        {}

    void SetTypeBy( const AsnIntType id )
        { intId = id; }

    AsnLen BEnc( AsnBuf& b );

    void BDec( AsnBuf& b, AsnLen &bytesDecoded );

    PDU_MEMBER_MACROS

    void Print (CTsvcLIB::LOG &os) const
    {
        if ( value )
            os << *value;
        else
            os << "VOID";
        }
};

///////////////////////////////////////////////////////////////////////////////
// eventInfo DEFINED BY EVENT
//
class EventInfo : public AsnType
{
public:
  
    AsnIntType  intId;
    AsnType*    value;

    EventInfo( MemBlock* mb )
        : AsnType( mb )
        { intId = -1; value = NULL; }

    ~EventInfo()
        {}

    void SetTypeBy( const ASN::EventTypeID& id );

    AsnLen BEnc( AsnBuf& b );

    void BDec( AsnBuf& b, AsnLen &bytesDecoded );

    PDU_MEMBER_MACROS

    void Print (CTsvcLIB::LOG &os) const
    {
        if ( value )
            os << *value;
        else
            os << "VOID";
        }
};

///////////////////////////////////////////////////////////////////////////////
// PrivateData ANY (supporting Ericsson Application Link)
//
class PrivateAnyData: public AsnType
{
public:
  
    AsnOid      oid;
    bool        encodeLenAsEric;

    size_t      octetLen;
    uint8*      octs;

    PrivateAnyData( MemBlock* mb )
        : AsnType( mb )
        , oid( mb )
        { octetLen = 0; octs = NULL; encodeLenAsEric = true; }

    ~PrivateAnyData()
        {}

    void SetTypeBy( const AsnOid& id )
        { oid = id; }

    AsnLen BEnc( AsnBuf& b );

    void BDec( AsnBuf& b, AsnLen &bytesDecoded );

    PDU_MEMBER_MACROS

    void Print (CTsvcLIB::LOG &os) const;

    USTR toUSTR( void ) const;
};

//////////////////////////////////////////////////////////////////////////////
} // namespace ASN

#endif // _CSTA_any_h_included