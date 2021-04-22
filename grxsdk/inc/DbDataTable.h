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


#ifndef OD_DBDATATABLE_H
#define OD_DBDATATABLE_H

#include "TD_PackPush.h"
#include "RxObject.h"
#include "DbObject.h"

class OdDbDataCellImpl;
/** \details
    Corresponding C++ library: TD_Db 
    <group OdDb_Classes>
*/
class DBENT_EXPORT OdDbDataCell : public OdRxObject
{
public:
  enum CellType {
      kUnknown      = 0,
      kInteger      = 1,
      kDouble       = 2,
      kCharPtr      = 3,
      kPoint        = 4,
      kObjectId     = 5,
      kHardOwnerId  = 6,
      kSoftOwnerId  = 7,
      kHardPtrId    = 8,
      kSoftPtrId    = 9,
      kBool         = 10,
      kVector       = 11
  };
  ODDB_DECLARE_MEMBERS(OdDbDataCell);

  // Constructors
  
  OdDbDataCell();
  OdDbDataCell(const OdDbDataCell& rCell);
  OdDbDataCell(bool b);
  OdDbDataCell(int i);
  OdDbDataCell(double d);
  OdDbDataCell(const OdString& str);
  OdDbDataCell(const OdGePoint3d& point);
  OdDbDataCell(const OdGeVector3d& vec);
  OdDbDataCell(const OdDbObjectId& id);
  OdDbDataCell(const OdDbHardOwnershipId& id);
  OdDbDataCell(const OdDbSoftOwnershipId& id);
  OdDbDataCell(const OdDbHardPointerId&   id);
  OdDbDataCell(const OdDbSoftPointerId&   id);

  virtual ~OdDbDataCell();
  
  virtual void init();

  virtual OdDbDataCell& operator = (const OdDbDataCell &cell);
  virtual OdDbDataCell& operator = (bool b);
  virtual OdDbDataCell& operator = (int i);
  virtual OdDbDataCell& operator = (double d);
  virtual OdDbDataCell& operator = (const OdChar * pChar);
  virtual OdDbDataCell& operator = (const OdGePoint3d &pt);
  virtual OdDbDataCell& operator = (const OdGeVector3d &vec);
  virtual OdDbDataCell& operator = (const OdDbObjectId &id);
  virtual OdDbDataCell& operator = (const OdDbHardOwnershipId &hoId);
  virtual OdDbDataCell& operator = (const OdDbSoftOwnershipId &soId);
  virtual OdDbDataCell& operator = (const OdDbHardPointerId   &hpId);
  virtual OdDbDataCell& operator = (const OdDbSoftPointerId   &spId);

  virtual operator bool() const;
  virtual operator int() const;
  virtual operator double() const;
  virtual operator const OdChar *() const;
  virtual operator OdGePoint3d&()const;
  virtual operator OdGeVector3d&()const;
  virtual operator OdDbObjectId&() const;
  virtual operator OdDbHardOwnershipId&() const;
  virtual operator OdDbSoftOwnershipId&() const;
  virtual operator OdDbHardPointerId&() const;
  virtual operator OdDbSoftPointerId&() const;

  virtual void set(const OdDbDataCell& cell);
  virtual void set(bool b);
  virtual void set(OdInt32 i);
  virtual void set(double d);
  virtual void set(const OdString& str);
  virtual void set(const OdGePoint3d& pt);
  virtual void set(const OdGeVector3d& vec);
  virtual void set(const OdDbObjectId& id);
  virtual void set(const OdDbHardOwnershipId& id);
  virtual void set(const OdDbSoftOwnershipId& id);
  virtual void set(const OdDbHardPointerId& id);
  virtual void set(const OdDbSoftPointerId& id);

  virtual void get(OdDbDataCell& cell);
  virtual void get(bool& b);
  virtual void get(OdInt32& i);
  virtual void get(double& d);
  virtual void get(OdString& str);
  virtual void get(OdGePoint3d& pt);
  virtual void get(OdGeVector3d& vec);
  virtual void get(OdDbObjectId& id);
  virtual void get(OdDbHardOwnershipId& id);
  virtual void get(OdDbSoftOwnershipId& id);
  virtual void get(OdDbHardPointerId& id);
  virtual void get(OdDbSoftPointerId& id);

  virtual bool operator == (const OdDbDataCell &cell) const;
  virtual bool operator != (const OdDbDataCell &cell) const;

  virtual OdDbDataCell::CellType type() const;
  OdDbDataCell(OdDbDataCellImpl* pValImpl);

protected:
  friend class OdDbSystemInternals;
  OdDbDataCellImpl* m_pImpl;
};

typedef OdSmartPtr<OdDbDataCell> OdDbDataCellPtr;

typedef OdArray<OdDbDataCellPtr> OdDbDataCellArray; 

class OdDbDataColumnImpl;

/** \details
    Corresponding C++ library: TD_Db 
    <group OdDb_Classes>
*/
class DBENT_EXPORT OdDbDataColumn : public OdRxObject
{
public:
  ODDB_DECLARE_MEMBERS(OdDbDataColumn);
  OdDbDataColumn();
  OdDbDataColumn(const OdDbDataColumn& rCol);
  OdDbDataColumn(const OdDbDataCell::CellType type,
    const OdChar* pColName = NULL);

//  virtual ~OdDbDataColumn();

  virtual OdUInt32 physicalLength() const;
  virtual OdUInt32 growLength() const;

  virtual OdResult setPhysicalLength(OdUInt32 n);
  virtual OdResult setGrowLength(OdUInt32 n);

