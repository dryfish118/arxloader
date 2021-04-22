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




#ifndef OD_DBDIMASSOC_H
#define OD_DBDIMASSOC_H

#include "TD_PackPush.h"

#include "DbSubentId.h"
#include "DbHandle.h"
#include "DbObject.h"
#include "grx/gsoft.h"

class OdDbDwgFiler;
class OdDbDxfFiler;
class OdGePoint3d;
class OdDbIdMapping;
class OdDbRotatedDimension;
class OdDbRadialDimension;
class OdDbRadialDimensionLarge; 
class OdDbOrdinateDimension;
class OdDbLeader;
class OdDbMLeader;
class OdDbAlignedDimension;
class OdDbDiametricDimension;
class OdDb2LineAngularDimension;
class OdDb3PointAngularDimension;
class OdDbArcDimension;

/** \details
    This class uniquely defines Xref subentities within an OdDbDatabase instance.  

    \remarks
    Each OdDbXrefFullSubentPath object consists of a OdDbSubentId object,
    an ordered array of Object IDs, and an ordered array of entity handles. 
    The SubentId consists the index and subentType
    of the object. The array of Object IDs, and the array of handles, define the path to the 
    subentity from the outermost entity (in PaperSpace or ModelSpace) 
    to the entity containing the subentity.
    
    Corresponding C++ library: TD_Db

    <group OdDb_Classes>
*/
class DBENT_EXPORT OdDbXrefFullSubentPath : public OdDbFullSubentPath
{
public:
  /** \details
    Returns a reference to the embedded OdHandleArray object in this XrefFullSubentPath object.
    
    \param objectIds [out]  Receives the array reference.
  */
  OdHandleArray& xrefObjHandles();
  const OdHandleArray& xrefObjHandles()const;

  /** \details
    Reads the .dwg file format data of this object from the specified file.
       
    \param pFiler [in]  Pointer to the filer from which the data are to be read.
  */
  void dwgIn(OdDbDwgFiler* pFiler);

  /** \details
    Writes the .dwg file format data of this object to the specified filer. 
    
    \param pFiler [in]  Pointer to the filer to which the data are to be written.
    
  */
  void dwgOut(OdDbDwgFiler* pFiler) const;

  /** \details
    Writes the DXF format data of this object to the specified filer. 
    
    \param pFiler [in]  Pointer to the filer to which the data are to be written.
    \param groupCodeOffset [in]  Group code offset.
  */
  void dxfOut(OdDbDxfFiler* pFiler, OdInt groupCodeOffset = 0) const;

  OdDbXrefFullSubentPath& operator =(const OdDbFullSubentPath& fullSubentPath)
  {
    //m_XrefObjHandles.clear();
    OdDbBaseFullSubentPath::operator=(fullSubentPath);
    return *this;
  }
private:
  OdHandleArray m_XrefObjHandles;
};

class OdDbOsnapPointRef;
class OdDbViewport;
/** \details
    This template class is a specialization of the OdSmartPtr class for OdDbOsnapPointRef object pointers.
*/
typedef OdSmartPtr<OdDbOsnapPointRef> OdDbOsnapPointRefPtr;
//typedef OdArray<OdDbFullSubentPath> OdDbFullSubentPathArray;

typedef OdArray<OdDbHandle, OdObjectsAllocator<OdDbHandle> > OdDbHandleArrayPtRef;
/** \details
    This class defines a point reference between a dimension and
	its corresponding object.

    Corresponding C++ library: TD_Db
    <group OdDb_Classes>
*/
class DBDIM_EXPORT OdDbPointRef : public OdRxObject
{
public:
  enum OsnapType { 
    kOsnapNone         = 0,
    kOsnapEnd          = 1,
    kOsnapMid          = 2,
    kOsnapCen          = 3,
    kOsnapNode         = 4,
    kOsnapQuad         = 5, 
    kOsnapInt          = 6,
    kOsnapIns          = 7,
    kOsnapPerp         = 8,
    kOsnapTan          = 9,
    kOsnapNear         = 10,
    kOsnapApint        = 11,
    kOsnapStart        = 13
  };
  ODRX_DECLARE_MEMBERS(OdDbPointRef);
  virtual OdDbPointRef& operator=(const OdDbPointRef& src);

