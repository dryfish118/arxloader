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




#ifndef _ODDBABSTRACTVIEWTABLE_INCLUDED
#define _ODDBABSTRACTVIEWTABLE_INCLUDED

#include "DbSymbolTable.h"

class OdDbAbstractViewTableRecord;

/** Gcad(Add): ���� DD ��ȱ�ٵ� OdDbAbstractViewTableIterator ��
  ����ʵ�ּ��ݵ� getRecord() ���麯��
*/
class TOOLKIT_EXPORT OdDbAbstractViewTableIterator : public OdDbSymbolTableIterator
{
public:
  ODRX_DECLARE_MEMBERS(OdDbAbstractViewTableIterator);

  virtual OdDbSymbolTableRecordPtr getRecord(
    OdDb::OpenMode openMode = OdDb::kForRead,
    bool openErasedRecord = false) const
  {
    return OdDbSymbolTableIterator::getRecord(openMode, openErasedRecord);
  }

  OdResult getRecord(
    OdDbAbstractViewTableRecord*& pRecord,
    OdDb::OpenMode openMode = OdDb::kForRead,
    bool openErasedRec = false) const;

  OdResult seek(OdDbObjectId id);
  OdResult seek(const OdDbAbstractViewTableRecord* pRecord);

protected:
  OdDbAbstractViewTableIterator();

  OdDbAbstractViewTableIterator(
    OdDbSymbolTableIteratorImpl* pImpl);
};

typedef OdSmartPtr<OdDbAbstractViewTableIterator> OdDbAbstractViewTableIteratorPtr;

/** \details
    This class is the base class for OdDbViewTable and OdDbViewportTable.


    <group OdDb_Classes> 
*/
class TOOLKIT_EXPORT OdDbAbstractViewTable : public OdDbSymbolTable
{
public:

  ODDB_DECLARE_MEMBERS(OdDbAbstractViewTable);

  /** \details
    Client applications typically do not use this constructor, insofar as 
    this class is a base class.
  */
  OdDbAbstractViewTable();

  virtual ~OdDbAbstractViewTable();

  TD_USING(OdDbSymbolTable::getAt);

  OdResult getAt (
    const OdChar * recordName,
    OdDbAbstractViewTableRecord*& pRec,
    OdDb::OpenMode openMode,
    bool openErasedRec = false) const;
//  void getAt(const OdChar* entryName, OdDbAbstractViewTableRecord** pRec,
//    OdDb::OpenMode openMode, bool openErasedRec = false) const;

//  OdDbObjectId getAt(const OdChar* entryName, bool getErasedRecord = false) const;

//  bool has(const OdChar* name) const;
//  bool has(const OdDbObjectId& id) const;

  OdResult newIterator(OdDbAbstractViewTableIterator*& pIterator,bool atBeginning = true, bool skipDeleted = true) const;

  virtual OdDbObjectId add(ODSYSDEFNAME, OdDbSymbolTableRecord* pRecord);

  OdResult add(OdDbObjectId& recordId, OdDbAbstractViewTableRecord* pRecord);

  OdResult add(OdDbAbstractViewTableRecord* pRecord);

};

#endif // _ODDBABSTRACTVIEWTABLE_INCLUDED

