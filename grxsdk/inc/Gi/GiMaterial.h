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

#ifndef __ODGIMATERIAL_H__
#define __ODGIMATERIAL_H__

#include "../TD_PackPush.h"
#include "../RootExport.h"
#include "GiExport.h"

#include "../CmColorBase.h"
#include "../Ge/GeMatrix3d.h"
#include "../Gi/GiDrawable.h"
#include "../Gi/GiVariant.h"
#include "../Gi/Giparameter.h"

class OdGiMaterialColor;
class OdGiMaterialMap;
class OdGiRasterImage;

/** \details
    This class defines the interface to material traits for the vectorization process.
    Corresponding C++ library: TD_Gi
    <group OdGi_Classes>
    \sa
    <link tv_working_with_attributes_materials, Working with Materials>
*/
class ODRX_ABSTRACT FIRSTDLL_EXPORT OdGiMaterialTraits : public OdGiNonEntityTraits
{
public:
  ODRX_DECLARE_MEMBERS(OdGiMaterialTraits);

  /** \details
    This enumeration specifies an illumination model used in the rendering process when 
    working with materials.
  */
  enum IlluminationModel
  {
    /**Blinn shader uses the light's color to determine the reflection color. */
    kBlinnShader = 0,
    /**Metal shader calculates the reflected light's color using the material's diffuse color and the light's color. */
    kMetalShader
  };

  /** \details
    Specifies material channels.
  */
  enum ChannelFlags
  {
    /**No material channels enabled. */
    kNone           = 0x00000,
    /**Enables diffuse material channel. */
    kUseDiffuse     = 0x00001,
    /**Enables specular material channel. */
    kUseSpecular    = 0x00002,
    /**Enables reflection material channel. */
    kUseReflection  = 0x00004,
    /**Enables opacity material channel. */
    kUseOpacity     = 0x00008,
    /**Enables bump material channel. */
    kUseBump        = 0x00010,
    /**Enables refraction material channel. */
    kUseRefraction  = 0x00020,
    /**Enables normal map material channel. */
    kUseNormalMap   = 0x00040,
    // BIM extensions
    /**Enables emission material channel. */
    kUseEmission    = 0x00080,
    /**Enables tint material channel. */
    kUseTint        = 0x00100,
    /**Enables all material channels. */
    kUseAll         = (kUseDiffuse | kUseSpecular | kUseReflection |
                       kUseOpacity | kUseBump | kUseRefraction | kUseNormalMap),
    /**Enables all material channels including extension channels. */
    kUseAllInternal = (kUseAll | kUseEmission | kUseTint)
  };
  
  /** \details
    Specifies the material model.
  */
  enum Mode
  {
    /**Realistic material model. */
    kRealistic = 0,
    /**Advanced material model. */
    kAdvanced
  };

  // Returned via subSetAttributes()
  enum
  {
    kByBlock    = (OdGiDrawable::kLastFlag << 1), // "ByBlock" material.
    kByLayer    = (OdGiDrawable::kLastFlag << 2)  // "ByLayer" material.
  };

  // Extended material traits enumerations

  /** \details
    Specifies the luminance modes.
  */
  enum LuminanceMode
  {
    /**Compute luminance from self-illumination parameters. */
    kSelfIllumination = 0,
    /**Use luminance specified by the setLuminance() method. */
    kLuminance,
    /**Compute luminance using an emission material channel. */
    kEmissionColor
  };

  /** \details
    Specifies the normal maps.
  */
  enum NormalMapMethod
  {
    /**Method of tangent spaces is used to compute the normal map. */
    kTangentSpace
  };

  /** \details
    Specifies the global illumination.
  */
  enum GlobalIlluminationMode
  {
    /**No global illumination. */
    kGlobalIlluminationNone,
    /**The global illumination is casting light. */
    kGlobalIlluminationCast,
    /**The global illumination is receiving light. */
    kGlobalIlluminationReceive,
    /**The global illumination is casting and receiving light. */
    kGlobalIlluminationCastAndReceive
  };

  /** \details
    Specifies the final gathering mode.
  */
  enum FinalGatherMode
  {
    /**No final gathering. */
    kFinalGatherNone,
    /**The final gathering is casting. */
    kFinalGatherCast,
    /**The final gathering is receiving. */
    kFinalGatherReceive,
    /**The final gathering is casting and receiving. */
    kFinalGatherCastAndReceive
  };

  // BIM extensions
  /** \details
    Specifies the diffuse color mode.
  */
  enum DiffuseColorMode
  {
    /**Use the color specified in the diffuse material channel. */
    kDiffuseRealisticColor = 0,
    /**Use the color specified by the setShadingDiffuse() method. */
    kDiffuseShadingColor,
    /**Chosen color depends on the active visual style. */
    kDiffuseStyleDependent
  };

  /** \details
    Returns the ambient color component of this MaterialTraits object.

    \param ambientColor [out]  Receives the ambient color.

    \remarks
    The ambient color component is most apparent when there is no direct illumination on the entity.
  */
  virtual void ambient(OdGiMaterialColor& ambientColor) const = 0;

  /** \details
    Returns the diffuse component of this MaterialTraits object.

    \param diffuseColor [out]  Receives the diffuse color.
    \param diffuseMap [out]  Receives the diffuse map.

    \remarks
    The diffuse component is most apparent when there is direct illumination on the entity.
  */
  virtual void diffuse(OdGiMaterialColor& diffuseColor, OdGiMaterialMap& diffuseMap) const = 0;

  /** \details
    Returns the specular component of this MaterialTraits object.

    \param specularColor [out]  Receives the specular color.
    \param specularMap [out]  Receives the specular map.
    \param glossFactor [out]  Receives the gloss factor.

    \remarks
    The specular component depends on the viewer's eye position and represents the light source reflection highlights on the entity surface.
  */
  virtual void specular(OdGiMaterialColor& specularColor, OdGiMaterialMap& specularMap, double& glossFactor) const = 0;

  /** \details
    Returns the reflection component of this MaterialTraits object.

    \param reflectionMap [out]  Receives the reflection map.

    \remarks
    The reflection component creates a mirror finish on the entity.
  */
  virtual void reflection(OdGiMaterialMap& reflectionMap) const = 0;

  /** \details
    Returns the opacity component of this MaterialTraits object.

    \param opacityPercentage [out]  Receives the opacity percentage.
    \param opacityMap [out]  Receives the opacity map.
  */
  virtual void opacity(double& opacityPercentage, OdGiMaterialMap& opacityMap) const = 0;

  /** \details
    Returns the bump component of this MaterialTraits object.

    \param bumpMap [out]  Receives the bump map.
  */
  virtual void bump(OdGiMaterialMap& bumpMap) const = 0;

  /** \details
    Returns the refraction component of this MaterialTraits object.

    \param refractionIndex [out]  Receives the refraction index.
    \param refractionMap [out]  Receives the refraction map.
  */
  virtual void refraction(double& refractionIndex, OdGiMaterialMap& refractionMap) const = 0;

  /** \details
    Returns the translucence of this MaterialTraits object.
    
    \returns
    translucence amount as a value of the double type.
  */
  virtual double translucence() const = 0;

  /** \details
    Returns the self illumination of this MaterialTraits object.
    
    \returns
    translucence amount as a value of the double type.
  */
  virtual double selfIllumination() const = 0;

  /** \details
    Returns the reflectivity of this MaterialTraits object.
    
    \returns
    reflectivity amount as a value of the double type.
  */
  virtual double reflectivity() const = 0;

  /** \details
    Returns the illumination model of this MaterialTraits object.
    
    \returns
    one of two shaders that define illumination model: kBlinnShader or kMetalShader.
  */
  virtual IlluminationModel illuminationModel() const = 0;

  /** \details
    Returns the material channels in use by this MaterialTraits object.
    
    \returns
    a set of flags that represent which channels are used.
  */
  virtual ChannelFlags channelFlags() const = 0;

  /** \details
    Returns the mode of this MaterialTraits object.
    
    \returns
    one of two render modes: kRealistic or kAdvanced.
  */
  virtual Mode mode() const = 0;

