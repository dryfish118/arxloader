#pragma once
#include "gcadstd.h"
#include "gcdb.h"

#pragma pack (push, 8)

class GcDbDwgFiler;
class GcDbDxfFiler;
class ENTITY;

extern "C"
{
	GCDB_DLL_DECL void gcdbModelerStart();
	GCDB_DLL_DECL void gcdbModelerEnd();
	
	GCDB_DLL_DECL OdBool gcdbIsModelerStarted();

    GCDB_DLL_DECL OdResult gcdbAcisSaveEntityToDwgFiler     (GcDbDwgFiler* filer, ENTITY* ent);
    GCDB_DLL_DECL OdResult gcdbAcisSaveEntityToDwgFiler2     (GcDbDwgFiler* filer, ENTITY* ent, GcDbDatabase* pDb);
    GCDB_DLL_DECL OdResult gcdbAcisRestoreEntityFromDwgFiler(GcDbDwgFiler* filer, ENTITY*& ent);
    GCDB_DLL_DECL OdResult gcdbAcisSaveEntityToDxfFiler     (GcDbDxfFiler* filer, ENTITY* ent);
    GCDB_DLL_DECL OdResult gcdbAcisSaveEntityToDxfFiler2     (GcDbDxfFiler* filer, ENTITY* ent, GcDbDatabase* pDb);
    GCDB_DLL_DECL OdResult gcdbAcisRestoreEntityFromDxfFiler(GcDbDxfFiler* filer, ENTITY*& ent); 

    GCDB_DLL_DECL void   gcdbAcisSetDeleteBulletins(OdBool onOff);
	
    GCDB_DLL_DECL OdBool gcdbAcisGetDeleteBulletins();

	GCDB_DLL_DECL OdBool gcdbSetAcisDwgVer(int version);

    GCDB_DLL_DECL void   gcdbAcisDeleteModelerBulletins(void);
}

GCDB_DLL_DECL int gcdbGetModelerDwgVer(GcDb::GcDbDwgVersion dwgVer, GcDbObject* pObj = nullptr);
GCDB_DLL_DECL OdResult gcdbModelerSaveEntityToDwgFiler(GcDbDwgFiler* filer,
                                                        ENTITY*       entity,
                                                        GcDbDatabase* pDb,
                                                        int modelerVersion = -1);
GCDB_DLL_DECL OdResult gcdbModelerSaveEntitiesToDwgFiler(GcDbDwgFiler* filer,
                                                          const GcArray<ENTITY*>& entities,
                                                          GcDbDatabase* pDb,
                                                          int modelerVersion = -1);
GCDB_DLL_DECL OdResult gcdbModelerSaveEntityToDxfFiler(GcDbDxfFiler* filer,
                                                        ENTITY*       entity,
                                                        GcDbDatabase* pDb,
                                                        int modelerVersion = -1);
GCDB_DLL_DECL OdResult gcdbModelerSaveEntitiesToDxfFiler(GcDbDxfFiler* filer,
                                                          const GcArray<ENTITY*>& entities,
                                                          GcDbDatabase* pDb,
                                                          int modelerVersion = -1);
enum ModelerRestoreOptions
{
  kReadForeignEntities = 0x01,    // Set this to restore foreign entities
  kReadUnknownEntities = 0x02,   // Set this to restore unknown entities
  kLoseUnknownCustomAttributes = 0x04, // Unset this to restore unknown custom attributes

  kReadStrangerEntityDefault = (kReadForeignEntities |
                                kReadUnknownEntities |
                                kLoseUnknownCustomAttributes), // Recommended default

  kModelerRestoreOptionsFuture1 = 0x08, // Unused, ignore
  kModelerRestoreOptionsFuture2 = 0x10, // Unused, ignore
  kModelerRestoreOptionsFuture3 = 0x20, // Unused, ignore
  kModelerRestoreOptionsFuture4 = 0x40, // Unused, ignore
};

GCDB_DLL_DECL OdResult gcdbModelerRestoreEntityFromDwgFiler(GcDbDwgFiler* filer,
                                                            ENTITY*& pEntity,
                                                            int* pModelerVersion = nullptr,
                                                            unsigned restoreOptions = kReadStrangerEntityDefault);

GCDB_DLL_DECL OdResult gcdbModelerRestoreEntitiesFromDwgFiler(GcDbDwgFiler* filer,
                                                              GcArray<ENTITY*>& entities,
                                                              int* pModelerVersion = nullptr,
                                                              unsigned restoreOptions = kReadStrangerEntityDefault);

GCDB_DLL_DECL OdResult gcdbModelerRestoreEntityFromDxfFiler(GcDbDxfFiler* filer,
                                                            ENTITY*& pEntity,
                                                            int* pModelerVersion = nullptr,
                                                            unsigned restoreOptions = kReadStrangerEntityDefault);



#define gcdbSaveAcisEntityToDwgFiler      gcdbAcisSaveEntityToDwgFiler
#define gcdbRestoreAcisEntityFromDwgFiler gcdbAcisRestoreEntityFromDwgFiler

#pragma pack (pop)

