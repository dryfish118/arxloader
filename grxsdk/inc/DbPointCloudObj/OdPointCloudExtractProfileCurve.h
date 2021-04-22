#pragma once 
#include "DbPointCloudObjExports.h"
#include "Ge/GeCircArc2d.h"
#include "Ge/GeLineSeg2d.h"

class DBPOINTCLOUDOBJ_EXPORT ProfileCurve2d
{
public:
    enum ProfileurveType
    {
        kLineSeg = 0,
        kArc,
    };    
private:
    OdGeLineSeg2d m_seg;
    OdGeCircArc2d m_arc;
    ProfileurveType m_type;

public:
    ProfileCurve2d()
    {
        m_type = kLineSeg;
    }
    ProfileCurve2d(const OdGeLineSeg2d& seg)
    {
        m_seg = seg;
        m_type = kLineSeg;
    }
    ProfileCurve2d(const OdGeCircArc2d& arc)
    {
        m_arc = arc;
        m_type = kArc;
    }

    bool isSegment() const
    {
        return m_type == kLineSeg;
    }
    bool isArc() const
    {
        return m_type == kArc;
    }

    OdGeLineSeg2d lineSeg() const
    {
        return m_seg;
    }
    void setLineSeg(const OdGeLineSeg2d& lineSeg)
    {
        m_seg = lineSeg;
        m_type = kLineSeg;
    }

    OdGeCircArc2d arc() const
    {
        return m_arc;
    }
    void setArc(const OdGeCircArc2d& arc)
    {
        m_arc = arc;
        m_type = kArc;
    }
};

class DBPOINTCLOUDOBJ_EXPORT OdPointCloudExtractResult
{
public:
    OdArray<ProfileCurve2d> Curves;
    OdGeMatrix3d            transform;
    OdGePlane               ProjectedPlane;
};