#pragma once
#include "gcadstd.h"
#include "../DbUnderlayHost.h"

//dbunderlayhostTodo.cpp
GCDB_DLL_DECL OdDbUnderlayHost* gcdbGetCurrentDgnDocHost();
GCDB_DLL_DECL OdDbUnderlayHost* gcdbSetCurrentDgnDocHost(OdDbUnderlayHost* pHost);
GCDB_DLL_DECL bool gcdbIsDgnToDwgInProgress();
GCDB_DLL_DECL OdDbUnderlayHost* gcdbGetCurrentPdfHost();
GCDB_DLL_DECL OdDbUnderlayHost* gcdbSetCurrentPdfHost(OdDbUnderlayHost* pHost);

//ODA
#define gcdbGetCurrentDgnHost oddbGetCurrentDgnHost
#define GcDbUnderlayHost OdDbUnderlayHost
#define GcDbUnderlayDrawContext OdDbUnderlayDrawContext
#define GcDbDgnUnderlayItem OdDbDgnUnderlayItem
#define gcdbSetCurrentDwfHost oddbSetCurrentDwfHost
#define gcdbSetCurrentDgnHost oddbSetCurrentDgnHost