  virtual OdResult evalPoint(OdGePoint3d& pnt_wcs) = 0;
  virtual OdResult getEntities(OdDbFullSubentPathArray& ents, bool getLastPtRef = true) const = 0;
  virtual bool isGeomErased() const = 0;
  virtual bool isXrefObj(OdDbObjectIdArray& ids1, OdDbObjectIdArray& ids2, bool isMainObj = true) const = 0;
  virtual OdResult updateXrefSubentPath() = 0;
  virtual OdResult updateSubentPath(OdDbIdMapping& idMap) = 0;

  virtual OdResult dwgOutFields(OdDbDwgFiler* filer) const = 0;
  virtual OdResult dwgOutFields(OdDbDwgFiler* filer, OdDbDatabase* pDb) const = 0;
  virtual OdResult dwgInFields(OdDbDwgFiler* filer, OdDbDatabase* pDb) = 0;

  virtual OdResult dxfOutFields(OdDbDxfFiler* filer, OdDbDatabase* pDb) const = 0;
  virtual OdResult dxfInFields(OdDbDxfFiler* filer,  OdDbDatabase* pDb) = 0;
  virtual OdResult subErase(OdBool erasing)
  {
    GSOFT_UNREFED_PARAM(erasing);
    return eOk;
  }
  virtual OdResult wblockClone(OdRxObject* pOwnerObject,
    OdDbObject*& pClonedObject,
    OdDbIdMapping& /*idMap*/,
    OdBool isPrimary = kTrue) const 
  {
    GSOFT_UNREFED_PARAM(pOwnerObject);
    GSOFT_UNREFED_PARAM(pClonedObject);
    GSOFT_UNREFED_PARAM(isPrimary);

    return eOk;
  }
  virtual OdResult deepClone(OdRxObject* pOwnerObject,
                              OdDbObject*& pClonedObject,
                              OdDbIdMapping& /*idMap*/,
                              OdBool isPrimary = kTrue) const 
  {
    GSOFT_UNREFED_PARAM(pOwnerObject);
    GSOFT_UNREFED_PARAM(pClonedObject);
    GSOFT_UNREFED_PARAM(isPrimary);

    return eOk;
  }

  virtual void dwgInFields(OdDbDwgFiler* filer) = 0;
  virtual OdResult dxfOutFields(OdDbDxfFiler* filer) const = 0;
  virtual OdResult dxfInFields(OdDbDxfFiler* filer) = 0;

  virtual void updateDueToMirror(bool inMirror = false) = 0;

/** \details
  Calculates transformation combined from OdDbViewport's MS2PS and BlockReference transformations
*/
  static bool calcTransform(const OdDbObjectIdArray& ids, OdGeMatrix3d& A_Ecs2Wcs);

  /** \details
  Returns matrix to convert MS coordinates to PS for given OdDbViewport entity
  */
  static OdGeMatrix3d mswcsToPswcs(const OdDbViewport* pVPort);

  static OdResult  dwgInFields(OdDbDwgFiler* filer, OdDbDatabase* pDb, OdDbPointRef*& pPointRef);
  static OdResult  dwgOutFields(OdDbDwgFiler* filer, OdDbDatabase* pDb, const OdDbPointRef* pPointRef);
  static OdResult  dxfInFields(OdDbDxfFiler* filer, OdDbDatabase* pDb, OdDbPointRef*& pPointRef);
  static OdResult  dxfOutFields(OdDbDxfFiler* filer, OdDbDatabase* pDb, const OdDbPointRef* pPointRef);
  static OdDbEntityPtr subentPtr(const OdDbFullSubentPath& objPath, bool& isCloned, bool& reverseArc, bool& isStandAloneArc);
  static OdGeMatrix3d wcsToDcsMatrix(const OdDbViewport* pVPort);
};

/** \details

    <group OdDb_Classes>
*/
class DBDIM_EXPORT OdDbOsnapPointRef : public OdDbPointRef
{
public:
  OdDbOsnapPointRef();
  virtual ~OdDbOsnapPointRef();

