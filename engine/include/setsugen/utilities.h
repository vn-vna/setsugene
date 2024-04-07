#include <setsugen/pch.h>

namespace setsugen
{

template<typename... Ts>
struct TupleHash : std::function<size_t(const std::tuple<Ts...>&)>
{
  size_t operator()(const std::tuple<Ts...>& t) const
  {
    return hash_combine<0>(t);
  }

  template<size_t I, typename... Tys>
  size_t hash_combine(const std::tuple<Tys...>& t) const
  {
    if constexpr (I >= sizeof...(Tys))
    {
      return 0;
    }
    else
    {
      auto next = hash_combine<I + 1>(t);
      return std::hash<std::tuple_element_t<I, std::tuple<Ts...>>>()(std::get<I>(t)) ^ next ^ (next << 6) ^ (next >> 2);
    }
  }
};

} // namespace setsugen
