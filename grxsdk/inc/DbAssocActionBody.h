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

#ifndef DbAssocActionBody_INCLUDED_
#define DbAssocActionBody_INCLUDED_ /*!DOM*/

#include "DbConstraintsExports.h"
#include "DbObject.h"
#include "DbAssocAction.h"
#include "DbAssocDependency.h"
#include "DbEntity.h"

#include "TD_PackPush.h"

/** \details
  This class is abstract base class for deriving custom action body.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT ODRX_ABSTRACT OdDbAssocActionBody : public OdDbObject
{
public: 
  ODRX_DECLARE_MEMBERS(OdDbAssocActionBody);

  /** \details
    Constructor creates an instance of this class.
  */
  explicit OdDbAssocActionBody(OdDbAssocCreateImpObject createImpObject = kOdDbAssocCreateImpObject);

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdDbAssocActionBody();

  /** \details
    Returns an object ID of the parent action. 
  */
  OdDbObjectId parentAction() const { return ownerId(); }

  static OdDbObjectId parentAction(const OdDbObjectId& actionBodyId);

  /** \details
    Returns the current status of this action. 
  */
  OdDbAssocStatus status() const;

  /** \details
    Sets the status for this action. 
  */
  OdResult setStatus(OdDbAssocStatus newStatus, 
                      bool           notifyOwningNetwork = true,
                      bool           setInOwnedActions   = false) const;

  /** \details
    Returns the logically owning association network, or kNull if it is the topmost. 
  */
  OdDbObjectId owningNetwork() const;

  /** \details
    Gets the dependencies of this action. The default implementation obtains all dependencies 
    owned by the base action class.
  */
  OdResult getDependencies(bool readDependenciesWanted, 
                           bool writeDependenciesWanted,
                           OdDbObjectIdArray& dependencyIds) const; 

  /** \details
    Adds a dependency for this action. The default implementation calls the corresponding method 
    of the parent class that owns this action.
  */
  OdResult addDependency(const OdDbObjectId& dependencyId, 
                         bool  setThisActionAsOwningAction = true) const;

  OdResult addDependency(OdRxClass*    pDependencyClass,
                         OdRxClass*    pDependencyBodyClass,
                         bool   isReadDep,
                         bool   isWriteDep,
                         int    order,
                         OdDbObjectId& dependencyId) const;

  /** \details
    Removes a dependency from this action. 
  */
  OdResult removeDependency(const OdDbObjectId& dependencyId, 
                            bool          alsoEraseIt) const;

  /** \details
    Clears all dependencies from this action. 
  */
  OdResult removeAllDependencies(bool alsoEraseThem) const;

  /** \details
    Evaluates those dependencies of the action that need to be evaluated
    by calling OdDbAssocDependency::evaluate(). Just a shortcut to OdDbAssocAction method.
  */
  OdResult evaluateDependencies() const;

  /** \details
    Checks whether the system is evaluating an action or a network of actions.
  */
  bool isActionEvaluationInProgress() const;

  /** \details
    Returns the current association evaluation callback set instance, or NULL if no action evaluation 
    is in progress.
  */
  OdDbAssocEvaluationCallback* currentEvaluationCallback() const;
  
  /** \details
    Creates ODDbAssocAction and ODDbAssocActionBody
    of the required class, makes the action own the action body and posts 
    both to the database of the given objectId.     
  */
  static OdResult createActionAndActionBodyAndPostToDatabase( OdRxClass* pActionBodyClass, const OdDbObjectId& objectId, OdDbObjectId& createdActionId, OdDbObjectId& createdActionBodyId);

  OdResult removeAllParams(bool alsoEraseThem) const;

  int paramCount() const;

  const OdDbObjectIdArray& ownedParams() const;

  
