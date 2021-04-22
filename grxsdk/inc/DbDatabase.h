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




#ifndef _ODDBDATABASE_INCLUDED_
#define _ODDBDATABASE_INCLUDED_

#include "TD_PackPush.h"

#include "RxObject.h"
#include "DbObjectId.h"
#include "RxObjectImpl.h"
#include "OdString.h"
#include "DbDate.h"
#include "OdCodePage.h"
#include "OdToolKit.h"
#include "DbObject.h"
#include "CmColor.h"
#include "DbSecurity.h"
#include "DbSystemServices.h"
#include "ViewportDefs.h"
#include "DbAnnotationScale.h"
#include "DbDatabaseReactor.h"
#include "DbDataLink.h"
#include "gdsdef.h"


class OdDbObject;

class OdDbSymbolTable;
class OdDbBlockTable;
class OdDbTextStyleTable;
class OdDbLinetypeTable;
class OdDbLayerTable;
class OdDbViewTable;
class OdDbUCSTable;
class OdDbUCSTable;
class OdDbViewportTable;
class OdDbRegAppTable;
class OdDbDimStyleTable;
class OdDbDimStyleTableRecord;
class OdDbBlockTableRecord;
class OdDbTextStyleTableRecord;
class OdDbRegAppTableRecord;
class OdDbLinetypeTableRecord;
class OdDbHostAppServices;
class OdDbLayout;
class OdDbLayoutManagerReactor;
class OdGsView;
class OdGsDevice;
class OdGsDCRect;

class OdDbDictionary;
class OdDbDictionaryWithDefault;
class OdDbFiler;
class OdDbIdMapping;
class OdDbDatabaseReactor;
class OdDbSpatialFilter;
class OdDbLayerFilter;
class OdDbAuditInfo;
class OdDbUndoController;
class OdDbTransactionReactor;
class OdDbTransactionManager;
class OdDbEntity;

class OdGePoint2d;
class OdGePoint3d;
class OdGeMatrix3d;
class OdGeVector3d;
class OdDbDwgFiler;

class OdGsModel;

class OdStreamBuf;
class OdThumbnailImage;

class OdDbDatabaseImpl;
class OdResBuf;
class OdDbUnitsFormatter;
class OdDbLayerStateManager;
class OdDwgFileHandle;
class IGcReadStream;
class OdDbObjectIdGraph;
class OdDbHistoryManager;
class OdDbSectionManager;

namespace Otil
{
  class Image; // for Atil::Image
}

/** \details
  This template class is a specialization of the OdSmartPtr class for OdResBuf object pointers.
*/
typedef OdSmartPtr<OdResBuf> OdResBufPtr;
/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbDictionary object pointers.
*/
typedef OdSmartPtr<OdDbDictionary> OdDbDictionaryPtr;
/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbDictionaryWithDefault object pointers.
*/
typedef OdSmartPtr<OdDbDictionaryWithDefault> OdDbDictionaryWithDefaultPtr;
/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbSymbolTable object pointers.
*/
typedef OdSmartPtr<OdDbSymbolTable> OdDbSymbolTablePtr;
/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbBlockTable object pointers.
*/
typedef OdSmartPtr<OdDbBlockTable> OdDbBlockTablePtr;
/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbLayerTable object pointers.
*/
typedef OdSmartPtr<OdDbLayerTable> OdDbLayerTablePtr;
/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbTextStyleTable object pointers.
*/
typedef OdSmartPtr<OdDbTextStyleTable> OdDbTextStyleTablePtr;
/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbViewTable object pointers.
*/
typedef OdSmartPtr<OdDbViewTable> OdDbViewTablePtr;
/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbUCSTable object pointers.
*/
typedef OdSmartPtr<OdDbUCSTable> OdDbUCSTablePtr;
/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbViewportTable object pointers.
*/
typedef OdSmartPtr<OdDbViewportTable> OdDbViewportTablePtr;
/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbRegAppTable object pointers.
*/
typedef OdSmartPtr<OdDbRegAppTable> OdDbRegAppTablePtr;
/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbDimStyleTable object pointers.
*/
typedef OdSmartPtr<OdDbDimStyleTable> OdDbDimStyleTablePtr;
/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbLinetypeTable object pointers.
*/
typedef OdSmartPtr<OdDbLinetypeTable> OdDbLinetypeTablePtr;
/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbBlockTableRecord object pointers.
*/
typedef OdSmartPtr<OdDbBlockTableRecord> OdDbBlockTableRecordPtr;
/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbDimStyleTableRecord object pointers.
*/
typedef OdSmartPtr<OdDbDimStyleTableRecord> OdDbDimStyleTableRecordPtr;
/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbTextStyleTableRecord object pointers.
*/
typedef OdSmartPtr<OdDbTextStyleTableRecord> OdDbTextStyleTableRecordPtr;
/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbRegAppTableRecord object pointers.
*/
typedef OdSmartPtr<OdDbRegAppTableRecord> OdDbRegAppTableRecordPtr;
/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbDimStyleTableRecord object pointers.
*/
typedef OdSmartPtr<OdDbDimStyleTableRecord> OdDbDimStyleTableRecordPtr;
/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbLinetypeTableRecord object pointers.
*/
typedef OdSmartPtr<OdDbLinetypeTableRecord> OdDbLinetypeTableRecordPtr;

class OdSecurityParams;

/** \details
  This template class is a specialization of the OdSmartPtr class for OdSecurityParams object pointers.
*/
typedef OdSmartPtr<OdSecurityParams> OdSecurityParamsPtr;

class OdFileDependencyManager;

/** \details
  This template class is a specialization of the OdSmartPtr class for OdFileDependencyManager object pointers.
*/
typedef OdSmartPtr<OdFileDependencyManager> OdFileDependencyManagerPtr;

class OdDbObjectContextManager;

/** \details
This template class is a specialization of the OdSmartPtr class for OdDbObjectContextManager object pointers.
*/
typedef OdSmartPtr<OdDbObjectContextManager> OdDbObjectContextManagerPtr;

/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbDatabase object pointers.
*/
typedef OdSmartPtr<OdDbDatabase> OdDbDatabasePtr;

class OdDbUndoController;
typedef OdSmartPtr<OdDbUndoController> OdDbUndoControllerPtr;
/** \details
    The namespace contains common enumration declarations used for drawing database options.
    <group TD_Namespaces>
*/
namespace OdDb
{

  /** \details
    Describes how duplicates of a linetype should be processed.
  */
  enum DuplicateLinetypeLoading
  {
    kDltNotApplicable = 0, //!< Not Applicable.
    kDltIgnore        = 1, //!< Ignore duplicate Linetypes.
    kDltReplace       = 2  //!< Replace duplicate Linetypes.
  };

  /** \details 
    Determines how proxy images should be shown.
  */
  enum ProxyImage
  {
    kProxyNotShow	    = 0, //!< Proxy images are not shown.
    kProxyShow	      	= 1, //!< Proxy images are shown.
    kProxyBoundingBox	= 2  //!< Proxy images are shown as a bounding box.
  };

  /** \details 
	Represents the fillet trimming mode.
  */
  enum FilletTrimMode   
  { 
    kTrimNone      = 0, //!< No fillet is trimmed.
    kTrimFirst     = 1, //!< The first fillet is trimmed.
    kTrimSecond    = 2, //!< The second fillet is trimmed.
    kTrimBoth      = 3  //!< Both fillets are trimmed.
  };

    enum ImplicitPointType 
    {
        kStartImplicit = 0,
        kEndImplicit,
        kMidImplicit,
        kCenterImplicit,
        kDefineImplicit
    };

  /** \details
    Determines what file encoding algorithm is used for functions that write data to a text file.
  */
  enum TextFileEncoding
  {
    kTextFileEncodingDefault = 0,   //!< Chooses the current system encoding automatically.
    kTextFileEncodingANSI = 1,      //!< Forces ANSI character set encoding text writing.
    kTextFileEncodingUTF8 = 11,     //!< Uses UTF8 encoding for file writing.
    kTextFileEncodingUTF16 = 21,    //!< Chooses UTF16 endian automatically.
    kTextFileEncodingUTF16LE = 22,  //!< UTF16 LittleEndian.
    kTextFileEncodingUTF16BE = 23,  //!< UTF16 BigEndian.
    kTextFileEncodingUTF32 = 31,    //!< Chooses UTF32 endian automatically.
    kTextFileEncodingUTF32LE = 32,  //!< UTF32 LittleEndian.
    kTextFileEncodingUTF32BE = 33   //!< UTF32 BigEndian.
  };

  /** \details 
    Represents the system layer types.
  */
  enum LayerAdskType
  {
    kLayerSystemLights = 0, //!< System lights layer type.
    kLayerConstraints  = 1  //!< System constraints layer type.
  };

  enum IndexingModeFlags {
    kNoIndexing             = 0,
    kUpdateBlockIndexOnSave = 1,
    kUseBlockChangeIterator = 2,  // partial index update
    kUseAll                 = kUpdateBlockIndexOnSave | kUseBlockChangeIterator
  };
}

/** \details
    This class represents a complete drawing file.


    <group OdDb_Classes>
*/
class TOOLKIT_EXPORT OdDbDatabase : public OdDbObject
{
public:
  OdDbDatabase(bool buildDefaultDrawing = true, bool noDocument = false);

public:

  /** \details 
    Returns the GUID of the database class. 
  */
  OdResult subGetClassID(
    CLSID* pClsid) const;

  ODRX_DECLARE_MEMBERS(OdDbDatabase);

  void addRef();

  void release();

  /** \details
    Returns the OdDbHostAppServices object associated with this database object.
  */
  OdDbHostAppServices* appServices() const;

  /** \details
    Adds the default set of objects and settings to this database object.

    \remarks
    This includes the ModelSpace and PaperSpace blocks, default table entries, system variable settings, etc.

    \remarks
    Measurement must be one the following:

    <table>
    Name              Value
    OdDb::kEnglish    0
    OdDb::kMetric     1
    </table>

    \param measurement [in]  Units of measurement.
  */
  void initialize(
    OdDb::MeasurementValue measurement = OdDb::kEnglish);

  /** \details 
    Destroys a database instance. 
  */
  virtual ~OdDbDatabase();

  /** \details
    Adds an object to this database object, and returns its Object ID.

    \param pObject  [in]  Pointer to the object.
    \param ownerId  [in]  Object ID of the owner of pObject.
    \param handle   [in]  Handle for pObject.

    \remarks
    A unique handle will be generated if a handle is not supplied or is 0.

  */
  OdDbObjectId addOdDbObject(
    OdDbObject* pObject,
    OdDbObjectId ownerId,
    OdDbHandle handle = OdDbHandle());
	
	OdResult addOdDbObject(OdDbObject*    pObj);
	OdResult addOdDbObject(OdDbObjectId&  objId,OdDbObject*    pObj);

  static OdResult markObjectNonPersistent(OdDbObjectId id, bool value);
  static bool isObjectNonPersistent(OdDbObjectId id);

  /** \details
    Adds the specified name to the APPID table of this database object.

    \param regAppName [in]  Application name.

    \remarks
    True if and only if the specified name had not been, and is now, in the APPID table.
  */
  bool newRegApp(
    const OdString& regAppName);


