#pragma once
#include "../grx/GcFdUi.h"
#include "acad2grx.h"

#include "AcFdUiFieldManager.h"

#define ACFDUI_CATEGORY_ID_ALL    GCFDUI_CATEGORY_ID_ALL
#define ACFDUI_CATID_USER_FIRST   GCFDUI_CATID_USER_FIRST
#define ACFDUI_FIELDID_USER_FIRST GCFDUI_FIELDID_USER_FIRST

#define AcFdUiGetFieldManager     GcFdUiGetFieldManager
#define AcFdUiInvokeFieldDialog   GcFdUiInvokeFieldDialog
#define CAcFdUiFieldManager       CGcFdUiFieldManager