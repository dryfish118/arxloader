#pragma once
#include "DbFiler.h"
#include "DbConstraintsExports.h"  

class OdImpGraphNode;
class OdGraph;

#include "TD_PackPush.h"

class DBCONSTRAINTS_EXPORT OdGraphNode : public OdRxObject/*,
                              public GcHeapOperators*/
{
public:
    ODRX_DECLARE_MEMBERS(OdGraphNode);

    virtual ~OdGraphNode();

    typedef OdUInt32 Id;

    enum {
		kNullId = 0};
	
    Id nodeId() const;

    OdGraph* owningGraph() const;

    OdResult connectNode (OdGraphNode* pNode);

    OdResult disconnectNode(OdGraphNode* pNode);

    OdResult disconnectAllNodes();

    OdResult getAdjacentNodes(OdArray<OdGraphNode*>& adjacentNodes) const;

    virtual void backup();

    bool isAdjacentTo(OdGraphNode *pNode) const;

    virtual OdResult nodeToBeConnectedNotification(OdGraphNode *pNode);

    virtual OdResult nodeToBeDisconnectedNotification(OdGraphNode* pNode);

    virtual OdResult nodeToBeMovedNotification(OdGraph *pGraph, OdArray<OdGraphNode *> & otherNodesToMove);

    virtual OdResult dwgOutFields(OdDbDwgFiler*) const;

    virtual OdResult dwgInFields (OdDbDwgFiler*);

    virtual OdResult dxfOutFields(OdDbDxfFiler*) const;

    virtual OdResult dxfInFields (OdDbDxfFiler*);

protected:
    explicit OdGraphNode(bool bCreateImp = true);

    OdImpGraphNode* mpImpGraphNode;

private:
  OdGraphNode(const OdGraphNode &node);

  OdGraphNode &operator = (const OdGraphNode &node);

friend class OdGraph;
friend class OdImpGraph;
};

#include "TD_PackPop.h"