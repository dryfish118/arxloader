#pragma once
#include "../grx/gcgs.h"
#include "acad2grx.h"
#include "acgidefs.h"
#include "acgitransient.h"

#define AcGs GcGs
#define acgsCustomUpdateMethod gcgsCustomUpdateMethod

#define acgsSetHighlightStyle    gcgsSetHighlightStyle
#define acgsGetHighlightStyle    gcgsGetHighlightStyle
#define acgsGetCurrentAcGsView   gcgsGetCurrentGcGsView
#define acgsGetCurrent3dAcGsView gcgsGetCurrent3dGcGsView
#define acgsObtainAcGsView       gcgsObtainGcGsView
#define acgsDrawableCached       gcgsDrawableCached
#define acgsGetGsHighlightModel  gcgsGetGsHighlightModel
#define acgsSetGsModel           gcgsSetGsModel
#define acgsSetGsHighlightModel  gcgsSetGsHighlightModel
