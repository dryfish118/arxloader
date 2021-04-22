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




#ifndef __DBRASTERIMAGEDEF_H
#define __DBRASTERIMAGEDEF_H

#include "TD_PackPush.h"

// Forward declarations
//

class OdDbDictionary;

#include "DbObjectReactor.h"
#include "DbObject.h"
#include "Gi/GiRasterImage.h"
#include "Ge/GeVector2d.h"
#include "RxObjectImpl.h"
#include "DbDictionary.h"
#include "DbSymUtl.h"
#include "Ge/GePoint2dArray.h"

#ifdef ISM_EXPORTS
#define ISM_EXPORT           OD_TOOLKIT_EXPORT
#define ISM_EXPORT_STATIC    OD_STATIC_EXPORT
#else
#define ISM_EXPORT           OD_TOOLKIT_IMPORT
#define ISM_EXPORT_STATIC    OD_STATIC_IMPORT
#endif

class RasterImageDefImp;
struct OdGiRequestScanLines;
struct OdGiSentScanLines;

namespace Otil
{
  class Image;
  class FileReadDescriptor;
}

enum ClassVersion
{
  kVersion1 = 0,    // S039 Oct 21, 1996
  kVersion2 = 1,    // S052 Jan 16, 1996
  kVersion3 = 2     // S061 Mar 21, 1997
};

/** \details
    This virtual base class defines raster image definition objects in an OdDbDatabase instance.
    Corresponding C++ library: ISM
   

    \remarks
    Raster image definitions (OdDbRasterImageDef objects) work with raster image (OdDbRasterImage) entities
    in much the same way that block table records (OdDbBlockTableRecord objects) work with block references
    (OdDbBlockReference entities).

    <group OdDb_Classes>
*/
class ISM_EXPORT OdDbRasterImageDef : public OdDbObject
{
public:
  ODDB_DECLARE_MEMBERS(OdDbRasterImageDef);

  /** \details
    This enumeration represents measurement units.
  */
  enum Units
  {
    /** No measurement units are used. */
    kNone = 0,
    /** Millimeters are used. */
    kMillimeter,
    /** Centimeters are used. */
    kCentimeter,
    /** Meters are used. */
    kMeter,
    /** Kilometers are used. */
    kKilometer,
    /** Inches are used. */
    kInch,
    /** Foots are used. */
    kFoot,
    /** Yards are used. */
    kYard,
    /** Miles are used. */
    kMile,
    /** Microinches are used. */
    kMicroinches,
    /** Mils (thousandths of an inch) are used. */
    kMils,
    /** Angstroms (10^-10 of a meter or ten-billionths of a meter) are used. */
    kAngstroms,
    /** Nanometers are used. */
    kNanometers,
    /** Microns are used. */
    kMicrons,
    /** Decimeters are used. */
    kDecimeters,
    /** Dekameters (10 meters) are used. */
    kDekameters,
    /** Hectometers (10^2 meters) are used. */
    kHectometers,
    /** Gigameters (10^9 meters) are used. */
    kGigameters,
    /** Astronominal units (149597870700 meters) are used. */
    kAstronomical,
    /** Light years (9460730472580800 meters) are used. */
    kLightYears,
    /** Parsecs (approx 3.261563777 light years) are used. */
    kParsecs
  };

  /** \details
    Returns number of millimeters in a given unit.

    \param units [in] Input measurement unit.

    \returns Number of millimeters in the given measurement unit.
  */
  static double millimetersInUnit(Units units)
  {
    switch (units)
    {
    case kNone:
      throw OdError(eInvalidInput);
    case kMillimeter:
      return 1.0;
    case kCentimeter:
      return 10.0;
    case kMeter:
      return 1000.0;
    case kKilometer:
      return 1000000.0;
    case kInch:
      return 25.4;
    case kFoot:
      return 25.4 * 12.0;
    case kYard:
      return 25.4 * 12.0 * 3.;
    case kMile:
      return 25.4 * 12.0 * 3. * 1760.;
    case kMicroinches:
      return 25.4 * 0.000001;
    case kMils:
      return 25.4 * 0.001;
    case kAngstroms:
      return 1000.0 * 1.e-10;
    case kNanometers:
      return 0.000001;
    case kMicrons:
      return 0.001;
    case kDecimeters:
      return 100.0;
    case kDekameters:
      return 10000.0;
    case kHectometers:
      return 100000.0;
    case kGigameters:
      return 1000. * 1.e9;
    case kAstronomical:
      return 1000. * 149597870700.;   // Approx. the length of the semi-major axis of the Earth's elliptical orbit around the Sun
    case kLightYears:
      return 1000. * 9460730472580800.;
    case kParsecs:
      return 1000. * 30856775814671900.;
    }
    ODA_ASSERT_ONCE(!"Unknown unit");
    return 1.0;
  }

