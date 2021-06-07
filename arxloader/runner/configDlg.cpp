#include "pch.h"
#include "Resource.h"
#include "configDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CConfigDlg::CConfigDlg(CArxCases& ac, CWnd* pParent /*=nullptr*/)
	: CBaseDlg(IDD_ARXLIST_DIALOG, pParent)
  , m_ac(ac)
{
  SetDialogName(L"ArxRunner Config Dialog");
}

void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
  CBaseDlg::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_TREE_TESTCASE, m_treeArx);
}

BEGIN_MESSAGE_MAP(CConfigDlg, CBaseDlg)
  ON_BN_CLICKED(IDC_BUTTON_FILE, &CConfigDlg::OnBnClickedButtonFile)
  ON_BN_CLICKED(IDC_BUTTON_VIEW, &CConfigDlg::OnBnClickedButtonView)
  ON_BN_CLICKED(IDC_BUTTON_FILTER, &CConfigDlg::OnBnClickedButtonFilter)
  ON_BN_CLICKED(IDC_BUTTON_ADD, &CConfigDlg::OnBnClickedButtonAdd)
  ON_BN_CLICKED(IDC_BUTTON_DEL, &CConfigDlg::OnBnClickedButtonDel)
  ON_NOTIFY(TVN_ITEMCHANGED, IDC_TREE_TESTCASE, &CConfigDlg::OnTvnItemChangedTree)
  ON_NOTIFY(NM_DBLCLK, IDC_TREE_TESTCASE, &CConfigDlg::OnNMDblclkTree)
  ON_BN_CLICKED(IDC_BUTTON_ALL, &CConfigDlg::OnBnClickedButtonAll)
  ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CConfigDlg::OnBnClickedButtonClear)
  ON_BN_CLICKED(IDOK, &CConfigDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CarxlistDlg 消息处理程序

static CString documentsPath()
{
  LPITEMIDLIST pidl = nullptr;
  if (SUCCEEDED(SHGetSpecialFolderLocation(NULL, CSIDL_MYDOCUMENTS, &pidl)))
  {
    wchar_t szPath[MAX_PATH] = { 0 };
    if (SHGetPathFromIDList(pidl, szPath))
    {
      CoTaskMemFree(pidl);

      return szPath;
    }
  }

  return L"";
}

BOOL CConfigDlg::OnInitDialog()
{
  CBaseDlg::OnInitDialog();

  StretchControlX(IDC_STATIC_LOG, 100);
  MoveControlX(IDC_BUTTON_FILE, 100);
  MoveControlX(IDC_BUTTON_VIEW, 100);
  StretchControlX(IDC_COMBO_FILTER, 100);
  MoveControlX(IDC_BUTTON_FILTER, 100);
  MoveControlX(IDC_BUTTON_ADD, 100);
  MoveControlX(IDC_BUTTON_DEL, 100);
  MoveControlXY(IDC_TREE_TESTCASE, 0, 0);
  StretchControlXY(IDC_TREE_TESTCASE, 100, 100);
  MoveControlY(IDC_BUTTON_ALL, 100);
  MoveControlY(IDC_BUTTON_CLEAR, 100);
  MoveControlXY(IDC_CHECK_SAVE, 100, 100);
  MoveControlXY(IDCANCEL, 100, 100);
  MoveControlXY(IDOK, 100, 100);

  if (m_logFile.IsEmpty())
  {
    m_logFile = documentsPath() + L"\\resuts.log";
  }
  SetDlgItemText(IDC_STATIC_LOG, m_logFile);

  CComboBox* box = (CComboBox*)GetDlgItem(IDC_COMBO_FILTER);
  for (int i = 0; i < m_filters.GetCount(); i++)
  {
    box->AddString(m_filters.GetAt(i));
  }

  m_treeArx.ModifyStyle(0, TVS_HASBUTTONS | TVS_HASLINES |
    TVS_LINESATROOT | TVS_DISABLEDRAGDROP | TVS_CHECKBOXES);
  initTree();
  OnBnClickedButtonFilter();

  ((CButton*)GetDlgItem(IDC_CHECK_SAVE))->SetCheck(m_bSave);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CConfigDlg::initTree()
{
  for (int i = 0; i < m_ac.moduleCount(); i++)
  {
    IArxModule* m = m_ac.moduleAt(i);
    HTREEITEM hRoot = m_treeArx.InsertItem(m->moduleName());
    m_treeArx.SetItemData(hRoot, (DWORD_PTR)i);
    for (int j = 0; j < m->caseCount(); j++)
    {
      IArxCase* c = m->caseAt(j);
      HTREEITEM hItem = m_treeArx.InsertItem(c->name(), hRoot);
      m_treeArx.SetItemData(hItem, (DWORD_PTR)j);
      m_treeArx.SetCheck(hItem, c->isEnabled());
    }
    m_treeArx.Expand(hRoot, TVE_EXPAND);
    m_treeArx.SetCheck(hRoot);
  }
}

void CConfigDlg::OnBnClickedButtonFile()
{
  wchar_t logFile[MAX_PATH] = { 0 };
  ::GetDlgItemText(GetSafeHwnd(), IDC_STATIC_LOG, logFile, MAX_PATH);
  CFileDialog dlg(FALSE, L"log", logFile,
    OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
    L"日志文件|*.log||");
  if (IDOK == dlg.DoModal())
  {
    SetDlgItemText(IDC_STATIC_LOG, dlg.GetPathName());
  }
}

void CConfigDlg::OnBnClickedButtonView()
{
  CString fileName;
  GetDlgItemText(IDC_STATIC_LOG, fileName);
  ShellExecute(NULL, NULL, fileName, NULL, NULL, SW_SHOW);
}

void CConfigDlg::OnBnClickedButtonFilter()
{

}

void CConfigDlg::OnBnClickedButtonAdd()
{
  CString str;
  GetDlgItemText(IDC_COMBO_FILTER, str);
  if (!str.Trim().IsEmpty())
  {
    CComboBox* box = (CComboBox*)GetDlgItem(IDC_COMBO_FILTER);
    if (-1 == box->FindString(0, str))
    {
      box->AddString(str);
    }
  }
}

void CConfigDlg::OnBnClickedButtonDel()
{
  CString str;
  GetDlgItemText(IDC_COMBO_FILTER, str);
  if (!str.Trim().IsEmpty())
  {
    CComboBox* box = (CComboBox*)GetDlgItem(IDC_COMBO_FILTER);
    int index = box->FindString(0, str);
    if (-1 != index)
    {
      box->DeleteString(index);
    }
    SetDlgItemText(IDC_COMBO_FILTER, L"");
  }
}

void CConfigDlg::OnTvnItemChangedTree(NMHDR *pNMHDR, LRESULT *pResult)
{
  NMTVITEMCHANGE *pNMTVItemChange = reinterpret_cast<NMTVITEMCHANGE*>(pNMHDR);
  HTREEITEM hItem = pNMTVItemChange->hItem;
  if (m_treeArx.GetParentItem(hItem) == nullptr)
  {
    BOOL ck = m_treeArx.GetCheck(hItem);
    HTREEITEM hChild = m_treeArx.GetChildItem(hItem);
    while (hChild)
    {
      m_treeArx.SetCheck(hChild, ck);
      hChild = m_treeArx.GetNextItem(hChild, TVGN_NEXT);
    }
  }

  *pResult = 0;
}

void CConfigDlg::OnNMDblclkTree(NMHDR *pNMHDR, LRESULT *pResult)
{
  HTREEITEM hItem = m_treeArx.GetSelectedItem();
  if (hItem != nullptr)
  {
    m_treeArx.SetCheck(hItem, !m_treeArx.GetCheck(hItem));
  }

  *pResult = 1;
}

void CConfigDlg::OnBnClickedButtonAll()
{
  checkTreeItem(TRUE);
}

void CConfigDlg::OnBnClickedButtonClear()
{
  checkTreeItem(FALSE);
}

void CConfigDlg::checkTreeItem(BOOL bCheck)
{
  HTREEITEM hRoot = m_treeArx.GetRootItem();
  while (hRoot)
  {
    m_treeArx.SetCheck(hRoot, bCheck);
    HTREEITEM hChild = m_treeArx.GetChildItem(hRoot);
    while (hChild)
    {
      m_treeArx.SetCheck(hChild, bCheck);
      hChild = m_treeArx.GetNextSiblingItem(hChild);
    }

    hRoot = m_treeArx.GetNextSiblingItem(hRoot);
  }
}

void CConfigDlg::OnBnClickedOk()
{
  GetDlgItemText(IDC_STATIC_LOG, m_logFile);

  m_filters.RemoveAll();
  CComboBox* box = (CComboBox*)GetDlgItem(IDC_COMBO_FILTER);
  for (int i = 0; i < box->GetCount(); i++)
  {
    CString str;
    box->GetLBText(i, str);
    m_filters.Add(str);
  }

  for (int i = 0; i < m_ac.moduleCount(); i++)
  {
    IArxModule* m = m_ac.moduleAt(i);
    for (int j = 0; j < m->caseCount(); j++)
    {
      IArxCase* c = m->caseAt(j);
      c->setEnabled(false);
    }
  }

  HTREEITEM hRoot = m_treeArx.GetRootItem();
  while (hRoot)
  {
    if (m_treeArx.GetCheck(hRoot))
    {
      int i = (int)m_treeArx.GetItemData(hRoot);
      IArxModule* m = m_ac.moduleAt(i);

      HTREEITEM hChild = m_treeArx.GetChildItem(hRoot);
      while (hChild)
      {
        if (m_treeArx.GetCheck(hChild))
        {
          int j = (int)m_treeArx.GetItemData(hChild);
          m->caseAt(j)->setEnabled(true);
        }

        hChild = m_treeArx.GetNextSiblingItem(hChild);
      }
    }

    hRoot = m_treeArx.GetNextSiblingItem(hRoot);
  }

  m_bSave = ((CButton*)GetDlgItem(IDC_CHECK_SAVE))->GetCheck();

  CBaseDlg::OnOK();
}

