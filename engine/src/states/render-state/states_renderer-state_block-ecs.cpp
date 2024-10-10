#include <setsugen/states.h>
#include <setsugen/logger.h>

namespace setsugen
{

RendererState::BlockECS::BlockECS(StateMachine& state_machine) : StateBase(state_machine)
{
  m_logger = LoggerFactory::default_factory().get("RendererState");
}

Void
RendererState::BlockECS::enter()
{
  m_logger->info("BlockECS");
}

Void
RendererState::BlockECS::update()
{
  m_state_machine.set_next_state(std::make_unique<PerformPipeline>(m_state_machine));
}

Void
RendererState::BlockECS::exit()
{}

} // namespace setsugen
