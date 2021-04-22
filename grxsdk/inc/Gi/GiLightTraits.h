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

#ifndef __OD_GI_LIGHT_TRAITS__
#define __OD_GI_LIGHT_TRAITS__

#include "../TD_PackPush.h"

#include "../OdaDefs.h"
#include "../Gi/GiExport.h"
#include "../Gi/Gi.h"
#include "GiDrawable.h"
#include "../OdString.h"
#include "../Ge/GeVector3d.h"
#include "../Gs/GsFiler.h"
#include "../CmColor.h"
#include "RxObject.h"


/** \details
    Corresponding C++ library: TD_Gi
    <group OdGi_Classes>
    \sa
    <link tv_working_with_lights, Working with Lights>
*/
class FIRSTDLL_EXPORT OdGiLightTraits : public OdGiNonEntityTraits
{
public:
  ODRX_DECLARE_MEMBERS(OdGiLightTraits);

  /** \details
    Specifies whether light is enabled.
    
    \param on [in]  Flag that specifies whether light is enabled.
  */
  virtual void setOn(bool on) = 0;
  
  /** \details
    Checks whether light is enabled.
    
    \returns
    true if light is enabled, false otherwise.
  */
  virtual bool isOn() const = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdGiLightTraits, OdGiLightTraits> object.
*/
typedef OdSmartPtr<OdGiLightTraits> OdGiLightTraitsPtr;

/** \details
    Corresponding C++ library: TD_Gi
    <group OdGi_Classes>
*/
struct OdGiColorRGB
{
  double red, green, blue;

  /** \details
    Default constructor for the OdGiColorRGB structure. Creates an object with red, green and blue components of a color set to 0.
  */
  OdGiColorRGB() : red(0.0), green(0.0), blue(0.0) { }
  
  /** \details
    Constructor for the OdGiColorRGB structure. Creates an object with specified red, green and blue components of a color.
    
    \param _red [in]  Red color component.
    \param _green [in]  Green color component.
    \param _blue [in]  Blue color component.
  */
  OdGiColorRGB(double _red, double _green, double _blue) : red(_red), green(_green), blue(_blue) { }

  friend OdGiColorRGB operator +(const OdGiColorRGB &c1, const OdGiColorRGB &c2)
  {
    return OdGiColorRGB(c1.red + c2.red, c1.green + c2.green, c1.blue + c2.blue);
  }
  friend OdGiColorRGB operator +(const OdGiColorRGB &c, double s)
  {
    return OdGiColorRGB(c.red + s, c.green + s, c.blue + s);
  }
  friend OdGiColorRGB operator +(double s, const OdGiColorRGB &c)
  {
    return OdGiColorRGB(s + c.red, s + c.green, s + c.blue);
  }

  friend OdGiColorRGB operator -(const OdGiColorRGB &c1, const OdGiColorRGB &c2)
  {
    return OdGiColorRGB(c1.red - c2.red, c1.green - c2.green, c1.blue - c2.blue);
  }
  friend OdGiColorRGB operator -(const OdGiColorRGB &c, double s)
  {
    return OdGiColorRGB(c.red - s, c.green - s, c.blue - s);
  }
  friend OdGiColorRGB operator -(double s, const OdGiColorRGB &c)
  {
    return OdGiColorRGB(s - c.red, s - c.green, s - c.blue);
  }

  friend OdGiColorRGB operator *(const OdGiColorRGB &c1, const OdGiColorRGB &c2)
  {
    return OdGiColorRGB(c1.red * c2.red, c1.green * c2.green, c1.blue * c2.blue);
  }
  friend OdGiColorRGB operator *(const OdGiColorRGB &c, double s)
  {
    return OdGiColorRGB(c.red * s, c.green * s, c.blue * s);
  }
  friend OdGiColorRGB operator *(double s, const OdGiColorRGB &c)
  {
    return OdGiColorRGB(s * c.red, s * c.green, s * c.blue);
  }

