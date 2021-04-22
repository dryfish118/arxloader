#pragma once
#include "gcadstd.h"
#include "gs.h"

class GcDbViewportTableRecord;
class GcGiDrawable;
class GcGsView;
class GcGsModel;
class GcGsDevice;
class IGcadDrawingSurface;

#ifdef GCGS_EXPORTS
#define  GCGSAPI __declspec(dllexport)
#else
#define  GCGSAPI __declspec(dllimport)
#endif

//////////////////////////////////////////////////////////////////////////
// 

class GcGsManager
{
public:
          GcGsManager(void)   { }
  virtual ~GcGsManager(void)  { }

  //////////////////////////////////////////////////////////////////////////
  // 以下函数内部不调用，做为兼容ARX接口存在
  virtual OdGsModel *         createCADModel    (GcGsGraphicsKernel &kernel)                                = 0;
  virtual OdGsView *          createCADViewport (GcGsGraphicsKernel &kernel, OdDbViewportTableRecord * vp)  = 0;
  virtual OdGsView *          createCADView     (GcGsGraphicsKernel &kernel, OdGiDrawable * drawable)       = 0;
  virtual OdGsDevice *        createCADDevice   (GcGsGraphicsKernel &kernel, GcGsWindowingSystemID id)      = 0;
  virtual OdGsDevice *        createCADOffScreenDevice(GcGsGraphicsKernel &kernel)                          = 0;

  virtual void                destroyCADModel   (OdGsModel  * model)            = 0;
  virtual void                destroyCADView    (OdGsView   * view)             = 0;
  virtual void                destroyCADDevice  (OdGsDevice * device)           = 0;

  virtual GcGsView*           createViewport(GcGsDevice* pDevice, GcDbViewportTableRecord *pVTR) = 0;
  virtual GcGsView*           createView(GcGsDevice* pDevice) = 0;
  virtual void                destroyView(GcGsView*, GcDbViewportTableRecord* pVTR = nullptr) = 0;
  
public:
  virtual OdGsModel        *  getDBModel        (GcGsGraphicsKernel &kernel)                          = 0;
  virtual OdGsDevice       *  getGUIDevice      (GcGsGraphicsKernel &kernel)                          = 0;
  virtual void                setGsModel(const GcDbDatabase* pDb, GcGsModel* pModel)                  = 0;
  virtual GcGsModel*          gsModel(const GcDbDatabase* pDb) const                                  = 0;

  virtual void                setGsHighlightModel(const GcDbDatabase* pDb, GcGsModel* pModel) = 0;
  virtual GcGsModel*          gsHighlightModel(const GcDbDatabase* pDb) const = 0;

  virtual GcGsDevice*         getOffScreenDevice(GcGsGraphicsKernel &kernel) = 0;
  virtual GcGsView*           getOffScreenView(GcGsGraphicsKernel &kernel, GcGsClientViewInfo &clientViewInfo) = 0;

  virtual bool                hasGsModel(const GcDbDatabase* pDb) const = 0;
  virtual bool                invalidateGsModel(const GcDbDatabase* pDb) = 0;

public:

  static GCGSAPI GcGsGraphicsKernel*   acquireGraphicsKernel(const GcGsKernelDescriptor &descriptor);
  static GCGSAPI void                  releaseGraphicsKernel(GcGsGraphicsKernel *pKernel);
  static GCGSAPI GcGsConfig*           getConfig(void);

public:
  virtual IGcadDrawingSurface* getDrawingSurface(void) { return NULL; }

  virtual GcGsGraphicsKernel *  getGSGraphicsKernel(void) { return NULL; }
};


