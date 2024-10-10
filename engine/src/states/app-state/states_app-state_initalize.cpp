#include <setsugen/application.h>
#include <setsugen/context.h>
#include <setsugen/gfx.h>
#include <setsugen/logger.h>
#include <setsugen/states.h>
#include <setsugen/wm.h>

#include <GLFW/glfw3.h>
#include <Volk/volk.h>

namespace setsugen
{

ApplicationState::Initialize::Initialize(StateMachine& state_machine) : State(state_machine)
{
  m_logger = LoggerFactory::default_factory().get("Application::Initialize");
}

Void
ApplicationState::Initialize::enter()
{}

Void
ApplicationState::Initialize::update()
{
  auto& app = this->state_machine().context().app();

  app.set_window_manager(WindowManager::create());
  app.set_main_window(app.window_manager()->create_window(800, 600, "Setsugen"));

  state_machine().set_next_state(std::make_unique<Start>(state_machine()));
}

Void
ApplicationState::Initialize::exit()
{}

} // namespace setsugen
