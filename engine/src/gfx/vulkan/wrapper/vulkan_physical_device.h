#include <setsugen/math.h>
#include <setsugen/version.h>
#include <volk.h>

namespace setsugen::gfx::vulkan
{

class Instance;
class PhysicalDevice;

enum class PhysicalDeviceType
{
  Other         = 0,
  IntegratedGPU = 1,
  DiscreteGPU   = 2,
  VirtualGPU    = 3,
  CPU           = 4
};

class PhysicalDeviceLimits
{
public:
  PhysicalDeviceLimits(VkPhysicalDevice device);

  UInt32  max_image_dimension_1d() const;
  UInt32  max_image_dimension_2d() const;
  UInt32  max_image_dimension_3d() const;
  UInt32  max_image_dimension_cube() const;
  UInt32  max_image_array_layers() const;
  UInt32  max_texel_buffer_elements() const;
  UInt32  max_uniform_buffer_range() const;
  UInt32  max_storage_buffer_range() const;
  UInt32  max_push_constants_size() const;
  UInt32  max_memory_allocation_count() const;
  UInt32  max_sampler_allocation_count() const;
  UInt64  buffer_image_granularity() const;
  UInt64  sparse_address_space_size() const;
  UInt32  max_bound_descriptor_sets() const;
  UInt32  max_per_stage_descriptor_samplers() const;
  UInt32  max_per_stage_descriptor_uniform_buffers() const;
  UInt32  max_per_stage_descriptor_storage_buffers() const;
  UInt32  max_per_stage_descriptor_sampled_images() const;
  UInt32  max_per_stage_descriptor_storage_images() const;
  UInt32  max_per_stage_descriptor_input_attachments() const;
  UInt32  max_per_stage_resources() const;
  UInt32  max_descriptor_set_samplers() const;
  UInt32  max_descriptor_set_uniform_buffers() const;
  UInt32  max_descriptor_set_uniform_buffers_dynamic() const;
  UInt32  max_descriptor_set_storage_buffers() const;
  UInt32  max_descriptor_set_storage_buffers_dynamic() const;
  UInt32  max_descriptor_set_sampled_images() const;
  UInt32  max_descriptor_set_storage_images() const;
  UInt32  max_descriptor_set_input_attachments() const;
  UInt32  max_vertex_input_attributes() const;
  UInt32  max_vertex_input_bindings() const;
  UInt32  max_vertex_input_attribute_offset() const;
  UInt32  max_vertex_input_binding_stride() const;
  UInt32  max_vertex_output_components() const;
  UInt32  max_tessellation_generation_level() const;
  UInt32  max_tessellation_patch_size() const;
  UInt32  max_tessellation_control_per_vertex_input_components() const;
  UInt32  max_tessellation_control_per_vertex_output_components() const;
  UInt32  max_tessellation_control_per_patch_output_components() const;
  UInt32  max_tessellation_control_total_output_components() const;
  UInt32  max_tessellation_evaluation_input_components() const;
  UInt32  max_tessellation_evaluation_output_components() const;
  UInt32  max_geometry_shader_invocations() const;
  UInt32  max_geometry_input_components() const;
  UInt32  max_geometry_output_components() const;
  UInt32  max_geometry_output_vertices() const;
  UInt32  max_geometry_total_output_components() const;
  UInt32  max_fragment_input_components() const;
  UInt32  max_fragment_output_attachments() const;
  UInt32  max_fragment_dual_src_attachments() const;
  UInt32  max_fragment_combined_output_resources() const;
  UInt32  max_compute_shared_memory_size() const;
  Dim3U   max_compute_work_group_count() const;
  UInt32  max_compute_work_group_invocations() const;
  Dim3U   max_compute_work_group_size() const;
  UInt32  sub_pixel_precision_bits() const;
  UInt32  sub_texel_precision_bits() const;
  UInt32  mipmap_precision_bits() const;
  UInt32  max_draw_indexed_index_value() const;
  UInt32  max_draw_indirect_count() const;
  Float32 max_sampler_lod_bias() const;
  Float32 max_sampler_anisotropy() const;
  UInt32  max_viewports() const;
  Dim2U   max_viewport_dimensions() const;
  Dim2F   viewport_bounds_range() const;
  UInt32  viewport_sub_pixel_bits() const;
  UInt64  min_memory_map_alignment() const;
  UInt64  min_texel_buffer_offset_alignment() const;
  UInt64  min_uniform_buffer_offset_alignment() const;
  UInt64  min_storage_buffer_offset_alignment() const;
  Int32   min_texel_offset() const;
  UInt32  max_texel_offset() const;
  Int32   min_texel_gather_offset() const;
  UInt32  max_texel_gather_offset() const;
  Float32 min_interpolation_offset() const;
  Float32 max_interpolation_offset() const;
  UInt32  sub_pixel_interpolation_offset_bits() const;
  UInt32  max_framebuffer_width() const;
  UInt32  max_framebuffer_height() const;
  UInt32  max_framebuffer_layers() const;
  UInt32  framebuffer_color_sample_counts() const;
  UInt32  framebuffer_depth_sample_counts() const;
  UInt32  framebuffer_stencil_sample_counts() const;
  UInt32  framebuffer_no_attachments_sample_counts() const;
  UInt32  max_color_attachments() const;
  UInt32  sampled_image_color_sample_counts() const;
  UInt32  sampled_image_integer_sample_counts() const;
  UInt32  sampled_image_depth_sample_counts() const;
  UInt32  sampled_image_stencil_sample_counts() const;
  UInt32  storage_image_sample_counts() const;
  UInt32  max_sample_mask_words() const;
  Bool    timestamp_compute_and_graphics() const;
  Float32 timestamp_period() const;
  UInt32  max_clip_distances() const;
  UInt32  max_cull_distances() const;
  UInt32  max_combined_clip_and_cull_distances() const;
  UInt32  discrete_queue_priorities() const;
  Dim2F   point_size_range() const;
  Dim2F   line_width_range() const;
  Float32 point_size_granularity() const;
  Float32 line_width_granularity() const;
  Bool    strict_lines() const;
  Bool    standard_sample_locations() const;
  UInt64  optimal_buffer_copy_offset_alignment() const;
  UInt64  optimal_buffer_copy_row_pitch_alignment() const;
  UInt64  non_coherent_atom_size() const;

private:
  VkPhysicalDeviceProperties m_properties;
};

class PhysicalDeviceFeatures
{
public:
  PhysicalDeviceFeatures(VkPhysicalDevice device);

