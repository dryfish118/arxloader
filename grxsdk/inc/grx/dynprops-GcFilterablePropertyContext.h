#pragma once

typedef
#ifdef _GSOFT_WINDOWS_
__declspec(uuid("87BFEB4C-0470-46AF-A77D-E962F6DCCF35"))
#endif
enum GcFilterablePropertyContext
{
  gcQuickPropertiesContext = 0,
  gcTooltipContext = 1
} GcFilterablePropertyContext;