  friend OdGiColorRGB operator /(const OdGiColorRGB &c1, const OdGiColorRGB &c2)
  {
    return OdGiColorRGB(c1.red / c2.red, c1.green / c2.green, c1.blue / c2.blue);
  }
  friend OdGiColorRGB operator /(const OdGiColorRGB &c, double s)
  {
    return OdGiColorRGB(c.red / s, c.green / s, c.blue / s);
  }
  friend OdGiColorRGB operator /(double s, const OdGiColorRGB &c)
  {
    return OdGiColorRGB(s / c.red, s / c.green, s / c.blue);
  }
};

/** \details
    Corresponding C++ library: TD_Gi
    <group OdGi_Classes>
    \sa
    <link gi_shadows_rendering, Shadows Visualization>
*/
class FIRSTDLL_EXPORT OdGiShadowParameters : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdGiShadowParameters);
  /** \details
    Default constructor for the OdGiShadowParameters class. Initializes the following data members:
    
    <table>
    <B>Data member</B>    <B>Value</B>                              <B>Description</B>
    m_bShadowsOn          true                                      Flag that shows if shadows are enabled
    m_shadowMapSoftness   1                                         The number of pixels at the shadow edge that are diffused.
    m_bShapeVisible       false                                     Flag that shows if the light shape is visible in the rendering.
    m_shadowType          OdGiShadowParameters::kShadowsRayTraced   Method which is used to compute shadows cast from the light source.
    m_shadowMapSize       256                                       Shadow map size in pixels.
    m_shadowSamples       16                                        The number of shadow rays to shoot for the light. 
    m_lightShape          OdGiShadowParameters::kSphere             The shape of the extended light source.
    m_lightLength         0.0                                       The length of the extended light source.
    m_lightWidth          0.0                                       The width of the extended light source.
    m_lightRadius         0.0                                       Radius of the extended light source.
    </table>
  */
  OdGiShadowParameters();
  
  /** \details
    Copy constructor for the OdGiShadowParameters class.
    
    \param parms  [in] Shadow parameters to be copied.
  */
  OdGiShadowParameters(const OdGiShadowParameters &parms);

  /** \details
    Assignment operator for the OdGiShadowParameters class.
    
    \param parms  [in] Shadow parameters to be assigned.
    
    \returns
    reference to shadow parameters.
  */
  OdGiShadowParameters &operator =(const OdGiShadowParameters &parms);

  /** \details
    Equality operator for the OdGiShadowParameters class.
    
    \param parms  [in] Parameters to be compared.
    
    \returns
    true if these shadow parameters are equal to the passed shadow parameters, false otherwise.
  */
  bool operator ==(const OdGiShadowParameters &parms) const;
  
  /** \details
    Inequality operator for the OdGiShadowParameters class.
    
    \param parms  [in] Parameters to be compared.
    
    \returns
    true if these shadow parameters are bot equal to the passed shadow parameters, false otherwise.
  */
  bool operator !=(const OdGiShadowParameters &parms) const;

  /** \details
    Represents methods that are used to compute shadows.
  */
  enum ShadowType 
  {
    /** Ray-traced shadows. */
    kShadowsRayTraced = 0,
    /** Shadow maps. */
    kShadowMaps,
    /** The area-sampled shadow algorithm shows the effect of extended light sources.*/
    kAreaSampled
  };

  /** \details
    Represents shapes of the extended light sources.
  */
  enum ExtendedLightShape {
    /** Linear light source.*/
    kLinear = 0,
    /** Rectangular-shaped light source.*/
    kRectangle,
    /** Disk-shaped light source.*/
    kDisk,
    /** Cylinder-shaped light source.*/
    kCylinder,
    /** Sphere-shaped light source.*/
    kSphere
  };

  /** \details
    Specifies whether shadows are casted from the light.
    
    \param on  [in] Flag that specifies whether to enable shadows .
  */
  virtual void setShadowsOn(bool on);
  
  /** \details
    Checks whether shadows are casted from the light.
    
    \returns
    true if shadows are enabled, false otherwise.
  */
  virtual bool shadowsOn() const;

  
  
  /** \details
    Specifies type of the shadows.
    
    \param typ  [in]  Shadow type.
  */
  virtual void setShadowType(ShadowType typ);
  
  /** \details
    Retrieves a type a the shadow.
    
    \returns
    a value from the ShadowType enumeration that represents one of the shadow types.
  */
  virtual ShadowType shadowType() const;



  /** \details
    Specifies a shadow map size.
    
    \param sz  [in]  Shadow map size.
    
    \remarks
    Valid values are 64, 128, 256, 512, 1024, 2048, and 4096. Smaller values provide softer and smudged shadows,
    while greater values provide sharper shadows, therefore they require more resources to be calculated.
  */
  virtual bool setShadowMapSize(OdUInt16 sz);
  
  /** \details
    Retrieves a shadow map size.
    
    \returns
    shadow map size as OdUInt16 value.
    
    \remarks
    Returned values can be 64, 128, 256, 512, 1024, 2048, and 4096. Smaller values represent softer and smudged shadows,
    while greater values represent sharper shadows.
  */
  virtual OdUInt16 shadowMapSize() const;

  
  
  /** \details
    Specifies a shadow map softness.
    
    \param soft  [in]  Shadow map softness value.
    
    \remarks
    The passed parameter represents the number of pixels at the shadow edge that are diffused. This method
    is useful only if shadow type if kShadowMaps.
  */
  virtual bool setShadowMapSoftness(OdUInt8 soft);
  
  /** \details
    Retrieves a shadow map softness.
    
    \returns
    the number of pixels at the shadow edge that are diffused.
  */
  virtual OdUInt8 shadowMapSoftness() const;

  
  /** \details
    Specifies a number of shadow rays to use for the light.
    
    \param nSamples  [in]  The number of shadow rays to use for the light.
    
    \returns
    true.
    
    \remarks
    The number of samples controls the softness of sampled shadows. This method
    is useful only if shadow type if kAreaSampled.
  */
  virtual bool setShadowSamples(OdUInt16 nSamples);
  
  /** \details
    Retrieves a number of shadow rays to use for the light.
    
    \returns
    the number of shadow rays for the light as OdUInt16 value.
    
    \remarks
    The number of samples controls the softness of sampled shadows. This method
    is useful only if shadow type if kAreaSampled.
  */
  virtual OdUInt16 shadowSamples() const;

  
  
  /** \details
    Specifies whether light shape should be visible in the rendering.
    
    \param bVisibility  [in]  Flag that specifies whether light shape should be visible.
  */
  virtual void setShapeVisibility(bool bVisibility);
  
  /** \details
    Checks whether light shape is visible in the rendering.
    
    \returns
    true if light source is visible in the rendering, false otherwise.
  */
  virtual bool shapeVisibility() const;

  
  
  /** \details
    Specifies the shape of the extended light source.
    
    \param lightShape  [in]  Light shape for the extended light source.
    
    \remarks
    This method is useful only if shadow type is kAreaSampled.
  */
  virtual bool setExtendedLightShape(ExtendedLightShape lightShape);
  
  /** \details
    Retrieves the shape of the extended light source.
    
    \returns
    the shape of the extended light source as a value from the ExtendedLightShape enumeration.
  */
  virtual ExtendedLightShape extendedLightShape() const;

  
  
  /** \details
    Specifies the length of the extended light source.
    
    \param dLength  [in]  Length for the extended light source.
    
    \remarks
    This method is useful only if shadow type is kAreaSampled and the shape 
    of the extended light source is kLinear, kRectangle or kCylinder.
  */
  virtual bool setExtendedLightLength(double dLength);
  
  /** \details
    Retrieves the length of the extended light source.
    
    \returns
    the length of the extended light source as a value of the double type.
  */
  virtual double extendedLightLength() const;

  
  
  /** \details
    Specifies the width of the extended light source.
    
    \param dWidth  [in]  Width for the extended light source.
    
    \remarks
    This method is useful only if shadow type is kAreaSampled and the shape 
    of the extended light source is kLinear, kRectangle or kCylinder.
  */
  virtual bool setExtendedLightWidth(double dWidth);
  
  /** \details
    Retrieves the width of the extended light source.
    
    \returns
    the width of the extended light source as a value of the double type.
  */
  virtual double extendedLightWidth() const;

  
  
  /** \details
    Specifies the radius of the extended light source.
    
    \param dRadius  [in]  Radius for the extended light source.
    
    \returns
    true.
    
    \remarks
    This method is useful only if shadow type is kAreaSampled and the shape 
    of the extended light source is kDisk, kCylinder or kSphere.
  */
  virtual bool setExtendedLightRadius(double dRadius);
  
  /** \details
    Retrieves the radius of the extended light source.
    
    \returns
    radius for the extended light source as the value of the double type.
  */
  virtual double extendedLightRadius() const;

  
  
  /** \details
    Saves the shadow parameters to the specified filer.
    
    \param pFiler  [in]  Pointer to a filer to save parameters to.
  */
  inline void save(OdGsFiler * pFiler) const {
    pFiler->wrBool(shadowsOn());
    pFiler->wrUInt8((OdUInt8)shadowType());
    pFiler->wrUInt16(shadowMapSize());
    pFiler->wrUInt8(shadowMapSoftness());
    pFiler->wrBool(shapeVisibility());
    pFiler->wrUInt8((OdUInt8)extendedLightShape());
    pFiler->wrDouble(extendedLightLength());
    pFiler->wrDouble(extendedLightWidth());
    pFiler->wrDouble(extendedLightRadius());
  }

  /** \details
    Loads the shadow parameters from the specified filer.
    
    \param pFiler  [in]  Pointer to a filer to load parameters from.
  */
  inline void load(OdGsFiler * pFiler) {
    setShadowsOn(pFiler->rdBool());
    setShadowType((ShadowType)pFiler->rdUInt8());
    setShadowMapSize(pFiler->rdUInt16());
    setShadowMapSoftness(pFiler->rdUInt8());
    setShapeVisibility(pFiler->rdBool());
    setExtendedLightShape((ExtendedLightShape)pFiler->rdUInt8());
    setExtendedLightLength(pFiler->rdDouble());
    setExtendedLightWidth(pFiler->rdDouble());
    setExtendedLightRadius(pFiler->rdDouble());
  }


private:
  bool               m_bShadowsOn;
  OdUInt8            m_shadowMapSoftness;
  bool               m_bShapeVisible;
  ShadowType         m_shadowType;
  OdUInt16           m_shadowMapSize;
  OdUInt16           m_shadowSamples;
  ExtendedLightShape m_lightShape;
  double             m_lightLength;
  double             m_lightWidth;
  double             m_lightRadius;
};

inline OdGiShadowParameters::OdGiShadowParameters()
  : m_bShadowsOn(true)
  , m_shadowMapSoftness(1)
  , m_bShapeVisible(false)
  , m_shadowType(OdGiShadowParameters::kShadowsRayTraced)
  , m_shadowMapSize(256)
  , m_shadowSamples(16)
  , m_lightShape(kSphere)
  , m_lightLength(0.0)
  , m_lightWidth(0.0)
  , m_lightRadius(0.0)
{
}

