#ifndef __GCGS_H__INCLUDED__
#define __GCGS_H__INCLUDED__

#pragma once

#include "gcadstd.h"

#include "../Gs/Gs.h"
#include "../Gs/GsModel.h"

#include "gcdb.h" // for namespace GcDb
#include "gcgitransient.h" // GcGiTransientDrawingMode
#include "gcgidefs.h"

#ifdef GCGS_EXPORTS
#define  GCGSAPI __declspec(dllexport)
#else
#define  GCGSAPI __declspec(dllimport)
#endif


class OdGiDrawable;
class OdGsView;
class OdGsModel;
class OdGePoint3d;
class OdGeVector3d;
class GcGsManager; 

class CView;
class OdDbDatabase;

GCGSAPI
OdBool gcgsGetDisplayInfo  (int & drawingWidth,    
                            int & drawingHeight,     
                            int & aspectWidth,
                            int & aspectHeight);
GCGSAPI
OdBool gcgsGetViewportInfo (int   viewportNumber,
                            int & left,    
                            int & bottom,
                            int & right,    
                            int & top);    


// for gcgsGetScreenShot
class GcGsScreenShot 
{
public:
    virtual OdBool getSize (int & width,             
                            int & height,
                            int & depth) const = 0; 

    virtual OdBool getColorMap (int       index,
                                OdUInt8 & red,
                                OdUInt8 & green,
                                OdUInt8 & blue) const = 0;

    virtual void const * getScanline (int offsetFromLeft,
                                      int offsetFromTop) const = 0;

    void * operator new (size_t size);

    void operator delete (void * p);

#ifndef PRODUCTION
    void * operator new (size_t size, const char *, int) { return operator new(size); }
#if _MSC_VER >= 1200
    void operator delete (void * p, const char *, int) { delete p; }
#endif
#endif

    GcGsScreenShot();
    virtual ~GcGsScreenShot () = 0;
};

// Compatibility definition
#define ScreenShot GcGsScreenShot

GCGSAPI
GcGsScreenShot * gcgsGetScreenShot (int viewportNumber);

GCGSAPI
void gcgsSetViewportRenderFlag (int viewportNumber);

GCGSAPI
OdBool gcgsDisplayImage            (int          viewportNumber,
                                    long         originLeft,    
                                    long         originTop,    
                                    int          imageWidth,    
                                    int          imageHeight,    
                                    void const * imageData,        
                                    int          hasTransparency);
GCGSAPI
OdBool gcgsRemoveAnonymousGraphics (int viewportNumber);


typedef void (*gcgsCustomUpdateMethod) (void * pParm, int left, int right, int bottom, int top);
GCGSAPI
OdBool gcgsSetCustomUpdateMethod (gcgsCustomUpdateMethod custom_update_method, void * pParm);

GCGSAPI
void gcgsRedrawShortTermGraphics (short minx, short miny, short maxx, short maxy);


struct GcGs
{
    enum LinePattern { eSolid                         = 0,
                       eDashed                        = 1,
                       eDotted                        = 2,
                       eDashDot                       = 3,
                       eShortDash                     = 4,
                       eMediumDash                    = 5,
                       eLongDash                      = 6,
                       eDoubleShortDash               = 7,
                       eDoubleMediumDash              = 8,
                       eDoubleLongDash                = 9,
                       eMediumLongDash                = 10,
                       eMediumDashShortDashShortDash  = 11,
                       eLongDashShortDash             = 12,
                       eLongDashDotDot                = 13,
                       eLongDashDot                   = 14,
                       eMediumDashDotShortDashDot     = 15,
                       eSparseDot                     = 16,
                       eDefaultLinePattern            = eDotted };
};

GCGSAPI
void gcgsSetHighlightColor (OdUInt16 colorIndex);

GCGSAPI
OdUInt16 gcgsGetHighlightColor (void);

