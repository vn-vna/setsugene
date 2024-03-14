#pragma once

#include <setsugen/pch.h>
#include <setsugen/format.h>

namespace setsugen
{
class Entity;
class Component;

class Component
    : virtual public Formattable,
      virtual EnableShared<Component>
{
public:
  Component(WeakPtr<Entity> entity);
  virtual ~Component() = default;

public:
  inline WeakPtr<Entity> get_entity() const
  {
    return m_entity;
  }

protected:
  WeakPtr<Entity> m_entity;
};

// class Camera : virtual public Component
// {};
//
// class Light : virtual public Component
// {};
//
// class Mesh : virtual public Component
// {};
//
// class Transform : virtual public Component
// {};
//
// class Behavior : virtual public Component
// {};
//
// class Shader : virtual public Component
// {};
//
// class Material : virtual public Component
// {};
}
