#pragma once
#include "gcadstd.h"
class GCED_DLL_DECL GcEdXrefFileLock
{
public:
  GcEdXrefFileLock();
  ~GcEdXrefFileLock();


  Gcad::ErrorStatus lockFile( int& retstatus, 
    const GcDbObjectId& selectedBTRid);

  Gcad::ErrorStatus releaseFile( int& retstatus, 
    bool bSkipSaveback = false,
    bool bReload = true);

  Gcad::ErrorStatus consistencyCheck( int& retstatus, 
    const GcDbObjectId& selectedBTRid,
    GcDbObjectIdArray& outofSyncBTRids);

  Gcad::ErrorStatus consistencyCheck( int& retstatus, 
    const GcDbObjectId& selectedBTRid);

  Gcad::ErrorStatus consistencyChecklocal( int& retstatus, 
    const GcDbObjectId& selectedBTRid);

  Gcad::ErrorStatus xloadctlType( int& retstatus,
    const GcDbObjectId& selectedBTRid);

  int getlockxloadctlType() const;

  const GcDbObjectIdArray& getoutofSyncIdArray() const;

  Gcad::ErrorStatus reloadFile(int& retstatus,
    const GcDbObjectIdArray& BTRids,
    const int xldctltype = -1);

  Gcad::ErrorStatus reloadFile(int& retstatus,
    const int xldctltype = -1);

  void              setInternalTNmgmt(bool bTNmgmt);
  GcDbObjectId      getLockBtrId() const;
};


class GCED_DLL_DECL GcDbXrefFileLocker
{
public:
  explicit GcDbXrefFileLocker(GcDbDatabase* pXrefDatabase);

  virtual ~GcDbXrefFileLocker();

  void release();

  Gcad::ErrorStatus status() const;

  void setSaveBackToXrefFile(bool yesNo);

  static bool isXrefDatabase(const GcDbDatabase* pDatabase);

private:

  void collectAllOpenedObjects(GcDbObjectIdArray& openedObjectIds);

  bool hasOpenedObjects();

  void closeOpenedObjects(GcDbObjectIdArray& openedObjectIds, GcArray<GcDb::OpenMode>& openModes, GcArray<int>& openCounts);
  void reopenClosedObjects(const GcDbObjectIdArray& openedObjectIds, const GcArray<GcDb::OpenMode>& openModes, const GcArray<int>& openCounts);

private:

  GcDbDatabase*     mpXrefDatabase;
  GcEdXrefFileLock  mXrefFileLock;
  Gcad::ErrorStatus mStatus;
  bool              mSaveBackToXrefFile;

  GcDbXrefFileLocker();
  GcDbXrefFileLocker(const GcDbXrefFileLocker&);
  GcDbXrefFileLocker& operator =(GcDbXrefFileLocker&);
};

