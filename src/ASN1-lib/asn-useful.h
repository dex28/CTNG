/*
    Project: ASN1Lib

    Module: asn-useful.h

    Description: class definitions for ASN.1 module ASN-USEFUL

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB

    Wed Aug 29 14:26:27 2001
*/

#ifndef _asn_useful_h_
#define _asn_useful_h_

///////////////////////////////////////////////////////////////////////////////
// Class declarations

class ObjectDescriptor;
class NumericString;
class PrintableString;
class TeletexString;
class T61String;
class VideotexString;
class IA5String;
class GraphicString;
class VisibleString;
class ISO646String;
class GeneralString;
class UTCTime;
class GeneralizedTime;
class EXTERNALChoice;
class EXTERNAL;

///////////////////////////////////////////////////////////////////////////////
// Class definitions

/* [UNIVERSAL 7] IMPLICIT OCTET STRING*/
class ObjectDescriptor: public AsnOcts
{
public:
  ObjectDescriptor( MemBlock* mb ): AsnOcts( mb ) {}
  ObjectDescriptor( MemBlock* mb, const uint8* str ): AsnOcts( mb, str ) {}
  ObjectDescriptor( MemBlock* mb, const uint8* str, const size_t len): AsnOcts( mb, str, len ) {}
  ObjectDescriptor( MemBlock* mb, const AsnOcts &o ): AsnOcts( mb, o) {}
  ObjectDescriptor &operator = (const ObjectDescriptor &o) { ReSet (o); return *this; }
  ObjectDescriptor &operator = (const uint8* str) { ReSet (str); return *this; }
  ObjectDescriptor &operator = (const char* str) { ReSet ((uint8*)str); return *this; }
  AsnType *Clone() const;

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

};


/* [UNIVERSAL 18] IMPLICIT OCTET STRING*/
class NumericString: public AsnOcts
{
public:
  NumericString( MemBlock* mb ): AsnOcts( mb ) {}
  NumericString( MemBlock* mb, const uint8* str ): AsnOcts( mb, str ) {}
  NumericString( MemBlock* mb, const uint8* str, const size_t len): AsnOcts( mb, str, len ) {}
  NumericString( MemBlock* mb, const AsnOcts &o ): AsnOcts( mb, o) {}
  NumericString &operator = (const NumericString &o) { ReSet (o); return *this; }
  NumericString &operator = (const uint8* str) { ReSet (str); return *this; }
  NumericString &operator = (const char* str) { ReSet ((uint8*)str); return *this; }
  AsnType *Clone() const;

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

};


/* [UNIVERSAL 19] IMPLICIT OCTET STRING*/
class PrintableString: public AsnOcts
{
public:
  PrintableString( MemBlock* mb ): AsnOcts( mb ) {}
  PrintableString( MemBlock* mb, const uint8* str ): AsnOcts( mb, str ) {}
  PrintableString( MemBlock* mb, const uint8* str, const size_t len): AsnOcts( mb, str, len ) {}
  PrintableString( MemBlock* mb, const AsnOcts &o ): AsnOcts( mb, o) {}
  PrintableString &operator = (const PrintableString &o) { ReSet (o); return *this; }
  PrintableString &operator = (const uint8* str) { ReSet (str); return *this; }
  PrintableString &operator = (const char* str) { ReSet ((uint8*)str); return *this; }
  AsnType *Clone() const;

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

};


/* [UNIVERSAL 20] IMPLICIT OCTET STRING*/
class TeletexString: public AsnOcts
{
public:
  TeletexString( MemBlock* mb ): AsnOcts( mb ) {}
  TeletexString( MemBlock* mb, const uint8* str ): AsnOcts( mb, str ) {}
  TeletexString( MemBlock* mb, const uint8* str, const size_t len): AsnOcts( mb, str, len ) {}
  TeletexString( MemBlock* mb, const AsnOcts &o ): AsnOcts( mb, o) {}
  TeletexString &operator = (const TeletexString &o) { ReSet (o); return *this; }
  TeletexString &operator = (const uint8* str) { ReSet (str); return *this; }
  TeletexString &operator = (const char* str) { ReSet ((uint8*)str); return *this; }
  AsnType *Clone() const;

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

};


