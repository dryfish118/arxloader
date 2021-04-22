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




#ifndef _OD_DB_3D_POLYLINE_
#define _OD_DB_3D_POLYLINE_

#include "TD_PackPush.h"

#include "DbCurve.h"
#include "DbObjectIterator.h"
#include "DwgDeclareMembers.h"

class OdDb3dPolylineVertex;
class OdDbSequenceEnd;

/** \details
    This template class is a specialization of the OdSmartPtr class for OdDb3dPolylineVertex object pointers.
*/
typedef OdSmartPtr<OdDb3dPolylineVertex> OdDb3dPolylineVertexPtr;
/** \details
    This template class is a specialization of the OdSmartPtr class for OdDbSequenceEnd object pointers.
*/
typedef OdSmartPtr<OdDbSequenceEnd> OdDbSequenceEndPtr;

/** \details
    This class represents 3D Polyline entities in an OdDbDatabase instance.
    <group OdDb_Classes> 
*/
class DBENT_EXPORT OdDb3dPolyline: public OdDbCurve
{
public:

  DWGMAP_DECLARE_MEMBERS(OdDb3dPolyline);

  OdDb3dPolyline();

  OdDb3dPolyline(OdDb::Poly3dType, OdGePoint3dArray& vertices, OdBool closed = kFalse);

  TOOLKIT_EXPORT OdResult     length(double &) const;
  TOOLKIT_EXPORT OdResult     setClosed(OdBool);
  /** \details
    Sets this Polyline entity closed (DXF 70, bit 0x01=1).
  */
  OdResult makeClosed();

  /** \details
    Sets this Polyline entity open (DXF 70, bit 0x01=0).
  */
  OdResult makeOpen();

  /** \details
    Returns the type of this Polyline entity. 
    
    \remarks
    polyType() returns one of the following:
    
    <table>
    Name                        Value   Description
    OdDb::k3dSimplePoly         0       Simple polyline.
    OdDb::k3dQuadSplinePoly     1       Quadratic B-spline fit (DXF 80, bit 0x08; DXF 75 == 5).
    OdDb::k3dCubicSplinePoly    2       Cubic B-spline-fit (DXF 80, bit 0x08; DXF 75 == 6).
    </table>
  */
  OdDb::Poly3dType polyType() const;

  /** \details
    Sets the type of this Polyline entity. 

    \param polyType [in]  Polyline type.
   
    \remarks
    polyType() returns one of the following:
    
    <table>
    Name                        Value   Description
    OdDb::k3dSimplePoly         0       Simple polyline.
    OdDb::k3dQuadSplinePoly     1       Quadratic B-spline fit (DXF 80, bit 0x08; DXF 75 == 5).
    OdDb::k3dCubicSplinePoly    2       Cubic B-spline-fit (DXF 80, bit 0x08; DXF 75 == 6).
    </table>
  */
  OdResult setPolyType(
    OdDb::Poly3dType polyType);

  /** \details
    Removes all spline fitting from this Polyline entity.
  
    \remarks
    Removes all but the simple vertices.
  */
  OdResult straighten();

  /** \details
    Appends the specified Vertex entity to this Polyline entity, and makes this Polyline entity its owner.
    
    \returns
    Returns the Object ID of the appended vertex.
    
    If this Polyline entity is database resident, the Vertex entity will be made database resident. 
    
    If this Polyline entity is not database resident, the Vertex entity will be made database resident
    when this Polyline entity is made database resident.
    
    \remarks
    If this Polyline is database resident, the Vertex entity must explicitly be closed when
    appendVertex() returns.
    
    \param pVertex [in]  Pointer to the Vertex entity to be appended.
  */
  OdDbObjectId appendVertex(ODSYSDEF,
    OdDb3dPolylineVertex* pVertex);

  OdResult appendVertex(OdDb3dPolylineVertex*);
  OdResult appendVertex(OdDbObjectId& objId, OdDb3dPolylineVertex*);
  /** \details
    Inserts the specified Vertex entity into this Polyline entity
    after the specified vertex, and makes this Polyline its owner.
    
    \returns
    Returns the Object ID of the newly inserted vertex.
    
    The Vertex will be made database resident. 
    
    If this Polyline entity is not database resident, the vertex will be made database resident
    when the polyline is made database resident.
    
    To insert the specified Vertex at the start of this Polyline, use a null indexVertexId.
    
    \remarks
    The Vertex entity must explicitly be closed when insertertex() returns.

    \param indexVertId [in]  Object ID of vertex after which to insert the specified vertex.
    \param pVertex [in]  Pointer to the Vertex entity to be inserted.
  */
  OdDbObjectId insertVertexAt(
    const OdDbObjectId& indexVertId, 
    OdDb3dPolylineVertex* pVertex);

