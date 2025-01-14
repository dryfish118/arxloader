﻿#pragma once

#include "basedlg.h"
#include "config.h"

class CConfigDlg : public CBaseDlg
{
// 构造
public:
	CConfigDlg(CWnd* pParent = nullptr);	// 标准构造函数
  enum { IDD = IDD_CONFIG_DIALOG };

  CConfig m_config;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
  void checkTreeItem(BOOL bCheck);

	// 生成的消息映射函数
  virtual BOOL OnInitDialog();
  afx_msg void OnBnClickedButtonFile();
  afx_msg void OnBnClickedButtonView();
  afx_msg void OnBnClickedButtonFilter();
  afx_msg void OnBnClickedButtonAdd();
  afx_msg void OnBnClickedButtonDel();
  afx_msg void OnTvnItemChangedTree(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnNMDblclkTree(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnBnClickedButtonAll();
  afx_msg void OnBnClickedButtonClear();
  afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

private:
  CTreeCtrl m_treeArx;
  bool m_bSetCheck;
};
