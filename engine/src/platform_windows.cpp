#include <setsugen/platform.h>

#ifdef SETSUGENE_WINDOWS
#  include <Windows.h>
#endif

#ifdef SETSUGENE_WINDOWS

namespace setsugen
{

String get_root_path()
{
  char buffer[MAX_PATH];
  GetModuleFileNameA(nullptr, buffer, MAX_PATH);
  String path = buffer;
  return path.substr(0, path.find_last_of("\\/"));
}

String get_assets_path()
{
  return get_root_path() + "/assets";
}

}  // namespace setsugen
#endif