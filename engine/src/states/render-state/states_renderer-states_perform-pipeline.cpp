#include <setsugen/states.h>

namespace setsugen
{

RendererState::ReleaseECS::ReleaseECS(StateMachine& state_machine) : StateBase(state_machine)
{
  m_logger = LoggerFactory::default_factory().get("RendererState");
}

Void
RendererState::ReleaseECS::enter()
{
  m_logger->info("ReleaseECS");
}

Void
RendererState::ReleaseECS::update()
{
  m_state_machine.set_next_state(std::make_unique<FrameEnd>(m_state_machine));
}

Void
RendererState::ReleaseECS::exit()
{}

} // namespace setsugen
