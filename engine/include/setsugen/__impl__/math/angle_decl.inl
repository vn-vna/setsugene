#pragma once

#include "math_fwd.inl"

namespace setsugen
{

template<AngleUnit Repr>
class Angle
{
public:
  Angle();

  Angle(Float32 value) noexcept;

  template<AngleUnit OtherUnit>
  Angle(const Angle<OtherUnit>& other);

  Angle(const Angle& other);

  Angle(Angle&& other) noexcept;

  template<AngleUnit OtherUnit>
  Angle& operator=(const Angle<OtherUnit>& other);

  inline Float32 value() const;

  template<AngleUnit OtherUnit>
  inline Float32 to() const;

  template<AngleUnit OtherUnit>
  inline static Angle from(Float32 value);

private:
  template<AngleUnit OtherUnit>
  inline constexpr static Float32 to_radian(Float32 value);

  template<AngleUnit OtherUnit>
  inline constexpr static Float32 to_degree(Float32 value);

  template<AngleUnit OtherUnit>
  inline constexpr static Float32 to_grad(Float32 value);

  template<AngleUnit OtherUnit>
  inline constexpr static Float32 to_arcminute(Float32 value);

  Float32 m_data;
};


} // namespace setsugen
