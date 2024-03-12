#include "gfx_renderer.h"

namespace setsugen
{

VkPrimitiveTopology convert_to_vulkan_topology(Topology topology)
{
  switch (topology)
  {
  case Topology::PointList:
    return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
  case Topology::LineList:
    return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
  case Topology::LineStrip:
    return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
  case Topology::TriangleList:
    return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
  case Topology::TriangleStrip:
    return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
  default:
    throw InvalidArgumentException("Invalid topology");
  }
}

VkFormat convert_to_vulkan_format(VertexFormat format, VertexType type, VertexSize size)
{
  static UnorderedMap<String, VkFormat> format_map = {
      {      "R_8_SINT",             VK_FORMAT_R8_SINT},
      {      "R_8_UINT",             VK_FORMAT_R8_UINT},
      {   "R_16_SFLOAT",          VK_FORMAT_R16_SFLOAT},
      {     "R_16_SINT",            VK_FORMAT_R16_SINT},
      {     "R_16_UINT",            VK_FORMAT_R16_UINT},
      {   "R_32_SFLOAT",          VK_FORMAT_R32_SFLOAT},
      {     "R_32_SINT",            VK_FORMAT_R32_SINT},
      {     "R_32_UINT",            VK_FORMAT_R32_UINT},
      {   "R_64_SFLOAT",          VK_FORMAT_R64_SFLOAT},
      {     "R_64_SINT",            VK_FORMAT_R64_SINT},
      {     "R_64_UINT",            VK_FORMAT_R64_UINT},
      {     "RG_8_SINT",           VK_FORMAT_R8G8_SINT},
      {     "RG_8_UINT",           VK_FORMAT_R8G8_UINT},
      {  "RG_16_SFLOAT",       VK_FORMAT_R16G16_SFLOAT},
      {    "RG_16_SINT",         VK_FORMAT_R16G16_SINT},
      {    "RG_16_UINT",         VK_FORMAT_R16G16_UINT},
      {  "RG_32_SFLOAT",       VK_FORMAT_R32G32_SFLOAT},
      {    "RG_32_SINT",         VK_FORMAT_R32G32_SINT},
      {    "RG_32_UINT",         VK_FORMAT_R32G32_UINT},
      {  "RG_64_SFLOAT",       VK_FORMAT_R64G64_SFLOAT},
      {    "RG_64_SINT",         VK_FORMAT_R64G64_SINT},
      {    "RG_64_UINT",         VK_FORMAT_R64G64_UINT},
      {    "RGB_8_SINT",         VK_FORMAT_R8G8B8_SINT},
      {    "RGB_8_UINT",         VK_FORMAT_R8G8B8_UINT},
      { "RGB_16_SFLOAT",    VK_FORMAT_R16G16B16_SFLOAT},
      {   "RGB_16_SINT",      VK_FORMAT_R16G16B16_SINT},
      {   "RGB_16_UINT",      VK_FORMAT_R16G16B16_UINT},
      { "RGB_32_SFLOAT",    VK_FORMAT_R32G32B32_SFLOAT},
      {   "RGB_32_SINT",      VK_FORMAT_R32G32B32_SINT},
      {   "RGB_32_UINT",      VK_FORMAT_R32G32B32_UINT},
      { "RGB_64_SFLOAT",    VK_FORMAT_R64G64B64_SFLOAT},
      {   "RGB_64_SINT",      VK_FORMAT_R64G64B64_SINT},
      {   "RGB_64_UINT",      VK_FORMAT_R64G64B64_UINT},
      {   "RGBA_8_SINT",       VK_FORMAT_R8G8B8A8_SINT},
      {   "RGBA_8_UINT",       VK_FORMAT_R8G8B8A8_UINT},
      {"RGBA_16_SFLOAT", VK_FORMAT_R16G16B16A16_SFLOAT},
      {  "RGBA_16_SINT",   VK_FORMAT_R16G16B16A16_SINT},
      {  "RGBA_16_UINT",   VK_FORMAT_R16G16B16A16_UINT},
      {"RGBA_32_SFLOAT", VK_FORMAT_R32G32B32A32_SFLOAT},
      {  "RGBA_32_SINT",   VK_FORMAT_R32G32B32A32_SINT},
      {  "RGBA_32_UINT",   VK_FORMAT_R32G32B32A32_UINT},
      {"RGBA_64_SFLOAT", VK_FORMAT_R64G64B64A64_SFLOAT},
      {  "RGBA_64_SINT",   VK_FORMAT_R64G64B64A64_SINT},
      {  "RGBA_64_UINT",   VK_FORMAT_R64G64B64A64_UINT},
  };

  StringStream skey;
  switch (format)
  {
  case VertexFormat::R:
    skey << "R";
    break;
  case VertexFormat::RG:
    skey << "RG";
    break;
  case VertexFormat::RGB:
    skey << "RGB";
    break;
  case VertexFormat::RGBA:
    skey << "RGBA";
    break;
  default:
    throw InvalidArgumentException("Invalid format");
  }

  switch (size)
  {
  case VertexSize::Size8:
    skey << "_8";
    break;
  case VertexSize::Size16:
    skey << "_16";
    break;
  case VertexSize::Size32:
    skey << "_32";
    break;
  case VertexSize::Size64:
    skey << "_64";
    break;
  default:
    throw InvalidArgumentException("Invalid size");
  }

  switch (type)
  {
  case VertexType::Int:
    skey << "_SINT";
    break;
  case VertexType::UInt:
    skey << "_UINT";
    break;
  case VertexType::Float:
    skey << "_SFLOAT";
    break;
  default:
    throw InvalidArgumentException("Invalid type");
  }

  auto key = skey.str();

  if (format_map.find(key) == format_map.end())
  {
    throw InvalidArgumentException("Invalid format");
  }

  return format_map[key];
}

VkCullModeFlags convert_to_vulkan_cull_mode(CullMode cull_mode)
{
  switch (cull_mode)
  {
  case CullMode::None:
    return VK_CULL_MODE_NONE;
  case CullMode::Front:
    return VK_CULL_MODE_FRONT_BIT;
  case CullMode::Back:
    return VK_CULL_MODE_BACK_BIT;
  default:
    throw InvalidArgumentException("Invalid cull mode");
  }
}

VkFrontFace convert_to_vulkan_front_face(FrontFace front_face)
{
  switch (front_face)
  {
  case FrontFace::Clockwise:
    return VK_FRONT_FACE_CLOCKWISE;
  case FrontFace::CounterClockwise:
    return VK_FRONT_FACE_COUNTER_CLOCKWISE;
  default:
    throw InvalidArgumentException("Invalid front face");
  }
}

VkPolygonMode convert_to_vulkan_polygon_mode(PolygonMode polygon_mode)
{
  switch (polygon_mode)
  {
  case PolygonMode::Fill:
    return VK_POLYGON_MODE_FILL;
  case PolygonMode::Line:
    return VK_POLYGON_MODE_LINE;
  case PolygonMode::Point:
    return VK_POLYGON_MODE_POINT;
  default:
    throw InvalidArgumentException("Invalid polygon mode");
  }
}

VkColorComponentFlags convert_to_vulkan_color_component_flags(const ColorBlend& color_blend)
{
  VkColorComponentFlags flags = 0;

  if (color_blend.blend_component.r())
  {
    flags |= VK_COLOR_COMPONENT_R_BIT;
  }

  if (color_blend.blend_component.g())
  {
    flags |= VK_COLOR_COMPONENT_G_BIT;
  }

  if (color_blend.blend_component.b())
  {
    flags |= VK_COLOR_COMPONENT_B_BIT;
  }

  if (color_blend.blend_component.a())
  {
    flags |= VK_COLOR_COMPONENT_A_BIT;
  }

  return flags;
}

VulkanWindowRenderer::VulkanWindowRenderer(const RendererConfig& config)
{
  RendererConfig renderer_config = config;

  if (renderer_config.render_target.expired())
  {
    throw InvalidArgumentException("Render target is expired");
  }

  if (renderer_config.render_target.lock()->type() != RenderTargetType::Window)
  {
    throw InvalidArgumentException("Render target is not a window");
  }

  create_graphics_pipeline(renderer_config);
  create_framebuffers(renderer_config);
  create_command_pool(renderer_config);
}

VulkanWindowRenderer::~VulkanWindowRenderer()
{
  auto vulkan_app = VulkanApplication::get_current().lock();
  auto device     = vulkan_app->get_logical_device();

  vkDestroyCommandPool(device, m_command_pool, nullptr);

  for (auto framebuffer : m_framebuffers)
  {
    vkDestroyFramebuffer(device, framebuffer, nullptr);
  }

  vkDestroyPipeline(device, m_pipeline, nullptr);
  vkDestroyPipelineLayout(device, m_pipeline_layout, nullptr);
  vkDestroyRenderPass(device, m_render_pass, nullptr);
}

Void VulkanWindowRenderer::create_graphics_pipeline(const RendererConfig& config)
{
  auto vulkan_app = VulkanApplication::get_current().lock();
  auto device     = vulkan_app->get_logical_device();
  auto target     = std::dynamic_pointer_cast<VulkanWindowRenderTarget>(config.render_target.lock());

  auto vertex_shader   = ShaderModule(config.vertex_shader.value_or(VulkanWindowRenderer::DEFAULT_VERTEX_SHADER));
  auto fragment_shader = ShaderModule(config.fragment_shader.value_or(VulkanWindowRenderer::DEFAULT_FRAGMENT_SHADER));

  // Create the vertex and fragment shader stage info
  VkPipelineShaderStageCreateInfo vert_shader_stage_info = {};
  vert_shader_stage_info.sType                           = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  vert_shader_stage_info.stage                           = VK_SHADER_STAGE_VERTEX_BIT;
  vert_shader_stage_info.module                          = vertex_shader.get_module();
  vert_shader_stage_info.pName                           = "main";

  VkPipelineShaderStageCreateInfo frag_shader_stage_info = {};
  frag_shader_stage_info.sType                           = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  frag_shader_stage_info.stage                           = VK_SHADER_STAGE_FRAGMENT_BIT;
  frag_shader_stage_info.module                          = fragment_shader.get_module();
  frag_shader_stage_info.pName                           = "main";

  // Create the shader stages
  VkPipelineShaderStageCreateInfo shader_stages[] = {vert_shader_stage_info, frag_shader_stage_info};

  // Create the vertex input info

  DArray<VkVertexInputBindingDescription> vertex_binding_descriptions;
  for (auto vertex_binding : config.vertex_bindings)
  {
    vertex_binding_descriptions.push_back({vertex_binding.binding, vertex_binding.stride});
  }

  DArray<VkVertexInputAttributeDescription> vertex_attribute_descriptions;
  for (auto vertex_attribute : config.vertex_attributes)
  {
    vertex_attribute_descriptions.push_back(
        {vertex_attribute.binding, vertex_attribute.location,
         convert_to_vulkan_format(vertex_attribute.format, vertex_attribute.type, vertex_attribute.size), vertex_attribute.offset}
    );
  }

  VkPipelineVertexInputStateCreateInfo vertex_input_info = {};
  vertex_input_info.sType                                = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

  // Create the input assembly
  VkPipelineInputAssemblyStateCreateInfo input_assembly = {};
  input_assembly.sType                                  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  input_assembly.topology                               = convert_to_vulkan_topology(config.topology);
  input_assembly.primitiveRestartEnable                 = VK_FALSE;

  DArray<VkViewport> viewports;
  for (auto viewport : config.viewports)
  {
    viewports.push_back({viewport.x, viewport.y, viewport.width, viewport.height, viewport.min_depth, viewport.max_depth});
  }

  DArray<VkRect2D> scissors;
  for (auto scissor : config.scissors)
  {
    scissors.push_back({
        {     static_cast<Int32>(scissor.x),       static_cast<Int32>(scissor.y)},
        {static_cast<UInt32>(scissor.width), static_cast<UInt32>(scissor.height)}
    });
  }

  VkPipelineViewportStateCreateInfo viewport_state = {};
  viewport_state.sType                             = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  viewport_state.viewportCount                     = (UInt32) viewports.size();
  viewport_state.pViewports                        = viewports.data();
  viewport_state.scissorCount                      = (UInt32) scissors.size();
  viewport_state.pScissors                         = scissors.data();

  VkPipelineRasterizationStateCreateInfo rasterizer = {};
  rasterizer.sType                                  = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  rasterizer.depthClampEnable                       = VK_FALSE;
  rasterizer.rasterizerDiscardEnable                = VK_FALSE;
  rasterizer.polygonMode                            = convert_to_vulkan_polygon_mode(config.polygon_mode);
  rasterizer.lineWidth                              = 1.0f;
  rasterizer.cullMode                               = convert_to_vulkan_cull_mode(config.cull_mode);
  rasterizer.frontFace                              = convert_to_vulkan_front_face(config.front_face);
  rasterizer.depthBiasEnable                        = VK_FALSE;

  VkPipelineMultisampleStateCreateInfo multisampling = {};
  multisampling.sType                                = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  multisampling.sampleShadingEnable                  = VK_FALSE;
  multisampling.rasterizationSamples                 = VK_SAMPLE_COUNT_1_BIT;

  VkPipelineColorBlendAttachmentState color_blend_attachment = {};
  color_blend_attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
  color_blend_attachment.blendEnable    = VK_FALSE;

  VkPipelineColorBlendStateCreateInfo color_blending = {};
  color_blending.sType                               = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  color_blending.logicOpEnable                       = VK_FALSE;
  color_blending.logicOp                             = VK_LOGIC_OP_COPY;
  color_blending.attachmentCount                     = 1;
  color_blending.pAttachments                        = &color_blend_attachment;

  VkPipelineLayoutCreateInfo pipeline_layout_info = {};
  pipeline_layout_info.sType                      = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;

  auto pipeline_layout_result = vkCreatePipelineLayout(device, &pipeline_layout_info, nullptr, &m_pipeline_layout);
  if (pipeline_layout_result != VK_SUCCESS)
  {
    throw EngineException("Failed to create pipeline layout");
  }

  VkAttachmentDescription color_attachment = {};
  color_attachment.format                  = target->m_surface_format.format;
  color_attachment.samples                 = VK_SAMPLE_COUNT_1_BIT;
  color_attachment.loadOp                  = VK_ATTACHMENT_LOAD_OP_CLEAR;
  color_attachment.storeOp                 = VK_ATTACHMENT_STORE_OP_STORE;
  color_attachment.stencilLoadOp           = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  color_attachment.stencilStoreOp          = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  color_attachment.initialLayout           = VK_IMAGE_LAYOUT_UNDEFINED;
  color_attachment.finalLayout             = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

  VkAttachmentReference color_attachment_ref = {};
  color_attachment_ref.attachment            = 0;
  color_attachment_ref.layout                = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  VkSubpassDescription subpass = {};
  subpass.pipelineBindPoint    = VK_PIPELINE_BIND_POINT_GRAPHICS;
  subpass.colorAttachmentCount = 1;
  subpass.pColorAttachments    = &color_attachment_ref;

  // Create render pass
  VkRenderPassCreateInfo render_pass_info = {};
  render_pass_info.sType                  = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  render_pass_info.attachmentCount        = 1;
  render_pass_info.pAttachments           = &color_attachment;
  render_pass_info.subpassCount           = 1;
  render_pass_info.pSubpasses             = &subpass;

  auto render_pass_result = vkCreateRenderPass(device, &render_pass_info, nullptr, &m_render_pass);
  if (render_pass_result != VK_SUCCESS)
  {
    throw EngineException("Failed to create render pass");
  }

  VkGraphicsPipelineCreateInfo pipeline_info = {};
  pipeline_info.sType                        = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  pipeline_info.stageCount                   = 2;
  pipeline_info.pStages                      = shader_stages;
  pipeline_info.pVertexInputState            = &vertex_input_info;
  pipeline_info.pInputAssemblyState          = &input_assembly;
  pipeline_info.pViewportState               = &viewport_state;
  pipeline_info.pRasterizationState          = &rasterizer;
  pipeline_info.pMultisampleState            = &multisampling;
  pipeline_info.pColorBlendState             = &color_blending;
  pipeline_info.layout                       = m_pipeline_layout;
  pipeline_info.renderPass                   = m_render_pass;
  pipeline_info.subpass                      = 0;
  pipeline_info.basePipelineHandle           = VK_NULL_HANDLE;

  auto pipeline_result = vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipeline_info, nullptr, &m_pipeline);
  if (pipeline_result != VK_SUCCESS)
  {
    throw EngineException("Failed to create graphics pipeline");
  }
}

