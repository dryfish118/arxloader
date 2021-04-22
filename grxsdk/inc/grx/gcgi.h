#pragma once

#include "gcadstd.h"

#include "../IdArrays.h"
#include "../Gi/Gi.h"
#include "../Gi/GiDrawable.h"
#include "../Gi/GiViewport.h"
#include "../Gi/GiCommonDraw.h"
#include "../Gi/GiWorldDraw.h"
#include "../Gi/GiViewportDraw.h"
#include "../Gi/GiGeometry.h"
#include "../Gi/GiWorldGeometry.h"
#include "../Gi/GiViewportGeometry.h"
#include "../Gi/GiTextStyle.h"
#include "../Gi/GiPolyline.h"
#include "../Gi/GiRasterWrappers.h"
#include "../GiContextForDbDatabase.h"
#include "../Gi/GiClipBoundary.h"
#include "../Gi/GiFill.h"

#ifndef ODGI_EXPORT_EX
  #ifdef GCGS_EXPORTS
    #define ODGI_EXPORT_EX
  #else
    #define ODGI_EXPORT_EX ODGI_EXPORT
  #endif
#endif

#include "gcgitransient.h"

struct TextParams;
struct FontInfo;
class OdFontHandle;
class GcGiImpGradientFill;

struct OdGiSentScanLines
{
  enum IsmRequestStatus {
    eOk,
    eInvalidInput,
    eInvalidColorDepth,
    eInvalidPixelRequest,
    eInvalidDeliveryMethod,
    eNoValidCompressors,
    eInsufficientMemory
  };

  OdInt8 *    mpPixelBuffer;
  OdUInt32    mRowBytes;
  void *      mpImageId;
  OdInt16     mIsCancelled;
  OdInt16     mHasFailed;
  OdUInt32    mBytes;
  IsmRequestStatus mRequestStatus;
};

struct OdGiRequestScanLines
{
  enum IEDitherMethod
  {
    kIEAnyPalette,
    kCustomDithering,
    kCustomDitheringMethod
  };

  enum IEColorSystem
  {
    kBitonal,
    kCMY,
    kCMYK,
    kRGB
  };

  enum ImagePaletteType
  {
    kFromDevice,
    kFromIeWholeImage
  };

  OdGiRequestScanLines()
    : mPixelMinX(0)
    , mPixelMinY(0)
    , mPixelMaxX(0)
    , mPixelMaxY(0)
    , mpImageId(0)
    , mImageOrg(kOdGiBitonal)
    , mImageOrient(kOdGiXLeftToRightTopFirst)
    , mWindowId(0)
    , mColorDepth(8)
    , mPaletteIncarnation(0)
    , mpPalette(0)
    , mIsDisplay(0)
    , mRasterRatio(1.0)
    , mPaletteType(kFromDevice)
    , mpDataBuffer(0)
    , mRowWidth(0)
    , mpBoundaryPoints(0)
    , mnContours(0)
    , mpCounts(0)
    , mScalingType(kDefaultScale)
    , mScaleFilterType(kDefaultScaleFilter)
    , mRotationFilterType(kDefaultRotationFilter)
    , mnTotalChunks(0)
    , mnThisChunk(0)
  {
  }

  OdUInt32       mPixelMinX;
  OdUInt32       mPixelMinY;
  OdUInt32       mPixelMaxX;
  OdUInt32       mPixelMaxY;
  OdGePoint2d         mLowerLeft;
  OdGePoint2d         mUpperRight;
  void *              mpImageId;
  OdGiImageOrg        mImageOrg;
  OdGiImageOrient     mImageOrient;
  OdInt16        mWindowId;
  OdInt16        mColorDepth;
  union {
    OdInt16 mBackgroundIndex;
    OdInt8 mBackgroundRGB[3];
  }                   mBackgroundColor;
  union {
    OdInt16 mTransparentIndex;
    OdInt8 mTransparentRGB[3];
  } mTransparentColor;
  union {
    OdInt16 mEntityIndex;
    OdInt8 mEntityRGB[3];
  }                   mEntityColor;
  OdInt32        mPaletteIncarnation;
  OdInt8 *       mpPalette;
  OdInt16        mIsDisplay;
  double              mRasterRatio;
  OdGeMatrix2d        mPixelToDc;
  ImagePaletteType    mPaletteType;
  void *              mpDataBuffer;
  OdInt32        mRowWidth;
  OdInt32        mNumRows;
  OdInt32 const *mpBoundaryPoints;
  OdUInt32       mnContours;
  OdInt32 const *mpCounts;
  OdGiScaleType          mScalingType;
  OdGiScaleFilterType    mScaleFilterType;
  OdGiRotationFilterType mRotationFilterType;
  short                  mnTotalChunks;
  short                  mnThisChunk;
};

enum GcGiColorIntensity
{
  kGcGiMinColorIntensity = 0x0,
  kGcGiColorIntensity1 = 0x1,
  kGcGiColorIntensity2 = 0x2,
  kGcGiColorIntensity3 = 0x3,
  kGcGiColorIntensity4 = 0x4,
  kGcGiColorIntensity5 = 0x5,
  kGcGiColorIntensity6 = 0x6,
  kGcGiMaxColorIntensity = 0x7
};

