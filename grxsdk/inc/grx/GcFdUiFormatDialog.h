#pragma once
#include "gduiDialog.h"
#include <afxwin.h>
class CGcFdUiFormatList;

#define GCFDUI_UM_FORMAT_CHANGED        (WM_APP + 100)
#define GCFDUI_UM_BEGIN_FORMATEX_DIALOG (WM_APP + 101)
#define GCFDUI_UM_END_FORMATEX_DIALOG   (WM_APP + 102)

#define GCFDUI_FDSTYLE_SIMPLE       (0x1 << 1)
#define GCFDUI_FDSTYLE_FILENAME     (0x1 << 2)
#define GCFDUI_FDSTYLE_DOUBLE       (0x1 << 3)
#define GCFDUI_FDSTYLE_DOUBLE_POINT (0x1 << 4)
#define GCFDUI_FDSTYLE_ALL          (0x1 << 5)

class GCUI_DLL_DECL CGcFdUiFormatDialog : public CGdUiDialog
{
  DECLARE_DYNAMIC(CGcFdUiFormatDialog)

public:
  CGcFdUiFormatDialog(CWnd* pParent, BOOL bNew);
  virtual ~CGcFdUiFormatDialog();

  virtual BOOL 	Create(CWnd* pParent);

  CGcFdUiFormatList* GetFormatList(void);
  CString    GetFormatType(void) const;
  BOOL       SetFormatType(LPCTSTR pszFormatType);
  int        GetCurrentFormat(CString& sDisplayName, CString& sFormatString, CString& sVersion) const;
  BOOL       SetCurrentFormat(LPCTSTR pszDisplayName, LPCTSTR pszFormatString);
  BOOL       SetFormatPreviewReadOnly(BOOL bReadOnly = TRUE);
  BOOL       SetFormatPreviewLabel(LPCTSTR pszText);
  BOOL       SetFormatPreviewText(LPCTSTR pszPreviewText, const GcValue& fieldValue);
  BOOL       SetDialogStyle(int nStyle);

protected:
  afx_msg void    OnLbnSelChangeFormatList(void);
  afx_msg void    OnEnChangePreview(void);
  afx_msg void    OnBnClickedFilenameOnly(void);
  afx_msg void    OnBnClickedPathOnly(void);
  afx_msg void    OnBnClickedPathAndFilename(void);
  afx_msg void    OnBnClickedIncludeExtension(void);
  afx_msg void    OnBnClickedFormatEx(void);
  afx_msg void    OnCbnSelChangePrecision(void);
  afx_msg void    OnCbnSelChangeDecimalSeparator(void);
  afx_msg void    OnCbnSelChangeListSeparator(void);
  afx_msg void    OnCbnEditChangeListSeparator(void);
  afx_msg void    OnBnClickedPointX(void);
  afx_msg void    OnBnClickedPointY(void);
  afx_msg void    OnBnClickedPointZ(void);
  afx_msg void    OnBnClickedAppendSymbol(void);
  afx_msg void    OnCbnSelChangeCurrencySymbol(void);
  afx_msg void    OnLbnSelChangeNegativeNumberList(void);
};