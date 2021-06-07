#ifndef ARXCASE_H
#define ARXCASE_H

class IArxCase
{
public:
  virtual const wchar_t* name() const = 0;
  virtual bool isEnabled() const = 0;
  virtual void setEnabled(bool e) = 0;
  virtual void run() = 0;
};

class IArxModule
{
public:
  virtual void putHandle(void* h) = 0;
  virtual void* getHandle() const = 0;
  virtual const wchar_t* moduleName() const = 0;
  virtual int caseCount() const = 0;
  virtual IArxCase* caseAt(int i) const = 0;
};

class IArxCases
{
public:
  virtual int moduleCount() const = 0;
  virtual IArxModule* moduleAt(int i) const = 0;
};

#endif //ARXCASE_H
