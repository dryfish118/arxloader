#include "pch.h"
#include "Resource.h"
#include "config.h"
#include "runnerDlg.h"

#define WM_THREAD_MESSAGE (WM_USER + 1001)

CRunnerDlg::CRunnerDlg(CWnd* pParent /*=nullptr*/)
	: CBaseDlg(CRunnerDlg::IDD, pParent)
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

  StretchControlXY(IDC_LIST_LOG, 100, 100);
  MoveControlY(IDC_BUTTON_VIEW, 100);
  MoveControlY(IDC_BUTTON_CONFIG, 100);
  MoveControlXY(IDCANCEL, 100, 100);
  MoveControlXY(IDOK, 100, 100);

  m_listLog.ModifyStyle(0, LVS_REPORT | LVS_ALIGNLEFT);
  m_listLog.ModifyStyleEx(0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
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
  STARTUPINFO si = { 0 };
  si.cb = sizeof(si);
  PROCESS_INFORMATION pi = { 0 };
  if (CreateProcess(nullptr, szCommandLine,
    nullptr, nullptr, FALSE, 0, nullptr, strDir,
    &si, &pi))
  {
    WaitForSingleObject(pi.hProcess, INFINITE);
  }
}

void CRunnerDlg::OnBnClickedOk()
{
  if (!GetDlgItem(IDCANCEL)->IsWindowEnabled())
  {
    
  }
  else
  {
    m_sLog.Empty();
    GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
    SetDlgItemText(IDOK, L"停止");

    m_listLog.DeleteAllItems();

    std::thread t(startRun, this);
    t.detach();
  }
}

#define WM_THREAD_FINISH 0
#define WM_THREAD_CASE   1


LRESULT CRunnerDlg::OnThreadMessage(WPARAM wp, LPARAM lp)
{
  switch (wp)
  {
  case WM_THREAD_FINISH:
  {
    GetDlgItem(IDCANCEL)->EnableWindow(TRUE);
    SetDlgItemText(IDOK, L"开始");

    m_listLog.InsertItem(m_listLog.GetItemCount(), L"完成");

    break;
  }
  case WM_THREAD_CASE:
  {
    m_listLog.InsertItem(m_listLog.GetItemCount(), (LPCTSTR)lp);
    break;
  }
  default:
    break;
  }

  return 1L;
}

void CRunnerDlg::startRun(CRunnerDlg* pDlg)
{
  CConfig cfg;
  for (int i = 0; i < cfg.m_ac.moduleCount(); i++)
  {
    IArxModule* m = cfg.m_ac.moduleAt(i);
    for (int j = 0; j < m->caseCount(); j++)
    {
      IArxCase* c = m->caseAt(j);
      if (c->isEnabled())
      {
        CString str;
        str.Format(L"%s[%s]", c->name(), m->moduleName());
        pDlg->SendMessage(WM_THREAD_MESSAGE, WM_THREAD_CASE, (LPARAM)(LPCTSTR)str);
      }
    }
  }

  for (int i = 0; i < cfg.m_ac.moduleCount(); i++)
  {
    IArxModule* m = cfg.m_ac.moduleAt(i);
    for (int j = 0; j < m->caseCount(); j++)
    {
      IArxCase* c = m->caseAt(j);
      if (c->isEnabled())
      {
        //
      }
    }
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  
  pDlg->PostMessage(WM_THREAD_MESSAGE, WM_THREAD_FINISH);
}
