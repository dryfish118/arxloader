#pragma once

#include "cases.h"

class CConfig
{
public:
  CConfig();
  ~CConfig();

public:
  bool m_bSave;
  CString m_logPath;
  CArxCases m_ac;
  CStringArray m_filters;
  int m_iSave;
  int m_iGcad;
};
