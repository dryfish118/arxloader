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

#ifndef __OD_GI_SHM_DATA_STORAGE__
#define __OD_GI_SHM_DATA_STORAGE__

#include "Gi/GiGeometry.h"
#include "Ge/GeVector3dArray.h"
#include "DbStubPtrArray.h"
#include "CmEntityColorArray.h"
#include "CmTransparencyArray.h"
#include "UInt8Array.h"
#include "UInt32Array.h"
#include "Int32Array.h"
#include "UInt16Array.h"
#include "GsMarkerArray.h"
#include "IdArrays.h"
/** \details
  Edge data storage class.

  <group OdGi_Classes>
*/

typedef OdArray<short, OdMemoryAllocator<short> > OdShortArray;

    //DOM-IGNORE-BEGIN
class OdGiEdgeDataStorage : public OdGiEdgeData
{
  protected:
    OdShortArray m_colors;
    OdCmEntityColorArray m_trueColors;    
    OdDbObjectIdArray m_layers;
    //DOM-IGNORE-END
    OdDbObjectIdArray m_linetypes;
    /** \details
      Default constructor for objects of the OdGiEdgeDataStorage class.
    */
    OdArray<OdLongPtr> m_selMarkers;
    OdUInt8Array m_visibilities;

    /** \details
      Retrieves the colors array of this OdGiEdgeDataStorage object.

      \returns
      Array of colors.
    */
  public:

    /** \details
      Retrieves the colors array of this OdGiEdgeDataStorage object.

      \returns
      Array of colors.
    */
    OdGiEdgeDataStorage() : OdGiEdgeData() { }

    /** \details
      Sets the colors array.
    */


    /** \details
      Resizes the colors array.

      \param nSize   [in] New colors array size.
      \param bSetPtr [in] True to set the colors array after resizing.

      \returns
      Pointer to the array of colors.
    */
    const OdShortArray &colorsArray() const { return m_colors; }
    OdShortArray &colorsArray() { return m_colors; }

    /** \details
      Retrieves the true colors array of this OdGiEdgeDataStorage object.

      \returns
      Array of true colors.
    */
    void setColorsArray() { setColors(m_colors.getPtr()); }

    /** \details
      Retrieves the true colors array of this OdGiEdgeDataStorage object.

      \returns
      Array of true colors.
    */
    short *resizeColorsArray(OdUInt32 nSize, bool bSetPtr = true) { m_colors.resize(nSize); if (bSetPtr) setColorsArray(); return m_colors.asArrayPtr(); }

    /** \details
      Sets the true colors array.
    */


    /** \details
      Resizes the true colors array.

      \param nSize   [in] New true colors array size.
      \param bSetPtr [in] True to set the true colors array after resizing.

      \returns
      Pointer to the array of true colors.
    */
    const OdCmEntityColorArray &trueColorsArray() const { return m_trueColors; }
    OdCmEntityColorArray &trueColorsArray() { return m_trueColors; }

    /** \details
      Retrieves the layers array of this OdGiEdgeDataStorage object.

      \returns
      Array of layers.
    */
    void setTrueColorsArray() { setTrueColors(m_trueColors.getPtr()); }

    /** \details
      Retrieves the layers array of this OdGiEdgeDataStorage object.

      \returns
      Array of layers.
    */
    OdCmEntityColor *resizeTrueColorsArray(OdUInt32 nSize, bool bSetPtr = true) { m_trueColors.resize(nSize); if (bSetPtr) setTrueColorsArray(); return m_trueColors.asArrayPtr(); }

    /** \details
      Sets the layers array.
    */


    /** \details
      Resizes the layers array.

      \param nSize   [in] New layers array size.
      \param bSetPtr [in] True to set the layers array after resizing.

      \returns
      Pointer to the array of layers.
    */
    const OdDbObjectIdArray &layerIdsArray() const { return m_layers; }
    OdDbObjectIdArray &layerIdsArray() { return m_layers; }

    /** \details
      Retrieves the linetype IDs array of this OdGiEdgeDataStorage object.

      \returns
      Array of linetype IDs.
    */
    void setLayersArray() { setLayers(const_cast<OdDbObjectId*>(m_layers.getPtr())); }

    /** \details
      Retrieves the linetype IDs array of this OdGiEdgeDataStorage object.

      \returns
      Array of linetype IDs.
    */
    OdDbObjectId*resizeLayerIdsArray(OdUInt32 nSize, bool bSetPtr = true) { m_layers.resize(nSize); if (bSetPtr) setLayersArray(); return m_layers.asArrayPtr(); }

    /** \details
      Sets the linetype IDs array.
    */


    /** \details
      Resizes the linetype IDs array.

      \param nSize   [in] New linetype IDs array size.
      \param bSetPtr [in] True to set the linetype IDs array after resizing.

      \returns
      Pointer to the array of linetype IDs.
    */
    const OdDbObjectIdArray &linetypeIdsArray() const { return m_linetypes; }
    OdDbObjectIdArray &linetypeIdsArray() { return m_linetypes; }

    /** \details
      Retrieves the selection markers array of this OdGiEdgeDataStorage object.

      \returns
      Array of selection markers.
    */
    void setLinetypesArray() { setLineTypes(const_cast<OdDbObjectId*>(m_linetypes.getPtr())); }

    /** \details
      Retrieves the selection markers array of this OdGiEdgeDataStorage object.

      \returns
      Array of selection markers.
    */
    OdDbObjectId*resizeLinetypeIdsArray(OdUInt32 nSize, bool bSetPtr = true) { m_linetypes.resize(nSize); if (bSetPtr) setLinetypesArray(); return m_linetypes.asArrayPtr(); }

    /** \details
      Sets the selection markers array.
    */


    /** \details
      Resizes the selection markers array.

      \param nSize   [in] New selection markers array size.
      \param bSetPtr [in] True to set the selection markers array after resizing.

      \returns
      Pointer to the array of selection markers.
    */
    const OdArray<OdLongPtr> &selectionMarkersArray() const { return m_selMarkers; }
    OdArray<OdLongPtr> &selectionMarkersArray() { return m_selMarkers; }

    /** \details
      Retrieves the visibilities array of this OdGiEdgeDataStorage object.

      \returns
      Array of visibilities.
    */
    void setSelectionMarkersArray() { setSelectionMarkers(m_selMarkers.getPtr()); }

