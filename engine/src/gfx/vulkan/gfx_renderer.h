#pragma once

#include <setsugen/application.h>
#include <setsugen/camera.h>
#include <setsugen/entity.h>
#include <setsugen/exception.h>
#include <setsugen/executor.h>
#include <setsugen/gfx.h>
#include <setsugen/logger.h>
#include <setsugen/math.h>
#include <setsugen/mesh.h>
#include <setsugen/platform.h>
#include <setsugen/scene.h>
#include <setsugen/utilities.h>
#include <setsugen/window.h>

#include <memory>
#include <unordered_map>


#include "../../wm/window_helper.h"

namespace setsugen
{
class GfxApplication;
class GfxWindowRenderTarget;
class GfxVulkanRenderer;
class ShaderModule;
class VulkanBuffer;
class VertexBuffer;
class IndexBuffer;
class UniformBuffer;
class VulkanGraphicsPipeline;
class VulkanRenderPass;
class GfxDescriptorPool;
class GfxDescriptorSet;
class GfxCommandBuffer;
class GfxCommandPool;
class GfxVulkanRenderTarget;

struct MeshDataBuffers
{
  std::vector<std::unique_ptr<VertexBuffer>> vertex_buffers;
  std::unique_ptr<IndexBuffer>               index_buffer;
};

struct MeshUniformBuffers
{
  std::vector<std::unique_ptr<UniformBuffer>>    uniform_buffers;
  std::vector<std::unique_ptr<GfxDescriptorSet>> descriptor_sets;
  std::unique_ptr<GfxDescriptorPool>             descriptor_pool;
};

struct MeshDrawCommand
{
  std::vector<std::unique_ptr<GfxCommandBuffer>> command_buffers;
};

struct DrawInfo
{
  VulkanGraphicsPipeline*        pipeline;
  VkFramebuffer                  framebuffer;
  RenderTarget*                  target;
  std::vector<Mesh*>             meshes;
  std::vector<GfxDescriptorSet*> descriptor_sets;
};

class ShaderModule
{
public:
  ShaderModule(const std::string& module_name, VkShaderStageFlagBits stage_flags);
  ~ShaderModule();

  VkShaderModule                  get_module() const;
  VkPipelineShaderStageCreateInfo get_stage_info() const;

private:
  VkShaderModule        m_shader_module;
  VkDevice              m_logical_device;
  GfxApplication*       m_vulkan_app;
  VkShaderStageFlagBits m_stage;
};

class VulkanBuffer
{
public:
  VulkanBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
  virtual ~VulkanBuffer();

  void copy_data(const void* data, VkDeviceSize size);
  void copy_buffer(GfxCommandPool* command_pool, VulkanBuffer* src_buffer, VkDeviceSize size);

  VkBuffer       get_handler() const;
  VkDeviceMemory get_memory_handler() const;

private:
  VkBuffer                m_buffer;
  VkDeviceMemory          m_buffer_memory;
  VkDevice                m_logical_device;
  std::shared_ptr<Logger> m_logger;
  GfxApplication*         m_vulkan_app;
};

class StaggingBuffer : public VulkanBuffer
{
public:
  explicit StaggingBuffer(VkDeviceSize size);
  ~StaggingBuffer() override;

  static std::unique_ptr<StaggingBuffer> create(VkDeviceSize size);
};

class VertexBuffer : public VulkanBuffer
{
public:
  explicit VertexBuffer(size_t size);
  ~VertexBuffer() override;

  static std::unique_ptr<VertexBuffer> from_meshdata(GfxVulkanRenderer* renderer, MeshData* data,
                                                     const VertexBufferLayout& layout);
};

class IndexBuffer : public VulkanBuffer
{
public:
  explicit IndexBuffer(size_t indicies_count);
  ~IndexBuffer() override;

  static std::unique_ptr<IndexBuffer> from_meshdata(GfxVulkanRenderer* renderer, MeshData* data);
};

class UniformBuffer : public VulkanBuffer
{
public:
  explicit UniformBuffer(size_t size);
  ~UniformBuffer() override;

  template<typename T>
  void update(const T& data)
  {
    copy_data(&data, sizeof(T));
  }

  static std::unique_ptr<UniformBuffer> create(size_t size);
};

class VulkanRenderPass
{
public:
  VulkanRenderPass(GfxWindowRenderTarget* target, const RendererConfig& config);
  ~VulkanRenderPass();

