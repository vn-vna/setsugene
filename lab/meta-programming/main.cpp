#include "main.h"

#include <iostream>
#include <source_location>

template<typename T>
void call_sth(T a)
{
  std::cout << std::source_location::current().function_name() << std::endl;
}

struct person
{
  std::string name;
};

int
main()
{
  auto p = person{};
  auto& [a] = p;

  call_sth(a);
}
