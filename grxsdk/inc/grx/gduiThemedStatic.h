#if !defined(_GDUITHEMEDSTATIC_H__)
#define _GDUITHEMEDSTATIC_H__

#if _MSC_VER > 1000
#pragma once
#endif 

class GDUI_PORT CGdUiThemedStatic : public CStatic
{
    DECLARE_DYNAMIC(CGdUiThemedStatic)
public:
    CGdUiThemedStatic();

    CGdUiThemedStatic(const CString & themeName);

    virtual ~CGdUiThemedStatic();

    CString GetThemeName() const;

    bool SetThemeName(const CString & themeName);

    HBITMAP SetBitmap(HBITMAP hBitmap);

    HICON SetIcon(HICON hIcon);

    virtual void PreSubclassWindow();

protected:
    void Initialize();

    afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
    DECLARE_MESSAGE_MAP()

private:
    CString mThemeName;             
    CBrush mBackgroundBrush;
};


#endif 
