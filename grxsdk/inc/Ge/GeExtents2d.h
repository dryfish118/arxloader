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

#ifndef _ODGEEXTENTS2D_INCLUDED_
#define _ODGEEXTENTS2D_INCLUDED_ /*!DOM*/

#include "../Ge/GePoint2d.h"
#include "../Ge/GePoint2dArray.h"
#include "../Ge/GeVector2d.h"
#include "../Ge/GeMatrix2d.h"

#include "../TD_PackPush.h"

#define INVALIDEXTENTS 1.0e20

/** \details
    This class represents 2D bounding boxes as minimum and maximum 2d points.

    Corresponding C++ library: TD_Ge

    <group OdGe_Classes> 
*/
class GE_TOOLKIT_EXPORT OdGeExtents2d
{
public:

  /** \details 
    Default constructor for the OdGeExtents2d class.
    
    \remarks
    Constructs invalid (not initialized) extents.
  */
  OdGeExtents2d ()
    : m_min (INVALIDEXTENTS,  INVALIDEXTENTS)
    , m_max (-INVALIDEXTENTS, -INVALIDEXTENTS)
  {}

  /** \details 
    Constructor for the OdGeExtents2d class.
    \param min [in]  Minimum point.
    \param max [in]  Maximum point.
  */
  OdGeExtents2d (
    const OdGePoint2d& min, 
    const OdGePoint2d& max) 
  { set (min, max); }

  /** \details
    The invalid extents.
  */
  GE_STATIC_EXPORT static const OdGeExtents2d kInvalid;

  /** \details
    Returns the minimum point of this Extents object.
  */
  const OdGePoint2d& minPoint () const 
  { return m_min; }

  /** \details
    Returns the maximum point of this Extents object.
  */
  const OdGePoint2d& maxPoint () const 
  { return m_max; }

  /** \details
  Returns the vector from minimal to maximal point.
  */
  OdGeVector2d diagonal () const 
  { return m_max - m_min; }

