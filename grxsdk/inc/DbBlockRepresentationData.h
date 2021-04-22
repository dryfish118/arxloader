#ifndef _DbBlockRepresentationData_h_Included_
#define _DbBlockRepresentationData_h_Included_

#include "DbBlockElement.h"
//#include "DbBlockElementImpl.h"

class DYNBLOCKS_EXPORT OdDbBlockRepresentationData : public OdDbObject
{
protected:
  OdInt16 m_nVersion;
  OdDbHardOwnershipId m_pId;
public:
  ODDB_DECLARE_MEMBERS(OdDbBlockRepresentationData);
  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  OdResult dwgOutFields(OdDbDwgFiler* pFiler) const;
  OdResult dxfInFields(OdDbDxfFiler* pFiler);
  OdResult dxfOutFields(OdDbDxfFiler* pFiler) const;
  OdDbBlockRepresentationData();
  virtual void setBlock( const OdDbObjectId& );
};

#endif // _DbBlockRepresentationData_h_Included_
