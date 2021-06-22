#ifndef GCOMMON_H
#define GCOMMON_H

#include<filesystem>

static CString appDir(HANDLE hDll = nullptr)
{
  wchar_t szFilePath[MAX_PATH] = { 0 };
  GetModuleFileName((HMODULE)hDll, szFilePath, MAX_PATH);
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

#endif//GCOMMON_H
