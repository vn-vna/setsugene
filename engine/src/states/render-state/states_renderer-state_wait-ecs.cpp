#include <setsugen/states.h>

namespace setsugen
{

RendererState::WaitECS::
WaitECS(StateMachine& state_machine)
    : StateBase(state_machine)
{
  m_logger = LoggerFactory::default_factory().get("RendererState");
}

Void
RendererState::WaitECS::enter()
{
  m_logger->info("WaitECS");
}

Void
RendererState::WaitECS::update()
{
  m_state_machine.set_next_state(std::make_unique<BlockECS>(m_state_machine));
}

Void
RendererState::WaitECS::exit()
{}

} // namespace setsugen
