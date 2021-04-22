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

#ifndef __GS_H_INCLUDED_
#define __GS_H_INCLUDED_

#include "../RxObject.h"
#include "../RxIterator.h"
#include "../Gs/GsExport.h"
#include "../DbBaseSubentId.h"
#include "../DbObjectId.h"

class OdGiDrawable;
class GcGsGraphicsKernel;
class GcGsRenderProgressMonitor;
class GcGsRenderInterrupter;
/** \details
  This template class is a specialization of the OdSmartPtr class for OdGiDrawable object pointers. 
*/
typedef OdSmartPtr<OdGiDrawable> OdGiDrawablePtr;

class OdGeMatrix3d;
class OdGePoint3d;
class OdGeVector3d;
class OdGePoint2d;
class OdGiEdgeData;
class OdGiFaceData;
class OdGiVertexData;
struct OdGiClipBoundary;
class OdGiAbstractClipBoundary;
class OdDbStub;
class OdGeExtents3d;
class OdGiVisualStyle;

#include "../TD_PackPush.h"

#include "../OdPlatform.h"
#include "../RxModule.h"
#include "../IntArray.h"
#include "../Gs/GsDCPointArray.h"
#include "../Ge/GePoint2dArray.h"

class OdGsSelectionReactor;

class OdGsView;

/** \details
  This template class is a specialization of the OdSmartPtr class for OdGsView object pointers. 
*/
typedef OdSmartPtr<OdGsView> OdGsViewPtr;

class OdGsModel;

/** \details
  This template class is a specialization of the OdSmartPtr class for OdGsModel object pointers. 
*/
typedef OdSmartPtr<OdGsModel> OdGsModelPtr;

/** \details
  This template class is a specialization of the OdArray class for OdGsModel object pointers.
*/
typedef OdArray<OdGsModel*, OdMemoryAllocator<OdGsModel*> > OdGsModelArray;

class OdGsDevice;

/** \details
  This template class is a specialization of the OdSmartPtr class for OdGsDevice object pointers. 
*/
typedef OdSmartPtr<OdGsDevice> OdGsDevicePtr;

class OdRxDictionary;

/** \details
  This template class is a specialization of the OdSmartPtr class for OdRxDictionary object pointers. 
*/
typedef OdSmartPtr<OdRxDictionary> OdRxDictionaryPtr;

class OdGsReactor;

/** \details
  This template class is a specialization of the OdSmartPtr class for OdGsReactor object pointers. 
*/
typedef OdSmartPtr<OdGsReactor> OdGsReactorPtr;

class OdGiRasterImage;

/** \details
  This template class is a specialization of the OdSmartPtr class for OdGiRasterImage object pointers. 
*/
typedef OdSmartPtr<OdGiRasterImage> OdGiRasterImagePtr;

class OdGsUpdateManager;
/** \details
  This template class is a specialization of the OdSmartPtr class for OdGsUpdateManager object pointers. 
*/
typedef OdSmartPtr<OdGsUpdateManager> OdGsUpdateManagerPtr;

#include "GsDefs.h"

class OdGiContext;
struct OdGsClientViewInfo;
class OdGsFiler;

class OdGsCollisionDetectionReactor;
class OdGsCollisionDetectionContext;
class OdGiPathNode;
class OdGiContextualAttributes;

#include "../Gi/GiContextualColors.h"

namespace Otil
{
  class Image;
};

namespace GS
{
  typedef enum
  {
    kSuccess = 0,
    kOutOfRange,
    kInvalidInput
  } ErrorStatus;

  typedef enum
  {
    kScreenDevice = 0,
    kOffScreenDevice,
    kSelectionDevice
  } DeviceType;

  typedef enum {
    kHighlightDashed = 0, // 默认高亮线型
    kHighlightThicken = 1, // 加厚(两侧)
    kHighlightDashedAndThicken = 2, // 中间高亮两侧加厚 (以上两个是热点提示用到)
    kHighlightCustom = 3, // 自定义 (图纸空间的中间虚线 动态输入中点线 等等)
    kHighlightDim = 4, // 
    kHighlightThickDim = 5, // (以上两个是2012 新特性 具体功能未知)
    kHighlightGlow = 6,
    kHighlightTransparency = 99
  }HighlightStyle;

  typedef enum
  {
    eSync = 0,
    eAsync = 1,
  }SyncBehavior;

  typedef enum
  {
    kTopDown = 0,
    kBottomUp = 1
  }ImageOrientation;

  typedef enum
  {
    kRGBA = 0,
    kBGRA = 1
  }ImageDataFormat;

  // 参考 OdGsView::RenderMode

  typedef enum
  {
    kWCS = 0,
    kOCS,     // Object, or Entity, or Model
    kECS,     // Eye (View)
    kDCS,     // Display (Projection)
    kUCS      // User
  } CoordnateSystem;

  typedef enum
  {
    kNotCare = 0, // use last
    kDraw,
    kUndraw,
    kXOR,
    kHighlight,
    kXORHighlight,
    kXORFill,
  } DrawMode;

  typedef enum
  {
    kModelSpace = 0,
    kPaperSpace
  } SpaceType;
};

