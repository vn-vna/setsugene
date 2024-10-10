#include <setsugen/application.h>
#include <setsugen/logger.h>
#include <setsugen/states.h>
#include <setsugen/context.h>

namespace setsugen
{

ApplicationState::FrameBegin::FrameBegin(StateMachine& state_machine) : State(state_machine)
{
  m_logger = LoggerFactory::default_factory().get("Application::FrameBegin");
}

Void
ApplicationState::FrameBegin::enter()
{}

Void
ApplicationState::FrameBegin::update()
{
  auto& app = this->state_machine().context().app();
  m_logger->info("FrameBegin");
  app.renderer_context()->signal_begin_frame();
  m_state_machine.set_next_state(std::make_unique<WaitRenderer>(m_state_machine));
}

Void
ApplicationState::FrameBegin::exit()
{}

} // namespace setsugen
