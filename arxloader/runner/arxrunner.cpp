
// arxrunner.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "arxrunner.h"
#include "configDlg.h"
#include "runnerDlg.h"


// CArxRunnerApp

BEGIN_MESSAGE_MAP(CArxRunnerApp, CWinApp)
END_MESSAGE_MAP()


// CArxRunnerApp 构造

CArxRunnerApp::CArxRunnerApp()
{
}

CArxRunnerApp theApp;

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

void executeCase(const CString& arg);
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
      CRunnerDlg dlg;
      m_pMainWnd = &dlg;
      dlg.DoModal();
    }
  }
  else if (!cmdInfo.sCase.IsEmpty())
  {
    executeCase(cmdInfo.sCase);
  }

	return FALSE;
}

