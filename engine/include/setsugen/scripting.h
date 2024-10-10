#pragma once

#include <setsugen/component.h>

namespace setsugen
{

class Behavior : public Component
{
public:
   Behavior(Entity* entity);
  ~Behavior() override;

  virtual Void update() = 0;
};

} // namespace setsugen
