#include "library.h"

using setsugen::ThisLibrary;
using setsugen::String;
using setsugen::Int32;
using setsugen::Bool;
using setsugen::Void;

Bool
on_load()
{
  thislib = new ThisLibrary(GetModuleHandle(NULL));
  return true;
}

Bool
on_unload()
{
  Bool success = true;
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
ThisLibrary::ThisLibrary(Void* handle) : m_handle(handle)
{}

String
ThisLibrary::get_path() const
{
  char path[MAX_PATH];
  GetModuleFileNameA((HMODULE) m_handle, path, MAX_PATH);
  return String(path);
}

Void*
ThisLibrary::get_handle() const
{
  return m_handle;
}

const std::forward_list<ThisLibrary::UnloadEventCallback>&
ThisLibrary::get_unload_events() const
{
  return m_on_unload;
}

Void
ThisLibrary::on_unload(const UnloadEventCallback& callback)
{
  m_on_unload.push_front(callback);
}

std::tuple<Int32, Int32, Int32>
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
