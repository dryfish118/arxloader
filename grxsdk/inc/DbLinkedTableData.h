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



#ifndef OD_DBLINKEDTABLEDATA_H
#define OD_DBLINKEDTABLEDATA_H

#include "TD_PackPush.h"

#include "DbObject.h"
#include "DbTableStyle.h"
#include "DbLinkedData.h"
#include "DbDataLink.h"
#include "DbField.h"
#include "DbTableIterator.h"

/** \details
  This class represents LinkedTableData objects in an OdDbDatabase instance.
  This enables linking to Excel data.

  \remarks
  Work in progress!


  <group OdDb_Classes> 
*/
class DBENT_EXPORT OdDbLinkedTableData : public OdDbLinkedData
{
public:
  //DOM-IGNORE-BEGIN
  ODDB_DECLARE_MEMBERS(OdDbLinkedTableData);
  //DOM-IGNORE-END

  /** \details
    Default constructor. Creates an object of the OdDbLinkedTableData class.
  */
  OdDbLinkedTableData();

  /** \details
    Sets the size for this linked table object.

    \param nRows [in]  Number of rows.
    \param nCols [in]  Number of columns.

    \remarks
    Method generates the eInvalidInput exception when the number of rows or
    columns is zero.
  */
  virtual OdResult setSize(
    int nRows, 
    int nCols);

  /** \details
    Returns the number of columns in this linked table object.
  */
  virtual int numColumns() const;

  /** \details
    Returns the column name as an OdString value.

    \param nIndex [in]  Column index.
    \returns Column name.
  */
  virtual const OdChar*  getColumnName(
    int nIndex) const;

  /** \details
    Sets the column name.

    \param nIndex [in]  Column index.
    \param name   [in]  Column name.
  */
  virtual OdResult setColumnName(
    int nIndex, 
    const OdChar*  name);

  /** \details
    Appends the specified number of columns into this linked table object.

    \param nNumCols [in]  Number of columns to add.
    \returns Starting index of the appended columns.
    \remarks
    Method generates the eInvalidInput exception when the row argument is zero
    or negative.
  */
  virtual int appendColumn(
    int nNumCols);

  /** \details
    Inserts the specified number of columns into this linked table object at the
    specified column index.

    \param nIndex   [in]  Column index.
    \param nNumCols [in]  Number of columns to insert.
    \returns Starting index of the inserted columns.
    \remarks
    Method generates the eInvalidInput exception when the column argument is
    grater than the number of columns or the width is zero.
  */
  virtual int insertColumn(
    int nIndex, 
    int nNumCols);

  /** \details
    Deletes the specified number of columns from this linked table object.

    \param nIndex           [in]  Index of the first column to delete.
    \param nNumColsToDelete [in]  Number of columns to delete.

    \remarks
    Method generates the eInvalidInput exception when the number of deleted
    columns is grater than the number of columns.
  */
  virtual OdResult deleteColumn(
    int nIndex, 
    int nNumColsToDelete);

  /** \details
    Returns the number of rows in this linked table object.

    \remarks
    This includes title and header rows if any.
  */
  virtual int numRows() const;

  /** \details
    Checks if new rows or columns can be inserted into the specified index.

    \param nIndex [in]  Index.
    \param bRow   [in]  Flag that indicates what to check: "true" for rows or "false" for columns.
    \returns True if rows or columns can be inserted; false otherwise.
  */
  virtual bool canInsert(
    int nIndex, 
    bool bRow) const;

  /** \details
    Appends the specified number of rows into this linked table object.

    \param nNumRows [in]  Number of rows to add.
    \returns Starting index of the appended rows.
    \remarks
    Method generates the eInvalidInput exception when the nNumRows argument is
    zero or negative.
  */
  virtual int appendRow(
    int nNumRows);

  /** \details
    Inserts the specified number of rows into this linked table object at the
    specified row index.

    \param nIndex   [in]  Row index.
    \param nNumRows [in]  Number of rows to insert.
    \returns Starting index of the inserted rows.
    \remarks
    Method generates the eInvalidInput exception when the nNumRows argument is
    zero or negative.
  */
  virtual int insertRow(
    int nIndex, 
    int nNumRows);

  /** \details
    Checks if rows or columns can be deleted from the specified index.

    \param nIndex [in]  Index.
    \param nCount [in]  Number of rows or columns.
    \param bRow   [in]  Flag that indicates what to check: "true" for rows or "false" for columns.
    \returns True if rows or columns can be deleted; false otherwise.
  */
  virtual bool canDelete(
    int nIndex, 
    int nCount, 
    bool bRow) const;

  /** \details
    Deletes the specified number of rows from this linked table object.

    \param nIndex           [in]  Index of the first row to delete.
    \param nNumRowsToDelete [in]  Number of rows to delete.

    \remarks
    Method generates the eInvalidInput exception when the number of rows to
    delete is grater than the number of rows in this linked table object.
  */
  virtual OdResult deleteRow(
    int nIndex, 
    int nNumRowsToDelete);

  /** \details
    Returns the "editing content flag" cell property.

    \param nRow [in]  Row index of the cell.
    \param nCol [in]  Column index of the cell.
    \returns True if the cell content can be edited or false if not.
  */
  virtual bool isContentEditable(
    int nRow, 
    int nCol) const;

  /** \details
    Returns the state of the cell.

    \param nRow [in]  Row index of the cell.
    \param nCol [in]  Column index of the cell.
    \returns Cell state.
    \remarks
    Cell state is an enumerator and takes one of the following values:

    <table>
    Name                                   Value
    kCellStateNone                         0x00
    kCellStateContentLocked                0x01
    kCellStateContentReadOnly              0x02
    kCellStateLinked                       0x04
    kCellStateContentModifiedAfterUpdate   0x08
    kCellStateFormatLocked                 0x10
    kCellStateFormatReadOnly               0x20
    kCellStateFormatModifiedAfterUpdate    0x40
    kAllCellStates                         (kCellStateContentLocked | kCellStateContentReadOnly |
                                           kCellStateLinked | kCellStateContentModifiedAfterUpdate |
                                           kCellStateFormatLocked | kCellStateFormatReadOnly |
                                           kCellStateFormatModifiedAfterUpdate)
    </table>
  */
  virtual OdDb::CellState cellState(
    int nRow, 
    int nCol) const;

