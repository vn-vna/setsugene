#include <setsugen/gfx.h>
#include <setsugen/logger.h>
#include <setsugen/wm.h>

#include <volk.h>

namespace setsugen::gfx::vulkan
{

class Instance;

class Surface
{
public:
  class Builder;

  friend class Builder;

  ~Surface();

  VkSurfaceKHR handle() const noexcept;

private:
  Surface(VkSurfaceKHR surface, Instance& instance, Window& window);

  Instance& m_instance;
  Window&   m_window;

  VkSurfaceKHR m_surface;
};


class Surface::Builder
{
public:
  Builder(Instance& instance, Window& window);

  Owner<Surface> build();

private:
  Instance& m_instance;
  Window&   m_window;
};

} // namespace setsugen::gfx::vulkan
