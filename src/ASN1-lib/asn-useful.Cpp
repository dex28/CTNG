/*
    Project: ASN1Lib

    Module: asn-useful.Cpp

    Description: class member functions for ASN.1 module ASN-USEFUL

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB

    Wed Aug 29 14:26:27 2001
*/

#include "ASN1-Implementation.h"
#include "asn-useful.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class member definitions

AsnType *ObjectDescriptor::Clone() const
{
  return new(memBlock) ObjectDescriptor(memBlock);
}

AsnLen ObjectDescriptor::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, UNIV, PRIM, OD_TAG_CODE);
    return l;
}

void ObjectDescriptor::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnTag tag;
    AsnLen elmtLen1;

    if (((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, PRIM, OD_TAG_CODE))
        && (tag != MAKE_TAG_ID (UNIV, CONS, OD_TAG_CODE)))
    {
        throw "ERROR C0100: ObjectDescriptor.BDec(): Wrong tag";
    }
    elmtLen1 = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int ObjectDescriptor::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ObjectDescriptor::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

AsnType *NumericString::Clone() const
{
  return new(memBlock) NumericString(memBlock);
}

AsnLen NumericString::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, UNIV, PRIM, NUMERICSTRING_TAG_CODE);
    return l;
}

void NumericString::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnTag tag;
    AsnLen elmtLen1;

    if (((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, PRIM, NUMERICSTRING_TAG_CODE))
        && (tag != MAKE_TAG_ID (UNIV, CONS, NUMERICSTRING_TAG_CODE)))
    {
        throw "ERROR C0101: NumericString.BDec(): Wrong tag";
    }
    elmtLen1 = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int NumericString::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int NumericString::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

AsnType *PrintableString::Clone() const
{
  return new(memBlock) PrintableString(memBlock);
}

AsnLen PrintableString::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, UNIV, PRIM, PRINTABLESTRING_TAG_CODE);
    return l;
}

void PrintableString::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnTag tag;
    AsnLen elmtLen1;

    if (((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, PRIM, PRINTABLESTRING_TAG_CODE))
        && (tag != MAKE_TAG_ID (UNIV, CONS, PRINTABLESTRING_TAG_CODE)))
    {
        throw "ERROR C0102: PrintableString.BDec(): Wrong tag";
    }
    elmtLen1 = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int PrintableString::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int PrintableString::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

AsnType *TeletexString::Clone() const
{
  return new(memBlock) TeletexString(memBlock);
}

AsnLen TeletexString::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, UNIV, PRIM, TELETEXSTRING_TAG_CODE);
    return l;
}

void TeletexString::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnTag tag;
    AsnLen elmtLen1;

    if (((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, PRIM, TELETEXSTRING_TAG_CODE))
        && (tag != MAKE_TAG_ID (UNIV, CONS, TELETEXSTRING_TAG_CODE)))
    {
        throw "ERROR C0103: TeletexString.BDec(): Wrong tag";
    }
    elmtLen1 = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int TeletexString::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int TeletexString::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

AsnType *T61String::Clone() const
{
  return new(memBlock) T61String(memBlock);
}

AsnLen T61String::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, UNIV, PRIM, TELETEXSTRING_TAG_CODE);
    return l;
}

void T61String::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnTag tag;
    AsnLen elmtLen1;

    if (((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, PRIM, TELETEXSTRING_TAG_CODE))
        && (tag != MAKE_TAG_ID (UNIV, CONS, TELETEXSTRING_TAG_CODE)))
    {
        throw "ERROR C0104: T61String.BDec(): Wrong tag";
    }
    elmtLen1 = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int T61String::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int T61String::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

AsnType *VideotexString::Clone() const
{
  return new(memBlock) VideotexString(memBlock);
}

AsnLen VideotexString::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, UNIV, PRIM, VIDEOTEXSTRING_TAG_CODE);
    return l;
}

void VideotexString::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnTag tag;
    AsnLen elmtLen1;

    if (((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, PRIM, VIDEOTEXSTRING_TAG_CODE))
        && (tag != MAKE_TAG_ID (UNIV, CONS, VIDEOTEXSTRING_TAG_CODE)))
    {
        throw "ERROR C0105: VideotexString.BDec(): Wrong tag";
    }
    elmtLen1 = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int VideotexString::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int VideotexString::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

