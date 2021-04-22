#if !defined(_GCHTMLAPI_H_INCLUDED_)
#define _GCHTMLAPI_H_INCLUDED_

#include "DbExport.h"
#if _MSC_VER >= 1000
#pragma once
#endif 

class CGdUiPaletteSet;

GCED_DLL_DECL int  gcedAddHTMLPalette(CGdUiPaletteSet* ps, const GCHAR* name, const GCHAR* uriOfHtmlPage);
GCED_DLL_DECL bool gcedShowHTMLModalWindow(HWND owner, const GCHAR* uriOfHtmlPage, bool persistSizeAndPosition = true);
GCED_DLL_DECL HWND gcedShowHTMLModelessWindow(HWND owner, const GCHAR* uriOfHtmlPage, bool persistSizeAndPosition = true);

struct HtmlWindowOptions {
  enum HtmlWindowFlags {
    eAllowResize = 0x0001,
    eAllowMinimize = 0x0002,
    eAllowMaximize = 0x0004,
    eInitPosition = 0x0008,
    eInitSize = 0x0010,
    eMaxSize = 0x0020,
    eMinSize = 0x0040,
    ePersistSizeAndPosition = 0x0080,
  };
  UINT flags;
  UINT x;
  UINT y;
  UINT width;
  UINT height;
  UINT maxWidth;
  UINT maxHeight;
  UINT minWidth;
  UINT minHeight;
};

GCED_DLL_DECL bool gcedShowHTMLModalWindow(HWND owner, const GCHAR* uriOfHtmlPage, HtmlWindowOptions opts);

class GcApDocWindow;
GCED_DLL_DECL GcApDocWindow* gcedAddHTMLDocWindow(const GCHAR* title, const GCHAR* uriOfHtmlPage);
GCED_DLL_DECL void gcedLoadJSScript(const GCHAR* pUriOfJSFile);
#endif 