#ifndef _GduiButton_h
#define _GduiButton_h
#pragma pack (push, 8)

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "gdUiTheme.h"  // INTERNAL USE ONLY
//#include "gdui.h"

class CGdUiOwnerDrawButton;
class CGdUiTrackButtonDraw;

class CGdUiODButtonThemeModReactor : public CGdUiThemeModifiedReactor  // INTERNAL USE ONLY
{
public:
    CGdUiODButtonThemeModReactor(CGdUiOwnerDrawButton* pBtn);  // INTERNAL USE ONLY
    virtual void ThemeModified(const CGdUiTheme * pTheme, GdUiThemeElement element);  // INTERNAL USE ONLY

private:
    CGdUiOwnerDrawButton * m_pBtn;
};


/////////////////////////////////////////////////////////////////////////////
// CGdUiOwnerDrawButton
#pragma warning(push)
#pragma warning(disable : 4275)
class GDUI_PORT CGdUiOwnerDrawButton : public CButton {
  friend class CGdUiODButtonThemeModReactor;  // INTERNAL USE ONLY

  DECLARE_DYNAMIC(CGdUiOwnerDrawButton)

public:
  CGdUiOwnerDrawButton ();
  virtual         ~CGdUiOwnerDrawButton ();

protected:
  CPoint  m_lastMousePoint;
  CRect   m_tipRect;
  CGdUiTheme * m_pTheme;  // INTERNAL USE ONLY

// GdUi message handler
protected:
  CWnd    *m_gduiParent;

  virtual GDUI_REPLY DoGdUiMessage (
    GDUI_NOTIFY notifyCode, UINT controlId, LPARAM lParam
    );
  virtual void    OnDrawTip (CDC& dc);
  virtual BOOL    OnDrawTipText (CGdUiDrawTipText& dtt);
  virtual GDUI_REPLY OnGetTipSupport (CPoint& p);
  virtual BOOL    OnGetTipRect (CRect& r);
  virtual BOOL    OnGetTipText (CString& text);
  virtual BOOL    OnHitTipRect (CPoint& p);
public:
  CWnd    *GetGdUiParent ();
  void    SetGdUiParent (CWnd *w);

  virtual void    SetTracking(BOOL b) { m_bIsTrackButton = b; };
  virtual CGdUiTheme * SetTheme(CGdUiTheme *pTheme);  // INTERNAL USE ONLY

  // Owner Draw routines
protected:
  static const UINT_PTR m_timerEvent;
  bool    m_bEnableDragDrop   : 1;
  bool    m_bEnableFastDraw   : 1;
  bool    m_bEnablePointedAt  : 1;
  bool    m_bIsPointedAt      : 1;
  bool    m_bIsStatic         : 1;
  bool    m_bIsToolButton     : 1;
  bool    m_bIsTrackButton    : 1;
  UINT_PTR  m_timerId;

  // members added for XP look and feel
  int     m_nPartId;
  int     m_nStateId;
  UINT    m_uEdge;
  BOOL    m_bMouseHover;

  virtual void    DrawBorder(CDC *pDC,CRect &r,COLORREF cr);
  virtual void    DrawHotBorder();
  virtual void    DrawButton(
    CDC& dc, int w, int h,
    BOOL isDefault,
    BOOL isDisabled,
    BOOL isSelected,
    BOOL isFocused
    );
  virtual void    DrawPushButtonBorder (
    CDC& dc, CRect& rButton, BOOL isDefault, BOOL isSelected
    );
  virtual void    DrawToolButtonBorder (
    CDC& dc, CRect& rButton, BOOL isSelected, BOOL isFocused
    );
  void    DrawTransparentBitmap (
    CDC& dc,
    CBitmap& bmp,
    int x, int y, int w, int h,
    BOOL isDisabled
    );
  void    DrawContentText (
    CDC& dc,
    CString sText,
    CRect& rcText,
    BOOL isDisabled
    );
  BOOL    GetIsPointedAt ();
  void    SetIsPointedAt (BOOL isPointedAt);
  virtual BOOL    OnAutoLoad ();
  virtual void    OnDragDrop (HDROP hDropInfo);
  virtual void    OnPointedAt (BOOL isPointedAt);
  virtual BOOL    OnReload (LPCTSTR strResId);
  void    StartTimer (DWORD ms=50);
  void    StopTimer ();


