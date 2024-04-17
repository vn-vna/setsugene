#include <setsugen/scripting.h>

namespace setsugen
{

Behavior::Behavior(Entity* entity) : Component{entity}
{}

Behavior::~Behavior() = default;

} // namespace setsugen
