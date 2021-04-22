/////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2021, Open Design Alliance (the "Alliance"). 
// All rights reserved. 
// 
// This software and its documentation and related materials are owned by 
// the Alliance. The software may only be incorporated into application 
// programs owned by members of the Alliance, subject to a signed 
// Membership Agreement and Supplemental Software License Agreement with the
// Alliance. The structure and organization of this software are the valuable  
// trade secrets of the Alliance and its suppliers. The software is also 
// protected by copyright law and international treaty provisions. Application  
// programs incorporating this software must include the following statement 
// with their copyright notices:
//   
//   This application incorporates Open Design Alliance software pursuant to a license 
//   agreement with Open Design Alliance.
//   Open Design Alliance Copyright (C) 2002-2021 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////

#ifndef DbAssocValueProviderPE_INCLUDED_
#define DbAssocValueProviderPE_INCLUDED_ /*!DOM*/


//#include "dbeval.h"
#include "DbConstraintsExports.h"
#include "RxObject.h"
#include "DbObject.h"
#include "TD_PackPush.h"
#include "grx/gsoft.h"

class OdDbEvalVariant;

/** \details
  This class provides the protocol extension pure virtual base class that declares the protocol 
  for getting and setting arbitrary simple scalar values.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdDbAssocValueProviderPE : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdDbAssocValueProviderPE);

  virtual bool canGetValue(const OdDbObject* pObject, const OdString& valueName)
  {
    GSOFT_UNREFED_PARAM(pObject);
    GSOFT_UNREFED_PARAM(valueName);
    return true;
  }

  virtual bool canSetValue(const OdDbObject* pObject, const OdString& valueName)
  {
    GSOFT_UNREFED_PARAM(pObject);
    GSOFT_UNREFED_PARAM(valueName);
    return false;
  }

  virtual OdResult getValue(const OdDbObject* pObject, const OdString& valueName, OdDbEvalVariant&  value);

  virtual OdResult setValue(OdDbObject* pObject, const OdString& valueName, const OdDbEvalVariant& newValue)
  {
    GSOFT_UNREFED_PARAM(pObject);
    GSOFT_UNREFED_PARAM(valueName);
    GSOFT_UNREFED_PARAM(newValue);
    return eNotHandled;
  }

  static OdResult getObjectValue(const OdDbObjectId&, const OdString& valueName, OdDbEvalVariant& value);
  static OdResult setObjectValue(const OdDbObjectId&, const OdString& valueName, const OdDbEvalVariant& value);
};


/** \details
  The typified smart pointer. This template class is specialization of the OdSmartPtr class 
  for the OdDbAssocValueProviderPE class.

  \sa
  <link smart_pointers, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdDbAssocValueProviderPE> OdDbAssocValueProviderPEPtr;

#include "TD_PackPop.h"

#endif