    /** \details
      Retrieves the visibilities array of this OdGiEdgeDataStorage object.

      \returns
      Array of visibilities.
    */
    OdGsMarker *resizeSelectionMarkersArray(OdUInt32 nSize, bool bSetPtr = true) { m_selMarkers.resize(nSize); if (bSetPtr) setSelectionMarkersArray(); return m_selMarkers.asArrayPtr(); }

    /** \details
      Sets the visibilities array.
    */


    /** \details
      Resizes the visibilities array.

      \param nSize   [in] New visibilities array size.
      \param bSetPtr [in] True to set the visibilities array after resizing.

      \returns
      Pointer to the array of visibilities.
    */
    const OdUInt8Array &visibilityArray() const { return m_visibilities; }
    OdUInt8Array &visibilityArray() { return m_visibilities; }

    /** \details
      Clones data of the specified OdGiEdgeData object.

      \param pData [in] OdGiEdgeData object, data of which to be cloned by this OdGiEdgeDataStorage object.
    */
    void setVisibilityArray() { setVisibility(m_visibilities.getPtr()); }

    /** \details
      Resets all array pointers of this OdGiEdgeDataStorage object to NULL.

      \remarks
      Resets the following array pointers: colors, true colors, layer IDs,
      linetypes, selection markers, visibilities.
    */
    OdUInt8 *resizeVisibilityArray(OdUInt32 nSize, bool bSetPtr = true) { m_visibilities.resize(nSize); if (bSetPtr) setVisibilityArray(); return m_visibilities.asArrayPtr(); }

    void cloneData(const OdGiEdgeData *pData) { *(OdGiEdgeData*)this = *pData; }
    void resetPointers()
    {
      setColors(NULL);
      setTrueColors(NULL);
      setLayers(NULL);
      setLineTypes(NULL);

    /** \details
      Sets all arrays of this OdGiEdgeDataStorage object using data from the
      specified OdGiEdgeData object.

      \param pEdgeData [in] Object to use data for setting arrays.

      \remarks
      Sets the following arrays: colors, true colors, layer IDs, linetypes,
      selection markers, visibilities.
    */
      setSelectionMarkers(NULL);
      setVisibility(NULL);
    }
    void setPointersArray(const OdGiEdgeData *pEdgeData = NULL)
    {
      if (!pEdgeData || pEdgeData->colors()) setColorsArray();
      if (!pEdgeData || pEdgeData->trueColors()) setTrueColorsArray();
      if (!pEdgeData || pEdgeData->layerIds()) setLayersArray();
      if (!pEdgeData || pEdgeData->linetypeIds()) setLinetypesArray();

    /** \details
      Clears all arrays of the specified OdGiEdgeData object.

      \param pEdgeData [in] Object to clear arrays of.

      \remarks
      Clears the following arrays: colors, true colors, layer IDs, linetypes,
      selection markers, visibilities.
    */
      if (!pEdgeData || pEdgeData->selectionMarkers()) setSelectionMarkersArray();
      if (!pEdgeData || pEdgeData->visibility()) setVisibilityArray();
    }
    void clearArrays(const OdGiEdgeData *pEdgeData = NULL)
    {
      if (!pEdgeData || pEdgeData->colors()) m_colors.clear();
      if (!pEdgeData || pEdgeData->trueColors()) m_trueColors.clear();
      if (!pEdgeData || pEdgeData->layerIds()) m_layers.clear();
      if (!pEdgeData || pEdgeData->linetypeIds()) m_linetypes.clear();

    /** \details
      Deletes all arrays of the specified OdGiEdgeData object.

      \param pEdgeData [in] Object to delete arrays of.

      \remarks
      Deletes the following arrays: colors, true colors, layer IDs, linetypes,
      selection markers, visibilities.
    */
      if (!pEdgeData || pEdgeData->selectionMarkers()) m_selMarkers.clear();
      if (!pEdgeData || pEdgeData->visibility()) m_visibilities.clear();
    }
    void deleteArrays(const OdGiEdgeData *pEdgeData = NULL)
    {
      if (!pEdgeData || pEdgeData->colors()) m_colors.setPhysicalLength(0);
      if (!pEdgeData || pEdgeData->trueColors()) m_trueColors.setPhysicalLength(0);
      if (!pEdgeData || pEdgeData->layerIds()) m_layers.setPhysicalLength(0);
      if (!pEdgeData || pEdgeData->linetypeIds()) m_linetypes.setPhysicalLength(0);

    /** \details
      Reserves cells in all arrays of the specified OdGiEdgeData object.

      \param pEdgeData [in] Object which arrays to reserve cells in.
      \param nReserve  [in] Number of cells to reserve.

      \remarks
      Reserves cells in the following arrays: colors, true colors, layer IDs,
      linetypes, selection markers, visibilities.
    */
      if (!pEdgeData || pEdgeData->selectionMarkers()) m_selMarkers.setPhysicalLength(0);
      if (!pEdgeData || pEdgeData->visibility()) m_visibilities.setPhysicalLength(0);
    }
    void reserveArrays(const OdGiEdgeData *pEdgeData, OdUInt32 nReserve)
    {
      if (!pEdgeData || pEdgeData->colors()) m_colors.reserve(nReserve);
      if (!pEdgeData || pEdgeData->trueColors()) m_trueColors.reserve(nReserve);
      if (!pEdgeData || pEdgeData->layerIds()) m_layers.reserve(nReserve);
      if (!pEdgeData || pEdgeData->linetypeIds()) m_linetypes.reserve(nReserve);

    /** \details
      Copies elements with the specified index from all arrays of the specified
      OdGiEdgeData object and appends them to arrays of this OdGiEdgeDataStorage
      object.

      \param pEdgeData [in] Object to copy array elements from.
      \param nEdge     [in] Index of the elements in arrays.

      \remarks
      Copies elements from the following arrays: colors, true colors, layer IDs,
      linetypes, selection markers, visibilities.
    */
      if (!pEdgeData || pEdgeData->selectionMarkers()) m_selMarkers.reserve(nReserve);
      if (!pEdgeData || pEdgeData->visibility()) m_visibilities.reserve(nReserve);
    }
    void copyFrom(const OdGiEdgeData *pEdgeData, OdUInt32 nEdge)
    {
      if (pEdgeData && pEdgeData->colors()) m_colors.push_back(pEdgeData->colors()[nEdge]);
      if (pEdgeData && pEdgeData->trueColors()) m_trueColors.push_back(pEdgeData->trueColors()[nEdge]);
      if (pEdgeData && pEdgeData->layerIds()) m_layers.push_back(pEdgeData->layerIds()[nEdge]);
      if (pEdgeData && pEdgeData->linetypeIds()) m_linetypes.push_back(pEdgeData->linetypeIds()[nEdge]);
      if (pEdgeData && pEdgeData->selectionMarkers()) m_selMarkers.push_back(pEdgeData->selectionMarkers()[nEdge]);
      if (pEdgeData && pEdgeData->visibility()) m_visibilities.push_back(pEdgeData->visibility()[nEdge]);
/** \details
  Face data storage class.

  <group OdGi_Classes>
*/
    }
};

    /** \details
      Material mapper object array data type definition.
    */
