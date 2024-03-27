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

Observer<Entity>
Scene::add_entity(Observer<Entity> entity)
{
  if (!entity)
  {
    return nullptr;
  }

  m_entities.emplace(entity->get_name(), std::move(SharedPtr<Entity>{entity}));
  return entity;
}

Observer<Entity>
Scene::get_entity(const String& name)
{
  const auto it = m_entities.find(name);
  if (it == m_entities.end())
  {
    return nullptr;
  }

  return it->second.get();
}

Void
Scene::remove_entity(const String& name)
{
  const auto it = m_entities.find(name);
  if (it == m_entities.end())
  {
    return;
  }

  m_entities.erase(it);
}

Void
Scene::set_main_camera(Observer<Camera> camera)
{
  m_main_camera = camera;
}

Observer<Camera>
Scene::get_main_camera() const
{
  return m_main_camera;
}

Void
Scene::add_meshdata(const String& path)
{
  m_meshdata_paths.emplace(path);
}

Void
Scene::remove_meshdata(const String& path)
{
  m_meshdata_paths.erase(path);
}
}
