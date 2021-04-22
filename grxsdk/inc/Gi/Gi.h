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

#ifndef _OD_GI_H_
#define _OD_GI_H_

#include "../RxObject.h"
#include "../CmColorBase.h"
#include "GiAuxData.h"
#include "../DbObjectId.h"
#include "GiLinetype.h"


class OdDbStub;
class OdCmEntityColor;
class OdGeVector3d;
class OdGiMapper;
class OdCmTransparency;
struct OdGiDgLinetypeModifiers;
class OdGiFill;
struct OdGiLineweightOverride;
class OdGiPalette;
class OdDbEntity;
class OdGiVariant;
class OdGiContext;

typedef enum
{
  kOdGiBitonal,
  kOdGiPalette,
  kOdGiGray,
  kOdGiRGBA,
  kOdGiBGRA,
  kOdGiARGB,
  kOdGiABGR,
  kOdGiBGR,
  kOdGiRGB
} OdGiImageOrg;

typedef enum
{
  kOdGiXLeftToRightTopFirst,
  kOdGiXLeftToRightBottomFirst,
  kOdGiXRightToLeftTopFirst,
  kOdGiXRightToLeftBottomFirst,
  kOdGiYTopToBottomLeftFirst,
  kOdGiYTopToBottomRightFirst,
  kOdGiYBottomToTopLeftFirst,
  kOdGiYBottomToTopRightFirst
} OdGiImageOrient;

typedef enum
{
  kDefaultScaleFilter,
  kNearestScaleFilter,
  kBellScaleFilter,
  kMitchellScaleFilter,
  kTriangleScaleFilter,
  kCubicScaleFilter,
  kBsplineScaleFilter,
  kLanczos3ScaleFilter
} OdGiScaleFilterType;

typedef enum
{
  kDefaultRotationFilter,
  kInterpolatedRotationFilter,
  kNearestRotationFilter,
} OdGiRotationFilterType;

typedef enum
{
  kDefaultScale,
  kRelativeScale,
  kUnTransformedScale
} OdGiScaleType;

enum OdGiHighlightStyle
{
  kOdGiHighlightNone,
  kOdGiHighlightCustom,
  kOdGiHighlightDashedAndThicken,
  kOdGiHighlightDim,
  kOdGiHighlightThickDim,
  kOdGiHighlightGlow
};

enum OdGiEdgeStyleMaskValues
{
  kOdGiNoEdgeStyleMask = 0,
  kOdGiJitterMask = 1,
  kOdGiOverhangMask = 2,
  kOdGiEdgeColorMask = 4
};

typedef enum
{
  kOdGiFillAlways = 1,  // Always fill closed graphic primitives.
  kOdGiFillNever  = 2   // Never fill closed graphic primitives.
} OdGiFillType;

typedef enum
{
  kOdGiInvisible      = 0, // Invisible
  kOdGiVisible        = 1, // Visible
  kOdGiSilhouette     = 2  // Silhouette edge
} OdGiVisibility;

#include "..\TD_PackPush.h"

/** \details
    This class provides an interface to the graphical attributes of graphic
    primitives.
  
    \remarks
    OdGiDrawableTraits is a superset of OdGiSubEntityTraits, and exposes
    additional traits that are consistant for the entire OdGiDrawable.
    
    An OdGiDrawableTraits instance is available during calls to subSetAttributes.
    Graphical attribute settings are used for all graphical primitives until they are changed.
    
    \sa
    TD_Gi
    
    <group OdGi_Classes> 
*/
class FIRSTDLL_EXPORT OdGiSubEntityTraits : public OdRxObject
{ 
public:
  ODRX_DECLARE_MEMBERS(OdGiSubEntityTraits);
public:

