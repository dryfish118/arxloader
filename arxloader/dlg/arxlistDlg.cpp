
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
END_MESSAGE_MAP()


// CarxlistDlg 消息处理程序

BOOL CarxlistDlg::OnInitDialog()
{
  CAcUiDialog::OnInitDialog();

  SetDialogName(L"ArxList Dialog");

  StretchControlXY(m_treeArx.GetDlgCtrlID(), 100, 100);
  MoveControlXY(m_treeArx.GetDlgCtrlID(), 0, 0);
  MoveControlXY(IDOK, 100, 100);

  m_treeArx.ModifyStyle(0,TVS_HASBUTTONS | TVS_HASLINES | 
    TVS_LINESATROOT | TVS_DISABLEDRAGDROP | TVS_CHECKBOXES |
    TVS_TRACKSELECT | /*TVS_SINGLEEXPAND | */TVS_FULLROWSELECT);
  HTREEITEM hRoot = m_treeArx.InsertItem(L"Dlg test cases");
  m_treeArx.InsertItem(L"Test CAcUiDialog", hRoot);
  m_treeArx.Expand(hRoot, TVE_EXPAND);
  m_treeArx.SetCheck(hRoot);
  hRoot = m_treeArx.InsertItem(L"Field test cases");
  m_treeArx.InsertItem(L"Create a mtext with a field", hRoot);
  m_treeArx.InsertItem(L"Create a line", hRoot);
  m_treeArx.InsertItem(L"List all fields in an object", hRoot);
  m_treeArx.InsertItem(L"Read the field info in an object", hRoot);
  m_treeArx.Expand(hRoot, TVE_EXPAND);
  m_treeArx.SetCheck(hRoot);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CarxlistDlg::OnDestroy()
{
  CAcUiDialog::OnDestroy();
}