/** \details
    This class is the abstract base class for classes that implement Viewport objects in GUI display windows.

    \remarks
    Each Viewport objects consists of a collection of objects to be viewed, and camera parameters that define the view.
    
    Corresponding C++ library: TD_Gs
    <group OdGs_Classes> 
    \sa
    <link tv_working_with_base_classes_view, Working with Visualize Graphical Views>
    \sa
    <link gs_OdGsView, Working with Views>
*/
class FIRSTDLL_EXPORT OdGsView : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdGsView);
  
  /** \details
    Render modes for the view.
  */
  enum RenderMode
  {
    kBoundingBox                  = -1,     // Bounding box. For internal use only.
    k2DOptimized                  = 0,      // Standard *display*. Optimized for 2D.
    kWireframe                    = 1,      // Standard *display*. Uses 3D pipeline.
    kHiddenLine                   = 2,      // Wireframe *display*. Hidden lines removed.
    kFlatShaded                   = 3,      // Faceted *display*. One *color* per face.
    kGouraudShaded                = 4,      // Smooth shaded *display*. Colors interpolated between *vertices*.
    kFlatShadedWithWireframe      = 5,      // Faceted *display* with wireframe overlay.
    kGouraudShadedWithWireframe   = 6,      // Smooth shaded *display* with wireframe overlay.
    kNone
  };

  enum ModelCloneOption
  {
    kCloneNoModels,
    kCloneMainPersistentModel,
    kCloneAllModels
  };
  enum EnableIRResult
  {
    kSuccess,
    kOutOfMemory
  };
  /** \details
    Projection types.
  */
  enum Projection
  {
    kParallel     = 0, // Orthogonal projection.
    kPerspective  = 1  // Perspective projection.
  };

  /** \details
    Selection modes.
  */
  enum SelectionMode
  {
    kWindow       = 0, // Selection by two points (represents rectangle). Select only objects which is entirely inside selection area.
    kCrossing     = 1, // Selection by two points (represents rectangle). Select objects which is entirely inside or intersects selection area.
    kFence        = 2, // Selection by two or more points (represents polyline). Select object which is intersects selection polyline.
    kWPoly        = 3, // Selection by three or more points (represents polygon). Select only objects which is entirely inside selection area.
    kCPoly        = 4, // Selection by three or more points (represents polygon). Select objects which is entirely inside or intersects selection area.

    kPoint        = 16 // Same as kCrossing, but returns only single selected object: top for 3D render modes or first for 2D render mode.
  };

  /** \details
    Default lighting modes.
  */
  enum DefaultLightingType
  {
    kOneLight = 0, // Single front light.
    kTwoLights,    // Front and back lights.
    kBackLight     // Single back light.
  };

  /** \details
    View update flags.
  */
  enum ViewUpdateFlags
  {
    kCameraChanged = 1
  };

  /** \details
    Returns the GsDevice object associated with this Viewport object.
    \sa
    <link tv_working_with_base_classes_device, Working with Visualize Graphics Devices>
  */
  virtual OdGsDevice* getDevice() const = 0;

  OdGsDevice* device() const
  {
    return getDevice();
  }
  /** \details
    Returns the GiContext object associated with this Viewport object.
  */
  virtual OdGiContext* userGiContext() const { return NULL; }

  /** \details
    Sets the User Context object associated with this Viewport object.
    \param pUserGiContext [in]  Pointer to the User Context.
  */
  virtual void setUserGiContext(OdGiContext* pUserGiContext) {}

  /** \details
    Returns the scale factor for displaying Lineweights in this Viewport object.
    \sa
    <link tv_working_with_attributes_lineweights, Working with Lineweights>
  */
  virtual double lineweightToDcScale() const { return 1.0; }
  /** \details
    Sets the scale factor for displaying Lineweights in this Viewport object.
    \param scale [in]  Scale factor.
    \sa
    <link tv_working_with_attributes_lineweights, Working with Lineweights>
  */
  virtual void setLineweightToDcScale(double scale) {}

  /** \details
    Sets the lineweights for this Viewport object.
    \param numLineweights [in]  Number of Lineweights.
    \param lineweights [in]  Array of Lineweights.
    \sa
    <link tv_working_with_attributes_lineweights, Working with Lineweights>
  */
  virtual void setLineweightEnum(int numLineweights, const OdUInt8* lineweights) {}

  /** \details
    Sets the size and position of this Viewport object.
    
    \param lowerLeft [in]  Lower-left corner in nomalized device coordinates [0.0 .. 1.0].
    \param upperRight [in]  Upper-right corner in nomalized device coordinates [0.0 .. 1.0].   
    \remarks
    (0,0) is the lower-left corner of the owning Device object. Coordinates increase upward and to the right.
    The View object can be partly or completely off screen.    
  */
  virtual void setViewport(const OdGePoint2d& lowerLeft, const OdGePoint2d& upperRight) = 0;
  
  /** \details
    Sets the size and position of this Viewport object.
    
    \param screenRect [in]  Screen rectangle in device coordinates (pixels).    
    \remarks
    (0,0) is the lower-left corner of the owning Device object. Coordinates increase upward and to the right. 
    \remarks
    The View object can be partly or completely off screen.    
  */
  virtual void setViewport(const OdGsDCRect& screenRect) = 0;
  
  /** \details
    Sets the size and position of this Viewport object.
    
    \param screenRect [in]  Screen rectangle in device coordinates (pixels).    
    \remarks
    (0,0) is the lower-left corner of the owning Device object. Coordinates increase upward and to the right.
    The View object can be partly or completely off screen.    
  */
  virtual void setViewport(const OdGsDCRectDouble& screenRect);

  /** \details
    Returns the size and position of this Viewport object.
    \param lowerLeft [out]  Receives the lower-left corner in nomalized device coordinates [0.0 .. 1.0].
    \param upperRight [out]  Receives the upper-right corner in nomalized device coordinates [0.0 .. 1.0].
    
    \remarks
    (0,0) is the lower-left corner of the owning Device object.  Coordinates increase upward and to the right.
    
    \remarks
    The View object may be partly or completely off screen.    
  */
  virtual void getViewport(OdGePoint2d& lowerLeft, OdGePoint2d& upperRight) const = 0;
  
  /** \details
    Returns the size and position of this Viewport object.
    \param screenRect [out]  Receives the screen rectangle in device coordinates (pixels).
    
    \remarks
    (0,0) is the lower-left corner of the owning Device object.  Coordinates increase upward and to the right.
    
    \remarks
    The View object may be partly or completely off screen.    
  */
  virtual void getViewport(OdGsDCRect& screenRect) const = 0;
  
  /** \details
    Returns the size and position of this Viewport object.
    \param screenRect [out]  Receives the screen rectangle in device coordinates (pixels).
    \remarks
    (0,0) is the lower-left corner of the owning Device object.  Coordinates increase upward and to the right.
    The View object may be partly or completely off screen.    
  */
  virtual void getViewport(OdGsDCRectDouble& screenRect) const;

  /** \details
    Defines a polygonal clip region for this Viewport object.
    
    \param numCoutours [in]  Number of polygonal contours.
    \param numVertices [in]  Array of the number of vertices in each polygonal contour.
    \param vertices [in]  Array of device coordinate (pixel) vertices defining the polygonal contours.
  */
  virtual void setViewportClipRegion(int numContours, int const* numVertices, OdGsDCPoint const* vertices) = 0;
  
  /** \details
    Defines a polygonal clip region for this Viewport object.
    
    \param numCoutours [in]  Number of polygonal contours.
    \param numVertices [in]  Array of the number of vertices in each polygonal contour.
    \param vertices [in]  Array of device coordinate (pixel) vertices defining the polygonal contours.
  */
  virtual void setViewportClipRegion(int numContours, int const* numVertices, OdGePoint2d const* vertices) {}

  /** \details
    Returns a polygonal clip region for this Viewport object.
    
    \param counts [out]  Array of the number of vertices in each polygonal contour.
    \param vertices [out]  Array of device coordinate (pixel) vertices defining the polygonal contours.
  */
  virtual void viewportClipRegion(OdIntArray& counts, OdGsDCPointArray& vertices) const {}
  
  /** \details
    Returns a polygonal clip region for this Viewport object.
    
    \param counts [out]  Array of the number of vertices in each polygonal contour.
    \param vertices [out]  Array of device coordinate (pixel) vertices defining the polygonal contours.
  */
  virtual void viewportClipRegion(OdIntArray& counts, OdGePoint2dArray& vertices) const {}

  /** \details
    Removes the polygonal clip region for this Viewport object.
  */
  virtual void removeViewportClipRegion();       

  /** \details
    Defines the 3d clipping for this Viewport object.

    \param pBoundary [in]  3d clipping boundary.
    \param pClipInfo [in]  Optional 3d clipping boundary extended data.
  */
  virtual void setViewport3dClipping(const OdGiClipBoundary* pBoundary, const OdGiAbstractClipBoundary* pClipInfo = NULL);

  /** \details
    Returns the current 3d clipping for this Viewport object.

    \param ppClipInfo [out]  Optional 3d clipping boundary extended data.

    \remarks
    Returns null if 3d clipping boundary doesn't set.
  */
  virtual const OdGiClipBoundary *viewport3dClipping(const OdGiAbstractClipBoundary** ppClipInfo = NULL) const;

  /** \details
    Removes the 3d clipping from this Viewport object.
  */
  void removeViewport3dClipping();

  /** \details
    Sets the color and width of the border for this Viewport object.
    \param color [in]  Border color.
    \param width [in]  Border width in pixels.
  */
  virtual void setViewportBorderProperties(const OdGsColor& color, int width) = 0;
  /** \details
    Returns the color and width of the border for this Viewport object.
    \param color [out]  Receives the border color.
    \param width [out]  Receives the border width in pixels.
  */
  virtual void getViewportBorderProperties(OdGsColor& color, int &width) const = 0;
  
  /** \details
    Controls the border visibility for this Viewport object.
    \param visible [in]  Controls visibility.
  */
  virtual void setViewportBorderVisibility(bool visible) = 0;

  /** \details
    Checks whether viewport border is visible.
    \returns
    true if the border is visible for this Viewport object, false otherwise.
  */
  virtual bool isViewportBorderVisible() const = 0;

  /** \details
    Sets the camera parameters for this Viewport object.
    
    \param position [in]  Camera position.
    \param target [in]  Camera target.
    \param upVector [in]  Camera up vector.
    \param fieldWidth [in]  Projection plane (field) width.
    \param fieldHeight [in]  Projection plane (field) height.
    \param projectionType [in]  Projection type.    
    \remarks
    This method defines the transfomation from WCS coordinates to normalized device coordinates.
    All parameters are in WCS coordinates.
    projectionType must be one of the following:
    
    <table>
    Name           Value
    kParallel      0
    kPerspective   1
    </table>
  */
  virtual void setView(
    const OdGePoint3d& position,
    const OdGePoint3d& target,
    const OdGeVector3d& upVector,
    double fieldWidth,
    double fieldHeight,
    Projection projectionType = kParallel) = 0;

  /** \details
    Returns the WCS camera position for this Viewport object.
  */
  virtual OdGePoint3d position() const = 0;

  /** \details
    Returns the WCS camera target for this Viewport object.
  */
  virtual OdGePoint3d target() const = 0;

  /** \details
    Returns the WCS camera up vector for this Viewport object.
  */
  virtual OdGeVector3d upVector() const = 0;

  /** \details
    Returns the perspective lens length for this Viewport object.
  */
  virtual double lensLength() const { return 0.0; }

  /** \details
    Sets the perspective lens length for this Viewport object.
    \param lensLength [in]  Perspective lens length.
  */
  virtual void setLensLength(double lensLength) {}

  /** \details
    Checks whether the projection type for the viewport object is kPerspective.
    \returns
    true if projection type for the viewport object is kPerspective, false otherwise.
  */
  virtual bool isPerspective() const = 0;

  /** \details
    Returns the WCS projection plane (field) width for this Viewport object.
  */
  virtual double fieldWidth() const = 0;
  /** \details
    Returns the WCS projection plane (field) height for this Viewport object.
  */
  virtual double fieldHeight() const = 0;
  virtual void setViewCenter(const OdGePoint2d &ct) {}

  /** \details
    Controls the front clipping of this Viewport object.
    \param enable [in]  Enable front clipping.
  */
  virtual void setEnableFrontClip(bool enable) = 0;

  /** \details
    Checks whether front clipping is enabled for the viewport object.
    \returns
    true if front clipping is enabled for the viewport object, false otherwise.
  */
  virtual bool isFrontClipped() const = 0;

  /** \details
    Sets the front clip distance from the target of this Viewport object.
    \param frontClip [in]  Front clip distance.
  */
  virtual void setFrontClip(double frontClip) = 0;

  /** \details
    Returns the front clip distance from the target of this Viewport object.
  */
  virtual double frontClip() const = 0;

  /** \details
    Controls the back clipping of this Viewport object.
    \param enable [in]  Enable back clipping.
  */
  virtual void setEnableBackClip(bool enable) = 0;

  /** \details
    Checks whether back clipping is enabled for the viewport object.
    \returns
    true if back clipping is enabled for the viewport object, false otherwise.
  */
  virtual bool isBackClipped() const = 0;

  /** \details
    Sets the back clip distance from the target of this Viewport object.
    \param backClip [in]  Back clip distance.
  */
  virtual void setBackClip(double backClip) = 0;
  /** \details
    Returns the back clip distance from the target of this Viewport object.
  */
  virtual double backClip() const = 0;

  /** \details
      Returns the matrix that transforms world space to view space for this Viewport object.

      \sa
      Coordinate Systems.
  */
  virtual OdGeMatrix3d viewingMatrix() const = 0;

  /** \details
      Returns the matrix that transforms view space to normalized device space for this Viewport object.

      \sa
      Coordinate Systems.
  */
  virtual OdGeMatrix3d projectionMatrix() const = 0;

  /** \details
      Returns the matrix that transforms normalized device space to screen space for this Viewport object.

      \sa
      Coordinate Systems.
  */
  virtual OdGeMatrix3d screenMatrix() const = 0;

  /** \details
      Returns a matrix that transforms coordinates from world space to screen space for this Viewport object. 
      
      \remarks
      This is equivalent to the concatenation of the viewingMatrix, 
      projectionMatrix, and screenMatrix.

      \sa
      Coordinate Systems.
  */
  virtual OdGeMatrix3d worldToDeviceMatrix() const = 0;  

  /** \details
      Returns the matrix that transforms coordinates from model space to screen space for this Viewport object.

      \sa
      Coordinate Systems.
  */
  virtual OdGeMatrix3d objectToDeviceMatrix() const = 0;

  /** \details
    Sets the render mode for this Viewport object.
    
    \param mode [in]  Render mode.
    
    \remarks
    mode must be one of the following:
    
    <table>
    Name                            Value      Description
    kBoundingBox                    -1         Bounding box. For internal use only.
    k2DOptimized                    0          Standard display. Optimized for 2D.
    kWireframe                      1          Standard display. Uses 3D pipeline.
    kHiddenLine                     2          Wireframe display. Hidden lines removed.
    kFlatShaded                     3          Faceted display. One color per face.
    kGouraudShaded                  4          Smooth shaded display. Colors interpolated between vertices.
    kFlatShadedWithWireframe        5          Faceted display with wireframe overlay.
    kGouraudShadedWithWireframe     6          Smooth shaded display with wireframe overlay.
    </table>
  */
  virtual void setMode(RenderMode mode) {}

  /** \details
    Sets the render mode for this Viewport object.
    
    \remarks
    mode must be one of the following:
    
    <table>
    Name                            Value      Description
    kBoundingBox                    -1         Bounding box. For internal use only.
    k2DOptimized                    0          Standard display. Optimized for 2D.
    kWireframe                      1          Standard display. Uses 3D pipeline.
    kHiddenLine                     2          Wireframe display. Hidden lines removed.
    kFlatShaded                     3          Faceted display. One color per face.
    kGouraudShaded                  4          Smooth shaded display. Colors interpolated between vertices.
    kFlatShadedWithWireframe        5          Faceted display with wireframe overlay.
    kGouraudShadedWithWireframe     6          Smooth shaded display with wireframe overlay.
    </table>
  */
  virtual RenderMode mode() const { return kNone; }

  /** \details
    Adds the specified scene graph to this Viewport object.
    
    \param pSceneGraph [in]  Pointer to the root of the scene graph.
    \param pModel [in]  Pointer to the Model object to which all scene graph notifications are to be directed.
    
    \remarks
    This function is intended to be used as follows:
    
    1.  Construct a scene graph of OdGiDrawable objects. 
        Each object draws its children with OdGiGeometry::draw().
    
    2.  With this function, add the root of the scene graph and the 
        OdGsModel that handles notifications to this Viewport object.
  */
  virtual bool add(OdGiDrawable* pSceneGraph, OdGsModel* pModel) = 0;

  /** \details
    Retrieves a quantity of root drawables for this viewport.
  */
  virtual int numRootDrawables() const { return 0; }

  /** \details
    Retrieves a persistent object identifier of the root drawable at the specified index.
    \param i [in]  Index of the drawable to return.
    \param pModelReturn [in]  Index of the drawable to return.
  */
  virtual OdDbStub* rootDrawableIdAt(int i, OdGsModelPtr* pModelReturn = 0) const { return NULL; }

  virtual OdGiDrawablePtr rootDrawableAt(int i, OdGsModelPtr* pModelReturn = 0) const { return OdGiDrawablePtr(); }

  /** \details
    Removes the specified scene graph from this Viewport object.
    
    \param sceneGraph [in]  Pointer to the root of the scene graph.
    \returns
    true if scene graph is successfully erased, false otherwise.
  */
  virtual bool erase(OdGiDrawable* sceneGraph) = 0;
  /** \details
    Removes all scene graphs from this Viewport object.
    
    \param sceneGraph [in]  Root of scene graph.
  */
  virtual void eraseAll() = 0;

  /** \details
    Returns OdGsModel object associated with specified OdGiDrawable object in this Viewport object.

    \param pDrawable [in]  Pointer onto OdGiDrawable object.
  */
  virtual OdGsModel *getModel(OdGiDrawable *pDrawable) const = 0;
  /** \details
    Returns array of OdGsModel objects associated with this Viewport object.
  */
  virtual void getModelList(OdArray<OdGsModel*>& p) const = 0;

   /** \details
    Marks the entire area of this View for refreshing.
   */
  virtual void invalidate() = 0;
  
  /** \details
    Marks for refresh the specified region of this Viewport object.
     
    \param screenRect [in]  Screen rectangle in device coordinates (pixels).
   */
  virtual void invalidate(const OdGsDCRect &screenRect) = 0;

  /** \details
    Checks whether this Viewport shows the correct image.
    \returns
    true if this Viewport object is showing the correct image, false otherwise.

    \remarks
    This implies the follow:
    * No part of GUI area is flagged for refresh.
    * All rasterizations are complete
    * The rendering pipeline has been flushed.
  */
  virtual bool isValid() const = 0;

  /** \details
    Flushes any queued graphics to the display device.
    
    \remarks
    If called while this Viewport object is in the interactive state, this function immediately returns.
  */
  virtual void update() = 0;

  /** \details
    Puts this Viewport object into interactive state.
    
    \param frameRateInHz [in]  Frames/second.
    
    \remarks
    A frame rate of 0.0 specifies the default frame rate.
    \sa
    <link gs_views_interactivity_mode, Working with Interactivity Mode for Views>
  */
  virtual void beginInteractivity(double frameRateInHz) = 0;
  /** \details
    Checks whether this Viewport object is in interactive state.
    \returns
    true if this View is in interactivity mode, false otherwise.
    \sa
    <link gs_views_interactivity_mode, Working with Interactivity Mode for Views>
  */
  virtual bool isInInteractivity() const { return false; }
  /** \details
    Returns interactivity frame rate.
    \sa
    <link gs_views_interactivity_mode, Working with Interactivity Mode for Views>
  */
  virtual double interactivityFrameRate() const { return 1.0; }
  /** \details
    Removes this Viewport object from the interactive state.
    \sa
    <link gs_views_interactivity_mode, Working with Interactivity Mode for Views>
  */
  virtual void endInteractivity() = 0;
  /** \details
    Flushes the graphic pipeline and renders this Viewport object.
    
    \remarks
    This function should be called only during interactivty. 
  */
  virtual void flush() = 0;

  /** \details
    Hides this Viewport object.
  */
  virtual void hide() = 0;

  /** \details
    Un-hides this Viewport object.
  */
  virtual void show() = 0;

  /** \details
    Checks whether the viewport object is not hidden.
    \returns
    true if the wrapped viewport object is visible, false otherwise.
  */
  virtual bool isVisible() = 0;

  /** \details
    Freezes the specified Layer object in this Viewport object.
    \param layerID [in]  Layer to freeze.
    \remarks
    All layers are thawed by default.
    \sa
    <link tv_working_with_attributes_layers, Working with Layers>
  */
  virtual void freezeLayer(OdLongPtr layerID) = 0;

  /** \details
    Thaws the specified Layer object in this Viewport object.
    \param layerID [in]  Layer to thaw.
    \remarks
    All layers are thawed by default.
    \sa
    <link tv_working_with_attributes_layers, Working with Layers>
  */
  virtual void thawLayer(OdLongPtr layerID) = 0;

  /** \details
    Thaws all Layer objects in this Viewport object.
    \remarks
    All layers are thawed by default.
    \sa
    <link tv_working_with_attributes_layers, Working with Layers>
  */
  virtual void clearFrozenLayers() = 0;

  /** \details
    Marks for regeneration all subViewportDraw() geometry for this Viewport object.
  */
  virtual void invalidateCachedViewportGeometry() = 0;

  /** \details
    Runs selection procedure inside this Viewport object.

    \param pts [in]  Selection points in device coordinate space.
    \param nPoints [in]  Count of selection points.
    \param pReactor [in]  Selection callback pointer.
    \param mode [in]  Selection mode.
    \sa
    <link tv_working_with_features_selections, Working with Selections>
  */
  virtual void select(const OdGsDCPoint* pts, int nPoints,
    OdGsSelectionReactor* pReactor,
    OdGsView::SelectionMode mode = OdGsView::kCrossing) {}

  /** \details
    Translates the camera position and target by the specified Camera Coordinate dolly amount.
     
    \param dollyVector [in]  Camera Coordinate dolly vector. 
    \remarks
    Camera Coordinates are relative to the view of a target from a camera. 
    * The Y-axis is along up vector. 
    * The Z-axis is along the vector from camera position to the target. 
    * The X-axis is the cross product Y-axis x Z-axis 
  */
  virtual void dolly(const OdGeVector3d& dollyVector) = 0;
  
  /** \details
    Translates the camera position and target by the specified Camera Coordinate dolly amount.
    
    \param xDolly [in]  Camera Coordinate X dolly amount.
    \param yDolly [in]  Camera Coordinate Y dolly amount.
    \param zDolly [in]  Camera Coordinate Z dolly amount.
    \remarks
    Camera Coordinates are relative to the view of a target from a camera.   
    * The Y-axis is along up vector. 
    * The Z-axis is along the vector from camera position to the target. 
    * The X-axis is the cross product Y-axis x Z-axis 
  */
  virtual void dolly(double xDolly, double yDolly, double zDolly) = 0;

  /** \details
    Rotates the camera by the specified amount about the eye vector.
     
    \param rollAngle [in]  Camera CCW roll angle.
    \remarks
    Positive angles rotate the camera counterclockwise about the eye vector
    when viewed from the camera position to the target. This corresponds
    to a clockwise rotation of the up vector.
    Camera Coordinates are relative to the view of a target from a camera. 
    * The Y-axis is along up-vector. 
    * The Z-axis (eye vector) is along the vector from camera position to the target. 
    * The X-axis is the cross product Y-axis x Z-axis.
    All angles are expressed in radians.
  */
    virtual void roll(double rollAngle) = 0;

  /** \details
    Orbits the camera about the target by the specified amounts.
     
    \param xOrbit [in]  X-axis Orbit.
    \param yOrbit [in]  Y-axis Orbit.
    \remarks
    the camera moves on the surface a sphere whose center the camera target and whose
    radius is the distance from the camera position to its target 
    * The camera is first rotated about an axis parallel to the X-axis and passing through the target.  
    * The camera is next rotated about an axis parallel to the Y-axis and passing through the target.
    Camera Coordinates are relative to the view of a target from a camera.  
    * The Y-axis is along up vector. 
    * The Z-axis is along the vector from camera position to the target. 
    * The X-axis is the cross product Y-axis x Z-axis 
    All angles are expressed in radians.
  */
    virtual void orbit(double xOrbit, double yOrbit) = 0;

  /** \details
    Scales the focal length of the camera by the specified amount.
     
    \param zoomFactor [in]  Zoom factor.
  */
    virtual void zoom(double zoomFactor) = 0;

  /** \details
    Rotates the target about the camera the specified amounts.
     
    \param xPan [in]  X-axis pan.
    \param yPan [in]  Y-axis pan.   
    \remarks
    The target moves on the surface a sphere whose center the camera position and whose
    radius is the distance from the camera position to its target.
    * The target is first rotated about an axis parallel to the X-axis and passing through the camera.  
    * The target is next rotated about an axis parallel to the Y-axis and passing through the camera.  
    Camera Coordinates are relative to the view of a target from a camera. 
    * The Y-axis is along up vector. 
    * The Z-axis is along the vector from camera position to the target. 
    * The X-axis is the cross product Y-axis x Z-axis 
    All angles are expressed in radians.
  */
    virtual void pan(double xPan, double yPan) = 0;

  /** \details
    Scales the camera to completely include specified WCS box inside view frustum.

    \param minPt [in]  minimal WCS box point.
    \param maxPt [in]  maximal WCS box point.
  */
  virtual void zoomExtents(const OdGePoint3d &minPt, const OdGePoint3d &maxPt) = 0;

  /** \details
    Scales the camera to completely include specified screen area.

    \param lowerLeft [in]  Lower-left corner in nomalized device coordinates [0.0 .. 1.0].
    \param upperRight [in]  Upper-right corner in nomalized device coordinates [0.0 .. 1.0].
  */
  virtual void zoomWindow(const OdGePoint2d &lowerLeft, const OdGePoint2d &upperRight) = 0;
  
  virtual void zoomScreenWindow(const OdGePoint2d& upLeft, const OdGePoint2d& bottomRight){}

  /** \details
    Checks whether specified point is visible inside current view frustum.

    \param pt [in]  WCS point for check.
    \returns
    true if the specified point is visible in the wrapped viewport, false otherwise.
  */
  virtual bool pointInView(const OdGePoint3d &pt) = 0;

  /** \details
    Checks whether specified WCS box is visible completely or partially inside current view frustum.

    \param minPt [in]  minimal WCS box point.
    \param maxPt [in]  maximal WCS box point.
    \returns
    true if the specified extents box is visible in the current viewport frustum of the wrapped view, false otherwise.
  */
  virtual bool extentsInView(const OdGePoint3d &minPt, const OdGePoint3d &maxPt) = 0;

  /** \details
    Clones this view object.

    \param cloneViewParameters [in]  If and only if true, view parameters will be cloned.
    \param cloneGeometry [in]  If and only if true, geometry will be cloned.
    \returns
    Returns a SmartPointer to the newly created object.
  */
  virtual OdGsView* clone(bool bCloneViewParameters = true, bool bCloneGeometry = false) = 0;

  /** \details
    Sets the view parameters of the specified OdGsView object to that of this Viewport object.
    \param pView [out]  Receives the view parameters.
  */
  virtual void viewParameters(OdGsView* pView) const {}

  /** \details
    Checks whether any view parameters have exceeded their boundaries since the last
    call to this function.
    \returns 
    true if any view parameters have exceeded their boundaries since the last call to this function, false otherwise.
    \remarks
    The following calls are monitored:
    
    * dolly()
    * orbit()
    * pan() 
    * roll()
    * setBackClip()
    * setFrontClip()
    * setView()
    * zoom()
  */
  virtual bool exceededBounds() = 0;

  /** \details
    Controls stereo viewing for this Viewport object.
    
    \param enable [in]  Controls stereo viewing.
  */
  virtual void enableStereo(bool enabled) = 0;

  /** \details
    Checks whether stereo viewing is enabled for this Viewport object.
    \returns
    true if and only if stereo viewing is enabled for this Viewport object, false otherwise.
  */
  virtual bool isStereoEnabled() const = 0;

  /** \details
    Sets the stereo parameters for this Viewport Object.
    \param magnitude [in]  View separation [0.0 .. 2.0].
    \param parallax [in]  Adjusts the plane of zero parallax [0.0 .. 2.0].
    
    \remarks
    magnitude controls view eye separation, and hence the stereo effect.
    * A magnitude of 1.0 is the default value.
    * A magnitude of 0.0 produces no stereo effect.
    * A magnitude of 2.0 produces a double stereo effect.
    parallax adjusts the zero parallax plane.
    * A parallax of 1.0 is the default value. An object centered at the target will be half-in and half-out of the screen.
    * A parallax of 0.0 moves the object into the screen.
    * A parallax of 2.0 move the object out of the screen.
  */
   virtual void setStereoParameters(double magnitude, double parallax) = 0;

  /** \details
    Returns the stereo parameters for this Viewport Object.
    
    \param magnitude [out]  Receives the view separation [0.0 .. 2.0].
    \param parallax [out]  Receives the plane of zero parallax adjustment [0.0 .. 2.0].
    \remarks
    magnitude controls view eye separation, and hence the stereo effect.
    * A magnitude of 1.0 is the default value.
    * A magnitude of 0.0 produces no stereo effect.
    * A magnitude of 2.0 produces a double stereo effect.
    parallax adjusts the zero parallax plane.
    * A parallax of 1.0 is the default value. An object centered at the target will be half-in and half-out of the screen.
    * A parallax of 0.0 moves the object into the screen.
    * A parallax of 2.0 move the object out of the screen.
  */
   virtual void getStereoParameters(double& magnitude, double& parallax) const = 0;

  /** \details
    Returns an iterator to traverse the lights attached to this Viewport object.
    \param pLightsIterator [in]  Pointer to the lights iterator.
  */
   virtual void initLights(OdRxIterator* pLightsIterator) {}

  /** \details
    Sets a multiplier that is used to scale all linetypes in this Viewport object.
    
    \param linetypeScaleMultiplier [in]  Linetype scale multiplier.
  */
   virtual void setLinetypeScaleMultiplier(double linetypeScaleMultiplier) {}

  /** \details
    Returns current linetype scale multiplier value.
    \sa
    <exref target="https://docs.opendesign.com/td/db_linetype.html">Working with Linetypes</exref>
  */
   virtual double linetypeScaleMultiplier() const { return 1.0; }

  /** \details
    Sets a multiplier that could be used as an alternate scale factor for linetypes in this Viewport object.
    
    \param linetypeAlternateScaleMultiplier [in]  Alternate linetype scale multiplier.
    \sa
    <exref target="https://docs.opendesign.com/td/db_linetype.html">Working with Linetypes</exref>
  */
   virtual void setAlternateLinetypeScaleMultiplier(double linetypeAlternateScaleMultiplier) {}

  /** \details
    Returns current alternate linetype scale multiplier value.
    \sa
    <exref target="https://docs.opendesign.com/td/db_linetype.html">Working with Linetypes</exref>
  */
   virtual double linetypeAlternateScaleMultiplier() const { return 1.0; }

  /** \details
    Returns the ClientViewInfo for this Viewport object.
    
    \param clientViewInfo [out]  Receives the ClientViewInfo.
  */
  virtual const OdGsClientViewInfo& getClientViewInfo() const = 0;  

  /** \details
    Clear color for this view.
  */
  enum ClearColor
  {
    kTransparent,         // Transparent color
    kDeviceBackground,    // Color from device background
    kPaletteBackground    // Palette background color
  };

  /** \details
    Sets the clear color for this view

    \param color [in]  The clear color.
  */
  virtual void setClearColor(ClearColor color) {}

  /** \details
    Checks whether the specified point is inside viewport area.

    \param screenPoint [in]  Check point in device coordinate space.
    \returns
    true if the passed point is inside the viewport, false otherwise.
  */
  virtual bool isPointInViewport(const OdInt32 x, const OdInt32 y) = 0;
  /** \details
    Returns the display pixel density at the specified point for this Viewport object.

    \param point [in]  WCS center of the unit square.
    \param pixelDensity [out]  Receives the pixel density.
    \param bUsePerspective [in]  Enable perspective inclusion into pixel density calculation.
    \remarks
    Pixel density is measured in pixels per WCS unit.
    This function can be used to determine if the geometry generated for an object will 
    be smaller than the size of a pixel.
  */
  virtual void getNumPixelsInUnitSquare(const OdGePoint3d& point,
                                        OdGePoint2d& pixelDensity, bool bUsePerspective = true) const = 0;

  /** \details
    Sets background object for this view.

    \param backgroundId [in]  New background object ID.
    \sa
    <link tv_working_with_attributes_view_backgrounds, Working with View Backgrounds>
  */
  virtual void setBackground(const OdDbObjectId backgroundId) = 0;
  /** \details
    Returns current background object ID for this view.
    \sa
    <link tv_working_with_attributes_view_backgrounds, Working with View Backgrounds>
  */
  virtual OdDbObjectId background() const = 0;

  /** \details
    Sets visual style object for this view.

    \param visualStyleId [in]  New visual style object ID.
    \sa
    <link tv_working_with_attributes_visual_styles, Working with Visual Styles>
  */
  virtual void setVisualStyle(const OdDbObjectId visualStyleId) = 0;
  /** \details
    Returns current visual style object ID for this view.
    \sa
    <link tv_working_with_attributes_visual_styles, Working with Visual Styles>
  */
  virtual OdDbObjectId visualStyle() const = 0;
  /** \details
    Sets visual style for this view.

    \param visualStyle [in]  New visual style data.
    \sa
    <link tv_working_with_attributes_visual_styles, Working with Visual Styles>
  */
  virtual void setVisualStyle(const OdGiVisualStyle &visualStyle) = 0;
  /** \details
    Returns current visual style for this view.

    \param visualStyle [out]  OdGiVisualStyle structure to fill by current visual style data.

    \returns
    Returns true if and only if OdGiVisualStyle structure is filled by visual style data.
    \sa
    <link tv_working_with_attributes_visual_styles, Working with Visual Styles>
  */
  virtual bool visualStyle(OdGiVisualStyle &visualStyle) const = 0;

  /** \details
    Enables default lighting for this view.

    \param bEnable [in]  New default lighting state.
    \param lightType [in]  New default lighting type.
    \sa
    <link tv_working_with_lights, Working with Lights>
  */
  virtual void enableDefaultLighting(bool bEnable, DefaultLightingType lightType = kTwoLights) = 0;

  /** \details
    Returns image of current view buffer.

    \param pImage [out]  Pointer for image to return.
    \param region [in]  Rectangle specifies region to return.
    \remarks
    Implementation can throw eNotImplementedYet exception if current vectorization module doesn't support snap shots.
  */
  virtual void getSnapShot(OdGiRasterImagePtr &pImage, const OdGsDCRect &region) {}

  /** \details
    Runs collision detection procedure inside this Viewport object.

    \param pInputList [in]  Pointer to the list of objects to check
    \param nInputListSize [in]  Size of the list of objects to check
    \param pCollisionWithList [in]  Pointer to the list of possible colliding objects
    \param nCollisionWithListSize [in]  Size of the list of possible colliding objects
    \param pCtx [in] Pointer to the OdGsCollisionDetectionContext that provide additional Collision Detection options
    \remarks
    If pCollisionWithList is NULL pInputList will be checked with all other drawables.
    If pCollisionWithList is not a NULL pInputList will be checked with pCollisionWithList only.
    If pInputList is NULL all drawables will be checked on collisions with each other.
    \sa
    <link gs_collision_detection, Working with Collision Detection>
  */
  virtual void collide(OdGiPathNode const*const* pInputList, OdUInt32 nInputListSize, OdGsCollisionDetectionReactor* pReactor,
    OdGiPathNode const*const* pCollisionWithList = NULL, OdUInt32 nCollisionWithListSize = 0,
    const OdGsCollisionDetectionContext* pCtx = NULL) {}

  /** \details
    Enable or disable anti-aliasing in current Viewport object.

    \param nMode [in]  Anti-aliasing mode (set as 3 by default). Set as 0 to disable anti-aliasing.
  */
  virtual void enableAntiAliasing(OdUInt32 nMode) {}
  /** \details
    Returns anti-aliasing mode for current Viewport object.
  */
  virtual OdUInt32 antiAliasingMode() const { return 3; }

  virtual GcGsGraphicsKernel &graphicsKernel(void);

  virtual void update(GS::SyncBehavior sync);

  virtual bool isInteractive(void) const ;

  virtual void setMaximumUpgrade(int step);
  virtual int maximumUpgrade(void);
  virtual void setMinimumDegrade(int step);
  virtual int minimumDegrade(void);

  virtual void invalidateCachedViewportGeometry(OdGiDrawable* pDrawable);

  virtual OdGsView* clone(bool bCloneViewParameters, ModelCloneOption cloneOption);

  virtual void getSnapShot(Otil::Image* pOutput, const OdGsDCPoint& offset);

  virtual bool renderToImage(Otil::Image* pOutput, 
    OdGiDrawable* pSettings,
    GcGsRenderProgressMonitor* pProgressMonitor,
    const OdGsDCRect & rectScreen,
    bool bReuseScene = false);

  virtual Otil::Image* createSnapshot(const OdGsDCPoint&     offset,
    const OdGsDCRect&      imageDim,
    GS::ImageDataFormat    format,
    GS::ImageOrientation   orientation,
    bool                   bOnlyCaptureRenderedImage = false);


  virtual EnableIRResult beginInteractiveRender(GcGsRenderProgressMonitor* pProgressMonitor);
  virtual void endInteractiveRender(void);
  virtual bool isRendering(void) const;

  virtual void beginFastInteractivity(void);
  virtual bool endFastInteractivity(void);
  virtual bool isFastInteractivity(void);
};
class OdGiPathNode;
class OdDbFullSubentPath;

