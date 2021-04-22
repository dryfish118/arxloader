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

#ifndef OD_GE_ENTITY_2D_H
#define OD_GE_ENTITY_2D_H /*!DOM*/

class OdGeMatrix2d;
class OdGeLine2d;
class OdGeEntity2dImpl;
class OdGeEntity3dImpl;
#include "../Ge/GeGbl.h"
#include "../Ge/GePoint2d.h"
#include "../Ge/GeInterval.h"
#include "../OdHeap.h"
#include "../grx/gegblnew.h"

#include "../TD_PackPush.h"

#define USE_GCGE

/** \details
    This class is the base class for all OdGe 2D geometric operations.

    Corresponding C++ library: TD_Ge

    <group OdGe_Classes> 
*/
class GE_TOOLKIT_EXPORT OdGeEntity2d
{
public:
//DOM-IGNORE-BEGIN
  ODRX_HEAP_OPERATORS();
//DOM-IGNORE-END
  
  /** \details
    Returns true if and only if this entity is of  type (or is derived from) entType.

    \param entType [in]  Entity type to test. 
  */
  OdBool isKindOf(
    OdGe::EntityId entType) const;

  /** \details
    Returns the entity type of this entity.
  */
  OdGe::EntityId type() const;

  /** \details
    Returns a copy of this entity.

    \remarks
    The returned object is created with the new operator, and it is the responsibility of the caller to delete it.
  */
  OdGeEntity2d* copy() const;

  /** \details
    Assignment operator for the OdGeEntity2d object.
  */
  OdGeEntity2d& operator =(
    const OdGeEntity2d& entity);

  /** \details
    Comparison operator for the OdGeEntity2d object.
    
    \returns
    A boolean value that indicates whether the input entity is identical to this entity.
  */
  OdBool operator ==(
    const OdGeEntity2d& entity) const;

  /** \details
    Comparison operator for the OdGeEntity2d object.
    
    \returns
    A boolean value that indicates whether the input entity is not identical to this entity.
  */
  OdBool operator !=(
    const OdGeEntity2d& entity) const;

  /** \details
    Returns true if the specified entity is equal to this one.

    \remarks
    Returns true if and only if both entities are of the same type, have the same point set within the 
    specified tolerance, and have the same parameterization.

    \param other [in]  Entity to be compared
    \param tol [in]  Geometric tolerance.
  */
  OdBool isEqualTo(
    const OdGeEntity2d& other, 
    const OdGeTol& tol = OdGeContext::gTol) const;

  /** \details
    Applies the 2D transformation matrix to this entity, and returns
    a reference to this entity.

    \param xfm [in]  2D transformation matrix.
  */
  OdGeEntity2d& transformBy(
    const OdGeMatrix2d& xfm);

  /** \details
    Applies the 2D translation vector to this entity, and returns
    a reference to this entity.

    \param translateVec [in]  Translation Vector.
  */
  OdGeEntity2d& translateBy(
    const OdGeVector2d& translateVec);

  /** \details
    Rotates this entity about the specified point by the specified angle, and returns
    a reference to this entity.

    \param angle [in]  Rotation angle.
    \param basePoint [in]  Basepoint.
  */
  OdGeEntity2d& rotateBy(
    double angle, 
    const OdGePoint2d& basePoint = OdGePoint2d::kOrigin);

  /** \details
    Mirrors this entity about the specified 2D line, and returns
    a reference to this entity.

    \param line [in]  Mirror Line.
  */
  OdGeEntity2d& mirror(
    const OdGeLine2d& line);

  /** \details
    Scales this entity by the scale factor about the basepoint, and returns
    a reference to this entity.

    \param scaleFactor [in]  Scale Factor. The scale factor must be greater than zero.
    \param basePoint [in]  Basepoint.
  */
  OdGeEntity2d& scaleBy(
    double scaleFactor, 
    const OdGePoint2d& basePoint = OdGePoint2d::kOrigin);

  /** \details
    Returns true if and only if the specified point is on this entity, as determined by the tolerance.

    \param point [in]  Point to be queried.
    \param tol [in]  Geometric tolerance.
  */
  OdBool isOn(
    const OdGePoint2d& point, 
    const OdGeTol& tol = OdGeContext::gTol) const;

  ~OdGeEntity2d();
//DOM-IGNORE-BEGIN
protected:
#ifndef  USE_GCGE
  friend class OdGeEntity3d;
  friend class OdGeImpEntity3d;
  class OdGeImpEntity3d* mpImpEnt;
  int mDelEnt;
#endif
  OdGeEntity2d();
  OdGeEntity2d(const OdGeEntity2d&);
#ifdef  USE_GCGE
  void connectTo(OdGeEntity3dImpl*);
#else
  void connectTo(OdGeEntity2dImpl*);
  OdGeEntity2d(OdGeImpEntity3d& pEntity, int value);
  OdGeEntity2d(OdGeImpEntity3d* pEntity);
  OdGeEntity2d* newEntity2d(OdGeImpEntity3d* pEntity) const;
#endif

protected:
#ifdef  USE_GCGE
  OdGeEntity2d(OdGeEntity3dImpl*);
  OdGeEntity3dImpl* m_pImpl;
  friend class OdGeEntity3dImpl;
#else
  OdGeEntity2d(OdGeEntity2dImpl*);
  OdGeEntity2dImpl* m_pImpl;
  friend class OdGeEntity2dImpl;
#endif
//DOM-IGNORE-BEGIN
};

#ifndef  USE_GCGE
inline OdGeEntity2d*
OdGeEntity2d::newEntity2d(OdGeImpEntity3d *impEnt) const
{
  return GENEWLOC(OdGeEntity2d, this) (impEnt);
}
#endif

#include "../TD_PackPop.h"

#endif // OD_GE_ENTITY_2D_H

