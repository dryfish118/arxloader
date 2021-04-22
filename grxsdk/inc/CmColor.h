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


#ifndef ODA_CM_COLOR
#define ODA_CM_COLOR

#include "OdString.h"
#include "Gi/Gi.h"
#include "CmColorBase.h"
#include "DbExport.h"

class OdCmEntityColor;
class OdDbDwgFiler;
class OdDbDxfFiler;
class OdDbAuditInfo;

#include "TD_PackPush.h"

class OdDbObject;
class OdDbFiler;

/** \details
    <group OdCm_Classes>

    This class implements Color object that represents the unnamed and named colors
    specified by the byLayer, byBlock, byColor, byACI, byPen, Foreground, byDgnIndex, or None 
    color methods.

    The OdCmEntityColor class,  the OdCmColorBase class
*/
class TOOLKIT_EXPORT OdCmColor : public OdCmColorBase
{
public:
  /** \details
    Default constructor. Sets the color to that of the layer.

    \remarks
      Specifies that the color method used by this color is kByLayer.
  */
  OdCmColor();
  
  /** \details
    Copy constructor. Sets the color according to a parameter.

    \param color [in] New color as OdCmColor.
  */
  OdCmColor(
    const OdCmColor& color);
  
  /** \details
    Constructor. Sets the color according to a parameter.

    \param color [in] New color as OdCmColorBase object.
  */
  OdCmColor(
    const OdCmColorBase& color);
    
  /** \details
    Constructor. Sets the color according to a color method.

    \param color [in] Color method.
    \remarks
    The color method can be one of the following:
    
    <table>
    <b>Name</b>    <b>Value</b>    <b>Description</b>
    kByLayer       0xC0            Color is specified by the layer object on which the object resides.
    kByBlock       0xC1            Color is specified by the block reference color.
    kByColor       0xC2            Color is specified by an RGB value.
    kByACI         0xC3            Color is specified by an index (ACI) of a color palette.
    kByPen         0xC4            Color is specified by an index of a pen color table.
    kForeground    0xC5            Color is the same as the foreground color.
    kByDgnIndex    0xC7            Color is specified by an index of a .dgn color table.
    kNone          0xC8            Color is absent (object is clear).
    </table>
  */
  OdCmColor(
    OdCmEntityColor::ColorMethod color, OdUInt32 rgbm = 0);
    
  /** \details
    Assignment operator. Assigns values of the rhs parameter to the lhs parameter.

    \param color [in] Color as OdCmdColor object.
    \returns OdCmColor object with values identical to those of the parameter.
    \remarks
      Values that are being assigned are RGBM, colorName and bookName. 
  */
  OdCmColor& operator=(const OdCmColor& inputColor)
  {
    setColor(inputColor.color());
    m_colorName = inputColor.m_colorName;
    m_bookName = inputColor.m_bookName;
    return (*this);
  }
    
  /** \details
    Assignment operator. Assigns values of the rhs parameter to the lhs parameter.

    \param color [in] Color as OdCmColorBase object.
    \returns OdCmColor object with values identical to those of the parameter.
  */
  OdCmColor& operator=(
    const OdCmColorBase& inputColor)
  {
    setColor(inputColor.color());
    m_colorName = inputColor.colorName();
    m_bookName = inputColor.bookName();
    return (*this);
  }
  
  /** \details
    Empty destructor.
  */
  ~OdCmColor();

  /** \details
    Compares two database color objects using their integer values together with their color names
    and returns true when their values are equal, or false when their values are not equal.

    \param color [in] Color as OdCmColor.
    \returns true if the objects are equal, false - otherwise.
  */
    bool operator ==(
    const OdCmColor& color) const;
    
  /** \details
    Compares an OdCmColor object and OdCmColorBase object using their integer values together with 
    their color names and returns true when their values are equal, or false when their values are 
    not equal. For comparison the OdCmColorBase object is converted to OdCmColor.

    \param color [in] Color as OdCmColorBase object.
    \returns true if the objects are equal, false - otherwise.
  */
  bool operator ==(
    const OdCmColorBase& color) const;

  /** \details
    Compares two database color objects using their integer values together with their color names
    and returns true when their values are not equal, or false when their values are equal.

    \param color [in] Color as OdCmColor.
    \returns true if the objects are not equal, false - otherwise.
  */
    bool operator !=(
    const OdCmColor& color) const;

