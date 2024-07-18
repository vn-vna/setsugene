#include <setsugen/entity.h>
#include <setsugen/mesh.h>
#include <setsugen/scene.h>

namespace setsugen
{

SceneManager::SceneManager() : m_current_scene{nullptr}
{}

SceneManager::~SceneManager() = default;

Scene*
SceneManager::create_scene(const std::string& name)
{
  auto scene     = new Scene(name);
  m_scenes[name] = std::unique_ptr<Scene>(scene);
  return scene;
}

Scene*
SceneManager::get_scene(const std::string& name) const
{
  if (auto it = m_scenes.find(name); it != m_scenes.end())
  {
    return it->second.get();
  }
  return nullptr;
}

Scene*
SceneManager::get_current_scene() const
{
  return m_current_scene;
}

void
SceneManager::set_current_scene(Scene* scene)
{
  if (!scene)
  {
    return;
  }

  if (m_current_scene == scene)
  {
    return;
  }

  if (m_current_scene)
  {
    m_current_scene->unload();
  }

  auto it = m_scenes.find(scene->get_name());
  if (it != m_scenes.end() && it->second.get() == scene)
  {
    m_current_scene = scene;
  }
  else
  {
    throw EngineException("Scene not found in the scene manager");
  }

  m_current_scene->load();
}


} // namespace setsugen
