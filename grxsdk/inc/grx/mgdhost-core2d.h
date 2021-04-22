#pragma once
#include "gcadstd.h"
#include "../grx/GdGChar.h"
#include "../grx/gcadstrc.h"
#include "../grx/GcDbCore2dDefs.h"

#define  GcDbManagedHost     OdDbManagedHost
#define  ODDBCORE2D_PORT     GCDBCORE2D_PORT

class OdString;

class OdDbManagedHost
{
public:
  virtual int version() { return 1; }
  virtual OdResult load(const OdChar * fname) = 0;
  virtual bool loadIndirectString(const OdString& resAssemblyPath, const OdString& cmdString, OdString& localCmd) = 0;
  virtual bool isLoaded() = 0;
};

GCDB_DLL_DECL OdDbManagedHost* GSOFT_STDCALL gcdbGetManagedHost();
GCDB_DLL_DECL OdResult GSOFT_STDCALL gcdbSetManagedHost(OdDbManagedHost* pHost);
