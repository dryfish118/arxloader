#pragma once
#include "gcdb.h"
#include "dynprops-GcFilterablePropertyContext.h"

#pragma pack (push, 8)


class GcDbPropertyFilterCustomizationPE : public GcRxObject
{
public:

  GCRX_DECLARE_MEMBERS(GcDbPropertyFilterCustomizationPE);

  virtual bool vetoCustomization(GcFilterablePropertyContext context,
    GcRxClass* pCls) const = 0;

  virtual bool createObject(GcDbDatabase* pDb,
    GcRxClass* pCls,
    GcDbEntity** ppEnt,
    GcDbObjectId& objId,
    const GcString& sGUID) const = 0;
};

GCRX_NO_CONS_DEFINE_MEMBERS(GcDbPropertyFilterCustomizationPE, GcRxObject);
#pragma pack (pop)