#pragma once

#include <setsugen/pch.h>
#include <setsugen/types.h>

namespace setsugen
{

template<typename Context>
class StateMachine;

template<typename Context>
class StateBase;

template <typename M>
class StateLoop;

template<typename Context>
concept StateContext = requires (Context ctx)
{
  { ctx.alive() } -> std::same_as<Bool>;
};

class AppContext;
class ECSContext;
class RenderContext;

} // namespace setsugen
