#pragma once
#pragma pack (push, 8)

#include "DbConstraintsExports.h"  
#include "OdGraphNode.h"
#include <map>

class OdImpGraph;
class OdDbObject;

typedef std::map<OdGraphNode::Id, OdGraphNode*> NodeIdToPtrMap;

class DBCONSTRAINTS_EXPORT OdGraph : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdGraph);

  enum PartialUndoCode
  {
    kAddNodePartialUndoCode = 0,

    kRemoveNodePartialUndoCode,

    kModifyNodePartialUndoCode,

    kModifyNextNewNodeIdPartialUndoCode,
  };

  typedef NodeIdToPtrMap::iterator iterator;
  typedef NodeIdToPtrMap::const_iterator const_iterator;

  explicit OdGraph(bool bCreateImp = true);

  virtual ~OdGraph();

  OdDbObject* owningObject() const;

  void setOwningObject(OdDbObject* pObj);

  virtual OdResult applyPartialUndo(OdDbDwgFiler* pUndoFiler,
    PartialUndoCode code,
    OdGraphNode::Id &nodeId);

  OdResult addGraphNode(OdGraphNode* pNewNode);

  OdResult addGraphNode(OdGraphNode* pNewNode, OdGraphNode::Id nodeId);

  OdResult removeGraphNode(OdGraphNode* pNode, bool bDelete = true);

  OdGraphNode* getGraphNodePtr(OdGraphNode::Id nodeId) const;

  OdResult moveAndMerge(const OdArray<OdGraphNode*> & nodesToMove);

  OdResult merge(const OdGraph &graph);

  OdResult getRelatedNodes(const OdArray<OdGraphNode *> &nodes, OdArray<OdGraphNode *> &relatedNodes) const;

  iterator begin();

  const_iterator begin() const;

  iterator end();

  const_iterator end() const;

  size_t size() const;

  void clear(bool bDelete);

  virtual OdResult dwgOutFields(OdDbDwgFiler *pFiler) const;

  virtual OdResult dwgInFields(OdDbDwgFiler *pFiler);

  virtual OdResult dxfOutFields(OdDbDxfFiler *pFiler) const;

  virtual OdResult dxfInFields(OdDbDxfFiler *pFiler);

  virtual OdUInt32     graphId() const;

  virtual void              setGraphId(OdUInt32 id);

protected:
  OdImpGraph* mpImpGraph;
private:
  OdGraph(const OdGraph &graph);

  OdGraph &operator = (const OdGraph &graph);

  friend class OdGraphNode;
  friend class OdImpGraphNode;
  friend class OdImpGraph;
};

#pragma pack (pop)