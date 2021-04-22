#pragma once

#include "gcadstd.h"
#include "../DbLayoutManager.h"

GCDB_DLL_DECL Gcad::ErrorStatus gcdbDoSetupForLayouts(GcDbDatabase* pDatabase, Gsoft::ULongPtr& contextHandle);

GCDB_DLL_DECL Gcad::ErrorStatus gcdbClearSetupForLayouts(Gsoft::ULongPtr contextHandle);

GCDB_DLL_DECL Gcad::ErrorStatus gcdbDeleteLayout (const GCHAR* delname, GcDbDatabase* pDb = NULL);

GCDB_DLL_DECL Gcad::ErrorStatus gcdbRenameLayout (const GCHAR* oldname, const GCHAR* newname, GcDbDatabase* pDb = NULL);

GCDB_DLL_DECL Gcad::ErrorStatus gcdbCopyLayout (const GCHAR* copyname, const GCHAR* newname, GcDbDatabase* pDb = NULL);
