#include "pch.h"
#include "Resource.h"
#include "runnerDlg.h"

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
END_MESSAGE_MAP()

BOOL CRunnerDlg::OnInitDialog()
{
	CBaseDlg::OnInitDialog();

  StretchControlXY(IDC_TREE_TESTCASE, 100, 100);
  MoveControlY(IDC_BUTTON_ALL, 100);
  MoveControlY(IDC_BUTTON_CLEAR, 100);
  MoveControlY(IDC_CHECK_SAVE, 100);
  MoveControlXY(IDC_STATIC, 100, 100);
  MoveControlXY(IDC_RADIO_GCAD, 100, 100);
  MoveControlXY(IDC_RADIO_ACAD, 100, 100);
  MoveControlXY(IDCANCEL, 100, 100);
  MoveControlXY(IDOK, 100, 100);

	return TRUE;
}

void CRunnerDlg::OnBnClickedButtonView()
{
}


void CRunnerDlg::OnBnClickedButtonConfig()
{
}


void CRunnerDlg::OnBnClickedOk()
{
}
