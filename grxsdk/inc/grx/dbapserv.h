#pragma once
#include "gcadstd.h"
#include "../OdArray.h"
#include "../RxObject.h"
#include "../DbHostAppServices.h"
#include "../DbBaseHostAppServices.h"
#include "../DbAppSystemVariables.h"
#include "../rxdlinkr.h"
#include "gcdb.h"

#define GcadInternalServices OdDbInternalServices
#define GcadInternalServices2 OdDbInternalServices2
#define gcdbSetBreak3dQueueForRegen oddbSetBreak3dQueueForRegen
#define gcdbSetHostApplicationServices oddbSetHostApplicationServices
#define gcdbSendInitialDwgFileOpenComplete oddbSendInitialDwgFileOpenComplete
#define gcdbTriggerAcadOctTreeReclassification oddbTriggerAcadOctTreeReclassification

GCDB_DLL_DECL int gcdbHostAppMinorVersion();

GCDB_DLL_DECL Gcad::ErrorStatus gcdbSetHostApplicationServices(GcDbHostApplicationServices * pServices);
