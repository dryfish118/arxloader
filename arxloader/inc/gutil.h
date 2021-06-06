#ifndef GUTIL_H
#define GUTIL_H

#include <arxHeaders.h>
#include <DbField.h>

typedef AcDbObjectPointer<AcDbLine> AcDbLinePtr;
typedef AcDbObjectPointer<AcDbMText> AcDbMtextPtr;
typedef AcDbObjectPointer<AcDbField> AcDbFieldPtr;

class CDebuger;
class CDbHelper;

class CGlobalUtil
{
public:
  virtual CDebuger* debuger() const = 0;
  virtual CDbHelper* dbHelper() const = 0;
};

#define ACRX_CLASS_GLOBALUTIL ACRX_T("Global Utility")
#define globalUtil \
  dynamic_cast<CGlobalUtil*>(acrxSysRegistry()->at(ACRX_CLASS_GLOBALUTIL))

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

class CDbHelper
{
public:
  virtual AcDbObjectId addToModelSpace(AcDbEntity* pEntity) = 0;
};

#define gDbHelper \
globalUtil->dbHelper()

#endif //GUTIL_H