  /** \details
    Sets the ambient color component of this MaterialTraits object.

    \param ambientColor [in]  Ambient color.

    \remarks
    The ambient color component is most apparent when there is no direct illumination on the entity.
  */
  virtual void setAmbient(const OdGiMaterialColor& ambientColor) = 0;

  /** \details
    Sets the diffuse component of this MaterialTraits object.

    \param diffuseColor [in]  Diffuse color.
    \param diffuseMap [in]  Diffuse map.

    \remarks
    The diffuse component is most apparent when there is direct illumination on the entity.
  */
  virtual void setDiffuse(const OdGiMaterialColor& diffuseColor, const OdGiMaterialMap& diffuseMap) = 0;

  /** \details
    Sets the specular component of this MaterialTraits object.

    \param specularColor [in]  Specular color.
    \param specularMap [in]  Specular map.
    \param glossFactor [in]  Gloss factor.

    \remarks
    The specular component depends on the viewer's eye position and represents light source reflection highlights on the entity surface.
  */
  virtual void setSpecular(const OdGiMaterialColor& specularColor, const OdGiMaterialMap& specularMap, double glossFactor) = 0;

  /** \details
    Sets the reflection component of this MaterialTraits object.

    \param reflectionMap [in]  Reflection map.

    \remarks
    The reflection component creates a mirror finish on the entity.
  */
  virtual void setReflection(const OdGiMaterialMap& reflectionMap) = 0;

  /** \details
    Sets the opacity component of this MaterialTraits object.

    \param opacityPercentage [in]  Opacity percentage.
    \param opacityMap [in]  Opacity map.
  */
  virtual void setOpacity(double opacityPercentage, const OdGiMaterialMap& opacityMap) = 0;

  /** \details
    Sets the bump component of this MaterialTraits object.

    \param bumpMap [in]  Bump map.
  */
  virtual void setBump(const OdGiMaterialMap& bumpMap) = 0;

  /** \details
    Sets the refraction component of this MaterialTraits object.

    \param refractionIndex [in]  Refraction index.
    \param refractionMap [in]  Refraction map.
  */
  virtual void setRefraction(double refractionIndex, const OdGiMaterialMap& refractionMap) = 0;

  /** \details
    Sets the translucence of this MaterialTraits object.

    \param value [in]  Translucence value.
  */
  virtual void setTranslucence(double value) = 0;

  /** \details
    Sets the self illumination of this MaterialTraits object.

    \param value [in]  Self illumination level.
  */
  virtual void setSelfIllumination(double value) = 0;

  /** \details
    Sets the reflectivity of this MaterialTraits object.

    \param value [in]  Reflectivity value.
  */
  virtual void setReflectivity(double value) = 0;

  /** \details
    Sets the illumination model of this MaterialTraits object.

    \param model [in]  Illumination model.
  */
  virtual void setIlluminationModel(IlluminationModel model) = 0;

  /** \details
    Sets the material channels to be used by this MaterialTraits object.

    \param value [in]  Channels to be used.
  */
  virtual void setChannelFlags(ChannelFlags flags) = 0;

  /** \details
    Sets the mode of this MaterialTraits object.

    \param value [in]  Mode value.
  */
  virtual void setMode(Mode value) = 0;

  // Extended material properties

  /** \details
    Sets the color bleed scale of this MaterialTraits object.

    \param scale [in]  Color bleed scale.
  */
  virtual void setColorBleedScale(double scale) = 0;

  /** \details
    Returns the color bleed scale of this MaterialTraits object.
    
    \returns
    color bleed scale as a value of the double type.
  */
  virtual double colorBleedScale() const = 0;

  /** \details
    Sets the indirect bump scale of this MaterialTraits object.

    \param scale [in]  Indirect bump scale.
  */
  virtual void setIndirectBumpScale(double scale) = 0;

  /** \details
    Returns the indirect bump scale of this MaterialTraits object.
    
    \returns
    indirect bump scale as a value of the double type.
  */
  virtual double indirectBumpScale() const = 0;

  /** \details
    Sets the reflectance scale of this MaterialTraits object.

    \param scale [in]  Reflectance scale.
  */
  virtual void setReflectanceScale(double scale) = 0;

  /** \details
    Returns the reflectance scale of this MaterialTraits object.
    
    \returns
    reference scale as a value of the double type.
  */
  virtual double reflectanceScale() const = 0;

  /** \details
    Sets the transmittance scale of this MaterialTraits object.

    \param scale [in]  Transmittance scale.
  */
  virtual void setTransmittanceScale(double scale) = 0;

  /** \details
    Returns the transmittance scale of this MaterialTraits object.
    
    \returns
    transmittance scale as a value of the double type.
  */
  virtual double transmittanceScale() const = 0;

  /** \details
    Sets the two-sided mode of this MaterialTraits object.

    \param flag [in]  Two-sided mode flag.
  */
  virtual void setTwoSided(bool flag) = 0;

  /** \details
    Returns the two-sided mode of this MaterialTraits object.
  */
  virtual bool twoSided() const = 0;

  /** \details
    Sets the luminance mode of this MaterialTraits object.

    \param mode [in]  Luminance mode.
  */
  virtual void setLuminanceMode(LuminanceMode mode) = 0;

  /** \details
    Returns the luminance mode of this MaterialTraits object.
    
    \returns
    a value from the LuminanceMode enumeration that represents one of the luminance modes.
  */
  virtual LuminanceMode luminanceMode() const = 0;

  /** \details
    Sets the luminance of this MaterialTraits object.

    \param value [in]  Luminance value.
  */
  virtual void setLuminance(double value) = 0;

  /** \details
    Returns the luminance of this MaterialTraits object.
    
    \returns
    luminance amount as a value of the double type.
  */
  virtual double luminance() const = 0;

  /** \details
    Sets the normalMap component of this MaterialTraits object.

    \param normalMap [in]  Normal map.
    \param method [in]  Normal map method.
    \param strength [in]  Strength factor.
  */
  virtual void setNormalMap(const OdGiMaterialMap &normalMap, NormalMapMethod method, double strength) = 0;

  /** \details
    Retrieves the normalMap component of this MaterialTraits object.

    \param normalMap [out]  Receives the normal map.
    \param method [out]  Receives the normal map method.
    \param strength [out]  Receives the normal map strength factor.
  */
  virtual void normalMap(OdGiMaterialMap &normalMap, NormalMapMethod &method, double &strength) const = 0;

  /** \details
    Sets the global illumination mode of this MaterialTraits object.

    \param mode [in]  Global illumination mode.
  */
  virtual void setGlobalIllumination(GlobalIlluminationMode mode) = 0;

  /** \details
    Returns the global illumination mode of this MaterialTraits object.
    
    \returns
    global illumination mode as a value from the GlobalIlluminationMode enumeration.
  */
  virtual GlobalIlluminationMode globalIllumination() const = 0;

  /** \details
    Sets the final gather mode of this MaterialTraits object.

    \param mode [in]  Final gather mode.
  */
  virtual void setFinalGather(FinalGatherMode mode) = 0;

  /** \details
    Returns the final gather mode of this MaterialTraits object.
    
    \returns
    final gathering mode as a value from the FinalGatherMode enumeration.
  */
  virtual FinalGatherMode finalGather() const = 0;

  // BIM extensions

  /** \details
    Sets the emission component of this MaterialTraits object.

    \param emissionColor [in]  Emission color.
    \param emissionMap [in]  Emission map.
  */
  virtual void setEmission(const OdGiMaterialColor& emissionColor, const OdGiMaterialMap& emissionMap) {}

  /** \details
    Returns the emission component of this MaterialTraits object.

    \param emissionColor [out]  Receives the emission color.
    \param emissionMap [out]  Receives the emission map.
  */
  virtual void emission(OdGiMaterialColor& emissionColor, OdGiMaterialMap& emissionMap) const {}

  /** \details
    Sets the tint component of this MaterialTraits object.

    \param tintColor [in]  Tint color.
  */
  virtual void setTint(const OdGiMaterialColor& tintColor) {}