AsnType *IA5String::Clone() const
{
  return new(memBlock) IA5String(memBlock);
}

AsnLen IA5String::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, UNIV, PRIM, IA5STRING_TAG_CODE);
    return l;
}

void IA5String::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnTag tag;
    AsnLen elmtLen1;

    if (((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, PRIM, IA5STRING_TAG_CODE))
        && (tag != MAKE_TAG_ID (UNIV, CONS, IA5STRING_TAG_CODE)))
    {
        throw "ERROR C0106: IA5String.BDec(): Wrong tag";
    }
    elmtLen1 = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int IA5String::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int IA5String::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

AsnType *GraphicString::Clone() const
{
  return new(memBlock) GraphicString(memBlock);
}

AsnLen GraphicString::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, UNIV, PRIM, GRAPHICSTRING_TAG_CODE);
    return l;
}

void GraphicString::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnTag tag;
    AsnLen elmtLen1;

    if (((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, PRIM, GRAPHICSTRING_TAG_CODE))
        && (tag != MAKE_TAG_ID (UNIV, CONS, GRAPHICSTRING_TAG_CODE)))
    {
        throw "ERROR C0107: GraphicString.BDec(): Wrong tag";
    }
    elmtLen1 = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int GraphicString::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int GraphicString::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

AsnType *VisibleString::Clone() const
{
  return new(memBlock) VisibleString(memBlock);
}

AsnLen VisibleString::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, UNIV, PRIM, VISIBLESTRING_TAG_CODE);
    return l;
}

void VisibleString::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnTag tag;
    AsnLen elmtLen1;

    if (((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, PRIM, VISIBLESTRING_TAG_CODE))
        && (tag != MAKE_TAG_ID (UNIV, CONS, VISIBLESTRING_TAG_CODE)))
    {
        throw "ERROR C0108: VisibleString.BDec(): Wrong tag";
    }
    elmtLen1 = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int VisibleString::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int VisibleString::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

AsnType *ISO646String::Clone() const
{
  return new(memBlock) ISO646String(memBlock);
}

AsnLen ISO646String::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, UNIV, PRIM, VISIBLESTRING_TAG_CODE);
    return l;
}

void ISO646String::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnTag tag;
    AsnLen elmtLen1;

    if (((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, PRIM, VISIBLESTRING_TAG_CODE))
        && (tag != MAKE_TAG_ID (UNIV, CONS, VISIBLESTRING_TAG_CODE)))
    {
        throw "ERROR C0109: ISO646String.BDec(): Wrong tag";
    }
    elmtLen1 = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int ISO646String::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int ISO646String::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

AsnType *GeneralString::Clone() const
{
  return new(memBlock) GeneralString(memBlock);
}

AsnLen GeneralString::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, UNIV, PRIM, GENERALSTRING_TAG_CODE);
    return l;
}

void GeneralString::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnTag tag;
    AsnLen elmtLen1;

    if (((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, PRIM, GENERALSTRING_TAG_CODE))
        && (tag != MAKE_TAG_ID (UNIV, CONS, GENERALSTRING_TAG_CODE)))
    {
        throw "ERROR C0110: GeneralString.BDec(): Wrong tag";
    }
    elmtLen1 = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int GeneralString::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int GeneralString::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

AsnType *UTCTime::Clone() const
{
  return new(memBlock) UTCTime(memBlock);
}

AsnLen UTCTime::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, UNIV, PRIM, UTCTIME_TAG_CODE);
    return l;
}

void UTCTime::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnTag tag;
    AsnLen elmtLen1;

    if (((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, PRIM, UTCTIME_TAG_CODE))
        && (tag != MAKE_TAG_ID (UNIV, CONS, UTCTIME_TAG_CODE)))
    {
        throw "ERROR C0111: UTCTime.BDec(): Wrong tag";
    }
    elmtLen1 = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int UTCTime::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int UTCTime::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

AsnType *GeneralizedTime::Clone() const
{
  return new(memBlock) GeneralizedTime(memBlock);
}

AsnLen GeneralizedTime::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, UNIV, PRIM, GENERALIZEDTIME_TAG_CODE);
    return l;
}

