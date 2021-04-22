#pragma once
#include "../grx/dbmain.h"
#include "../grx/gcdbgds.h"
#include "acad2grx.h"
#include "PAL/api/AcLocale.h"

#define AcDbDataLinkManager  GcDbDataLinkManager
#define AcDwgFileHandle      GcDwgFileHandle
#define AcDbUndoController   GcDbUndoController
#define AcCmComplexColor     GcCmComplexColor
#define AcCmColorBase        GcCmColorBase
#define AcCmHSB              GcCmHSB

#define acdbValidateSetup         gcdbValidateSetup
#define acdbCleanUp               gcdbCleanUp
#define acdbSetDefaultOdGiContext gcdbSetDefaultOdGiContext
#define acdbGetThumbnailBitmapFromDxfFile gcdbGetThumbnailBitmapFromDxfFile

#define acdbSetDefaultAcGiContext gcdbSetDefaultAcGiContext

