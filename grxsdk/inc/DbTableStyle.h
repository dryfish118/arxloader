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


#ifndef OD_DBTABLESTYLE_H
#define OD_DBTABLESTYLE_H

#include "TD_PackPush.h"
#include "DbObject.h"
#include "DbColor.h"
#include "OdValue.h"
#include "StringArray.h"

class OdDbTableTemplate;

  /** \details
    This class represents the parameters of cells for OdDbTable entities..
    
    <group Other_Classes>
  */
class OdCellRange
{
public:
  int  mnTopRow;
  int  mnLeftColumn;
  int  mnBottomRow;
  int  mnRightColumn;

  OdCellRange() : mnTopRow(-1)
    , mnLeftColumn(-1)
    , mnBottomRow(-1)
    , mnRightColumn(-1) {}

  OdCellRange(OdInt32 topRow, OdInt32 leftColumn, OdInt32 bottomRow, OdInt32 rightColumn)
    : mnTopRow(topRow)
    , mnLeftColumn(leftColumn)
    , mnBottomRow(bottomRow)
    , mnRightColumn(rightColumn)
  {}

  bool operator ==(
    const OdCellRange& range) const
  {
    return ( mnTopRow == range.mnTopRow &&
              mnLeftColumn == range.mnLeftColumn &&
              mnBottomRow == range.mnBottomRow &&
              mnRightColumn == range.mnRightColumn );
  }
  bool operator !=(
    const OdCellRange& range) const
  {
    return !( *this == range);
  }
};

typedef OdArray<OdCellRange> OdCellRangeArray;

 /** \details
    This class represents a grid for OdDbTable entities.
    
    <group Other_Classes>
 */
class OdGridProperty
{
public:

  OdDb::GridProperty  mnPropMask;
  OdDb::GridLineStyle mnLineStyle;
  OdDb::LineWeight    mnLineWeight;
  OdDbHardPointerId   mLinetype;
  OdCmColor           mColor;
  OdDb::Visibility    mnVisibility;
  double              mfDoubleLineSpacing;

  OdGridProperty() : mnPropMask(OdDb::kGridPropInvalid)
    , mnLineStyle(OdDb::kGridLineStyleSingle)
    , mnLineWeight(OdDb::kLnWtByBlock)
    , mnVisibility(OdDb::kVisible)
    , mfDoubleLineSpacing(0.0) {}

};

/** \details
    This class represents TableStyles for OdDbTable entities in an OdDbDatabase instance.

    <group OdDb_Classes>
*/
class DBENT_EXPORT OdDbTableStyle : public OdDbObject
{
public:
  ODDB_DECLARE_MEMBERS(OdDbTableStyle);

  OdDbTableStyle();
  // virtual ~OdDbTableStyle();

  // General Properties
  //
  
  /** \details
    Returns the name of this TableStyle object.
  */
  virtual OdString getName() const;

  virtual OdResult   getName(OdChar*& pszName) const;

  /** \details
    Sets the name of this TableStyle object.

    \param name [in]  Name.
  */
  virtual OdResult setName(const OdChar * pszName);

  bool isRenamable() const;

  /** \details
    Returns the description of this TableStyle object.
  */
  virtual const OdChar* description() const;

  /** \details
    Sets the description of this TableStyle object.
    
    \param description [in]  Description.
  */
  virtual OdResult setDescription(const OdChar * pszDescription);

  /** \details
    Returns the bit flags for this TableStyle object (DXF 71). 
      
    \remarks
    bitFlags() returns a combination of zero or more of the following:
    
    <table>
    Name                      Value
    kHorzInsideLineFirst      1
    kHorzInsideLineSecond     2
    kHorzInsideLineThird      4
    kTableStyleModified       8 
    </table>
  */
  virtual OdUInt32 bitFlags() const;