class OdGiFaceDataStorage : public OdGiFaceData
{
    //DOM-IGNORE-BEGIN
  public:
    typedef OdArray<OdGiMapper, OdMemoryAllocator<OdGiMapper> > OdGiMapperArray;
  protected:
    OdShortArray m_colors;
    OdCmEntityColorArray m_trueColors;
    OdDbObjectIdArray m_layers;
    OdArray<OdLongPtr> m_markers;
    OdGeVector3dArray m_normals;
    OdUInt8Array m_visibilities;
    //DOM-IGNORE-END
    OdDbObjectIdArray m_materials;

    /** \details
      Default constructor for objects of the OdGiFaceDataStorage class.
    */
    OdGiMapperArray m_mappers;
    OdCmTransparencyArray m_transparencies;

    /** \details
      Retrieves the colors array of this OdGiFaceDataStorage object.

      \returns
      Array of colors.
    */
  public:

    /** \details
      Retrieves the colors array of this OdGiFaceDataStorage object.

      \returns
      Array of colors.
    */
    OdGiFaceDataStorage() : OdGiFaceData() { }

    /** \details
      Sets the colors array.
    */


    /** \details
      Resizes the colors array.

      \param nSize   [in] New colors array size.
      \param bSetPtr [in] True to set the colors array after resizing.

      \returns
      Pointer to the array of colors.
    */
    const OdShortArray &colorsArray() const { return m_colors; }
    OdShortArray &colorsArray() { return m_colors; }

    /** \details
      Retrieves the true colors array of this OdGiFaceDataStorage object.

      \returns
      Array of true colors.
    */
    void setColorsArray() { setColors(m_colors.getPtr()); }

    /** \details
      Retrieves the true colors array of this OdGiFaceDataStorage object.

      \returns
      Array of true colors.
    */
    short *resizeColorsArray(OdUInt32 nSize, bool bSetPtr = true) { m_colors.resize(nSize); if (bSetPtr) setColorsArray(); return m_colors.asArrayPtr(); }

    /** \details
      Sets the true colors array.
    */


    /** \details
      Resizes the true colors array.

      \param nSize   [in] New true colors array size.
      \param bSetPtr [in] True to set the true colors array after resizing.

      \returns
      Pointer to the array of true colors.
    */
    const OdCmEntityColorArray &trueColorsArray() const { return m_trueColors; }
    OdCmEntityColorArray &trueColorsArray() { return m_trueColors; }

    /** \details
      Retrieves the layer IDs array of this OdGiFaceDataStorage object.

      \returns
      Array of layer IDs.
    */
    void setTrueColorsArray() { setTrueColors(m_trueColors.getPtr()); }

    /** \details
      Retrieves the layer IDs array of this OdGiFaceDataStorage object.

      \returns
      Array of layer IDs.
    */
    OdCmEntityColor *resizeTrueColorsArray(OdUInt32 nSize, bool bSetPtr = true) { m_trueColors.resize(nSize); if (bSetPtr) setTrueColorsArray(); return m_trueColors.asArrayPtr(); }

    /** \details
      Sets the layer IDs array.
    */


    /** \details
      Resizes the layer IDs array.

      \param nSize   [in] New layer IDs array size.
      \param bSetPtr [in] True to set the layer IDs array after resizing.

      \returns
      Pointer to the array of layer IDs.
    */
    const OdDbObjectIdArray &layerIdsArray() const { return m_layers; }
    OdDbObjectIdArray &layerIdsArray() { return m_layers; }

    /** \details
      Retrieves the selection markers array of this OdGiFaceDataStorage object.

      \returns
      Array of selection markers.
    */
    void setLayersArray() { setLayers(m_layers.getPtr()); }

    /** \details
      Retrieves the selection markers array of this OdGiFaceDataStorage object.

      \returns
      Array of selection markers.
    */
    OdDbObjectId*resizeLayerIdsArray(OdUInt32 nSize, bool bSetPtr = true) { m_layers.resize(nSize); if (bSetPtr) setLayersArray(); return m_layers.asArrayPtr(); }

    /** \details
      Sets the selection markers array.
    */


    /** \details
      Resizes the selection markers array.

      \param nSize   [in] New selection markers array size.
      \param bSetPtr [in] True to set the selection markers array after resizing.

      \returns
      Pointer to the array of selection markers.
    */
    const OdArray<OdLongPtr> &selectionMarkersArray() const { return m_markers; }
    OdArray<OdLongPtr> &selectionMarkersArray() { return m_markers; }

    /** \details
      Retrieves the normals array of this OdGiFaceDataStorage object.

      \returns
      Array of normals.
    */
    void setSelectionMarkersArray() { setSelectionMarkers(m_markers.getPtr()); }

    /** \details
      Retrieves the normals array of this OdGiFaceDataStorage object.

      \returns
      Array of normals.
    */
    OdLongPtr *resizeSelectionMarkersArray(OdUInt32 nSize, bool bSetPtr = true) { m_markers.resize(nSize); if (bSetPtr) setSelectionMarkersArray(); return m_markers.asArrayPtr(); }

    /** \details
      Sets the normals array.
    */


