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

#ifndef __ODGIGEOMETRY_H__
#define __ODGIGEOMETRY_H__

#include "../TD_PackPush.h"
#include "../RxObject.h"

#include "../Ge/GePoint3d.h"
#include "../Ge/GeMatrix3d.h"

#include "../Gi/GiRasterImage.h"
#include "../Gi/GiMaterial.h"
#include "../Gi/GiParameter.h"

class OdDbStub;
class OdCmEntityColor;
class OdGeMatrix3d;
class OdGeVector3d;
class OdGePoint2d;
class OdGeCurve2d;
class OdGiPathNode;
class OdGiMapper;
class OdCmTransparency;
class OdGiImageBGRA32;
class OdGiPointCloud;
class OdGeDashLine3d;
class OdGeMultiDashLine3d;

class GcGiPolyline;
class GcGiGdiDrawObject;

typedef OdArray<OdGeCurve2d*> OdGiEdge2dArray;

class OdGiSilhouetteData
{
public:
  OdGeVector3d m_viewdir;
  struct SilhouetteData
  {
    OdInt32 faceIndex;
    OdInt32 edgeIndex;
    OdInt32 verticesIndices[2];
  };
  OdArray<SilhouetteData> m_data;
};

/** \details
    This class represents arrays of edge attributes for meshes and shells.
    
    \remarks
    EdgeData objects are optional; they can be optionally passed 
    to OdGiWorldGeometry and OdGiViewportGeometry when using their 
	mesh and shell methods. 
    
    \remarks 
    Setting an 'improper' size of any array will cause
    unpredictable or fatal results.

    \sa
    TD_Gi

    <group OdGi_Classes> 
*/
class OdGiImpEdgeData;
class ODGI_EXPORT OdGiEdgeData : public OdGiParameter
{
public:
  ODRX_DECLARE_MEMBERS_READWRITE(OdGiEdgeData, OdGiImpEdgeData);

  ~OdGiEdgeData();
  /** \details
    Default constructor for the OdGiEdgeData class. Sets current color index, true color, 
    layer and linetype identifiers, selection markers, visibility objects to NULL.
  */
  OdGiEdgeData();

  /** \details
    Sets the edge colors to be used by this object.

    \param colors [in]  Array of color indices.        
    \remarks
    You cannot call both setColors() and setTrueColors().
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. An incorrect number of elements will have unpredictable or fatal consequences.
    \sa
    <exref target="https://docs.opendesign.com/td/cm.html">Working with Colors</exref>
  */
  virtual void            setColors(const short *colors);

  /** \details
    Sets the edge colors to be used by this object.

    \param colors [in]  Array of OdCmEntityColor objects.        
    \remarks
    You cannot call both setColors() and setTrueColors().
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. An incorrect number of elements will have unpredictable or fatal consequences.
    \sa
    <exref target="https://docs.opendesign.com/td/cm.html">Working with Colors</exref>
  */
  virtual void            setTrueColors(const OdCmEntityColor *colors);

  /** \details
    Sets the edge Layer Table Records to be used by this object.

    \param layerIds [in]  Array of LayerTableRecord Object IDs.       
    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. An incorrect number of elements will have unpredictable or fatal consequences.
    \sa
    <link tv_working_with_attributes_layers, Working with Layers>
  */
  virtual void            setLayers(const OdDbObjectId *layers);

  /** \details
    Sets the edge Linetype Table Records to be used by this object.

    \param linetypeIds [in]  Array of LinetypeTableRecord Object IDs.        
    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. An incorrect number of elements will have unpredictable or fatal consequences.
    \sa
    <exref target="https://docs.opendesign.com/td/db_linetype.html">Working with Linetypes</exref>
  */
  virtual void            setLineTypes(const OdDbObjectId *linetypes);

  /** \details
    Sets the edge graphics system selection markers to be used by this object.

    \param selectionMarkers [in]  Array of graphics system selection markers.        
    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. An incorrect number of elements will have unpredictable or fatal consequences.
  */
  virtual void            setSelectionMarkers(const OdLongPtr* pSelectionMarkers);

  /** \details
    Sets the edge visibilities to be used by this object.

    \param visibilities [in]  Array of visibility values.
    \remarks
    Each visibility must be one of the following:
     
    <table>
    Name              Value   Description
    kOdGiInvisible    0       Invisible 
    kOdGiVisible      1       Visible 
    kOdGiSilhouette   2       Silhouette edge 
    </table>
        
    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. An incorrect number of elements will have unpredictable or fatal consequences.
  */
  virtual void            setVisibility(const OdUInt8* pVisibility);
  
  /** \details
    Returns the array of edge colors used by this object.
    
    \returns
    pointer to the array of color indices.
    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. Writing beyond the array bounds will have unpredictable or fatal consequences.
    \sa
    <exref target="https://docs.opendesign.com/td/cm.html">Working with Colors</exref>
  */
  virtual short*          colors() const;

  /** \details
    Returns the array of edge colors used by this object.

    \returns
    pointer to the array of colors.
    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. Writing beyond the array bounds will have unpredictable or fatal consequences.
    \sa
    <exref target="https://docs.opendesign.com/td/cm.html">Working with Colors</exref>
  */
  virtual OdCmEntityColor* trueColors() const;

  /** \details
    Returns the array of edge LayerTableRecord Object IDs used by this object.

    \returns
    pointer to the array of layer identifiers.
    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. Writing beyond the array bounds will have unpredictable or fatal consequences.
    \sa
    <link tv_working_with_attributes_layers, Working with Layers>
  */
  virtual OdDbObjectId*   layerIds() const;

  /** \details
    Returns the array of edge LinetypeTableRecord Object IDs used by this object.

    \returns
    pointer to the array of linetype identifiers.
    
    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. Writing beyond the array bounds will have unpredictable or fatal consequences.
    \sa
    <exref target="https://docs.opendesign.com/td/db_linetype.html">Working with Linetypes</exref>
  */
  virtual OdDbObjectId*   linetypeIds() const;

  /** \details
    Returns the array of edge graphics system selection markers used by this object.

    \returns
    pointer to the array of selection markers.
    
    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. Writing beyond the array bounds will have unpredictable or fatal consequences.
  */
  virtual OdLongPtr* selectionMarkers() const;

  /** \details
    Returns the array of edge visibilities used by this object.

    \returns
    pointer to the array of visibility values.
    
    \remarks
    Each visibility must be one of the following:
     
    <table>
    Name              Value   Description
    kOdGiInvisible    0       Invisible 
    kOdGiVisible      1       Visible 
    kOdGiSilhouette   2       Silhouette edge 
    </table>

    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. Writing beyond the array bounds will have unpredictable or fatal consequences.
  */
  virtual OdUInt8*   visibility() const;

  OdGiSilhouetteData*   silhouetteData() const;
  void setSilhouetteData(OdGiSilhouetteData* pSilhouetteData);
};


/** \details
    This class contains arrays of face attributes for meshes and shells.

    \sa
    TD_Gi

    <group OdGi_Classes> 
*/
class OdGiImpFaceData;
class ODGI_EXPORT OdGiFaceData : public OdGiParameter  
{
public:
  ODRX_DECLARE_MEMBERS_READWRITE(OdGiFaceData, OdGiImpFaceData);

