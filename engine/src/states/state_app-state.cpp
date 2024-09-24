#include <setsugen/states.h>

namespace setsugen
{

ApplicationState::ApplicationState()
{
  set_state(std::make_unique<Initialize>(*this));
}

ApplicationState::Initialize::Initialize(StateMachine& state_machine) : State(state_machine) {}

void
ApplicationState::Initialize::update()
{
  m_state_machine.set_state(std::make_unique<Start>(m_state_machine));
}

}
