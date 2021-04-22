#pragma once
#include <afxwin.h>
#include "gduiDialog.h"

class GcDbField;
class GcDbDatabase;
class CGcFdUiFieldOptionDialog;
class CGcFdUiImpFieldDialog;

#define GCFDUI_FD_CREATE_FIELD         1
#define GCFDUI_FD_EDIT_FIELD           2

class GCUI_DLL_DECL CGcFdUiFieldDialog : public CGdUiDialog
{
  friend CGcFdUiImpFieldDialog;
  DECLARE_DYNAMIC(CGcFdUiFieldDialog)

public:
  CGcFdUiFieldDialog(CWnd* pParent = NULL);
  virtual ~CGcFdUiFieldDialog();

  INT_PTR         DoModal(GcDbField*& pField, BOOL bEdit, GcDbDatabase* pDb);
  GcDbField*      GetFieldToEdit(void) const;
  BOOL            SetFieldCodeReadOnly(BOOL bReadOnly = TRUE);
  CString         GetFieldCode(void) const;
  BOOL            SetFieldCode(LPCTSTR pszExpr);
  BOOL            IsFieldCodeDirty(void);
  CEdit*          GetFieldCodeEditCtrl(void);
  BOOL            GetCurrentField(UINT* pFieldId, UINT* pCatId) const;
  BOOL            SelectField(UINT uFieldId, UINT uCatId);
  CGcFdUiFieldOptionDialog* GetOptionDialog(void) const;

public:
  // Base class overrides
  void            BeginEditorCommand(void);
  void            CompleteEditorCommand(BOOL restoreDialogs = TRUE);
  void            CancelEditorCommand(void);
protected:
  afx_msg void    OnCbnSelChangeCategoryList(void);
  afx_msg void    OnLbnSelChangeFieldNameList(void);
  afx_msg void    OnEnChangeFieldCode(void);
  afx_msg LRESULT OnFormatChanged(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnBeginFormatExDialog(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnEndFormatExDialog(WPARAM wParam, LPARAM lParam);
};
