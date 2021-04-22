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

#ifndef _OD_DB_POINTCLOUDEX_
#define _OD_DB_POINTCLOUDEX_

#include "DbPointCloudObjExports.h"
#include "DbPointCloudCropping.h"
#include "DbPointCloudIntensityStyle.h"
#include "TD_PackPush.h"

#include "DbEntity.h"
#include "DbPointCloudHostPE.h"
#include "OdPointCloudItem.h"

class OdDbPointCloudExLimitBox;
class OdDbPointCloudItem;
class PointCloudPerfMonitor;

class IOdDbPointCloudDataBuffer;
class IOdDbPointCloudPointProcessor;
class IOdDbPointCloudSpatialFilter;
class IOdDbPointCloudAttributeFilter;

class OdPointCloudExtractedCylinder;

class OdDbPointCloudCropStateManager;
/** \details
This class represents PointCloudEx entities in an OdDbDatabase instance.

Corresponding C++ library: AcDbPointCloudObj

<group OdDbPointCloud_Classes>
*/
class DBPOINTCLOUDOBJ_EXPORT OdDbPointCloudEx : public OdDbEntity
{
public:

  //DOM-IGNORE-BEGIN
  ODDB_DECLARE_MEMBERS( OdDbPointCloudEx );
  //DOM-IGNORE-END

  /** \details
    Default constructor. Creates an empty point cloud entity.
  */
  OdDbPointCloudEx();

  /** \details
    Destructor.
  */
  ~OdDbPointCloudEx() {}

  /** \details
  Returns the Object ID of the OdDbPointCloudDefEx object associated with this point cloud ex entity.
  */
  OdDbObjectId pointCloudDefExId() const;

  /** \details
  Sets the Object ID of the OdDbPointCloudDefEx object associated with this point cloud ex entity.

  \param pointCloudDefExId [in]  Object ID of the point cloud ex to be associated with this point cloud ex entity.
  */
  void setPointCloudDefExId( const OdDbObjectId pointCloudDefExId );  

  /** \details
  Returns the Object ID of the OdDbPointCloudDefReactorEx object associated with this point cloud ex entity.

  \remarks
  Each OdDbPointCloudEx object must have an OdDbPointCloudDefReactorEx associated with the OdDbPointCloudDefEx object it is using.
  */
  OdDbObjectId reactorId() const;

  /** \details
  Sets the Object ID of the OdDbPointCloudDefReactorEx object associated with this point cloud entity.

  \param pointCloudDefReactorExId [in]  Object ID of a reactor for this point cloud ex entity.

  \remarks
  Each OdDbPointCloudEx object must have an OdDbPointCloudDefReactorEx associated with the OdDbPointCloudDefEx object it is using.
  */
  void setReactorId( const OdDbObjectId pointCloudDefReactorExId );

  /** \details
  Returns true if the point cloud entity ex is locked or false otherwise.
  */
  bool locked() const;

  /** \details
  Sets the point cloud entity ex to be locked.
  */
  void setLocked( bool bLocked );

  /** \details
    Returns the current scaling multiplier.
  */
  double scale() const;

  /** \details
    Sets a new scaling multiplier.
  
    \param scale [in] New scaling multiplier.
  */
  OdResult setScale( double scale );

  /** \details
    Returns the current rotation angle value.
  */
  double rotation() const;

  /** \details
    Sets a new rotation angle value.

    \param newRotation [in] New rotation angle value. 
  */
  OdResult setRotation( double newRotation );

  /** \details
    Returns the 3d point, that the represents the translation values
    in the transformation matrix.
  */
  OdGePoint3d location() const;

  /** \details
    Sets new translation values to the transformation matrix.

    \param newLocation [in] New translation values as a point.
  */
  OdResult setLocation( OdGePoint3d newLocation );

  /** \details
    Returns native cloud extents.

    \param extents [out] Output extents.
  */
  void getNativeCloudExtent( OdGeExtents3d& extents ) const;

  /** \details
  NOT IMPLEMENTED
  */
  unsigned int getVisiblePointCount() const;

