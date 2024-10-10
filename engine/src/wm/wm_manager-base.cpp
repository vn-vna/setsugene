#include <setsugen/wm.h>

#include "./glfw/glfw_window-manager.h"

namespace setsugen 
{

Observer<WindowManager> WindowManager::s_instance = nullptr;

WindowManager::WindowManager()
{
  if (s_instance != nullptr)
  {
    throw InvalidOperationException("WindowManager already exists");
  }

  s_instance = this;
}

WindowManager::~WindowManager()
{
  s_instance = nullptr;
}

Void 
WindowManager::register_window(Observer<Window> window)
{
  m_windows.insert(window);
}

Void
WindowManager::unregister_window(Observer<Window> window)
{
  m_windows.erase(window);
}

UnorderedSet<Observer<Window>>&
WindowManager::windows()
{
  return m_windows;
}

Owner<WindowManager>
WindowManager::create()
{
  return Owner<WindowManager>{new GlfwWindowManager{}};
}

}