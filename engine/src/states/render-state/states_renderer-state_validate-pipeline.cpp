#include <setsugen/states.h>
#include <setsugen/context.h>
#include <setsugen/gfx.h>

namespace setsugen
{

RendererState::ValidatePipeline::
ValidatePipeline(StateMachine& state_machine)
    : StateBase(state_machine)
{
  m_logger = LoggerFactory::default_factory().get("RendererState");
}

Void
RendererState::ValidatePipeline::enter()
{
  m_logger->info("ValidatePipeline");
}

Void
RendererState::ValidatePipeline::update()
{
  auto present_target = m_state_machine.context().present_target();
  if (!present_target || !present_target->is_validated())
  {
    m_state_machine.set_next_state(std::make_unique<DestroyPipeline>(m_state_machine));
  }

  m_state_machine.set_next_state(std::make_unique<WaitECS>(m_state_machine));
}

Void
RendererState::ValidatePipeline::exit()
{}

} // namespace setsugen