Void VulkanWindowRenderer::create_framebuffers(const RendererConfig& config)
{
  auto vulkan_app       = VulkanApplication::get_current().lock();
  auto device           = vulkan_app->get_logical_device();
  auto target           = std::dynamic_pointer_cast<VulkanWindowRenderTarget>(config.render_target.lock());
  auto swapchain_images = target->m_swapchain_images;

  m_framebuffers.resize(swapchain_images.size());

  for (UInt32 i = 0; i < swapchain_images.size(); ++i)
  {
    VkImageView attachments[] = {target->m_swapchain_image_views[i]};

    VkFramebufferCreateInfo framebuffer_info = {};
    framebuffer_info.sType                   = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebuffer_info.renderPass              = m_render_pass;
    framebuffer_info.attachmentCount         = 1;
    framebuffer_info.pAttachments            = attachments;
    framebuffer_info.width                   = target->width();
    framebuffer_info.height                  = target->height();
    framebuffer_info.layers                  = 1;

    auto framebuffer_result = vkCreateFramebuffer(device, &framebuffer_info, nullptr, &m_framebuffers[i]);
    if (framebuffer_result != VK_SUCCESS)
    {
      throw EngineException("Failed to create framebuffer");
    }
  }
}

Void VulkanWindowRenderer::create_command_pool(const RendererConfig& config)
{
  auto vulkan_app = VulkanApplication::get_current().lock();
  auto device     = vulkan_app->get_logical_device();

  auto queue_family_indices = vulkan_app->get_queue_family_indices();

  VkCommandPoolCreateInfo pool_info = {};
  pool_info.sType                   = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  pool_info.queueFamilyIndex        = queue_family_indices.graphics_family.value();
  pool_info.flags                   = 0;

  auto command_pool_result = vkCreateCommandPool(device, &pool_info, nullptr, &m_command_pool);
  if (command_pool_result != VK_SUCCESS)
  {
    throw EngineException("Failed to create command pool");
  }
}

