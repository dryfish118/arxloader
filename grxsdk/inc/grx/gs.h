#pragma once

#include "gcadstd.h"
#include "../Gs/Gs.h"
#include "../Gs/GsDefs.h"
#include "../Gs/GsBaseModel.h"
#include "../Gs/GsBaseInclude.h"
#include "../Gs/GsBitMap.h"
#include "../Gs/GsBMPDevice.h"
#include "../Gs/GsContainerNode.h"
#include "../Gs/GsDCPointArray.h"
#include "../Gs/GsEntityNode.h"
#include "../Gs/GsExport.h"
#include "../Gs/GsLayerNode.h"
#include "../Gs/GsLight.h"
#include "../Gs/GsLightNode.h"
#include "../Gs/GsModel.h"
#include "../Gs/GsNode.h"
#include "../Gs/GsSelectionReactor.h"
#include "../Gs/GsViewProps.h"
#include "../Gs/LineWtIndex.h"
#include "../Gs/GsConfig.h"

#include "gcgi.h"

#ifdef GCGS_EXPORTS
#define  GCGSAPI __declspec(dllexport)
#else
#define  GCGSAPI __declspec(dllimport)
#endif

#define  GcGiContextualAttributes   OdGiContextualAttributes
#define  GcGsConfigReactor          OdGsConfigReactor
#define  GcGsConfig                 OdGsConfig
#define  GcGsDrawableLink           OdGsDrawableLink
//////////////////////////////////////////////////////////////////////////
// 

typedef unsigned long GcGsDrawModeFlag;
#define GcGsMakeDMF(drawmode, highlightstyle) ((drawmode) | ((highlightstyle)<<8))
#define GcGsGetDrawMode(dmf)                  ((dmf) & 0xff)
#define GcGsGetDrawHLFlag(dmf)                (((dmf)>>8) & 0xff)

//////////////////////////////////////////////////////////////////////////
// 
typedef OdGiDrawable* (* GcGsGetInterfaceFunc)     (LONG_PTR objectId, bool bNeedsValidation);
typedef void          (* GcGsReleaseInterfaceFunc) (OdGiDrawable*);
class OdGiContextForDbDatabase;
typedef OdSmartPtr<OdGiContextForDbDatabase> OdGiContextForDbDatabasePtr;

class GcGsConfig;
class GcGiContextualAttributes;

class OdGsRenderProgressMonitor
{
public:
  virtual ~OdGsRenderProgressMonitor() { }

  enum Phase
  {
    kTranslation,
    kPhotonEmission,
    kFinalGather,
    kRender,
    kDraft,
    kInitialize,
  };

  enum RenderingStatus
  {
    kRendering,
    kPaused,
    kFinished,
    kAborted,
    kWillNotRender,
    kSoftOutOfMemory,
    kHardOutOfMemory,
    kError,
  };

  virtual bool OnProgress(Phase ePhase,
    float fOverallProgress,
    int iRenderTimeSpent,
    int iCurrentRenderLevel,
    float fCurrentLevelProgress,
    int iTileIndex = 0) = 0;

  virtual void OnTile(int x, int y, int w, int h, const unsigned char* pPixels) = 0;

  //virtual void SetStatistics(const AcGsRenderStatistics* pStats) = 0; //需要修改地方太多

  virtual bool ShouldReuseDatabase() { return false; }

  virtual bool IsValid() { return true; }

  virtual bool IsAsync() { return false; }

  virtual bool IsOutputImageFlipped() { return false; }
};

class GcGsKernelDescriptor : public GcGiKernelDescriptor
{
public:
  void addSupport(const OdUniqueString *capability) { append(capability); }

  bool requires(const OdUniqueString *capability) const { return contains(capability); }

  static GCGSAPI const OdUniqueString *k2DDrawing;
  static GCGSAPI const OdUniqueString *k3DDrawing;
  static GCGSAPI const OdUniqueString *k3DSelection;
  static GCGSAPI const OdUniqueString *k3DRapidRTRendering;
};

