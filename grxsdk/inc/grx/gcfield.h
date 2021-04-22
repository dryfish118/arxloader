#pragma once
#include "gcadstd.h"
#include "dbmain.h"
#include "../FdField.h"

#define GcFdFieldEvaluator        OdFdFieldEvaluator
#define GcFdFieldEvaluatorLoader  OdFdFieldEvaluatorLoader
#define GcFdFieldResult           OdFdFieldResult

GCDB_DLL_DECL Gcad::ErrorStatus   gcdbAddFieldReactor     (GcFdFieldReactor* pReactor);
GCDB_DLL_DECL Gcad::ErrorStatus   gcdbRemoveFieldReactor  (GcFdFieldReactor* pReactor);

