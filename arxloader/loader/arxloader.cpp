#include "pch.h"
#include "util.h"
#include "arxlistDlg.h"

typedef std::unordered_map<HMODULE, IArxModule*> ModuleArray;

static void listModule(const wchar_t* path, ModuleArray& modules)
{
  HMODULE hArx = LoadLibrary(path);
  if (hArx)
  {
    typedef IArxModule* (WINAPI *ARXMODULE)();
    ARXMODULE fun = (ARXMODULE)GetProcAddress(hArx, "arx_module");
    if (fun)
    {
      IArxModule* am = fun();
      if (am)
      {
        modules.insert(std::make_pair(hArx, am));
        hArx = nullptr;
      }
    }
    FreeLibrary(hArx);
  }
}

static void listModules(ModuleArray& modules)
{
#ifdef ARX
  HANDLE h = GetModuleHandle(L"arxloader.arx");
#else
  HANDLE h = GetModuleHandle(L"arxloader.grx");
#endif // ARX
  if (h == nullptr)
  {
    return;
  }
  wchar_t szFilePath[MAX_PATH] = { 0 };
  GetModuleFileName((HMODULE)h, szFilePath, MAX_PATH);
  if (wcslen(szFilePath) == 0)
  {
    return;
  }

#if _MSVC_LANG >= 201703L
  std::filesystem::path currentFilePath(szFilePath);
  std::filesystem::path currentPath = currentFilePath.parent_path();
  std::filesystem::directory_iterator its(currentPath);
  for (auto& it : its)
  {
    if (it.path().extension() == ".dll")
    {
      listModule(it.path().c_str(), modules);
    }
  }
#else
  wchar_t* szTail = wcsrchr(szFilePath, L'\\');
  wchar_t szDir[MAX_PATH] = { 0 };
  wcsncpy_s(szDir, MAX_PATH, szFilePath, szTail - szFilePath + 1);

  WIN32_FIND_DATA fd = { 0 };
  HANDLE hFind = FindFirstFile(AcString(szDir) + L"*.dll", &fd);
  if (hFind == INVALID_HANDLE_VALUE)
  {
    return;
  }

  do
  {
    listModule(AcString(szDir) + fd.cFileName, modules);
  } while (FindNextFile(hFind, &fd) != 0);

  FindClose(hFind);
#endif // ARX
}

static void cmd_asdf()
{
  ModuleArray modules;
  listModules(modules);

  for (auto& it : modules)
  {
    AcString msg;
    msg.format(L"\n********\t%s\t********", it.second->moduleName());
    gDebuger->printInfo(msg);
    for (int i = 0; i < it.second->casesCount(); i++)
    {
      ITestCase* tc = it.second->getCase(i);
      msg.format(L"\nRun the case \"%s\" ...", tc->name());
      gDebuger->printInfo(msg);
      tc->run();
    }
    FreeLibrary(it.first);
  }
}

static void cmd_subasdf()
{
  //AcRxResourceInstance
#ifdef ARX
  HANDLE h = GetModuleHandle(L"arxloader.arx");
#else
  HANDLE h = GetModuleHandle(L"arxloader.grx");
#endif // ARX

  ModuleArray modules;
  listModules(modules);

  AfxSetResourceHandle((HINSTANCE)h);
  CarxlistDlg dlg;
  for (auto& it : modules)
  {
    dlg.m_modules.emplace_back(it.second);
  }
  dlg.DoModal();
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