  /** \details
    Sets the minimum and maximum points for this Extents object.
    
    \param min [in]  Minimum point.
    \param max [in]  Maximum point.
  */
  void set ( const OdGePoint2d& min, const OdGePoint2d& max) 
  { 
    //ODA_ASSERT_ONCE(min.x <= max.x);
    //ODA_ASSERT_ONCE(min.y <= max.y);
    m_min = min; m_max = max; 
  }

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
    const OdGePoint2d& pt1,
    const OdGePoint2d& pt2);

  /** \details
    Updates the extents of this Extents object with the specified point.

    \param point [in]  A 2D point that is added to define new extents.
  */
  OdGeExtents2d& addPoint (
    const OdGePoint2d& point)
  {
    if ( !isValidExtents() )
    {
      m_max = m_min = point;
    }
    else
    {
      m_max.x = odmax (point.x, m_max.x);
      m_max.y = odmax (point.y, m_max.y);
      m_min.x = odmin (point.x, m_min.x);
      m_min.y = odmin (point.y, m_min.y);
    }
    return *this;
  }

  /** \details
    Updates the extents of this Extents object with the specified array of points.

    \param points [in]  Array of 2D points to define the extents.
  */
  OdGeExtents2d& addPoints(const OdGePoint2dArray& points);

  /** \details
    Updates the extents of this Extents object with the specified Extents object.
    
    \param extents [in]  2D Extents object with the points to be added.
  */
  OdGeExtents2d& addExt (
    const OdGeExtents2d& extents)
  {
    if (extents.isValidExtents ())
    {
      addPoint (extents.minPoint ());
      addPoint (extents.maxPoint ());
    }
    return *this;
  }

  /** \details
    Returns true if and only if this Extents object contains valid extents.
    
    \remarks
    Extents are valid if and only if each member of the minimum extents 
    is less than or equal to the corresponding member of maximum extents.
  */
  bool isValidExtents () const
  {
    return ( (m_max.x >= m_min.x) && (m_max.y >= m_min.y) );
  }

  /** \details
    Updates the extents of this Extents object by the specified vector.
    \param vect [in]  A 2D vector that defines where new points are located.
  */
  void expandBy (
    const OdGeVector2d& vect);

  /** \details
    Applies the 2D transformation matrix to the extents.

    \param xfm [in]  2D transformation matrix.
  */
  void transformBy (
    const OdGeMatrix2d& xfm);
    
  void translate (
    const OdGeVector2d &iShift)
  {
    m_min += iShift;
    m_max += iShift;
  }

  /** \details
    Indicates whether this Extents object contains the specified point.
    
    \param point [in]  A 2D point that is presumably contained inside this extents.
    \param tol [in]  Tolerance of measurement error.
    
    \returns
    Returns true if this Extents object contains the specified point. Otherwise
    returns false.
  */
  bool contains (
    const OdGePoint2d& point, const OdGeTol& tol = OdGeContext::gTol) const;

  /** \details
    Indicates whether this Extents object contains the specified Extents object.
    
    \param extents [in]  A 2D Extents object that is tested to be within this extents.
    \param tol [in]  Tolerance of measurement error.

    \returns
    Returns true if the specified Extents object is completely inside this
    Extents object. Otherwise returns false.
  */
  bool contains (
    const OdGeExtents2d& extents, const OdGeTol& tol = OdGeContext::gTol) const;

  /** \details
    Indicates whether the specified Extents object intersects this Extents object.

    \param extents [in]  A 2D Extents object.
    \param tol [in]  Tolerance of measurement error.

    \returns
    Returns true if and only if the specified Extents object does not intersect
    this Extents object. Otherwise returns false.
  */
  bool isDisjoint (
    const OdGeExtents2d& extents, const OdGeTol& tol = OdGeContext::gTol) const;  

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
    
    \param extents [in]  Any 2D Extents object.
    \param pResult [out]  Receives extents of the intersection.
    
    \remarks
    pResult object should be created by the caller. Possible return values are as follows.
    
    @untitled table
    kIntersectUnknown   Either or both Extents objects are invalid
    kIntersectNot       The Extents objects are NOT intersecting
    kIntersectOpIn      The specified Extents object is completely within this one
    kIntersectOpOut     This Extents object is completely within the specified one
    kIntersectOk        The Extents objectes are intersecting, and a result is returned
    
  */
  IntersectionStatus intersectWith (
    const OdGeExtents2d& extents, 
    OdGeExtents2d* pResult = 0) const;

  /** \details
    Returns a center point of this Extents object.
  */
  OdGePoint2d center() const
  {
    return OdGePoint2d(0.5 * (m_min.x + m_max.x), 0.5 * (m_min.y + m_max.y));
  }

  /** \details
    Checks if this Extents object is equal to the passed Extents object.
    
    \param extents [in]  A 2D Extents object to be tested for equality.
    \param tol [in]  Geometric tolerance.
    
    \remarks
    This method compares this object to the passed object by testing the equivalence of their definition points. 
    If the points match within the range specified by tolerance, this method returns true. Otherwise, it returns false.
  */
  bool isEqualTo(const OdGeExtents2d& extents, const OdGeTol& tol = OdGeContext::gTol) const;

  /** \details
    Comparison operator for the OdGeExtents2d object.
    
    \returns
    A boolean value that indicates whether the input Extents object is identical to this Extents object.
  */
  bool operator ==(const OdGeExtents2d& extents) const
  {
    return isEqualTo(extents);
  }
  
  /** \details
    Comparison operator for the OdGeExtents2d object.
    
    \returns
    A boolean value that indicates whether the input Extents object is not identical to this Extents object.
  */
  bool operator !=(const OdGeExtents2d& extents) const
  {
    return !isEqualTo(extents);
  }
//DOM-IGNORE-BEGIN
protected:
  OdGePoint2d m_min;
  OdGePoint2d m_max;
//DOM-IGNORE-END
};

// Inlines section

inline void OdGeExtents2d::comparingSet(const OdGePoint2d& pt1, const OdGePoint2d& pt2)
{
  m_min.x = odmin(pt1.x, pt2.x);
  m_max.x = odmax(pt1.x, pt2.x);
  m_min.y = odmin(pt1.y, pt2.y);
  m_max.y = odmax(pt1.y, pt2.y);
}

inline bool OdGeExtents2d::contains(const OdGePoint2d& point, const OdGeTol& tol) const
{
  //ODA_ASSERT(isValidExtents());   //note: empty/invalid box does NOT contain any point

  return ( (point.x + tol.equalPoint()) >= m_min.x
    && (point.y + tol.equalPoint()) >= m_min.y
    && (point.x - tol.equalPoint()) <= m_max.x
    && (point.y - tol.equalPoint()) <= m_max.y );
}

inline bool OdGeExtents2d::contains(const OdGeExtents2d& extents, const OdGeTol& tol) const
{
  ODA_ASSERT(isValidExtents());

  return ((extents.m_min.x + tol.equalPoint()) >= m_min.x 
    && (extents.m_min.y + tol.equalPoint()) >= m_min.y 
    && m_max.x >= (extents.m_max.x - tol.equalPoint()) 
    && m_max.y >= (extents.m_max.y - tol.equalPoint()));
}

