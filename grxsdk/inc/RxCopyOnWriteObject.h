#ifndef _RXCOPYONWRITEOBJECT_H
#define _RXCOPYONWRITEOBJECT_H

#include "TD_PackPush.h"

#include "rxobject.h"
#include "rxboiler.h"

class FIRSTDLL_EXPORT OdRxCopyOnWriteObject : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdRxCopyOnWriteObject);
  
  OdRxCopyOnWriteObject(OdRxObject* pData);
  OdRxCopyOnWriteObject(const OdRxCopyOnWriteObject& other);
  ~OdRxCopyOnWriteObject();
  const OdRxCopyOnWriteObject& operator=(const OdRxCopyOnWriteObject& other);

protected:
  OdRxObject* write();
  const OdRxObject* read() const;
  void unshare();

private:
  void* m_pData;
};


#define ODRX_DECLARE_MEMBERS_READWRITE(CLASS_NAME, DATA_NAME)   \
    ODRX_DECLARE_MEMBERS(CLASS_NAME);                           \
    DATA_NAME* write()                                          \
    {                                                           \
        return (DATA_NAME*)OdRxCopyOnWriteObject::write();      \
    }                                                           \
    const DATA_NAME* read() const                               \
    {                                                           \
        return (const DATA_NAME*)OdRxCopyOnWriteObject::read(); \
    }

#include "TD_PackPop.h"

#endif//_RXCOPYONWRITEOBJECT_H
