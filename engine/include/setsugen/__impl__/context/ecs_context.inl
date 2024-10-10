#pragma once

#include "context_fwd.inl"

namespace setsugen
{

class ECSContext
{
public:
  ECSContext();
  ~ECSContext();

  Bool alive() const;

private:
  Bool m_alive;
};

} // namespace setsugen
