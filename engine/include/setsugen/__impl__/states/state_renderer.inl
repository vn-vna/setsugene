#pragma once

#include "../logger/logger_fwd.inl"
#include "state_interface.inl"
#include "state_machine.inl"

namespace setsugen
{

class RendererState : public StateMachine<RenderContext>
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

  RendererState(Context& ctx);
};

class RendererState::Initialize : public StateBase<RenderContext>
{
public:
  Initialize(StateMachine& state_machine);

  Void enter() override;
  Void update() override;
  Void exit() override;

private:
  Owner<Logger> m_logger;
};

class RendererState::Start : public StateBase<RenderContext>
{
public:
  Start(StateMachine& state_machine);

  Void enter() override;
  Void update() override;
  Void exit() override;

private:
  Owner<Logger> m_logger;
};

class RendererState::Ready : public StateBase<RenderContext>
{
public:
  Ready(StateMachine& state_machine);

  Void enter() override;
  Void update() override;
  Void exit() override;

private:
  Owner<Logger> m_logger;
};

class RendererState::WaitFrameBegin : public StateBase<RenderContext>
{
public:
  WaitFrameBegin(StateMachine& state_machine);

  Void enter() override;
  Void update() override;
  Void exit() override;

private:
  Owner<Logger> m_logger;
};

class RendererState::FrameBegin : public StateBase<RenderContext>
{
public:
  FrameBegin(StateMachine& state_machine);

  Void enter() override;
  Void update() override;
  Void exit() override;

private:
  Owner<Logger> m_logger;
};

class RendererState::ValidatePipeline : public StateBase<RenderContext>
{
public:
  ValidatePipeline(StateMachine& state_machine);

  Void enter() override;
  Void update() override;
  Void exit() override;

private:
  Owner<Logger> m_logger;
};

class RendererState::DestroyPipeline : public StateBase<RenderContext>
{
public:
  DestroyPipeline(StateMachine& state_machine);

  Void enter() override;
  Void update() override;
  Void exit() override;

private:
  Owner<Logger> m_logger;
};

class RendererState::DestroyRenderTarget : public StateBase<RenderContext>
{
public:
  DestroyRenderTarget(StateMachine& state_machine);

  Void enter() override;
  Void update() override;
  Void exit() override;

private:
  Owner<Logger> m_logger;
};

class RendererState::CreateRenderTarget : public StateBase<RenderContext>
{
public:
  CreateRenderTarget(StateMachine& state_machine);

  Void enter() override;
  Void update() override;
  Void exit() override;

private:
  Owner<Logger> m_logger;
};

class RendererState::CreatePipeline : public StateBase<RenderContext>
{
public:
  CreatePipeline(StateMachine& state_machine);

  Void enter() override;
  Void update() override;
  Void exit() override;

private:
  Owner<Logger> m_logger;
};

class RendererState::WaitECS : public StateBase<RenderContext>
{
public:
  WaitECS(StateMachine& state_machine);

  Void enter() override;
  Void update() override;
  Void exit() override;

private:
  Owner<Logger> m_logger;
};

class RendererState::BlockECS : public StateBase<RenderContext>
{
public:
  BlockECS(StateMachine& state_machine);

  Void enter() override;
  Void update() override;
  Void exit() override;

private:
  Owner<Logger> m_logger;
};

class RendererState::PerformPipeline : public StateBase<RenderContext>
{
public:
  PerformPipeline(StateMachine& state_machine);

  Void enter() override;
  Void update() override;
  Void exit() override;

private:
  Owner<Logger> m_logger;
};

class RendererState::ReleaseECS : public StateBase<RenderContext>
{
public:
  ReleaseECS(StateMachine& state_machine);

  Void enter() override;
  Void update() override;
  Void exit() override;

private:
  Owner<Logger> m_logger;
};

class RendererState::FrameEnd : public StateBase<RenderContext>
{
public:
  FrameEnd(StateMachine& state_machine);

  Void enter() override;
  Void update() override;
  Void exit() override;

private:
  Owner<Logger> m_logger;
};

class RendererState::SignalHandle : public StateBase<RenderContext>
{
public:
  SignalHandle(StateMachine& state_machine);

  Void enter() override;
  Void update() override;
  Void exit() override;

private:
  Owner<Logger> m_logger;
};

class RendererState::Stop : public StateBase<RenderContext>
{
public:
  Stop(StateMachine& state_machine);

  Void enter() override;
  Void update() override;
  Void exit() override;

private:
  Owner<Logger> m_logger;
};

class RendererState::Destroy : public StateBase<RenderContext>
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
