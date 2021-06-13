﻿
// arxrunnerDlg.h: 头文件
//

#pragma once


// CarxrunnerDlg 对话框
class CarxrunnerDlg : public CDialogEx
{
// 构造
public:
	CarxrunnerDlg(CWnd* pParent = nullptr);	// 标准构造函数
	enum { IDD = IDD_ARXRUNNER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
