#pragma once
#include "OdPointCloudEngineAPI.h"

class DBPOINTCLOUDOBJ_EXPORT PointCloudBinaryOperatorFilter : public IPointCloudFilter
{
public:
  ////PointCloudBinaryOperatorFilter() {}
    virtual ~PointCloudBinaryOperatorFilter();
    virtual int testCell(double minX, double minY,
                         double minZ, double maxX,
                         double maxY, double maxZ) const = 0;

    virtual bool testPoint(float x, float y, float z) const = 0;

    virtual IPointCloudFilter* clone() const = 0;

    virtual void freeObject(void) = 0;

    virtual bool isInverted() const;
    virtual void setIsInverted(bool bInverted);

protected:
    PointCloudBinaryOperatorFilter(IPointCloudFilter* pLeft, IPointCloudFilter* pRight);
    PointCloudBinaryOperatorFilter(const PointCloudBinaryOperatorFilter& other);

    IPointCloudFilter*  mpLeftFilter;
    IPointCloudFilter*  mpRightFilter;

private:
    bool                mbIsInverted;

private:
    PointCloudBinaryOperatorFilter& operator = (const PointCloudBinaryOperatorFilter&);
};

class DBPOINTCLOUDOBJ_EXPORT PointCloudIntersectionFilter : public PointCloudBinaryOperatorFilter
{
public:
    PointCloudIntersectionFilter(IPointCloudFilter* pLeft, IPointCloudFilter* pRight);
    virtual ~PointCloudIntersectionFilter();
    virtual int testCell(double minX, double minY, double minZ,
                        double maxX, double maxY, double maxZ) const;
    virtual bool testPoint(float x, float y, float z) const;
    virtual IPointCloudFilter* clone() const;
    virtual void freeObject(void);
};

class DBPOINTCLOUDOBJ_EXPORT PointCloudUnionFilter : public PointCloudBinaryOperatorFilter
{
public:
    PointCloudUnionFilter(IPointCloudFilter* pLeft, IPointCloudFilter* pRight);
    virtual ~PointCloudUnionFilter();

    virtual int testCell(double minX, double minY, double minZ,
                        double maxX, double maxY, double maxZ) const;
    virtual bool testPoint(float x, float y, float z) const;
    virtual IPointCloudFilter* clone() const;
    virtual void freeObject(void);
};

class DBPOINTCLOUDOBJ_EXPORT PointCloudXORFilter : public PointCloudBinaryOperatorFilter
{
public:
    PointCloudXORFilter(IPointCloudFilter* pLeft, IPointCloudFilter* pRight);
    virtual ~PointCloudXORFilter();

    virtual int testCell(double minX, double minY, double minZ,
                        double maxX, double maxY, double maxZ) const;
    virtual bool testPoint(float x, float y, float z) const;
    virtual IPointCloudFilter* clone() const;
    virtual void freeObject(void);
};