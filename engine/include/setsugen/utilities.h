#include <setsugen/pch.h>

namespace setsugen
{

template <typename ...Ts>
struct TupleHash : Fn<Size(const Tuple<Ts...>&)>
{
  Size operator()(const Tuple<Ts...>& t) const
  {
    return hash_combine<0>(t);
  }

  template <Size I, typename ...Ts>
  Size hash_combine(const Tuple<Ts...>& t) const
  {
    if constexpr (I >= sizeof...(Ts))
    {
      return 0;
    }
    else
    {
      auto next = hash_combine<I + 1>(t);
      return std::hash<std::tuple_element_t<I, Tuple<Ts...>>>()(std::get<I>(t)) ^ next ^ (next << 6) ^ (next >> 2);
    }
  }
};

}