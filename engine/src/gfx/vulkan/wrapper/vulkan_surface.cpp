#include "vulkan_surface.h"
#include "vulkan_instance.h"

#include "../../../wm/glfw/glfw_window.h"

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace setsugen::gfx::vulkan
{

Surface::Surface(VkSurfaceKHR surface, Instance& instance, Window& window)
    : m_instance(instance), m_window(window), m_surface(surface)
{}

Surface::~Surface()
{
  vkDestroySurfaceKHR(m_instance.handle(), m_surface, nullptr);
}

Surface::Builder::Builder(Instance& instance, Window& window) : m_instance(instance), m_window(window)
{}

Owner<Surface>
Surface::Builder::build()
{
  auto glfw_window = dynamic_cast<GlfwWindow*>(&m_window);
  if (glfw_window)
  {
    VkSurfaceKHR surface;
    glfwCreateWindowSurface(m_instance.handle(), (GLFWwindow*) glfw_window->handle(), nullptr, &surface);

    return Owner<Surface>{new Surface{surface, m_instance, m_window}};
  }

  throw InvalidOperationException("Window type not supported");
}

} // namespace setsugen::gfx::vulkan
