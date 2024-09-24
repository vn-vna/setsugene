#pragma once

#include "state_fwd.inl"

namespace setsugen
{

class StateMachine
{
public:
  void update();
  void set_state(std::unique_ptr<State> state);

private:
  std::unique_ptr<State>                m_current_state;
  std::optional<std::unique_ptr<State>> m_next_state;
};

} // namespace setsugen
