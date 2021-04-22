#pragma once

#include "GcTcUiCatalogView.h"

#ifndef _GSOFT_MAC_
class GCTCUI_PORT CGcTcUiPaletteView : public CGcTcUiCatalogView
{
public:
  CGcTcUiPaletteView();
  virtual ~CGcTcUiPaletteView();

protected:
  virtual DROPEFFECT  DragEnter(GDUI_DRAGDATA* pDragData);
  virtual DROPEFFECT  DragOver(GDUI_DRAGDATA* pDragData);
  virtual void        DragLeave(GDUI_DRAGDATA* pDragData);
  virtual DROPEFFECT  Drop(GDUI_DRAGDATA* pDragData);
  virtual DROPEFFECT  DropEx(GDUI_DRAGDATA* pDragData);

protected:
  CGcTcUiPaletteView(GcTcUiSystemInternals*);

protected:
  afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnInvokeCommand(UINT nID);
  afx_msg void OnPaletteRemove();
  afx_msg void OnCatalogItemSpecifyImage();
  afx_msg void OnCatalogItemRemoveImage();
  afx_msg void OnCatalogItemUpdateImage();
  DECLARE_MESSAGE_MAP()
};
#endif 
