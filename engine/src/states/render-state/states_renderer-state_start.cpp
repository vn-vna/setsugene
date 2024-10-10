#include <setsugen/states.h>

namespace setsugen
{

RendererState::Start::Start(StateMachine& state_machine) : StateBase(state_machine)
{
  m_logger = LoggerFactory::default_factory().get("RendererState");
}

Void
RendererState::Start::enter()
{
  m_logger->info("Start");
}

Void
RendererState::Start::update()
{
  m_state_machine.set_next_state(std::make_unique<Ready>(m_state_machine));
}

Void
RendererState::Start::exit()
{}

} // namespace setsugen
