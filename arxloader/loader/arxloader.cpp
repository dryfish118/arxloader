#include "pch.h"
#include "util.h"
#include "../inc/arxcase.h"
#include "../runner/sharefile.h"

CString getAutoCadInstallDir()
{
  CRegKey rk;
  if (ERROR_SUCCESS == rk.Open(HKEY_LOCAL_MACHINE,
    L"SOFTWARE\\Autodesk\\AutoCAD\\R23.1\\ACAD-3001:804", KEY_READ))
  {
    wchar_t	szPath[2048] = { 0 };
    ULONG len = 2048;
    if (ERROR_SUCCESS == rk.QueryStringValue(L"AcadLocation", szPath, &len))
    {
      size_t len = wcslen(szPath);
      if (len)
      {
        if (szPath[len - 1] != L'\\')
        {
          szPath[len] = L'\\';
          szPath[len + 1] = L'\0';
        }
      }

      return szPath;
    }
  }
  return L"";
}

static void cmd_asdf()
{
  wchar_t szFilePath[MAX_PATH] = { 0 };
  GetModuleFileName(nullptr, szFilePath, MAX_PATH);
  wchar_t fileName[MAX_PATH] = { 0 };
  _wsplitpath_s(szFilePath, 0, 0, 0, 0, fileName, MAX_PATH, 0, 0);
  HANDLE hLoader = nullptr;
  if (fileName == CString(L"acad"))
  {
    hLoader = GetModuleHandle(L"arxloader.arx");
  }
  else
  {
    hLoader = GetModuleHandle(L"arxloader.grx");
  }
  CString strDir = appDir(hLoader);

  CShareFile sf(strCaseName, true);
  CString str = sf.readLine();
  int pos = str.Find(L':');
  if (pos == -1)
  {
  }
  else
  {
    CString moduleName = str.Left(pos);
    CString caseName = str.Mid(pos + 1);
    HMODULE hArx = LoadLibrary(strDir + moduleName);
    if (hArx)
    {
      typedef IArxModule* (WINAPI *ARXMODULE)();
      ARXMODULE fun = (ARXMODULE)GetProcAddress(hArx, "arx_module");
      if (fun)
      {
        IArxModule* m = fun();
        if (m)
        {
          for (int i = 0; i < m->caseCount(); i++)
          {
            IArxCase* c = m->caseAt(i);
            if (c->name() == caseName)
            {
              CString ret = L"0";
              try
              {
                c->run();
                ret = L"1";
              }
              catch (...)
              {
              }

              sf.reset();
              sf.writeLine(ret);
              const wchar_t strEvent[] = L"Global-Gstarcad Cases";
              HANDLE hEvent = OpenEvent(EVENT_MODIFY_STATE, TRUE, strEvent);
              if (hEvent)
              {
                SetEvent(hEvent);
                CloseHandle(hEvent);
              }

              while (acDocManager->curDocument())
              {
                acDocManager->appContextCloseDocument (acDocManager->curDocument());
              }

              PostQuitMessage(0);

              break;
            }
          }
          hArx = nullptr;
        }
      }
      FreeLibrary(hArx);
    }
  }
}

static void cmd_subasdf()
{
}

class CDocManagerReactor : AcApDocManagerReactor
{
public:
  CDocManagerReactor()
  {
    acDocManager->addReactor(this);
  }

  virtual ~CDocManagerReactor()
  {
    acDocManager->removeReactor(this);
  }

  virtual void documentCreated(AcApDocument* pDocCreating)
  {
    if (acDocManager->documentCount() == 1 &&
      acDocManager->curDocument() == pDocCreating &&
      pDocCreating->docTitle() == CString(L"Drawing1.dwg"))
    {
      acedCommandS(RTSTR, L"ASDF", RTNONE);
    }
    delete this;
  }

  virtual void documentDestroyed(const ACHAR* fileName)
  {
    delete this;
  }
};

void
initApp()
{
  acedRegCmds->addCommand(_T("ASDK_TEST_COMMANDS"),
    _T("ASDK_ASDF"), _T("asdf"), ACRX_CMD_MODAL, cmd_asdf);
  acedRegCmds->addCommand(_T("ASDK_TEST_COMMANDS"),
    _T("ASDK_SUBASDF"), _T("-asdf"), ACRX_CMD_MODAL, cmd_subasdf);
  
  acrxSysRegistry()->atPut(ACRX_CLASS_GLOBALUTIL, new CGlobalUtilImpl());

  new CDocManagerReactor;
}

void
unloadApp()
{
  delete acrxSysRegistry()->remove(ACRX_CLASS_GLOBALUTIL);

  acedRegCmds->removeGroup(_T("ASDK_TEST_COMMANDS"));
}

extern "C" AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* appId)
{
  switch (msg) {
  case AcRx::kInitAppMsg:
    acrxDynamicLinker->unlockApplication(appId);
    acrxDynamicLinker->registerAppMDIAware(appId);
    initApp();
    break;
  case AcRx::kUnloadAppMsg:
    unloadApp();
  }
  return AcRx::kRetOK;
}
//13683229938