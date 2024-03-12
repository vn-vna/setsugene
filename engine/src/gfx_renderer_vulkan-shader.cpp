#include "gfx_renderer.h"

namespace setsugen
{

ShaderModule::ShaderModule(const String& module_name)
{
  String shader_path = "assets/shaders/" + module_name + ".spv";
  IFileStream file(module_name, std::ios::ate | std::ios::binary);

  if (!file.is_open())
  {
    throw InvalidArgumentException("Failed to open shader file: " + module_name);
  }

  Size file_size = static_cast<Size>(file.tellg());
  file.seekg(0);
  DArray<Byte> m_code(file_size);
  file.read(reinterpret_cast<Char*>(m_code.data()), file_size);

  VkShaderModuleCreateInfo create_info = {};
  create_info.sType                    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  create_info.codeSize                 = file_size;
  create_info.pCode                    = reinterpret_cast<UInt32*>(m_code.data());

  auto logical_device = m_vulkan_app.lock()->get_logical_device();
  auto result = vkCreateShaderModule(logical_device, &create_info, nullptr, &m_shader_module);

  if (result != VK_SUCCESS)
  {
    throw EngineException("Failed to create shader module");
  }
}

ShaderModule::~ShaderModule()
{
  auto logical_device = m_vulkan_app.lock()->get_logical_device();
  vkDestroyShaderModule(logical_device, m_shader_module, nullptr);
}

VkShaderModule ShaderModule::get_module() const
{
  return m_shader_module;
}

}  // namespace setsugen