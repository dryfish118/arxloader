#pragma once
#include "gcdb.h"

//********************************************************************************
// MODULE:      AcGiLineAttrUtils.h
// PURPOSE:     Utility functions to convert between different
//              line attributes tables
// ********************************************************************************

class GcGiLineAttrUtils
{
public:
  // Index is an 8-bit integer value
  static char gcgiLineWeightToIndex(GcDb::LineWeight lw);
  static GcDb::LineWeight gcgiIndexToLineWeight(char index);
};