/** \details

    Corresponding C++ library: TD_Gs

    <group OdGs_Classes>
*/
class FIRSTDLL_EXPORT ODRX_ABSTRACT OdGsCache : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdGsCache);

  /** \details
    Returns pointer to the Model object associated with this Cache object.
  */
  virtual OdGsModel* model() const { return NULL; }

  /** \details
    Reset pointer to the underlying GiDrawable object associated with this Cache object.
  */
  virtual void setDrawableNull() {}

  /** \details
    Returns the extents of the underlying GiDrawable object(s) associated with this Cache object.

    \param extents [out]  Receives the extents.

    \returns
    Returns true if and only if the GiDrawable object(s) have extents.
  */
  virtual bool extents(OdGeExtents3d& extents) const { return false; }

  virtual OdGiDrawable* drawable(void) const { return NULL; }
};

typedef OdGiDrawablePtr(*OdGiOpenDrawableFn)(OdDbStub* id);

class OdGsModelReactor;

/** \details
    The class represents collections of drawable objects in the ODA Platform framework.

    Corresponding C++ library: TD_Gs

    <group OdGs_Classes>
*/
class FIRSTDLL_EXPORT ODRX_ABSTRACT OdGsModel : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdGsModel);

  /** \details
    Specifies the function called for drawable object open by this Model object.

    \param openDrawableFn [in]  Function to be called.
  */
  virtual void setOpenDrawableFn(OdGiOpenDrawableFn openDrawableFn) {}

  /** \details
    Notification function called whenever a drawable object is added to this Model object.

    \param pAdded [in]  Pointer to the added Drawable object.
    \param pParent [in]  Pointer to the parent of the added Drawable object.
  */
  virtual void onAdded(OdGiDrawable* pAdded, OdGiDrawable* pParent) = 0;

  /** \details
    Notification function called whenever a drawable object is added to this Model object.

    \param pAdded [in]  Pointer to the added Drawable object.
    \param parentID [in]  Object ID of the parent of the added Drawable object.
  */
  virtual void onAdded(OdGiDrawable* pAdded, OdIntDbId parentID) = 0;

  /** \details
    Notification function called whenever a drawable object is modified in this Model object.

    \param pModified [in]  Pointer to the modified Drawable object.
    \param pParent [in]  Pointer to the parent of the modified Drawable object.
  */
  virtual void onModified(OdGiDrawable* pModified, OdGiDrawable* pParent) = 0;

  /** \details
    Notification function called whenever a drawable object is modified in this Model object.

    \param pModified [in]  Pointer to the modified Drawable object.
    \param parentID [in]  Object ID of the parent of the modified Drawable object.
  */
  virtual void onModified(OdGiDrawable* pModified, OdIntDbId parentID) = 0;

  /** \details
    Function to call directly whenever a drawable object's graphics has been modified
    but not the drawable itself

    \param pModified [in]  Pointer to the Drawable object with modified graphics
    \param parentID [in]   Object ID of the parent of the modified Drawable object.
  */
  virtual void onModifiedGraphics(const OdGiDrawable* pModified, OdDbStub* parentID) {}

  /** \details
    Notification function called whenever a drawable object is erased from this Model object.

    \param pErased [in]  Pointer to the erased Drawable object.
    \param pParent [in]  Pointer to the parent of the erased Drawable object.
  */
  virtual void onErased(OdGiDrawable* pErased, OdGiDrawable* pParent) = 0;

  /** \details
    Notification function called whenever a drawable object is erased from this Model object.

    \param pErased [in]  Pointer to the erased Drawable object.
    \param parentID [in]  Object ID of the parent of the erased Drawable object.
  */
  virtual void onErased(OdGiDrawable* pErased, OdIntDbId parentID) = 0;

  /** \details
    Notification function called whenever a drawable object is unerased in this Model object.

    \param pUnerased [in]  Pointer to the unerased Drawable object.
    \param pParent [in]  Pointer to the parent of the unerased Drawable object.
  */
  virtual void onUnerased(OdGiDrawable* pUnerased, OdGiDrawable* pParent);

  /** \details
    Notification function called whenever a drawable object is unerased in this Model object.

    \param pUnerased [in]  Pointer to the unerased Drawable object.
    \param parentID [in]  Object ID of the parent of the unerased Drawable object.
  */
  virtual void onUnerased(OdGiDrawable* pUnerased, OdIntDbId parentID);

  // Invalidation Hint

  /** \details
    The InvalidationHint enumeration specifies how the Graphic System should process
    the invalidate() method.
  */
  enum InvalidationHint
  {
    kInvalidateNone,
    kInvalidateIsolines,
    kInvalidateViewportCache,
    kInvalidateAll,
    kInvalidateAllStatic,
    kInvalidateFacets,
    kInvalidateFills,
    kInvalidateLinetypes,
    kInvalidateMaterials,
    kInvalidateLayers,
    kInvalidateXrefs,
    kInvalidateRasterImages,
    kInvalidateAttributes,
    kInvalidateUnderlayFrame,
    kInvalidateLtScale,
    kInvalidateTransform,
    kInvalidateTransparencies,
    kInvalidateDrawableByView
  };

  enum OrderActionType
  {
    kMoveBelow,
    kMoveAbove,
    kSwapOrder,
  };

  /** \details
    Invalidates the specified cached data contained in this Model object.

    \param hint [in]  Invalidation hint.

    \remarks
    Hint must be one of the following:

    <table>
    Name                        Value
    kInvalidateIsolines         0
    kInvalidateViewportCache    1
    kInvalidateAll              2
    kInvalidateMaterials        3
    kInvalidateLinetypes        4
    </table>
  */
  virtual void invalidate(InvalidationHint hint) = 0;

  /** \details
    Invalidates cached data associated with the specified View object.

    \param pView [in]  Pointer to the OdGsView object for which data is to be invalidated.
  */
  virtual void invalidate(OdGsView* pView) {}

  /** \details
    Invalidates cached data that visible on the device.

    \param pView [in]  Pointer to the OdGsDevice object for which data is to be invalidated.
  */
  virtual void invalidateVisible(OdGsDevice* pDevice) {}

  /** \details
    Transforms this Model object by applying the specified transformation matrix to the model contents.

    \param OdGeMatrix3d [in]  Transformation matrix.
  */
  virtual void setTransform(const OdGeMatrix3d&) = 0;

  /** \details
    Obtains the current transformation matrix of this Model object.
  */
  virtual OdGeMatrix3d transform() const = 0;

  /** \details
    Highlights the specified entity in this Model object.
    
    \param path [in]  Path to the entity for highlighting.
    \param bDoIt [in]  Flag that indicates whether highlighting is enabled (true value) or disabled (false value).
    \param nStyle [in]  Selection style index.
    \param pView [in]  Pointer to the view where the specified entity should be highlighted.
  */
  virtual void highlight(const OdGiPathNode& path, bool bDoIt = true, OdUInt32 nStyle = 0, const OdGsView* pView = NULL){}

  /** \details
    Highlights the specified subentities of entity in this Model object.

    \param path [in]  Path to the entity
    \param pMarkers [in] Array of subentity markers
    \param nMarkers [in] Count of subentity markers
    \param bDoIt [in]  Flag that indicates whether highlighting is enabled (true value) or disabled (false value).
    \param pView [in]  Pointer to the view where the specified entity should be highlighted.
  */
  virtual void highlight(const OdGiPathNode& path, const OdGsMarker* pMarkers, OdUInt32 nMarkers, bool bDoIt = true,
                         OdUInt32 nStyle = 0, const OdGsView* pView = NULL) {}

  virtual void highlight(OdGsCache* pGsNode, const OdGiPathNode& path, bool bDoIt, const OdGsView* pView = 0) {}
  virtual bool highlight(const OdDbFullSubentPath& pPath, bool bDoIt = true, const OdGsView* pView = 0) { return false; }

  /** \details
    Hides the specified entity in this Model object.

    \param path [in]  Path to the entity for hide.
    \param bDoIt [in]  Flag that indicates whether hiding is enabled (true value) or disabled (false value).
    \param bSelectHidden [in] Flag that indicates whether hidden object is selectable or not.
    \param pView [in]  Pointer to the view where the specified entity should be hidden.
  */
  virtual void hide(const OdGiPathNode& path, bool bDoIt = true, bool bSelectHidden = false, const OdGsView* pView = NULL){}

  /** \details
    Hides the specified subentities of entity in this Model object..

    \param path [in]  Path to the entity for hide.
    \param pMarkers [in] Array of subentity markers.
    \param nMarkers [in] Count of subentity markers.
    \param bDoIt [in]  Flag that indicates whether hiding is enabled (true value) or disabled (false value).
    \param bSelectHidden [in] Flag that indicates whether hidden object is selectable or not.
    \param pView [in]  Pointer to the view where the specified entity should be hidden.
  */
  virtual void hide(const OdGiPathNode& path, const OdGsMarker* pMarkers, OdUInt32 nMarkers, bool bDoIt = true,
                    bool bSelectHidden = false, const OdGsView* pView = 0) {}

  /** \details
    Specifies how the model's geometry should be rendered by the Graphic System.
  */
  enum RenderType
  {
    kMinRenderType = -3, // Number of RenderType's in negative values range
    kUserBg1 = -3, // User-defined background rendering type without Z-buffer
    kUserBg2 = -2, // User-defined background rendering type with own Z-buffer
    kUserBg3 = -1, // User-defined background rendering type with Z-buffer
    kMain = 0, // Use main Z-buffer
    kSprite,             // Use alternate Z-buffer (for sprites)
    kDirect,             // Render on device directly
    kHighlight,          // Render on device directly (skipping frame buffer and Z-buffer)
    kHighlightSelection, // Render on device directly using highlighting style (skipping frame buffer and Z-buffer)
    kDirectTopmost,      // Render on top of all other render types without Z-buffer
    kContrast,           // Render with contrast style
    kCount,              // Number of primary predefined RenderType's
    kUserFg1 = kCount,   // User-defined foreground rendering type with Z-buffer
    kUserFg2,            // User-defined foreground rendering type with own Z-buffer
    kUserFg3,            // Second user-defined foreground rendering type without Z-buffer
    kMaxRenderType,      // Number of RenderType's in positive values range
    kNumRenderTypes = kMaxRenderType - kMinRenderType // Exact number of RenderType's including predefined and user-defined RenderType's
  };

  /** \details
    Sets the render type for this Model object.

    \param renderType [in]  Render type.
  */
  virtual void setRenderType(RenderType renderType) {}

  /** \details
    Returns the render type of this Model object.
  */
  virtual RenderType renderType() = 0;

  //virtual bool addSceneGraphRoot(OdGiDrawable* pRoot) = 0;
  //virtual bool eraseSceneGraphRoot(OdGiDrawable* pRoot) = 0;

  /** \details
    Sets the specified rendering mode override for this Model object.

    \param mode [in]  Render mode override.

    \remarks
    Rendering mode specified as OdGsView::kNone cancels currently set rendering mode override.
  */
  virtual void setRenderModeOverride(OdGsView::RenderMode mode = OdGsView::kNone) {}

  /** \details
    Returns rendering mode override, specified for this Model object.

    \remarks
    Returns OdGsView::kNone in case if rendering mode overide doesn't specified.
  */
  virtual OdGsView::RenderMode renderModeOverride() const { return OdGsView::kNone; }

  /** \details
    Enables this model's geometry to ignore the view's front and back clipping planes (if any) and viewport 3d clipping (if set).
    If the method's input value is false, the view's clipping planes and viewport 3d clipping are allowed by this Model object.

    \param bEnable [in]  Boolean flag which indicates that the model ignores the view's clipping planes and viewport 3d clipping (true value).
  */
  virtual void setViewClippingOverride(bool bEnable) = 0;

  /** \details
    Returns true in case if view clipping override enabled for this Model object, elsewhere returns false.
  */
  virtual bool viewClippingOverride() const { return false; }

  /** \details
    Sets the background of this Model object.

    \param backgroundId [in]  OdDbBackground object ID.
  */
  virtual void setBackground(const OdDbObjectId backgroundId) = 0;

  /** \details
    Returns the OdDbBackground object ID if the background was set to this Model object.
  */
  virtual OdDbObjectId background() const = 0;

  /** \details
    Sets the visual style for this Model object. This method is used to direct views
    to display the model in the specified visual style. By default, models are displayed
    in the visual style assigned to the view.

    \param visualStyleId [in]  Visual style object ID used by objects in this model

    \remarks
    Specify the OdDbObjectId::kNull as an input value to clear the model's visual style
    and use the view visual style for displaying the model's objects.
  */
  virtual void setVisualStyle(const OdDbObjectId visualStyleId) = 0;

  /** \details
    Returns the visual style of this Model object.
  */
  virtual OdDbObjectId visualStyle() const = 0;

  /** \details
    Sets the visual style for this Model object. This method is used to direct views
    to display the model in the specified visual style. By default, models are displayed
    in the visual style assigned to the view.

    \param visualStyle [in]  Visual style object
  */
  virtual void setVisualStyle(const OdGiVisualStyle &visualStyle) = 0;

  /** \details
    Returns the visual style of this Model object.

    \param visualStyle [out]  Visual style

    \returns Returns true if the visual style is set for the model, false otherwise.
  */
  virtual bool visualStyle(OdGiVisualStyle &visualStyle) const = 0;

  /** \details
    Adds a model reactor for this Model object.

    \param pReactor [in]  Model reactor
  */
  virtual void addModelReactor(OdGsModelReactor *pReactor) {}

  /** \details
    Removes the specified model reactor from this Model object.

    \param pReactor [in]  Pointer to the model reactor that should be removed
  */
  virtual void removeModelReactor(OdGsModelReactor *pReactor) {}

  /** \details
    Enables the currently specified sectioning in the views displaying this Model object.

    \param bEnable [in]  Boolean flag which indicates whether sectioning should be enabled
  */
  virtual void setEnableSectioning(bool bEnable) = 0;

  /** \details
    Returns true if the sectioning is active in the views displaying this Model object.
    Returns false in the other case.
  */
  virtual bool isSectioningEnabled() const = 0;

  /** \details
    Sets the active sectioning for this Model object. After specifying the sectioning,
    it should be enabled by the setEnableSectioning() method.

    \param points [in]  Array of co-planar points specifying a sectioning region
    \param upVector [in]  Vector that specifies the orientation of the plane that contains points

    \remarks
    If the last point of the points array is equal to the first point of this array, the sectioning region is closed.
    The upVector is used to specify the clipped and unclipped sides of the sectioning. The unclipped side
    is determined by the direction of the cross product of the first line segment defined by the point array, and the upVector.
  */
  virtual bool setSectioning(const OdGePoint3dArray &points, const OdGeVector3d &upVector) = 0;

  /** \details
    Sets the active sectioning for this Model object. The sectioning is capped vertically using
    the specified top and bottom heights. After specifying the sectioning, it should be enabled
    by the setEnableSectioning() method.

    \param points [in]  Array of co-planar points specifying a sectioning region
    \param upVector [in]  Vector that specifies the orientation of the plane that contains points
    \param dTop [in]  Specifies the top capping height of the sectioning
    \param dBottom [in]  Specifies the bottom capping height of the sectioning

    \returns Returns true if the specified sectioning is valid. Returns false
    if the specified sectioning is invalid or malformed.

    \remarks
    If the last point of the points array is equal to the first point of this array,
    the sectioning region is closed. The upVector is used to specify the clipped and unclipped
    sides of the sectioning. The unclipped side is determined by the direction of the
    cross product of the first line segment defined by the point array, and the upVector.
  */
  virtual bool setSectioning(const OdGePoint3dArray &points, const OdGeVector3d &upVector,
                             double dTop, double dBottom) = 0;

  /** \details
    Sets the visual style for the objects on the clipped side of the sectioning.

    \param visualStyleId [in]  Visual style object ID. Null by default.

    \remarks
    If the input parameter is a null object ID, the clipped side should not be drawn.
  */
  virtual void setSectioningVisualStyle(const OdDbObjectId visualStyleId) = 0;

  enum AdditionMode
  {
    kAddDrawable = 0, // Add new drawable
    kUneraseDrawable  // Added drawables are unerased
  };

  /** \details
    Enables or disables linetype display in any OdGsView object that views this Model object.

    \param bEnable [in]  Boolean flag which enables (true value) or disables (false value) linetype display.
  */
  virtual void setEnableLinetypes(bool bEnable) {}

  /** \details
    Returns true if the linetype display is enabled or returns false in the other case.
  */
  virtual bool isLinetypesEnabled() const { return false; }
  /** \details
    Enables or disables the ability to select entities inside this Model object. If the input value
    is true, entities inside this Model object is selectable. If the input value is false,
    entities inside this Model object is not selectable.

    \param bEnable [in]  Boolean flag which indicates whether this Model object is selectable.
  */
  virtual void setSelectable(bool bEnable) = 0;

  /** \details
    Checks whether entities inside this Model object is selectable. If the returning value is true,
    entities inside this Model object is selectable. If the returning value is false,
    entities inside this Model object is not selectable.
  */
  virtual bool isSelectable() const { return false; }

  /** \details
    Enables or disables extents calculation for entities inside this Model object. If the input value
    is true, entities inside this Model object will be used during view extents calculation.
    If the input value is false, entities inside this Model object will be not used in view extents calculations.

    \param bEnable [in]  Boolean flag which indicates that Model entities which will be used during view extents calculation.
  */
  virtual void setEnableViewExtentsCalculation(bool bEnable) {}

  /** \details
    Checks whether entities inside this Model object is used for view extents calculation. If the returning value is true,
    entities inside this Model object will be used in view extents calculation. If the returning value is false,
    entities inside this Model object will be not used in view extents calculation.
  */
  virtual bool isViewExtentsCalculationEnabled() const { return false; }

  /** \details
    Enables or disables lights in blocks.

    \param bEnable [in]  Boolean flag which enables (true value) or disables (false value) lights in blocks.
  */
  virtual void setEnableLightsInBlocks(bool bEnable) {}

  /** \details
    Returns true if lights in blocks are enabled or returns false in the other case.
  */
  virtual bool isLightsInBlocksEnabled() const { return false; }

  /** \details
    Enables or disables view sectioning override. In case if view sectioning override enabled, sectioning, which is enabled
    for View object (which is represents this Model object), will be ignored for Drawable objects in this Model object.

    \param bEnable [in]  Boolean flag which enabled (true value) or disables (false value) view sectioning override in this Model object.
  */
  virtual void setViewSectioningOverride(bool bEnable) {}

  /** \details
    Returns current state of view sectioning override (true value in case if view sectioning override enabled or false elsewhere).
  */
  virtual bool viewSectioningOverride() const { return false; }
  virtual void setCacheInvalid(bool) {}

  virtual GcGsGraphicsKernel &graphicsKernel(void) = 0;

  virtual bool addSceneGraphRoot(OdGiDrawable * pRoot) = 0;
  virtual bool eraseSceneGraphRoot(OdGiDrawable * pRoot) = 0;

  virtual void                onModified(OdGiDrawable * pModified,
    OdGiDrawable * pParent,
    InvalidationHint hint) {}
  virtual void                onModified(OdGiDrawable * pModified,
    OdIntDbId  parentID,
    InvalidationHint hint) {}

  virtual void                onPaletteModified(void) {}

  virtual void                setExtents(const OdGePoint3d & obj1,
    const OdGePoint3d &obj2)
  {
  }

  virtual void                enableLinetypes(bool bEnable) {}
  virtual bool                linetypesEnabled(void) const { return true; }

  virtual double              shadowPlaneLocation(void) const { return 0; }
  virtual void                setShadowPlaneLocation(double planeLocationZ) {}

  virtual bool                selectable(void) const { return true; }

  virtual void                setDrawOrder(OdGiDrawable*   pDrawable,
    OdGiDrawable*   pRelativeDrawable,
    OdGiDrawable*   pParent,
    OrderActionType action)
  {

  }

  virtual bool                bounds(const OdGiDrawable& drawable,
    OdGePoint3d& minPt,
    OdGePoint3d& maxPt)
  {
    return false;
  }

  virtual void                setUnitScale(double metersPerUnit) {}

  virtual double              unitScale(void) const { return 1.0; }

  virtual void                setLightingPhotometric(bool bPhotometric) {}

  virtual bool                isLightingPhotometric(void) const { return false; }

  virtual void                setLightsInBlocksEnabled(bool bEnabled) {}

  virtual bool                lightsInBlocksEnabled(void) const { return false; }

  virtual void                setEnableNotify(bool) {}
  virtual bool                isEnableNotify() const { return true; }
};




