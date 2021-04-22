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




// DynamicLinker.h: interface for the OdaDynamicLinkerI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_ODADYNAMICLINKERI_H_INCLUDED_)
#define _ODADYNAMICLINKERI_H_INCLUDED_

#include "StringArray.h"
#include "rxLocale.h"
#include "rxsrvice.h"
#include "LoadReasons.h"

class OdRxDictionary;
class OdRxDLinkerReactor;

#include "RxDictionary.h"
#include "RxModule.h"

class OdRxModule;
/** \details
  This template class is a specialization of the OdSmartPtr class for OdRxModule pointers.
*/
typedef OdSmartPtr<OdRxModule> OdRxModulePtr;

class OdRxSystemServices;
/** \details
  This template class is a specialization of the OdSmartPtr class for OdRxSystemServices pointers.
*/
typedef OdSmartPtr<OdRxSystemServices> OdRxSystemServicesPtr;

#include "TD_PackPush.h"

/** \details
    This class implements Dynamic Linker services for ODA Xtension(TX) applications:
    
    The following services are implemented:
    * Loading applications by specified by application name.
    * Loading and unloading modules specified by filename.
    * Addition and removal of reactors from the dynamic linker reactor chain.
    
    \remarks
    There is exactly one OdRxDynamicLinker class object. It is global to the ODA Platform
    and thus is non-instantiable for client applications.
    
    A pointer to the OdRxDynamicLinker object will be returned by the
    global odrxDynamicLinker() function.

    <group OdRx_Classes> 
*/
class FIRSTDLL_EXPORT OdRxDynamicLinker : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdRxDynamicLinker);

  virtual void* getSymbolAddress(const OdChar* serviceName,
    const char* symbol) const = 0;

  virtual void* getSymbolAddress(const OdChar* serviceName,
    const OdChar* symbol) const = 0;

  virtual bool initListedModules(const OdChar* fileName) = 0;

  virtual bool isAppBusy(const OdChar* modulename) const = 0;

  virtual bool isApplicationLocked(const OdChar* modulename) const = 0;

  virtual bool isAppMDIAware(const OdChar* modulename) const = 0;

  virtual bool loadApp(const OdChar* appName,
    OdaApp::LoadReasons al,
    bool printit,
    bool asCmd = false) = 0;

  virtual bool lockApplication(void* appId) const = 0;

  virtual OdLocale ProductLocale() const = 0;
  
  virtual bool registerAppMDIAware(void* appId) const = 0;
  virtual bool registerAppNotMDIAware(void* appId) const = 0;
  virtual OdaApp::ErrorStatus registerApp(OdaApp::LoadReasons alr, const OdChar *logicalName, void* entryPoint = nullptr) = 0;
  virtual OdRxObject* registerService(const OdChar* serviceName, OdRxService* serviceObj) = 0;
  virtual void setAppBusy(const OdChar* modulename, bool bBusyFlag) const = 0;
  virtual bool unloadApp(const OdChar* appName, bool asCmd = false) = 0;
  virtual bool unloadModule(const OdChar* fileName, bool asCmd = false) = 0;
  virtual bool unlockApplication(void* appId) const = 0;
  virtual OdaApp::ErrorStatus unregisterApp(const OdChar* logicalName) = 0;

  virtual bool loadModule(const OdChar* fileName, bool printit, bool asCmd = false) = 0;
  /** \details
    Adds the specified reactor to the dynamic linker reactor chain.
    \param pReactor [in]  Pointer to the reactor.
  */
  virtual void addReactor (
    OdRxDLinkerReactor* pReactor) = 0;
  /** \details
    Removes the specified reactor to the dynamic linker reactor chain.
    \param pReactor [in]  Pointer to the reactor.
  */
  virtual void removeReactor (
    OdRxDLinkerReactor* pReactor) = 0;

  virtual OdUInt32 ProductLcid() const { return 0; }

  /** \details
    Loads the specified abstract (platform-independent) module.
    
    \returns
    Returns a SmartPointer to the abstract module object.
    
    \param moduleFileName [in]  Module filename to load.
    \param silent [in]  If true, no load status message will be printed.
  */
  virtual OdRxModulePtr loadModule(const OdString& moduleFileName, bool silent = true)
  {
    return OdRxModulePtr();
  }

  /** \details
    Unoads the specified abstract (platform-independent) module.
    
    \param moduleFileName [in]  Module filename to unload.
  */
  virtual bool unloadModule(
    const OdString& moduleFileName)
  {
    return false;
  }


  /** \details
    Unoads all unreferenced modules.
  */
  virtual bool unloadUnreferenced() { return false; }

  /** \details
    Maps the specfied application name to the a module filename,
    and loads that module.

    \param applicationName [in]  TX application name.
    \param silent [in]  If and only if true, no load status message will be printed.
  */
  virtual OdRxModulePtr loadApp(
    const OdString& applicationName,
    bool silent = true) 
  {
    return OdRxModulePtr();
  }

  /** \details
    Returns a SmartPointer to the OdDbSystemServices instance that is used for file creation and access.
    
    \sa
    odInitialize
  */
  virtual OdRxSystemServicesPtr sysServices() const { return OdRxSystemServicesPtr(); }

  /** \details
    Returns a SmartPointer to the OdRxDictionary instance that created by OdInitialize.
  */
  virtual OdRxDictionaryPtr sysRegistry() const { return OdRxDictionaryPtr(); }

  /*!DOM*/  
  /** \details
    Special internal method - used for non-standard module loading only
  */
  virtual OdRxModule* loadModuleObj(
    OdRxModule* pModuleObj, bool bSilent = true)
  {
    return NULL;
  }

  void lockApplication(void *pkt);
  void unlockApplication(void *pkt);
  void registerAppMDIAware(void *pkt);
  void registerAppNotMDIAware(void *pkt);
  /** \details
    Returns the count of loaded modules.
  */
  virtual int getModuleCount() const { return 0; }

  /** \details
    Returns the specified abstract (platform-independent) module.
  */
  virtual OdRxModulePtr getModule(
    int index,
    OdString& key) const
  {
    return OdRxModulePtr();
  }

  /** \details
    Returns the specified abstract (platform-independent) module.
  */
  virtual OdRxModulePtr getModule(
    const OdString& key) const 
  {
    return OdRxModulePtr();
  }

  virtual void getLoadedApps(OdStringArray& res) 
  {
  }
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdRxDynamicLinker pointers.
*/
typedef OdSmartPtr<OdRxDynamicLinker> OdRxDynamicLinkerPtr;


