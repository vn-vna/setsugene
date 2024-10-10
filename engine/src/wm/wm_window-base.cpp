#include <setsugen/wm.h>

namespace setsugen
{

Window::Window(WindowManager& manager) : m_manager(manager)
{
  m_manager.register_window(this);
}

Window::~Window() noexcept
{
  m_manager.unregister_window(this);
}

}