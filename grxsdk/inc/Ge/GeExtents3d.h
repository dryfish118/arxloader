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

#ifndef _ODGEEXTENTS3D_INCLUDED_
#define _ODGEEXTENTS3D_INCLUDED_ /*!DOM*/

#include "../Ge/GePoint3d.h"
#include "../Ge/GeVector3d.h"
#include "../Ge/GeMatrix3d.h"

#include "../TD_PackPush.h"

class OdGeExtents2d;

#define INVALIDEXTENTS 1.0e20

/** \details
    This class represents 3D bounding boxes as minimum and maximum 3d points.

    Corresponding C++ library: TD_Ge

    <group OdGe_Classes> 
*/
class GE_TOOLKIT_EXPORT OdGeExtents3d
{
public:

  /** \details
    Default constructor for the OdGeExtents3d class.
  */
  OdGeExtents3d();

  /** \details
    Constructor for the OdGeExtents3d class.
    \param min [in]  Minimum point.
    \param max [in]  Maximum point.
  */
  OdGeExtents3d(
    const OdGePoint3d& min, 
    const OdGePoint3d& max);

  /** \details
    The invalid extents.
  */
  GE_STATIC_EXPORT static const OdGeExtents3d kInvalid;

  /** \details
    Returns the minimum point of this Extents object.
  */
  const OdGePoint3d& minPoint() const;

  /** \details
    Returns the maximum point of this Extents object.
  */
  const OdGePoint3d& maxPoint() const;

  /** \details
    Returns the vertex of the box depending on index.
    Minimum vertex is returned when iIndex = 0, maximum vertex otherwise.
  */
  const OdGePoint3d& operator[] (int iIndex) const {
    return iIndex == 0 ? m_min : m_max;
  }
  OdGePoint3d& operator[] (int iIndex) {
    return iIndex == 0 ? m_min : m_max;
  }

  /** \details
    Sets the minimum and maximum points for this Extents object.
    
    \param min [in]  Minimum point.
    \param max [in]  Maximum point.
  */
  OdResult set(
    const OdGePoint3d& min, 
    const OdGePoint3d& max);

  /** \details
    Sets the minimum and maximum points for this Extents object to
    that of the box defined by pt1 and pt2.
    
    \param pt1 [in]  First point that defines the extents.
    \param pt2 [in]  Second point that defines the extents.

    \remarks
    The passed first and second points are only needed to define a box. The points
    themselves do not necessarily need to be minimum and maximum points. The
    coordinates of the passed points are compared and then set to real minimum and maximum points.
  */
  void comparingSet(
    const OdGePoint3d& pt1, 
    const OdGePoint3d& pt2);

  /** \details
    Updates the extents of this Extents object with the specified point.

    \param point [in]  Any 3D point.
  */
  OdGeExtents3d& addPoint(
    const OdGePoint3d& point);

  /** \details
    Updates the extents of this Extents object with the specified point.

    \param point [in]  A 3D point that is added to define new extents.
  */
  OdGeExtents3d& addPoints(
    const OdGePoint3dArray& points);

  /** \details
    Updates the extents of this Extents object with the specified array of points.

    \param points [in]  Array of 3D points to define the extents.
  */
  OdGeExtents3d& addExt(
    const OdGeExtents3d& extents);

  /** \details
    Returns true if and only if this Extents object contains valid extents.
    
    \remarks
    Extents are valid if and only if each member of the minimum extents 
    is less than or equal to the corresponding member of maximum extents.
  */
  inline bool isValidExtents() const
  {
    return ( (m_max.x >= m_min.x) && (m_max.y >= m_min.y) && (m_max.z >= m_min.z));
  }

  /** \details
    Updates the extents of this Extents object by the specified vector.
    \param vect [in]  A 3D vector that defines where new points are located.
  */
    void expandBy(
    const OdGeVector3d& vect);

  /** \details
    Applies the 3D transformation matrix to the extents.

    \param xfm [in]  3D transformation matrix.
  */
  void transformBy(
    const OdGeMatrix3d& xfm);
    
  /** \details
    Returns true if and only if this Extents object contains the specified point.
    
    \param point [in]  A 3D point that is presumably contained inside this extents.
    \param tol [in]  Geometric tolerance.
  */
  bool contains(
    const OdGePoint3d& point, const OdGeTol& tol = OdGeContext::gTol) const;

  /** \details
    Returns true if and only if this Extents object contains the specified extents.
    
    \param extents [in]  A 3D Extents object that is tested to be within this extents.
    \param tol [in]  Geometric tolerance.
  */
  bool contains(
    const OdGeExtents3d& extents, const OdGeTol& tol = OdGeContext::gTol) const;

  /** \details
    Returns true if and only if specified Extents object
    does not intersect this one.

    \param extents [in]  Any 3D Extents object.
  */
  bool isDisjoint(
    const OdGeExtents3d& extents, const OdGeTol& tol = OdGeContext::gTol) const;

