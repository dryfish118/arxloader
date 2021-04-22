#pragma once
#include "rxobject.h"

#include "rxnames.h"
#pragma pack (push, 8)

class OdRxClass;
FIRSTDLL_EXPORT OdRxClass * odrxFindOdRxClass(const OdChar *pClassName);


#ifdef ODRX_AUTO_INIT 

#define ODRX_DEFINE_GPDESC(CLASS_NAME) \
    OdRxClass* CLASS_NAME::g_pDesc = odrxQueueClassForInitialization(&CLASS_NAME::g_pDesc, &CLASS_NAME::rxInit);

#else

#define ODRX_DEFINE_GPDESC(CLASS_NAME) \
    OdRxClass* CLASS_NAME::g_pDesc = nullptr;
#endif

#define ODRX_DECLARE_GPDESC(CLASS_NAME) \
    static OdRxClass* g_pDesc; 

class OdRxObject;
template <typename T>
static OdRxObject* odrxInstantiateClass() { return new T(); }

#define ODRX_DECLARE_MEMBERS_EXPIMP(CLASS_NAME, EXPIMP) \
    friend OdRxObject* ::odrxInstantiateClass<CLASS_NAME>(); \
    EXPIMP virtual OdRxClass* isA() const ODRX_OVERRIDE; \
    ODRX_DECLARE_GPDESC(CLASS_NAME); \
    EXPIMP static OdRxClass* desc(); \
    static CLASS_NAME* cast(const OdRxObject* inPtr) \
        { return ((inPtr == NULL) || !inPtr->isKindOf(CLASS_NAME::desc())) \
          ? NULL : (CLASS_NAME*)inPtr; }; \
    static void rxInit(); \
    static void rxInit(AppNameChangeFuncPtr);\
    static void rxUninit();\
    virtual OdRxObject* queryX(const OdRxClass* protocolClass) const;\
    static OdRxObjectPtr pseudoConstructor(); 

#define ODRX_EMPTY

#define ODRX_DEFINE_MEMBERS3(CLASS_NAME) \
OdRxClass* CLASS_NAME::desc() \
{ \
    if (g_pDesc == nullptr) \
        g_pDesc = ::odrxFindOdRxClass(OD_T(#CLASS_NAME)); \
    return g_pDesc; \
} \
OdRxClass* CLASS_NAME::isA() const \
{ \
    if (g_pDesc == nullptr) \
        g_pDesc = ::odrxFindOdRxClass(OD_T(#CLASS_NAME)); \
    return g_pDesc; \
} \
OdRxObject* CLASS_NAME::queryX(const OdRxClass* pClass) const {            \
    return NULL;            \
}\
ODRX_DEFINE_GPDESC(CLASS_NAME)

extern "C" void FIRSTDLL_EXPORT odrx_abort(const OdChar * format, ...);
#define ODRX_STATIC_CHECK(CLASS_NAME) \
    if (g_pDesc!=nullptr) { \
        OdRxClass *pClass = ::odrxFindOdRxClass(OD_T(#CLASS_NAME)); \
        if (pClass) { \
            if (g_pDesc == pClass) \
                return; \
            else \
                odrx_abort(OD_T("Class mismatch")); \
        } \
    }

#define ODRX_NO_CONS_DEFINE_MEMBERS_WITH_PROPERTIES(CLASS_NAME,PARENT_CLASS, MAKEPROPS) \
ODRX_DEFINE_MEMBERS3(CLASS_NAME); \
void CLASS_NAME::rxInit() { \
    ODRX_STATIC_CHECK(CLASS_NAME); \
    g_pDesc = newOdRxClass(OD_T(#CLASS_NAME), OD_T(#PARENT_CLASS), \
        0, 0, 0, \
        0, 0, 0, 0, MAKEPROPS); \
}

#define ODRX_DXF_DEFINE_MEMBERS_WITH_PROPERTIES(CLASS_NAME,PARENT_CLASS,DWG_VERSION,\
              MAINTENANCE_VERSION,PROXY_FLAGS,DXF_NAME,APP, MAKEPROPS) \
ODRX_DEFINE_MEMBERS3(CLASS_NAME); \
void CLASS_NAME::rxInit() { \
    ODRX_STATIC_CHECK(CLASS_NAME); \
    g_pDesc = newOdRxClass(OD_T(#CLASS_NAME), OD_T(#PARENT_CLASS), \
        DWG_VERSION,MAINTENANCE_VERSION,PROXY_FLAGS, \
        &odrxInstantiateClass<CLASS_NAME>, OD_T(#DXF_NAME), OD_T(#APP), NULL, MAKEPROPS); \
} \
void CLASS_NAME::rxInit(AppNameChangeFuncPtr ptr) { \
    ODRX_STATIC_CHECK(CLASS_NAME); \
    g_pDesc = newOdRxClass(OD_T(#CLASS_NAME), OD_T(#PARENT_CLASS), \
        DWG_VERSION,MAINTENANCE_VERSION,PROXY_FLAGS, \
        &odrxInstantiateClass<CLASS_NAME>, OD_T(#DXF_NAME), OD_T(#APP), ptr, MAKEPROPS); \
}
#pragma pack (pop)