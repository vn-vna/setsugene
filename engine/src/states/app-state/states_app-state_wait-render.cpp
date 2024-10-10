#include <setsugen/application.h>
#include <setsugen/context.h>
#include <setsugen/gfx.h>
#include <setsugen/logger.h>
#include <setsugen/states.h>

namespace setsugen
{

ApplicationState::WaitRenderer::WaitRenderer(StateMachine& state_machine) : State(state_machine)
{}

Void
ApplicationState::WaitRenderer::enter()
{}

Void
ApplicationState::WaitRenderer::update()
{
  auto app            = Application::current_app();
  auto render_context = app->renderer_context();

  render_context->wait_render_complete();
  m_state_machine.set_next_state(std::make_unique<FrameEnd>(m_state_machine));
}

Void
ApplicationState::WaitRenderer::exit()
{}

} // namespace setsugen
