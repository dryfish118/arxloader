#ifndef _DBDYNAMICBLOCKPURGEPREVENTER__INCLUDED_
#define _DBDYNAMICBLOCKPURGEPREVENTER__INCLUDED_

#include "DbBlockRepresentationData.h"

class DYNBLOCKS_EXPORT OdDbDynamicBlockPurgePreventer : public OdDbBlockRepresentationData
{
public:
  ODDB_DECLARE_MEMBERS(OdDbDynamicBlockPurgePreventer);
  static OdSmartPtr<OdDbDynamicBlockPurgePreventer> safeCreateByClassName();
  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  OdResult dwgOutFields(OdDbDwgFiler* pFiler) const;
  OdResult dxfInFields(OdDbDxfFiler* pFiler);
  OdResult dxfOutFields(OdDbDxfFiler* pFiler) const;
  OdDbDynamicBlockPurgePreventer();
};

typedef OdSmartPtr<OdDbDynamicBlockPurgePreventer> OdDbDynamicBlockPurgePreventerPtr;

inline OdDbDynamicBlockPurgePreventerPtr OdDbDynamicBlockPurgePreventer::safeCreateByClassName() {
  return ::odrxSafeCreateObject<OdDbDynamicBlockPurgePreventer>("AcDbDynamicBlockPurgePreventer", "TD_DynBlock");
}



#endif // _DBDYNAMICBLOCKPURGEPREVENTER__INCLUDED_