  /** \details
    Sets the cell state.

    \param nRow       [in]  Row index of the cell.
    \param nCol       [in]  Column index of the cell.
    \param nCellState [in]  Cell state.

    \remarks
    Cell state should take one of the following values:

    <table>
    Name                                   Value
    kCellStateNone                         0x00
    kCellStateContentLocked                0x01
    kCellStateContentReadOnly              0x02
    kCellStateLinked                       0x04
    kCellStateContentModifiedAfterUpdate   0x08
    kCellStateFormatLocked                 0x10
    kCellStateFormatReadOnly               0x20
    kCellStateFormatModifiedAfterUpdate    0x40
    kAllCellStates                         (kCellStateContentLocked | kCellStateContentReadOnly |
                                           kCellStateLinked | kCellStateContentModifiedAfterUpdate |
                                           kCellStateFormatLocked | kCellStateFormatReadOnly |
                                           kCellStateFormatModifiedAfterUpdate)
    </table>

    Method generates the eInvalidInput exception when the input row number and
    the column number are less than 0 or greater than the table size.
  */
  virtual OdResult setCellState(
    int nRow, 
    int nCol,
    OdDb::CellState nCellState);

  /** \details
    Returns the tooltip of the cell as an OdString value.

    \param nRow [in]  Row index.
    \param nCol [in]  Column index.
    \returns Tooltip of the cell.
  */
  virtual OdString getToolTip(
    int nRow,
    int nCol) const;

  /** \details
    Sets the tooltip of the cell.

    \param nRow     [in]  Row index of the cell.
    \param nCol     [in]  Column index of the cell.
    \param sToolTip [in]  Tooltip.
  */
  virtual OdResult setToolTip(
    int nRow,
    int nCol,
    const OdChar* sToolTip);

  /** \details
    Returns the custom data value of a cell, column or row as an OdInt32 value.
    Use a valid row index and pass the column index '-1' to get the row data.
    Use a valid column index and pass the row index '-1' to get the column data.

    \param nRow [in]  Row index.
    \param nCol [in]  Column index.
    \returns Custom data value.
  */
  virtual int getCustomData(
    int nRow,
    int nCol) const;

  /** \details
    Sets the custom data value of a cell, column or row.
    Use a valid row index and pass the column index '-1' to set the row data.
    Use a valid column index and pass the row index '-1' to set the column data.

    \param nRow  [in]  Row index of the cell.
    \param nCol  [in]  Column index of the cell.
    \param nData [in]  Custom data value.
  */
  virtual OdResult setCustomData(
    int nRow,
    int nCol,
    int nData);

  /** \details
    Returns the custom data value of a cell, column or row as an OdInt32 value.
    Use a valid row index and pass the column index '-1' to get the row data.
    Use a valid column index and pass the row index '-1' to get the column data.

    \param nRow [in]  Row index of the cell.
    \param nCol [in]  Column index of the cell.
    \param sKey [in]  Key to use for the custom data.
  */
  virtual OdValue getCustomData(
    OdInt32 nRow, 
    OdInt32 nCol, 
    const OdString& sKey ) const;

  virtual OdResult getCustomData(
    int nRow, 
    int nCol, 
    const OdChar* pszKey,
    OdValue* pValue) const;

  /** \details
    Sets the custom data value of a cell, column or row.
    Use a valid row index and pass the column index '-1' to get the row data.
    Use a valid column index and pass the row index '-1' to get the column data.

    \param nRow  [in]  Row index of the cell.
    \param nCol  [in]  Column index of the cell.
    \param sKey  [in]  Key to use for the custom data.
    \param pData [in]  Custom data value.
  */
  virtual OdResult setCustomData(
    int nRow, 
    int nCol, 
    const OdChar* sKey,
    const OdValue* pData);

  /** \details
    Returns the number of contents in the cell.

    \param nRow [in]  Row index of the cell.
    \param nCol [in]  Column index of the cell.
    \returns Number of contents.
    \remarks
    Method generates the eInvalidInput exception when the input row number and
    column number are less than 0 or greater than the table size.
  */
  virtual int numContents(
    int nRow, 
    int nCol) const;

  /** \details
    Creates additional content for the cell.

    \param nRow   [in]  Row index of the cell.
    \param nCol   [in]  Column index of the cell.
    \param nIndex [in]  Index at which the content will be created.
    \returns Index of the created content.
    \remarks
    Method generates the eInvalidInput exception when the input row number and
    column number are less than 0 or greater than the table size.
  */
  virtual int createContent(
    int nRow, 
    int nCol, 
    int nIndex);
  
  /** \details
    Moves content in a cell from one position to another.

    \param nRow       [in]  Row index of the cell.
    \param nCol       [in]  Column index of the cell.
    \param nFromIndex [in]  Index of the content to move.
    \param nToIndex   [in]  Target index of the content where it should be moved to.

    \remarks
    Method generates the eNotImplementedYet exception.
  */
  virtual OdResult moveContent(
    int nRow,
    int nCol,
    int nFromIndex,
    int nToIndex);

  /** \details
    Deletes content from a cell.

    \param nRow     [in]  Row index of the cell.
    \param nCol     [in]  Column index of the cell.
    \param nContent [in]  Index of the content.

    \remarks
    Method generates the eInvalidInput exception when the input row number and
    column number are less than 0 or greater than the table size.
    Method generates the eIsWriteProtected exception when the content is not
    editable (!isContentEditable()).
  */
  virtual OdResult deleteContent(
    int nRow, 
    int nCol, 
    int nContent);