void GeneralizedTime::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnTag tag;
    AsnLen elmtLen1;

    if (((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, PRIM, GENERALIZEDTIME_TAG_CODE))
        && (tag != MAKE_TAG_ID (UNIV, CONS, GENERALIZEDTIME_TAG_CODE)))
    {
        throw "ERROR C0112: GeneralizedTime.BDec(): Wrong tag";
    }
    elmtLen1 = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int GeneralizedTime::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int GeneralizedTime::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

EXTERNALChoice::EXTERNALChoice( MemBlock* mb ) : AsnType( mb )
{
  choiceId = single_ASN1_typeCid;
  single_ASN1_type = NULL; // incomplete initialization of mandatory element!
}

EXTERNALChoice::EXTERNALChoice( MemBlock* mb, const EXTERNALChoice & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined EXTERNALChoice::EXTERNALChoice (const EXTERNALChoice &)";
  abort();
}

EXTERNALChoice::~EXTERNALChoice()
{
} // end of destructor

AsnType *EXTERNALChoice::Clone() const
{
  return new(memBlock) EXTERNALChoice(memBlock);
}

EXTERNALChoice &EXTERNALChoice::operator = (const EXTERNALChoice &that)
{
  if (this != &that)
  {
    switch (choiceId = that.choiceId)
    {
      case single_ASN1_typeCid:
        single_ASN1_type = new(memBlock) AsnOcts(memBlock);
        *single_ASN1_type = *that.single_ASN1_type;
        break;
      case octet_alignedCid:
        octet_aligned = new(memBlock) AsnOcts(memBlock);
        *octet_aligned = *that.octet_aligned;
        break;
      case arbitraryCid:
        arbitrary = new(memBlock) AsnBits(memBlock);
        *arbitrary = *that.arbitrary;
        break;
    }
  }

  return *this;
}

AsnLen
EXTERNALChoice::BEncContent (AsnBuf& b)
{
  AsnLen l;
  switch (choiceId)
  {
    case single_ASN1_typeCid:
      BEncEocIfNec (b);
      l = single_ASN1_type->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, UNIV, PRIM, OCTETSTRING_TAG_CODE);
    l += BEncConsLen (b, l);

    l += BEncTag1 (b, CNTX, CONS, 0);
      break;

    case octet_alignedCid:
      l = octet_aligned->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 1);
      break;

    case arbitraryCid:
      l = arbitrary->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, CNTX, PRIM, 2);
      break;

  } // end switch
  return l;
} // EXTERNALChoice::BEncContent


void EXTERNALChoice::BDecContent (AsnBuf& b, AsnTag tag, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnLen elmtLen1;
  switch (tag)
  {
    case MAKE_TAG_ID (CNTX, CONS, 0):
      tag = BDecTag (b, bytesDecoded);
      if ((tag != MAKE_TAG_ID (UNIV, PRIM, OCTETSTRING_TAG_CODE))
          && (tag != MAKE_TAG_ID (UNIV, CONS, OCTETSTRING_TAG_CODE)))
      {
         throw "ERROR C0113: Unexpected Tag";
      }

      elmtLen1 = BDecLen (b, bytesDecoded);
      choiceId = single_ASN1_typeCid;
      single_ASN1_type = new(memBlock) AsnOcts(memBlock);
        single_ASN1_type->BDecContent (b, tag, elmtLen1, bytesDecoded);
      if (elmtLen0 == INDEFINITE_LEN)
        BDecEoc (b, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 1):
    case MAKE_TAG_ID (CNTX, CONS, 1):
      choiceId = octet_alignedCid;
      octet_aligned = new(memBlock) AsnOcts(memBlock);
        octet_aligned->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    case MAKE_TAG_ID (CNTX, PRIM, 2):
    case MAKE_TAG_ID (CNTX, CONS, 2):
      choiceId = arbitraryCid;
      arbitrary = new(memBlock) AsnBits(memBlock);
        arbitrary->BDecContent (b, tag, elmtLen0, bytesDecoded);
      break;

    default:
      throw "ERROR C0114: Unexpected tag in CHOICE";
      break;
  } // end switch
} // EXTERNALChoice::BDecContent


AsnLen EXTERNALChoice::BEnc (AsnBuf& b)
{
    AsnLen l;
    l = BEncContent (b);
    return l;
}