  virtual OdDbDataColumn& operator = (const OdDbDataColumn& col);

  virtual OdResult setColumnType(OdDbDataCell::CellType type);
  virtual OdDbDataCell::CellType columnType() const;

  virtual OdResult setColumnName(const OdChar* pName);
  virtual const OdChar* columnName() const;

  virtual OdDbDataCellPtr getCellAt(OdUInt32 index) const;
  virtual void setCellAt(OdUInt32 index, const OdDbDataCellPtr cell);

  virtual OdResult getCellAt(OdUInt32 index, OdDbDataCell& outCell) const;
  virtual OdResult setCellAt(OdUInt32 index, const OdDbDataCell& cell);
  virtual OdResult appendCell(const OdDbDataCell& cell);
  virtual OdResult insertCellAt(OdUInt32 index, const OdDbDataCell& cell);

  virtual void appendCell(const OdDbDataCellPtr cell);

  virtual void insertCellAt(OdUInt32 index, const OdDbDataCellPtr& cell);
  virtual OdResult   removeCellAt(OdUInt32 index);
  virtual OdInt32  getIndexAtCell(const OdDbDataCellPtr& cell) const;
  virtual OdResult getIndexAtCell(const OdDbDataCell& cell, OdUInt32& index) const;

  virtual OdUInt32 numCells() const;

  OdDbDataColumn(OdDbDataColumnImpl* m_pImpl);

protected:
  friend class OdDbSystemInternals;
  OdDbDataColumnImpl* m_pImpl;
};

typedef OdSmartPtr<OdDbDataColumn> OdDbDataColumnPtr;

class OdDbDataTableImpl;

/** \details
    Corresponding C++ library: TD_Db 
    <group OdDb_Classes>
*/
class DBENT_EXPORT OdDbDataTable : public OdDbObject
{
public:
  ODDB_DECLARE_MEMBERS(OdDbDataTable);
  
  OdDbDataTable(void);
  
  virtual OdDbDataTable& operator = (const OdDbDataTable& table);

  virtual OdUInt32 numColumns() const;
  virtual OdUInt32 numRows() const;

  virtual OdResult setNumRowsPhysicalSize(OdUInt32 n);
  virtual OdResult setNumRowsGrowSize(OdUInt32 n);

  virtual OdUInt32 numRowsPhysicalSize() const;
  virtual OdUInt32 numRowsGrowSize() const;

  virtual OdResult setNumColsPhysicalSize(OdUInt32 n);
  virtual OdResult setNumColsGrowSize(OdUInt32 n);

  virtual OdUInt32 numColsPhysicalSize() const;
  virtual OdUInt32 numColsGrowSize() const;
  
  virtual const OdChar* tableName() const;
  virtual OdResult setTableName(const OdChar* pName);

  virtual OdDbDataColumnPtr getColumnAt(OdUInt32 index) const;
  virtual OdResult getColumnAt(OdUInt32 index, const OdDbDataColumn*& pCol) const;
  virtual OdString columnNameAt(OdUInt32 index) const;

  virtual OdResult getColumnNameAt(OdUInt32 index, OdChar *& pName) const;
  virtual OdResult getColumnTypeAt(OdUInt32 index, OdDbDataCell::CellType& type) const;
  virtual OdResult getColumnIndexAtName(const OdChar * pName, OdUInt32& index) const;

  virtual  OdDbDataCell::CellType columnTypeAt(OdUInt32 index) const;
  virtual  OdInt32 columnIndexAtName (const OdString& name) const;

  virtual  OdResult appendColumn(
      OdDbDataCell::CellType type, const OdChar* colName = NULL);
  virtual  OdResult insertColumnAt(OdUInt32 index,
      OdDbDataCell::CellType type, const OdChar* colName = NULL);
  virtual  OdResult removeColumnAt(OdUInt32 index);

  virtual  OdResult getRowAt(OdUInt32 index,
      OdDbDataCellArray& outRow) const;
  virtual  OdResult setRowAt(OdUInt32 index,
      const OdDbDataCellArray& row, bool bValidate = true);

  virtual  OdResult appendRow(
      const OdDbDataCellArray& row, bool bValidate = true);

  virtual  OdResult insertRowAt(OdUInt32 index,
      const OdDbDataCellArray& row, bool bValidate = true);

  virtual  OdResult removeRowAt(OdUInt32 index);

  virtual  OdDbDataCellPtr getCellAt(OdUInt32 row, OdUInt32 col) const;
  virtual OdResult getCellAt(OdUInt32 row, OdUInt32 col, OdDbDataCell& outCell) const;
  virtual  void setCellAt(OdUInt32 row, OdUInt32 col,
      const OdDbDataCellPtr& cell);
  virtual OdResult setCellAt(OdUInt32 row, OdUInt32 col, const OdDbDataCell& cell);

  //********************************************************************
  // Overridden methods from OdDbObject
  //********************************************************************
  //

  virtual OdResult  dwgInFields(
    OdDbDwgFiler* pFiler);
  virtual OdResult dwgOutFields(
    OdDbDwgFiler* pFiler) const;
  virtual OdResult  dxfInFields(
    OdDbDxfFiler* pFiler);
  virtual OdResult dxfOutFields(
    OdDbDxfFiler* pFiler) const;

  // virtual   audit(OdDbAuditInfo* pAuditInfo);
};

typedef OdSmartPtr<OdDbDataTable> OdDbDataTablePtr;

#include "TD_PackPop.h"

#endif
