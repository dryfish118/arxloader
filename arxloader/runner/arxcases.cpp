#include "pch.h"
#include "arxcases.h"

CArxCases::~CArxCases()
{
  for (auto& it : m_modules)
  {
    FreeLibrary((HMODULE)it->getHandle());
  }
}

CString getAutoCadInstallDir()
{
  CRegKey rk;
  if (ERROR_SUCCESS == rk.Open(HKEY_LOCAL_MACHINE,
    L"SOFTWARE\\Autodesk\\AutoCAD\\R23.1\\ACAD-3001:804", KEY_READ))
  {
    wchar_t	szDir[2048] = { 0 };
    ULONG len = 2048;
    if (ERROR_SUCCESS == rk.QueryStringValue(L"AcadLocation", szDir, &len))
    {
      return szDir;
    }
  }
  return L"";
}

bool CArxCases::init()
{
  HANDLE h = GetModuleHandle(L"arxrunner.exe");
  if (h == nullptr)
  {
    return false;
  }
  wchar_t szFilePath[MAX_PATH] = { 0 };
  GetModuleFileName((HMODULE)h, szFilePath, MAX_PATH);
  if (wcslen(szFilePath) == 0)
  {
    return false;
  }

  SetCurrentDirectory(getAutoCadInstallDir());

#if _MSVC_LANG >= 201703L
  std::filesystem::path currentFilePath(szFilePath);
  std::filesystem::path currentPath = currentFilePath.parent_path();
  std::filesystem::directory_iterator its(currentPath);
  for (auto& it : its)
  {
    if (it.path().extension() == ".dll")
    {
      listModule(it.path().c_str());
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

  return true;
}

void CArxCases::listModule(const wchar_t* path)
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
        am->putHandle(hArx);
        m_modules.emplace_back(am);
        hArx = nullptr;
      }
    }
    FreeLibrary(hArx);
  }
}

void CArxCases::loadCases()
{

}

void CArxCases::saveCases()
{

}

int CArxCases::moduleCount() const
{
  return (int)m_modules.size();
}

IArxModule* CArxCases::moduleAt(int i) const
{
  return m_modules.at(i);
}