  /** \details
  NOT IMPLEMENTED
  */
  unsigned int getLoadedVisiblePointCount() const;

  /** \details
  NOT IMPLEMENTED
  */
  unsigned int getDisplayedVisiblePointCount() const;

  PointCloudPerfMonitor*   getPointCloudPerfMonitor();

  /** \details
    Retrieves the currently active file name.

    \param fileName [out] Output active file name.
    \returns true.
  */
  bool getActiveFileName( OdString& fileName ) const;

  /** \details
    Sets an active file name.

    \param strActiveFileName [in] New active file name.
    \returns true.
  */
  bool setActiveFileName( const OdChar* strActiveFileName );

  /** \details
    Returns the name of the saved file.
  */
  OdString getPointCloudName() const;

  /** \details
    Sets the name of the saved file.

    \param name [in] New saved file name.
    \returns eOk.
  */
  OdResult setPointCloudName( const OdString& name );

  //

  /** \details
    Returns the current point cloud cropping.

    \param index [in]
    \returns 
      NULL if index if greater than the array size.
      Pointer to the OdDbPointCloudCrop element with specified index from an array - otherwise.
  */
  OdDbPointCloudCrop* getConstPointCloudCropping( int index );

  /** \details
    Returns the current point cloud cropping.

    \param index [in]
    \returns
      NULL if index if greater than the array size.
      Pointer to the OdDbPointCloudCrop element with specified index from an array - otherwise.
  */
  OdDbPointCloudCrop const* getConstPointCloudCropping( int index ) const;

  /** \details
    Adds a cropping boundary to the boundary array if it's valid.

    \param boundary [in] New cropping boundary to be added.
  */
  void addCroppingBoundary( OdDbPointCloudCrop const &boundary );

  /** \details
    Clears the cropping boundary array.
  
    \returns eOk.
  */
  OdResult clearCropping();

  /** \details
    Removes the last cropping boundary from the array.

    \returns eOk.
  */
  OdResult removeLastCropping();

  /** \details
  NOT IMPLEMENTED
  */
  int getCroppingCount() const;

  /** \details
    NOT IMPLEMENTED
  */
  bool getCroppingInvert() const;

  /** \details
  NOT IMPLEMENTED
  */
  OdResult setCroppingInvert( bool bInvert );

  /** \details
  NOT IMPLEMENTED
  */
  void setInCreatingCroppingMode( bool bCreating );

  /** \details
  Returns true only if this point cloud ex entity is displayed as clipped.
  */
  bool showCropped() const;

  /** \details
  Set whether this point cloud ex entity is displayed as clipped.

    \param bShowcropping [in]  Value for option.
  \returns
  Returns eOk.
  */
  OdResult setShowCropped( bool bShowCropping );

  //
  /** \details
    This enumeration represents various stylization types for point cloud entities.
  */
  enum StylizationType
  {
    kTrueColor = 1,
    kSingleColor,
    kNormalRamp,
    kHeightRamp,
    kIntensityRamp,
    kClassificationRamp
  };

  /** \details
    Returns the current stylization type.

    \remarks
      Possible stylization type values:
      <table>
        <b>Name</b>           <b>Value</b>     <b>Description</b>
        kTrueColor            1                TrueColor description.
        kSingleColor          2                SingleColor description.
        kNormalRamp           3                NormalRamp description.
        kHeightRamp           4                HeightRamp desctiption.
        kIntensityRamp        5                IntensityRamp description.
        kClassificationRamp   6                ClassificationRamp description.
      </table>
  */
  StylizationType stylizationType() const;

  /** \details
    Sets new stylization type.

    \param type [in] Enum value of stylization type.
    \returns eOk if the opertation completed successfully, or an appropriate error code otherwise.
    \remarks
      Possible stylization type values:
      <table>
        <b>Name</b>           <b>Value</b>     <b>Description</b>
        kTrueColor            1                TrueColor description.
        kSingleColor          2                SingleColor description.
        kNormalRamp           3                NormalRamp description.
        kHeightRamp           4                HeightRamp desctiption.
        kIntensityRamp        5                IntensityRamp description.
        kClassificationRamp   6                ClassificationRamp description.
      </table>
  */
  OdResult setStylizationType( StylizationType type );

