#pragma once

class CBaseDlg : public CDialogEx
{
// 构造
public:
	CBaseDlg(UINT idd, CWnd* pParent = nullptr);	// 标准构造函数
  virtual ~CBaseDlg();

// 实现
protected:
  BOOL GetPixelData(CRect& r);
  BOOL GetDialogData(LPCTSTR valueName, DWORD& data);
  BOOL SetDialogData(LPCTSTR valueName, DWORD data);
  BOOL GetDialogKey(CString& key);
  BOOL GetDialogName(CString& name);
  void SetDialogName(LPCTSTR name);
  BOOL MoveControlX(UINT id, LONG lMovePct);
  BOOL MoveControlXY(UINT id, LONG lMoveXPct, LONG lMoveYPct);
  BOOL MoveControlY(UINT id, LONG lMovePct);
  BOOL StretchControlX(UINT id, LONG lStretchPct);
  BOOL StretchControlXY(UINT id, LONG lStretchXPct, LONG lStretchYPct);
  BOOL StretchControlY(UINT id, LONG lStretchPct);

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
  virtual void OnOK();
  afx_msg LRESULT HandleInitDialog(WPARAM, LPARAM);
  afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()

private:
  LPVOID  m_pElastic;
  CString m_dlgName;
};
