#include <setsugen/states.h>

namespace setsugen
{

ApplicationState::ApplicationState(AppContext& ctx) : StateMachine(ctx, std::make_unique<Initialize>(*this))
{}

} // namespace setsugen
