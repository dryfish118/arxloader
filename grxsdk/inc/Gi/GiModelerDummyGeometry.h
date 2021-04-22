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

#ifndef _ODGIMODELERDUMMYGEOM_INCLUDED_
#define _ODGIMODELERDUMMYGEOM_INCLUDED_

#include "Gi/GiDummyGeometry.h"

#include "DbBaseSubentId.h" 

#include "ModelerMarkers.h"

#include "TD_PackPush.h"

/** \details

Corresponding C++ library: TD_Gi
<group OdGi_Classes>
*/
template<class T, class DRAW, class WR, class WRA> class OdGeomGrabber : public T
{
  OdLongPtr m_curSelMarker;
  WRA &wires;

  OdGeomGrabber();
protected:
  virtual OdLongPtr getCurSelMarker() const {
    return m_curSelMarker;
  }

public:

  OdGeomGrabber(WRA &pW, DRAW &pVd)
    : T(pVd, pVd.geometry(), pVd.subEntityTraits())
    , m_curSelMarker(0)
    , wires(pW)
  { }

  virtual void setSelectionMarker(const OdLongPtr n) { m_curSelMarker = n; T::setSelectionMarker(n); }

  virtual WR *appendWire() const
  {
    WR *pWire = wires.append();
    pWire->selMarker = OdIntToGsMarker(-getFaceIndex(m_curSelMarker));
    pWire->color = T::subEntityTraits().trueColor();
    return pWire;
  }

  virtual OdBool circle(const OdGePoint3d& center, const double radius, const OdGeVector3d& normal) const
  {
    appendWire()->circle(center, radius, normal);
    return T::circle(center, radius, normal);
  }

  virtual OdBool circle(const OdGePoint3d& p1, const OdGePoint3d& p2, const OdGePoint3d& p3) const
  {
    appendWire()->circle(p1, p2, p3);
    return T::circle(p1, p2, p3);
  }

  virtual OdBool circularArc(const OdGePoint3d& center,
    const double radius,
    const OdGeVector3d& normal,
    const OdGeVector3d& startVector,
    const double sweepAngle,
    const OdGiArcType arcType = kOdGiArcSimple) const
  {
    appendWire()->circularArc(center, radius, normal, startVector, sweepAngle);
    return T::circularArc(center, radius, normal, startVector, sweepAngle, arcType);
  }

  virtual OdBool circularArc(const OdGePoint3d& start,
    const OdGePoint3d& point,
    const OdGePoint3d& end,
    const OdGiArcType arcType = kOdGiArcSimple) const
  {
    appendWire()->circularArc(start, point, end);
    return T::circularArc(start, point, end, arcType);
  }

  virtual OdBool polyline(const OdUInt32 nbPoints,
    const OdGePoint3d* pVertexList,
    const OdGeVector3d* pNormal = NULL,
    OdLongPtr lBaseSubEntMarker = -1) const
  {
    appendWire()->polyline(nbPoints, pVertexList);
    return T::polyline(nbPoints, pVertexList, pNormal, lBaseSubEntMarker);
  }

  virtual OdBool nurbs(const OdGeNurbCurve3d& nurbs, const OdGeVector3d* pNormal = 0) const
  {
    appendWire()->nurbs(nurbs);
    return T::nurbs(nurbs, pNormal);    
  }
};

/** \details

Corresponding C++ library: TD_Gi
<group OdGi_Classes>
*/
template<class T, class DRAW, class WR, class WRA> class OdShellGrabber : public T
{
  OdGsMarker m_curSelMarker;
  WRA &wires;

  OdShellGrabber();
public:

  OdShellGrabber(WRA &pW, DRAW &pVd) : T(pVd, pVd.geometry(), *OdGiDrawableTraits::cast(&pVd.subEntityTraits()))
    , m_curSelMarker(0)
    , wires(pW)
  { }

  virtual OdGiRegenType regenType() const              { return kOdGiHideOrShadeCommand; }

  virtual void setSelectionMarker(const OdLongPtr n) { m_curSelMarker = n; T::setSelectionMarker(n); }

  virtual OdBool shell(
    const OdUInt32 numVertices,
    const OdGePoint3d* vertexList,
    const OdUInt32 faceListSize,
    const OdInt32* faceList,
    const OdGiEdgeData* pEdgeData = 0,
    const OdGiFaceData* pFaceData = 0,
    const OdGiVertexData* pVertexData = 0)
  {
    WR *pWire = wires.append();
    pWire->selMarker = m_curSelMarker;
    pWire->color = T::subEntityTraits().trueColor();
    pWire->shell(
      numVertices,
      vertexList,
      faceListSize,
      faceList,
      pEdgeData,
      pFaceData,
      pVertexData);

    return T::shell(
      numVertices,
      vertexList,
      faceListSize,
      faceList,
      pEdgeData,
      pFaceData,
      pVertexData);
  }
};

#include "TD_PackPop.h"

#include "ModelerMarkersUndef.h"

#endif // #ifndef _ODGIMODELERDUMMYGEOM_INCLUDED_
