#pragma once
//#include "gcadstd.h"
//#include "gcdb.h"
//#include "dbmain.h"
//#include "../DbPointCloudObj/DbPointCloud.h"
#include "../DbPointCloudObj/OdPointCloud.h"

#define GcViewFrustum OdViewFrustum
#define GcPcPointFloat OdPcPointFloat
#define GcPcPointDouble OdPcPointDouble
#define GcPcPointAttributes OdPcPointAttributes
#define IGcPcDataBuffer IOdPcDataBuffer
#define IGcPcPointFilter IOdPcPointFilter
#define IGcPcPointFilter IOdPcPointFilter
#define IGcPcPointProcessor IOdPcPointProcessor
#define GcPointCloudViewFrustum OdPointCloudViewFrustum

#define gcdbCreatePointCloudEntity oddbCreatePointCloudEntity
#define gcdbAttachPointCloudExEntity oddbAttachPointCloudExEntity
#define gcdbAttachPointCloudEntity oddbAttachPointCloudEntity
#define gcdbModifyPointCloudDataView oddbModifyPointCloudDataView
#define gcdbResetPointCloudDataView oddbResetPointCloudDataView
#define gcdbSetPointCloudFilter oddbSetPointCloudFilter
#define gcdbProcessPointCloudData oddbProcessPointCloudData

