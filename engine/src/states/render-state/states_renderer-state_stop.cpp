#include <setsugen/states.h>

namespace setsugen
{

RendererState::Stop::
Stop(StateMachine& state_machine)
    : StateBase(state_machine)
{
  m_logger = LoggerFactory::default_factory().get("RendererState");
}

Void
RendererState::Stop::enter()
{
  m_logger->info("Stop");
}

Void
RendererState::Stop::update()
{
  m_state_machine.set_next_state(std::make_unique<Destroy>(m_state_machine));
}

Void
RendererState::Stop::exit()
{}

} // namespace setsugen
