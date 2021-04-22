#ifndef _RXSHAREDOBJ_H_
#define _RXSHAREDOBJ_H_
#pragma once

#include "pimplapi.h"
#include "OdHeap.h"

#undef PAL
namespace Gstarsoft { namespace GstarCAD { namespace PAL { class OdRxSharedObjImp; } } }

class OdRxSharedObject
  : public Pimpl::ApiPart<OdHeapOperators, Gstarsoft::GstarCAD::PAL::OdRxSharedObjImp>
{
private:
  OdRxSharedObject(Gstarsoft::GstarCAD::PAL::OdRxSharedObjImp* soImp);

  OdRxSharedObject(const OdRxSharedObject& from) = delete;
  OdRxSharedObject& operator=(const OdRxSharedObject& from) = delete;

public:
  FIRSTDLL_EXPORT OdRxSharedObject();
  FIRSTDLL_EXPORT OdRxSharedObject(void* nativeHandle);
  FIRSTDLL_EXPORT ~OdRxSharedObject();
  FIRSTDLL_EXPORT OdRxSharedObject(OdRxSharedObject&& from) = default;
  FIRSTDLL_EXPORT OdRxSharedObject& operator=(OdRxSharedObject&& from);


  FIRSTDLL_EXPORT bool isLoaded() const noexcept;
  FIRSTDLL_EXPORT void * getSymbol(const char *  name) const noexcept;

  static FIRSTDLL_EXPORT OdRxSharedObject tryLoad(const wchar_t* path, bool autoRelease = true);
};

#endif 