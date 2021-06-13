
// arxrunner.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "arxrunner.h"
#include "configDlg.h"
#include "arxrunnerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CArxRunnerApp

BEGIN_MESSAGE_MAP(CArxRunnerApp, CWinApp)
END_MESSAGE_MAP()


// CArxRunnerApp 构造

CArxRunnerApp::CArxRunnerApp()
{
}

CArxRunnerApp theApp;

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

// CArxRunnerApp 初始化

class CArxRunnerCommandLine
  : public CCommandLineInfo
{
public:
  CArxRunnerCommandLine()
  {
    bConfig = FALSE;
    bRunner = FALSE;
    bCase = FALSE;
  }
  virtual void ParseParam(const TCHAR* pszParam, BOOL bFlag, BOOL bLast)
  {
    if (bFlag)
    {
      bCase = FALSE;
      if (_wcsicmp(pszParam, L"config") == 0)
      {
        bConfig = TRUE;
      }
      else if (_wcsicmp(pszParam, L"run") == 0)
      {
        bRunner = TRUE;
      }
      else if (_wcsicmp(pszParam, L"case") == 0)
      {
        bCase = TRUE;
      }
    }
    else if (bCase)
    {
      sCase = pszParam;
    }
  }

  BOOL bConfig;
  BOOL bRunner;
  BOOL bCase;
  CString sCase;
};


BOOL CArxRunnerApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
	SetRegistryKey(_T("ArxRunner"));

  CArxRunnerCommandLine cmdInfo;
  ParseCommandLine(cmdInfo);

  if (cmdInfo.bConfig)
  {
    CMutex m(TRUE, L"Arx runner - Config");
    if (m.m_hObject)
    {
      CConfigDlg dlg;
      m_pMainWnd = &dlg;
      dlg.DoModal();
    }
  }
  else if (cmdInfo.bRunner)
  {
    CMutex m(TRUE, L"Arx runner - Runner");
    if (m.m_hObject)
    {
      CarxrunnerDlg dlg;
      m_pMainWnd = &dlg;
      dlg.DoModal();
    }
  }
  else if (!cmdInfo.sCase.IsEmpty())
  {
    //
  }

	return FALSE;
}

