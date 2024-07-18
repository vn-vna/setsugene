#include <setsugen/exception.h>

#include "./window_helper.h"

namespace setsugen
{
constexpr auto default_window_width  = 640;
constexpr auto default_window_height = 480;
constexpr auto default_window_title  = "SetsugenE Window";

std::optional<GlfwInstance*> s_instance;

GlfwInstance*
GlfwInstance::get_instance()
{
  return s_instance.value();
}

GlfwInstance::GlfwInstance()
{
  if (!glfwInit())
  {
    throw InvalidStateException("Cannot initialize GLFW");
  }

  s_instance = this;
}

GlfwInstance::~GlfwInstance()
{
  glfwTerminate();
  s_instance = {};
}

void
GlfwInstance::instance_locked_execute(GlfwCommand command)
{
  std::lock_guard lock{m_mutex};
  invoke(command);
}

GLFWwindow*
GlfwInstance::create_default_window()
{
  std::lock_guard lock{m_mutex};
  glfwDefaultWindowHints();
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  return glfwCreateWindow(default_window_width, default_window_height, default_window_title, nullptr, nullptr);
}

std::unique_ptr<GlfwInstance>
GlfwInstance::create()
{
  return std::make_unique<GlfwInstance>();
}
} // namespace setsugen
