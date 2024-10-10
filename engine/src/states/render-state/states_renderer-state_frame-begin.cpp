#include <setsugen/states.h>
#include <setsugen/context.h>

namespace setsugen
{

RendererState::FrameBegin::FrameBegin(StateMachine& state_machine) : StateBase(state_machine)
{
  m_logger = LoggerFactory::default_factory().get("RendererState");
}

Void
RendererState::FrameBegin::enter()
{
  m_logger->info("FrameBegin");
}

Void
RendererState::FrameBegin::update()
{
}

Void
RendererState::FrameBegin::exit()
{}

} // namespace setsugen
