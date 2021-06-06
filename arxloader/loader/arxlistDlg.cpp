
// arxlistDlg.cpp: 实现文件
//

#include "pch.h"
#include "Resource.h"
#include "arxlistDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CarxlistDlg 对话框


CarxlistDlg::CarxlistDlg(CWnd* pParent /*=nullptr*/)
	: CAcUiDialog(IDD_ARXLIST_DIALOG, pParent)
{
}

void CarxlistDlg::DoDataExchange(CDataExchange* pDX)
{
  CAcUiDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_TREE_TESTCASE, m_treeArx);
}

BEGIN_MESSAGE_MAP(CarxlistDlg, CAcUiDialog)
  ON_WM_DESTROY()
  ON_NOTIFY(TVN_ITEMCHANGED, IDC_TREE_TESTCASE, &CarxlistDlg::OnTvnItemChangedTree)
  ON_NOTIFY(NM_DBLCLK, IDC_TREE_TESTCASE, &CarxlistDlg::OnNMDblclkTree)
  ON_BN_CLICKED(IDC_BUTTON_FILE, &CarxlistDlg::OnBnClickedButtonFile)
  ON_BN_CLICKED(IDC_BUTTON_VIEW, &CarxlistDlg::OnBnClickedButtonView)
  ON_BN_CLICKED(IDOK, &CarxlistDlg::OnBnClickedOk)
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

BOOL CarxlistDlg::OnInitDialog()
{
  CAcUiDialog::OnInitDialog();

  SetDialogName(L"ArxList Dialog");

  StretchControlXY(m_treeArx.GetDlgCtrlID(), 100, 100);
  MoveControlXY(m_treeArx.GetDlgCtrlID(), 0, 0);
  StretchControlX(IDC_STATIC_LOG, 100);
  MoveControlXY(IDC_STATIC_LOG, 0, 100);
  MoveControlXY(IDC_BUTTON_FILE, 100, 100);
  MoveControlXY(IDC_BUTTON_VIEW, 100, 100);
  MoveControlXY(IDOK, 100, 100);

  m_treeArx.ModifyStyle(0, TVS_HASBUTTONS | TVS_HASLINES |
    TVS_LINESATROOT | TVS_DISABLEDRAGDROP | TVS_CHECKBOXES);
  initTree();

  SetDlgItemText(IDC_STATIC_LOG, documentsPath() + L"\\resuts.log");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CarxlistDlg::OnDestroy()
{
  CAcUiDialog::OnDestroy();
}

void CarxlistDlg::initTree()
{
  for (auto& module : m_modules)
  {
    HTREEITEM hRoot = m_treeArx.InsertItem(module->moduleName());
    for (int i = 0; i < module->casesCount(); i++)
    {
      m_treeArx.InsertItem(module->getCase(i)->name(), hRoot);
    }
    m_treeArx.Expand(hRoot, TVE_EXPAND);
    m_treeArx.SetCheck(hRoot);
  }
}

void CarxlistDlg::OnTvnItemChangedTree(NMHDR *pNMHDR, LRESULT *pResult)
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

void CarxlistDlg::OnNMDblclkTree(NMHDR *pNMHDR, LRESULT *pResult)
{
  HTREEITEM hItem = m_treeArx.GetSelectedItem();
  if (hItem != nullptr)
  {
    m_treeArx.SetCheck(hItem, !m_treeArx.GetCheck(hItem));
  }

  *pResult = 1;
}


void CarxlistDlg::OnBnClickedButtonFile()
{
}


void CarxlistDlg::OnBnClickedButtonView()
{
  CString fileName;
  GetDlgItemText(IDC_STATIC_LOG, fileName);
  ShellExecute(NULL, NULL, fileName, NULL, NULL, SW_SHOW);
}


void CarxlistDlg::OnBnClickedOk()
{
}

