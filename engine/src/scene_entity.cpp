#include <setsugen/scene.h>

namespace setsugen
{
Entity::Entity(const String& name)
  : m_name{name},
    m_scene{nullptr},
    m_parent{nullptr}
{
  if (m_parent)
  {
    m_parent->m_children.emplace(name, this);
  }
}

const String&
Entity::get_name() const
{
  return m_name;
}

Observer<Entity::ComponentManager>
Entity::get_components()
{
  return &m_components;
}

Void
Entity::add_child(Observer<Entity> entity)
{
  entity->m_parent = this;
  m_children.emplace(entity->get_name(), entity);
}
}
