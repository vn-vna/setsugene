#pragma once

// Setsugen headers
#include <setsugen/pch.h>
#include <setsugen/version.h>

namespace setsugen
{

class ThisLibrary final
{
public:
  using UnloadEventCallback = Fn<Void()>;

public:
  ThisLibrary(Void* handle);

  ThisLibrary(const ThisLibrary&)            = delete;
  ThisLibrary(ThisLibrary&&)                 = delete;
  ThisLibrary& operator=(const ThisLibrary&) = delete;
  ThisLibrary& operator=(ThisLibrary&&)      = delete;

  String                                  get_path() const;
  Void*                                   get_handle() const;
  const ForwardList<UnloadEventCallback>& get_unload_events() const;

  Void on_unload(const UnloadEventCallback& callback);

public:
  static ThisLibrary&               get();
  static Tuple<Int32, Int32, Int32> get_version();

private:
  Void* m_handle;

  ForwardList<UnloadEventCallback> m_on_unload;
};

}  // namespace setsugen
