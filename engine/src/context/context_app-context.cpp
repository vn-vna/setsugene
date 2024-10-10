#include <setsugen/application.h>
#include <setsugen/context.h>

namespace setsugen
{

Atomic<Observer<AppContext>> AppContext::s_current = nullptr;

AppContext::AppContext(Application& app) : m_app(app), m_alive(true)
{
  if (s_current)
  {
    throw InvalidStateException("AppContext already exists");
  }

  s_current = this;
}

AppContext::~AppContext()
{
  s_current = nullptr;
}

Bool
AppContext::alive() const
{
  return m_alive;
}

Application&
AppContext::app()
{
  return m_app;
}

} // namespace setsugen
