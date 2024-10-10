#pragma once

#include "context_fwd.inl"

#include "../application/app_fwd.inl"

namespace setsugen
{

class AppContext
{
public:
  AppContext(Application& app);
  ~AppContext();

  Bool         alive() const;
  Application& app();

  static Observer<AppContext> current();

private:
  static Atomic<Observer<AppContext>> s_current;

  Application& m_app;
  Bool         m_alive;
};

} // namespace setsugen
