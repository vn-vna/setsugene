#include <setsugen/camera.h>

namespace setsugen
{

Camera::Camera(Entity* entity, const Vec3F& position, const Vec3F& direction, const Vec3F& up)
    : Component{entity}, m_position{position}, m_center{direction}, m_up{up}
{}

Vec3F
Camera::get_position() const
{
  return m_position;
}

Vec3F
Camera::get_direction() const
{
  return m_center;
}

void
Camera::set_position(const Vec3F& position)
{
  m_position = position;
}

void
Camera::set_center(const Vec3F& center)
{
  m_center = center;
}

Mat4x4F
Camera::get_view_matrix() const
{
  return Mat4x4F::look_at(m_position, m_center, m_up);
}

const char*
Camera::get_type()
{
  return "Camera";
}

} // namespace setsugen