  VkRenderPass get_handler() const;

  static std::unique_ptr<VulkanRenderPass> create(GfxWindowRenderTarget* target, const RendererConfig& config);

private:
  VkRenderPass            m_render_pass;
  VkDevice                m_logical_device;
  GfxApplication*         m_vulkan_app;
  GfxWindowRenderTarget*  m_target;
  const RendererConfig&   m_config;
  std::shared_ptr<Logger> m_logger;
};

class VulkanGraphicsPipeline
{
public:
  VulkanGraphicsPipeline(GfxWindowRenderTarget* target, const RendererConfig& config);
  ~VulkanGraphicsPipeline();

  VkPipeline            get_handler() const;
  VkPipelineLayout      get_layout_handler() const;
  VkRenderPass          get_render_pass() const;
  VkDescriptorSetLayout get_descriptor_set_layout() const;

  const RendererConfig& get_config() const;

  static std::unique_ptr<VulkanGraphicsPipeline> create(GfxWindowRenderTarget* target, const RendererConfig& config);

private:
  VkPipeline                        m_pipeline;
  VkPipelineLayout                  m_pipeline_layout;
  std::vector<VkDescriptorSet>      m_descriptor_sets;
  VkDevice                          m_logical_device;
  GfxApplication*                   m_vulkan_app;
  std::unique_ptr<VulkanRenderPass> m_render_pass;
  GfxWindowRenderTarget*            m_target;
  const RendererConfig&             m_config;
  std::shared_ptr<Logger>           m_logger;
  VkDescriptorSetLayout             m_descriptor_set_layout;
};

class GfxCommandBuffer
{
public:
  GfxCommandBuffer(GfxCommandPool* cmd_pool, VkCommandBufferLevel level);
  ~GfxCommandBuffer();

  VkCommandBuffer get_handler() const;

  void begin();
  void end();

  void bind_vertex_buffers(const std::vector<VertexBuffer*>& vertex_buffers);
  void bind_index_buffer(IndexBuffer* index_buffer);
  void bind_descriptor_set(const std::vector<GfxDescriptorSet*>& descriptor_sets, VulkanGraphicsPipeline* pipeline);
  void begin_render_pass(VulkanGraphicsPipeline* pipeline, GfxVulkanRenderTarget* target, VkFramebuffer framebuffer);
  void draw(VulkanGraphicsPipeline* pipeline, std::vector<VertexBuffer*>& vertex_buffers, IndexBuffer* index_buffer,
            std::vector<GfxDescriptorSet*>& descriptor_sets, uint32_t index_count);
  void end_render_pass();
  void record_copy_buffer_command(VulkanBuffer* src_buffer, VulkanBuffer* dst_buffer, VkDeviceSize size);

private:
  VkCommandBuffer m_command_buffer;
  VkDevice        m_logical_device;
  VkCommandPool   m_command_pool;
};

class GfxCommandPool
{
public:
  GfxCommandPool(VkCommandPoolCreateFlags flags);
  ~GfxCommandPool();

  std::unique_ptr<GfxCommandBuffer>
  allocate_command_buffer(VkCommandBufferLevel level = VK_COMMAND_BUFFER_LEVEL_PRIMARY);

  VkCommandPool get_command_pool() const;

  static std::unique_ptr<GfxCommandPool> create(VkCommandPoolCreateFlags flags);

private:
  VkCommandPool   m_command_pool;
  VkDevice        m_logical_device;
  GfxApplication* m_vulkan_app;
};

class GfxDescriptorSet
{
public:
  GfxDescriptorSet(GfxDescriptorPool* pool, VkDescriptorSetLayout layout);
  ~GfxDescriptorSet();

  void update_uniform_buffers(const std::vector<UniformBuffer*>& uniform_buffers);

  VkDescriptorSet get_handler() const;

private:
  VkDescriptorSet m_descriptor_set;
  VkDevice        m_logical_device;
  GfxApplication* m_vulkan_app;
};

class GfxDescriptorPool
{
public:
  explicit GfxDescriptorPool(size_t pool_size, size_t max_sets);
  ~GfxDescriptorPool();

  VkDescriptorPool get_handler() const;

  std::unique_ptr<GfxDescriptorSet> allocate_descriptor_set(VkDescriptorSetLayout layout);

