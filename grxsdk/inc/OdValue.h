/////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2021, Open Design Alliance (the "Alliance"). 
// All rights reserved. 
// 
// This software and its documentation and related materials are owned by 
// the Alliance. The software may only be incorporated into application 
// programs owned by members of the Alliance, subject to a signed 
// Membership Agreement and Supplemental Software License Agreement with the
// Alliance. The structure and organization of this software are the valuable  
// trade secrets of the Alliance and its suppliers. The software is also 
// protected by copyright law and international treaty provisions. Application  
// programs incorporating this software must include the following statement 
// with their copyright notices:
//   
//   This application incorporates Open Design Alliance software pursuant to a license 
//   agreement with Open Design Alliance.
//   Open Design Alliance Copyright (C) 2002-2021 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////



#ifndef _ODVALUE_INCLUDED_
#define _ODVALUE_INCLUDED_

#include "TD_PackPush.h"
#include "StaticRxObject.h" 
#include "OdTimeStamp.h"
#include "DbEvalVariant.h"
#include "OdArray.h"

typedef struct tagVARIANT VARIANT;

class OdValueImpl;
class OdValue;
typedef OdSmartPtr<OdValue> OdValuePtr;
struct resbuf;


/** \details
    <group Other_Classes>
*/
class DBENT_EXPORT OdValue : public OdStaticRxObject<OdRxObject>
{
public:
  ODRX_HEAP_OPERATORS();

  enum DataType
  {
    kUnknown            = 0x00,
    kLong               = 0x01,
    kDouble             = 0x02,
    kString             = 0x04,
    kDate               = 0x08,
    kPoint              = 0x10,
    k3dPoint            = 0x20,
    kObjectId           = 0x40,
    kBuffer             = 0x80,
    kResbuf             = 0x100,
    kGeneral            = 0x200,
    kColor              = 0x400
  };

  enum UnitType
  {
    kUnitless           = 0x00,
    kDistance           = 0x01,
    kAngle              = 0x02,
    kArea               = 0x04,
    kVolume             = 0x08,
    kCurrency           = 0x10,
    kPercentage         = 0x20,
    kAngleNotTransformed = (0x1 << 16)
  };

  enum ParseOption
  {
    kParseOptionNone        = 0x00,
    kSetDefaultFormat       = 0x01,
    kPreserveMtextFormat    = 0x02,
    kConvertTextToValue     = 0x04,
    kChangeDataType         = 0x08,
    kParseTextForFieldCode  = 0x10
  };

  enum FormatOption
  {
    kFormatOptionNone       = 0x00,
    kForEditing             = 0x01,
    kForExpression          = 0x02,
    kUseMaximumPrecision    = 0x04,
    kIgnoreMtextFormat      = 0x08
  };
public:
  static bool isValidDataType(const VARIANT& var);

public:
  ODRX_DECLARE_MEMBERS(OdValue);

  OdValue(void);
  ~OdValue(void);

  OdValue(const OdValue& value);
  OdValue(OdValue&& value);
  OdValue(const OdString& value);
  OdValue(OdInt32 value);
  OdValue(double value);
  OdValue(const OdInt64& date);
  OdValue(double x, double y);
  OdValue(double x, double y, double z);
  OdValue(const OdGePoint2d& pnt);
  OdValue(const OdGePoint3d& pnt);
  OdValue(const OdDbObjectId& objectId);
  OdValue(const OdResBufPtr& resBuf);
  OdValue(const resbuf& rb);
  OdValue(const OdTimeStamp& time);
  // OdValue(const OdRxVariantValue& var);

  OdValue(const void* buffer, OdInt32 bufferSize);

  OdValue(OdValue::DataType nDataType);

  OdValue(const SYSTEMTIME& date);

  OdValue(const std::tm& date);

  OdValue(const OdDbEvalVariant& evalVar);

  OdValue(const VARIANT& var);

  OdValue(const OdCmColor& var);

  OdValue(const OdChar * pszValue);

  bool  resetValue(void);
  /** \details
  Sets the datatype of this FieldValue object to kUnknown.
  \remarks
  This function always returns true.
  */
  bool reset();
  /** \details
  Returns the datatype of this FieldValue object.
  \remarks
  dataType() returns one of the following:

  <table>
  Name              Value
  kUnknown          0x00
  kLong             0x01
  kDouble           0x02
  kString           0x04
  kDate             0x08
  kPoint            0x10
  k3dPoint          0x20
  kObjectId         0x40
  kBuffer           0x80
  kResbuf           0x100
  </table>
  */
  OdValue::DataType dataType () const;
  /** \details
  Returns true if and only if the datatype of this FieldValue is not kUnknown.
  */
  bool isValid () const;