  /** \details
    Represents valid bitmasks that are passed to the setDrawFlags() method calls.
  */
  enum DrawFlags
  {
    kNoDrawFlags = 0x0000,   // Default value. No DrawFlags specified.
    kDrawBackfaces = 0x0001,   // Forces backfaces vectorization.
    kDrawHatchGroup = 0x0002,   // Next shells and meshes should draw hatches.
    kDrawFrontfacesOnly = 0x0004,   // Forces discard backfaces mode.
    kDrawGradientFill = 0x0008,   // Draws with gradient fill.
    kDrawSolidFill = 0x0010,   // Draws with solid fill.
    kDrawNoLineWeight = 0x0020,   // Disables lineweight.
    kDrawNoOptimization = 0x0040,
    kDrawUseAcGiEntityForDgnLineType = 0x0080,
    kDrawFillTextBoundaryStart = 0x00100,
    kDrawFillTextBoundaryEnd = 0x00200,
    kDrawFillSelectionWindow = 0x00400,
    kDrawNoForceByLayer = 0x00800,
    kDrawNoPlotstyle = 0x001000,   // Disables plotstyles.        
    // the range before 0x8000 is reserved.
    kDrawContourFill = 0x08000, // Specific to DGN files.
    kDisableLayoutCache = 0x10000, // Disable metafile caching for layout switching.
    kDrawBoundaryForClipping = 0x20000, // Draw (rough) boundary of object to be checked // when clipping is performed, set by vectorizer.
    kDrawBoundaryForClippingDrw = 0x40000, // Draw (rough) boundary of object to be checked // when clipping is performed, set by a drawable.
    kClipSetIsEmpty = 0x80000,
    kDrawPolygonFill = 0x100000, // Fill in all modes if FillAlways mode enabled.
    kExcludeFromViewExt = 0x200000, // Don't use extents of the entity when calculating total extents.
    kDrawDgLsPolyWithoutBreaks = 0x400000, // Draw polylines/polygons with Dgn Line Style without segmentation.
    kPolygonProcessing = 0x800000, // Polygon filling logic must be applied for shell primitive.
    kDisableAutoGenerateNormals = 0x1000000, // Avoid automatic generation of normals for mesh/shell primitives.
    kDisableFillModeCheck = 0x2000000, // Avoid checking of OdGiContext::fillMode during filling of geometry primitives.
    kDrawUnderlayReference = 0x4000000, // Draw underlay reference object.
    kLineStyleScaleOverride = 0x8000000, // Doesn't multiply current line scale to byBlock line scale. Only for multiplyByBlockLinetypeScales mode.
    kDisableDisplayClipping = 0x10000000, // Disable display clipping
    kRegenTypeDependent2dDraw   = 0x20000000, // Specific for spamodeler. Draw edges as polyline created by points generated by the faceter
    kInternalDrawFlags = kDisableLayoutCache | kClipSetIsEmpty | kRegenTypeDependent2dDraw,
    // Flags which can be inherited by nested drawables.
    kInheritableDrawFlags = kDrawNoLineWeight | kDrawNoPlotstyle | kDrawBoundaryForClipping | kDrawBoundaryForClippingDrw |
    kInternalDrawFlags | kExcludeFromViewExt | kDrawBackfaces | kDrawFrontfacesOnly | kDisableDisplayClipping | kRegenTypeDependent2dDraw
  };
 
  /** \details
    Represents shadow flags.
  */
  enum ShadowFlags
  {
    kShadowsCastAndReceive = 0,   // Geometry could cast and receive shadows.
    kShadowsDoesNotCast = 1,   // Geometry doesn't cast shadows.
    kShadowsDoesNotReceive = 2,   // Geometry doesn't receive shadows.
    kShadowsIgnore = kShadowsDoesNotCast | kShadowsDoesNotReceive // Geometry doesn't cast and receive shadows.
  };
  /** \details
    Represents bitmask lock flags.
  */
  enum LockFlags
  {
    kNoLockFlags = 0x00000000,   // No lock flags are used.
    kLockColors = 0x00000001,   // Lock colors.
    kLockLineWeight = 0x00000002,   // Lock lineweight.
    kLockLineType = 0x00000004,   // Lock linetype.
    kLockLineTypeScale = 0x00000008,   // Lock linetype scale.
    kLockLayer = 0x00000010,   // Lock layer.
    kLockByBlockLayer = 0x00000020,   // Lock the ByBlock layer.
    kKeepAuxDataAndLockFlags = 0x00000040,   // Keep auxiliary data and lock flags.
    kInheritableLockFlags = kLockColors | kLockLineWeight | kLockLineType | kLockLineTypeScale | kLockLayer | kKeepAuxDataAndLockFlags  // Inherited lock flags.
  };



