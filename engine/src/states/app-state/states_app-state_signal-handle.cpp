#include <setsugen/application.h>
#include <setsugen/logger.h>
#include <setsugen/states.h>
#include <setsugen/wm.h>

namespace setsugen
{

ApplicationState::SignalHandle::SignalHandle(StateMachine& state_machine) : State(state_machine)
{
  m_logger = LoggerFactory::default_factory().get("Application::SignalHandle");
}

Void
ApplicationState::SignalHandle::enter()
{}

Void
ApplicationState::SignalHandle::update()
{
  auto& app = this->state_machine().context().app();
  auto  wm  = app.window_manager();

  if (wm->windows().empty() || app.main_window()->is_closing())
  {
    m_state_machine.set_next_state(std::make_unique<Stop>(m_state_machine));
    return;
  }

  wm->poll_events();

  m_state_machine.set_next_state(std::make_unique<Pause>(m_state_machine));
}

Void
ApplicationState::SignalHandle::exit()
{}

} // namespace setsugen
