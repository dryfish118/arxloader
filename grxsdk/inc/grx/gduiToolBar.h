#if !defined(_GDUITOOLBAR_H__)
#define _GDUITOOLBAR_H__

#if _MSC_VER > 1000
#pragma once
#endif 

#include "gduiToolBarCtrl.h"

class GDUI_PORT CGdUiToolBar : public CToolBar
{
    DECLARE_DYNAMIC(CGdUiToolBar)
public:
    CGdUiToolBar();

    virtual ~CGdUiToolBar();

    BOOL LoadToolBar(LPCTSTR lpszResourceName);

    BOOL LoadToolBar(UINT nIDResource);
	
protected:
    afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
    DECLARE_MESSAGE_MAP()
};


#endif 