  /** \details
    Compares two color objects as OdCmColor and OdCmColorBase their integer values together with their color names
    and returns true when their values are not equal, or false when their values are equal.
    For comparison the OdCmColorBase object is converted to OdCmColor.
  
    \param color [in] Color as OdCmColorBase.
    \returns true if the objects are not equal, false - otherwise.
  */
  bool operator !=(
    const OdCmColorBase& color) const;
  
  /** \details
    Returns the description string of the database color object.
  */
  OdString getDescription() const;

  /** \details
    Returns the explanation string of the database color object.
  */
  OdString getExplanation() const;

  /** \details
    Returns the color method of this color.

    \remarks
    The color method can be one of the following:

    <table>
    <b>Name</b>    <b>Value</b>    <b>Description</b>
    kByLayer       0xC0            Color is specified by the layer object on which the object resides.
    kByBlock       0xC1            Color is specified by the block reference color.
    kByColor       0xC2            Color is specified by an RGB value.
    kByACI         0xC3            Color is specified by an index (ACI) of a color palette.
    kByPen         0xC4            Color is specified by an index of a pen color table.
    kForeground    0xC5            Color is the same as the foreground color.
    kByDgnIndex    0xC7            Color is specified by an index of a .dgn color table.
    kNone          0xC8            Color is absent (object is clear).
    </table>
  */
  virtual OdCmEntityColor::ColorMethod colorMethod() const;

  /** \details
    Sets a color method for this color.

    \param colorMethod [in] Color method. Possible values are listed below.
    \remarks
    The color method can be one of the following:

    <table>
    <b>Name</b>    <b>Value</b>    <b>Description</b>
    kByLayer       0xC0            Color is specified by the layer object on which the object resides.
    kByBlock       0xC1            Color is specified by the block reference color.
    kByColor       0xC2            Color is specified by an RGB value.
    kByACI         0xC3            Color is specified by an index (ACI) of a color palette.
    kByPen         0xC4            Color is specified by an index of a pen color table.
    kForeground    0xC5            Color is the same as the foreground color.
    kByDgnIndex    0xC7            Color is specified by an index of a .dgn color table.
    kNone          0xC8            Color is absent (object is clear).
    </table>
  */
  virtual OdResult setColorMethod(
    OdCmEntityColor::ColorMethod colorMethod);

  /** \details
    Checks if the color is specified by an RGB value
    (color method of this color is set to "kByColor").
    

    \returns 
      true if the color method of this color is set to "kByColor", 
      false - otherwise.
  */
  virtual bool isByColor() const;

  /** \details
    Checks if the color is specified by the layer object on which the object resides
    (color method of this color is set to "kByLayer", 
    or it is set to "kByACI" and ACI color method is "kACIbyLayer").

    \returns 
      true if the color method of this color is set to "kByLayer",
      or if it is set to "kByACI" and ACI color method is "kACIbyLayer",
      false - otherwise.
  */
  virtual bool isByLayer() const;

  /** \details
    Checks if the color is specified by the block object in which the object is contained
    (color method of this color is set to "kByBlock",
    or it is set to "kByACI" and ACI color method is "kACIbyBlock").

    \returns 
      true if the color method of this color is set to "kByBlock", 
      or if it is set to "kByACI" and ACI color method is "kACIbyBlock",
      false - otherwise.
  */
  virtual bool isByBlock() const;

  /** \details
    Checks if the color is specified by an index (ACI) of a color palette 
    (color method of this color is set to "kByACI").

    \returns 
      true if the color method of this color is set to "kByACI", 
      false - otherwise.
  */
  virtual bool isByACI() const;

  /** \details
    Checks if the color is the same as the foreground color 
    (color method of this color is set to "kForeground",
    or it is set to "kByACI" and ACI color method is "kACIforeground").

    \returns 
      true if the color method of this color is set to "kForeground",
      or if it is set to "kByACI" and ACI color method is "kACIforeground",
      false - otherwise.
  */
  virtual bool isForeground() const;

  /** \details
    Checks if the color is specified by an index of a .dgn color table 
    (color method of this color is set to "kByDgnIndex").

    \returns Always false.
  */
  virtual bool isByDgnIndex() const;

