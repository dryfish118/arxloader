#pragma once
#include "gcadstd.h"
#include "../RxOverrule.h"
#include "gcbasedefs.h"
#include "rxobject.h"
#include "gcarray.h"

#pragma pack (push, 8)

class GcRxOverruleIteratorBase;

class GCDB_DLL_DECL GcRxOverruleBase : public GcRxObject
{
public:
  GCRX_DECLARE_MEMBERS(GcRxOverruleBase);
private:
  mutable GcRxOverruleIteratorBase* m_pIter;
  friend class GcRxOverruleInternals;
};

#pragma warning( push )
#pragma warning( disable : 4275 )

class GCBASE_PORT GcRxQueryXOverrule : public GcRxOverrule
{
public:
  GCRX_DECLARE_MEMBERS(GcRxQueryXOverrule);

  GcRxQueryXOverrule();

  virtual GcRxObject* queryX(const GcRxObject* pSubject, const GcRxClass* protocolClass) const {};
};
#pragma warning( pop ) 

#pragma pack (pop)