  /** \details
    Sets the bit flags for this TableStyle object (DXF 71). 
    
    \param bitFlags [in]  Bit flags.
    
    \remarks
    bitFlags must be a combination of one or more of the following:
    
    <table>
    Name                      Value
    kHorzInsideLineFirst      1
    kHorzInsideLineSecond     2
    kHorzInsideLineThird      4
    kTableStyleModified       8 
    </table>
  */
  virtual OdResult setBitFlags(OdUInt32 bitFlags);

  /** \details
    Returns the direction this TableStyle object flows from its first row to its last (DXF 70).

    \remarks
    flowDirection() returns one of the following:
    
    <table>
    Name          Value   Description
    OdDb::kTtoB   0       Top to Bottom
    OdDb::kBtoT   1       Bottom to Top
    </table>
  */
  virtual OdDb::FlowDirection flowDirection() const; 

  /** \details
    Sets the direction this TableStyle objectflows from its first row to its last. (DXF 70).

    \param flowDirection [in]  Flow direction.
    
    \remarks
    flowDirection must be one of the following: 
         
    <table>
    Name          Value   Description
    OdDb::kTtoB   0       Top to Bottom
    OdDb::kBtoT   1       Bottom to Top
    </table>
  */
  virtual OdResult setFlowDirection(OdDb::FlowDirection flowDirection);

  /** \details
    Returns the horizontal cell margin for this TableStyle object (DXF 40). 
    \remarks
    The horizontal cell margin is the horizontal space between the cell text and the cell border.
  */
  virtual double horzCellMargin() const;

  /** \details
    Sets the horizontal cell margin for this TableStyle object (DXF 40).
    
    \param cellMargin [in]  Cell margin.
    
    \remarks
    The horizontal cell margin is the horizontal space between the cell text and the cell border.
  */
  virtual OdResult setHorzCellMargin(double cellMargin);


  /** \details
    Returns the vertical cell margin for this TableStyle object (DXF 41). 

    \remarks
    The vertical cell margin is the vertical space between the cell text and the cell border.
  */
  virtual double vertCellMargin() const;

  /** \details
    Sets the vertical cell margin for this Table entity (DXF 41).
    
    \param cellMargin [in]  Cell margin.
    
    \remarks
    The vertical cell margin is the vertical space between the cell text and the cell border.
  */
  virtual OdResult setVertCellMargin(double cellMargin);

  /** \details
      Returns true if and only if the title row is suppressed for this TableStyle object (DXF 280).
  */
  virtual bool isTitleSuppressed() const;

  /** \details
    Controls the suppression of the title row (DXF 280).
    \param suppress [in]  Controls suppression.
  */
  virtual OdResult suppressTitleRow(
    bool suppress);

  /** \details
    Returns true if and only if the header row is suppressed for this TableStyle object (DXF 281). 
  */
  virtual bool isHeaderSuppressed() const;

  /** \details
      Controls the suppression of the header row for this TableStyle object (DXF 280).
      \param enable [in]  Controls suppression.
  */
  virtual OdResult suppressHeaderRow(
    bool suppress);


  /** \details
    Returns the Object ID of the text style for the specified row type in this TableStyle object (DXF 7).

    \param rowType [in]  Row type.
    
    \remarks
    rowType must be one of the following:
    
    <table>
    Name              Value
    kTitleRow         1
    kHeaderRow        2
    kDataRow          4
    </table>
  */
  virtual OdDbObjectId textStyle(
    OdDb::RowType rowType = OdDb::kDataRow) const;

  /** \details
    Sets the Object ID of the text style for the specified row types for this TableStyle object (DXF 7).
    
    \param rowTypes [in]  Row types.
    \param textStyleId [in]  Text style Object ID.

    \remarks
    rowTypes must be a combination of one or more of the following:
    
    <table>
    Name              Value
    kTitleRow         1
    kHeaderRow        2
    kDataRow          4
    </table>
  */
  virtual OdResult setTextStyle(
    const OdDbObjectId textStyleId, 
    int rowTypes = OdDb::kAllRows);

