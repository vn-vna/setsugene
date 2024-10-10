#include <setsugen/application.h>
#include <setsugen/logger.h>
#include <setsugen/states.h>
#include <setsugen/wm.h>

namespace setsugen
{

ApplicationState::Ready::Ready(StateMachine& state_machine) : State(state_machine)
{
  m_logger = LoggerFactory::default_factory().get("Application::Ready");
}

Void
ApplicationState::Ready::enter()
{}

Void
ApplicationState::Ready::update()
{
  auto& app = this->state_machine().context().app();
  app.main_window()->show();
  m_state_machine.set_next_state(std::make_unique<Resume>(m_state_machine));
}

Void
ApplicationState::Ready::exit()
{}

} // namespace setsugen
