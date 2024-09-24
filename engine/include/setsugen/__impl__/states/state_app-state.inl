#pragma once

#include "state_interface.inl"
#include "state_machine.inl"

namespace setsugen
{

class ApplicationState : public StateMachine
{
public:
  class Initialize;
  class Start;
  class Ready;

  class Resume;
  class FrameBegin;
  class WaitRenderer;
  class FrameEnd;

  class SignalHandle;
  class Pause;
  class Stop;
  class Destroy;

  ApplicationState();
};

#define DECLARE_STATE_CLASS(StateName)                                                                                 \
  class ApplicationState::StateName : public State                                                                     \
  {                                                                                                                    \
  public:                                                                                                              \
    explicit StateName(StateMachine& state_machine);                                                                   \
    void update() override;                                                                                            \
  }


DECLARE_STATE_CLASS(Initialize);
DECLARE_STATE_CLASS(Start);
DECLARE_STATE_CLASS(Ready);
DECLARE_STATE_CLASS(Resume);
DECLARE_STATE_CLASS(FrameBegin);
DECLARE_STATE_CLASS(WaitRenderer);
DECLARE_STATE_CLASS(FrameEnd);
DECLARE_STATE_CLASS(SignalHandle);
DECLARE_STATE_CLASS(Pause);
DECLARE_STATE_CLASS(Stop);
DECLARE_STATE_CLASS(Destroy);

#undef DECLARE_STATE_CLASS

} // namespace setsugen
