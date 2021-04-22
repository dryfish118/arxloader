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

#pragma once

#ifndef OdDbAssocOffsetSurfaceActionBody_INCLUDED_
#define OdDbAssocOffsetSurfaceActionBody_INCLUDED_ /*!DOM*/

#include "DbAssocSurfaceActionBody.h"
#include "TD_PackPush.h"

/** \details
  <group Contraint_Classes>
  Library: Source code provided.
*/
class DBCONSTRAINTS_EXPORT OdDbAssocOffsetSurfaceActionBody : public OdDbAssocSurfaceActionBody
{
public:
	ODRX_DECLARE_MEMBERS(OdDbAssocOffsetSurfaceActionBody);

	/** \details
	Constructor creates an instance of this class.
	*/
  explicit OdDbAssocOffsetSurfaceActionBody(OdDbAssocCreateImpObject createImpObject = kOdDbAssocCreateImpObject);

	/** \details
	Destructor destroys an instance of this class.
	*/
	virtual ~OdDbAssocOffsetSurfaceActionBody();

  OdResult setDistance(double distance, const OdString& expression = OdString(),
    const OdString& evaluatorId = OdString());

  double distance(OdString& expression = dummyString(), OdString& evaluatorId = dummyString()) const;
  /** \details
  Creates associative array: action, action body, dependencies etc.
*/
  static OdResult createInstance(const OdDbObjectId& resultingSurfaceId,
    const OdDbObjectId& inputSurfaceId,
    double distance,
    bool bEnabled,
    OdDbObjectId& createdActionId
  );
};

typedef OdSmartPtr<OdDbAssocOffsetSurfaceActionBody> OdDbAssocOffsetSurfaceActionBodyPtr;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "TD_PackPop.h"

#endif
