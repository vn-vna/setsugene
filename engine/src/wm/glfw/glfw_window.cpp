#include "glfw_window.h"

namespace setsugen
{

GlfwWindow::GlfwWindow(WindowManager& manager, UInt32 width, UInt32 height, const String& title)
    : Window(manager), m_width(width), m_height(height), m_title(title), m_window(nullptr)
{
  glfwDefaultWindowHints();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

  m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

  if (m_window == nullptr)
  {
    throw InvalidOperationException("Failed to create GLFW window");
  }

  glfwSetWindowUserPointer(m_window, this);
  glfwSetWindowTitle(m_window, m_title.c_str());
  glfwSetWindowSize(m_window, m_width, m_height);

  if (glfwRawMouseMotionSupported())
  {
    glfwSetInputMode(m_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
  }

  auto cursor_callback = [](GLFWwindow* window, Float64 x, Float64 y)
  {
    auto wm = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
    wm->on_cursor_move({static_cast<Int32>(x), static_cast<Int32>(y)});
  };

  glfwSetCursorPosCallback(m_window, cursor_callback);

  auto close_callback = [](GLFWwindow* window)
  {
    auto wm = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
    wm->on_close();
  };

  glfwSetWindowCloseCallback(m_window, close_callback);

  auto key_callback = [](GLFWwindow* window, Int32 key, Int32 scan, Int32 action, Int32 mods)
  {
    auto wm = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
    if (action == GLFW_PRESS)
    {
      wm->on_key_press(key, scan, mods);
    }
    else if (action == GLFW_RELEASE)
    {
      wm->on_key_release(key, scan, mods);
    }
  };

  glfwSetKeyCallback(m_window, key_callback);

  auto text_callback = [](GLFWwindow* window, UInt32 codepoint)
  {
    auto wm = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
    wm->on_text_input(codepoint);
  };

  glfwSetCharCallback(m_window, text_callback);

  auto mouse_enter_callback = [](GLFWwindow* window, Int32 entered)
  {
    auto wm = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
    wm->on_mouse_enter(entered);
  };

  glfwSetCursorEnterCallback(m_window, mouse_enter_callback);

  auto mouse_button_callback = [](GLFWwindow* window, Int32 button, Int32 action, Int32 mods)
  {
    auto wm = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
    if (action == GLFW_PRESS)
    {
      wm->on_mouse_button_press(button, mods);
    }
    else if (action == GLFW_RELEASE)
    {
      wm->on_mouse_button_release(button, mods);
    }
  };

  glfwSetMouseButtonCallback(m_window, mouse_button_callback);

  glfwSetWindowUserPointer(m_window, this);
}

GlfwWindow::~GlfwWindow()
{
  glfwDestroyWindow(m_window);
  glfwTerminate();
}

Void
GlfwWindow::show()
{
  glfwShowWindow(m_window);
}

Void
GlfwWindow::hide()
{
  glfwHideWindow(m_window);
}

Void
GlfwWindow::set_title(const String& title)
{
  m_title = title;
  glfwSetWindowTitle(m_window, m_title.c_str());
}

Void
GlfwWindow::set_size(UInt32 width, UInt32 height)
{
  m_width  = width;
  m_height = height;
  glfwSetWindowSize(m_window, m_width, m_height);
}

Void
GlfwWindow::set_position(UInt32 x, UInt32 y)
{
  glfwSetWindowPos(m_window, x, y);
}

Void
GlfwWindow::set_fullscreen(Bool fullscreen)
{
  if (fullscreen)
  {
    glfwSetWindowMonitor(m_window, glfwGetPrimaryMonitor(), 0, 0, m_width, m_height, GLFW_DONT_CARE);
  }
  else
  {
    glfwSetWindowMonitor(m_window, nullptr, 0, 0, m_width, m_height, GLFW_DONT_CARE);
  }
}

Void
GlfwWindow::set_cursor_visible(Bool visible)
{
  if (visible)
  {
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  }
  else
  {
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
  }
}

Void
GlfwWindow::set_cursor_grabbed(Bool grabbed)
{
  if (grabbed)
  {
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  }
  else
  {
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  }
}

Void
GlfwWindow::set_cursor_position(UInt32 x, UInt32 y)
{
  glfwSetCursorPos(m_window, x, y);
}

Void
GlfwWindow::set_resizable(Bool resizable)
{
  if (resizable)
  {
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
  }
  else
  {
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  }
}

Void
GlfwWindow::set_decorated(Bool decorated)
{
  if (decorated)
  {
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
  }
  else
  {
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
  }
}

Void
GlfwWindow::set_floating(Bool floating)
{
  if (floating)
  {
    glfwSetWindowAttrib(m_window, GLFW_FLOATING, GLFW_TRUE);
  }
  else
  {
    glfwSetWindowAttrib(m_window, GLFW_FLOATING, GLFW_FALSE);
  }
}

Void
GlfwWindow::set_minimized(Bool minimized)
{
  if (minimized)
  {
    glfwIconifyWindow(m_window);
  }
  else
  {
    glfwRestoreWindow(m_window);
  }
}

Void
GlfwWindow::set_maximized(Bool maximized)
{
  if (maximized)
  {
    glfwMaximizeWindow(m_window);
  }
  else
  {
    glfwRestoreWindow(m_window);
  }
}

Void
GlfwWindow::set_min_size(Dim2U size)
{
  glfwSetWindowSizeLimits(m_window, size.width(), size.height(), GLFW_DONT_CARE, GLFW_DONT_CARE);
}

Void
GlfwWindow::set_aspect_ratio(Dim2U aspect)
{
  glfwSetWindowAspectRatio(m_window, aspect.width(), aspect.height());
}

Void
GlfwWindow::set_opacity(Float32 opacity)
{
  glfwSetWindowOpacity(m_window, opacity);
}

Void
GlfwWindow::set_key_repeat(Bool repeat)
{
  if (repeat)
  {
    glfwSetInputMode(m_window, GLFW_REPEAT, GLFW_TRUE);
  }
  else
  {
    glfwSetInputMode(m_window, GLFW_REPEAT, GLFW_FALSE);
  }
}

Void*
GlfwWindow::handle()
{
  return m_window;
}

Dim2U
GlfwWindow::get_size() const
{
  Int32 width, height;
  glfwGetWindowSize(m_window, &width, &height);
  return {static_cast<UInt32>(width), static_cast<UInt32>(height)};
}

Dim2U
GlfwWindow::get_framebuffer_size() const
{
  Int32 width, height;
  glfwGetFramebufferSize(m_window, &width, &height);
  return {static_cast<UInt32>(width), static_cast<UInt32>(height)};
}

Dim2U
GlfwWindow::get_position() const
{
  Int32 x, y;
  glfwGetWindowPos(m_window, &x, &y);
  return {static_cast<UInt32>(x), static_cast<UInt32>(y)};
}

Bool
GlfwWindow::is_fullscreen() const
{
  return glfwGetWindowMonitor(m_window) != nullptr;
}

Bool
GlfwWindow::is_cursor_visible() const
{
  return glfwGetInputMode(m_window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL;
}

Bool
GlfwWindow::is_closing() const
{
  return glfwWindowShouldClose(m_window);
}

Void
GlfwWindow::on_cursor_move(Dim2I position)
{}

Void
GlfwWindow::on_close()
{
  this->hide();
  glfwSetWindowShouldClose(m_window, GLFW_TRUE);
}

Void
GlfwWindow::on_key_press(Int32 key, Int32 scan, Int32 mods)
{}

Void
GlfwWindow::on_key_release(Int32 key, Int32 scan, Int32 mods)
{}

Void
GlfwWindow::on_text_input(UInt32 codepoint)
{}

Void
GlfwWindow::on_mouse_button_press(Int32 button, Int32 mods)
{}

Void
GlfwWindow::on_mouse_button_release(Int32 button, Int32 mods)
{}

Void
GlfwWindow::on_mouse_enter(Bool entered)
{}

} // namespace setsugen
