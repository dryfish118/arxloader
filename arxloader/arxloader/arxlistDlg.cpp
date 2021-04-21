
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
	: CDialogEx(IDD_ARXLIST_DIALOG, pParent)
{
}

void CarxlistDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CarxlistDlg, CDialogEx)
END_MESSAGE_MAP()


// CarxlistDlg 消息处理程序

BOOL CarxlistDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
