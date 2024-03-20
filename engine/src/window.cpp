#include <setsugen/window.h>

// Setsugen headers
#include <setsugen/application.h>
#include <setsugen/exception.h>
#include <setsugen/preprocessor.h>

// Dpenedency headers
#include <glfw/glfw3.h>

// Private headers
#include "window_helper.h"

constexpr auto window_wait_event_timeout = 0.1;

namespace setsugen
{
using GlfwInstance = helper::GlfwInstance;

Window::Window(const String& title, Int32 width, Int32 height)
  : m_handler{nullptr},
    m_event_mode{WindowEventMode::Polling}
{
  auto app = Application::current_app();
  m_logger = app->create_logger(typeid(Window).name());

  m_thread = Thread{
    [=]
    {
      GLFWwindow* handler = GlfwInstance::get_instance().lock()->create_default_window();
      m_handler           = handler;

      if (!m_handler)
      {
        throw InvalidStateException("Cannot instantiate a new window");
      }

      ::glfwSetWindowTitle(handler, title.c_str());
      ::glfwSetWindowSize(handler, width, height);

      m_logger->info("Window created successfully");

      const auto render_target = this->create_render_target();
      const auto renderer      = RendererBuilder::create()
                          ->with_render_target(render_target.get())
                          ->with_vertex_shader("test.vert")
                          ->with_fragment_shader("test.frag")
                          ->with_topology(Topology::TriangleList)
                          ->add_viewport({0.0f, 0.0f, 800.0f, 600.0f, 0.0f, 1.0f})
                          ->add_scissor({0.0f, 0.0f, 800.0f, 600.0f})
                          ->add_color_blend({false, ColorFlag{true, true, true, true}})
                          ->build();

      while (!glfwWindowShouldClose(handler))
      {
        m_command_queue.execute();

        switch (m_event_mode)
        {
          case WindowEventMode::Polling:
          {
            glfwPollEvents();
            break;
          }
          case WindowEventMode::Wait:
          {
            glfwWaitEventsTimeout(window_wait_event_timeout);
            break;
          }
          default: break;
        }

        renderer->render();
      }

      renderer->cleanup();
      glfwDestroyWindow(handler);
    }
  };
}

Window::~Window() = default;

SharedPtr<RenderTarget>
Window::create_render_target()
{
  return RenderTarget::create_window_target(this);
}

Dim2I
Window::get_size() const
{
  Int32 width, height;
  ::glfwGetWindowSize((GLFWwindow*) m_handler, &width, &height);
  return {width, height};
}

Dim2I
Window::get_framebuffer_size() const
{
  Int32 width, height;
  ::glfwGetFramebufferSize((GLFWwindow*) m_handler, &width, &height);
  return {width, height};
}

Bool
Window::is_visible() const
{
  return ::glfwGetWindowAttrib((GLFWwindow*) m_handler, GLFW_VISIBLE);
}

Void
Window::set_event_mode(WindowEventMode event_mode)
{
  m_event_mode = event_mode;
}

Void
Window::show_window()
{
  m_command_queue.push([=]
  {
    glfwShowWindow(static_cast<GLFWwindow*>(m_handler));
  });
}

Void
Window::hide_window()
{
  m_command_queue.push([=]
  {
    glfwHideWindow(static_cast<GLFWwindow*>(m_handler));
  });
}

Void
Window::set_title(const String& title)
{
  m_command_queue.push([=]
  {
    glfwSetWindowTitle(static_cast<GLFWwindow*>(m_handler), title.c_str());
  });
}

Void
Window::set_size(Int32 width, Int32 height)
{
  m_command_queue.push([=]
  {
    glfwSetWindowSize(static_cast<GLFWwindow*>(m_handler), width, height);
  });
}

Void
Window::join()
{
  m_thread.join();
}

Handler
Window::get_handler() const
{
  return m_handler;
}

SharedPtr<Window>
Window::create(const String& title, Int32 width, Int32 height)
{
  return std::make_shared<Window>(title, width, height);
}
} // namespace setsugen
