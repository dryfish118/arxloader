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


#ifndef __OD_DB_UNDERLAY_HOST__
#define __OD_DB_UNDERLAY_HOST__

#include "TD_PackPush.h"

#include "Gi/GiRasterImage.h"
#include "DbDatabase.h"
#include "DbEntity.h"

#include "DbUnderlayItem.h" // classes OdUnderlayLayer, OdDbUnderlayDrawContext & OdDbUnderlayItem were moved

class OdDbUnderlayDefinition;

typedef bool(*GetPasswordFunPtr)(const OdString& path, bool bUser, OdString& password);
/** Description:

    Set a callback function to show a password input dialog for pdf documents loading.
    If pFun is NULL or do not call this function, it will show the default password input dialog in AppServices which is mostly used for DWG documents.
*/
extern "C" __declspec(dllexport) void odSetPdfCallBackGetPasswordFun(GetPasswordFunPtr pFun);

/** Description:

    Set a callback function to show a password input dialog for dwf documents loading.
    If pFun is NULL or do not call this function, it will show the default password input dialog in AppServices which is mostly used for DWG documents.
*/
extern "C" __declspec(dllexport) void odSetDwfCallBackGetPasswordFun(GetPasswordFunPtr pFun);

/** \details

    <group OdDb_Classes>
*/
class UNDERLAY_EXPORT OdDbUnderlayFile : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdDbUnderlayFile);

  virtual int getItemCount() const = 0;
  virtual OdDbUnderlayItemPtr getItem(int i) const;
  virtual OdDbUnderlayItemPtr getItem(OdString name) const;
  virtual OdResult getItem(int i, OdDbUnderlayItem*& pItem) const = 0;
  virtual OdResult getItem(const OdChar* name, OdDbUnderlayItem*& pItem) const = 0;
};

typedef OdSmartPtr<OdDbUnderlayFile> OdDbUnderlayFilePtr;

// Instance of this PE should be registered for each OdDbUnderlayDefinition inheritant


/** \details

    <group OdDb_Classes>
*/
class UNDERLAY_EXPORT OdDbUnderlayHostPE : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdDbUnderlayHostPE);

  OdDbUnderlayHostPE();

  virtual OdResult load(OdString path, OdString password, OdDbUnderlayFilePtr& result) = 0;
  virtual OdResult getFile(const OdChar* fullPath, const wchar_t* password, OdDbUnderlayFile*& pFile) const = 0;
};

typedef OdSmartPtr<OdDbUnderlayHostPE> OdDbUnderlayHostPEPtr;
class IGcReadStream;
class UNDERLAY_EXPORT OdDbUnderlayHost
{
public:
	OdDbUnderlayHost();
     virtual OdResult getFile(
                                const OdChar* fullPath, 
                                const wchar_t* password, 
                                OdDbUnderlayFile*& pFile) const = 0;
    virtual OdResult getFile(
                                IGcReadStream* pFileStream,
                                const wchar_t* password, 
                                OdDbUnderlayFile*& pFile) const = 0;

   static void getAdjustedColor(
                               OdGeVector3d& rgbResult, 
                               const OdGeVector3d& rgbInputColor, 
                               const OdGeVector3d& rgbCurrentBackgroundColor, 
                               const OdGeVector3d& hslFadedContrastColor,
                               const OdDbUnderlayDrawContext& drawContext);
protected:
    ///<summary>Destructor.</summary>
    virtual ~OdDbUnderlayHost() = 0;
};

UNDERLAY_EXPORT void oddbConvertRgbToHsl(const OdGeVector3d& rgb, OdGeVector3d& hsl);
UNDERLAY_EXPORT void oddbConvertHslToRgb(const OdGeVector3d& hsl, OdGeVector3d& rgb);
UNDERLAY_EXPORT void oddbUnderlayHostGetAdjustedColor(OdGeVector3d& rgbResult,
                                                     const OdGeVector3d& rgbInputColor,
                                                     const OdGeVector3d& rgbCurrentBackgroundColor,
                                                     const OdGeVector3d& hslFadedContrastColor,
                                                     const OdDbUnderlayDrawContext& drawContext);

// DGNUnderlay extensions
#include "DbDgnUnderlayHost.h"

UNDERLAY_EXPORT OdDbUnderlayHost* oddbGetCurrentDwfHost();
UNDERLAY_EXPORT OdDbUnderlayHost* oddbSetCurrentDwfHost(OdDbUnderlayHost* pHost);

//UNDERLAY_EXPORT OdDbUnderlayHost* oddbGetCurrentPdfHost();
//UNDERLAY_EXPORT OdDbUnderlayHost* oddbSetCurrentPdfHost(OdDbUnderlayHost* pHost);

UNDERLAY_EXPORT OdDbUnderlayHost* oddbGetCurrentDgnHost();
UNDERLAY_EXPORT OdDbUnderlayHost* oddbSetCurrentDgnHost(OdDbUnderlayHost* pHost);

#include "TD_PackPop.h"

#endif // __OD_DB_UNDERLAY_HOST__
