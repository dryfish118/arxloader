#pragma once
#include "DbAssocArrayItem.h"
#include "DbDimData.h"
class DBCONSTRAINTS_EXPORT OdDbArrayGripAppData : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdDbArrayGripAppData);

  OdDbArrayGripAppData(const OdGePoint3d& position = OdGePoint3d(),
    unsigned int modes = 0);

  virtual ~OdDbArrayGripAppData();

  const OdGePoint3d& position() const { return mPosition; }
    
  unsigned int modes() const { return mnModes; }

  void addGripMode(unsigned int mode) { mnModes |= mode; }

  void* getAppData(OdRxClass** ppClass = NULL) const
  {
    if (NULL != ppClass)
      *ppClass = mpAppDataClass;
    return mpAppData;
  }

  void setAppData(void* pData, OdRxClass* pClass)
  {
    mpAppData = pData; mpAppDataClass = pClass;
  }

  bool& arrowGrip() { return mbArrowGrip; }

  OdGeVector3d& xDir() { return mDirections[0]; }

  OdGeVector3d& yDir() { return mDirections[1]; }

  OdDbItemLocator& locator() { return mLocator; }

  const OdDbDimDataPtrArray& dimData() const { return mDimData; }

  void appendDimData(OdDbDimData* pData);

  void deleteDimData();

  void setBasePoint(OdGePoint3d &basePoint);

  const OdGePoint3d* basePoint() const { return mpBasePoint; }

private:
  OdGePoint3d mPosition;
  unsigned int mnModes;
  void* mpAppData;
  OdRxClass* mpAppDataClass;
  OdDbItemLocator mLocator;
  bool mbArrowGrip;
  OdGeVector3d mDirections[2];
  OdDbDimDataPtrArray mDimData;
  OdGePoint3d *mpBasePoint;
};
