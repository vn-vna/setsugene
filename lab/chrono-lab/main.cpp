#include <chrono>
#include <iostream>

#include <setsugen/engine.h>

int main()
{
  setsugen::Duration d {12192917034UL};
  setsugen::TimePoint t {31231231387100000UL};
  std::cout << setsugen::Formatter::format("{}", t);
}