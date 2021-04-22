#pragma once

#include "DbPointCloudObjExports.h"
#include "rxobject.h"
#include "OdString.h"
#include "DbEntity.h"

class OdPointCloudViewFrustum;
class IPointCloudFilter;

class DBPOINTCLOUDOBJ_EXPORT OdViewFrustum
{
public:
  OdViewFrustum();
  ~OdViewFrustum();

  void setNearUpperRight(double x, double y, double z);
  void setNearUpperLeft(double x, double y, double z);
  void setNearLowerLeft(double x, double y, double z);
  void setNearLowerRight(double x, double y, double z);

  void setFarUpperRight(double x, double y, double z);
  void setFarUpperLeft(double x, double y, double z);
  void setFarLowerLeft(double x, double y, double z);
  void setFarLowerRight(double x, double y, double z);

  void nearUpperRight(double& x, double& y, double& z) const;
  void nearUpperLeft(double& x, double& y, double& z) const;
  void nearLowerLeft(double& x, double& y, double& z) const;
  void nearLowerRight(double& x, double& y, double& z) const;

  void farUpperRight(double& x, double& y, double& z) const;
  void farUpperLeft(double& x, double& y, double& z) const;
  void farLowerLeft(double& x, double& y, double& z) const;
  void farLowerRight(double& x, double& y, double& z) const;

  void setNearClip(bool clip);
  bool nearClip() const;

  void setFarClip(bool clip);
  bool farClip() const;

  OdPointCloudViewFrustum* asPointCloudFrustum() const;
private:
  void* m_pData;
};

class DBPOINTCLOUDOBJ_EXPORT OdPcPointFloat {
public:
    float m_x, m_y, m_z;
    DWORD m_argb;
};

class DBPOINTCLOUDOBJ_EXPORT OdPcPointDouble {
public:
    double m_x, m_y, m_z;
    DWORD m_argb;
};

class DBPOINTCLOUDOBJ_EXPORT OdPcPointAttributes
{
public:
    float   m_intensity;
    float   m_nx, m_ny, m_nz;
    BYTE    m_classification;
};

class DBPOINTCLOUDOBJ_EXPORT IOdPcDataBuffer {
public:
    virtual ~IOdPcDataBuffer()              = 0 {};

    virtual bool nativeDbl()                = 0;
    virtual bool resize(DWORD size)         = 0;
    virtual bool shrink(DWORD size)         = 0;
    virtual DWORD size() const              = 0;

    virtual OdPcPointFloat*  floatPoints () = 0;
    virtual OdPcPointDouble* doublePoints() = 0;

    virtual OdPcPointAttributes* pointAttributes() = 0;

    virtual bool floatPoint  (DWORD ptIx, OdPcPointFloat&  pt) const    = 0;
    virtual bool doublePoint (DWORD ptIx, OdPcPointDouble& pt) const    = 0;

    virtual bool setFloatPoint  (DWORD ptIx, OdPcPointFloat&  pt)       = 0;
    virtual bool setDoublePoint (DWORD ptIx, OdPcPointDouble& pt)       = 0;

    virtual bool offset   (double& x, double& y, double& z) const       = 0;
    virtual bool entityTransform(OdGeMatrix3d& matrix) const            = 0;

    virtual void copyFrom(IOdPcDataBuffer const & from)                 = 0;
};


class DBPOINTCLOUDOBJ_EXPORT IOdPcPointFilter {
public: 
    virtual void doFilter(
        const IOdPcDataBuffer& inBuffer, 
        IOdPcDataBuffer&       outBuffer) = 0;
};

class DBPOINTCLOUDOBJ_EXPORT IOdPcPointProcessor {
public:
    virtual bool cancel()   = 0;  

    virtual void abort()    = 0; 

    virtual void finished() = 0;

    virtual bool processPoints() = 0; 

    virtual IOdPcPointFilter*  filter() = 0;

    IOdPcDataBuffer* buffer();

    void setBuffer(IOdPcDataBuffer* buffer);

private:
    IOdPcDataBuffer* mpBuffer;
};

DBPOINTCLOUDOBJ_EXPORT OdResult oddbCreatePointCloudEntity(
    OdDbEntity*& newPointCloud,
    const OdString& indexFile,
    const OdString& sourceFile, 
    OdGePoint3d&    location,
    double          scale = 1.0,
    double          rotation = 0.0);

DBPOINTCLOUDOBJ_EXPORT OdResult oddbAttachPointCloudExEntity(
    OdDbObjectId&   newPointCloudExId,
    const OdString& pointCloudFile,
    OdGePoint3d&    location,
    double          scale = 1.0,
    double          rotation = 0.0,
    OdDbDatabase* pDb = NULL);

DBPOINTCLOUDOBJ_EXPORT OdResult oddbAttachPointCloudEntity(
    OdDbObjectId& newPointCloudId,
    const OdString& indexFile,
    const OdString& sourceFile,
    OdGePoint3d&    location,
    double          scale = 1.0,
    double          rotation = 0.0,
    OdDbDatabase*   pDb = NULL);


DBPOINTCLOUDOBJ_EXPORT OdResult oddbModifyPointCloudDataView(
    OdDbEntity* pEnt,
    IOdPcPointFilter* pFilter
    );

DBPOINTCLOUDOBJ_EXPORT OdResult oddbResetPointCloudDataView(
    OdDbEntity* pEnt
    );


DBPOINTCLOUDOBJ_EXPORT OdResult oddbProcessPointCloudData(
    OdDbEntity* pEnt,
    const OdDbExtents& ext,
    int levelOfDetail,
    IOdPcPointProcessor* pCallback);

DBPOINTCLOUDOBJ_EXPORT OdResult oddbProcessPointCloudData(
    OdDbEntity* pEnt,
    const OdViewFrustum& frustum,
    int levelOfDetail,
    IOdPcPointProcessor* pCallback);

DBPOINTCLOUDOBJ_EXPORT OdResult oddbSetPointCloudFilter(
    OdDbEntity* pEnt,
    IPointCloudFilter* pFilter);
