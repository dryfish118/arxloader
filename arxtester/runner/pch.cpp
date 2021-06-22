// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"

// 当使用预编译的头时，需要使用此源文件，编译才能成功。

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

HANDLE startProc(wchar_t* szCommandLine)
{
  STARTUPINFO si = { 0 };
  si.cb = sizeof(si);
  PROCESS_INFORMATION pi = { 0 };
  if (CreateProcess(nullptr, szCommandLine,
    nullptr, nullptr, FALSE, 0, nullptr, nullptr,
    &si, &pi))
  {
    return pi.hProcess;
  }
  return nullptr;
}
