#include <setsugen/application.h>
#include <setsugen/logger.h>
#include <setsugen/states.h>

namespace setsugen
{

ApplicationState::Destroy::Destroy(StateMachine& state_machine) : State(state_machine)
{
  m_logger = LoggerFactory::default_factory().get("Application::Destroy");
}

Void
ApplicationState::Destroy::enter()
{}

Void
ApplicationState::Destroy::update()
{
  auto& app = this->state_machine().context().app();

  app.m_main_loop->stop();
}

Void
ApplicationState::Destroy::exit()
{
  m_logger->info("Application Exiting Destroy State");
}

} // namespace setsugen
