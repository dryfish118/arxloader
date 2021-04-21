#include "pch.h"
#include "arxlistDlg.h"

class CDlg : public ITestCase
{
public:
  virtual const wchar_t* name() const
  {
    return L"Test CAcUiDialog";
  }

  virtual void run(IRoot* root)
  {
    HANDLE h = GetModuleHandle(L"dlg.dll");
    AfxSetResourceHandle((HINSTANCE)h);
    CarxlistDlg dlg;
    dlg.DoModal();
  }
};

class CArxModule : public IArxModule
{
  std::vector<ITestCase*> m_cases;
public:
  CArxModule()
  {
    m_cases.push_back(new CDlg);
  }
  ~CArxModule()
  {
    for (auto& it : m_cases)
    {
      delete it;
    }
  }

  virtual const wchar_t* moduleName() const
  {
    return L"Dlg test cases";
  }

  virtual int casesCount() const
  {
    return (int)m_cases.size();
  }

  virtual ITestCase* getCase(int i) const
  {
    return m_cases.at(i);
  }
};

extern "C" __declspec(dllexport) IArxModule* __stdcall arx_module()
{
  static CArxModule module;
  return &module;
}
