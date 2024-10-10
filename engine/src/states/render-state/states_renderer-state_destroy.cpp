#include <setsugen/application.h>
#include <setsugen/context.h>
#include <setsugen/logger.h>
#include <setsugen/states.h>


namespace setsugen
{

RendererState::Destroy::Destroy(StateMachine& state_machine) : StateBase(state_machine)
{
  m_logger = LoggerFactory::default_factory().get("RendererState");
}

Void
RendererState::Destroy::enter()
{
  m_logger->info("Destroy");
}

Void
RendererState::Destroy::update()
{
  auto& context = m_state_machine.context();
  auto  app     = Application::current_app();
  app->render_loop()->stop();
}

Void
RendererState::Destroy::exit()
{}

} // namespace setsugen
