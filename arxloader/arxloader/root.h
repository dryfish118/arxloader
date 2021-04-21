#pragma once
#include "../inc/arxmodule.h"

class CRoot : public IRoot
{
public:
  virtual void printInfo(const AcString& msg, MessageLevel = kInfo);
  virtual void printError(Acad::ErrorStatus es, const AcString& prefex = L"");
  virtual AcDbObjectId addToModelSpace(AcDbEntity* pEntity);
};
