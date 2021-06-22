#include "pch.h"
#include "util.h"
#include "../inc/arxcase.h"
#include "../runner/sharefile.h"

static void exitAll(void *)
{
  while (acDocManager->documentCount())
  {
    AcApDocument* pDoc = acDocManager->curDocument();
    if (pDoc)
    {
      resbuf rb = { 0 };
      acedGetVar(L"DBMOD", &rb);
      if (rb.resval.rint == 1)
      {
        acDocManager->lockDocument(pDoc);
        pDoc->pushDbmod();
        acDocManager->unlockDocument(pDoc);
      }
      acDocManager->appContextCloseDocument(pDoc);
    }
  }

  PostQuitMessage(0);
}

static bool isInAcad()
{
  wchar_t szFilePath[MAX_PATH] = { 0 };
  GetModuleFileName(nullptr, szFilePath, MAX_PATH);
  wchar_t fileName[MAX_PATH] = { 0 };
  _wsplitpath_s(szFilePath, 0, 0, 0, 0, fileName, MAX_PATH, 0, 0);
  return CString(L"acad").CompareNoCase(fileName);
}

static void cmd_asdf()
{
  OutputDebugString(L"Command: ASDF");

  HANDLE hLoader = GetModuleHandle(
    isInAcad() ? L"loader.arx" : L"loader.grx");
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

    str.Format(L"Load: %s%s", strDir, moduleName);
    OutputDebugString(str);
    HMODULE hArx = LoadLibrary(strDir + moduleName);
    if (hArx)
    {
      OutputDebugString(L"Loaded");
      typedef IArxModule* (WINAPI *ARXMODULE)();
      ARXMODULE fun = (ARXMODULE)GetProcAddress(hArx, "arx_module");
      if (fun)
      {
        OutputDebugString(L"Arx module");
        IArxModule* m = fun();
        if (m)
        {
          for (int i = 0; i < m->caseCount(); i++)
          {
            IArxCase* c = m->caseAt(i);
            if (c->name() == caseName)
            {
              str.Format(L"Case: %s", caseName);
              OutputDebugString(str);

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

              acDocManager->executeInApplicationContext(exitAll, nullptr);

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

void
initApp()
{
  acedRegCmds->addCommand(_T("ASDK_TEST_COMMANDS"),
    _T("ASDK_ASDF"), _T("asdf"), ACRX_CMD_MODAL, cmd_asdf);
  acedRegCmds->addCommand(_T("ASDK_TEST_COMMANDS"),
    _T("ASDK_SUBASDF"), _T("-asdf"), ACRX_CMD_MODAL, cmd_subasdf);
  
  acrxSysRegistry()->atPut(ACRX_CLASS_GLOBALUTIL, new CGlobalUtilImpl());
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
