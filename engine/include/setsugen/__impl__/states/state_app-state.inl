#pragma once

#include "state_fwd.inl"
#include "state_interface.inl"
#include "state_machine.inl"

#include "../logger/logger_decl.inl"
#include "../logger/logger_fwd.inl"

namespace setsugen
{

class ApplicationState : public StateMachine<AppContext>
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

  ApplicationState(Context& ctx);
};

class ApplicationState::Initialize : public StateBase<AppContext>
{
public:
  Initialize(StateMachine& state_machine);

  Void enter() override;
  Void update() override;
  Void exit() override;

private:
  Owner<Logger> m_logger;
};

class ApplicationState::Start : public StateBase<AppContext>
{
public:
  Start(StateMachine& state_machine);

  Void enter() override;
  Void update() override;
  Void exit() override;

private:
  Owner<Logger> m_logger;
};

class ApplicationState::Ready : public StateBase<AppContext>
{
public:
  Ready(StateMachine& state_machine);

  Void enter() override;
  Void update() override;
  Void exit() override;

private:
  Owner<Logger> m_logger;
};

class ApplicationState::Resume : public StateBase<AppContext>
{
public:
  Resume(StateMachine& state_machine);

  Void enter() override;
  Void update() override;
  Void exit() override;

private:
  Owner<Logger> m_logger;
};

class ApplicationState::FrameBegin : public StateBase<AppContext>
{
public:
  FrameBegin(StateMachine& state_machine);

  Void enter() override;
  Void update() override;
  Void exit() override;

private:
  Owner<Logger> m_logger;
};

class ApplicationState::WaitRenderer : public StateBase<AppContext>
{
public:
  WaitRenderer(StateMachine& state_machine);

  Void enter() override;
  Void update() override;
  Void exit() override;

private:
  Owner<Logger> m_logger;
};

class ApplicationState::FrameEnd : public StateBase<AppContext>
{
public:
  FrameEnd(StateMachine& state_machine);

  Void enter() override;
  Void update() override;
  Void exit() override;

private:
  Owner<Logger> m_logger;
};

class ApplicationState::SignalHandle : public StateBase<AppContext>
{
public:
  SignalHandle(StateMachine& state_machine);

  Void enter() override;
  Void update() override;
  Void exit() override;

private:
  Owner<Logger> m_logger;
};

class ApplicationState::Pause : public StateBase<AppContext>
{
public:
  Pause(StateMachine& state_machine);

  Void enter() override;
  Void update() override;
  Void exit() override;

private:
  Owner<Logger> m_logger;
};

class ApplicationState::Stop : public StateBase<AppContext>
{
public:
  Stop(StateMachine& state_machine);

  Void enter() override;
  Void update() override;
  Void exit() override;

private:
  Owner<Logger> m_logger;
};

class ApplicationState::Destroy : public StateBase<AppContext>
{
public:
  Destroy(StateMachine& state_machine);

  Void enter() override;
  Void update() override;
  Void exit() override;

private:
  Owner<Logger> m_logger;
};

} // namespace setsugen
