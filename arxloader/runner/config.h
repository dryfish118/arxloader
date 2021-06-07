#pragma once

#include "arxcases.h"

class CConfig
{
public:
  CConfig();
  ~CConfig();

public:
  CString m_logFile;
  CArxCases m_ac;
  CStringArray m_filters;
  int m_bSave;
};
