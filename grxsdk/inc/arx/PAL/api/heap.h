#pragma once
#include "../../../grx/PAL/api/heap.h"
#include "acad2grx.h"

#define AcHeapHandle GcHeapHandle
#define acHeapCreate gcHeapCreate
#define acHeapDestroy gcHeapDestroy
#define acHeapAlloc gcHeapAlloc
#define acTryHeapAlloc gcTryHeapAlloc
#define acHeapFree gcHeapFree
#define acHeapReAlloc gcHeapReAlloc
#define acHeapSize gcHeapSize
#define acHeapValidate gcHeapValidate
#define acAllocAligned gcAllocAligned
#define acFreeAligned gcFreeAligned
#define acMsizeAligned gcMsizeAligned