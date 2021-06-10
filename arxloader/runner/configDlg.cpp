#include "pch.h"
#include "Resource.h"
#include "configDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CConfigDlg::CConfigDlg(CConfig& cfg, CWnd* pParent /*=nullptr*/)
	: CBaseDlg(IDD_ARXLIST_DIALOG, pParent)
  , m_config(cfg)
  , m_bSetCheck(false)
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
  MoveControlY(IDC_CHECK_SAVE, 100);
  MoveControlXY(IDC_STATIC, 100, 100);
  MoveControlXY(IDC_RADIO_GCAD, 100, 100);
  MoveControlXY(IDC_RADIO_ACAD, 100, 100);
  MoveControlXY(IDCANCEL, 100, 100);
  MoveControlXY(IDOK, 100, 100);

  SetDlgItemText(IDC_STATIC_LOG, m_config.m_logFile);

  CComboBox* box = (CComboBox*)GetDlgItem(IDC_COMBO_FILTER);
  for (int i = 0; i < m_config.m_filters.GetCount(); i++)
  {
    box->AddString(m_config.m_filters.GetAt(i));
  }

  initTree();
  OnBnClickedButtonFilter();

  ((CButton*)GetDlgItem(IDC_CHECK_SAVE))->SetCheck(m_config.m_bSave);
  ((CButton*)GetDlgItem(IDC_RADIO_GCAD))->SetCheck(m_config.m_bGcad);
  ((CButton*)GetDlgItem(IDC_RADIO_ACAD))->SetCheck(!m_config.m_bGcad);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CConfigDlg::initTree()
{
  m_treeArx.ModifyStyle(0, TVS_HASBUTTONS | TVS_HASLINES |
    TVS_LINESATROOT | TVS_DISABLEDRAGDROP | TVS_CHECKBOXES);

  //m_bSetCheck = true;
  for (int i = 0; i < m_config.m_ac.moduleCount(); i++)
  {
    IArxModule* m = m_config.m_ac.moduleAt(i);
    HTREEITEM hRoot = m_treeArx.InsertItem(m->moduleName());
    m_treeArx.SetItemData(hRoot, (DWORD_PTR)i);
    for (int j = 0; j < m->caseCount(); j++)
    {
      IArxCase* c = m->caseAt(j);
      HTREEITEM hItem = m_treeArx.InsertItem(c->name(), hRoot);
      m_treeArx.SetItemData(hItem, (DWORD_PTR)j);
      if (c->isEnabled())
      {
        m_treeArx.SetCheck(hItem, TRUE);
      }
    }
    m_treeArx.Expand(hRoot, TVE_EXPAND);
  }
  //m_bSetCheck = false;
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

#define isChecked(uState) (((uState) & INDEXTOSTATEIMAGEMASK(2)) == INDEXTOSTATEIMAGEMASK(2))

void CConfigDlg::OnTvnItemChangedTree(NMHDR *pNMHDR, LRESULT *pResult)
{
  if (!m_bSetCheck)
  {
    NMTVITEMCHANGE *pNMTVItemChange = reinterpret_cast<NMTVITEMCHANGE*>(pNMHDR);
    if ((isChecked(pNMTVItemChange->uStateOld) && !isChecked(pNMTVItemChange->uStateNew)) ||
      (!isChecked(pNMTVItemChange->uStateOld) && isChecked(pNMTVItemChange->uStateNew)))
    {
      HTREEITEM hItem = pNMTVItemChange->hItem;
      HTREEITEM hRoot = m_treeArx.GetParentItem(hItem);
      if (hRoot == nullptr)
      {
        BOOL ck = m_treeArx.GetCheck(hItem);
        HTREEITEM hChild = m_treeArx.GetChildItem(hItem);
        while (hChild)
        {
          m_treeArx.SetCheck(hChild, ck);
          hChild = m_treeArx.GetNextSiblingItem(hChild);
        }
      }
      else
      {
        if (m_treeArx.GetCheck(hItem) && !m_treeArx.GetCheck(hRoot))
        {
          m_bSetCheck = true;
          m_treeArx.SetCheck(hRoot, TRUE);
          m_bSetCheck = false;
        }
      }
    }
  }

  *pResult = 1;
}

void CConfigDlg::OnNMDblclkTree(NMHDR *pNMHDR, LRESULT *pResult)
{
  HTREEITEM hItem = m_treeArx.GetSelectedItem();
  if (hItem != nullptr)
  {
    m_treeArx.SetCheck(hItem, m_treeArx.GetCheck(hItem) ? 0 : 1);
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
  m_bSetCheck = true;
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
  m_bSetCheck = false;
}

void CConfigDlg::OnBnClickedOk()
{
  GetDlgItemText(IDC_STATIC_LOG, m_config.m_logFile);

  m_config.m_filters.RemoveAll();
  CComboBox* box = (CComboBox*)GetDlgItem(IDC_COMBO_FILTER);
  for (int i = 0; i < box->GetCount(); i++)
  {
    CString str;
    box->GetLBText(i, str);
    m_config.m_filters.Add(str);
  }

  for (int i = 0; i < m_config.m_ac.moduleCount(); i++)
  {
    IArxModule* m = m_config.m_ac.moduleAt(i);
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
      IArxModule* m = m_config.m_ac.moduleAt(i);

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

  m_config.m_bSave = ((CButton*)GetDlgItem(IDC_CHECK_SAVE))->GetCheck();
  m_config.m_bGcad = ((CButton*)GetDlgItem(IDC_RADIO_GCAD))->GetCheck();

  CBaseDlg::OnOK();
}