  /** \details
    Deletes content from a cell.

    \param nRow [in]  Row index of the cell.
    \param nCol [in]  Column index of the cell.

    \remarks
    Method generates the eInvalidInput exception when the input row number and
    column number are less than 0 or greater than the table size.
    Method generates the eIsWriteProtected exception when the content is not
    editable (!isContentEditable()).
  */
  virtual OdResult deleteContent(
    int nRow, 
    int nCol);

  /** \details
    Deletes content from cells.

    \param range [in]  Range of cells.
  */
  virtual OdResult deleteContent(
    const OdCellRange& range);

  /** \details
    Returns content type of the first content of a cell.

    \param nRow [in]  Row index of the cell.
    \param nCol [in]  Column index of the cell.
    \returns Content type.
    \remarks
    Content type is an enumerator and takes one of the following values:

    <table>
    Name                      Value
    kCellContentTypeUnknown   0x0
    kCellContentTypeValue     0x1
    kCellContentTypeField     0x2
    kCellContentTypeBlock     0x4
    </table>
  */
  virtual OdDb::CellContentType contentType(
    int nRow, 
    int nCol) const;

  /** \details
    Returns content type of content at the specified index in a cell.

    \param nRow     [in]  Row index of the cell.
    \param nCol     [in]  Column index of the cell.
    \param nContent [in]  Index of content.
    \returns Content type.
    \remarks
    Content type is an enumerator and takes one of the following values:

    <table>
    Name                      Value
    kCellContentTypeUnknown   0x0
    kCellContentTypeValue     0x1
    kCellContentTypeField     0x2
    kCellContentTypeBlock     0x4
    </table>
  */
  virtual OdDb::CellContentType contentType(
    int nRow, 
    int nCol, 
    int nContent) const;

  /** \details
    Gets the data type of the first content of the specified cell.

    \param nRow       [in]  Row index of the cell.
    \param nCol       [in]  Column index of the cell.
    \param nDataType [out]  Reference to data type.
    \param nUnitType [out]  Reference to unit type.

    \remarks
    Data type should take one of the following values:

    <table>
    Name        Value
    kUnknown    0x00
    kLong       0x01
    kDouble     0x02
    kString     0x04
    kDate       0x08
    kPoint      0x10
    k3dPoint    0x20
    kObjectId   0x40
    kBuffer     0x80
    kResbuf     0x100
    kGeneral    0x200
    kColor      0x400
    </table>

    Unit type should take one of the following values:

    <table>
    Name          Value
    kUnitless     0x00
    kDistance     0x01
    kAngle        0x02
    kArea         0x04
    kVolume       0x08
    kCurrency     0x10
    kPercentage   0x20
    </table>

    Method generates the eInvalidInput exception when the input row number and
    column number are less than 0 or greater than the table size.
  */
  virtual OdResult getDataType(
    int nRow, 
    int nCol, 
    OdValue::DataType& nDataType, 
    OdValue::UnitType& nUnitType) const;

  /** \details
    Gets the data type of the content at the specified index in a cell.

    \param nRow       [in]  Row index of the cell.
    \param nCol       [in]  Column index of the cell.
    \param nContent   [in]  Content index.
    \param nDataType [out]  Reference to data type.
    \param nUnitType [out]  Reference to unit type.

    \remarks
    Data type should take one of the following values:

    <table>
    Name        Value
    kUnknown    0x00
    kLong       0x01
    kDouble     0x02
    kString     0x04
    kDate       0x08
    kPoint      0x10
    k3dPoint    0x20
    kObjectId   0x40
    kBuffer     0x80
    kResbuf     0x100
    kGeneral    0x200
    kColor      0x400
    </table>

    Unit type should take one of the following values:

    <table>
    Name          Value
    kUnitless     0x00
    kDistance     0x01
    kAngle        0x02
    kArea         0x04
    kVolume       0x08
    kCurrency     0x10
    kPercentage   0x20
    </table>

    Method generates the eInvalidInput exception when the input row number and
    column number are less than 0 or greater than the table size.
  */
  virtual OdResult getDataType(
    int nRow, 
    int nCol, 
    int nContent,
    OdValue::DataType& nDataType, 
    OdValue::UnitType& nUnitType) const;

  /** \details
    Sets the data type of the first content of a cell.

    \param nRow      [in]  Row index of the cell.
    \param nCol      [in]  Column index of the cell.
    \param nDataType [in]  Data type.
    \param nUnitType [in]  Unit type.

    \remarks
    Data type should take one of the following values:

    <table>
    Name        Value
    kUnknown    0x00
    kLong       0x01
    kDouble     0x02
    kString     0x04
    kDate       0x08
    kPoint      0x10
    k3dPoint    0x20
    kObjectId   0x40
    kBuffer     0x80
    kResbuf     0x100
    kGeneral    0x200
    kColor      0x400
    </table>

    \remarks
    Unit type should take one of the following values:

    <table>
    Name          Value
    kUnitless     0x00,
    kDistance     0x01,
    kAngle        0x02,
    kArea         0x04,
    kVolume       0x08,
    kCurrency     0x10,
    kPercentage   0x20
    </table>

    \remarks
    Method generates the eInvalidInput exception when the input row number and
    column number are less than 0 or greater than the table size.
    Method generates the eIsWriteProtected exception when the format is not
    editable (!isFormatEditable()).
  */
  virtual OdResult setDataType(
    int nRow, 
    int nCol, 
    OdValue::DataType nDataType, 
    OdValue::UnitType nUnitType);

