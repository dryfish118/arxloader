#pragma once
#include "gcadstd.h"
#include <rxsrvice.h>

#pragma pack (push, 8)

class GcRxClass;
class GcRxDictionary;

class GCDB_DLL_DECL GcRxKernel : public GcRxService
{
public:
  GCRX_DECLARE_MEMBERS(GcRxKernel);

  GcRxKernel();
  virtual ~GcRxKernel();

  virtual GcRxDictionary* newAcRxDictionary(Gsoft::Boolean sorted = Gsoft::kTrue, Gsoft::Boolean ignoreCase = Gsoft::kFalse) = 0;
  virtual GcRxDictionary* newAcRxDictionary(unsigned long length, Gsoft::Boolean delObjects, Gsoft::Boolean sorted = Gsoft::kTrue, Gsoft::Boolean ignoreCase = Gsoft::kFalse) = 0;
  virtual GcRxDictionary* newAcRxDictionary(const GcRxClass * filter) = 0;
};

#define gcrxKernel GcRxKernel::cast(GcRxDictionary::cast(gcrxSysRegistry()->at(GCRX_SERVICE_DICTIONARY))->at(GCRX_KERNEL_SERVICES))


#pragma pack (pop)
