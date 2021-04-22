#pragma once

#include <stddef.h>
#include "gsoft.h"
#include "rxregsvc.h"


typedef void* GcHeapHandle;
GCRX_DLL_DECL GcHeapHandle gcHeapCreate(Gsoft::UInt32 flags);
GCRX_DLL_DECL void gcHeapDestroy(GcHeapHandle heap);
GCRX_DLL_DECL void* gcHeapAlloc(GcHeapHandle heap, size_t size);
GCRX_DLL_DECL void* gcTryHeapAlloc(GcHeapHandle heap, size_t size);
GCRX_DLL_DECL void gcHeapFree(GcHeapHandle heap, void* p);
GCRX_DLL_DECL void* gcHeapReAlloc(GcHeapHandle heap, void* p, size_t size);
GCRX_DLL_DECL size_t gcHeapSize(GcHeapHandle heap, const void* p);
GCRX_DLL_DECL bool gcHeapValidate(GcHeapHandle heap, const void* p);

GCRX_DLL_DECL void* gcAllocAligned(size_t alignment, size_t size);
GCRX_DLL_DECL void gcFreeAligned(void* p);
GCRX_DLL_DECL size_t gcMsizeAligned(void* p, size_t alignment);