/* [UNIVERSAL 20] IMPLICIT OCTET STRING*/
class T61String: public AsnOcts
{
public:
  T61String( MemBlock* mb ): AsnOcts( mb ) {}
  T61String( MemBlock* mb, const uint8* str ): AsnOcts( mb, str ) {}
  T61String( MemBlock* mb, const uint8* str, const size_t len): AsnOcts( mb, str, len ) {}
  T61String( MemBlock* mb, const AsnOcts &o ): AsnOcts( mb, o) {}
  T61String &operator = (const T61String &o) { ReSet (o); return *this; }
  T61String &operator = (const uint8* str) { ReSet (str); return *this; }
  T61String &operator = (const char* str) { ReSet ((uint8*)str); return *this; }
  AsnType *Clone() const;

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

};


/* [UNIVERSAL 21] IMPLICIT OCTET STRING*/
class VideotexString: public AsnOcts
{
public:
  VideotexString( MemBlock* mb ): AsnOcts( mb ) {}
  VideotexString( MemBlock* mb, const uint8* str ): AsnOcts( mb, str ) {}
  VideotexString( MemBlock* mb, const uint8* str, const size_t len): AsnOcts( mb, str, len ) {}
  VideotexString( MemBlock* mb, const AsnOcts &o ): AsnOcts( mb, o) {}
  VideotexString &operator = (const VideotexString &o) { ReSet (o); return *this; }
  VideotexString &operator = (const uint8* str) { ReSet (str); return *this; }
  VideotexString &operator = (const char* str) { ReSet ((uint8*)str); return *this; }
  AsnType *Clone() const;

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

};


/* [UNIVERSAL 22] IMPLICIT OCTET STRING*/
class IA5String: public AsnOcts
{
public:
  IA5String( MemBlock* mb ): AsnOcts( mb ) {}
  IA5String( MemBlock* mb, const uint8* str ): AsnOcts( mb, str ) {}
  IA5String( MemBlock* mb, const uint8* str, const size_t len): AsnOcts( mb, str, len ) {}
  IA5String( MemBlock* mb, const AsnOcts &o ): AsnOcts( mb, o) {}
  IA5String &operator = (const IA5String &o) { ReSet (o); return *this; }
  IA5String &operator = (const uint8* str) { ReSet (str); return *this; }
  IA5String &operator = (const char* str) { ReSet ((uint8*)str); return *this; }
  AsnType *Clone() const;

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

};


/* [UNIVERSAL 25] IMPLICIT OCTET STRING*/
class GraphicString: public AsnOcts
{
public:
  GraphicString( MemBlock* mb ): AsnOcts( mb ) {}
  GraphicString( MemBlock* mb, const uint8* str ): AsnOcts( mb, str ) {}
  GraphicString( MemBlock* mb, const uint8* str, const size_t len): AsnOcts( mb, str, len ) {}
  GraphicString( MemBlock* mb, const AsnOcts &o ): AsnOcts( mb, o) {}
  GraphicString &operator = (const GraphicString &o) { ReSet (o); return *this; }
  GraphicString &operator = (const uint8* str) { ReSet (str); return *this; }
  GraphicString &operator = (const char* str) { ReSet ((uint8*)str); return *this; }
  AsnType *Clone() const;

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

};


/* [UNIVERSAL 26] IMPLICIT OCTET STRING*/
class VisibleString: public AsnOcts
{
public:
  VisibleString( MemBlock* mb ): AsnOcts( mb ) {}
  VisibleString( MemBlock* mb, const uint8* str ): AsnOcts( mb, str ) {}
  VisibleString( MemBlock* mb, const uint8* str, const size_t len): AsnOcts( mb, str, len ) {}
  VisibleString( MemBlock* mb, const AsnOcts &o ): AsnOcts( mb, o) {}
  VisibleString &operator = (const VisibleString &o) { ReSet (o); return *this; }
  VisibleString &operator = (const uint8* str) { ReSet (str); return *this; }
  VisibleString &operator = (const char* str) { ReSet ((uint8*)str); return *this; }
  AsnType *Clone() const;

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

};


/* [UNIVERSAL 26] IMPLICIT OCTET STRING*/
class ISO646String: public AsnOcts
{
public:
  ISO646String( MemBlock* mb ): AsnOcts( mb ) {}
  ISO646String( MemBlock* mb, const uint8* str ): AsnOcts( mb, str ) {}
  ISO646String( MemBlock* mb, const uint8* str, const size_t len): AsnOcts( mb, str, len ) {}
  ISO646String( MemBlock* mb, const AsnOcts &o ): AsnOcts( mb, o) {}
  ISO646String &operator = (const ISO646String &o) { ReSet (o); return *this; }
  ISO646String &operator = (const uint8* str) { ReSet (str); return *this; }
  ISO646String &operator = (const char* str) { ReSet ((uint8*)str); return *this; }
  AsnType *Clone() const;

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

};


