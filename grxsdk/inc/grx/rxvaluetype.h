#pragma once
#include "../RxValueType.h"
#include "rxmember.h"
#include "gcbasedefs.h"

#ifdef NDEBUG
#define GCRXVALUE_ASSERT(x)
#else
#define GCRXVALUE_ASSERT(x) if (!(x)) gcutAssertMessage(GCRX_T(#x), GCRX_T(__FILE__), __LINE__, 0 ); else
#endif

#define Storage OdRxValueStorage
#define GcRxValueType OdRxValueType
#define IGcRxObjectValue IOdRxObjectValue
#define IGcRxEnumeration IOdRxEnumeration
#define IGcRxReferenceType IOdRxReferenceType
#define IGcRxNonBlittableType IOdRxNonBlittableType