  OdDbRasterImageDef();

  virtual  ~OdDbRasterImageDef();

  RasterImageDefImp*          ptrImp() const;

  RasterImageDefImp* setPtrImp(RasterImageDefImp* pImp);


  OdResult subErase(
    bool erasing);
  virtual OdResult subHandOverTo (
    OdDbObject* pNewObject);
  OdResult subClose();

  OdResult dwgInFields(
    OdDbDwgFiler* pFiler);

  OdResult dwgOutFields(
    OdDbDwgFiler* pFiler) const;

  OdResult dxfInFields(
    OdDbDxfFiler* pFiler);

  OdResult dxfOutFields(
    OdDbDxfFiler* pFiler) const;

  /** \details
    Sets the name of the source file containing the raster image for this raster image definition object (DXF 1).
    
    \param pathName [in]  Path name.
  */
  virtual OdResult setSourceFileName(const OdChar* pPathName);

  /** \details
    Returns the name of the source file containing the raster image for this raster image definition object (DXF 1).
    
    \remarks
    This function calls searchForActivePath() to determine the active path.
    
    \remarks
    This RasterImageDef object must be open for reading.
  */
  virtual const OdChar* sourceFileName() const;

  virtual const OdChar *searchForActivePath();
  /** \details
    Loads the source image file for this raster image definition object.
    
    \param modifyDatabase [in]  If and only if true, an undo recording will be done for this object.

    \remarks
    This function calls searchForActivePath() to determine the active path.
    
    If the image file is currently loaded, the file will not be read.
    
    "Lazy loading" implies that the image file will not be loaded until it is required.
    
  */
  virtual OdResult load();
  OdResult load(bool modifyDatabase);

  virtual OdGiImageOrg organization() const;

  /** \details
    Unloads the image for this raster image definition object. 
    
    \param modifyDatabase [in]  If and only if true, an undo recording will be done for this object.

    \remarks
    This RasterImageDef object must be open for writing.

  */
  virtual OdResult unload(
    bool modifyDatabase = true);

  /** \details
    Returns true if and only if the image file for this raster image definition object is loaded (DXF 280).
  */
  virtual bool isLoaded() const;

  /** \details
    Returns the XY pixel size of the image for this raster image definition (DXF 10).
  */
  virtual OdGeVector2d size() const;


  /** \details
    Returns the default physical pixel size, in mm/pixel, of the image for this raster image definition object (DXF 10).
    
    \remarks
    If the image has no default pixel size, 
    this function returns 1.0/(image width in pixels) for XY resolutions.
  */
  virtual OdGeVector2d resolutionMMPerPixel() const;

  /** \details
    Sets the default physical pixel size, in mm/pixel, of the image for this raster image definition object (DXF 10).
    
    \remarks
    Loading the actual image file resets this value if the image has a default pixel size.
  */
  virtual OdResult setResolutionMMPerPixel(const OdGeVector2d&);

  /** \details
    Returns the number of raster images associated with this raster image definition object.
    
    \param pbLocked [in]  If this value is not NULL, the value 'true' will be set at the pointer.
  */
  virtual int entityCount(bool* pbLocked = NULL) const;
  
  /** \details
    Causes all raster images associated with this raster image definition object to be redrawn.
    
    \remarks Associated raster images will be redrawn after any modifications to this raster image 
	definition object (e.g., load, unload, etc.).
  */
  virtual void updateEntities() const;

  /** \details
    Returns the resolution units for the image for this raster image definition object (DXF 281).
  */
  virtual Units resolutionUnits() const;

  /** \details
    Sets the resolution units for the image for this raster image definition object (DXF 281).

    \remarks
    Loading the actual image file resets this value.
  */
  virtual void setResolutionUnits(enum Units);

  /** \details
    Returns the OdGiRasterImage object associated with this RasterImageDef object. 
  */
  virtual OdGiRasterImagePtr image(bool load = true);

