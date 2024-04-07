#include <setsugen/camera.h>

namespace setsugen
{

Camera::Camera(Entity* entity, const Vec3F& position, const Vec3F& direction)
    : Component{entity}, m_position{position}, m_direction{direction}
{}

Vec3F
Camera::get_position() const
{
  return m_position;
}

Vec3F
Camera::get_direction() const
{
  return m_direction;
}

void
Camera::set_position(const Vec3F& position)
{
  m_position = position;
}

void
Camera::set_direction(const Vec3F& direction)
{
  m_direction = direction;
}

Mat4x4F
Camera::get_view_matrix() const
{
  return Mat4x4F::look_at(m_position, m_direction, Vec3F{0.0f, 1.0f, 0.0f});
}

const char*
Camera::get_type()
{
  return "Camera";
}

} // namespace setsugen
