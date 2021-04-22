#pragma once
#include "GcFdUiFieldDialogHook.h"
class GCUI_DLL_DECL CGcFdUiFieldManager : public CObject
{
public:
  CGcFdUiFieldManager(void);
  ~CGcFdUiFieldManager(void);

  BOOL  RegisterFieldDialogHook(CGcFdUiFieldDialogHook* pDlgHook);
  BOOL  UnregisterFieldDialogHook(const CGcFdUiFieldDialogHook* pDlgHook);
  int   GetRegisteredDialogHooks(GcFdUiFieldDialogHookArray& hooks);
};