  /** \details
    Represents flags that hint which attributes to set.
  */
  enum SubEntityHints
  {
    kHint2DAttributes = 1,  // Setup attributes only available in 2DWireframe mode (plotStyles and etc.).
    kHint3DAttributes = 2,  // Setup attributes only available in shaded modes (materials and etc.).
    kHintAllAttributes = kHint2DAttributes | kHint3DAttributes,  // Setup attributes that available in both 2D and 3D modes.
    kHintSnapModeOn = 4,  // Setup that we currently inside selection for snap method.
    kHintDefaultState = kHintAllAttributes  // Default setup flag for the attributes.
  };

  /** \details
    Represents selection flags.
  */
  enum SelectionFlags
  {
    kNoSelectionFlags = 0, // No selection flags set.
    kSelectionIgnore = 1, // Avoid geometry selection.
    kHighlightingGeometry = 2, // Geometry drawn only in case if entire entity highlighted.
    kHiddenInHighlight = 4  // Geometry hidden only in case if entire entity highlighted. 
  };

  virtual void              setColor(const OdUInt16 color) = 0;
  virtual void              setTrueColor(const OdCmEntityColor& color) = 0;
  virtual void              setLayer(const OdDbObjectId layerId) = 0;
  virtual void              setLineType(const OdDbObjectId linetypeId) = 0;
  virtual void              setSelectionMarker(const OdLongPtr markerId) = 0;
  virtual void              setFillType(const OdGiFillType) = 0;
  virtual void              setLineWeight(const OdDb::LineWeight lw) = 0;
  virtual void              setLineTypeScale(double dScale = 1.0) = 0;
  virtual void              setThickness(double dThickness) = 0;
  virtual void              setVisualStyle(const OdDbObjectId visualStyleId);
  virtual void              setPlotStyleName(OdDb::PlotStyleNameType /*type*/, const OdDbObjectId & /*id*/ = OdDbObjectId()) { }
  virtual void              setMaterial(const OdDbObjectId materialId);
  virtual void              setMapper(const OdGiMapper * mapper);
  virtual void              setSectionable(bool bSectionable);
  virtual OdResult          setDrawFlags(OdUInt32 flags);
  virtual OdResult          setShadowFlags(ShadowFlags flags);
  virtual void              setSelectionGeom(bool bSelectionflag);
  virtual void              setTransparency(const OdCmTransparency &transparency);
  virtual void              setFill(const OdGiFill* pFill);

  virtual OdUInt16                color(void) const = 0;
  virtual OdCmEntityColor         trueColor(void) const = 0;
  virtual OdDbObjectId            layerId(void) const = 0;
  virtual OdDbObjectId            lineTypeId(void) const = 0;
  virtual OdGiFillType            fillType(void) const = 0;
  virtual OdDb::LineWeight        lineWeight(void) const = 0;
  virtual double                  lineTypeScale(void) const = 0;
  virtual double                  thickness(void) const = 0;
  virtual OdDbObjectId            visualStyle(void) const;
  virtual OdDb::PlotStyleNameType getPlotStyleNameId(OdDbObjectId & /*idResult*/) const
  {
    return OdDb::kPlotStyleNameByLayer;
  }
  virtual OdDbObjectId            materialId(void) const;
  virtual const OdGiMapper *      mapper(void) const;
  virtual bool                    sectionable(void) const;
  virtual OdUInt32                drawFlags(void) const;
  virtual ShadowFlags             shadowFlags(void) const;
  virtual bool                    selectionGeom(void) const;
  virtual OdCmTransparency        transparency(void) const;
  virtual const OdGiFill*         fill(void) const;

