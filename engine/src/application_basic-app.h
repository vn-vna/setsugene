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
  ~BasicApplication() = default;

public:
  Void              run() override;
  SharedPtr<Logger> create_logger(const String& name) const override;
  WeakPtr<Window>   get_window() const override;

public:
  WeakPtr<VulkanApplication> get_vulkan_app();

private:
  ApplicationDescription m_description;

  SharedPtr<Window>            m_window;
  SharedPtr<Renderer>          m_scene_renderer;
  SharedPtr<LoggerFactory>     m_logger_factory;
  SharedPtr<VulkanApplication> m_vulkan_app;

private:
  friend class ::setsugen::ApplicationBuilder;
};

}  // namespace setsugen::impl__