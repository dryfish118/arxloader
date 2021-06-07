#include "pch.h"
#include "config.h"
#include "xmlutil.h"

static CString documentsPath()
{
  LPITEMIDLIST pidl = nullptr;
  if (SUCCEEDED(SHGetSpecialFolderLocation(NULL, CSIDL_MYDOCUMENTS, &pidl)))
  {
    wchar_t szPath[MAX_PATH] = { 0 };
    if (SHGetPathFromIDList(pidl, szPath))
    {
      CoTaskMemFree(pidl);

      return szPath;
    }
  }

  return L"";
}

CConfig::CConfig()
{
  CXmlUtilDocReader* reader = xmlutilCreateXMLDocReader();
  if (reader->Load(appDir() + L"config.xml"))
  {
    CXmlUtilNode* root = reader->Root();
    if (root)
    {
      CXmlUtilNode* nodeLog = root->Child(L"Log file");
      if (nodeLog)
      {
        m_logFile = nodeLog->Value().c_str();
      }

      CXmlUtilNode* nodeCases = root->Child(L"Cases");
      if (nodeCases)
      {
        for (int i = 0; i < nodeCases->ChildCount(); i++)
        {
          m_filters.Add(nodeCases->Child(i)->Value().c_str());
        }
      }

      CXmlUtilNode* nodeFilters = root->Child(L"Filters");
      if (nodeFilters)
      {
        for (int i = 0; i < nodeFilters->ChildCount(); i++)
        {
          m_filters.Add(nodeFilters->Child(i)->Value().c_str());
        }
      }

      CXmlUtilNode* nodeSave = root->Child(L"Save");
      if (nodeSave)
      {
        m_bSave = nodeSave->Value() == L"0" ? 0 : 1;
      }
    }
  }
  reader->Release();

  if (m_logFile.IsEmpty())
  {
    m_logFile = documentsPath() + L"\\resuts.log";
  }
}

CConfig::~CConfig()
{
}
