#include <setsugen/states.h>

namespace setsugen
{

RendererState::RendererState(Context& ctx) : StateMachine(ctx, std::make_unique<Initialize>(*this))
{}

} // namespace setsugen
