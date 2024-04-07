#include <setsugen/entity.h>

namespace setsugen
{
Entity::Entity(const std::string& name, Scene* m_scene) : m_name{name}, m_scene{m_scene}, m_parent{nullptr}
{
  if (m_parent)
  {
    m_parent->m_children.emplace(id_of(this), this);
  }
}

Entity::~Entity() = default;

const std::string&
Entity::get_name() const
{
  return m_name;
}

Scene*
Entity::get_scene() const
{
  return m_scene;
}

Entity::ComponentManager*
Entity::get_components()
{
  return &m_components;
}

void
Entity::add_child(Entity* entity)
{
  entity->m_parent = this;
  m_children.emplace(id_of(entity), entity);
}

std::vector<Entity*>
Entity::find_children(const std::string& name)
{
  std::vector<Entity*> entities;
  for (const auto& [id, entity]: m_children)
  {
    if (entity->get_name() == name)
    {
      entities.emplace_back(entity);
    }
  }
  return entities;
}

void
Entity::remove_child(Entity* entity)
{
  if (auto it = m_children.find(id_of(entity)); it != m_children.end())
  {
    m_children.erase(it);
  }
}

size_t
Entity::id_of(Entity* entity)
{
  return std::hash<Entity*>()(entity);
}
} // namespace setsugen
