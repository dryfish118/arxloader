#ifndef ARXMODULE_H
#define ARXMODULE_H

#include <arxHeaders.h>
#include <DbField.h>

typedef AcDbObjectPointer<AcDbLine> AcDbLinePtr;
typedef AcDbObjectPointer<AcDbMText> AcDbMtextPtr;
typedef AcDbObjectPointer<AcDbField> AcDbFieldPtr;

class CDebuger;

#define ACRX_CLASS_GLOBALUTIL ACRX_T("Global Utility")

class CGlobalUtil : public AcRxObject
{
public:
  ACRX_DECLARE_MEMBERS_EXPIMP(CGlobalUtil, ACBASE_PORT);

  virtual CDebuger* debuger() const = 0;
  virtual AcDbObjectId addToModelSpace(AcDbEntity* pEntity) = 0;
};

#define globalUtil \
CGlobalUtil::cast(acrxSysRegistry()->at(ACRX_CLASS_GLOBALUTIL))

class CDebuger
{
public:
  enum MessageLevel
  {
    kInfo = 0,
    kDebug,
    kWarning,
    kError,
  };

  virtual void printInfo(const AcString& msg, MessageLevel = kInfo) = 0;
  virtual void printError(Acad::ErrorStatus es, const AcString& prefex = L"") = 0;

  virtual void failure_eq(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line) = 0;
  virtual void failure_ne(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line) = 0;
  virtual void failure_le(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line) = 0;
  virtual void failure_lt(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line) = 0;
  virtual void failure_ge(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line) = 0;
  virtual void failure_gt(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line) = 0;
  virtual void assert_eq(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line) = 0;
  virtual void assert_ne(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line) = 0;
  virtual void assert_le(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line) = 0;
  virtual void assert_lt(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line) = 0;
  virtual void assert_ge(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line) = 0;
  virtual void assert_gt(const ACHAR* m1, const ACHAR* m2, const ACHAR* file, const ACHAR* line) = 0;
};

#define gDebuger \
globalUtil->debuger()

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
