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

#ifndef FILER_INCLUDED
#define FILER_INCLUDED

#include <float.h>
#include "RxObject.h"
#include "OdStreamBuf.h"
#include "DbObjectId.h"
#include "gdsdef.h"   //"TdxDefs.h"

class OdString;
class OdGeScale3d;
class OdBinaryData;
class OdDbFilerController;
class OdDbDatabase;
class OdResBuf;
typedef OdSmartPtr<OdResBuf> OdResBufPtr;
class OdDbObjectId;
class OdGePoint2d;
class OdGePoint3d;
class OdGeVector2d;
class OdGeVector3d;
class OdDbAuditInfo;

#include "TD_PackPush.h"

/** \details
    This class is the abstract base class for classes that are used for file I/O operations
    utilizing the .dwg and .dxf file formats.
    
    Corresponding C++ library: TD_Db
    
    <group OdDb_Classes>
*/
class TOOLKIT_EXPORT OdDbFiler : public OdRxObject
{
public:
  OdDbFiler() {}

  ODRX_DECLARE_MEMBERS(OdDbFiler);

  /** \details
    Returns the current status of this Filer object.    

    \remarks
    The default implementation of this function does nothing but
    throw an exception.
  */
  virtual OdResult filerStatus() const;

  /** \details
    Resets the current status of this Filer object to eOk.    
    \remarks
    The default implementation of this function does nothing but
    throw an exception.
  */
  virtual void resetFilerStatus();

  /** \details
    Returns the type of this Filer object.
  */
  virtual OdDb::FilerType filerType() const;

  /** \details
    Returns the database with which this Filer object is associated.  
  */
  virtual OdDbDatabase* database() const;

  /** \details
    Returns the version of this the file which this Filer object is associated.
    
    \remarks
    The maintenance release version is returned if and only if pMaintReleaseVer != 0. 

    \param pMaintReleaseVer [in]  Pointer to the MaintReleaseVer to receive the maintenance release version.
  */
  virtual OdDb::DwgVersion dwgVersion(
    OdDb::MaintReleaseVer* pMaintReleaseVer = 0) const;

  virtual OdResult dwgVersion(OdDb::DwgVersion &, OdDb::MaintReleaseVer &) const;


  /** \details
    Returns the AuditInfo with which this Filer object is associated.  
  */
  OdDbAuditInfo * getAuditInfo() const;

  /** \details
    Sets the FilerController with which this Filer object is associated.
    
    \param pFilerController [in]  Pointer to the FilerController.
  */
  virtual void setController(
    OdDbFilerController * pFilerController);

  /** \details
    Returns the FilerController with which this Filer object is associated.
  */
  ODRX_SEALED_VIRTUAL OdDbFilerController* controller(ODSYSDEF) const ODRX_SEALED;

  virtual OdDbFilerController& controller() const;

  virtual OdResult extendedDwgMaintenanceReleaseVersion(
    OdDb::MaintReleaseVer& maintVer
  ) const;
};

///////////////////////////////////////////////////////////////////////
/** \details
  <group Other_Classes>

  This class defines a function that returns the data type using 
  the specified group code (DXF code). 

  \sa
  <link db_rb_verify, Determining the Data Type by Group Code>  
*/
class TOOLKIT_EXPORT OdDxfCode
{
public:
  /** \details
    Defines codes for data types.
  */
  typedef enum
  {
    Unknown         = 0,
    Name            = 1,
    String          = 2,
    Bool            = 3,
    Integer8        = 4,
    Integer16       = 5,
    Integer32       = 6,
    Double          = 7,
    Angle           = 8,
    Point           = 9,
    BinaryChunk     = 10,
    LayerName       = 11,
    Handle          = 12,
    ObjectId        = 13,
    SoftPointerId   = 14,
    HardPointerId   = 15,
    SoftOwnershipId = 16,
    HardOwnershipId = 17,
    Integer64       = 18
  } Type;

  /** \details
    Returns the data type for the specified group code (DXF code).

    \sa
    <link db_rb_verify, Determining the Data Type by Group Code>

    \sa
    <link db_rb_type, Getting and Setting Tagged Data>
  */
  static Type _getType( int code );
};

/** \details
    This class is the abstract base class for classes that are used for file I/O operations
    with DXF formats.
    
    Corresponding C++ library: TD_Db
    
    <group OdDb_Classes>
*/
class TOOLKIT_EXPORT OdDbDxfFiler : public OdDbFiler
{
public:
  ODRX_DECLARE_MEMBERS(OdDbDxfFiler);
  OdDbDxfFiler() {}

  /** \details
    Moves the I/O pointer to the specified location in this Filer object.
    
    \param offset [in]  Number of bytes.
    \param seekType [in]  Seek type.
    
    \remarks
    seekType must be one of the following:
    
    <table>
    Name                    Value       Description.
    OdDb::kSeekFromStart    SEEK_SET    Start of file.
    OdDb::kSeekFromCurrent  SEEK_CUR    Current position of I/O pointer.
    OdDb::kSeekFromEnd      SEEK_END    End of file.
    </table>

    \remarks
    The default implementation of this function does nothing but
    throw an exception.
  */
  virtual OdResult seek(
    OdInt64 offset, 
    int seekType);
  
  /** \details
    Returns the current I/O pointer position of this Filer object.
    
    \remarks
    The default implementation of this function does nothing but
    throw an exception.
  */
  virtual OdInt64 tell() const;

  /** \details
    Returns the number of decimal places for DxfOut filing with this Filer object.
    
    \remarks
    Returns kDfltPrec for DxfIn filing.
    
    \remarks
    The default implementation of this function does nothing but
    throw an exception.
  */
  virtual int precision() const;

  virtual int rewindFiler();


  /** \details
    Sets the number of decimal places DxfOut filing with this Filer object.
    
    \param precision [in]  Decimal places.
    
    \remarks
    The default implementation of this function does nothing but
    throw an exception.
  */
  virtual void setPrecision(
    int decimalDigits);

  virtual double thickness() const;

  /** \details
    Number of decimal digits written to ASCII DXF files.
  */
  enum 
  { 
    kDfltPrec = -1, 
    kMaxPrec = DBL_DIG + 1 
  };

  /** \details
    Indicates the start of xdata in this Filer object.
  */
  
  
  //virtual OdResult readResBuf(resbuf*);
  

  //OdResult readItem(resbuf* pItem);
  OdResult writeItem(const resbuf & pItem);
  virtual OdResult writeOdDbHandle(OdDb::DxfCode groupCode, const OdDbHandle& value);
  virtual OdResult writeBChunk(OdDb::DxfCode groupCode, const gds_binary & value);
  virtual OdResult writeBool(OdDb::DxfCode groupCode, bool value);
  virtual OdResult writeBoolean(OdDb::DxfCode groupCode, OdBool val);
  virtual OdResult writeDouble(OdDb::DxfCode groupCode, double value, int precision = kDfltPrec);
  virtual OdResult writeEmbeddedObjectStart();