/** \details
    Returns the Teigha global dynamic linker.
*/
FIRSTDLL_EXPORT OdRxDynamicLinker* odrxDynamicLinker();

/** \details
    This function creates a new instance of the class specified by the argument as a string
    and returns a /typified smart pointer/ to it. Always returns non-null pointer (or throws exception).

    \param sClassName [in]  Custom class name as a string.
    \param sAppName [in,optional] RX application name to load if class is not registred.
*/
template <class TClass>
OdSmartPtr<TClass> odrxSafeCreateObject(const OdString& sClassName, const OdString& sAppName = OdString::kEmpty) {
  OdRxDictionaryPtr clsdict = odrxClassDictionary();
  OdRxClass* pClass = (OdRxClass*)clsdict->getAt(sClassName).get();
  if(pClass)
    return (TClass*)pClass->ODSYSCALL0(create).get();
  if(!sAppName.isEmpty()) {
    odrxDynamicLinker()->loadApp(sAppName, false);
    pClass = (OdRxClass*)clsdict->getAt(sClassName).get();
    if(pClass)
      return (TClass*)pClass->ODSYSCALL0(create).get();
  }
  throw OdError(sClassName +" class was not found");
}


inline OdRxModulePtr odrxLoadApp(const OdString& applicationName) { return odrxDynamicLinker()->loadApp(applicationName); }

inline OdRxModulePtr odrxSafeLoadApp(const OdString& applicationName) { return odrxDynamicLinker()->loadApp(applicationName, false); }
FIRSTDLL_EXPORT bool odrxLoadModule(const OdChar * moduleName, bool printit, bool asCmd=false);
FIRSTDLL_EXPORT bool odrxUnloadModule(const OdChar* moduleName,bool asCmd = false);

FIRSTDLL_EXPORT bool odrxAppIsLoaded(const OdString& appname);
FIRSTDLL_EXPORT bool odrxUnloadApp(const OdChar* appname, bool asCmd = false);

FIRSTDLL_EXPORT OdString odrxModuleName(const OdString& appname);

FIRSTDLL_EXPORT bool odrxLockApplication(void* appId);
FIRSTDLL_EXPORT bool odrxApplicationIsLocked(const OdChar* modulename);
FIRSTDLL_EXPORT bool odrxUnlockApplication(void* appId);

FIRSTDLL_EXPORT void* odrxRegisterService(const OdChar* serviceName);
FIRSTDLL_EXPORT void* odrxGetServiceSymbolAddr(const OdChar* serviceName, const OdChar* symbol);
FIRSTDLL_EXPORT bool  odrxServiceIsRegistered(const OdChar * serviceName);
#include "TD_PackPop.h"

#endif // !defined(_ODADYNAMICLINKERI_H_INCLUDED_)

