#pragma once

#include "state_interface.inl"
#include "state_machine.inl"

namespace setsugen
{

class RendererState : public StateMachine
{
public:
  class Initialize;
  class Start;
  class Ready;
  class WaitFrameBegin;
  class FrameBegin;
  class ValidatePipeline;
  class DestroyPipeline;
  class DestroyRenderTarget;
  class CreateRenderTarget;
  class CreatePipeline;
  class WaitECS;
  class BlockECS;
  class PerformPipeline;
  class ReleaseECS;
  class FrameEnd;
  class SignalHandle;
  class Stop;
  class Destroy;

  RendererState();
};

#define DECLARE_STATE_CLASS(StateName)                                                                                 \
  class RendererState::StateName : public State                                                                     \
  {                                                                                                                    \
  public:                                                                                                              \
    explicit StateName(StateMachine& state_machine);                                                                   \
    void update() override;                                                                                            \
  }

DECLARE_STATE_CLASS(Initialize);
DECLARE_STATE_CLASS(Start);
DECLARE_STATE_CLASS(Ready);
DECLARE_STATE_CLASS(WaitFrameBegin);
DECLARE_STATE_CLASS(FrameBegin);
DECLARE_STATE_CLASS(ValidatePipeline);
DECLARE_STATE_CLASS(DestroyPipeline);
DECLARE_STATE_CLASS(DestroyRenderTarget);
DECLARE_STATE_CLASS(CreateRenderTarget);
DECLARE_STATE_CLASS(CreatePipeline);
DECLARE_STATE_CLASS(WaitECS);
DECLARE_STATE_CLASS(BlockECS);
DECLARE_STATE_CLASS(PerformPipeline);
DECLARE_STATE_CLASS(ReleaseECS);
DECLARE_STATE_CLASS(FrameEnd);
DECLARE_STATE_CLASS(SignalHandle);
DECLARE_STATE_CLASS(Stop);
DECLARE_STATE_CLASS(Destroy);

#undef DECLARE_STATE_CLASS

} // namespace setsugen
