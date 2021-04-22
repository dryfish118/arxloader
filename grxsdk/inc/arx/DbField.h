#pragma once
#include "../grx/DbField.h"
#include "../grx/DbFieldTodo.h"
#include "acad2grx.h"

#define AcHyperlink  GcHyperlink
#define AcFd  GcFd

#define acdbGetFieldEngine                gcdbGetFieldEngine
#define acdbGetFieldMarkers               gcdbGetFieldMarkers
#define acdbHasFields                     gcdbHasFields
#define acdbFindField                     gcdbFindField
#define acdbEvaluateFields                gcdbEvaluateFields
#define acdbConvertFieldsToText           gcdbConvertFieldsToText
#define acdbMakeFieldCode                 gcdbMakeFieldCode
