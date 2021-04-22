#pragma once
#include "rxvar.h"
#include "gdscodes.h"
class GcRxVariableCache : public GcRxVariableReactor
{
  virtual void changed(const GcRxVariable* sender, const GcRxVariableChangedEventArgs& args) override
  {
    const auto& rb = args.newValue();
    memcpy(&m_cache, &rb, sizeof(rb));
    if (rb.restype == RTSTR)
    {
      Gcad::ErrorStatus es = gcutUpdString(rb.resval.rstring, m_cache.resval.rstring);
      ASSERT(Gcad::eOk == es);
    }
  }
  resbuf m_cache;
  GcString m_name;
public:
  GcRxVariableCache(const GCHAR* name)
    :m_name(name)
    , m_cache({ 0 })
  {
    m_cache.restype = RTNONE;
    auto var = GcRxVariablesDictionary::get()->getVariable(name);
    if (var == nullptr)
      return;
    var->addReactor(this);
    Gcad::ErrorStatus es = var->getValue(m_cache);
    ASSERT(Gcad::eOk == es);
  }
  ~GcRxVariableCache()
  {
    auto var = GcRxVariablesDictionary::get()->getVariable(m_name.kwszPtr());
    if (var == nullptr)
      return;
    var->removeReactor(this);
  }
  bool getBool(bool def)
  {
    return !!getInt16(def ? 1 : 0);
  }
  short getInt16(short def)
  {
    ASSERT(m_cache.restype == RTSHORT || m_cache.restype == RTNONE);
    if (m_cache.restype != RTSHORT)
      return def;
    return m_cache.resval.rint;
  }
  double getDouble(double def)
  {
    ASSERT(m_cache.restype == RTREAL || m_cache.restype == RTNONE);
    if (m_cache.restype != RTREAL)
      return def;
    return m_cache.resval.rreal;
  }
  GcString getString()
  {
    GcString ret;
    ASSERT(m_cache.restype == RTSTR || m_cache.restype == RTNONE);
    if (m_cache.restype != RTSTR)
      return ret;
    return m_cache.resval.rstring;
  }
};