  /** \details
    Returns the text height for the specified row type in this TableStyle object (DXF 140).

    \param rowType [in]  Row type
    
    \remarks
    rowType must be one of the following:
    
    <table>
    Name                    Value
    OdDb::kTitleRow         1
    OdDb::kHeaderRow        2
    OdDb::kDataRow          4
    </table>
  */
  virtual double textHeight(
    OdDb::RowType rowType = OdDb::kDataRow) const;

  /** \details
    Sets the text height for the specified row types in this TableStyle object (DXF 140).

    \param rowTypes [in]  Row types.
    \param height [in]  Text height.

    \remarks
    rowTypes must be a combination of one or more of the following:
    
    <table>
    Name              Value
    kTitleRow         1
    kHeaderRow        2
    kDataRow          4
    </table>
  */
  virtual OdResult setTextHeight(double height, int rowTypes = OdDb::kAllRows);

  /** \details
    Returns the cell alignment for the specified row type in this TableStyle object (DXF 170).

    \param rowType [in]  Row type
    
    \remarks
    rowType() returns one of the following:
    
    <table>
    Name                    Value
    OdDb::kTitleRow         1
    OdDb::kHeaderRow        2
    OdDb::kDataRow          4
    </table>
    
    alignment() returns one of the following:
    
    <table>
    Name                    Value
    OdDb::kTopLeft          1
    OdDb::kTopCenter        2 
    OdDb::kTopRight         3
    OdDb::kMiddleLeft       4
    OdDb::kMiddleCenter     5
    OdDb::kMiddleRight      6
    OdDb::kBottomLeft       7 
    OdDb::kBottomCenter     8
    OdDb::kBottomRight      9
    </table>
  */
  virtual OdDb::CellAlignment alignment(
    OdDb::RowType rowType = OdDb::kDataRow) const;


  /** \details
    Sets the cell alignment for the specified row types in this TableStyle object (DXF 170).
    
    \param rowTypes [in]  Row types.
    \param alignment [in]  Alignment.

    \remarks
    rowTypes must be a combination of one or more of the following:
    
    <table>
    Name                    Value
    OdDb::kTitleRow         1
    OdDb::kHeaderRow        2
    OdDb::kDataRow          4
    </table>
    
    alignment must be one of the following:
    
    <table>
    Name                    Value
    OdDb::kTopLeft          1
    OdDb::kTopCenter        2 
    OdDb::kTopRight         3
    OdDb::kMiddleLeft       4
    OdDb::kMiddleCenter     5
    OdDb::kMiddleRight      6
    OdDb::kBottomLeft       7 
    OdDb::kBottomCenter     8
    OdDb::kBottomRight      9
    </table>
  */
  virtual OdResult setAlignment(
    OdDb::CellAlignment alignment, 
    int rowTypes = OdDb::kAllRows);

  /** \details
    Returns the text color for the specified row type in this TableStyle object (DXF 62).

    \param rowTypes [in]  Row types.

    \remarks
    rowTypes must be a combination of one or more of the following:
    
    <table>
    Name                    Value
    OdDb::kTitleRow         1
    OdDb::kHeaderRow        2
    OdDb::kDataRow          4
    </table>
  */
  virtual OdCmColor color(
    OdDb::RowType rowType = OdDb::kDataRow) const;
    

  /** \details
    Sets the text color for the specified row types in this TableStyle object (DXF 62).

    \param rowTypes [in]  Row types.
    \param color [in]  Color.

    \remarks
    rowTypes must be a combination of one or more of the following:
    
    <table>
    Name                    Value
    OdDb::kTitleRow         1
    OdDb::kHeaderRow        2
    OdDb::kDataRow          4
    </table>
  */
  virtual OdResult setColor(const OdCmColor& color, int rowTypes = OdDb::kAllRows);