  /** \details
    Checks if the color is absent 
    (color method of this color is set to "kNone",
    or it is set to "kByACI" and ACI color method is "kACInone").
    
    \returns 
      true if the color method of this color is set to "kNone",
      or if it is set to "kByACI" and ACI color method is "kACInone",
      false - otherwise.
  */
  bool isNone() const;

  /** \details
    Returns the current color value as integer.
  */
  virtual OdUInt32 color() const;

  /** \details
    Sets a color and color method from an integer value.

    \param color [in] Color value as integer.
  */
  virtual OdResult setColor(
    OdUInt32 color);

  /** \details
    Sets color using RGB values. Color method is set to "kByColor".

    \param red [in] Red component value.
    \param green [in] Green component value.
    \param blue [in] Blue component value.
  */
  virtual OdResult setRGB(
    OdUInt8 red, 
    OdUInt8 green, 
    OdUInt8 blue);

  /** \details
    Sets the red component of this color.

    \param red [in] Red component value.
  */
  virtual OdResult setRed(
    OdUInt8 red);

  /** \details
    Sets the green component of this color.

    \param green [in] Green component value.
  */
  virtual OdResult setGreen(
    OdUInt8 green);

  /** \details
    Sets the blue component of this color.

    \param blue [in] Blue component value.
  */
  virtual OdResult setBlue(
    OdUInt8 blue);

  /** \details
    Returns the value of the red component of this color.
  */
  virtual OdUInt8 red() const;

  /** \details
    Returns the value of the green component of this color.
  */
  virtual OdUInt8 green() const;
  
  /** \details
    Returns the value of the blue component of this color.
  */
  virtual OdUInt8 blue() const;

  /** \details
    Returns the color index (ACI) of the entity color object.
        
    \remarks
      The color index can be one of the following:
     
      <table>
      Name              Value   Description
      kACIbyBlock       0       Sets the color method to byBlock.
      kACIRed           1       Red. 
      kACIYellow        2       Yellow. 
      kACIGreen         3       Green. 
      kACICyan          4       Cyan. 
      kACIBlue          5       Blue. 
      kACIMagenta       6       Magenta. 
      kACIforeground    7       Sets the color method to Foreground.
      ..                8-255   Defined by current palette.
      kACIbyLayer       256     Sets the color method to byLayer. 
      kACInone          257     Sets the color method to None.
      </table>
  */
  virtual OdUInt16 colorIndex() const;

  /** \details
    Sets the color index (ACI) of a color palette and sets the color method to byACI for the entity color object.

    \param colorIndex [in]  An integer value that is the index of the color in a palette.
    \remarks
      The color index can be one of the following:

      <table>
      Name              Value   Description
      kACIbyBlock       0       Sets the color method to byBlock.
      kACIRed           1       Red.
      kACIYellow        2       Yellow.
      kACIGreen         3       Green.
      kACICyan          4       Cyan.
      kACIBlue          5       Blue.
      kACIMagenta       6       Magenta.
      kACIforeground    7       Sets the color method to Foreground.
      ..                8-255   Defined by current palette.
      kACIbyLayer       256     Sets the color method to byLayer.
      kACInone          257     Sets the color method to None.
      </table>

      An entity does not have a color from the time it is first instantiated until it is assigned one
      or added to a database.
  */
  virtual OdResult setColorIndex(
    OdUInt16 colorIndex);

  /** \details
    Sets the color name and the book name.

    \param colorName [in] Name of the color to be set.
    \param bookName [in] Name of the book to be set.
    \returns 
      true if the operation is complete.
      If colorName is empty, but bookName isn't - returns false.
      If colorName and bookName are empty - returns true.
    \remarks
      If colorName is empty, then current bookName will be emptied,
      and the new one will not be assigned.
  */
  virtual OdResult setNames(
    const OdChar* colorName,
    const OdChar* bookName = NULL);

  /** \details
    Returns the name of the current color.
  */
  virtual const OdChar* colorName() const;

  /** \details
    Returns the current book name.
  */
  virtual const OdChar* bookName() const;

  /**
    If colorName isn't empty, returns it as a string.
    Otherwise returns color method as a string.
  */
  virtual const OdChar* colorNameForDisplay();

  // Gcad(Add) {{
  virtual bool hasColorName() const;
  virtual bool hasBookName() const;
  virtual bool isByPen() const;
  virtual OdUInt16 penIndex() const;
  virtual OdResult setPenIndex(OdUInt16 penIndex);

