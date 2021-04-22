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




#ifndef _SUMMINFO_H_
#define _SUMMINFO_H_

#include "RxObject.h"
#include "DbDatabase.h"
#include "DbLibraryInfo.h"

#include "TD_PackPush.h"

/** \details
    This class encapsulates a set of character strings containing 
    additional information for an OdDbDatabase as Summary Information.

    \remarks
    In addition to the predefined fields, you add create any number of custom fields to the Summary Information.
    Corresponding C++ library: TD_Db
    <group OdDb_Classes>
*/
class TOOLKIT_EXPORT OdDbDatabaseSummaryInfo : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdDbDatabaseSummaryInfo);

  OdDbDatabaseSummaryInfo();
  
  /** \details
    Returns the value of the Title field of the Summary Information.
  */
  virtual OdResult getTitle(OdChar*& title) const = 0;

  /** \details
    Sets the value of the Title field of the Summary Information.
    \param title [in]  Title.
  */
  virtual OdResult setTitle(const OdChar* title) = 0;
  
  /** \details
    Returns the value of the Subject field of the Summary Information.
  */
  virtual OdResult getSubject(OdChar*& subject) const = 0;

  /** \details
    Sets the value of the Subject field of the Summary Information.
    \param subject [in]  Subject.
  */
  virtual OdResult setSubject(const OdChar* subject) = 0;
  
  /** \details
    Returns the value of the Author field of the Summary Information.
  */
  virtual OdResult getAuthor(OdChar*& author) const = 0;

  /** \details
    Sets the value of the Author field of the Summary Information.
    \param author [in]  Author.
  */
  virtual OdResult setAuthor(const OdChar* author) = 0;

  /** \details
    Returns the value of the Keywords field of the Summary Information.
    
    \remarks
    Keywords are delimited by spaces.
  */
  virtual OdResult getKeywords(OdChar*& keywordlist) const = 0;

  /** \details
    Sets the value of the Keywords field of the Summary Information.
    \param keywords [in]  Keywords.
    \remarks
    Keywords are delimited by spaces.
  */
  virtual OdResult setKeywords(const OdChar* keywords) = 0;

  /** \details
    Returns the value of the Comments field of the Summary Information.
  */
  virtual OdResult getComments(OdChar*& comments) const = 0;

  /** \details
    Sets the value of the Comments field of the Summary Information.
    \param comments [in]  Comments.
  */
  virtual OdResult setComments(const OdChar* comments) = 0;


  /** \details
    Returns the value of the LastSavedBy field of the Summary Information.
  */
  virtual OdResult getLastSavedBy(OdChar*& lastSavedBy) const = 0;

  /** \details
    Sets the value of the LastSavedBy field of the Summary Information.
    \param lastSavedBy [in]  Last Saved By.
  */
  virtual OdResult setLastSavedBy(const OdChar* lastSavedBy) = 0;

  /** \details
    Returns the value of the RevisionNumber field of the Summary Information.
    
    \remarks
    The RevisionNumber field is returned as a string.
  */
  virtual OdResult getRevisionNumber(OdChar*& revisionNumber) const = 0;

  /** \details
    Sets the value of the RevisionNumber field of the Summary Information.
    \param revisionNumber [in]  Revision number.
    \remarks
    The RevisionNumber field is set as a string.
  */
  virtual OdResult setRevisionNumber(const OdChar* revisionNumber) = 0;
    
  /** \details
    Returns the value of the HyperlinkBase field of the Summary Information.
  */
  virtual OdResult getHyperlinkBase(OdChar*& HyperlinkBase) const = 0;

  /** \details
    Sets the value of the HyperlinkBase field of the Summary Information.
    \param hyperlinkBase [in]  HyperlinkBase.
  */
  virtual OdResult setHyperlinkBase(const OdChar* hyperlinkBase) = 0;
  /** Description:
    Returns the number of custom fields in the Summary Information  
  */
  virtual int numCustomInfo() const = 0;
  
  /** \details
    Appends a custom field to the Summary Information.
    \param key [in]  Name of the custom field.
    \param value [in]  Value of the custom field.
  */
  virtual OdResult addCustomSummaryInfo(const OdChar* key, const OdChar* value) = 0;
  
  /** \details
    Deletes the specified custom field from the Summary Information.
    \param fieldIndex [in]  Field index [1..numCustomInfo()].
  */
  virtual OdResult deleteCustomSummaryInfo(int fieldIndex) = 0;
  
  /** \details
    Deletes the specified custom field from the Summary Information.
    \param key [in]  Name of the field.
  */
  virtual OdResult deleteCustomSummaryInfo(const OdChar* key) = 0;

    
  /** \details
    Returns the value of the specified custom field of the Summary Information.
    \param fieldIndex [in]  Field index [1..numCustomInfo()].
    \param key [out]  Receives the name.
    \param rvalue [out]  Receives the value.
  */
  virtual OdResult getCustomSummaryInfo(int fieldIndex, OdChar*& key,
										OdChar *& value ) const = 0;

  /** \details
    Sets the value of the specified custom field of the Summary Information.
    \param fieldIndex [in]  Field index [1..numCustomInfo()].
    \param key [in]  Name of the field.
    \param value [in]  Value for the field.
  */
  virtual OdResult setCustomSummaryInfo(int fieldIndex, const OdChar* key,
										const OdChar *value ) = 0;
  
  /** \details
    Returns the value of the specified custom field of the Summary Information.
    \param customInfoKey [in]  Name of the field to retrieve.
    \param rvalue [out]  Receives the value.
  */
  virtual OdResult getCustomSummaryInfo(const OdChar *customInfoKey,
										OdChar *& value ) const = 0;
  
  /** \details
    Sets the value of the specified custom field of the Summary Information.
    \param customInfoKey [in]  Name of the field to set.
    \param value [in]  Value for the field.
  */
  virtual OdResult setCustomSummaryInfo(const OdChar *customInfoKey,
										const OdChar *value ) = 0;
  
  /** \details
    Returns the OdDbDatabase associated with this Summary Information.
  */
  virtual OdDbDatabase* database() const = 0; 
  
  /** \details
    Sets the OdDbDatabase associated with this Summary Information.
    \param pDb [in]  Pointer to the database.
  */
  virtual void setDatabase(OdDbDatabase *pDb) = 0;

  virtual ~OdDbDatabaseSummaryInfo() {};
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdDbDatabaseSummaryInfo object pointers.
*/
typedef OdSmartPtr<OdDbDatabaseSummaryInfo> OdDbDatabaseSummaryInfoPtr;


