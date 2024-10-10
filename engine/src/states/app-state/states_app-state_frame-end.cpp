#include <setsugen/states.h>
#include <setsugen/logger.h>
#include <setsugen/application.h>

namespace setsugen
{

ApplicationState::FrameEnd::FrameEnd(StateMachine& state_machine) : State(state_machine)
{
  m_logger  = LoggerFactory::default_factory().get("Application::FrameEnd");
}

Void
ApplicationState::FrameEnd::enter()
{}

Void
ApplicationState::FrameEnd::update()
{
  m_state_machine.set_next_state(std::make_unique<SignalHandle>(m_state_machine));
}

Void
ApplicationState::FrameEnd::exit()
{}

} // namespace setsugen
