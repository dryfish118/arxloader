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


#ifndef _OD_DBSUN_H_INCLUDED_
#define _OD_DBSUN_H_INCLUDED_

#include "TD_PackPush.h"

#include "Gi/GiLightTraits.h"
#include "DbLight.h"
#include "RxDictionary.h"

class SCENEOE_EXPORT OdDbSun;
typedef OdSmartPtr<OdDbSun> OdDbSunPtr;


/** \details
    Corresponding C++ library: SCENEOE

    <group OdDb_Classes>
*/
class SCENEOE_EXPORT OdDbSun : public OdDbObject
{
public:
  ODDB_DECLARE_MEMBERS(OdDbSun);

  OdDbSun();

  virtual DrawableType drawableType() const;
  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits);

  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler);
  virtual OdResult dwgOutFields(OdDbDwgFiler* pFiler) const;
  virtual OdResult dxfInFields(OdDbDxfFiler* pFiler);
  virtual OdResult dxfOutFields(OdDbDxfFiler* pFiler) const;

  virtual OdResult decomposeForSave(
    OdDb::DwgVersion ver,
    OdDbObject*& replaceObj,
    OdDbObjectId& replaceId,
    OdBool& exchangeXData);
  
  OdGiDrawable* drawable();

  virtual bool isOn() const;


  virtual OdResult setOn(bool value);


  virtual double intensity() const;


  virtual OdResult setIntensity(double intensity);

 
  virtual const OdCmColor& sunColor() const;


  virtual OdResult setSunColor(const OdCmColor& color);

  virtual const OdGiColorRGB& sunColorPhotometric(const double multiplier);

  virtual const OdGiShadowParameters& shadowParameters() const;


  virtual void setShadowParameters(const OdGiShadowParameters& params);


  virtual OdResult setDateTime(const OdDbDate& datetime);


  virtual const OdDbDate& dateTime() const;


  virtual OdResult setDayLightSavingsOn(bool value);


  virtual bool isDayLightSavingsOn() const;


  virtual OdResult setAzimuth(double azimuth);


  virtual double azimuth() const;


  virtual OdResult setAltitude(double altitude);


  virtual double altitude() const;


  virtual const OdGeVector3d& sunDirection() const;


  virtual void setSunDirection(const OdGeVector3d& sundir);


  OdResult setSkyParameters(const OdGiSkyParameters& params);


  OdResult skyParameters(OdGiSkyParameters& params) const;

  static OdDbSunPtr castByClassName(OdRxObject* obj);
  static OdDbSunPtr safeCastByClassName(OdRxObject* obj);
  static OdDbSunPtr safeCreateByClassName(); 
};


inline OdDbSunPtr OdDbSun::castByClassName(OdRxObject* obj) {
  return ::odrxCastByClassName<OdDbSun>(obj, "AcDbSun");
}

inline OdDbSunPtr OdDbSun::safeCastByClassName(OdRxObject* obj) {
  return ::odrxSafeCastByClassName<OdDbSun>(obj, "AcDbSun");
}

inline OdDbSunPtr OdDbSun::safeCreateByClassName() {
  return ::odrxSafeCreateObject<OdDbSun>("AcDbSun", "SCENEOE");
};


#include "TD_PackPop.h"

#endif

