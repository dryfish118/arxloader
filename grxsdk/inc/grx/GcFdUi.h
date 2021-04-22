#pragma once
#include "gcadstd.h"
#include "DbField.h"
#include <afxwin.h>

class CGcFdUiFieldManager;

#define GCFDUI_CATEGORY_ID_ALL              -1
#define GCFDUI_CATID_USER_FIRST             1000
#define GCFDUI_FIELDID_USER_FIRST           50000

GCUI_DLL_DECL CGcFdUiFieldManager* GcFdUiGetFieldManager(void);

GCUI_DLL_DECL int GcFdUiInvokeFieldDialog(GcDbField*& pNewField, BOOL bEdit, GcDbDatabase* pDb, CWnd* pParent = NULL);