  /** \details
  Same as isDisjoint, but checks precisely whether minimal Euclidean distance is greater than tolerance.
  */
  bool isDisjointEuclidean(
    const OdGeExtents3d& extents, const OdGeTol& tol = OdGeContext::gTol) const;

  /** \details
  Returns 0.0 if point is inside the box or euclidean distance in other case
  */
  double distanceTo(const OdGePoint3d& iPoint) const;

  /** \details
  Types of intersection results.
  */
  enum IntersectionStatus
  {
    kIntersectUnknown,// Either or both extents are invalid
    kIntersectNot,    // Extents are NOT intersecting
    kIntersectOpIn,   // Operand is completely within this extents
    kIntersectOpOut,  // This extents is completely within operand
    kIntersectOk      // Extents are intersecting, result is returned
  };

  /** \details
    Determines the intersection of the specified Extents object with this one,
    and returns the resulting intersection box.
    
    \param extents [in]  Any 3D Extents object.
    \param pResult [out]  Receives extents of the intersection.
    
    \remarks
    pResult object should be created by the caller. Possible return values are as follows.
    
    @untitled table
    kIntersectUnknown   Either or both extents boxes are invalid
    kIntersectNot       The extents boxes are NOT intersecting
    kIntersectOpIn      The specified Extents object is completely within this one
    kIntersectOpOut     This Extents object is completely within the specified one
    kIntersectOk        The extents boxes are intersecting, and a result is returned
    
  */
  IntersectionStatus intersectWith(const OdGeExtents3d& extents, OdGeExtents3d* pResult = 0) const;
  
  /** \details
   Checks whether the box intersects the sphere with specified center and radius.
   
   \param pt [in]  A 3D point that represents the sphere center.
   \param radius [in]  A radius of the sphere.   
  */
  bool isWithinRange(const OdGePoint3d &pt, double radius);

  /** \details
    Returns a center point of this Extents object.
  */
  OdGePoint3d center() const
  {
    return m_min + (m_max - m_min) * 0.5;
  }
  
  /** \details
    Returns the vector from minimum to maximum point.
  */
  OdGeVector3d diagonal() const
  {
    return m_max - m_min;
  }

  /** \details
    Types of 2D planes.
  */
  enum Convert2dPlane
  {
    kConvert2dPlaneXY = 0x04,
    kConvert2dPlaneXZ = 0x08,
    kConvert2dPlaneYX = 0x01,
    kConvert2dPlaneYZ = 0x09,
    kConvert2dPlaneZX = 0x02,
    kConvert2dPlaneZY = 0x06
  };
  
  /** \details
    Converts this 3D Extents object to a 2D Extents object.
    
    \param extents [out]  Resulting converted 2D Extents object.
    \param plane [in]  Plane according to which conversion is calculated.
    
    \remarks
    This method sets minimum and maximum 2D points of this Extents object, eliminating one of the axes.
  */
  void convert2d(OdGeExtents2d &extents, Convert2dPlane plane = kConvert2dPlaneXY) const;
  
  /** \details
    Sets minimum and maximum points for this Extents object from a passed 2D Extents object.
    
    \param extents [in]  A 2D Extents object from which conversion is calculated.
    \param plane [in]  Plane on which the 2D Extents object lies.
    
    \remarks
    This method sets 0 to the coordinate on the axis that is absent in the passed 2D Extents object.
  */
  void setFrom2d(const OdGeExtents2d &extents, Convert2dPlane plane = kConvert2dPlaneXY);

  /** \details
    Checks if this Extents object is equal to the passed Extents object.
    
    \param extents [in]  A 3D Extents object to be compared for equality.
    \param tol [in]  Geometric tolerance.
    
    \remarks
    This method compares this object to the passed object by testing the equivalence of their definition points. 
    If the points match within the range specified by tolerance, this method returns true. Otherwise, it returns false.
  */
  bool isEqualTo(const OdGeExtents3d& extents, const OdGeTol& tol = OdGeContext::gTol) const;

  /** \details
    Comparison operator for the OdGeExtents3d object.
    
    \returns
    A boolean value that indicates whether the input Extents object is identical to this Extents object.
  */
  bool operator ==(const OdGeExtents3d& extents) const
  {
    return isEqualTo(extents);
  }
  
  /** \details
    Comparison operator for the OdGeExtents3d object.
    
    \returns
    A boolean value that indicates whether the input Extents object is not identical to this Extents object.
  */
  bool operator !=(const OdGeExtents3d& extents) const
  {
    return !isEqualTo(extents);
  }
//DOM-IGNORE-BEGIN
protected:
  OdGePoint3d m_min;
  OdGePoint3d m_max;
//DOM-IGNORE-END
};

// Inline implementations

inline OdGeExtents3d::OdGeExtents3d()
  : m_min(INVALIDEXTENTS,  INVALIDEXTENTS,  INVALIDEXTENTS)
  , m_max(-INVALIDEXTENTS, -INVALIDEXTENTS, -INVALIDEXTENTS)
{
}

inline OdGeExtents3d::OdGeExtents3d(const OdGePoint3d& min, const OdGePoint3d& max)
  : m_min(min)
  , m_max(max)
{
}