  virtual OdResult writeInt16(OdDb::DxfCode groupCode, OdInt16 value);
  virtual OdResult writeInt64(OdDb::DxfCode groupCode, OdInt64 value);
  virtual OdResult writeInt32(OdDb::DxfCode groupCode, OdInt32 value);
  virtual OdResult writeInt8(OdDb::DxfCode groupCode, OdInt8 value);
  virtual OdResult writeObjectId(OdDb::DxfCode groupCode, const OdDbObjectId& value);
  virtual OdResult writePoint2d(OdDb::DxfCode groupCode, const OdGePoint2d&value, int precision = kDfltPrec);
  virtual OdResult writePoint3d(OdDb::DxfCode groupCode, const OdGePoint3d&value, int precision = kDfltPrec);
  virtual OdResult writeResBuf(const resbuf& Rb);
  virtual OdResult writeScale3d(OdDb::DxfCode groupCode, const OdGeScale3d&value, int precision = kDfltPrec);
  virtual OdResult writeString(OdDb::DxfCode groupCode, const OdString& value);
  virtual OdResult writeString(OdDb::DxfCode groupCode, const OdChar * value);
  virtual OdResult writeUInt64(OdDb::DxfCode groupCode, OdUInt64 value);
  virtual OdResult writeUInt32(OdDb::DxfCode groupCode, OdUInt32 value);
  virtual OdResult writeUInt16(OdDb::DxfCode groupCode, OdUInt16 value);
  virtual OdResult writeUInt8(OdDb::DxfCode groupCode, OdUInt8 value);
  virtual OdResult writeVector2d(OdDb::DxfCode groupCode, const OdGeVector2d&value, int precision = kDfltPrec);
  virtual OdResult writeVector3d(OdDb::DxfCode groupCode, const OdGeVector3d&value, int precision = kDfltPrec);
  virtual OdResult writeXDataStart();

  OdResult writeItem(OdDb::DxfCode groupCode, const OdDbHandle&);
  OdResult writeItem(OdDb::DxfCode groupCode, const OdDbObjectId&);
  OdResult writeItem(OdDb::DxfCode, const OdGePoint2d&, int = kDfltPrec);
  OdResult writeItem(OdDb::DxfCode, const OdGePoint3d&, int = kDfltPrec);
  OdResult writeItem(OdDb::DxfCode, const OdGeScale3d&, int = kDfltPrec);
  OdResult writeItem(OdDb::DxfCode, const OdGeVector2d&, int = kDfltPrec);
  OdResult writeItem(OdDb::DxfCode, const OdGeVector3d&, int = kDfltPrec);

  OdResult writeItem(OdDb::DxfCode, const OdChar *);
  OdResult writeItem(OdDb::DxfCode, const OdString&);

#ifndef OdBool_is_bool
  OdResult writeItem(OdDb::DxfCode, OdBool);
#endif
  OdResult writeItem(OdDb::DxfCode, OdInt16);
  OdResult writeItem(OdDb::DxfCode, OdInt32);
  OdResult writeItem(OdDb::DxfCode, OdInt8);
  OdResult writeItem(OdDb::DxfCode, OdUInt16);
  OdResult writeItem(OdDb::DxfCode, OdUInt32);
  OdResult writeItem(OdDb::DxfCode, OdUInt8);
  OdResult writeItem(OdDb::DxfCode, const gds_binary& val);
  OdResult writeItem(OdDb::DxfCode, bool);
  OdResult writeItem(OdDb::DxfCode, double, int = kDfltPrec);

  /** \details
    Returns true if and only if default values are normally written 
    to the file associated with this Filer object.
  */
    virtual bool includesDefaultValues() const;

    virtual bool isModifyingExistingObject() const;

    virtual void haltAtClassBoundaries(bool halt);


  /** \details
    Returns true if and only if this Filer object is at the end of an object's data.
    
    \remarks
    This will be true when the filter is at any of the following:

    * A subclass data marker.
    * The start of an object's xdata.
    * The start of embedded object's data.
    * The start of another object's data.
    * The end of a file.

    \remarks
    The default implementation of this function does nothing but
    throw an exception.
  */
  virtual bool atEOF();
  
  /** \details
    Returns true if and only if this Filer object is at the end of an object's data.
    
    \remarks
    This will be true when the filter is at any of the following:
    
    * The start of another object's data.
    * The end of a file.
    
    \remarks
    The default implementation of this function does nothing but
    throw an exception.
  */
  virtual bool atEndOfObject();
  
  /** \details
    Returns true if and only if this Filer object is at the start of an object's xdata.
    
    \remarks
    The default implementation of this function does nothing but
    throw an exception.
  */
  virtual bool atExtendedData();

  /** \details
    Returns true if and only if this Filer object is at a subclass data marker with the specified subClassName.

    \param subClassName [in]  Subclass name.
    
    \remarks
    If true, the Filer advances the file pointer to the next item.
     
    \remarks
    The default implementation of this function does nothing but
    throw an exception.
  */
  virtual bool atSubclassData(
    const OdChar* subClassName);

  virtual double elevation() const;


  virtual OdResult setError(OdResult, const OdChar *, ...);
  virtual OdResult setError(const OdChar *, ...);
  virtual const OdChar * errorMessage() const;

  /** \details
    Returns true if and only if this Filer object is at start of an embedded object.
    
    \remarks
    If true, the Filer advances the file pointer to the next item.
     
    \remarks
    The default implementation of this function does nothing but
    throw an exception.
  */
  virtual bool atEmbeddedObjectStart();

  /** \details
    Reads the next item of this Filer object, and returns its group code.
    
    \remarks
    The default implementation of this function does nothing but
    throw an exception.
  */
  virtual int nextItem();
  
  /** \details
    Reads the next item of this Filer object, and returns a SmartPointer to its ResBuf.
  */
  virtual resbuf* nextRb();
  
  /** \details
    Writes the specified ResBuf object to this Filer object.
    \param pRb [in]  Pointer to the ResBuf object.
  */
  virtual void writeRb(
    const OdResBuf* pRb);

  /** \details
    Resets this Filer object to where it was before the last item was read.
    
    \remarks
    The default implementation of this function does nothing but
    throw an exception.
  */
    virtual OdResult pushBackItem();

    OdResult readItem(resbuf* pItem);
    virtual OdResult readResBuf(resbuf*);
  
  /** \details
    Returns the string value of the current item of this Filer object.
    \param value [out]  Receives the value.
  */
  OdString rdString();
  virtual void rdString(
    OdString &value) {}

  /** \details
    Returns the bool value of the current item of this Filer object.
  */
  virtual bool rdBool() { return true; }

  /** \details
    Returns the Int8 value of the current item of this Filer object.
  */
  virtual OdInt8 rdInt8() { return 0; }

  /** \details
    Returns the Int16 value of the current item of this Filer object.
  */
  virtual OdInt16 rdInt16() { return 0; }

