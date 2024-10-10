#include <setsugen/states.h>

namespace setsugen
{

RendererState::DestroyPipeline::
DestroyPipeline(StateMachine& state_machine)
    : StateBase(state_machine)
{
  m_logger = LoggerFactory::default_factory().get("RendererState");
}

Void
RendererState::DestroyPipeline::enter()
{
  m_logger->info("DestroyPipeline");
}

Void
RendererState::DestroyPipeline::update()
{
  m_logger->info("Destroying pipeline");
  m_state_machine.set_next_state(std::make_unique<DestroyRenderTarget>(m_state_machine));
}

Void
RendererState::DestroyPipeline::exit()
{}

} // namespace setsugen