/** \details
    GsModel reactor.

    Corresponding C++ library: TD_Gs
    <group OdGs_Classes>
*/
class OdGsModelReactor
{
public:
  OdGsModelReactor() { }
  virtual ~OdGsModelReactor() { }

  virtual bool onSceneGraphRootAdded(OdGsModel *pModel, OdGiDrawable *pAdded) { return true; }
  virtual bool onSceneGraphRootErased(OdGsModel *pModel, OdGiDrawable *pErased) { return true; }

  /** \details
    Notification function called whenever a drawable object is added to the Model object. Does nothing in current implementation.

    \param pModel [in]  Pointer to the model.
    \param pAdded [in]  Pointer to the added Drawable object.
    \param pParent [in]  Pointer to the parent of the added Drawable object.
    \returns
    true
  */
  virtual bool onAdded(OdGsModel *pModel, OdGiDrawable *pAdded, OdGiDrawable *pParent) { return true; }

  /** \details
    Notification function called whenever a drawable object is added to the Model object. Does nothing in current implementation.

    \param pModel [in]  Pointer to the model.
    \param pAdded [in]  Pointer to the added Drawable object.
    \param parentID [in]  Object ID of the parent of the added Drawable object.
    \returns
    true
  */
  virtual bool onAdded(OdGsModel *pModel, OdGiDrawable *pAdded, OdIntDbId parentID) { return true; }

