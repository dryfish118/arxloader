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


#ifndef _OD_GEENTITY3D_H_
#define _OD_GEENTITY3D_H_ /*!DOM*/

#include "../Ge/GeGbl.h"
#include "../Ge/GePoint3d.h"
#include "../Ge/GeEntity2d.h"
#include "../Ge/GeInterval.h"
#include "../OdHeap.h"

#include "../grx/gegblnew.h"

#include "../TD_PackPush.h"

class OdGeMatrix3d;
class OdGePlane;
class OdGeEntity3dImpl;

/** \details
    This class is the base class for all OdGe 3D geometric operations.

    Corresponding C++ library: TD_Ge

    <group OdGe_Classes> 
*/
class GE_TOOLKIT_EXPORT OdGeEntity3d
{
public:
//DOM-IGNORE-BEGIN
  ODRX_HEAP_OPERATORS();

  ~OdGeEntity3d();
//DOM-IGNORE-END
  // Run time type information.

  /** \details
    Returns true if and only if this entity is of type (or is derived from) entType.

    \param entType [in]  Entity type to test. 
  */
   OdBool isKindOf(
    OdGe::EntityId entType) const;

  /** \details
    Returns the entity type.
  */
   OdGe::EntityId type() const;

  /** \details
    Returns a copy of this entity.

    \remarks
  The returned object is created with the new operator, and it is the responsibility of the caller to delete it.
  */
   OdGeEntity3d* copy() const;

  /** \details
    Assignment operator for the OdGeEntity3d object.
  */
  OdGeEntity3d& operator =(
    const OdGeEntity3d& entity);

  /** \details
    Comparison operator for the OdGeEntity3d object.
    
    \returns
    A boolean value that indicates whether the input entity is identical to this entity.
  */
  OdBool operator ==(
    const OdGeEntity3d& entity) const;
  
  /** \details
    Comparison operator for the OdGeEntity3d object.
    
    \returns
    A boolean value that indicates whether the input entity is not identical to this entity.
  */
  OdBool operator !=(
    const OdGeEntity3d& entity) const;

  /** Returns true if the specified entity is equal to this one.

    \remarks
    Returns true if and only if both entities are of the same type, have the same point set within the 
    specified tolerance, and have the same parameterization.

    \param other [in]  Entity to be compared
    \param tol [in]  Geometric tolerance.
  */
   OdBool isEqualTo(
    const OdGeEntity3d& object, 
    const OdGeTol& tol = OdGeContext::gTol) const;

  /** \details
    Applies the 3D transformation matrix to this entity, and returns
    a reference to this entity.

    \param xfm [in]  3D transformation matrix.
  */
   OdGeEntity3d& transformBy(
    const OdGeMatrix3d& xfm);

  /** \details
    Applies the 3D translation vector to this entity, and returns
    a reference to this entity.

    \param translateVec [in]  Translation Vector.
  */
   OdGeEntity3d& translateBy(
    const OdGeVector3d& translateVec);

  /** \details
    Rotates this entity by the specified angle about the axis
    defined by the point and the vector, and returns
    a reference to this entity.

    \param angle [in]  Rotation angle.
    \param vect [in]  Vector about which entitiy is rotated. 
    \param basePoint [in]  Basepoint.
  */
   OdGeEntity3d& rotateBy(
    double angle, 
    const OdGeVector3d& vect,
    const OdGePoint3d& basePoint = OdGePoint3d::kOrigin);

  /** \details
    Mirrors this entity about the specified plane, and returns
    a reference to this entity.

    \param plane [in]  Plane about which entity is to be mirrored.
  */
   OdGeEntity3d& mirror(
    const OdGePlane& plane);

  /** \details
    Scales this entity by the scale factor about the basepoint, and returns
    a reference to this entity.

    \param scaleFactor [in]  Scale Factor. Must be greater than 0.
    \param basePoint [in]  Basepoint.
  */
   OdGeEntity3d& scaleBy(
    double scaleFactor,
    const OdGePoint3d& basePoint = OdGePoint3d::kOrigin);

  /** \details
    Returns true if and only if the specified point is on this entity, 
    as determined by the tolerance.

    \param point [in]  Point to be queried.
    \param tol [in]  Geometric tolerance.
  */
   OdBool isOn(
    const OdGePoint3d& point,
    const OdGeTol& tol = OdGeContext::gTol) const;

//DOM-IGNORE-BEGIN
protected:
#ifndef  USE_GCGE
  friend class OdGeImpEntity3d;
  class OdGeImpEntity3d  *mpImpEnt;
  int              mDelEnt;
#endif

  OdGeEntity3d();
  OdGeEntity3d(const OdGeEntity3d&);
  OdGeEntity3d(OdGeEntity3dImpl*);
  void connectTo(OdGeEntity3dImpl*);
#ifndef  USE_GCGE
  OdGeEntity3d(OdGeImpEntity3d&, int);
  OdGeEntity3d(OdGeImpEntity3d*);
  OdGeEntity2d* newEntity2d(OdGeImpEntity3d*) const;
  OdGeEntity2d* newEntity2d(OdGeImpEntity3d&, int) const;
  OdGeEntity3d* newEntity3d(OdGeImpEntity3d*) const;
  OdGeEntity3d* newEntity3d(OdGeImpEntity3d&, int) const;
#endif
private:

  OdGeEntity3dImpl* m_pImpl;
  friend class OdGeEntity3dImpl;
//DOM-IGNORE-END
};

#ifndef  USE_GCGE

inline OdGeEntity2d*
OdGeEntity3d::newEntity2d(OdGeImpEntity3d *impEnt) const
{
  return GENEWLOC(OdGeEntity2d, this) (impEnt);
}

inline OdGeEntity3d*
OdGeEntity3d::newEntity3d(OdGeImpEntity3d *impEnt) const
{
  return GENEWLOC(OdGeEntity3d, this) (impEnt);
}

inline OdGeEntity3d*
OdGeEntity3d::newEntity3d(OdGeImpEntity3d& impEnt, int dummy) const
{
  return GENEWLOC(OdGeEntity3d, this)(impEnt, dummy);
}

inline OdGeEntity2d*
OdGeEntity3d::newEntity2d(OdGeImpEntity3d& impEnt, int dummy) const
{
  return GENEWLOC(OdGeEntity2d, this)(impEnt, dummy);
}
#endif
#include "../TD_PackPop.h"

#endif //_OD_GEENTITY3D_H_