  OdDbOsnapPointRef(const OdGePoint3d& refPt);

  OdDbOsnapPointRef(OdDbPointRef::OsnapType osnapType, 
                    const OdDbFullSubentPath *objPath, 
                    const OdDbFullSubentPath *intObjPath = NULL,
                    const OdGePoint3d *refPt = NULL,
                    OdDbPointRef* lastPtRef = NULL);

  OdDbOsnapPointRef(const OdDbOsnapPointRef& src);

  virtual OdDbPointRef& operator= (const OdDbPointRef& src);

  virtual OdResult subErase(OdBool erasing) { return eOk; }

  OdDbOsnapPointRef& operator= (const OdDbOsnapPointRef& src);

  ODRX_DECLARE_MEMBERS(OdDbOsnapPointRef);

  /** \details
    Returns the object snap mode for this OsnapPointRef object.
    \remarks
    osnapMode() returns one of the following:
    
    <table>
    Name                      Value   Description 
    OdDb::kOsModeEnd          1       End Point
    OdDb::kOsModeMid          2       Mid Point
    OdDb::kOsModeCen          3       Center
    OdDb::kOsModeNode         4       Node
    OdDb::kOsModeQuad         5       Quadrant
    OdDb::kOsModeIntersec     6       Intersection
    OdDb::kOsModeIns          7       Insertion point
    OdDb::kOsModePerp         8       Perpendicular
    OdDb::kOsModeTan          9       Tangent
    OdDb::kOsModeNear         10      Nearest
    OdDb::kOsModeApint        11      Apparent intersection
    OdDb::kOsModePar          12      Parallel
    OdDb::kOsModeStart        13      Start Point 
    </table>
 
  */
  OdDbPointRef::OsnapType osnapType() const;
  /** \details
    Sets the object snap mode for this OsnapPointRef object.
 
    \remarks
    osnapMode must be one of the following:
    
    <table>
    Name                      Value   Description 
    OdDb::kOsModeEnd          1       End Point
    OdDb::kOsModeMid          2       Mid Point
    OdDb::kOsModeCen          3       Center
    OdDb::kOsModeNode         4       Node
    OdDb::kOsModeQuad         5       Quadrant
    OdDb::kOsModeIntersec     6       Intersection
    OdDb::kOsModeIns          7       Insertion point
    OdDb::kOsModePerp         8       Perpendicular
    OdDb::kOsModeTan          9       Tangent
    OdDb::kOsModeNear         10      Nearest
    OdDb::kOsModeApint        11      Apparent intersection
    OdDb::kOsModePar          12      Parallel
    OdDb::kOsModeStart        13      Start Point
    </table>
  */
  OdResult setOsnapType(OdDbPointRef::OsnapType osnapMode);

  /** \details
    Returns a reference to the OdDbXrefFullSubentPath of the main entity for the OsnapPointRef object. 
  */
  OdDbXrefFullSubentPath& mainEntity();
  /** \details
    Returns a reference to the OdDbXrefFullSubentPath of the intersecting entity for the OsnapPointRef object. 
  */
  OdDbXrefFullSubentPath& intersectEntity();

  OdResult getIdPath(OdDbFullSubentPath& idPath) const;
  OdResult setIdPath(const OdDbFullSubentPath& idPath);

  OdResult getIntIdPath(OdDbFullSubentPath& intIdPath) const;
  OdResult setIntIdPath(const OdDbFullSubentPath& intIdPath);

  /** \details
    Returns the near Osnap value for this OsnapPointRef object.
  */
  double nearPointParam() const;

  /** \details
    Returns the near Osnap value for this OsnapPointRef object.
    \param nearOsnap [in]  Near Osnap value.
  */
  OdResult setNearPointParam(double nearOsnap);

  /** \details
    Returns a reference to the Osnap point for this OsnapPointRef object.
  */
  OdGePoint3d point() const;
  OdResult setPoint(const OdGePoint3d& pt);