  virtual void ThemeModified(GdUiThemeElement element);  // INTERNAL USE ONLY
public:
  BOOL    AutoLoad ();
  BOOL    GetEnableDragDrop ();
  void    SetEnableDragDrop (BOOL allow);
  BOOL    GetEnableFastDraw ();
  void    SetEnableFastDraw (BOOL allow);
  BOOL    GetEnablePointedAt ();
  void    SetEnablePointedAt (BOOL allow);
  BOOL    GetIsStatic ();
  void    SetIsStatic (BOOL isStatic);
  BOOL    GetIsToolButton ();
  void    SetIsToolButton (BOOL isToolButton);
  BOOL    Reload (LPCTSTR strResId);

  // ClassWizard-controlled
public:
  //{{AFX_VIRTUAL(CGdUiOwnerDrawButton)
public:
  virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
  virtual void PreSubclassWindow();
  //}}AFX_VIRTUAL

protected:
  //{{AFX_MSG(CGdUiOwnerDrawButton)
  afx_msg LRESULT OnGdUiMessage (WPARAM wParam, LPARAM lParam);
  afx_msg void OnDropFiles(HDROP hDropInfo);
  afx_msg UINT OnGetDlgCode();
  afx_msg void OnKillFocus(CWnd* pNewWnd);
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg LRESULT OnMouseLeave(WPARAM, LPARAM);
  afx_msg void OnNcDestroy();
  afx_msg void OnSetFocus(CWnd* pOldWnd);
  afx_msg void OnTimer(UINT_PTR nIDEvent);
  afx_msg void OnDestroy( );
  afx_msg LRESULT OnThemeChanged(WPARAM wParam, LPARAM lParam);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP()
protected:
  HANDLE GetVisualStylesTheme() {return m_hVS;}
private:
  CGdUiODButtonThemeModReactor* m_pThemeModReactor;  // INTERNAL USE ONLY
  HANDLE    m_hVS;               // INTERNAL USE ONLY
};
#pragma warning(pop)
/////////////////////////////////////////////////////////////////////////////
// CGdUiBitmapButton

class GDUI_PORT CGdUiBitmapButton : public CGdUiOwnerDrawButton 
{
    DECLARE_DYNAMIC(CGdUiBitmapButton)

    friend class CGdUiImpBitmapButton;
public:
    CGdUiBitmapButton ();
    virtual ~CGdUiBitmapButton ();

    enum Constants
    {
        ThemedSize = 24,
    };

    BOOL GetAutoSizeToBitmap ();
    void SetAutoSizeToBitmap (BOOL autoSizeToBitmap);
    void SizeToBitmap ();
    bool SetBitmapOffsets(int nBorderOffset, int nFocusRectOffset);

    virtual BOOL IsThemed() const;

    virtual void SetIsThemed(BOOL isThemed);

    virtual void EnableThemedState(BOOL bEnableHover, BOOL bEnableClick);
    
    virtual CGdUiTheme * SetTheme(CGdUiTheme *pTheme);

    virtual void SetThemeBackground(GdUiThemeElement nElement);

    enum ImageDrawStyle
    {
        kImageDrawStyle_Default              = 0x0,
        kImageDrawStyle_Static               = 0x1,
        kImageDrawStyle_Center               = 0x2,
        kImageDrawStyle_Stretch_BtnSize      = 0x3,
    };

    ImageDrawStyle GetImageDrawStyle() const;

    void SetImageDrawStyle(ImageDrawStyle style);

    BOOL LoadBitmap (LPCTSTR strResId);

protected:
    virtual void  DrawButton(CDC& dc, int w, int h,
                             BOOL isDefault,
                             BOOL isDisabled,
                             BOOL isSelected,
                             BOOL isFocused);
    virtual void DrawButtonImage(CDC* pDC, const CRect& rect, BOOL isSelected, BOOL isDisabled);
    virtual void DrawFocusMark(CDC* pDC, CRect& rect, BOOL isDefault, BOOL isSelected, BOOL isFocused);
    virtual BOOL OnAutoLoad ();
    virtual BOOL OnReload (LPCTSTR strResId);