  /** \details
    Creates an image from the specified OdGiRasterImage object.
    \param pImage [in]  Pointer to the RasterImage object.
    \param modifyDatabase [in]  If and only if true, marks the associated OdDbDatabase instance as modified.
    
    \remarks
    isLoaded() returns false if pImage is NULL. Otherwise, it returns true.
  */
  virtual void setImage(OdGiRasterImage* pImage, bool modifyDatabase = true);

  virtual OdResult setImage(const Otil::Image* pImage,
    const Otil::FileReadDescriptor* pFileDesc,
    bool modifyDatabase = true);

  OdResult forceImageFileClosed(OdBool modifyDatabase);

  /** \details
    Creates an image dictionary, if it is not already present, in the specified OdDbDatabase instance.

    \param pDb [in]  Pointer to the database.
    
    \returns
    Returns the object ID of the image dictionary.
  */
  static OdDbObjectId createImageDictionary(OdDbDatabase* pDb);
  static OdResult createImageDictionary(OdDbDatabase* pDb, OdDbObjectId& dictId);

  /** \details
    Returns the object ID of the image dictionary in the specified OdDbDatabase instance.
    \param pDb [in]  Pointer to the database.  
  */
  static OdDbObjectId imageDictionary(OdDbDatabase* pDb);

  enum 
  { 
    kMaxSuggestNameSize = 2049 
  };

  /** \details
    Modifies the original image filename to return a new
    image name suitable for an image dictionary.
    \param pImageDictionary [in]  Pointer to the image dictionary.
    \param strFilePath [in]  New image file name. 
    \param nMaxLength [in]  Max length of the name returned.
  */
  static OdString suggestName(const OdDbDictionary* pImageDictionary,
                  const OdString& strFilePath, int nMaxLength = kMaxSuggestNameSize);
  
  /** \details
    Returns the actual file name of the raster image associated with this raster image definition object.  
  */
  virtual const OdChar *activeFileName() const;

  /** \details
    Sets the actual file name of the raster image associated with this raster image definition object.

    \param pPathName [in] Input actual file name.
  */
  virtual OdResult setActiveFileName(const OdChar* pPathName);

  virtual int colorDepth() const;
  /** DOM-IGNORE-BEGIN */
  /*   comment this out for a while

  int colorDepth() const;*/

  virtual OdGiSentScanLines* makeScanLines(
    const OdGiRequestScanLines* pReq,
    const OdGeMatrix2d& pixToScreen,
    OdGePoint2dArray* pActiveClipBndy = 0, // Data will be modified!
    OdBool draftQuality = false,
    OdBool isTransparent = false,
    const double brightness = 50.0,
    const double contrast = 50.0,
    const double fade = 0.0
    ) const;

  //OdString searchForActivePath();

  virtual OdResult embed();

  virtual OdBool isEmbedded() const;

  virtual OdResult setUndoStoreSize(unsigned int maxImages = 10);

  virtual unsigned int undoStoreSize() const;

  virtual OdResult setImageModified(OdBool modified);

  virtual OdBool imageModified() const;

  virtual IGcReadStream*      getReadStream();

  static OdResult suggestName(
    OdDbDictionary* pImageDictionary,
    const OdChar* pNewImagePathName,
    OdChar* newImageName,
    size_t nSize);

  /*OdString fileType() const;
  */

  virtual OdResult loadThumbnail(OdUInt16& maxWidth, OdUInt16& maxHeight,
    OdUInt8* pPalette = 0, int nPaletteEntries = 0);

  virtual OdResult unloadThumbnail();

  virtual void* createThumbnailBitmap(BITMAPINFO*& pBitmapInfo,
    OdUInt8 brightness = 50, OdUInt8 contrast = 50, OdUInt8 fade = 0);

  virtual Otil::Image* imageCopy(OdBool bForceImageLoad = true) const;

  virtual Otil::FileReadDescriptor* fileDescCopy() const;

  virtual OdResult openImage(Otil::Image*& pImage);
  /*
  void getScanLines(OdGiBitmap& bitmap,
    double brightness = 50.0,
    double contrast = 50.0,
    double fade = 0.0) const;
  void closeImage();

  */
  /** DOM-IGNORE-END */
  /** \details
    Returns the version of the raster image associated with this raster image definition object.  
  */
  static ClassVersion classVersion();

  virtual const OdChar* fileType() const;

  virtual OdResult closeImage();

};




