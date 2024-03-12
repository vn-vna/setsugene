#include <setsugen/exception.h>

#include "./window_helper.h"

namespace setsugen::helper
{

constexpr const Int32 default_window_width  = 640;
constexpr const Int32 default_window_height = 480;
constexpr const Char* default_window_title  = "SetsugenE Window";

WeakPtr<GlfwInstance> GlfwInstance::get_instance()
{
  static auto instance = std::make_shared<GlfwInstance>();
  return instance;
}

GlfwInstance::GlfwInstance()
    : m_mutex {}
{
  if (!::glfwInit())
  {
    throw InvalidStateException("Cannot initialize GLFW");
  }
}

GlfwInstance::~GlfwInstance()
{
  ::glfwTerminate();
}

Void GlfwInstance::instance_locked_execute(GlfwInstance::GlfwCommand command)
{
  ::std::lock_guard<std::mutex> lock {m_mutex};
  ::std::invoke(command);
}

GLFWwindow* GlfwInstance::create_default_window()
{
  ::std::lock_guard<std::mutex> lock {m_mutex};
  ::glfwDefaultWindowHints();
  ::glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  ::glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  ::glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  return glfwCreateWindow(
      default_window_width, default_window_height, default_window_title, nullptr, nullptr
  );
}

}  // namespace setsugen::helper