    virtual void DrawThemedButton(CDC& dc, int x, int y, int width, int height, int statusId);

    virtual void ThemeModified(GdUiThemeElement element);

    enum ImageType
    {
        kImageType_Undefined,
        kImageType_Bitmap,
        kImageType_Icon,
        kImageType_RCDATA
    };

    BOOL LoadIconResource(LPCTSTR strResId, HINSTANCE hInst = NULL);

    BOOL LoadRCDATAResource(LPCTSTR strResId, HINSTANCE hInst = NULL);

    BOOL LoadBitmapResource (LPCTSTR strResId, CBitmap& bmp, HINSTANCE hInst = NULL);

    virtual BOOL OnLoadBitmap (LPCTSTR strResId);

    void ClearImages(bool bClearResId = false);

    void CalcBitmapSize();

    void SaveAndCalcSize(LPCTSTR strResId, ImageType type);

    BOOL    m_bAutoSizeToBitmap;
    CBitmap m_bmp;
    void *  m_image;
    CString m_bmpResId;
    int     m_bmpHeight;
    int     m_bmpWidth;
    int     m_bmpX;
    int     m_bmpY;
    int     m_focusRectOffset;
    BOOL    m_isThemed;
    BOOL    m_enableThemedHoverState;
    BOOL    m_enableThemedClickState;
    GdUiThemeElement m_backgroundElement; 
    ImageType m_imageType;
    ImageDrawStyle m_imageDrawStyle;

public:

protected:

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGdUiBitmapStatic

class GDUI_PORT CGdUiBitmapStatic : public CGdUiBitmapButton {
	DECLARE_DYNAMIC(CGdUiBitmapStatic)

public:
	            CGdUiBitmapStatic ();
 virtual         ~CGdUiBitmapStatic ();

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CGdUiBitmapStatic)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CGdUiBitmapStatic)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGdUiDropSite

class GDUI_PORT CGdUiDropSite : public CGdUiBitmapStatic {
	DECLARE_DYNAMIC(CGdUiDropSite)

public:
	            CGdUiDropSite ();
 virtual         ~CGdUiDropSite ();

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CGdUiDropSite)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CGdUiDropSite)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGdUiToolButton

class GDUI_PORT CGdUiToolButton : public CGdUiBitmapButton {
	DECLARE_DYNAMIC(CGdUiToolButton)

public:
	            CGdUiToolButton ();
 virtual         ~CGdUiToolButton ();

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CGdUiToolButton)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CGdUiToolButton)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGdUiTrackButton

class GDUI_PORT CGdUiTrackButton : public CGdUiOwnerDrawButton {
	DECLARE_DYNAMIC(CGdUiTrackButton)

public:
	            CGdUiTrackButton();
                CGdUiTrackButton(const CGdUiTrackButtonDraw & pDraw);
 virtual         ~CGdUiTrackButton();

// ClassWizard-controlled
public:
	//{{AFX_VIRTUAL(CGdUiTrackButton)
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

virtual CGdUiTheme * GetTheme() const;
 virtual CGdUiTheme * SetTheme(CGdUiTheme *pTheme);  // INTERNAL USE ONLY

static  CGdUiTrackButtonDraw * SetDefaultDraw(CGdUiTrackButtonDraw * pDraw);
        CGdUiTrackButtonDraw * SetDraw(CGdUiTrackButtonDraw * pDraw);

virtual void    SetTracking(BOOL b);

protected:
virtual void    DrawButton(
                    CDC& dc, int w, int h,
	                BOOL isDefault,
	                BOOL isDisabled,
                    BOOL isSelected,
	                BOOL isFocused
                );
virtual void    DrawBorder(CDC *pDC,CRect &r,COLORREF cr);
virtual void    DrawHotBorder();
virtual void    DrawPushButtonBorder (CDC& dc, CRect& rButton, BOOL isDefault, BOOL isSelected);
virtual void    DrawToolButtonBorder (CDC& dc, CRect& rButton, BOOL isSelected, BOOL isFocused);

virtual GDUI_REPLY OnGetTipSupport (CPoint& p);

	//{{AFX_MSG(CGdUiTrackButton)
    afx_msg void OnNcPaint();
    afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

     virtual void releaseDraw();

// Implementation
private:
    static CGdUiTrackButtonDraw * s_pDefaultDraw;
    CGdUiTrackButtonDraw * m_pDraw;

};

