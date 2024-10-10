#pragma once

#include "wm_fwd.inl"

namespace setsugen
{

class WindowManager
{
public:
  friend class Window;

  WindowManager();
  ~WindowManager();

  virtual Void poll_events() = 0;
  virtual Void wait_events() = 0;

  virtual UnorderedSet<Observer<Window>>& windows();

  virtual Owner<Window> create_window(UInt32 width, UInt32 height, const String& title) = 0;

  static Observer<WindowManager> instance();
  static Owner<WindowManager>    create();

private:
  virtual Void register_window(Observer<Window> window);
  virtual Void unregister_window(Observer<Window> window);

  static Observer<WindowManager> s_instance;

  UnorderedSet<Observer<Window>> m_windows;
};

} // namespace setsugen
