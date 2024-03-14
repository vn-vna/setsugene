#pragma once

#include <setsugen/pch.h>
#include <setsugen/format.h>
#include <setsugen/component.h>

namespace setsugen
{
class Entity;

class Entity : virtual public Formattable,
               virtual public EnableShared<Entity>
{
public:
  Entity();
  virtual ~Entity();

public:
  template <typename T, typename... CArgs>
  std::enable_if_t<std::is_base_of_v<Component, T>, Void> add_component(CArgs... args)
  {
    m_components[typeid(T)] = std::dynamic_pointer_cast<Component>(
      std::make_shared<T>(shared_from_this(), std::forward<CArgs>(args)...)
    );
  }

  template <typename T>
  std::enable_if_t<std::is_base_of_v<Component, T>, Void> remove_component()
  {
    String type_name = typeid(T).name();
    m_components.erase(typeid(T));
  }

  template <typename T>
  std::enable_if_t<std::is_base_of_v<Component, T>, WeakPtr<T>> get_component()
  {
    if (auto it = m_components.find(typeid(T)); it != m_components.end())
    {
      return std::dynamic_pointer_cast<T>(it->second);
    }
    return nullptr;
  }

private:
  UnorderedMap<TypeInfo, SharedPtr<Component>> m_components;
  UnorderedMap<String, SharedPtr<Entity>>      m_children;
};
} // namespace setsugen
