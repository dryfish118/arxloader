#pragma once
#include "GcFdUiFieldDialog.h"

class CGcFdUiFieldDialogHook;
class GCUI_DLL_DECL CGcFdUiFieldOptionDialog : public CGdUiDialog
{
  friend CGcFdUiFieldDialog;
  //friend CGcFdUiImpFieldDialog;

  DECLARE_DYNAMIC(CGcFdUiFieldOptionDialog)

public:
  CGcFdUiFieldOptionDialog(CGcFdUiFieldDialogHook* pDialogHook, CGcFdUiFieldDialog* pFieldDlg, UINT nIDTemplate, HINSTANCE hDialogResource = NULL);
  virtual ~CGcFdUiFieldOptionDialog();

  CGcFdUiFieldDialogHook* GetFieldDialogHook(void) const;
  CGcFdUiFieldDialog* GetFieldDialog(void) const;
  virtual BOOL    Create(CWnd* pParent);

public:
  // Base class overrides
  virtual BOOL    Create(LPCTSTR lpszTemplateName, CWnd* pParent = NULL);
  virtual BOOL    Create(UINT nIDTemplate, CWnd* pParent = NULL);

protected:
  virtual BOOL    OnSetActive(void);
  virtual BOOL    OnKillActive(void);
  virtual BOOL    OnFieldSelected(UINT uNewFieldId);

  virtual void DoDataExchange(CDataExchange* pDX);
  afx_msg LRESULT OnFormatChanged(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnBeginFormatExDialog(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnEndFormatExDialog(WPARAM wParam, LPARAM lParam);
};
