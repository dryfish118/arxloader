#include "pch.h"
#include "basedlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MOVEX               0x00001
#define MOVEY               0x00002
#define MOVEXY              0x00003
#define ELASTICX            0x00010
#define ELASTICY            0x00020
#define ELASTICXY           0x00030

typedef struct _SControlTag {
  DWORD       id;
  DWORD       flags;
  DWORD       pctX;
  DWORD       pctY;
  CSize       m_dlgRemainderSize;
  _SControlTag()
  {
    id = 0;
    flags = 0;
    pctX = 0;
    pctY = 0;
    m_dlgRemainderSize.cx = 0;
    m_dlgRemainderSize.cy = 0;
  }
} SCTRLINFO, *PSCTRLINFO;

class CElasticMgr
{
public:
  CElasticMgr(CWnd* pCWnd);
  ~CElasticMgr();

  BOOL LockHeight();
  BOOL LockWidth();

  CSize* GetCurrentDelta();
  BOOL GetMinMaxInfo(MINMAXINFO& mmi);

  BOOL SetMinExtents(int x, int y);
  BOOL SetMaxExtents(int x, int y);

  bool findCtrlInfo(DWORD id, DWORD flags);

public:
  CWnd*  m_pCWnd;
  CArray<PSCTRLINFO, PSCTRLINFO>	m_CtrlsInfo;
  CSize				m_szDelta;

  void Free();
  CSize  m_dlgLastSize;
  CRect  m_dlgLastRect;
  CSize  m_dlgMinSize;
  CSize  m_dlgMaxSize;
};

CElasticMgr::CElasticMgr(CWnd* pCWnd)
  : m_szDelta(0, 0), m_dlgLastSize(0, 0), m_dlgLastRect(0, 0, 0, 0), m_dlgMinSize(-1, -1),
  m_dlgMaxSize(-1, -1), m_pCWnd(pCWnd)
{

}

CElasticMgr::~CElasticMgr()
{
  Free();
}

void CElasticMgr::Free()
{
  for (int i = 0; i < m_CtrlsInfo.GetSize(); i++)
  {
    delete m_CtrlsInfo[i];
    m_CtrlsInfo[i] = NULL;
  }
  m_CtrlsInfo.RemoveAll();
}

BOOL CElasticMgr::LockHeight()
{
  CRect rect;
  m_pCWnd->GetWindowRect(rect);
  m_dlgMinSize.cy = rect.Height();
  m_dlgMaxSize.cy = rect.Height();
  return TRUE;
}

BOOL CElasticMgr::LockWidth()
{
  CRect rect;
  m_pCWnd->GetWindowRect(rect);
  m_dlgMinSize.cx = rect.Width();
  m_dlgMaxSize.cx = rect.Width();
  return TRUE;
}

CSize* CElasticMgr::GetCurrentDelta()
{
  return &m_szDelta;
}

BOOL CElasticMgr::GetMinMaxInfo(MINMAXINFO& mmi)
{
  if (m_dlgMinSize.cx >= 0)
  {
    mmi.ptMinTrackSize.x = m_dlgMinSize.cx;
  }
  if (m_dlgMinSize.cy >= 0)
  {
    mmi.ptMinTrackSize.y = m_dlgMinSize.cy;
  }
  if (m_dlgMaxSize.cx >= 0)
  {
    mmi.ptMaxTrackSize.x = m_dlgMaxSize.cx;
  }
  if (m_dlgMaxSize.cy >= 0)
  {
    mmi.ptMaxTrackSize.y = m_dlgMaxSize.cy;
  }
  return TRUE;
}

BOOL CElasticMgr::SetMinExtents(int x, int y)
{
  m_dlgMinSize.cx = x;
  m_dlgMinSize.cy = y;
  return TRUE;
}

BOOL CElasticMgr::SetMaxExtents(int x, int y)
{
  m_dlgMaxSize.cx = x;
  m_dlgMaxSize.cy = y;
  return TRUE;
}