  /** \details
    Notification function called whenever a drawable object is erased from the Model object.

    \param pModel [in]  Pointer to the model.
    \param pErased [in]  Pointer to the erased Drawable object.
    \param pParent [in]  Pointer to the parent of the erased Drawable object.
    \returns
    true
  */
  virtual bool onErased(OdGsModel *pModel, OdGiDrawable *pErased, OdGiDrawable *pParent) { return true; }

  /** \details
    Notification function called whenever a drawable object is erased from the Model object.

    \param pModel [in]  Pointer to the model.
    \param pErased [in]  Pointer to the erased Drawable object.
    \param parentID [in]  Object ID of the parent of the erased Drawable object.
    \returns
    true
  */
  virtual bool onErased(OdGsModel *pModel, OdGiDrawable *pErased, OdIntDbId parentID) { return true; }

  /** \details
    Notification function called whenever a drawable object is modified in the Model object. Does nothing in current implementation.

    \param pModel [in]  Pointer to the model.
    \param pModified [in]  Pointer to the modified Drawable object.
    \param pParent [in]  Pointer to the parent of the modified Drawable object.
    \returns
    true
  */
  virtual bool onModified(OdGsModel *pModel, OdGiDrawable *pModified, OdGiDrawable *pParent) { return true; }

  /** \details
    Notification function called whenever a drawable object is modified in the Model object. Does nothing in current implementation.

    \param pModel [in]  Pointer to the model.
    \param pModified [in]  Pointer to the modified Drawable object.
    \param parentID [in]  Object ID of the parent of the modified Drawable object.
    \returns
    true
  */
  virtual bool onModified(OdGsModel *pModel, OdGiDrawable *pModified, OdIntDbId parentID) { return true; }

