#pragma once

#include <setsugen/pch.h>
#include <setsugen/format.h>
#include <setsugen/gfx.h>

namespace setsugen
{
class Scene;
class Entity;
class Component;

template <typename T>
concept ComponentType = std::is_base_of_v<Component, T>;

class Scene final
{
public:
  Scene(const String& name);
  ~Scene() = default;

  const String& get_name() const;

  Void             render(const RenderContext& context);
  Observer<Entity> create_entity(const String& name);

private:
  String                                  m_name;
  UnorderedMap<String, SharedPtr<Entity>> m_entities;
};

class Entity
{
public:
  Entity(const String& name);
  ~Entity() = default;

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

  auto& get_components()
  {
    return m_components;
  }

  const auto& get_components() const
  {
    return m_components;
  }

protected:
  String                                   m_name;
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

  Void load();
  Void unload();

protected:
  DArray<VertexData> m_vertices;
  String             m_path;
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
