#pragma once

#include <GLFW/glfw3.h>
#include <setsugen/wm.h>

namespace setsugen
{

class GlfwWindow : public Window
{
public:
  using ControlEvent = std::function<Void(Window&)>;

  GlfwWindow(WindowManager& manager, UInt32 width, UInt32 height, const String& title);

  virtual ~GlfwWindow();

  Void  show() override;
  Void  hide() override;
  Void  set_title(const String& title) override;
  Void  set_size(UInt32 width, UInt32 height) override;
  Void  set_position(UInt32 x, UInt32 y) override;
  Void  set_fullscreen(Bool fullscreen) override;
  Void  set_cursor_visible(Bool visible) override;
  Void  set_cursor_grabbed(Bool grabbed) override;
  Void  set_cursor_position(UInt32 x, UInt32 y) override;
  Void  set_resizable(Bool resizable) override;
  Void  set_decorated(Bool decorated) override;
  Void  set_floating(Bool floating) override;
  Void  set_minimized(Bool minimized) override;
  Void  set_maximized(Bool maximized) override;
  Void  set_min_size(Dim2U size) override;
  Void  set_aspect_ratio(Dim2U aspect) override;
  Void  set_opacity(Float32 opacity) override;
  Void  set_key_repeat(Bool repeat) override;
  Void* handle() override;

  Dim2U get_size() const override;
  Dim2U get_framebuffer_size() const override;
  Dim2U get_position() const override;
  Bool  is_fullscreen() const override;
  Bool  is_cursor_visible() const override;
  Bool  is_closing() const override;

private:
  Void on_cursor_move(Dim2I position);
  Void on_close();
  Void on_key_press(Int32 key, Int32 scan, Int32 mods);
  Void on_key_release(Int32 key, Int32 scan, Int32 mods);
  Void on_text_input(UInt32 codepoint);
  Void on_mouse_button_press(Int32 button, Int32 mods);
  Void on_mouse_button_release(Int32 button, Int32 mods);
  Void on_mouse_enter(Bool entered);

  UInt32      m_width;
  UInt32      m_height;
  String      m_title;
  GLFWwindow* m_window;
};

} // namespace setsugen
