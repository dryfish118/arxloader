#pragma once

typedef enum {
  kMiterJoin   = 0x00,
  kBevelJoin   = 0x01,
  kRoundJoin   = 0x02,
  kDiamondJoin = 0x03,
} GcGiLineJoinStyle;

typedef enum {
  kButtCap    = 0x00,
  kSquareCap  = 0x01,
  kRoundCap   = 0x02,
  kDiamondCap = 0x03,
} GcGiLineEndStyle;

typedef enum {
  kFillStyleSolid  = 0x00,
  kCheckerboard    = 0x01,
  kCrosshatch      = 0x02,
  kDiamonds        = 0x03,
  kHorizontal_Bars = 0x04,
  kSlant_Left      = 0x05,
  kSlant_Right     = 0x06,
  kSquare_Dots     = 0x07,
  kVertical_Bars   = 0x08,
  kUser_Defined    = 0x09
}GcGiLineFillStyle;

class GSOFT_NO_VTABLE GcGiLineAttributes
{
public:

  virtual ~GcGiLineAttributes() { }

  virtual GcDb::LineWeight getLineweight() const = 0;
  virtual void             setLineweight(GcDb::LineWeight lweight) = 0;

  virtual GcGiLineJoinStyle getJoinstyle() const = 0;
  virtual void              setJoinstyle(GcGiLineJoinStyle joinstyle) = 0;

  virtual GcGiLineEndStyle getEndstyle() const = 0;
  virtual void             setEndstyle(GcGiLineEndStyle endstyle) = 0;

  virtual GcGiLineType getLinetype() const = 0;
  virtual void         setLinetype(GcGiLineType linetype) = 0;

  virtual GcGiLineFillStyle getFillstyle() const = 0;
  virtual void              setFillstyle(GcGiLineFillStyle fillstyle) = 0;

  virtual bool isLinetypeAdaptive() const = 0;
  virtual void setLinetypeAdaptive(bool isAdaptive) = 0;

  virtual bool isLineWeightByLayer() const = 0;
  virtual void setLineWeightByLayer(bool isLineweightByLayer) = 0;

  virtual bool hasCustomLineweight() const = 0;
  virtual void setCustomLineweight(bool isCustomLineweight) = 0;

  virtual bool isLineweightDefault() const = 0;
  virtual void setLineweightDefault() = 0;

  virtual GcGiLineAttributes* clone() const = 0;

};