//TODO:暂时不考虑pctX这个参数，等有需求再说吧
bool CElasticMgr::findCtrlInfo(DWORD id, DWORD flags)
{
  for (int i = 0; i < m_CtrlsInfo.GetSize(); i++)
  {
    if (m_CtrlsInfo.GetAt(i)->id == id && m_CtrlsInfo.GetAt(i)->flags == flags)
    {
      return true;
    }
  }
  return false;
}

CBaseDlg::CBaseDlg(UINT idd, CWnd* pParent /*=nullptr*/)
	: CDialogEx(idd, pParent)
{
  m_pElastic = new CElasticMgr(this);
}

CBaseDlg::~CBaseDlg()
{
  if (m_pElastic != NULL)
  {
    delete (CElasticMgr*)m_pElastic;
    m_pElastic = NULL;
  }
}

BEGIN_MESSAGE_MAP(CBaseDlg, CDialogEx)
  ON_MESSAGE(WM_INITDIALOG, CBaseDlg::HandleInitDialog)
  ON_WM_DESTROY()
  ON_WM_GETMINMAXINFO()
  ON_WM_SIZE()
END_MESSAGE_MAP()

static BOOL IsResizableDialog(CBaseDlg* pDlg)
{
  if (pDlg == NULL || pDlg->GetSafeHwnd() == NULL)
  {
    ASSERT(FALSE);
    return FALSE;
  }

  DWORD dwStyle = pDlg->GetStyle();
  return !(dwStyle & DS_MODALFRAME);
}

BOOL CBaseDlg::OnInitDialog()
{
  CDialogEx::OnInitDialog();

  if (m_pElastic && IsResizableDialog(this))
  {
    CElasticMgr* pElasticMgr = (CElasticMgr*)m_pElastic;
    CRect rect;

    GetWindowRect(&rect);
    pElasticMgr->SetMinExtents(rect.Width(), rect.Height());
    pElasticMgr->m_dlgLastRect = rect;

    GetClientRect(&rect);
    pElasticMgr->m_dlgLastSize = rect.Size();

    ::GetWindowRect(::GetDesktopWindow(), &rect);
    pElasticMgr->SetMaxExtents(rect.Width(), rect.Height());
  }

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CBaseDlg::OnDestroy()
{
  CDialogEx::OnDestroy();
}

void CBaseDlg::OnOK()
{
  CRect rect;
  GetWindowRect(rect);
  SetDialogData(L"X", rect.left);
  SetDialogData(L"Y", rect.top);
  SetDialogData(L"Width", rect.Width());
  SetDialogData(L"Height", rect.Height());

  CDialogEx::OnOK();
}

LRESULT CBaseDlg::HandleInitDialog(WPARAM wParam, LPARAM lParam)
{
  LRESULT ret = CDialogEx::HandleInitDialog(wParam, lParam);

  if (m_pElastic && IsResizableDialog(this))
  {
    CElasticMgr* pElasticMgr = (CElasticMgr*)m_pElastic;

    CRect rect;
    GetWindowRect(&rect);

    if (rect == pElasticMgr->m_dlgLastRect)
    {
      if (GetPixelData(rect))
      {
        if (MonitorFromRect(rect, MONITOR_DEFAULTTONULL) != NULL)
        {
          MoveWindow(rect.left, rect.top, rect.Width(), rect.Height());
        }
      }
    }
  }
  else
  {
    CRect rect;
    GetWindowRect(rect);

    CRect pos;
    if (GetPixelData(pos))
    {
      if (MonitorFromRect(pos, MONITOR_DEFAULTTONULL) != NULL)
      {
        MoveWindow(pos.left, pos.top, rect.Width(), rect.Height());
      }
    }
  }

  return ret;
}

void CBaseDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI)
{
  if (m_pElastic)
  {
    CElasticMgr* pElasticMgr = (CElasticMgr*)m_pElastic;
    pElasticMgr->GetMinMaxInfo(*lpMMI);
  }
}

