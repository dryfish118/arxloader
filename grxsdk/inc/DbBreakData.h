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

#ifndef _DbBreakData_h_Included_
#define _DbBreakData_h_Included_

#include "DbObject.h"
#include "OdArray.h"
#include "SmartPtr.h"
#include "DbDimAssoc.h"

class OdDbBreakPointRef;
typedef OdSmartPtr<OdDbBreakPointRef> OdDbBreakPointRefPtr;
typedef OdArray<OdDbBreakPointRefPtr> OdDbBreakPointRefPtrArray;

/** \details 
  This class represents break data for dimensions.

    <group OdDb_Classes>
*/
class DBDIM_EXPORT OdDbBreakData : public OdDbObject
{
public:
  ODDB_DECLARE_MEMBERS(OdDbBreakData);

  OdDbBreakData();
  OdDbObjectId dimObjId() const;
  OdResult setDimObjId(const OdDbObjectId& dimId);

  OdResult addBreakPointRef(OdDbBreakPointRef* ptRef);
  OdResult getBreakPointRef(int lineIndex, OdArray<OdDbBreakPointRef*>& ptRefs) const;
  OdResult getBreakPointRef(OdArray<OdDbBreakPointRef*>& ptRefs) const;
  OdResult deleteAllBreakPointRefs();
  OdResult removeAssociativity(bool force = true);
  OdResult postToDb(OdDbObjectId& breakObjId);
  OdResult eraseFromDb(); 

  virtual OdResult dwgInFields (OdDbDwgFiler*);
  virtual OdResult dwgOutFields(OdDbDwgFiler*) const;
  virtual OdResult dxfInFields (OdDbDxfFiler*);
  virtual OdResult dxfOutFields(OdDbDxfFiler*) const;
  virtual void modifiedGraphics(const OdDbEntity* pEnt);
  virtual void erased(const OdDbObject* pObj, bool erasing);
  virtual void modified(const OdDbObject* pObj);

  OdResult updateAssociativity(const OdDbObjectIdArray& ids, int cmdType);
};

typedef OdSmartPtr<OdDbBreakData> OdDbBreakDataPtr;

/** \details 
  This class represents break points for dimensions.
    
    <group OdDb_Classes>
*/
class DBDIM_EXPORT OdDbBreakPointRef : public OdDbObject
{
public:
  ODDB_DECLARE_MEMBERS(OdDbBreakPointRef);

  enum BreakPointType { 
    kDynamic           = 0,
    kStatic            = 1,
    kStatic2Point      = 2
  };

  OdDbBreakPointRef();
  OdDbBreakPointRef::BreakPointType pointType() const;
  OdResult setPointType(OdDbBreakPointRef::BreakPointType newVal);
  OdInt32 lineIndex() const;
  OdResult setLineIndex(OdInt32 index);
  OdGePoint3d breakPoint() const;
  OdResult setBreakPoint(const OdGePoint3d& pt);
  OdGePoint3d breakPoint2() const;
  OdResult setBreakPoint2(const OdGePoint3d& pt);
  void getBreakPointId(OdDbXrefFullSubentPath& idPath) const;
  OdResult getBreakPointId(OdDbFullSubentPath& idPath) const;
  void setBreakPointId(const OdDbXrefFullSubentPath& idPath);
  OdResult setBreakPointId(const OdDbFullSubentPath& idPath);
  OdDbEntityPtr subentPtr() const;
  OdResult intersectWith(const OdDbEntity* pEnt, OdGePoint3dArray& points, OdGePoint3dArray& textBoxPts);

  virtual OdResult dwgInFields (OdDbDwgFiler*);
  virtual OdResult dwgOutFields(OdDbDwgFiler*) const;
  virtual OdResult dxfInFields (OdDbDxfFiler*);
  virtual OdResult dxfOutFields(OdDbDxfFiler*) const;
};

DBDIM_EXPORT OdResult oddbGetBreakSubentIndex(OdDbEntity* pEnt,
                                  const OdGePoint3d& pickPt,
                                  const OdGeVector3d& viewDir,
                                  int& subentIndex,
                                  OdGePoint3d& ptOnEnt,
                                  const OdGeTol& tol = OdGeContext::gTol);

#endif