  ~OdGiFaceData();
  /** \details
    Default constructor for the OdGiFaceData class. Sets current color index, true color, 
    layer and linetype identifiers, selection markers, visibility objects, normals, material identifiers,
    mappers, transparency objects, fill origins and directions to NULL.
  */
  OdGiFaceData();

  /** \details
    Sets the face colors to be used by this object.

    \param colors [in]  Array of color indices.
        
    \remarks
    You cannot call both setColors() and setTrueColors().
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. An incorrect number of elements will have unpredictable or fatal consequences.
    \sa
    <exref target="https://docs.opendesign.com/td/cm.html">Working with Colors</exref>
  */
  virtual void            setColors(const short *colors);

  /** \details
    Sets the face colors to be used by this object.

    \param colors [in]  Array of OdCmEntityColor objects.
        
    \remarks
    You cannot call both setColors() and setTrueColors().
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. An incorrect number of elements will have unpredictable or fatal consequences.
    \sa
    <exref target="https://docs.opendesign.com/td/cm.html">Working with Colors</exref>
  */
  virtual void            setTrueColors(const OdCmEntityColor *colors);

  /** \details
    Sets the face Layer Table Records to be used by this object.

    \param layerIds [in]  Array of LayerTableRecord Object IDs.        
    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. An incorrect number of elements will have unpredictable or fatal consequences.
    \sa
    <link tv_working_with_attributes_layers, Working with Layers>
  */
  virtual void            setLayers(const OdDbObjectId *layers);

  /** \details
    Sets the face graphics system selection markers to be used by this object.

    \param selectionMarkers [in]  Array of graphics system selection markers.     
    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. An incorrect number of elements will have unpredictable or fatal consequences.
  */
  virtual void            setSelectionMarkers(const OdLongPtr* pSelectionMarkers);

  /** \details
    Sets the face normal vectors to be used by this object.

    \param normals [in]  Array of normal vectors.
    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. An incorrect number of elements will have unpredictable or fatal consequences.
  */
  virtual void            setNormals(const OdGeVector3d* pNormals);

  /** \details
    Sets the face visibilities to be used by this object.

    \param visibilities [in]  Array of visibility values.
    \remarks
    Each visibility must be one of the following:
     
    <table>
    Name              Value   Description
    kOdGiInvisible    0       Invisible 
    kOdGiVisible      1       Visible 
    </table>
        
    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. An incorrect number of elements will have unpredictable or fatal consequences.
  */
  virtual void            setVisibility(const OdUInt8* vis);

  /** \details
    Sets the face material object IDs to be used by this object.

    \param materialIds [in]  Array of material object IDs.
    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. An incorrect number of elements will have unpredictable or fatal consequences.
    \sa
    <link tv_working_with_attributes_materials, Working with Materials>
  */
  virtual void            setMaterials(const OdDbObjectId * materials);

  /** \details
    Sets the face material mappers to be used by this object.

    \param mappers [in]  Array of material mappers.
        
    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. An incorrect number of elements will have unpredictable or fatal consequences.
    \sa
    <link tv_working_with_attributes_materials_mapping, Working with Mapping Properties>
  */
  virtual void            setMappers(const OdGiMapper * mappers);

  /** \details
    Sets the face transparency to be used by this object.

    \param transparencies [in]  Array of OdCmTransparency objects.
    \remarks 
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. An incorrect number of elements will have unpredictable or fatal consequences.
    \sa
    <exref target="https://docs.opendesign.com/td/cm_transparency_alpha.html">Transparency Functionality as an Alpha-value</exref>
    \sa
    <exref target="https://docs.opendesign.com/td/cm_transparency_integer.html">Transparency Functionality as an Integer-value</exref>
  */
  virtual void            setTransparency(const OdCmTransparency *transparency);

  /** \details
    Sets the face fill origin points to be used by this object. BIM-specific

    \param fillOrigins [in]  Array of fill origin points.    
    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. An incorrect number of elements will have unpredictable or fatal consequences.
    \sa
    <link tv_working_with_attributes_fill_patterns, Working with Fill Patterns>
  */
  virtual void setFillOrigins(const OdGePoint2d* fillOrigins);

  /** \details
    Sets the face fill direction vectors to be used by this object. BIM-specific

    \param fillDirections [in]  Array of fill direction vectors.
    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. An incorrect number of elements will have unpredictable or fatal consequences.
    \sa
    <link tv_working_with_attributes_fill_patterns, Working with Fill Patterns>
  */
  virtual void setFillDirections(const OdGeVector2d* fillDirections);

  /** \details
    Returns the array of face colors used by this object.

    \returns
    pointer to face color indices. 
    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. Writing beyond the array bounds will have unpredictable or fatal consequences.
    \sa
    <exref target="https://docs.opendesign.com/td/cm.html">Working with Colors</exref>
  */
  virtual short*          colors() const;

  /** \details
    Returns the array of face colors used by this object.

    \returns
    pointer to face colors.
    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. Writing beyond the array bounds will have unpredictable or fatal consequences.
    \sa
    <exref target="https://docs.opendesign.com/td/cm.html">Working with Colors</exref>
  */
  virtual OdCmEntityColor* trueColors() const;

  /** \details
    Returns the array of face LayerTableRecord Object IDs used by this object.

    \returns
    pointer to layer identifiers.
    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. Writing beyond the array bounds will have unpredictable or fatal consequences.
    \sa
    <link tv_working_with_attributes_layers, Working with Layers>
  */
  virtual OdDbObjectId*   layerIds() const;

  /** \details
    Returns the array of face graphics system selection markers used by this object.

    \returns
    pointer to selection markers.
    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. Writing beyond the array bounds will have unpredictable or fatal consequences.
  */
  virtual OdLongPtr* selectionMarkers() const;

  /** \details
    Returns the array of face normal vectors used by this object.

    \returns
    pointer to face normals.
    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. Writing beyond the array bounds will have unpredictable or fatal consequences.
  */
  virtual OdGeVector3d*   normals() const;

  /** \details
    Returns the array of edge visibilities used by this object.

    \returns
    pointer to visibility values.
    \remarks
    Each visibility must be one of the following:
     
    <table>
    Name              Value   Description
    kOdGiInvisible    0       Invisible 
    kOdGiVisible      1       Visible 
    </table>

    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. Writing beyond the array bounds will have unpredictable or fatal consequences.
  */
  virtual OdUInt8*   visibility() const;

  /** \details
    Returns the array of face material object IDs used by this object.

    \returns
    pointer to face materials.
    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. Writing beyond the array bounds will have unpredictable or fatal consequences.
    \sa
    <link tv_working_with_attributes_materials, Working with Materials>
  */
  virtual OdDbObjectId*   materials() const;

  /** \details
    Returns the array of face material mappers used by this object.

    \returns
    pointer to face material mappers.
    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. Writing beyond the array bounds will have unpredictable or fatal consequences.
    \sa
    <link tv_working_with_attributes_materials_mapping, Working with Mapping Properties>
  */
  virtual OdGiMapper*     mappers() const;

  /** \details
    Returns the array of face transparency used by this object.

    \returns
    pointer to face transparency objects. 
    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. Writing beyond the array bounds will have unpredictable or fatal consequences.
    \sa
    <exref target="https://docs.opendesign.com/td/cm_transparency_alpha.html">Transparency Functionality as an Alpha-value</exref>
    \sa
    <exref target="https://docs.opendesign.com/td/cm_transparency_integer.html">Transparency Functionality as an Integer-value</exref>
  */
  virtual OdCmTransparency* transparency() const;
  