void CBaseDlg::OnSize(UINT nType, int cx, int cy)
{
  BOOL bIsInvalidate = FALSE;

  if (m_pElastic && IsResizableDialog(this))
  {
    CElasticMgr* pElasticMgr = (CElasticMgr*)m_pElastic;
    if (pElasticMgr->m_dlgLastSize.cx > 0)
    {
      CRect wndRect;
      CWnd* pCWnd;
      CSize dlgDeltaSize;  //对话框改变的大小
      CSize ctrlDeltaSize; //控件需改变的大小
      dlgDeltaSize.cx = cx - pElasticMgr->m_dlgLastSize.cx;
      dlgDeltaSize.cy = cy - pElasticMgr->m_dlgLastSize.cy;
      for (int i = 0; i < pElasticMgr->m_CtrlsInfo.GetSize(); i++)
      {
        if (NULL == pElasticMgr->m_CtrlsInfo[i])
        {
          continue;
        }
        ctrlDeltaSize.cx = (pElasticMgr->m_CtrlsInfo[i]->pctX) * dlgDeltaSize.cx
          + pElasticMgr->m_CtrlsInfo[i]->m_dlgRemainderSize.cx;
        pElasticMgr->m_CtrlsInfo[i]->m_dlgRemainderSize.cx = ctrlDeltaSize.cx % 100;
        ctrlDeltaSize.cx = ctrlDeltaSize.cx / 100;

        ctrlDeltaSize.cy = (pElasticMgr->m_CtrlsInfo[i]->pctY) * dlgDeltaSize.cy
          + pElasticMgr->m_CtrlsInfo[i]->m_dlgRemainderSize.cy;
        pElasticMgr->m_CtrlsInfo[i]->m_dlgRemainderSize.cy = ctrlDeltaSize.cy % 100;
        ctrlDeltaSize.cy = ctrlDeltaSize.cy / 100;

        pCWnd = GetDlgItem(pElasticMgr->m_CtrlsInfo[i]->id);
        if (NULL == pCWnd)
        {
          continue;
        }
        pCWnd->GetWindowRect(&wndRect);
        ScreenToClient(&wndRect);
        if (ctrlDeltaSize.cx != 0 && pElasticMgr->m_CtrlsInfo[i]->flags == MOVEX)//movex
        {
          wndRect.OffsetRect(ctrlDeltaSize.cx, 0);
        }
        else if (ctrlDeltaSize.cy != 0 && pElasticMgr->m_CtrlsInfo[i]->flags == MOVEY)//movey
        {
          wndRect.OffsetRect(0, ctrlDeltaSize.cy);
        }
        else if ((ctrlDeltaSize.cx != 0 || ctrlDeltaSize.cy != 0) && pElasticMgr->m_CtrlsInfo[i]->flags == MOVEXY)//movexy
        {
          wndRect.OffsetRect(ctrlDeltaSize.cx, ctrlDeltaSize.cy);
        }
        else if (ctrlDeltaSize.cx != 0 && pElasticMgr->m_CtrlsInfo[i]->flags == ELASTICX)//stretchx
        {
          wndRect.InflateRect(0, 0, ctrlDeltaSize.cx, 0);
        }
        else if (ctrlDeltaSize.cy != 0 && pElasticMgr->m_CtrlsInfo[i]->flags == ELASTICY)//stretchy
        {
          wndRect.InflateRect(0, 0, 0, ctrlDeltaSize.cy);
        }
        else if ((ctrlDeltaSize.cx != 0 || ctrlDeltaSize.cy != 0) && pElasticMgr->m_CtrlsInfo[i]->flags == ELASTICXY)//stretchxy
        {
          wndRect.InflateRect(0, 0, ctrlDeltaSize.cx, ctrlDeltaSize.cy);
        }
        else
        {
          continue;
        }
        if (FALSE == bIsInvalidate)
          bIsInvalidate = TRUE;
        pCWnd->MoveWindow(&wndRect, FALSE);
      }

    }
    pElasticMgr->m_dlgLastSize.cx = cx;
    pElasticMgr->m_dlgLastSize.cy = cy;
  }
  if (TRUE == bIsInvalidate)
    Invalidate();

  CDialogEx::OnSize(nType, cx, cy);
}

