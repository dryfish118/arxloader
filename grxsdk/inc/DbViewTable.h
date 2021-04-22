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




#ifndef _ODDBVIEWTABLE_INCLUDED
#define _ODDBVIEWTABLE_INCLUDED

#include "TD_PackPush.h"

#include "DbAbstractViewTable.h"
#include "DwgDeclareMembers.h"

class OdDbViewTableRecord;
class OdDbViewTableIterator;

class TOOLKIT_EXPORT OdDbViewTableIterator : public OdDbAbstractViewTableIterator
{
public:
  ODRX_DECLARE_MEMBERS(OdDbViewTableIterator);

  virtual OdDbSymbolTableRecordPtr getRecord(
    OdDb::OpenMode openMode = OdDb::kForRead,
    bool openErasedRecord = false) const
  {
    return OdDbAbstractViewTableIterator::getRecord(openMode, openErasedRecord);
  }

  OdResult getRecord(
    OdDbViewTableRecord*& pRecord,
    OdDb::OpenMode openMode = OdDb::kForRead,
    bool openErasedRec = false) const;

  OdResult seek(OdDbObjectId id);
  OdResult seek(const OdDbViewTableRecord* pRecord);

protected:
  OdDbViewTableIterator();

  OdDbViewTableIterator(
    OdDbSymbolTableIteratorImpl* pImpl);
};

typedef OdSmartPtr<OdDbViewTableIterator> OdDbViewTableIteratorPtr;

/** \details
    This class implements the ViewTable, which represents stored views in an OdDbDatabase instance.


    <group OdDb_Classes>
*/
class TOOLKIT_EXPORT OdDbViewTable: public OdDbAbstractViewTable
{
public:
  DWGMAP_DECLARE_MEMBERS(OdDbViewTable);

  /** \details
    Client applications typically will not use this constructor, insofar as 
    this class is a base class.
  */
  OdDbViewTable();
  virtual ~OdDbViewTable();

  TD_USING(OdDbAbstractViewTable::getAt);
  OdResult getAt (
    const OdChar * recordName,
    OdDbViewTableRecord*& pRec,
    OdDb::OpenMode openMode,
    bool openErasedRec = false) const;
	
  virtual OdDbSymbolTableIteratorPtr newIterator(
    bool atBeginning = true,
    bool skipDeleted = true) const;

  // 根据基类类似函数重新实现
  OdResult newIterator(
    OdDbViewTableIterator*& pIterator,
    bool atBeginning = true,
    bool skipDeleted = true) const;

  virtual OdDbObjectId add(ODSYSDEFNAME, OdDbSymbolTableRecord* pRecord);

  OdResult add(OdDbObjectId& recordId, OdDbViewTableRecord* pRecord);

  OdResult add(OdDbViewTableRecord* pRecord);

  virtual OdResult subGetClassID(
    CLSID* pClsid) const;
};
/** \details
    This template class is a specialization of the OdSmartPtr class for OdDbViewTable object pointers.
*/
typedef OdSmartPtr<OdDbViewTable> OdDbViewTablePtr;

#include "TD_PackPop.h"

#endif // _ODDBVIEWTABLE_INCLUDED