Void VulkanWindowRenderer::create_command_buffers(const RendererConfig& config)
{
  auto vulkan_app = VulkanApplication::get_current().lock();
  auto device     = vulkan_app->get_logical_device();
  auto target     = std::dynamic_pointer_cast<VulkanWindowRenderTarget>(config.render_target.lock());

  m_command_buffers.resize(m_framebuffers.size());

  VkCommandBufferAllocateInfo alloc_info = {};
  alloc_info.sType                       = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  alloc_info.commandPool                 = m_command_pool;
  alloc_info.level                       = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  alloc_info.commandBufferCount          = static_cast<UInt32>(m_command_buffers.size());

  auto command_buffer_result = vkAllocateCommandBuffers(device, &alloc_info, m_command_buffers.data());
  if (command_buffer_result != VK_SUCCESS)
  {
    throw EngineException("Failed to allocate command buffers");
  }

  for (UInt32 i = 0; i < m_command_buffers.size(); ++i)
  {
    VkCommandBufferBeginInfo begin_info = {};
    begin_info.sType                    = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    auto begin_result = vkBeginCommandBuffer(m_command_buffers[i], &begin_info);
    if (begin_result != VK_SUCCESS)
    {
      throw EngineException("Failed to begin recording command buffer");
    }

    VkRenderPassBeginInfo render_pass_info = {};
    render_pass_info.sType                 = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    render_pass_info.renderPass            = m_render_pass;
    render_pass_info.framebuffer           = m_framebuffers[i];
    render_pass_info.renderArea.offset     = {0, 0};
    render_pass_info.renderArea.extent     = {(UInt32) target->width(), (UInt32) target->height()};
    VkClearValue clear_color               = {0.0f, 0.0f, 0.0f, 1.0f};
    render_pass_info.clearValueCount       = 1;
    render_pass_info.pClearValues          = &clear_color;

    vkCmdBeginRenderPass(m_command_buffers[i], &render_pass_info, VK_SUBPASS_CONTENTS_INLINE);
    vkCmdBindPipeline(m_command_buffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline);
    vkCmdDraw(m_command_buffers[i], 3, 1, 0, 0);
    vkCmdEndRenderPass(m_command_buffers[i]);

    auto end_result = vkEndCommandBuffer(m_command_buffers[i]);
    if (end_result != VK_SUCCESS)
    {
      throw EngineException("Failed to record command buffer");
    }
  }
}

}  // namespace setsugen