  static std::unique_ptr<GfxDescriptorPool> create(size_t pool_size, size_t max_sets);

private:
  VkDescriptorPool m_descriptor_pool;
  VkDevice         m_logical_device;
  GfxApplication*  m_vulkan_app;
};

class GfxApplication
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

  GfxApplication();
  ~GfxApplication();

  static GfxApplication*                 get_current();
  static std::unique_ptr<GfxApplication> create();

  VkPhysicalDevice   get_physical_device() const;
  VkDevice           get_logical_device() const;
  VkInstance         get_instance() const;
  QueueFamilyIndices get_queue_family_indices() const;
  VkQueue            get_graphics_queue() const;
  VkQueue            get_present_queue() const;
  unsigned int       find_memory_type(unsigned int type_filter, VkMemoryPropertyFlags properties) const;
  void               execute_one_time_commands(VkQueue queue, const std::vector<GfxCommandBuffer*>& commands);

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

  static std::atomic<GfxApplication*> s_current_app;
};

class GfxVulkanRenderTarget : public RenderTarget
{
public:
  virtual VkImage get_next_image() = 0;
};

class GfxWindowRenderTarget : public GfxVulkanRenderTarget
{
public:
  explicit GfxWindowRenderTarget(Window* window);
  ~GfxWindowRenderTarget() override;

  void resize(int width, int height) override;
  void present() override;

  int width() const override;
  int height() const override;

  VkImage get_next_image() override;

  RenderTargetType type() const override;

  VkSurfaceKHR   get_surface() const;
  VkSwapchainKHR get_swapchain() const;
  VkExtent2D     get_swapchain_extent() const;
  VkFormat       get_surface_format() const;

private:
  void create_surface();
  void create_swapchain();
  void create_image_views();

private:
  Window*                  m_window;
  GfxApplication*          m_vulkan_app;
  VkDevice                 m_logical_device;
  VkSurfaceKHR             m_surface;
  VkSurfaceFormatKHR       m_surface_format;
  VkPresentModeKHR         m_present_mode;
  VkSwapchainKHR           m_swapchain;
  VkExtent2D               m_swapchain_extent;
  std::vector<VkImage>     m_swapchain_images;
  std::vector<VkImageView> m_swapchain_image_views;

  friend class GfxVulkanRenderer;
};

class GfxVulkanRenderer : virtual public Renderer
{
public:
  GfxVulkanRenderer(RendererConfig&& config);
  ~GfxVulkanRenderer() override;

  void render() override;
  void cleanup() override;

  GfxCommandPool* get_command_pool();

public:
  static constexpr auto DEFAULT_VERTEX_SHADER   = "default";
  static constexpr auto DEFAULT_FRAGMENT_SHADER = "default";

private:
  void create_graphics_pipeline();
  void create_framebuffers();
  void create_command_pool();
  void create_command_buffers(Scene* scene);
  void create_synchronization_objects();
  void create_uniform_buffers(Scene* scene);
  void create_vertex_buffer(MeshData* meshdata);
  void create_index_buffer(MeshData* meshdata);
  void prepare_scene(Scene* scene);
  void unload_scene(Scene* scene);
  void update_scene(int frame_index);

private:
  GfxApplication*                                    m_vulkan_app;
  GfxWindowRenderTarget*                             m_target;
  VkDevice                                           m_logical_device;
  std::unique_ptr<GfxCommandPool>                    m_command_pool;
  std::unique_ptr<VulkanGraphicsPipeline>            m_graphics_pipeline;
  std::vector<VkFramebuffer>                         m_framebuffers;
  std::shared_ptr<Logger>                            m_logger;
  std::vector<VkFence>                               m_inflight_fences;
  std::vector<VkSemaphore>                           m_image_available_semaphores;
  std::vector<VkSemaphore>                           m_render_finished_semaphores;
  unsigned int                                       m_current_frame;
  Scene*                                             m_current_scene;
  Scene*                                             m_next_scene;
  std::vector<std::unique_ptr<UniformBuffer>>        m_scene_uniform_buffer;
  std::unordered_map<MeshData*, MeshDataBuffers>     m_meshdata_buffers;
  std::unique_ptr<Executor<FixedThreadPoolExecutor>> m_executor;
  RendererConfig                                     m_config;
  std::unique_ptr<MeshDrawCommand>                   m_draw_command;
  std::unordered_map<Mesh*, MeshUniformBuffers>      m_mesh_drawinfo;
};
} // namespace setsugen