  /** \details
    Returns the last OsnapPointRef for this OsnapPointRef object.
  */
  const OdDbOsnapPointRef* lastPointRef(ODSYSDEF) const;
  OdDbPointRef*      lastPointRef() const;
  
  /** \details
    Returns the last OsnapPointRef for this OsnapPointRef object.
  */
  OdDbOsnapPointRef* lastPointRef();

  /** \details
    Sets the last OsnapPointRef for this OsnapPointRef object.
    \param pOsnapPointRef [in]  Pointer to the last OsnapPointRef object.
  */
  OdResult setLastPointRef(OdDbOsnapPointRefPtr pOsnapPointRef);

  virtual bool isGeomErased() const;
  virtual bool isXrefObj(OdDbObjectIdArray& ids1, OdDbObjectIdArray& ids2, bool isMainObj = true) const;
  virtual OdResult updateXrefSubentPath();
  virtual OdResult updateSubentPath(OdDbIdMapping& idMap);
  virtual OdResult evalPoint(OdGePoint3d &pt);

  TOOLKIT_EXPORT OdResult  evalPoint(OdDbPointRef::OsnapType ospType, const OdGePoint3d& lastPt, OdGePoint3d &pt);
  virtual OdResult getEntities(OdDbFullSubentPathArray& ents, bool getLastPtRef = true) const;
  virtual void updateDueToMirror(bool inMirror = false);

  OdResult getXrefHandles(OdHandleArray& xrefHandles) const;
  OdResult setXrefHandles(const OdHandleArray& xrefHandles);
  OdResult getXrefIntHandles(OdHandleArray& xrefHandles) const;
  OdResult setXrefIntHandles(const OdHandleArray& xrefHandles);

  /** \details
    Reads the .dwg file format data of this object from the specified file.
       
    \param pFiler [in]  Pointer to the filer from which the data are to be read.
  */
  void dwgInFields(OdDbDwgFiler* pFiler);
  /** \details
    Writes the .dwg file format data of this object to the specified filer. 
    
    \param pFiler [in]  Pointer to the filer to which the data are to be written.
  */
  OdResult dwgOutFields(OdDbDwgFiler* pFiler) const;

  OdResult dwgOutFields(OdDbDwgFiler* filer, OdDbDatabase* pDb) const;
  OdResult dwgInFields(OdDbDwgFiler* filer, OdDbDatabase* pDb);

  OdResult dxfOutFields(OdDbDxfFiler* filer, OdDbDatabase* pDb) const;
  OdResult dxfInFields(OdDbDxfFiler* filer, OdDbDatabase* pDb);


  /** \details
    Writes the DXF format data of this object to the specified filer. 
    
    \param pFiler [in]  Pointer to the filer to which the data are to be written.
  */
  OdResult dxfOutFields(OdDbDxfFiler* pFiler) const;
  OdResult dxfInFields(OdDbDxfFiler* filer);
protected:
  OdGePoint3d        nearPoint();
  double             findNearPointParam(const OdGePoint3d& pt) const;
  bool               getEllipseParams(double& sP, double& eP) const;
  bool               isTransSpatial(bool isMainObj = true) const;

  OdResult  evalPointGuts(OdDbPointRef::OsnapType ospType,
                          const OdGePoint3d& pickPt,
                          const OdGePoint3d& lastPt,
                          OdGePoint3d &pt);
  OdResult  getIntPoints(const OdDbEntity* pEnt,
                          const OdDbEntity* pIntEnt,
                          OdDb::Intersect intType,
                          OdGePoint3dArray& intPts,
                          int gsMarker1 = 0,
                          int gsMarker2 = 0) const;
  OdResult  updateSubentPathGuts(OdDbFullSubentPath& path, OdDbIdMapping&      idMap);
private:
  OdDbPointRef::OsnapType m_OsnapMode;
  OdDbXrefFullSubentPath m_MainEntity;
  OdDbXrefFullSubentPath m_IntersectEntity;
  double                 m_dNearOsnap;
  OdGePoint3d            m_OsnapPoint;
  OdDbOsnapPointRefPtr   m_pLastPointRef;
  bool                   m_bUpdateDueToMirror;
};

