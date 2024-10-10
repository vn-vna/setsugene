#pragma once

#include "math_fwd.inl"

namespace setsugen
{

template<Arithmetic T>
class Quaternion
{
public:
  Quaternion() : m_data{0, 0, 0, 1}
  {}

  template<typename... Args>
    requires(sizeof...(Args) == 4) && (std::is_convertible_v<Args, T> && ...)
  Quaternion(Args... args) : m_data{std::forward<Args>(args)...}
  {}

  Quaternion(const Quaternion& other) = default;
  Quaternion(Quaternion&& other)      = default;

  ~Quaternion() noexcept = default;

  Quaternion& operator=(const Quaternion& other)     = default;
  Quaternion& operator=(Quaternion&& other) noexcept = default;

  T& x()
  {
    return m_data[0];
  }

  T x() const
  {
    return m_data[0];
  }

  T& y()
  {
    return m_data[1];
  }

  T y() const
  {
    return m_data[1];
  }

  T& z()
  {
    return m_data[2];
  }

  T z() const
  {
    return m_data[2];
  }


  T& w()
  {
    return m_data[3];
  }

  T w() const
  {
    return m_data[3];
  }

  Quaternion operator*(const Quaternion& other) const
  {
    return Quaternion(w() * other.x() + x() * other.w() + y() * other.z() - z() * other.y(),
                      w() * other.y() - x() * other.z() + y() * other.w() + z() * other.x(),
                      w() * other.z() + x() * other.y() - y() * other.x() + z() * other.w(),
                      w() * other.w() - x() * other.x() - y() * other.y() - z() * other.z());
  }

  Quaternion operator*(T scalar) const
  {
    return Quaternion(x() * scalar, y() * scalar, z() * scalar, w() * scalar);
  }

  Quaternion operator/(T scalar) const
  {
    return Quaternion(x() / scalar, y() / scalar, z() / scalar, w() / scalar);
  }

  Quaternion operator+(const Quaternion& other) const
  {
    return Quaternion(x() + other.x(), y() + other.y(), z() + other.z(), w() + other.w());
  }

  Quaternion operator-(const Quaternion& other) const
  {
    return Quaternion(x() - other.x(), y() - other.y(), z() - other.z(), w() - other.w());
  }

  Quaternion operator-() const
  {
    return Quaternion(-x(), -y(), -z(), -w());
  }

  Bool operator==(const Quaternion& other) const
  {
    return x() == other.x() && y() == other.y() && z() == other.z() && w() == other.w();
  }

  Bool operator!=(const Quaternion& other) const
  {
    return !(*this == other);
  }

  Quaternion normalize() const
  {
    T length = std::sqrt(x() * x() + y() * y() + z() * z() + w() * w());
    return Quaternion(x() / length, y() / length, z() / length, w() / length);
  }

  Vec<T, 3> get_euler_angles() const
  {
    Vec<T, 3> result;
    T         sinr_cosp = T(2) * (w() * x() + y() * z());
    T         cosr_cosp = T(1) - T(2) * (x() * x() + y() * y());
    result.x()          = std::atan2(sinr_cosp, cosr_cosp);

    T sinp = T(2) * (w() * y() - z() * x());
    if (std::abs(sinp) >= T(1))
    {
      result.y() = std::copysign(std::numbers::pi_v<T> / T(2), sinp);
    }
    else
    {
      result.y() = std::asin(sinp);
    }

    T siny_cosp = T(2) * (w() * z() + x() * y());
    T cosy_cosp = T(1) - T(2) * (y() * y() + z() * z());
    result.z()  = std::atan2(siny_cosp, cosy_cosp);

    return result;
  }

  Vec<T, 3> get_rotation_axis() const
  {
    T s = std::sqrt(1 - w() * w());
    if (s < std::numeric_limits<T>::epsilon())
    {
      return Vec<T, 3>(1, 0, 0);
    }
    return Vec<T, 3>(x() / s, y() / s, z() / s);
  }

  T get_rotation_angle() const
  {
    return std::acos(w()) * 2;
  }

private:
  Array<T, 4> m_data;
};

} // namespace setsugen