    /** \details
      Resizes the normals array.

      \param nSize   [in] New normals array size.
      \param bSetPtr [in] True to set the normals array after resizing.

      \returns
      Pointer to the array of normals.
    */
    const OdGeVector3dArray &normalsArray() const { return m_normals; }
    OdGeVector3dArray &normalsArray() { return m_normals; }

    /** \details
      Retrieves the visibilities array of this OdGiFaceDataStorage object.

      \returns
      Array of visibilities.
    */
    void setNormalsArray() { setNormals(m_normals.getPtr()); }

    /** \details
      Retrieves the visibilities array of this OdGiFaceDataStorage object.

      \returns
      Array of visibilities.
    */
    OdGeVector3d *resizeNormalsArray(OdUInt32 nSize, bool bSetPtr = true) { m_normals.resize(nSize); if (bSetPtr) setNormalsArray(); return m_normals.asArrayPtr(); }

    /** \details
      Sets the visibilities array.
    */


    /** \details
      Resizes the visibilities array.

      \param nSize   [in] New visibilities array size.
      \param bSetPtr [in] True to set the visibilities array after resizing.

      \returns
      Pointer to the array of visibilities.
    */
    const OdUInt8Array &visibilityArray() const { return m_visibilities; }
    OdUInt8Array &visibilityArray() { return m_visibilities; }

    /** \details
      Retrieves the materials array of this OdGiFaceDataStorage object.

      \returns
      Array of materials.
    */
    void setVisibilityArray() { setVisibility(m_visibilities.getPtr()); }

    /** \details
      Retrieves the materials array of this OdGiFaceDataStorage object.

      \returns
      Array of materials.
    */
    OdUInt8 *resizeVisibilityArray(OdUInt32 nSize, bool bSetPtr = true) { m_visibilities.resize(nSize); if (bSetPtr) setVisibilityArray(); return m_visibilities.asArrayPtr(); }

    /** \details
      Sets the materials array.
    */


    /** \details
      Resizes the materials array.

      \param nSize   [in] New materials array size.
      \param bSetPtr [in] True to set the materials array after resizing.

      \returns
      Pointer to the array of materials.
    */
    const OdDbObjectIdArray &materialsArray() const { return m_materials; }
    OdDbObjectIdArray &materialsArray() { return m_materials; }

    /** \details
      Retrieves the material mappers array of this OdGiFaceDataStorage object.

      \returns
      Array of material mappers.
    */
    void setMaterialsArray() { setMaterials(m_materials.getPtr()); }

    /** \details
      Retrieves the material mappers array of this OdGiFaceDataStorage object.

      \returns
      Array of material mappers.
    */
    OdDbObjectId*resizeMaterialsArray(OdUInt32 nSize, bool bSetPtr = true) { m_materials.resize(nSize); if (bSetPtr) setMaterialsArray(); return m_materials.asArrayPtr(); }

    /** \details
      Sets the material mappers array.
    */


    /** \details
      Resizes the material mappers array.

      \param nSize   [in] New material mappers array size.
      \param bSetPtr [in] True to set the material mappers array after resizing.

      \returns
      Pointer to the array of material mappers.
    */
    const OdGiMapperArray &mappersArray() const { return m_mappers; }
    OdGiMapperArray &mappersArray() { return m_mappers; }

    /** \details
      Retrieves the transparencies array of this OdGiFaceDataStorage object.

      \returns
      Array of transparencies.
    */
    void setMappersArray() { setMappers(m_mappers.getPtr()); }

    /** \details
      Retrieves the transparencies array of this OdGiFaceDataStorage object.

      \returns
      Array of transparencies.
    */
    OdGiMapper *resizeMappersArray(OdUInt32 nSize, bool bSetPtr = true) { m_mappers.resize(nSize); if (bSetPtr) setMappersArray(); return m_mappers.asArrayPtr(); }

    /** \details
      Sets the transparencies array.
    */


    /** \details
      Resizes the transparencies array.

      \param nSize   [in] New transparencies array size.
      \param bSetPtr [in] True to set the transparencies array after resizing.

      \returns
      Pointer to the array of transparencies.
    */
    const OdCmTransparencyArray &transparencyArray() const { return m_transparencies; }
    OdCmTransparencyArray &transparencyArray() { return m_transparencies; }

    /** \details
      Clones data of the specified OdGiFaceData object.

      \param pData [in] OdGiFaceData object, data of which to be cloned by this OdGiFaceDataStorage object.
    */
    void setTransparencyArray() { setTransparency(m_transparencies.getPtr()); }

    /** \details
      Resets all array pointers of this OdGiFaceDataStorage object to NULL.

      \remarks
      Resets the following array pointers: colors, true colors, layer IDs,
      selection markers, normals, visibilities, materials, material mappers,
      transparencies.
    */
    OdCmTransparency *resizeTransparencyArray(OdUInt32 nSize, bool bSetPtr = true) { m_transparencies.resize(nSize); if (bSetPtr) setTransparencyArray(); return m_transparencies.asArrayPtr(); }

