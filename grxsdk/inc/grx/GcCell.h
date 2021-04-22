#pragma once

typedef struct GcCell
{
    int     mnRow;
    int     mnColumn;

} GcCell;

typedef GcArray<GcCell> GcCellArray;
typedef GcArray<GcCellRange> GCCellRangeArray;
#define GcCellRangeArray OdCellRangeArray