TOOLKIT_EXPORT OdDbLibraryInfo*           oddbGetLibraryInfo(void);
TOOLKIT_EXPORT OdDbDatabaseSummaryInfoPtr oddbGetSummaryInfo(OdDbDatabase* pDb);

TOOLKIT_EXPORT OdResult oddbGetSummaryInfo(OdDbDatabase* pDb, OdDbDatabaseSummaryInfo*& pInfo);

TOOLKIT_EXPORT OdResult oddbPutSummaryInfo(const OdDbDatabaseSummaryInfo* pInfo, OdDbDatabase *pDb);

#define INVALID_CHARACTERS           OD_T("<>/\\\":;?*|,=`")

TOOLKIT_EXPORT OdResult oddbValidateCustomSummaryInfoKey(const OdChar* key, const OdDbDatabaseSummaryInfo* pInfo = NULL);

inline OdResult oddbPutSummaryInfo(const OdDbDatabaseSummaryInfo* pInfo)
{
  return ::oddbPutSummaryInfo(pInfo, pInfo->database());
}

class TOOLKIT_EXPORT OdDbSummaryInfoReactor
{
public:
    virtual void summaryInfoHasChanged(const OdDbDatabase*, const OdDbDatabaseSummaryInfo*) {};
    virtual ~OdDbSummaryInfoReactor() {};
};

class TOOLKIT_EXPORT OdDbSummaryInfoManager
{
public:
    virtual void  addReactor(OdDbSummaryInfoReactor* pReact) = 0;
    virtual void  removeReactor(OdDbSummaryInfoReactor* pReact) = 0;
};

// Stand-alone function to return the manager
//
TOOLKIT_EXPORT OdDbSummaryInfoManager* oddbSummaryInfoManager();

// Obsolete methods.  These will be removed in
// a future release.
//
inline void initOdDbSummaryInfoManager() {};
inline void deleteOdDbSummaryInfoManager() {};
#include "TD_PackPop.h"

#endif // _SUMMINFO_H_
