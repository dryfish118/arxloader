#pragma once 

#include "DbPointCloudEx.h"
#include "OdPointCloudExtractProfileCurve.h"

class DBPOINTCLOUDOBJ_EXPORT ExtractOption
{
public:
    enum ExtractionType
    {
        kOutLine,
        kAllLine,
    };

public:
    ExtractionType  m_extractionType;
    unsigned int    m_processPoints;
    double          m_fillGap;
    unsigned int    m_snapAngle;
    double          m_minSegLength;
    bool            m_useLineSegmentOnly;

    ExtractOption();
};

class DBPOINTCLOUDOBJ_EXPORT IPointCloudExtracProgressCallback
{
public:
    IPointCloudExtracProgressCallback(void){}
    virtual ~IPointCloudExtracProgressCallback(void){}

    virtual void updateProgress(int progress) = 0;

    virtual void updateCaption(const OdString& caption) = 0;

    virtual bool cancelled() const = 0;

    virtual void cancel() = 0;

    virtual void updateRemainTime(double remainTime) = 0;

    virtual void end() = 0;
};

class DBPOINTCLOUDOBJ_EXPORT OdPointCloudExtractor
{
public:

    static OdResult extract(OdDbPointCloudEx *pointCloud,
        const OdGeVector3d& planeZDirection,
        const OdGeVector3d& planeXDirection,
        const OdGePoint3d pointPlane,
        const ExtractOption& extractOption,
        OdPointCloudExtractResult& outlineResult,
        IPointCloudExtracProgressCallback* progress = 0);
    
    static OdDbObjectIdArray appendLineProfile(const OdPointCloudExtractResult& profile,
        OdDbObjectId spaceId,
        OdString layer,
        OdCmColor color);

    static OdDbObjectIdArray appendPolylineProfile(const OdPointCloudExtractResult& profile,
        OdDbObjectId spaceId,
        OdString layer,
        OdCmColor color,
        double polylineWidth);

};