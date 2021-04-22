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

#ifndef OdDbEvalVariant_INCLUDED_
#define OdDbEvalVariant_INCLUDED_ /*!DOM*/

#include "DbConstraintsExports.h"
#include "ResBuf.h"
#include "DbFiler.h"

#include "TD_PackPush.h"
#include "OdDb.h"

class OdDbEvalVariant;
class OdRxValue;
class OdRxValueType;

typedef OdSmartPtr<OdDbEvalVariant> OdDbEvalVariantPtr;

/** \details
  This class represents a wrapper for a resbuf structure.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBENT_EXPORT OdDbEvalVariant : public OdResBuf
{
public:
  ODRX_DECLARE_MEMBERS(OdDbEvalVariant );

  /** \details
    Constructor creates an instance of this class.
  */
  OdDbEvalVariant();

  /** \details
    Destructor destroys an instance of this class.
  */
  ~OdDbEvalVariant();

  /** \details
    Initializes the content of this variable.
  */
  static OdDbEvalVariantPtr init(const OdDbEvalVariant& other); 
  
  /** \details
    Initializes the content of this variable.
  */
  static OdDbEvalVariantPtr init(const OdDbEvalVariant* pOther);
  
  /** \details
    Initializes the content of this variable.
  */
  static OdDbEvalVariantPtr init(double       dVal);
  
  /** \details
    Initializes the content of this variable.
  */
  static OdDbEvalVariantPtr init(short        iVal);