class GDUI_PORT CGdUiBitmapTextButton : public CGdUiBitmapButton 
{
    friend class CGdUiImpBitmapButton;
    DECLARE_DYNAMIC(CGdUiBitmapTextButton)
public:
    enum ButtonType
    {
        kBitmap = 0x1,
        kText = 0x2,
    };

    enum BitmapLocation
    {
        kLeft = 0x1,
        kTop = 0x2,
        kRight = 0x4,
        kBottom = 0x8,
    };

	enum ButtonStyle
	{
		kButtonStyleNone  = 0,
		kButtonStyleFlat  = 0x1,
		kButtonStyleCheck = 0x2,

		kButtonHCenter     = 0x00000300,
		kButtonVCenter    = 0x00000C00,
	};
 
public:
    CGdUiBitmapTextButton();
    virtual ~CGdUiBitmapTextButton();

protected:
    virtual void DrawButton(
        CDC& dc, int w, int h,
        BOOL isDefault,
        BOOL isDisabled,
        BOOL isSelected,
        BOOL isFocused
        );
    virtual BOOL OnAutoLoad ();
    virtual BOOL OnReload (LPCTSTR strResId);
    virtual BOOL OnLoadBitmap (LPCTSTR strResId);

public:
  BOOL                GetAutoSizeToContent();
  void                SetAutoSizeToContent(BOOL autoSizeToContent);
  void                SizeToContent();
  void                SetContentOffsets(int nBorderOffset,
    int nFocusRectOffset);
  UINT                GetButtonType();
  UINT                GetBitmapLocation();
  UINT                SetButtonType(UINT btnType);
  UINT                SetBitmapLocation(UINT imgPos);

  ButtonStyle			GetBitmapTextButtonStyle() const;
  void				SetBitmapTextButtonStyle(ButtonStyle nBtnStyle);

  DECLARE_MESSAGE_MAP()
public:
    BOOL				GetAutoSizeToBitmap ();
    void				SetAutoSizeToBitmap (BOOL autoSizeToBitmap);
    void				SizeToBitmap ();
    void				SetBitmapOffsets(int nBorderOffset, int nFocusRectOffset);
	
	void				SetBkColor(COLORREF);
	void				SetBorderColor(COLORREF);

	void				SetCheck(int nCheck);
	int					GetCheck();

	HICON				SetIcon(HICON hIcon, BOOL bRedraw = TRUE);
	HICON				GetIcon() const;
	HBITMAP				SetBitmap(HBITMAP hBitmap, BOOL bRedraw = TRUE);
	HBITMAP				GetBitmap() const;
private:
    void*               mpImpObj;
};

class GDUI_PORT CGdUiThemedDropDownBitmapButton : public CGdUiBitmapButton
{
    DECLARE_DYNAMIC(CGdUiThemedDropDownBitmapButton)
public:
    enum
    {
        BitmapButtonSize = 24,
        MenuButtonWidth = 15,
    };
    CGdUiThemedDropDownBitmapButton();
    virtual ~CGdUiThemedDropDownBitmapButton();

    BOOL            GetMainButtonSelected ();

    void            SetMainButtonSelected (BOOL selected);

    BOOL            GetMenuButtonSelected ();

    void            SetMenuButtonSelected (BOOL selected);
    
    void            ClearClick ();

    virtual int     GetMenuButtonWidth ();

    virtual bool    SetMenuButtonWidth(int width);

protected:
    BOOL    m_bMainButtonSelected;              
    BOOL    m_bMenuButtonSelected;              
    int     m_menuButtonWidth;                  

protected:
    virtual void DrawButton(CDC& dc, int w, int h, BOOL isDefault, BOOL isDisabled, BOOL isSelected, BOOL isFocused);

    afx_msg void OnKeyDown (UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKillFocus (CWnd *pNewWnd);
    afx_msg void OnLButtonDown (UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp (UINT nFlags, CPoint point);
    afx_msg void OnSysKeyDown (UINT nChar, UINT nRepCnt, UINT nFlags);

    DECLARE_MESSAGE_MAP()
};


#pragma pack (pop)
#endif

//////////////////////////////////////////////////////////////////////////////