  //

  /** \details
    Retrieves the current color scheme. if the current stylization type is one of the following:
      <table>
        kIntensityRamp
        kHeightRamp
        kClassificationRamp
      <table>.
    
    \returns 
      The current color scheme if the current stylization type is one of the following:
        <table>
          kIntensityRamp
          kHeightRamp
          kClassificationRamp
        <table>.
      Empty string otherwise.


  */
  OdString getCurrentColorScheme() const;

  /** \details
    Sets new color scheme f the current stylization type is one of the following:
      <table>
        kIntensityRamp
        kHeightRamp
        kClassificationRamp
      <table>.

    \param guid [in] New color scheme to be set.
    \returns eOk if the operation completed successfully, or an appropriate error code otherwise.
  */
  OdResult setCurrentColorScheme( const OdString &guid );

  OdString getColorSchemeForStylization( StylizationType type ) const;

  OdResult setColorSchemeForStylization( const OdString &guid, StylizationType type );

  //

  /** \details
    This enumeration represents various types of behaviour
    when an option (intensity of elevation) is out of range.
  */
  enum DispOptionOutOfRange
  {
    kUseMinMaxColors = 0,
    kUseRGBScanColors,
    kHidePoints
  };

  /** \details
    Checks if the intensity is shown as gradient.

    \returns true if intensity is shown as gradient, false - otherwise.
  */
  bool showIntensityAsGradient() const;

  /** \details
    Sets a flag whether to show intensity as gradient.

    \param bShowAsGradient [in] Flag value.
  */
  void setShowIntensityAsGradient( bool bShowAsGradient );

  /** \details
    Returns the current value of minimal intensity.
  */
  OdInt32 minIntensity() const;

  /** \details
    Returns the current value of maximal intensity.
  */
  OdInt32 maxIntensity() const;

  /** \details
    Sets minimal and maximal intensity.

    \param min [in] New minimal intensity.
    \param max [in] New maximal intensity.
    \returns eOk if the operation completed successfully, or an appropriate error code otherwise.
  */
  OdResult setMinMaxIntensity( OdInt32 min, OdInt32 max );

  /** \details
    Returns the behaviour that will be executed when intensity is out of range.

    \remarks
      Possible behaviours:
        <table>               
        <b>Name</b>             <b>Value</b>       <b>Description</b>
        kUseMinMaxColors        0                  UseMinMaxColors desc.
        kUseRGBScanColors       1                  UseRGBScanColors desc.
        kHidePoints             2                  HidePoints desc.
        </table>
  */
  DispOptionOutOfRange intensityOutOfRangeBehavior() const;

  /** \details
    Sets the behaviour that will be executed when intensity is out of range.

    \param displayOption [in] Enum value associated with the behaviour.
    \remarks
      Possible behaviours:
        <table>               
        <b>Name</b>             <b>Value</b>       <b>Description</b>
        kUseMinMaxColors        0                  UseMinMaxColors desc.
        kUseRGBScanColors       1                  UseRGBScanColors desc.
        kHidePoints             2                  HidePoints desc.
        </table>
  */
  void setIntensityOutOfRangeBehavior(DispOptionOutOfRange displayOption );

  /** \details
    Checks if the elevation is shown as gradient.

    \returns true if elevation is shows as gradient, false - otherwise.
  */
  bool showElevationAsGradient() const;

  /** \details
    Sets a falg whether to show elevation as gradient.

    \param bShowAsGradient [in] Flag value.
  */
  void setShowElevationAsGradient( bool bShowAsGradient );

  /** \details
    Returns the current minimal elevation.
  */
  double minElevation() const;

  /** \details
    Returns the current maximal elevation.
  */
  double maxElevation() const;

  /** \details
    Sets minimal and maximal elevation.

    \param min [in] New minimal elevation.
    \param max [in] New maximal elevation.
    \returns eOk if the operation completed successfully, or an appropriate error code otherwise.
  */
  OdResult setMinMaxElevation( double min, double max );