  /** \details
    Returns the array of fill origin points used by this object. BIM-specific

    \returns
    pointer to face fill origin points.
    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. Writing beyond the array bounds will have unpredictable or fatal consequences.
    \sa
    <link tv_working_with_attributes_fill_patterns, Working with Fill Patterns>
  */
  virtual OdGePoint2d* fillOrigins() const;

  /** \details
    Returns the array of fill direction vectors used by this object. BIM-specific

    \returns
    pointer to face fill directions.
    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. Writing beyond the array bounds will have unpredictable or fatal consequences.
    \sa
    <link tv_working_with_attributes_fill_patterns, Working with Fill Patterns>
  */
  virtual OdGeVector2d* fillDirections() const;
};

typedef enum
{
  /** Counter-clockwise orientation.*/
  kOdGiCounterClockwise = -1,
  /** No orientation for faces.*/
  kOdGiNoOrientation    = 0,
  /** Clockwise orientation.*/
  kOdGiClockwise        = 1
} OdGiOrientationType;  // Represents faces orientation for calculating various parameters.

class OdGiImpVertexData;

/** \details
    This class contains arrays of vertex attributes for meshes and shells.
    
    \remarks
    VertexData objects are optional; they can be optionally passed 
    to OdGiWorldGeometry and OdGiViewportGeometry when using their 
	mesh and shell methods.
	
	 Setting an 'improper' size of any array will cause unpredictable or fatal results.

    \sa
    TD_Gi

    <group OdGi_Classes> 
*/
class ODGI_EXPORT OdGiVertexData : public OdGiParameter
{
public:
  ODRX_DECLARE_MEMBERS_READWRITE(OdGiVertexData, OdGiImpVertexData);
  ~OdGiVertexData();
  /** \details
    Default constructor for the OdGiVertexData class. Sets normals, colors and mapping coordinates to NULL and the orientation flag to kOdGiNoOrientation. 
  */
  OdGiVertexData();

  /** \details
    Represents types of map channels. 
  */
  enum MapChannel
  {
    kAllChannels,
    kMapChannels
  };

  /** \details
    Sets the vertex normal vectors to be used by this object.

    \param normals [in]  Array of normal vectors.

    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. An incorrect number of elements will have unpredictable or fatal consequences.
  */
  virtual void setNormals(const OdGeVector3d* pNormals);

  /** \details
    Sets the orientation type to be used by this object.

    \param orientationType [in]  Orientation type.

    \remarks
    The orientation type defines the positive direction of the normal at the vertices.

    orientationType must be one of the following:

    <table>
    Name                      Value 
    kOdGiCounterClockwise     -1
    kOdGiNoOrientation        0
    kOdGiClockwise            1
    </table>
  */
  virtual void setOrientationFlag(const OdGiOrientationType oflag);
  
  /** \details
    Sets the vertex colors to be used by this object.

    \param colors [in]  Array of OdCmEntityColor objects.
    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. An incorrect number of elements will have unpredictable or fatal consequences.
    \sa
    <exref target="https://docs.opendesign.com/td/cm.html">Working with Colors</exref>
  */
  virtual void setTrueColors(const OdCmEntityColor *colors);
  
  /** \details
    Sets the mapping coordinates to be used by this object.

    \param channel [in]  Specifies mapping channel.
    \param coords [in]  Array of OdGePoint3d objects.
    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. An incorrect number of elements will have unpredictable or fatal consequences.
    \sa
    <link tv_working_with_attributes_materials_mapping, Working with Mapping Properties>
  */
  virtual void setMappingCoords(MapChannel mapChannel, const OdGePoint3d* pCoords);

  /** \details
    Returns the array of vertex normal vectors used by this object.

    \returns
    pointer to an array of vertex normals.
    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. Writing beyond the array bounds will have unpredictable or fatal consequences.
  */
  virtual OdGeVector3d* normals() const;

  /** \details
    Returns the direction of the normal at the vertices that is used by this object.

    \returns
    orientationFlag which can be one of the following:

    <table>
    Name                      Value 
    kOdGiCounterClockwise     -1
    kOdGiNoOrientation        0
    kOdGiClockwise            1
    </table>
  */
  virtual OdGiOrientationType orientationFlag() const;

  /** \details
    Returns the array of vertex colors used by this object.

    \returns
    pointer to an array of vertex colors.
    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. Writing beyond the array bounds will have unpredictable or fatal consequences.
    \sa
    <exref target="https://docs.opendesign.com/td/cm.html">Working with Colors</exref>
  */
  virtual OdCmEntityColor* trueColors() const;

  /** \details
    Returns the array of mapping coordinates used by this object.

    \param channel [in]  Specifies mapping channel.

    \returns
    pointer to an array of mapping coordinates.
    \remarks
    This function does not make a copy of the array, which should have the same number of elements as the 
    mesh or shell with which it is used. Writing beyond the array bounds will have unpredictable or fatal consequences.
    \sa
    <link tv_working_with_attributes_materials_mapping, Working with Mapping Properties>
  */
  virtual OdGePoint3d* mappingCoords(MapChannel mapChannel) const;
};

class OdGiDrawable;
struct OdGiClipBoundary;
class OdGiAbstractClipBoundary;

class OdDbPolyline;
class OdPolyPolygon3d;
class OdGeNurbCurve3d;
class OdGiTextStyle;
class OdDbBody;
class OdGeEllipArc3d;
class OdGiPolyline;
class OdGiBrep;

/** \details
    Arc types.
*/
typedef enum
{
  kOdGiArcSimple = 0,   // Unfilled.
  kOdGiArcSector = 1,   // Filled area bounded by the arc and its center.
  kOdGiArcChord  = 2    // Filled area bounded by the arc and its end points
} OdGiArcType;

typedef enum 
{
  kGcGiWorldPosition,
  kGcGiViewportPosition,
  kGcGiScreenPosition,
  kGcGiScreenLocalOriginPosition,
  kGcGiWorldWithScreenOffsetPosition
} GcGiPositionTransformBehavior;

typedef enum 
{
  kGcGiWorldScale,
  kGcGiViewportScale,
  kGcGiScreenScale,
  kGcGiViewportLocalOriginScale,
  kGcGiScreenLocalOriginScale
} GcGiScaleTransformBehavior;

typedef enum 
{
  kGcGiWorldOrientation,
  kGcGiScreenOrientation,
  kGcGiZAxisOrientation
} GcGiOrientationTransformBehavior;