  /** \details
    Returns the background color for the specified row type in this TableStyle object (DXF 63).

    \param rowType [in]  Row type.

    \remarks
    rowType must be one of the following:
    
    <table>
    Name                    Value
    OdDb::kTitleRow         1
    OdDb::kHeaderRow        2
    OdDb::kDataRow          4
    </table>
  */
  virtual OdCmColor backgroundColor(
    OdDb::RowType rowType = OdDb::kDataRow) const;

  /** \details
    Sets the background color for the specified row type in this TableStyle object (DXF 63). 

    \param rowTypes [in]  Row types.
    \param color [in]  Background color.
    
    \remarks
    rowTypes must be a combination of one or more of the following:
    
    <table>
    Name                    Value
    OdDb::kTitleRow         1
    OdDb::kHeaderRow        2
    OdDb::kDataRow          4
    </table>
  */
  virtual OdResult setBackgroundColor(const OdCmColor& color, int rowTypes = OdDb::kAllRows);

  /** \details
    Returns true if and only if the background color for the specified row 
    type is disabled for this TableStyle object (DXF 283).

    \param rowType [in]  Row type
    \param row [in]  Row index of the cell.
    \param column [in]  Column index of the cell.

    \remarks
    rowType must be one of the following:
    
    <table>
    Name                    Value
    OdDb::kTitleRow         1
    OdDb::kHeaderRow        2
    OdDb::kDataRow          4
    </table>
  */
  virtual bool isBackgroundColorNone(
    OdDb::RowType rowType = OdDb::kDataRow) const;

  /** \details
    Controls the background color setting for the specified row types or cell in this TableStyle object (DXF 283). 

    \param disable [in]  Disables the background color if true, enables if false.
    \param rowTypes [in]  Row types.

    \remarks
    rowTypes must be a combination of one or more of the following:
    
    <table>
    Name                    Value
    OdDb::kTitleRow         1
    OdDb::kHeaderRow        2
    OdDb::kDataRow          4
    </table>
  */
  virtual OdResult setBackgroundColorNone(bool disable, int rowTypes = OdDb::kAllRows);

  //Gridline properties
  //
  
  /** \details
    Returns the grid lineweight for the specified gridline type and row type in this TableStyle object (DXF 274-279).
      
    \param gridlineType [in]  Gridline type.
    \param rowType [in]  Row type.

    \remarks
    gridlineType must be one of the following:
    
    <table>
    Name                    Value
    OdDb::kHorzTop          1
    OdDb::kHorzInside       2
    OdDb::kHorzBottom       4
    OdDb::kVertLeft         8
    OdDb::kVertInside       0x10
    OdDb::kVertRight        0x20
    </table>
    
    rowType must be one of the following:
    
    <table>
    Name                    Value
    OdDb::kTitleRow         1
    OdDb::kHeaderRow        2
    OdDb::kDataRow          4
    </table>
    
  */
  virtual OdDb::LineWeight gridLineWeight(
    OdDb::GridLineType gridlineType,
    OdDb::RowType rowType = OdDb::kDataRow) const; 
  
  /** \details
    Sets the grid lineweight for the specified gridline types and row types,
    or the specified cell and edges in this Table entity (DXF 274-279).
      
    \param lineWeight [in]  Lineweight.      
    \param gridlineTypes [in]  Gridline types.
    \param rowTypes [in]  Row types.

    \remarks
    gridlineTypes must be a combination of one or more of the following:
    
    <table>
    Name                    Value
    OdDb::kHorzTop          1
    OdDb::kHorzInside       2
    OdDb::kHorzBottom       4
    OdDb::kVertLeft         8
    OdDb::kVertInside       0x10
    OdDb::kVertRight        0x20
    </table>
    
    rowTypes must be a combination of one or more of the following:
    
    <table>
    Name                    Value
    OdDb::kTitleRow         1
    OdDb::kHeaderRow        2
    OdDb::kDataRow          4
    </table>
  */
  virtual OdResult setGridLineWeight(OdDb::LineWeight lineWeight, int gridlineTypes = OdDb::kAllGridLines, int rowTypes = OdDb::kAllRows);


