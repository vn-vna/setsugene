#pragma once

#include "state_interface.inl"

namespace setsugen
{

template<typename Context>
StateBase<Context>::StateBase(StateMachine& state_machine) : m_state_machine(state_machine)
{}

template<typename Context>
StateMachine<Context>&
StateBase<Context>::state_machine()
{
  return m_state_machine;
}

} // namespace setsugen
