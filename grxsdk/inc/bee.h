#pragma once
#include <functional>


#define CONNECTION(a, b) a##b

#define VAR_LINK(var, squ) CONNECTION(var, squ)

class deferhelper {
public:
  deferhelper(std::function<void()>&& rf) :m_f(rf)
  {
  }
  ~deferhelper()
  {
    if (m_f)
    {
      m_f();
    }
  }

private:
  std::function<void()> m_f;
};

#define Defer(autocode) deferhelper VAR_LINK(F, __LINE__)([&](){autocode;})