  /** \details
    Returns the grid color for the specified gridline type and row type
    in this TableStyle object (DXF 63,64,65,66,68,69).
      
    \param gridlineType [in]  Gridline type.
    \param rowType [in]  Row type.

    \remarks
    gridlineType must be one of the following:
    
    <table>
    Name                    Value
    OdDb::kHorzTop          1
    OdDb::kHorzInside       2
    OdDb::kHorzBottom       4
    </table>
    
    rowType must be one of the following:
    
    <table>
    Name                    Value
    OdDb::kTitleRow         1
    OdDb::kHeaderRow        2
    OdDb::kDataRow          4
    </table>
  */
  virtual OdCmColor gridColor(
    OdDb::GridLineType gridlineType,
    OdDb::RowType rowType = OdDb::kDataRow) const; 

  /** \details
    Returns the grid color for the specified gridline types and row type
    in this TableStyle object (DXF 63,64,65,66,68,69).
      
    \param gridlineTypes [in]  Gridline types.
    \param rowTypes [in]  Row types.

    \remarks
    gridlineTypes must be a combination of one or more of the following:
    
    <table>
    Name                    Value
    OdDb::kHorzTop          1
    OdDb::kHorzInside       2
    OdDb::kHorzBottom       4
    </table>
    
    rowTypes must be a combination of one or more of the following:
    
    <table>
    Name                    Value
    OdDb::kTitleRow         1
    OdDb::kHeaderRow        2
    OdDb::kDataRow          4
    </table>
  */
  virtual OdResult setGridColor(const OdCmColor color, int gridlineTypes = OdDb::kAllGridLines, int rowTypes = OdDb::kAllRows);


  /** \details
    Returns the grid visibility for the specified gridline type and row type,
    in this TableStyle object (DXF 284-289).
      
    \param gridlineType [in]  Gridline type.
    \param rowType [in]  Row type.

    \remarks
    gridVisibility() returns one of the following:
    
    <table>
    Name                    Value
    OdDb::kInvisible        1
    OdDb::kVisible          0 
    </table>
        
    gridlineType must be one of the following:
    
    <table>
    Name                    Value
    OdDb::kHorzTop          1
    OdDb::kHorzInside       2
    OdDb::kHorzBottom       4
    OdDb::kVertLeft         8
    OdDb::kVertInside       0x10
    OdDb::kVertRight        0x20
    </table>
    
    rowType must be one of the following:
    
    <table>
    Name                    Value
    OdDb::kTitleRow         1
    OdDb::kHeaderRow        2
    OdDb::kDataRow          4
    </table>
    
  */
  virtual OdDb::Visibility gridVisibility(
    OdDb::GridLineType gridlineType,
    OdDb::RowType rowType = OdDb::kDataRow) const; 


/** \details
    Sets the grid visibility for the specified gridline types and row types,
    in this TableStyle object (DXF 284-289).
      
    \param gridVisibility [in]  Grid visibility.      
    \param gridlineTypes [in]  Gridline types.
    \param rowTypes [in]  Row types.

    \remarks
    gridVisibility must be one of the following:
    
    <table>
    Name                    Value
    OdDb::kInvisible        1
    OdDb::kVisible          0 
    </table>
        
    gridlineTypes must be a combination of one or more of the following:
    
    <table>
    Name                    Value
    OdDb::kHorzTop          1
    OdDb::kHorzInside       2
    OdDb::kHorzBottom       4
    OdDb::kVertLeft         8
    OdDb::kVertInside       0x10
    OdDb::kVertRight        0x20
    </table>
    
    rowTypes must be a combination of one or more of the following:
    
    <table>
    Name                    Value
    OdDb::kTitleRow         1
    OdDb::kHeaderRow        2
    OdDb::kDataRow          4
    </table>
    
*/
  virtual OdResult setGridVisibility(OdDb::Visibility gridVisiblity, int gridlineTypes = OdDb::kAllGridLines, int rowTypes = OdDb::kAllRows);