  /** \details
    Returns the Int32 value of the current item of this Filer object.
  */
  virtual OdInt32 rdInt32() { return 0; }
  
  /** \details
  Returns the Int64 value of the current item of this Filer object.
  */
  virtual OdInt64 rdInt64() { return 0; }

  /** \details
    Returns the UInt8 value of the current item of this Filer object.
  */
  virtual OdUInt8 rdUInt8() { return 0; }
  
  /** \details
    Returns the UInt16 value of the current item of this Filer object.
  */
  virtual OdUInt16 rdUInt16() { return 0; }
  
  /** \details
    Returns the UInt32 value of the current item of this Filer object.
  */
  virtual OdUInt32 rdUInt32() { return 0; }
  
  /** \details
  Returns the UInt64 value of the current item of this Filer object.
  */
  virtual OdUInt64 rdUInt64() { return 0; }

  /** \details
    Returns the handle value of the current item of this Filer object.
  */
  virtual OdDbHandle rdHandle() { return OdDbHandle(); }
  
  /** \details
    Returns the Object ID value of the current item of this Filer object.
  */
  virtual OdDbObjectId rdObjectId() { return OdDbObjectId(); }

  /** \details
  Returns the angle value of the current item of this Filer object.
  */
  virtual double rdAngle() { return 0.0; }

  /** \details
    Returns the double value of the current item of this Filer object.
  */
  virtual double rdDouble() { return 0.0; }
 
  /** \details
    Returns the 2D point value of the current item of this Filer object.
    \param value [out]  Receives the value.
  */
  virtual void rdPoint2d(
    OdGePoint2d& value) {}
    
  /** \details
    Returns the 3D point value of the current item of this Filer object.
    \param value [out]  Receives the value.
  */
  virtual void rdPoint3d(
    OdGePoint3d& value) {}

  /** \details
    Returns the 2D vector value of the current item of this Filer object.
    \param value [out]  Receives the value.
  */
  virtual void rdVector2d(
    OdGeVector2d& value) {}

  /** \details
    Returns the 3D vector value of the current item of this Filer object.
    \param value [out]  Receives the value.
  */
  virtual void rdVector3d(
    OdGeVector3d& value) {}
  
  /** \details
    Returns the scale value of the current item of this Filer object.
    \param value [out]  Receives the value.
  */
  virtual void rdScale3d(
    OdGeScale3d& value) {}
    
  /** \details
    Returns the BinaryData value of the current item of this Filer object.
    
    \param value [out]  Receives the value.
  */
  virtual void rdBinaryChunk(
    OdBinaryData& value) {}

  /** \details
    Copies the current item from the specified Filer object to this one.
    \param pSource [in]  Pointer to the source Filer.
  */
  virtual void copyItem(
    OdDbDxfFiler * pSource);

  /** \details
    Writes the specified name value to this Filer object.
    \param groupCode [in]  Group code.
    \param value [in]  Value.
  */
  virtual void wrName(
    OdDb::DxfCode groupCode,
	  const OdString& value){}

  /** Description:
    Writes the specified *string* *value* to this Filer object.
    Arguments:
    groupCode (I) Group code.
    value (I) Value.
  */  
  ODRX_SEALED_VIRTUAL void wrString(
    OdDb::DxfCode groupCode,
    const OdString& value) ODRX_SEALED;
  
  /** Description:
    Writes the specified optional *string* *value* to this Filer object.
    
    \remarks
    value is written if and only if
              (value != NULL) || (includesDefaultValues() == true)
     
    \param groupCode [in]  Group code.
    \param value [in]  Value.
  */
    void wrStringOpt(
      OdDb::DxfCode groupCode,
    const OdString& value);

  /** \details
    Writes the specified subclass data marker to this Filer object.
      
    \param value [in]  Value.
  */
    void wrSubclassMarker(
    const OdString &value);

  /** \details
    Writes the embedded object start marker to this Filer object.
  */
    void wrEmbeddedObjectStart();

  /** Description:
    Writes the specified bool *value* to this Filer object.
    Arguments:
    groupCode (I) Group code.
    value (I) Value.
  */  
  ODRX_SEALED_VIRTUAL void wrBool(
    OdDb::DxfCode groupCode,
    bool value) ODRX_SEALED;
    
  /** \details
    Writes the specified optional bool value to this Filer object.
    
    \remarks
    value is written if and only if
              (value != default) || (includesDefaultValues() == true)
     
    \param groupCode [in]  Group code.
    \param value [in]  Value.
    \param defaultValue [in]  Default value.
  */
  void wrBoolOpt(
    OdDb::DxfCode groupCode,
    bool value, 
    bool defaultValue);

  /** Description:
    Writes the specified Int8 *value* to this Filer object.
    Arguments:
    groupCode (I) Group code.
    value (I) Value.
  */  
  ODRX_SEALED_VIRTUAL void wrInt8(
    OdDb::DxfCode groupCode,
    OdInt8 value) ODRX_SEALED;
  
  /** Description:
    Writes the specified optional Int8 *value* to this Filer object.
    
    \remarks
    value is written if and only if
              (value != default) || (includesDefaultValues() == true)
     
    \param groupCode [in]  Group code.
    \param value [in]  Value.
    \param defaultValue [in]  Default value.
  */
  void wrInt8Opt(
    OdDb::DxfCode groupCode,
    OdInt8 value, 
    OdInt8 defaultValue);

  /** Description:
    Writes the specified UInt8 *value* to this Filer object.
    Arguments:
    groupCode (I) Group code.
    value (I) Value.
  */  
  ODRX_SEALED_VIRTUAL void wrUInt8(
    OdDb::DxfCode groupCode,
    OdUInt8 value) ODRX_SEALED; 

  /** Description:
    Writes the specified optional UInt8 *value* to this Filer object.
    
    \remarks
    value is written if and only if
              (value != default) || (includesDefaultValues() == true)
     
    \param groupCode [in]  Group code.
    \param value [in]  Value.
    \param defaultValue [in]  Default value.
  */
  void wrUInt8Opt(
    OdDb::DxfCode groupCode,
    OdUInt8 value, 
    OdUInt8 defaultValue);

  /** Description:
    Writes the specified Int16 *value* to this Filer object.
    Arguments:
    groupCode (I) Group code.
    value (I) Value.
  */  
  ODRX_SEALED_VIRTUAL void wrInt16(
    OdDb::DxfCode groupCode,
    OdInt16 value) ODRX_SEALED;  
    
  /** \details
    Writes the specified optional Int16 value to this Filer object.
    
    \remarks
    value is written if and only if
              (value != default) || (includesDefaultValues() == true)
     
    \param groupCode [in]  Group code.
    \param value [in]  Value.
    \param defaultValue [in]  Default value.
  */
  void wrInt16Opt(
    OdDb::DxfCode groupCode,
    OdInt16 value, 
    OdInt16 defaultValue);

