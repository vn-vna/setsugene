#include "vulkan_physical_device.h"

namespace setsugen::gfx::vulkan
{

PhysicalDevice::PhysicalDevice(Instance& instance, VkPhysicalDevice physical_device)
    : m_physical_device(physical_device), m_limits(physical_device), m_features(physical_device), m_instance(instance)
{
  vkGetPhysicalDeviceProperties(m_physical_device, &m_properties);

  UInt32 queue_family_count = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(m_physical_device, &queue_family_count, nullptr);

  DArray<VkQueueFamilyProperties> queue_families(queue_family_count);
  vkGetPhysicalDeviceQueueFamilyProperties(m_physical_device, &queue_family_count, queue_families.data());

  for (UInt32 i = 0; i < queue_family_count; ++i)
  {
    m_queue_families.push_back(PhysicalDeviceQueueFamily{i, queue_families[i]});
  }
}

PhysicalDevice::~PhysicalDevice()
{}

VkPhysicalDevice
PhysicalDevice::handle() const
{
  return m_physical_device;
}

Instance&
PhysicalDevice::instance()
{
  return m_instance;
}

Version
PhysicalDevice::api_version() const
{
  return Version{m_properties.apiVersion};
}

Version
PhysicalDevice::driver_version() const
{
  return Version{m_properties.driverVersion};
}

UInt32
PhysicalDevice::vendor_id() const
{
  return m_properties.vendorID;
}

UInt32
PhysicalDevice::device_id() const
{
  return m_properties.deviceID;
}

PhysicalDeviceType
PhysicalDevice::type() const
{
  switch (m_properties.deviceType)
  {
    case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: return PhysicalDeviceType::IntegratedGPU;
    case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU: return PhysicalDeviceType::DiscreteGPU;
    case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU: return PhysicalDeviceType::VirtualGPU;
    case VK_PHYSICAL_DEVICE_TYPE_CPU: return PhysicalDeviceType::CPU;
    default: return PhysicalDeviceType::Other;
  }
}

String
PhysicalDevice::name() const
{
  return String{m_properties.deviceName};
}

PhysicalDeviceLimits&
PhysicalDevice::limits()
{
  return m_limits;
}

DArray<PhysicalDeviceQueueFamily>&
PhysicalDevice::queue_families()
{
  return m_queue_families;
}

PhysicalDeviceQueueFamily::PhysicalDeviceQueueFamily(UInt32 index, VkQueueFamilyProperties properties)
    : m_index(index), m_properties(properties)
{}

UInt32
PhysicalDeviceQueueFamily::queue_count() const
{
  return m_properties.queueCount;
}

Bool
PhysicalDeviceQueueFamily::graphics() const
{
  return (m_properties.queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0;
}

Bool
PhysicalDeviceQueueFamily::compute() const
{
  return (m_properties.queueFlags & VK_QUEUE_COMPUTE_BIT) != 0;
}

Bool
PhysicalDeviceQueueFamily::transfer() const
{
  return (m_properties.queueFlags & VK_QUEUE_TRANSFER_BIT) != 0;
}

Bool
PhysicalDeviceQueueFamily::sparse_binding() const
{
  return (m_properties.queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) != 0;
}

Bool
PhysicalDeviceQueueFamily::protected_memory() const
{
  return (m_properties.queueFlags & VK_QUEUE_PROTECTED_BIT) != 0;
}

UInt32
PhysicalDeviceQueueFamily::index() const
{
  return m_index;
}

PhysicalDeviceLimits::PhysicalDeviceLimits(VkPhysicalDevice device)
{
  vkGetPhysicalDeviceProperties(device, &m_properties);
}

UInt32
PhysicalDeviceLimits::max_image_dimension_1d() const
{
  return m_properties.limits.maxImageDimension1D;
}

UInt32
PhysicalDeviceLimits::max_image_dimension_2d() const
{
  return m_properties.limits.maxImageDimension2D;
}

UInt32
PhysicalDeviceLimits::max_image_dimension_3d() const
{
  return m_properties.limits.maxImageDimension3D;
}

UInt32
PhysicalDeviceLimits::max_image_dimension_cube() const
{
  return m_properties.limits.maxImageDimensionCube;
}

UInt32
PhysicalDeviceLimits::max_image_array_layers() const
{
  return m_properties.limits.maxImageArrayLayers;
}

UInt32
PhysicalDeviceLimits::max_texel_buffer_elements() const
{
  return m_properties.limits.maxTexelBufferElements;
}

UInt32
PhysicalDeviceLimits::max_uniform_buffer_range() const
{
  return m_properties.limits.maxUniformBufferRange;
}

UInt32
PhysicalDeviceLimits::max_storage_buffer_range() const
{
  return m_properties.limits.maxStorageBufferRange;
}

UInt32
PhysicalDeviceLimits::max_push_constants_size() const
{
  return m_properties.limits.maxPushConstantsSize;
}

UInt32
PhysicalDeviceLimits::max_memory_allocation_count() const
{
  return m_properties.limits.maxMemoryAllocationCount;
}

UInt32
PhysicalDeviceLimits::max_sampler_allocation_count() const
{
  return m_properties.limits.maxSamplerAllocationCount;
}

UInt64
PhysicalDeviceLimits::buffer_image_granularity() const
{
  return m_properties.limits.bufferImageGranularity;
}

UInt64
PhysicalDeviceLimits::sparse_address_space_size() const
{
  return m_properties.limits.sparseAddressSpaceSize;
}

UInt32
PhysicalDeviceLimits::max_bound_descriptor_sets() const
{
  return m_properties.limits.maxBoundDescriptorSets;
}

UInt32
PhysicalDeviceLimits::max_per_stage_descriptor_samplers() const
{
  return m_properties.limits.maxPerStageDescriptorSamplers;
}

UInt32
PhysicalDeviceLimits::max_per_stage_descriptor_uniform_buffers() const
{
  return m_properties.limits.maxPerStageDescriptorUniformBuffers;
}

UInt32
PhysicalDeviceLimits::max_per_stage_descriptor_storage_buffers() const
{
  return m_properties.limits.maxPerStageDescriptorStorageBuffers;
}

UInt32
PhysicalDeviceLimits::max_per_stage_descriptor_sampled_images() const
{
  return m_properties.limits.maxPerStageDescriptorSampledImages;
}

UInt32
PhysicalDeviceLimits::max_per_stage_descriptor_storage_images() const
{
  return m_properties.limits.maxPerStageDescriptorStorageImages;
}

UInt32
PhysicalDeviceLimits::max_per_stage_descriptor_input_attachments() const
{
  return m_properties.limits.maxPerStageDescriptorInputAttachments;
}

UInt32
PhysicalDeviceLimits::max_per_stage_resources() const
{
  return m_properties.limits.maxPerStageResources;
}

UInt32
PhysicalDeviceLimits::max_descriptor_set_samplers() const
{
  return m_properties.limits.maxDescriptorSetSamplers;
}

UInt32
PhysicalDeviceLimits::max_descriptor_set_uniform_buffers() const
{
  return m_properties.limits.maxDescriptorSetUniformBuffers;
}

UInt32
PhysicalDeviceLimits::max_descriptor_set_uniform_buffers_dynamic() const
{
  return m_properties.limits.maxDescriptorSetUniformBuffersDynamic;
}

UInt32
PhysicalDeviceLimits::max_descriptor_set_storage_buffers() const
{
  return m_properties.limits.maxDescriptorSetStorageBuffers;
}

UInt32
PhysicalDeviceLimits::max_descriptor_set_storage_buffers_dynamic() const
{
  return m_properties.limits.maxDescriptorSetStorageBuffersDynamic;
}

UInt32
PhysicalDeviceLimits::max_descriptor_set_sampled_images() const
{
  return m_properties.limits.maxDescriptorSetSampledImages;
}

UInt32
PhysicalDeviceLimits::max_descriptor_set_storage_images() const
{
  return m_properties.limits.maxDescriptorSetStorageImages;
}

UInt32
PhysicalDeviceLimits::max_descriptor_set_input_attachments() const
{
  return m_properties.limits.maxDescriptorSetInputAttachments;
}

UInt32
PhysicalDeviceLimits::max_vertex_input_attributes() const
{
  return m_properties.limits.maxVertexInputAttributes;
}

UInt32
PhysicalDeviceLimits::max_vertex_input_bindings() const
{
  return m_properties.limits.maxVertexInputBindings;
}

UInt32
PhysicalDeviceLimits::max_vertex_input_attribute_offset() const
{
  return m_properties.limits.maxVertexInputAttributeOffset;
}

UInt32
PhysicalDeviceLimits::max_vertex_input_binding_stride() const
{
  return m_properties.limits.maxVertexInputBindingStride;
}

UInt32
PhysicalDeviceLimits::max_vertex_output_components() const
{
  return m_properties.limits.maxVertexOutputComponents;
}

UInt32
PhysicalDeviceLimits::max_tessellation_generation_level() const
{
  return m_properties.limits.maxTessellationGenerationLevel;
}

UInt32
PhysicalDeviceLimits::max_tessellation_patch_size() const
{
  return m_properties.limits.maxTessellationPatchSize;
}

UInt32
PhysicalDeviceLimits::max_tessellation_control_per_vertex_input_components() const
{
  return m_properties.limits.maxTessellationControlPerVertexInputComponents;
}

UInt32
PhysicalDeviceLimits::max_tessellation_control_per_vertex_output_components() const
{
  return m_properties.limits.maxTessellationControlPerVertexOutputComponents;
}

UInt32
PhysicalDeviceLimits::max_tessellation_control_per_patch_output_components() const
{
  return m_properties.limits.maxTessellationControlPerPatchOutputComponents;
}

UInt32
PhysicalDeviceLimits::max_tessellation_control_total_output_components() const
{
  return m_properties.limits.maxTessellationControlTotalOutputComponents;
}

UInt32
PhysicalDeviceLimits::max_tessellation_evaluation_input_components() const
{
  return m_properties.limits.maxTessellationEvaluationInputComponents;
}

UInt32
PhysicalDeviceLimits::max_tessellation_evaluation_output_components() const
{
  return m_properties.limits.maxTessellationEvaluationOutputComponents;
}

UInt32
PhysicalDeviceLimits::max_geometry_shader_invocations() const
{
  return m_properties.limits.maxGeometryShaderInvocations;
}

UInt32
PhysicalDeviceLimits::max_geometry_input_components() const
{
  return m_properties.limits.maxGeometryInputComponents;
}

UInt32
PhysicalDeviceLimits::max_geometry_output_components() const
{
  return m_properties.limits.maxGeometryOutputComponents;
}

UInt32
PhysicalDeviceLimits::max_geometry_output_vertices() const
{
  return m_properties.limits.maxGeometryOutputVertices;
}

UInt32
PhysicalDeviceLimits::max_geometry_total_output_components() const
{
  return m_properties.limits.maxGeometryTotalOutputComponents;
}

UInt32
PhysicalDeviceLimits::max_fragment_input_components() const
{
  return m_properties.limits.maxFragmentInputComponents;
}

UInt32
PhysicalDeviceLimits::max_fragment_output_attachments() const
{
  return m_properties.limits.maxFragmentOutputAttachments;
}

UInt32
PhysicalDeviceLimits::max_fragment_dual_src_attachments() const
{
  return m_properties.limits.maxFragmentDualSrcAttachments;
}

UInt32
PhysicalDeviceLimits::max_fragment_combined_output_resources() const
{
  return m_properties.limits.maxFragmentCombinedOutputResources;
}

UInt32
PhysicalDeviceLimits::max_compute_shared_memory_size() const
{
  return m_properties.limits.maxComputeSharedMemorySize;
}

Dim3U
PhysicalDeviceLimits::max_compute_work_group_count() const
{
  return {
      m_properties.limits.maxComputeWorkGroupCount[0],
      m_properties.limits.maxComputeWorkGroupCount[1],
      m_properties.limits.maxComputeWorkGroupCount[2],
  };
}

UInt32
PhysicalDeviceLimits::max_compute_work_group_invocations() const
{
  return m_properties.limits.maxComputeWorkGroupInvocations;
}

Dim3U
PhysicalDeviceLimits::max_compute_work_group_size() const
{
  return {
      m_properties.limits.maxComputeWorkGroupSize[0],
      m_properties.limits.maxComputeWorkGroupSize[1],
      m_properties.limits.maxComputeWorkGroupSize[2],
  };
}

UInt32
PhysicalDeviceLimits::sub_pixel_precision_bits() const
{
  return m_properties.limits.subPixelPrecisionBits;
}

UInt32
PhysicalDeviceLimits::sub_texel_precision_bits() const
{
  return m_properties.limits.subTexelPrecisionBits;
}

UInt32
PhysicalDeviceLimits::mipmap_precision_bits() const
{
  return m_properties.limits.mipmapPrecisionBits;
}

UInt32
PhysicalDeviceLimits::max_draw_indexed_index_value() const
{
  return m_properties.limits.maxDrawIndexedIndexValue;
}

UInt32
PhysicalDeviceLimits::max_draw_indirect_count() const
{
  return m_properties.limits.maxDrawIndirectCount;
}

Float32
PhysicalDeviceLimits::max_sampler_lod_bias() const
{
  return m_properties.limits.maxSamplerLodBias;
}

Float32
PhysicalDeviceLimits::max_sampler_anisotropy() const
{
  return m_properties.limits.maxSamplerAnisotropy;
}

UInt32
PhysicalDeviceLimits::max_viewports() const
{
  return m_properties.limits.maxViewports;
}

Dim2U
PhysicalDeviceLimits::max_viewport_dimensions() const
{
  return {m_properties.limits.maxViewportDimensions[0], m_properties.limits.maxViewportDimensions[1]};
}

Dim2F
PhysicalDeviceLimits::viewport_bounds_range() const
{
  return {m_properties.limits.viewportBoundsRange[0], m_properties.limits.viewportBoundsRange[1]};
}

UInt32
PhysicalDeviceLimits::viewport_sub_pixel_bits() const
{
  return m_properties.limits.viewportSubPixelBits;
}

UInt64
PhysicalDeviceLimits::min_memory_map_alignment() const
{
  return m_properties.limits.minMemoryMapAlignment;
}

UInt64
PhysicalDeviceLimits::min_texel_buffer_offset_alignment() const
{
  return m_properties.limits.minTexelBufferOffsetAlignment;
}

UInt64
PhysicalDeviceLimits::min_uniform_buffer_offset_alignment() const
{
  return m_properties.limits.minUniformBufferOffsetAlignment;
}

UInt64
PhysicalDeviceLimits::min_storage_buffer_offset_alignment() const
{
  return m_properties.limits.minStorageBufferOffsetAlignment;
}

Int32
PhysicalDeviceLimits::min_texel_offset() const
{
  return m_properties.limits.minTexelOffset;
}

UInt32
PhysicalDeviceLimits::max_texel_offset() const
{
  return m_properties.limits.maxTexelOffset;
}

Int32
PhysicalDeviceLimits::min_texel_gather_offset() const
{
  return m_properties.limits.minTexelGatherOffset;
}

UInt32
PhysicalDeviceLimits::max_texel_gather_offset() const
{
  return m_properties.limits.maxTexelGatherOffset;
}

Float32
PhysicalDeviceLimits::min_interpolation_offset() const
{
  return m_properties.limits.minInterpolationOffset;
}

Float32
PhysicalDeviceLimits::max_interpolation_offset() const
{
  return m_properties.limits.maxInterpolationOffset;
}

UInt32
PhysicalDeviceLimits::sub_pixel_interpolation_offset_bits() const
{
  return m_properties.limits.subPixelInterpolationOffsetBits;
}

UInt32
PhysicalDeviceLimits::max_framebuffer_width() const
{
  return m_properties.limits.maxFramebufferWidth;
}

UInt32
PhysicalDeviceLimits::max_framebuffer_height() const
{
  return m_properties.limits.maxFramebufferHeight;
}

UInt32
PhysicalDeviceLimits::max_framebuffer_layers() const
{
  return m_properties.limits.maxFramebufferLayers;
}

UInt32
PhysicalDeviceLimits::framebuffer_color_sample_counts() const
{
  return m_properties.limits.framebufferColorSampleCounts;
}

UInt32
PhysicalDeviceLimits::framebuffer_depth_sample_counts() const
{
  return m_properties.limits.framebufferDepthSampleCounts;
}

UInt32
PhysicalDeviceLimits::framebuffer_stencil_sample_counts() const
{
  return m_properties.limits.framebufferStencilSampleCounts;
}

UInt32
PhysicalDeviceLimits::framebuffer_no_attachments_sample_counts() const
{
  return m_properties.limits.framebufferNoAttachmentsSampleCounts;
}

UInt32
PhysicalDeviceLimits::max_color_attachments() const
{
  return m_properties.limits.maxColorAttachments;
}

UInt32
PhysicalDeviceLimits::sampled_image_color_sample_counts() const
{
  return m_properties.limits.sampledImageColorSampleCounts;
}

UInt32
PhysicalDeviceLimits::sampled_image_integer_sample_counts() const
{
  return m_properties.limits.sampledImageIntegerSampleCounts;
}

UInt32
PhysicalDeviceLimits::sampled_image_depth_sample_counts() const
{
  return m_properties.limits.sampledImageDepthSampleCounts;
}

UInt32
PhysicalDeviceLimits::sampled_image_stencil_sample_counts() const
{
  return m_properties.limits.sampledImageStencilSampleCounts;
}

UInt32
PhysicalDeviceLimits::storage_image_sample_counts() const
{
  return m_properties.limits.storageImageSampleCounts;
}

UInt32
PhysicalDeviceLimits::max_sample_mask_words() const
{
  return m_properties.limits.maxSampleMaskWords;
}

Bool
PhysicalDeviceLimits::timestamp_compute_and_graphics() const
{
  return m_properties.limits.timestampComputeAndGraphics;
}

Float32
PhysicalDeviceLimits::timestamp_period() const
{
  return m_properties.limits.timestampPeriod;
}

UInt32
PhysicalDeviceLimits::max_clip_distances() const
{
  return m_properties.limits.maxClipDistances;
}

UInt32
PhysicalDeviceLimits::max_cull_distances() const
{
  return m_properties.limits.maxCullDistances;
}

UInt32
PhysicalDeviceLimits::max_combined_clip_and_cull_distances() const
{
  return m_properties.limits.maxCombinedClipAndCullDistances;
}

UInt32
PhysicalDeviceLimits::discrete_queue_priorities() const
{
  return m_properties.limits.discreteQueuePriorities;
}

Dim2F
PhysicalDeviceLimits::point_size_range() const
{
  return {m_properties.limits.pointSizeRange[0], m_properties.limits.pointSizeRange[1]};
}

Dim2F
PhysicalDeviceLimits::line_width_range() const
{
  return {
      m_properties.limits.lineWidthRange[0],
      m_properties.limits.lineWidthRange[1],
  };
}

Float32
PhysicalDeviceLimits::point_size_granularity() const
{
  return m_properties.limits.pointSizeGranularity;
}

Float32
PhysicalDeviceLimits::line_width_granularity() const
{
  return m_properties.limits.lineWidthGranularity;
}

Bool
PhysicalDeviceLimits::strict_lines() const
{
  return m_properties.limits.strictLines;
}

Bool
PhysicalDeviceLimits::standard_sample_locations() const
{
  return m_properties.limits.standardSampleLocations;
}

UInt64
PhysicalDeviceLimits::optimal_buffer_copy_offset_alignment() const
{
  return m_properties.limits.optimalBufferCopyOffsetAlignment;
}

UInt64
PhysicalDeviceLimits::optimal_buffer_copy_row_pitch_alignment() const
{
  return m_properties.limits.optimalBufferCopyRowPitchAlignment;
}

UInt64
PhysicalDeviceLimits::non_coherent_atom_size() const
{
  return m_properties.limits.nonCoherentAtomSize;
}

PhysicalDeviceFeatures::PhysicalDeviceFeatures(VkPhysicalDevice device)
{
  vkGetPhysicalDeviceFeatures(device, &m_features);
}

Bool
PhysicalDeviceFeatures::robust_buffer_access() const
{
  return m_features.robustBufferAccess;
}


Bool
PhysicalDeviceFeatures::full_draw_index_uint32() const
{
  return m_features.fullDrawIndexUint32;
}


Bool
PhysicalDeviceFeatures::image_cube_array() const
{
  return m_features.imageCubeArray;
}


Bool
PhysicalDeviceFeatures::independent_blend() const
{
  return m_features.independentBlend;
}


Bool
PhysicalDeviceFeatures::geometry_shader() const
{
  return m_features.geometryShader;
}


Bool
PhysicalDeviceFeatures::tessellation_shader() const
{
  return m_features.tessellationShader;
}


Bool
PhysicalDeviceFeatures::sample_rate_shading() const
{
  return m_features.sampleRateShading;
}


Bool
PhysicalDeviceFeatures::dual_src_blend() const
{
  return m_features.dualSrcBlend;
}


Bool
PhysicalDeviceFeatures::logic_op() const
{
  return m_features.logicOp;
}


Bool
PhysicalDeviceFeatures::multi_draw_indirect() const
{
  return m_features.multiDrawIndirect;
}


Bool
PhysicalDeviceFeatures::draw_indirect_first_instance() const
{
  return m_features.drawIndirectFirstInstance;
}


Bool
PhysicalDeviceFeatures::depth_clamp() const
{
  return m_features.depthClamp;
}


Bool
PhysicalDeviceFeatures::depth_bias_clamp() const
{
  return m_features.depthBiasClamp;
}


Bool
PhysicalDeviceFeatures::fill_mode_non_solid() const
{
  return m_features.fillModeNonSolid;
}


Bool
PhysicalDeviceFeatures::depth_bounds() const
{
  return m_features.depthBounds;
}


Bool
PhysicalDeviceFeatures::wide_lines() const
{
  return m_features.wideLines;
}


Bool
PhysicalDeviceFeatures::large_points() const
{
  return m_features.largePoints;
}


Bool
PhysicalDeviceFeatures::alpha_to_one() const
{
  return m_features.alphaToOne;
}


Bool
PhysicalDeviceFeatures::multi_viewport() const
{
  return m_features.multiViewport;
}


Bool
PhysicalDeviceFeatures::sampler_anisotropy() const
{
  return m_features.samplerAnisotropy;
}


Bool
PhysicalDeviceFeatures::texture_compression_etc2() const
{
  return m_features.textureCompressionETC2;
}


Bool
PhysicalDeviceFeatures::texture_compression_astc_ldr() const
{
  return m_features.textureCompressionASTC_LDR;
}


Bool
PhysicalDeviceFeatures::texture_compression_bc() const
{
  return m_features.textureCompressionBC;
}


Bool
PhysicalDeviceFeatures::occlusion_query_precise() const
{
  return m_features.occlusionQueryPrecise;
}


Bool
PhysicalDeviceFeatures::pipeline_statistics_query() const
{
  return m_features.pipelineStatisticsQuery;
}


Bool
PhysicalDeviceFeatures::vertex_pipeline_stores_and_atomics() const
{
  return m_features.vertexPipelineStoresAndAtomics;
}


Bool
PhysicalDeviceFeatures::fragment_stores_and_atomics() const
{
  return m_features.fragmentStoresAndAtomics;
}


Bool
PhysicalDeviceFeatures::shader_tessellation_and_geometry_point_size() const
{
  return m_features.shaderTessellationAndGeometryPointSize;
}


Bool
PhysicalDeviceFeatures::shader_image_gather_extended() const
{
  return m_features.shaderImageGatherExtended;
}


Bool
PhysicalDeviceFeatures::shader_storage_image_extended_formats() const
{
  return m_features.shaderStorageImageExtendedFormats;
}


Bool
PhysicalDeviceFeatures::shader_storage_image_multisample() const
{
  return m_features.shaderStorageImageMultisample;
}


Bool
PhysicalDeviceFeatures::shader_storage_image_read_without_format() const
{
  return m_features.shaderStorageImageReadWithoutFormat;
}


Bool
PhysicalDeviceFeatures::shader_storage_image_write_without_format() const
{
  return m_features.shaderStorageImageWriteWithoutFormat;
}


Bool
PhysicalDeviceFeatures::shader_uniform_buffer_array_dynamic_indexing() const
{
  return m_features.shaderUniformBufferArrayDynamicIndexing;
}


Bool
PhysicalDeviceFeatures::shader_sampled_image_array_dynamic_indexing() const
{
  return m_features.shaderSampledImageArrayDynamicIndexing;
}


Bool
PhysicalDeviceFeatures::shader_storage_buffer_array_dynamic_indexing() const
{
  return m_features.shaderStorageBufferArrayDynamicIndexing;
}


Bool
PhysicalDeviceFeatures::shader_storage_image_array_dynamic_indexing() const
{
  return m_features.shaderStorageImageArrayDynamicIndexing;
}


Bool
PhysicalDeviceFeatures::shader_clip_distance() const
{
  return m_features.shaderClipDistance;
}


Bool
PhysicalDeviceFeatures::shader_cull_distance() const
{
  return m_features.shaderCullDistance;
}


Bool
PhysicalDeviceFeatures::shader_float64() const
{
  return m_features.shaderFloat64;
}


Bool
PhysicalDeviceFeatures::shader_int64() const
{
  return m_features.shaderInt64;
}


Bool
PhysicalDeviceFeatures::shader_int16() const
{
  return m_features.shaderInt16;
}


Bool
PhysicalDeviceFeatures::shader_resource_residency() const
{
  return m_features.shaderResourceResidency;
}


Bool
PhysicalDeviceFeatures::shader_resource_min_lod() const
{
  return m_features.shaderResourceMinLod;
}


Bool
PhysicalDeviceFeatures::sparse_binding() const
{
  return m_features.sparseBinding;
}


Bool
PhysicalDeviceFeatures::sparse_residency_buffer() const
{
  return m_features.sparseResidencyBuffer;
}


Bool
PhysicalDeviceFeatures::sparse_residency_image_2d() const
{
  return m_features.sparseResidencyImage2D;
}


Bool
PhysicalDeviceFeatures::sparse_residency_image_3d() const
{
  return m_features.sparseResidencyImage3D;
}


Bool
PhysicalDeviceFeatures::sparse_residency_2_samples() const
{
  return m_features.sparseResidency2Samples;
}


Bool
PhysicalDeviceFeatures::sparse_residency_4_samples() const
{
  return m_features.sparseResidency4Samples;
}


Bool
PhysicalDeviceFeatures::sparse_residency_8_samples() const
{
  return m_features.sparseResidency8Samples;
}


Bool
PhysicalDeviceFeatures::sparse_residency_16_samples() const
{
  return m_features.sparseResidency16Samples;
}


Bool
PhysicalDeviceFeatures::sparse_residency_aliased() const
{
  return m_features.sparseResidencyAliased;
}

Bool
PhysicalDeviceFeatures::variable_multisample_rate() const
{
  return m_features.variableMultisampleRate;
}


Bool
PhysicalDeviceFeatures::inherited_queries() const
{
  return m_features.inheritedQueries;
}


} // namespace setsugen::gfx::vulkan
