#pragma once

#include <memory>
#include "DbPointCloudObjExports.h"
#include "Ge/GeVector3d.h"

class OdPointCloudExtractedCylinderImp;

class DBPOINTCLOUDOBJ_EXPORT OdPointCloudExtractedCylinder
{
public:
  OdPointCloudExtractedCylinder();
  OdPointCloudExtractedCylinder(double radius, double height, OdGeVector3d axis = OdGeVector3d::kZAxis, OdGePoint3d origin = OdGePoint3d::kOrigin);
  virtual ~OdPointCloudExtractedCylinder();

  OdPointCloudExtractedCylinder(const OdPointCloudExtractedCylinder& o);
  bool operator == (const OdPointCloudExtractedCylinder& o) const;
  bool operator != (const OdPointCloudExtractedCylinder& o) const;
  OdPointCloudExtractedCylinder& operator = (const OdPointCloudExtractedCylinder& o);

  const static OdPointCloudExtractedCylinder kInvalid;
public:
  bool isValid() const;

  void clear();

  OdGeVector3d getAxis() const;

  void setAxis(OdGeVector3d axis);

  OdGePoint3d getOrigin() const;

  void setOrigin(OdGePoint3d origin);

  double getHeight() const;

  void setHeight(double height);

  double getRadius() const;

  void setRadius(double radius);

private: 
    //std::unique_ptr<OdPointCloudExtractedCylinderImp> m_pImp;//OdPointCloudExtractedCylinderImp未实现，暂时屏蔽，ACAD是放开的
};