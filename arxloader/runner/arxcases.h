#pragma once

class CArxCases : public IArxCases
{
  std::vector<IArxModule*> m_modules;
public:
  virtual ~CArxCases();
  virtual bool init();
  virtual void loadCases();
  virtual void saveCases();
  virtual int moduleCount() const;
  virtual IArxModule* moduleAt(int i) const;

private:
  void listModule(const wchar_t* path);
};