    void cloneData(const OdGiFaceData *pData) { *(OdGiFaceData*)this = *pData; }
    void resetPointers()
    {
      setColors(NULL);
      setTrueColors(NULL);
      setLayers(NULL);
      setSelectionMarkers(NULL);
      setNormals(NULL);
      setVisibility(NULL);
      setMaterials(NULL);

    /** \details
      Sets all arrays of this OdGiFaceDataStorage object using data from the
      specified OdGiFaceData object.

      \param pFaceData [in] Object to use data for setting arrays.

      \remarks
      Sets the following arrays: colors, true colors, layer IDs, selection
      markers, normals, visibilities, materials, material mappers,
      transparencies.
    */
      setMappers(NULL);
      setTransparency(NULL);
    }
    void setPointersArray(const OdGiFaceData *pFaceData = NULL)
    {
      if (!pFaceData || pFaceData->colors()) setColorsArray();
      if (!pFaceData || pFaceData->trueColors()) setTrueColorsArray();
      if (!pFaceData || pFaceData->layerIds()) setLayersArray();
      if (!pFaceData || pFaceData->selectionMarkers()) setSelectionMarkersArray();
      if (!pFaceData || pFaceData->normals()) setNormalsArray();
      if (!pFaceData || pFaceData->visibility()) setVisibilityArray();
      if (!pFaceData || pFaceData->materials()) setMaterialsArray();

    /** \details
      Clears all arrays of the specified OdGiFaceData object.

      \param pFaceData [in] Object to clear arrays of.

      \remarks
      Clears the following arrays: colors, true colors, layer IDs, selection
      markers, normals, visibilities, materials, material mappers,
      transparencies.
    */
      if (!pFaceData || pFaceData->mappers()) setMappersArray();
      if (!pFaceData || pFaceData->transparency()) setTransparencyArray();
    }
    void clearArrays(const OdGiFaceData *pFaceData = NULL)
    {
      if (!pFaceData || pFaceData->colors()) m_colors.clear();
      if (!pFaceData || pFaceData->trueColors()) m_trueColors.clear();
      if (!pFaceData || pFaceData->layerIds()) m_layers.clear();
      if (!pFaceData || pFaceData->selectionMarkers()) m_markers.clear();
      if (!pFaceData || pFaceData->normals()) m_normals.clear();
      if (!pFaceData || pFaceData->visibility()) m_visibilities.clear();
      if (!pFaceData || pFaceData->materials()) m_materials.clear();

    /** \details
      Deletes all arrays of the specified OdGiFaceData object.

      \param pFaceData [in] Object to delete arrays of.

      \remarks
      Deletes the following arrays: colors, true colors, layer IDs, selection
      markers, normals, visibilities, materials, material mappers,
      transparencies.
    */
      if (!pFaceData || pFaceData->mappers()) m_mappers.clear();
      if (!pFaceData || pFaceData->transparency()) m_transparencies.clear();
    }
    void deleteArrays(const OdGiFaceData *pFaceData = NULL)
    {
      if (!pFaceData || pFaceData->colors()) m_colors.setPhysicalLength(0);
      if (!pFaceData || pFaceData->trueColors()) m_trueColors.setPhysicalLength(0);
      if (!pFaceData || pFaceData->layerIds()) m_layers.setPhysicalLength(0);
      if (!pFaceData || pFaceData->selectionMarkers()) m_markers.setPhysicalLength(0);
      if (!pFaceData || pFaceData->normals()) m_normals.setPhysicalLength(0);
      if (!pFaceData || pFaceData->visibility()) m_visibilities.setPhysicalLength(0);
      if (!pFaceData || pFaceData->materials()) m_materials.setPhysicalLength(0);

    /** \details
      Reserves cells in all arrays of the specified OdGiFaceData object.

      \param pFaceData [in] Object which arrays to reserve cells in.
      \param nReserve  [in] Number of cells to reserve.

      \remarks
      Reserves cells in the following arrays: colors, true colors, layer IDs,
      selection markers, normals, visibilities, materials, material mappers,
      transparencies.
    */
      if (!pFaceData || pFaceData->mappers()) m_mappers.setPhysicalLength(0);
      if (!pFaceData || pFaceData->transparency()) m_transparencies.setPhysicalLength(0);
    }
    void reserveArrays(const OdGiFaceData *pFaceData, OdUInt32 nReserve)
    {
      if (!pFaceData || pFaceData->colors()) m_colors.reserve(nReserve);
      if (!pFaceData || pFaceData->trueColors()) m_trueColors.reserve(nReserve);
      if (!pFaceData || pFaceData->layerIds()) m_layers.reserve(nReserve);
      if (!pFaceData || pFaceData->selectionMarkers()) m_markers.reserve(nReserve);
      if (!pFaceData || pFaceData->normals()) m_normals.reserve(nReserve);
      if (!pFaceData || pFaceData->visibility()) m_visibilities.reserve(nReserve);
      if (!pFaceData || pFaceData->materials()) m_materials.reserve(nReserve);

    /** \details
      Copies elements with the specified index from all arrays of the specified
      OdGiFaceData object and appends them to arrays of this OdGiFaceDataStorage
      object.

      \param pFaceData [in] Object to copy array elements from.
      \param nFace     [in] Index of the elements in arrays.

      \remarks
      Copies elements from the following arrays: colors, true colors, layer IDs,
      selection markers, normals, visibilities, materials, material mappers,
      transparencies.
    */
      if (!pFaceData || pFaceData->mappers()) m_mappers.reserve(nReserve);
      if (!pFaceData || pFaceData->transparency()) m_transparencies.reserve(nReserve);
    }
    void copyFrom(const OdGiFaceData *pFaceData, OdUInt32 nFace)
    {
      if (pFaceData && pFaceData->colors()) m_colors.push_back(pFaceData->colors()[nFace]);
      if (pFaceData && pFaceData->trueColors()) m_trueColors.push_back(pFaceData->trueColors()[nFace]);
      if (pFaceData && pFaceData->layerIds()) m_layers.push_back(pFaceData->layerIds()[nFace]);
      if (pFaceData && pFaceData->selectionMarkers()) m_markers.push_back(pFaceData->selectionMarkers()[nFace]);
      if (pFaceData && pFaceData->normals()) m_normals.push_back(pFaceData->normals()[nFace]);
      if (pFaceData && pFaceData->visibility()) m_visibilities.push_back(pFaceData->visibility()[nFace]);
      if (pFaceData && pFaceData->materials()) m_materials.push_back(pFaceData->materials()[nFace]);
      if (pFaceData && pFaceData->mappers()) m_mappers.push_back(pFaceData->mappers()[nFace]);
      if (pFaceData && pFaceData->transparency()) m_transparencies.push_back(pFaceData->transparency()[nFace]);
/** \details
  Vertex data storage class.

  <group OdGi_Classes>
*/
    }
};

    //DOM-IGNORE-BEGIN
class OdGiVertexDataStorage : public OdGiVertexData
{
  protected:
    //DOM-IGNORE-END
    OdGeVector3dArray m_normals;

    /** \details
      Default constructor for objects of the OdGiVertexDataStorage class.
    */
    OdCmEntityColorArray m_trueColors;
    OdGePoint3dArray m_texCoords;

    /** \details
      Retrieves the normals array of this OdGiVertexDataStorage object.

      \returns
      Array of normals.
    */
  public:

    /** \details
      Retrieves the normals array of this OdGiVertexDataStorage object.

      \returns
      Array of normals.
    */
    OdGiVertexDataStorage() : OdGiVertexData() { }

    /** \details
      Sets the normals array.
    */


