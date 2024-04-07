#include <filesystem>

#include "gfx_renderer.h"

namespace setsugen
{
ShaderModule::ShaderModule(const std::string& module_name)
    : m_vulkan_app{VulkanApplication::get_current()},
      m_logical_device{VulkanApplication::get_current()->get_logical_device()}, m_shader_module{nullptr}
{
  const auto assets_path = get_assets_path();

  const auto path = std::filesystem::path(Formatter::format("{}/shaders/{}.spv", assets_path, module_name));

  if (!std::filesystem::exists(path))
  {
    throw InvalidArgumentException(
        Formatter::format("Cannot find shader module {} in folder {}", module_name, assets_path));
  }

  std::ifstream file;
  file.open(path, std::ios::ate | std::ios::binary);
  if (!file.is_open())
  {
    throw InvalidArgumentException(
        Formatter::format("Cannot open shader module {}, in folder {}", module_name, assets_path));
  }

  const size_t file_size = file.tellg();
  file.seekg(0);
  std::vector<char> m_code(file_size);
  file.read(m_code.data(), file_size);

  VkShaderModuleCreateInfo create_info = {};
  create_info.sType                    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  create_info.codeSize                 = file_size;
  create_info.pCode                    = reinterpret_cast<unsigned int*>(m_code.data());

  auto result = vkCreateShaderModule(m_logical_device, &create_info, nullptr, &m_shader_module);

  if (result != VK_SUCCESS)
  {
    throw EngineException("Failed to create shader module");
  }
}

ShaderModule::~ShaderModule()
{
  vkDestroyShaderModule(m_logical_device, m_shader_module, nullptr);
}

VkShaderModule
ShaderModule::get_module() const
{
  return m_shader_module;
}
} // namespace setsugen
