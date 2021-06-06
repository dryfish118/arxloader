#pragma once
#include "../inc/arxmodule.h"

class CDebugerImpl;

class CGlobalUtilImpl : public CGlobalUtil
{
  std::unique_ptr< CDebugerImpl> m_debuger;
public:
  CGlobalUtilImpl();

  virtual CDebuger* debuger() const;
  virtual AcDbObjectId addToModelSpace(AcDbEntity* pEntity);
};
