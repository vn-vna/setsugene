#pragma once

#include <setsugen/thislib.h>

extern setsugen::ThisLibrary* thislib = nullptr;

extern "C"
{
bool on_load();
bool on_unload();
}