  /** Description:
    Writes the specified UInt16 *value* to this Filer object.
    Arguments:
    groupCode (I) Group code.
    value (I) Value.
  */  
  ODRX_SEALED_VIRTUAL void wrUInt16(
    OdDb::DxfCode groupCode,
    OdUInt16 value) ODRX_SEALED;  
    
  /** \details
    Writes the specified optional UInt16 value to this Filer object.
    
    \remarks
    value is written if and only if
              (value != default) || (includesDefaultValues() == true)
     
    \param groupCode [in]  Group code.
    \param value [in]  Value.
    \param defaultValue [in]  Default value.
  */
  void wrUInt16Opt(
    OdDb::DxfCode groupCode,
    OdUInt16 value, 
    OdUInt16 defaultValue);

  /** Description:
    Writes the specified Int32 *value* to this Filer object.
    Arguments:
    groupCode (I) Group code.
    value (I) Value.
  */  
  ODRX_SEALED_VIRTUAL void wrInt32(
    OdDb::DxfCode groupCode,
    OdInt32 value) ODRX_SEALED;  
    
  /** \details
    Writes the specified optional Int32 value to this Filer object.
    
    \remarks
    value is written if and only if
              (value != default) || (includesDefaultValues() == true)
     
    \param groupCode [in]  Group code.
    \param value [in]  Value.
    \param defaultValue [in]  Default value.
  */
  void wrInt32Opt(
    OdDb::DxfCode groupCode,
    OdInt32 value, 
    OdInt32 defaultValue);

  /** Description:
    Writes the specified UInt32 *value* to this Filer object.
    Arguments:
    groupCode (I) Group code.
    value (I) Value.
  */  
  ODRX_SEALED_VIRTUAL void wrUInt32(
    OdDb::DxfCode groupCode, OdUInt32 value) ODRX_SEALED;
    
  /** Description:
    Writes the specified optional UInt32 *value* to this Filer object.
    
    \remarks
    value is written if and only if
              (value != default) || (includesDefaultValues() == true)
     
    \param groupCode [in]  Group code.
    \param value [in]  Value.
    \param defaultValue [in]  Default value.
  */
  void wrUInt32Opt(
    OdDb::DxfCode groupCode,
    OdUInt32 value, 
    OdUInt32 defaultValue);

  /** Description:
    Writes the specified Int64 *value* to this Filer object.
    Arguments:
    groupCode (I) Group code.
    value (I) Value.
  */  
  ODRX_SEALED_VIRTUAL void wrInt64(
    OdDb::DxfCode groupCode, 
    OdInt64 value) ODRX_SEALED;  

  /** \details
    Writes the specified optional Int64 value to this Filer object.

    \remarks
    value is written if and only if
    (value != default) || (includesDefaultValues() == true)

    \param groupCode [in]  Group code.
    \param value [in]  Value.
    \param defaultValue [in]  Default value.
  */
  void wrInt64Opt(
    OdDb::DxfCode groupCode, 
    OdInt64 value, 
    OdInt64 defaultValue);

  /** Description:
    Writes the specified UInt64 *value* to this Filer object.
    Arguments:
    groupCode (I) Group code.
    value (I) Value.
  */  
  ODRX_SEALED_VIRTUAL void wrUInt64(
    OdDb::DxfCode groupCode, 
    OdUInt64 value) ODRX_SEALED;
  

  /** \details
    Writes the specified optional UInt64 value to this Filer object.

    \remarks
    value is written if and only if
    (value != default) || (includesDefaultValues() == true)

    \param groupCode [in]  Group code.
    \param value [in]  Value.
    \param defaultValue [in]  Default value.
  */
  void wrUInt64Opt(
    OdDb::DxfCode groupCode, 
    OdUInt64 value, 
    OdUInt64 defaultValue);

  /** Description:
    Writes the specified bool *value* to this Filer object.
    Arguments:
    groupCode (I) Group code.
    value (I) Value.
  */  
  ODRX_SEALED_VIRTUAL void wrHandle(
    OdDb::DxfCode groupCode, 
    const OdDbHandle& value) ODRX_SEALED;

  /** Description:
    Writes the specified Object ID *value* to this Filer object.
    Arguments:
    groupCode (I) Group code.
    value (I) Value.
  */  
  ODRX_SEALED_VIRTUAL void wrObjectId(
    OdDb::DxfCode groupCode, 
    const OdDbObjectId& value) ODRX_SEALED;

  /** Description:
    Writes the specified optional Object ID *value* to this Filer object.
    
    \remarks
    value is written if and only if
              (value != NULL) || (includesDefaultValues() == true)
     
    \param groupCode [in]  Group code.
    \param value [in]  Value.
    \param defaultValue [in]  Default value.
  */
  void wrObjectIdOpt(
    OdDb::DxfCode groupCode, 
    const OdDbObjectId& value);

  /** \details
    Writes the specified angle value to this Filer object.
    \param groupCode [in]  Group code.
    \param value [in]  Value.
    \param precision [in]  Decimal places.
  */
    virtual void wrAngle(
    OdDb::DxfCode groupCode, 
    double value, 
    int precision = kDfltPrec) {}
    
  /** \details
    Writes the specified optional angle value to this Filer object.
    
    \remarks
    value is written if and only if
              (value != default) || (includesDefaultValues() == true)
     
    \param groupCode [in]  Group code.
    \param value [in]  Value.
    \param defaultValue [in]  Default value.
    \param precision [in]  Decimal places.
  */
  void wrAngleOpt(
    OdDb::DxfCode groupCode, 
    double value, 
    double defaultValue = 0., 
    int precision = kDfltPrec);

  /** Description:
    Writes the specified double *value* to this Filer object.
    Arguments:
    groupCode (I) Group code.
    value (I) Value.
    precision (I) Decimal places.
  */  
  ODRX_SEALED_VIRTUAL void wrDouble(
    OdDb::DxfCode groupCode, 
    double value, 
    int precision = kDfltPrec) ODRX_SEALED;  
    
  /** \details
    Writes the specified optional double value to this Filer object.
    
    \remarks
    value is written if and only if
              (value != default) || (includesDefaultValues() == true)
     
    \param groupCode [in]  Group code.
    \param value [in]  Value.
    \param defaultValue [in]  Default value.
    \param precision [in]  Decimal places.
  */
  void wrDoubleOpt(
    OdDb::DxfCode groupCode, 
    double value, 
    double defaultValue = 0., 
    int precision = kDfltPrec);

  /** Description:
    Writes the specified 2D *point* *value* to this Filer object.
    Arguments:
    groupCode (I) Group code.
    value (I) Value.
    precision (I) Decimal places.
  */  
  ODRX_SEALED_VIRTUAL void wrPoint2d(
    OdDb::DxfCode groupCode, 
    const OdGePoint2d& value, 
    int precision = kDfltPrec) ODRX_SEALED;
    