/** \details
    This class defines functions that allow entities to vectorize themselves.

    \sa
    TD_Gi

    <group OdGi_Classes> 
*/
class FIRSTDLL_EXPORT OdGiGeometry : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdGiGeometry);

  enum TransparencyMode
  {
    kTransparencyOff,
    kTransparency1Bit,
    kTransparency8Bit,
  };
  /** \details
    Returns the model-to-world coordinate transform matrix for the entity being vectorized.
    
    \returns
    model-to-world transform matrix.
    
    \remarks
    This is the inverse of the matrix returned by getWorldToModelTransform(). 

    If an entity is in one or more blocks, this matrix can be used to
    determine the WCS coordinates of the entity.  
  */
  virtual OdGeMatrix3d getModelToWorldTransform() const;
  virtual void getModelToWorldTransform(OdGeMatrix3d& unnamed) const = 0;

  /** \details
    Returns the world-to-model coordinate transform matrix for the entity being vectorized.
    
    \returns
    world-to-model transform matrix.
    
    \remarks
    This is the inverse of the matrix returned by getModelToWorldTransform(). 
  */
  virtual OdGeMatrix3d getWorldToModelTransform() const;
  virtual void getWorldToModelTransform(OdGeMatrix3d& unnamed) const = 0;
  
  /** \details
    Specifies a model transformation matrix for the current transformation stack.  
    
    \remarks
    When a vector is specified, the transformation is created using the arbitrary axis algorithm 
    on the vector. 
 
    The specified transformation is concatenated to the current model transformation 
	(which is initially the identity transform). The resulting model transformation 
	is subsequently applied to all geometry introduced into this vectorization context, 
	until popModelTransform() is called.
    
    \param normal [in]  Normal vector.    
  */
  virtual OdBool pushModelTransform(
    const OdGeVector3d& normal) = 0;

  /** \details
    Specifies a model transformation matrix for the current transformation stack.  
    
    \remarks
    The specified transformation is concatenated to the current model transformation 
	(which is initially the identity transform). The resulting model transformation 
	is subsequently applied to all geometry introduced into this vectorization context, 
	until popModelTransform() is called.
    
    \param xfm [in]  Transformation matrix.
    
  */
  virtual OdBool pushModelTransform(
    const OdGeMatrix3d& xfm) = 0;

  /** \details
    Removes the top transformation off the current transformation stack.
  */
  virtual OdBool popModelTransform() = 0;
  
  virtual OdGeMatrix3d pushPositionTransform(GcGiPositionTransformBehavior behavior, const OdGePoint3d& offset);
  virtual OdGeMatrix3d pushPositionTransform(GcGiPositionTransformBehavior behavior, const OdGePoint2d& offset);
  virtual OdGeMatrix3d pushScaleTransform(GcGiScaleTransformBehavior behavior, const OdGePoint3d& extents);
  virtual OdGeMatrix3d pushScaleTransform(GcGiScaleTransformBehavior behavior, const OdGePoint2d& extents);
  virtual OdGeMatrix3d pushOrientationTransform(GcGiOrientationTransformBehavior behavior);

  /** \details
    Introduces a circle to this vectorization context.  
    
    \remarks
    The circle is not filled and takes on the current color.
    
    If firstPoint, secondPoint, and thirdPoint are specified, they
    cannot be colinear and no two can be coincident.

    \param center [in]  Center point.
    \param radius [in]  Radius.
    \param normal [in]  Normal.
    \sa
    <link tv_geometry_circles, Working with Circles>
  */
  virtual OdBool circle(
    const OdGePoint3d& center, 
    const double radius, 
    const OdGeVector3d& normal) const = 0;
  
  /** \details
    Introduces a circle to this vectorization context.

    \param firstPoint [in]  First point of a 3-point circle.
    \param secondPoint [in]  Second point of a 3-point circle.
    \param thirdPoint [in]  Third point of a 3-point circle.    
    \remarks
    firstPoint, secondPoint, and thirdPoint cannot be colinear and no two can be coincident.
    \sa
    <link tv_geometry_circles, Working with Circles>
  */
  virtual OdBool circle(
    const OdGePoint3d& firstPoint, 
    const OdGePoint3d& secondPoint, 
    const OdGePoint3d& thirdPoint) const = 0;
  
