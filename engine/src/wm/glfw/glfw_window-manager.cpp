#include "glfw_window-manager.h"
#include "glfw_window.h"

#include <GLFW/glfw3.h>

namespace setsugen
{

GlfwWindowManager::GlfwWindowManager()
{
  if (!glfwInit())
  {
    throw InvalidOperationException("Failed to initialize GLFW");
  }
}

GlfwWindowManager::~GlfwWindowManager()
{
  glfwTerminate();
}

Void
GlfwWindowManager::poll_events()
{
  glfwPollEvents();
}

Void
GlfwWindowManager::wait_events()
{
  glfwWaitEvents();
}

Owner<Window>
GlfwWindowManager::create_window(UInt32 width, UInt32 height, const String& title)
{
  return Owner<Window>{new GlfwWindow{*this, width, height, title}};
}

} // namespace setsugen
