#include "pch.h"
#include "config.h"
#include "xmlutil.h"

typedef std::set<std::wstring> StringArray;

CConfig::CConfig()
  : m_bSave(false)
  , m_iSave(0)
  , m_iGcad(1)
{
  CoInitialize(nullptr);

  CXmlUtilDocReader* reader = xmlutilCreateXMLDocReader();
  if (reader->Load(appDir() + L"config.xml"))
  {
    CXmlUtilNode* root = reader->Root();
    if (root && root->Name() == L"Config")
    {
      CXmlUtilNode* nodeLog = root->Child(L"Log");
      if (nodeLog)
      {
        m_logPath = nodeLog->Value().c_str();
      }

      CXmlUtilNode* nodeModuleCases = root->Child(L"ModuleCases");
      if (nodeModuleCases)
      {
        typedef std::unordered_map<std::wstring, StringArray> ModuleCases;
        ModuleCases mc;
        for (int i = 0; i < nodeModuleCases->ChildCount(); i++)
        {
          CXmlUtilNode* nodeModule = nodeModuleCases->Child(i);
          if (nodeModule->Name() == L"Module")
          {
            StringArray cases;
            for (int j = 0; j < nodeModule->ChildCount(); j++)
            {
              CXmlUtilNode* nodeCase = nodeModule->Child(j);
              if (nodeCase->Name() == L"Case")
              {
                cases.emplace(nodeCase->Value());
              }
            }
            mc.emplace(std::make_pair(nodeModule->Attribute(L"Name")->Value(), cases));
          }
        }

        if (!mc.empty())
        {
          for (int i = 0; i < m_ac.moduleCount(); i++)
          {
            IArxModule* m = m_ac.moduleAt(i);
            auto& it = mc.find(m->moduleName());
            if (it == mc.end())
            {
              for (int j = 0; j < m->caseCount(); j++)
              {
                m->caseAt(j)->setEnabled(false);
              }
            }
            else
            {
              for (int j = 0; j < m->caseCount(); j++)
              {
                m->caseAt(j)->setEnabled(it->second.end() != it->second.find(m->caseAt(j)->name()));
              }
            }
          }
        }
      }

      CXmlUtilNode* nodeFilters = root->Child(L"Filters");
      if (nodeFilters)
      {
        for (int i = 0; i < nodeFilters->ChildCount(); i++)
        {
          if (nodeFilters->Child(i)->Name() == L"Filter")
          {
            m_filters.Add(nodeFilters->Child(i)->Value().c_str());
          }
        }
      }

      CXmlUtilNode* nodeSave = root->Child(L"Save");
      if (nodeSave)
      {
        m_iSave = nodeSave->Value() == L"0" ? 0 : 1;
      }

      CXmlUtilNode* nodeGcad = root->Child(L"Gcad");
      if (nodeGcad)
      {
        m_iGcad = nodeGcad->Value() == L"0" ? 0 : 1;
      }
    }
  }
  reader->Release();

  CoUninitialize();

  if (m_logPath.IsEmpty())
  {
    m_logPath = documentsPath();
  }
}

CConfig::~CConfig()
{
  if (m_bSave)
  {
    CoInitialize(nullptr);

    CXmlUtilDocWriter* writer = xmlutilCreateXMLDocWriter();

    CXmlUtilNode* root = writer->CreateRoot(L"Config");

    CXmlUtilNode* nodeLog = root->CreateChild(L"Log");
    nodeLog->SetValue(m_logPath);

    if (m_iSave)
    {
      CXmlUtilNode* nodeModuleCases = root->CreateChild(L"ModuleCases");
      for (int i = 0; i < m_ac.moduleCount(); i++)
      {
        IArxModule* m = m_ac.moduleAt(i);
        StringArray sa;
        for (int j = 0; j < m->caseCount(); j++)
        {
          if (m->caseAt(j)->isEnabled())
          {
            sa.emplace(m->caseAt(j)->name());
          }
        }

        if (!sa.empty())
        {
          CXmlUtilNode* nodeModule = nodeModuleCases->CreateChild(L"Module");
          nodeModule->AddAttribute(L"Name", m->moduleName());
          for (auto& it : sa)
          {
            CXmlUtilNode* nodeCase = nodeModule->CreateChild(L"Case");
            nodeCase->SetValue(it.c_str());
          }
        }
      }
    }

    if (!m_filters.IsEmpty())
    {
      CXmlUtilNode* nodeFilters = root->CreateChild(L"Filters");
      for (int i = 0; i < m_filters.GetCount(); i++)
      {
        CXmlUtilNode* nodeFilter = nodeFilters->CreateChild(L"Filter");
        nodeFilter->SetValue(m_filters.GetAt(i));
      }
    }

    CXmlUtilNode* nodeSave = root->CreateChild(L"Save");
    nodeSave->SetValue(m_iSave ? L"1" : L"0");

    CXmlUtilNode* nodeGcad = root->CreateChild(L"Gcad");
    nodeGcad->SetValue(m_iGcad ? L"1" : L"0");

    writer->Save(appDir() + L"config.xml");
    writer->Release();
    CoUninitialize();
  }
}
