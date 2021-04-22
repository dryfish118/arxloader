#ifndef GCADAPPINFO_INCLUDED
#define GCADAPPINFO_INCLUDED

#include "gcadstd.h"
#include "gcdb.h"
#include "rxdlinkr.h"
#include "rxregsvc.h"

class GcadAppInfoImp;


#pragma pack (push, 8)

class GCRX_DLL_DECL GcadAppInfo: public GcRxObject
{
public:
    GCRX_DECLARE_MEMBERS(GcadAppInfo);

    enum CmdStatus
    {
      kNoAction = 0,
      kRetry    = 1,
      kShowMsg  = 2,
      kNoModule = 3
    };
    enum MgdType
    {
      kUnManaged  = 0,
      kManaged    = 1,
      kJavaScript = 2
    };
    enum ReadFlags
    {
      kNone                      = 0,
      kSkipFindFileForModuleName = 1
    };

    typedef GcadAppInfo::CmdStatus (*LoaderFunPtr)(void *);

    GcadAppInfo();
    virtual ~GcadAppInfo();

    const GCHAR *appName() const;
    void setAppName(const GCHAR *);

    const GCHAR *moduleName() const;
    void setModuleName(const GCHAR *);

    const GCHAR *appDesc() const;
    void setAppDesc(const GCHAR *);

    bool appImplements(const GCHAR *) const;
    GcadAppInfo::MgdType managed() const;
    void setManaged(GcadAppInfo::MgdType bManaged);

    GcadApp::ErrorStatus writeToRegistry(bool bObjDbx = false, bool skipHKLM = false);

    GcadApp::ErrorStatus readFromRegistry();
    GcadApp::ErrorStatus readFromRegistry(ReadFlags flags);
    GcadApp::ErrorStatus delFromRegistry(bool bObjDbx = false);

    GcadAppInfo::CmdStatus runAppLoader();
    void setAppLoader(LoaderFunPtr);

    GcadApp::LoadReasons loadReason() const;
    void setLoadReason(GcadApp::LoadReasons);
    GcadApp::ErrorStatus status() const;

    GcadApp::ErrorStatus writeGroupNameToRegistry(const GCHAR* group);

    GcadApp::ErrorStatus writeCommandNameToRegistry(const GCHAR* globalCmdName, const GCHAR* localCmdName);

    virtual void addRef() {}
    virtual void release(){}

private:
    GcadAppInfoImp * mpImp;
};

#pragma pack (pop)

#endif //GCADAPPINFO_INCLUDED

