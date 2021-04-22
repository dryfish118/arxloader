#ifndef __GCTCUITOOLPALETTE_H__
#define __GCTCUITOOLPALETTE_H__


#if _MSC_VER > 1000
#pragma once
#endif 

#include "GcTcUI.h"
#include "gduiPalette.h"
#include "GcTcUiPaletteView.h"

class CGcTcUiImpToolPalette;
class GcTcUiSystemInternals;
class CGcTcUiScheme;

#ifndef _GSOFT_MAC_
class GCTCUI_PORT CGcTcUiToolPalette : public CGdUiPalette
{
  friend CGcTcUiImpToolPalette;

  DECLARE_DYNCREATE(CGcTcUiToolPalette);

public:
  CGcTcUiToolPalette();
  virtual ~CGcTcUiToolPalette();

  CGcTcUiPaletteView* GetView(void);

public:
  virtual BOOL   Create(CGdUiPaletteSet* pParent);
  BOOL           Create(DWORD dwStyle, LPCTSTR pszName, CGdUiPaletteSet* pParent, DWORD dwPaletteStyle = 0);
  virtual BOOL   Load(IUnknown* pUnk);
  virtual bool   CanFrameworkTakeFocus();
  virtual BOOL   Save(IUnknown* pUnk);
  virtual BOOL   Import(IUnknown* pUnk, LPCTSTR pszRefPath);
  virtual BOOL   Export(IUnknown* pUnk, LPCTSTR pszRefPath);
  virtual BOOL   OnKillActive(void);
  virtual BOOL   GetMinimumSize(CSize& size);
  virtual void   OnSetActive(void);
  virtual BOOL   NameEditValidation(CEdit* pEdit);
  virtual BOOL   Paste(IDataObject* pDataObject, int iIndex = -1, GcTcCatalogItemArray* pNewTools = NULL);
  virtual BOOL   CanPaste(IDataObject* pDataObject);
  BOOL           SetView(CGcTcUiPaletteView* pView);
  CGcTcUiScheme* GetScheme(void) const;

protected:
  afx_msg void    OnSize(UINT nType, int cx, int cy);
  afx_msg int     OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void    OnSetFocus(CWnd* pOldWnd);
  afx_msg void    OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg LRESULT OnDragEnter(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnDragOver(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnDragLeave(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnDrop(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnDropEx(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnUpdate(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnEndNameEdit(WPARAM, LPARAM);
  DECLARE_MESSAGE_MAP()

protected:
  void            *   mpImpObj;

private:
  friend class GcTcUiSystemInternals;
};

#endif 
#endif 