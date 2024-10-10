#include <setsugen/states.h>
#include <setsugen/application.h>
#include <setsugen/wm.h>

namespace setsugen
{

RendererState::SignalHandle::SignalHandle(StateMachine& state_machine) : StateBase(state_machine)
{
  m_logger = LoggerFactory::default_factory().get("RendererState");
}

Void
RendererState::SignalHandle::enter()
{
  m_logger->info("SignalHandle");
}

Void
RendererState::SignalHandle::update()
{
  auto& context = m_state_machine.context();
  auto app = Application::current_app();

  if (app->main_window()->is_closing())
  {
    m_state_machine.set_next_state(std::make_unique<Stop>(m_state_machine));
    return;
  }

  m_state_machine.set_next_state(std::make_unique<WaitFrameBegin>(m_state_machine));
}

Void
RendererState::SignalHandle::exit()
{}

} // namespace setsugen
