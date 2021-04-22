﻿/////////////////////////////////////////////////////////////////////////////// 
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

#ifndef _OD_DB_POINTCLOUDCROPPING_
#define _OD_DB_POINTCLOUDCROPPING_

#include "../TD_PackPush.h"
#include "DbPointCloudObjExports.h"
#include "../DbObject.h"
#include "../Ge/GePoint3d.h"
#include "../Ge/GePoint2dArray.h"
#include "../Ge/GePlane.h"

namespace Gstarsoft {
  namespace RealityStudio {
    namespace SDK {
      namespace Interface {
        class ARCSpatialFilter;
      }
    }
  }
};

class OdDbPointCloudDxfHandler;
class OdGiGeometry;

/** \details
  This class represents cropping boundaries for point cloud entities.

  Corresponding C++ library: AcDbPointCloudObj

  <group OdDbPointCloud_Classes>
*/
class DBPOINTCLOUDOBJ_EXPORT OdDbPointCloudCrop
{
public:
  /** \details
  Defines cropping boundary types.
  */
  enum CropType
  {
    kInvalid = 0,       //Box
    kRectangular,         //Rectangular boundary
    kPolygonal,          //Polyline boundary
    kCircular           //Circular bounfary 
  };

  /** \details
    Default constructor. Creates an OdDbPointCloudCrop instance.
  */
  OdDbPointCloudCrop();

  virtual ~OdDbPointCloudCrop()
  {

  }

  bool operator == (const OdDbPointCloudCrop&) const;

  bool operator != (const OdDbPointCloudCrop& other) const;

  /** \details
    Check whether the boundary is valid. Returns true only if a number of vertices matches the boundary type: 
    box or rectangular boundary must have two vertices, polygonal - at least 3 vertices.
  */
  bool isValid() const;

  /** \details
    Returns the number of vertices of this cropping boundary.
  */
  OdInt16 length() const; 

  /** \details
    Returns the type of this cropping boundary.
  */
  CropType type() const;

  /** \details
    Set type of this cropping boundary.
  */
  void setCropType( CropType type );
  
  /** \details
    Sets the boundary to inverted.
  */
  void setInvert(const bool);

  /** \details
    Sets the boundary to inverted.
  */
  void setInverted(const bool);

  /** \details
    Returns true if only the boundary is inverted.
  */
  bool isInverted() const;

  /** \details
    Returns closed boundary
  */
  const OdGePoint3dArray& get() const;

  /** \details
    Returns closed boundary
  */
  void set( const OdGePoint3dArray& points) ;

  /** \details

  */
  bool getCropPlane( OdGePlane& plane ) const;

  /** \details

  */
  void setCropPlane( const OdGePlane& plane ) ;

  /** \details

  */
  void setInside(const bool);

  /** \details

  */
  bool isInside() const;

  /** \details

  */
  void clear();

  /** \details

  */
  virtual void draw( OdGiGeometry &geom );

  virtual OdResult dwgInFields( OdDbDwgFiler *pFiler );
  virtual OdResult dwgOutFields( OdDbDwgFiler *pFiler ) const;

  virtual OdResult dxfInFields(OdDbDxfFiler* pFiler, OdInt16& dxfInt8, OdInt16& dxfInt32, OdInt16& dxfXCoord, OdInt16& dxfNormalX);

  OdResult dxfInFields( OdDbDxfFiler *pFiler );
  virtual OdResult dxfOutFields( OdDbDxfFiler *pFiler, OdInt16 &dvfInt8, OdInt16 &dxfInt32, OdInt16 &dxfXCoord, OdInt16 &dxfNormalX ) const;

  virtual Gstarsoft::RealityStudio::SDK::Interface::ARCSpatialFilter*  toSpatialFilter() const;

public:
  void setDxfHandler(OdDbPointCloudDxfHandler* dxfHandler);

private:
  
  OdInt8 m_type;
  bool m_isInside;
  bool m_inverted;
  OdGePlane m_plane;
  OdGePoint3dArray m_points;
};

#include "../TD_PackPop.h"

#endif //_OD_DB_POINTCLOUDCROPPING_