/** \details
    This class implements raster image definition reactor objects in an OdDbDatabase instance.
    
    
    \remarks
    Raster image definition reactor (OdDbRasterImageDefReactor) objects are used 
    to notify raster image (OdDbRasterImage) objects 
    of changes to their associated raster image definition (OdDbRasterImage) objects.
    
    Modifications of image definition objects redraw their dependent raster image entities. 
    Deletion of image definition objects delete their dependent raster image entities.

    <group OdDb_Classes>
*/
class ISM_EXPORT OdDbRasterImageDefReactor : public OdDbObject
{
public:
  ODDB_DECLARE_MEMBERS(OdDbRasterImageDefReactor);

  OdDbRasterImageDefReactor();

  OdResult dwgInFields(
    OdDbDwgFiler* pFiler);

  OdResult dwgOutFields(
    OdDbDwgFiler* pFiler) const;

  OdResult dxfInFields(
    OdDbDxfFiler* pFiler);

  OdResult dxfOutFields(
    OdDbDxfFiler* pFiler) const;
  
  /** \details
    Notification function called whenever an object has been erased or unerased.  

    \param pObject  [in]  Pointer to the object that was erased/unerased.  	
    \param erasing  [in]  True if and only if this object is being erased. 

    \remarks The default implementation of this function does nothing. This function can be overridden in custom classes.
  */
  void erased(
    const OdDbObject* pObject, 
    bool erasing = true);

  /** \details
    Notification function called whenever an object is opened OdDb::kForWrite, a function has been called that could modify the content of this object, and this object is now being closed.

    \param pObject  [in]  Pointer to the object that is being closed after being modified.  	

    \remarks The default implementation of this function does nothing. This function can be overridden in custom classes.
  */
  void modified(
    const OdDbObject* pObject);

  enum DeleteImageEvent
  {
    kUnload = 1,
    kErase = 2
  };
  /** \details
    Controls notifications of OdDbRasterImage object events.
    
    \param enable [in]  If and only if true, enables notifications.
  */
  static void setEnable(
    bool enable);

  /** \details
    Notification function called whenever an OdDbRasterImageDef object is about to be unloaded or erased.
    
    \param pImageDef [in]  Pointer to the OdDbRasterImageDef object sending this notification.
    \param event [in]  Event triggering the notification.
    \param cancelAllowed [in]  True to enable user cancellation, false to disable.
    
    \returns
    Returns true if and only if not cancelled. 
    \remarks
    Event must be one of the following:
    
    <table>
    Name      Value
    kUnload   1
    kErase    2
    </table>
    
    
    \remarks
    Use imageModified() to determine if the image definition has been modified.
  */
  virtual bool onDeleteImage( 
    const OdDbRasterImageDef* pImageDef,
    DeleteImageEvent event,
    bool cancelAllowed);
  

  virtual bool onDeleteImage(
    const OdDbRasterImageDef* pImageDef,
    const Otil::Image* pImage,
    DeleteImageEvent event,
    bool cancelAllowed);
  /** \details
    Returns the version of the raster image associated with this object.  
  */
  static ClassVersion classVersion();
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbRasterImageDefReactor object pointers.
*/
typedef OdSmartPtr<OdDbRasterImageDefReactor> OdDbRasterImageDefReactorPtr;

/** \details
    This class implements raster image definition transient reactor objects in an OdDbDatabase instance.
    Corresponding C++ library: TD_Db
    <group OdDb_Classes>
*/
class ISM_EXPORT OdDbRasterImageDefTransReactor : public OdDbObjectReactor
{
protected:
  OdDbRasterImageDefTransReactor() {}
public:
  ODRX_DECLARE_MEMBERS(OdDbRasterImageDefTransReactor);

  /** \details
    Notification function called whenever an OdDbRasterImageDef object is about to be unloaded or erased.
    
    \param pImageDef [in]  Pointer to the OdDbRasterImageDef object sending this notification.
    \param event [in]  Event triggering the notification.
    \param cancelAllowed [in]  True to enable user cancellation, false to disable.
    
    \returns
    Returns true if and only if not cancelled. 
    \remarks
    Event must be one of the following:
    
    <table>
    Name                                 Value
    OdDbRasterImageDefReactor::kUnload   1
    OdDbRasterImageDefReactor::kErase    2
    </table>
  */
  virtual OdBool onDeleteImage(const OdDbRasterImageDef* pImageDef,
    const Otil::Image* pImage,
    OdDbRasterImageDefReactor::DeleteImageEvent event,
    OdBool cancelAllowed) = 0;
};

#if 1 /*!DOM*/


/** \details
  <group OdDb_Classes>
*/
class ISM_EXPORT OdDbRasterImageDefFileAccessReactor : public OdDbObjectReactor
{
protected:
  OdDbRasterImageDefFileAccessReactor() {}
public:
  ODRX_DECLARE_MEMBERS(OdDbRasterImageDefFileAccessReactor);