  /** \details
    Writes the specified optional 2D point value to this Filer object.
    
    \remarks
    value is written if and only if
              (value != default) || (includesDefaultValues() == true)
     
    \param groupCode [in]  Group code.
    \param value [in]  Value.
    \param defaultValue [in]  Default value.
    \param precision [in]  Decimal places.
  */
  void wrPoint2dOpt(
    OdDb::DxfCode groupCode, 
    const OdGePoint2d& value, 
    const OdGePoint2d& defaultValue, 
    int precision = kDfltPrec);

  /** Description:
    Writes the specified 3D *point* *value* to this Filer object.
    Arguments:
    groupCode (I) Group code.
    value (I) Value.
    precision (I) Decimal places.
  */  
  ODRX_SEALED_VIRTUAL void wrPoint3d(
    OdDb::DxfCode groupCode, 
    const OdGePoint3d& value, 
    int precision = kDfltPrec) ODRX_SEALED;  
    
  /** \details
    Writes the specified optional 3D point value to this Filer object.
    
    \remarks
    value is written if and only if
              (value != default) || (includesDefaultValues() == true)
     
    \param groupCode [in]  Group code.
    \param value [in]  Value.
    \param defaultValue [in]  Default value.
    \param precision [in]  Decimal places.
  */
  void wrPoint3dOpt(
    OdDb::DxfCode groupCode, 
    const OdGePoint3d& value, 
    const OdGePoint3d& defaultValue, 
    int precision = kDfltPrec);

  /** Description:
    Writes the specified 2D *vector* *value* to this Filer object.
    Arguments:
    groupCode (I) Group code.
    value (I) Value.
    precision (I) Decimal places.
  */  
  ODRX_SEALED_VIRTUAL void wrVector2d(
    OdDb::DxfCode groupCode, 
    const OdGeVector2d& value, 
    int precision = kDfltPrec) ODRX_SEALED;  
    
  /** \details
    Writes the specified optional 2D vector value to this Filer object.
    
    \remarks
    value is written if and only if
              (value != default) || (includesDefaultValues() == true)
     
    \param groupCode [in]  Group code.
    \param value [in]  Value.
    \param defaultValue [in]  Default value.
    \param precision [in]  Decimal places.
  */
  void wrVector2dOpt(
    OdDb::DxfCode groupCode, 
    const OdGeVector2d& value, 
    const OdGeVector2d& defaultValue, 
    int precision = kDfltPrec);

  /** Description:
    Writes the specified 3D *vector* *value* to this Filer object.
    Arguments:
    groupCode (I) Group code.
    value (I) Value.
    precision (I) Decimal places.
  */  
  ODRX_SEALED_VIRTUAL void wrVector3d(
    OdDb::DxfCode groupCode, 
    const OdGeVector3d& value, 
    int precision = kDfltPrec) ODRX_SEALED;
    
  /** \details
    Writes the specified optional 3D vector value to this Filer object.
    
    \remarks
    value is written if and only if
              (value != default) || (includesDefaultValues() == true)
     
    \param groupCode [in]  Group code.
    \param value [in]  Value.
    \param defaultValue [in]  Default value.
    \param precision [in]  Decimal places.
  */
  void wrVector3dOpt(
    OdDb::DxfCode groupCode, 
    const OdGeVector3d& value, 
    const OdGeVector3d& defaultValue, 
    int precision = kDfltPrec);

  /** Description:
    Writes the specified 2D *scale*  *value* to this Filer object.
    Arguments:
    groupCode (I) Group code.
    value (I) Value.
    precision (I) Decimal places.
  */  
  ODRX_SEALED_VIRTUAL void wrScale3d(
    OdDb::DxfCode groupCode, 
    const OdGeScale3d& value, 
    int precision = kDfltPrec) ODRX_SEALED;

  /** \details
    Writes the specified BinaryChunk value to this Filer object.
    \param groupCode [in]  Group code.
    \param numBytes [in]  Number of bytes.
    \param buffer [in]  Array of bytes.
  */
    virtual void wrBinaryChunk(
    OdDb::DxfCode groupCode, 
    const OdUInt8* buffer, 
    OdUInt32 numBytes) {}
  
  /** \details
    Writes the specified BinaryChunk value to this Filer object.
    \param groupCode [in]  Group code.
    \param value [in]  Value.
  */   
  void wrBinaryChunk(
    OdDb::DxfCode groupCode, 
    const OdBinaryData& value);
};
/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbDxfFiler object pointers.
*/
typedef OdSmartPtr<OdDbDxfFiler> OdDbDxfFilerPtr;

/** \details
    This class implements OdError objects with Result codes of eDwgObjectImproperlyRead.
    
    Corresponding C++ library: TD_Db
    <group Error_Classes> 
*/
class TOOLKIT_EXPORT OdError_DwgObjectImproperlyRead : public OdError
{
public:
  OdError_DwgObjectImproperlyRead() : OdError(eDwgObjectImproperlyRead){}
};

/** \details
    This class is the abstract base class for classes that are used for file I/O operations
    with the .dwg file format.
    
    Corresponding C++ library: TD_Db

    <group OdDb_Classes>
*/

class OdDbIdRefQueue;
class TOOLKIT_EXPORT OdDbDwgFiler : public OdDbFiler
{
public:
  OdDbDwgFiler();

  ODRX_DECLARE_MEMBERS(OdDbDwgFiler);

  virtual void resetFilerStatus();
  
  virtual OdDb::FilerType filerType() const;
  virtual void setFilerStatus(OdResult es);




  /** \details
    Moves the I/O pointer to the specified location in this Filer object.
    
    \param offset [in]  Number of bytes.
    \param seekType [in]  Seek type.
    
    \remarks
    seekType must be one of the following:
    
    <table>
    Name                    Value       Description.
    OdDb::kSeekFromStart    SEEK_SET    Start of file.
    OdDb::kSeekFromCurrent  SEEK_CUR    Current position of I/O pointer.
    OdDb::kSeekFromEnd      SEEK_END    End of file.
    </table>
  */
  virtual OdResult seek(OdInt64 offset, int seekType);

  /** \details
    Returns the current I/O pointer position of this Filer object.
  */
  virtual OdInt64 tell() const 
  { return 0; }

  /** \details
    Returns the bool value of the current item of this Filer object.
  */
  ODRX_SEALED_VIRTUAL bool rdBool() ODRX_SEALED;

  /** \details
    Returns the string value of the current item of this Filer object.

  */
  ODRX_SEALED_VIRTUAL OdString rdString() ODRX_SEALED;

  
  /** \details
    Returns the specified number of bytes from this Filer object.
    \param buffer [out]  Receives the bytes.
    \param numBytes [in]  Number of bytes.
  */
  ODRX_SEALED_VIRTUAL void rdBytes(
    void* buffer,
    OdUInt32 numBytes) ODRX_SEALED;


  /** \details
    Returns the Int8 value of the current item of this Filer object.
  */
  ODRX_SEALED_VIRTUAL OdInt8 rdInt8() ODRX_SEALED;
  
