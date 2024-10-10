#pragma once

#include "wm_cursor.inl"
#include "wm_fwd.inl"

#include <setsugen/math.h>

namespace setsugen
{

class Window
{
public:
  Window(WindowManager& manager);

  virtual ~Window() noexcept;

  virtual Void  show()                                  = 0;
  virtual Void  hide()                                  = 0;
  virtual Void  set_title(const String& title)          = 0;
  virtual Void  set_size(UInt32 width, UInt32 height)   = 0;
  virtual Void  set_position(UInt32 x, UInt32 y)        = 0;
  virtual Void  set_fullscreen(Bool fullscreen)         = 0;
  virtual Void  set_cursor_visible(Bool visible)        = 0;
  virtual Void  set_cursor_grabbed(Bool grabbed)        = 0;
  virtual Void  set_cursor_position(UInt32 x, UInt32 y) = 0;
  virtual Void  set_resizable(Bool resizable)           = 0;
  virtual Void  set_decorated(Bool decorated)           = 0;
  virtual Void  set_floating(Bool floating)             = 0;
  virtual Void  set_minimized(Bool minimized)           = 0;
  virtual Void  set_maximized(Bool maximized)           = 0;
  virtual Void  set_min_size(Dim2U size)                = 0;
  virtual Void  set_aspect_ratio(Dim2U aspect)          = 0;
  virtual Void  set_opacity(Float32 opacity)            = 0;
  virtual Void  set_key_repeat(Bool repeat)             = 0;
  virtual Void* handle()                                = 0;

  virtual Dim2U get_size() const             = 0;
  virtual Dim2U get_framebuffer_size() const = 0;
  virtual Dim2U get_position() const         = 0;
  virtual Bool  is_fullscreen() const        = 0;
  virtual Bool  is_cursor_visible() const    = 0;
  virtual Bool  is_closing() const           = 0;

private:
  WindowManager& m_manager;
};

} // namespace setsugen
