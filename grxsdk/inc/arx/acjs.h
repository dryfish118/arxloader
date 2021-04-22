#pragma once
#include "../grx/gcjs.h"
#include "acad2grx.h"

#define AcJsFunctionPtr GcJsFunctionPtr

#define acjsDefun        gcjsDefun
#define acjsInvokeAsync  gcjsInvokeAsync
#define acjsInvokeAsyncA gcjsInvokeAsyncA

#define ACJS_FUNC_INVOKEINDOC    GCJS_FUNC_INVOKEINDOC
#define ACJS_FUNC_HANDLE_NULLDOC GCJS_FUNC_HANDLE_NULLDOC
#define ACJSCORESTUB_DEFUN       GCJSCORESTUB_DEFUN
