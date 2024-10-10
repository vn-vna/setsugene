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
  explicit Scene(const String& name);

  Scene(const Scene&) = delete;

  Scene(Scene&&) noexcept;

  ~Scene() noexcept;

  const String& get_name() const;

  Void load();
  Void unload();

  /**
   * Collects all entities with the given name.
   * @param name the name of the entities to find
   * @return A dynamic array of observers to the entities
   */
  DArray<Entity*> find_entities(const String& name) const;

  /**
   * Collects all root entities with the given name.
   * @param name the name of the entities to find
   * @return A dynamic array of observers to the entities
   */
  DArray<Entity*> find_root_entities(const String& name) const;

  /**
   * Removes the given entity from the scene.
   * @param entity the entity to be removed
   */
  Void remove_entity(Entity* entity);

  /**
   * Sets the main camera of the scene.
   * @param camera the camera component to set as the main camera
   */
  Void set_main_camera(Camera* camera);

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
  Void add_meshdata(const String& path);

  /**
   * Remove mesh data from the scene.
   * @param path
   */
  Void remove_meshdata(const String& path);

  /**
   * Get mesh data from the scene.
   * @param path mesh path
   * @return an observer to the mesh data
   */
  MeshData* get_meshdata(const String& path) const;

  /**
   * Get all mesh data in the scene.
   * @return a dynamic array of observers to the mesh data
   */
  DArray<MeshData*> get_all_meshdata() const;

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
  Entity* create_entity(const String& name, Entity* parent = nullptr);

  /**
   * Get all entities in the scene.
   * @return a dynamic array of observers to the entities
   */
  DArray<Entity*> get_entities() const;

  /** Check if the scene is loaded. */
  Bool is_loaded() const;

  /** Update the scene. */
  Void update();

private:
  Camera*                                                    m_main_camera;
  String                                                m_name;
  UnorderedMap<size_t, Owner<Entity>>        m_entities;
  std::unordered_set<Entity*>                                m_root_entities;
  UnorderedMap<String, Owner<MeshData>> m_meshdata;
  Owner<Executor<FixedThreadPoolExecutor>>         m_executor;
  Shared<Logger>                                    m_logger;
  std::atomic<Bool>                                          m_loaded;

  friend class Entity;
};

class SceneManager final
{
public:
  using SceneMapping = UnorderedMap<String, Owner<Scene>>;

   SceneManager();
  ~SceneManager();

  Scene* create_scene(const String& name);
  Scene* get_scene(const String& name) const;

  Scene* get_current_scene() const;
  Void   set_current_scene(Scene* scene);

private:
  Scene*       m_current_scene;
  SceneMapping m_scenes;
};

template<>
class Stringify<Scene>
{
  static Void stringify(const FormatContext& context, const Scene& value)
  {
    context.result << "[[Scene: name = " << value.get_name() << "]]";
  }
};
} // namespace setsugen