inline OdGiShadowParameters::OdGiShadowParameters(const OdGiShadowParameters &parms)
  : m_bShadowsOn(parms.m_bShadowsOn)
  , m_shadowMapSoftness(parms.m_shadowMapSoftness)
  , m_bShapeVisible(parms.m_bShapeVisible)
  , m_shadowType(parms.m_shadowType)
  , m_shadowMapSize(parms.m_shadowMapSize)
  , m_shadowSamples(parms.m_shadowSamples)
  , m_lightShape(parms.m_lightShape)
  , m_lightLength(parms.m_lightLength)
  , m_lightWidth(parms.m_lightWidth)
  , m_lightRadius(parms.m_lightRadius)
{
}

inline OdGiShadowParameters &OdGiShadowParameters::operator =(const OdGiShadowParameters &parms)
{
  m_bShadowsOn        = parms.m_bShadowsOn;
  m_shadowType        = parms.m_shadowType;
  m_shadowMapSize     = parms.m_shadowMapSize;
  m_shadowMapSoftness = parms.m_shadowMapSoftness;
  m_shadowSamples     = parms.m_shadowSamples;
  m_bShapeVisible     = parms.m_bShapeVisible;
  m_lightShape        = parms.m_lightShape;
  m_lightLength       = parms.m_lightLength;
  m_lightWidth        = parms.m_lightWidth;
  m_lightRadius       = parms.m_lightRadius;
  return *this;
}

inline bool OdGiShadowParameters::operator ==(const OdGiShadowParameters &parms) const
{
  return (m_bShadowsOn        == parms.m_bShadowsOn)        &&
         (m_shadowType        == parms.m_shadowType)        &&
         (m_shadowMapSize     == parms.m_shadowMapSize)     &&
         (m_shadowMapSoftness == parms.m_shadowMapSoftness) &&
         (m_shadowSamples     == parms.m_shadowSamples)     &&
         (m_bShapeVisible     == parms.m_bShapeVisible)     &&
         (m_lightShape        == parms.m_lightShape)        &&
         OdEqual(m_lightLength , parms.m_lightLength)       &&
         OdEqual(m_lightWidth  , parms.m_lightWidth)        &&
         OdEqual(m_lightRadius , parms.m_lightRadius);
}

inline bool OdGiShadowParameters::operator !=(const OdGiShadowParameters &parms) const
{
  return (m_bShadowsOn        != parms.m_bShadowsOn)        ||
         (m_shadowType        != parms.m_shadowType)        ||
         (m_shadowMapSize     != parms.m_shadowMapSize)     ||
         (m_shadowMapSoftness != parms.m_shadowMapSoftness) ||
         (m_shadowSamples     != parms.m_shadowSamples)     ||
         (m_bShapeVisible     != parms.m_bShapeVisible)     ||
         (m_lightShape        != parms.m_lightShape)        ||
         !OdEqual(m_lightLength, parms.m_lightLength)       ||
         !OdEqual(m_lightWidth , parms.m_lightWidth)        ||
         !OdEqual(m_lightRadius, parms.m_lightRadius);
}

inline void OdGiShadowParameters::setShadowsOn(bool on)
{
  m_bShadowsOn = on;
}

inline bool OdGiShadowParameters::shadowsOn() const
{
  return m_bShadowsOn;
}

inline void OdGiShadowParameters::setShadowType(ShadowType typ)
{
  m_shadowType = typ;
}

inline OdGiShadowParameters::ShadowType OdGiShadowParameters::shadowType() const
{
  return m_shadowType;
}

inline bool OdGiShadowParameters::setShadowMapSize(OdUInt16 sz)
{
  if((sz & (sz-1)) == 0 && sz >= 64 && sz <= 4096) // valid values are 64, 128, 256, 512, 1024, 2048, and 4096
  {
    m_shadowMapSize = sz;    
    return true;
  }
  else
  {
    return false;
  }
}

inline OdUInt16 OdGiShadowParameters::shadowMapSize() const
{
  return m_shadowMapSize;
}

inline bool OdGiShadowParameters::setShadowMapSoftness(OdUInt8 soft)
{
  m_shadowMapSoftness = soft;
  return true;
}

inline OdUInt8 OdGiShadowParameters::shadowMapSoftness() const
{
  return m_shadowMapSoftness;
}

inline bool OdGiShadowParameters::setShadowSamples(OdUInt16 nSamples)
{
  m_shadowSamples = nSamples;
  return true;
}

inline OdUInt16 OdGiShadowParameters::shadowSamples() const
{
  return m_shadowSamples;
}

inline void OdGiShadowParameters::setShapeVisibility(bool bVisibility)
{
  m_bShapeVisible = bVisibility;
}

inline bool OdGiShadowParameters::shapeVisibility() const
{
  return m_bShapeVisible;
}

inline bool OdGiShadowParameters::setExtendedLightShape(OdGiShadowParameters::ExtendedLightShape lightShape)
{
  m_lightShape = lightShape;
  return true;
}

inline OdGiShadowParameters::ExtendedLightShape OdGiShadowParameters::extendedLightShape() const
{
  return m_lightShape;
}

inline bool OdGiShadowParameters::setExtendedLightLength(double dLength)
{
  m_lightLength = dLength;
  return true;
}

inline double OdGiShadowParameters::extendedLightLength() const
{
  return m_lightLength;
}

inline bool OdGiShadowParameters::setExtendedLightWidth(double dWidth)
{
  m_lightWidth = dWidth;
  return true;
}

inline double OdGiShadowParameters::extendedLightWidth() const
{
  return m_lightWidth;
}

inline bool OdGiShadowParameters::setExtendedLightRadius(double dRadius)
{
  m_lightRadius = dRadius;
  return true;
}

inline double OdGiShadowParameters::extendedLightRadius() const
{
  return m_lightRadius;
}

/** \details
    This class represents light attenuation parameters.
    
    Corresponding C++ library: TD_Gi
    <group OdGi_Classes>
    \sa
    <link tv_working_with_lights, Working with Lights>
*/
class FIRSTDLL_EXPORT OdGiLightAttenuation : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdGiLightAttenuation);

  /** \details
    Default constructor for the OdGiLightAttenuation class. Initializes the following data members:
    
    <table>
    <B>Data member</B>    <B>Value</B>                            <B>Description</B>
    m_attenType           OdGiLightAttenuation::kNone             Attenuation type for the light.
    m_bUseAttenLimits     false                                   Flag which shows whether attenuation limits are used.
    m_dAttenStartLimit    1.0                                     Start attenuation limit.
    m_dAttenEndLimit      10.0                                    End attenuation limit.
    </table>
  */
  OdGiLightAttenuation();

  virtual ~OdGiLightAttenuation();
  
  /** Represents attenuation types for lights. */
  enum AttenuationType 
  {
    /** No attenuation is used. */
    kNone = 0,
    /** Light intensity equals to the inverse of the linear distance from the light source. */
    kInverseLinear,
    /** Light intensity equals to the inverse of the square distance from the light source. This type of attenuation is the most physically accurate. */
    kInverseSquare
  };
  
  
  
  /** \details
    Specifies type of the light attenuation.
    
    \param typ  [in]  Attenuation type.
  */
  virtual void setAttenuationType(AttenuationType typ);
  
  /** \details
    Retrieves a type of the light attenuation.
    
    \returns
    a type of the light attenuation as a value from the AttenuationType enumeration.
  */
  virtual AttenuationType attenuationType() const;
  
  
  
  /** \details
    Specifies whether attenuation limits should be used.
    
    \param on  [in]  Flag that specifies whether attenuation limits should be used.
  */
  virtual void setUseLimits(bool on);
  
  /** \details
    Checks whether attenuation limits are used.
    
    \returns
    true if attenuation limits are used, false otherwise.
  */
  virtual bool useLimits() const;
  
  
  
  /** \details
    Specifies values for both start and end attenuation limits.
    
    \param startlim  [in]  Start limit that defines the distance from the light source where light begins to affect the scene.
    \param endlim  [in]  End limit that defines the distance beyond which objects are not affected by the light.
  */
  virtual void setLimits(double startlim, double endlim);
  
  /** \details
    Retrieves start attenuation limit.
    
    \returns
    start attenuation limit as a value of the double type.
    
    \remarks
    The start limit defines the distance from the light source where light begins to affect the scene. Object closer than the start limit are not lit.
  */
  virtual double startLimit() const;
  
  /** \details
    Retrieves end attenuation limit.
    
    \returns
    end attenuation limit as a value of the double type.
    
    \remarks
    The end limit defines the distance from the light source beyond which objects in the scene are not lit.
  */
  virtual double endLimit() const;
  
  
  
  /** \details
    Saves the light attenuation parameters to the specified filer.
    
    \param pFiler  [in]  Pointer to a filer to save parameters to.
  */
  void save(OdGsFiler *pFiler) const;
  
  /** \details
    Loads the light attenuation parameters from the specified filer.
    
    \param pFiler  [in]  Pointer to a filer to load parameters from.
  */
  void load(OdGsFiler *pFiler);

  /** \details
    Equality operator for the OdGiLightAttenuation object. Returns true if members of this OdGiLightAttenuation object
    is equal to the members other OdGiLightAttenuation object.

    \param other [in]  A OdGiLightAttenuation object to be compared with this OdGiLightAttenuation object.
  */
  bool operator ==(const OdGiLightAttenuation &other) const;

  /** \details
    Inequality operator for the OdGiLightAttenuation object. Returns true if members of this OdGiLightAttenuation object
    is not equal to the members other OdGiLightAttenuation object.

    \param scaleVec [in]  A scale vector to be compared with this scale vector.
  */
  bool operator !=(const OdGiLightAttenuation &other) const;

