#include <setsugen/scene.h>

namespace setsugen
{
Entity::Entity(const String& name)
  : m_name{name}
{}

const String&
Entity::get_name() const
{
  return m_name;
}
}
