#pragma once

#include <iostream>
#include <type_traits>

namespace lib
{

class Foo
{
public:
  template<typename T>
  Foo(T&& value);
};

} // namespace lib
