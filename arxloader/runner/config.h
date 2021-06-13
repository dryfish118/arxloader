#pragma once

#include "arxcases.h"

class CConfig
{
public:
  CConfig();
  ~CConfig();

public:
  CString m_logPath;
  CArxCases m_ac;
  CStringArray m_filters;
  int m_bSave;
  int m_bGcad;
};