  /** \details
    Returns the UInt8 value of the current item of this Filer object.
  */
  ODRX_SEALED_VIRTUAL OdUInt8 rdUInt8() ODRX_SEALED;

  /** \details
    Returns the Int16 value of the current item of this Filer object.
  */
  ODRX_SEALED_VIRTUAL OdInt16 rdInt16() ODRX_SEALED;

  /** \details
    Returns the Int32 value of the current item of this Filer object.
  */
  ODRX_SEALED_VIRTUAL OdInt32 rdInt32() ODRX_SEALED;

  /** \details
    Returns the Int64 value of the current item of this Filer object.
  */
  ODRX_SEALED_VIRTUAL OdInt64 rdInt64() ODRX_SEALED;

  /** \details
    Returns the memory address value of the current item of this Filer object.
  */

  

  ODRX_SEALED_VIRTUAL void* rdAddress() ODRX_SEALED;
  //ODRX_SEALED_VIRTUAL void* rdAddress() ODRX_SEALED;

  /** \details
    Returns the double value of the current item of this Filer object.
  */
  ODRX_SEALED_VIRTUAL double rdDouble() ODRX_SEALED;

  /** \details
    Returns the handle value of the current item of this Filer object.
  */
  ODRX_SEALED_VIRTUAL OdDbHandle rdDbHandle() ODRX_SEALED;

  /** \details
    Returns the SoftOwnershipId value of the current item of this Filer object.
  */
  ODRX_SEALED_VIRTUAL OdDbSoftOwnershipId rdSoftOwnershipId() ODRX_SEALED;

  /** \details
    Returns the HardOwnershipId value of the current item of this Filer object.
  */
  ODRX_SEALED_VIRTUAL OdDbHardOwnershipId rdHardOwnershipId() ODRX_SEALED;

  /** \details
    Returns the HardPointerId value of the current item of this Filer object.
  */
  ODRX_SEALED_VIRTUAL OdDbHardPointerId rdHardPointerId() ODRX_SEALED;

  /** \details
    Returns the SoftPointerId value of the current item of this Filer object.
  */
  ODRX_SEALED_VIRTUAL OdDbSoftPointerId rdSoftPointerId() ODRX_SEALED;

  /** \details
    Returns the 2D point value of the current item of this Filer object.
  */
  ODRX_SEALED_VIRTUAL OdGePoint2d rdPoint2d() ODRX_SEALED;
    
  /** \details
    Returns the 3D point value of the current item of this Filer object.
  */
  ODRX_SEALED_VIRTUAL OdGePoint3d rdPoint3d() ODRX_SEALED;

  /** \details
    Returns the 2D vector value of the current item of this Filer object.
  */
  ODRX_SEALED_VIRTUAL OdGeVector2d rdVector2d() ODRX_SEALED;

  /** \details
    Returns the 3D vector value of the current item of this Filer object.
  */
  ODRX_SEALED_VIRTUAL OdGeVector3d rdVector3d() ODRX_SEALED;
  
  /** \details
    Returns the scale value of the current item of this Filer object.
  */
  ODRX_SEALED_VIRTUAL OdGeScale3d rdScale3d() ODRX_SEALED;

  /** \details
    Returns the thickness value of the current item of this Filer object.
  */
  virtual double rdThickness();

  /** \details
    Returns the extrusion value of the current item of this Filer object.
  */
  virtual OdGeVector3d rdExtrusion();

  //acad 的接口
  virtual OdResult readOdDbHandle(OdDbHandle* unnamed) { return Oda::eOk; }
  virtual OdResult readAddress(void** unnamed);
  virtual OdResult readBChunk(gds_binary* unnamed) { return Oda::eOk; }
  virtual OdResult readBoolean(OdBool*) { return Oda::eOk; }
  virtual OdResult readBool(bool* unnamed) { return Oda::eOk; }
  virtual OdResult readBytes(void* buffer, OdUIntPtr numBytes) { return Oda::eOk; }
  virtual OdResult readDouble(double* unnamed) { return Oda::eOk; }
  virtual OdResult readHardOwnershipId(OdDbHardOwnershipId* unnamed) { return Oda::eOk; }
  virtual OdResult readHardPointerId(OdDbHardPointerId* unnamed) { return Oda::eOk; }
  virtual OdResult readInt16(OdInt16* unnamed) { return Oda::eOk; }
  virtual OdResult readInt64(OdInt64* unnamed) { return Oda::eOk; }
  virtual OdResult readInt32(OdInt32* unnamed) { return Oda::eOk; }
  virtual OdResult readPoint2d(OdGePoint2d* unnamed) { return Oda::eOk; }
  virtual OdResult readPoint3d(OdGePoint3d* unnamed) { return Oda::eOk; }
  virtual OdResult readScale3d(OdGeScale3d* unnamed) { return Oda::eOk; }
  virtual OdResult readSoftOwnershipId(OdDbSoftOwnershipId* unnamed) { return Oda::eOk; }
  virtual OdResult readSoftPointerId(OdDbSoftPointerId* unnamed) { return Oda::eOk; }
  virtual OdResult readString(OdString& unnamed) { return Oda::eOk; }
  virtual OdResult readString(OdChar** unnamed) { return Oda::eOk; }
  virtual OdResult readUInt16(OdUInt16* unnamed) { return Oda::eOk; }
  virtual OdResult readUInt32(OdUInt32* unnamed) { return Oda::eOk; }
  virtual OdResult readUInt64(OdUInt64* unnamed) { return Oda::eOk; }
  virtual OdResult readUInt8(OdUInt8* unnamed) { return Oda::eOk; }
  virtual OdResult readVector2d(OdGeVector2d* unnamed) { return Oda::eOk; }
  virtual OdResult readVector3d(OdGeVector3d* unnamed) { return Oda::eOk; }
  virtual OdResult readInt8(OdInt8* unnamed) { return Oda::eOk; }

  OdResult readItem(OdDbHandle*);
  OdResult readItem(OdDbHardOwnershipId*);
  OdResult readItem(OdDbHardPointerId*);
  OdResult readItem(OdDbSoftOwnershipId*);
  OdResult readItem(OdDbSoftPointerId*);
  OdResult readItem(OdGePoint2d*);
  OdResult readItem(OdGePoint3d*);
  OdResult readItem(OdGeScale3d*);
  OdResult readItem(OdGeVector2d*);
  OdResult readItem(OdGeVector3d*);
  OdResult readItem(OdChar **);
#ifndef OdBool_is_bool 
  OdResult readItem(OdBool*);
#endif
  OdResult readItem(OdInt16*);
  OdResult readItem(OdInt32*);
  OdResult readItem(OdInt8*);
  OdResult readItem(OdUInt16*);
  OdResult readItem(OdUInt32*);
  OdResult readItem(OdUInt8*);
  OdResult readItem(gds_binary*);
  OdResult readItem(bool*);
  OdResult readItem(double*);
  OdResult readItem(void **);
  OdResult readItem(void *, OdUIntPtr);
  OdResult readItem(OdUInt64*);