  /** \details
    Returns the tint component of this MaterialTraits object.

    \param tintColor [out]  Receives the tint color.
  */
  virtual void tint(OdGiMaterialColor& tintColor) const {}

  /** \details
    Sets the shading ambient color component of this MaterialTraits object.

    \param ambientColor [in]  Shading ambient color.
  */
  virtual void setShadingAmbient(const OdGiMaterialColor& ambientColor) {}

  /** \details
    Returns the shading ambient color component of this MaterialTraits object.

    \param ambientColor [out]  Receives the shading ambient color.
  */
  virtual void shadingAmbient(OdGiMaterialColor& ambientColor) const {}

  /** \details
    Sets the shading diffuse color component of this MaterialTraits object.

    \param diffuseColor [in]  Shading diffuse color.
  */
  virtual void setShadingDiffuse(const OdGiMaterialColor& diffuseColor) {}

  /** \details
    Returns the shading diffuse color component of this MaterialTraits object.

    \param diffuseColor [out]  Receives the shading diffuse color.
  */
  virtual void shadingDiffuse(OdGiMaterialColor& diffuseColor) const {}

  /** \details
    Sets the shading specular color component of this MaterialTraits object.

    \param specularColor [in]  Shading specular color.
  */
  virtual void setShadingSpecular(const OdGiMaterialColor& specularColor) {}

  /** \details
    Returns the shading specular color component of this MaterialTraits object.

    \param specularColor [out]  Receives the shading specular color.
  */
  virtual void shadingSpecular(OdGiMaterialColor& specularColor) const {}

  /** \details
    Sets the shading opacity component of this MaterialTraits object.

    \param opacityPercentage [in]  Shading opacity percentage.
  */
  virtual void setShadingOpacity(double opacityPercentage) {}

  /** \details
    Returns the shading opacity component of this MaterialTraits object.

    \param opacityPercentage [out]  Receives the shading opacity percentage.
  */
  virtual void shadingOpacity(double &opacityPercentage) const {}

  /** \details
    Sets diffuse, ambient, specual color and opacity behavior.

    \param diffuseColorMode [in]  New setting for diffuse color and opacity mode.
  */
  virtual void setDiffuseColorMode(DiffuseColorMode diffuseColorMode) {}

  /** \details
    Returns current diffuse, ambient, specular color and opacity behavior.
    \returns
    diffuse color mode as a value from the DiffuseColorMode enumeration.
  */
  virtual DiffuseColorMode diffuseColorMode() const { return kDiffuseRealisticColor; }

  // Visualize extensions

  /** \details
    Sets coefficient of opacity influence onto received shadows.

    \param effectPercentage [in]  Coefficient in 0.0-1.0 range.
    \param nonShadowLightsMergeEffect [in]  Setup amount in 0.0-1.0 range of lights influence which is doesn't cast shadows.
  */
  virtual void setShadowsOpacityEffect(double effectPercentage, double nonShadowLightsMergeEffect = 1.0) {}

  /** \details
    Returns coefficient of opacity influence onto received shadows.
    Coefficient set to 1.0 by default, which is means that shadows opacity will fully depends from material opacity.

    \param nonShadowLightsMergeEffect [out]  Amount in 0.0-1.0 range of lights influence which is doesn't cast shadows.
  */
  virtual double shadowsOpacityEffect(double &nonShadowLightsMergeEffect) const { return 0.0; }

  /** \details
    Setup specular highlighting behavior override.

    \param overrideVal [in]  Specular highlighting override value.

    \remarks
    Positive override value means absolute specular highlighting factor.
    Zero override value disables specular highlighting override.
    Negative override value provides maximal speculat highlighting factor and means that highlighting factor must be got from Visual Style.
  */
  virtual void setSpecularHighlightingOverride(double overrideVal) {}

  /** \details
    Returns specular highlighting behavior override.
  */
  virtual double specularHighlightingOverride() const { return 0.0; }
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdGiMaterialTraits object pointers.
*/
typedef OdSmartPtr<OdGiMaterialTraits> OdGiMaterialTraitsPtr;

/** \details
    This class implements material colors by color method and value.

    \sa
    <link tv_working_with_attributes_materials_color, Working with Color Properties of Materials>

    <group OdGi_Classes>
*/
class FIRSTDLL_EXPORT OdGiMaterialColor : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdGiMaterialColor);

  /** \details
    Specifies the color method used by setMethod() and method(). 
  */
  enum Method
  {
    /**Uses the current drawing color. */
    kInherit  = 0,
    /**Uses the color set with setColor(). */
    kOverride = 1
  };

  FIRSTDLL_EXPORT_STATIC static const OdGiMaterialColor kNull;

  /** \details
    Default constructor for the OdGiMaterialColor class. Sets color method to kInherit and color bleed factor to 1.0.
  */
  OdGiMaterialColor();

  /** \details
    Constructs with color override mode. Also sets color bleed factor to 1.0

    \param overrideColor [in]  Color of this MaterialColor object.
  */
  OdGiMaterialColor(const OdCmEntityColor &overrideColor);
  OdGiMaterialColor(const OdGiMaterialColor &matColor);
  OdGiMaterialColor & operator= (const OdGiMaterialColor &matColor);

  virtual void set(const OdGiMaterialColor &matColor);
  /** \details
    Sets the color method for this MaterialColor object.

    \param method [in]  Color method.

    \remarks
    method must be one of the following:

    <table>
    Name          Value    Description
    kInherit      0        Uses the current drawing color.
    kOverride     1        Uses the color set with setColor.
    </table>
  */
  virtual void setMethod(Method method);

  /** \details
    Sets the color factor for this MaterialColor object.

    \param factor [in]  Color factor.

    \remarks
    A color factor of 0.0 makes all colors black; a color factor of 1.0 leaves them unchanged.
  */
  virtual void setFactor(double factor);

  /** \details
    Retrieves a color for this object.
    \returns
    a reference to, or a copy of, the color of this MaterialColor object as
    an OdCmEntityColor instance.
  */
  OdCmEntityColor& color();

  /** \details
    Retrieves the color method for this MaterialColor object.

    \returns
    a value from the Method enumeration which can be one of the following:

    <table>
    Name          Value    Description
    kInherit      0        Uses the current drawing color.
    kOverride     1        Uses the color set with setColor.
    </table>
  */
  virtual Method method() const;

  /** \details
    Returns the color factor for this MaterialColor object.

    \returns
    color factor as a value of the double type.
    
    \remarks
    A color factor of 0.0 makes all colors black; a color factor of 1.0 leaves them unchanged.
  */
  virtual double factor() const;

  /** \details
    Retrieves a color for this object.
    \returns
    a reference to, or a copy of, the color of this MaterialColor object as
    an OdCmEntityColor instance.
  */
  virtual const OdCmEntityColor& color() const;

  /** \details
    Equality operator for the OdGiMaterialColor class.
    Material colors are equal if:
    * color methods are equal
    * color bleed factors are equal
    * color values are equal
    
    \param other  [in] Other object to be compared.
    
    \returns
    true if the specified material color is equal to this material color, false otherwise.
  */
  bool operator ==(const OdGiMaterialColor &other) const
  {
    return (m_method == other.m_method) &&
           (m_factor == other.m_factor) &&
           (m_color  == other.m_color);      
  }
  
  /** \details
    Inequality operator for the OdGiMaterialColor class.
    Material colors are equal if one of the following conditions fails:
    * color methods are equal
    * color bleed factors are equal
    * color values are equal
    
    \param other  [in] Other object to be compared.
    
    \returns
    true if the specified material color is not equal to this material color, false otherwise.
  */
  bool operator != (const OdGiMaterialColor &other) const
  {
    return (m_method != other.m_method) ||
           (m_factor != other.m_factor) ||
           (m_color  != other.m_color);      
  }

  /** \details
    Sets the color for this MaterialColor object.
    \param color [in]  New color for this MaterialColor object.
  */
  virtual void setColor(const OdCmEntityColor &color);

