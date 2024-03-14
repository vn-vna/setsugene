#pragma once

#include <setsugen/pch.h>
#include <setsugen/format.h>

namespace setsugen
{
class Entity;

class Scene : virtual public Formattable,
              EnableSelfShared<Scene>
{
public:
  Scene();
  ~Scene();

private:
  Map<String, SharedPtr<Entity>> m_entities;
};
}
