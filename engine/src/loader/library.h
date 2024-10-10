#pragma once

#include <setsugen/thislib.h>

#ifdef SETSUGENE_WINDOWS
#include <Windows.h>
#endif

setsugen::ThisLibrary* thislib = nullptr;

extern "C"
{
  setsugen::Bool on_load();
  setsugen::Bool on_unload();
}