//static OdDbEvalVariantPtr init(const ACHAR*  szVal);
  
  /** \details
    Initializes the content of this variable.
  */
  static OdDbEvalVariantPtr init(int         lVal);
  
  /** \details
    Initializes the content of this variable.
  */
  static OdDbEvalVariantPtr init(const OdDbObjectId& id);
  
  /** \details
    Initializes the content of this variable.
  */
  static OdDbEvalVariantPtr init(const OdGePoint2d&  pt);
  
  /** \details
    Initializes the content of this variable.
  */
  static OdDbEvalVariantPtr init(const OdGePoint3d&  pt);
  
  /** \details
    Initializes the content of this variable.
  */
  static OdDbEvalVariantPtr init(const OdResBuf& rb);
  
  /** \details
    Initializes the content of this variable.
  */
  static OdDbEvalVariantPtr init(const OdString& str);

  OdDbEvalVariant(const OdResBuf& rb)
  {
	  *this = rb;
  }
  OdDbEvalVariant(double      dVal)
  {
	  *this = dVal;
  }
  OdDbEvalVariant(short       iVal)
  {
	  *this = iVal;
  }
  OdDbEvalVariant(int        lVal)
  {
	  *this = lVal;
  }
  OdDbEvalVariant(const OdDbEvalVariant& other)
  {
	  *this = other;
  }

  OdDbEvalVariant(const OdDbEvalVariant* pOther);

  OdDbEvalVariant(const OdDbObjectId& id)
  {
	  *this = id;
  }
  OdDbEvalVariant(const OdGePoint2d&  pt)
  {
	  *this = pt;
  }
  OdDbEvalVariant(const OdGePoint3d&  pt)
  {
	  *this = pt;
  }
  OdDbEvalVariant(const resbuf& rb);

  OdDbEvalVariant(const OdChar* szVal)
  {
	  *this = szVal;
  }

  OdDbEvalVariant& operator=(const OdResBuf& rb);
  OdDbEvalVariant& operator=(double      dVal);
  OdDbEvalVariant& operator=(short       iVal);
  OdDbEvalVariant& operator=(int        lVal);
  OdDbEvalVariant& operator=(const OdChar* szVal);
  OdDbEvalVariant& operator=(const OdDbEvalVariant& other);
  OdDbEvalVariant& operator=(const OdDbObjectId& id);
  OdDbEvalVariant& operator=(const OdGePoint2d&  pt);
  OdDbEvalVariant& operator=(const OdGePoint3d&  pt);

  /** \details
    Clears the content of this variable and frees any allocated memory.
  */
  void clear();

  /** \details
    Copies the content of the variable from another rx-object.
  */
  OdResult copyFrom(const OdRxObject* pOther);//eWrongObjectType 

  /** \details
    Checks whether content of this variable less than content of a given variable.
  */
  bool operator <  ( const OdDbEvalVariant& val ) const;

  /** \details
    Checks whether content of this variable more than content of a given variable.
  */
  bool operator >  ( const OdDbEvalVariant& val ) const;

  /** \details
    Checks whether content of this variable equal to or less than content of a given variable.
  */
  bool operator <= ( const OdDbEvalVariant& val ) const;

  /** \details
    Checks whether content of this variable equal to or more than content of a given variable.
  */
  bool operator >= ( const OdDbEvalVariant& val ) const;

  /** \details
    Checks whether content of this variable is equal to the content of a given variable.
  */
  bool operator == ( const OdDbEvalVariant& val ) const;

  /** \details
    Checks whether content of this variable is not equal to the content of a given variable.
  */
  bool operator != ( const OdDbEvalVariant& val ) const;

  /** \details
    Reads the .dwg file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  OdResult dwgInFields(OdDbDwgFiler* pFiler);

  /** \details
    Writes the .dwg file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  OdResult dwgOutFields(OdDbDwgFiler* pFiler) const;

  /** \details
    Reads the .dxf file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  OdResult dxfInFields(OdDbDxfFiler* pFiler);

  /** \details
    Writes the .dxf file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  OdResult dxfOutFields(OdDbDxfFiler* pFiler) const;

  /** \details
    Returns the data type of this variable.
  */
  OdDb::DwgDataType getType() const;

  /** \details
    Sets the content of this variable using a given value.
  */
  OdResult setValue(int /*AcDb::DxfCode*/ groupcode, const double value);
  
  /** \details
    Sets the content of this variable using a given value.
  */
  OdResult setValue(int /*AcDb::DxfCode*/ groupcode, const short value);
  
  /** \details
    Sets the content of this variable using a given value.
  */
  OdResult setValue(int /*AcDb::DxfCode*/ groupcode, const int value);
  
  /** \details
    Sets the content of this variable using a given value.
  */
  OdResult setValue(int /*AcDb::DxfCode*/ groupcode, const OdString& value);
  
  /** \details
    Sets the content of this variable using a given value.
  */
  OdResult setValue(int /*AcDb::DxfCode*/ groupcode, const OdDbObjectId value);
  
  /** \details
    Sets the content of this variable using a given value.
  */
  OdResult setValue(int /*AcDb::DxfCode*/ groupcode, const OdGePoint3d& value);
  
  /** \details
    Sets the content of this variable using a given value.
  */
  OdResult setValue(int /*AcDb::DxfCode*/ groupcode, const OdGePoint2d& value);

  /** \details
    Gets the content of this variable.
  */
  OdResult getValue(double& value) const;
  
  /** \details
    Gets the content of this variable.
  */
  OdResult getValue(short& value) const;

  OdResult getValue(OdInt32& value) const;
  /** \details
    Gets the content of this variable.
  */
  OdResult getValue(int& value) const;
  
  /** \details
    Gets the content of this variable.
  */
  OdResult getValue(OdString& value) const;
  
  /** \details
    Gets the content of this variable.
  */
  OdResult getValue(OdDbObjectId& value, OdDbDatabase *pDb = NULL) const;
  
  /** \details
    Gets the content of this variable.
  */
  OdResult getValue(OdGePoint3d& value) const;
  
  /** \details
    Gets the content of this variable.
  */
  OdResult getValue(OdGePoint2d& value) const;

  OdResult toOdRxValue(const OdRxValueType& type, OdRxValue& value) const;
  OdResult fromOdRxValue(const OdRxValue& value);
  /** \details
    Gets the value of this variable transformed to 'int'.
  */
  int getAsInt() const;

  /** \details
    Gets the value of this variable transformed to 'double'.
  */
  double getAsDouble() const;

