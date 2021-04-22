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

#ifndef DbAssocPatchSurfaceActionBody_INCLUDED_
#define DbAssocPatchSurfaceActionBody_INCLUDED_ /*!DOM*/
#include "DbAssocSurfaceActionBody.h"
#include "TD_PackPush.h"

/** \details
This class represents the base class OdDbAssocPatchSurfaceActionBody for the action bodies.

Library: Source code provided.
<group Contraint_Classes>
*/
class DBCONSTRAINTS_EXPORT OdDbAssocPatchSurfaceActionBody : public OdDbAssocPathBasedSurfaceActionBody
{
public:
	ODRX_DECLARE_MEMBERS(OdDbAssocPatchSurfaceActionBody);

	/** \details
	Constructor creates an instance of this class.
	*/
  explicit OdDbAssocPatchSurfaceActionBody(OdDbAssocCreateImpObject createImpObject = kOdDbAssocCreateImpObject);

	/** \details
	Destructor destroys an instance of this class.
	*/
	virtual ~OdDbAssocPatchSurfaceActionBody();

  OdResult setConstraintPoints(const OdArray<OdDbVertexRef> & constraintPoints);

  OdResult setConstraintCurves(const OdArray<OdDbEdgeRef> & constraintCurves);
  
  OdResult setContinuity(int continuity, const OdString& expression = OdString(),
    const OdString& evaluatorId = OdString());

  int continuity(OdString& expression = dummyString(), OdString& evaluatorId = dummyString()) const;

  OdResult getContinuityGripPoint(OdGePoint3d&  gripPt) const;

  OdResult setBulge(double bulge, const OdString& expression = OdString(),
    const OdString& evaluatorId = OdString());

  double bulge(OdString& expression = dummyString(), OdString& evaluatorId = dummyString()) const;

  static OdResult createInstance(const OdDbObjectId& patchSurfaceId,
    const OdArray<OdDbEdgeRef>& profileCurves,
    const OdArray<OdDbEdgeRef>& constraintCurves,
    const OdArray<OdDbVertexRef>&constraintPoints,
    int nContinuity,
    double dBulge,
    bool bEnabled,
    OdDbObjectId& createdActionId);

  static OdResult createInstance(const OdDbObjectId& patchSurfaceId,
    const OdArray<OdDbEdgeRef>& profileCurves,
    const OdArray<OdDbEdgeRef>& constraintCurves,
    const OdArray<OdDbVertexRef>&constraintPoints,
    bool bEnabled,
    OdDbObjectId& createdActionId);
};

typedef OdSmartPtr<OdDbAssocPatchSurfaceActionBody> OdDbAssocPatchSurfaceActionBodyPtr;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "TD_PackPop.h"

#endif



