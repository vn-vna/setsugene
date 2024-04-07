#include <setsugen/window.h>

// Setsugen headers
#include <setsugen/application.h>
#include <setsugen/exception.h>
#include <setsugen/mesh.h>
#include <setsugen/preprocessor.h>

// Dpenedency headers
#include <glfw/glfw3.h>

// Private headers
#include "setsugen/camera.h"
#include "setsugen/entity.h"
#include "window_helper.h"

constexpr auto window_wait_event_timeout = 0.1;

namespace setsugen
{
Window::Window(const std::string& title, int width, int height)
    : m_handler{nullptr}, m_event_mode{WindowEventMode::Polling}
{
  auto app = Application::current_app();
  m_logger = app->create_logger("setsugen::Window");

  auto threadfn = [=, this]
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

  m_thread = std::thread{threadfn};
}

Window::~Window() = default;

std::shared_ptr<RenderTarget>
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

Window::Handler
Window::get_handler() const
{
  return m_handler;
}

void
Window::window_thread_func(const char* title, int width, int height)
{
  GLFWwindow* handler = GlfwInstance::get_instance()->create_default_window();
  m_handler           = handler;

  if (!m_handler)
  {
    throw InvalidStateException{"Cannot instantiate a new window"};
  }

  glfwSetWindowTitle(handler, title);
  glfwSetWindowSize(handler, width, height);

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

  const auto scene         = std::make_shared<Scene>("MAIN");
  const auto entity        = scene->create_entity("Root");
  const auto entity_camera = scene->create_entity("Camera");

  entity->add_component<Mesh>("/user/mesh/untitled.fbx");
  const auto camera = entity_camera->add_component<PerspectiveCamera>();
  scene->set_main_camera(camera);

  scene->load();

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

    renderer->render(scene.get());
  }

  scene->unload();

  renderer->cleanup();
  glfwDestroyWindow(handler);
}

std::unique_ptr<Window>
Window::create(const std::string& title, int width, int height)
{
  return std::make_unique<Window>(title, width, height);
}
} // namespace setsugen