  /** \details
    Notification function called whenever a drawable object is unerased in the Model object.

    \param pModel [in]  Pointer to the model.
    \param pUnerased [in]  Pointer to the unerased Drawable object.
    \param pParent [in]  Pointer to the parent of the unerased Drawable object.
  */
  virtual bool onUnerased(OdGsModel *pModel, OdGiDrawable *pUnerased, OdGiDrawable *pParent) { return onAdded(pModel, pUnerased, pParent); }

  /** \details
    Notification function called whenever a drawable object is unerased in the Model object.

    \param pModel [in]  Pointer to the model.
    \param pUnerased [in]  Pointer to the unerased Drawable object.
    \param pParent [in]  Object ID of the parent of the modified Drawable object.
  */
  virtual bool onUnerased(OdGsModel *pModel, OdGiDrawable *pUnerased, OdIntDbId parentID) { return onAdded(pModel, pUnerased, parentID); }
};

enum
{
  kLayerLockFaded = 0x00000001,
  kXrefDwgFaded = 0x00000002,
  kRefWorksetFaded = 0x00000004,
  kRefWorksetFadedCheck = 0x00000008,
  kRefWorkset = kRefWorksetFaded | kRefWorksetFadedCheck,
  kBvModeFaded = 0x00000010
};

/** \details
    This stucture contains the Window ID and Viewport Object ID.
    
    Corresponding C++ library: TD_Gs

    <group !!RECORDS_TD_APIRef>
*/
struct OdGsClientViewInfo 
{
  enum ViewportFlags
  {
    kDependentViewport = 1,
    kDependentGeometry = 2,
    kHelperView        = 4,
    kSetViewportId     = 8
  };

