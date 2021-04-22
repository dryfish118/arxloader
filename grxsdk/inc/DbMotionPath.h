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

#ifndef _OD_DBMOTIONPATH_H_INCLUDED_
#define _OD_DBMOTIONPATH_H_INCLUDED_

#include "DbObject.h"

#include "TD_PackPush.h"

/** \details
    Corresponding C++ library: SCENEOE

    <group OdDb_Classes>
*/
const OdChar ODDB_MOTIONPATH_DICTIONARY[] = __OD_T("ACAD_MOTION");

SCENEOE_EXPORT OdResult gcdbGetMotionPathDictionary(OdDbDatabase* pDb, OdDbDictionary*& pDict, OdDb::OpenMode mode, bool createIfNonExist);
SCENEOE_EXPORT OdResult gcdbGetMotionPathDictionary(OdDbDatabase* pDb, OdDbDictionary*& pDict, OdDb::OpenMode mode);

class OdDbImpMotionPath;

class SCENEOE_EXPORT OdDbMotionPath : public OdDbObject
{
  public:
    ODDB_DECLARE_MEMBERS(OdDbMotionPath);

    OdDbMotionPath();
    virtual ~OdDbMotionPath();

    OdResult setCameraPath(const OdDbObjectId &pathId);
    OdDbObjectId cameraPath() const;

    OdResult setTargetPath(const OdDbObjectId &pathId);
    OdDbObjectId targetPath() const;

    OdResult setViewTableRecordId(const OdDbObjectId &viewId);
    OdDbObjectId viewTableRecordId() const;

    OdResult setFrames(OdUInt32 nFrames);
    OdUInt32 frames() const;

    OdResult setFrameRate(OdUInt32 nRate);
    OdUInt32 frameRate() const;

    OdResult setCornerDecel(bool bCornerDecel);
    bool cornerDecel() const;

    OdDbImpMotionPath* imp() const;

    virtual OdResult dwgInFields(OdDbDwgFiler* pFiler);
    virtual OdResult dwgOutFields(OdDbDwgFiler* pFiler) const;
    virtual OdResult dxfInFields(OdDbDxfFiler* pFiler);
    virtual OdResult dxfOutFields(OdDbDxfFiler* pFiler) const;
};

typedef OdSmartPtr<OdDbMotionPath> OdDbMotionPathPtr;

SCENEOE_EXPORT OdDbObjectId oddbGetMotionPathDictionaryId(OdDbDatabase* pDb, bool createIfNotFound = false);
SCENEOE_EXPORT OdDbDictionaryPtr oddbGetMotionPathDictionary(OdDbDatabase* pDb, OdDb::OpenMode mode, bool createIfNotFound = false);

#include "TD_PackPop.h"

#endif // _OD_DBMOTIONPATH_H_INCLUDED_