private:
  Method          m_method;
  double          m_factor;
  OdCmEntityColor m_color;
};

/** \details
  This class defines material textures.
  Corresponding C++ library: TD_Gi
  <group OdGi_Classes>
  \sa
  <link tv_working_with_attributes_materials, Working with Materials>
*/
class ODRX_ABSTRACT FIRSTDLL_EXPORT OdGiMaterialTexture : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdGiMaterialTexture);
  virtual bool operator==(const OdGiMaterialTexture & texture)const;
protected:
  OdGiMaterialTexture() { }
  ~OdGiMaterialTexture() { }
};

inline bool OdGiMaterialTexture::operator==(const OdGiMaterialTexture & texture) const {
  return (texture.isA() == isA());
}

/** \details
  This template class is a specialization of the OdSmartPtr class for OdGiMaterialTexture object pointers.
*/
typedef OdSmartPtr<OdGiMaterialTexture> OdGiMaterialTexturePtr;

/** \details
  This class defines material textures based on images.
  Corresponding C++ library: TD_Gi
  <group OdGi_Classes>
  \sa
  <link tv_working_with_attributes_materials, Working with Materials>
*/
class ODRX_ABSTRACT FIRSTDLL_EXPORT OdGiImageTexture : public OdGiMaterialTexture
{
public:
  ODRX_DECLARE_MEMBERS(OdGiImageTexture);
protected:
  OdGiImageTexture() { }
  ~OdGiImageTexture() { }
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdGiImageTexture object pointers.
*/
typedef OdSmartPtr<OdGiImageTexture> OdGiImageTexturePtr;

/** \details
  This class defines material textures based on image files.
  Corresponding C++ library: TD_Gi
  <group OdGi_Classes>
  \sa
  <link tv_working_with_attributes_materials, Working with Materials>
*/
class FIRSTDLL_EXPORT OdGiImageFileTexture : public OdGiImageTexture
{
public:
  ODRX_DECLARE_MEMBERS(OdGiImageFileTexture);

  OdGiImageFileTexture(void);
  OdGiImageFileTexture(const OdGiImageFileTexture &texture);
  virtual ~OdGiImageFileTexture(void);


  /** \details
    Sets the name of the source file containing the image. 
    
    \param fileName [in]  File name.
  */
  virtual void setSourceFileName(const OdChar * fileName);
  
  /** \details
    Retrieves the name of the file that is used as the image texture.
    \returns
    the OdString instance that represents the name of the source file containing the image.
  */
  virtual const OdChar * sourceFileName() const;

  /** \details
    Equality operator for the OdGiMaterialTexture class.
    The objects are equal if:
    * the passed object is an image file texture.
    * source file paths are equal
    
    \param texture  [in] Texture to be compared.
    
    \returns
    true if the specified texture is equal to this image file texture, false otherwise.
  */
  virtual bool operator==(const OdGiMaterialTexture & texture) const;
  
  /** \details
    Assignment operator for the OdGiImageFileTexture class.
    Assigns file path of the specifies texture and returns a reference to this image texture.
    
    \param texture  [in] Texture to be assigned.
    
    \returns
    a reference to this image file texture.
  */
  OdGiImageFileTexture &operator =(const OdGiImageFileTexture &texture);

  // OdRxObject overrides

  /** \details
    Copies the data of the source object to the current object.

    \param pSource [in] Input source object.
  */
  OdResult copyFrom(const OdRxObject* pSource);
private:
  OdString m_sourceFileName;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdGiImageFileTexture object pointers.
*/
typedef OdSmartPtr<OdGiImageFileTexture> OdGiImageFileTexturePtr;

/** \details
    This class defines material textures based on raster images.
    Corresponding C++ library: TD_Gi
    <group OdGi_Classes>
    \sa
    <link tv_working_with_attributes_materials, Working with Materials>
*/
class FIRSTDLL_EXPORT OdGiRasterImageTexture : public OdGiImageTexture
{
public:
  ODRX_DECLARE_MEMBERS(OdGiRasterImageTexture);
  /** \details
    Sets a raster image to this object.

    \param pRasterImage [in] Input raster image.
  */
  virtual void setRasterImage(const OdGiRasterImage *pRasterImage);

  /** \details
    Retrieves the raster image of this object.
    \returns
    pointer the raster image represented by OdGiRasterImage class.
  */
  virtual const OdGiRasterImage *rasterImage() const;

  /** \details
    Equality operator for the OdGiRasterImageTexture class.
    The objects are equal if:
    * the passed object is an image file texture.
    * source file paths are equal
    
    \param texture  [in] Texture to be compared.
    
    \returns
    true if the specified texture is equal to this image file texture, false otherwise.
  */
  virtual bool operator==(const OdGiMaterialTexture & texture) const;
  
  /** \details
    Assignment operator for the OdGiRasterImageTexture class.
    Assigns file path of the specifies texture and returns a reference to this image texture.
    
    \param texture  [in] Texture to be assigned.
    
    \returns
    a reference to this raster image texture.
  */
  OdGiRasterImageTexture &operator =(const OdGiRasterImageTexture &texture);

  /** \details
    Copies the data of the source object to the current object.

    \param pSource [in] Input source object.
  */
  OdResult copyFrom(const OdRxObject* pSource);
private:
  OdRxObjectPtr m_pRasterImage;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdGiRasterImageTexture object pointers.
*/
typedef OdSmartPtr<OdGiRasterImageTexture> OdGiRasterImageTexturePtr;

/** \details
    This class defines procedural material textures.
    Corresponding C++ library: TD_Gi
    <group OdGi_Classes>
*/
class ODRX_ABSTRACT FIRSTDLL_EXPORT OdGiProceduralTexture : public OdGiMaterialTexture
{
public:
  ODRX_DECLARE_MEMBERS(OdGiProceduralTexture);

  /** \details
    Specifies the different procedural textures.
  */
  enum Type
  {
    kWood    = 0, // Wood texture.
    kMarble  = 1, // Marble texture.
    kGeneric = 2  // Generic texture.
  };

  /** \details
    Retrieves the type of the procedural texture.
    \returns
    the type of procedural texture as a value from the Type enumeration.
  */
  virtual Type type() const { return kGeneric; }
protected:
  OdGiProceduralTexture() { }
  ~OdGiProceduralTexture() { }
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdGiProceduralTexture object pointers.
*/
typedef OdSmartPtr<OdGiProceduralTexture> OdGiProceduralTexturePtr;

/** \details
    This class defines wood procedural material textures.
    Corresponding C++ library: TD_Gi
    <group OdGi_Classes>
*/
class FIRSTDLL_EXPORT OdGiWoodTexture : public OdGiProceduralTexture
{
public:
  ODRX_DECLARE_MEMBERS(OdGiWoodTexture);

  /** \details
    Default constructor for the OdGiWoodTexture class. Sets the radial noise, axial noise and grain thickness to 0.
  */
  OdGiWoodTexture();
  OdGiWoodTexture(const OdGiWoodTexture &texture);
  virtual ~OdGiWoodTexture(void);

  /** \details
    Retrieves the type of the procedural texture.
    \returns
    the kWood value from the Type enumeration.
  */
  virtual Type type() const  {return kWood;}

  // wood properties

  /** \details
    Sets the color of the first wood grain.

    \param woodColor1 [in] Color value.
  */
  virtual void setColor1(const OdGiMaterialColor &woodColor1);
  
  /** \details
    Retrieves the color of the first wood grain.
    \returns
    reference to the color of the first wood grain represented by OdGiMaterialColor class.
  */
  virtual const OdGiMaterialColor& color1(void) const;

  /** \details
    Sets the color of the second wood grain.

    \param woodColor2 [in] Color value.
  */
  virtual void setColor2(const OdGiMaterialColor &woodColor2);
  
  /** \details
    Retrieves the color of the second wood grain.
    \returns
    reference to the color of the second wood grain represented by OdGiMaterialColor class.
  */
  virtual const OdGiMaterialColor& color2(void) const;

  /** \details
    Sets the radial noise level of the wood grain.

    \param radialNoise [in] Radial noise level.
  */
  virtual void setRadialNoise(double radialNoise);
    
