#ifndef __ODGIPARAMETER_H__
#define __ODGIPARAMETER_H__

#include "../TD_PackPush.h"
#include "RxCopyOnWriteObject.h"

class OdGiParameterImp;

class FIRSTDLL_EXPORT OdGiParameter : public OdRxCopyOnWriteObject
{
  friend class OdGiParameterImp;

public:
  ODRX_DECLARE_MEMBERS_READWRITE(OdGiParameter, OdGiParameterImp);

  OdGiParameter(OdGiParameterImp* pImp);
  OdGiParameter(const OdGiParameter& other);
  const OdGiParameter& operator=(const OdGiParameter& other);
};

#include "../TD_PackPop.h"

#endif // !__ODGIPARAMETER_H__
