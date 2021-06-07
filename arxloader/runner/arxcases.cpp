#include "pch.h"
#include "arxcases.h"

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

CArxCases::CArxCases()
{
  SetCurrentDirectory(getAutoCadInstallDir());

#if _MSVC_LANG >= 201703L
  std::filesystem::path currentPath((LPCTSTR)appDir());
  std::filesystem::directory_iterator its(currentPath);
  for (auto& it : its)
  {
    if (it.path().extension() == ".dll")
    {
      listModule(it.path().c_str());
    }
  }
#else
  WIN32_FIND_DATA fd = { 0 };
  HANDLE hFind = FindFirstFile(appDir() + L"*.dll", &fd);
  if (hFind == INVALID_HANDLE_VALUE)
  {
    return;
  }

  do
  {
    listModule(appDir() + fd.cFileName);
  } while (FindNextFile(hFind, &fd) != 0);

  FindClose(hFind);
#endif // ARX
}

CArxCases::~CArxCases()
{
  for (auto& it : m_modules)
  {
    FreeLibrary((HMODULE)it->getHandle());
  }
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

int CArxCases::moduleCount() const
{
  return (int)m_modules.size();
}

IArxModule* CArxCases::moduleAt(int i) const
{
  return m_modules.at(i);
}
