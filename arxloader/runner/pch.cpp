// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"

// 当使用预编译的头时，需要使用此源文件，编译才能成功。

CString appDir()
{
  wchar_t szFilePath[MAX_PATH] = { 0 };
  GetModuleFileName(nullptr, szFilePath, MAX_PATH);
  if (wcslen(szFilePath) == 0)
  {
    return L"";
  }

#if _MSVC_LANG >= 201703L
  std::filesystem::path currentFilePath(szFilePath);
  return currentFilePath.parent_path().c_str() + CString(L"\\");
#else
  wchar_t* szTail = wcsrchr(szFilePath, L'\\');
  wchar_t szDir[MAX_PATH] = { 0 };
  wcsncpy_s(szDir, MAX_PATH, szFilePath, szTail - szFilePath + 1);
  return szDir;
#endif
}

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

CString documentsPath()
{
  LPITEMIDLIST pidl = nullptr;
  if (SUCCEEDED(SHGetSpecialFolderLocation(NULL, CSIDL_MYDOCUMENTS, &pidl)))
  {
    wchar_t szPath[MAX_PATH] = { 0 };
    if (SHGetPathFromIDList(pidl, szPath))
    {
      CoTaskMemFree(pidl);

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