  OdResult getBlockTable(OdDbSymbolTable*&    pTable, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getLayerTable(OdDbSymbolTable*&    pTable, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getTextStyleTable(OdDbSymbolTable*&    pTable, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getLinetypeTable(OdDbSymbolTable*&    pTable, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getViewTable(OdDbSymbolTable*&    pTable, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getUCSTable(OdDbSymbolTable*&    pTable, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getViewportTable(OdDbSymbolTable*&    pTable, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getRegAppTable(OdDbSymbolTable*&    pTable, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getDimStyleTable(OdDbSymbolTable*&    pTable, OdDb::OpenMode mode = OdDb::kForRead);

  OdResult getSymbolTable(OdDbBlockTable*&     pTable, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getSymbolTable(OdDbLayerTable*&     pTable, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getSymbolTable(OdDbTextStyleTable*& pTable, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getSymbolTable(OdDbLinetypeTable*&  pTable, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getSymbolTable(OdDbViewTable*&      pTable, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getSymbolTable(OdDbUCSTable*&       pTable, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getSymbolTable(OdDbViewportTable*&  pTable, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getSymbolTable(OdDbRegAppTable*&    pTable, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getSymbolTable(OdDbDimStyleTable*&  pTable, OdDb::OpenMode mode = OdDb::kForRead);

  OdResult getGroupDictionary(OdDbDictionary*& pDict, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getMLStyleDictionary(OdDbDictionary*& pDict, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getLayoutDictionary(OdDbDictionary*& pDict, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getPlotStyleNameDictionary(OdDbDictionaryWithDefault*& pDict, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getMaterialDictionary(OdDbDictionary*& pDict, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getVisualStyleDictionary(OdDbDictionary*& pDict, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getColorDictionary(OdDbDictionary*& pDict, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getScaleListDictionary(OdDbDictionary*& pDict, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getNamedObjectsDictionary(OdDbDictionary*& pDict, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getPlotSettingsDictionary(OdDbDictionary*& pDict, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getTableStyleDictionary(OdDbDictionary*& pDict, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getMLeaderStyleDictionary(OdDbDictionary*& pDict, OdDb::OpenMode mode = OdDb::kForRead);

  // The following getXXXTable(OdDbXXXTable*& ...) functions exist
  // for backwards compatibility and may be removed in future releases.
  OdResult getBlockTable(OdDbBlockTable*&     pTable, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getLayerTable(OdDbLayerTable*&     pTable, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getTextStyleTable(OdDbTextStyleTable*& pTable, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getLinetypeTable(OdDbLinetypeTable*&  pTable, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getViewTable(OdDbViewTable*&      pTable, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getUCSTable(OdDbUCSTable*&       pTable, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getViewportTable(OdDbViewportTable*&  pTable, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getRegAppTable(OdDbRegAppTable*&    pTable, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult getDimStyleTable(OdDbDimStyleTable*&  pTable, OdDb::OpenMode mode = OdDb::kForRead);

  OdResult getDataLinkDictionary(OdDbDictionary*& pDict, OdDb::OpenMode mode = OdDb::kForRead);
  OdResult updateDataLink(OdDb::UpdateDirection nDir, OdDb::UpdateOption nOption);

  bool needsRecovery() const;

  void setFullSaveRequired();

  /** \details
    Returns the object ID of the BlockTable of this database object.
  */
  OdDbObjectId getBlockTableId() const;

  inline OdDbObjectId blockTableId() const { return getBlockTableId(); }
  /** \details
    Returns the object ID of the LayerTable of this database object.
  */
  OdDbObjectId getLayerTableId() const;

  inline OdDbObjectId layerTableId() const { return getLayerTableId(); }
  /** \details
    Returns the object ID of the TextStyleTable of this database object.
  */
  OdDbObjectId getTextStyleTableId() const;

  inline OdDbObjectId textStyleTableId() const { return getTextStyleTableId(); }
  /** \details
    Returns the object ID of the LinetypeTable of this database object.
  */
  OdDbObjectId getLinetypeTableId() const;

  inline OdDbObjectId linetypeTableId() const { return getLinetypeTableId(); }
  /** \details
    Returns the object ID of the ViewTable of this database object.
  */
  OdDbObjectId getViewTableId() const;

  inline OdDbObjectId viewTableId() const { return getViewTableId(); }
  /** \details
    Returns the object ID of the UCSTable of this database object.
  */
  OdDbObjectId getUCSTableId() const;

  inline OdDbObjectId UCSTableId() const { return getUCSTableId(); }
  /** \details
    Returns the object ID of the ViewportTable of this database object.
  */
  OdDbObjectId getViewportTableId() const;

  inline OdDbObjectId viewportTableId() const { return getViewportTableId(); }
  /** \details
    Returns the object ID of the RegAppTable of this database object.
  */
  OdDbObjectId getRegAppTableId() const;

  inline OdDbObjectId regAppTableId() const { return getRegAppTableId(); }
  /** \details
    Returns the object ID of the DimStyleTable of this database object.
  */
  OdDbObjectId getDimStyleTableId() const;
  inline OdDbObjectId dimStyleTableId() const { return getDimStyleTableId(); }

  /** \details
    Returns the object ID of the MLineStyle dictionary of this database object.
    \param createIfNotFound [in]  Controls the creation of the object if it does not exist.
  */
  OdDbObjectId getMLStyleDictionaryId(
    bool createIfNotFound = true) const;

  inline OdDbObjectId mLStyleDictionaryId() const { return getMLStyleDictionaryId(false); }
  /** \details
    Returns the object ID of the Group dictionary of this database object.
    \param createIfNotFound [in]  Controls the creation of the object if it does not exist.
  */
  OdDbObjectId getGroupDictionaryId(
    bool createIfNotFound = true) const;

  inline OdDbObjectId groupDictionaryId() const { return getGroupDictionaryId(false); }
  /** \details
    Returns the object ID of the Layout dictionary of this database object.
    \param createIfNotFound [in]  Controls the creation of the object if it does not exist.
  */
  OdDbObjectId getLayoutDictionaryId(
    bool createIfNotFound = true) const;

  inline OdDbObjectId layoutDictionaryId() const { return getLayoutDictionaryId(false); }
  /** \details
    Returns the object ID of the PlotStyleName dictionary of this database object.
    \param createIfNotFound [in]  Controls the creation of the object if it does not exist.
  */
  OdDbObjectId getPlotStyleNameDictionaryId(
    bool createIfNotFound = true) const;

  inline OdDbObjectId plotStyleNameDictionaryId() const { return getPlotStyleNameDictionaryId(false); }
  /** \details
    Returns the object ID of the NamedObjects dictionary of this database object.
  */
  OdDbObjectId getNamedObjectsDictionaryId() const;

  inline OdDbObjectId namedObjectsDictionaryId() const { return getNamedObjectsDictionaryId(); }
  /** \details
    Returns the object ID of the PlotSettings dictionary of this database object.
    \param createIfNotFound [in]  Controls the creation of the object if it does not exist.
  */
  OdDbObjectId getPlotSettingsDictionaryId(
    bool createIfNotFound = true) const;

  inline OdDbObjectId plotSettingsDictionaryId() const { return getPlotSettingsDictionaryId(false); }
  /** \details
    Returns the object ID of the Color dictionary of this database object.
    \param createIfNotFound [in]  Controls the creation of the object if it does not exist.
  */
  OdDbObjectId getColorDictionaryId(
    bool createIfNotFound = true) const;

  inline OdDbObjectId colorDictionaryId() const { return getColorDictionaryId(false); }
  /** \details
    Returns the object ID of the Material dictionary of this database object.
    \param createIfNotFound [in]  Controls the creation of the object if it does not exist.
  */
  OdDbObjectId getMaterialDictionaryId(
    bool createIfNotFound = true) const;

  inline OdDbObjectId materialDictionaryId() const { return getMaterialDictionaryId(false); }
  /** \details
    Returns the object ID of the VisualStyle dictionary of this database object.
    \param createIfNotFound [in]  Controls the creation of the object if it does not exist.
  */
  OdDbObjectId getVisualStyleDictionaryId(
    bool createIfNotFound = true) const;

  inline OdDbObjectId visualStyleDictionaryId() const { return getVisualStyleDictionaryId(false); }
  /** \details
    Returns the object ID of the TableStyle dictionary of this database object.
    \param createIfNotFound [in]  Controls the creation of the object if it does not exist.
  */
  OdDbObjectId getTableStyleDictionaryId(
    bool createIfNotFound = true) const;

  inline OdDbObjectId tableStyleDictionaryId() const { return getTableStyleDictionaryId(false); }
  /** \details
    Returns the object ID of the ScaleList dictionary of this database object.
    
    \param createIfNotFound [in]  Controls the creation of the object if it does not exist.
  */
  OdDbObjectId getScaleListDictionaryId(
    bool createIfNotFound = true) const;
  inline OdDbObjectId scaleListDictionaryId() const { return getScaleListDictionaryId(false); }
  /** \details
    Returns the object ID of the current TableStyle of this database object.
  */
  OdDbObjectId tablestyle() const;

  /** \details
    Sets the object ID of the current TableStyle of this database object.
    \param objectId [in]  Object ID.
  */
  OdResult setTablestyle(
    OdDbObjectId objectId);

  /** \details
    Returns the object ID of the MLeaderStyle dictionary of this database object.
    \param createIfNotFound [in]  Controls the creation of the object if it does not exist.
  */
  OdDbObjectId getMLeaderStyleDictionaryId(
    bool createIfNotFound = true) const;
  inline OdDbObjectId mleaderStyleDictionaryId() const { return getMLeaderStyleDictionaryId(false); }
  /** \details
    Returns the object ID of the current MLeaderStyle of this database object.
  */
  OdDbObjectId mleaderstyle() const;

  /** \details
    Sets the object ID of the current MLeaderStyle of this database object.
    \param objectId [in]  Object ID.
  */
  OdResult setMLeaderstyle(
    OdDbObjectId objectId);

  /** \details
    Returns the object ID of the DetailViewStyle dictionary of this database object.
    \param createIfNotFound [in]  Determines whether to create a DetailViewStyle dictionary if it does not exist.
  */
  OdDbObjectId getDetailViewStyleDictionaryId(
    bool createIfNotFound = true) const;
   
  /** \details
    Returns the object ID of the current DetailViewStyle of this database object.
  */
  OdDbObjectId detailViewStyle() const;

  /** \details
    Sets the object ID of the current DetailViewStyle of this database object.
    \param objectId [in]  Object ID.
  */
  OdResult setDetailViewStyle(
    OdDbObjectId objectId);

  /** \details
    Returns the object ID of the SectionViewStyle dictionary of this database object.
    \param createIfNotFound [in]  Determines whether to create a SectionViewStyle dictionary if it does not exist.
  */
  OdDbObjectId getSectionViewStyleDictionaryId(
    bool createIfNotFound = true) const;

  /** \details
    Returns the object ID of the current SectionViewStyle of this database object.
  */
  OdDbObjectId sectionViewStyle() const;

  /** \details
    Sets the object ID of the current SectionViewStyle of this database object.
    \param objectId [in]  Object ID.
  */
  OdResult setSectionViewStyle(
    OdDbObjectId objectId);

  /** \details
    Returns the object ID of the "ACAD" RegApp object of this database object.
  */
  OdDbObjectId getRegAppAcadId() const;

  /** \details
    Returns the object ID of the "Continuous" Linetype object of this database object.
  */
  OdDbObjectId getLinetypeContinuousId() const;
  inline OdDbObjectId continuousLinetype() const { return getLinetypeContinuousId(); }

  /** \details
    Returns the object ID of the "ByLayer" Linetype object of this database object.
  */
  OdDbObjectId getLinetypeByLayerId() const;
  inline OdDbObjectId byLayerLinetype() const { return getLinetypeByLayerId(); }

  /** \details
    Returns the object ID of the "ByBlock" Linetype object of this database object.
  */
  OdDbObjectId getLinetypeByBlockId() const;
  inline OdDbObjectId byBlockLinetype() const { return getLinetypeByBlockId(); }

  /** \details
    Returns the object ID of the ModelSpace Block object of this database object.
  */
  OdDbObjectId getModelSpaceId() const;

  /** \details
    Returns the object ID of the PaperSpace Block object of this database object.
  */
  OdDbObjectId getPaperSpaceId() const;

  OdDbObjectId currentSpaceId() const;
  /** \details
    Returns the object ID of the "Standard" text style object of this database object.
  */
  OdDbObjectId getTextStyleStandardId() const;

  /** \details
    Returns the object ID of the "Standard" dimension style object of this database object.
  */
  OdDbObjectId getDimStyleStandardId() const;

  /** \details
    Returns the object ID of the "0" layer object of this database object.
  */
  OdDbObjectId getLayerZeroId() const;
  inline OdDbObjectId layerZero() const { return getLayerZeroId(); }

  /** \details
    Returns the object ID of the "DEFPOINTS" layer object of this database object.
    \param createIfNotFound [in]  Controls the creation of the object if it does not exist.
  */
  OdDbObjectId getLayerDefpointsId(
    bool createIfNotFound = false) const;

  /** \details
    Returns the object ID of the specified system layer object of this database object.
    \param layerType [in]  Type of system layer.
    \param createIfNotFound [in]  Controls the creation of the object if it does not exist.

    \remarks
    layerType must be one of the following:

    <table>
    Name                        Value       Layer name
    OdDb::kLayerSystemLights    0           *ADSK_SYSTEM_LIGHTS
    OdDb::kLayerConstraints     1           *ADSK_CONSTRAINTS
    </table>
  */
  OdDbObjectId getLayerAdskId(
    OdDb::LayerAdskType layerType,
    bool createIfNotFound = false) const;

  /** \details
    Returns the object ID of the section manager.

    \remarks
    The ID may be null if the database
    has never contained any section planes.
  */
  OdDbObjectId getSectionManager() const;
  OdResult getSectionManager(OdDbSectionManager*& pMgr, OdDb::OpenMode mode) const;

  OdDbTransactionManager* transactionManager() const;

  /** \details
    Returns the object ID of the point cloud dictionary.

    \remarks
    The ID may be null if the database
    has never contained any point clouds.
  */
  OdDbObjectId getPointCloudDictionaryId() const;

  /** \details
    Returns the class DXF name for the specified class.

    \param pClass [in]  Pointer to the class object.

    \sa
	<exref target= "https://docs.opendesign.com/tkernel/OdRxClass.html">OdRxClass</exref>
  */
  const OdString classDxfName(
    const OdRxClass* pClass);

  /** \details
    Returns the object ID corresponding to the specified handle object in this database.

    \param objHandle        [in]  Database handle.
    \param createIfNotFound [in]  Controls the creation of the object if it does not exist.
    \param xRefId           [in]  Not used.

    \remarks
    If objHandle is 0, this function will create a new unique handle and return a
    newly created object ID corresponding to this handle.

    \remarks
    createIfNotFound is for internal use only and should always be false for client applications.

    \sa
    <link OdDbObjectId, OdDbObjectId class>
  */
  OdDbObjectId getOdDbObjectId(
    const OdDbHandle& objHandle,
    bool createIfNotFound = false,
    OdUInt32 xRefId = 0);

  OdResult getOdDbObjectId(OdDbObjectId& retId,
    bool createIfNotFound,
    const OdDbHandle& objHandle,
    OdUInt32 xRefId = 0);

  /** \details
    Writes the contents of this database object to the specified StreamBuf object.

    \param pStreamBuf         [in]  Pointer to the StreamBuf object to which the data is to be written.
    \param fileType           [in]  File type.
    \param fileVersion        [in]  File version.
    \param saveThumbnailImage [in]  Controls the saving of a thumbnail image to the file.
    \param dxfPrecision       [in]  DXF file decimal digits precision. [0 .. 16].

    \remarks
    fileType must be one of the following:

    <table>
    Name          Value   Description
    OdDb::kDwg    0       .dwg file.
    OdDb::kDxf    1       .dxf file.
    OdDb::kDxb    2       Binary .dxf file.
    </table>

    Parameter fileVersion must be one of the following:

    <table>
    OdDb::kDwg?    Name          Value  Description
    n              OdDb::vAC09   11     Release 9
    n              OdDb::vAC10   13     Release 10
    y              OdDb::vAC12   16     Release 11-12
    y              OdDb::vAC13   19     Release 13
    y              OdDb::vAC14   21     Release 14
    y              OdDb::vAC15   23     2000-2002
    y              OdDb::vAC18   25     2004-2006
    y              OdDb::vAC21   27     2007-2009
    y              OdDb::vAC24   29     2010-2012
    y              OdDb::vAC27   31     2013-2016
    </table>

    Throws:
    OdError if the write is unsuccessful.
  */
  void writeFile(
    OdStreamBuf* pStreamBuf,
    OdDb::SaveFileType fileType,
    OdDb::DwgVersion fileVersion,
    bool saveThumbnailImage = false,
    int dxfPrecision = 16);


  /** \details
    Writes the contents of this database object to the specified output file.

    \param filename           [in] Name of the file to which the data is to be written.
    \param fileType           [in] File type.
    \param fileVersion        [in] File version.
    \param saveThumbnailImage [in] Controls the saving of a thumbnail image to the file.
    \param dxfPrecision       [in] DXF file decimal digits precision. [0 .. 16].

    \remarks
    Parameter fileType must be one of the following:

    <table>
    Name          Value   Description
    OdDb::kDwg    0       .dwg file.
    OdDb::kDxf    1       .dxf file.
    OdDb::kDxb    2       Binary .dxf file.
    </table>

    fileVersion must be one of the following:

    <table>
    OdDb::kDwg?    Name          Value  Description
    n              OdDb::vAC09   11     Release 9
    n              OdDb::vAC10   13     Release 10
    y              OdDb::vAC12   16     Release 11-12
    y              OdDb::vAC13   19     Release 13
    y              OdDb::vAC14   21     Release 14
    y              OdDb::vAC15   23     2000-2002
    y              OdDb::vAC18   25     2004-2006
    y              OdDb::vAC21   27     2007-2009
    y              OdDb::vAC24   29     2010-2012
    y              OdDb::vAC27   31     2013-2016
    </table>

    Throws:
    OdError if the write is unsuccessful.
  */
  void writeFile(
    const OdString& filename,
    OdDb::SaveFileType fileType,
    OdDb::DwgVersion fileVersion,
    bool saveThumbnailImage = false,
    int dxfPrecision = 16)
  {
    closeInput();
    OdStreamBufPtr pFile = odSystemServices()->createFile(filename, (Oda::FileAccessMode)(Oda::kFileRead | Oda::kFileWrite), 
      Oda::kShareDenyReadWrite, Oda::kCreateAlways);
    writeFile(pFile, fileType, fileVersion, saveThumbnailImage, dxfPrecision);
  }
  
  /** \details 
    Saves the database contents to the specified output stream buffer. 
    Database contents are saved as a .dwg file of the latest supported version.
    
    \param pStreamBuf         [in] Pointer to the StreamBuf object to which the data is to be written.
    \param saveThumbnailImage [in] Controls the saving of a thumbnail image to the file.
  */
  void save(
    OdStreamBuf* pStreamBuf,
    bool saveThumbnailImage = false);

  /** \details 
    Saves the database contents to the specified output .dwg file.
    Output file has the latest supported version format. 
    Database contents are saved as a .dwg file of the latest supported version.
    
    \param filename         [in] Target file absolute path.
    \param saveThumbnailImage [in] Controls the saving of a thumbnail image to the file.
  */
  void save(
    const OdString& filename,        
    bool saveThumbnailImage = false);
  
  /** \details
    Reads the contents of the specified StreamBuf object or file into this database object.

    \param pStreamBuf         [in]  Pointer to the StreamBuf object from which the data is to be read.
    \param partialLoad        [in]  Controls the partial loading of .dwg files.
    \param pAuditInfo         [in]  Pointer to an OdDbAuditInfo object.
    \param password           [in]  Password for file.
    \param allowCPConversion  [in]  If and only if true, allows code page conversion.

    \remarks
    Using this function in .tx code is not recommended.
    In .tx modules use OdDbHostAppServices::readFile() or OdDbHostAppServices::recoverFile() instead.
    This provides more control for host applications which can override these virtual methods.

    The specified OdDbAuditInfo object controls the audit and receives the audit status.

    If pAuditInfo is non-zero, a recover will be performed instead of a load.

    Throws:
    OdError if the read is unsuccessful.
  */
  void readFile(
    OdStreamBuf* pStreamBuf,
    bool partialLoad = false,
    OdDbAuditInfo *pAuditInfo = 0,
    const OdPassword& password = OdPassword(),
    bool allowCPConversion = false,
    bool bFireEvent = true);

  /** \details 
    Reads the contents of the specified drawing file into this database object.
  
    \param filename   [in] Name of the file from which the data is to be read.
    \param shareMode  [in] Share mode to use when opening the specified file.

    \remarks
    shareMode must be one of the following:

    <table>
    Name                         Value       Description
    Oda::kShareDenyReadWrite     0x10        deny read/write mode
    Oda::kShareDenyWrite         0x20        deny write mode
    Oda::kShareDenyRead          0x30        deny read mode
    Oda::kShareDenyNo            0x40        deny none mode
    </table>

  */
  void readFile(
    const OdString& filename,
    bool partialLoad = false,
    Oda::FileShareMode shareMode = Oda::kShareDenyWrite,
    const OdPassword& password = OdPassword(),
    bool allowCPConversion = false )
  {
    readFile(odSystemServices()->createFile(filename, Oda::kFileRead, shareMode), partialLoad, 0, password, allowCPConversion);
  }

  // Filing Operations
//
  enum OpenMode {
    kForReadAndReadShare = 1,  // open for read and allow read sharing (_SH_DENYWR)
    kForReadAndWriteNoShare = 2,  // open for read/write and allow no sharing (_SH_DENYRW)
    kForReadAndAllShare = 3,  // open for read and allow read and write sharing (_SH_DENYNO)
    kTryForReadShare = 4   // try kForReadAndReadShare, and if that fails,
    // then try kForReadAndAllShare 
  };

private:
   OdResult readDwgFileEx(const OdChar* filename,
     const int shmode,
     bool bAllowCPConversion = false,
     const wchar_t* wszPassword = 0);

public:
  OdResult readDwgFile(const OdChar* fileName,
    OpenMode shmode = kForReadAndReadShare,
    bool bAllowCPConversion = false,
    const wchar_t* wszPassword = NULL);

  OdResult readDwgFile(OdDwgFileHandle *pDwgFile,
    bool bAllowCPConversion = false,
    const wchar_t* wszPassword = NULL);

  inline OdResult saveAs(const OdChar* fileName, const SecurityParams* pSecParams = 0)
  {
    return saveAs(fileName, true, OdDb::kDHL_CURRENT, pSecParams);
  }

  OdResult saveAs(const OdChar* fileName,
    const bool bBakAndRename,
    const OdDb::DwgVersion dwgVer = OdDb::kDHL_CURRENT,
    const SecurityParams* pSecParams = 0);

  OdResult saveAs(OdDwgFileHandle * pOutputFiler,
    const SecurityParams* pSecParams = 0,
    bool crashing = false);

  OdResult dxfOut(const OdChar* fileName,
    int precision = 16,
    OdDb::DwgVersion dwgVer = OdDb::kDHL_CURRENT,
    bool saveThumbnailImage = false);

  OdResult save();

  OdResult dxfIn(const OdChar* dxfFilename, const OdChar*logFilename = NULL);
  OdResult dxfIn(IGcReadStream* pInputStream, const OdChar* logFilename = NULL);

  const OdChar* originalFileName() const;

  bool isBeingDestroyed() const;

  OdDb::MaintReleaseVer lastSavedAsMaintenanceVersion() const;
  OdDb::MaintReleaseVer originalFileMaintenanceVersion() const;
  OdDb::MaintReleaseVer originalFileSavedByMaintenanceVersion() const;

  OdDwgFileHandle * inputFiler() const;

  void forceWblockDatabaseCopy();

  //DOM-IGNORE-BEGIN
  /** \details
    Forces all data to be loaded from the input file associated with this database object, and closes the file.

    \remarks
    Client applications will normally not need to call this function.
  */
  OdResult closeInput(bool bCloseFile = false);
  //DOM-IGNORE-END

  /** \details
    Returns the approximate number of objects in this database object.

    \remarks
    This function returns a value greater than or equal to the number of objects
    in this database object.

    This number is used to construct an OdDbObjectIdArray that can hold all the objects in the database, avoiding
    memory fragmentation and increasing performance.
  */
  OdInt32 approxNumObjects() const;

  /** \details
    Returns the version of this database object.

    \param pMaintReleaseVer [in]  Pointer to the MaintReleaseVer object to receive the maintenance release version.
    
    \remarks
    The maintenance release version is returned if and only if pMaintReleaseVer != 0.
  */
  OdDb::DwgVersion version(
    OdDb::MaintReleaseVer* pMaintReleaseVer = 0) const;

  /** \details
    Returns the number of times this database object has been saved since it was opened.

    \remarks
    This number can be zero.
  */
  OdInt32 numberOfSaves() const;

  /** \details
    Returns the version to which this database object was last saved.

    \param pMaintReleaseVer [in]  Pointer to the MaintReleaseVer object to receive the maintenance release version.

    \remarks
    The maintenance release version is returned if and only if pMaintReleaseVer != 0.
  */
  OdDb::DwgVersion lastSavedAsVersion(
    OdDb::MaintReleaseVer* pMaintReleaseVer = 0) const;

  /** \details
    Returns the filetype of the file from which this database object was read.

    \remarks
    originalFileType() returns one of the following:

    <table>
    Name         Value   Description
    OdDb::kDwg    0       .dwg file.
    OdDb::kDxf    0       .dxf file.
    </table>
  */
  OdDb::SaveFileType originalFileType() const;

  /** \details
    Returns the version of the file from which this database object was read.

    \param pMaintReleaseVer [in]  Pointer to the MaintReleaseVer object to receive the maintenance release version.

    \remarks
    The maintenance release version is returned if and only if pMaintReleaseVer != 0.
  */
  OdDb::DwgVersion originalFileVersion(
    OdDb::MaintReleaseVer* pMaintReleaseVer = 0) const;

  /** \details
    Returns the version of the application that created the file from which this database object was read.

    \param pMaintReleaseVer [in]  Pointer to the MaintReleaseVer object to receive the maintenance release version.

    \remarks
    The maintenance release version is returned if and only if pMaintReleaseVer != 0.
  */
  OdDb::DwgVersion originalFileSavedByVersion(
    OdDb::MaintReleaseVer* pMaintReleaseVer = 0) const;

   /** \details
    Adds the specified reactor to this object's reactor list.

    \param pReactor [in]  Pointer to the reactor object.
   */
  OdResult addReactor(
    OdDbDatabaseReactor* pReactor) const;

  void addReactor(
    OdDbDatabaseReactor* pReactor,int pos) const;
  /** \details
    Removes the specified reactor from this object's reactor list.

    \param pReactor [in]  Pointer to the reactor object.
  */
  OdResult removeReactor(OdDbDatabaseReactor*
    pReactor) const;

  OdResult auditXData(OdDbAuditInfo* pInfo);

  OdDb::MaintReleaseVer maintenanceReleaseVersion() const;
  
  /** \details
    Returns the R14 DIMFIT system variable of this database object.

    \remarks
    The DIMATFIT and DIMTMOVE values will be converted to DIMFIT. The complete mapping is as follows:

    <table>
    DIMTMOVE    DIMAFIT   DIMFIT
    0           0         0
    0           1         1
    0           2         2
    0           3         3
    1           0         4
    1           1         4
    1           2         4
    1           3         4
    2           0         5
    2           1         5
    2           2         5
    2           3         5
    </table>
  */
  int dimfit() const;

  /** \details
    Returns the R14 DIMUNIT system variable of this database object.

    \remarks
    The DIMLUNIT and DIMFRAC values will be converted to DIMUNIT. The complete mapping is as follows:

    <table>
    DIMFRAC   DIMLUNIT  DIMUNIT
    0         1         1
    0         2         2
    0         3         3
    0         4         4
    0         5         5
    0         6         8
    1         1         1
    1         2         2
    1         3         3
    1         4         4
    1         5         5
    1         6         8
    2         1         1
    2         2         2
    2         3         3
    2         4         6
    2         5         7
    2         6         8
    </table>

    All other input combinations return 2.
  */
  int dimunit() const;

  /** \details
    Sets the R14 DIMFIT system variable of this database object.

    \param val [in]  New value for DIMFIT. [0..5]

    \remarks
    The DIMFIT value will be converted to DIMATFIT and DIMTMOVE values.
  */
  OdResult setDimfit(
    int val);

  /** \details
    Sets the R14 DIMUNIT system variable of this database object.

    \param val [in]  New value for DIMUNIT. [1..7]

    \remarks
    The DIMUNIT value will be converted to DIMLUNIT and DIMFRAC values.
  */
  OdResult setDimunit(
    int val);

  OdInt16	pickstyle() const;
  OdResult	setPickstyle(OdInt16 style);
  /** \details
    Deep clones a set of objects and appends the clones to the specified owner object.

    \param objectIds [in]  Array of object IDs of the objects to be cloned.
    \param ownerId [in]  Object ID of owner object.
    \param idMap [in/out] ID map.
    \param deferXlation [in] Defer translation.

    \remarks
    idMap associates the object IDs of the original objects with the object IDs of the newly created clones.

    When cloning objects with different owner IDs, a separate call to this function is required for each
    ownerId. In this case, all but the final call to this function should be made with deferXlation == true.
    This defers translation until all objects have been cloned.

    A deep clone is a clone of the specified objects and everything they own.

    \sa
    <link OdDbDatabase::wblockCloneObjects@OdDbObjectIdArray&@OdDbObjectId@OdDbIdMapping&@OdDb::DuplicateRecordCloning@bool, OdDbDatabase::wblockCloneObjects() method>

  */
  OdResult deepCloneObjects(
    const OdDbObjectIdArray& objectIds,
    OdDbObjectId ownerId,
    OdDbIdMapping& idMap,
    bool deferXlation = false);


  /** \details
    Shallow clones a set of objects and appends the clones to the specified owner object.

    \param objectIds    [in]  Array of object IDs of the objects to be cloned.
    \param ownerId      [in]  Object ID of the owner object.
    \param idMap        [in/out] ID map.
    \param deferXlation [in] Defer translation.

    \remarks
    idMap associates the object IDs of the original objects with the object IDs of the newly created clones.

    When cloning objects with different owner IDs, a separate call to this function is required for each
    ownerId. In this case, all but the final call to this function should be made with deferXlation == true.
    This defers translation until all objects have been cloned.

    A shallow clone is a clone of the specified objects but not what they own.

	duplicateRecordCloning must be one of the following:

    <table>
    Name                        Value   Description
    OdDb::kDrcNotApplicable     0       Not applicable to the object.
    OdDb::kDrcIgnore            1       If a duplicate record exists, use the existing record in the database and ignore the clone.
    OdDb::kDrcReplace           2       If a duplicate record exists, replace it with the cloned record.
    OdDb::kDrcXrefMangleName    3       Incoming record names are mangled with <Xref>$0$<name>.
    OdDb::kDrcMangleName        4       Incoming record names are mangled with $0$<name>.
    OdDb::kDrcUnmangleName      5       Unmangle the names mangled by OdDb::kDrcMangleName, then default to OdDb::kDrcIgnore. Typically used by RefEdit when checking records into the original database.
    </table>

    \sa
    <link OdDbDatabase::deepCloneObjects@OdDbObjectIdArray&@OdDbObjectId@OdDbIdMapping&@bool OdDbDatabase::deepCloneObjects() method>

  */
  OdResult wblockCloneObjects(
    const OdDbObjectIdArray& objectIds,
    OdDbObjectId ownerId,
    OdDbIdMapping& idMap,
    OdDb::DuplicateRecordCloning duplicateRecordCloning,
    bool deferXlation = false);

  /** \details
    Terminates a call to deepCloneObjects() or wblockCloneObjects().

    \param idMap [in/out] ID map of the function call to be terminated.

    \remarks
    Parameter idMap associates the object IDs of the original objects with the object IDs of the newly created clones.

    This call is necessary only when a call to deepCloneObjects() or wblockCloneObjects() is made with deferXlation == true,
    and no call will be made with deferXlation == false.
  */
  void abortDeepClone(
    OdDbIdMapping& idMap);

  /** \details
    Performs an audit operation on the header of this database object.

    \param pAuditInfo [in]  Pointer to an OdDbAuditInfo object.

    \remarks
    The specified OdDbAuditInfo object controls the audit and receives the audit status.
  */
  OdResult audit(
    OdDbAuditInfo* pAuditInfo);

  void              disableUndoRecording(bool disable);
  bool              undoRecording() const ;
  /** \details
    Starts a new transaction of this database object.
  */
  virtual void startTransaction();

  /** \details
    Flush all the changes made during first transaction started on this database object.
    \remarks
    Forces all the objects modified in transaction to send reactor notifications
    and mark them to be in non-modified state. Does nothing if there is no active transaction.
    \returns true if transaction is active false otherwise.
  */
  virtual bool flushAllTransactedChanges();

  /** \details
    Ends the current transaction associated with this database object.

    \remarks
    This function commits all changes to objects since the start of the current transaction.
  */
  virtual void endTransaction();

  /** \details
    Aborts the current transaction associated with this database object.

    \remarks
    This function initiates an immediate rollback of all changes to objects
    since the start of the current transaction. This rollback occurs for
    all transaction-resident objects.
  */
  virtual void abortTransaction();

  /** \details
    Returns the number of active transactions associated with this database object.
  */
  virtual int numActiveTransactions();

  /** \details
    Adds a transaction reactor to this database object.

    \param reactor [in]  Transaction reactor.
  */
  virtual void addTransactionReactor(
    OdDbTransactionReactor* reactor);

  /** \details
    Removes the specified transaction reactor from this database object.

    \param reactor [in]  Transaction reactor.
  */
  virtual void removeTransactionReactor(
    OdDbTransactionReactor* reactor);


  /** \details
    Returns the thumbnail bitmap associated with this database object.

    \remarks
    The thumbnail is in Microsoft(R) Windows(R) BITMAPINFO* format.

    \param dataLength [out]  Receives the data length of the thumbnail.
  */
  const void* thumbnailBitmap(
    OdUInt32& dataLength) const;

  void* thumbnailBitmap() const;

  OdResult thumbnailImage(Otil::Image*& pPreviewImage) const;

  OdResult setThumbnailImage(const Otil::Image *pPreviewImage);

  OdCmTransparency cetransparency() const;

  OdResult setCetransparency(const OdCmTransparency& transparency);

  OdResult setPucs(const OdGePoint3d& ucsOrigin, const OdGeVector3d& ucsXDir, const OdGeVector3d& ucsYDir);

  OdResult setPucsname(const OdDbObjectId& ucsRecId);

  OdResult setUcs(const OdGePoint3d& ucsOrigin, const OdGeVector3d& ucsXDir, const OdGeVector3d& ucsYDir);

  OdResult setUcsname(const OdDbObjectId& ucsRecId);

  OdResult getDimpost(OdChar*&) const;
  OdResult getDimapost(OdChar*&) const;

  OdResult getDimblk(OdChar*&) const;
  OdResult getDimblk1(OdChar*&) const;
  OdResult getDimblk2(OdChar*&) const;

  virtual OdResult setDimblk(const OdChar*);
  virtual OdResult setDimblk1(const OdChar*);
  virtual OdResult setDimblk2(const OdChar*);
  virtual OdResult setDimldrblk(const OdChar*);

  OdResult setTStackAlign(int val);

  OdResult setTStackSize(int val);

  OdResult getDetailViewStyleDictionary(OdDbDictionary*& pDict, OdDb::OpenMode mode = OdDb::kForRead);
  
  OdDbObjectId detailViewStyleDictionaryId() const;
  
  OdResult getSectionViewStyleDictionary(OdDbDictionary*& pDict, OdDb::OpenMode mode = OdDb::kForRead);
  
  OdDbObjectId sectionViewStyleDictionaryId() const;

  bool geoMarkerVisibility() const;

  OdResult setGeoMarkerVisibility(bool value);

  OdString geoCoordinateSystemId() const;

  OdUInt8 lightingUnits() const;
  OdResult setLightingUnits(OdUInt8 val);

  bool lightsInBlocks() const;
  OdResult setLightsInBlocks(bool val);

  OdInt16 dxeVal() const;
  OdResult setDxeVal(OdInt16 val);

  OdInt16 cDynDisplayMode() const;
  OdResult setCDynDisplayMode(OdInt16 val);

  OdInt16 previewType() const;
  OdResult setPreviewType(OdInt16 val);

  OdUInt8 indexctl() const;
  OdResult setIndexctl(OdUInt8 val);

  OdUInt8 layerEval() const;
  OdResult setLayerEval(OdUInt8 val);

  OdInt16 layerNotify() const;
  OdResult setLayerNotify(OdInt16 val);

  double msOleScale() const;
  OdResult setMsOleScale(double val);

  OdUInt8 updateThumbnail() const;
  OdResult setUpdateThumbnail(OdUInt8 val);

  enum EraseMask
  {
    kZeroLengthCurve = 0x01,
    kEmptyText = 0x02,
    kAllEmptyObj = 0xFFFFFFFF
  };

  OdUInt32 eraseEmptyObjects(const OdUInt32 flags);
  OdUInt32 countEmptyObjects(const OdUInt32 flags);


  /** \details
    Sets the thumbnail bitmap associated with this database object.

    \remarks
    The thumbnail is in Windows BITMAPINFO* format.

    \param dataLength [in]  Data length of the thumbnail.
    \param pBMPData   [in]  Pointer to the bitmap data.
  */
  void setThumbnailBitmap(
    const void* pBMPData,
    OdUInt32 dataLength);

  // Gcad(Add)
  OdResult setThumbnailBitmap(void*);

  /** \details
    Returns the state of the RetainOriginalThumbnailBitmap flag.
  */
  bool retainOriginalThumbnailBitmap() const;

  /** \details
    Controls the state of the RetainOriginalThumbnailBitmap flag.

    \param retain [in]  Retain if and only if true.
  */
  void setRetainOriginalThumbnailBitmap(
    bool retain);

  OdResult dwgOutFields(
    OdDbDwgFiler* pFiler) const;

  OdResult dwgInFields(
    OdDbDwgFiler* pFiler);

//DOM-IGNORE-BEGIN
#define VAR_DEF(type, name, def_value, metric_def_value, reserve1, reserve2)\
    SVARS_FUNC_MODIFIER type get##name() const;

#include "SysVarDefs.h"

#undef VAR_DEF
#undef RO_VAR_DEF

#define RO_VAR_DEF(type, name, def_value, metric_def_value, reserve1, reserve2)
#define VAR_DEF(type, name, def_value, metric_def_value, reserve1, reserve2)\
    SVARS_FUNC_MODIFIER void set##name(type val);

#include "SysVarDefs.h"

#undef RO_VAR_DEF
#undef VAR_DEF

#define VAR_DEF(type, name, dxf, def_value, metric_def_value, reserve1, reserve2, readType, writeType)\
    virtual readType dim##name() const;\
    virtual OdResult setDim##name(writeType val);

#include "DimVarDefs.h"

#undef VAR_DEF
//DOM-IGNORE-END

  /** \details
    Returns true if current dimension style is annotative.
  */
  bool getDIMANNO() const;

  /** \details
    Returns the TDCREATE system variable of this database object.
    
    \remarks
    TDUCREATE represents the time and date, in local time, that the database was created.
  */
  OdDbDate getTDCREATE() const;

  /** \details
    Returns the TDUPDATE system variable of this database object.
    
    \remarks
    TDUUPDATE represents the time and date, in local time, that the database was last saved.
  */
  OdDbDate getTDUPDATE() const;

  bool   dwgFileWasSavedByAutodeskSoftware() const;

  OdInt16 coords() const;
  OdResult setCoords(OdInt16 coords);

  OdInt16 delUsedObj() const;
  OdResult setDelUsedObj(OdInt16 deleteObj);

  OdInt16 dragmode() const;
  OdResult setDragmode(OdInt16 mode);

  OdInt16 osmode() const;
  OdResult setOsmode(OdInt16 mode);

  bool blipmode() const;
  OdResult setBlipmode(bool mode);

  bool attreq() const;
  OdResult setAttreq(bool dia);

  bool attdia() const;
  OdResult setAttdia(bool dia);

  OdUInt8 xclipFrame() const;
  OdResult setXclipFrame(OdUInt8 disp);

  OdInt8 pdfframe() const;
  OdResult setPdfframe(OdInt8 val);

  bool usrtimer() const { return !!getUSRTIMER(); }
  OdResult setUsrtimer(bool timer) { setUSRTIMER(timer ? 1 : 0); return Oda::eOk; }

  /** \details
    Resets TDCREATE, TDUPDATE, TDINDWG and TDUSRTIMER system variables to the settings of the new drawing.
    
    \remarks
    TDCREATE and TDUPDATE will be set to the current system time and date. TDINDWG and TDUSRTIMER will be set to zero.
  */
  OdResult resetTimes();

  /** \details
    Returns the specified system variable of this database object.

    \param name [in]  Name of the system variable.

    \returns
    Returns a smart pointer to an OdResBuf object that contains the value.

    System variable names are case-insensitive strings.

    \sa
	<link TD_SysVars System Variables>
  */
  OdResBufPtr getSysVar(
    const OdString& name) const;

  /** \details
    Sets the specified system variable of this database object.

    \param name   [in]  Name of the system variable.
    \param pValue [in]  Pointer to an OdResBuf object that contains the new value.

    \remarks
    System variable names are case-insensitive strings.

    \sa
    System Variables
  */
  void setSysVar(
    const OdString& name,
    const OdResBuf* pValue);

  /** \details
    Returns the next available handle number of this database object.
    
    \remarks
    Use OdDbHandle::getIntoAsciiBuffer() to return the hex string version of the handle.
  */
  OdDbHandle handseed() const;

  OdResult setHandseed(const OdDbHandle&);
  /** \details
    Copies the dimension variables of this database object to the
    specified DimStyleTableRecord.

    \param pDestination [in]  Pointer to the destination record.
  */
  OdResult getDimstyleData(
    OdDbDimStyleTableRecord* pDestination) const;

  /** \details
    Returns the child dimension style data and dimension style object identifier.

    \param pDimClass  [in]  A pointer to a dimension class instance.
    \param pRec       [out] A pointer to an output dimension styles table record, which should contain child dimension style data after the method returns the control. 
    \param style      [out] Identifier of the output style object.
    
    \returns Returns eOk if style data has been retrieved successfully or an error code in the other case.

    \remarks
    The method returns parent style information and identifier if the child style can not be retrieved.
  */
  OdResult getDimstyleChildData(const OdRxClass *pDimClass,
                                OdDbDimStyleTableRecord* pRec,
                                OdDbObjectId &style) const;
  /** \details 
  
    Returns the identifier of the child dimension style. 
    
    \param pDimClass    [in] A pointer to a dimension class instance. 
    \param parentStyle  [in] A parent dimension style object identifier.
    
    \remarks 
    The method returns the parent dimension identifier if the child style can not be retrieved. 
  */
  OdDbObjectId getDimstyleChildId(const OdRxClass *pDimClass,
                                  const OdDbObjectId &parentStyle) const;

  /** \details 
    Returns the identifier of the parent dimension style.
    
    \param childStyle [in] A child dimension style object identifier.
    
    \remarks 
    The method returns the child dimension identifier if the parent style can not be retrieved. 
  */
  OdDbObjectId getDimstyleParentId(const OdDbObjectId &childStyle) const;


  /** \details
    Copies the dimension style data from the specified DimStyleTableRecord
    to the dimension variables of this database object.
    
    \param pSource [in] Pointer to the source record.
  */
  OdResult setDimstyleData(
    const OdDbDimStyleTableRecord* pSource);

  /** \details
    Copies the dimension style data from the specified DimStyleTableRecord
    to the dimension variables of this database object.
    
    \param objectId [in]  Object ID of the source record.
  */
  OdResult setDimstyleData(
    OdDbObjectId objectId);

  /** \details
    Loads a linetype into this database object.

    \param ltName   [in] Name of the linetype to load.
    \param filename [in] Name of the linetype file from which to load.
    \param encode   [in] Encoding used in linetype text file (if known).

    \remarks
    Wildcards are permitted in ltName; if "*" is specified, all linetypes from the filename will be loaded.

    dlt must be one of the following:

    <table>
    Name                      Value   Description
    OdDb::kDltNotApplicable     0       Not Applicable.
    OdDb::kDltIgnore            1       Ignore duplicate linetypes.
    OdDb::kDltReplace           2       Replace duplicate linetypes.
    </table>

    Throws:
    An appropriate error if not successful.
  */
  OdResult loadLineTypeFile(
    const OdChar* ltName,
    const OdChar* filename,
    OdDb::DuplicateLinetypeLoading dlt = OdDb::kDltNotApplicable,
    OdDb::TextFileEncoding encode = OdDb::kTextFileEncodingDefault);

  /** \details
      Returns the name of the file this database object was loaded from.
    Can return empty string in case the database was created from scratch.
  */
  virtual OdString originalFilename() const;

  /** \details
  Returns the name of the file associated with this database object.
  */
  virtual OdString getFilename() const;
  OdResult getFilename(const OdChar* & pOutput) const;
  OdResult getFilename(OdChar* & pOutput) const;

  /** \details
    Forcibly sets the name of the current file for this database instance.
    
    \param fileName [in] Name of the file to be set as current for this database instance.
  */
  virtual void setFilename(const OdString& fileName);

  /** \details
    Removes the object IDs from the specified array that are hard referenced in this database object.
    
    \param objectIds [in/out] Array of object IDs.

    \remarks
    Any remaining object IDs can be safely erased.
    This function does not modify this database object.
  */
  virtual OdResult purge(
    OdDbObjectIdArray& objectIds) const;

  /** \details
    Removes the nodes from the id graph that are hard referenced in this database object.
    
    \param objectIds [in/out] Id graph to examine.
   
    \remarks
    This function builds a reference graph between the objects, which can be used to remove objects with circular references in one pass.
    All the objects referenced from outside of the graph are removed from it on return.
    This function does not modify this database object.
  */
  OdResult purge(OdDbObjectIdGraph& objectIds);

  /** \details
      Returns a count of hard references to each of the specified object IDs.

      \param objectIds  [in]  Array of object IDs.
      \param counts     [out] Receives an array of hard reference counts. 

      \remarks
      counts must be the same size as objectIds.

      Each element of counts will be incremented for each hard reference of the corresponding objectId.
      The caller must initialize the elements of count to zero or an appropriate value
      before calling this function.
  */
  virtual OdResult countHardReferences(
    const OdDbObjectIdArray& objectIds,
    OdUInt32* counts) const;


  OdResult reclaimMemoryFromErasedObjects(const OdDbObjectIdArray& erasedObjects);

  bool hasClass(const OdRxClass* pClass) const;

  /** \details
      Returns the object ID of the active layout of this database object.
  */
  OdDbObjectId currentLayoutId() const;

  /** \details
    Sets the current layout of this database object.

    \param layoutName [in]  Name of the layout to be set as current.
  */
  virtual void setCurrentLayout(
    const OdString& layoutName);

  /** \details 
    Sets the current layout of this database object.
    
    \param layoutId [in]  Object ID of layout to be set as current.
  */
  virtual void setCurrentLayout(
    const OdDbObjectId& layoutId);

  /** \details
      Returns the name of the active layout of this database object.

      \param allowModel [in]  If and only if true, allows the ModelSpace layout name to be returned.

      \remarks
      If allowModel == false, an empty string will be returned if the active layout is ModelSpace.
  */
  virtual const OdChar* findActiveLayout(
    bool allowModel) const;

  /** \details
    Returns the object ID of the BlockTableRecord associated with the active
    layout of this database object.
  */
  virtual OdDbObjectId getActiveLayoutBTRId() const;

  /** \details
    Returns the object ID of the specified layout in this database object.

    \param layoutName [in]  Layout name.

    \remarks
    Returns a null object ID if the specified layout is not found.
  */
  virtual OdDbObjectId findLayoutNamed(
    const OdString& layoutName) const;

  /** \details
    Deletes the specified layout from this database object.

    \param layoutName [in]  Layout name.
  */
  virtual void deleteLayout(
    const OdString& layoutName);

  /** \details
    Creates a new layout with the specified name in this database object.

    \remarks
    The newly created layout is added to this database object along with its
    newly created associated OdDbBlockTableRecord.

    \param layoutName [in]  Layout name.
    \param pBlockTableRecId [in]  Pointer to the BlockTableRecID to receive the object ID of the new BlockTableRecord object.
  */
  virtual OdDbObjectId createLayout(
    const OdString& layoutName,
    OdDbObjectId* pBlockTableRecId = 0);

  /** \details
    Returns the number of layouts in this database object.
  */
  virtual int countLayouts() const;

  /** \details
    Renames the specified layout in this database object.
    \param oldName [in]  Old name.
    \param newName [in]  New name.
  */
  virtual void renameLayout(
    const OdString& oldName,
    const OdString& newName);

  /** \details
      Starts undo recording of this database object.
  */
  void startUndoRecord(const OdChar* pRecordName = 0);

  /** \details
      Returns true if undo information exists for this database object.
  */
  bool hasUndo() const;
  bool hasCurUndo(bool *pIsNothing = 0) const;
  OdDbUndoController* undoController() const;

  /** \details
    Performs an undo operation on this database object.

    \remarks
    All operations performed since the last call to startUndoRecording will be undone.
    At least 1 undo step is always supported for internal needs.
  */
  void undo();

  /** \details
    Blocks or unblocks undo history recording. 
    
    \param bBegin [in] A flag determining whether undo history recording is blocked (if true) or not (if false). 
  */
  void blockUndoRecording(bool bBegin);

  /** \details
    Returns whether undo history recording has been blocked (returns true) or not (returns false). 
  */
  bool isUndoBlockStarted();

  /** \details
    Sets an undo marker on this database object.
  */
  void setUndoMark();

  /** \details
    Returns whether an undo marker has been set on this database object (returns true) or not (returns false).
  */
  bool hasUndoMark() const;

  /** \details
    Performs the undo operation on this database object. 
  */
  void undoBack();

  /** \details
    Returns the quantity of undo markers.
  */
  int getUNDOMARKS() const;

  /** \details
    Clears undo history.
  */
  void clearUndo();

  /** \details
    Returns true if redo information exists for this database object.
  */
  bool hasRedo() const;
  OdDbUndoControllerPtr redoController() const;

  /** \details
    Performs a redo operation on this database object.

    \remarks
    Restores operations undone by the last undo.
  */
  void redo();

  /** \details
    Performs an audit operation on the this entire database object.

    \param pAuditInfo [in]  Pointer to an AuditInfo object.

    \remarks
    The specified AuditInfo object controls the audit and receives the audit status.
  */
  void auditDatabase(
    OdDbAuditInfo *pAuditInfo);

  /** \details 
    Applies a partial undo operation.
    
    \param pUndoFiler [in] Object used for perfoming input/output operations. 
    \param pClassObj  [in] A pointer to an object for perfoming undo actions.
  */
  OdResult applyPartialUndo(
    OdDbDwgFiler* pUndoFiler,
    OdRxClass* pClassObj);

  /** \details 
    Returns the current object used for udo file input/output operations. 
  */
  OdDbDwgFiler* undoFiler();

  /** \details
    Copies the content of a specified database to this database.  

    \param destinationBlockName   [in]  Name for the new OdDbBlockTableRecord.
    \param pSource                [in]  Source database.
    \param preserveSourceDatabase [in]  Not used. Objects from the source database are always copied, not moved.
    
    \remarks
    The data that will be copied includes content of the following enities: 
    * BlockTable
    * LayerTable
    * LinetypeTable
    * DimStyleTable
    * RegAppTable
    * TextStyleTable
    * PlotStyleNameDictionary
    * PlotSettingsDictionary
    * MLStyleDictionary
    * ColorDictionary
    * MaterialDictionary
    * TableStyleDictionary
    * MLeaderStyleDictionary
    * ScaleListDictionary
    * VisualStyleDictionary 
    * GroupDictionary

    Unlike the wblockCloneObjects() method, insert() also copies the sortens table. 
    While copying duplicate objects, names will be ignored; a destination object that has the same name as the source object will be rewritten by the source one.

    A new OdDbBlockTableRecord is created and all model space entities of pSource are copied into the new block.
	  */
  OdDbObjectId insert(
    const OdString& destinationBlockName,
    OdDbDatabase* pSource,
    bool preserveSourceDatabase = true);

  /** \details
    Copies the content of a specified database to this database.  

    \param sourceBlockName        [in]  Name of the OdDbBlockTableRecord in pSource.
    \param destinationBlockName   [in]  Name for the new OdDbBlockTableRecord.
    \param pSource                [in]  Source database.
    \param preserveSourceDatabase [in]  Not used. Objects from the source database are always copied, not moved.
    
    \remarks
    The data that will be copied includes content of the folloowing enities: 
    * BlockTable,
    * LayerTable
    * LinetypeTable
    * DimStyleTable
    * RegAppTable
    * TextStyleTable
    * PlotStyleNameDictionary
    * PlotSettingsDictionary
    * MLStyleDictionary
    * ColorDictionary
    * MaterialDictionary
    * TableStyleDictionary
    * MLeaderStyleDictionary
    * ScaleListDictionary
    * VisualStyleDictionary
    * GroupDictionary

    Unlike the wblockCloneObjects() method, insert() also copies the sortens table. 
    While copying duplicate objects, names will be ignored; a destination object that has the same name as the source object will be rewritten by the source one.

    All entities in the BlockTableRecord specified by sourceBlockName in pSource are copied into the new OdDbBlockTableRecord and offset by the INSBASE value. 
    Contents of layout blocks are copied only if sourceBlockName is a layout block name. 
  */
  OdDbObjectId insert(
    const OdString& sourceBlockName,
    const OdString& destinationBlockName,
    OdDbDatabase* pSource,
    bool preserveSourceDatabase = true);

  /** \details
    Copies the content of a specified database to this database.  

    \param xfm                    [in]  Transformation matrix.
    \param pSource                [in]  Source database.
    \param preserveSourceDatabase [in]  Not used. Objects from the source database are always copied, not moved.
    
    \remarks
    The data that will be copied includes content of the folloowing enities: 
    * BlockTable
    * LayerTable
    * LinetypeTable
    * DimStyleTable
    * RegAppTable
    * TextStyleTable
    * PlotStyleNameDictionary
    * PlotSettingsDictionary
    * MLStyleDictionary
    * ColorDictionary
    * MaterialDictionary
    * TableStyleDictionary
    * MLeaderStyleDictionary
    * ScaleListDictionary
    * VisualStyleDictionary
    * GroupDictionary

    Unlike the wblockCloneObjects() method, insert() also copies the sortens table. 
    While copying duplicate objects, names will be ignored; a destination object that has the same name as the source object will be rewritten by the source one.
    
    All model space entities in pSource are copied into model space of this database object and transformed by xfm.
  */
  OdResult insert(
    const OdGeMatrix3d& xfm,
    OdDbDatabase* pSource,
    bool preserveSourceDatabase = true);

   OdResult insert(OdDbObjectId& blockId,
          const OdChar * destinationBlockName,
				  OdDbDatabase* pDb,
				  bool preserveSourceDatabase = true);

   OdResult insert(OdDbObjectId& blockId, 
          const OdChar * sourceBlockName,
          const OdChar * destinationBlockName,
				  OdDbDatabase* pDb,
				  bool preserveSourceDatabase = true);     
  /** \details
    Clones specified objects of this database to a new database.

    \param outObjIds [in]  Array of object IDs to be cloned.
    \param basePoint [in]  WCS base point for the insertion.

    \remarks
    The method creates a new OdDbDatabase object, populates it with specified objects from this database using the wblockClone() method and returns a smart pointer to the new database. 
    All objects are copied with their dependencies. For example, if a text entity uses a specific textstyle, it will be copied as well; line entities will be copied with their linestyles, etc.
  */
  OdDbDatabasePtr wblock(
    const OdDbObjectIdArray& outObjIds,
    const OdGePoint3d& basePoint);

  /** \details
    Clones specified objects of this database to a new database.

    \param blockId [in]  Object ID of the BlockTableRecord to be cloned.
     
    \remarks
    The method creates a new OdDbDatabase object, populates it with specified objects from this database using the wblockClone() method and returns a smart pointer to the new database. 
    All objects are copied with their dependencies. For example, if a text entity uses a specific textstyle, it will be copied as well; line entities will be copied with their linestyles, etc.
  */
  OdDbDatabasePtr wblock(
    OdDbObjectId blockId);

  /** \details
    Clones the entire contents of this database to a new database.

    \remarks
    The method creates a new OdDbDatabase object, populates it with objects from this database and returns a smart pointer to the new database. 
    All objects are copied with their dependencies. For example, if a text entity uses a specific textstyle, it will be copied as well; line entities will be copied with their linestyles, etc.
  */
  OdDbDatabasePtr wblock();

 /** \details
    As implemented, this function does nothing but return a null SmartPointer.
    It will be fully implemented in a future release.
 */
  OdDbObjectPtr subWblockClone(OdDbIdMapping& ownerIdMap, OdDbObject*) const;
  using OdDbObject::subWblockClone; // Fix -Woverloaded-virtual

  OdResult wblock(OdDbDatabase*& pOutputDb,
    const OdDbObjectIdArray& outObjIds,
    const OdGePoint3d& basePoint);

  OdResult wblock(OdDbDatabase* pOutputDb,  // pre-existing (template) db
    const OdDbObjectIdArray& outObjIds,
    const OdGePoint3d& basePoint,
    OdDb::DuplicateRecordCloning drc);  // kDrcIgnore

  OdResult wblock(OdDbDatabase*& pOutputDb, OdDbObjectId blockId);

  OdResult wblock(OdDbDatabase*& pOutputDb);

  /** \details
    Sets the security parameters of this database object.

    \param secParams  [in]  Security params.
    \param setDbMod   [in]  If and only if true, the DBMOD variable will be set if the security settings are modified.

    \remarks
    As implemented, this function ignores setDbMod and never modifies the DBMOD variable.
    It will be fully implemented in a future release.
  */
  void setSecurityParams(
    const OdSecurityParams& secParams,
    bool setDbMod = true);

  bool annotativeDwg() const;
  OdResult setAnnotativeDwg(bool anno);
  /** \details
    Returns the security parameters of this database object.
    
    \param secParams [in]  Security params.
    
    \remarks
    Returns true only if field nFlags of secParams is not equal to 0 and field password of secParams is not empty.
  */
  bool securityParams(
    OdSecurityParams& secParams) const;
    
  /*/Gcad(Add)
  /*/
  bool                  setSecurityParams(const SecurityParams* pSecParams, bool bSetDbMod = true);
  const SecurityParams* cloneSecurityParams();
  static void           disposeSecurityParams(const SecurityParams* pSecParams);

  /** \details
    Returns the OdFileDependencyManager object of this database object.
  */
  OdFileDependencyManager* fileDependencyManager() const;
  
  /** \details
  Returns the OdDbObjectContextManager object of this database object.
  */
  OdDbObjectContextManager* objectContextManager() const;
  
  /** \details
    Returns the OdDbLayerStateManager object of this database object.
  */
  OdDbLayerStateManager* getLayerStateManager() const;

  /** \details
    Recalculates the extents of this database object.
    
    \param bExact [in]  Enables a slower but more exact extents calculation algorithm.
  */
  OdResult updateExt(bool bExact = false);

  /** \details
    Returns true if and only if this database object was created by an educational version of the application.
  */
  bool isEMR() const;
  
  /** \details
    Returns the object ID of the OdDbBlockTableRecord that references this database object as an Xref.
  */
  OdDbObjectId xrefBlockId() const;

  /** \details
    Returns true if and only if this database object is partially opened.
  */
  bool isPartiallyOpened() const;

  OdResult applyPartialOpenFilters(
    const OdDbSpatialFilter* pSpatialFilter,
    const OdDbLayerFilter* pLayerFilter);

  void disablePartialOpen();


  /** \details
    Returns true if and only if this database object is being loaded from a file.
  */
  bool isDatabaseLoading() const;

  /** \details
    Returns true if and only if this database object is being converted after loading from a file or before saving to a file.
  */
  bool isDatabaseConverting() const;

  /** \details
    Returns the pointer to OdDbAuditInfo if the database is being loaded from a file in recover modem, otherwise returns Null.
  */
  OdDbAuditInfo* auditInfo() const;

  OdResult evaluateFields(int nContext,
    const OdChar* pszPropName = NULL,
    OdDbDatabase* pDb = NULL,
    int* pNumFound = NULL,
    int* pNumEvaluated = NULL);

  OdResult getViewportArray(OdDbObjectIdArray& vportIds,
    bool bGetPaperspaceVports = true) const;

  OdResult getTimeZoneInfo(OdDb::TimeZone tz, double& offset, OdString& desc) const;
  OdResult setTimeZoneAsUtcOffset(double offset);

  double mleaderscale() const;
  OdResult setMLeaderscale(double scale);

  /** \details
    Sets the current UCS of this database object.

    \param viewType [in]  Orthographic view type.

    \remarks
    viewType must be one of the following:

    <table>
    Name                  Value   View type
    OdDb::kNonOrthoView   0       Non-orthographic with respect to the UCS
    OdDb::kTopView        1       Top view with respect to the UCS
    OdDb::kBottomView     2       Bottom view with respect to the UCS
    OdDb::kFrontView      3       Front view with respect to the UCS
    OdDb::kBackView       4       Back view with respect to the UCS
    OdDb::kLeftView       5       Left view with respect to the UCS
    OdDb::kRightView      6       Right view with respect to the UCS
    </table>
  */
  void setCurrentUCS(
    OdDb::OrthographicView viewType);
 
  /** \details
    Sets the current UCS of this database object.

    \param ucsId    [in]  Object ID of the UCS.
  */
  void setCurrentUCS(
    const OdDbObjectId& ucsId);
    
  /** \details
    Sets the current UCS of this database object.

    \param origin   [in]  The WCS origin of the UCS.
    \param xAxis    [in]  The WCS X-axis of the UCS.
    \param yAxis    [in]  The WCS Y-axis of the UCS.
  */
  void setCurrentUCS(
    const OdGePoint3d& origin,
    const OdGeVector3d& xAxis,
    const OdGeVector3d& yAxis);

  /** \details
    Returns the UCS origin and orthographic view type for the current UCS.

    \param viewType [in]  Orthographic view type.

    \remarks
    viewType must be one of the following:

    <table>
    Name            Value   View type
    OdDb::kNonOrthoView   0       Non-orthographic with respect to the UCS
    OdDb::kTopView        1       Top view with respect to the UCS
    OdDb::kBottomView     2       Bottom view with respect to the UCS
    OdDb::kFrontView      3       Front view with respect to the UCS
    OdDb::kBackView       4       Back view with respect to the UCS
    OdDb::kLeftView       5       Left view with respect to the UCS
    OdDb::kRightView      6       Right view with respect to the UCS
    </table>
  */
  OdGePoint3d getUCSBASEORG(
    OdDb::OrthographicView viewType) const;

  /** \details
    Sets the UCS origin and orthographic view type for the current UCS.

    \param origin   [in]  The WCS origin of the UCS.
    \param viewType [in]  Orthographic view type.

    \remarks
    viewType must be one of the following:

    <table>
    Name            Value   View type
    OdDb::kNonOrthoView   0       Non-orthographic with respect to the UCS
    OdDb::kTopView        1       Top view with respect to the UCS
    OdDb::kBottomView     2       Bottom view with respect to the UCS
    OdDb::kFrontView      3       Front view with respect to the UCS
    OdDb::kBackView       4       Back view with respect to the UCS
    OdDb::kLeftView       5       Left view with respect to the UCS
    OdDb::kRightView      6       Right view with respect to the UCS
    </table>
  */
  void setUCSBASEORG(
    OdDb::OrthographicView viewType,
    const OdGePoint3d& origin);

  /** \details
    Returns the UCS origin and orthographic view type for the current PaperSpace UCS.

    \param viewType [in]  Orthographic view type.

    \remarks
    viewType must be one of the following:

    <table>
    Name                  Value   View type
    OdDb::kNonOrthoView   0       Non-orthographic with respect to the UCS
    OdDb::kTopView        1       Top view with respect to the UCS
    OdDb::kBottomView     2       Bottom view with respect to the UCS
    OdDb::kFrontView      3       Front view with respect to the UCS
    OdDb::kBackView       4       Back view with respect to the UCS
    OdDb::kLeftView       5       Left view with respect to the UCS
    OdDb::kRightView      6       Right view with respect to the UCS
    </table>
  */
   OdGePoint3d getPUCSBASEORG(
    OdDb::OrthographicView viewType) const;

 /** \details
    Sets the UCS origin and orthographic view type for the current PaperSpace UCS.

    \param origin   [in]  The WCS origin of the UCS.
    \param viewType [in]  Orthographic view type.

    \remarks
    viewType must be one of the following:

    <table>
    Name                  Value   View type
    OdDb::kNonOrthoView   0       Non-orthographic with respect to the UCS
    OdDb::kTopView        1       Top view with respect to the UCS
    OdDb::kBottomView     2       Bottom view with respect to the UCS
    OdDb::kFrontView      3       Front view with respect to the UCS
    OdDb::kBackView       4       Back view with respect to the UCS
    OdDb::kLeftView       5       Left view with respect to the UCS
    OdDb::kRightView      6       Right view with respect to the UCS
    </table>
 */
  void setPUCSBASEORG(
    OdDb::OrthographicView viewType,
    const OdGePoint3d& origin);

  /** \details
  Returns the database to its original state (when the xref was first read) by undoing
  any modifications.
  \remarks
  This function should be used with restoreForwardingXrefSymbols when reading or writing any xref object. 
  */
  OdResult restoreOriginalXrefSymbols();

  /** \details
  Returns the database to its modified state (before any original state restoration) by
  redoing modifications.
  \remarks
  This function should be used with restoreOriginalXrefSymbols when reading or
  writing any xref object. The database requires write-access to symbol tables and 
  records.
  */
  OdResult restoreForwardingXrefSymbols();

  /** \details
    Requires a lineweight and returns True if the specified lineweight is valid, that is, one of the
    predefined lineweights in this database, or False otherwise.

    \param weight [in]  The lineweight value.
  */
  static bool isValidLineWeight(int weight);

  /** \details
    Requires a lineweight and returns the nearest OdDb::LineWeight enum number for this database. For example, 
    when the passed value is 8, the returned value is kLnWt009.

    \param weight [in]  The lineweight value.
  */
  static OdDb::LineWeight getNearestLineWeight(int weight);

  bool isUcsOrthographic(OdDb::OrthographicView&) const;

  bool isPucsOrthographic(OdDb::OrthographicView&) const;

  OdGePoint3d worldUcsBaseOrigin(OdDb::OrthographicView) const;

  OdResult setWorldUcsBaseOrigin(const OdGePoint3d&, OdDb::OrthographicView);

  OdResult setWorldPucsBaseOrigin(const OdGePoint3d&, OdDb::OrthographicView);

  OdGePoint3d worldPucsBaseOrigin(OdDb::OrthographicView) const;

  //DOM-IGNORE-BEGIN
  /*
  bool plotStyleMode() const;


  void forceWblockDatabaseCopy();

  void auditXData(OdDbAuditInfo* pInfo);

  OdDbUndoController* undoController() const;

  void setDimblk(const OdChar*);
  void setDimblk1(const OdChar*);
  void setDimblk2(const OdChar*);
  void setDimldrblk(const OdChar*);

  void getDimstyleChildData(const OdRxClass *pDimClass,
                            OdDbDimStyleTableRecordPtr& pRec,
                            OdDbObjectId &style) const;

  OdDbObjectId getDimstyleChildId(const OdRxClass *pDimClass,
                                  OdDbObjectId &parentStyle) const;

  OdDbObjectId getDimstyleParentId(OdDbObjectId &childStyle) const;

  void getDimRecentStyleList(OdDbObjectIdArray& objIds) const;

  void applyPartialOpenFilters(const OdDbSpatialFilter* pSpatialFilter,
                               const OdDbLayerFilter* pLayerFilter);

  void disablePartialOpen();

  void newFingerprintGuid();

  void newVersionGuid();

  double viewportScaleDefault() const;

  void setViewportScaleDefault(double newDefaultVPScale);

  OdDbObjectId getPaperSpaceVportId() const;

  virtual void copyLayout(const OdChar* copyname, const OdChar* newname);

  virtual void cloneLayout(const OdDbLayout* pLBTR, const OdChar* newname, int newTabOrder);

  virtual OdDbObjectId getNonRectVPIdFromClipId(const OdDbObjectId& clipId);

  virtual bool isViewportClipped(short index);

  */
  //DOM-IGNORE-END
  
  OdDbObjectId getPaperSpaceVportId() const;

  OdDbObjectId paperSpaceVportId() const { return getPaperSpaceVportId(); };


  OdResult getDimRecentStyleList(OdDbObjectIdArray& objIds) const;


  /** \details
    Returns the identifier of the by-layer material for this database.
  */
  OdDbObjectId byLayerMaterialId() const;
  
  /** \details
    Returns the identifier of the by-block material for this database.
  */
  OdDbObjectId byBlockMaterialId() const;
  
  
  /** \details
    Returns the identifier of the global material for this database.
  */  
  OdDbObjectId globalMaterialId() const;

  /** \details
    Returns the identifier of the active viewport for this database.
  */  
  OdDbObjectId activeViewportId() const;


  OdDbObjectId globalMaterial() const { return globalMaterialId(); }
  OdDbObjectId byLayerMaterial() const { return byLayerMaterialId(); }
  OdDbObjectId byBlockMaterial() const { return byBlockMaterialId(); }


#define OD_SYSVAR_DEF_R(RName, DDName, type) \
        type RName() const;
#define OD_SYSVAR_DEF_W(WName, DDName, type) \
        OdResult WName(type);
# include "DwgSysVar.h"
#undef OD_SYSVAR_DEF_R
#undef OD_SYSVAR_DEF_W

  OdResult getMenu(OdChar*&) const;
  OdResult getProjectName(OdChar*&) const;
  OdResult setProjectName(const OdChar*);
  OdResult getHyperlinkBase(OdChar*&) const;
  OdResult setHyperlinkBase(const OdChar*);
  OdResult getStyleSheet(OdChar*&) const;
  OdResult setStyleSheet(const OdChar*);

  OdDb::PlotStyleNameType getCePlotStyleNameId(OdDbObjectId& id) const;
  OdResult setCePlotStyleName(OdDb::PlotStyleNameType, OdDbObjectId newId = OdDbObjectId::kNull);

  OdResult getFingerprintGuid(OdChar*&) const;
  OdResult setFingerprintGuid(const OdChar*);

  OdResult getVersionGuid(OdChar*&) const;
  OdResult setVersionGuid(const OdChar*);

  /** \details
    Returns the current formatter for units in this database.
  */  
  virtual OdDbUnitsFormatter& formatter();

  /** \details
    Enables graphics flushing.
    
    \param bEnable [in] A flag which determines whether graphic flushing is enabled (true) or not (false).
  */  
  void enableGraphicsFlush(bool bEnable);
  
  /** \details
    Flushes the graphics in this database.
  */  
  void flushGraphics();

// ODA_MT_DB_BEGIN
  /** \details 
    If multi-threaded mode is on, the method returns true. In the other case it returns false. 
  */
  bool isMultiThreadedMode() const;
  
  /** \details 
    Returns which multi-threaded mode the database currently uses. 
    
    \remarks 
    Returns one of the following values:
    <table>
    Name                                    Value   Multi-Threaded mode
    OdDb::MultiThreadedMode::kSTMode        0       No multi-threaded, uses single-threaded mode.
    OdDb::MultiThreadedMode::kMTLoading     1       Multi-threaded data loading.
    OdDb::MultiThreadedMode::kMTRendering   2       Multi-threaded rendering.
  */
  OdDb::MultiThreadedMode multiThreadedMode() const;
  
    /** \details 
    Sets a new multi-threaded mode for the database. 
    
    \param  [in] A new value of multi-threaded mode to be set. 
    
    \remarks 
    New value can be one of the following:
    <table>
    Name                                    Value   Multi-threaded mode
    OdDb::MultiThreadedMode::kSTMode        0       No multi-threaded, uses single-threaded mode.
    OdDb::MultiThreadedMode::kMTLoading     1       Multi-threaded data loading.
    OdDb::MultiThreadedMode::kMTRendering   2       Multi-threaded rendering.
  */
  virtual void setMultiThreadedMode(OdDb::MultiThreadedMode);
// ODA_MT_DB_END
  
  /** \details 
    Sets a new annotation scale as a context object for this database. 
    \param val [in] A new value of annotation scale. 
    
    \sa 
    <link OdDbAnnotationScale, OdDbAnnotationScale class>
  */
  void setCannoscale(ODSYSDEF, OdDbAnnotationScale* val);

  //arx
  OdResult setCannoscale(OdDbAnnotationScale* val);
  /** \details 
    Returns the current annotation scale as a context object for this database. 
    
    \sa 
    <link OdDbAnnotationScale, OdDbAnnotationScale class>
  */
  OdDbAnnotationScalePtr cannoscale(ODSYSDEF) const;

  //arx
  OdDbAnnotationScale* cannoscale() const;

  //当前激活视口的比例，相当于系统变量值
  OdDbAnnotationScale* cvannoscale() const;
  
  OdDbObjectId   dataLinkDictionaryId(void) const;
  OdDbDictionaryPtr dataLinkDictionary(OdDb::OpenMode mode);

  OdDbDataLinkManager* getDataLinkManager(void) const;
  /** \details 
    Returns the true if OdDbDatabase instance is restricted to use only core objects.
    In such mode implementation of OdDbDatabase::initialize() for example will not create some objects
    like dimension style table and default dimension style or default multi-line style.
    Default implementation simply returns 'false'
  */
  virtual bool usingCoreOnly() const;

  /** \details
    Enqueues the object paging, mark it for paging in next call to pageObjects().  

    \remarks
    See Paging Support for details.
  */
  bool enqueuePaging(const OdDbObjectId &id);

  /** \details
    Pages the database objects that have been marked for paging since the last call to this function.  

    \remarks
    See Paging Support for details.
  */
  bool pageObjects();

  /** \details
    \returns OdDb::IndexingModeFlags combination

  */
  int indexingMode() const;

  /** \details
    \param nIndexingModeBitFlags[in] OdDb::IndexingModeFlags combination

  */
  void setIndexingMode(int nIndexingModeBitFlags);

  /** \details
    Returns true if per object converting mode is used for this database object.
  */
  bool isPerObjectConverting() const;

  OdResult getVisualStyleList(OdArray<const OdChar*> & vstyleList);
private:
  friend class OdDbDatabaseImpl;
  OdDbDatabaseImpl* m_pImpl;
};

TOOLKIT_EXPORT OdResult oddbGetExtnames(bool& value, OdDbDatabase* pDb);
TOOLKIT_EXPORT OdResult oddbSetExtnames(OdDbDatabase* pDb, bool value);

  /** \details
  */
TOOLKIT_EXPORT OdUInt32 getGapsAmount(OdDbDatabase* pDb);
TOOLKIT_EXPORT OdRxClass* getClassByName(OdDbDatabase* pDb, const OdString& className);

/** \details
   Verify drawing Digital Signature if exists.

   \param drawingFullPath [in] Full path to the drawing file to verify the signature.
   \param verificationResult  [out] Verification result.
   \param signatureDesc       [out] Data structure into which signature description data will be placed.

   \returns
   Returns eOk if the verification process completed without errors, and verificationResult contains the verification result.
   Returns eCantOpenFile if can't open the drawing file specified by drawingFullPath.
   Returns eInvalidInput if the drawing file has a version for which the verification process can not be performed.   
*/
DBIO_EXPORT OdResult validateDrawingSignature(const OdString& drawingFullPath, 
  OdCryptoServices::OdSignatureVerificationResult& verificationResult, 
  OdSignatureDescription& signatureDesc);

/** Fills in the OdThumbnailImage object from stream. Throws appropriate exception if an error occurred.
*/

TOOLKIT_EXPORT void odDbGetPreviewBitmap(OdStreamBuf* pStreamBuf, OdThumbnailImage* pPreview);


// The functions below provide write access to "Read-Only" *database* variables.
// Actually they are a OdDb::kludge for bypassing non-implemented DD functionality
// or to repair invalid drawings.
// They should be used with care.

/** \details
    Sets the DWGCODEPAGE value in the specified OdDbDatabase instance.

    \param db [in]  Database.
    \param val [in]  Value for DWGCODEPAGE.

    \remarks
    This function provides write access to "Read-Only" system variables.
    It may be used to bypass non-implemented Drawings functionality or to repair drawings,
    and should be used with care.
*/
TOOLKIT_EXPORT void odDbSetDWGCODEPAGE(
  OdDbDatabase& db,
  OdCodePageId val);

/** \details
    Sets the TDUCREATE system variable in the specified OdDbDatabase instance.

    \param db [in]  Database.
    \param val [in]  Value for TDUCREATE.

    \remarks
    This function provides write access to "Read-Only" system variables.
    It may be used to bypass non-implemented Drawings functionality or to repair drawings,
    and should be used with care.
*/
TOOLKIT_EXPORT void odDbSetTDUCREATE(
  OdDbDatabase& db,
  OdDbDate val);

/** \details
    Sets the TDUUPDATE value in the specified OdDbDatabase instance.

    \param db [in]  Database.
    \param val [in]  Value for TDUUPDATE.

    \remarks
    This function provides write access to "Read-Only" system variables.
    It may be used to bypass non-implemented Drawings functionality or to repair drawings,
    and should be used with care.
*/
TOOLKIT_EXPORT void odDbSetTDUUPDATE(
  OdDbDatabase& db,
  OdDbDate val);

/** \details
    Sets the TDINDWG value in the specified OdDbDatabase instance.

    \param db [in]  Database.
    \param val [in]  Value for TDINDWG.

    \remarks
    This function provides write access to "Read-Only" system variables.
    It may be used to bypass non-implemented Drawings functionality or to repair drawings,
    and should be used with care.
*/
TOOLKIT_EXPORT void odDbSetTDINDWG(
  OdDbDatabase& db,
  OdDbDate val);

/** \details
    Sets the TDUSRTIMER value in the specified OdDbDatabase instance.

    \param db [in]  Database.
    \param val [in]  Value for TDUSRTIMER.

    \remarks
    This function provides write access to "Read-Only" system variables.
    It may be used to bypass non-implemented Drawings functionality or to repair drawings,
    and should be used with care.
*/
TOOLKIT_EXPORT void odDbSetTDUSRTIMER(
  OdDbDatabase& db,
  OdDbDate val);

/** \details
    Sets the PSTYLEMODE value in the specified OdDbDatabase instance.

    \param db [in]  Database.
    \param val [in]  Value for PSTYLEMODE.

    \remarks
    This function provides write access to "Read-Only" system variables.
    It may be used to bypass non-implemented Drawings functionality or to repair drawings,
    and should be used with care.
*/
TOOLKIT_EXPORT void odDbSetPSTYLEMODE(
  OdDbDatabase& db,
  bool val);

/** \details
    Sets the UCSORG system variable in the specified OdDbDatabase instance.

    \param db [in]  Database.
    \param val [in]  Value for UCSORG.

    \remarks
    This function provides write access to "Read-Only" system variables.
    It may be used to bypass non-implemented Drawings functionality or to repair drawings,
    and should be used with care.
*/
TOOLKIT_EXPORT void odDbSetUCSORG(
  OdDbDatabase& db,
  OdGePoint3d val);

/** \details
    Sets the UCSXDIR value in the specified OdDbDatabase instance.

    \param db [in]  Database.
    \param val [in]  Value for UCSXDIR.

    \remarks
    This function provides write access to "Read-Only" system variables.
    It may be used to bypass non-implemented Drawings functionality or to repair drawings,
    and should be used with care.
*/
TOOLKIT_EXPORT void odDbSetUCSXDIR(
  OdDbDatabase& db,
  OdGeVector3d val);

/** \details
    Sets the UCSYDIR value in the specified OdDbDatabase instance.

    \param db [in]  Database.
    \param val [in]  Value for UCSYDIR.

    \remarks
    This function provides write access to "Read-Only" system variables.
    It may be used to bypass non-implemented Drawings functionality or to repair drawings,
    and should be used with care.
*/
TOOLKIT_EXPORT void odDbSetUCSYDIR(
  OdDbDatabase& db,
  OdGeVector3d val);

/** \details
    Sets the PUCSORG value in the specified OdDbDatabase instance.

    \param db [in]  Database.
    \param val [in]  Value for PUCSORG.

    \remarks
    This function provides write access to "Read-Only" system variables.
    It may be used to bypass non-implemented Drawings functionality or to repair drawings,
    and should be used with care.
*/
TOOLKIT_EXPORT void odDbSetPUCSORG(
  OdDbDatabase& db,
  OdGePoint3d val);

/** \details
    Sets the PUCSXDIR value in the specified OdDbDatabase instance.

    \param db [in]  Database.
    \param val [in]  Value for PUCSXDIR.

    \remarks
    This function provides write access to "Read-Only" system variables.
    It may be used to bypass non-implemented Drawings functionality or to repair drawings,
    and should be used with care.
*/
TOOLKIT_EXPORT void odDbSetPUCSXDIR(
  OdDbDatabase& db,
  OdGeVector3d val);

/** \details
    Sets the PUCSYDIR value in the specified OdDbDatabase instance.

    \param db [in]  Database.
    \param val [in]  Value for PUCSYDIR.

    \remarks
    This function provides write access to "Read-Only" system variables.
    It may be used to bypass non-implemented Drawings functionality or to repair drawings,
    and should be used with care.
*/
TOOLKIT_EXPORT void odDbSetPUCSYDIR(
  OdDbDatabase& db,
  OdGeVector3d val);

/** Description:
    Sets the LASTPOINT value in the specified OdDbDatabase instance.

    Arguments:
    db (I) Database.
    val (I) Value for LASTPOINT.

    Note:
    This function provides write access to "Read-Only" system variables.
    It may be used to bypass non-implemented Teigha functionality or to repair drawings,
    and should be used with care.
*/
TOOLKIT_EXPORT void odDbSetLASTPOINT(
  OdDbDatabase& db,
  const OdGePoint3d& pnt);

 /** \details
    Saves linetypes to the specified file.
    \param db [in]  OdDbDatabase object.
    \param filename [in]  Name of the linetype file to save.
		\param encode [in]  Encoding used for writing linetype text files.
 */
extern TOOLKIT_EXPORT void odDbSaveLineTypeFile(OdDbDatabase &Db, OdStreamBuf &filename, OdDb::TextFileEncoding encode = OdDb::kTextFileEncodingDefault);

 /** \details
    Loads an MLineStyle into the specified database object.

    \param db [in]  OdDbDatabase object.
    \param patternName [in]  Name of the pattern to load.
    \param filename [in]  Name of the MlineStyle file from which to load.
    \param dlt [in]  Duplicate linetype loading.
    \remarks
    dlt must be one of the following:

    <table>
    Name                        Value   Description
    OdDb::kDltNotApplicable     0       Not Applicable.
    OdDb::kDltIgnore            1       Ignore duplicate linetypes.
    OdDb::kDltReplace           2       Replace duplicate linetypes.
    </table>

    Throws:
    An appropriate error if not successful.
 */
extern DBENT_EXPORT void odDbLoadMlineStyleFile(
  OdDbDatabase &db,
  const OdString& patternName,
    OdStreamBuf &filename,
  OdDb::DuplicateLinetypeLoading dlt = OdDb::kDltNotApplicable );

 /** \details
    Saves an MLineStyle to the specified file.
    \param db [in]  OdDbDatabase object.
    \param filename [in]  Name of the MlineStyle file to save.
 */
extern DBENT_EXPORT void odDbSaveMlineStyleFile(OdDbDatabase &Db, OdStreamBuf &filename );

namespace OdDb
{
  /** \details 
    Returns a specified .dwg version as a null terminated string. 
    \param ver [in] A .dwg version value to be converted to string.
  */
  TOOLKIT_EXPORT const char* DwgVersionToStr(DwgVersion ver);

  /** \details 
    Returns the .dwg version value from a null-terminated string. 
    \param ver [in] A pointer to a null-terminated string, from which the version value should be converted.
  */
  TOOLKIT_EXPORT DwgVersion DwgVersionFromStr(const char* str);
}

class OdDbDataLinkManager;
DBENT_EXPORT OdDbDataLinkManager* odDbGetDataLinkManager(OdDbDatabase* db);

/**
  <group !!RECORDS_tdrawings_apiref>
*/
struct TOOLKIT_EXPORT OdMTLoadReactor
{
  /** \details
  This function is continuously queried during partial loading process, to stop it if necessary.
  */
  virtual bool shouldInterrupt() { return false; }
  /** \details
  This function notifies detected block references for further processing
  */
  virtual void insertDetected(OdDbObjectId id) {}
  /** \details
  This function returns database access mutex
  */
  virtual OdMutex* accessMutex() { return NULL; }
};

TOOLKIT_EXPORT OdDb::DwgDataType oddbGroupCodeToType(OdDb::DxfCode pCode);
TOOLKIT_EXPORT OdResult oddbGetObjectId(OdDbObjectId& objId, const gds_name objName);
TOOLKIT_EXPORT OdResult oddbGetGdsName(gds_name& objName, OdDbObjectId objId);

TOOLKIT_EXPORT OdArray<OdDbDatabase *> & gcdbActiveDatabaseArray();

TOOLKIT_EXPORT bool gcdbIsPersistentReactor(const void * pSomething);
TOOLKIT_EXPORT OdDbObjectId gcdbPersistentReactorObjectId(const void * pSomething);

TOOLKIT_EXPORT OdResult oddbSetReferenced(OdDbObjectId objId);


#include "TD_PackPop.h"

#endif /* _ODDBDATABASE_INCLUDED_ */