/** \details
    Introduces a circular arc to this vectorization context.  
    
    \param center [in]  Center point.
    \param radius [in]  Radius.
    \param normal [in]  Normal vector.
    \param startVector [in]  Start of the arc.
    \param sweepAngle [in]  Angle that defines the arc.
    \param arcType [in]  Arc type.    
    \remarks
    The arc takes on the current color.
    All angles are expressed in radians.
    arcType must be one of the following:
    
    <table>
    Name              Value     Description
    kOdGiArcSimple    0         Unfilled.
    kOdGiArcSector    1         Filled area bounded by the arc and its center.
    kOdGiArcChord     2         Filled area bounded by the arc and its end points
    </table>
    
    \sa
    <link tv_geometry_arcs, Working with Arcs>
*/
  virtual OdBool circularArc(
    const OdGePoint3d& center,
    const double radius,
    const OdGeVector3d& normal,
    const OdGeVector3d& startVector,
    const double sweepAngle,
    const OdGiArcType arcType = kOdGiArcSimple) const = 0;
  
  /** \details
    Introduces a circular arc to this vectorization context.
    
    \param firstPoint [in]  First point of a 3-point arc.
    \param secondPoint [in]  Second point of a 3-point arc.
    \param thirdPoint [in]  Third point of a 3-point arc.
    \param arcType [in]  Arc type.
    \sa
    <link tv_geometry_arcs, Working with Arcs>
  */
  virtual OdBool circularArc(
    const OdGePoint3d& firstPoint,
    const OdGePoint3d& secondPoint,
    const OdGePoint3d& thirdPoint,
    const OdGiArcType arcType = kOdGiArcSimple) const = 0;

  /** \details
    Introduces a polyline to this vectorization context.  

    \param numVertices [in]  Number of vertices.
    \param vertexList [in]  Array of vertices.
    \param pNormal [in]  Pointer to the normal vector.
    \param baseSubEntMarker [in]  Not used.
    \remarks
    The polyline is unfilled and takes on the current color and thickness. Use polygon() to render filled areas.
    The polyline is rendered as a series of lines connecting the first point
    in vertexList to the second, the second to the third, etc.
    All points must be coplanar. Use polygon() to render closed areas.
    \sa
    <link tv_geometry_lines, Working with Lines>
  */
  virtual OdBool polyline(
    const OdUInt32 numVertices,
    const OdGePoint3d* vertexList,
    const OdGeVector3d* pNormal = 0,
    OdLongPtr baseSubEntMarker = -1) const = 0;

  virtual OdBool polyline(const GcGiPolyline& polylineObj) const;
  virtual OdBool polyPolyline(OdUInt32 nbPolylines, const GcGiPolyline* pPolylines) const;
  
  /** \details
    Introduces a polygon to this vectorization context.  

    \param numVertices [in]  Number of vertices.
    \param vertexList [in]  Array of vertices.
    \remarks
    The polygon is filled and takes on the current color. Use polyline() to render unfilled areas.
    The polygon is rendered as a series of lines connecting the first point
    in vertexList to the second, the second to the third, etc.
    All points must be coplanar.
    \sa
    <link tv_geometry_polygons, Working with Polygons>
  */
  virtual OdBool polygon(
    const OdUInt32 numVertices, 
    const OdGePoint3d* vertexList) const = 0;

  /** \details
    Introduces a polygon (with a normal) to this vectorization context.

    \param numVertices [in]  Number of vertices.
    \param vertexList [in]  Array of vertices.
    \param pNormal [in]  Pointer to the normal vector.
    \remarks
    The polygon is filled and takes on the current color. Use polyline() to render unfilled areas.
    The polygon is rendered as a series of lines connecting the first point
    in vertexList to the second, the second to the third, etc.
    All points must be coplanar.
    \sa
    <link tv_geometry_polygons, Working with Polygons>
  */
  virtual OdBool polygon(
    OdInt32 numVertices,
    const OdGePoint3d* vertexList,
    const OdGeVector3d* pNormal);

  virtual OdBool dashLineSegs(
    const OdUInt32 numSegs,
    const OdGeDashLine3d* dlList,
    const OdGeVector3d* pNormal = 0,
    OdLongPtr baseSubEntMarker = -1) const 
  {
    return kFalse;
  }

  virtual OdBool dashLineSegs(
    const OdGeMultiDashLine3d* dlList,
    const OdGeVector3d* pNormal = 0,
    OdLongPtr baseSubEntMarker = -1) const
  {
    return kFalse;
  }
  /** \details
    Introduces a lightweight polyline into this vectorization context.

    \param polyline [in]  Polyline.
    \param fromIndex [in]  Index of the first segment to be processed.
    \param numSegs [in]  Number of segments to be processed (0 indicates all segments).
    \remarks
    The polyline may contain varying segment widths, straight segments
    and arc segments. The polyline takes on the current color. All points must be coplanar.
    \sa
    <link tv_geometry_lines, Working with Lines>
  */
  virtual OdBool pline(
    const OdGiPolyline& polyline, 
    OdUInt32 fromIndex = 0, 
    OdUInt32 numSegs = 0) const
  {
    return kFalse;
  }

  virtual OdBool pline(
    const OdDbPolyline& polyline, 
    OdUInt32 fromIndex = 0, 
    OdUInt32 numSegs = 0) const = 0;

  /** \details
    Introduces a mesh into this vectorization context.  
    
    \param numRows [in]  Number of rows.
    \param numColumns [in]  Number of columns.
    \param vertexList [in]  Array of vertices.
    \param pEdgeData [in]  Pointer to additional edge data.
    \param pFaceData [in]  Pointer to additional face data.
    \param pVertexData [in]  Pointer to additional vertex data. 
    \remarks
    A mesh is a surface defined by a grid of vertices, and corresponds to a Polygon Mesh.
    By default, a mesh takes on the current color. Color, linetype, and
    and other properties can be controlled supplying the appropriate
    data for the pEdgeData, pFaceData, and pVertexData arguments.
    \remarks
    * vertexList must have numRows x numColumns elements.
    * The arrays in *pEdgeData must be NULL or contain (numRows - 1) x numColumns + numRows x (numColumns -1) elements.
    * The arrays in *pFaceData must be NULL or contain (numRows - 1) x (numColumns - 1) elements.
    * The arrays in *pVertexData must be NULL or contain numRows x numColumns elements. 
    \sa
    <link tv_geometry_meshes, Working with Meshes>
  */
  virtual OdBool mesh(
    const OdUInt32 numRows,
    const OdUInt32 numColumns,
    const OdGePoint3d* vertexList,
    const OdGiEdgeData* pEdgeData = 0,
    const OdGiFaceData* pFaceData = 0,
    const OdGiVertexData* pVertexData = 0,const bool bAutoGenerateNormals = true) const = 0;
  
  /** \details
    Introduces a shell into this vectorization context.  
    
    \param numVertices [in]  Number of vertices.
    \param vertexList [in]  Array of vertices.
    \param faceListSize [in]  Number of entries in facesList.
    \param faceList [in]  Array of integers defining faces.
    \param pEdgeData [in]  Pointer to additional edge data.
    \param pFaceData [in]  Pointer to additional face data.
    \param pVertexData [in]  Pointer to additional vertex data.
    \remarks
    A shell is a set of faces that can contain holes, and corresponds to a Polyface mesh.
    By default, a mesh takes on the current color. Color, linetype, and
    and other properties can be controlled supplying the appropriate
    data for the pEdgeData, pFaceData, and pVertexData arguments.
    \remarks
    * The arrays in *pEdgeData must be NULL or contain the same number of elements as there are edges.
    * The arrays in *pFaceData must be NULL or contain the same number of elements as there are faces.
    * The arrays in *pVertexData must be NULL or contain numVertices elements. 
    \sa
    <link tv_geometry_shells, Working with Shells>
  */
  virtual OdBool shell(
    const OdUInt32 numVertices,
    const OdGePoint3d* vertexList,
    const OdUInt32 faceListSize,
    const OdInt32* faceList,
    const OdGiEdgeData* pEdgeData = 0,
    const OdGiFaceData* pFaceData = 0,
    const OdGiVertexData* pVertexData = 0,
    const struct resbuf* pResBuf = NULL,
    const bool bAutoGenerateNormals = true) const = 0;
  
  /** Description:
    Introduces text into this vectorization context.
    
    \param position [in]  Position of the text string.
    \param normal [in]  Normal vector of the text.
    \param direction [in]  Baseline direction of the text.
    \param height [in]  Height of the text.
    \param width [in]  Width factor of the text.
    \param oblique [in]  Oblique angle.
    \param msg [in]  Text string.
    \remarks
    The text takes on the current color.
    If numBytes is not specified, msg must be null terminated.
    All angles are expressed in radians.
    As currently implemented, this function ignores width and oblique.
    They will be fully implemented in a future release.
    \sa
    <link tv_geometry_text, Working with Text>
  */
  virtual OdBool text(
    const OdGePoint3d& position,
    const OdGeVector3d& normal, 
    const OdGeVector3d& direction,
    const double height, 
    const double width, 
    const double oblique, 
    const OdChar * msg) const = 0;

  /** \details
    Introduces text into this vectorization context.
    
    \param position [in]  Position of the text string.
    \param normal [in]  Normal vector of the text.
    \param direction [in]  Baseline direction of the text.
    \param msg [in]  Text string.
    \param length [in]  Number of characters in msg (not including the optional null character).
    \param raw [in]  If and only if true, escape sequences, such as %%P, will not be converted to special characters.
    \param pTextStyle [in]  Pointer to the TextStyle for the text.
    \sa
    <link tv_geometry_text, Working with Text>
  */
  virtual OdBool text(
    const OdGePoint3d& position,
    const OdGeVector3d& normal, 
    const OdGeVector3d& direction,
    const OdChar* msg, 
    const OdInt32 length, 
    const OdBool raw, 
    const OdGiTextStyle& pTextStyle) const = 0;

  /** \details
    Introduces an Xline into this vectorization context.  
    
    \param firstPoint [in]  First point.
    \param secondPoint [in]  Second point.
    \remarks
    Xlines are infinite lines passing through two points.
    The xline takes on the current color.
    \sa
    <link tv_geometry_lines, Working with Lines>
  */
  virtual OdBool xline(
    const OdGePoint3d& firstPoint, 
    const OdGePoint3d& secondPoint) const = 0;

  /** \details
    Introduces a Ray into this vectorization context.  
 
    \param basePoint [in]  Base point.
    \param throughPoint [in]  Through point.
    \remarks
    A Ray is a semi-infinite line that starts at the basePoint, and passes 
    through the throughPoint. The ray takes on the current color.
    \sa
    <link tv_geometry_lines, Working with Lines>
  */
  virtual OdBool ray(
    const OdGePoint3d& basePoint, 
    const OdGePoint3d& throughPoint) const = 0;
  
  /** \details
    Introduces a NURBS curve into this vectorization context.
    
    \param nurbsCurve [in]  NURBS curve data.
    \remarks
    The curve takes on the current color.
    \sa
    <link tv_geometry_nurbs, Working with NURBS>
  */
  virtual OdBool nurbs(
    const OdGeNurbCurve3d& nurbsCurve,const OdGeVector3d* pNormal = 0) const 
  {
    return kFalse;
  }

  /** \details
    Introduces an elliptical arc into this vectorization context.
        
    \param ellipArc [in]  Elliptical arc.
    \param endPointsOverrides [in]  Array of points to be used as the first and last points of the vectorized arc.
    \param arcType [in]  Arc type.        
    \remarks
    arcType must be one of the following:
    
    <table>
    Name              Value     Description
    kOdGiArcSimple    0         Unfilled.
    kOdGiArcSector    1         Filled area bounded by the arc and its center.
    kOdGiArcChord     3         Filled area bounded by the arc and its end points
    </table>
    \sa
    <link tv_geometry_arcs, Working with Arcs>
  */
  virtual OdBool ellipArc(
    const OdGeEllipArc3d& ellipArc,
    const OdGePoint3d* endPointsOverrides = 0,
    OdGiArcType arcType = kOdGiArcSimple) const 
  {
    return kFalse;
  }

  /** \details
    Introduces the specified object into this vectorization context.
    
    \param pDrawable [in]  Pointer to the Drawable object.

    \remarks
    Implementations of this method are expected to do the following:
    * Call OdGiDrawable::subSetAttributes to set attribute information for the object.
    * Call subWorldDraw on the drawable object  to vectorize it into this context.
    * If subWorldDraw returns false, call subViewportDraw each viewport.
  */
  virtual OdBool draw(
    OdGiDrawable* pDrawable) const = 0;

  /** \details
    Specifies a clip boundary for the current clip stack.

    \param pBoundary [in]  Pointer to the boundary.
    \remarks
    Subsequent objects are clipped until popClipBoundary() is called.
    \sa
    <link gi_clipping_engine, Working with the Clipping Engine>
  */
  virtual OdBool pushClipBoundary(
    OdGiClipBoundary* pBoundary) = 0;

  /** \details
    Removes the top clip boundary from the clip stack.
    \sa
    <link gi_clipping_engine, Working with the Clipping Engine>
  */
  virtual void popClipBoundary() = 0;

  /** \details
    Introduces a line into this vectorization context.  

    \param points [in]  Array of WCS start and end points.
	  \remarks
    The current model transformation is not applied to the line.
    \sa
    <link tv_geometry_lines, Working with Lines>
  */
  virtual OdBool worldLine(const OdGePoint3d pnts[2]) 
  {
    return kFalse;
  };

  /** \details
    Inroduces a image in BGRA format into this vectorization context.
    
    \param img [in]  Image in BGRA format.
    \param origin [in]  Image position in WCS.
    \param uVec [in]  Image width and X-axis orientation.
    \param vVec [in]  Image height and Y-axis orientation.
    \param trpMode [in]  Image transparency processing mode.
    \sa
    <link tv_geometry_raster_images, Working with Raster Image Geometry Data>
  */
  virtual OdBool image(
    const OdGiImageBGRA32& img,
    const OdGePoint3d& origin,
    const OdGeVector3d& uVec,
    const OdGeVector3d& vVec,
    TransparencyMode trpMode = kTransparency8Bit) const
  {
    return kFalse;
  }

  /** \details
    Inroduces a boundary for hatch filling.
    
    \param edges [in]  Array of 2d curves which represents filling boundary.
  */
  virtual OdBool edge(
    const OdGiEdge2dArray& edges) const { return kFalse; }

  /** \details
    Returns currently processing GiDrawable objects graph.
    
    \returns
    pointer to the OdGiPathNode object that represents processing GiDrawable objects graph.
  */
  virtual const OdGiPathNode* currentGiPath() const;

  /** \details
    Specifies a clip boundary with additional clipping information for the current clip stack.

    \param pBoundary [in]  Pointer to the boundary.
    \param pClipInfo [in]  Additional clipping information.
    \remarks
    Subsequent objects are clipped until popClipBoundary() is called.
    \sa
    <link gi_clipping_engine, Working with the Clipping Engine>
  */
  virtual OdBool pushClipBoundary(
    OdGiClipBoundary* pBoundary, OdGiAbstractClipBoundary* pClipInfo);

  /** \details
    Introduces an array of points to this vectorization context.

    \param numPoints [in]  Number of point in array.
    \param vertexList [in]  Array of points.
    \param pColors [in]  Array of colors.
    \param pTransparency [in]  Array of transparencies.
    \param pNormals [in]  Optional array of normal vectors.
    \param pSubEntMarkers [in]  Optional array of subentity markers.
    \param nPointSize [in]  Size of points in pixels.
    \remarks
    The points takes on the current color if pColors array doesn't specified.
    Lengths of pColors, pTransparency, pNormals and pSubEntMarkers arrays if them set must be equal to numPoints.
  */
  virtual OdBool polypoint(
    OdInt32 numPoints,
    const OdGePoint3d* vertexList,
    const OdCmEntityColor* pColors,
    const OdCmTransparency* pTransparency,
    const OdGeVector3d* pNormals = NULL,
    const OdLongPtr* pSubEntMarkers = NULL,
    OdInt32 nPointSize = 0);
  
  /** \details
    Introduces an array of points to this vectorization context.

    \param numPoints [in]  Number of point in array.
    \param vertexList [in]  Array of points.
    \param pColors [in]  Array of colors.
    \param pNormals [in]  Optional array of normal vectors.
    \param pSubEntMarkers [in]  Optional array of subentity markers.
    \remarks
    The points takes on the current color if pColors array doesn't specified.
    Lengths of pColors, pNormals and pSubEntMarkers arrays if them set must be equal to numPoints.
  */
  ODRX_SEALED_VIRTUAL OdBool polypoint(
    OdInt32 numPoints,
    const OdGePoint3d* vertexList,
    const OdCmEntityColor* pColors,
    const OdGeVector3d* pNormals = NULL,
    const OdLongPtr* pSubEntMarkers = NULL) ODRX_SEALED;
  
  /** \details
    Introduces an array of points to this vectorization context.

    \param numPoints [in]  Number of point in array.
    \param vertexList [in]  Array of points.
    \param pNormals [in]  Optional array of normal vectors.
    \param pSubEntMarkers [in]  Optional array of subentity markers.
    \remarks
    The points takes on the current color if pColors array doesn't specified.
    Lengths of pNormals and pSubEntMarkers arrays if them set must be equal to numPoints.
  */
  ODRX_SEALED_VIRTUAL OdBool polypoint(
    OdInt32 numPoints,
    const OdGePoint3d* vertexList,
    const OdGeVector3d* pNormals = NULL,
    const OdLongPtr* pSubEntMarkers = NULL) ODRX_SEALED;

    /** \details
      Introduces set of polygons to this vectorization context.

      \param numIndices [in]  Number of polgon indices.
      \param pNumPositions [in]  Number of positions per polygon.
      \param pPositions [in]  Array of polygon offsets for all polygon invocations.
      \param pNumPoint [in]  Number of points per polygon.
      \param pPoints [in]  Array of polygon points.
      \param pOutlineColors [in]  Colors of polygon outlines.
      \param pOutlinePsLinetypes [in]  Linetypes of polygon outlines (see OdPs::LineType enumeration).
      \param pFillColors [in]  Polygon fill colors.
      \param pFillTransparencies [in]  Polygon fill transparencies.
    */
    virtual OdBool polyPolygon(const OdUInt32 numIndices, const OdUInt32* pNumPositions, const OdGePoint3d* pPositions,
                              const OdUInt32* pNumPoints, const OdGePoint3d* pPoints,
                              const OdCmEntityColor* pOutlineColors = NULL, const OdGiLineType* pOutlinePsLinetypes = NULL,
                              const OdCmEntityColor* pFillColors = NULL, const OdCmTransparency* pFillTransparencies = NULL) const;

  /** \details
    Introduces a row of points to this vectorization context.

    \param numPoints [in]  Number of points to draw.
    \param startPoint [in]  First point to draw.
    \param dirToNextPoint [in]  Offset and direction between next points.

    \remarks
    The points takes on the current color.
  */
  virtual OdBool rowOfDots(
    int numPoints, const OdGePoint3d& startPoint, const OdGeVector3d& dirToNextPoint) const;

  /** \details
    Introduces a Point Cloud entity into this vectorization context.

    \param pCloud [in]  Point Cloud object.
  */
  virtual void pointCloud(
    const OdGiPointCloud &pCloud);

  /** \details
    Introduces a BREP into this vectorization context.

    \param giBrep [in]  BREP.
    \return Returns true, if BREP input is supported, false other wise
  */
  virtual bool brep( const OdGiBrep& giBrep );
  
  virtual OdBool polyPoints(
    const OdUInt32 numVertices, 
    const OdGePoint3d* vertexList,
    OdLongPtr baseSubEntMarker = -1) const
  {
    return kFalse;
  }

  virtual OdBool polypoint(const OdUInt32 nbPoints, const OdGePoint3d* pVertexList, const OdGeVector3d* pNormal = NULL, const OdLongPtr *pSubEntMarkers = NULL) const 
  {
    OdGePoint3d pline[2];
    OdBool retval = kFalse;
    for (OdUInt32 i = 0; i < nbPoints; i++) 
    {
      pline[1] = pline[0] = pVertexList[i];
      retval = polyline(2, pline, pNormal ? &pNormal[i] : NULL, pSubEntMarkers ? pSubEntMarkers[i] : -1);
      if (retval)
        return retval;
    }
    return retval;
  };

  virtual OdBool lineSegs(
    const OdUInt32 numSegs , 
    const OdGePoint3d * vertexList,
    const OdGeVector3d* pNormal = 0,
    OdLongPtr baseSubEntMarker = -1) const;
	
  enum POLYLINEEXFLAGS
  {
    kNormal = 0,
    kOnlyHighlight = 0x01,
    kLinetypeGen = 0x02,
    kControlLine = 0x04,
    kControlPoint = 0x08
  };
  virtual OdBool polylineEx(
    const OdUInt32 numVertices,
    const OdGePoint3d* vertexList,
    const OdGeVector3d* pNormal = 0,
    OdLongPtr baseSubEntMarker = -1,
    int flags = 0) const
  {
    if ((flags & (OdGiGeometry::kControlLine | OdGiGeometry::kOnlyHighlight)) == 0)
    {
      return polyline(numVertices, vertexList, pNormal, baseSubEntMarker);
    }
    return kFalse;
  }

  enum DrawOperator
  {
    kNone = 0,
    kBeginEdgeModelIsolines,
    kEndEdgeModelIsolines,
    kBeginEdge,
    kEndEdge,
    kBeginTransients,
    kEndTransients,
    kBeginOnlyHightlight,
    kEndOnlyHightlight,
    kDynPlineArcSample,
    kDrawSimpleShell,
    kEdgeMode,
    kDispFacetEdges
  };
  virtual OdBool drawOperator(OdUInt32 op, void *pData) const
  {
    return kFalse;
  }

  virtual OdBool ownerDraw(GcGiGdiDrawObject*, const OdGePoint3d&, const OdGeVector3d&, const OdGeVector3d&) const
  {
    return kTrue;
  };
 
  virtual OdBool ellipticalArc(const OdGePoint3d& center, const OdGeVector3d& normal, double majorAxisLength,
    double minorAxisLength, double startDegreeInRads, double endDegreeInRads, double tiltDegreeInRads, OdGiArcType arcType = kOdGiArcSimple) const;
};

