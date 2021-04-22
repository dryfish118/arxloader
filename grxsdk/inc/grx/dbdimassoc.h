#pragma once
#include "gcadstd.h"
#include "dbmain.h"
#include "../DbDimassoc.h"


GCDB_DLL_DECL Gcad::ErrorStatus gcdbGetDimAssocId(GcDbObjectId dimId, GcDbObjectId& dimAssocId);
GCDB_DLL_DECL Gcad::ErrorStatus gcdbGetDimAssocIds(GcDbObjectId entId, GcDbObjectIdArray& dimAssocIds);

GCDB_DLL_DECL Gcad::ErrorStatus gcdbPostDimAssoc(GcDbObjectId dimId, GcDbDimAssoc* pDimAssoc, 
                                                  GcDbObjectId& dimAssocId, bool isActive = true);

GCDB_DLL_DECL Gcad::ErrorStatus gcdbUpdateDimension(GcDbObjectId dimId);

GCDB_DLL_DECL Gcad::ErrorStatus gcdbUpdateAllDimensions(GcDbDatabase* pDb);

GCDB_DLL_DECL bool gcdbIsTransSpatial(const GcDbFullSubentPath& idPath);

GCDB_DLL_DECL Gcad::ErrorStatus gcdbGetAssocAnnotationActionBody(const GcDbObjectId& idDim, GcDbObjectId& idActionBody);

GCDB_DLL_DECL Gcad::ErrorStatus gcdbGetNonAssocAnnotations(GcDbDatabase* pDb, bool isPaperSpace, GcDbObjectId& blockId, GcDbObjectIdArray& annoIds, bool ignoreOffOrFrozenLayers = false);

GCDB_DLL_DECL bool gcdbIsEntityInBlockOrXref(const GcDbEntity* pEnt);

GCDB_DLL_DECL bool gcdbIsAnnoMonitorOn();

GCDB_DLL_DECL bool gcdbIsAssociativityAlertIconDisabled(GcDbEntity *pEnt);

GCDB_DLL_DECL bool gcdbDisableAssociativityAlertIcon(GcDbEntity *pEnt, bool disable);

GCDB_DLL_DECL bool gcdbIsAssociativeAnnotation(GcDbObject* pObj, bool* pIsPartialAssoc = NULL);

class GcDbAnnoAlertDisabler
{
public:
  GCDB_DLL_DECL GcDbAnnoAlertDisabler(const GcDbObjectId& objId);
  GCDB_DLL_DECL ~GcDbAnnoAlertDisabler();
private:
  GcDbObjectId m_objId;
};

GCDB_DLL_DECL bool gcdbGetAssociativityOverride(GcDbEntity *pEnt, int& nValue);

GCDB_DLL_DECL bool gcdbSetAssociativityOverride(GcDbEntity *pEnt, int nValue);