  /** \details
    Sets the data type of the content at the specified index in a cell.

    \param nRow      [in]  Row index of the cell.
    \param nCol      [in]  Column index of the cell.
    \param nContent  [in]  Content index.
    \param nDataType [in]  Data type.
    \param nUnitType [in]  Unit type.

    \remarks
    Data type should take one of the following values:

    <table>
    Name        Value
    kUnknown    0x00
    kLong       0x01
    kDouble     0x02
    kString     0x04
    kDate       0x08
    kPoint      0x10
    k3dPoint    0x20
    kObjectId   0x40
    kBuffer     0x80
    kResbuf     0x100
    kGeneral    0x200
    kColor      0x400
    </table>

    Unit type should take one of the following values:

    <table>
    Name          Value
    kUnitless     0x00,
    kDistance     0x01,
    kAngle        0x02,
    kArea         0x04,
    kVolume       0x08,
    kCurrency     0x10,
    kPercentage   0x20
    </table>

    Method generates the eInvalidInput exception when the input row number and
    column number are less than 0 or greater than the table size.
    Method generates the eIsWriteProtected exception when the format is not
    editable (!isFormatEditable()).
  */
  virtual OdResult setDataType(
    int nRow, 
    int nCol, 
    int nContent,
    OdValue::DataType nDataType, 
    OdValue::UnitType nUnitType);

  /** \details
    Returns data format of the zero content of a cell as an OdString value.

    \param nRow [in]  Row index of the cell.
    \param nCol [in]  Column index of the cell.
    \returns Data format.
  */
  virtual OdString dataFormat(
    int nRow, 
    int nCol) const;

  /** \details
    Returns data format of the specified content of a cell as an OdString value.

    \param nRow     [in]  Row index of the cell.
    \param nCol     [in]  Column index of the cell.
    \param nContent [in]  Number of content.
  */
  virtual OdString dataFormat(
    int nRow, 
    int nCol,
    int nContent) const;

  /** \details
    Sets the data format of the zero content of a cell.

    \param nRow    [in]  Row index of the cell.
    \param nCol    [in]  Column index of the cell.
    \param sFormat [in]  Data format.

    \remarks
    Method generates the eInvalidInput exception when the input row number and
    column number are less than 0 or greater than the table size.
    Method generates the eIsWriteProtected exception when content is not
    editable (!isContentEditable()).
  */
  virtual OdResult setDataFormat(
    int nRow, 
    int nCol, 
    const OdChar* sFormat);

  /** \details
    Sets data format of the specified content of a cell.

    \param nRow     [in]  Row index of the cell.
    \param nCol     [in]  Column index of the cell.
    \param nContent [in]  Number of content.
    \param sFormat  [in]  Data format.

    \remarks
    Method generates the eInvalidInput exception when the input row number and
    column number are less than 0 or greater than the table size.
    Method generates the eIsWriteProtected exception when the content is not
    editable (!isContentEditable()).
  */
  virtual OdResult setDataFormat(
    int nRow, 
    int nCol, 
    int nContent,
    const OdChar* sFormat);

  /** \details
    Returns the value of the zero content of a cell.

    \param nRow [in]  Row index of the cell.
    \param nCol [in]  Column index of the cell.
    \returns Cell value.
  */
  virtual OdValue getValue(
    OdInt32 nRow, 
    OdInt32 nCol) const;

  /** \details
    Returns the value of the specified content of a cell.

    \param nRow     [in]  Row index of the cell.
    \param nCol     [in]  Column index of the cell.
    \param nContent [in]  Number of content.
    \param nOption  [in]  Format option of the value.

    \remarks
    Format option is an enumerator and takes one of the following values:

    <table>
    Name                   Value
    kFormatOptionNone      0x00
    kForEditing            0x01
    kForExpression         0x02
    kUseMaximumPrecision   0x04
    kIgnoreMtextFormat     0x08
    </table>
  */
  virtual OdValue getValue(
    OdInt32 nRow, 
    OdInt32 nCol, 
    OdUInt32 nContent, 
    OdValue::FormatOption nOption) const;

  virtual OdResult getValue(
    int nRow,
    int nCol,
    OdValue &value) const;

  virtual OdResult getValue(
    int nRow,
    int nCol,
    int nContent,
    OdValue::FormatOption nOption,
    OdValue &value) const;
  /** \details
    Sets a value to the zero content of a cell.
     
    \param nRow  [in]  Row index of the cell.
    \param nCol  [in]  Column index of the cell.
    \param value [in]  Value.

    \remarks
    Method generates the eInvalidInput exception when the input row number and
    column number are less than 0 or greater than the table size.
    Method generates the eIsWriteProtected exception when content is not
    editable (!isContentEditable()).
  */
  virtual OdResult setValue(
    int nRow, 
    int nCol, 
    const OdValue& value);

  /** \details
    Sets a value to the specified content of a cell.

    \param nRow     [in]  Row index of the cell.
    \param nCol     [in]  Column index of the cell.
    \param nContent [in]  Number of content.
    \param value    [in]  Value.

    \remarks
    Method generates the eInvalidInput exception when the input row number and
    column number are less than 0 or greater than the table size.
    Method generates the eIsWriteProtected exception when content is not
    editable (!isContentEditable()).
  */
  virtual OdResult setValue(
    int nRow, 
    int nCol, 
    int nContent, 
    const OdValue& value);

  /** \details
    Sets a value to the specified content of a cell.

    \param nRow     [in]  Row index of the cell.
    \param nCol     [in]  Column index of the cell.
    \param nContent [in]  Number of content.
    \param value    [in]  Value.
    \param nOption  [in]  Parse option of value.

    \remarks
    Parse option is an enumerator and takes one of the following values:

    <table>
    Name                     Value
    kParseOptionNone         0x00
    kSetDefaultFormat        0x01
    kPreserveMtextFormat     0x02
    kConvertTextToValue      0x04
    kChangeDataType          0x08
    kParseTextForFieldCode   0x10
    </table>

    Method generates the eInvalidInput exception when the input row number and
    column number are less than 0 or greater than the table size.
    Method generates the eIsWriteProtected exception when content is not
    editable (!isContentEditable()).
  */
  virtual OdResult setValue(
    int nRow, 
    int nCol, 
    int nContent, 
    const OdValue& value,
    OdValue::ParseOption nOption);

  /** \details
    Returns the text string from the zero content of a cell as an OdString value.

    \param nRow [in]  Row index of the cell.
    \param nCol [in]  Column index of the cell.
    \returns Content text string.
  */
  virtual OdString getText(
    int nRow, 
    int nCol) const;