  OdLongPtr      viewportId;        // Returned by OdGiViewport::viewportId()
  OdLongPtr      acadWindowId;      // Returned by OdGiViewport::acadWindowId()
  OdIntDbId      viewportObjectId;  // Returned by OdGiViewportDraw::viewportObjectId() OdDbStub*
  //OdGiContextualColorsPtr contextColors; // Returned by OdGiViewport::contextualColors()
  OdUInt32  viewportFlags;     // Optional view flags
  OdGiContextualColors *contextColors;  
  OdGiContextualAttributes *contextualAttributes; 

  OdDbObjectId viewportObjectAsObjectId() const { return (OdDbStub*)viewportObjectId; }

  OdGsClientViewInfo()
    : viewportId(-1)
    , acadWindowId(0)
    , viewportObjectId(NULL)
    , viewportFlags(0)
  {
  }
};

/** \details
    This class is the base class for custom classes that receive notification
    of OdGs Collision Detection events.
    
    \remarks
    The default implementations of all methods in this class do nothing but return.

    <group OdGs_Classes> 
    \sa
    <link gs_collision_detection, Working with Collision Detection>
*/
class OdGsCollisionDetectionReactor
{
public:
  enum
  {
    kNotImplemented = 0x80000000,
    kContinue       = 0,
    kBreak          = 1
  };
  /** \details
    Notification function called whenever an collision detected.

    \param pPathNode1 [in]  Pointer to the OdGiPathNode object from OdGsView::collide input list
    \param pPathNode2 [in]  Pointer to the OdGiPathNode object that collides with pathNode1

    \remarks
    Returns kContinue if the operation is to continue or kBreak to stop collision detection
  */
  virtual OdUInt32 collisionDetected(const OdGiPathNode* /*pPathNode1*/, const OdGiPathNode* /*pPathNode2*/)
  {
    return OdUInt32(kNotImplemented);
  }

  /** \details
  Notification function called whenever an collision detected if distance calsulation is specified

  \param pPathNode1 [in]  Pointer to the OdGiPathNode object from OdGsView::collide input list
  \param pPathNode2 [in]  Pointer to the OdGiPathNode object that collides with pathNode1
  \param dDistace   [in]  Collision distance. If negative, it is the penetration depth. If positive, it is the clearance.

  \remarks
  Returns kContinue if the operation is to continue or kBreak to stop collision detection
*/
  virtual OdUInt32 collisionDetected( const OdGiPathNode* pPathNode1, const OdGiPathNode* pPathNode2, double dDistance )
  {
    return collisionDetected( pPathNode1, pPathNode2 );
  }
};

/** \details
    This class is the context for Collision Detection
    
    \sa
    TD_Gs
  
    <group OdGs_Classes> 
*/
class OdGsCollisionDetectionContext
{
//DOM-IGNORE-BEGIN
protected:
  OdUInt8 m_flags;
  OdGeTol m_tolerance;
  enum Options
  {
    kIntersectionOnly = 1,
    kIntersectionWithModel = 1 << 1,
    kIgnoreViewExtents = 1 << 2,
    kCombineSubEntities = 1 << 3,
    kOverrideTolerance = 1 << 4,
    kCalculateDistance = 1 << 5,
    kCheckAll = 1 << 6,
    kProcessSingleList = 1 << 7
  };
  double m_clearance;
//DOM-IGNORE-END
public:
  /** \details
    Default constructor for the OdGsCollisionDetectionContext class. Sets default tolerance value for geometric operations.
  */
  OdGsCollisionDetectionContext() : m_flags( kCalculateDistance ) { m_tolerance = OdGeTol(); m_clearance = 0.0; };

  /** \details
    Sets flag that specifies whether collisions are detected only when objects intersect.
    \param bSet    [in]  Flag that specifies whether to detect collisions only when objects intersect. If set to false, collisions can be detected via touches (no intersections).
  */
  void setIntersectionOnly( bool bSet ) { SETBIT( m_flags, kIntersectionOnly, bSet ); }
  
  /** \details
    Retrieves a flag that specifies whether collisions are detected only when objects intersect. 
    \returns
    true if collisions are detected only when objects intersect or false when collisions can be detected via touches.
  */
  bool intersectionOnly() const { return GETBIT( m_flags, kIntersectionOnly ); }

  /** \details
    Sets flag that specifies whether collisions should be detected with a model.
    \param bSet    [in]  Flag that specifies whether to detected collisions with a model.
  */
  void setIntersectionWithModel( bool bSet ) { SETBIT( m_flags, kIntersectionWithModel, bSet ); }
  
  /** \details
    Retrieves a flag that specifies whether collisions are detected only when objects intersect. 
    \returns
    true if collisions are detected only when objects intersect or false when collisions can be detected via touches.
  */
  bool intersectionWithModel() const { return GETBIT( m_flags, kIntersectionWithModel ); }

  /** \details
    Specifies whether collisions should be detected despite objects are outside view extents.
    \param bSet    [in]  Flag that specifies whether to detected collisions even if objects are beyond view extents.
  */
  void setIgnoreViewExtents( bool bSet ) { SETBIT( m_flags, kIgnoreViewExtents, bSet ); }
  
  /** \details
    Checks whether collisions are detected even if objects are outside view extents. 
    \returns
    true if collisions are detected even if objects are beyond view extents, false otherwise.
  */
  bool ignoreViewExtents() const { return GETBIT( m_flags, kIgnoreViewExtents ); }
  /** \details
  Specifies subentity markers ignoring.
  \param bSet [in] If true, subentities markers will be ignored.
  */
  void setCombineSubEntities( bool bSet ) { SETBIT( m_flags, kCombineSubEntities, bSet ); }
  /** \details
  Retrives subentity markers ignoring.
  \returns Returns flag that indicates should subentities markers be ignored or not.
  */
  bool combineSubEntities() const { return GETBIT( m_flags, kCombineSubEntities ); }
  /** \details
  Specifies custom collision tolerance.
  \param tol [in] Collision tolerance
  */
  void setToleranceOverride( const OdGeTol& tol )
  {
    SETBIT_1( m_flags, kOverrideTolerance );
    m_tolerance = tol;
  }
  /** \details
  Checks that collision detection should use custom tolerance.
  \returns Returns flag that indicates should collision detection use custom tolerance or not.
  */
  bool isToleranceOverride() const { return GETBIT( m_flags, kOverrideTolerance ); }
  /** \details
  Retrives custom collision detection tolerance.
  \returns Returns custom collision detection tolerance.
  */
  const OdGeTol& toleranceOverride() const { return m_tolerance; }
  /** \details
  Specifies that collision detection should also calculate distances (penetration depth or distance between objects)
  \param bSet [in] If true, distances will be calculated.
  */
  void setCalculateDistance( bool bSet ) { SETBIT( m_flags, kCalculateDistance, bSet ); }
  /** \details
  Checks should collision detection calculate distances (penetration depth or distance between objects)
  \returns Returns flag that indicates should collision detection calculate distances or not.
  */
  bool getCalculateDistance() const { return GETBIT( m_flags, kCalculateDistance ); }
  /** \details
  Specifies that collision detection should check all faces instead of detecting first collision.
  \param bSet [in] If true, collision detection will check all faces instead of detecting first collision.
  */
  void setCheckAll( bool bSet ) { SETBIT( m_flags, kCheckAll, bSet ); }
  /** \details
  Checks that collision detection should check all faces instead of detecting first collision.
  \returns Returns flag that indicates should collision detection check all faces instead of detecting first collision.
  */
  bool getCheckAll() const { return GETBIT( m_flags, kCheckAll ); }
  /** \details
  Specifies collision detection clearance value.
  \param c [in] Collision detection clearance value.
  */
  void setClearance( double c ) { m_clearance = c; }
  /** \details
  Retrives collision detection clearance value.
  \returns Returns collision detection clearance value.
  */
  double getClearance() const { return m_clearance; }
  /** \details
  Specifies should collision detection detects collisions between list and all other entities (false)
  or it should detect collisions between entities in list (true).
  \param bSet [in] If true, collision detection will detect collisions between entities in list instead of between list and other entities.
  */
  void setProcessSignleList( bool bSet ) { SETBIT( m_flags, kProcessSingleList, bSet ); }
  /** \details
  Checks that collision detection should detects collisions between list and all other entities (false)
  or it should detect collisions between entities in list (true).
  \returns Returns flag that indicates should collision detection detect collisions between entities in list instead of between list and other entities.
  */
  bool getProcessSignleList() const { return GETBIT( m_flags, kProcessSingleList ); }

};

class OdGiContext;

