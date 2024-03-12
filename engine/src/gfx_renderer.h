#pragma once

#include <setsugen/application.h>
#include <setsugen/exception.h>
#include <setsugen/gfx.h>
#include <setsugen/logger.h>
#include <setsugen/window.h>

#include "window_helper.h"

namespace setsugen
{

class VulkanApplication;
class VulkanWindowRenderTarget;
class ShaderCompiler;

class ShaderModule
{
public:
  ShaderModule(const String& module_name);
  ~ShaderModule();

  VkShaderModule get_module() const;

private:
  VkShaderModule             m_shader_module;
  WeakPtr<VulkanApplication> m_vulkan_app;
};

class VulkanApplication

{
public:
  struct QueueFamilyIndices
  {
    Optional<UInt32> graphics_family;
    Optional<UInt32> present_family;

    Bool is_complete() const
    {
      return graphics_family.has_value() &&  //
             present_family.has_value();
    }
  };

public:
  VulkanApplication();
  ~VulkanApplication();

public:
  static WeakPtr<VulkanApplication>   get_current();
  static SharedPtr<VulkanApplication> create_instance();

public:
  VkPhysicalDevice   get_physical_device();
  VkDevice           get_logical_device();
  VkInstance         get_instance();
  QueueFamilyIndices get_queue_family_indices();

private:
  Void                initialize_instance();
  DArray<const Char*> get_instance_layers();
  Bool                check_layers_support(const DArray<const Char*>& layers);
  DArray<const Char*> get_instance_extensions();
  Bool                check_extensions_support(const DArray<const Char*>& extensions);
  Void                setup_debug_messenger();
  Void                query_physical_devices();
  Bool                check_physical_device_extensions(VkPhysicalDevice device);
  Int32               auto_select_physical_device();
  QueueFamilyIndices  find_queue_families(VkPhysicalDevice device);
  Void                create_logical_device();

private:
  VkInstance               m_instance;
  VkDebugUtilsMessengerEXT m_debug_messenger;
  DArray<VkPhysicalDevice> m_physical_devices;
  Int32                    m_physical_device_index;
  QueueFamilyIndices       m_queue_family_indices;
  VkDevice                 m_logical_device;
  VkQueue                  m_graphics_queue;
  VkQueue                  m_present_queue;
};

class VulkanWindowRenderTarget : virtual public RenderTarget
{
public:
  VulkanWindowRenderTarget(WeakPtr<Window> window);
  ~VulkanWindowRenderTarget() override;

  Void resize(Int32 width, Int32 height) override;
  Void present() override;

  Int32 width() const override;
  Int32 height() const override;

  RenderTargetType type() const override;

private:
  Void create_surface();
  Void create_swapchain();
  Void create_image_views();

private:
  WeakPtr<Window>            m_window;
  WeakPtr<VulkanApplication> m_vulkan_app;
  VkSurfaceKHR               m_surface;
  VkSurfaceFormatKHR         m_surface_format;
  VkPresentModeKHR           m_present_mode;
  VkSwapchainKHR             m_swapchain;
  DArray<VkImage>            m_swapchain_images;
  DArray<VkImageView>        m_swapchain_image_views;
  GLFWwindow*                m_window_handler;

  friend class VulkanWindowRenderer;
};

class VulkanWindowRenderer : virtual public Renderer
{
public:
  VulkanWindowRenderer(const RendererConfig& config);
  ~VulkanWindowRenderer() override;

public:
  static constexpr const Char* DEFAULT_VERTEX_SHADER   = "default";
  static constexpr const Char* DEFAULT_FRAGMENT_SHADER = "default";

private:
  Void create_graphics_pipeline(const RendererConfig& config);
  Void create_framebuffers(const RendererConfig& config);
  Void create_command_pool(const RendererConfig& config);
  Void create_command_buffers(const RendererConfig& config);

private:
  WeakPtr<VulkanApplication> m_vulkan_app;
  DArray<VkCommandBuffer>    m_command_buffers;
  VkCommandPool              m_command_pool;
  VkPipelineLayout           m_pipeline_layout;
  VkRenderPass               m_render_pass;
  VkPipeline                 m_pipeline;
  DArray<VkFramebuffer>      m_framebuffers;
};

}  // namespace setsugen