  // NEW 2007
  
  virtual OdResult getDataType(
    OdValue::DataType& nDataType,
    OdValue::UnitType& nUnitType) const;

  virtual OdResult getDataType(
    OdValue::DataType& nDataType,
    OdValue::UnitType& nUnitType,
    OdDb::RowType rowType) const;

  virtual OdResult setDataType(OdValue::DataType nDataType, OdValue::UnitType nUnitType, int rowTypes);
  virtual OdResult setDataType(OdValue::DataType nDataType, OdValue::UnitType nUnitType);

  virtual const OdChar* format (void) const;
  virtual const OdChar* format (OdDb::RowType rowType) const;

  virtual OdResult setFormat(const OdChar* pszFormat);
  virtual OdResult setFormat(const OdChar* pszFormat, int rowTypes);


  virtual OdResult dwgInFields(
    OdDbDwgFiler* pFiler);

  virtual OdResult dwgOutFields(
    OdDbDwgFiler* pFiler) const;

  virtual OdResult dxfInFields(
    OdDbDxfFiler* pFiler);

  virtual OdResult dxfOutFields(
    OdDbDxfFiler* pFiler) const;

  // virtual OdResult audit(OdDbAuditInfo* pAuditInfo);

  // Utility functions
  //

  /** \details
    Applies the default properties of the specified database to this TableStyle object.
    
    \param pDb [in]  Pointer to the database whose default values are to be used.
     
    \remarks
    If pDb is null, the database containing this object is used
  */
  void setDatabaseDefaults(OdDbDatabase* pDb = 0);

  /** \details
    Adds this TableStyle object to the specified database.
  
    \param pDb [in]  Pointer to the database in which to post.
    \param styleName [in]  Name for the table style. 
    \param tableStyleId [out]  Receives 

    \returns
    Returns the Object ID of the posted table style.
  */
  virtual OdDbObjectId postTableStyleToDb(OdDbDatabase* pDb, const OdString& styleName);

  virtual OdResult postTableStyleToDb(OdDbDatabase* pDb, const OdChar* pStyleName, OdDbObjectId& tableStyleId);

  const OdChar *  createCellStyle(void);

  OdResult createCellStyle(const OdChar* pszCellStyle);

  OdResult createCellStyle(const OdChar* pszCellStyle, const OdChar* fromCellStyle);

  OdResult renameCellStyle(const OdChar* oldName, const OdChar* newName);

  OdResult deleteCellStyle(const OdChar* cellStyle);

  OdResult copyCellStyle(const OdChar* srcCellStyle, const OdChar* targetCellStyle);

  OdResult copyCellStyle(const OdDbTableStyle* pSrc, const OdChar* srcCellStyle, const OdChar* targetCellStyle);
  
  OdResult getUniqueCellStyleName(const OdChar* baseName, OdString& sUniqueName) const;

  bool isCellStyleInUse(const OdChar* cellStyle) const;

  OdInt32 numCellStyles(void) const;

  OdInt32 getCellStyles(OdStringArray& cellstyles) const;

  OdInt32 cellStyleId(const OdChar* cellStyle) const;
  OdString cellStyleName(OdInt32 cellStyle) const;

  OdDbObjectId textStyle(const OdChar* pszCellStyle) const;
  OdResult setTextStyle (const OdDbObjectId& id,const OdChar* pszCellStyle);

  double textHeight(const OdChar* cellStyle) const;
  OdResult setTextHeight(double dHeight, const OdChar* cellStyle);

  OdDb::CellAlignment alignment(const OdChar* cellStyle) const;
  OdResult setAlignment(OdDb::CellAlignment alignment, const OdChar* cellStyle);

  OdCmColor color(const OdChar* cellStyle) const;
  OdResult setColor(const OdCmColor& color, const OdChar* cellStyle);

