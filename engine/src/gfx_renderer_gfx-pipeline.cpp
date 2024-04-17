#include "gfx_renderer.h"

namespace setsugen
{

VkPrimitiveTopology
convert_to_vulkan_topology(Topology topology)
{
  switch (topology)
  {
    case Topology::PointList: return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
    case Topology::LineList: return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
    case Topology::LineStrip: return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
    case Topology::TriangleList: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    case Topology::TriangleStrip: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
    default: throw InvalidArgumentException("Invalid topology");
  }
}

VkFormat
convert_to_vulkan_format(VertexFormat format, VertexType type, VertexSize size)
{
  using VkFormatMapping = std::unordered_map<std::tuple<VertexFormat, VertexSize, VertexType>, VkFormat,
                                             TupleHash<VertexFormat, VertexSize, VertexType>>;

  static VkFormatMapping format_map = {
      {{VertexFormat::R, VertexSize::Size8, VertexType::Int}, VK_FORMAT_R8_SINT},
      {{VertexFormat::R, VertexSize::Size8, VertexType::UInt}, VK_FORMAT_R8_UINT},
      {{VertexFormat::R, VertexSize::Size16, VertexType::Int}, VK_FORMAT_R16_SINT},
      {{VertexFormat::R, VertexSize::Size16, VertexType::UInt}, VK_FORMAT_R16_UINT},
      {{VertexFormat::R, VertexSize::Size16, VertexType::Float}, VK_FORMAT_R16_SFLOAT},
      {{VertexFormat::R, VertexSize::Size32, VertexType::Int}, VK_FORMAT_R32_SINT},
      {{VertexFormat::R, VertexSize::Size32, VertexType::UInt}, VK_FORMAT_R32_UINT},
      {{VertexFormat::R, VertexSize::Size32, VertexType::Float}, VK_FORMAT_R32_SFLOAT},
      {{VertexFormat::R, VertexSize::Size64, VertexType::Int}, VK_FORMAT_R64_SINT},
      {{VertexFormat::R, VertexSize::Size64, VertexType::UInt}, VK_FORMAT_R64_UINT},
      {{VertexFormat::R, VertexSize::Size64, VertexType::Float}, VK_FORMAT_R64_SFLOAT},

      {{VertexFormat::RG, VertexSize::Size8, VertexType::Int}, VK_FORMAT_R8G8_SINT},
      {{VertexFormat::RG, VertexSize::Size8, VertexType::UInt}, VK_FORMAT_R8G8_UINT},
      {{VertexFormat::RG, VertexSize::Size16, VertexType::Int}, VK_FORMAT_R16G16_SINT},
      {{VertexFormat::RG, VertexSize::Size16, VertexType::UInt}, VK_FORMAT_R16G16_UINT},
      {{VertexFormat::RG, VertexSize::Size16, VertexType::Float}, VK_FORMAT_R16G16_SFLOAT},
      {{VertexFormat::RG, VertexSize::Size32, VertexType::Int}, VK_FORMAT_R32G32_SINT},
      {{VertexFormat::RG, VertexSize::Size32, VertexType::UInt}, VK_FORMAT_R32G32_UINT},
      {{VertexFormat::RG, VertexSize::Size32, VertexType::Float}, VK_FORMAT_R32G32_SFLOAT},
      {{VertexFormat::RG, VertexSize::Size64, VertexType::Int}, VK_FORMAT_R64G64_SINT},
      {{VertexFormat::RG, VertexSize::Size64, VertexType::UInt}, VK_FORMAT_R64G64_UINT},
      {{VertexFormat::RG, VertexSize::Size64, VertexType::Float}, VK_FORMAT_R64G64_SFLOAT},

      {{VertexFormat::RGB, VertexSize::Size8, VertexType::Int}, VK_FORMAT_R8G8B8_SINT},
      {{VertexFormat::RGB, VertexSize::Size8, VertexType::UInt}, VK_FORMAT_R8G8B8_UINT},
      {{VertexFormat::RGB, VertexSize::Size16, VertexType::Int}, VK_FORMAT_R16G16B16_SINT},
      {{VertexFormat::RGB, VertexSize::Size16, VertexType::UInt}, VK_FORMAT_R16G16B16_UINT},
      {{VertexFormat::RGB, VertexSize::Size16, VertexType::Float}, VK_FORMAT_R16G16B16_SFLOAT},
      {{VertexFormat::RGB, VertexSize::Size32, VertexType::Int}, VK_FORMAT_R32G32B32_SINT},
      {{VertexFormat::RGB, VertexSize::Size32, VertexType::UInt}, VK_FORMAT_R32G32B32_UINT},
      {{VertexFormat::RGB, VertexSize::Size32, VertexType::Float}, VK_FORMAT_R32G32B32_SFLOAT},
      {{VertexFormat::RGB, VertexSize::Size64, VertexType::Int}, VK_FORMAT_R64G64B64_SINT},
      {{VertexFormat::RGB, VertexSize::Size64, VertexType::UInt}, VK_FORMAT_R64G64B64_UINT},
      {{VertexFormat::RGB, VertexSize::Size64, VertexType::Float}, VK_FORMAT_R64G64B64_SFLOAT},

      {{VertexFormat::RGBA, VertexSize::Size8, VertexType::Int}, VK_FORMAT_R8G8B8A8_SINT},
      {{VertexFormat::RGBA, VertexSize::Size16, VertexType::UInt}, VK_FORMAT_R8G8B8A8_UINT},
      {{VertexFormat::RGBA, VertexSize::Size16, VertexType::Int}, VK_FORMAT_R16G16B16A16_SINT},
      {{VertexFormat::RGBA, VertexSize::Size16, VertexType::UInt}, VK_FORMAT_R16G16B16A16_UINT},
      {{VertexFormat::RGBA, VertexSize::Size16, VertexType::Float}, VK_FORMAT_R16G16B16A16_SFLOAT},
      {{VertexFormat::RGBA, VertexSize::Size32, VertexType::Int}, VK_FORMAT_R32G32B32A32_SINT},
      {{VertexFormat::RGBA, VertexSize::Size32, VertexType::UInt}, VK_FORMAT_R32G32B32A32_UINT},
      {{VertexFormat::RGBA, VertexSize::Size32, VertexType::Float}, VK_FORMAT_R32G32B32A32_SFLOAT},
      {{VertexFormat::RGBA, VertexSize::Size64, VertexType::Int}, VK_FORMAT_R64G64B64A64_SINT},
      {{VertexFormat::RGBA, VertexSize::Size64, VertexType::UInt}, VK_FORMAT_R64G64B64A64_UINT},
      {{VertexFormat::RGBA, VertexSize::Size64, VertexType::Float}, VK_FORMAT_R64G64B64A64_SFLOAT},
  };

  const auto format_tuple = std::make_tuple(format, size, type);
  const auto format_iter  = format_map.find(format_tuple);
  if (format_iter == format_map.end())
  {
    throw InvalidArgumentException("Invalid format");
  }

  return format_iter->second;
}

VkCullModeFlags
convert_to_vulkan_cull_mode(CullMode cull_mode)
{
  switch (cull_mode)
  {
    case CullMode::None: return VK_CULL_MODE_NONE;
    case CullMode::Front: return VK_CULL_MODE_FRONT_BIT;
    case CullMode::Back: return VK_CULL_MODE_BACK_BIT;
    default: throw InvalidArgumentException("Invalid cull mode");
  }
}

VkFrontFace
convert_to_vulkan_front_face(FrontFace front_face)
{
  switch (front_face)
  {
    case FrontFace::Clockwise: return VK_FRONT_FACE_CLOCKWISE;
    case FrontFace::CounterClockwise: return VK_FRONT_FACE_COUNTER_CLOCKWISE;
    default: throw InvalidArgumentException("Invalid front face");
  }
}

VkPolygonMode
convert_to_vulkan_polygon_mode(PolygonMode polygon_mode)
{
  switch (polygon_mode)
  {
    case PolygonMode::Fill: return VK_POLYGON_MODE_FILL;
    case PolygonMode::Line: return VK_POLYGON_MODE_LINE;
    case PolygonMode::Point: return VK_POLYGON_MODE_POINT;
    default: throw InvalidArgumentException("Invalid polygon mode");
  }
}

VkColorComponentFlags
convert_to_vulkan_color_component_flags(const ColorBlend& color_blend)
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


VulkanGraphicsPipeline::VulkanGraphicsPipeline(GfxWindowRenderTarget* target, const RendererConfig& config)
    : m_config{config},
      m_vulkan_app{GfxApplication::get_current()},
      m_target{target},
      m_logical_device{GfxApplication::get_current()->get_logical_device()},
      m_pipeline{nullptr},
      m_pipeline_layout{nullptr},
      m_descriptor_set_layout{nullptr}
{
  m_logger = Application::current_app()->create_logger("setsugen::VulkanGraphicsPipeline");

  m_render_pass = VulkanRenderPass::create(target, config);

  auto vertex_shader   = ShaderModule(m_config.vertex_shader.value(), VK_SHADER_STAGE_VERTEX_BIT);
  auto fragment_shader = ShaderModule(m_config.fragment_shader.value(), VK_SHADER_STAGE_FRAGMENT_BIT);

  std::vector<VkPipelineShaderStageCreateInfo> shader_stages;
  shader_stages.push_back(vertex_shader.get_stage_info());
  shader_stages.push_back(fragment_shader.get_stage_info());

  // Create the vertex input info

  std::vector<VkVertexInputBindingDescription>   vertex_binding_descriptions;
  std::vector<VkVertexInputAttributeDescription> vertex_attribute_descriptions;

  for (int i = 0; i < m_config.vertex_buffer_layouts.size(); ++i)
  {
    auto& layout = m_config.vertex_buffer_layouts[i];

    int stride = 0;

    for (auto element: layout)
    {
      VkVertexInputAttributeDescription attribute_description{};
      attribute_description.binding  = i;
      attribute_description.location = vertex_attribute_descriptions.size();
      attribute_description.offset   = stride;

      switch (element)
      {
        case VertexElement::Position:
          attribute_description.format =
              convert_to_vulkan_format(VertexFormat::RGB, VertexType::Float, VertexSize::Size32);
          stride += 3 * sizeof(float);
          break;
        case VertexElement::Normal:
          attribute_description.format =
              convert_to_vulkan_format(VertexFormat::RGB, VertexType::Float, VertexSize::Size32);
          stride += 3 * sizeof(float);
          break;
        case VertexElement::Uv:
          attribute_description.format =
              convert_to_vulkan_format(VertexFormat::RG, VertexType::Float, VertexSize::Size32);
          stride += 2 * sizeof(float);
          break;
        default: throw InvalidArgumentException("Invalid vertex element");
      }

      vertex_attribute_descriptions.push_back(attribute_description);
    }

    VkVertexInputBindingDescription binding_description{};
    binding_description.binding   = i;
    binding_description.stride    = stride;
    binding_description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    vertex_binding_descriptions.push_back(binding_description);
  }

  m_logger->trace("Vertex binding descriptions: {}", vertex_binding_descriptions.size());
  for (const auto& binding_description: vertex_binding_descriptions)
  {
    m_logger->trace("Binding: {}, Stride: {}, Input Rate: {}", binding_description.binding, binding_description.stride,
                    binding_description.inputRate);
  }

  m_logger->trace("Vertex attribute descriptions: {}", vertex_attribute_descriptions.size());
  for (const auto& attribute_description: vertex_attribute_descriptions)
  {
    m_logger->trace("Binding: {}, Location: {}, Format: {}, Offset: {}", attribute_description.binding,
                    attribute_description.location, attribute_description.format, attribute_description.offset);
  }

  VkPipelineVertexInputStateCreateInfo vertex_input_info{};
  vertex_input_info.sType                           = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  vertex_input_info.vertexBindingDescriptionCount   = (unsigned int) vertex_binding_descriptions.size();
  vertex_input_info.pVertexBindingDescriptions      = vertex_binding_descriptions.data();
  vertex_input_info.vertexAttributeDescriptionCount = (unsigned int) vertex_attribute_descriptions.size();
  vertex_input_info.pVertexAttributeDescriptions    = vertex_attribute_descriptions.data();

  // Create the input assembly
  VkPipelineInputAssemblyStateCreateInfo input_assembly{};
  input_assembly.sType                  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  input_assembly.topology               = convert_to_vulkan_topology(m_config.topology);
  input_assembly.primitiveRestartEnable = VK_FALSE;

  std::vector<VkViewport> viewports;
  for (const auto& [x, y, width, height, min_depth, max_depth]: m_config.viewports)
  {
    viewports.push_back({x, y, width, height, min_depth, max_depth});
  }

  if (viewports.empty())
  {
    m_logger->warn("No viewports specified");
  }

  std::vector<VkRect2D> scissors;
  for (const auto& [x, y, width, height]: m_config.scissors)
  {
    scissors.push_back({{(int) x, (int) y}, {(unsigned int) width, (unsigned int) height}});
  }

  if (scissors.empty())
  {
    m_logger->warn("No scissors specified");
  }

  VkPipelineViewportStateCreateInfo viewport_state{};
  viewport_state.sType         = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  viewport_state.viewportCount = (unsigned int) viewports.size();
  viewport_state.pViewports    = viewports.data();
  viewport_state.scissorCount  = (unsigned int) scissors.size();
  viewport_state.pScissors     = scissors.data();

  VkPipelineRasterizationStateCreateInfo rasterizer{};
  rasterizer.sType                   = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  rasterizer.depthClampEnable        = VK_FALSE;
  rasterizer.rasterizerDiscardEnable = VK_FALSE;
  rasterizer.polygonMode             = convert_to_vulkan_polygon_mode(m_config.polygon_mode);
  rasterizer.lineWidth               = 1.0f;
  rasterizer.cullMode                = convert_to_vulkan_cull_mode(m_config.cull_mode);
  rasterizer.frontFace               = convert_to_vulkan_front_face(m_config.front_face);
  rasterizer.depthBiasEnable         = VK_FALSE;

  VkPipelineMultisampleStateCreateInfo multisampling{};
  multisampling.sType                = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  multisampling.sampleShadingEnable  = VK_FALSE;
  multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

  std::vector<VkPipelineColorBlendAttachmentState> color_blend_attachments;
  for (auto color_blend: m_config.color_blends)
  {
    VkPipelineColorBlendAttachmentState color_blend_attachment{};
    color_blend_attachment.colorWriteMask = convert_to_vulkan_color_component_flags(color_blend);
    color_blend_attachment.blendEnable    = color_blend.blend_enable;

    color_blend_attachments.push_back(color_blend_attachment);
  }

  VkPipelineColorBlendStateCreateInfo color_blending{};
  color_blending.sType           = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  color_blending.logicOpEnable   = VK_FALSE;
  color_blending.logicOp         = VK_LOGIC_OP_COPY;
  color_blending.attachmentCount = (unsigned int) color_blend_attachments.size();
  color_blending.pAttachments    = color_blend_attachments.data();

  VkPipelineLayoutCreateInfo pipeline_layout_info{};
  pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;

  std::vector<VkDescriptorSetLayoutBinding> descriptor_set_bindings;
  for (int i = 0; i < m_config.uniform_buffer_layouts.size(); ++i)
  {
    auto& buffer_layout = m_config.uniform_buffer_layouts[i];

    VkDescriptorSetLayoutBinding binding{};
    binding.binding            = i;
    binding.descriptorType     = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    binding.descriptorCount    = 1;
    binding.pImmutableSamplers = nullptr;

    switch (buffer_layout.stage)
    {
      case UniformStage::Vertex: binding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT; break;
      case UniformStage::Fragment: binding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT; break;
      default: throw InvalidArgumentException("Invalid uniform stage");
    }

    descriptor_set_bindings.push_back(binding);
  }

  VkDescriptorSetLayoutCreateInfo descriptor_set_layout_info{};
  descriptor_set_layout_info.sType        = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  descriptor_set_layout_info.bindingCount = (unsigned int) descriptor_set_bindings.size();
  descriptor_set_layout_info.pBindings    = descriptor_set_bindings.data();

  auto descriptor_set_layout_result =
      vkCreateDescriptorSetLayout(m_logical_device, &descriptor_set_layout_info, nullptr, &m_descriptor_set_layout);
  if (descriptor_set_layout_result != VK_SUCCESS)
  {
    throw EngineException("Failed to create descriptor set layout");
  }

  pipeline_layout_info.setLayoutCount = 1;
  pipeline_layout_info.pSetLayouts    = &m_descriptor_set_layout;

  auto pipeline_layout_result =
      vkCreatePipelineLayout(m_logical_device, &pipeline_layout_info, nullptr, &m_pipeline_layout);
  if (pipeline_layout_result != VK_SUCCESS)
  {
    throw EngineException("Failed to create pipeline layout");
  }

  VkGraphicsPipelineCreateInfo pipeline_info{};
  pipeline_info.sType               = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  pipeline_info.stageCount          = (unsigned int) shader_stages.size();
  pipeline_info.pStages             = shader_stages.data();
  pipeline_info.pVertexInputState   = &vertex_input_info;
  pipeline_info.pInputAssemblyState = &input_assembly;
  pipeline_info.pViewportState      = &viewport_state;
  pipeline_info.pRasterizationState = &rasterizer;
  pipeline_info.pMultisampleState   = &multisampling;
  pipeline_info.pColorBlendState    = &color_blending;
  pipeline_info.layout              = m_pipeline_layout;
  pipeline_info.renderPass          = m_render_pass->get_handler();
  pipeline_info.subpass             = 0;
  pipeline_info.basePipelineHandle  = VK_NULL_HANDLE;

  auto pipeline_result =
      vkCreateGraphicsPipelines(m_logical_device, VK_NULL_HANDLE, 1, &pipeline_info, nullptr, &m_pipeline);
  if (pipeline_result != VK_SUCCESS)
  {
    throw EngineException("Failed to create graphics pipeline");
  }
}

VulkanGraphicsPipeline::~VulkanGraphicsPipeline()
{
  vkDestroyDescriptorSetLayout(m_logical_device, m_descriptor_set_layout, nullptr);
  vkDestroyPipeline(m_logical_device, m_pipeline, nullptr);
  vkDestroyPipelineLayout(m_logical_device, m_pipeline_layout, nullptr);
}

VkPipeline
VulkanGraphicsPipeline::get_handler() const
{
  return m_pipeline;
}

VkPipelineLayout
VulkanGraphicsPipeline::get_layout_handler() const
{
  return m_pipeline_layout;
}

VkRenderPass
VulkanGraphicsPipeline::get_render_pass() const
{
  return m_render_pass->get_handler();
}

std::unique_ptr<VulkanGraphicsPipeline>
VulkanGraphicsPipeline::create(GfxWindowRenderTarget* target, const RendererConfig& config)
{
  return std::make_unique<VulkanGraphicsPipeline>(target, config);
}

const RendererConfig&
VulkanGraphicsPipeline::get_config() const
{
  return m_config;
}

VkDescriptorSetLayout
VulkanGraphicsPipeline::get_descriptor_set_layout() const
{
  return m_descriptor_set_layout;
}

} // namespace setsugen