/* [UNIVERSAL 27] IMPLICIT OCTET STRING*/
class GeneralString: public AsnOcts
{
public:
  GeneralString( MemBlock* mb ): AsnOcts( mb ) {}
  GeneralString( MemBlock* mb, const uint8* str ): AsnOcts( mb, str ) {}
  GeneralString( MemBlock* mb, const uint8* str, const size_t len): AsnOcts( mb, str, len ) {}
  GeneralString( MemBlock* mb, const AsnOcts &o ): AsnOcts( mb, o) {}
  GeneralString &operator = (const GeneralString &o) { ReSet (o); return *this; }
  GeneralString &operator = (const uint8* str) { ReSet (str); return *this; }
  GeneralString &operator = (const char* str) { ReSet ((uint8*)str); return *this; }
  AsnType *Clone() const;

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

};


/* [UNIVERSAL 23] IMPLICIT OCTET STRING*/
class UTCTime: public AsnOcts
{
public:
  UTCTime( MemBlock* mb ): AsnOcts( mb ) {}
  UTCTime( MemBlock* mb, const uint8* str ): AsnOcts( mb, str ) {}
  UTCTime( MemBlock* mb, const uint8* str, const size_t len): AsnOcts( mb, str, len ) {}
  UTCTime( MemBlock* mb, const AsnOcts &o ): AsnOcts( mb, o) {}
  UTCTime &operator = (const UTCTime &o) { ReSet (o); return *this; }
  UTCTime &operator = (const uint8* str) { ReSet (str); return *this; }
  UTCTime &operator = (const char* str) { ReSet ((uint8*)str); return *this; }
  AsnType *Clone() const;

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

};


/* [UNIVERSAL 24] IMPLICIT OCTET STRING*/
class GeneralizedTime: public AsnOcts
{
public:
  GeneralizedTime( MemBlock* mb ): AsnOcts( mb ) {}
  GeneralizedTime( MemBlock* mb, const uint8* str ): AsnOcts( mb, str ) {}
  GeneralizedTime( MemBlock* mb, const uint8* str, const size_t len): AsnOcts( mb, str, len ) {}
  GeneralizedTime( MemBlock* mb, const AsnOcts &o ): AsnOcts( mb, o) {}
  GeneralizedTime &operator = (const GeneralizedTime &o) { ReSet (o); return *this; }
  GeneralizedTime &operator = (const uint8* str) { ReSet (str); return *this; }
  GeneralizedTime &operator = (const char* str) { ReSet ((uint8*)str); return *this; }
  AsnType *Clone() const;

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

};


class EXTERNALChoice : public AsnType
{
public:
  enum ChoiceIdEnum
  {
     single_ASN1_typeCid = 0,
     octet_alignedCid = 1,
     arbitraryCid = 2
  };

  enum ChoiceIdEnum choiceId;

  union
  {
     AsnOcts* single_ASN1_type;
     AsnOcts* octet_aligned;
     AsnBits* arbitrary;
  };


  EXTERNALChoice( MemBlock* mb );
  EXTERNALChoice( MemBlock* mb, const EXTERNALChoice &);
  ~EXTERNALChoice();

  AsnType *Clone() const;

  EXTERNALChoice &operator = (const EXTERNALChoice &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);
  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print (CTsvcLIB::LOG &os) const;
};


class EXTERNAL : public AsnType
{
public:
  AsnOid* direct_reference;
  AsnInt* indirect_reference;
  ObjectDescriptor* data_value_descriptor;
  EXTERNALChoice* encoding;

 EXTERNAL( MemBlock* mb );
 EXTERNAL ( MemBlock* mb, const EXTERNAL & );
 ~EXTERNAL();
  AsnType *Clone() const;

  EXTERNAL &operator = (const EXTERNAL &);
  AsnLen BEncContent (AsnBuf& b);
  void BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen, AsnLen &bytesDecoded);

  AsnLen BEnc (AsnBuf& b);
  void BDec (AsnBuf& b, AsnLen &bytesDecoded);
  int BEncPdu (AsnBuf& b, AsnLen &bytesEncoded);
  int BDecPdu (AsnBuf& b, AsnLen &bytesDecoded);

  void Print (CTsvcLIB::LOG &os) const;
};


///////////////////////////////////////////////////////////////////////////////

#endif /* conditional include of asn-useful.h */
