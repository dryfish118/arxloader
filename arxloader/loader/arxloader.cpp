#include "pch.h"
#include "util.h"

static void cmd_asdf()
{
//   ModuleArray modules;
//   listModules(modules);
// 
//   for (auto& it : modules)
//   {
//     AcString msg;
//     msg.format(L"\n********\t%s\t********", it.second->moduleName());
//     gDebuger->printInfo(msg);
//     for (int i = 0; i < it.second->caseCount(); i++)
//     {
//       IArxCase* tc = it.second->caseAt(i);
//       msg.format(L"\nRun the case \"%s\" ...", tc->name());
//       gDebuger->printInfo(msg);
//       tc->run();
//     }
//     FreeLibrary(it.first);
//   }
}

static void cmd_subasdf()
{
//   //AcRxResourceInstance
// #ifdef ARX
//   HANDLE h = GetModuleHandle(L"arxloader.arx");
// #else
//   HANDLE h = GetModuleHandle(L"arxloader.grx");
// #endif // ARX
// 
//   ModuleArray modules;
//   listModules(modules);
// 
//   AfxSetResourceHandle((HINSTANCE)h);
//   CarxlistDlg dlg;
//   for (auto& it : modules)
//   {
//     dlg.m_modules.emplace_back(it.second);
//   }
//   dlg.DoModal();
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
