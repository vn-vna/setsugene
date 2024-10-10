#pragma once

#include "state_fwd.inl"

namespace setsugen
{

template<typename Context>
class StateBase
{
public:
  using StateMachine = StateMachine<Context>;

  StateBase(StateMachine& state_machine);

  virtual Void enter() = 0;
  virtual Void update() = 0;
  virtual Void exit() = 0;

  StateMachine& state_machine();

protected:
  StateMachine& m_state_machine;
};

}