  /** \details
    Retrieves the radial noise level of the wood grain.
    \returns
    radial noise level as value of the double type.
  */
  virtual double radialNoise(void) const;

  /** \details
    Sets the axial noise level of the wood grain.

    \param axialNoise [in] Axial noise level.
  */
  virtual void setAxialNoise(double axialNoise);
  
  /** \details
    Retrieves the axial noise level of the wood grain.
    \returns
    axial noise level as value of the double type.
  */
  virtual double axialNoise(void) const;

  /** \details
    Sets the thickness of the wood grain.

    \param grainThickness [in] Thickness value.
  */
  virtual void setGrainThickness(double grainThickness);
  
  /** \details
    Retrieves the thickness of the wood grain.
    \returns
    the thickness of the wood grain as value of the double type.
  */
  virtual double grainThickness(void) const;

  /** \details
    Equality operator for the OdGiWoodTexture class.
    Textures are equal if:
    * the specified texture is wooden texture
    * first grain colors are equal
    * second grain colors are equal
    * radial noise levels are equal
    * axial noise levels are equal
    * wood grain thickness values are equal
    
    \param texture  [in] Texture to be compared.
    
    \returns
    true if the specified texture is equal to this wood texture, false otherwise.
  */
  virtual bool operator==(const OdGiMaterialTexture & texture) const;
  
  /** \details
    Assignment operator for the OdGiWoodTexture class.
    Assigns first and second grain colors, radial and axial noise levels, grain thickness value and returns
    a reference to the wood texture.
    
    \param texture  [in] Texture to be assigned.
    
    \returns
    a reference to this wood texture.
  */
  OdGiWoodTexture &operator =(const OdGiWoodTexture &texture);

  // OdRxObject overrides

  /** \details
    Copies the data of the source object to the current object.

    \param pSource [in] Input source object.
  */
  OdResult copyFrom(const OdRxObject* pSource);
private:
  OdGiMaterialColor m_color1;
  OdGiMaterialColor m_color2;
  double            m_radialNoise;
  double            m_axialNoise;
  double            m_grainThickness;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdGiWoodTexture object pointers.
*/
typedef OdSmartPtr<OdGiWoodTexture> OdGiWoodTexturePtr;

/** \details
    This class defines marble procedural material textures.
    Corresponding C++ library: TD_Gi
    <group OdGi_Classes>
*/
class FIRSTDLL_EXPORT OdGiMarbleTexture : public OdGiProceduralTexture
{
public:
  ODRX_DECLARE_MEMBERS(OdGiMarbleTexture);

  /** \details
    Default constructor for the OdGiMarbleTexture class. Sets the vein spacing and width to 0.
  */
  OdGiMarbleTexture();
  OdGiMarbleTexture(const OdGiMarbleTexture &texture);
  virtual ~OdGiMarbleTexture(void);

  /** \details
    Retrieves the type of the procedural texture.
    \returns
    the kMarble value from the Type enumeration.
  */
  virtual Type type() const  {return kMarble;}

  /** \details
    Sets the stone color of the marble.

    \param stoneColor [in] Color value.
  */
  virtual void setStoneColor(const OdGiMaterialColor &stoneColor);
  
  /** \details
    Retrieves the stone color of the marble.
    
    \returns
    reference to the OdGiMaterialColor object that represents stone color of the marble.
  */
  virtual const OdGiMaterialColor& stoneColor(void) const;

  /** \details
    Sets the vein color of the marble.

    \param veinColor [in] Color value.
  */
  virtual void setVeinColor(const OdGiMaterialColor &veinColor);
  
  /** \details
    Retrieves the vein color of the marble.
    
    \returns
    reference to the OdGiMaterialColor object that represents vein color of the marble.
  */
  virtual const OdGiMaterialColor& veinColor(void) const;

  /** \details
    Sets the spacing between veins of the marble.

    \param veinSpacing [in] Spacing value.
  */
  virtual void setVeinSpacing(double veinSpacing);
  
  /** \details
    Retrieves vein spacing of this marble texture.
    
    \returns
    the spacing between veins of the marble.
  */
  virtual double veinSpacing(void) const;

  /** \details
    Sets the vein width of the marble.

    \param veinWidth [in] Vein width value.
  */
  virtual void setVeinWidth(double veinWidth);
  
  /** \details
    Retrieves vein width of this marble texture.
    
    \returns
    the vein width of the marble.
  */
  virtual double veinWidth(void) const;

  /** \details
    Equality operator for the OdGiMarbleTexture class.
    Textures are equal if:
    * the specified texture is marble texture
    * stone colors are equal
    * vein colors are equal
    * vein spacing values are equal
    * vein width values are equal
    
    \param texture  [in] Texture to be compared.
    
    \returns
    true if the specified texture is equal to this marble texture, false otherwise.
  */
  virtual bool operator==(const OdGiMaterialTexture & texture) const;
  
  /** \details
    Assignment operator for the OdGiMarbleTexture class.
    Assigns stone and vein colors, vein spacing, vein width and returns
    a reference to the marble texture.
    
    \param texture  [in] Texture to be assigned.
    
    \returns
    a reference to this marble texture.
  */
  OdGiMarbleTexture &operator =(const OdGiMarbleTexture &texture);

  // OdRxObject overrides

  /** \details
    Copies the data of the source object to the current object.

    \param pSource [in] Input source object.
  */
  OdResult copyFrom(const OdRxObject* pSource);
private:
  OdGiMaterialColor m_stoneColor;
  OdGiMaterialColor m_veinColor;
  double            m_veinSpacing;
  double            m_veinWidth;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdGiMarbleTexture object pointers.
*/
typedef OdSmartPtr<OdGiMarbleTexture> OdGiMarbleTexturePtr;

/** \details
    This class defines generic procedural material textures.
    Corresponding C++ library: TD_Gi
    <group OdGi_Classes>
*/
class FIRSTDLL_EXPORT OdGiGenericTexture : public OdGiProceduralTexture
{
public:
  ODRX_DECLARE_MEMBERS(OdGiGenericTexture);

  /** \details
    Default constructor for the OdGiGenericTexture class.
  */
  OdGiGenericTexture();
  OdGiGenericTexture(const OdGiGenericTexture &texture);
  virtual ~OdGiGenericTexture(void);

  /** \details
    Retrieves the type of the procedural texture.
    \returns
    the kGeneric value from the Type enumeration.
  */
  virtual Type type() const  {return kGeneric;}

  /** \details
    Sets the new OdGiVariant value to this generic texture.

    \param definition [in] New OdGiVariant value.
  */
  virtual void setDefinition(const OdGiVariant &definition);
  
  /** \details
    Retrieves the pointer to the OdGiVariant object used to store the procedural texture data.
    \returns
    smart pointer to the OdGiVariant object that holds the procedural texture data.
  */
  virtual OdGiVariantPtr definition(ODSYSDEF) const;
  OdGiVariant            definition(void) const;

  /** \details
    Retrieves a copy of the OdGiVariant object used to store the procedural texture data.
    
    \param pDefinition [in] Smart pointer to the object from which procedural texture data is copied.
  */
  virtual void definition(ODSYSDEF, OdGiVariantPtr &pDefinition) const;
  void         definition(OdGiVariant*& pDefinition);

  /** \details
    Equality operator for the OdGiGenericTexture class.
    Textures are equal if:
    * the specified texture is generic texture
    * underlaying definition object that store texture data are equal
    
    \param texture  [in] Texture to be compared.
    
    \returns
    true if the specified texture is equal to this texture, false otherwise.
  */
  virtual bool operator==(const OdGiMaterialTexture & texture) const;
  
  /** \details
    Assignment operator for the OdGiGenericTexture class.
    \param texture  [in] Texture to be assigned.
    
    \returns
    a reference to this generic texture.
  */
  OdGiGenericTexture &operator =(const OdGiGenericTexture &texture);

  // OdRxObject overrides