inline bool OdGeExtents2d::isDisjoint(const OdGeExtents2d& extents, const OdGeTol& tol) const
{
  //ODA_ASSERT(isValidExtents());   //note: empty/invalid box is disjoint with everything

  return ((extents.m_min.x - tol.equalPoint()) > m_max.x 
    || (extents.m_min.y - tol.equalPoint()) > m_max.y 
    || m_min.x > (extents.m_max.x + tol.equalPoint())
    || m_min.y > (extents.m_max.y + tol.equalPoint()));
} 

/** \details
    Updates a minimum and maximum points according to coordinates of the input points.

    \param minPt [out] Resulting minimum point.
    \param maxPt [out] Resulting maximum point.
    \param pt1   [in]  First point to be processed.
    \param pt2   [in]  Second point to be processed.
  */
inline void pointsExtents(OdGePoint2d& minPt, OdGePoint2d& maxPt
  , const OdGePoint2d& pt1, const OdGePoint2d& pt2)
{
  if (pt1.x <= pt2.x)
  {
    minPt.x = pt1.x;
    maxPt.x = pt2.x;
  }
  else
  {
    minPt.x = pt2.x;
    maxPt.x = pt1.x;
  }

  if (pt1.y <= pt2.y)
  {
    minPt.y = pt1.y;
    maxPt.y = pt2.y;
  }
  else
  {
    minPt.y = pt2.y;
    maxPt.y = pt1.y;
  }
}

/** \details
    Updates one of the values of the extents ('minValue' or 'maxValue') if the specified 'value' is not between the minimum and maximum values.

    \param minValue [in/out] Receives a new minimum value if the specified 'value' is less than current 'minValue'.
    \param maxValue [in/out] Receives a new maximum value if the specified 'value' is greater than current 'maxValue'.
    \param value    [in]  Value to compare.

    \remarks
    'minValue' and 'maxValue' must be must be initialized. 'minValue' must be less than 'maxValue'.

    \returns
    Returns true if extents were extended (new 'minValue' or 'maxValue' was received), false otherwise ('value' lied between 'minValue' and 'maxValue').
  */
inline bool extendExtents(double& minValue, double& maxValue, const double& value)
{
  ODA_ASSERT(minValue <= maxValue);

  if (value < minValue)
  {
    minValue = value;

    return true;
  }

  if (value > maxValue)
  {
    maxValue = value;

    return true;
  }

  return false;
}

/** \details
    Extends point's coordinates of 'minPt' or/and 'maxPt' if coordinates of the 'pt' parameter are not between corresponding coordinates the minimum and maximum points.
    If 'pt' has one of coordinates (or both) less than 'minPt', these coordinates are assigned to 'minPt'.
    If 'pt' has one of coordinates (or both) greater than 'maxPt', these coordinates are assigned to 'maxPt'.

    \param minPt [in/out] Receives new coordinates for a minimum point.
    \param maxPt [in/out] Receives new coordinates for a maximum point.
    \param pt    [in]  Point to compare.

    \remarks
    'minPt' and 'maxPt' must be must be initialized.

    \returns
    Returns true if coordinates of 'minPt' or/and 'maxPt' have been changed, false otherwise.
  */
inline bool extendExtents(OdGePoint2d& minPt, OdGePoint2d& maxPt, const OdGePoint2d& pt)
{
  bool extended = extendExtents(minPt.x, maxPt.x, pt.x);

  extended |= extendExtents(minPt.y, maxPt.y, pt.y);

  return extended;
}

/** \details
    Checks whether the specified point lies in the extents defined by its minimum and maximum points.

    \param minPt [in] Point of the extents minimum.
    \param maxPt [in] Point of the extents maximum.
    \param pt    [in] Point to check.
    \param tol   [in] Geometric tolerance.

    \returns 
    Returns true if the point is placed in the extents or on its border, false otherwise.
  */
inline bool isBoxContainsPoint(const OdGePoint2d& minPt, const OdGePoint2d& maxPt
  , const OdGePoint2d& pt, const OdGeTol& tol = OdGeContext::gTol)
{
  ODA_ASSERT(minPt.x <= maxPt.x);
  ODA_ASSERT(minPt.y <= maxPt.y);

  return (OdGreaterOrEqual(pt.x, minPt.x, tol.equalPoint())
    && OdGreaterOrEqual(pt.y, minPt.y, tol.equalPoint())
    && OdLessOrEqual(pt.x, maxPt.x, tol.equalPoint())
    && OdLessOrEqual(pt.y, maxPt.y, tol.equalPoint()));
}

#undef INVALIDEXTENTS

#include "../TD_PackPop.h"

#endif //_ODGEEXTENTS2D_INCLUDED_