    /** \details
      Resizes the normals array.

      \param nSize   [in] New normals array size.
      \param bSetPtr [in] True to set the normals array after resizing.

      \returns
      Pointer to the array of normals.
    */
    const OdGeVector3dArray &normalsArray() const { return m_normals; }
    OdGeVector3dArray &normalsArray() { return m_normals; }

    /** \details
      Retrieves the true colors array of this OdGiVertexDataStorage object.

      \returns
      Array of true colors.
    */
    void setNormalsArray() { setNormals(m_normals.getPtr()); }

    /** \details
      Retrieves the true colors array of this OdGiVertexDataStorage object.

      \returns
      Array of true colors.
    */
    OdGeVector3d *resizeNormalsArray(OdUInt32 nSize, bool bSetPtr = true) { m_normals.resize(nSize); if (bSetPtr) setNormalsArray(); return m_normals.asArrayPtr(); }

    /** \details
      Sets the true colors array.
    */


    /** \details
      Resizes the true colors array.

      \param nSize   [in] New true colors array size.
      \param bSetPtr [in] True to set the true colors array after resizing.

      \returns
      Pointer to the array of true colors.
    */
    const OdCmEntityColorArray &trueColorsArray() const { return m_trueColors; }
    OdCmEntityColorArray &trueColorsArray() { return m_trueColors; }

    /** \details
      Retrieves the mapping coordinates array of this OdGiVertexDataStorage
      object.

      \param channel [in] Mapping channel.

      \returns
      Array of mapping coordinates.
    */
    void setTrueColorsArray() { setTrueColors(m_trueColors.getPtr()); }

    /** \details
      Retrieves the mapping coordinates array of this OdGiVertexDataStorage
      object.

      \param channel [in] Mapping channel.

      \returns
      Array of mapping coordinates.
    */
    OdCmEntityColor *resizeTrueColorsArray(OdUInt32 nSize, bool bSetPtr = true) { m_trueColors.resize(nSize); if (bSetPtr) setTrueColorsArray(); return m_trueColors.asArrayPtr(); }

    /** \details
      Sets the mapping coordinates array.

      \param channel [in] Mapping channel.
    */


    /** \details
      Resizes the mapping coordinates array.

      \param channel [in] Mapping channel.
      \param nSize   [in] New mapping coordinates array size.
      \param bSetPtr [in] True to set the mapping coordinates array after resizing.

      \returns
      Pointer to the array of mapping coordinates.
    */
    const OdGePoint3dArray &mappingCoordsArray(MapChannel /*channel*/) const { return m_texCoords; }
    OdGePoint3dArray &mappingCoordsArray(MapChannel /*channel*/) { return m_texCoords; }

    /** \details
      Clones data of the specified OdGiVertexData object.

      \param pData [in] OdGiVertexData object, data of which to be cloned by this OdGiVertexDataStorage object.
    */
    void setMappingCoordsArray(MapChannel channel) { setMappingCoords(channel, m_texCoords.getPtr()); }

    /** \details
      Resets all array pointers of this OdGiVertexDataStorage object to NULL.

      \remarks
      Resets the following array pointers: normals, true colors, mapping
      coordinates.
    */
    OdGePoint3d *resizeMappingCoordsArray(MapChannel channel, OdUInt32 nSize, bool bSetPtr = true) { m_texCoords.resize(nSize); if (bSetPtr) setMappingCoordsArray(channel); return m_texCoords.asArrayPtr(); }

    void cloneData(const OdGiVertexData *pData) { *(OdGiVertexData*)this = *pData; }
    void resetPointers()
    {
      setNormals(NULL);

    /** \details
      Sets all arrays of this OdGiVertexDataStorage object using data from the
      specified OdGiVertexData object.

      \param pVertexData [in] Object to use data for setting arrays.

      \remarks
      Sets the following arrays: normals, true colors, mapping coordinates.
    */
      setTrueColors(NULL);
      setMappingCoords(OdGiVertexData::kAllChannels, NULL);
    }
    void setPointersArray(const OdGiVertexData *pVertexData = NULL)
    {
      if (!pVertexData || pVertexData->normals()) setNormalsArray();

    /** \details
      Clears all arrays of the specified OdGiVertexData object.

      \param pVertexData [in] Object to clear arrays of.

      \remarks
      Clears the following arrays: normals, true colors, mapping coordinates.
    */
      if (!pVertexData || pVertexData->trueColors()) setTrueColorsArray();
      if (!pVertexData || pVertexData->mappingCoords(OdGiVertexData::kAllChannels)) setMappingCoordsArray(OdGiVertexData::kAllChannels);
    }
    void clearArrays(const OdGiVertexData *pVertexData = NULL)
    {
      if (!pVertexData || pVertexData->normals()) m_normals.clear();

    /** \details
      Deletes all arrays of the specified OdGiVertexData object.

      \param pVertexData [in] Object to delete arrays of.

      \remarks
      Deletes the following arrays: normals, true colors, mapping coordinates.
    */
      if (!pVertexData || pVertexData->trueColors()) m_trueColors.clear();
      if (!pVertexData || pVertexData->mappingCoords(OdGiVertexData::kAllChannels)) m_texCoords.clear();
    }
    void deleteArrays(const OdGiVertexData *pVertexData = NULL)
    {
      if (!pVertexData || pVertexData->normals()) m_normals.setPhysicalLength(0);

    /** \details
      Reserves cells in all arrays of the specified OdGiVertexData object.

      \param pVertexData [in] Object which arrays to reserve cells in.
      \param nReserve    [in] Number of cells to reserve.

      \remarks
      Reserves cells in the following arrays: normals, true colors, mapping
      coordinates.
    */
      if (!pVertexData || pVertexData->trueColors()) m_trueColors.setPhysicalLength(0);
      if (!pVertexData || pVertexData->mappingCoords(OdGiVertexData::kAllChannels)) m_texCoords.setPhysicalLength(0);
    }
    void reserveArrays(const OdGiVertexData *pVertexData, OdUInt32 nReserve)
    {
      if (!pVertexData || pVertexData->normals()) m_normals.reserve(nReserve);

    /** \details
      Copies elements with the specified index from all arrays of the specified
      OdGiVertexData object and appends them to arrays of this
      OdGiVertexDataStorage object.

      \param pVertexData [in] Object to copy array elements from.
      \param nVertex     [in] Index of the elements in arrays.

      \remarks
      Copies elements from the following arrays: normals, true colors, mapping
      coordinates.
    */
      if (!pVertexData || pVertexData->trueColors()) m_trueColors.reserve(nReserve);
      if (!pVertexData || pVertexData->mappingCoords(OdGiVertexData::kAllChannels)) m_texCoords.reserve(nReserve);
    }
    void copyFrom(const OdGiVertexData *pVertexData, OdUInt32 nVertex)
    {
      if (pVertexData && pVertexData->normals()) m_normals.push_back(pVertexData->normals()[nVertex]);
      if (pVertexData && pVertexData->trueColors()) m_trueColors.push_back(pVertexData->trueColors()[nVertex]);
      if (pVertexData && pVertexData->mappingCoords(OdGiVertexData::kAllChannels))
        m_texCoords.push_back(pVertexData->mappingCoords(OdGiVertexData::kAllChannels)[nVertex]);
/** \details
  SHM data storage class.

  <group OdGi_Classes>
*/
    }
};

    //DOM-IGNORE-BEGIN
