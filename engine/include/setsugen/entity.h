#pragma once

#include <setsugen/component.h>
#include <setsugen/exception.h>
#include <setsugen/pch.h>
#include <setsugen/scene.h>

namespace setsugen
{

class Scene;

class Entity
{
public:
  using ComponentManager = UnorderedMap<size_t, Owner<Component>>;
  using ChildrenMap      = UnorderedMap<size_t, Entity*>;

           Entity(const String& name, Scene* scene = nullptr);
  virtual ~Entity();

  const String& get_name() const;
  Scene*             get_scene() const;

  template<ComponentType T, typename... Args>
  T* add_component(Args&&... args)
  {
    const auto id   = typeid(T).hash_code();
    const auto iter = m_components.find(id);
    if (iter != m_components.end())
    {
      throw InvalidArgumentException("Component already exists");
    }

    auto tcomp       = new T(this, std::forward<Args>(args)...);
    auto component   = dynamic_cast<Component*>(tcomp);
    m_components[id] = Owner<Component>(component);
    return tcomp;
  }

  template<ComponentType T>
  T* get_component()
  {
    const auto id   = typeid(T).hash_code();
    const auto iter = m_components.find(id);
    if (iter == m_components.end())
    {
      throw InvalidArgumentException("Component not found");
    }

    return dynamic_cast<T*>(iter->second.get());
  }

  template<ComponentType T>
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

  ComponentManager*    get_components();
  Void                 add_child(Entity* entity);
  DArray<Entity*> find_children(const String& name);
  Void                 remove_child(Entity* entity);

  static size_t id_of(Entity* entity);

protected:
  String      m_name;
  Scene*           m_scene;
  Entity*          m_parent;
  ChildrenMap      m_children;
  ComponentManager m_components;

  friend class Scene;
  Void update();
};

template<>
class Stringify<Entity>
{
public:
  using ValueType = Entity;

  static Void stringify(const FormatContext& context, const ValueType& value)
  {
    context.result << "[[Entity: name = " << value.get_name()
                   << "] owned by [Scene: name = " << value.get_scene()->get_name() << "]]";
  }
};

} // namespace setsugen
