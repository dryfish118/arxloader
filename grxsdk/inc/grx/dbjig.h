#ifndef _GCAD_JIG_H_
#define _GCAD_JIG_H_

#include "gcadstd.h"
#include "gcdb.h"
#include "dbdimdata.h"
#include "gccoredefs.h"

#pragma pack (push, 8)

class	GcEdImpJig;
class	GcDbEntity;
class GcEdDragStyle;

class GCED_DLL_DECL GcEdJig: public GcRxObject
{
public:
  GCRX_DECLARE_MEMBERS(GcEdJig);

  enum UserInputControls
  {
    kGovernedByOrthoMode         = 0x0001,
    kNullResponseAccepted        = 0x0002,
    kDontEchoCancelForCtrlC      = 0x0004,
    kDontUpdateLastPoint         = 0x0008,
    kNoDwgLimitsChecking         = 0x0010,
    kNoZeroResponseAccepted      = 0x0020,
    kNoNegativeResponseAccepted  = 0x0040,
    kAccept3dCoordinates         = 0x0080,
    kAcceptMouseUpAsPoint        = 0x0100,
    kAnyBlankTerminatesInput     = 0x0200,
    kInitialBlankTerminatesInput = 0x0400,
    kAcceptOtherInputString      = 0x0800,
    kGovernedByUCSDetect         = 0x1000,
    kNoZDirectionOrtho           = 0x2000,
    kImpliedFaceForUCSChange     = 0x4000,
    kUseBasePointElevation       = 0x8000,
    kDisableDirectDistanceInput  = 0x010000,
  };

  enum DragStatus
  {
    kModeless       = -17,
    kNoChange       = -6,
    kCancel         = -4,
    kOther          = -3,
    kNull           = -1,
    kNormal         = 0,
    kKW1,
    kKW2,
    kKW3,
    kKW4,
    kKW5,
    kKW6,
    kKW7,
    kKW8,
    kKW9
  };

  enum CursorType
  {
    kNoSpecialCursor = -1,
    kCrosshair = 0,
    kRectCursor,
    kRubberBand,
    kNotRotated,
    kTargetBox,
    kRotatedCrosshair,
    kCrosshairNoRotate,
    kInvisible,
    kEntitySelect,
    kParallelogram,
    kEntitySelectNoPersp,
    kPkfirstOrGrips,
    kCrosshairDashed
  };

public:
  GcEdJig();
  virtual ~GcEdJig();

  DragStatus drag();
  DragStatus drag(const GcEdDragStyle& style);
  virtual DragStatus sampler();
  virtual Gsoft::Boolean update();
  GcDbObjectId append();

  const GCHAR* keywordList();
  void  setKeywordList(const GCHAR*);

  const GCHAR* dispPrompt();
  void  setDispPrompt(const GCHAR*, ...);

  DragStatus acquireString(GCHAR(&str)[2049]);
  DragStatus acquireAngle(double& ang);
  DragStatus acquireAngle(double& ang, const GcGePoint3d& basePnt);
  DragStatus acquireDist(double& dist);
  DragStatus acquireDist(double& dist, const GcGePoint3d& basePnt);
  DragStatus acquirePoint(GcGePoint3d&);
  DragStatus acquirePoint(GcGePoint3d&, const GcGePoint3d& basePnt);

  GcEdJig::CursorType specialCursorType();
  void setSpecialCursorType(CursorType);

  GcEdJig::UserInputControls userInputControls();
  void setUserInputControls(GcEdJig::UserInputControls);

  virtual GcDbEntity* entity() const;
  virtual GcDbDimDataPtrArray* dimData(const double dimScale);
  virtual Gcad::ErrorStatus setDimValue(const GcDbDimData* dimData, const double dimValue); 

  //Gcad use
  virtual DragStatus acquireAngleEx(double& ang, const GcGePoint3d& basePnt);
  virtual DragStatus acquireDistEx(double& dist, const GcGePoint3d& basePnt, GcGePoint3d& ToPnt, bool& usePnt);

protected:
  GcEdImpJig* mpImpJig;
};

class GCED_DLL_DECL GcEdDragStyle
{
public:

    enum StyleType
    {
        kNone = 0, 
        
        kHide,
        
        kTransparent25,

        kTransparent75,

        kDeletedEffect,

        kHighlight,

        kNotSet
    };

    GcEdDragStyle  ();

    GcEdDragStyle  ( StyleType styleTypeForOriginal, StyleType styleTypeForDragged );

    GcEdDragStyle  ( const GcEdDragStyle& dragStyle );

    ~GcEdDragStyle ();

    StyleType             styleTypeForOriginal () const;

    StyleType             styleTypeForDragged () const;

    Gcad::ErrorStatus     setStyleTypeForOriginal ( StyleType styleType );

    Gcad::ErrorStatus     setStyleTypeForDragged ( StyleType styleType );
    
    GcEdDragStyle&  operator = ( const GcEdDragStyle& src );

    bool operator == ( const GcEdDragStyle& other ) const;
    bool operator != ( const GcEdDragStyle& other ) const;

private:
    //GcEdImpDragStyle  *mpOriginalDragStyle;
    //GcEdImpDragStyle  *mpDraggedDragStyle;

    //friend class GcEdImpDragStyle;
};
#pragma pack (pop)

#endif//_GCAD_JIG_H_