public: 
  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdDbAssocAction::evaluate() method).
  */
  virtual void evaluateOverride() = 0;

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdDbAssocAction::getDependencies() method).

    \remarks 
	Not implemented
  */
  virtual OdResult getDependenciesOverride(bool readDependenciesWanted,
                                   bool writeDependenciesWanted,
                                   OdDbObjectIdArray& dependencyIds) const
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdDbAssocAction::getDependentObjects() method).

    \remarks 
	Not implemented
  */
  virtual OdResult getDependentObjectsOverride(bool readDependenciesWanted,
                                       bool writeDependenciesWanted,
                                       OdDbObjectIdArray& objectIds) const
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdDbAssocAction::removeAllDependencies() method).

    \remarks 
	Not implemented
  */
  virtual OdResult removeAllDependenciesOverride(bool alsoEraseThem)
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdDbAssocAction::isOwnedDependency() method).

    \remarks 
	Not implemented
  */
  virtual OdResult isOwnedDependencyOverride(const OdDbAssocDependency* pDependency, 
                                             bool& isOwnedDependency) const
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdDbAssocAction::isExternalDependency() method).

    \remarks 
	Not implemented
  */
  virtual OdResult isExternalDependencyOverride(const OdDbAssocDependency* pDependency, 
                                                      bool& isExternalDependency) const
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdDbAssocAction::hasDependencyCachedValue() method).

    \remarks 
	Not implemented
  */
  virtual OdResult hasDependencyCachedValueOverride(const OdDbAssocDependency* pDependency,
                                                             bool& hasDepCachedValue) const
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdDbAssocAction::isRelevantDependencyChange() method).

    \remarks 
	Not implemented
  */
  virtual OdResult isRelevantDependencyChangeOverride(const OdDbAssocDependency* pDependency,
                                                      bool& isRelevantDepChange) const
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdDbAssocAction::areDependenciesOnTheSameThing() method).

    \remarks 
	Not implemented
  */
  virtual OdResult areDependenciesOnTheSameThingOverride(const OdDbAssocDependency* pDependency1,
                                                         const OdDbAssocDependency* pDependency2,
                                                         bool& areDependentOnSameThing) const
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdDbAssocAction::areDependenciesEqual() method).

    \remarks 
	Not implemented
  */
  virtual OdResult areDependenciesEqualOverride(const OdDbAssocDependency* pDependency1,
                                                const OdDbAssocDependency* pDependency2,
                                                bool& areEqual) const
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdDbAssocAction::evaluateDependency() method).

    \remarks 
	Not implemented
  */
  virtual OdResult evaluateDependencyOverride(OdDbAssocDependency* pDependency)
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdDbAssocAction::dependentObjectCloned() method).

    \remarks 
	Not implemented
  */
  virtual OdResult dependentObjectClonedOverride(const OdDbAssocDependency* pDependency, 
                                                 const OdDbObject*          pDbObj, 
                                                 const OdDbObject*          pNewObj);

  /** \details
    Method is called by the corresponding method of the parent action which owns this action body.

	\remarks 
	Not implemented

    \sa
    <link OdDbAssocAction::addMoreObjectsToDeepClone@OdDbIdMapping&@OdDbObjectIdArray&@const,OdDbAssocAction::addMoreObjectsToDeepClone() method>

  */
  virtual OdResult addMoreObjectsToDeepCloneOverride(OdDbIdMapping& idMap, 
                                                     OdDbObjectIdArray& additionalObjectsToClone) const;

  /** \details
    Method is called by the corresponding method of the parent action which owns this action body.

    \sa
    <link OdDbAssocAction::postProcessAfterDeepClone@OdDbIdMapping&, OdDbAssocAction::postProcessAfterDeepClone()>

    \remarks 
	Not implemented
  */
  virtual OdResult postProcessAfterDeepCloneOverride(OdDbIdMapping& idMap) 
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdDbAssocAction::postProcessAfterDeepCloneCancel() method).

    \remarks 
	Not implemented
  */
  virtual OdResult postProcessAfterDeepCloneCancelOverride(OdDbIdMapping& idMap)
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdDbAssocAction::ownedDependencyStatusChanged() method).

    \remarks 
	Not implemented
  */
  virtual OdResult ownedDependencyStatusChangedOverride(OdDbAssocDependency* pOwnedDependency, 
                                                        OdDbAssocStatus      previousStatus)
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdDbAssocAction::isEqualTo() method).

    \remarks Not implemented
  */
  virtual OdResult isEqualToOverride(const OdDbAssocAction* pOtherAction, bool& isEqual) const
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdDbAssocAction::evaluationPriority() method).

    \remarks Not implemented
  */
  virtual OdResult evaluationPriorityOverride(OdDbAssocEvaluationPriority& priority) const
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdDbAssocAction::getDependentActionsToEvaluate() method).

    \remarks Not implemented
  */
  virtual OdResult getDependentActionsToEvaluateOverride(OdDbActionsToEvaluateCallback* pActionsToEvaluateCallback) const
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdDbAssocAction::transformActionBy() method).

    \remarks Not implemented
  */
  virtual OdResult transformActionByOverride(const OdGeMatrix3d&)
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdDbAssocAction::dragStatus() method).

    \remarks Not implemented
  */
  virtual OdResult dragStatusOverride(const OdDb::DragStat status)
  { return eNotImplemented; }

  virtual OdResult removeActionsControllingObjectOverride(OdDbObject* pControlledObject);

  virtual void auditAssociativeDataOverride(OdDbAssocStatus& parentActionHandling);

  virtual OdResult notificationOverride(class OdDbAssocNotificationData* pNotificationData);

  virtual OdResult collectPersSubentNamingDataOverride(OdDbPersStepIdArray& stepIds,OdDbPersSubentIdArray& persSubentIds) const;

  virtual OdResult clonePersSubentNamingDataOverride(class OdDbAssocPersSubentManagerCloner* pCloner);
  /** \details
    Reads the .dwg file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler);

  /** \details
    Writes the .dwg file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual OdResult dwgOutFields(OdDbDwgFiler* pFiler) const;

  /** \details
    Reads the .dxf file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dxfInFields(OdDbDxfFiler* pFiler);

  /** \details
    Writes the .dxf file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual OdResult dxfOutFields(OdDbDxfFiler* pFiler) const;
  
  /** \details
    Just a shortcut to OdDbAssocAction method.
  */
  OdResult getValueParam( const OdString& paramName,
                          OdDbEvalVariant& value,
                          OdString& expression,
                          OdString& evaluatorId,
                          int valueIndex = 0) const; 


  /** \details
    Just a shortcut to OdDbAssocAction method.
  */
  OdResult setValueParam( const OdString& paramName,
                          const OdDbEvalVariant& value,
                          const OdString& expression,
                          const OdString& evaluatorId,
                          OdString& errorMessage,
                          bool silentMode,
                          int valueIndex = 0) const;

  /** \details
    Just a shortcut to OdDbAssocAction method.
  */
  OdDbObjectId paramAtName(const OdString& paramName, int index = 0) const;

  /** \details
    Just a shortcut to OdDbAssocAction method.
  */
  OdValue::UnitType valueParamUnitType(const OdString& paramName) const;

  /** \details
    Just a shortcut to OdDbAssocAction method.
  */
  OdResult setValueParamUnitType(const OdString& paramName, OdValue::UnitType unitType) const;
  /** \details
    Just a shortcut to OdDbAssocAction method.
  */
  OdResult addParam( const OdString& paramName, 
                     OdRxClass* pParamClass, 
                     OdDbObjectId& paramId, 
                     int& paramIndex) const;

  OdResult addParam(const OdDbObjectId& paramId, int& paramIndex) const;

  OdResult removeParam(const OdDbObjectId& paramId, bool alsoEraseIt) const;

  const OdDbObjectIdArray& paramsAtName(const OdString& paramName) const;

  OdDbObjectId paramAtIndex(int paramIndex) const;

  OdResult getValueParamArray(const OdString&    paramName,
                              OdArray<OdDbEvalVariant>& values,
                              OdArray<OdString>&    expressions,
                              OdArray<OdString>&    evaluatorIds) const;

  OdResult setValueParamArray(const OdString&     paramName,
                              const OdArray<OdDbEvalVariant>& values,
                              const OdArray<OdString>&   expressions,
                              const OdArray<OdString>&   evaluatorIds,
                              OdArray<OdString>&      errorMessages,
                              bool     silentMode) const;

  OdResult removeValueParam(const OdString& paramName) const;

  OdResult valueParamInputVariables(const OdString& paramName, OdDbObjectIdArray& variableIds) const;

  OdResult setValueParamControlledObjectDep(const OdString& paramName, const OdDbObjectId& controlledObjectDepId) const;

  OdResult updateValueParamControlledObject(const OdString& paramName) const;

  OdResult updateValueParamFromControlledObject(const OdString& paramName) const;

  OdResult updateAllObjectsControlledByValueParams() const;

  OdResult transformAllConstantGeometryParams(const OdGeMatrix3d& transform) const;

  OdResult scaleAllDistanceValueParams(double scaleFactor) const;

  bool hasAnyErasedOrBrokenDependencies() const;

  static OdResult getActionBodiesOnObject(const OdDbObject*  pObject,
                                          bool               ignoreInternalActions, 
                                          bool               ignoreSuppressedActions,
                                          OdDbObjectId*      pWriteOnlyActionBodyId,
                                          OdDbObjectIdArray* pReadWriteActionBodyIds,
                                          OdDbObjectIdArray* pReadOnlyActionBodyIds = NULL);
  /** \details
    Just a shortcut to OdDbAssocAction method.
  */
  void ownedValueParamNames(OdStringArray& paramNames) const;

  virtual OdStringArray compareWith(const OdDbObjectId bodyIDToCompare, OdDb::DwgVersion filerVersion = OdDb::kDHL_CURRENT) const;
protected:
  /*!DOM*/
  friend class OdDbImpAssocAction;
  /*!DOM*/
  class OdDbImpAssocActionBody* m_pImpObj;
};
/** \details
  The typified smart pointer. This template class is specialization of the OdSmartPtr class 
  for the OdDbAssocActionBody class.

  \sa
  <link smart_pointers, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdDbAssocActionBody> OdDbAssocActionBodyPtr;

DBCONSTRAINTS_EXPORT OdString& dummyString();

#include "TD_PackPop.h"
#endif

