#pragma once
#include "gcadstd.h"
#include "gced-hatch.h"
#include "../DbEntity.h"
#include "../rxsrvice.h"
#include "rxvar.h"

class GcEdImpSysVarIterator;

enum DimstyleTabSuppressed
{
  kSymbolsArrowsTabSuppressed = 0x01,
  kTextTabSuppressed = 0x02,
  kFitTabSuppressed = 0x04,
  kPrimaryTabSuppressed = 0x08,
  kAlternateTabSuppressed = 0x10,
  kToleranceTabSuppressed = 0x20
};

GCED_DLL_DECL int gcedEditDimstyleInteractiveEx(GcDbDatabase * pDb, GcDbDimStyleTableRecord * pRec,
  int familyType, const GCHAR* title = NULL, int tabCtrlFlags = 0);

GCED_DLL_DECL Gcad::ErrorStatus gcedConvertEntityToHatch(GcDbHatch* pHatch, GcDbEntity*& pEnt, bool transferId);

GCED_DLL_DECL Gcad::ErrorStatus gcedManageHatchEditorReactor(GcDbObjectId hatchId, GcHatchEdReact action,
  GcDbObjectId boundaryId = GcDbObjectId::kNull,
  GcHatchNotifier notifyType = kNobody,
  bool transformed = false);

GCED_DLL_DECL bool gcdbCanonicalToSystemRange(int eUnits, const GcString& strIn, GcString& strOut);

GCED_DLL_DECL bool gcdbSystemRangeToCanonical(int eUnits, const GcString& strIn, GcString& strOut);

GCED_DLL_DECL bool gcedIsInBackgroundMode();

GCED_DLL_DECL void gcedOpenDocWindowsMinimized(bool bMinimized);

GCED_DLL_DECL bool gcedCompareToCurrentViewport(const GcDbViewTableRecord *pVwRec);

GCED_DLL_DECL unsigned long gcedGetAnimationFrameId(void);

GCED_DLL_DECL bool gcedShowConstraintBar(GcDbFullSubentPathArray &subentPaths);
GCED_DLL_DECL bool gcedHideConstraintBar(GcDbFullSubentPathArray &subentPaths);

GCED_DLL_DECL bool gcedShowConstraintBarForAll(bool bToShow);

GCED_DLL_DECL Gcad::ErrorStatus gcedTraceBoundary(const GcGePoint3d& seedPoint, bool detectIslands, GcDbVoidPtrArray& resultingBoundarySet);

GCED_DLL_DECL Gcad::ErrorStatus gcedAudit(GcDbDatabase* pDb, bool bFixErrors, bool bCmdLnEcho = false);
GCED_DLL_DECL bool gcedAddSupplementalCursorImage(const GcGiImageBGRA32* pSuppCursorImage, int priorityOrder = 0);
GCED_DLL_DECL bool gcedRemoveSupplementalCursorImage(const GcGiImageBGRA32* pSuppCursorImage);
GCED_DLL_DECL bool gcedHasSupplementalCursorImage();
GCED_DLL_DECL void gcedSetSupplementalCursorOffset(int x, int y);
GCED_DLL_DECL void gcedGetSupplementalCursorOffset(int& x, int& y);
GCED_DLL_DECL float gcedGetDpiScalingValue();
GCED_DLL_DECL bool gcedScaleImageWithGDIPlus(const GcGiImageBGRA32 *pSrcImg, const GcGiImageBGRA32 *pDstImg);

GCED_DLL_DECL void gcedDisableDefaultARXExceptionHandler(Gsoft::Boolean disable = Gsoft::kTrue);

class OdEdServices : public OdRxService
{
public:
  ODRX_DECLARE_MEMBERS(OdEdServices);
  virtual OdEdCommand* newAcEdCommand(GcRxFunctionPtr cmdFcnAddr, OdInt32 cmdFlags) const = 0;
};

class CGdUiPathname;

class OdEditorReactor3 : public OdEditorReactor2
{
public:
  ODRX_DECLARE_MEMBERS(OdEditorReactor3);

  virtual void fullRegenEnded(OdDbDatabase*  pDb,
    const OdDbIntArray & regenedViewports) {}

  virtual void curDocOpenUpgraded(OdDbDatabase* pDb,
    const CGdUiPathname& filename)
  {}

  virtual void curDocOpenDowngraded(OdDbDatabase* pDb,
    const CGdUiPathname& filename)
  {}
};

class GcEdSysVarIterator
{
public:
  GCED_DLL_DECL GcEdSysVarIterator();
  GCED_DLL_DECL ~GcEdSysVarIterator();

  GCED_DLL_DECL void step();
  GCED_DLL_DECL const GcRxVariable* getSysVar();
  GCED_DLL_DECL void reset();
  GCED_DLL_DECL bool done() const;
private:
  GcEdImpSysVarIterator* m_pImp;
};


  GCED_DLL_DECL Gsoft::Boolean gcedSetOLELock(int handle, int flags = 0);

  GCED_DLL_DECL Gsoft::Boolean gcedClearOLELock(int handle);
