#include "pch.h"
#include "Resource.h"
#include "config.h"
#include "sharefile.h"
#include "runnerDlg.h"

#define WM_THREAD_MESSAGE (WM_USER + 1001)

CRunnerDlg::CRunnerDlg(CWnd* pParent /*=nullptr*/)
	: CBaseDlg(CRunnerDlg::IDD, pParent)
  , m_hThread(nullptr)
  , m_hEvent(nullptr)
{
  SetDialogName(L"ArxRunner Runner Dialog");
}

void CRunnerDlg::DoDataExchange(CDataExchange* pDX)
{
  CBaseDlg::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_LIST_LOG, m_listLog);
}

BEGIN_MESSAGE_MAP(CRunnerDlg, CBaseDlg)
  ON_BN_CLICKED(IDC_BUTTON_VIEW, &CRunnerDlg::OnBnClickedButtonView)
  ON_BN_CLICKED(IDC_BUTTON_CONFIG, &CRunnerDlg::OnBnClickedButtonConfig)
  ON_BN_CLICKED(IDOK, &CRunnerDlg::OnBnClickedOk)
  ON_MESSAGE(WM_THREAD_MESSAGE, &CRunnerDlg::OnThreadMessage)
END_MESSAGE_MAP()

BOOL CRunnerDlg::OnInitDialog()
{
	CBaseDlg::OnInitDialog();

  SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

  StretchControlXY(IDC_LIST_LOG, 100, 100);
  MoveControlY(IDC_BUTTON_VIEW, 100);
  MoveControlY(IDC_BUTTON_CONFIG, 100);
  MoveControlXY(IDCANCEL, 100, 100);
  MoveControlXY(IDOK, 100, 100);

  m_listLog.ModifyStyle(0, LVS_REPORT | LVS_ALIGNLEFT);
  m_listLog.SetExtendedStyle(m_listLog.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
  m_listLog.InsertColumn(0, L"用例", LVCFMT_CENTER, 400);
  m_listLog.InsertColumn(1, L"结果", LVCFMT_CENTER, 50);

	return TRUE;
}

void CRunnerDlg::OnCancel()
{
  if (!GetDlgItem(IDCANCEL)->IsWindowEnabled())
  {
    return;
  }

  CBaseDlg::OnCancel();
}

void CRunnerDlg::OnBnClickedButtonView()
{
  if (!m_sLog.IsEmpty())
  {
    ShellExecute(NULL, NULL, m_sLog, NULL, NULL, SW_SHOW);
  }
}

void CRunnerDlg::OnBnClickedButtonConfig()
{
  CString strDir(appDir());
  wchar_t szCommandLine[MAX_PATH] = { 0 };
  wcscpy_s(szCommandLine, strDir);
  wcscat_s(szCommandLine, MAX_PATH, L"arxrunner.exe /config");
  HANDLE hInst = startProc(szCommandLine);
  if (hInst)
  {
    WaitForSingleObject(hInst, INFINITE);
  }
}

void CRunnerDlg::OnBnClickedOk()
{
  if (m_hThread)
  {
    SetEvent(m_hEvent);
    WaitForSingleObject(m_hThread, INFINITE);
    CloseHandle(m_hThread);
    m_hThread = nullptr;

    CloseHandle(m_hEvent);
    m_hEvent = nullptr;

    GetDlgItem(IDCANCEL)->EnableWindow(TRUE);
    SetDlgItemText(IDOK, L"开始");
  }
  else
  {
    GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
    SetDlgItemText(IDOK, L"停止");

    m_listLog.DeleteAllItems();

    m_hEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
    DWORD id = 0;
    m_hThread = CreateThread(nullptr, 0,
      (LPTHREAD_START_ROUTINE)threadProc,
      (LPVOID)this, 0, &id);
  }
}

int CRunnerDlg::threadProc(LPVOID param)
{
  ((CRunnerDlg*)param)->run();
  return 0;
}

#define WM_THREAD_FINISH  0
#define WM_THREAD_CANCEL  1
#define WM_THREAD_CASE    2
#define WM_THREAD_SUCCESS 4
#define WM_THREAD_FAIL    5
#define WM_THREAD_CRASH   6
#define WM_THREAD_ERROR   7

void CRunnerDlg::run()
{
  std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
  std::time_t nowTime = std::chrono::system_clock::to_time_t(now);
  std::wstringstream ss;
  ss << std::put_time(std::localtime(&nowTime), L"%Y%m%d-%H%M%S");
  m_sLog.Format(L"%sresult-%s.log", (LPCTSTR)appDir(), ss.str().c_str());

  CConfig cfg;
  CStringArray cases;
  for (int i = 0; i < cfg.m_ac.moduleCount(); i++)
  {
    IArxModule* m = cfg.m_ac.moduleAt(i);
    for (int j = 0; j < m->caseCount(); j++)
    {
      IArxCase* c = m->caseAt(j);
      if (c->isEnabled())
      {
        CString str;
        str.Format(L"%s - [%s]", c->name(), m->moduleName());
        SendMessage(WM_THREAD_MESSAGE, WM_THREAD_CASE, (LPARAM)(LPCTSTR)str);
        
        str.Format(L"%s:%s", m->arxName(), c->name());
        cases.Add(str);
      }
    }
  }

  for (int i = 0; i < cases.GetCount(); i++)
  {
    const wchar_t strEvent[] = L"Global-Gstarcad Cases";
    HANDLE hEvent = CreateEvent(nullptr, TRUE, FALSE, strEvent);

    CShareFile sf(strCaseName);
    sf.writeLine(cases.GetAt(i));

    wchar_t strCmdLine[MAX_PATH * 2] = { 0 };
    if (cfg.m_iGcad)
    {
    }
    else
    {
      swprintf_s(strCmdLine, MAX_PATH * 2,
        //L"\"%sacad.exe\" /ld \"%sarxloader.arx\"",
        L"\"%sacad.exe\" /b \"%srunner.scr\"",
        (LPCTSTR)getAutoCadInstallDir(),
        (LPCTSTR)appDir());
    }
    HANDLE hInst = startProc(strCmdLine);
    if (hInst)
    {
      HANDLE handles[] = { m_hEvent, hEvent, hInst };
      DWORD objId = WaitForMultipleObjects(3, handles, FALSE, INFINITE);
      if (WAIT_OBJECT_0 == objId)
      {
        SetEvent(hEvent);
        CloseHandle(hEvent);

        if (WAIT_OBJECT_0 != WaitForSingleObject(hInst, 1000))
        {
          TerminateProcess(hInst, 0);
        }

        PostMessage(WM_THREAD_MESSAGE, WM_THREAD_CANCEL);
        return;
      }
      else if (WAIT_OBJECT_0 + 1 == objId)
      {
        if (WAIT_OBJECT_0 != WaitForSingleObject(hInst, 1000))
        {
          TerminateProcess(hInst, 0);
        }

        sf.reset();
        if (sf.readLine() == "1")
        {
          PostMessage(WM_THREAD_MESSAGE, WM_THREAD_SUCCESS, i);
        }
        else
        {
          PostMessage(WM_THREAD_MESSAGE, WM_THREAD_FAIL, i);
        }
      }
      else if (WAIT_OBJECT_0 + 2 == objId)
      {
        PostMessage(WM_THREAD_MESSAGE, WM_THREAD_CRASH, i);
      }
    }
    else
    {
      PostMessage(WM_THREAD_MESSAGE, WM_THREAD_ERROR, i);
    }
    CloseHandle(hEvent);
  }

  PostMessage(WM_THREAD_MESSAGE, WM_THREAD_FINISH);
}

LRESULT CRunnerDlg::OnThreadMessage(WPARAM wp, LPARAM lp)
{
  switch (wp)
  {
  case WM_THREAD_CASE:
  {
    m_listLog.InsertItem(m_listLog.GetItemCount(), (LPCTSTR)lp);
    break;
  }
  case WM_THREAD_FINISH:
  {
    m_listLog.InsertItem(m_listLog.GetItemCount(), L"完成");
    OnBnClickedOk();
    break;
  }
  case WM_THREAD_CANCEL:
  {
    SetEvent(m_hEvent);
    WaitForSingleObject(m_hThread, INFINITE);
    CloseHandle(m_hThread);
    m_hThread = nullptr;

    CloseHandle(m_hEvent);
    m_hEvent = nullptr;

    GetDlgItem(IDCANCEL)->EnableWindow(TRUE);
    SetDlgItemText(IDOK, L"开始");

    m_listLog.InsertItem(m_listLog.GetItemCount(), L"取消");
    break;
  }
  case WM_THREAD_SUCCESS:
  {
    m_listLog.SetItemText((int)lp, 1, L"成功");
    break;
  }
  case WM_THREAD_FAIL:
  {
    m_listLog.SetItemText((int)lp, 1, L"失败");
    break;
  }
  case WM_THREAD_CRASH:
  {
    m_listLog.SetItemText((int)lp, 1, L"崩溃");
    break;
  }
  case WM_THREAD_ERROR:
  {
    m_listLog.SetItemText((int)lp, 1, L"错误");
    break;
  }
  default:
    break;
  }

  return 1L;
}
