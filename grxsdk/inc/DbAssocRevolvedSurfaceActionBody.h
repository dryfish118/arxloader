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

#ifndef DbAssocRevolvedSurfaceActionBody_INCLUDED_
#define DbAssocRevolvedSurfaceActionBody_INCLUDED_ /*!DOM*/
#include "DbAssocSurfaceActionBody.h"
#include "DbRevolveOptions.h"
#include "TD_PackPush.h"

/** \details
This class represents the base class OdDbAssocRevolvedSurfaceActionBody for the action bodies.

Library: Source code provided.
<group Contraint_Classes>
*/
class DBCONSTRAINTS_EXPORT OdDbAssocRevolvedSurfaceActionBody : public OdDbAssocPathBasedSurfaceActionBody
{
public:
	ODRX_DECLARE_MEMBERS(OdDbAssocRevolvedSurfaceActionBody);

	/** \details
	Constructor creates an instance of this class.
	*/
  explicit OdDbAssocRevolvedSurfaceActionBody(OdDbAssocCreateImpObject createImpObject = kOdDbAssocCreateImpObject);

	/** \details
	Destructor destroys an instance of this class.
	*/
	virtual ~OdDbAssocRevolvedSurfaceActionBody();

	//const OdDbSmartCenterMarkParametersPtr parameters() const;
	//OdDbSmartCenterMarkParametersPtr& parameters();
	//virtual void composeForLoad(OdDb::SaveType format, OdDb::DwgVersion version, OdDbAuditInfo* pAuditInfo);

  OdResult setRevolveAngle(double angle, const OdString& expression = OdString(),
    const OdString& evaluatorId = OdString());

  static OdResult createInstance(const OdDbObjectId& resultingSurfaceId,
    const OdDbPathRef& revolvePath,
    const OdDbPathRef& axisPath,
    double dAngle,
    double dStartAngle,
    const OdDbRevolveOptions& revolveOptions,
    bool bFlipAxisDirection,
    bool bEnabled,
    OdDbObjectId& createdActionId);

  double revolveAngle(OdString& expression = dummyString(), OdString& evaluatorId = dummyString()) const;
};

typedef OdSmartPtr<OdDbAssocRevolvedSurfaceActionBody> OdDbAssocRevolvedSurfaceActionBodyPtr;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "TD_PackPop.h"

#endif