  /** \details
  Returns this object as the specified type.

  \remarks
  OdInt64 is used for date values.
  */
  operator const OdChar * (void) const;
  operator OdString() const;
  operator OdInt32() const;
  operator double() const;
  operator OdInt64() const;
  operator OdDbObjectId() const;  
  operator OdGePoint2d (void) const;
  operator OdGePoint3d (void) const;

  OdValue& operator=(const OdChar * value);
  OdValue& operator=(const OdValue& value);
  OdValue& operator=(const OdString& value);
  OdValue& operator=(OdInt32 value);
  OdValue& operator=(double value);
  OdValue& operator=(OdInt64 date);
  OdValue& operator=(const OdDbObjectId& objectId);
  OdValue& operator=(const OdGePoint2d& pt);
  OdValue& operator=(const OdGePoint3d& pt);
  OdValue& operator=(const OdResBufPtr& resBuf);
  OdValue& operator=(const resbuf& rb);

  bool  operator==(const OdValue& val) const;
  bool  operator!=(const OdValue& val) const;

  // OdValue& operator=    (const OdRxVariantValue& var);

  // bool  get                    (const OdChar*& pszValue) const;

  /** \details
      Returns the value of this FieldValue object.
      \param value [out]  Receives the value.

      \returns
      Returns true if and only if successful.
  */
  bool get(OdString& value) const;
  /** \details
      Returns the value of this FieldValue object.
      \param value [out]  Receives the value.

      \returns
      Returns true if and only if successful.
  */
  bool get(OdInt32& value) const;
  /** \details
      Returns the value of this FieldValue object.
      \param value [out]  Receives the value.

      \returns
      Returns true if and only if successful.
  */
  bool get(double& value) const;
  /** \details
      Returns the value of this FieldValue object.

      \param date [out]  Receives the date value

      \returns
      Returns true if and only if successful.
  */
  bool get(OdInt64& date) const;
  /** \details
      Returns the value of this FieldValue object.

      \param x [out]  Receives the X-coordinate of the point.
      \param y [out]  Receives the Y-coordinate of the point.

      \returns
      Returns true if and only if successful.
  */
  bool get(double& x, double& y) const;
  /** \details
      Returns the value of this FieldValue object.

      \param x [out]  Receives the X-coordinate of the point.
      \param y [out]  Receives the Y-coordinate of the point.
      \param z [out]  Receives the Z-coordinate of the point.

      \returns
      Returns true if and only if successful.
  */
  bool get(double& x, double& y, double& z) const;
  /** \details
      Returns the value of this FieldValue object.

      \param objectId [in]  Object ID.
      
	  \returns
      Returns true if and only if successful.
  */

  bool get(OdGePoint2d& pt) const;
  bool get(OdGePoint3d& pt) const;

  bool get(OdDbObjectId& objectId) const;
  /** \details
      Returns the value of this FieldValue object.

      \param resBuf [out]  Receives the  ResBuf list.

      \returns
      Returns true if and only if successful.
  */
  bool get(OdResBufPtr& resBuf) const;
  bool get(resbuf** pRb) const;

  // bool get(OdRxVariantValue& var) const;

  /** \details
      Returns the value of this FieldValue object.
      
	  \param pBuf [out]  Receives a pointer to the buffer.
      \param bufferSize [out]  Receives the buffer size.
      
	  \returns
      Returns true if and only if successful.
  */
  bool get(void*& pBuf, OdInt32& bufferSize) const;

  bool get(const OdChar *& pszValue) const;
  bool get(OdChar *& pszValue) const;

  /** \details
    Returns the value of this FieldValue object.

    \param time [out]  Receives the time value.

    \returns
      Returns true if and only if successful.
  */
  bool get(OdTimeStamp& time) const;

  bool get(std::tm& date) const;
  bool get(SYSTEMTIME& date) const;
  bool get(OdDbEvalVariant& evalVar) const;
  bool get(OdCmColor& clr) const;
  bool get(VARIANT& var) const;
  bool get(void*& pBuf, uint32_t& dwBufSize) const;

  bool set(OdValue::DataType nDataType, const OdChar* pszValue);

