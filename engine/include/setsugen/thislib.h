#pragma once

// Setsugen headers
#include <setsugen/pch.h>
#include <setsugen/version.h>

namespace setsugen
{

class  ThisLibrary final
{
public:
  using UnloadEventCallback = std::function<void()>;

public:
  ThisLibrary(void* handle);

  ThisLibrary(const ThisLibrary&)            = delete;
  ThisLibrary(ThisLibrary&&)                 = delete;
  ThisLibrary& operator=(const ThisLibrary&) = delete;
  ThisLibrary& operator=(ThisLibrary&&)      = delete;

  std::string                                   get_path() const;
  void*                                         get_handle() const;
  const std::forward_list<UnloadEventCallback>& get_unload_events() const;

  void on_unload(const UnloadEventCallback& callback);

public:
  static ThisLibrary&              get();
  static std::tuple<int, int, int> get_version();

private:
  void* m_handle;

  std::forward_list<UnloadEventCallback> m_on_unload;
};

} // namespace setsugen
