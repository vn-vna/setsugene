#pragma once

#include "state_loop.inl"

namespace setsugen
{

template<typename M>
StateLoop<M>::StateLoop(M& machine) : m_context(machine.context()), m_machine(machine)
{}

template<typename M>
StateLoop<M>::StateLoop(const StateLoop& other) : m_context(other.m_context), m_machine(other.m_context)
{}

template<typename M>
StateLoop<M>::StateLoop(StateLoop&& other) noexcept : m_context(other.m_context), m_machine(std::move(other.m_machine))
{}

template<typename M>
Void
StateLoop<M>::run()
{
  m_running = true;
  while (m_context.alive() && m_running)
  {
    m_machine.update();
  }
}

template<typename M>
Void
StateLoop<M>::stop()
{
  m_running = false;
}

} // namespace setsugen