  /** \details
    Returns the text string from the specified content of a cell as an OdString value.

    \param nRow     [in]  Row index of the cell.
    \param nCol     [in]  Column index of the cell.
    \param nContent [in]  Number of content.
    \returns Content text string.
  */
  virtual OdString getText(
    int nRow, 
    int nCol, 
    int nContent) const;

  /** \details
    Returns the text string from the specified content of a cell as an OdString value.

    \param nRow     [in]  Row index of the cell.
    \param nCol     [in]  Column index of the cell.
    \param nContent [in]  Number of content.
    \param nOption  [in]  Format option of the value.
    \returns Content text string.
    \remarks
    Format option is an enumerator and takes one of the following values:

    <table>
    Name                   Value
    kFormatOptionNone      0x00
    kForEditing            0x01
    kForExpression         0x02
    kUseMaximumPrecision   0x04
    kIgnoreMtextFormat     0x08
    </table>
  */
  virtual OdString getText(
    int nRow, 
    int nCol, 
    int nContent, 
    OdValue::FormatOption nOption) const;

  /** \details
    Sets a text string to a cell.

    \param nRow  [in]  Row index of the cell.
    \param nCol  [in]  Column index of the cell.
    \param sText [in]  Text string.

    \remarks
    Method generates the eInvalidInput exception when the input row number and
    column number are less than 0 or greater than the table size.
    Method generates the eIsWriteProtected exception when content is not
    editable (!isContentEditable()).
  */
  virtual OdResult setText(
    int nRow, 
    int nCol, 
    const OdChar *sText);

  /** \details
    Sets a text string to the specified content of a cell.

    \param nRow     [in]  Row index of the cell.
    \param nCol     [in]  Column index of the cell.
    \param nContent [in]  Number of content.
    \param sText    [in]  Text string.

    \remarks
    Method generates the eInvalidInput exception when the input row number and
    column number are less than 0 or greater than the table size.
    Method generates the eIsWriteProtected exception when content is not
    editable (!isContentEditable()).
  */
  virtual OdResult setText(
    int nRow, 
    int nCol, 
    int nContent, 
    const OdChar* sText);

  /** \details
    Checks if the cell has a formula in the specified content.

    \param nRow     [in]  Row index of the cell.
    \param nCol     [in]  Column index of the cell.
    \param nContent [in]  Number of content.
    \returns True if the cell has a formula in the specified content; false
             otherwise.
  */
  virtual bool hasFormula(
    int nRow, 
    int nCol, 
    int nContent) const;

  /** \details
    Returns the formula of the specified content of a cell as an object of the
    OdString class.

    \param nRow     [in]  Row index of the cell.
    \param nCol     [in]  Column index of the cell.
    \param nContent [in]  Number of content.
    \returns Formula string.
  */
  virtual OdString getFormula(
    int nRow, 
    int nCol, 
    int nContent) const;

  /** \details
    Sets the formula of the specified content of a cell.

    \param nRow     [in]  Row index of the cell.
    \param nCol     [in]  Column index of the cell.
    \param nContent [in]  Number of content.
    \param sFormula [in]  Formula.

    \remarks
    Method generates the eNotImplementedYet exception.
  */
  virtual OdResult setFormula(
    int nRow, 
    int nCol, 
    int nContent, 
    const OdChar* pszFormula);

  /** \details
    Returns the field ID of a cell as an object of the OdDbObjectId class.

    \param nRow [in]  Row index of the cell.
    \param nCol [in]  Column index of the cell.
    \returns Field ID of the cell.
  */
  virtual OdDbObjectId getFieldId(
    int nRow, 
    int nCol) const;

  /** \details
    Returns the field ID of the specified content of a cell as an object of the
    OdDbObjectId class.

    \param nRow     [in]  Row index of the cell.
    \param nCol     [in]  Column index of the cell.
    \param nContent [in]  Number of content.
    \returns Field ID of the cell.
  */
  virtual OdDbObjectId getFieldId(
    int nRow, 
    int nCol, 
    int nContent) const;

  /** \details
    Sets a field ID to the zero content of a cell.

    \param nRow    [in]  Row index of the cell.
    \param nCol    [in]  Column index of the cell.
    \param idField [in]  Field ID.

    \remarks
    Method generates the eInvalidInput exception when the input row number and
    column number are less than 0 or greater than the table size.
    Method generates the eIsWriteProtected exception when content is not
    editable (!isContentEditable()).
  */
  virtual OdResult setFieldId(
    int nRow, 
    int nCol, 
    const OdDbObjectId& idField);

  /** \details
    Sets a field ID to the specified content of a cell.

    \param nRow     [in]  Row index of the cell.
    \param nCol     [in]  Column index of the cell.
    \param nContent [in]  Number of content.
    \param idField  [in]  Field ID.

    \remarks
    Method generates the eInvalidInput exception when the input row number and
    column number are less than 0 or greater than the table size.
    Method generates the eIsWriteProtected exception when content is not
    editable (!isContentEditable()).
  */
  virtual OdResult setFieldId(
    int nRow, 
    int nCol, 
    int nContent, 
    const OdDbObjectId& idField);

  /** \details
    Returns the field of the specified content of a cell as an object pointer.

    \param nRow     [in]  Row index of the cell.
    \param nCol     [in]  Column index of the cell.
    \param nContent [in]  Number of content.
    \param mode     [in]  Open mode.
    \returns Cell content field as an object pointer.
    \remarks
    Open mode must take one of the following values:

    <table>
    Name         Value
    kNotOpen     -1
    kForRead     0
    kForWrite    1
    kForNotify   2
    </table>
  */
  virtual OdDbFieldPtr getField(
    OdInt32 nRow, 
    OdInt32 nCol, 
    OdUInt32 nContent,
    OdDb::OpenMode mode) const;

  virtual OdResult getField(
    int nRow,
    int nCol,
    int nContent,
    OdDbField*& pField,
    OdDb::OpenMode mode) const;

