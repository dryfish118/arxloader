#pragma once
#include <string>
#include "RootExport.h"
class OdLocaleImp;

class FIRSTDLL_EXPORT OdLocale
{
public:
  OdLocale(const wchar_t* iso2LangName, const wchar_t* iso2CountryName);
  ~OdLocale();
  OdLocale(const OdLocale& locale);
  OdLocale& operator =(const OdLocale& locale);
  OdLocale(OdLocale&& locale);
  OdLocale& operator =(OdLocale&& locale);
  bool operator ==(const OdLocale& loc) const;
  bool operator !=(const OdLocale& loc) const;

  const wchar_t*   iso2LangName() const;
  const wchar_t*   iso2CountryName() const;

  bool             isValid() const;

#if defined(GC_NON_CROSS_PLATFORM_API)
  using LocaleId = int;
  GCPAL_PORT OdLocale(LocaleId lcid);
  GCPAL_PORT operator LocaleId();
#endif

private:
  friend class GcLocaleService;
  OdLocale(const OdLocaleImp* pImpLocale);

  OdLocaleImp* m_pImpGcLocale;
};