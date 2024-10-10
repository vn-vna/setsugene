#include <setsugen/application.h>
#include <setsugen/logger.h>
#include <setsugen/states.h>

namespace setsugen
{

ApplicationState::Resume::Resume(StateMachine& state_machine) : State(state_machine)
{
  m_logger = LoggerFactory::default_factory().get("Application::Resume");
}

Void
ApplicationState::Resume::enter()
{}

Void
ApplicationState::Resume::update()
{
  m_state_machine.set_next_state(std::make_unique<FrameBegin>(m_state_machine));
}

Void
ApplicationState::Resume::exit()
{}

} // namespace setsugen
