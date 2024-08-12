#pragma once

#include <setsugen/pch.h>

// Setsugen headers
#include <setsugen/gfx.h>
#include <setsugen/input.h>
#include <setsugen/logger.h>
#include <setsugen/math.h>

// C++ Standard headers
#include <functional>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

namespace setsugen
{
enum class WindowEventMode;
class InputManager;
class Window;
class WindowManager;

using WindowCommand = std::function<void()>;

enum class WindowEventMode
{
  Polling,
  Wait
};

class WindowCommandQueue
{
public:
   WindowCommandQueue();
  ~WindowCommandQueue();

public:
  void push(WindowCommand command);
  void execute();

private:
  std::queue<WindowCommand> m_queue;
  std::mutex                m_mutex;

private:
  friend class Window;
};

class Window
{
public:
  using Handler = void*;

   Window(const std::string& title, int width, int height);
  ~Window();

  static std::unique_ptr<Window> create(const std::string& title, int width, int height);

  Dim2I get_size() const;
  Dim2I get_framebuffer_size() const;
  bool  is_visible() const;

  void set_event_mode(WindowEventMode event_mode);
  void set_title(const std::string& title);
  void set_size(int width, int height);

  void show_window();
  void hide_window();

  void loop();
  void join();

  Handler get_handler() const;

private:
  std::unique_ptr<RenderTarget> create_render_target();

  void window_thread_func(const char* title, int width, int height);

  void*                         m_handler;
  std::thread                   m_thread;
  std::function<void()>         m_main_loop;
  WindowEventMode               m_event_mode;
  WindowCommandQueue            m_command_queue;
  std::shared_ptr<InputManager> m_input_manager;
  Renderer*                     m_renderer;
  std::shared_ptr<Logger>       m_logger;
  std::condition_variable       m_window_ready_condition;
  std::mutex                    m_window_ready_mutex;

  friend class WindowCommandQueue;
};
} // namespace setsugen
