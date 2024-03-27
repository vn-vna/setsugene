#pragma once

#include <setsugen/pch.h>
#include <setsugen/format.h>
#include <setsugen/gfx.h>

namespace setsugen
{
class SceneManager;
class Scene;
class Entity;
class Component;
class Transform;
class MeshData;
class Mesh;
class Camera;
class PerspectiveCamera;
class OrthographicCamera;

template <typename T>
concept ComponentType = std::is_base_of_v<Component, T>;

class Scene final
{
public:
  Scene(const String& name);
  ~Scene() = default;

  const String& get_name() const;

  Void load();
  Void unload();

  Observer<Entity> add_entity(Observer<Entity> entity);
  Observer<Entity> get_entity(const String& name);
  Void             remove_entity(const String& name);
  Void             set_main_camera(Observer<Camera> camera);
  Observer<Camera> get_main_camera() const;
  Void             add_meshdata(const String& path);
  Void             remove_meshdata(const String& path);

  auto& get_entity_manager()
  {
    return m_entities;
  }

private:
  Observer<Camera>                        m_main_camera;
  UnorderedSet<String>                    m_meshdata_paths;
  String                                  m_name;
  UnorderedMap<String, SharedPtr<Entity>> m_entities;

  friend class Entity;
};

class SceneManager final
{
public:
  SceneManager();

private:
};

class Entity
{
public:
  using ComponentManager = UnorderedMap<Size, SharedPtr<Component>>;

  Entity(const String& name);
  ~Entity();

  const String& get_name() const;

  template <ComponentType T, typename... Args>
  Observer<T> add_component(Args... args)
  {
    const auto id   = typeid(T).hash_code();
    const auto iter = m_components.find(id);
    if (iter != m_components.end())
    {
      throw InvalidArgumentException("Component already exists");
    }

    auto tcomp     = new T(this, std::forward<Args>(args)...);
    auto component = dynamic_cast<Component*>(tcomp);
    m_components.emplace(id, SharedPtr<Component>{component});
    return tcomp;
  }

  template <ComponentType T>
  Observer<T> get_component()
  {
    const auto id   = typeid(T).hash_code();
    const auto iter = m_components.find(id);
    if (iter == m_components.end())
    {
      throw InvalidArgumentException("Component not found");
    }

    return dynamic_cast<T*>(iter->second.get());
  }

  template <ComponentType T>
  Void remove_component()
  {
    const auto id   = typeid(T).hash_code();
    const auto iter = m_components.find(id);
    if (iter == m_components.end())
    {
      throw InvalidArgumentException("Component not found");
    }

    m_components.erase(iter);
  }

  Observer<ComponentManager> get_components();
  Void                       add_child(Observer<Entity> entity);
  Observer<Entity>           get_child(const String& name);
  Void                       remove_child(const String& name);

protected:
  String                                   m_name;
  Observer<Scene>                          m_scene;
  Observer<Entity>                         m_parent;
  UnorderedMap<String, SharedPtr<Entity>>  m_children;
  UnorderedMap<Size, SharedPtr<Component>> m_components;

  friend class Scene;
};

class Component
{
public:
  Component(Observer<Entity> entity);
  virtual ~Component() = default;

  Observer<Entity>       get_entity();
  Observer<const Entity> get_entity() const;

protected:
  String           m_name;
  Observer<Entity> m_entity;
};

class Transform : virtual public Component
{
public:
  Transform(Observer<Entity> entity,
            const Vec3F&     position = Vec3F{},
            const Vec3F&     rotation = Vec3F{},
            const Vec3F&     scale    = Vec3F{});

  ~Transform() override = default;

  const Vec3F& get_position() const;
  const Vec3F& get_rotation() const;
  const Vec3F& get_scale() const;

protected:
  Vec3F m_position;
  Vec3F m_rotation;
  Vec3F m_scale;
};

class Mesh : virtual public Component
{
public:
  struct VertexData
  {
    Vec3F m_position;
    Vec3F m_color;
  };

  Mesh(Observer<Entity> entity, const String& file_path);
  ~Mesh() override = default;

private:
  Observer<MeshData> m_data;
};

class Camera : virtual public Component
{
public:
  Camera(Observer<Entity> entity,
         const Vec3F&     position  = Vec3F{},
         const Vec3F&     direction = Vec3F{});

private:
  Vec3F m_position;
  Vec3F m_direction;
};

class PerspectiveCamera : virtual public Camera
{
public:
  PerspectiveCamera(Observer<Entity> entity,
                    const Vec3F&     position   = Vec3F{},
                    const Vec3F&     direction  = Vec3F{},
                    Float            near_plane = 0.5f,
                    Float            far_plane  = 1000.0f,
                    Float            fov        = 75.0f);

private:
  Float m_near;
  Float m_far;
  Float m_fov;
};

class OrthographicCamera : virtual public Camera
{
public:
  OrthographicCamera(Observer<Entity> entity,
                     const Vec3F&     position   = Vec3F{},
                     const Vec3F&     direction  = Vec3F{},
                     const Vec2F&     horizontal = Vec2F{-10.0f, 10.0f},
                     const Vec2F&     vertical   = Vec2F{-10.0f, 10.0f},
                     const Vec2F&     depth      = Vec2F{1.0f, 1000.0f});
};

class Behavior : virtual public Component
{};

template <>
class Stringify<Scene>
{};

template <>
class Stringify<Entity>
{
public:
  using ValueType = Entity;

  static Void stringify(const FormatContext& context, Observer<const ValueType> value)
  {
    context.result
        << "[[Entity: "
        << value->get_name()
        << "] contains "
        << value->get_components().size()
        << " components]";
  }
};

template <ComponentType C>
class Stringify<C>
{
public:
  using ValueType = C;

  static Void stringify(const FormatContext& context, Observer<const ValueType> value)
  {
    context.result
        << "[[Component: "
        << get_component_name(typeid(C).name())
        << "] owned by [Entity: "
        << value->get_entity()->get_name()
        << "]]";
  }

  static const Char* get_component_name(const Char* name)
  {
    const Char* p = name;
    while (*name)
    {
      if (*name == ':')
      {
        p = name;
      }

      ++name;
    }

    return p + 1;
  }
};
}