  /** \details
    Writes the specified bool value to this Filer object.
    \param value [in]  Value.
  */
  ODRX_SEALED_VIRTUAL void wrBool(
    bool value) ODRX_SEALED;

  /** \details
    Writes the specified string value to this Filer object.
    \param value [in]  Value.
  */
  ODRX_SEALED_VIRTUAL void wrString(
    const OdString &value) ODRX_SEALED;
    
  /** \details
    Writes the specified number of bytes to this Filer object.
    \param buffer [in]  array of bytes.
    \param numBytes [in]  Number of bytes.
  */
  ODRX_SEALED_VIRTUAL void wrBytes(
    const void* buffer, 
    OdUInt32 numBytes) ODRX_SEALED;

  /** \details
    Writes the specified Int8 value to this Filer object.
    \param value [in]  Value.
  */
  ODRX_SEALED_VIRTUAL void wrInt8(
    OdInt8 value) ODRX_SEALED;
    
  /** \details
    Writes the specified UInt8 value to this Filer object.
    \param value [in]  Value.
  */
  ODRX_SEALED_VIRTUAL void wrUInt8(
    OdUInt8 value) ODRX_SEALED;

  /** \details
    Writes the specified Int16 value to this Filer object.
    \param value [in]  Value.
  */
  ODRX_SEALED_VIRTUAL void wrInt16(
    OdInt16 value) ODRX_SEALED;
    
  /** \details
    Writes the specified Int32 value to this Filer object.
    \param value [in]  Value.
  */
  ODRX_SEALED_VIRTUAL void wrInt32(
    OdInt32 value) ODRX_SEALED;

  /** \details
    Writes the specified Int64 value to this Filer object.
    \param value [in]  Value.
  */
  ODRX_SEALED_VIRTUAL void wrInt64(
    OdInt64 value) ODRX_SEALED;

  /** \details
    Writes the specified memory address value to this Filer object.
    \param value [in]  Value.
  */
  ODRX_SEALED_VIRTUAL void wrAddress(
    const void* value) ODRX_SEALED;
    
  /** \details
    Writes the specified double value to this Filer object.
    \param value [in]  Value.
  */
  ODRX_SEALED_VIRTUAL void wrDouble(double value) ODRX_SEALED;

  /** \details
    Writes the specified handle value to this Filer object.
    \param value [in]  Value.
  */
  ODRX_SEALED_VIRTUAL void wrDbHandle(
    const OdDbHandle& value) ODRX_SEALED;

  /** \details
    Writes the specified SoftOwnershipId value to this Filer object.
    \param value [in]  Value.
  */
  ODRX_SEALED_VIRTUAL void wrSoftOwnershipId(
    const OdDbObjectId& value) ODRX_SEALED;
    
  /** \details
    Writes the specified HardOwnershipId value to this Filer object.
    \param value [in]  Value.
  */
  ODRX_SEALED_VIRTUAL void wrHardOwnershipId(
    const OdDbObjectId& value) ODRX_SEALED;

  /** \details
    Writes the specified SoftPointerId value to this Filer object.
    \param value [in]  Value.
  */
  ODRX_SEALED_VIRTUAL void wrSoftPointerId(
    const OdDbObjectId& value) ODRX_SEALED;

  /** \details
    Writes the specified HardPointerId value to this Filer object.
    \param value [in]  Value.
  */
  ODRX_SEALED_VIRTUAL void wrHardPointerId(
    const OdDbObjectId& value) ODRX_SEALED;

  /** \details
    Writes the specified 2D point value to this Filer object.
    \param value [in]  Value.
  */
  ODRX_SEALED_VIRTUAL void wrPoint2d(
    const OdGePoint2d& value) ODRX_SEALED;

  /** \details
    Writes the specified 3D point value to this Filer object.
    \param value [in]  Value.
  */
  ODRX_SEALED_VIRTUAL void wrPoint3d(
    const OdGePoint3d& value) ODRX_SEALED;
  
  /** \details
    Writes the specified 2D vector value to this Filer object.
    \param value [in]  Value.
  */
  ODRX_SEALED_VIRTUAL void wrVector2d(
    const OdGeVector2d& value) ODRX_SEALED;
  
  /** \details
    Writes the specified 3D vector value to this Filer object.
    \param value [in]  Value.
  */
  ODRX_SEALED_VIRTUAL void wrVector3d(
    const OdGeVector3d& value) ODRX_SEALED;
  
  /** \details
    Writes the specified 3D scale value to this Filer object.
    \param value [in]  Value.
  */
    ODRX_SEALED_VIRTUAL void wrScale3d(
    const OdGeScale3d& value) ODRX_SEALED;

  /** \details
    Writes the specified thickness value to this Filer object.
    \param value [in]  Value.
  */
  virtual void wrThickness(double value);

  /** \details
    Writes the specified extrusion value to this Filer object.
    \param value [in]  Value.
  */
  virtual void wrExtrusion(const OdGeVector3d& value);

  virtual OdResult writeOdDbHandle(const OdDbHandle& value);
  virtual OdResult writeAddress(const void* value);
  virtual OdResult writeBChunk(const gds_binary& unnamed) { return Oda::eOk; }
  virtual OdResult writeBool(bool value) { return Oda::eOk; }
  virtual OdResult writeBoolean(OdBool) { return Oda::eOk; }
  virtual OdResult writeBytes(const void* buffer, OdUIntPtr numBytes) { return Oda::eOk; }
  virtual OdResult writeDouble(double value) { return Oda::eOk; }
  virtual OdResult writeHardOwnershipId(const OdDbHardOwnershipId& value) { return Oda::eOk; }
  virtual OdResult writeHardPointerId(const OdDbHardPointerId& value) { return Oda::eOk; }
  virtual OdResult writeInt16(OdInt16 value) { return Oda::eOk; }
  virtual OdResult writeInt64(OdInt64 value) { return Oda::eOk; }
  virtual OdResult writeInt32(OdInt32 value) { return Oda::eOk; }
  virtual OdResult writeInt8(OdInt8 value) { return Oda::eOk; }
  virtual OdResult writePoint2d(const OdGePoint2d& value) { return Oda::eOk; }
  virtual OdResult writePoint3d(const OdGePoint3d& value) { return Oda::eOk; }
  virtual OdResult writeScale3d(const OdGeScale3d& value) { return Oda::eOk; }
  virtual OdResult writeSoftOwnershipId(const OdDbSoftOwnershipId& value) { return Oda::eOk; }
  virtual OdResult writeSoftPointerId(const OdDbSoftPointerId& value) { return Oda::eOk; }
  virtual OdResult writeString(const OdString &value) { return Oda::eOk; }
  virtual OdResult writeString(const OdChar* unnamed) { return Oda::eOk; }
  virtual OdResult writeUInt16(OdUInt16 unnamed) { return Oda::eOk; }
  virtual OdResult writeUInt32(OdUInt32 unnamed) { return Oda::eOk; }
  virtual OdResult writeUInt64(OdUInt64 unnamed) { return Oda::eOk; }
  virtual OdResult writeUInt8(OdUInt8 value) { return Oda::eOk; }
  virtual OdResult writeVector2d(const OdGeVector2d& value) { return Oda::eOk; }
  virtual OdResult writeVector3d(const OdGeVector3d& value) { return Oda::eOk; }
  virtual OdResult readInt(int*) { return Oda::eOk; }
  virtual OdResult writeInt(int) { return Oda::eOk; }

