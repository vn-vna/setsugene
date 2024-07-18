#include <setsugen/executor.h>

#include "executor_platform-utilities.h"

namespace setsugen
{

FixedThreadPoolExecutor::FixedThreadPoolExecutor(size_t num_threads) : m_stopped(true), m_num_threads(num_threads)
{
  if (m_num_threads == 0)
  {
    m_num_threads = std::thread::hardware_concurrency();
  }

  if (m_num_threads == 0)
  {
    m_num_threads = 1;
  }
}

FixedThreadPoolExecutor::~FixedThreadPoolExecutor()
{
  std::unique_lock<std::mutex> lock(m_queue_mutex);
  m_stopped = true;
  m_threads.clear();
}

void
FixedThreadPoolExecutor::enqueue(ExecutorTask&& task)
{
  std::unique_lock<std::mutex> lock(m_queue_mutex);
  m_tasks.push(task);
}

FixedThreadPoolExecutor::ExecutorTask
FixedThreadPoolExecutor::dequeue()
{
  std::unique_lock<std::mutex> lock(m_queue_mutex);
  if (m_tasks.empty())
  {
    return nullptr;
  }

  auto task = m_tasks.front();
  m_tasks.pop();
  return task;
}


void
FixedThreadPoolExecutor::start()
{
  if (!m_stopped)
  {
    return;
  }

  m_stopped = false;

  if (!m_threads.empty())
  {
    m_threads.clear();
  }

  for (size_t i = 0; i < m_num_threads; ++i)
  {
    m_threads.emplace_back(std::make_unique<std::thread>(
        [this]
        {
          while (true)
          {
            if (m_stopped)
            {
              break;
            }

            if (is_queue_empty())
            {
              std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }

            auto task = dequeue();
            if (task)
            {
              std::invoke(task, false);
            }
          }
        }));
  }
}

void
FixedThreadPoolExecutor::stop()
{
  m_stopped = true;
  while (!is_queue_empty())
  {
    auto task = dequeue();
    if (task)
    {
      std::invoke(task, true);
    }
  }
}

void
FixedThreadPoolExecutor::force_stop()
{
  m_stopped = true;
  for (auto& thread: m_threads)
  {
    terminate_thread(*thread);
  }

  m_stopped = true;
  while (!is_queue_empty())
  {
    auto task = dequeue();
    if (task)
    {
      std::invoke(task, true);
    }
  }
}

void
FixedThreadPoolExecutor::join()
{
  for (auto& thread: m_threads)
  {
    thread->join();
  }
}

bool
FixedThreadPoolExecutor::is_stopped() const
{
  return m_stopped;
}

bool
FixedThreadPoolExecutor::is_queue_empty() const
{
  std::lock_guard<std::mutex> lock(m_queue_mutex);
  return m_tasks.empty();
}

} // namespace setsugen
