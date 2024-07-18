#include <memory>
#include <vector>
#include <vulkan/vulkan_core.h>
#include "gfx_renderer.h"

namespace setsugen
{

VulkanRenderPass::VulkanRenderPass(GfxWindowRenderTarget* target, const RendererConfig& config)
    : m_vulkan_app{GfxApplication::get_current()}, m_config{config}, m_target{target}
{
  m_logical_device = m_vulkan_app->get_logical_device();

  VkAttachmentDescription color_attachment{};
  color_attachment.format         = m_target->get_surface_format();
  color_attachment.samples        = VK_SAMPLE_COUNT_1_BIT;
  color_attachment.loadOp         = VK_ATTACHMENT_LOAD_OP_CLEAR;
  color_attachment.storeOp        = VK_ATTACHMENT_STORE_OP_STORE;
  color_attachment.stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  color_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  color_attachment.initialLayout  = VK_IMAGE_LAYOUT_UNDEFINED;
  color_attachment.finalLayout    = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

  VkAttachmentReference color_attachment_ref{};
  color_attachment_ref.attachment = 0;
  color_attachment_ref.layout     = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  VkSubpassDescription subpass{};
  subpass.pipelineBindPoint    = VK_PIPELINE_BIND_POINT_GRAPHICS;
  subpass.colorAttachmentCount = 1;
  subpass.pColorAttachments    = &color_attachment_ref;

  // Create render pass
  VkRenderPassCreateInfo render_pass_info{};
  render_pass_info.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  render_pass_info.attachmentCount = 1;
  render_pass_info.pAttachments    = &color_attachment;
  render_pass_info.subpassCount    = 1;
  render_pass_info.pSubpasses      = &subpass;

  VkSubpassDependency dependency{};
  dependency.srcSubpass    = VK_SUBPASS_EXTERNAL;
  dependency.dstSubpass    = 0;
  dependency.srcStageMask  = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  dependency.srcAccessMask = 0;
  dependency.dstStageMask  = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

  render_pass_info.dependencyCount = 1;
  render_pass_info.pDependencies   = &dependency;

  auto render_pass_result = vkCreateRenderPass(m_logical_device, &render_pass_info, nullptr, &m_render_pass);
  if (render_pass_result != VK_SUCCESS)
  {
    throw EngineException("Failed to create render pass");
  }
}

VulkanRenderPass::~VulkanRenderPass()
{
  vkDestroyRenderPass(m_logical_device, m_render_pass, nullptr);
}

VkRenderPass
VulkanRenderPass::get_handler() const
{
  return m_render_pass;
}

std::unique_ptr<VulkanRenderPass>
VulkanRenderPass::create(GfxWindowRenderTarget* target, const RendererConfig& config)
{
  return std::make_unique<VulkanRenderPass>(target, config);
}

} // namespace setsugen