inline const OdGiPathNode* OdGiGeometry::currentGiPath() const
{
  return 0;
}

inline OdBool OdGiGeometry::pushClipBoundary(OdGiClipBoundary* pBoundary, OdGiAbstractClipBoundary* /*pClipInfo*/)
{
  // Some implementations could not support additional clipping styles, so redirect to old style clipping method by default.
  return pushClipBoundary(pBoundary);
}

inline OdBool OdGiGeometry::polygon(OdInt32 numVertices, const OdGePoint3d* vertexList, const OdGeVector3d* pNormal)
{
  return polygon(numVertices, vertexList);
}

inline OdBool OdGiGeometry::polypoint(OdInt32 numPoints, const OdGePoint3d* vertexList, const OdCmEntityColor* pColors,
                                    const OdGeVector3d* pNormals, const OdLongPtr* pSubEntMarkers)
{
  return polypoint(numPoints, vertexList, pColors, NULL, pNormals, pSubEntMarkers);
}

inline OdBool OdGiGeometry::polypoint(OdInt32 numPoints, const OdGePoint3d* vertexList,
                                    const OdGeVector3d* pNormals, const OdLongPtr* pSubEntMarkers)
{
  return polypoint(numPoints, vertexList, NULL, pNormals, pSubEntMarkers);
}