protected:
  void init();

protected:

  int m_groupCode;
  /*!DOM*/
  OdDb::DwgDataType m_type;

};

typedef OdArray<OdDbEvalVariant> OdDbEvalVariantArray;

class DBENT_EXPORT GcDbEvalVariant : public resbuf, public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(GcDbEvalVariant);

  GcDbEvalVariant();
  GcDbEvalVariant(const GcDbEvalVariant& other);
  GcDbEvalVariant(const GcDbEvalVariant* pOther);

  GcDbEvalVariant(const OdDbEvalVariant& other);
  GcDbEvalVariant(const OdDbEvalVariant* pOther);

  ~GcDbEvalVariant();

  GcDbEvalVariant(double dVal);
  GcDbEvalVariant(short iVal);
  GcDbEvalVariant(const OdChar* szVal);
  GcDbEvalVariant(OdInt32 lVal);
  GcDbEvalVariant(const OdDbObjectId& id);
  GcDbEvalVariant(const OdGePoint2d& pt);
  GcDbEvalVariant(const OdGePoint3d& pt);
  GcDbEvalVariant(const resbuf& rb);

  GcDbEvalVariant& operator=(const resbuf& rb);
  GcDbEvalVariant& operator=(double dVal);
  GcDbEvalVariant& operator=(short iVal);
  GcDbEvalVariant& operator=(OdInt32 lVal);
  GcDbEvalVariant& operator=(const OdChar* szVal);
  GcDbEvalVariant& operator=(const GcDbEvalVariant& other);
  GcDbEvalVariant& operator=(const OdDbObjectId& id);
  GcDbEvalVariant& operator=(const OdGePoint2d&  pt);
  GcDbEvalVariant& operator=(const OdGePoint3d&  pt);

  void clear();

  virtual OdResult copyFrom(const OdRxObject* pOther);

  bool operator < (const GcDbEvalVariant& val) const;
  bool operator > (const GcDbEvalVariant& val) const;
  bool operator <= (const GcDbEvalVariant& val) const;
  bool operator >= (const GcDbEvalVariant& val) const;

  bool operator == (const GcDbEvalVariant& val) const;
  bool operator != (const GcDbEvalVariant& val) const;
  
  OdResult dwgOutFields(OdDbDwgFiler* pFiler) const;
  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  OdResult dxfOutFields(OdDbDxfFiler* pFiler) const;
  OdResult dxfInFields(OdDbDxfFiler* pFiler);

  OdDb::DwgDataType getType() const;

  OdResult setValue(OdDb::DxfCode groupcode, const double value);
  OdResult setValue(OdDb::DxfCode groupcode, const short value);
  OdResult setValue(OdDb::DxfCode groupcode, const OdInt32 value);
  OdResult setValue(OdDb::DxfCode groupcode, const OdString& value);
  OdResult setValue(OdDb::DxfCode groupcode, const OdDbObjectId value);
  OdResult setValue(OdDb::DxfCode groupcode, const OdGePoint3d& value);
  OdResult setValue(OdDb::DxfCode groupcode, const OdGePoint2d& value);

  OdResult getValue(double& value) const;
  OdResult getValue(short& value) const;
  OdResult getValue(OdInt32& value) const;
  OdResult getValue(OdString& value) const;
  OdResult getValue(OdDbObjectId& value, OdDbDatabase *pDb = NULL) const;
  OdResult getValue(OdGePoint3d& value) const;
  OdResult getValue(OdGePoint2d& value) const;

  //OdResult toOdRxValue(const OdRxValueType& type, OdRxValue& value) const;
  //OdResult fromOdRxValue(const OdRxValue& value);

  operator OdDbEvalVariant() const;

  GcDbEvalVariant& operator = (const OdDbEvalVariant& value);

protected:
  void init();
};
#include "TD_PackPop.h"

#endif
