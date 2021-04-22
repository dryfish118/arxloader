#pragma once
#include "gcadstd.h"
#include "../rxregsvc.h"
#include "../DynamicLinker.h"
#include "PAL/api/GcLocale.h"

#ifdef _GCRX_MODULE_
#  define GCRX_DLL_DECL __declspec(dllexport)
#else
#  define GCRX_DLL_DECL __declspec(dllimport)
#endif

GCRX_DLL_DECL bool gcrxLoadApp(const OdChar* appname, bool asCmd = false);

GCRX_DLL_DECL GcLocale gcrxProductLocale();
GCRX_DLL_DECL OdArray<wchar_t *> * gcrxLoadedApps();
GCRX_DLL_DECL bool gcrxLoadAutoloadApps(const OdChar * appname);
GCRX_DLL_DECL bool gcrxUnloadAutoloadApps(const OdChar * appname);

GCRX_DLL_DECL bool gcrxRegisterAppMDIAware(void* appId);
GCRX_DLL_DECL bool gcrxIsAppMDIAware(const OdChar * moduleName);
GCRX_DLL_DECL bool gcrxRegisterAppNotMDIAware(void* appId);

GCRX_DLL_DECL const OdChar* gcrxProductKey();
unsigned long gcrxProductLCID();

GCRX_DLL_DECL const OdChar * gcrxObjectDBXRegistryKey();

GCRX_DLL_DECL GcadApp::ErrorStatus gcrxRegisterApp(GcadApp::LoadReasons alr, const OdChar *logicalName, bool bDwgU = false);
GCRX_DLL_DECL GcadApp::ErrorStatus gcrxUnregisterApp(const OdChar *logicalname, bool bDwgU = false);

#define	gcrxLoadModule	odrxLoadModule
#define	gcrxUnloadModule	odrxUnloadModule
#define	gcrxUnloadApp	odrxUnloadApp

#define	gcrxLoadedApps	odrxLoadedApps
#define	gcrxAppIsLoaded	odrxAppIsLoaded

#define	gcrxGetServiceSymbolAddr	odrxGetServiceSymbolAddr
#define	gcrxRegisterService	odrxRegisterService
#define	gcrxServiceIsRegistered	odrxServiceIsRegistered

#define	gcrxUnlockApplication	odrxUnlockApplication
#define	gcrxApplicationIsLocked	odrxApplicationIsLocked
#define	gcrxLockApplication	odrxLockApplication

//#define gcrxObjectDBXRegistryKey odrxObjectDBXRegistryKey