/** \details
This class is used to ensure OdGiGeometry::pushClipBoundary()/OdGiGeometry::popClipBoundary() 
consistency (exception safety).

\sa
TD_Gi

<group OdGi_Classes> 
*/
class OdGiClipBoundarySaver
{
  bool m_bSave;
  OdGiGeometry& m_geom;
public:
  OdGiClipBoundarySaver(OdGiGeometry& geom, bool bSave) : m_bSave(bSave), m_geom(geom){}
  void setSave(bool bSave){m_bSave = bSave;}
  ~OdGiClipBoundarySaver()
  {
    if (m_bSave)
      m_geom.popClipBoundary();
  }
};

/** \details
This class is used to ensure OdGiGeometry::pushModelTransform()/OdGiGeometry::popModelTransform() 
consistency (exception safety).

\sa
TD_Gi

<group OdGi_Classes> 
*/
class OdGiModelTransformSaver
{
  OdGiGeometry& m_geom;
public:
  OdGiModelTransformSaver(OdGiGeometry& geom, const OdGeMatrix3d& xMat) : m_geom(geom)
  {
    m_geom.pushModelTransform(xMat);
  }
  ~OdGiModelTransformSaver()
  {
    m_geom.popModelTransform();
  }
};

/* #11298 info: Matrix identity check was removed from OdGiModelTransformSaver and place into separate OdGiModelTransformSaverOpt class.
                Identity check is also time consuming operation and it is only makes things worse if matrices become identity seldom in
                some case. Following statistics on 10 typical drawing was collected on 18.10.2012:

                     Source File                                     : Line     Identity=true      Identity=false     % of identity=true
..\..\..\..\..\TD\Source\Gs\GsBlockReferenceNode.cpp                 : 1263     3202               60838              5%
..\..\..\..\..\TD\Source\Gs\GsBlockReferenceNodeImpl.cpp             : 707      2                  64364              0.003%
..\..\..\..\..\TD\Source\Gs\GsBlockReferenceNodeImpl.cpp             : 868      3                  62                 4.6%
..\..\..\..\..\TD\Source\database\Entities\DbBlockReference.cpp      : 1101     25                 64905              0.038%
..\..\..\..\..\TD\Source\database\Entities\DbDimension.cpp           : 1307     12546              16                 99.87%
..\..\..\..\..\TD\Source\database\Entities\DbHatchRender.cpp         : 714      38566              0                  100%
..\..\..\..\..\TD\Source\database\Entities\DbMInsertBlock.cpp        : 322      1603               30457              5%
..\..\..\..\..\TD\Source\database\Entities\DbModelerGeometryImpl.cpp : 1410     8                  0                  100%
..\..\..\..\..\TD\Source\database\Entities\DbModelerGeometryImpl.cpp : 1545     6                  0                  100%
..\..\..\..\..\TD\Source\database\Entities\DbPoint.cpp               : 264      0                  208                0%
..\..\..\..\TD\Source\database\GiDefaultContext.cpp                  : 454      4405               0                  100%
..\..\..\..\TD\Source\database\GiDefaultContext.cpp                  : 557      124                23626              0.522%

All places where percents of identity=true < 10% will use OdGiModelTransformSaver. Places where Identity=true very frequent will use
OdGiModelTransformSaverOpt. Unchecked places isn't principle since them are called very seldom.                                          */

