#pragma once

#include <setsugen/application.h>
#include <setsugen/exception.h>
#include <setsugen/gfx.h>
#include <setsugen/logger.h>
#include <setsugen/platform.h>
#include <setsugen/utilities.h>
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
  VkShaderModule              m_shader_module;
  VkDevice                    m_logical_device;
  Observer<VulkanApplication> m_vulkan_app;
};

class VulkanApplication

{
public:
  using ExtensionList = DArray<const Char*>;

  struct QueueFamilyIndices
  {
    Optional<UInt32> graphics_family;
    Optional<UInt32> present_family;

    Bool is_complete() const
    {
      return graphics_family.has_value() && //
             present_family.has_value();
    }
  };

  VulkanApplication();
  ~VulkanApplication();

  static Observer<VulkanApplication>  get_current();
  static SharedPtr<VulkanApplication> create();

  VkPhysicalDevice   get_physical_device() const;
  VkDevice           get_logical_device() const;
  VkInstance         get_instance() const;
  QueueFamilyIndices get_queue_family_indices() const;
  VkQueue            get_graphics_queue() const;
  VkQueue            get_present_queue() const;

private:
  Void               initialize_instance();
  ExtensionList      get_instance_layers();
  Void               setup_debug_messenger();
  Void               query_physical_devices();
  Int32              auto_select_physical_device();
  QueueFamilyIndices find_queue_families(VkPhysicalDevice device) const;
  Void               create_logical_device();

  static ExtensionList get_instance_extensions();
  static Bool          check_physical_device_extensions(VkPhysicalDevice device);
  static Bool          check_layers_support(const DArray<const Char*>& layers);
  static Bool          check_extensions_support(const DArray<const Char*>& extensions);

  VkInstance               m_instance;
  VkDebugUtilsMessengerEXT m_debug_messenger;
  DArray<VkPhysicalDevice> m_physical_devices;
  Int32                    m_physical_device_index;
  QueueFamilyIndices       m_queue_family_indices;
  VkDevice                 m_logical_device;
  VkQueue                  m_graphics_queue;
  VkQueue                  m_present_queue;

  static Atomic<Observer<VulkanApplication>> s_current_app;
};

class VulkanWindowRenderTarget : virtual public RenderTarget
{
public:
  VulkanWindowRenderTarget(Observer<Window> window);
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
  Observer<Window>            m_window;
  Observer<VulkanApplication> m_vulkan_app;
  VkDevice                    m_logical_device;
  VkSurfaceKHR                m_surface;
  VkSurfaceFormatKHR          m_surface_format;
  VkPresentModeKHR            m_present_mode;
  VkSwapchainKHR              m_swapchain;
  VkExtent2D                  m_swapchain_extent;
  DArray<VkImage>             m_swapchain_images;
  DArray<VkImageView>         m_swapchain_image_views;
  GLFWwindow*                 m_window_handler;

  friend class VulkanWindowRenderer;
};

class VulkanWindowRenderer : virtual public Renderer
{
public:
  VulkanWindowRenderer(const RendererConfig& config);
  ~VulkanWindowRenderer() override;

  Void render() override;
  Void cleanup() override;

public:
  static constexpr auto DEFAULT_VERTEX_SHADER   = "default";
  static constexpr auto DEFAULT_FRAGMENT_SHADER = "default";

private:
  Void create_graphics_pipeline(const RendererConfig& config);
  Void create_framebuffers(const RendererConfig& config);
  Void create_command_pool(const RendererConfig& config);
  Void create_command_buffers(const RendererConfig& config);
  Void create_synchronization_objects(const RendererConfig& config);

private:
  Observer<VulkanApplication>        m_vulkan_app;
  Observer<VulkanWindowRenderTarget> m_target;
  VkDevice                           m_logical_device;
  VkCommandPool                      m_command_pool;
  VkPipelineLayout                   m_pipeline_layout;
  VkRenderPass                       m_render_pass;
  VkPipeline                         m_pipeline;
  DArray<VkCommandBuffer>            m_command_buffers;
  DArray<VkFramebuffer>              m_framebuffers;
  SharedPtr<Logger>                  m_logger;
  DArray<VkFence>                    m_inflight_fences;
  DArray<VkSemaphore>                m_image_available_semaphores;
  DArray<VkSemaphore>                m_render_finished_semaphores;
  UInt32                             m_current_frame;
};
} // namespace setsugen
