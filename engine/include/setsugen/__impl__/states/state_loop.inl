#pragma once

#include "state_fwd.inl"

namespace setsugen
{

template<typename M>
class StateLoop
{
public:
  using Context = typename M::Context;

  StateLoop(M& machine);
  StateLoop(const StateLoop& other);
  StateLoop(StateLoop&& other) noexcept;

  virtual Void run();
  virtual Void stop();

private:
  Context& m_context;
  M&       m_machine;
  Bool     m_running;
};

} // namespace setsugen
