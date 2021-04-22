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




#ifndef _OD_DB_FACE_
#define _OD_DB_FACE_

#include "TD_PackPush.h"

#include "DbEntity.h"
#include "DwgDeclareMembers.h"

/** \details
  <group OdDb_Classes> 

  This class implements the /3d face/ object (3D Face entity) in the database. 
  This class inherits the base functionality of entities. 

    
  \sa
  <link db_face_sample, Example of Working with the 3D Face Object>

  \sa
  <link db_face, Working with 3D Faces>
*/
class DBENT_EXPORT OdDbFace : public OdDbEntity
{
public:                
  DWGMAP_DECLARE_MEMBERS(OdDbFace);

  /** \details
    Builds an instance of the /3d face/ entity.
    
    \remarks
    Use the static pseudo-constructor instead it.
    See: <link db_face_overview, Overview of 3D Faces>
  */
  OdDbFace();
  OdDbFace(const OdGePoint3d&   pt0,
    const OdGePoint3d&   pt1,
    const OdGePoint3d&   pt2,
    const OdGePoint3d&   pt3,
    OdBool e0vis = kTrue,
    OdBool e1vis = kTrue,
    OdBool e2vis = kTrue,
    OdBool e3vis = kTrue);
  OdDbFace(const OdGePoint3d&   pt0,
    const OdGePoint3d&   pt1,
    const OdGePoint3d&   pt2,
    OdBool e0vis = kTrue,
    OdBool e1vis = kTrue,
    OdBool e2vis = kTrue,
    OdBool e3vis = kTrue);

  /** \details
    Gets the WCS coordinates of the vertex belonged to the 3d face entity using its index 
    (DXF 10, 11, 12, or 13).

    \param vertexIndex [in]  Vertex index 0, 1, 2, or 3.
    \param vertexValue [out]  Reference to a variable in which this method must save the 3d face vertex 
                    as a three-dimensional point instance.

    \sa
    <link db_face_sample, Example of Working with the 3D Face Object>

    \sa
    <link db_face_specific, Specific 3D Face Properties>

    OdDbFace::setVertexAt() method
  */
  OdResult getVertexAt( OdUInt16 vertexIndex, OdGePoint3d& vertexValue ) const;


  /** \details
    Sets the WCS coordinates of the vertex belonged to the 3d face entity using its index 
    (DXF 10, 11, 12, or 13).

    \param pointIndex [in]  Vertex index 0, 1, 2, or 3.
    \param pointValue [in]  Three-dimensional point instance to be set the vertex.

    \sa
    <link db_face_sample, Example of Working with the 3D Face Object>

    \sa
    <link db_face_specific, Specific 3D Face Properties>

    OdDbFace::getVertexAt() method
  */
  OdResult setVertexAt( OdUInt16 vertexIndex, const OdGePoint3d& vertexValue );


  /** \details
    Determines the visiblity of 3d face edge at the specified index (DXF 70) and returns 
    True if the edge is visible or False if the edge is invisible. 

    \param edgeIndex [in]  Edge index 0, 1, 2, or 3.

    \sa
    <link db_face_sample, Example of Working with the 3D Face Object>

    \sa
    <link db_face_specific, Specific 3D Face Properties>

    OdDbFace::makeEdgeVisibleAt(), OdDbFace::makeEdgeInvisibleAt() methods
  */
  bool isEdgeVisibleAt( OdUInt16 edgeIndex ) const;

  OdResult isEdgeVisibleAt(OdUInt16 edgeIndex, OdBool& visible) const;

  /** \details
    Turns to visible the 3d face edge at the specified index (DXF 70).

    \param edgeIndex [in]  Edge index 0, 1, 2, or 3.

    \sa
    <link db_face_sample, Example of Working with the 3D Face Object>

    \sa
    <link db_face_specific, Specific 3D Face Properties>

    OdDbFace::isEdgeVisibleAt(), OdDbFace::makeEdgeInvisibleAt() methods
  */
  OdResult makeEdgeVisibleAt( OdUInt16 edgeIndex );


  /** \details
    Turns to invisible the 3d face edge at the specified index (DXF 70).

    \param edgeIndex [in]  Edge index 0, 1, 2, or 3.

    \sa
    <link db_face_sample, Example of Working with the 3D Face Object>

    \sa
    <link db_face_specific, Specific 3D Face Properties>

    OdDbFace::makeEdgeVisibleAt(), OdDbFace::isEdgeVisibleAt() methods
  */
  OdResult makeEdgeInvisibleAt( OdUInt16 edgeIndex );

  virtual OdResult getPlane(
    OdGePlane& plane,
    OdDb::Planarity& planarity) const;


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

  OdBool subWorldDraw(
    OdGiWorldDraw* pWd);

  void subViewportDraw(
    OdGiViewportDraw* pVd);

  virtual OdResult subGetClassID(
    CLSID* pClsid) const;

  virtual OdResult subTransformBy(const OdGeMatrix3d& xfm);

  virtual OdResult subGetSubentPathsAtGsMarker(OdDb::SubentType type, OdGsMarker gsMark,
    const OdGePoint3d& pickPoint, const OdGeMatrix3d& xfm,
    int& numPaths, OdDbFullSubentPath*& subentPaths,
    int numInserts = 0,
    OdDbObjectId* pEntAndInsertStack = 0) const;

  virtual OdResult subGetGsMarkersAtSubentPath(const OdDbFullSubentPath& subPath,
    OdGsMarkerArray& gsMarkers) const;
  virtual OdDbEntity* subSubentPtr(const OdDbFullSubentPath& path) const;
};

/** \details
  The typified smart pointer for the /3d face/ object (3D Face entity). This template class 
  is specialization of the OdSmartPtr class for the OdDbFace object.

  \sa
  <link smart_pointers, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdDbFace> OdDbFacePtr;

#include "TD_PackPop.h"

#endif
