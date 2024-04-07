#include "library.h"

#include <cstdint>
#include <iostream>

namespace lib
{

template <typename T>
void do_sth(T value)
{
  std::cout << "Called with type: " << typeid(T).name() << std::endl;
}

template void do_sth(int8_t);
template void do_sth(int16_t);
template void do_sth(int32_t);
template void do_sth(int64_t);

template void do_sth(uint8_t);
template void do_sth(uint16_t);
template void do_sth(uint32_t);
template void do_sth(uint64_t);

}  // namespace lib