private:
  AttenuationType m_attenType;
  bool            m_bUseAttenLimits;
  double          m_dAttenStartLimit;
  double          m_dAttenEndLimit;
};

inline OdGiLightAttenuation::OdGiLightAttenuation()
: m_attenType(OdGiLightAttenuation::kNone)
, m_bUseAttenLimits(false)
, m_dAttenStartLimit(1.0)
, m_dAttenEndLimit(10.0)
{
}

inline OdGiLightAttenuation::~OdGiLightAttenuation()
{

}

inline void OdGiLightAttenuation::setAttenuationType(AttenuationType typ)
{
  m_attenType = typ;
}

inline OdGiLightAttenuation::AttenuationType OdGiLightAttenuation::attenuationType() const
{
  return m_attenType;
}
  
inline void OdGiLightAttenuation::setUseLimits(bool on)
{
  m_bUseAttenLimits = on;
}

inline bool OdGiLightAttenuation::useLimits() const
{
  return m_bUseAttenLimits;
}

inline void OdGiLightAttenuation::setLimits(double startlim, double endlim)
{
  m_dAttenStartLimit = startlim;
  m_dAttenEndLimit   = endlim;
}

inline double OdGiLightAttenuation::startLimit() const
{
  return m_dAttenStartLimit;
}

inline double OdGiLightAttenuation::endLimit() const
{
  return m_dAttenEndLimit;
}

inline void OdGiLightAttenuation::save(OdGsFiler * pFiler) const {
  pFiler->wrUInt8(OdUInt8(m_attenType));
  pFiler->wrBool(m_bUseAttenLimits);
  pFiler->wrDouble(m_dAttenStartLimit);
  pFiler->wrDouble(m_dAttenEndLimit);
}

inline void OdGiLightAttenuation::load(OdGsFiler * pFiler) {
  m_attenType = AttenuationType(pFiler->rdUInt8());
  m_bUseAttenLimits = pFiler->rdBool();
  m_dAttenStartLimit = pFiler->rdDouble();
  m_dAttenEndLimit = pFiler->rdDouble();
}

inline bool OdGiLightAttenuation::operator ==(const OdGiLightAttenuation &other) const
{
  return (m_attenType == other.m_attenType) &&
    (m_bUseAttenLimits == other.m_bUseAttenLimits) &&
    (m_dAttenStartLimit == other.m_dAttenStartLimit) &&
    (m_dAttenEndLimit == other.m_dAttenEndLimit);
 }

inline bool OdGiLightAttenuation::operator !=(const OdGiLightAttenuation &other) const
{
  return (m_attenType != other.m_attenType) ||
    (m_bUseAttenLimits != other.m_bUseAttenLimits) ||
    (m_dAttenStartLimit != other.m_dAttenStartLimit) ||
    (m_dAttenEndLimit != other.m_dAttenEndLimit);
}

/** \details
    This class contains all sky properties for OdDbSun objects.

    \sa
    TD_Gi

    <group OdGi_Classes> 
*/
class ODGI_EXPORT OdGiSkyParameters : public OdRxObject
{
public:

  ODRX_DECLARE_MEMBERS(OdGiSkyParameters);
  /** \details
    Default constructor for the OdGiSkyParameters class. Initializes the following data members:
    
    <table>
    <B>Data member</B>    <B>Value</B>            <B>Description</B>
    m_status              false                   Flag that shows if sky illumination is enabled.
    m_intensityFactor     1                       Intensity factor for the sky illumination.
    m_haze                0.0                     Turbulence of the atmosphere.
    m_horizonHeight       0.0                     WCS height of the horizon plane.
    m_horizonBlur         0.1                     Amount of blur between ground plane and sky.
    m_aerialPerspective   false                   Flag that shows if aerial perspective is applied.
    m_visibilityDistance  10000.0                 Distance at which 10% haze occlusion results.
    m_diskScale           4.0                     Sun disk scale.
    m_glowIntensity       1.0                     Intensity of the sun glow.
    m_diskIntensity       1.0                     Intensity of the sun disk.
    m_solarDiskSamples    8                       Number of samples for the solar disk.
    m_redBlueShift        0.0                     Red-blue shift value for the sky. 
    m_saturation          1.0                     Sky saturation level.
    m_groundColor         0xc2808080              Color of the ground plane.
    m_nightColor          0xc2010205              Color of the night sky.
    m_sunDirection        (0.35, 1.0, -0.25)      Sun direction vector.
    </table>
  */
  OdGiSkyParameters();

  /** \details
    Equality operator for the OdGiSkyParameters class.
    
    \param params  [in] Parameters to be compared.
    
    \returns
    true if these sky parameters are equal to the passed parameters, false otherwise.
  */
  bool operator==(const OdGiSkyParameters& params) const;

  
  
  /** \details
    Specifies whether sky illumination should be enabled.
    
    \param enable  [in]  Flag that specifies whether sky illumination should be enabled.
  */
  void setIllumination(bool enable);
  
  /** \details
    Checks whether sky illumination is enabled.
    
    \returns
    true if sky illumination is enabled, false otherwise.
  */
  bool illumination() const;

  
  
  /** \details
    Specifies intensity factor for the sky illumination.
    
    \param intensity  [in]  Intensity factor for the sky illumination.
  */
  bool setIntensityFactor(double intensity);
  
  /** \details
    Retrieves intensity factor for the sky illumination.
    
    \returns
    intensity factor for the sky illumination as a value of the double type. 
  */
  double intensityFactor() const;

  
  
  /** \details
    Specifies the turbulence of the atmosphere.
    
    \param haze  [in]  Turbulence of the atmosphere.
  */
  bool setHaze(double haze);
  