  OdResult writeItem(const OdDbHandle&);
  OdResult writeItem(const OdDbHardOwnershipId&);
  OdResult writeItem(const OdDbHardPointerId&);
  OdResult writeItem(const OdDbSoftOwnershipId&);
  OdResult writeItem(const OdDbSoftPointerId&);
  OdResult writeItem(const OdGePoint2d&);
  OdResult writeItem(const OdGePoint3d&);
  OdResult writeItem(const OdGeScale3d&);
  OdResult writeItem(const OdGeVector2d&);
  OdResult writeItem(const OdGeVector3d&);
  OdResult writeItem(const OdChar *);
  OdResult writeItem(const OdString& val);
#ifndef OdBool_is_bool 
  OdResult writeItem(OdBool);
#else
inline OdResult readItem(int* pVal)
{   return readInt(pVal); }

inline OdResult writeItem(int val)
{   return writeInt(val);   }
#endif

  OdResult writeItem(OdInt16);
  OdResult writeItem(OdInt32);
  OdResult writeItem(OdInt8);

  OdResult writeItem(OdUInt16);
  OdResult writeItem(OdUInt32);
  OdResult writeItem(OdUInt8);

  OdResult writeItem(const gds_binary&);
  OdResult writeItem(bool);
  OdResult writeItem(double);
  OdResult writeItem(void *);
  OdResult writeItem(const void *, OdUIntPtr);
  OdResult writeItem(OdUInt64);

  /** \details
    Returns true if and only if this Filer object wishes to see
    all object references.
    
    \remarks
    The default implementation of this function always returns true. 
  */
  virtual bool usesReferences() const;
  
  /*!DOM*/
  /** \details
  */
  virtual void addReference(OdDbObjectId id, OdDb::ReferenceType rt);


  virtual OdResult addReferences(OdDbIdRefQueue& /*qToAbsorb*/);

  /** \details
  Returns true if and only if this filer object is used to store/read revision control format.

  \remarks
  The default implementation of this function always returns false.
  */
  virtual bool isPersistentMode() const;

  virtual OdDbFilerController& controller() const;

  virtual OdDbAuditInfo * getAuditInfo() const;

  TD_USING(OdDbFiler::controller);
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbDwgFiler object pointers.
*/
typedef OdSmartPtr<OdDbDwgFiler> OdDbDwgFilerPtr;


/** \details
    This class is the empty implementation of a base class 
    for classes that are used as ID Filers.
    
    Corresponding C++ library: TD_Db
    
    <group Other_Classes>
*/
class TOOLKIT_EXPORT OdIdFiler : public OdDbDwgFiler
{
public:
  OdIdFiler() : m_pController(NULL) {}

  OdResult seek(
    OdInt64 offset, 
    int seekType);
  
  OdInt64 tell() const;
  
  OdResult filerStatus() const;
  
  void resetFilerStatus();
  
  OdDb::FilerType filerType() const;
  
  OdDb::DwgVersion dwgVersion(
    OdDb::MaintReleaseVer* pMaintReleaseVer = 0) const;

  OdResult readOdDbHandle(OdDbHandle* unnamed);
  OdResult readBChunk(gds_binary* unnamed);
  OdResult readBoolean(OdBool*);
  OdResult readBool(bool* unnamed);
  OdResult readBytes(void* buffer, OdUIntPtr numBytes);
  OdResult readDouble(double* unnamed);
  OdResult readHardOwnershipId(OdDbHardOwnershipId* unnamed);
  OdResult readHardPointerId(OdDbHardPointerId* unnamed);
  OdResult readInt8(OdInt8* unnamed);
  OdResult readInt16(OdInt16* unnamed);
  OdResult readInt32(OdInt32* unnamed);
  OdResult readInt64(OdInt64* unnamed);
  OdResult readPoint2d(OdGePoint2d* unnamed);
  OdResult readPoint3d(OdGePoint3d* unnamed);
  OdResult readScale3d(OdGeScale3d* unnamed);
  OdResult readSoftOwnershipId(OdDbSoftOwnershipId* unnamed);
  OdResult readSoftPointerId(OdDbSoftPointerId* unnamed);
  OdResult readString(OdString& unnamed);
  OdResult readString(OdChar** unnamed);
  OdResult readUInt8(OdUInt8* unnamed);
  OdResult readUInt16(OdUInt16* unnamed);
  OdResult readUInt32(OdUInt32* unnamed);
  OdResult readUInt64(OdUInt64* unnamed);
  OdResult readVector2d(OdGeVector2d* unnamed);
  OdResult readVector3d(OdGeVector3d* unnamed);
  OdResult readInt(int*);

  OdResult writeOdDbHandle(const OdDbHandle& value);
  OdResult writeBChunk(const gds_binary& unnamed);
  OdResult writeBool(bool value);
  OdResult writeBoolean(OdBool);
  OdResult writeBytes(const void* buffer, OdUIntPtr numBytes);
  OdResult writeDouble(double value);
  OdResult writeInt8(OdInt8 value);
  OdResult writeInt16(OdInt16 value);
  OdResult writeInt32(OdInt32 value);
  OdResult writeInt64(OdInt64 value);
  OdResult writePoint2d(const OdGePoint2d& value);
  OdResult writePoint3d(const OdGePoint3d& value);
  OdResult writeScale3d(const OdGeScale3d& value);
  OdResult writeString(const OdString &value);
  OdResult writeString(const OdChar* unnamed);
  OdResult writeUInt8(OdUInt8 value);
  OdResult writeUInt16(OdUInt16 unnamed);
  OdResult writeUInt32(OdUInt32 unnamed);
  OdResult writeUInt64(OdUInt64 unnamed);
  OdResult writeVector2d(const OdGeVector2d& value);
  OdResult writeVector3d(const OdGeVector3d& value);
  OdResult writeInt(int);

  void setController(
    OdDbFilerController* pFilerController) { m_pController = pFilerController; }
  OdDbFilerController& controller() const { return *m_pController; }

  TD_USING(OdDbFiler::controller);
private:
  OdDbFilerController* m_pController;
};

inline OdResult OdDbDxfFiler::readItem(resbuf * pVal)
{
  return readResBuf(pVal);
}

inline OdResult OdDbDxfFiler::writeItem(const resbuf& val)
{
  return writeResBuf(val);
}

#include "TD_PackPop.h"

#endif  // FILER_INCLUDED