  virtual void pushMarkerOverride(bool /*flag*/, const OdLongPtr /*markerId*/) { }
  virtual void popMarkerOverride(void) { }
  virtual void clearMarkerOverride(void) { }
  
  virtual void setFillPlane(const OdGeVector3d* pNormal = 0);
  virtual bool fillPlane(OdGeVector3d&);

  virtual void setSecondaryTrueColor(const OdCmEntityColor& color);
  virtual OdCmEntityColor secondaryTrueColor() const;

  virtual OdResult setSelectionFlags(const SelectionFlags flags) { return eOk; }
  virtual SelectionFlags    selectionFlags(void) const {return kNoSelectionFlags;}
  /** \details
    Sets the lock flags.

    \param lockFlags [in]  Input bitmask with LockFlags.
  */
  virtual void setLockFlags(
    OdUInt32 lockFlags);

  /** \details
    Retrieves the current LockFlags bitmask.

    \returns
    Lock bit flags as the OdUInt32 value.
  */
  virtual OdUInt32 lockFlags() const;

  // Specific to DGN files
  /** \details
    Sets Dgn Line Style modifiers.

    \param pLSMod [in]  Pointer to structure with Dgn Line Style modifiers.
  */
  virtual void setLineStyleModifiers(
    const OdGiDgLinetypeModifiers* pLSMod);

  /** \details
    Retrieves pointer to the current Dgn Line Style modifiers structure.

    \returns
    pointer to the OdGiDgLinetypeModifiers.
  */
  virtual const OdGiDgLinetypeModifiers* lineStyleModifiers() const;

  /** \details
  Sets pointer to auxiliary data context.

  \param pAuxData [in]  pointer to auxiliary data context.
  */
  virtual void setAuxData(
    const OdGiAuxiliaryDataPtr& pAuxData);

  /** \details
    Retrieves pointer to auxiliary data context.

    \returns
    smart pointer to the auxiliary data context object.
  */
  virtual OdGiAuxiliaryDataPtr auxData() const;

  /** \details
    Pushes lineweight scale and style override into lineweight overrides stack.
    \param pOverride [in]  New lineweight override.
    \returns
    true in case if lineweight overrides supported by underlying vectorization pipeline.
  */
  virtual bool pushLineweightOverride(const OdGiLineweightOverride* pOverride);

  /** \details
    Pops lineweight scale and style override from lineweight overrides stack.
  */
  virtual void popLineweightOverride();

  /** \details
    Push palette override into palette overrides stack.
    \param pOverride [in]  New palette override.
    \returns Returns true in case if palette overrides supported by underlying vectorization pipeline.
  */
  virtual bool pushPaletteOverride(const OdGiPalette* pOverride);

  /** \details
    Pop palette override from palette overrides stack.
  */
  virtual void popPaletteOverride();

  /** \details
   Retrieves the set of SubEntityHints flags which can be used to provide more flexible tuning of
   subSetAttributes traits processing.

   \returns
   SubEntityHints flags as the OdUInt32 value.
 */
  virtual OdUInt32 setupForEntity() const;

  virtual void setHighlightFlags(bool bEnable, OdInt32 nPattern); // internal use
  virtual bool highlightFlags(OdInt32* pPattern = NULL) const; // internal use

};

inline void OdGiSubEntityTraits::setMaterial(const OdDbObjectId /*materialId*/)
{
}

inline OdDbObjectId OdGiSubEntityTraits::materialId(void) const
{
  return OdDbObjectId();
}

inline void OdGiSubEntityTraits::setMapper(const OdGiMapper * /*mapper*/)
{
}

inline const OdGiMapper* OdGiSubEntityTraits::mapper(void) const
{
  return NULL;
}

inline void OdGiSubEntityTraits::setVisualStyle(OdDbObjectId /*visualStyleId*/)
{
}

