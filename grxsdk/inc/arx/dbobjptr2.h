#pragma once
#include "../grx/dbobjptr2.h"
#include "acad2grx.h"

#define WritableAcDbObject WritableGcDbObject
#define ReadableAcDbObject ReadableGcDbObject
#define AcDbSmartObjectPointer GcDbSmartObjectPointer
#define accessAcDbObjectForRead accessGcDbObjectForRead
#define accessAcDbObjectForWrite  accessGcDbObjectForWrite
#define revertAcDbObjectFromWrite  revertGcDbObjectFromWrite
