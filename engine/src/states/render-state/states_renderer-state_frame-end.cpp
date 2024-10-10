#include <setsugen/states.h>
#include <setsugen/context.h>

namespace setsugen
{

RendererState::FrameEnd::FrameEnd(StateMachine& state_machine) : StateBase(state_machine)
{
  m_logger = LoggerFactory::default_factory().get("RendererState");
}

Void
RendererState::FrameEnd::enter()
{
  m_logger->info("FrameEnd");
}

Void
RendererState::FrameEnd::update()
{
  auto& context = m_state_machine.context();
  context.signal_end_frame();
  m_state_machine.set_next_state(std::make_unique<SignalHandle>(m_state_machine));
}

Void
RendererState::FrameEnd::exit()
{}

} // namespace setsugen
