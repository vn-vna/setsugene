#include <setsugen/context.h>
#include <setsugen/states.h>


namespace setsugen
{

RendererState::WaitFrameBegin::WaitFrameBegin(StateMachine& state_machine) : StateBase(state_machine)
{
  m_logger = LoggerFactory::default_factory().get("RendererState");
}

Void
RendererState::WaitFrameBegin::enter()
{
  m_logger->info("WaitFrameBegin");
}

Void
RendererState::WaitFrameBegin::update()
{
  auto& context = m_state_machine.context();
  context.wait_render_begin();

  m_state_machine.set_next_state(std::make_unique<ValidatePipeline>(m_state_machine));
}

Void
RendererState::WaitFrameBegin::exit()
{}

} // namespace setsugen