  /** \details
    Inserts the specified Vertex entity into this Polyline entity
    after the specified vertex, and makes this Polyline its owner.
    
    \returns
    Returns the Object ID of the newly inserted vertex.
    
    The Vertex will be made database resident. 
    
    If this Polyline entity is not database resident, the vertex will be made database resident
    when the polyline is made database resident.
    
    To insert the specified Vertex at the start of this Polyline, use a null indexVertexId.
    
    \remarks
    The Vertex entity must explicitly be closed when insertertex() returns.

    \param pIndexVert [in]  Pointer to vertex after which to insert the specified vertex.
    \param pVertex [in]  Pointer to the Vertex entity to be inserted.
  */
  OdDbObjectId insertVertexAt(ODSYSDEF,
    const OdDb3dPolylineVertex* pIndexVert, 
    OdDb3dPolylineVertex* pVertex);

  OdResult insertVertexAt(const OdDb3dPolylineVertex* pIndexVert,
        OdDb3dPolylineVertex* pNewVertex); 
  OdResult insertVertexAt(OdDbObjectId& newVertId,
        const OdDbObjectId& indexVertId, OdDb3dPolylineVertex* pNewVertex);
  /** \details
    Opens a vertex owned by this Polyline entity.

    \param vertId [in]  Object ID of vertex to be opened.
    \param mode [in]  Mode in which to open the vertex.
    \param openErasedOne [in]  If and only if true, erased objects will be opened.

    \returns
    Returns a SmartPointer to the opened object if successful, otherwise a null SmartPointer.
  */
  OdDb3dPolylineVertexPtr openVertex(
    OdDbObjectId vertId, 
    OdDb::OpenMode mode, 
    bool openErasedOne = false);

  OdResult openVertex(OdDb3dPolylineVertex*& pVertex, OdDbObjectId vertId,
    OdDb::OpenMode,
    bool openErasedOne = false);

  /** \details
    Opens the OdDbSequenceEnd entity for this Polyline entity.

    \param mode [in]  Mode in which to open the OdDbSequenceEnd entity.

    \returns
    Returns a SmartPointer to the newly opened OdDbSequenceEnd, or a null SmartPointer.

    \remarks
    This method is provided solely for applications that store XData on
    OdDbSequenceEnd entities; this is not recommended. 
  */
  OdDbSequenceEndPtr openSequenceEnd(
    OdDb::OpenMode mode);

  /**
  Remarks:
    Returns eOk if successful

  Arguments:
  pSeqEnd(O) a Pointer to the newly opened OdDbSequenceEnd.

  Gcad(Add):增加兼容接口
  */
  OdResult openSequenceEnd(OdDbSequenceEnd*& pSeqEnd, OdDb::OpenMode);

  /** \details
    Returns a SmartPointer to an iterator that can be used to traverse the vertices owned 
    by this Polyline entity.
  */
  OdDbObjectIteratorPtr vertexIterator(ODSYSDEF) const;

#ifdef ODARXDEF
  OdDbObjectIterator* vertexIterator() const;
#endif

  virtual OdResult dxfOut(
    OdDbDxfFiler* pFiler,
    OdBool allXdFlag = kTrue,
    unsigned char* regAppTable = NULL) const;

  virtual OdResult dxfIn(
    OdDbDxfFiler* pFiler);

  virtual OdResult dwgInFields(
    OdDbDwgFiler* pFiler);

  virtual OdResult dwgOutFields(
    OdDbDwgFiler* pFiler) const;

  virtual OdResult dxfInFields(
    OdDbDxfFiler* pFiler);

  virtual OdResult dxfOutFields(
    OdDbDxfFiler* pFiler) const;

  virtual OdResult dxfInFields_R12(
    OdDbDxfFiler* pFiler);

  virtual void dxfOutFields_R12(
    OdDbDxfFiler* pFiler) const;

  virtual OdResult subGetClassID(
    CLSID* pClsid) const;

  OdResult subClose();

  virtual OdResult subExplode(
    OdDbVoidPtrArray& entitySet) const;

  virtual OdResult explodeGeometry(
    OdRxObjectPtrArray& entitySet) const;