typedef void *GcGsWindowingSystemID;
typedef void *GcGsWindowId;         

class GcGsGraphicsKernel : public GcGiGraphicsKernel
{
public:
  GcGsGraphicsKernel(void) : m_refCount(0) { }
  virtual            ~GcGsGraphicsKernel(void) { }

  GCGSAPI void addRef(void);

  GCGSAPI bool delRef(void);

  virtual bool        isCompatibleWith(const GcGsKernelDescriptor &descriptor) const = 0;

  virtual GcGsModel  *createModel(GcGsModel::RenderType type, Gsoft::IntDbId databaseId,
    GcGsGetInterfaceFunc getFunc, GcGsReleaseInterfaceFunc releaseFunc) = 0;

  virtual void        deleteModel(GcGsModel *pModel) = 0;

  virtual GcGsView   *createView(const GcGsClientViewInfo * pClientViewInfo = nullptr,
    bool bEnableLayerVisibilityPerView = false) = 0;
  
  virtual void        deleteView(GcGsView *pView) = 0;

  virtual GcGsDevice *createDevice(GcGsWindowingSystemID id, GS::DeviceType deviceType = GS::kScreenDevice) = 0;

  virtual GcGsDevice *createOffScreenDevice(void) = 0;

  virtual void        deleteDevice(GcGsDevice *pDevice) = 0;

  virtual GcGsConfig *getConfig(void) const = 0;

  virtual void        addReactor(GcGsReactor *pReactor) = 0;

  virtual void        removeReactor(GcGsReactor *pReactor) = 0;

  virtual void        addModelReactor(GcGsModel *pModel, GcGsModelReactor *pReactor) = 0;

  virtual void        removeModelReactor(GcGsModel *pModel, GcGsModelReactor *pReactor) = 0;

  virtual void        associate(Gsoft::LongPtr databasePtr, GcGsModel *pModel, GcGsModel::RenderType renderType) = 0;

  virtual GcGsModel*  find(Gsoft::LongPtr databasePtr, GcGsModel::RenderType renderType) = 0;

  virtual OdGiContextForDbDatabasePtr createContext() { return OdGiContextForDbDatabasePtr(); }
protected:
  int m_refCount;
};


class GcGsRenderInterrupter
{
public:
  virtual bool interrupt(GcGsView* pView, GcGsModel::RenderType nType) = 0;
};

struct GcGsRenderStatistics
{
public:
  float fRenderTime;

  size_t iMemory;

  size_t iMaterialCount;

  size_t iLightCount;

  size_t iTriangleCount;
};

class GcGsRenderProgressMonitor
{
public:
  enum Phase
  {
    kTranslation,
    kPhotonEmission,
    kFinalGather,
    kRender,
    kDraft,
    kInitialize,
  };

  enum RenderingStatus
  {
    kRendering,
    kPaused,
    kFinished,
    kAborted,
    kWillNotRender,
    kSoftOutOfMemory,
    kHardOutOfMemory,
    kError,
  };

  virtual ~GcGsRenderProgressMonitor()
  {
  }

  virtual bool OnProgress(Phase ePhase,
    float fOverallProgress,
    int iRenderTimeSpent,
    int iCurrentRenderLevel,
    float fCurrentLevelProgress,
    int iTileIndex = 0) = 0;


  virtual void OnTile(int x, int y, int w, int h, const unsigned char* pPixels) = 0;

  virtual void OnStatusChanged(RenderingStatus status) = 0;

  virtual void SetStatistics(const GcGsRenderStatistics* pStats) = 0;

  virtual bool ShouldReuseDatabase() { return false; }

  virtual bool IsValid() { return true; }

  virtual bool IsAsync() { return false; }

  virtual bool IsOutputImageFlipped() { return false; }
};