  /** \details
    Checks if elevation is applied to a fixed range.

    \returns true if elevation is applied to a fixed range, false - otherwise.
  */
  bool elevationApplyToFixedRange() const;

  /** \details
    Sets a flag whether to apply elevation to a fixed range.

    \param bFixedRange [in] Flag value.
  */
  void setElevationApplyToFixedRange( bool bFixedRange );

  /** \details
    Returns the behaviour that will be executed when elevation is out of range.

    \remarks
      Possible behaviours:
        <table>
        <b>Name</b>             <b>Value</b>       <b>Description</b>
        kUseMinMaxColors        0                  UseMinMaxColors desc.
        kUseRGBScanColors       1                  UseRGBScanColors desc.
        kHidePoints             2                  HidePoints desc.
        </table>
  */
  DispOptionOutOfRange elevationOutOfRangeBehavior() const;

  /** \details
    Sets the behaviour that will be executed when elevation is out of range.

    \param displayOption [in] Enum value associated with the behaviour.
    \remarks
      Possible behaviours:
        <table>
        <b>Name</b>             <b>Value</b>       <b>Description</b>
        kUseMinMaxColors        0                  UseMinMaxColors desc.
        kUseRGBScanColors       1                  UseRGBScanColors desc.
        kHidePoints             2                  HidePoints desc.
        </table>
  */
  void setElevationOutOfRangeBehavior(DispOptionOutOfRange displayOption );

  void getLimitBox(OdDbPointCloudExLimitBox& limitBox) const;
  OdResult setLimitBox(const OdDbPointCloudExLimitBox& limitBox);

  void resetLimitBox();

  void setHighlightLimitboxBoundary(bool val);

  OdPointCloudItem* findRegionItem(int regionId);
  OdPointCloudItem* findScanItem(const OdString& scanGuid);

  /** \details
   Returns the cropping boudary at the given index. Returns NULL if index is out of range of (0 ~ cropping count).
   \remarks
   Returns a cropping boundary by index, for editing. Requires that the AcDbPointCloudEx be open for writing.
   */
  OdDbPointCloudCrop* getPointCloudCropping( int index );

  const OdDbPointCloudCrop*  getPointCloudCroppingConst(int index) const;

  const OdPointCloudItemArray*    getPointCloudDataList() const;

  void setRegionVisibility(int regionId, bool bVisible);

  void setScanVisibility(const OdString& scanGuid, bool bVisible);

  void setAllScansVisibility(bool bVisible);

  void setAllRegionsVisibility(bool bVisible, bool includeUnassigned = false);

  void setAllScansVisibilityByRegion(int regionId, bool bVisible);

  bool getScanViewInfo(const OdString& scanGuid, OdGePoint3d& origin, OdDbExtents& extent) const;

  void resetScanRegionVisibility();

  void setAllScanHighlight(bool bHighlight);

  void setAllRegionHighlight(bool bHighlight, bool bIncludeUnassignedPoints = false);

  void applyGeoLocation(bool useDrawingGeo = false, const OdString& geoCS = OD_T(/*MSG0*/""));

  void updateGeoLocation();

  void clearGeoLocation();

  bool geolocate() const;

  enum PointCloudOSnapMode
  {
    kOsModePNod = 0,
    kOsModePNea = 1,
    kOsModePPer = 2,
    kOsModePEdgeNea = 3,
    kOsModePEdgePer = 4,
    kOsModePInt = 5,
    kOsModePCL = 6,
    kOsModePCorner = 7
  };

  OdResult getCustomOsnapInfo(PointCloudOSnapMode snapMode,
    const OdGePoint3d& pickPoint,
    const OdGePoint3d& lastPoint,
    const OdGeMatrix3d& viewXform,
    OdArray<OdGePoint3d>& snapPoints);

  OdResult getPointDataByPointCount(IOdDbPointCloudDataBuffer*& pointData, OdUInt32 pointCount,
    IOdDbPointCloudSpatialFilter* pSpatialFilter, IOdDbPointCloudAttributeFilter* pAttributeFilter, OdUInt32 dataTypes, OdUInt32 maxPointLimitation) const;