class OdGiShmDataStorage
{
  protected:
    OdGePoint3dArray m_vertexList;
    const OdGePoint3d *m_pVertexList;
    OdInt32Array m_faceList;
    const OdInt32 *m_pFaceList;
    OdGiEdgeDataStorage m_edgeData;
    const OdGiEdgeData *m_pEdgeData;
    OdGiFaceDataStorage m_faceData;
    //DOM-IGNORE-END
    const OdGiFaceData *m_pFaceData;

    /** \details
      Default constructor for objects of the OdGiShmDataStorage class.
    */
    OdGiVertexDataStorage m_vertexData;
    const OdGiVertexData *m_pVertexData;
  public:
    OdGiShmDataStorage()
      : m_pVertexList(NULL)
      , m_pFaceList(NULL)
      , m_pEdgeData(NULL)
      , m_pFaceData(NULL)

    /** \details
      Sets the vertex list of this OdGiShmDataStorage object.

      \param pVertexList [in] Pointer to the vertex list.
    */
      , m_pVertexData(NULL)

    /** \details
      Retrieves the vertex list of this OdGiShmDataStorage object.

      \returns
      List of vertices.
    */
    { }

    /** \details
      Retrieves the vertex list array of this OdGiShmDataStorage object.

      \returns
      Array of lists of vertices.
    */


    /** \details
      Retrieves the vertex list array of this OdGiShmDataStorage object.

      \returns
      Array of lists of vertices.
    */
    void setVertexList(const OdGePoint3d *pVertexList) { m_pVertexList = pVertexList; }

    /** \details
      Sets the vertex list array of this OdGiShmDataStorage object.
    */
    const OdGePoint3d *vertexList() const { return m_pVertexList; }

    /** \details
      Resizes the vertex list array.

      \param nSize   [in] New vertex list array size.
      \param bSetPtr [in] True to set the vertex list array after resizing.

      \returns
      Pointer to the array of lists of vertices.
    */
    const OdGePoint3dArray &vertexListArray() const { return m_vertexList; }
    OdGePoint3dArray &vertexListArray() { return m_vertexList; }

    /** \details
      Sets the face list of this OdGiShmDataStorage object.

      \param pFaceList [in] Pointer to the face list.
    */
    void setVertexListArray() { setVertexList(m_vertexList.getPtr()); }

    /** \details
      Retrieves the face list of this OdGiShmDataStorage object.

      \returns
      List of faces.
    */
    OdGePoint3d *resizeVertexListArray(OdUInt32 nSize, bool bSetPtr = true) { m_vertexList.resize(nSize); if (bSetPtr) setVertexListArray(); return m_vertexList.asArrayPtr(); }

    /** \details
      Retrieves the face list array of this OdGiShmDataStorage object.

      \returns
      Array of lists of faces.
    */


    /** \details
      Retrieves the face list array of this OdGiShmDataStorage object.

      \returns
      Array of lists of faces.
    */
    void setFaceList(const OdInt32 *pFaceList) { m_pFaceList = pFaceList; }

    /** \details
      Sets the face list array of this OdGiShmDataStorage object.
    */
    const OdInt32 *faceList() const { return m_pFaceList; }

    /** \details
      Resizes the face list array.

      \param nSize   [in] New face list array size.
      \param bSetPtr [in] True to set the face list array after resizing.

      \returns
      Pointer to the array of lists of faces.
    */
    const OdInt32Array &faceListArray() const { return m_faceList; }
    OdInt32Array &faceListArray() { return m_faceList; }

    /** \details
      Sets the edge data of this OdGiShmDataStorage object.

      \param pEdgeData [in] Pointer to the edge data.
    */
    void setFaceListArray() { setFaceList(m_faceList.getPtr()); }

    /** \details
      Retrieves the edge data of this OdGiShmDataStorage object.

      \returns
      Edge data.
    */
    OdInt32 *resizeFaceListArray(OdUInt32 nSize, bool bSetPtr = true) { m_faceList.resize(nSize); if (bSetPtr) setFaceListArray(); return m_faceList.asArrayPtr(); }

    /** \details
      Retrieves the edge data storage of this OdGiShmDataStorage object.

      \returns
      Edge data storage.
    */


    /** \details
      Retrieves the edge data storage of this OdGiShmDataStorage object.

      \returns
      Edge data storage.
    */
    void setEdgeData(const OdGiEdgeData *pEdgeData) { m_pEdgeData = pEdgeData; }

    /** \details
      Sets the edge data storage of this OdGiShmDataStorage object.
    */
    const OdGiEdgeData *edgeData() const { return m_pEdgeData; }

    /** \details
      Resets the edge data pointer of this OdGiShmDataStorage object to NULL.
    */
    const OdGiEdgeDataStorage &edgeDataStorage() const { return m_edgeData; }

    /** \details
      Clones edge data of the specified OdGiEdgeData object to this
      OdGiShmDataStorage object.

      \param pEdgeData [in] Object, edge data of which to be cloned.
    */
    OdGiEdgeDataStorage &edgeDataStorage() { return m_edgeData; }
    void setEdgeDataStorage() { setEdgeData(&m_edgeData); }

