#pragma once
#include "../inc/gutil.h"

class CDebugerImpl;
class CDbHelperImpl;

class CGlobalUtilImpl
  : public AcRxObject
  , public CGlobalUtil
{
  std::unique_ptr<CDebugerImpl> m_debuger;
  std::unique_ptr<CDbHelperImpl> m_dbHelper;
public:
  CGlobalUtilImpl();

  virtual CDebuger* debuger() const;
  virtual CDbHelper* dbHelper() const;
};