  /** \details
    Retrieves the turbulence value of the atmosphere.
    
    \returns
    turbulence of the atmosphere as a value of the double type.
  */
  double haze() const;

  
  
  /** \details
    Specifies the height of the horizon plane.
    
    \param height  [in]  	The world-space height of the horizon plane.
  */
  bool setHorizonHeight(double height);
  
  /** \details
    Retrieves the height of the horizon plane.
    
    \returns
    the height of the horizon plane in the world-space.
  */
  double horizonHeight() const;

  
  
  /** \details
    Specifies the amount of blur between ground plane and sky.
    
    \param blur  [in]  	The amount of blurring between ground plane and sky.
  */
  bool setHorizonBlur(double blur);
  
  /** \details
    Retrieves the amount of blur between ground plane and sky.
    
    \returns
    amount of blur between ground plane and sky.
  */
  double horizonBlur() const;

  
  
  /** \details
    Specifies the color of the ground plane.
    
    \param color  [in]  	Color of the ground plane.
  */
  void setGroundColor(const OdCmColor& color);
  
  /** \details
    Retrieves the color of the ground plane.
    
    \returns
    color of the ground plane as OdCmEntityColor instance.
  */
  OdCmColor groundColor() const;

  
  
  /** \details
    Specifies the color of the night sky.
    
    \param color  [in]  	Color of the night sky.
  */
  void setNightColor(const OdCmColor& color);
  
  /** \details
    Retrieves the color of the night sky.
    
    \returns
    color of the ground plane as OdCmEntityColor instance.
  */
  OdCmColor nightColor() const;

  
  
  /** \details
    Specifies whether aerial perspective should be applied.
    
    \param apply  [in]  	Flag that specifies whether aerial perspective should be applied.
  */
  void setAerialPerspective(bool apply);
  
  /** \details
    Checks whether aerial perspective should be applied.
    
    \returns
    true if aerial perspective is applied, false otherwise.
  */
  bool aerialPerspective() const;

  
  /** \details
    Specifies visibility haze distance.
    
    \param distance  [in]  	Distance at which 10% haze occlusion results.
  */
  bool setVisibilityDistance(double distance);
  
  /** \details
    Retrieves visibility haze distance.
    
    \returns
    distance at which 10% haze occlusion results.
  */
  double visibilityDistance() const;

  
  
  /** \details
    Specifies disk scale of sun.
    
    \param scale  [in]  	Scale of the sun disk.
  */
  bool setDiskScale(double scale);
  
  /** \details
    Retrieves scale of the sun disk.
    
    \returns
    disk scale of the sun as a value of the double value.
  */
  double diskScale() const;

  
  
  /** \details
    Specifies intensity of the sun glow.
    
    \param intensity  [in]  	Intensity of the sun glow.
  */
  bool setGlowIntensity(double intensity);
  
  /** \details
    Retrieves intensity of the sun glow.
    
    \returns
    intensity of the sun glow as a value of the double value.
  */
  double glowIntensity() const;

  
  
  /** \details
    Specifies intensity of the sun disk.
    
    \param intensity  [in]  	Intensity of the sun disk.
  */
  bool setDiskIntensity(double intensity);
  
  /** \details
    Retrieves intensity of the sun disk.
    
    \returns
    intensity of the sun disk as a value of the double value.
  */
  double diskIntensity() const;

  
  
  /** \details
    Specifies a number of samples for the sun disk.
    
    \param samples  [in]  	Sample quantity for the sun disk.
  */
  bool setSolarDiskSamples(OdUInt16 samples);
  
  /** \details
    Retrieves a number of samples for the sun disk.
    
    \returns
    sample quantity for the sun disk as a value of the double type.
  */
  OdUInt16 solarDiskSamples() const;

  
  
  /** \details
    Specifies a direction from the sun to a model.
    
    \param sundir  [in]  	Vector that specifies the direction from the sun to a model.
  */
  bool setSunDirection(const OdGeVector3d& sundir);
  
  /** \details
    Retrieves a direction from the sun to a model.
    
    \returns
    a vector that specifies the direction from the sun to a model.
  */
  const OdGeVector3d& sunDirection() const;

  
  
  /** \details
    Specifies how much a color of the sky is shifted to red or blue.
    
    \param redBlueShift  [in]  	Value in [-1..1] range where -1 represents a maximum shift to blue sky, while 1 represents a maximum shift to red sky.
  */
  bool setRedBlueShift(double redBlueShift);
  
  /** \details
    Retrieves a value that shows how much a color of the sky is shifted to red or blue.
    
    \returns
    a value in [-1..1] range where -1 represents a maximum shift to blue sky and 1 represents a maximum shift to red sky.
  */
  double redBlueShift() const;

  
  
  /** \details
    Specifies sky saturation.
    
    \param saturation  [in]  	Sky saturation.
  */
  bool setSaturation(double saturation);
  
  /** \details
    Retrieves sky saturation value.
    
    \returns
    sky saturation as value of the double type.
  */
  double saturation() const;
protected:
  virtual void setIlluminationImp(bool enable);
  virtual bool illuminationImp(void) const;

  virtual bool setIntensityFactorImp(double intensity);
  virtual double intensityFactorImp() const;

  virtual bool setHazeImp(double haze);
  virtual double hazeImp(void) const;

  virtual bool setHorizonHeightImp(double height);
  virtual double horizonHeightImp(void) const;

  virtual bool setHorizonBlurImp(double blur);
  virtual double horizonBlurImp() const;

  virtual void setGroundColorImp(const OdCmColor& color);
  virtual OdCmColor groundColorImp() const;

  virtual void setNightColorImp(const OdCmColor& color);
  virtual OdCmColor nightColorImp() const;

  virtual void setAerialPerspectiveImp(bool apply);
  virtual bool aerialPerspectiveImp() const;

  virtual bool setVisibilityDistanceImp(double distance);
  virtual double visibilityDistanceImp() const;

  virtual bool setDiskScaleImp(double scale);
  virtual double diskScaleImp() const;

  virtual bool setGlowIntensityImp(double intensity);
  virtual double glowIntensityImp() const;

  virtual bool setDiskIntensityImp(double intensity);
  virtual double diskIntensityImp() const;

  virtual bool setSolarDiskSamplesImp(OdUInt16 samples);
  virtual OdUInt16 solarDiskSamplesImp(void) const;

  virtual bool  setSunDirectionImp(const OdGeVector3d& sundir);
  virtual const OdGeVector3d& sunDirectionImp(void) const;

  virtual bool setRedBlueShiftImp(double redBlueShift);
  virtual double  redBlueShiftImp(void) const;

  virtual bool setSaturationImp(double saturation);
  virtual double  saturationImp(void) const;
private:
  bool            m_status;
  double          m_intensityFactor;
  double          m_haze;
  double          m_horizonHeight;
  double          m_horizonBlur;
  OdCmEntityColor m_groundColor;
  OdCmEntityColor m_nightColor;
  bool            m_aerialPerspective;
  double          m_visibilityDistance;
  double          m_diskScale;
  double          m_glowIntensity;
  double          m_diskIntensity;
  OdUInt16        m_solarDiskSamples;
  OdGeVector3d    m_sunDirection;
  double          m_redBlueShift;
  double          m_saturation;
};

inline OdGiSkyParameters::OdGiSkyParameters()
: m_status(false)
, m_intensityFactor(1.0)
, m_haze(0.0)
, m_horizonHeight(0.0)
, m_horizonBlur(0.1)
, m_aerialPerspective(false)
, m_visibilityDistance(10000.0)
, m_diskScale(4.0)
, m_glowIntensity(1.0)
, m_diskIntensity(1.0)
, m_solarDiskSamples(8)
, m_redBlueShift(0.0)
, m_saturation(1.0)
{
  m_groundColor.setColor(0xc2808080);
  m_nightColor.setColor(0xc2010205);
  m_sunDirection.set(0.35, 1.0, -0.25);
}

