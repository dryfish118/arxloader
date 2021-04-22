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




#ifndef _ODDBVIEWPORTTABLE_INCLUDED
#define _ODDBVIEWPORTTABLE_INCLUDED

#include "TD_PackPush.h"

#include "DbAbstractViewTable.h"
#include "DbObject.h"
#include "DwgDeclareMembers.h"

class OdDbViewportTableRecord;

class TOOLKIT_EXPORT OdDbViewportTableIterator : public OdDbAbstractViewTableIterator
{
public:
  ODRX_DECLARE_MEMBERS(OdDbViewportTableIterator);

  virtual OdDbSymbolTableRecordPtr getRecord(
    OdDb::OpenMode openMode = OdDb::kForRead,
    bool openErasedRecord = false) const
  {
    return OdDbAbstractViewTableIterator::getRecord(openMode, openErasedRecord);
  }

  OdResult getRecord(
    OdDbViewportTableRecord*& pRecord,
    OdDb::OpenMode openMode = OdDb::kForRead,
    bool openErasedRec = false) const;

  OdResult seek(OdDbObjectId id);
  OdResult seek(const OdDbViewportTableRecord* pRecord);

protected:
  OdDbViewportTableIterator();

  OdDbViewportTableIterator(
    OdDbSymbolTableIteratorImpl* pImpl);
};

typedef OdSmartPtr<OdDbViewportTableIterator> OdDbViewportTableIteratorPtr;

/** \details
    This class implements the ViewportTable, which represents tiled viewports in an OdDbDatabase instance.


    \remarks
    Do not derive from this class.
    
    <group OdDb_Classes>
*/
class TOOLKIT_EXPORT OdDbViewportTable: public OdDbAbstractViewTable
{
public:
  DWGMAP_DECLARE_MEMBERS(OdDbViewportTable);

  /** \details
    Client applications typically will not use this constructor, insofar as 
    this class is a base class.
  */
  OdDbViewportTable();
  virtual ~OdDbViewportTable();
  TD_USING(OdDbAbstractViewTable::getAt);
  OdResult getAt (
    const OdChar * recordName,
    OdDbViewportTableRecord*& pRec,
    OdDb::OpenMode openMode,
    bool openErasedRec = false) const;

  virtual OdDbSymbolTableIteratorPtr newIterator(
    bool atBeginning = true,
    bool skipDeleted = true) const;

  // 根据基类类似函数重新实现
  OdResult newIterator(
    OdDbViewportTableIterator*& pIterator,
    bool atBeginning = true,
    bool skipDeleted = true) const;

  /** \details
    Makes the specified viewport the active viewport of this ViewportTable object.

    \param viewportId [in]  Object ID of the active viewport.      
  */
  void SetActiveViewport(
    OdDbObjectId viewportId);

  /** \details
    Returns the active viewport of this ViewportTable object.
  */
  OdDbObjectId getActiveViewportId() const;

  /** \details
    Deletes the specified configuration from this ViewportTable object.
    
    \param configName [in]  Configuration name to delete.
  */
  void DeleteConfiguration(
    const OdString& configName);

  virtual OdDbObjectId add(ODSYSDEFNAME, OdDbSymbolTableRecord* pRecord);

  OdResult add(OdDbObjectId& recordId, OdDbViewportTableRecord* pRecord);

  OdResult add(OdDbViewportTableRecord* pRecord);

  OdResult dxfIn(
    OdDbDxfFiler* pFiler);

  OdResult subGetClassID(
    CLSID* pClsid) const;

  OdResult subClose();
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdDbTextStyleTable object pointers.
*/
typedef OdSmartPtr<OdDbViewportTable> OdDbViewportTablePtr;

#include "TD_PackPop.h"

#endif // _ODDBVIEWPORTTABLE_INCLUDED