  virtual OdResult subTransformBy(
    const OdGeMatrix3d& xfm);

  virtual OdBool subWorldDraw(
    OdGiWorldDraw* pWd);

  virtual OdBool isPlanar() const;

  virtual OdResult getPlane(
    OdGePlane& plane, 
      OdDb::Planarity& planarity) const;


  /* OdDbCurveMethods */

  /** \details
  Returns true if 3D-Polyline is closed or false otherwise.
  */
  virtual OdBool isClosed() const;

  virtual OdBool isPeriodic() const;

  virtual OdResult getStartParam(
    double& startParam) const;

  virtual OdResult getEndParam(
    double& endParam) const;

  virtual OdResult getStartPoint(
    OdGePoint3d& startPoint) const;

  virtual OdResult getEndPoint(
    OdGePoint3d& endPoint) const;

  virtual OdResult getPointAtParam(
    double param, 
    OdGePoint3d& pointOnCurve) const;

  virtual OdResult getParamAtPoint(
    const OdGePoint3d& pointOnCurve, 
    double& param) const;

  virtual OdResult getDistAtParam( double param, double& dist ) const;

  virtual OdResult getParamAtDist( double dist, double& param ) const;

  virtual OdResult getFirstDeriv (
    double param,
    OdGeVector3d& firstDeriv) const;

  virtual OdResult getSecondDeriv (
    double param,
    OdGeVector3d& secondDeriv) const;

  virtual OdResult getArea(
    double& area) const;

  TD_USING(OdDbCurve::getFirstDeriv);
  TD_USING(OdDbCurve::getSecondDeriv);


  /** \details
  Convert 3D-Polyline to the specified type.

  \param newVal [in]  Polyline type.
    
  \remarks
  newVal must be one of the following:

  <table>
    Name                        Value   Description
    OdDb::k3dSimplePoly         0       Simple polyline.
    OdDb::k3dQuadSplinePoly     1       Quadratic B-spline fit (DXF 80, bit 0x08; DXF 75 == 5).
    OdDb::k3dCubicSplinePoly    2       Cubic B-spline-fit (DXF 80, bit 0x08; DXF 75 == 6).
    </table>
  */
  OdResult convertToPolyType(OdDb::Poly3dType newVal); 

  /** \details
  Transforms all simple vertices to control vertices and creates a new spline-fit vertices based
  on a control vertices, through which the polyline will be drawn.
  
  \returns eOk if successful, or an appropriate error code if not.
  */
  OdResult splineFit();

  /** \details
  Transforms all simple vertices to control vertices and creates a new spline-fit vertices based
  on a control vertices, through which the polyline will be drawn.

  \param splineType [in]  Spline-Fit Polyline type.

  \param splineSegs [in]  Number of Spline-Fit segments.
  
  \returns eOk if successful, or an appropriate error code if not.
  */
  OdResult splineFit(OdDb::Poly3dType splineType, OdInt16 splineSegs);

  virtual OdResult subGetSubentPathsAtGsMarker(OdDb::SubentType type, OdGsMarker gsMark,
    const OdGePoint3d& pickPoint, const OdGeMatrix3d& xfm,
    int& numPaths, OdDbFullSubentPath*& subentPaths,
    int numInserts = 0,
    OdDbObjectId* pEntAndInsertStack = 0) const;

  virtual OdResult subGetGsMarkersAtSubentPath(const OdDbFullSubentPath& subPath,
    OdGsMarkerArray& gsMarkers) const;

  virtual OdDbEntity* subSubentPtr(const OdDbFullSubentPath& path) const;

  virtual OdResult getOdGeCurve(OdGeCurve3d*& pGeCurve, const OdGeTol& tol = OdGeContext::gTol) const;
  virtual OdResult setFromOdGeCurve(const OdGeCurve3d& geCurve, OdGeVector3d *normal = NULL, const OdGeTol& tol = OdGeContext::gTol);
  
  /** \details
  Reverses the Polyline so that the first vertex become the last vertex of a Polyline 
  and the last vertex become the first vertex.
    
  \returns eOk if successful, or an appropriate error code if not.
  */
  virtual OdResult reverseCurve();

  virtual OdInt32 findVertexIndex(const OdDbVertex* vert) const;
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdDb3dPolyline object pointers.
*/
typedef OdSmartPtr<OdDb3dPolyline> OdDb3dPolylinePtr;

#include "TD_PackPop.h"

#endif