/** \details
    This class represents Associative Dimension objects in an OdDbDatabase instance.

    Corresponding C++ library: TD_Db
    
    <group OdDb_Classes>
*/
class DBDIM_EXPORT OdDbDimAssoc : public OdDbObject
{
public:
  ODDB_DECLARE_MEMBERS(OdDbDimAssoc);

  OdDbDimAssoc();

  enum { kMaxPointRefs = 4 };
  
  enum PointType 
  {
    kXline1Point          = 0,
    kXline2Point          = 1,
    kOriginPoint          = 0,
    kDefiningPoint        = 1,
    kXline1Start          = 0,
    kXline1End            = 1,
    kXline2Start          = 2,
    kXline2End            = 3,
    kVertexPoint          = 2,
    kChordPoint           = 0,
    kCenterPoint          = 1,
    kFarChordPoint        = 1,
    kOverrideCenterPoint  = 2,
    kAngLineStart         = 2,
    kJogPoint             = 3,
    kAngLineEnd           = 3,
    kLeaderPoint          = 0
  };

  enum RotatedDimType
  {
    kUnknown       = 0,
    kParallel      = 1,
    kPerpendicular = 2
  };

  enum AssocFlags 
  {
    kFirstPointRef     = (1<<0),
    kSecondPointRef    = (1<<1),
    kThirdPointRef     = (1<<2),
    kFourthPointRef    = (1<<3)
  };
  
  enum
  {
    kPointAmount = 4
  };

  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler) ODRX_OVERRIDE;
  virtual OdResult dwgOutFields(OdDbDwgFiler* pFiler) const ODRX_OVERRIDE;
  virtual OdResult dxfInFields(OdDbDxfFiler* pFiler) ODRX_OVERRIDE;
  virtual OdResult dxfOutFields(OdDbDxfFiler* pFiler) const ODRX_OVERRIDE;

  /** \details
    Returns the Object ID of the Dimension entity associated with this Associative Dimension object (DXF 330).
  */
  OdDbObjectId dimObjId() const;

  /** \details
    Sets the Object ID of the Dimension entity associated with this Associative Dimension object (DXF 330).
    \param dimId [in]  Dimension Object ID.
  */
  OdResult setDimObjId(const OdDbObjectId& dimId);

  /** \details
    Returns the associativity flag of this Associative Dimension object (DXF 90).
  */
  OdInt32 assocFlag() const;

  /** \details
    Returns the associativity flag of the specified Osnap Point Reference for this Associative Dimension object.
  */
  bool assocFlag(int pointIndex) const;

  void setAssocFlag(int assocFlag);
  // Sets the index of point reference being used and establishes or clears the association flag. 
  OdResult setAssocFlag(int pointIndex, bool flagValue);

  /** \details
    Returns the specified Osnap Point Reference for this Associative Dimension object.
    
    \param pointIndex [in]  Point index. The value should be 0, 1, 2, 3 or from the PointType enum 
    
    \remarks
    pointIndex must be one of the following:
   
  */
  OdDbOsnapPointRefPtr pointRef(int pointIndex) const;

  /** \details
    Sets the specified Osnap Point Reference for this Associative Dimension object.
    
    \param pointIndex [in]  Point index. The value should be 0, 1, 2, 3 or from the PointType enum 
    \param pOsnapPointRef [in]  SmartPointer to the Osnap Point Reference.
  */
  OdResult setPointRef(int pointIndex, OdDbOsnapPointRefPtr pOsnapPointRef);

  /** \details
  Returns the rotated dimension type of this Associative Dimension object (DXF 71).

  \remarks
  rotatedDimType() returns one of the following:

  <table>
  Name              Value
  kParallel         1
  kPerpendicular    2
  </table>
  */
  RotatedDimType rotatedDimType() const;

  /** \details
  Sets the rotated dimension type of this Associative Dimension object (DXF 71).

  \remarks
  rotatedDimType must be one of the following:

  <table>
  Name              Value
  kParallel         1
  kPerpendicular    2
  </table>
  */
  OdResult setRotatedDimType(RotatedDimType dimType);

  OdResult addToPointRefReactor();
  OdResult addToDimensionReactor(bool isAdd = true);

  OdResult removePointRef(int ptType);
  OdResult updateDimension(bool update = true, bool skipReactors = false);
  OdResult removeAssociativity(bool force = true);
  
  /** \details
  Returns the trans-space flag of this Associative Dimension object (DXF 70).
  */
  bool isTransSpatial() const;
  /** \details
  Sets the trans-space flag of this Associative Dimension object (DXF 70).
  \param transSpace [out]  Trans-space flag.
  */
  OdResult setTransSpatial(bool value);

  OdResult startCmdWatcher();
  OdResult startOopsWatcher(bool bAddAll = true);
  void     removeOopsWatcher(void);
  OdResult restoreAssocFromOopsWatcher(void);
  bool     hasOopsWatcher(void) const;

  OdResult post(OdDbObjectId dimId, OdDbObjectId& dimAssocId, bool isActive = true);
  OdResult getDimAssocGeomIds(OdDbObjectIdArray& geomIds) const;
  bool isAllGeomErased() const;
  
  virtual void modifiedGraphics(const OdDbObject* pObj) ODRX_OVERRIDE;
  virtual void modifiedGraphics(const OdDbEntity* pObj);
  virtual OdResult swapReferences(const OdDbIdMapping& idMap);

  OdResult updateFillet(const OdDbObjectIdArray& ids);
  OdResult updateAssociativity(const OdDbObjectIdArray& ids);
  OdResult updateXrefSubentPath();
  OdResult updateSubentPath(OdDbIdMapping& idMap);
  void updateDueToMirror(bool wasInMirror);

  virtual void copied(const OdDbObject* pObj, const OdDbObject* pNewObj) ODRX_OVERRIDE;
  virtual void erased(const OdDbObject *pObj, bool erasing = true) ODRX_OVERRIDE;
  virtual void openedForModify(const OdDbObject* pObject) ODRX_OVERRIDE;

  virtual OdDbObjectPtr subWblockClone(OdDbIdMapping& idMap, OdDbObject* pOwner, bool bPrimary) const ODRX_OVERRIDE;
  virtual OdDbObjectPtr subDeepClone(OdDbIdMapping& idMap, OdDbObject* pOwner, bool bPrimary) const ODRX_OVERRIDE;

