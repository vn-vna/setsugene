#include <setsugen/application.h>
#include <setsugen/exception.h>

namespace setsugen
{
std::atomic<Application*> Application::s_current_app = {};

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

Application*
Application::current_app()
{
  return s_current_app;
}
} // namespace setsugen


#ifdef SETSUGENE_WINDOWS
#include <Windows.h>
#endif

#ifdef SETSUGENE_WINDOWS

namespace setsugen
{

std::string
Application::get_root_path()
{
  char buffer[MAX_PATH];
  GetModuleFileNameA(nullptr, buffer, MAX_PATH);
  std::string path = buffer;
  return path.substr(0, path.find_last_of("\\/"));
}

std::string
Application::get_assets_path()
{
  return get_root_path() + "/assets";
}

} // namespace setsugen
#endif
