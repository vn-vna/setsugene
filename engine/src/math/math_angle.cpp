#include <setsugen/math.h>

namespace setsugen
{

template<>
template<>
constexpr Float32
Angle<AngleUnit::Radian>::to_radian<AngleUnit::Radian>(Float32 value)
{
  return value;
}

template<>
template<>
constexpr Float32
Angle<AngleUnit::Radian>::to_radian<AngleUnit::Degree>(Float32 value)
{
  return value * 180.0f / std::numbers::pi_v<Float32>;
}

template<>
template<>
constexpr Float32
Angle<AngleUnit::Radian>::to_radian<AngleUnit::Grad>(Float32 value)
{
  return value * 200.0f / std::numbers::pi_v<Float32>;
}

template<>
template<>
constexpr Float32
Angle<AngleUnit::Radian>::to_radian<AngleUnit::Arcminute>(Float32 value)
{
  return value * 60.0f * 180.0f / std::numbers::pi_v<Float32>;
}

template<>
template<>
constexpr Float32
Angle<AngleUnit::Degree>::to_degree<AngleUnit::Radian>(Float32 value)
{
  return value * std::numbers::pi_v<Float32> / 180.0f;
}

template<>
template<>
constexpr Float32
Angle<AngleUnit::Degree>::to_degree<AngleUnit::Degree>(Float32 value)
{
  return value;
}

template<>
template<>
constexpr Float32
Angle<AngleUnit::Degree>::to_degree<AngleUnit::Grad>(Float32 value)
{
  return value * 200.0f / 180.0f;
}

template<>
template<>
constexpr Float32
Angle<AngleUnit::Degree>::to_degree<AngleUnit::Arcminute>(Float32 value)
{
  return value * 60.0f;
}

template<>
template<>
constexpr Float32
Angle<AngleUnit::Grad>::to_grad<AngleUnit::Radian>(Float32 value)
{
  return value * std::numbers::pi_v<Float32> / 200.0f;
}

template<>
template<>
constexpr Float32
Angle<AngleUnit::Grad>::to_grad<AngleUnit::Degree>(Float32 value)
{
  return value * 180.0f / 200.0f;
}

template<>
template<>
constexpr Float32
Angle<AngleUnit::Grad>::to_grad<AngleUnit::Grad>(Float32 value)
{
  return value;
}

template<>
template<>
constexpr Float32
Angle<AngleUnit::Grad>::to_grad<AngleUnit::Arcminute>(Float32 value)
{
  return value * 60.0f / 200.0f;
}

template<>
template<>
constexpr Float32
Angle<AngleUnit::Arcminute>::to_arcminute<AngleUnit::Radian>(Float32 value)
{
  return value * std::numbers::pi_v<Float32> / 180.0f / 60.0f;
}

template<>
template<>
constexpr Float32
Angle<AngleUnit::Arcminute>::to_arcminute<AngleUnit::Degree>(Float32 value)
{
  return value / 60.0f;
}

template<>
template<>
constexpr Float32
Angle<AngleUnit::Arcminute>::to_arcminute<AngleUnit::Grad>(Float32 value)
{
  return value * 200.0f / 60.0f;
}

template<>
template<>
constexpr Float32
Angle<AngleUnit::Arcminute>::to_arcminute<AngleUnit::Arcminute>(Float32 value)
{
  return value;
}

template class Angle<AngleUnit::Radian>;
template class Angle<AngleUnit::Degree>;
template class Angle<AngleUnit::Grad>;
template class Angle<AngleUnit::Arcminute>;

} // namespace setsugen
