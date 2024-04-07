#include <setsugen/platform.h>

#ifdef SETSUGENE_WINDOWS
#include <Windows.h>
#endif

#ifdef SETSUGENE_WINDOWS

namespace setsugen
{

std::string
get_root_path()
{
  char buffer[MAX_PATH];
  GetModuleFileNameA(nullptr, buffer, MAX_PATH);
  std::string path = buffer;
  return path.substr(0, path.find_last_of("\\/"));
}

std::string
get_assets_path()
{
  return get_root_path() + "/assets";
}

} // namespace setsugen
#endif
