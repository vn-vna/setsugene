#include <setsugen/window.h>

// Setsugen headers
#include <setsugen/application.h>
#include <setsugen/exception.h>
#include <setsugen/mesh.h>
#include <setsugen/preprocessor.h>

// Dpenedency headers
#include <GLFW/glfw3.h>
#include <setsugen/transform.h>

// Private headers
#include "setsugen/camera.h"
#include "setsugen/entity.h"
#include "window_helper.h"

constexpr auto window_wait_event_timeout = 0.1;

namespace setsugen
{
Window::Window(const std::string& title, int width, int height)
    : m_handler{nullptr}, m_event_mode{WindowEventMode::Polling}, m_window_ready_condition{}, m_window_ready_mutex{}
{
  auto app = Application::current_app();
  m_logger = app->create_logger("setsugen::Window");

  m_main_loop = [=, this]
  {
    try
    {
      this->window_thread_func(title.c_str(), width, height);
    }
    catch (const SetsugenException& e)
    {
      m_logger->error("An error occurred in the window thread: {}", e);
    }
    catch (...)
    {
      m_logger->error("An unknown error occurred in the window thread");
    }
  };
}

Window::~Window() = default;

std::unique_ptr<RenderTarget>
Window::create_render_target()
{
  return RenderTarget::create_window_target(this);
}

Dim2I
Window::get_size() const
{
  int width, height;
  glfwGetWindowSize((GLFWwindow*) m_handler, &width, &height);
  return {width, height};
}

Dim2I
Window::get_framebuffer_size() const
{
  int width, height;
  glfwGetFramebufferSize((GLFWwindow*) m_handler, &width, &height);
  return {width, height};
}

bool
Window::is_visible() const
{
  return ::glfwGetWindowAttrib((GLFWwindow*) m_handler, GLFW_VISIBLE);
}

void
Window::set_event_mode(WindowEventMode event_mode)
{
  m_event_mode = event_mode;
}

void
Window::show_window()
{
  m_command_queue.push([=, this] { glfwShowWindow(static_cast<GLFWwindow*>(m_handler)); });
}

void
Window::hide_window()
{
  m_command_queue.push([=, this] { glfwHideWindow(static_cast<GLFWwindow*>(m_handler)); });
}

void
Window::set_title(const std::string& title)
{
  m_command_queue.push([=, this] { glfwSetWindowTitle(static_cast<GLFWwindow*>(m_handler), title.c_str()); });
}

void
Window::set_size(int width, int height)
{
  m_command_queue.push([=, this] { glfwSetWindowSize(static_cast<GLFWwindow*>(m_handler), width, height); });
}

void
Window::join()
{
  m_thread.join();
}

void
Window::loop()
{
  m_thread = std::thread{m_main_loop};

  m_logger->trace("Waiting for window to be ready");

  std::unique_lock<std::mutex> lock{m_window_ready_mutex};
  m_window_ready_condition.wait(lock);

  m_logger->trace("Window is ready");
}

Window::Handler
Window::get_handler() const
{
  return m_handler;
}

void
Window::window_thread_func(const char* title, int width, int height)
{
  std::unique_ptr<Renderer> renderer;

  {
    std::lock_guard<std::mutex> lock{m_window_ready_mutex};

    m_logger->trace("Initializing window");

    GLFWwindow* handler = GlfwInstance::get_instance()->create_default_window();
    m_handler           = handler;

    if (!m_handler)
    {
      throw InvalidStateException{"Cannot instantiate a new window"};
    }

    glfwSetWindowTitle(handler, title);
    glfwSetWindowSize(handler, width, height);

    m_logger->trace("Window created successfully");

    renderer = RendererBuilder::create()
                        ->with_render_target(create_render_target())
                        ->with_vertex_shader("test.vert")
                        ->with_fragment_shader("test.frag")
                        ->with_topology(Topology::TriangleList)
                        ->add_viewport({0.0f, 0.0f, 800.0f, 600.0f, 0.0f, 1.0f})
                        ->add_scissor({0.0f, 0.0f, 800.0f, 600.0f})
                        ->add_color_blend({false, ColorFlag{true, true, true, true}})
                        ->set_vertex_buffer_layouts({{VertexElement::Position, VertexElement::Normal}})
                        ->set_uniform_buffer_layouts({{
                                                          UniformStage::Vertex,
                                                          {UniformElement::View, UniformElement::Projection},
                                                      },
                                                      {
                                                          UniformStage::Vertex,
                                                          {UniformElement::Model},
                                                      }})
                        ->build();

    m_renderer = renderer.get();

    m_logger->trace("Initializing window complete");
  }

  while (!glfwWindowShouldClose((GLFWwindow*) m_handler))
  {
    auto begin_time = std::chrono::high_resolution_clock::now();

    m_window_ready_condition.notify_all();
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

    m_renderer->render();
    auto crr_scene = Application::current_app()->get_scene_manager()->get_current_scene();
    if (crr_scene)
    {
      crr_scene->update();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin_time).count();
    auto sleep_time = 16 - elapsed_time;

    if (sleep_time > 0)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
    }
  }

  m_renderer->cleanup();
  glfwDestroyWindow((GLFWwindow*) m_handler);
}

std::unique_ptr<Window>
Window::create(const std::string& title, int width, int height)
{
  return std::make_unique<Window>(title, width, height);
}

} // namespace setsugen