GCGSAPI
void gcgsSetHighlightLinePattern (GcGs::LinePattern pattern);

GCGSAPI
GcGs::LinePattern gcgsGetHighlightLinePattern (void);

GCGSAPI
void gcgsSetHighlightLineWeight (OdUInt16 weight);

GCGSAPI
OdUInt16 gcgsGetHighlightLineWeight (void);

GCGSAPI
void gcgsSetHighlightStyle(GcGiHighlightStyle style);

GCGSAPI
GcGiHighlightStyle  gcgsGetHighlightStyle(void);


GCGSAPI
OdBool gcgsSetViewParameters (int viewportNumber, const GcGsView * pView,
                              bool bRegenRequired, bool bRescaleRequired,
                              bool bSyncRequired = false);
GCGSAPI
OdBool gcgsGetViewParameters (int viewportNumber, GcGsView * pView);

GCGSAPI
OdBool gcgsSetLensLength (int viewportNumber, const double & lensLength);

GCGSAPI
OdBool gcgsGetLensLength (int viewportNumber, double & lensLength);

GCGSAPI
void   gcgsWriteViewToUndoController (int viewportNumber);

GCGSAPI
OdBool gcgsSetView2D (int viewportNumber);


GCGSAPI
GcGsView *gcgsGetCurrentGcGsView(int vpNum);

GCGSAPI
GcGsView *gcgsGetCurrent3dGcGsView(int vpNum);


GCGSAPI
GcGsView *    gcgsGetGsView (int viewportNumber, bool bCreateIfNone);

GCGSAPI
GcGsManager * gcgsGetGsManager (CView * pView = NULL); 

GCGSAPI
GcGsView *gcgsObtainGcGsView(int vpNum, const class GcGsKernelDescriptor &);

GCGSAPI
GcGsModel *   gcgsGetGsModel (GcGiTransientDrawingMode mode,
                              int subDrawingMode,
                              int viewportNumber);
GCGSAPI
OdBool gcgsGetOrthoViewParameters (int viewportNumber, 
                                   GcDb::OrthographicView view,
                                   GcGeVector3d * pViewDir,
                                   GcGeVector3d * pUpVector);


// for gcgsCreate2DViewLimitManager and gcgsDestroy2DViewLimitManager 
class  GcGs2DViewLimitManager 
{      
public:
    virtual               ~GcGs2DViewLimitManager (void) { }
    virtual bool          testView                (const GcGePoint3d & target,
                                                   double              dFieldHeight)  = 0;
};

GCGSAPI
GcGs2DViewLimitManager * gcgsCreate2DViewLimitManager  (int viewportNumber);

GCGSAPI
void   gcgsDestroy2DViewLimitManager (GcGs2DViewLimitManager * pLimitManager);

GCGSAPI
OdBool gcgsDrawableModified (GcGiDrawable *pDrawable, 
                             GcGiDrawable *pParentDrawable);
GCGSAPI
OdBool gcgsDrawableErased (GcGiDrawable *pDrawable, 
                           GcGiDrawable *pParentDrawable);

GCGSAPI
OdBool gcgsDrawableCached(GcGiDrawable *pDrawable);


GCGSAPI
GcGsModel * gcgsGetGsModel(const GcDbDatabase* pDb);

GCGSAPI
GcGsModel * gcgsGetGsHighlightModel(const GcDbDatabase* pDb);

GCGSAPI
void gcgsSetGsModel(const GcDbDatabase* pDb, GcGsModel * pModel);

GCGSAPI
void gcgsSetGsHighlightModel(const GcDbDatabase* pDb, GcGsModel * pModel);


GCGSAPI
HBITMAP gcgsGetViewImage (GcGsView *pGsView, int nWidth, int nHeight);

GCGSAPI
void gcgsSetLineWeightDisplay(GcGsDevice *pDevice, bool bDisplay);

#endif //__GCGS_H__INCLUDED__

