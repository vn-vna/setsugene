#pragma once

#include "state_fwd.inl"

namespace setsugen
{

template<typename Ctx>
class StateMachine
{
public:
  using Context = Ctx;
  using State   = StateBase<Context>;

  StateMachine(Context& ctx, Owner<State>&& initial_state);

  Void update();
  Void set_state(Owner<State>&& state);
  Void set_next_state(Owner<State>&& state);

  Context& context();

private:
  Owner<State> m_current_state;
  Owner<State> m_next_state;

  Context& m_context;
};

} // namespace setsugen
