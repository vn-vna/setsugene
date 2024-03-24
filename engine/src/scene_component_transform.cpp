#include <setsugen/scene.h>

namespace setsugen
{
Transform::Transform(Observer<Entity> entity, const Vec3F& position, const Vec3F& rotation, const Vec3F& scale)
  : Component{entity},
    m_position{position},
    m_rotation{rotation},
    m_scale{scale}
{}

const Vec3F&
Transform::get_position() const
{
  return m_position;
}

const Vec3F&
Transform::get_rotation() const
{
  return m_rotation;
}

const Vec3F&
Transform::get_scale() const
{
  return m_scale;
}
}
