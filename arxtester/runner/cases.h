#pragma once

class CArxCases : public IArxCases
{
  std::vector<IArxModule*> m_modules;
public:
  CArxCases();
  virtual ~CArxCases();

  virtual int moduleCount() const;
  virtual IArxModule* moduleAt(int i) const;

private:
  void listModule(const wchar_t* path);
};

