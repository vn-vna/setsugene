#include <setsugen/application.h>
#include <setsugen/exception.h>

namespace setsugen
{
Atomic<Observer<Application>> Application::s_current_app = {};

Application::Application()
{
  if (s_current_app)
  {
    throw EngineException("An application is already running");
  }

  s_current_app = this;
}

Application::~Application()
{
  s_current_app = nullptr;
}

Observer<Application>
Application::current_app()
{
  return s_current_app;
}
}
