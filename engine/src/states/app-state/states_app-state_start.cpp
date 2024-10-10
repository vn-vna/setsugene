#include <setsugen/application.h>
#include <setsugen/context.h>
#include <setsugen/logger.h>
#include <setsugen/states.h>
#include <setsugen/wm.h>

namespace setsugen
{

ApplicationState::Start::Start(StateMachine& state_machine) : State(state_machine)
{
  m_logger = LoggerFactory::default_factory().get("Application::Start");
}

Void
ApplicationState::Start::enter()
{}

Void
ApplicationState::Start::update()
{
  auto& app = this->state_machine().context().app();
  app.m_renderer_thread = std::make_unique<Thread>(
      []()
      {
        auto app = Application::current_app();
        app->render_loop()->run();
      });
  
  m_logger->info("Waiting for renderer to be ready");
  app.renderer_context()->wait_renderer_ready();
  m_logger->info("Renderer is ready");

  m_state_machine.set_next_state(std::make_unique<Ready>(m_state_machine));
}

Void
ApplicationState::Start::exit()
{}

} // namespace setsugen
