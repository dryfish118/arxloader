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

#ifndef __FMMDL_VERTEXDATA_H__
#define __FMMDL_VERTEXDATA_H__

#include "../FacetModeler/Modeler/FMMdlCircle3d.h"

/**
  <group TA_Geometry>
*/
namespace FacetModeler
{

  class FMGEOMETRY_API PolygonVertexData
  {
  public:

    enum Type { kArc3d, kArcByRadius, kArcByBulge, kFilletByRadius, kUnspecifiedCurve };

    PolygonVertexData(Type);                            
    PolygonVertexData(Type, const Circle3d&, int apprx);
    PolygonVertexData(Type, double rad, bool isCenLeft, int apprx);
    PolygonVertexData(Type, double bulgeOrRadius, int apprx);      

    bool isArc() const 
    { 
      return type == kArc3d || type == kArcByRadius || type == kArcByBulge || type == kFilletByRadius; 
    }

  public: // data

    Type     type;
    Circle3d circle;
    int      approx;
    bool     isCenterLeft;
    double   bulge;
    Curve*   curve;
    Surface* surface;

  }; // class PolygonVertexData

 FMGEOMETRY_API void deleteVertexData(PolygonVertexData* vertexDataArray[], int arrayLength, bool alsoDeleteArray);
}

#endif //__FMMDL_VERTEXDATA_H__