inline bool OdGiSkyParameters::operator==(const OdGiSkyParameters& params) const
{
  if (m_status             != params.m_status)             return false;
  if (m_intensityFactor    != params.m_intensityFactor)    return false;
  if (m_haze               != params.m_haze)               return false;
  if (m_horizonHeight      != params.m_horizonHeight)      return false;
  if (m_horizonBlur        != params.m_horizonBlur)        return false;
  if (m_groundColor        != params.m_groundColor)        return false;
  if (m_nightColor         != params.m_nightColor)         return false;
  if (m_aerialPerspective  != params.m_aerialPerspective)  return false;
  if (m_visibilityDistance != params.m_visibilityDistance) return false;
  if (m_diskScale          != params.m_diskScale)          return false;
  if (m_glowIntensity      != params.m_glowIntensity)      return false;
  if (m_diskIntensity      != params.m_diskIntensity)      return false;
  if (m_solarDiskSamples   != params.m_solarDiskSamples)   return false;
  if (m_sunDirection       != params.m_sunDirection)       return false;
  if (m_redBlueShift       != params.m_redBlueShift)       return false;
  if (m_saturation         != params.m_saturation)         return false;
  return true;
}

inline void OdGiSkyParameters::setIllumination(bool enable)
{
  setIlluminationImp(enable);
}
inline bool OdGiSkyParameters::illumination() const
{
  return illuminationImp();
}
inline bool OdGiSkyParameters::setIntensityFactor(double intensity)
{
  return setIntensityFactorImp(intensity);
}
inline double OdGiSkyParameters::intensityFactor() const
{
  return intensityFactorImp();
}
inline bool OdGiSkyParameters::setHaze(double haze)
{
  return setHazeImp(haze);
}
inline double OdGiSkyParameters::haze() const
{
  return hazeImp();
}
inline bool OdGiSkyParameters::setHorizonHeight(double height)
{
  return setHorizonHeightImp(height);
}
inline double OdGiSkyParameters::horizonHeight() const
{
  return horizonHeightImp();
}
inline bool OdGiSkyParameters::setHorizonBlur(double blur)
{
  return setHorizonBlurImp(blur);
}
inline double OdGiSkyParameters::horizonBlur() const
{
  return horizonBlurImp();
}
inline void OdGiSkyParameters::setGroundColor(const OdCmColor& color)
{
  setGroundColorImp(color);
}
inline OdCmColor OdGiSkyParameters::groundColor() const
{
  return groundColorImp();
}
inline void OdGiSkyParameters::setNightColor(const OdCmColor& color)
{
  setNightColorImp(color);
}
inline OdCmColor OdGiSkyParameters::nightColor() const
{
  return nightColorImp();
}
inline void OdGiSkyParameters::setAerialPerspective(bool apply)
{
  setAerialPerspectiveImp(apply);
}
inline bool OdGiSkyParameters::aerialPerspective() const
{
  return aerialPerspectiveImp();
}
inline bool OdGiSkyParameters::setVisibilityDistance(double distance)
{
  return setVisibilityDistanceImp(distance);
}
inline double OdGiSkyParameters::visibilityDistance() const
{
  return visibilityDistanceImp();
}
inline bool OdGiSkyParameters::setDiskScale(double scale)
{
  return setDiskScaleImp(scale);
}
inline double OdGiSkyParameters::diskScale() const
{
  return diskScaleImp();
}
inline bool OdGiSkyParameters::setGlowIntensity(double intensity)
{
  return setGlowIntensityImp(intensity);
}
inline double OdGiSkyParameters::glowIntensity() const
{
  return glowIntensityImp();
}
inline bool OdGiSkyParameters::setDiskIntensity(double intensity)
{
  return setDiskIntensityImp(intensity);
}
inline double OdGiSkyParameters::diskIntensity() const
{
  return diskIntensityImp();
}
inline bool OdGiSkyParameters::setSolarDiskSamples(OdUInt16 samples)
{
  return setSolarDiskSamplesImp(samples);
}
inline OdUInt16 OdGiSkyParameters::solarDiskSamples() const
{
  return solarDiskSamplesImp();
}
inline bool OdGiSkyParameters::setSunDirection(const OdGeVector3d& sundir)
{
  return setSunDirectionImp(sundir);
}
inline const OdGeVector3d& OdGiSkyParameters::sunDirection() const
{
  return sunDirectionImp();
}
inline bool OdGiSkyParameters::setRedBlueShift(double redBlueShift)
{
  return setRedBlueShiftImp(redBlueShift);
}
inline double OdGiSkyParameters::redBlueShift() const
{
  return redBlueShiftImp();
}
inline bool OdGiSkyParameters::setSaturation(double saturation)
{
  return setSaturationImp(saturation);
}
inline double OdGiSkyParameters::saturation() const
{
  return saturationImp();
}

inline void OdGiSkyParameters::setIlluminationImp(bool enable)
{
  m_status = enable;
}
inline bool OdGiSkyParameters::illuminationImp(void) const
{
  return m_status;
}

inline bool OdGiSkyParameters::setIntensityFactorImp(double intensity)
{
  m_intensityFactor = intensity;
  return true;
}
inline double OdGiSkyParameters::intensityFactorImp() const
{
  return m_intensityFactor;  
}

inline bool OdGiSkyParameters::setHazeImp(double haze)
{
  m_haze = haze;
  return true;
}
inline double OdGiSkyParameters::hazeImp(void) const
{
  return m_haze;
}

inline bool OdGiSkyParameters::setHorizonHeightImp(double height)
{
  m_horizonHeight = height;
  return true;
}
inline double OdGiSkyParameters::horizonHeightImp(void) const
{
  return m_horizonHeight;
}

inline void OdGiSkyParameters::setGroundColorImp(const OdCmColor& color)
{
  m_groundColor = color.entityColor();
}

inline OdCmColor OdGiSkyParameters::groundColorImp() const
{
  OdCmColor clr;
  clr.setColor(m_groundColor.color());
  return clr;
}

inline void OdGiSkyParameters::setNightColorImp(const OdCmColor& color)
{
  m_nightColor = color.entityColor();
}

inline OdCmColor OdGiSkyParameters::nightColorImp() const
{
  OdCmColor clr;
  clr.setColor(m_nightColor.color());
  return clr;  
}

inline bool OdGiSkyParameters::setHorizonBlurImp(double blur)
{
  m_horizonBlur = blur;
  return true;
}
inline double OdGiSkyParameters::horizonBlurImp() const
{
  return m_horizonBlur;
}

inline void OdGiSkyParameters::setAerialPerspectiveImp(bool apply)
{
  m_aerialPerspective = apply;
}
inline bool OdGiSkyParameters::aerialPerspectiveImp() const
{
  return m_aerialPerspective;  
}

inline bool OdGiSkyParameters::setVisibilityDistanceImp(double distance)
{
  m_visibilityDistance = distance;
  return true;
}
inline double OdGiSkyParameters::visibilityDistanceImp() const
{
  return m_visibilityDistance;
}

inline bool OdGiSkyParameters::setDiskScaleImp(double scale)
{
  m_diskScale = scale;
  return true;
}
inline double OdGiSkyParameters::diskScaleImp() const
{
  return m_diskScale;
}

inline bool OdGiSkyParameters::setGlowIntensityImp(double intensity)
{
  m_glowIntensity = intensity;
  return true;
}
inline double OdGiSkyParameters::glowIntensityImp() const
{
  return m_glowIntensity;
}

