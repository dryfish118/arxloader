﻿#pragma once

#include "basedlg.h"

class CRunnerDlg : public CBaseDlg
{
// 构造
public:
	CRunnerDlg(CWnd* pParent = nullptr);	// 标准构造函数
	enum { IDD = IDD_ARXRUNNER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
  virtual BOOL OnInitDialog();
  virtual void OnCancel();
  afx_msg void OnBnClickedButtonView();
  afx_msg void OnBnClickedButtonConfig();
  afx_msg void OnBnClickedOk();
  afx_msg LRESULT OnThreadMessage(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()

  static int threadProc(LPVOID param);
  void run();

private:
  CListCtrl m_listLog;
  CString m_sLog;
  HANDLE m_hThread;
  HANDLE m_hEvent;
};
