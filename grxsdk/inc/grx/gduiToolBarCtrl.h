﻿#if !defined(_GDUITOOLBARCTRL_H__)
#define _GDUITOOLBARCTRL_H__

#if _MSC_VER > 1000
#pragma once
#endif 

#define GDUI_TBSTYLE_AUTOSTRETCH 0x00080000

class GDUI_PORT CGdUiToolBarCtrl : public CToolBarCtrl
{
    DECLARE_DYNAMIC(CGdUiToolBarCtrl)
public:
    CGdUiToolBarCtrl();

    virtual ~CGdUiToolBarCtrl();

    int AddBitmap(int nNumButtons, UINT nBitmapID);

    int AddBitmap(int nNumButtons, CBitmap* pBitmap);

protected:
    afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
    DECLARE_MESSAGE_MAP()

private:
    CBitmap *m_pBmp;
    void UpdateBitmap(const CBitmap& bmp);
};


#endif 