  /** \details
    Copies the data of the source object to the current object.

    \param pSource [in] Input source object.
  */
  virtual OdResult copyFrom(const OdRxObject* pSource);
private:
  OdGiVariantPtr    m_definition;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdGiGenericTexture object pointers.
*/
typedef OdSmartPtr<OdGiGenericTexture> OdGiGenericTexturePtr;

class OdGiImpMapper;
/** \details
  This class implements mappers.

  \remarks
  Mappers determine how an OdGiMaterialMap is mapped to an object surface.
  \sa
  <link tv_working_with_attributes_materials_mapping, Working with Mapping Properties>

  <group OdGi_Classes>
*/
class ODGI_EXPORT OdGiMapper : public OdGiParameter
{
public:
  ODRX_DECLARE_MEMBERS_READWRITE(OdGiMapper, OdGiImpMapper);
  /** \details
    Specifies the mapping projection.
  */
  enum Projection
  {
    /**Inherits projection from the current material's mapper. */
    kInheritProjection   = 0,
    /**Maps directly to XY coordinates. */
    kPlanar              = 1,
    /**Maps to planes perpendicular to major axes. */
    kBox                 = 2,
    /**Maps to cylinders aligned with the Z-axis. */
    kCylinder            = 3,
    /**Maps to spheres aligned with the Z-axis. */
    kSphere              = 4,
    /**Maps directly to surface coordinates. For .dgn materials. */
    kDgnParametric       = 0x32,
    /**Maps directly to surface coordinates. For .dgn materials. */
    kDgnPlanar           = 0x33,
    /**Maps to cylinders aligned with the Z-axis. For .dgn materials. */
    kDgnCylinder         = 0x34,
    /**Maps to cylinders aligned with the Z-axis. If normal to surface is the same as Z-axis, then uses planar mapping. For .dgn materials. */
    kDgnCylinderCapped   = 0x35,
    /**Maps to spheres aligned with the Z-axis. For .dgn materials. */
    kDgnSphere           = 0x36
  };

  /** \details
    Specifies the mapper's tiling method.
  */
  enum Tiling
  {
    /**Inherits tiling from the current material's mapper. */
    kInheritTiling    = 0,
    /**Repeats map along image axes. */
    kTile             = 1,
    /**Crops map < 0.0 or > 1.0 on image axes. */
    kCrop             = 2,
    /**Clamps (stretches) map between 0.0 and 1.0 on image axes. */
    kClamp            = 3,
    /**Mirrors the material map at every integer boundary. */
    kMirror           = 4
  };

  /** \details
    Specifies the automatic transform mode.
  */
  enum AutoTransform
  {
    /**Inherits automatic transform mode from the current material's mapper. */
    kInheritAutoTransform = 0x0,
    /**No automatic transform. */
    kNone                 = 0x1,
    /**Adjusts the mapper transform to align with and fit the current object. */
    kObject               = 0x2,
    /**Multiplies the mapper transform by the current block transform. */
    kModel                = 0x4
  };

  ODGI_EXPORT_STATIC static const OdGiMapper kIdentity;

  OdGiMapper(void);
  virtual ~OdGiMapper(void);

  OdGiMapper(const OdGiMapper &mapper);
  OdGiMapper & operator= (const OdGiMapper &mapper);
  bool         operator==(const OdGiMapper &mapper) const;
  bool         operator!=(const OdGiMapper &mapper) const
  {
    return !(*this == mapper);
  };

  virtual                  void set(const OdGiMapper &mapper);
  virtual                  void setProjection(Projection projection);
  virtual                  void setAutoTransform(AutoTransform autoTransform);
  virtual                  void setTransform(const OdGeMatrix3d &transform);

  virtual                     Projection             projection(void) const;
  virtual                     AutoTransform          autoTransform(void) const;
  virtual                     const OdGeMatrix3d&    transform(void) const;

  void        setUTiling(Tiling tiling);
  void        setVTiling(Tiling tiling);
  Tiling      uTiling(void) const;
  Tiling      vTiling(void) const;
};


/** \details
  This class implements material maps.

  \remarks
  Material maps define bitmapped images that are applied to object surfaces.
  \sa
  <link tv_working_with_attributes_materials_mapping, Working with Mapping Properties>
  <group OdGi_Classes>
*/
class ODGI_EXPORT OdGiMaterialMap : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdGiMaterialMap);

  /** \details
    Describes the image source of this MaterialMap object.
  */
  enum Source
  {
    /**Map is created from the current scene. */
    kScene      = 0,
    /**Map is from a file. */
    kFile       = 1,
    /**Map is procedural. */
    kProcedural = 2
  };
  enum Filter
  {
    kFilterDefault = 0,
    kFilterNone
  };

  ODGI_EXPORT_STATIC static const OdGiMaterialMap kNull;

  /** \details
    Default constructor for the OdGiMaterialMap class. Sets the material map source to kFile
    and blend factor to 1.0.
  */
  OdGiMaterialMap();
  OdGiMaterialMap(const OdGiMaterialMap &matMap);

  virtual void set(const OdGiMaterialMap &matMap);
  /** \details
    Sets the image source for this MaterialMap object.

    \param source [in]  Image source.

    \remarks
    Source must be one of the following:

    <table>
    Name         Value   Description
    kScene       0       Image is created from the current scene.
    kFile        1       Image is from a file.
    kProcedural  2       Image is procedurally generated.
    </table>
  */
  virtual void setSource(Source source);

  /** \details
    Sets the source filename for this MaterialMap object.
    \param filename [in]  Source filename.
  */
  virtual void setSourceFileName(const OdChar * filename);

  /** \details
    Sets the blend factor for this MaterialMap object.

    \param blendFactor [in]  Blend factor.

    \remarks
    A blend factor of 0.0 makes the MaterialMap invisible. A blend factor of 1.0 makes it opaque.
    In between, the MaterialMap is transparent.
  */
  virtual void setBlendFactor(double blendFactor);

  /** \details
    Sets the material texture for this MaterialMap object.

    \param pTexture [in]  Material texture.
  */
  void setTexture(ODSYSDEF, OdGiMaterialTexturePtr pTexture);
  virtual void setTexture(const OdGiMaterialTexture * pTexture);

  /** \details
    Retrieves a mapper for this material map.
    
    \returns
    Returns a reference to, or a copy of, the OdGiMapper for this MaterialMap object.

    \remarks
    The transform matrix defines mapping of an OdGiMaterialMap image when applied to the surface of an object.
  */
  OdGiMapper& mapper();

  /** \details
    Retrieves the image source for this MaterialMap object.

    \returns
    a value from the Source enumeration that can be one of the following:

    <table>
    Name         Value   Description
    kScene       0       Image is created from the current scene.
    kFile        1       Image is from a file.
    kProcedural  2       Image is procedurally generated.
    </table>
  */
  virtual Source source() const;

  /** \details
    Retrieves the source filename for this MaterialMap object.
    
    \returns
    source filename as OdString instance.
  */
  virtual const OdChar* sourceFileName() const;

  /** \details
    Retrieves the blend factor for this MaterialMap object.

    \returns
    blend factor as a value of the double type.
    
    \remarks
    A blend factor of 0.0 makes the MaterialMap invisible. A blend factor of 1.0 makes it opaque.
    In between, the MaterialMap is transparent.
  */
  virtual double blendFactor() const;

  /** \details
    Retrieves a mapper for this material map.
    \returns
    a reference to the OdGiMapper for this MaterialMap object.
  */
  virtual const OdGiMapper& mapper() const;

  /** \details
    Sets the OdGiMapper for this MaterialMap object.

    \param mapper [in]  OdGiMapper reference.
  */
  virtual void setMapper(const OdGiMapper &mapper);

  /** \details
    Retrieves the material texture for this MaterialMap object.
    
    \returns
    a smart pointer to the material texture.
  */
  const OdGiMaterialTexturePtr texture(ODSYSDEF) const;
  virtual const OdGiMaterialTexture * texture(void) const;

