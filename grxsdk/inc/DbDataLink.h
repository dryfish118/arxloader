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



#ifndef OD_DBDATALINK_H
#define OD_DBDATALINK_H

#include "DbObject.h"
#include "OdValue.h"
#include "StringArray.h"

#include "TD_PackPush.h"

/** \details
    This class links a table to data in another file.

    
    <group OdDb_Classes> 

*/
class DBENT_EXPORT OdDbDataLink : public OdDbObject
{
public:
  ODDB_DECLARE_MEMBERS(OdDbDataLink);

  OdDbDataLink(void);
  
  OdString name (void) const;
  OdResult setName (const OdString& sName);
  OdString description (void) const;
  OdResult setDescription (const OdString& sDescription);
  OdString getToolTip (void) const;
  OdResult setToolTip (const OdString& sToolTip);
  OdString  dataAdapterId (void) const;
  OdResult setDataAdapterId (const OdString& sAdapterId);
  OdString  connectionString (void) const;
  OdResult setConnectionString(const OdString& sConnectionString);
  OdDb::DataLinkOption option (void) const;
  OdResult setOption (OdDb::DataLinkOption nOption);
  OdInt32 updateOption (void) const;
  OdResult setUpdateOption(OdInt32 nOption);
  OdResult update (OdDb::UpdateDirection nDir, OdDb::UpdateOption nOption);
  OdResult getUpdateStatus(OdDb::UpdateDirection* pDir, OdTimeStamp* pTime, OdString* pErrMessage) const;
  TOOLKIT_EXPORT OdResult getUpdateStatus(OdDb::UpdateDirection* pDir, std::tm* pTime, OdString* pErrMessage) const;
  OdResult setUpdateStatus(const OdString& sErrMessage);
  bool isValid (void) const;
  OdInt32 getTargets (OdDbObjectIdArray& targetIds) const;
  OdResult getSourceFiles(OdDb::DataLinkGetSourceContext nContext, OdStringArray& files) const;
  OdResult repathSourceFiles(const wchar_t* pszBasePath, OdDb::PathOption nOption);
  OdDbObjectId contentId() const;
  OdValue getCustomData(const OdString& sKey) const;
  TOOLKIT_EXPORT OdResult getCustomData(const OdChar* pszKey, OdValue* pData) const;
  OdResult setCustomData(const OdString& sKey, const OdValue* pData);
  OdDbObjectPtr subWblockClone(OdDbIdMapping& idMap, OdDbObject* owner, bool bPrimary) const;

  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler);
  virtual OdResult dwgOutFields(OdDbDwgFiler* pFiler) const;
  virtual OdResult dxfInFields(OdDbDxfFiler* pFiler);
  virtual OdResult dxfOutFields(OdDbDxfFiler* pFiler) const;
};

typedef OdArray<OdDbDataLink*> OdDbDataLinkArray;

typedef OdSmartPtr<OdDbDataLink> OdDbDataLinkPtr;


//*************************************************************************
// OdDbDataLinkManager
//*************************************************************************
class OdDbDataLinkManagerImpl;

/** \details
    <group OdDb_Classes> 
*/
class DBENT_EXPORT OdDbDataLinkManager : public OdStaticRxObject<OdRxObject>
{
public:
  ODRX_HEAP_OPERATORS();

  ODRX_DECLARE_MEMBERS(OdDbDataLinkManager);
  
  OdDbDataLinkManager(void);
  ~OdDbDataLinkManager(void);
  OdDbObjectId createDataLink(const OdString& adapterId, const OdString& name,
    const OdString& description, const OdString& connectionString);

  TOOLKIT_EXPORT OdResult createDataLink(const OdChar* pszAdapterId,
                                    const OdChar* pszName,
                                    const OdChar* pszDescription,
                                    const OdChar* pszConnectionString,
                                    OdDbObjectId& idDataLink);

  OdResult getDataLink(const OdChar* pszName,OdDbObjectId& idDataLink) const;
  OdDbDataLinkPtr getDataLink(const OdString& name, OdDb::OpenMode mode) const;
  TOOLKIT_EXPORT OdResult getDataLink(const OdChar* pszName, OdDbDataLink*& pDataLink, OdDb::OpenMode mode) const;

  int   dataLinkCount(void) const;

  int   getDataLink(OdDbObjectIdArray& dataLinks) const;

  TOOLKIT_EXPORT OdResult addDataLink(OdDbDataLink* pDataLink);
  OdResult addDataLink(OdDbDataLink* pDataLink, OdDbObjectId& idDataLink);

  OdResult removeDataLink(const OdString& sKey, OdDbObjectId& idDataLink);

  OdResult removeDataLink(const OdDbObjectId& idDataLink);

  OdResult update(const OdDbObjectIdArray& dataIds, OdDb::UpdateDirection nDir, OdDb::UpdateOption nOption);
  OdResult update(OdDb::UpdateDirection nDir, OdDb::UpdateOption nOption);

  void setDatabase(OdDbDatabase* pDb);
protected:
  OdDbDataLinkManager(OdDbDataLinkManagerImpl* pValImpl);
  OdDbDataLinkManagerImpl* m_pImpl;
  friend class OdDbSystemInternals;
};

typedef OdSmartPtr<OdDbDataLinkManager> OdDbDataLinkManagerPtr;

/** \details
    <group OdDb_Classes> 
*/
class DBDIM_EXPORT OdDbDataLinkUpdatePE : public OdRxObject
{
public:
  virtual OdError dataLinkUpdate(OdDbDataLink* pDataLink, OdDb::UpdateDirection nDir, OdDb::UpdateOption nOption) = 0;
  virtual OdError repathSourceFiles(const wchar_t* pszBasePath, OdDb::PathOption nOptionm, OdString& path) = 0;

  ODRX_DECLARE_MEMBERS(OdDbDataLinkUpdatePE);
};

typedef OdSmartPtr<OdDbDataLinkUpdatePE> OdDbDataLinkUpdatePEPtr;

#include "TD_PackPop.h"

#endif // OD_DBDATALINK_H
