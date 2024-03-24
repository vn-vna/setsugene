#pragma once

// Setsugen headers
#include <setsugen/application.h>
#include <setsugen/window.h>

#include "gfx_renderer.h"

namespace setsugen
{
class BasicApplication : virtual public Application
{
public:
  explicit BasicApplication(ApplicationDescription&& app_desc);
  ~BasicApplication() override;

  Void              run() override;
  SharedPtr<Logger> create_logger(const String& name) const override;
  Observer<Window>  get_window() override;
  Observer<Scene>   get_current_scene() override;

  Observer<VulkanApplication> get_vulkan_app();

private:
  ApplicationDescription m_description;

  SharedPtr<GlfwInstance>      m_glfw_instance;
  SharedPtr<Scene>             m_scene;
  SharedPtr<Window>            m_window;
  SharedPtr<Renderer>          m_scene_renderer;
  SharedPtr<LoggerFactory>     m_logger_factory;
  SharedPtr<VulkanApplication> m_vulkan_app;

  friend class ApplicationBuilder;
};
} // namespace setsugen::impl__
