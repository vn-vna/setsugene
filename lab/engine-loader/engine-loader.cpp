#include <setsugen/engine.h>

#include <cassert>
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

int main()
{
  using namespace setsugen;

  ApplicationBuilder().build()->run();
}
