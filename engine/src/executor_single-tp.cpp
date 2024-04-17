#include <setsugen/executor.h>

#include "executor_platform-utilities.h"

namespace setsugen
{

SingleThreadExecutor::SingleThreadExecutor() : m_stopped(true)
{}

SingleThreadExecutor::~SingleThreadExecutor() = default;

void
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

void
SingleThreadExecutor::stop()
{
  if (m_stopped)
  {
    return;
  }

  m_stopped = true;
}

void
SingleThreadExecutor::force_stop()
{
  if (m_stopped)
  {
    return;
  }

  m_stopped = true;
  terminate_thread(*m_thread);
}

void
SingleThreadExecutor::join()
{
  if (m_thread && m_thread->joinable())
  {
    m_thread->join();
  }
}

bool
SingleThreadExecutor::is_stopped() const
{
  return m_stopped;
}

bool
SingleThreadExecutor::is_queue_empty() const
{
  return m_tasks.empty();
}

void
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