BOOL CBaseDlg::GetPixelData(CRect& r)
{
  DWORD left, top, width, height;
  if (GetDialogData(L"X", left) &&
    GetDialogData(L"Y", top) &&
    GetDialogData(L"Width", width) &&
    GetDialogData(L"Height", height))
  {
    r.left = left;
    r.top = top;
    r.right = left + width;
    r.bottom = top + height;

    return TRUE;
  }
  else if (GetSafeHwnd())
  {
    GetWindowRect(r);
    return FALSE;
  }
  else
  {
    return FALSE;
  }
}

BOOL CBaseDlg::GetDialogKey(CString& key)
{
  CString dlgName;
  if (GetDialogName(dlgName))
  {
    key.Format(L"Dialogs\\%s\\", (const wchar_t*)dlgName);
    return TRUE;
  }
  return FALSE;
}

BOOL CBaseDlg::GetDialogData(LPCTSTR valueName, DWORD& data)
{
  CString str;
  GetDialogKey(str);

  CRegKey registerAccess;
  if (ERROR_SUCCESS == registerAccess.Open(HKEY_CURRENT_USER, str, KEY_READ))
  {
    return ERROR_SUCCESS == registerAccess.QueryDWORDValue(valueName, data);
  }

  data = 0;
  return FALSE;
}

BOOL CBaseDlg::SetDialogData(LPCTSTR valueName, DWORD data)
{
  CString str;
  GetDialogKey(str);

  CRegKey registryAccess;
  if (ERROR_SUCCESS == registryAccess.Open(HKEY_CURRENT_USER, str, KEY_WRITE))
  {
    return ERROR_SUCCESS == registryAccess.SetDWORDValue(valueName, data);
  }

  return FALSE;
}

BOOL CBaseDlg::GetDialogName(CString& name)
{
  // 设置对话框名称，前提是派生类未设置
  // 如果在第一次使用m_dlgName时用户没有设置该值，则使用系统的。且不能再设置。
  if (m_dlgName.IsEmpty())
  {
    HINSTANCE hInst = AfxGetResourceHandle();
    wchar_t szModulePath[MAX_PATH] = L"";
    ::GetModuleFileName(hInst, szModulePath, MAX_PATH);

    wchar_t* pszModuleName = wcsrchr(szModulePath, L'\\');
    if (pszModuleName == NULL)
    {
      ASSERT(FALSE);
      pszModuleName = szModulePath;
    }
    else
    {
      pszModuleName++;
    }
    _wcsupr_s(pszModuleName, wcslen(pszModuleName));

    m_dlgName.Format(L"%s-%X", pszModuleName, GetDlgCtrlID());
  }

  name = m_dlgName;
  return !m_dlgName.IsEmpty();
}

void CBaseDlg::SetDialogName(LPCTSTR name)
{
  m_dlgName = name;
  m_dlgName.Trim();
}

BOOL CBaseDlg::MoveControlX(UINT id, LONG lMovePct)
{
  CWnd* pCWnd = GetDlgItem(id);
  if (NULL == pCWnd)
  {
    return FALSE;
  }
  if (m_pElastic)
  {
    CElasticMgr* pElasticMgr = (CElasticMgr*)m_pElastic;
    if (!pElasticMgr->findCtrlInfo(id, MOVEX))
    {
      PSCTRLINFO pSCtrlInfo = new SCTRLINFO;
      pSCtrlInfo->id = id;
      pSCtrlInfo->flags = MOVEX;
      pSCtrlInfo->pctX = lMovePct;
      pElasticMgr->m_CtrlsInfo.Add(pSCtrlInfo);
    }
    return TRUE;
  }
  return FALSE;
}

