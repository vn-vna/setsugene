#include "library.h"

using setsugen::ThisLibrary;

bool
on_load()
{
  thislib = new ThisLibrary(GetModuleHandle(NULL));
  return true;
}

bool
on_unload()
{
  bool success = true;
  for (auto& callback: thislib->get_unload_events())
  {
    try
    {
      callback();
    }
    catch (...)
    {
      success = false;
    }
  }

  delete thislib;
  return success;
}

#ifdef SETSUGENE_WINDOWS
BOOL WINAPI
DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
  switch (fdwReason)
  {
    case DLL_PROCESS_ATTACH: return on_load();
    case DLL_PROCESS_DETACH: return on_unload();
    default: return true;
  }
}
#endif

#pragma region Class_ThisLibrary_Definitions

namespace setsugen
{
ThisLibrary::ThisLibrary(void* handle) : m_handle(handle)
{}

std::string
ThisLibrary::get_path() const
{
  char path[MAX_PATH];
  GetModuleFileNameA((HMODULE) m_handle, path, MAX_PATH);
  return std::string(path);
}

void*
ThisLibrary::get_handle() const
{
  return m_handle;
}

const std::forward_list<ThisLibrary::UnloadEventCallback>&
ThisLibrary::get_unload_events() const
{
  return m_on_unload;
}

void
ThisLibrary::on_unload(const UnloadEventCallback& callback)
{
  m_on_unload.push_front(callback);
}

std::tuple<int, int, int>
ThisLibrary::get_version()
{
  return std::make_tuple(SETSUGENE_VERSION_MAJOR, SETSUGENE_VERSION_MINOR, SETSUGENE_VERSION_PATCH);
}

ThisLibrary&
ThisLibrary::get()
{
  return *thislib;
}
} // namespace setsugen

#pragma endregion
