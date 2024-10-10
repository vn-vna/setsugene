#include <setsugen/application.h>
#include <setsugen/logger.h>
#include <setsugen/states.h>

namespace setsugen
{

ApplicationState::Stop::Stop(StateMachine& state_machine) : State(state_machine)
{
  m_logger = LoggerFactory::default_factory().get("Application::Stop");
}

Void
ApplicationState::Stop::enter()
{}

Void
ApplicationState::Stop::update()
{
  auto& app = this->state_machine().context().app();
  app.m_renderer_thread->join();
  state_machine().set_next_state(std::make_unique<Destroy>(state_machine()));
}

Void
ApplicationState::Stop::exit()
{}

} // namespace setsugen
