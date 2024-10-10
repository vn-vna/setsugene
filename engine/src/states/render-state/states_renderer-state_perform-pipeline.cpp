#include <setsugen/logger.h>
#include <setsugen/states.h>

namespace setsugen
{

RendererState::PerformPipeline::PerformPipeline(StateMachine& state_machine) : StateBase(state_machine)
{
  m_logger = LoggerFactory::default_factory().get("RendererState");
}

Void
RendererState::PerformPipeline::enter()
{
  m_logger->info("PerformPipeline");
}

Void
RendererState::PerformPipeline::update()
{
  m_state_machine.set_next_state(std::make_unique<ReleaseECS>(m_state_machine));
}

Void
RendererState::PerformPipeline::exit()
{}

} // namespace setsugen
