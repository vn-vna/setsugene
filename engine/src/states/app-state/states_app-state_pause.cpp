#include <setsugen/states.h>
#include <setsugen/application.h>
#include <setsugen/wm.h>

namespace setsugen
{

ApplicationState::Pause::Pause(StateMachine& state_machine) : State(state_machine)
{}

Void
ApplicationState::Pause::enter()
{}

Void
ApplicationState::Pause::update()
{
  auto& app = this->state_machine().context().app();
  auto wm  = app.window_manager();

  m_state_machine.set_next_state(std::make_unique<Resume>(m_state_machine));
}

Void
ApplicationState::Pause::exit()
{}

} // namespace setsugen