  // Gcad(Add) }}
  /** \details
    Returns the OdCmEntityColor settings of the database color object.
  */
  OdCmEntityColor entityColor() const;

  /** \details
    Returns a dictionary key based on the color name and book name of the database color object.
   
    \remarks
    OdCmColor objects with color names can be stored in the form of an OdDbColor in a dictionary.
    getDictionaryKey() returns the key for that dictionary.
  */
  OdString getDictionaryKey() const;
  
  /** \details
    Sets the book name and color name for the dictionary keyword.

    \param dictionaryKey [in]  Dictionary keyword.   
    \returns
      Returns true if and only if successful.
      The dictionary key is the string that is the combination of the book name and color name joined by the dollar '$' symbol
  */
  OdResult setNamesFromDictionaryKey(
    const OdChar* dictKey);

  /** \details
    Reads the .dwg file format data of this object from the specified file.
       
    \param pFiler [in]  Pointer to the filer from which the data are to be read.
  */
  OdResult dwgIn(
    OdDbDwgFiler* pFiler);

  /** \details
    Writes the .dwg file format data of this object to the specified filer. 
    
    \param pFiler [in]  Pointer to the filer to which the data are to be written.
  */
  OdResult dwgOut(
    OdDbDwgFiler* pFiler) const;

  /** \details
    Reads the DXF format data of this object from the specified filer. 
    
    \param pFiler [in]  Pointer to the filer from which the data are to be read.
    \param groupCodeOffset [in]  Group code offset.
  */
  OdResult dxfIn(
    OdDbDxfFiler* pFiler, 
    int groupCodeOffset = 0);

  /** \details
    Writes the DXF format data of this object to the specified filer. 
    
    \param pFiler [in]  Pointer to the filer to which the data are to be written.
    \param groupCodeOffset [in]  Group code offset.
  */
  OdResult dxfOut(
    OdDbDxfFiler* pFiler, 
    int groupCodeOffset = 0) const;

  /** \details
    Perform an audit operation on this object.

    \param pAuditInfo [in]  Pointer to an AuditInfo object.
    \remarks
      When overriding this function for a custom class, first call OdCmColorBase::audit(pAuditInfo) 
      to validate the audit operation.
  */
  OdResult audit(
    OdDbAuditInfo* pAuditInfo);

  int dictionaryKeyLength() const; // Gcad(Add)
 OdResult getDictionaryKey(OdChar* dictKey) const;
 OdResult getDictionaryKey(OdChar *pKey, size_t nLen) const;
  OdResult serializeOut(void *pBuff, int *pBuflen, OdDb::DwgVersion ver = OdDb::kDHL_CURRENT) const;
  OdResult serializeIn(const void *pBuff, int *pBuflen);
  /**
	This function sets desc to point to a copy of the OdCmColor object's description string, or,
	if the OdCmColor object is complex, then a copy of that OdCmComplexColor object's description
	string is returned instead.
   */
  OdResult getDescription(OdChar*& desc) const;
  
  /**
	This function sets desc to point to a copy of the OdCmColor object's explanation string, or,
	if the OdCmColor object is complex, then a copy of that OdCmComplexColor object's explanation
	string is returned instead.
  */
  OdResult getExplanation(OdChar*& exp) const;
  OdResult     dwgInAsTrueColor (
    OdDbDwgFiler* pFiler);

  /*!DOM*/
  OdResult     dwgOutAsTrueColor(
    OdDbDwgFiler* pFiler) const;

  TOOLKIT_EXPORT_STATIC static const OdUInt16 MaxColorIndex;

private:
  enum NameFlags
  {    
    kNoNames      = 0,
    kHasColorName = 1,
    kHasBookName  = 2
  };
  OdCmEntityColor::RGBM   m_RGBM;
  OdString                m_colorName;
  OdString                m_bookName;
};