  /** \details
    Equality operator for the OdGiMaterialMap class.
    Material maps are equal if:
    * the texture source file values are equal (both can be NULL)
    * source file names are equal
    * blend factors are equal
    * mapper objects are equal.
    
    \param other  [in] Material mapper to be compared.
    
    \returns
    true if the material map is equal to this material map, false otherwise.
  */
  bool operator ==(const OdGiMaterialMap &other) const
  {
    if ((m_source      == other.m_source)      &&
        (m_fileName    == other.m_fileName)    &&
        (m_blendFactor == other.m_blendFactor) &&
        (m_mapper      == other.m_mapper))
    {
      if (m_texture.isNull() && other.m_texture.isNull())
        return true;
      if (!m_texture.isNull() && !other.m_texture.isNull())
        return (*m_texture == *(other.m_texture));
    }
    return false;
  }
  
  /** \details
    Inequality operator for the OdGiMaterialMap class.
    Material maps are not equal if at least one of the following conditions fails:
    * the texture source file values are equal (both can be NULL)
    * source file names are equal
    * blend factors are equal
    * mapper objects are equal.
    
    \param other  [in] Material mapper to be compared.
    
    \returns
    true if the material map is not equal to this material map, false otherwise.
  */
  bool operator !=(const OdGiMaterialMap &other) const
  {
    return !(*this == other);
  }

  /** \details
    Assignment operator for the OdGiMaterialMap class.
    Assigns map source, file name, blend factor, mapper and texture to this material map.
    
    \param texture  [in] Texture to be assigned.
    
    \returns
    a reference to this material map.
  */
  OdGiMaterialMap &operator =(const OdGiMaterialMap& mmap)
  {
    m_source = mmap.m_source;
    m_fileName = mmap.m_fileName;
    m_blendFactor = mmap.m_blendFactor;
    m_mapper = mmap.m_mapper;
    m_texture = mmap.m_texture;
    return *this;
  }