BOOL CBaseDlg::MoveControlXY(UINT id, LONG lMoveXPct, LONG lMoveYPct)
{
  CWnd* pCWnd = GetDlgItem(id);
  if (NULL == pCWnd)
  {
    return FALSE;
  }
  if (m_pElastic)
  {
    CElasticMgr* pElasticMgr = (CElasticMgr*)m_pElastic;
    if (!pElasticMgr->findCtrlInfo(id, MOVEXY))
    {
      PSCTRLINFO pSCtrlInfo = new SCTRLINFO;
      pSCtrlInfo->id = id;
      pSCtrlInfo->flags = MOVEXY;
      pSCtrlInfo->pctX = lMoveXPct;
      pSCtrlInfo->pctY = lMoveYPct;
      pElasticMgr->m_CtrlsInfo.Add(pSCtrlInfo);
    }
    return TRUE;
  }
  return FALSE;
}

BOOL CBaseDlg::MoveControlY(UINT id, LONG lMovePct)
{
  CWnd* pCWnd = GetDlgItem(id);
  if (NULL == pCWnd)
  {
    return FALSE;
  }
  if (m_pElastic)
  {
    CElasticMgr* pElasticMgr = (CElasticMgr*)m_pElastic;
    if (!pElasticMgr->findCtrlInfo(id, MOVEY))
    {
      PSCTRLINFO pSCtrlInfo = new SCTRLINFO;
      pSCtrlInfo->id = id;
      pSCtrlInfo->flags = MOVEY;
      pSCtrlInfo->pctY = lMovePct;
      pElasticMgr->m_CtrlsInfo.Add(pSCtrlInfo);
    }
    return TRUE;
  }
  return FALSE;
}

BOOL CBaseDlg::StretchControlX(UINT id, LONG lStretchPct)
{
  CWnd* pCWnd = GetDlgItem(id);
  if (NULL == pCWnd)
  {
    return FALSE;
  }
  if (m_pElastic)
  {
    CElasticMgr* pElasticMgr = (CElasticMgr*)m_pElastic;
    if (!pElasticMgr->findCtrlInfo(id, ELASTICX))
    {
      PSCTRLINFO pSCtrlInfo = new SCTRLINFO;
      pSCtrlInfo->id = id;
      pSCtrlInfo->flags = ELASTICX;
      pSCtrlInfo->pctX = lStretchPct;
      pElasticMgr->m_CtrlsInfo.Add(pSCtrlInfo);
    }
    return TRUE;
  }
  return FALSE;
}

BOOL CBaseDlg::StretchControlXY(UINT id, LONG lStretchXPct, LONG lStretchYPct)
{
  CWnd* pCWnd = GetDlgItem(id);
  if (NULL == pCWnd)
  {
    return FALSE;
  }
  if (m_pElastic)
  {
    CElasticMgr* pElasticMgr = (CElasticMgr*)m_pElastic;
    if (!pElasticMgr->findCtrlInfo(id, ELASTICXY))
    {
      PSCTRLINFO pSCtrlInfo = new SCTRLINFO;
      pSCtrlInfo->id = id;
      pSCtrlInfo->flags = ELASTICXY;
      pSCtrlInfo->pctX = lStretchXPct;
      pSCtrlInfo->pctY = lStretchYPct;
      pElasticMgr->m_CtrlsInfo.Add(pSCtrlInfo);
    }
    return TRUE;
  }
  return FALSE;

}

BOOL CBaseDlg::StretchControlY(UINT id, LONG lStretchPct)
{
  CWnd* pCWnd = GetDlgItem(id);
  if (NULL == pCWnd)
  {
    return FALSE;
  }
  if (m_pElastic)
  {
    CElasticMgr* pElasticMgr = (CElasticMgr*)m_pElastic;
    if (!pElasticMgr->findCtrlInfo(id, ELASTICY))
    {
      PSCTRLINFO pSCtrlInfo = new SCTRLINFO;
      pSCtrlInfo->id = id;
      pSCtrlInfo->flags = ELASTICY;
      pSCtrlInfo->pctY = lStretchPct;
      pElasticMgr->m_CtrlsInfo.Add(pSCtrlInfo);
    }
    return TRUE;
  }
  return FALSE;
}
