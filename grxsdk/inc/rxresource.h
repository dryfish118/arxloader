#ifndef _RXRESOURCE_H_
#define _RXRESOURCE_H_
#pragma once

#include "pimplapi.h"
#include "OdHeap.h"

class OdString;


#undef PAL
namespace Gstarsoft { namespace GstarCAD { namespace PAL { class OdRxResourceInstanceImp; } } }

class OdRxResourceInstance
  : public Pimpl::ApiPart<OdHeapOperators, Gstarsoft::GstarCAD::PAL::OdRxResourceInstanceImp>
{
public:
  FIRSTDLL_EXPORT explicit OdRxResourceInstance(const wchar_t* path);

  FIRSTDLL_EXPORT OdRxResourceInstance(void* hInst);

  FIRSTDLL_EXPORT OdRxResourceInstance(const OdRxResourceInstance& other);

  FIRSTDLL_EXPORT ~OdRxResourceInstance();

  OdRxResourceInstance(OdRxResourceInstance&&) = default;

  OdRxResourceInstance& operator= (OdRxResourceInstance&&) = default;

  OdRxResourceInstance& operator= (const OdRxResourceInstance& other) = delete;

  FIRSTDLL_EXPORT bool tryLoadString(OdInt32 id, OdString& out) const noexcept;
  FIRSTDLL_EXPORT bool isLoaded() const noexcept;

  FIRSTDLL_EXPORT bool loadDataResource(OdInt32 id, unsigned long& resourceSize, const void*& data) const noexcept;

  FIRSTDLL_EXPORT void freeDataResource(const void*& data) const noexcept;


  FIRSTDLL_EXPORT const static OdRxResourceInstance& empty();
};
#endif 