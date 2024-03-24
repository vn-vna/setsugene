#include <setsugen/scene.h>

namespace setsugen
{
Component::Component(Observer<Entity> entity)
  : m_entity{entity}
{}

Observer<Entity>
Component::get_entity()
{
  return m_entity;
}

Observer<const Entity>
Component::get_entity() const
{
  return m_entity;
}
}
