#pragma once
 
 class CGcUiNavDialog;

 typedef void(*FileDiaCallbackFuncPtr)(CGcUiNavDialog*);

 GCAD_PORT void gcedRegisterNavDialogCallbackFunction(FileDiaCallbackFuncPtr funcPtr);
 GCAD_PORT void gcedUnregisterNavDialogCallbackFunction(FileDiaCallbackFuncPtr funcPtr);