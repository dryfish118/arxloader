#ifndef DbSurfaceTrimInfo_INCLUDED_
#define DbSurfaceTrimInfo_INCLUDED_

#include "DbAssocActionParam.h"
#include "DbCompoundObjectId.h"

#include "TD_PackPush.h"

class ENTITY;
class DBCONSTRAINTS_EXPORT OdDbSurfaceTrimInfo
{
public:
  
  enum TrimRelation
  {
    outside_tool,
    inside_tool,
  };

  OdDbSurfaceTrimInfo();

  virtual ~OdDbSurfaceTrimInfo();

  void setTrimInfo(const OdDbCompoundObjectId& curveId, const OdGeVector3d & projVector, TrimRelation relation);

  void setTrimInfo(ENTITY *pWireBody, const OdGeVector3d& projVector, TrimRelation relation);

  void setTrimInfo(const OdDbCompoundObjectId &surfaceId, TrimRelation relation, const OdDbSubentId& subentId);

  void setTrimInfo(ENTITY *pAsmBody, TrimRelation relation, const OdDbSubentId& subentId);

  bool isCurve() const;

  ENTITY *toolBody() const;

  void setToolBody(ENTITY *pEntity);

  OdDbCompoundObjectId toolBodyId() const;

  void setToolBodyId(const OdDbCompoundObjectId &toolId);

  TrimRelation relation() const;

  void setRelation(TrimRelation relation);

  OdGeVector3d projVector() const;

  void setProjVector(const OdGeVector3d& projVector);

  OdDbSubentId faceSubentId() const;
};

#include "TD_PackPop.h"

#endif