inline OdDbObjectId OdGiSubEntityTraits::visualStyle(void) const
{
  return OdDbObjectId();
}

inline void OdGiSubEntityTraits::setSectionable(bool /*bSectionable*/)
{
}

inline bool OdGiSubEntityTraits::sectionable(void) const
{
  return false;
}

inline OdResult OdGiSubEntityTraits::setDrawFlags(OdUInt32 /*flags*/)
{
  return Oda::eNotImplementedYet;
}

inline OdUInt32 OdGiSubEntityTraits::drawFlags(void) const
{
  return 0;
}

inline OdResult OdGiSubEntityTraits::setShadowFlags(ShadowFlags /*flags*/)
{
  return Oda::eNotImplementedYet;
}

inline OdGiSubEntityTraits::ShadowFlags OdGiSubEntityTraits::shadowFlags(void) const
{
  return kShadowsCastAndReceive;
}

inline void OdGiSubEntityTraits::setSelectionGeom(bool)
{
}

inline bool OdGiSubEntityTraits::selectionGeom(void) const
{
  return false;
}

inline void OdGiSubEntityTraits::setTransparency(const OdCmTransparency&)
{
}


inline void OdGiSubEntityTraits::setFill(const OdGiFill * /*pFill*/)
{
}

inline const OdGiFill *OdGiSubEntityTraits::fill(void) const
{
  return NULL;
}

/** \details
    This class provides an interface to the graphical attributes of graphic
    primitives.
  
    \remarks
    An OdGiSubEntityTraits instance is available during calls to subWorldDraw and subViewportDraw,
    so that drawable classes can control attributes during the vectorization process. 
    Graphical attribute settings are used for all graphical primitives until they are changed.
    
    The functions in this class are implemented by the OdGiAbstractVectorizer
    class.

    \sa
    TD_Gi
    
    <group OdGi_Classes> 
*/
class FIRSTDLL_EXPORT OdGiDrawableTraits : public OdGiSubEntityTraits
{
public:
  
public:
  ODRX_DECLARE_MEMBERS(OdGiDrawableTraits);

  enum HighlightProperty
  {
    kVertexRolloverHighlightSize,
  };

  TD_USING(OdGiSubEntityTraits::setupForEntity);
  virtual void              setupForEntity(OdDbEntity *pEntity);

  /** \details
    Adds a light object to the model.

    \param lightId [in]  Object ID of the light.

    \remarks
    Through this interface, drawables that emit light can add light objects to the model.
    \sa
    <link tv_working_with_lights, Working with Lights>
  */
  virtual void addLight(const OdDbObjectId& lightId);

  virtual void              setLinePattern(const OdGiLineType linePattern);
  virtual OdGiLineType      linePattern(void) const;

  virtual OdResult setSelectionFlags(const SelectionFlags flags);
  virtual SelectionFlags    selectionFlags(void) const;

  virtual OdResult setHighlightProperty(HighlightProperty p, OdGiVariant&       value);
  virtual OdGiVariant  highlightProperty(HighlightProperty p) const;

  virtual OdGiContext      *context(void) const { return NULL; }

protected:

  enum LayerFlags {
    kNone = 0x00,
    kOff = 0x01,
    kFrozen = 0x02,
    kZero = 0x04,
    kLocked = 0x08
  };

  virtual void               setLayerFlags(OdUInt8 /*flags*/) { }
};


/** \details
  A data type that represents a smart pointer to an <link OdGiSubEntityTraits, OdGiSubEntityTraits> object.
*/
typedef OdSmartPtr<OdGiSubEntityTraits> OdGiSubEntityTraitsPtr;
typedef OdSmartPtr<OdGiDrawableTraits> OdGiDrawableTraitsPtr;

class FIRSTDLL_EXPORT OdGiNonEntityTraits : public OdGiDrawableTraits
{
public:
  ODRX_DECLARE_MEMBERS(OdGiNonEntityTraits);

  virtual void                setupForEntity(OdDbEntity* pEntity);
  virtual void                addLight(const OdDbObjectId& id);

