#pragma once

#include "gfx_fwd.inl"

namespace setsugen
{

class PresentTarget
{
public:
  virtual ~PresentTarget() = default;

  virtual Void present()      = 0;
  virtual Bool is_validated() = 0;
};

} // namespace setsugen
