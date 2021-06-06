#ifndef ARXMODULE_H
#define ARXMODULE_H

struct ITestCase
{
  virtual ~ITestCase() { }
  virtual const wchar_t* name() const = 0;
  virtual void run() = 0;
};

struct IArxModule
{
  virtual const wchar_t* moduleName() const = 0;
  virtual int casesCount() const = 0;
  virtual ITestCase* getCase(int i) const = 0;
};

#endif //ARXMODULE_H