class GcGiColorRGBA
{
public:
    GcGiColorRGBA (void)
        : red   (0.0)
        , green (0.0)
        , blue  (0.0)
        , alpha (1.0)
    { }

    GcGiColorRGBA (double r, double g, double b, double a) 
        : red   (r)
        , green (g)
        , blue  (b)
        , alpha (a)
    { }

    double red;
    double green;
    double blue;
    double alpha;
};

inline GcGiColorRGBA operator* (const GcGiColorRGBA& c1, const GcGiColorRGBA& c2)
{
    return GcGiColorRGBA(c1.red   * c2.red, 
                         c1.green * c2.green, 
                         c1.blue  * c2.blue, 
                         c1.alpha * c2.alpha);
}

inline GcGiColorRGBA operator*(const GcGiColorRGBA& c, double s)
{
    return GcGiColorRGBA(s * c.red, 
                         s * c.green, 
                         s * c.blue, 
                         s * c.alpha);
}

inline GcGiColorRGBA operator* (double s, const GcGiColorRGBA& c)
{
    return c * s;
}

inline GcGiColorRGBA operator+ (const GcGiColorRGBA& c1, const GcGiColorRGBA& c2)
{
    return GcGiColorRGBA(c1.red   + c2.red, 
                         c1.green + c2.green, 
                         c1.blue  + c2.blue, 
                         c1.alpha + c2.alpha);
}

ODGI_EXPORT_EX Gcad::ErrorStatus gcgiGetRegenBlockRefStack(GcDbObjectIdArray& blkRefs);

ODGI_EXPORT_EX bool gcgiIsValidClipBoundary(const GcGePoint2dArray& pts);

class OdUniqueString;

class GcGiKernelDescriptor : public OdArray<const OdUniqueString *>
{
public:
  // Require support for a given capability.
  void addRequirement(const OdUniqueString *capability) { append(capability); }

  // Query support for a given capability.
  bool supports(const OdUniqueString *capability) const { return contains(capability); }

  bool supports(const GcGiKernelDescriptor& desc) const
  {
    int len = desc.length();
    for (int i = 0; i < len; i++)
    {
      if (!contains(desc[i]))
        return false;
    }
    return true;
  }
};

class GcGiGraphicsKernel
{
public:
  virtual ~GcGiGraphicsKernel() { }
  virtual const GcGiKernelDescriptor &getDescriptor(void) const { return m_descriptor; }

private:
  GcGiKernelDescriptor m_descriptor;
};

class GCDB_DLL_DECL GcGiGradientFill : public GcGiFill
{
public:
  enum GradientType
  {
    kLinear,
    kCylinder,
    kInvCylinder,
    kSpherical,
    kHemispherical,
    kCurved,
    kInvSpherical,
    kInvHemispherical,
    kInvCurved
  };

  GCRX_DECLARE_MEMBERS(GcGiGradientFill);

  GcGiGradientFill(double                              gradientAngle,
    double                              gradientShift,
    bool                                bAdjustAspect,
    GcArray<GcCmColor>&                 gradientColors,
    GcGiGradientFill::GradientType type);

  GcGiGradientFill(const GcGiGradientFill&);
  virtual ~GcGiGradientFill();

  void setGradientAngle(double val);
  double gradientAngle() const;

  void setGradientShift(double val);
  double gradientShift() const;

  void setIsAdjustAspect(bool val);
  bool isAdjustAspect() const;

  void setGradientColors(const GcArray<GcCmColor>& val);
  const GcArray<GcCmColor>& gradientColors() const;

  void setGradientType(GcGiGradientFill::GradientType type);
  const GcGiGradientFill::GradientType gradientType() const;

private:
  GcGiImpGradientFill *mpImp;
};

#define GCGI_SERVICES  _T("GcGiServices")

#define GcGiSelectionMarkerACADReserveStart         (-2147483647 - 1)
#define GcGiSelectionMarkerACADReserveEnd           (GcGiSelectionMarkerACADReserveStart + 65535)

#define GcGiSelectionMarkerACADSelectionPreviewOff  (GcGiSelectionMarkerACADReserveStart + 1)
#define GcGiSelectionMarkerACADSelectionPreviewOn   (GcGiSelectionMarkerACADReserveStart + 2)

#define ACGI_SERVICES                               GCGI_SERVICES
#define AcGiSelectionMarkerACADReserveStart         GcGiSelectionMarkerACADReserveStart
#define AcGiSelectionMarkerACADReserveEnd           GcGiSelectionMarkerACADReserveEnd
#define AcGiSelectionMarkerACADSelectionPreviewOff  GcGiSelectionMarkerACADSelectionPreviewOff
#define AcGiSelectionMarkerACADSelectionPreviewOn   GcGiSelectionMarkerACADSelectionPreviewOn

#define GcGiHatchPatternDefinition OdGiHatchPatternDefinition
#define GcGiHatchPattern           OdGiHatchPattern

#define GcGiImpEdgeData OdGiImpEdgeData
#define GcGiImpFaceData OdGiImpFaceData
#define GcGiImpVertexData OdGiImpVertexData
#define GcGiImpTextStyle  OdGiImpTextStyle

#define GCRX_DECLARE_MEMBERS_READWRITE  ODRX_DECLARE_MEMBERS_READWRITE
