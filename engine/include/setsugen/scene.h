#pragma once

#include <setsugen/pch.h>

#include <setsugen/executor.h>
#include <setsugen/format.h>
#include <setsugen/logger.h>

#include <memory>


namespace setsugen
{
class SceneManager;
class MeshManager;
class Scene;
class Entity;
class Component;
class Camera;
class MeshData;

class Scene final
{
public:
  explicit Scene(const std::string& name);

  Scene(const Scene&) = delete;

  Scene(Scene&&) noexcept;

  ~Scene() noexcept;

  const std::string& get_name() const;

  void load();
  void unload();

  /**
   * Collects all entities with the given name.
   * @param name the name of the entities to find
   * @return A dynamic array of observers to the entities
   */
  std::vector<Entity*> find_entities(const std::string& name) const;

  /**
   * Collects all root entities with the given name.
   * @param name the name of the entities to find
   * @return A dynamic array of observers to the entities
   */
  std::vector<Entity*> find_root_entities(const std::string& name) const;

  /**
   * Removes the given entity from the scene.
   * @param entity the entity to be removed
   */
  void remove_entity(Entity* entity);

  /**
   * Sets the main camera of the scene.
   * @param camera the camera component to set as the main camera
   */
  void set_main_camera(Camera* camera);

  /**
   * Gets the main camera of the scene.
   * @return an observer to the main camera
   */
  Camera* get_main_camera() const;

  /**
   * Add mesh data to the scene.
   * (Why is this here? Because the scene is the owner of the mesh data. It's a design choice.)
   * @param path
   */
  void add_meshdata(const std::string& path);

  /**
   * Remove mesh data from the scene.
   * @param path
   */
  void remove_meshdata(const std::string& path);

  /**
   * Get mesh data from the scene.
   * @param path mesh path
   * @return an observer to the mesh data
   */
  MeshData* get_meshdata(const std::string& path) const;

  /**
   * Get all mesh data in the scene.
   * @return a dynamic array of observers to the mesh data
   */
  std::vector<MeshData*> get_all_meshdata() const;

  /**
   * Get the number of entities in the scene.
   * @return entity count
   */
  size_t get_entity_count() const;

  /**
   * Create a new entity that belongs to the scene.
   * @param name the name of the entity
   * @return an observer to the entity
   */
  Entity* create_entity(const std::string& name, Entity* parent = nullptr);

  /**
   * Get all entities in the scene.
   * @return a dynamic array of observers to the entities
   */
  std::vector<Entity*> get_entities() const;

  /** Check if the scene is loaded. */
  bool is_loaded() const;

  /** Update the scene. */
  void update();

private:
  Camera*                                                    m_main_camera;
  std::string                                                m_name;
  std::unordered_map<size_t, std::unique_ptr<Entity>>        m_entities;
  std::unordered_set<Entity*>                                m_root_entities;
  std::unordered_map<std::string, std::unique_ptr<MeshData>> m_meshdata;
  std::unique_ptr<Executor<FixedThreadPoolExecutor>>         m_executor;
  std::shared_ptr<Logger>                                    m_logger;
  std::atomic<bool>                                          m_loaded;

  friend class Entity;
};

class SceneManager final
{
public:
  using SceneMapping = std::unordered_map<std::string, std::unique_ptr<Scene>>;

  SceneManager();
  ~SceneManager();

  Scene* create_scene(const std::string& name);
  Scene* get_scene(const std::string& name) const;

  Scene* get_current_scene() const;
  void   set_current_scene(Scene* scene);

private:
  Scene*       m_current_scene;
  SceneMapping m_scenes;
};

template<>
class Stringify<Scene>
{
  static void stringify(const FormatContext& context, const Scene& value)
  {
    context.result << "[[Scene: name = " << value.get_name() << "]]";
  }
};
} // namespace setsugen
