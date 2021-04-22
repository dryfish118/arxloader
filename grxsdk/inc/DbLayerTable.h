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




#ifndef _ODDBLAYERTABLE_INCLUDED
#define _ODDBLAYERTABLE_INCLUDED

#include "TD_PackPush.h"

#include "DbSymbolTable.h"
#include "DwgDeclareMembers.h"

class OdDbLayerTableRecord;

/** Gcad(Add): 增加 DD 库缺少的 OdDbLayerTableIterator 类
  重新实现兼容的 getRecord() 非虚函数
*/
class TOOLKIT_EXPORT OdDbLayerTableIterator : public OdDbSymbolTableIterator
{
public:
  ODRX_DECLARE_MEMBERS(OdDbLayerTableIterator);

  virtual OdDbSymbolTableRecordPtr getRecord(
    OdDb::OpenMode openMode = OdDb::kForRead,
    bool openErasedRecord = false) const
  {
    return OdDbSymbolTableIterator::getRecord(openMode, openErasedRecord);
  }

  OdResult getRecord(
    OdDbLayerTableRecord*& pRecord,
    OdDb::OpenMode openMode = OdDb::kForRead,
    bool openErasedRec = false) const;

  OdResult seek(OdDbObjectId id);
  OdResult seek(const OdDbLayerTableRecord* pRecord);

  bool getSkipHidden() const;
  void setSkipHidden(bool value);

  bool getSkipReconciled() const;
  void setSkipReconciled(bool value);
protected:
  OdDbLayerTableIterator();

  OdDbLayerTableIterator(OdDbSymbolTableIteratorImpl* pImpl);
};

typedef OdSmartPtr<OdDbLayerTableIterator> OdDbLayerTableIteratorPtr;

/** \details
  <group OdDb_Classes>

  This class implements the layer table object, which represents a container for storing 
  and accessing of layer record objects in the database. This class inherits the base 
  functionality of predefined tables.


  \sa
  <link db_layer_sample_table, Example of Working with the Layer Table Object>

  <link db_layer_sample_record, Example of Working with the Layer Record Object>

  \sa
  <link db_layer, Working with Layers>

  OdDbLayerTableRecord class
*/
class TOOLKIT_EXPORT OdDbLayerTable: public OdDbSymbolTable
{
public:
  DWGMAP_DECLARE_MEMBERS(OdDbLayerTable);

  /** \details
    Builds an instance of the layer table object.
    
    Applications typically will not use this constructor, insofar as the database object 
    creates own instance of the layer table. The layer table object exists in the database 
    a prior.
  */
  OdDbLayerTable();
  virtual ~OdDbLayerTable();
  /****************************************
 * Gcad(Add): 新增兼容函数         *
 *--------------------------------------*/
  typedef OdDbLayerTableRecord RecordType;

  TD_USING(OdDbSymbolTable::getAt);
  
  OdResult getAt (
    const OdChar * recordName,
    OdDbLayerTableRecord*& pRec,
    OdDb::OpenMode openMode,
    bool openErasedRec = false) const;

  virtual OdDbSymbolTableIteratorPtr newIterator(
    bool atBeginning = true,
    bool skipDeleted = true) const;

  // 根据基类类似函数重新实现
  OdResult newIterator(
    OdDbLayerTableIterator*& pIterator,
    bool atBeginning = true,
    bool skipDeleted = true) const;

  virtual OdDbObjectId add(ODSYSDEFNAME, OdDbSymbolTableRecord* pRecord);

  OdResult add(OdDbObjectId& recordId, OdDbLayerTableRecord* pRecord);

  OdResult add(OdDbLayerTableRecord* pRecord);

  virtual OdResult subGetClassID(
    CLSID* pClsid) const;


  /** \details
    Generates usage data for each record in the layer table object.
    
    \remarks
    Usage data can be accessed via the OdDbLayerTableRecord::isInUse() method.
  */
  void generateUsageData();
  bool hasUnreconciledLayers() const;
    OdResult getUnreconciledLayers(OdDbObjectIdArray& idArray) const;
};

/** \details
  The typified smart pointer for the layer table object. This template class is specialization 
  of the OdSmartPtr class for the OdDbLayerTable object.

  \sa
  <link smart_pointers, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdDbLayerTable> OdDbLayerTablePtr;

#include "TD_PackPop.h"

TOOLKIT_EXPORT OdResult applyCurDwgLayerTableChanges();

#endif // _ODDBLAYERTABLE_INCLUDED