/** \details
This class is used to ensure OdGiGeometry::pushModelTransform()/OdGiGeometry::popModelTransform() 
consistency (exception safety) with additional optimization check of matrix identity.

\sa
TD_Gi

<group OdGi_Classes> 
*/
class OdGiModelTransformSaverOpt
{
  OdGiGeometry& m_geom;
  bool          m_bIdentity;
public:
  OdGiModelTransformSaverOpt(OdGiGeometry& geom, const OdGeMatrix3d& xMat) : m_geom(geom)
  {
    // @@@TODO: check, probably simple memcmp will be more effective here. memcmp is very assembler-optimized in modern crt's. Identity
    //          matrix could be inexact only after some multiplications and etc. But statistics must be collected first for isEqual check
    //          and for memcmp, if it will be faster and precisely enough isEqualTo check with tolerance can be exchanged by memcmp.
    m_bIdentity = xMat.isEqualTo(OdGeMatrix3d::kIdentity);
    if (!m_bIdentity)
      m_geom.pushModelTransform(xMat);
  }
  ~OdGiModelTransformSaverOpt()
  {
    if (!m_bIdentity)
      m_geom.popModelTransform();
  }
};

class GcGiPolyline
{
public:
  GcGiPolyline()
    : m_nbPoints(0)
    , m_pVertexList(NULL)
    , m_pNormal(NULL)
    , m_lBaseSubEntMarker(-1)
    , m_linetypeGen(kEndToEnd)
    , m_pSubEntMarkerList(NULL)
    , m_pArcSegmentFlags(NULL)
  { }

  GcGiPolyline(OdUInt32  nbPoints,
    OdGePoint3d*   pVertexList,
    OdGeVector3d*  pNormal = NULL,
    OdLongPtr lBaseSubEntMarker = -1)
    : m_nbPoints(nbPoints)
    , m_pVertexList(pVertexList)
    , m_pNormal(pNormal)
    , m_lBaseSubEntMarker(lBaseSubEntMarker)
    , m_linetypeGen(kEndToEnd)
    , m_pSubEntMarkerList(NULL)
    , m_pArcSegmentFlags(NULL)
  { }

  enum LinetypeGeneration { kPerSegment, kEndToEnd };

  OdUInt32         points() const;
  const OdGePoint3d*    vertexList() const;
  const OdGeVector3d*   normal() const;
  LinetypeGeneration    linetypeGen() const;
  OdLongPtr        baseSubEntMarker() const;
  const OdLongPtr* subEntMarkerList() const;
  const bool*           arcSegmentFlags() const;

  void setVertexList(OdUInt32 nbPoints,
    const OdGePoint3d* pVertexList);
  void setNormal(const OdGeVector3d* pNormal);
  void setLinetypeGen(LinetypeGeneration ltgen);
  void setBaseSubEntMarker(OdLongPtr lBaseSubEntMarker);
  void setSubEntMarkerList(const OdLongPtr* pSubEntMarkerList);
  void setArcSegmentFlags(const bool *pArcSegmentFlags);

private:
  OdUInt32         m_nbPoints;
  const OdGePoint3d*    m_pVertexList;
  const OdGeVector3d*   m_pNormal;
  LinetypeGeneration    m_linetypeGen;
  OdLongPtr        m_lBaseSubEntMarker;
  const OdLongPtr* m_pSubEntMarkerList;
  const bool*           m_pArcSegmentFlags;
};

inline OdUInt32 GcGiPolyline::points() const
{
  return m_nbPoints;
}

inline const OdGePoint3d* GcGiPolyline::vertexList() const
{
  return m_pVertexList;
}

inline const OdGeVector3d* GcGiPolyline::normal() const
{
  return m_pNormal;
}

inline OdLongPtr GcGiPolyline::baseSubEntMarker() const
{
  return m_lBaseSubEntMarker;
}

inline GcGiPolyline::LinetypeGeneration GcGiPolyline::linetypeGen() const
{
  return m_linetypeGen;
}

inline const OdLongPtr* GcGiPolyline::subEntMarkerList() const
{
  return m_pSubEntMarkerList;
}

inline const bool* GcGiPolyline::arcSegmentFlags() const
{
  return m_pArcSegmentFlags;
}

inline void GcGiPolyline::setVertexList(
  OdUInt32  nbPoints,
  const OdGePoint3d*   pVertexList)
{
  m_nbPoints = nbPoints;
  m_pVertexList = pVertexList;
}

inline void GcGiPolyline::setNormal(const OdGeVector3d*  pNormal)
{
  m_pNormal = pNormal;
}

inline void GcGiPolyline::setBaseSubEntMarker(OdLongPtr lBaseSubEntMarker)
{
  m_lBaseSubEntMarker = lBaseSubEntMarker;
}

inline void GcGiPolyline::setLinetypeGen(GcGiPolyline::LinetypeGeneration ltgen)
{
  m_linetypeGen = ltgen;
}

inline void GcGiPolyline::setSubEntMarkerList(const OdLongPtr* pSubEntMarkerList)
{
  m_pSubEntMarkerList = pSubEntMarkerList;
}

inline void GcGiPolyline::setArcSegmentFlags(const bool* pArcSegmentFlags)
{
  m_pArcSegmentFlags = pArcSegmentFlags;
}

#ifndef _WINDEF_
struct HDC__;
typedef struct HDC__ *  HDC;
#endif

class GcGiGdiDrawObject : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(GcGiGdiDrawObject);

  virtual OdBool  draw(HDC hDC, int x, int y, int w, int h) = 0;
  virtual int     width() const = 0;
  virtual int     height() const = 0;
  virtual void    addRef() = 0;
  virtual void    delRef() = 0;
};

#include "../TD_PackPop.h"

#endif
