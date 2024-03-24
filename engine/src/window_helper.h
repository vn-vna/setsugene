// GLFW3 Headers
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace setsugen
{
class GlfwInstance
{
public:
  using GlfwCommand = Fn<Void()>;

  GlfwInstance();
  ~GlfwInstance();

  Void        instance_locked_execute(GlfwCommand command);
  GLFWwindow* create_default_window();

  static SharedPtr<GlfwInstance> create();
  static Observer<GlfwInstance>    get_instance();

private:
  Mutex m_mutex;
};
} // namespace setsugen::helper
