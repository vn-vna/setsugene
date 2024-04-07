#include <setsugen/entity.h>
#include <setsugen/scene.h>
#include <setsugen/mesh.h>

#include <utility>

namespace setsugen
{
Scene::Scene(const std::string& name) : m_main_camera(nullptr), m_name{name}
{}

Scene::Scene(const Scene& other) : m_main_camera{other.m_main_camera}, m_name{other.m_name}
{}

Scene::Scene(Scene&& other) noexcept
    : m_main_camera{std::exchange(other.m_main_camera, nullptr)}, m_name{std::move(other.m_name)}
{}

const std::string&
Scene::get_name() const
{
  return m_name;
}

void
Scene::load()
{
  std::vector<std::future<void>> futures;
  for (auto& [path, meshdata]: m_meshdata)
  {
    futures.emplace_back(std::async(std::launch::async, [&meshdata] { meshdata->load(); }));
  }

  for (auto& future: futures)
  {
    future.wait();
  }
}

void
Scene::unload()
{
  for (auto& [path, meshdata]: m_meshdata)
  {
    meshdata->unload();
  }
}

std::vector<Entity*>
Scene::find_entities(const std::string& name) const
{
  std::vector<Entity*> entities;
  for (const auto& [id, entity]: m_entities)
  {
    if (entity->get_name() == name)
    {
      entities.emplace_back(entity.get());
    }
  }
  return entities;
}

std::vector<Entity*>
Scene::find_root_entities(const std::string& name) const
{
  std::vector<Entity*> entities;
  for (const auto& entity: m_root_entities)
  {
    if (entity->get_name() == name)
    {
      entities.emplace_back(entity);
    }
  }
  return entities;
}

void
Scene::remove_entity(Entity* entity)
{
  const auto eid = Entity::id_of(entity);
  if (const auto it = m_entities.find(eid); it != m_entities.end())
  {
    if (entity->m_parent != nullptr)
    {
      entity->m_parent->remove_child(entity);
    }
  }
}

void
Scene::set_main_camera(Camera* camera)
{
  m_main_camera = camera;
}

Camera*
Scene::get_main_camera() const
{
  return m_main_camera;
}

void
Scene::add_meshdata(const std::string& path)
{
  if (m_meshdata.find(path) != m_meshdata.end())
  {
    return;
  }

  m_meshdata[path] = std::make_unique<MeshData>(path);
}

void
Scene::remove_meshdata(const std::string& path)
{
  m_meshdata.erase(path);
}

MeshData*
Scene::get_meshdata(const std::string& path) const
{
  return m_meshdata.at(path).get();
}

size_t
Scene::get_entity_count() const
{
  return m_entities.size();
}

Entity*
Scene::create_entity(const std::string& name, Entity* parent)
{
  auto entity                    = std::make_unique<Entity>(name, this);
  auto ptr                       = entity.get();
  m_entities[Entity::id_of(ptr)] = std::move(entity);

  if (parent)
  {
    parent->add_child(ptr);
  }
  else
  {
    m_root_entities.emplace(ptr);
  }

  return ptr;
}

} // namespace setsugen