  Bool robust_buffer_access() const;
  Bool full_draw_index_uint32() const;
  Bool image_cube_array() const;
  Bool independent_blend() const;
  Bool geometry_shader() const;
  Bool tessellation_shader() const;
  Bool sample_rate_shading() const;
  Bool dual_src_blend() const;
  Bool logic_op() const;
  Bool multi_draw_indirect() const;
  Bool draw_indirect_first_instance() const;
  Bool depth_clamp() const;
  Bool depth_bias_clamp() const;
  Bool fill_mode_non_solid() const;
  Bool depth_bounds() const;
  Bool wide_lines() const;
  Bool large_points() const;
  Bool alpha_to_one() const;
  Bool multi_viewport() const;
  Bool sampler_anisotropy() const;
  Bool texture_compression_etc2() const;
  Bool texture_compression_astc_ldr() const;
  Bool texture_compression_bc() const;
  Bool occlusion_query_precise() const;
  Bool pipeline_statistics_query() const;
  Bool vertex_pipeline_stores_and_atomics() const;
  Bool fragment_stores_and_atomics() const;
  Bool shader_tessellation_and_geometry_point_size() const;
  Bool shader_image_gather_extended() const;
  Bool shader_storage_image_extended_formats() const;
  Bool shader_storage_image_multisample() const;
  Bool shader_storage_image_read_without_format() const;
  Bool shader_storage_image_write_without_format() const;
  Bool shader_uniform_buffer_array_dynamic_indexing() const;
  Bool shader_sampled_image_array_dynamic_indexing() const;
  Bool shader_storage_buffer_array_dynamic_indexing() const;
  Bool shader_storage_image_array_dynamic_indexing() const;
  Bool shader_clip_distance() const;
  Bool shader_cull_distance() const;
  Bool shader_float64() const;
  Bool shader_int64() const;
  Bool shader_int16() const;
  Bool shader_resource_residency() const;
  Bool shader_resource_min_lod() const;
  Bool sparse_binding() const;
  Bool sparse_residency_buffer() const;
  Bool sparse_residency_image_2d() const;
  Bool sparse_residency_image_3d() const;
  Bool sparse_residency_2_samples() const;
  Bool sparse_residency_4_samples() const;
  Bool sparse_residency_8_samples() const;
  Bool sparse_residency_16_samples() const;
  Bool sparse_residency_aliased() const;
  Bool variable_multisample_rate() const;
  Bool inherited_queries() const;

private:
  VkPhysicalDeviceFeatures m_features;
};

class PhysicalDeviceQueueFamily
{
public:
  friend class PhysicalDevice;

  UInt32 queue_count() const;
  Bool   graphics() const;
  Bool   compute() const;
  Bool   transfer() const;
  Bool   sparse_binding() const;
  Bool   protected_memory() const;
  UInt32 index() const;

private:
  PhysicalDeviceQueueFamily(UInt32 index, VkQueueFamilyProperties properties);

  UInt32                  m_index;
  VkQueueFamilyProperties m_properties;
};

class PhysicalDevice
{
public:
  friend class Instance;

  ~PhysicalDevice();

  VkPhysicalDevice handle() const;
  Instance&        instance();

  Version            api_version() const;
  Version            driver_version() const;
  UInt32             vendor_id() const;
  UInt32             device_id() const;
  PhysicalDeviceType type() const;
  String             name() const;

  PhysicalDeviceLimits&              limits();
  DArray<PhysicalDeviceQueueFamily>& queue_families();

private:
  PhysicalDevice(Instance& instance, VkPhysicalDevice physical_device);

  VkPhysicalDevice                  m_physical_device;
  VkPhysicalDeviceProperties        m_properties;
  Instance&                         m_instance;
  PhysicalDeviceLimits              m_limits;
  PhysicalDeviceFeatures            m_features;
  DArray<PhysicalDeviceQueueFamily> m_queue_families;
};

} // namespace setsugen::gfx::vulkan
