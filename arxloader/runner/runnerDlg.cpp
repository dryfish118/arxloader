#include "pch.h"
#include "Resource.h"
#include "config.h"
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

static HANDLE startProc(wchar_t* szCommandLine)
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

    DeleteObject(m_hEvent);
    m_hEvent = nullptr;

    GetDlgItem(IDCANCEL)->EnableWindow(TRUE);
    SetDlgItemText(IDOK, L"开始");
  }
  else
  {
    m_sLog.Empty();
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
#define WM_THREAD_RESULT  3

void CRunnerDlg::run()
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
        SendMessage(WM_THREAD_MESSAGE, WM_THREAD_CASE, (LPARAM)(LPCTSTR)str);
      }
    }
  }

  int count = 0;
  const wchar_t szEvent[] = L"Gstarcad Cases";
  HANDLE hEvent = CreateEvent(nullptr, TRUE, TRUE, szEvent);
  for (int i = 0; i < cfg.m_ac.moduleCount(); i++)
  {
    IArxModule* m = cfg.m_ac.moduleAt(i);
    for (int j = 0; j < m->caseCount(); j++)
    {
      IArxCase* c = m->caseAt(j);
      if (c->isEnabled())
      {
        wchar_t strCmdLine[MAX_PATH] = { 0 };
        swprintf_s(strCmdLine, MAX_PATH,
          L"%sarxrunner.exe /case \"%s:%s:%s\"",
          (LPCTSTR)appDir(), szEvent, m->moduleName(), c->name());
        HANDLE hInst = startProc(strCmdLine);
        if (hInst)
        {
          HANDLE handles[] = { m_hEvent, hInst };
          DWORD objId = WaitForMultipleObjects(2, handles, FALSE, INFINITE);
          if (WAIT_OBJECT_0 == objId)
          {
            ResetEvent(hEvent);
            CloseHandle(hEvent);
            WaitForSingleObject(hInst, INFINITE);
            SendMessage(WM_THREAD_MESSAGE, WM_THREAD_CANCEL);
            return;
          }
          else if (WAIT_OBJECT_0 + 1 == objId)
          {
            DWORD ret = 0;
            GetExitCodeProcess(hInst, &ret);
            SendMessage(WM_THREAD_MESSAGE, WM_THREAD_RESULT, (count << 4) | ret);
          }
        }
        else
        {
          SendMessage(WM_THREAD_MESSAGE, WM_THREAD_RESULT, (count << 4) | 2);
        }
        count++;
      }
    }
  }
  CloseHandle(hEvent);

  SendMessage(WM_THREAD_MESSAGE, WM_THREAD_FINISH);
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
  case WM_THREAD_CANCEL:
  {
    GetDlgItem(IDCANCEL)->EnableWindow(TRUE);
    SetDlgItemText(IDOK, L"开始");

    m_listLog.InsertItem(m_listLog.GetItemCount(),
      (wp == WM_THREAD_FINISH) ? L"完成" : L"取消");

    break;
  }
  case WM_THREAD_RESULT:
  {
    m_listLog.SetItemText((int)(lp >> 4), 1, ((lp & 0xF) == 1) ? L"成功" : L"失败");
    break;
  }
  default:
    break;
  }

  return 1L;
}
