#pragma once

// Setsugen headers
#include <setsugen/application.h>
#include <setsugen/entity.h>
#include <setsugen/window.h>
#include <setsugen/mesh.h>

#include "gfx_renderer.h"

namespace setsugen
{
class BasicApplication : virtual public Application
{
public:
  explicit BasicApplication(ApplicationDescription&& app_desc);
  ~BasicApplication() override;

  void                    run() override;
  std::shared_ptr<Logger> create_logger(const std::string& name) const override;
  Window*                 get_window() override;
  SceneManager*           get_scene_manager() override;

  VulkanApplication* get_vulkan_app();

private:
  ApplicationDescription m_description;

  std::unique_ptr<GlfwInstance>      m_glfw_instance;
  std::unique_ptr<Scene>             m_scene;
  std::unique_ptr<Window>            m_window;
  std::unique_ptr<Renderer>          m_scene_renderer;
  std::unique_ptr<LoggerFactory>     m_logger_factory;
  std::unique_ptr<VulkanApplication> m_vulkan_app;

  friend class ApplicationBuilder;
};
} // namespace setsugen
