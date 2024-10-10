#include <setsugen/application.h>
#include <setsugen/context.h>
#include <setsugen/gfx.h>
#include <setsugen/states.h>


namespace setsugen
{

RendererState::Initialize::Initialize(StateMachine& state_machine) : StateBase(state_machine)
{
  m_logger = LoggerFactory::default_factory().get("RendererState");
}

Void
RendererState::Initialize::enter()
{
  m_logger->info("Initialize");
}

Void
RendererState::Initialize::update()
{
  auto& context = m_state_machine.context();
  m_logger->info("Creating renderer");
  context.set_renderer(Renderer::create(*Application::current_app()->config(), RendererType::Vulkan));
  m_logger->info("Created renderer, notifying renderer ready");
  context.signal_renderer_ready();
  m_state_machine.set_next_state(std::make_unique<Start>(m_state_machine));
}

Void
RendererState::Initialize::exit()
{}

} // namespace setsugen