  OdResult traverseAllPointData(IOdDbPointCloudPointProcessor* processor, IOdDbPointCloudSpatialFilter* pSpatialFilter, OdUInt32 dataTypes, int LODLevel) const;

  OdResult  addSpatialFilter(IOdDbPointCloudSpatialFilter* pFilter);

  OdResult  removeSpatialFilter(IOdDbPointCloudSpatialFilter* pFilter);

  void  clearSpatialFilters();

  OdResult addAttributeFilter(IOdDbPointCloudAttributeFilter* pFilter);

  OdResult removeAttributeFilter(IOdDbPointCloudAttributeFilter* pFilter);

  void  clearAttributeFilters();

  bool  getPlaneOrPointAt(const OdGeMatrix3d & viewXform, const OdGePoint3d & pickPt, OdArray<OdGePoint3d> & points);

  bool  getPlaneBoundaryAt(const OdGeMatrix3d& viewXform, const OdGePoint3d& pickPt, OdGePoint3dArray& arrPlaneVertices);

  void * getQuery();

  void objectToWorldMatrix(OdGeMatrix3d& mat) const;

  OdResult getCandidatePlane(const class CPoint& pt, OdGePlane &result, double &distToEdge, double &objWidth, double &objHeight, void*& context) const;

  OdResult  getCylinderAt(const OdGeMatrix3d& viewXform, const OdGePoint3d& pickPt, OdGePoint3d& origin, OdGeVector3d& axis, double& height, double& radius);

  const OdDbPointCloudCropStateManager* cropStatesManagerConst() const;

  OdDbPointCloudCropStateManager* cropStatesManager();

  OdResult getMinDistPrecision(double& minDistPrecision) const;

  OdResult getPointDataByPrecision(IOdDbPointCloudDataBuffer*& pointData, double distPrecision, 
    IOdDbPointCloudSpatialFilter* pSpatialFilter = NULL,IOdDbPointCloudAttributeFilter* pAttributeFilter = NULL, 
    OdUInt32 dataTypes = 0, OdUInt32 maxPointLimitation = 1000000uLL) const;

  OdResult getEstimatedPointCountByPrecision(unsigned long long &pointCount, double distPrecision,
    IOdDbPointCloudSpatialFilter* pSpatialFilter = NULL, IOdDbPointCloudAttributeFilter* pAttributeFilter = NULL) const;

  OdResult  decomposeForSave(OdDb::DwgVersion ver, OdDbObject*& replaceObj, OdDbObjectId& replaceId, OdBool& exchangeXData);

  OdResult getCylinderAt(const OdGeMatrix3d& viewXform, const OdGePoint3d& pickPt, OdPointCloudExtractedCylinder& extractedCylinder);

  OdResult  detectPointBelonger(const OdGePoint3d& ptInWCS, OdString& scanGuid, OdUInt16& segmentIndex) const;

  OdResult  getPointDataBySegment(IOdDbPointCloudDataBuffer*& pointData, const OdString& scanGuid, 
    OdUInt16 nSegmentIndex, OdUInt32 nExpectedCount) const;

  OdResult  getPointDataByPointCount(IOdDbPointCloudDataBuffer*& pointData, OdUInt32 pointCount, const OdArray<OdString>& arrScanGuids,
    IOdDbPointCloudSpatialFilter* pSpatialFilter,IOdDbPointCloudAttributeFilter* pAttributeFilter, 
    OdUInt32 dataTypes, OdUInt32 maxPointLimitation) const;

  OdResult  traverseAllPointData(IOdDbPointCloudPointProcessor* processor, IOdDbPointCloudSpatialFilter* pSpatialFilter, 
    OdUInt32 dataTypes, int LODLevel, const OdArray<OdString>& arrScanGuids) const;
  /** \details
    Applies a transformation matrix to this XData object. Only available if transformation is uniform.

    \param xform [in] Transformation matrix to be applied.
    \returns eOk if the operation completed successfully, or an appropriate error code otherwise
  */
  OdResult subTransformBy( const OdGeMatrix3d& xform );

  OdBool subWorldDraw( OdGiWorldDraw* pWd );