protected:
  OdResult setPointRefReactor(int ptType, bool isAdd = true);

  OdResult removeDimExtDict(void);
  bool     isPointBetweenRays(const OdGePoint3d& vertex,
                              const OdGePoint3d& firstPt,
                              const OdGePoint3d& secondPt,
                              const OdGePoint3d& angPt,
                              const OdGeVector3d& normal);
  OdResult updateDimension(OdDbRotatedDimension* pRotDim,
                            OdGePoint3d* pNewPts,
                            bool bUpdate = true);

  OdResult updateDimension(OdDbAlignedDimension* pAlnDim,
                            OdGePoint3d* pNewPts,
                            bool bUpdate = true);
  OdResult   updateDimension(OdDbRadialDimension* pRadDim,
    OdGePoint3d* pNewPts,
    bool bUpdate = true);

  OdResult   updateDimension(OdDbRadialDimensionLarge* pRadDimLarge, OdGePoint3d* pNewPts, bool bUpdate = true);
  OdResult   updateDimension(OdDbDiametricDimension* pDiaDim, OdGePoint3d* pNewPts, bool bUpdate = true);
  OdResult   updateDimension(OdDb2LineAngularDimension* pA2Dim, OdGePoint3d* pNewPts, bool bUpdate = true);
  OdResult   updateDimension(OdDb3PointAngularDimension* pA3Dim, OdGePoint3d* pNewPts, bool bUpdate = true);
  OdResult   updateDimension(OdDbOrdinateDimension* pOrdDim, OdGePoint3d* pNewPts, bool bUpdate = true);
  OdResult   updateDimension(OdDbArcDimension* pArcDim, OdGePoint3d* pNewPts, bool bUpdate = true);
  OdResult   updateDimension(OdDbLeader* pLeader, OdGePoint3d* pNewPts, bool bUpdate = true);
  OdResult   updateDimension(OdDbMLeader* pMLeader, OdGePoint3d* pNewPts, bool bUpdate = true);

  OdResult   updateDimLineAndTextLocation(OdDbRotatedDimension* pAlnDim, const OdGePoint3d* kpOldPts, const OdGePoint3d* kpNewPts);
  OdResult   updateDimLineAndTextLocation(OdDbAlignedDimension* pAlnDim, const OdGePoint3d* pOldPts, const OdGePoint3d* pNewPts);
  OdResult   updateDimLineAndTextLocation(OdDb2LineAngularDimension* pA2Dim, const OdGePoint3d* pOldPts, const OdGePoint3d* pNewPts);
  OdResult   updateDimLineAndTextLocation(OdDb3PointAngularDimension* pA3Dim, const OdGePoint3d* pOldPts, const OdGePoint3d* pNewPts);
  OdResult   updateDimLineAndTextLocation(OdDbArcDimension* pArcDim, const OdGePoint3d* kpOldPts, const OdGePoint3d* kpNewPts);
  OdResult   calculate3PointAngDimArcLocation(const OdGePoint3d* kpOldPts,
                                              const OdGePoint3d& kOldArcPt,
                                              const OdGePoint3d& kOldTextPt,
                                              const OdGePoint3d* kpNewPts,
                                              const OdGeVector3d& normal,
                                              OdGePoint3d& newArcPt,
                                              OdGePoint3d& newTextPt);
  OdResult   calculate2LineAngDimArcLocation( const OdGePoint3d* kpOldPts,
                                              const OdGePoint3d& kOldArcPt,
                                              const OdGePoint3d& kOldTextPt,
                                              const OdGePoint3d* kpNewPts,
                                              const OdGeVector3d& kNormal,
                                              OdGePoint3d& newArcPt,
                                              OdGePoint3d& newTextPt);
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdDbDimAssoc object pointers.
*/
typedef OdSmartPtr<OdDbDimAssoc> OdDbDimAssocPtr;

