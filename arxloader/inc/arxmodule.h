#ifndef ARXMODULE_H
#define ARXMODULE_H

#include <arxHeaders.h>
#include <DbField.h>

typedef AcDbObjectPointer<AcDbLine> AcDbLinePtr;
typedef AcDbObjectPointer<AcDbMText> AcDbMtextPtr;
typedef AcDbObjectPointer<AcDbField> AcDbFieldPtr;

struct IRoot
{
  enum MessageLevel
  {
    kInfo = 0,
    kDebug,
    kWarning,
    kError,
  };

  virtual void printInfo(const AcString& msg, MessageLevel = kInfo) = 0;
  virtual void printError(Acad::ErrorStatus es, const AcString& prefex = L"") = 0;
  virtual AcDbObjectId addToModelSpace(AcDbEntity* pEntity) = 0;
};

struct ITestCase
{
  virtual ~ITestCase() { }
  virtual const wchar_t* name() const = 0;
  virtual void run(IRoot* root) = 0;
};

struct IArxModule
{
  virtual const wchar_t* moduleName() const = 0;
  virtual int casesCount() const = 0;
  virtual ITestCase* getCase(int i) const = 0;
};

#endif //ARXMODULE_H
