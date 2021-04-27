
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

  MoveControlXY(m_treeArx.GetDlgCtrlID(), 0, 0);
  MoveControlX(IDOK, 0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CarxlistDlg::OnDestroy()
{
  CAcUiDialog::OnDestroy();
}
