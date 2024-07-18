#include <setsugen/window.h>

// Dependency headers
#include <GLFW/glfw3.h>

namespace setsugen
{

WindowCommandQueue::WindowCommandQueue() : m_queue{}, m_mutex{}
{}

WindowCommandQueue::~WindowCommandQueue() = default;

void
WindowCommandQueue::push(WindowCommand command)
{
  std::lock_guard<std::mutex> lock{m_mutex};
  m_queue.push(command);
}

void
WindowCommandQueue::execute()
{
  std::lock_guard<std::mutex> lock{m_mutex};
  while (!m_queue.empty())
  {
    std::invoke(m_queue.front());
    m_queue.pop();
  }
}

} // namespace setsugen
