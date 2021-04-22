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




#ifndef _OD_DB_ATTRDEF_
#define _OD_DB_ATTRDEF_

#include "TD_PackPush.h"

#include "DbText.h"
#include "DbMText.h"
#include "DwgDeclareMembers.h"

/** \details
    This class represents attribute definition (Attdef) entities in an OdDbDatabase instance.
  

    <group OdDb_Classes>
*/
class DBENT_EXPORT OdDbAttributeDefinition : public OdDbText
{
public:

  DWGMAP_DECLARE_MEMBERS(OdDbAttributeDefinition);
  OdDbAttributeDefinition();
  OdDbAttributeDefinition(
    const OdGePoint3d& position,
    const OdChar *     text,
    const OdChar *     tag,
    const OdChar *     prompt,
    OdDbObjectId       style = OdDbObjectId::kNull);

  /** \details
    Returns the prompt string of this Attdef entity (DXF 3).
  */
  const OdString prompt(ODSYSDEF) const;
  OdChar*  prompt() const;

  /** Gcad(Add):增加兼容接口
  */
  const OdChar* promptConst() const;

  /** \details
    Sets the prompt string of this Attdef entity (DXF 3).
    \param promptString [in]  Prompt string
  */
  OdResult setPrompt(
    const OdString& promptString);

  /** \details
    Returns the tag string of this Attdef entity (DXF 2).
  */
  const OdString tag(ODSYSDEF) const;
  OdChar*  tag() const;

  /** Gcad(Add):增加兼容接口
  */
  const OdChar* tagConst() const;

  /** \details
    Sets the tag string of this Attdef entity (DXF 2).
    \param tagString [in]  Tag string.  
  */
  OdResult setTag(
    const OdString& tagString);

  /** \details
    Returns true if and only if this Attdef entity is invisible (DXF 70, bit 0x01).
  */
  bool isInvisible() const;

  /** \details
    Controls the invisibility of this Attdef entity (DXF 70, bit 0x01).

    \param invisible [in]  Controls invisibility.
  */
  OdResult setInvisible(
    bool invisible);

  /** \details
    Returns true if and only if this Attdef entity is constant (DXF 70, bit 0x02).
  */
  virtual bool isConstant() const;

  /** \details
    Controls the constant status of this Attdef entity (DXF 70, bit 0x02).
    \param constant [in]  Controls constant status.
  */
  OdResult setConstant(bool constant);

  /** \details
    Returns true if and only if this Attdef entity is verifiable (DXF 70, bit 0x04).
  */
  bool isVerifiable() const;

  /** \details
    Controls the verifiable status of this Attdef entity (DXF 70, bit 0x04).
    \param verifiable [in]  Controls verifiable status.
  */
  OdResult setVerifiable(bool);

  /** \details
    Returns true if and only if this Attdef entity is preset (DXF 70, bit 0x08).
  */
  bool isPreset() const;

  /** \details
    Controls the preset status of this Attdef entity (DXF 70, bit 0x08).
    \param preset [in]  Controls preset status.
  */
  OdResult setPreset(bool);

  /** \details
    Returns the field length of this Attdef entity (DXF 73).
  */
  OdUInt16 fieldLength() const;

  /** \details
    Sets the field length of this Attdef entity (DXF 73).
    \param fieldLength [in]  Field length.
  */
  OdResult setFieldLength(OdUInt16 fieldLength);

  virtual OdResult subGetClassID(
    CLSID* pClsid) const;

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

  OdBool subWorldDraw(
    OdGiWorldDraw* pWd);
  void subViewportDraw(
    OdGiViewportDraw* pVd);
  OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits);

  void appendToOwner(
    OdDbIdPair& Idpair, 
    OdDbObject* pOwnerObject, 
    OdDbIdMapping& ownerIdMap);

  bool lockPositionInBlock() const;
  OdResult setLockPositionInBlock(bool bValue);
  // multiline attribute definition support
  bool isMTextAttributeDefinition() const;
  OdDbMText* getMTextAttributeDefinition() const;
  const OdDbMText* getMTextAttributeDefinitionConst() const;
  OdResult setMTextAttributeDefinition(OdDbMText*);
  TOOLKIT_EXPORT OdResult setMTextAttributeDefinitionConst(const OdDbMText*);
  OdResult convertIntoMTextAttributeDefinition (bool val = true);
  OdResult updateMTextAttributeDefinition();
  virtual OdResult subClose() ODRX_OVERRIDE;
};
/** \details
  This template class is a specialization of the OdSmartPtr class for OdDbAttributeDefinition object pointers.
*/
typedef OdSmartPtr<OdDbAttributeDefinition> OdDbAttributeDefinitionPtr;

#include "TD_PackPop.h"

#endif

