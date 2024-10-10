#include <setsugen/executor.h>

#include "executor_platform-utilities.h"

namespace setsugen
{

SingleThreadExecutor::SingleThreadExecutor() : m_stopped(true)
{}

SingleThreadExecutor::~SingleThreadExecutor() = default;

Void
SingleThreadExecutor::start()
{
  if (!m_stopped)
  {
    return;
  }

  m_stopped = false;

  m_thread = std::make_unique<std::thread>(
      [this]
      {
        while (true)
        {
          if (m_stopped)
          {
            break;
          }

          if (m_tasks.empty())
          {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
          }

          auto task = dequeue();
          if (task)
          {
            std::invoke(task, m_stopped);
          }
        }
      });
}

Void
SingleThreadExecutor::stop()
{
  if (m_stopped)
  {
    return;
  }

  m_stopped = true;
}

Void
SingleThreadExecutor::force_stop()
{
  if (m_stopped)
  {
    return;
  }

  m_stopped = true;
  terminate_thread(*m_thread);
}

Void
SingleThreadExecutor::join()
{
  if (m_thread && m_thread->joinable())
  {
    m_thread->join();
  }
}

Bool
SingleThreadExecutor::is_stopped() const
{
  return m_stopped;
}

Bool
SingleThreadExecutor::is_queue_empty() const
{
  return m_tasks.empty();
}

Void
SingleThreadExecutor::enqueue(ExecutorTask&& task)
{
  m_tasks.push(task);
}

SingleThreadExecutor::ExecutorTask
SingleThreadExecutor::dequeue()
{
  if (m_tasks.empty())
  {
    return nullptr;
  }

  auto task = m_tasks.front();
  m_tasks.pop();
  return task;
}

} // namespace setsugen