  bool  set(const OdChar* value);
  /** \details
      Sets the value for this FieldValue object.
	  
      \param value [in]  Value.
      
	  \returns
      Returns true if and only if successful.
  */
  bool set(const OdValue& value);
  /** \details
      Sets the value for this FieldValue object.
      
	  \param value [in]  Value.

      \returns
      Returns true if and only if successful.
  */
  bool set(const OdString& value);
  /** \details
      Sets the value for this FieldValue object.
      
	  \param value [in]  Value.
      
	  \returns
      Returns true if and only if successful.
  */
  bool set(OdInt32 value);
  /** \details
      Sets the value for this FieldValue object.
      
	  \param value [in]  Value.
      
	  \returns
      Returns true if and only if successful.
  */
  bool set(double value);
  /** \details
      Sets the value for this FieldValue object.

      \param date [in]  Date value

      \returns
      Returns true if and only if successful.
  */
  bool set(const OdInt64& date);
  /** \details
      Sets the value for this FieldValue object.

      \param x [in]  X-coordinate of the point.
      \param y [in]  Y-coordinate of the point.

      \returns
      Returns true if and only if successful.
  */
  bool set(double x, double y);
  /** \details
      Sets the value for this FieldValue object.

      \param x [in]  X-coordinate of the point.
      \param y [in]  Y-coordinate of the point.
      \param z [in]  Z-coordinate of the point.

      \returns
      Returns true if and only if successful.
  */
  bool set(double x, double y, double z);
  /** \details
      Sets the value for this FieldValue object.

      \param objectId [in]  Object ID.
	  
      \returns
      Returns true if and only if successful.
  */

  bool set(const OdGePoint2d& pt);
  bool set(const OdGePoint3d& pt);

  bool set(const OdDbObjectId& objectId);
  /** \details
      Sets the value for this FieldValue object.

      \param resBuf [in]  ResBuf list.

      \returns
      Returns true if and only if successful.
  */
  bool set(const OdResBufPtr& resBuf);
  bool set(const resbuf& rb);

  // bool  set                    (const OdRxVariantValue& var);

  /** \details
      Sets the value for this FieldValue object.

      \param buffer [in]  Buffer.
      \param bufferSize [in]  Buffer size.

      \returns
      Returns true if and only if successful.
  */
  bool set(const void* buffer, OdInt32 bufferSize);

  /** \details
      Returns the value of this FieldValue object.

      \param time [in]  The time value.

      \returns
      Returns true if and only if successful.
  */
  bool set(const OdTimeStamp& time);

  bool  parse(const OdChar* pszText,
    OdValue::DataType nDataType,
    OdValue::UnitType nUnitType,
    const OdChar* pszFormat,
    OdValue::ParseOption nOption,
    const OdDbObjectId* pTextStyleId);

//     bool  reset                   (void);
  /** \details
      Sets the datatype of this FieldValue object to kUnknown.
      
	  \remarks
      This function always returns true.
  */
  bool  reset  (OdValue::DataType nDataType);
//     bool  resetValue              (void);

  OdValue::UnitType unitType (void) const;
  bool  setUnitType (OdValue::UnitType nUnitType);
  OdString   getFormat (void) const;
  bool  setFormat (const OdString& pszFormat);

//     bool  parse                   (const OdString& pszText, 
//                                             OdValue::DataType nDataType, 
//                                             OdValue::UnitType nUnitType, 
//                                             const ACHAR* pszFormat, 
//                                             OdValue::ParseOption nOption, 
//                                             const AcDbObjectId* pTextStyleId);
// 

  OdString format(const OdChar* pszFormat) const;
  OdString format(OdDbDatabase* pDb = 0) const;
  OdString format(OdValue::FormatOption nOption, OdDbDatabase* pDb = 0);
  OdString format(const OdString& pszFormat, OdValue::FormatOption nOption, OdDbDatabase* pDb = 0);
  bool format(const OdString& pszFormat, OdString& pszValue, OdDbDatabase* pDb = 0) const;
  bool format(const OdChar* pszFormat, OdChar*& pszValue) const;

  bool  convertTo               (OdValue::DataType nDataType, 
                                          OdValue::UnitType nUnitType);
  bool  convertTo               (OdValue::DataType nDataType, 
                                          OdValue::UnitType nUnitType, 
                                          bool bResetIfIncompatible);

  virtual OdResult dwgInFields (
    OdDbDwgFiler* pFiler);
  virtual OdResult dwgOutFields(
    OdDbDwgFiler* pFiler) const;

  virtual OdResult dxfInFields (
    OdDbDxfFiler* pFiler);
  virtual OdResult dxfOutFields(
    OdDbDxfFiler* pFiler) const;

protected:
  OdValue(OdValueImpl* pValImpl);

  friend class OdDbSystemInternals;
  OdValueImpl* m_pImpl;
};

typedef OdArray<OdValue, OdObjectsAllocator<OdValue> > OdValueArray;

#include "TD_PackPop.h"

#endif // _ODVALUE_INCLUDED_
