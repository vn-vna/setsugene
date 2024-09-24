#pragma once

#include "state_fwd.inl"

namespace setsugen
{

class State
{
public:
  State(StateMachine& state_machine);

  virtual void update() = 0;

protected:
  StateMachine& m_state_machine;
};

}
