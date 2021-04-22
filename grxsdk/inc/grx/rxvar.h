#pragma once
#include "GcDbCore2dDefs.h"
#include "gcadstrc.h"
#include "GcString.h"
#include "gcarray.h"
#include "rxobject.h"

class GcRxVariableReactor;
class GcRxImpVariable;
class GcRxImpVariablesDirectory;
class GcRxImpVariablesDictionary;
class GcRxImpVariableChangingEventArgs;
struct resbuf;

class GcRxVariable
{
public:
  enum StorageType
  {
    kStoragePerSession = 0,
    kStoragePerUser = 1,
    kStoragePerProfile = 2,
    kStoragePerDatabase = 3,
    kStoragePerViewport = 4
  };
  enum SecondaryType
  {
    kSecondaryTypeNone = 0,
    kSecondaryTypeBoolean = 1,
    kSecondaryTypeSymbolName = 2,
    kSecondaryTypeArea = 3,
    kSecondaryTypeDistance = 4,
    kSecondaryTypeAngle = 5,
    kSecondaryTypeUnitlessReal = 6,
    kSecondaryTypeLast = 6,
  };
  enum TypeFlags
  {
    kTypeFlagsNone = 0,
    kTypeFlagSpacesAllowed = 1,
    kTypeFlagDotMeansEmpty = 2,
    kTypeFlagNoUndo = 4,
    kTypeFlagsChatty = 8,
    kTypeDeprecated = 16,
  };
  struct Range
  {
    Range() :lowerBound(0), upperBound(0) {}
    Range(int lb, int ub) :lowerBound(lb), upperBound(ub) {}
    int lowerBound;
    int upperBound;
  };
  GCRXLIB_DECL const GCHAR* name() const;
  GCRXLIB_DECL short primaryType() const;
  GCRXLIB_DECL GcRxVariable::SecondaryType secondaryType() const;
  GCRXLIB_DECL GcRxVariable::StorageType storageType() const;
  GCRXLIB_DECL short typeFlags() const;
  GCRXLIB_DECL const Range* range() const;
  GCRXLIB_DECL Gcad::ErrorStatus setValue(const resbuf& value, void* ownerId = NULL, GcString* failReason = NULL);
  GCRXLIB_DECL Gcad::ErrorStatus getValue(resbuf& value) const;
  GCRXLIB_DECL bool isReadOnly(GcString* reason = NULL) const;
  GCRXLIB_DECL Gcad::ErrorStatus setIsReadOnly(bool value, void* ownerId, const GcString* reason = NULL);
  GCRXLIB_DECL void addReactor(GcRxVariableReactor* reactor);
  GCRXLIB_DECL bool isLocked() const;
  GCRXLIB_DECL void removeReactor(GcRxVariableReactor* reactor);
  GCRXLIB_DECL Gcad::ErrorStatus reset();

  GCRXLIB_DECL ~GcRxVariable();
private:
  friend class GcRxImpVariable;
  GcRxVariable(GcRxImpVariable*);
  GcRxImpVariable* m_pImp;
};

class GcRxVariablesDictionary
{
public:
  ~GcRxVariablesDictionary();
  GCRXLIB_DECL void addReactor(GcRxVariableReactor* reactor);
  GCRXLIB_DECL void removeReactor(GcRxVariableReactor* reactor);
  GCRXLIB_DECL const GcArray<GcString>& getAllNames() const;
  GCRXLIB_DECL GcRxVariable* getVariable(const GCHAR* name) const;
  GCRXLIB_DECL static GcRxVariablesDictionary* get();
  GCRXLIB_DECL Gcad::ErrorStatus reset(GcRxVariable::StorageType filter);


  GCRXLIB_DECL static bool getBool(const GCHAR* name, bool def);
  GCRXLIB_DECL static bool getBool(const GcRxVariable* pVar, bool def);
  GCRXLIB_DECL static Gcad::ErrorStatus setBool(const GCHAR* name, bool val);
  GCRXLIB_DECL static Gcad::ErrorStatus setBool(GcRxVariable*, bool val);
  GCRXLIB_DECL static short getInt16(const GCHAR* name, short def);
  GCRXLIB_DECL static short getInt16(const GcRxVariable* pVar, short def);
  GCRXLIB_DECL static Gcad::ErrorStatus setInt16(const GCHAR* name, short val);
  GCRXLIB_DECL static Gcad::ErrorStatus setInt16(GcRxVariable* pVar, short val);
  GCRXLIB_DECL static double getDouble(const GCHAR* name, double def);
  GCRXLIB_DECL static double getDouble(const GcRxVariable* pVar, double def);
  GCRXLIB_DECL static Gcad::ErrorStatus setDouble(const GCHAR* name, double val);
  GCRXLIB_DECL static Gcad::ErrorStatus setDouble(GcRxVariable* pVar, double val);
  GCRXLIB_DECL static GcString getString(const GCHAR* name);
  GCRXLIB_DECL static GcString getString(const GcRxVariable* pVar);
  GCRXLIB_DECL static Gcad::ErrorStatus setString(const GCHAR* name, const GCHAR* val);
  GCRXLIB_DECL static Gcad::ErrorStatus setString(GcRxVariable* pVar, const GCHAR* val);

private:
  GcArray<GcString> m_gcAr;
  friend class GcRxImpVariablesDictionary;
  GcRxVariablesDictionary(GcRxImpVariablesDictionary*);
  GcRxImpVariablesDictionary* m_pImp;
};
class GcRxVariableChangedEventArgs
{
public:
  GCRXLIB_DECL const resbuf& oldValue() const;
  GCRXLIB_DECL const resbuf& newValue() const;

  friend class GcRxImpVariableChangingEventArgs;
  GcRxVariableChangedEventArgs(GcRxImpVariableChangingEventArgs*);
protected:
  GcRxImpVariableChangingEventArgs* m_pImp;
private:
  resbuf m_resBuf;
};

class GcRxVariableChangingEventArgs : public GcRxVariableChangedEventArgs
{
public:
  GCRXLIB_DECL Gcad::ErrorStatus setNewValue(const resbuf& value, void* ownerId = NULL);
  GCRXLIB_DECL void veto(const GCHAR* failReason);
  GCRXLIB_DECL bool isResetting() const;
  GcRxVariableChangingEventArgs(GcRxImpVariableChangingEventArgs*);
};
class GSOFT_NO_VTABLE GcRxVariableReactor : public GcRxObject
{
public:
  virtual void changing(const GcRxVariable* sender, GcRxVariableChangingEventArgs& args)
  {
    (sender); (args);
  }
  virtual void changed(const GcRxVariable* sender, const GcRxVariableChangedEventArgs& args)
  {
    (sender); (args);
  }
};
