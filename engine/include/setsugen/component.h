#pragma once

#include <setsugen/format.h>
#include <setsugen/pch.h>

namespace setsugen
{
class Entity;

class  Component
{
public:
  Component(Entity* entity);
  virtual ~Component() = default;

  Entity*       get_entity();
  const Entity* get_entity() const;

  virtual const char* get_type() = 0;

protected:
  Entity* m_entity;
};

template<typename T>
concept ComponentType = std::is_base_of_v<Component, T>;

template<ComponentType C>
class Stringify<C>
{
public:
  static void stringify(const FormatContext& context, const C& value)
  {
    context.result << "[[Component: type = " << value.get_type()
                   << "] owned by [Entity: name = " << value.get_entity()->get_name() << "]]";
  }
};
} // namespace setsugen
