#include <setsugen/states.h>

namespace setsugen
{

RendererState::CreateRenderTarget::
CreateRenderTarget(StateMachine& state_machine)
    : StateBase(state_machine)
{
  m_logger = LoggerFactory::default_factory().get("RendererState");
}

Void
RendererState::CreateRenderTarget::enter()
{
  m_logger->info("CreatingTarget");
}

Void
RendererState::CreateRenderTarget::update()
{
  m_state_machine.set_next_state(std::make_unique<CreatePipeline>(m_state_machine));
}

Void
RendererState::CreateRenderTarget::exit()
{}

} // namespace setsugen