  OdResult setFilter(Filter filter);
  Filter filter(void) const;
private:
  Source     m_source;
  OdString   m_fileName;
  double     m_blendFactor;
  OdGiMapper m_mapper;
  OdGiMaterialTexturePtr m_texture;
};

// OdGiMaterialColor inline implementations

inline
OdGiMaterialColor::OdGiMaterialColor()
  : m_method(kInherit)
  , m_factor(1.0)
{
}

inline
OdGiMaterialColor::OdGiMaterialColor(const OdCmEntityColor &overrideColor)
  : m_method(kOverride)
  , m_factor(1.0)
  , m_color(overrideColor)
{
}

inline
OdGiMaterialColor::OdGiMaterialColor(const OdGiMaterialColor &matColor)
{
  m_method = matColor.m_method;
  m_factor = matColor.m_factor;
  m_color = matColor.m_color;
}

inline
OdGiMaterialColor& OdGiMaterialColor::operator= (const OdGiMaterialColor &matColor)
{
  m_method = matColor.m_method;
  m_factor = matColor.m_factor;
  m_color = matColor.m_color;
  return *this;
}

inline void OdGiMaterialColor::set(const OdGiMaterialColor &matColor)
{
  m_method = matColor.m_method;
  m_factor = matColor.m_factor;
  m_color = matColor.m_color;
}

inline void
OdGiMaterialColor::setMethod(Method method)
{
  m_method = method;
}

inline void
OdGiMaterialColor::setFactor(double factor)
{
  m_factor = factor;
}

inline OdCmEntityColor&
OdGiMaterialColor::color()
{
  return m_color;
}

inline OdGiMaterialColor::Method
OdGiMaterialColor::method() const
{
  return m_method;
}

inline double
OdGiMaterialColor::factor() const
{
  return m_factor;
}

inline const OdCmEntityColor&
OdGiMaterialColor::color() const
{
  return m_color;
}

inline void
OdGiMaterialColor::setColor(const OdCmEntityColor &color)
{
  m_color = color;
}

// OdGiMaterialMap inline implementations

inline
OdGiMaterialMap::OdGiMaterialMap()
  : m_source(kFile)
  , m_blendFactor(1.0)
{
}

inline
OdGiMaterialMap::OdGiMaterialMap(const OdGiMaterialMap &matMap)
{
  set(matMap);
}

inline void
OdGiMaterialMap::setSource(Source source)
{
  m_source = source;
}

inline void
OdGiMaterialMap::setSourceFileName(const OdChar * filename)
{
  m_fileName = filename;
}

inline void
OdGiMaterialMap::setBlendFactor(double blendFactor)
{
  m_blendFactor = blendFactor;
}

inline OdGiMapper&
OdGiMaterialMap::mapper()
{
  return m_mapper;
}

inline OdGiMaterialMap::Source
OdGiMaterialMap::source() const
{
  return m_source;
}

inline const OdChar *
OdGiMaterialMap::sourceFileName() const
{
  return m_fileName.kwszPtr();
}

inline double
OdGiMaterialMap::blendFactor() const
{
  return m_blendFactor;
}

inline const OdGiMapper&
OdGiMaterialMap::mapper() const
{
  return m_mapper;
}

inline void
OdGiMaterialMap::setMapper(const OdGiMapper &mapper)
{
  m_mapper = mapper;
}

inline void
OdGiMaterialMap::setTexture(ODSYSDEF, OdGiMaterialTexturePtr pTexture)
{
  m_texture = pTexture;
}

inline const OdGiMaterialTexturePtr
OdGiMaterialMap::texture(ODSYSDEF) const
{
  return m_texture;
}

inline void
OdGiImageFileTexture::setSourceFileName(const OdChar * fileName)
{
  m_sourceFileName = fileName;
}

inline const OdChar * 
OdGiImageFileTexture::sourceFileName() const
{
  return m_sourceFileName;
}

inline bool
OdGiImageFileTexture::operator==(const OdGiMaterialTexture & texture) const
{
  if (!(texture.isA() == isA()))
    return false;
  const OdGiImageFileTexture &refTexture = static_cast<const OdGiImageFileTexture&>(texture);
  return m_sourceFileName == refTexture.m_sourceFileName;
}

inline OdGiImageFileTexture &
OdGiImageFileTexture::operator =(const OdGiImageFileTexture &texture)
{
  m_sourceFileName = texture.m_sourceFileName;
  return *this;
}

inline OdResult OdGiImageFileTexture::copyFrom(const OdRxObject* pSource)
{
  OdGiImageFileTexturePtr pSrcTex = OdGiImageFileTexture::ODSYSCALL1(cast, pSource);
  if (!pSrcTex.isNull())
  {
    setSourceFileName(pSrcTex->sourceFileName());
  }
  else
  {
    return eNotApplicable;
  }
  return eOk;
}

// OdGiRasterImageTexture inline implementations

inline void
OdGiRasterImageTexture::setRasterImage(const OdGiRasterImage *pRasterImage)
{
  m_pRasterImage = reinterpret_cast<const OdRxObject*>(pRasterImage);
}

inline const OdGiRasterImage *
OdGiRasterImageTexture::rasterImage() const
{
  return reinterpret_cast<const OdGiRasterImage*>(m_pRasterImage.get());
}

inline bool
OdGiRasterImageTexture::operator==(const OdGiMaterialTexture & texture) const
{
  if (!(texture.isA() == isA()))
    return false;
  const OdGiRasterImageTexture &refTexture = static_cast<const OdGiRasterImageTexture&>(texture);
  return m_pRasterImage.get() == refTexture.m_pRasterImage.get();
}

inline OdGiRasterImageTexture &
OdGiRasterImageTexture::operator =(const OdGiRasterImageTexture &texture)
{
  m_pRasterImage = texture.m_pRasterImage;
  return *this;
}

inline OdResult OdGiRasterImageTexture::copyFrom(const OdRxObject* pSource)
{
  OdGiRasterImageTexturePtr pSrcTex = OdGiRasterImageTexture::ODSYSCALL1(cast, pSource);
  if (!pSrcTex.isNull())
  {
    setRasterImage(pSrcTex->rasterImage());
  }
  else
  {
    return eNotApplicable;
  }
  return eOk;
}

// OdGiWoodTexture inline implementations

inline
OdGiWoodTexture::OdGiWoodTexture()
  : m_radialNoise(0.)
  , m_axialNoise(0.)
  , m_grainThickness(0.)
{
}

inline void
OdGiWoodTexture::setColor1(const OdGiMaterialColor &woodColor1)
{
  m_color1 = woodColor1;
}

inline const OdGiMaterialColor&
OdGiWoodTexture::color1(void) const
{
  return m_color1;
}

inline void
OdGiWoodTexture::setColor2(const OdGiMaterialColor &woodColor2)
{
  m_color2 = woodColor2;
}

inline const OdGiMaterialColor&
OdGiWoodTexture::color2(void) const
{
  return m_color2;
}

inline void
OdGiWoodTexture::setRadialNoise(double radialNoise)
{
  m_radialNoise = radialNoise;
}

inline double
OdGiWoodTexture::radialNoise(void) const
{
  return m_radialNoise;
}

inline void
OdGiWoodTexture::setAxialNoise(double axialNoise)
{
  m_axialNoise = axialNoise;
}

inline double
OdGiWoodTexture::axialNoise(void) const
{
  return m_axialNoise;
}

inline void
OdGiWoodTexture::setGrainThickness(double grainThickness)
{
  m_grainThickness = grainThickness;
}

inline double
OdGiWoodTexture::grainThickness(void) const
{
  return m_grainThickness;
}

inline bool
OdGiWoodTexture::operator==(const OdGiMaterialTexture & texture) const
{
  if (!(texture.isA() == isA()))
    return false;
  const OdGiWoodTexture &refTexture = static_cast<const OdGiWoodTexture&>(texture);
  return (m_color1 == refTexture.m_color1) &&
         (m_color2 == refTexture.m_color2) &&
         (m_radialNoise == refTexture.m_radialNoise) &&
         (m_axialNoise == refTexture.m_axialNoise) &&
         (m_grainThickness == refTexture.m_grainThickness);
}

inline OdGiWoodTexture &
OdGiWoodTexture::operator =(const OdGiWoodTexture &texture)
{
  m_color1 = texture.m_color1;
  m_color2 = texture.m_color2;
  m_radialNoise = texture.m_radialNoise;
  m_axialNoise = texture.m_axialNoise;
  m_grainThickness = texture.m_grainThickness;
  return *this;
}

inline OdResult OdGiWoodTexture::copyFrom(const OdRxObject* pSource)
{
  OdGiWoodTexturePtr pSrcTex = OdGiWoodTexture::ODSYSCALL1(cast, pSource);
  if (!pSrcTex.isNull())
  {
    setColor1(pSrcTex->color1());
    setColor2(pSrcTex->color2());
    setRadialNoise(pSrcTex->radialNoise());
    setAxialNoise(pSrcTex->axialNoise());
    setGrainThickness(pSrcTex->grainThickness());
  }
  else
  {
    return eNotApplicable;
  }
  return eOk;
}

// OdGiMarbleTexture inline implementations

inline
OdGiMarbleTexture::OdGiMarbleTexture()
  : m_veinSpacing(0.)
  , m_veinWidth(0.)
{
}

inline void
OdGiMarbleTexture::setStoneColor(const OdGiMaterialColor &stoneColor)
{
  m_stoneColor = stoneColor;
}

inline const OdGiMaterialColor&
OdGiMarbleTexture::stoneColor(void) const
{
  return m_stoneColor;
}

inline void
OdGiMarbleTexture::setVeinColor(const OdGiMaterialColor &veinColor)
{
  m_veinColor = veinColor;
}

inline const OdGiMaterialColor&
OdGiMarbleTexture::veinColor(void) const
{
  return m_veinColor;
}

inline void
OdGiMarbleTexture::setVeinSpacing(double veinSpacing)
{
  m_veinSpacing = veinSpacing;
}

inline double
OdGiMarbleTexture::veinSpacing(void) const
{
  return m_veinSpacing;
}

inline void
OdGiMarbleTexture::setVeinWidth(double veinWidth)
{
  m_veinWidth = veinWidth;
}

inline double
OdGiMarbleTexture::veinWidth(void) const
{
  return m_veinWidth;
}

inline bool
OdGiMarbleTexture::operator==(const OdGiMaterialTexture & texture) const
{
  if (!(texture.isA() == isA()))
    return false;
  const OdGiMarbleTexture &refTexture = static_cast<const OdGiMarbleTexture&>(texture);
  return (m_stoneColor == refTexture.m_stoneColor) &&
         (m_veinColor == refTexture.m_veinColor) &&
         (m_veinSpacing == refTexture.m_veinSpacing) &&
         (m_veinWidth == refTexture.m_veinWidth);
}

inline OdGiMarbleTexture &
OdGiMarbleTexture::operator =(const OdGiMarbleTexture &texture)
{
  m_stoneColor = texture.m_stoneColor;
  m_veinColor = texture.m_veinColor;
  m_veinSpacing = texture.m_veinSpacing;
  m_veinWidth = texture.m_veinWidth;
  return *this;
}

inline OdResult OdGiMarbleTexture::copyFrom(const OdRxObject* pSource)
{
  OdGiMarbleTexturePtr pSrcTex = OdGiMarbleTexture::ODSYSCALL1(cast, pSource);
  if (!pSrcTex.isNull())
  {
    setStoneColor(pSrcTex->stoneColor());
    setVeinColor(pSrcTex->veinColor());
    setVeinSpacing(pSrcTex->veinSpacing());
    setVeinWidth(pSrcTex->veinWidth());
  }
  else
  {
    return eNotApplicable;
  }
  return eOk;
}

// OdGiGenericTexture inline implementations

inline
OdGiGenericTexture::OdGiGenericTexture()
{
}

inline void
OdGiGenericTexture::setDefinition(const OdGiVariant &definition)
{
  if (m_definition.isNull())
  {
    m_definition = OdGiVariant::createObject(definition);
  }
  else
  {
    *m_definition = definition;
  }
}

inline OdGiVariantPtr
OdGiGenericTexture::definition(ODSYSDEF) const
{
  return m_definition;
}
inline OdGiVariant
OdGiGenericTexture::definition(void) const
{
  OdGiVariantPtr pDef = ODSYSCALL0(definition);
  if (!pDef.isNull())
  {
    return *pDef.get();
  }
  return OdGiVariant();
}

inline void
OdGiGenericTexture::definition(ODSYSDEF, OdGiVariantPtr &pDefinition) const
{
  if (m_definition.isNull())
  {
    pDefinition = OdGiVariant::createObject();
  }
  else
  {
    pDefinition = OdGiVariant::createObject(*m_definition);
  }
}

inline void
OdGiGenericTexture::definition(OdGiVariant*& pDefinition)
{
  pDefinition = new OdGiVariant(definition());
}

inline bool
OdGiGenericTexture::operator==(const OdGiMaterialTexture & texture) const
{
  if (!(texture.isA() == isA()))
    return false;
  const OdGiGenericTexture &refTexture = static_cast<const OdGiGenericTexture&>(texture);
  if (m_definition.isNull() && refTexture.m_definition.isNull())
    return true;
  if (!m_definition.isNull() && !refTexture.m_definition.isNull())
    return (*m_definition == *(refTexture.m_definition));
  return false;
}

inline OdGiGenericTexture &
OdGiGenericTexture::operator =(const OdGiGenericTexture &texture)
{
  if (!texture.m_definition.isNull())
    m_definition = OdGiVariant::createObject(*(texture.m_definition));
  else
    m_definition.release();
  return *this;
}

inline OdResult OdGiGenericTexture::copyFrom(const OdRxObject* pSource)
{
  OdGiGenericTexturePtr pSrcTex = OdGiGenericTexture::ODSYSCALL1(cast, pSource);
  if (!pSrcTex.isNull())
  {
    setDefinition(*(pSrcTex->ODSYSCALL0(definition)));
  }
  else
  {
    return eNotApplicable;
  }
  return eOk;
}

#include "../TD_PackPop.h"

#endif //#ifndef __ODGIMATERIAL_H__
