#include <setsugen/states.h>

namespace setsugen
{

RendererState::CreatePipeline::
CreatePipeline(StateMachine& state_machine)
    : StateBase(state_machine)
{
  m_logger = LoggerFactory::default_factory().get("RendererState");
}

Void
RendererState::CreatePipeline::enter()
{
  m_logger->info("CreatePipeline");
}

Void
RendererState::CreatePipeline::update()
{
  m_state_machine.set_next_state(std::make_unique<WaitECS>(m_state_machine));
}

Void
RendererState::CreatePipeline::exit()
{}

} // namespace setsugen