void EXTERNALChoice::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
    AsnLen elmtLen;
    AsnTag tag;

    /*  CHOICEs are a special case - grab identifying tag */
    /*  this allows easier handling of nested CHOICEs */
    tag = BDecTag (b, bytesDecoded);
    elmtLen = BDecLen (b, bytesDecoded);
    BDecContent (b, tag, elmtLen, bytesDecoded);
}

int EXTERNALChoice::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int EXTERNALChoice::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void EXTERNALChoice::Print (CTsvcLIB::LOG &os) const
{
  switch (choiceId)
  {
    case single_ASN1_typeCid: os << "AsnOcts*"; break;
    case octet_alignedCid: os << "AsnOcts*"; break;
    case arbitraryCid: os << "AsnBits*"; break;
  } // end of switch
  os << " CHOICE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;
  Indent (os, indentG);

  switch (choiceId)
  {
    case single_ASN1_typeCid:
      os << "single-ASN1-type : ";
      if (single_ASN1_type)
        os << *single_ASN1_type;
      else
        os << "VOID";
      break;

    case octet_alignedCid:
      os << "octet-aligned : ";
      if (octet_aligned)
        os << *octet_aligned;
      else
        os << "VOID";
      break;

    case arbitraryCid:
      os << "arbitrary : ";
      if (arbitrary)
        os << *arbitrary;
      else
        os << "VOID";
      break;

  } // end of switch

  indentG -= stdIndentG;
  os << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "}";
} // EXTERNALChoice::Print

EXTERNAL::EXTERNAL( MemBlock* mb ) : AsnType( mb )
{
  direct_reference = NULL;
  indirect_reference = NULL;
  data_value_descriptor = NULL;
  encoding = NULL; // incomplete initialization of mandatory element!
}

EXTERNAL::EXTERNAL( MemBlock* mb, const EXTERNAL & ) : AsnType( mb )
{
  throw "ERROR C0099: Use of incompletely defined EXTERNAL::EXTERNAL (const EXTERNAL &)";
  abort();
}

EXTERNAL::~EXTERNAL()
{
}

AsnType *EXTERNAL::Clone() const
{
  return new(memBlock) EXTERNAL(memBlock);
}

EXTERNAL &EXTERNAL::operator = (const EXTERNAL &that)
{
  if (this != &that)
  {
    if (that.direct_reference)
    {
      if (!direct_reference)
        direct_reference = new(memBlock) AsnOid(memBlock);
      *direct_reference = *that.direct_reference;
    }
    else
    {
      direct_reference = NULL;
    }
    if (that.indirect_reference)
    {
      if (!indirect_reference)
        indirect_reference = new(memBlock) AsnInt(memBlock);
      *indirect_reference = *that.indirect_reference;
    }
    else
    {
      indirect_reference = NULL;
    }
    if (that.data_value_descriptor)
    {
      if (!data_value_descriptor)
        data_value_descriptor = new(memBlock) ObjectDescriptor(memBlock);
      *data_value_descriptor = *that.data_value_descriptor;
    }
    else
    {
      data_value_descriptor = NULL;
    }
    if (that.encoding)
    {
      if (!encoding)
        encoding = new(memBlock) EXTERNALChoice(memBlock);
      *encoding = *that.encoding;
    }
    else
    {
      encoding = NULL;
    }
  }

  return *this;
}

AsnLen
EXTERNAL::BEncContent (AsnBuf& b)
{
  AsnLen totalLen = 0;
  AsnLen l;

    l = encoding->BEncContent (b);
    totalLen += l;

  if (NOT_NULL (data_value_descriptor))
  {
    l = data_value_descriptor->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, UNIV, PRIM, OD_TAG_CODE);
    totalLen += l;
  }

  if (NOT_NULL (indirect_reference))
  {
    l = indirect_reference->BEncContent (b);
    BEncDefLenTo127 (b, l);
    l++;

    l += BEncTag1 (b, UNIV, PRIM, INTEGER_TAG_CODE);
    totalLen += l;
  }

  if (NOT_NULL (direct_reference))
  {
    l = direct_reference->BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, UNIV, PRIM, OID_TAG_CODE);
    totalLen += l;
  }

  return totalLen;
} // EXTERNAL::BEncContent


