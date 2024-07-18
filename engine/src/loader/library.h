#pragma once

#include <setsugen/thislib.h>

setsugen::ThisLibrary* thislib = nullptr;

extern "C"
{
  bool on_load();
  bool on_unload();
}
