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

#ifndef __OD_DB_CAMERA__
#define __OD_DB_CAMERA__

#undef DBCAMERA_EXPORT
#ifdef DBCAMERA_EXPORTS
# define DBCAMERA_EXPORT OD_TOOLKIT_EXPORT
#else
# define DBCAMERA_EXPORT OD_TOOLKIT_IMPORT
#endif

#include "DbEntity.h"
#include "DynamicLinker.h"

#include "TD_PackPush.h"

/** \details
  <group OdDb_Classes>
*/
class OdDbViewTableRecord;
typedef OdSmartPtr<OdDbViewTableRecord> OdDbViewTableRecordPtr;

/** \details
    Corresponding C++ library: ACCAMERA

    <group OdDb_Classes>
*/
class DBCAMERA_EXPORT OdDbCamera : public OdDbEntity
{
public:
  ODDB_DECLARE_MEMBERS(OdDbCamera);

  OdDbCamera();

  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler);
  virtual OdResult dwgOutFields(OdDbDwgFiler* pFiler) const;
  virtual OdResult dxfInFields(OdDbDxfFiler* pFiler);
  virtual OdResult dxfOutFields(OdDbDxfFiler* pFiler) const;

  virtual OdResult subErase(bool erasing);
  virtual OdResult subOpen(OdDb::OpenMode openMode);
  virtual OdResult subClose();

  OdDbObjectId view() const;
  OdResult setView(const OdDbObjectId &viewId);

  // Some helpful methods for NDBRO editing (required for grip points implementation for example)
  // For internal use
  OdDbViewTableRecordPtr openView(OdDb::OpenMode openMode = OdDb::kForRead) const;
  // For internal use
  void updateView();

protected:

  virtual OdResult subTransformBy(const OdGeMatrix3d& xfm);

  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits);
  virtual OdBool subWorldDraw(OdGiWorldDraw* pWd);
  virtual void subViewportDraw(OdGiViewportDraw* pVd);

  virtual OdResult subGetClassID(CLSID* pClsid) const;

  virtual OdResult subGetGeomExtents(OdDbExtents& extents) const;

  virtual OdDbObjectPtr subDeepClone(OdDbIdMapping& ownerIdMap, OdDbObject*, bool bPrimary) const ODRX_OVERRIDE;
  virtual OdDbObjectPtr subWblockClone(OdDbIdMapping& ownerIdMap, OdDbObject*, bool bPrimary) const ODRX_OVERRIDE;

  virtual OdResult subDeepClone(OdDbObject* pOwnerObject, OdDbObject*& pClonedObject, OdDbIdMapping& idMap, OdBool isPrimary = kTrue) const;
  virtual OdResult subWblockClone(OdRxObject* pOwnerObject, OdDbObject*& pClonedObject,OdDbIdMapping& idMap, OdBool isPrimary = kTrue) const;

  virtual OdResult subHighlight(const OdDbFullSubentPath& subId = kNullSubent, const OdBool highlightAll = false) const;
  virtual OdResult subUnhighlight(const OdDbFullSubentPath& subId = kNullSubent, const OdBool highlightAll = false) const;
};

typedef OdSmartPtr<OdDbCamera> OdDbCameraPtr;

/** \details
  <group OdDb_Classes>
*/
class CameraModule : public OdRxModule {
protected:
  virtual void initApp();
  virtual void uninitApp();
public:
  virtual void UpdateViewTableRecordCamera(OdDbViewTableRecord *pVTR);
  virtual void InitialUpdateViewTableRecordCameras(OdDbDatabase *pDb);
};

typedef OdSmartPtr<CameraModule> CameraModulePtr;

inline void oddbUpdateViewTableRecordCamera(OdDbViewTableRecord *pVTR) {
  CameraModulePtr cammod(::odrxLoadApp("ACCAMERA"));
  if(cammod.get())
    cammod->UpdateViewTableRecordCamera(pVTR);

}

inline void oddbInitialUpdateViewTableRecordCameras(OdDbDatabase *pDb) {
  CameraModulePtr cammod(::odrxLoadApp("ACCAMERA"));
  if(cammod.get())
    cammod->InitialUpdateViewTableRecordCameras(pDb);
}

#include "TD_PackPop.h"

#endif // __OD_DB_CAMERA__