/** \details
    This class is the abstract base class for classes that encapsulate GUI display windows.

    \remarks
    OdGsDevice objects own, update, and refresh one or more OdGsView objects.
    In addition, they responds to operating system notifications,
    such as window resize, forwarded by the graphics system client.
    Corresponding C++ library: TD_Gs
        
    <group OdGs_Classes>
    \sa
    <link tv_working_with_base_classes_device, Working with Visualize Graphics Devices>
    \sa
    <link gs_OdGsDevice, Working with Graphics Devices>
*/
class FIRSTDLL_EXPORT OdGsDevice : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdGsDevice);

  enum RendererType
  {
    kDefault,
    kSoftware,
    kSoftwareNewViewsOnly,
    kFullRender,
    kSelectionRender,
    kFbxExportRender
  };
  enum EnableIRResult
  {
    kSuccess,
    kOutOfMemory
  };
  /** \details
    Returns a SmartPointer to the dictionary containing the 
    properties for this Device object.
    \sa
    <link gs_DeviceProps, ODA Vectorization Devices Properties>
  */
  virtual OdRxDictionaryPtr properties() { return OdRxDictionaryPtr(); }

  /** \details
    Returns the User Context object associated with this Device object.
  */
  virtual OdGiContext* userGiContext() const { return NULL; }

  /** \details
    Sets the User Context object associated with this Device object.
    \param pUserGiContext [in]  Pointer to the User Context.
  */
  virtual void setUserGiContext(OdGiContext* pUserGiContext) {}

  /** \details
    Marks for refresh entire region of the GUI window of this Device object.
  */
  virtual void invalidate() = 0;

  /** \details
    Marks for refresh the specified region of the GUI window of this Device object.
     
    \param screenRect [in]  Rectangular area.
  */
  virtual void invalidate(const OdGsDCRect &screenRect) = 0;

  /** \details
    Checks whether the GUI window for this Device object is showing the correct image.
    
    \returns 
    true if the GUI window for this Device object is showing the correct image, false otherwise.
    \remarks
    This implies the following:
    * No part of GUI area is flagged for refresh.
    * All rasterizations are complete
    * The rendering pipeline has been flushed.
  */
  virtual bool isValid() const = 0;

  /** \details
    Updates the GUI window for this Device object.
    
    \param pUpdatedRect [out]  Pointer to the a rectangle to receive the region updated by this function.

    \remarks
    This function call is propagated to all OdGsView objects owned by this Device object,
    thus displaying the correct image on the GUI window of this Device object.
  */
  virtual void update(OdGsDCRect* pUpdatedRect = 0) = 0;

  /** \details
    Notification function called whenever the size of the GUI window for this Device object has changed.
    
    \param outputRect [in]  New size of the output rectangle in device coordinates (pixels).

    \remarks
    This function should not be called if this Device object has a width and/or height of 0, .
  */
  virtual void onSize(const OdGsDCRect& outputRect) {}
  
  /** \details
    Notification function called whenever the size of the GUI window for this Device object has changed.
    
    \param outputRect [in]  New size of the output rectangle in device coordinates (pixels).

    \remarks
    This function should not be called if this Device object has a width and/or height of 0, .
  */
  virtual void onSize(const OdGsDCRectDouble& outputRect);
  virtual void onSize(int x, int y);

  /** \details
    Returns device surface output rectangle.

    \param outputRect [out]  Obtains size of the output rectangle in device coordinates (pixels).
  */
  virtual void getSize(OdGsDCRect& outputRect) const {}
  
  /** \details
    Returns device surface output rectangle.

    \param outputRect [out]  Obtains size of the output rectangle in device coordinates (pixels).
  */
  virtual void getSize(OdGsDCRectDouble& outputRect) const;

  /** \details
    
    \remarks
    Causes this Device object to realize its foreground palette.
  */
    virtual void onRealizeForegroundPalette() = 0;

  /** \details
    Notification function typically called whenever the GUI window for this Device object loses focus.
    
    \remarks
    Causes this Device object to realize its background palette.
  */
    virtual void onRealizeBackgroundPalette() = 0;

  /** \details
    Notification function called whenever the OS screen resolution and/or color depth have changed.
    
    \param bitsPerPixel [in]  Color depth.
    \param xPixels [in]  X pixels.
    \param yPixels [in]  Y pixels.
  
    \remarks
    This function is called after the operation.  
  */
  virtual void onDisplayChange(int bitsPerPixel, int xPixels, int yPixels) = 0;

  /** \details
    Creates a new OdGsView object, and associates it with this Device object.
    
    \param pViewInfo [in]  Pointer to the Client View Information for this Device object.
    \param enableLayerVisibilityPerView [in]  Layer visibility per viewport is supported, if and only if true.
    
    \returns
    Returns a SmartPointer to the newly created object.

    pViewInfo contains information returned by OdGiViewport::acadWindowId() and OdGiViewportDraw::viewportObjectId()
  */
  virtual OdGsViewPtr createView(
    const OdGsClientViewInfo* pViewInfo = 0,
    bool enableLayerVisibilityPerView = false) 
  {
    return OdGsViewPtr();
  }

  /** \details
    Associates the specified Viewport object with this Device object.
    
    \param pView [in]  Pointer to the OdGsView object.
  */
  virtual bool add(OdGsView* pView) = 0;

  /** \details
    Creates a new OdGsModel object, and associates it with this Device object.
    
    \returns
    Returns a SmartPointer to the newly created object.
  */
  virtual OdGsModelPtr createModel()
  {
    return OdGsModelPtr();
  }

  /** \details
    Checks compatibility between specified OdGsModel and this Device object.

    \param pModel [in]  Model object pointer to check compatibility.
    \returns
    true if the provided model is compatible with this device, false otherwise.
    \remarks
    Use this method to check compatibility of exist Model object and newly created device
    to be sure the exist Model object could be used with this Device object.
    By default this always returns false. It is must be implemented in inherited classes
    to enable Model object reuse support. If Device object use overriden Model object
    it should return false if input Model object doesn't overriden.
    Typical way to check compatibility is using of RTTI.
    If your metafiles cache doesn't support per-device sharing override and return false.
  */
  virtual bool isModelCompatible(OdGsModel* pModel) const;

  /** \details
    Stores current device state into filer object.

    \param pFiler [out]  Filer object.
    \returns
    true if device state is successfully saved, false if device state saving is not supported.
  */
  virtual bool saveDeviceState(OdGsFiler *pFiler) const;
  /** \details
    Restores device state from filer object.

    \param pFiler [in]  Filer object.
    \returns
    true if device state is successfully loaded, false if device state loading is not supported.
  */
  virtual bool loadDeviceState(OdGsFiler *pFiler);

  /** \details
    Inserts the specified Viewport object to the specified position in this Device object.

    \param viewIndex [in]  View index.
    \param pView [in]  Pointer to the OdGsView object.
  */
  virtual void insertView(int viewIndex, OdGsView* pView) {}

  /** \details
    Erases the specified View object.
    \param pView [in]  Pointer to the OdGsView object.

    \returns
    Returns true if and only if successful.
  */
  virtual bool erase(OdGsView* pView) = 0;
  
  /** \details
    Erases the specified View object.

    \param viewIndex [in]  View index.
    \returns
    Returns true if and only if successful.
  */
  virtual bool eraseView(int viewIndex) { return false; }

  /** \details
    Erases all views associated with this Device object.
  */
  virtual void eraseAll() = 0;

  /** \details
    Returns the number of views associated with this Device object.
  */
  virtual int numViews() const { return 0; }

  /** \details
    Returns the specified OdGsView object associated with this Device object.
    \param viewIndex [in]  View index.
  */
  virtual OdGsView* viewAt(int viewIndex) { return 0; }

  /** \details
    Sets the Background Color of the GUI window of this Device object.
    \param backgroundColor [in]  Background color.
  */
  virtual bool setBackgroundColor(OdGsColor backgroundColor) = 0;

  /** \details
    Returns the Background Color of the GUI window of this Device object.
  */
  virtual OdGsColor getBackgroundColor() = 0;

  /** \details
    Sets the logical pallete to be used by this Device object.
    
    \param logicalPalette [in]  Logical palette.
    \param numColors [in]  Number of colors in palette.
    
    \remarks
    The logical pallete is used with calls to OdGiSubEntityTraits::setColor().
  */
  virtual void setLogicalPalette(const ODCOLORREF* logicalPalette, int numColors) {}


  /** \details
    Returns the logical pallete used by this Device object.

    \param numColors [out]  Number of colors in palette.
  */
  virtual const ODCOLORREF* getLogicalPalette(int &numColors) const { return NULL; }

  /** \details
    Returns image of current device buffer.

    \param pImage [out]  Pointer for image to return.
    \param region [in]  Rectangle specifies region to return.

    \remarks
    Implementation can throw eNotImplementedYet exception if current vectorization module doesn't support snap shots.
  */
  virtual void getSnapShot(OdGiRasterImagePtr &pImage, const OdGsDCRect &region) {}

  /** \details
    Returns OdGsUpdateManager associated with current device

    \param createIfNotExist [in] Creates instance of OdGsUpdateManager if no one associated with device
  */
  virtual OdGsUpdateManagerPtr getUpdateManager( bool createIfNotExist = false );

  /** \details
    Associates OdGsUpdateManager with device

    \param pManager [in] Pointer to the OdGsUpdateManager
  */
  virtual void setUpdateManager( OdGsUpdateManagerPtr pManager );

  virtual void setLogicalPalette(const OdGsColor* logicalPalette, int numColors);
  virtual void setPhysicalPalette(const OdGsColor * palette, int nCount);
  
  virtual GcGsGraphicsKernel &graphicsKernel(void);

  virtual void invalidate(OdGsModel::RenderType pane);
  virtual void invalidate(const OdGsDCRect &rect, OdGsModel::RenderType pane);

  virtual void update(OdGsDCRect* pUpdatedRect, GS::SyncBehavior sync);
  virtual Otil::Image *       createSnapshot(const OdGsDCPoint&     offset,
    const OdGsDCRect&      imageDim,
    GS::ImageDataFormat    format,
    GS::ImageOrientation   orientation);

  virtual int                 getMaxDeviceWidth(void);
  virtual int                 getMaxDeviceHeight(void);

  virtual void                setDesiredFrameRate(float frameRate);
  virtual void                pauseInteractiveRender(void);
  virtual void                resumeInteractiveRender(void);
  virtual void                postRenderProgressCheckingReqeust();

  virtual EnableIRResult      beginInteractiveRender(GcGsRenderProgressMonitor* pProgressMonitor);
  virtual void                endInteractiveRender(void);
  virtual bool                isRendering(void) const;
  
  virtual void                setFontKerningDisplay(bool bDisplay);

  virtual void                getSnapShot(Otil::Image *pOutput, const OdGsDCPoint& offset);
  
  virtual void                setDeviceRenderer(RendererType type);
  virtual RendererType        getDeviceRenderer(void);

  virtual void                setRenderInterrupter(GcGsRenderInterrupter* pInterrupter);
  virtual GcGsRenderInterrupter* getRenderInterrupter(void) const;
  virtual void                setDisplayUpdateSuppressed(bool bSuppressed);
};

class OdGsModule;

/** \details
    This class is the base class for custom classes that receive notification
    of OdGs events.
    
    \remarks
    The default implementations of all methods in this class do nothing but return.

    \sa
    TD_Gs
  
    <group OdGs_Classes> 
*/
class FIRSTDLL_EXPORT OdGsReactor : public OdRxObject
{
public:
  enum ViewUpdateFlags { kCameraChanged = 1 };
  /** \details
    Notification function called whenever a OdGsView object has been created.
    \param pView [in]  Pointer to the OdGsView object.

    \remarks
    This function is called after the operation.
  */
  virtual void viewWasCreated(OdGsView* pView);

  /** \details
    Notification function called whenever an OdGsView object is about to be destroyed.
    \param pView [in]  Pointer to the OdGsView object.

    \remarks
    This function is called before the operation.
  */
  virtual void viewToBeDestroyed(OdGsView* pView);

  /** \details
    Notification function called before OdGsView properties are updated.
    \param pView [in]  Pointer to the OdGsView object.
    \param flags [in]  Bitcoded flags of type ViewUpdateFlags depending on which properties are effected.
  */
  virtual void viewToBeUpdated(OdGsView* pView, int flags);

  /** \details
    Notification function called after OdGsView properties are updated.
    \param pView [in]  Pointer to the OdGsView object.
    \param flags [in]  Bitcoded flags of type ViewUpdateFlags depending on which properties are effected.
  */
  virtual void viewWasUpdated(OdGsView* pView, int flags);

  /** \details
    Notification function called whenever an OdGsModule object is about to be unloaded.
    \param pModule [in]  Pointer to the OdGsModule object.

    \remarks
    This function is called after the operation.
  */
  virtual void gsToBeUnloaded(OdGsModule* pModule);

  virtual void gsToBeUnloaded(GcGsGraphicsKernel *p);

  virtual void viewInteractivityToBeChanged(const OdGsView *, bool) { }
  virtual void viewInteractivityWasChanged(const OdGsView *, bool) { }
};

/** \details
    This class provides management of OdGsDevice classes.
    Corresponding C++ library: TD_Gs 
    <group OdGs_Classes> 
*/
class FIRSTDLL_EXPORT OdGsModule : public OdRxModule
{
public:
  ODRX_DECLARE_MEMBERS(OdGsModule);

  /** \details
    Creates a new OdGsDevice object, and associates it with this Module object.
    \returns
    Returns a SmartPointer to the newly created object.
  */
  virtual OdGsDevicePtr createDevice() = 0;

  /** \details
    Creates a new OdGsBaseVectorizeDevice object, and associates it with this Module object.
    \returns
    Returns a SmartPointer to the newly created object.
  */
  virtual OdGsDevicePtr createBitmapDevice();

  /** \details
    Adds the specified reactor to this object's reactor list.
    \param pReactor [in]  Pointer to the reactor object.
  */
  virtual void addReactor(OdGsReactor* pReactor) = 0;

  /** \details
    Removes the specified reactor from this object's reactor list.
    \param pReactor [in]  Pointer to the reactor object.
  */
  virtual void removeReactor(OdGsReactor* pReactor) = 0;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdGsModule object pointers. 
*/
typedef OdSmartPtr<OdGsModule> OdGsModulePtr;

/** \details
  Default Gs Marker value for highlight entire entity.
*/

#include "../TD_PackPop.h"

#endif // __GS_H_INCLUDED_
