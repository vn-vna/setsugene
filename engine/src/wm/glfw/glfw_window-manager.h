#pragma once

#include <setsugen/wm.h>

namespace setsugen
{

class GlfwWindowManager : public WindowManager
{
public:
  GlfwWindowManager();
  ~GlfwWindowManager();

  Void poll_events() override;
  Void wait_events() override;

  Owner<Window> create_window(UInt32 width, UInt32 height, const String& title) override;

private:
};

} // namespace setsugen
