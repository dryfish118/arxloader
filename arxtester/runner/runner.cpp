
// runner.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "runner.h"
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
  }
  virtual void ParseParam(const TCHAR* pszParam, BOOL bFlag, BOOL bLast)
  {
    if (bFlag && _wcsicmp(pszParam, L"config") == 0)
    {
      bConfig = TRUE;
    }
  }

  BOOL bConfig;
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
  else
  {
    CMutex m(TRUE, L"Arx runner - Runner");
    if (m.m_hObject)
    {
      CRunnerDlg dlg;
      m_pMainWnd = &dlg;
      dlg.DoModal();
    }
  }

	return FALSE;
}

