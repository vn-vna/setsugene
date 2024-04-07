#pragma once

#include <setsugen/application.h>
#include <setsugen/exception.h>
#include <setsugen/gfx.h>
#include <setsugen/logger.h>
#include <setsugen/platform.h>
#include <setsugen/scene.h>
#include <setsugen/utilities.h>
#include <setsugen/window.h>

#include "window_helper.h"

namespace setsugen
{
class VulkanApplication;
class VulkanWindowRenderTarget;
class MeshBuffer;
class MeshBufferManager;

class MeshBuffer
{
public:
  MeshBuffer();

  ~MeshBuffer();

private:
};

class MeshBufferManager
{};

class ShaderModule
{
public:
  ShaderModule(const std::string& module_name);
  ~ShaderModule();

  VkShaderModule get_module() const;

private:
  VkShaderModule     m_shader_module;
  VkDevice           m_logical_device;
  VulkanApplication* m_vulkan_app;
};

class VulkanApplication
{
public:
  using ExtensionList = std::vector<const char*>;

  struct QueueFamilyIndices
  {
    std::optional<unsigned int> graphics_family;
    std::optional<unsigned int> present_family;

    bool is_complete() const
    {
      return graphics_family.has_value() && //
             present_family.has_value();
    }
  };

  VulkanApplication();
  ~VulkanApplication();

  static VulkanApplication*                 get_current();
  static std::unique_ptr<VulkanApplication> create();

  VkPhysicalDevice   get_physical_device() const;
  VkDevice           get_logical_device() const;
  VkInstance         get_instance() const;
  QueueFamilyIndices get_queue_family_indices() const;
  VkQueue            get_graphics_queue() const;
  VkQueue            get_present_queue() const;

private:
  void               initialize_instance();
  ExtensionList      get_instance_layers();
  void               setup_debug_messenger();
  void               query_physical_devices();
  int                auto_select_physical_device();
  QueueFamilyIndices find_queue_families(VkPhysicalDevice device) const;
  void               create_logical_device();

  static ExtensionList get_instance_extensions();
  static bool          check_physical_device_extensions(VkPhysicalDevice device);
  static bool          check_layers_support(const std::vector<const char*>& layers);
  static bool          check_extensions_support(const std::vector<const char*>& extensions);

  VkInstance                    m_instance;
  VkDebugUtilsMessengerEXT      m_debug_messenger;
  std::vector<VkPhysicalDevice> m_physical_devices;
  int                           m_physical_device_index;
  QueueFamilyIndices            m_queue_family_indices;
  VkDevice                      m_logical_device;
  VkQueue                       m_graphics_queue;
  VkQueue                       m_present_queue;

  static std::atomic<VulkanApplication*> s_current_app;
};

class VulkanWindowRenderTarget : virtual public RenderTarget
{
public:
  VulkanWindowRenderTarget(Window* window);
  ~VulkanWindowRenderTarget() override;

  void resize(int width, int height) override;
  void present() override;

  int width() const override;
  int height() const override;

  RenderTargetType type() const override;

private:
  void create_surface();
  void create_swapchain();
  void create_image_views();

private:
  Window*                  m_window;
  VulkanApplication*       m_vulkan_app;
  VkDevice                 m_logical_device;
  VkSurfaceKHR             m_surface;
  VkSurfaceFormatKHR       m_surface_format;
  VkPresentModeKHR         m_present_mode;
  VkSwapchainKHR           m_swapchain;
  VkExtent2D               m_swapchain_extent;
  std::vector<VkImage>     m_swapchain_images;
  std::vector<VkImageView> m_swapchain_image_views;

  friend class VulkanWindowRenderer;
};

class VulkanWindowRenderer : virtual public Renderer
{
public:
  VulkanWindowRenderer(const RendererConfig& config);
  ~VulkanWindowRenderer() override;

  void render(Scene*) override;
  void cleanup() override;

public:
  static constexpr auto DEFAULT_VERTEX_SHADER   = "default";
  static constexpr auto DEFAULT_FRAGMENT_SHADER = "default";

private:
  void create_graphics_pipeline(const RendererConfig& config);
  void create_framebuffers(const RendererConfig& config);
  void create_command_pool(const RendererConfig& config);
  void create_command_buffers(const RendererConfig& config);
  void create_synchronization_objects(const RendererConfig& config);

private:
  VulkanApplication*           m_vulkan_app;
  VulkanWindowRenderTarget*    m_target;
  VkDevice                     m_logical_device;
  VkCommandPool                m_command_pool;
  VkPipelineLayout             m_pipeline_layout;
  VkRenderPass                 m_render_pass;
  VkPipeline                   m_pipeline;
  std::vector<VkCommandBuffer> m_command_buffers;
  std::vector<VkFramebuffer>   m_framebuffers;
  std::shared_ptr<Logger>      m_logger;
  std::vector<VkFence>         m_inflight_fences;
  std::vector<VkSemaphore>     m_image_available_semaphores;
  std::vector<VkSemaphore>     m_render_finished_semaphores;
  unsigned int                 m_current_frame;
};
} // namespace setsugen