inline bool OdGiSkyParameters::setDiskIntensityImp(double intensity)
{
  m_diskIntensity = intensity;
  return true;
}
inline double OdGiSkyParameters::diskIntensityImp() const
{
  return m_diskIntensity;
}

inline bool OdGiSkyParameters::setSolarDiskSamplesImp(OdUInt16 samples)
{
  m_solarDiskSamples = samples;
  return true;
}
inline OdUInt16 OdGiSkyParameters::solarDiskSamplesImp(void) const
{
  return m_solarDiskSamples;
}

inline bool OdGiSkyParameters::setSunDirectionImp(const OdGeVector3d& sundir)
{
  m_sunDirection = sundir;
  return true;
}
inline const OdGeVector3d& OdGiSkyParameters::sunDirectionImp(void) const
{
  return m_sunDirection;
}

inline bool OdGiSkyParameters::setRedBlueShiftImp(double redBlueShift)
{
  m_redBlueShift = redBlueShift;
  return true;
}
inline double OdGiSkyParameters::redBlueShiftImp(void) const
{
  return m_redBlueShift;
}

inline bool OdGiSkyParameters::setSaturationImp(double saturation)
{
  m_saturation = saturation;
  return true;
}
inline double OdGiSkyParameters::saturationImp(void) const
{
  return m_saturation;
}

ODGI_EXPORT void odgiSetSkyParametersGroundColor(OdGiSkyParameters* pParameters, const OdCmEntityColor& clr);
ODGI_EXPORT void odgiSetSkyParametersNightColor(OdGiSkyParameters* pParameters, const OdCmEntityColor& clr);
/** \details
    Represents characteristics of a standard light source.
    
    Corresponding C++ library: TD_Gi
    <group OdGi_Classes>
    \sa
    <link tv_working_with_lights, Working with Lights>
*/
class FIRSTDLL_EXPORT OdGiStandardLightTraits : public OdGiLightTraits
{
public:
  ODRX_DECLARE_MEMBERS(OdGiStandardLightTraits);

  /** \details
    Specifies intensity of a light source.
    
    \param inten  [in]  Light source intensity.
  */
  virtual void setIntensity(double inten) = 0;

  /** \details
    Retrieves intensity of a light source.
    
    \returns
    the intensity of the light source as a value of the double type.
  */
  virtual double intensity() const = 0;

  
  
  /** \details
    Specifies color of a light source.
    
    \param color  [in]  Color of the emitted light.
  */
  virtual void setLightColor(const OdCmColor& color) = 0;
  
  /** \details
    Retrieves color of a light source.
    
    \returns
    color of the emitted light as OdCmEntityColor instance.
  */
  virtual OdCmColor lightColor() const = 0;

  
  
  /** \details
    Specifies shadow parameters for this light source.
    
    \param params  [in]  Shadow parameters.
  */
  virtual void setShadowParameters(const OdGiShadowParameters& params) = 0;
  
  /** \details
    Retrieves shadow parameters of this light source.
    
    \returns
    shadow parameters as OdGiShadowParameters instance.
  */
  virtual void shadowParameters(OdGiShadowParameters&) const = 0;
};

ODGI_EXPORT void odgiSetStandardLightTraitsLightColor(OdGiStandardLightTraits* pLightTraits, const OdCmEntityColor& clr);
/** \details
  A data type that represents a smart pointer to an <link OdGiStandardLightTraits, OdGiStandardLightTraits> object.
*/
typedef OdSmartPtr<OdGiStandardLightTraits> OdGiStandardLightTraitsPtr;

/** \details
    Represents characteristics for the point light. This type of light source emits light in all directions.
    
    Corresponding C++ library: TD_Gi
    <group OdGi_Classes>
    \sa
    <link tv_working_with_lights, Working with Lights>
*/
class FIRSTDLL_EXPORT OdGiPointLightTraits : public OdGiStandardLightTraits
{
public:
  ODRX_DECLARE_MEMBERS(OdGiPointLightTraits);

  /** \details
    Specifies position of the point light source.
    
    \param pos  [in]  Point light source position.
  */
  virtual void setPosition(const OdGePoint3d& pos) = 0;
  
  /** \details
    Retrieves position of the point light source.
    
    \returns
    point light position as OdGePoint3d instance.
  */
  virtual OdGePoint3d position() const = 0;

  
  
  /** \details
    Retrieves light attenuation parameters for this light source.
    
    \returns
    light attenuation parameters as OdGiLightAttenuation instance.
  */
  virtual void lightAttenuation(OdGiLightAttenuation&) const = 0;
  
  /** \details
    Specifies attenuation light parameters for the point light source.
    
    \param atten  [in]  Point light source position.
  */
  virtual void setAttenuation(const OdGiLightAttenuation& atten) = 0;

  
  
  /** \details
    Specifies physical intensity for this light source in candela.
    
    \param fIntensity  [in]  Physical intensity of the light in candela.
  */
  virtual void setPhysicalIntensity(double fIntensity) = 0;
  
  /** \details
    Retrieves physical intensity for this light source in candela.
    
    \returns
    physical intensity of the light as a value of the double type.
  */
  virtual double physicalIntensity() const = 0;

  
  
  /** \details
    Specifies color for the light lamp.
    
    \param color  [in]  RGB color value.
  */
  virtual void setLampColor(const OdGiColorRGB& color) = 0;
  
  /** \details
    Retrieves color of the light lamp.
    
    \returns
    color of the light lamp as OdGiColorRGB instance.
  */
  virtual void lampColor(OdGiColorRGB&) const = 0;

  
  
  /** \details
    Specifies whether this point should have an associated target grip displayed.
    
    \param bTarget  [in]  Flag that specifies whether to display a target grip for orienting the light.
  */
  virtual void setHasTarget(bool bTarget) = 0;
  
  /** \details
    Checks whether this point has an associated target grip displayed.
    
    \returns
    true if light displays a target grip, false otherwise.
  */
  virtual bool hasTarget() const = 0;

  
  
  /** \details
    Specifies target location of the light.
    
    \param loc  [in]  Location of the target. Must differ from the point light position.
  */
  virtual void setTargetLocation(const OdGePoint3d &loc) = 0;
  
  /** \details
    Retrieves target location of the light.
    
    \returns
    target location of the light as OdGePoint3d instance.
  */
  virtual OdGePoint3d targetLocation() const = 0;

  
  
  virtual void setHemisphericalDistribution(bool bHemisphere) = 0;
  virtual bool hemisphericalDistribution() const = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdGiPointLightTraits, OdGiPointLightTraits> object.
*/
typedef OdSmartPtr<OdGiPointLightTraits> OdGiPointLightTraitsPtr;


/** \details
    Represents characteristics for the spot light. This type of light source emits a cone of light in a specified direction.
    Corresponding C++ library: TD_Gi
    <group OdGi_Classes>
    \sa
    <link tv_working_with_lights, Working with Lights>
*/
class FIRSTDLL_EXPORT OdGiSpotLightTraits : public OdGiStandardLightTraits
{
public:
  ODRX_DECLARE_MEMBERS(OdGiSpotLightTraits);

  /** \details
    Specifies position of the spot light source.
    
    \param pos  [in]  Spot light source position.
  */
  virtual void setPosition(const OdGePoint3d& pos) = 0;
  
  /** \details
    Retrieves position of the spot light source.
    
    \returns
     position of the spot light source as OdGePoint3d instance.
  */
  virtual OdGePoint3d position() const = 0;

  
  
