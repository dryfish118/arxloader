#ifndef GCDB_OSNAP2_H
#define GCDB_OSNAP2_H

#include "dbosnap.h"

class GCDB_DLL_DECL GcDbCustomOsnapMode2 : public GcDbCustomOsnapMode {
public:
  virtual HICON menuIcon()
  {
    return NULL;
  }

  virtual HICON menuIconForDarkTheme()
  {
    return NULL;
  }

  virtual const GCHAR * displayString()
  {
    return localModeString();
  }
};

#endif 