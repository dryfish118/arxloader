#pragma once
#include "../grx/dbunderlayhost.h"
#include "acad2grx.h"

//dbunderlayhostTodo
#define acdbGetCurrentDgnDocHost gcdbGetCurrentDgnDocHost//gcad
#define acdbSetCurrentDgnDocHost gcdbSetCurrentDgnDocHost//gcad
#define acdbIsDgnToDwgInProgress gcdbIsDgnToDwgInProgress//gcad
#define acdbGetCurrentPdfHost gcdbGetCurrentPdfHost//gcad
#define acdbSetCurrentPdfHost gcdbSetCurrentPdfHost//gcad

//dbunderlayhost
#define AcDbUnderlayHost GcDbUnderlayHost
#define AcDbUnderlayDrawContext GcDbUnderlayDrawContext
#define AcDbDgnUnderlayItem GcDbDgnUnderlayItem

#define acdbSetCurrentDwfHost gcdbSetCurrentDwfHost
#define acdbSetCurrentDgnHost gcdbSetCurrentDgnHost