  void subViewportDraw( OdGiViewportDraw* pVd );

  /** \details
    Retrieves geometrical extents affected by current transformation.

    \param extents [out] Geometrical extents.
    \returns Returns eOk.
  */
  virtual OdResult subGetGeomExtents(OdDbExtents& ext) const;

  // File IO

  /** \details
    Reads the .dwg file data of this object.

    \param pFiler [in]  Filer object from which data are read.
    \returns
      Returns the filer status.
      This function is called by dwgIn() to allow the object to read its data.
      When overriding this function:
        1)  Call assertWriteEnabled().
        2)  Call the parent class's dwgInFields(pFiler).
        3)  If it returns eOK, continue; otherwise return whatever the parent's dwgInFields(pFiler) returned.
        4)  Call the OdDbDwgFiler(pFiler) methods to read each of the object's data items in the order they were written.
        5)  Return pFiler->filerStatus().
  */
  virtual OdResult  dwgInFields( OdDbDwgFiler * );

  /** \details
    Writes the .dwg file data of this object.

    \param pFiler [in]  Pointer to the filer to which data are written.
    \remarks
      This function is called by dwgIn() to allow the object to write its data.
      When overriding this function:
        1)  Call assertReadEnabled().
        2)  Call the parent class's dwgOutFields(pFiler).
        3)  Call the OdDbDwgFiler(pFiler) methods to write each of the object's data items in the order they were written.
  */
  virtual OdResult  dwgOutFields( OdDbDwgFiler * ) const;

  /** \details
    Reads the DXF data of this object.

    \param pFiler [in]  Pointer to the filer from which data are read.
    \returns
      Returns the filer status.
      This function is called by dxfIn() to allow the object to read its data.
      When overriding this function:
        1)  Call assertWriteEnabled().
        2)  Call the parent class's dwgInFields(pFiler).
        3)  If it returns eOK, continue; otherwise return whatever the parent's dxfInFields(pFiler) returned.
        4)  Call the OdDbDxfFiler(pFiler) methods to read each of the object's data items in the order they were written.
        5)  Return pFiler->filerStatus().
  */
  virtual OdResult  dxfInFields( OdDbDxfFiler * );

  /** \details
    Writes the DXF data of this object.

    \param pFiler [in]  Pointer to the filer to which data are to be written.
    \remarks
      This function is called by dxfOut() to allow the object to write its data.
      When overriding this function:
        1)  Call assertReadEnabled().
        2)  Call the parent class's dxfOutFields(pFiler).
        4)  Use pFiler to call the OdDbDxfFiler methods to write each of the object's data items in the order they were written.
  */
  virtual OdResult  dxfOutFields( OdDbDxfFiler * ) const;

};

typedef OdSmartPtr<OdDbPointCloudEx> OdDbPointCloudExPtr;

/** \details
  This method performs the whole point cloud entity creation routine: creates the OdDbPointCloudEx entity, appends it to the database,
  applies specified attributes, creates the OdDbPointCloudDefEx object (if needed), restores or creates new links to the OdDbPointCloudDefEx object, adds reactors.

  \param pBlockToAdd [in]  Pointer to the block table record to add the point cloud entity to.
  \param newPointCloud [out]  Recieves a pointer to the created point cloud entity.
  \param sourceFile [in]  Source file path.
  \param location [in]  Location of the entity.
  \param scale [in]  Scale factor.
  \param rotation [in]  Rotation angle.
  \param vAxis [in]  Rotation axis.
  \returns
  Returns eOk.
*/
DBPOINTCLOUDOBJ_EXPORT OdResult oddbCreatePointCloudExEntity(
  OdDbBlockTableRecord* pBlockToAdd,
  OdDbPointCloudExPtr& newPointCloud,  
  const OdString& sourceFile,
  const OdGePoint3d& location = OdGePoint3d::kOrigin,
  double             scale = 1.0,
  double             rotation = 0.0,
  const OdGeVector3d& vAxis = OdGeVector3d::kZAxis
);

#include "TD_PackPop.h"


#endif //_OD_DB_POINTCLOUDEX_
