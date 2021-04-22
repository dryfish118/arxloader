#pragma once
#include "gcadstd.h"
#include "../Gi/GiUtils.h"

#include "dbid.h"
#include "GdGChar.h"
#include "gcgi.h"

Gcad::ErrorStatus fromGcDbTextStyle(GcGiTextStyle&, const GcDbObjectId& GcDbStyleId);
Gcad::ErrorStatus fromGcDbTextStyle(GcGiTextStyle&, const GCHAR * GcDbStyleName);

Gcad::ErrorStatus toGcDbTextStyle(GcGiTextStyle&);

Gcad::ErrorStatus toGcDbTextStyle(GcGiTextStyle&, GcDbObjectId& GcDbStyleId);

Gcad::ErrorStatus toGcDbTextStyle(const GcDbObjectId GcDbStyleId, GcGiTextStyle&);

Gcad::ErrorStatus toGcDbTextStyle(GcGiTextStyle&, const GCHAR * GcDbStyleName);

Gcad::ErrorStatus toGcDbTextStyle(GcGiTextStyle&, const GCHAR * GcDbStyleName, GcDbObjectId& GcDbStyleId);
