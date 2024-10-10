#include <setsugen/states.h>

namespace setsugen
{

RendererState::Ready::Ready(StateMachine& state_machine) : StateBase(state_machine)
{
  m_logger = LoggerFactory::default_factory().get("RendererState");
}

Void
RendererState::Ready::enter()
{
  m_logger->info("Ready");
}

Void
RendererState::Ready::update()
{
  m_state_machine.set_next_state(std::make_unique<WaitFrameBegin>(m_state_machine));
}

Void
RendererState::Ready::exit()
{}

} // namespace setsugen
