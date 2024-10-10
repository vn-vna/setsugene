#include <setsugen/states.h>

namespace setsugen
{

RendererState::DestroyRenderTarget::
DestroyRenderTarget(StateMachine& state_machine)
    : StateBase(state_machine)
{
  m_logger = LoggerFactory::default_factory().get("RendererState");
}

Void
RendererState::DestroyRenderTarget::enter()
{
  m_logger->info("DestroyRenderTarget");
}

Void
RendererState::DestroyRenderTarget::update()
{
  m_state_machine.set_next_state(std::make_unique<CreateRenderTarget>(m_state_machine));
}

Void
RendererState::DestroyRenderTarget::exit()
{}

} // namespace setsugen