  /** \details
    Returns the ID of the block table record of the zero content of a cell as an
    object of the OdDbObjectId class.

    \param nRow [in]  Row index of the cell.
    \param nCol [in]  Column index of the cell.
    \returns ID of the block table record.
  */
  virtual OdDbObjectId getBlockTableRecordId(
    int nRow, 
    int nCol) const;

  /** \details
    Returns the ID of the block table record of the specified content of a cell
    as an object of the OdDbObjectId class.

    \param nRow     [in]  Row index of the cell.
    \param nCol     [in]  Column index of the cell.
    \param nContent [in]  Number of content.
    \returns ID of the block table record.
  */
  virtual OdDbObjectId getBlockTableRecordId(
    int nRow, 
    int nCol, 
    int nContent) const;

  /** \details
    Sets the ID of the block table record of the zero content of a cell as an
    object of the OdDbObjectId class.

    \param nRow  [in]  Row index of the cell.
    \param nCol  [in]  Column index of the cell.
    \param idBTR [in]  ID of the block table record.

    \remarks
    Method generates the eInvalidInput exception when the input row number and
    column number are less than 0 or greater than the table size.
    Method generates the eIsWriteProtected exception when content is not
    editable (!isContentEditable()).
  */
  virtual OdResult setBlockTableRecordId(
    int nRow, 
    int nCol, 
    const OdDbObjectId& idBTR);

  /** \details
    Sets the ID of the block table record of the specified content of a cell as
    an object of the OdDbObjectId class.

    \param nRow     [in]  Row index of the cell.
    \param nCol     [in]  Column index of the cell.
    \param nContent [in]  Number of content.
    \param idBTR    [in]  ID of the block table record.

    \remarks
    Method generates the eInvalidInput exception when the input row number and
    column number are less than 0 or greater than the table size.
    Method generates the eIsWriteProtected exception when content is not
    editable (!isContentEditable()).
  */
  virtual OdResult setBlockTableRecordId(
    int nRow, 
    int nCol, 
    int nContent, 
    const OdDbObjectId& idBTR);

  /** \details
    Returns the attribute value of the block cell using the specified object ID
    key as an OdString value.

    \param nRow     [in]  Row index of the cell.
    \param nCol     [in]  Column index of the cell.
    \param idAttDef [in]  Object ID.
    \returns Attribute value of the block cell.
    \remarks
    Method generates the eInvalidInput exception when the input row number and
    column number are less than 0 or greater than the table size.
  */
  virtual OdString getBlockAttributeValue(
    int nRow, 
    int nCol, 
    const OdDbObjectId& idAttDef) const;

  /** \details
    Returns the attribute value of the block cell using the specified object ID
    key as an OdString value.

    \param nRow     [in]  Row index of the cell.
    \param nCol     [in]  Column index of the cell.
    \param nContent [in]  Number of content.
    \param idAttDef [in]  Object id.
    \returns Attribute value of the block cell.
    \remarks
    Method generates the eInvalidInput exception when the input row number and
    column number are less than 0 or greater than the table size.
  */
  virtual OdString getBlockAttributeValue(
    int nRow, 
    int nCol, 
    int nContent, 
    const OdDbObjectId& idAttDef) const;

  /** \details
    Sets the attribute value of the block cell using the specified object ID key.

    \param nRow      [in]  Row index of the cell.
    \param nCol      [in]  Column index of the cell.
    \param idAttDef  [in]  Object ID.
    \param sAttValue [in]  Attribute value.

    \remarks
    Method generates the eInvalidInput exception when the input row number and
    column number are less than 0 or greater than the table size.
    Method generates the eIsWriteProtected exception when content is not
    editable (!isContentEditable()).
  */
  virtual OdResult setBlockAttributeValue(
    int nRow, 
    int nCol, 
    const OdDbObjectId& idAttDef, 
    const OdChar* sAttValue);

  /** \details
    Sets the attribute value of the block cell using the specified object ID key.

    \param nRow      [in]  Row index of the cell.
    \param nCol      [in]  Column index of the cell.
    \param nContent  [in]  Number of content.
    \param idAttDef  [in]  Object ID.
    \param sAttValue [in]  Attribute value.

    \remarks
    Method generates the eInvalidInput exception when the input row number and
    column number are less than 0 or greater than the table size.
    Method generates the eIsWriteProtected exception when content is not
    editable (!isContentEditable()).
  */
  virtual OdResult setBlockAttributeValue(
    int nRow, 
    int nCol, 
    int nContent, 
    const OdDbObjectId& idAttDef, 
    const OdChar* sAttValue);

  /** \details
    Checks if a cell is linked to a data source.

    \param nRow [in]  Row index of the cell.
    \param nCol [in]  Column index of the cell.
    \returns True if the cell is linked to a data source; false otherwise.
  */
  virtual bool isLinked(
    int nRow, 
    int nCol) const;

  /** \details
    Returns the data link  object ID (OdDbDataLink) for the specified row and column.

    \param nRow [in]  Row index of the cell.
    \param nCol [in]  Column index of the cell.
    \returns Data link  object ID.
  */
  virtual OdDbObjectId getDataLink(
    int nRow,
    int nCol) const;

  /** \details
    Opens and returns the data link (OdDbDataLink) for the specified row and column.

    \param nRow [in]  Row index of the cell.
    \param nCol [in]  Column index of the cell.
    \param mode [in]  Open mode.

    \remarks
    Open mode should take one of the following values:

    <table>
    Name         Value
    kNotOpen     -1
    kForRead     0
    kForWrite    1
    kForNotify   2
    </table>
  */
  virtual OdDbDataLinkPtr getDataLink(
    OdInt32 nRow, 
    OdInt32 nCol, 
    OdDb::OpenMode mode) const;

  virtual OdResult getDataLink(
    int nRow,
    int nCol,
    OdDbDataLink*& pDataLink,
    OdDb::OpenMode mode) const;

