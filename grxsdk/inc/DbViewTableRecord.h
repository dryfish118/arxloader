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




#ifndef _ODDBVIEWTABLERECORD_INCLUDED
#define _ODDBVIEWTABLERECORD_INCLUDED

#include "TD_PackPush.h"

#include "DbAbstractViewTableRecord.h"
#include "DbAnnotationScale.h"
#include "DbObject.h"
#include "DwgDeclareMembers.h"

/** \details
    This class represents View records in the OdDbViewTable in an OdDbDatabase instance.

    <group OdDb_Classes>
*/

namespace Otil
{
  class Image;
  class FileReadDescriptor;
}

class TOOLKIT_EXPORT OdDbViewTableRecord : public OdDbAbstractViewTableRecord
{
public:
  DWGMAP_DECLARE_MEMBERS(OdDbViewTableRecord);

  OdDbViewTableRecord();

  /** \details
    Returns true if and only if this View is a Paper Space view (DXF 70, bit 0x01).
  */
  bool isPaperspaceView() const;
  
  /** \details
    Controls if this View is a Paper Space view (DXF 70, bit 0x01).
    
    \param pspaceView [in]  True for Paper Space, false for Model space.
  */
  void setIsPaperspaceView(
    bool pspaceView);
  
  /** \details
    Returns true if and only if there is a UCS associated with this View.
  */
  bool isUcsAssociatedToView() const;
  /** \details
    Disassociates any UCS associated with this View.
  */
  OdResult disassociateUcsFromView();

  virtual OdResult dwgInFields(
    OdDbDwgFiler* pFiler);

  virtual OdResult dwgOutFields(
    OdDbDwgFiler* pFiler) const;

  virtual OdResult dxfInFields(
    OdDbDxfFiler* pFiler);

  virtual OdResult dxfOutFields(
    OdDbDxfFiler* pFiler) const;

  virtual OdResult dxfInFields_R12(
    OdDbDxfFiler* pFiler);

  virtual void dxfOutFields_R12(
    OdDbDxfFiler* pFiler) const;

  virtual OdResult subGetClassID(
    CLSID* pClsid) const;

  // new in 2005
  
  /** \details
    Returns the name of the category of this View.
  */
  OdString getCategoryName() const;
  OdResult getCategoryName(OdChar *& categoryName) const;
  /** \details
    Sets the name of the category of this View.
    \param categoryName [in]  Category name.
  */
  void setCategoryName(ODSYSDEF,
    const OdString& categoryName);
  OdResult setCategoryName(
    const OdChar * categoryName);
  /** \details
    Returns the name of the layer state of this View.
  */
  OdString getLayerState() const;
  OdResult getLayerState(OdChar*& layerStateName) const;

  /** \details
    Sets the name of the layer state of this View.
    \param layerStateName [in]  Layer State name.
  */
  OdResult setLayerState(ODSYSDEF,
    const OdString& layerStateName);

  OdResult setLayerState(
    const OdChar * layerStateName);
  /** \details
    Returns the Object ID of the OdDbLayout of this View.
  */
  OdDbObjectId getLayout() const;
  OdResult getLayout(OdDbObjectId& layoutId) const;
  /** \details
    Sets the Object ID of the Layout of this View.
    \param layoutId [in]  Layout ID.
  */
  OdResult setLayout(OdDbObjectId layoutId);

  /** \details
    Returns true if and only if this View is associated with a Paper Space Viewport.
  */
  bool isViewAssociatedToViewport() const;
  
  /** \details
    Controls if this View is associated with a Viewport.
    \param viewAssociated [in]  Controls association.
  */
  OdResult setViewAssociatedToViewport (bool viewAssociated);

  /** \details
    Returns the thumbnail information for this view.
    
    \param pThumbnail [out]  Receives a pointer to the thumbnail.
    
    \remarks
    Thumbnail information consists of a packed BITMAPINFO structure 
    immediately followed in memory by the thumbnail data.
  */
  void getThumbnail (
    OdBinaryData* pThumbnail) const;
  OdResult getThumbnail(BITMAPINFO*& thumbnail) const;
  /** \details
    Sets the thumbnail information for this view.
    
    \param pThumbnail [in]  Pointer to the thumbnail.

    \remarks
    Thumbnail information consists of a packed BITMAPINFO structure 
    immediately followed in memory by the thumbnail data.
  */
  void setThumbnail(
    const OdBinaryData* pThumbnail);

  OdResult setThumbnail(const BITMAPINFO * thumbnail);

  OdResult getPreviewImage(Otil::Image*& pPreviewImage) const;

  OdResult setPreviewImage(const Otil::Image * pPreviewImage);

  OdResult setParametersFromViewport(OdDbObjectId objId);
  
  // new R21 methods
  
  bool isCameraPlottable () const;
  OdResult setIsCameraPlottable(bool plottable);

  OdDbObjectId camera() const;
  OdResult setCamera(const OdDbObjectId &cameraId);

  virtual OdResult subClose();

  virtual OdResult subSwapIdWith(
    const OdDbObjectId& otherId,
    bool swapXdata = false,
    bool swapExtDict = false);

  // Live Section

  OdDbObjectId liveSection() const;
  OdResult setLiveSection(const OdDbObjectId& liveSectionId);

  OdResult setAnnotationScale(const OdDbAnnotationScale* pScaleObj);
  OdDbAnnotationScalePtr annotationScale(ODSYSDEF) const;
  OdDbAnnotationScale* annotationScale() const;
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdDbViewTableRecord object pointers.
*/
typedef OdSmartPtr<OdDbViewTableRecord> OdDbViewTableRecordPtr;

#include "TD_PackPop.h"

#endif // _ODDBVIEWTABLERECORD_INCLUDED

