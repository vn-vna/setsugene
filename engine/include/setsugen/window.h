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
#include <optional>
#include <queue>
#include <string>
#include <thread>

namespace setsugen
{
enum class WindowEventMode;
class InputManager;
class Window;
class WindowManager;

using WindowCommand = Fn<Void()>;

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
  Void push(WindowCommand command);
  Void execute();

private:
  Queue<WindowCommand> m_queue;
  Mutex                m_mutex;

private:
  friend class Window;
};

class Window
{
public:
  Window(const String& title, Int32 width, Int32 height);
  ~Window();

  static SharedPtr<Window> create(const String& title, Int32 width, Int32 height);

  SharedPtr<RenderTarget> create_render_target();
  Dim2I                   get_size() const;
  Dim2I                   get_framebuffer_size() const;
  Bool                    is_visible() const;

  Void set_event_mode(WindowEventMode event_mode);
  Void set_title(const String& title);
  Void set_size(Int32 width, Int32 height);

  Void show_window();
  Void hide_window();
  Void join();

  Handler get_handler() const;

private:
  Void*                   m_handler;
  Thread                  m_thread;
  WindowEventMode         m_event_mode;
  WindowCommandQueue      m_command_queue;
  SharedPtr<InputManager> m_input_manager;
  SharedPtr<Renderer>     m_renderer;
  SharedPtr<Logger>       m_logger;

  friend class WindowCommandQueue;
};
} // namespace setsugen