  virtual void                setColor(const OdUInt16 color);
  virtual OdUInt16            color(void) const;
  virtual void                setTrueColor(const OdCmEntityColor& color);
  virtual OdCmEntityColor     trueColor(void) const;
  virtual void                setLayer(const OdDbObjectId layerId);
  virtual OdDbObjectId        layerId(void) const;
  virtual void                setLineType(const OdDbObjectId linetypeId);
  virtual OdDbObjectId        lineTypeId(void) const;
  virtual void                setSelectionMarker(const OdLongPtr markerId);
  virtual void                setFillType(const OdGiFillType fillType);
  virtual OdGiFillType        fillType(void) const;
  virtual void                setLineWeight(const OdDb::LineWeight lw);
  virtual OdDb::LineWeight    lineWeight(void) const;
  virtual void                setThickness(double thickness);
  virtual double              thickness(void) const;
  virtual void                setLineTypeScale(double dScale);
  virtual double              lineTypeScale(void) const;
  virtual void                setMaterial(const OdDbObjectId matId);
  virtual OdDbObjectId        materialId(void) const;
  virtual void                setSelectionGeom(bool bSelectionflag);
  virtual bool                selectionGeom(void) const;

  virtual void                setTransparency(const OdCmTransparency& transparency);
  virtual OdCmTransparency    transparency(void) const;

};

inline void OdGiNonEntityTraits::setupForEntity(OdDbEntity* /*pEntity*/)
{  
}

inline void OdGiNonEntityTraits::addLight(const OdDbObjectId& /*id*/)
{  
}

inline void OdGiNonEntityTraits::setColor(const OdUInt16 /*color*/)
{  
}

inline OdUInt16 OdGiNonEntityTraits::color(void) const
{
  return 0;
}

inline void OdGiNonEntityTraits::setTrueColor(const OdCmEntityColor& /*color*/)
{  
}

inline void OdGiNonEntityTraits::setLayer(const OdDbObjectId /*layerId*/)
{

}

inline OdDbObjectId OdGiNonEntityTraits::layerId(void) const
{
  return OdDbObjectId();
}

inline void OdGiNonEntityTraits::setLineType(const OdDbObjectId /*linetypeId*/)
{ 
}

inline OdDbObjectId OdGiNonEntityTraits::lineTypeId(void) const
{
  return  OdDbObjectId();
}

inline void OdGiNonEntityTraits::setMaterial(const OdDbObjectId /*matId*/)
{  
}

inline OdDbObjectId OdGiNonEntityTraits::materialId(void) const
{
  return  OdDbObjectId();
}

inline void OdGiNonEntityTraits::setSelectionMarker(const OdLongPtr /*markerId*/)
{  
}

inline void OdGiNonEntityTraits::setFillType(const OdGiFillType /*fillType*/)
{  
}

inline OdGiFillType OdGiNonEntityTraits::fillType(void) const
{
  return kOdGiFillAlways;
}

inline void OdGiNonEntityTraits::setLineWeight(const OdDb::LineWeight /*lw*/)
{  
}

inline OdDb::LineWeight OdGiNonEntityTraits::lineWeight(void) const
{
  return OdDb::kLnWt000;
}

inline void OdGiNonEntityTraits::setThickness(double /*thickness*/)
{  
}

inline double OdGiNonEntityTraits::thickness(void) const
{
  return 0.0;
}

inline void OdGiNonEntityTraits::setLineTypeScale(double /*dScale*/)
{  
}

inline double OdGiNonEntityTraits::lineTypeScale(void) const
{
  return 0.0;
}

inline void OdGiNonEntityTraits::setSelectionGeom(bool)
{  
}

inline bool OdGiNonEntityTraits::selectionGeom(void) const
{
  return false;
}

inline void OdGiNonEntityTraits::setTransparency(const OdCmTransparency&)
{  
}

typedef unsigned int OdGiEdgeStyleMask;
#include "../TD_PackPop.h"

#endif //_OD_GI_H_
