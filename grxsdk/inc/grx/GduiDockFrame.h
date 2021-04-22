#pragma once
#include <afxpriv.h>                    
#include "gchar.h"
#include "gduiDock.h"
#include "gduiTheme.h"
#include "gdui.h"

class CGdUiThemeModifiedReactor;
class CGdUiDockControlBar;
class CGdUiTheme;
class CGdUiDockControlBar;

class CGdUiDockControlBarThemeModReactor : public CGdUiThemeModifiedReactor
{
public:
  CGdUiDockControlBarThemeModReactor(CGdUiDockControlBar* pDockControlBar) {};
  virtual void ThemeModified(const CGdUiTheme * pTheme, GdUiThemeElement element);
  void SetDockControlBar(CGdUiDockControlBar* pDockControlBar);

private:
  CGdUiDockControlBar * m_pDockControlBar;
};

class GDUI_PORT CGdUiPaletteSetDockFrame : public CMiniDockFrameWnd
{
  friend class CGdUiImpPaletteSet;
  friend class CGdUiDockDragContext;
  friend class CGdUiDockBarMutator;
  friend class CGdUiAnchorBar;

  DECLARE_DYNCREATE(CGdUiPaletteSetDockFrame)

public:
  CGdUiPaletteSetDockFrame();
  virtual ~CGdUiPaletteSetDockFrame();

  virtual BOOL Create(CWnd* pParent, DWORD dwBarStyle);
  static bool HidePalettes();
  static bool ShowPalettes();

public:
  enum ContainedBarType
  {
    Unknown,
    Standard,
    GsftBar
  };

  enum ContainedBarType GetContainedBarType();

  void SetAutoRollup(BOOL bSet);

  virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);

  typedef enum
  {
    kLeft = 0,
    kRight
  } GdUiTitleBarLocation;

  CGdUiPaletteSetDockFrame::GdUiTitleBarLocation TitleBarLocation();
  void SetTitleBarLocation(CGdUiPaletteSetDockFrame::GdUiTitleBarLocation);
protected:
  enum ContainedBarType m_nContainedBarType;
  bool m_bZOrderChanged;

  bool CanFrameworkTakeFocus();
  void ForceChildRepaint();
  void UpdateThemeElements();

protected:
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
  virtual BOOL PreTranslateMessage(MSG * msg);

  afx_msg int     OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void    OnDestroy();
  afx_msg void    OnSize(UINT nType, int cx, int cy);
  afx_msg void    OnClose();
  afx_msg void    OnLButtonDown(UINT nHitTest, CPoint pt);
  afx_msg void    OnNcLButtonDown(UINT nHitTest, CPoint pt);
  afx_msg void    OnNcRButtonDown(UINT nHitTest, CPoint pt);
  afx_msg void    OnNcRButtonUp(UINT nHitTest, CPoint pt);
  afx_msg void    OnNcLButtonUp(UINT nHitTest, CPoint pt);
#if _MSC_VER<1400
  afx_msg UINT    OnNcHitTest(CPoint point);
#else
  afx_msg LRESULT OnNcHitTest(CPoint point);
#endif
  afx_msg void    OnMouseMove(UINT nHitTest, CPoint pt);
  afx_msg void    OnNcMouseMove(UINT nHitTest, CPoint pt);
  afx_msg int     OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
  afx_msg void    OnWindowPosChanging(WINDOWPOS* lpwndpos);
  afx_msg void    OnPaint();
  afx_msg void    OnNcPaint();
  afx_msg LRESULT OnDisplayChange(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnNcCalcSize(WPARAM wParam, LPARAM lParam);
  afx_msg void    OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
  afx_msg BOOL    OnNcActivate(BOOL bActive);
  afx_msg void    OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
  afx_msg void    OnSizing(UINT nSide, LPRECT pRect);
  afx_msg void    OnShowWindow(BOOL bShow, UINT nStatus);
  afx_msg BOOL    OnSetCursor(CWnd *pwnd, UINT nHitTest, UINT msg);
  afx_msg void    OnSetFocus(CWnd * pOldWnd);
  afx_msg void    OnTimer(UINT_PTR nIdEvent);
  afx_msg void    OnContextMenu(CWnd* pWnd, CPoint pos);
  afx_msg BOOL    OnEraseBkgnd(CDC* pDC);
  afx_msg LRESULT OnEnterSizeMove(WPARAM, LPARAM);
  afx_msg LRESULT OnExitSizeMove(WPARAM, LPARAM);
  afx_msg void    OnSettingChange(UINT uFlags, LPCTSTR lpszSection);

  virtual LRESULT OnDragEnter(WPARAM wParam, LPARAM lParam);
  virtual LRESULT OnDragOver(WPARAM wParam, LPARAM lParam);
  virtual LRESULT OnDrop(WPARAM wParam, LPARAM lParam);
  virtual LRESULT OnDropEx(WPARAM wParam, LPARAM lParam);
  virtual LRESULT OnDragLeave(WPARAM wParam, LPARAM lParam);
  virtual LRESULT OnDragScroll(WPARAM wParam, LPARAM lParam);

  bool CanGstarCADTakeFocus();

  BOOL HitTest(CPoint pt, UINT& nFlag, DWORD& dwData);

  CGdUiPaletteSet* GetPaletteSet();

  DECLARE_MESSAGE_MAP()

private:
  enum GdUiSkBtnItems
  {
    kBtnUnknown = -1,
    kBtnPushPin = 0,
    kBtnOptionMenu = 1,
    kBtnClose = 2,
    kBtnIcon = 3,
  };

  enum GdUiSkIds
  {
    kRollupTimerId = 0x3011,
    kRolloutTimerId = 0x3012,
    kCursorCheckTimerId = 0x3013
  };

  enum AdUiSkUiFlags
  {
    kImgListUnpinnedLeft = 0,
    kImgListUnpinnedRight = 1,
    kImgListPinnedLeft = 2,
    kImgListPinnedRight = 3,
    kImgListOptionMenuLeft = 4,
    kImgListOptionMenuRight = 5,
    kImgListClose = 6,
    kImgList_Count = 7,
  };

};

void GDUI_PORT GdUiSaveDockingToolPositions();
void GDUI_PORT GdUiShowDockControlBars(bool bShow);
bool GDUI_PORT GdUiRegisterDockingTool(LPCTSTR lpszToolName, LPCTSTR lpszCommand, UINT nToolbarID);

typedef HRESULT GDUI_LOADFN(IUnknown** ppIdUiRootNode);
typedef HRESULT GDUI_SAVEFN(IUnknown* pIdUiRootNode);

void GDUI_PORT GdUiEnableDocking(CFrameWnd *pFrame, DWORD dwDockStyle, GDUI_LOADFN* pLoadFcn, GDUI_SAVEFN* pSaveFcn);

bool GDUI_PORT CanStealFocusFromDockedWindow();
void GDUI_PORT GetSystemVirtualScreen(RECT &rect);
void GDUI_PORT GdUiEnableDockControlBars(BOOL bEnable, CStringArray* pToolIds = NULL);



