#include <setsugen/component.h>

namespace setsugen
{

Component::Component(Entity* entity) : m_entity{entity}
{}

Entity*
Component::get_entity()
{
  return m_entity;
}

const Entity*
Component::get_entity() const
{
  return m_entity;
}
} // namespace setsugen