  /** \details
    Specifies target location of the light.
    
    \param loc  [in]  Location of the target. Must differ from the spot light position.
  */
  virtual void setTargetLocation(const OdGePoint3d& loc) = 0;
  
  /** \details
    Retrieves target location of the light.
    
    \returns
    target location of the light as OdGePoint3d instance.
  */
  virtual OdGePoint3d targetLocation() const = 0;

  
  
  /** \details
    Specifies target location of the light.
    
    \param hotspot  [in]  Hotspot cone angle, in radians. Defines the brightest part of the spot light beam.
    \param falloff  [in]  Falloff angle, in radians. Defines the full cone of light.
  */
  virtual bool setHotspotAndFalloff(double hotspot, double falloff) = 0;
  
  /** \details
    Retrieves the cone angle that produces the brightest part of the beam (hotspot) of this light.
    
    \returns
    cone of the hotspot as a value of the double type.
  */
  virtual double hotspot() const = 0;
  
  /** \details
    Retrieves the cone angle that produces the light falloff.
    
    \returns
    cone of the falloff as a value of the double type.
  */
  virtual double falloff() const = 0;

  
  
  /** \details
    Retrieves light attenuation parameters for this light source.
    
    \returns
    light attenuation parameters as OdGiLightAttenuation instance.
  */
  virtual void lightAttenuation(OdGiLightAttenuation&) const = 0;
  
  /** \details
    Specifies attenuation light parameters for the point light source.
    
    \param atten  [in]  Point light source position.
  */
  virtual void setAttenuation(const OdGiLightAttenuation& atten) = 0;

  
  
  /** \details
    Specifies physical intensity for this light source in candela.
    
    \param fIntensity  [in]  Physical intensity of the light in candela.
  */
  virtual void setPhysicalIntensity(double fIntensity) = 0;
  
  /** \details
    Retrieves physical intensity for this light source in candela.
    
    \returns
    physical intensity of the light as a value of the double type.
  */
  virtual double physicalIntensity() const = 0;

  
  
  /** \details
    Specifies color for the light lamp.
    
    \param color  [in]  RGB color value.
  */
  virtual void setLampColor(const OdGiColorRGB& color) = 0;
  
  /** \details
    Retrieves color of the light lamp.
    
    \returns
    color of the light lamp as OdGiColorRGB instance.
  */
  virtual void lampColor(OdGiColorRGB&) const = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdGiSpotLightTraits, OdGiSpotLightTraits> object.
*/
typedef OdSmartPtr<OdGiSpotLightTraits> OdGiSpotLightTraitsPtr;


/** \details
    Represents characteristics for the distant light. This type of light source is located infinitely far from the scene and emits light in a specified direction.
    Corresponding C++ library: TD_Gi
    <group OdGi_Classes>
    \sa
    <link tv_working_with_lights, Working with Lights>
*/
class FIRSTDLL_EXPORT OdGiDistantLightTraits : public OdGiStandardLightTraits
{
public:
  ODRX_DECLARE_MEMBERS(OdGiDistantLightTraits);
  
  /** \details
    Specifies direction of the distant light.
    
    \param vec  [in]  Light direction.
  */
  virtual void setLightDirection(const OdGeVector3d& vec) = 0;
  
  /** \details
    Retrieves direction of the distant light.
    
    \returns
    direction of the distant light as OdGeVector3d instance.
  */
  virtual OdGeVector3d lightDirection() const = 0;
  
  
  
  /** \details
    Specifies whether this light is rendered as sunlight.
    
    \param isSunlight  [in]  Flag that specifies whether to render this light as sunlight.
  */
  virtual void setIsSunlight(bool isSunlight) = 0;
  
  /** \details
    Checks whether this light is rendered as sunlight.
    
    \returns
    true if this light is rendered as sunlight, false otherwise.
  */
  virtual bool isSunlight() const = 0;

  
  
  /** \details
    Specifies physical intensity for this light source in candela.
    
    \param fIntensity  [in]  Physical intensity of the light in candela.
  */
  virtual void setPhysicalIntensity(double fIntensity) = 0;
  
  /** \details
    Retrieves physical intensity for this light source in candela.
    
    \returns
    physical intensity of the light as a value of the double type.
  */
  virtual double physicalIntensity() const = 0;

  
  
  /** \details
    Specifies color for the light lamp.
    
    \param color  [in]  RGB color value.
  */
  virtual void setLampColor(const OdGiColorRGB& color) = 0;
  
  /** \details
    Retrieves color of the light lamp.
    
    \returns
    color of the light lamp as OdGiColorRGB instance.
  */
  virtual void lampColor(OdGiColorRGB&) const = 0;

  
  
  /** \details
    Specifies sky parameters for this light.
    
    \param params  [in]  Sky properties for this light.
  */
  virtual void setSkyParameters(const OdGiSkyParameters &params) = 0;
  
  /** \details
    Retrieves sky parameters of this light.
    
    \returns
    sky parameters as OdGiColorRGB instance.
  */
  virtual void skyParameters(OdGiSkyParameters &params) const = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdGiDistantLightTraits, OdGiDistantLightTraits> object.
*/
typedef OdSmartPtr<OdGiDistantLightTraits> OdGiDistantLightTraitsPtr;

/** \details
    Extended point light that provides photometric web traits.
    Corresponding C++ library: TD_Gi
    <group OdGi_Classes>
*/
class FIRSTDLL_EXPORT OdGiWebLightTraits : public OdGiPointLightTraits
{
public:
  ODRX_DECLARE_MEMBERS(OdGiWebLightTraits);

  enum WebFileType
  {
    kTypeA = 3,
    kTypeB = 2,
    kTypeC = 1
  };

  enum WebSymmetry
  {
    kNoSymmetry = 0,
    kSingleSymmetry,
    kDoubleSymmetry,
    kAxialSymmetry
  };

  virtual void setWebFile(const OdChar* fileName) = 0;
  virtual void webFile(OdString&) const = 0;

  virtual void setWebRotation(OdGeVector3d fRot) = 0;
  virtual void webRotation(OdGeVector3d&) const = 0;

  virtual void setWebFlux(double fFlux) const = 0;
  virtual double webFlux() const = 0;

  virtual void setWebFileType(WebFileType type) = 0;
  virtual WebFileType webFileType() const = 0;

  virtual void setWebSymmetry(WebSymmetry sym) = 0;
  virtual WebSymmetry webSymmetry() const = 0;

  virtual void setWebHorzAng90to270(bool bFlag) = 0;
  virtual bool webHorzAng90to270() const = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdGiWebLightTraits, OdGiWebLightTraits> object.
*/
typedef OdSmartPtr<OdGiWebLightTraits> OdGiWebLightTraitsPtr;


/** \details
    Corresponding C++ library: TD_Gi
    <group OdGi_Classes>
*/
class FIRSTDLL_EXPORT OdGiLightTraitsVpDep : public OdGiNonEntityTraits
{
public:
  ODRX_DECLARE_MEMBERS(OdGiLightTraitsVpDep);
  // returned via subSetAttributes()
  enum
  {
    kVpDep = (OdGiDrawable::kLastFlag << 1)
  };
  // 
  virtual OdUInt32 viewportId() const = 0;
  virtual OdDbStub* viewportObjectId() const = 0;
  //
  virtual void setOn(bool on) = 0;
  virtual bool isOn() const = 0;
  //
  virtual void setDimming(double dim) = 0;
  virtual double dimming() const = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdGiLightTraitsVpDep, OdGiLightTraitsVpDep> object.
*/
typedef OdSmartPtr<OdGiLightTraitsVpDep> OdGiLightTraitsVpDepPtr;

#include "../TD_PackPop.h"

#endif // __OD_GI_LIGHT_TRAITS__
