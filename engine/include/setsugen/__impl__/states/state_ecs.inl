#pragma once

#include "state_interface.inl"
#include "state_machine.inl"

namespace setsugen
{

class ECSState : public StateMachine<ECSContext>
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

class ECSState::Initialize : public StateBase<ECSState>
{
public:
  Initialize(StateMachine& state_machine);

  Void enter() override;
  Void update() override;
  Void exit() override;
};

class ECSState::Start : public StateBase<ECSState>
{
public:
  Start(StateMachine& state_machine);

  Void enter() override;
  Void update() override;
  Void exit() override;
};

class ECSState::Ready : public StateBase<ECSState>
{
public:
  Ready(StateMachine& state_machine);

  Void enter() override;
  Void update() override;
  Void exit() override;
};


} // namespace setsugen