inline const OdGePoint3d& OdGeExtents3d::minPoint() const
{
  return m_min;
}

inline const OdGePoint3d& OdGeExtents3d::maxPoint() const
{
  return m_max;
}

inline OdResult OdGeExtents3d::set(const OdGePoint3d& min, const OdGePoint3d& max)
{
  //ODA_ASSERT_ONCE(min.x <= max.x);
  //ODA_ASSERT_ONCE(min.y <= max.y);
  //ODA_ASSERT_ONCE(min.z <= max.z);
  m_min = min;
  m_max = max;
  return Oda::eOk;
}

inline void OdGeExtents3d::comparingSet(const OdGePoint3d& pt1, const OdGePoint3d& pt2)
{
  m_min.x = odmin(pt1.x, pt2.x);
  m_max.x = odmax(pt1.x, pt2.x);
  m_min.y = odmin(pt1.y, pt2.y);
  m_max.y = odmax(pt1.y, pt2.y);
  m_min.z = odmin(pt1.z, pt2.z);
  m_max.z = odmax(pt1.z, pt2.z);
}

inline OdGeExtents3d& OdGeExtents3d::addPoint(const OdGePoint3d& point)
{
  if ((m_max.x < m_min.x) || (m_max.y < m_min.y) || (m_max.z < m_min.z))
  {
    //TODO: it's better to remove this case for better performance!
    m_max = m_min = point;
  }
  else
  {
    m_min.x = odmin(m_min.x, point.x);
    m_max.x = odmax(m_max.x, point.x);
    m_min.y = odmin(m_min.y, point.y);
    m_max.y = odmax(m_max.y, point.y);
    m_min.z = odmin(m_min.z, point.z);
    m_max.z = odmax(m_max.z, point.z);
  }
  return *this;
}

inline OdGeExtents3d& OdGeExtents3d::addExt(const OdGeExtents3d& extents)
{
  ODA_ASSERT(extents.isValidExtents());

#if 0
  addPoint(extents.minPoint());
  addPoint(extents.maxPoint());
#else
  if ((m_max.x < m_min.x) || (m_max.y < m_min.y) || (m_max.z < m_min.z))
  {
    //TODO: it's better to remove this case for better performance!
    set(extents.minPoint(), extents.maxPoint());
  }
  else
  {
    m_min.x = odmin(m_min.x, extents.m_min.x);
    m_max.x = odmax(m_max.x, extents.m_max.x);
    m_min.y = odmin(m_min.y, extents.m_min.y);
    m_max.y = odmax(m_max.y, extents.m_max.y);
    m_min.z = odmin(m_min.z, extents.m_min.z);
    m_max.z = odmax(m_max.z, extents.m_max.z);
  }
#endif
  return *this;
}

inline void OdGeExtents3d::expandBy(const OdGeVector3d& vect)
{
  ODA_ASSERT(isValidExtents());

  OdGePoint3d p1 = m_min, p2 = m_max;
  addPoint(p1 + vect);
  addPoint(p2 + vect);
}    

inline bool OdGeExtents3d::contains(const OdGePoint3d& point, const OdGeTol& tol) const
{
  //ODA_ASSERT(isValidExtents());   //note: empty/invalid box does NOT contain any point

  return ( (point.x + tol.equalPoint()) >= m_min.x
    && (point.y + tol.equalPoint()) >= m_min.y
    && (point.z + tol.equalPoint()) >= m_min.z
    && (point.x - tol.equalPoint()) <= m_max.x
    && (point.y - tol.equalPoint()) <= m_max.y
    && (point.z - tol.equalPoint()) <= m_max.z );
}

inline bool OdGeExtents3d::contains(const OdGeExtents3d& extents, const OdGeTol& tol) const
{
  ODA_ASSERT(isValidExtents());

  return ((extents.m_min.x + tol.equalPoint()) >= m_min.x 
    && (extents.m_min.y + tol.equalPoint()) >= m_min.y 
    && (extents.m_min.z + tol.equalPoint()) >= m_min.z 
    && m_max.x >= (extents.m_max.x - tol.equalPoint()) 
    && m_max.y >= (extents.m_max.y - tol.equalPoint()) 
    && m_max.z >= (extents.m_max.z - tol.equalPoint()));
}    

inline bool OdGeExtents3d::isDisjoint(const OdGeExtents3d& extents, const OdGeTol& tol) const
{
  //ODA_ASSERT(isValidExtents());   //note: empty/invalid box is disjoint with everything

  return ((extents.m_min.x - tol.equalPoint()) > m_max.x 
    || (extents.m_min.y - tol.equalPoint()) > m_max.y 
    || (extents.m_min.z - tol.equalPoint()) > m_max.z
    || m_min.x > (extents.m_max.x + tol.equalPoint())
    || m_min.y > (extents.m_max.y + tol.equalPoint())
    || m_min.z > (extents.m_max.z + tol.equalPoint()));
}    

#undef INVALIDEXTENTS

#include "../TD_PackPop.h"

#endif //_ODGEEXTENTS3D_INCLUDED_