  OdCmColor backgroundColor(const OdChar* cellStyle) const;
  OdResult setBackgroundColor(const OdCmColor& color, const OdChar* cellStyle);

  OdResult getDataType(OdValue::DataType& nDataType, OdValue::UnitType& nUnitType, const OdChar* pszCellStyle) const;
  OdResult setDataType(OdValue::DataType nDataType, OdValue::UnitType nUnitType, const OdChar* pszCellStyle);
 
  const OdChar * format(const OdChar* pszCellStyle) const;

  OdResult setFormat(const OdChar* pszFormat, const OdChar* pszCellStyle);

  OdInt32 cellClass(const OdChar* cellStyle) const;
  OdResult setCellClass(OdInt32 nClass, const OdChar* cellStyle);

  double rotation(const OdChar* cellStyle) const;
  OdResult setRotation(double rotation, const OdChar* cellStyle);

  bool isMergeAllEnabled (const OdChar* cellStyle) const;
  OdResult enableMergeAll(bool bEnable, const OdChar* cellStyle);

  double margin(OdDb::CellMargin nMargin, const OdChar* cellStyle) const;
  OdResult setMargin(OdDb::CellMargin nMargins, double fMargin, const OdChar* cellStyle);

  //Gridline properties
  //
  OdDb::LineWeight gridLineWeight(OdDb::GridLineType gridLineType, const OdChar* cellStyle) const;
  OdResult setGridLineWeight(OdDb::LineWeight lineWeight, OdDb::GridLineType gridLineTypes, const OdChar* cellStyle);

  OdCmColor gridColor(OdDb::GridLineType gridLineType, const OdChar* cellStyle) const;
  OdResult setGridColor(const OdCmColor color, OdDb::GridLineType gridLineTypes, const OdChar* cellStyle);

  OdDb::Visibility gridVisibility(OdDb::GridLineType gridLineType, const OdChar* cellStyle) const;
  OdResult setGridVisibility(OdDb::Visibility visible, OdDb::GridLineType gridLineTypes, const OdChar* cellStyle);

  double gridDoubleLineSpacing(OdDb::GridLineType gridLineType, const OdChar* cellStyle) const;
  OdResult setGridDoubleLineSpacing(double fSpacing, OdDb::GridLineType gridLineTypes, const OdChar* cellStyle);

  OdDb::GridLineStyle gridLineStyle(OdDb::GridLineType gridLineType, const OdChar* cellStyle) const;
  OdResult setGridLineStyle(OdDb::GridLineStyle nLineStyle, OdDb::GridLineType gridLineTypes, const OdChar* cellStyle);

  OdDbObjectId gridLinetype(OdDb::GridLineType gridLineType, const OdChar* cellStyle) const;
  OdResult setGridLinetype(const OdDbObjectId& id, OdDb::GridLineType gridLineTypes, const OdChar* cellStyle);

  OdResult getGridProperty(OdGridProperty& gridProp, OdDb::GridLineType nGridLineTypes, const OdChar* cellStyle) const;
  OdResult setGridProperty (const OdGridProperty& gridProp, OdDb::GridLineType nGridLineTypes, const OdChar* cellStyle);

  virtual OdResult subGetClassID(CLSID* pClsid) const;

  // Template functions
  OdDbObjectId  getTemplate(void) const;

  OdResult getTemplate(OdDbTableTemplate *&pTemplate, OdDb::OpenMode mode);

  OdResult setTemplate(const OdDbObjectId templateId, OdDb::MergeCellStyleOption nOption);

  OdResult setTemplate(
    OdDbTableTemplate *pTemplate,
    OdDb::MergeCellStyleOption nOption,
    OdDbObjectId& templateId);

  OdDbObjectId removeTemplate(void);
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbTableStyle object pointers.
*/
typedef OdSmartPtr<OdDbTableStyle> OdDbTableStylePtr;

#include "TD_PackPop.h"

#endif // OD_DBTABLESTYLE_H
