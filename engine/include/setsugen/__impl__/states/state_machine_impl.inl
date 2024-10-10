#pragma once

#include "state_machine.inl"

namespace setsugen
{

template<typename Context>
StateMachine<Context>::StateMachine(Context& ctx, Owner<State>&& initial_state)
    : m_current_state(nullptr), m_next_state(std::move(initial_state)), m_context(ctx)
{}

template<typename Context>
Void
StateMachine<Context>::set_state(Owner<State>&& state)
{
  m_next_state = std::move(state);
}

template<typename Context>
Void
StateMachine<Context>::set_next_state(Owner<State>&& state)
{
  m_next_state = std::move(state);
}

template<typename Context>
Void
StateMachine<Context>::update()
{
  if (m_current_state)
  {
    m_current_state->update();
  }

  if (m_next_state)
  {
    if (m_current_state)
    {
      m_current_state->exit();
    }

    m_current_state = std::move(m_next_state);
    m_next_state    = nullptr;

    m_current_state->enter();
  }
}

template<typename Context>
Context&
StateMachine<Context>::context()
{
  return m_context;
}

} // namespace setsugen
