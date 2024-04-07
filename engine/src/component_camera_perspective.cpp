#include <setsugen/camera.h>

namespace setsugen
{

PerspectiveCamera::PerspectiveCamera(Entity* entity, const Vec3F& position, const Vec3F& direction, float near_plane,
                                     float far_plane, float fov)
    : Camera{entity, position, direction}, m_near{near_plane}, m_far{far_plane}, m_fov{fov}
{}

float
PerspectiveCamera::get_near_plane() const
{
  return m_near;
}

float
PerspectiveCamera::get_far_plane() const
{
  return m_far;
}

float
PerspectiveCamera::get_fov() const
{
  return m_fov;
}
Mat4x4F
PerspectiveCamera::get_projection_matrix(float aspect) const
{
  return Mat4x4F::perspective(m_fov, aspect, m_near, m_far);
}

void
PerspectiveCamera::set_near_plane(float near_plane)
{
  m_near = near_plane;
}

void
PerspectiveCamera::set_far_plane(float far_plane)
{
  m_far = far_plane;
}

void
PerspectiveCamera::set_fov(float fov)
{
  m_fov = fov;
}


} // namespace setsugen