//
// Inlines
//

inline
OdHandleArray& OdDbXrefFullSubentPath::xrefObjHandles()
{ 
  return m_XrefObjHandles; 
}

inline
const OdHandleArray& OdDbXrefFullSubentPath::xrefObjHandles() const
{ 
  return m_XrefObjHandles; 
}

inline
OdDbPointRef::OsnapType OdDbOsnapPointRef::osnapType() const
{
  return m_OsnapMode;
}

inline
OdResult OdDbOsnapPointRef::setOsnapType(OdDbPointRef::OsnapType osnapMode)
{
  m_OsnapMode = osnapMode;

  return eOk;
}

inline
OdDbXrefFullSubentPath& OdDbOsnapPointRef::mainEntity()
{
  return m_MainEntity;
}

inline
OdDbXrefFullSubentPath& OdDbOsnapPointRef::intersectEntity()
{
  return m_IntersectEntity;
}

inline
double OdDbOsnapPointRef::nearPointParam() const
{
  return m_dNearOsnap;
}

inline
OdResult OdDbOsnapPointRef::setNearPointParam(double nearOsnap)
{
  m_dNearOsnap = nearOsnap;
  return eOk;
}

inline
OdGePoint3d OdDbOsnapPointRef::point() const
{
  return m_OsnapPoint;
}
inline
OdResult OdDbOsnapPointRef::setPoint(const OdGePoint3d& pt)
{
  m_OsnapPoint = pt;
  return eOk;
}

inline
const OdDbOsnapPointRef* OdDbOsnapPointRef::lastPointRef(ODSYSDEF) const
{
  return m_pLastPointRef;
}

inline
OdDbOsnapPointRef* OdDbOsnapPointRef::lastPointRef()
{
  return m_pLastPointRef;
}

inline
OdResult OdDbOsnapPointRef::setLastPointRef(OdDbOsnapPointRefPtr pOsnapPointRef)
{
  m_pLastPointRef = pOsnapPointRef;
  return eOk;
}

#include "TD_PackPop.h"

#endif // OD_DBDIMASSOC_H