  /** \details
    Function is called whenever a new raster image is about to attach to the current drawing.

    \param OdDbRasterImageDef  [in]  Input pointer to the affected RasterImageDef object.
    \param pPath  [in]  Input raster image file name.
  */
  virtual void onAttach(const OdDbRasterImageDef*, const OdChar* pPath) = 0;

  /** \details
    Function is called whenever a new raster image is about to detach from the current drawing.

    \param OdDbRasterImageDef  [in]  Input pointer to the affected RasterImageDef object.
    \param pPath  [in]  Input raster image file name.
  */
  virtual void onDetach(const OdDbRasterImageDef*, const OdChar* pPath) = 0;

  /** \details
    Function is called whenever a new raster image is about to open in the current drawing.

    \param OdDbRasterImageDef  [in]  Input pointer to the affected RasterImageDef object.
    \param pPath  [in]  Input saved raster image file name.
    \param pActivePath  [in]  Input active raster image file name.
    \param replacePath  [in]  Is set to 'true' if replacementPath should be used instead of pActivePath.
    \param replacementPath  [in]  Input replacement raster image file name.
  */
  virtual bool onOpen(const OdDbRasterImageDef*, const OdChar* pPath,
    const OdChar* pActivePath, bool& replacePath, OdChar*& replacementPath) = 0;

  /** \details
    Function is called before the raster image active path is changed.

    \param OdDbRasterImageDef  [in]  Input pointer to the affected RasterImageDef object.
    \param pPath  [in]  Input saved raster image file name.
    \param pActivePath  [in]  Input active raster image file name.
    \param replacePath  [in]  Is set to 'true' if replacementPath should be used instead of pActivePath.
    \param replacementPath  [in]  Input replacement raster image file name.
  */
  virtual bool onPathChange(const OdDbRasterImageDef*,
    const OdChar* pPath, const OdChar* pActivePath,
    bool& replacePath, OdChar*& replacementPath) = 0;

  /** \details
    Function is called whenever a raster image is about to be closed.

    \param OdDbRasterImageDef  [in]  Input pointer to the affected RasterImageDef object.
    \param pPath  [in]  Input saved raster image file name.
  */
  virtual void onClose(const OdDbRasterImageDef*, const OdChar* pPath) = 0;

  /** \details
    Function is called whenever a raster image browse dialog is about to be posted.

    \param OdDbRasterImageDef  [in]  Input pointer to the affected RasterImageDef object.
    \param pCaption  [in]  Input dialog box caption that will be posted.
    \param pFileExtensions  [in]  Input list of the file extensions.
  */
  virtual void onDialog(OdDbRasterImageDef*,
    const OdChar* pCaption, const OdChar* pFileExtensions) = 0;
};

#endif

// next 3 functions are static...
inline OdDbObjectId OdDbRasterImageDef::createImageDictionary(OdDbDatabase* pDb) {
  if (!pDb)
    throw OdError(eNoDatabase);
  OdDbDictionaryPtr pRootDict = pDb->getNamedObjectsDictionaryId().safeOpenObject(OdDb::kForWrite);
  OdDbObjectId ImgDictId = pRootDict->getAt(ACAD_IMAGE_DICT);
  if (ImgDictId.isNull()) {
    OdDbObjectPtr pImgDict = OdDbDictionary::createObject();
    ImgDictId = pRootDict->setAt(ACAD_IMAGE_DICT, pImgDict);
  }
  return ImgDictId;
}

inline OdDbObjectId OdDbRasterImageDef::imageDictionary(OdDbDatabase* pDb) {
  if (!pDb)
    throw OdError(eNoDatabase);
  OdDbDictionaryPtr pDict = pDb->getNamedObjectsDictionaryId().safeOpenObject();
  return pDict->getAt(ACAD_IMAGE_DICT);
}

inline OdString OdDbRasterImageDef::suggestName(const OdDbDictionary* pDic, const OdString& strPath, int nMaxLength) {
  return pDic->suggestName(strPath, nMaxLength);
}

/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbRasterImageDef object pointers.
*/
typedef OdSmartPtr<OdDbRasterImageDef> OdDbRasterImageDefPtr;

#include "TD_PackPop.h"

#endif // __DBRASTERIMAGEDEF_H