  /** \details
    Returns the number of data links (OdDbDataLink) for the specified cell range.

    \param pRange       [in]  Cell range.
    \param dataLinkIds [out]  Array of data link IDs.
    \returns Number of data links.
  */
  virtual OdInt32 getDataLink(
    const OdCellRange& pRange, 
    OdDbObjectIdArray& dataLinkIds) const;

  virtual int getDataLink(
    const OdCellRange* pRange,
    OdDbObjectIdArray& dataLinkIds) const;

  /** \details
    Sets the data link (OdDbDataLink) for the specified row and column.

    \param nRow       [in]  Row index of the cell.
    \param nCol       [in]  Column index of the cell.
    \param idDataLink [in]  Data lin object ID.
    \param bUpdate    [in]  Flag that indicates whether or not the data link
                            should be updated after setting.

    \remarks
    Method generates the eNotThatKindOfClass exception when idDataLink in not an
    OdDbDataLink object ID.
  */
  virtual OdResult setDataLink(
    int nRow,
    int nCol,
    const OdDbObjectId& idDataLink,
    bool bUpdate);

  /** \details
    Sets the data link object ID (OdDbDataLink) for the specified cell range.

    \param range      [in]  Cell range.
    \param idDataLink [in]  Data link object ID.
    \param bUpdate    [in]  Flag that indicates whether or not the data link
                            should be updated after setting.

    \remarks
    Method generates the eNotThatKindOfClass exception when idDataLink in not an
    OdDbDataLink object ID.
  */

  virtual OdResult setDataLink(
    const OdCellRange& range, 
    const OdDbObjectId& idDataLink,
    bool bUpdate);

  /** \details
    Returns the data link cell range that includes the specified row and column.

    \param nRow [in]  Row index of the cell.
    \param nCol [in]  Column index of the cell.
    \returns Cell range.
  */
  virtual OdCellRange getDataLinkRange(
    int nRow, 
    int nCol) const;

  /** \details
    Removes the data link at the specified cell.

    \param nRow [in]  Row index of the cell.
    \param nCol [in]  Column index of the cell.

    \remarks
    Method generates the eInvalidInput exception when the input row number and
    column number are less than 0 or greater than the table size.
  */
  virtual OdResult removeDataLink(
    int nRow, 
    int nCol);

  /** \details
    Removes all data links.
  */
  virtual OdResult removeDataLink(void);

  /** \details
    Updates the data link of a cell.

    \param nRow    [in]  Row index of the cell.
    \param nCol    [in]  Column index of the cell.
    \param nDir    [in]  Direction of update.
    \param nOption [in]  Update option.

    \remarks
    Direction of update should take one of the following values:

    <table>
    Name                           Value
    kUpdateDirectionSourceToData   0x1
    kUpdateDirectionDataToSource   0x2
    </table>

    Update option should take one of the following values:

    <table>
    Name                                               Value
    kUpdateOptionNone                                  0
    kUpdateOptionSkipFormat                            0x20000
    kUpdateOptionUpdateRowHeight                       0x40000
    kUpdateOptionUpdateColumnWidth                     0x80000
    kUpdateOptionAllowSourceUpdate                     0x100000
    kUpdateOptionForceFullSourceUpdate                 0x200000
    kUpdateOptionOverwriteContentModifiedAfterUpdate   0x400000
    kUpdateOptionOverwriteFormatModifiedAfterUpdate    0x800000
    kUpdateOptionForPreview                            0x1000000
    kUpdateOptionIncludeXrefs                          0x2000000
    kUpdateOptionSkipFormatAfterFirstUpdate            0x4000000
    </table>

    Method generates the eInvalidInput exception when the input row number and
    column number are less than 0 or greater than the table size.
  */
  virtual OdResult updateDataLink(
    int nRow,
    int nCol, 
    OdDb::UpdateDirection nDir,
    OdDb::UpdateOption nOption);

  /** \details
    Updates the data link in the table.

    \param nDir     [in]  Direction of update.
    \param nOption [out]  Update option.

    \remarks
    Direction of update should take one of the following values:

    <table>
    Name                           Value
    kUpdateDirectionSourceToData   0x1
    kUpdateDirectionDataToSource   0x2
    </table>

    Update option should take one of the following values:

    <table>
    Name                                               Value
    kUpdateOptionNone                                  0
    kUpdateOptionSkipFormat                            0x20000
    kUpdateOptionUpdateRowHeight                       0x40000
    kUpdateOptionUpdateColumnWidth                     0x80000
    kUpdateOptionAllowSourceUpdate                     0x100000
    kUpdateOptionForceFullSourceUpdate                 0x200000
    kUpdateOptionOverwriteContentModifiedAfterUpdate   0x400000
    kUpdateOptionOverwriteFormatModifiedAfterUpdate    0x800000
    kUpdateOptionForPreview                            0x1000000
    kUpdateOptionIncludeXrefs                          0x2000000
    kUpdateOptionSkipFormatAfterFirstUpdate            0x4000000
    </table>
  */
  virtual OdResult updateDataLink(
    OdDb::UpdateDirection nDir, 
    OdDb::UpdateOption nOption);

  /** \details
    Clears all data.
  */
  virtual OdResult clear();

  /** \details
    Copies the content from a source table to this table with specified option.

    \param pSource [in] Source table.
  */
  virtual OdResult copyFrom(
    const OdRxObject* pSource);

