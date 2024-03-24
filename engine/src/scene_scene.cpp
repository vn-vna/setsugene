#include <setsugen/scene.h>

namespace setsugen
{
Scene::Scene(const String& name)
  : m_name{name}
{}

const String&
Scene::get_name() const
{
  return m_name;
}

Void
Scene::render(const RenderContext& context)
{}

Observer<Entity>
Scene::create_entity(const String& name)
{
  auto entity = new Entity(name);
  m_entities.emplace(name, std::move(SharedPtr<Entity>{entity}));
  return entity;
}
}
