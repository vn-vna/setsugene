#pragma once

#include "state_interface.inl"
#include "state_machine.inl"

namespace setsugen
{

class ECSState : public StateMachine
{
public:
  class Initialize;
  class Start;
  class Ready;

  class WaitRenderer;
  class UpdateBegin;
  class HandleInput;
  class SceneUpdate;
  class ValidateScene;
  class DestroyScene;
  class CreateScene;
  class UpdateScene;
  class UpdatePhysics;
  class UpdateAnimation;
  class UpdateAudio;
  class UpdateScript;
  class UpdateUI;
  class UpdateFinish;

  class SignalHandle;
  class Stop;
  class Destroy;

  ECSState();
};

#define DECLARE_STATE_CLASS(StateName)                                                                                 \
  class ECSState::StateName : public State                                                                             \
  {                                                                                                                    \
  public:                                                                                                              \
    explicit StateName(StateMachine& state_machine);                                                                   \
    void update() override;                                                                                            \
  }

DECLARE_STATE_CLASS(Initialize);
DECLARE_STATE_CLASS(Start);
DECLARE_STATE_CLASS(Ready);
DECLARE_STATE_CLASS(WaitRenderer);
DECLARE_STATE_CLASS(UpdateBegin);
DECLARE_STATE_CLASS(HandleInput);
DECLARE_STATE_CLASS(SceneUpdate);
DECLARE_STATE_CLASS(ValidateScene);
DECLARE_STATE_CLASS(DestroyScene);
DECLARE_STATE_CLASS(CreateScene);
DECLARE_STATE_CLASS(UpdateScene);
DECLARE_STATE_CLASS(UpdatePhysics);
DECLARE_STATE_CLASS(UpdateAnimation);
DECLARE_STATE_CLASS(UpdateAudio);
DECLARE_STATE_CLASS(UpdateScript);
DECLARE_STATE_CLASS(UpdateUI);
DECLARE_STATE_CLASS(UpdateFinish);
DECLARE_STATE_CLASS(SignalHandle);
DECLARE_STATE_CLASS(Stop);
DECLARE_STATE_CLASS(Destroy);

#undef DECLARE_STATE_CLASS

} // namespace setsugen
