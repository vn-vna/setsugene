#include <setsugen/window.h>

// Setsugen headers
#include <setsugen/application.h>
#include <setsugen/exception.h>

// Dpenedency headers
#include <glfw/glfw3.h>

// Private headers
#include "window_helper.h"

constexpr auto window_wait_event_timeout = 0.1;

namespace setsugen
{

using GlfwInstance = helper::GlfwInstance;

Window::Window(const String& title, Int32 width, Int32 height)
    : m_handler {nullptr},
      m_event_mode {WindowEventMode::Polling},
      m_command_queue {},
      m_thread {}
{
  auto app = Application::current_app();
  m_logger = app->create_logger(typeid(Window).name());

  m_thread = Thread {[=] {
    m_handler = GlfwInstance::get_instance().lock()->create_default_window();
    ::glfwSetWindowTitle((GLFWwindow*) m_handler, title.c_str());
    ::glfwSetWindowSize((GLFWwindow*) m_handler, width, height);

    if (!m_handler)
    {
      throw InvalidStateException("Cannot instantiate a new window");
    }

    m_logger->info("Window created successfully");

    try
    {
      auto render_target = RenderTarget::create_window_target(app->get_window());
      auto renderer      = RendererBuilder()
                          .with_render_target(render_target)
                          .with_vertex_shader("test.vert")
                          .with_fragment_shader("test.frag")
                          .add_color_blend(true, ColorFlag {true, true, true, true})
                          .build();
    }
    catch (const SetsugenException& e)
    {
      std::cerr << e.what() << std::endl;
    }
    catch (...)
    {
      std::cerr << "An unknown error occurred" << std::endl;
    }

    while (!::glfwWindowShouldClose((GLFWwindow*) m_handler))
    {
      m_command_queue.execute();

      switch (m_event_mode)
      {
      case WindowEventMode::Polling:
        ::glfwPollEvents();
        break;
      case WindowEventMode::Wait:
        ::glfwWaitEventsTimeout(window_wait_event_timeout);
        break;
      default:
        break;
      }
    }

    ::glfwDestroyWindow((GLFWwindow*) m_handler);
  }};
}

Window::~Window() = default;

Dim2I Window::get_size() const
{
  Int32 width, height;
  ::glfwGetWindowSize((GLFWwindow*) m_handler, &width, &height);
  return {width, height};
}

Dim2I Window::get_framebuffer_size() const
{
  Int32 width, height;
  ::glfwGetFramebufferSize((GLFWwindow*) m_handler, &width, &height);
  return {width, height};
}

Bool Window::is_visible() const
{
  return ::glfwGetWindowAttrib((GLFWwindow*) m_handler, GLFW_VISIBLE);
}

Void Window::set_event_mode(WindowEventMode event_mode)
{
  m_event_mode = event_mode;
}

Void Window::show_window()
{
  m_command_queue.push([=] { ::glfwShowWindow((GLFWwindow*) m_handler); });
}

Void Window::hide_window()
{
  m_command_queue.push([=] { ::glfwHideWindow((GLFWwindow*) m_handler); });
}

Void Window::set_title(const String& title)
{
  m_command_queue.push([=] { ::glfwSetWindowTitle((GLFWwindow*) m_handler, title.c_str()); });
}

Void Window::set_size(Int32 width, Int32 height)
{
  m_command_queue.push([=] { ::glfwSetWindowSize((GLFWwindow*) m_handler, width, height); });
}

Void Window::join()
{
  m_thread.join();
}

Void* Window::get_handler()
{
  return m_handler;
}

SharedPtr<Window> Window::create(const String& title, Int32 width, Int32 height)
{
  return std::make_shared<Window>(title, width, height);
}

}  // namespace setsugen