    /** \details
      Sets the face data of this OdGiShmDataStorage object.

      \param pFaceData [in] Pointer to the face data.
    */
    void resetEdgeData() { m_pEdgeData = NULL; }

    /** \details
      Retrieves the face data of this OdGiShmDataStorage object.

      \returns
      Face data.
    */
    void cloneEdgeData(const OdGiEdgeData *pEdgeData) { if (pEdgeData) { m_edgeData.cloneData(pEdgeData); setEdgeDataStorage(); } else resetEdgeData(); }

    /** \details
      Retrieves the face data storage of this OdGiShmDataStorage object.

      \returns
      Face data storage.
    */


    /** \details
      Retrieves the face data storage of this OdGiShmDataStorage object.

      \returns
      Face data storage.
    */
    void setFaceData(const OdGiFaceData *pFaceData) { m_pFaceData = pFaceData; }

    /** \details
      Sets the face data storage of this OdGiShmDataStorage object.
    */
    const OdGiFaceData *faceData() const { return m_pFaceData; }

    /** \details
      Resets the face data pointer of this OdGiShmDataStorage object to NULL.
    */
    const OdGiFaceDataStorage &faceDataStorage() const { return m_faceData; }

    /** \details
      Clones edge data of the specified OdGiFaceData object to this
      OdGiShmDataStorage object.

      \param pFaceData [in] Object, face data of which to be cloned.
    */
    OdGiFaceDataStorage &faceDataStorage() { return m_faceData; }
    void setFaceDataStorage() { setFaceData(&m_faceData); }

    /** \details
      Sets the vertex data of this OdGiShmDataStorage object.

      \param pVertexData [in] Pointer to the vertex data.
    */
    void resetFaceData() { m_pFaceData = NULL; }

    /** \details
      Retrieves the vertex data of this OdGiShmDataStorage object.

      \returns
      Vertex data.
    */
    void cloneFaceData(const OdGiFaceData *pFaceData) { if (pFaceData) { m_faceData.cloneData(pFaceData); setFaceDataStorage(); } else resetFaceData(); }

    /** \details
      Retrieves the vertex data storage of this OdGiShmDataStorage object.

      \returns
      Vertex data storage.
    */


    /** \details
      Retrieves the vertex data storage of this OdGiShmDataStorage object.

      \returns
      Vertex data storage.
    */
    void setVertexData(const OdGiVertexData *pVertexData) { m_pVertexData = pVertexData; }

    /** \details
      Sets the vertex data storage of this OdGiShmDataStorage object.
    */
    const OdGiVertexData *vertexData() const { return m_pVertexData; }

    /** \details
      Resets the vertex data pointer of this OdGiShmDataStorage object to NULL.
    */
    const OdGiVertexDataStorage &vertexDataStorage() const { return m_vertexData; }

    /** \details
      Clones vertex data of the specified OdGiVertexData object to this
      OdGiShmDataStorage object.

      \param pVertexData [in] Object, vertex data of which to be cloned.
    */
    OdGiVertexDataStorage &vertexDataStorage() { return m_vertexData; }
    void setVertexDataStorage() { setVertexData(&m_vertexData); }

    /** \details
      Resets all pointers, data and data storages of this OdGiShmDataStorage
      object.

      \remarks
      Resets the following pointers: vertex list and face list. Resets edge,
      face and vertex data. Resets edge, face and vertex data storages.
    */
    void resetVertexData() { m_pVertexData = NULL; }
    void cloneVertexData(const OdGiVertexData *pVertexData) { if (pVertexData) { m_vertexData.cloneData(pVertexData); setVertexDataStorage(); } else resetVertexData(); }

    void resetPointers()
    {
      setVertexList(NULL);
      setFaceList(NULL);
      resetEdgeData();
      resetFaceData();
      resetVertexData();
      m_edgeData.resetPointers();

    /** \details
      Sets all lists and data to storages of this OdGiShmDataStorage object.

      \param pFaceData   [in] Face data.
      \param pEdgeData   [in] Edge data.
      \param pVertexData [in] Vertex data.

      \remarks
      Sets vertex and face lists. Sets edge, face and vertex data to storages.
    */
      m_faceData.resetPointers();
      m_vertexData.resetPointers();
    }
    void setPointersArray(const OdGiFaceData *pFaceData = NULL, const OdGiEdgeData *pEdgeData = NULL, const OdGiVertexData *pVertexData = NULL)
    {
      setVertexListArray();
      setFaceListArray();
      if (pEdgeData) setEdgeDataStorage();
      if (pFaceData) setFaceDataStorage();
      if (pVertexData) setVertexDataStorage();
      m_edgeData.setPointersArray(pEdgeData);

    /** \details
      Clears all lists and data from storages of this OdGiShmDataStorage object.

      \param pFaceData   [in] Face data.
      \param pEdgeData   [in] Edge data.
      \param pVertexData [in] Vertex data.

      \remarks
      Clears vertex and face lists. Clears edge, face and vertex data from
      storages.
    */
      m_faceData.setPointersArray(pFaceData);
      m_vertexData.setPointersArray(pVertexData);
    }
    void clearArrays(const OdGiFaceData *pFaceData = NULL, const OdGiEdgeData *pEdgeData = NULL, const OdGiVertexData *pVertexData = NULL)
    {
      m_vertexList.clear();
      m_faceList.clear();
      m_edgeData.clearArrays(pEdgeData);

    /** \details
      Deletes all lists and data from storages of this OdGiShmDataStorage
      object.

      \param pFaceData   [in] Face data.
      \param pEdgeData   [in] Edge data.
      \param pVertexData [in] Vertex data.

      \remarks
      Deletes vertex and face lists. Deletes edge, face and vertex data from
      storages.
    */
      m_faceData.clearArrays(pFaceData);
      m_vertexData.clearArrays(pVertexData);
    }
    void deleteArrays(const OdGiFaceData *pFaceData = NULL, const OdGiEdgeData *pEdgeData = NULL, const OdGiVertexData *pVertexData = NULL)
    {
      m_vertexList.setPhysicalLength(0);
      m_faceList.setPhysicalLength(0);
      m_edgeData.deleteArrays(pEdgeData);
      m_faceData.deleteArrays(pFaceData);
      m_vertexData.deleteArrays(pVertexData);
    }
};

#endif // __OD_GI_SHM_DATA_STORAGE__