class TOOLKIT_EXPORT OdCmHSB
{
public:
  OdCmHSB();
  OdCmHSB(OdUInt16 hue, OdUInt8 saturation, OdUInt8 brightness);
  OdCmHSB(const OdCmHSB&);
  OdCmHSB& operator=(const OdCmHSB& inputColor);
  virtual ~OdCmHSB();
  bool operator ==(const OdCmHSB& color) const;
  bool operator !=(const OdCmHSB& color) const;
  virtual OdUInt32     value() const;
  virtual OdResult rgbToHSB(OdUInt8 r, OdUInt8 g, OdUInt8 b);
  virtual OdResult hsbToRGB(OdUInt8 *r, OdUInt8 *g, OdUInt8 *b);
  virtual OdResult setHSB(OdUInt32 value);
  virtual OdResult setHSB(OdUInt16 hue,OdUInt8 saturation,OdUInt8 brightness);
  virtual OdResult setHSB(double hue, double saturation, double brightness);
  virtual OdResult setHue(OdUInt16 hue);
  virtual OdResult setHue(double hue);
  virtual OdResult setSaturation(OdUInt8 saturation);
  virtual OdResult setSaturation(double saturation);
  virtual OdResult setBrightness(OdUInt8 brightness);
  virtual OdResult setBrightness(double brightness);
  virtual OdUInt16     hue() const;
  virtual OdUInt8     saturation() const;
  virtual OdUInt8      brightness() const;
private:
  OdUInt32           mHSB;
};


inline OdCmColor::OdCmColor()
{
  setColorMethod(OdCmEntityColor::kByLayer);
}

inline OdCmColor::OdCmColor(const OdCmColor& col)
{
  m_RGBM = col.m_RGBM;
  m_colorName = col.m_colorName;
  m_bookName = col.m_bookName;
}

inline OdCmColor::~OdCmColor()
{
}

inline OdCmEntityColor::ColorMethod OdCmColor::colorMethod() const
{
  return OdCmEntityColor::colorMethod(&m_RGBM);
}

inline OdResult OdCmColor::setColorMethod(OdCmEntityColor::ColorMethod cm)
{
  return OdCmEntityColor::setColorMethod(&m_RGBM, cm);
}

inline bool OdCmColor::isByColor() const
{
  return OdCmEntityColor::isByColor(&m_RGBM);
}

inline bool OdCmColor::isByLayer() const
{
  return OdCmEntityColor::isByLayer(&m_RGBM);
}

inline bool OdCmColor::isByBlock() const
{
  return OdCmEntityColor::isByBlock(&m_RGBM);
}

inline bool OdCmColor::isByACI() const
{
  return OdCmEntityColor::isByACI(&m_RGBM);
}

inline bool OdCmColor::isForeground() const
{
  return OdCmEntityColor::isForeground(&m_RGBM);
}

inline bool OdCmColor::isByDgnIndex() const
{
  return false;
}

inline bool OdCmColor::isNone() const
{
  return OdCmEntityColor::isNone(&m_RGBM);
}

inline OdUInt32 OdCmColor::color() const
{
  return m_RGBM.whole;
}

inline OdResult OdCmColor::setColor(OdUInt32 color)
{
  return OdCmEntityColor::setColor(&m_RGBM, color);
}

inline OdResult OdCmColor::setRGB(OdUInt8 red, OdUInt8 green, OdUInt8 blue)
{
  return OdCmEntityColor::setRGB(&m_RGBM, red, green, blue);
}

inline OdResult OdCmColor::setRed(OdUInt8 red)
{
  if (colorMethod() == OdCmEntityColor::kByColor)
    return OdCmEntityColor::setRed(&m_RGBM, red);
  else
    return eNotApplicable;
}

inline OdResult OdCmColor::setGreen(OdUInt8 green)
{
  if (colorMethod() == OdCmEntityColor::kByColor)
    return OdCmEntityColor::setGreen(&m_RGBM, green);
  else
    return eNotApplicable;
}

inline OdResult OdCmColor::setBlue(OdUInt8 blue)
{
  if (colorMethod() == OdCmEntityColor::kByColor)
    return OdCmEntityColor::setBlue(&m_RGBM, blue);
  else
    return eNotApplicable;
}

inline OdUInt8 OdCmColor::red() const
{
  switch (colorMethod())
  {
  case OdCmEntityColor::kByLayer:
  case OdCmEntityColor::kByBlock:
    return 0;
  case OdCmEntityColor::kByColor:
    return OdCmEntityColor::red(&m_RGBM);
  case OdCmEntityColor::kByACI:
    return OdCmEntityColor::mLUT[colorIndex()][0];
  case OdCmEntityColor::kForeground:
  case OdCmEntityColor::kNone:
    return 0;
  case OdCmEntityColor::kByDgnIndex:
  case OdCmEntityColor::kByPen:
    ODA_FAIL_ONCE();
    return 0;
  }
  return 0;
}