void EXTERNAL::BDecContent (AsnBuf& b, AsnTag /*tag0*/, AsnLen elmtLen0, AsnLen &bytesDecoded)
{
  AsnTag tag1;
  AsnLen seqBytesDecoded = 0;
  AsnLen elmtLen1;
  tag1 = BDecTag (b, seqBytesDecoded);

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, OID_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    direct_reference = new(memBlock) AsnOid(memBlock);
    direct_reference->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, INTEGER_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    indirect_reference = new(memBlock) AsnInt(memBlock);
    indirect_reference->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }

  if ((tag1 == MAKE_TAG_ID (UNIV, PRIM, OD_TAG_CODE))
    || (tag1 == MAKE_TAG_ID (UNIV, CONS, OD_TAG_CODE)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    data_value_descriptor = new(memBlock) ObjectDescriptor(memBlock);
    data_value_descriptor->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
    tag1 = BDecTag (b, seqBytesDecoded);
  }

  if ((tag1 == MAKE_TAG_ID (CNTX, CONS, 0))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 1))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 1))
    || (tag1 == MAKE_TAG_ID (CNTX, PRIM, 2))
    || (tag1 == MAKE_TAG_ID (CNTX, CONS, 2)) )
  {
    elmtLen1 = BDecLen (b, seqBytesDecoded);
    encoding = new(memBlock) EXTERNALChoice(memBlock);
    encoding->BDecContent (b, tag1, elmtLen1, seqBytesDecoded);
  }
  else
  {
    throw "ERROR C0115: SEQUENCE is missing non-optional elmt.";
  }

  bytesDecoded += seqBytesDecoded;
  if (elmtLen0 == INDEFINITE_LEN)
  {
    BDecEoc (b, bytesDecoded);
    return;
  }
  else if (seqBytesDecoded != elmtLen0)
  {
    throw "ERROR C0116: Length discrepancy on sequence.";
  }
  else
    return;
} // EXTERNAL::BDecContent

AsnLen EXTERNAL::BEnc (AsnBuf& b)
{
  AsnLen l;
  l = BEncContent (b);
  l += BEncConsLen (b, l);
  l += BEncTag1 (b, UNIV, CONS, EXTERNAL_TAG_CODE);
  return l;
}

void EXTERNAL::BDec (AsnBuf& b, AsnLen &bytesDecoded)
{
  AsnTag tag;
  AsnLen elmtLen1;

  if ((tag = BDecTag (b, bytesDecoded)) != MAKE_TAG_ID (UNIV, CONS, EXTERNAL_TAG_CODE))
  {
    throw "ERROR C134862360: Dec.B„,­û(): Wrong tag";
  }
  elmtLen1 = BDecLen (b, bytesDecoded);
  BDecContent (b, tag, elmtLen1, bytesDecoded);
}

int EXTERNAL::BEncPdu (AsnBuf& b, AsnLen &bytesEncoded)
{
    bytesEncoded = BEnc (b);
    return !b.WriteError();
}

int EXTERNAL::BDecPdu (AsnBuf& b, AsnLen &bytesDecoded)
{
    bytesDecoded = 0;
    try
    {
         BDec (b, bytesDecoded);
         return !b.ReadError();
    }
    catch( const char* err )
    {
         PRINTERR( "ASN.1 Error: " << err );
         return false;
    }
}

void EXTERNAL::Print (CTsvcLIB::LOG &os) const
{
  os << "EXTERNAL SEQUENCE" << CTsvcLIB::eline;
  Indent (os, indentG);
  os << "{" << CTsvcLIB::eline;
  indentG += stdIndentG;

  Indent (os, indentG);
  os << "direct-reference : ";
  if (NOT_NULL (direct_reference))
    os << *direct_reference;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "indirect-reference : ";
  if (NOT_NULL (indirect_reference))
    os << *indirect_reference;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "data-value-descriptor : ";
  if (NOT_NULL (data_value_descriptor))
    os << *data_value_descriptor;
  else
    os << "VOID";
  os << "," << CTsvcLIB::eline;

  Indent (os, indentG);
  os << "encoding : ";
  if (NOT_NULL (encoding))
    os << *encoding;
  else
    os << "VOID";
  os << CTsvcLIB::eline;

  indentG -= stdIndentG;
  Indent (os, indentG);
  os << "}";
} // EXTERNAL::Print