  /** \details
    Copies the content from a source table to this table.

    \param pSrc    [in]  Pointer to source table.
    \param nOption [in]  Copy option.

    \remarks
    Option should take one of the following values:

    <table>
    Name                                                  Value
    kTableCopyOptionNone                                  0
    kTableCopyOptionExpandOrContractTable                 0x1
    kTableCopyOptionSkipContent                           0x2
    kTableCopyOptionSkipValue                             0x4
    kTableCopyOptionSkipField                             0x8
    kTableCopyOptionSkipFormula                           0x10
    kTableCopyOptionSkipBlock                             0x20
    kTableCopyOptionSkipDataLink                          0x40
    kTableCopyOptionSkipLabelCell                         0x80
    kTableCopyOptionSkipDataCell                          0x100
    kTableCopyOptionSkipFormat                            0x200
    kTableCopyOptionSkipCellStyle                         0x400
    kTableCopyOptionConvertFormatToOverrides              0x800
    kTableCopyOptionSkipCellState                         0x1000
    kTableCopyOptionSkipContentFormat                     0x2000
    kTableCopyOptionSkipDissimilarContentFormat           0x4000
    kTableCopyOptionSkipGeometry                          0x8000
    kTableCopyOptionSkipMerges                            0x10000
    kTableCopyOptionFillTarget                            0x20000
    kTableCopyOptionOverwriteReadOnlyContent              0x40000
    kTableCopyOptionOverwriteContentModifiedAfterUpdate   0x100000
    kTableCopyOptionOverwriteFormatModifiedAfterUpdate    0x200000
    kTableCopyOptionOnlyContentModifiedAfterUpdate        0x400000
    kTableCopyOptionOnlyFormatModifiedAfterUpdate         0x800000
    kTableCopyOptionRowHeight                             0x1000000
    kTableCopyOptionColumnWidth                           0x2000000
    kTableCopyOptionFullCellState                         0x4000000
    kTableCopyOptionForRountrip                           0x8000000
    kTableCopyOptionConvertFieldToValue                   0x10000000
    kTableCopyOptionSkipFieldTranslation                  0x20000000
    </table>
  */
  virtual OdResult copyFrom(const OdDbLinkedTableData* pSrc,
    OdDb::TableCopyOption nOption);

  /** \details
    Copies the content from a source table to this table.

    \param pSrc             [in]  Pointer to source table.
    \param nOption          [in]  Copy option.
    \param srcRange         [in]  Source cell range.
    \param targetRange      [in]  Target cell range.
    \param pNewTargetRange [out]  New target cell range.

    \remarks
    Option should take one of the following values:

    <table>
    Name                                                  Value
    kTableCopyOptionNone                                  0
    kTableCopyOptionExpandOrContractTable                 0x1
    kTableCopyOptionSkipContent                           0x2
    kTableCopyOptionSkipValue                             0x4
    kTableCopyOptionSkipField                             0x8
    kTableCopyOptionSkipFormula                           0x10
    kTableCopyOptionSkipBlock                             0x20
    kTableCopyOptionSkipDataLink                          0x40
    kTableCopyOptionSkipLabelCell                         0x80
    kTableCopyOptionSkipDataCell                          0x100
    kTableCopyOptionSkipFormat                            0x200
    kTableCopyOptionSkipCellStyle                         0x400
    kTableCopyOptionConvertFormatToOverrides              0x800
    kTableCopyOptionSkipCellState                         0x1000
    kTableCopyOptionSkipContentFormat                     0x2000
    kTableCopyOptionSkipDissimilarContentFormat           0x4000
    kTableCopyOptionSkipGeometry                          0x8000
    kTableCopyOptionSkipMerges                            0x10000
    kTableCopyOptionFillTarget                            0x20000
    kTableCopyOptionOverwriteReadOnlyContent              0x40000
    kTableCopyOptionOverwriteContentModifiedAfterUpdate   0x100000
    kTableCopyOptionOverwriteFormatModifiedAfterUpdate    0x200000
    kTableCopyOptionOnlyContentModifiedAfterUpdate        0x400000
    kTableCopyOptionOnlyFormatModifiedAfterUpdate         0x800000
    kTableCopyOptionRowHeight                             0x1000000
    kTableCopyOptionColumnWidth                           0x2000000
    kTableCopyOptionFullCellState                         0x4000000
    kTableCopyOptionForRountrip                           0x8000000
    kTableCopyOptionConvertFieldToValue                   0x10000000
    kTableCopyOptionSkipFieldTranslation                  0x20000000
    </table>
  */
  virtual OdResult copyFrom(const OdDbLinkedTableData* pSrc,
    OdDb::TableCopyOption nOption, 
    const OdCellRange& srcRange, 
    const OdCellRange& targetRange,
    OdCellRange* pNewTargetRange);

  /** \details
    Returns the table iterator.
  */
  OdDbTableIteratorPtr getIterator(void) const;

  /** \details
    Returns the table iterator for the specified range.

    \param pRange  [in]  Pointer to the input range for iteration.
    \param nOption [in]  Iteration option.

    \remarks
    Option should take one of the following values:

    <table>
    Name                                Value
    kTableIteratorNone                  0
    kTableIteratorIterateSelection      0x1
    kTableIteratorIterateRows           0x2
    kTableIteratorIterateColumns        0x4
    kTableIteratorIterateDataLinks      0x80
    kTableIteratorReverseOrder          0x8
    kTableIteratorSkipReadOnlyContent   0x10
    kTableIteratorSkipReadOnlyFormat    0x20
    kTableIteratorSkipMerged            0x40
    </table>
  */
  OdDbTableIteratorPtr getIterator(const OdCellRange* pRange,
    OdDb::TableIteratorOption nOption) const;

  /** \details
    OdDbObject override.
  */
  virtual OdResult dwgInFields(
    OdDbDwgFiler* pFiler);

  /** \details
    OdDbObject override.
  */
  virtual OdResult dwgOutFields(
    OdDbDwgFiler* pFiler) const;

  /** \details
    OdDbObject override.
  */
  virtual OdResult dxfInFields(
    OdDbDxfFiler* pFiler);

  /** \details
    OdDbObject override.
  */
  virtual OdResult dxfOutFields(
    OdDbDxfFiler* pFiler) const;

  virtual OdResult evaluateFormula();
};

/** \details
  This template class is a specialization of the OdSmartPtr class for smart
  pointers to objects of the OdDbLinkedTableData class.
*/
typedef OdSmartPtr<OdDbLinkedTableData> OdDbLinkedTableDataPtr;

#include "TD_PackPop.h"

#endif // OD_DBLINKEDTABLEDATA_H
