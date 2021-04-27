
// arxlistDlg.h: 头文件
//

#pragma once


// CarxlistDlg 对话框
class CarxlistDlg : public CAcUiDialog
{
// 构造
public:
	CarxlistDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ARXLIST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
  void initTree();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
  afx_msg void OnDestroy();
  afx_msg void OnTvnItemChangedTree(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnNMDblclkTree(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnBnClickedButtonFile();
  afx_msg void OnBnClickedButtonView();
  afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

private:
  CTreeCtrl m_treeArx;
};
