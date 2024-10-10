#pragma once

#include "angle_decl.inl"

#include <utility>

namespace setsugen
{

template<AngleUnit Unit>
Angle<Unit>::Angle() : m_data(0.0f)
{}

template<AngleUnit Unit>
Angle<Unit>::Angle(Float32 value) noexcept : m_data(value)
{}

template<AngleUnit Unit>
Angle<Unit>::Angle(const Angle& other) : m_data(other.m_data)
{}

template<AngleUnit Unit>
template<AngleUnit OtherUnit>
Angle<Unit>::Angle(const Angle<OtherUnit>& other) : m_data(other.value())
{
  if constexpr (Unit == AngleUnit::Arcminute)
  {
    m_data = to_arcminute<OtherUnit>(other.value());
  }

  if constexpr (Unit == AngleUnit::Degree)
  {
    m_data = to_degree<OtherUnit>(other.value());
  }

  if constexpr (Unit == AngleUnit::Grad)
  {
    m_data = to_grad<OtherUnit>(other.value());
  }

  if constexpr (Unit == AngleUnit::Radian)
  {
    m_data = to_radian<OtherUnit>(other.value());
  }
}

template<AngleUnit Unit>
Angle<Unit>::Angle(Angle&& other) noexcept : m_data(std::exchange(other.m_data, 0.0f))
{}

template<AngleUnit Unit>
template<AngleUnit OtherUnit>
Angle<Unit>&
Angle<Unit>::operator=(const Angle<OtherUnit>& other)
{
  m_data = other.value();
  if constexpr (Unit == AngleUnit::Arcminute)
  {
    m_data = to_arcminute<OtherUnit>(other.value());
  }

  if constexpr (Unit == AngleUnit::Degree)
  {
    m_data = to_degree<OtherUnit>(other.value());
  }

  if constexpr (Unit == AngleUnit::Grad)
  {
    m_data = to_grad<OtherUnit>(other.value());
  }

  if constexpr (Unit == AngleUnit::Radian)
  {
    m_data = to_radian<OtherUnit>(other.value());
  }

  return *this;
}

template<AngleUnit Unit>
Float32
Angle<Unit>::value() const
{
  return m_data;
}

template<AngleUnit Unit>
template<AngleUnit OtherUnit>
Float32
Angle<Unit>::to() const
{
  if constexpr (Unit == OtherUnit)
  {
    return m_data;
  }

  if constexpr (Unit == AngleUnit::Arcminute)
  {
    return to_arcminute<OtherUnit>(m_data);
  }

  if constexpr (Unit == AngleUnit::Degree)
  {
    return to_degree<OtherUnit>(m_data);
  }

  if constexpr (Unit == AngleUnit::Grad)
  {
    return to_grad<OtherUnit>(m_data);
  }

  if constexpr (Unit == AngleUnit::Radian)
  {
    return to_radian<OtherUnit>(m_data);
  }
}

template<AngleUnit Unit>
template<AngleUnit OtherUnit>
Angle<Unit>
Angle<Unit>::from(Float32 value)
{
  return Angle<Unit>(value);
}


} // namespace setsugen