inline OdUInt8 OdCmColor::green() const
{
  switch (colorMethod())
  {
  case OdCmEntityColor::kByLayer:
  case OdCmEntityColor::kByBlock:
    return 0;
  case OdCmEntityColor::kByColor:
    return OdCmEntityColor::green(&m_RGBM);
  case OdCmEntityColor::kByACI:
    return OdCmEntityColor::mLUT[colorIndex()][1];
  case OdCmEntityColor::kForeground:
  case OdCmEntityColor::kNone:
    return 0;
  case OdCmEntityColor::kByDgnIndex:
  case OdCmEntityColor::kByPen:
    ODA_FAIL_ONCE();
    return 0;
  }
  return 0;
}

inline OdUInt8 OdCmColor::blue() const
{
  switch (colorMethod())
  {
  case OdCmEntityColor::kByLayer:
  case OdCmEntityColor::kByBlock:
    return 0;
  case OdCmEntityColor::kByColor:
    return OdCmEntityColor::blue(&m_RGBM);
  case OdCmEntityColor::kByACI:
    return OdCmEntityColor::mLUT[colorIndex()][2];
  case OdCmEntityColor::kForeground:
  case OdCmEntityColor::kNone:
    return 0;
  case OdCmEntityColor::kByDgnIndex:
  case OdCmEntityColor::kByPen:
    ODA_FAIL_ONCE();
    return 0;
  }
  return 0;
}


inline OdUInt16 OdCmColor::colorIndex() const
{
  return OdCmEntityColor::colorIndex(&m_RGBM);
}

inline OdResult OdCmColor::setColorIndex(OdUInt16 colorIndex)
{
  return OdCmEntityColor::setColorIndex(&m_RGBM, colorIndex);
}

inline OdResult OdCmColor::setNames(const OdChar* colorName, const OdChar* bookName)
{
  if (colorName == NULL)
  {
    return Oda::eNotApplicable;
  }

  // Acad returns eInvalidKey if colorName.isEmpty() && !bookName.isEmpty()
  // But throwing exception is superfluous decision (it can corrupt loading of files which acad loads correctly)
  m_colorName = colorName;
  if (m_colorName.isEmpty())
  {
    m_bookName.empty();
    return ((bookName == NULL || *bookName == __OD_T('\0')) ? Oda::eOk : Oda::eInvalidKey);
  }
  m_bookName = (bookName ? bookName : OdString::kEmpty);
  return Oda::eOk;
}

inline const OdChar* OdCmColor::colorName() const
{
  return m_colorName;
}

inline const OdChar* OdCmColor::bookName() const
{
  return m_bookName;
}

inline OdUInt16 OdCmColor::penIndex() const
{ // GreatStar(Todo)
  return OdCmEntityColor::penIndex(&m_RGBM);
}

inline OdResult OdCmColor::setPenIndex(OdUInt16 penIndex)
{ // GreatStar(Todo)
  return OdCmEntityColor::setPenIndex(&m_RGBM, penIndex);
}

#if defined(TD_Gs_EXPORTS) || defined(TD_Gi_EXPORTS) || defined(TD_Root_EXPORTS) ||defined(TD_DbRoot_EXPORTS)
inline const OdChar* OdCmColor::colorNameForDisplay()
{
  if (!m_colorName.isEmpty())
    return m_colorName;

  static OdString res;
  return res;
}
#endif

inline bool OdCmColor::hasColorName() const
{
  const OdChar* name = colorName();
  return (name != NULL && *name != 0);
}

inline bool OdCmColor::hasBookName() const
{
  const OdChar* name = bookName();
  return (name != NULL && *name != 0);
}

inline bool OdCmColor::isByPen() const
{ // GreatStar(Todo)
  return (OdCmEntityColor::colorMethod(&m_RGBM) == OdCmEntityColor::kByPen);
}

inline OdCmEntityColor OdCmColor::entityColor(void) const
{
  OdCmEntityColor res;
  res.setColor(color());
  return res;
}


#include "TD_PackPop.h"

#endif // ODA_CM_COLOR
