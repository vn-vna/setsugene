#pragma once

namespace setsugen
{
template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires(Dimension > 0)
Vec<T, Dimension, Usage>::Vec()
{
  for (int i = 0; i < Dimension; ++i)
  {
    m_data[i] = T();
  }
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
template<typename... Args>
  requires (sizeof...(Args) == Dimension) && (std::is_convertible_v<Args, T> && ...)
Vec<T, Dimension, Usage>::Vec(Args... args)
  : m_data{std::forward<Args>(args)...}
{}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
Vec<T, Dimension, Usage>::Vec(const Vec& other) = default;

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
Vec<T, Dimension, Usage>::Vec(Vec&& other) noexcept = default;

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
Vec<T, Dimension, Usage>::~Vec() noexcept = default;

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
Vec<T, Dimension, Usage>& Vec<T, Dimension, Usage>::operator=(const Vec& other) = default;

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
Vec<T, Dimension, Usage>& Vec<T, Dimension, Usage>::operator=(Vec&& other) noexcept = default;

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
T&
Vec<T, Dimension, Usage>::get(int index)
{
  if (index < 0 || index >= Dimension)
  {
    throw InvalidArgumentException("Index is out of range");
  }
  return m_data[index];
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
const T&
Vec<T, Dimension, Usage>::get(int index) const
{
  if (index < 0 || index >= Dimension)
  {
    throw InvalidArgumentException("Index is out of range");
  }
  return m_data[index];
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
template<int N>
  requires (N == 1 && Dimension >= 1 && Usage == VectorUsage::Math)
T&
Vec<T, Dimension, Usage>::x()
{
  return m_data[N - 1];
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
template<int N>
  requires (N == 1 && Dimension >= 1 && Usage == VectorUsage::Math)
const T&
Vec<T, Dimension, Usage>::x() const
{
  return m_data[N - 1];
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
template<int N>
  requires (N == 2 && Dimension >= 2 && Usage == VectorUsage::Math)
T&
Vec<T, Dimension, Usage>::y()
{
  return m_data[N - 1];
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
template<int N>
  requires (N == 2 && Dimension >= 2 && Usage == VectorUsage::Math)
const T&
Vec<T, Dimension, Usage>::y() const
{
  return m_data[N - 1];
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
template<int N>
  requires (N == 3 && Dimension >= 3 && Usage == VectorUsage::Math)
T&
Vec<T, Dimension, Usage>::z()
{
  return m_data[N - 1];
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
template<int N>
  requires (N == 3 && Dimension >= 3 && Usage == VectorUsage::Math)
const T&
Vec<T, Dimension, Usage>::z() const
{
  return m_data[N - 1];
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
template<int N>
  requires (N == 4 && Dimension >= 4 && Usage == VectorUsage::Math)
T&
Vec<T, Dimension, Usage>::w()
{
  return m_data[N - 1];
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
template<int N>
  requires (N == 4 && Dimension >= 4 && Usage == VectorUsage::Math)
const T&
Vec<T, Dimension, Usage>::w() const
{
  return m_data[N - 1];
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
template<int N>
  requires (N == 1 && Dimension >= 1 && Usage == VectorUsage::Size)
T&
Vec<T, Dimension, Usage>::width()
{
  return m_data[N - 1];
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
template<int N>
  requires (N == 1 && Dimension >= 1 && Usage == VectorUsage::Size)
const T&
Vec<T, Dimension, Usage>::width() const
{
  return m_data[N - 1];
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
template<int N>
  requires (N == 2 && Dimension >= 2 && Usage == VectorUsage::Size)
T&
Vec<T, Dimension, Usage>::height()
{
  return m_data[N - 1];
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
template<int N>
  requires (N == 2 && Dimension >= 2 && Usage == VectorUsage::Size)
const T&
Vec<T, Dimension, Usage>::height() const
{
  return m_data[N - 1];
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
template<int N>
  requires (N == 3 && Dimension >= 3 && Usage == VectorUsage::Size)
T&
Vec<T, Dimension, Usage>::depth()
{
  return m_data[N - 1];
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
template<int N>
  requires (N == 3 && Dimension >= 3 && Usage == VectorUsage::Size)
const T&
Vec<T, Dimension, Usage>::depth() const
{
  return m_data[N - 1];
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
template<int N>
  requires (N == 1 && Dimension >= 1 && Usage == VectorUsage::Color)
T&
Vec<T, Dimension, Usage>::r()
{
  return m_data[N - 1];
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
template<int N>
  requires (N == 1 && Dimension >= 1 && Usage == VectorUsage::Color)
const T&
Vec<T, Dimension, Usage>::r() const
{
  return m_data[N - 1];
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
template<int N>
  requires (N == 2 && Dimension >= 2 && Usage == VectorUsage::Color)
T&
Vec<T, Dimension, Usage>::g()
{
  return m_data[N - 1];
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
template<int N>
  requires (N == 2 && Dimension >= 2 && Usage == VectorUsage::Color)
const T&
Vec<T, Dimension, Usage>::g() const
{
  return m_data[N - 1];
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
template<int N>
  requires (N == 3 && Dimension >= 3 && Usage == VectorUsage::Color)
T&
Vec<T, Dimension, Usage>::b()
{
  return m_data[N - 1];
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
template<int N>
  requires (N == 3 && Dimension >= 3 && Usage == VectorUsage::Color)
const T&
Vec<T, Dimension, Usage>::b() const
{
  return m_data[N - 1];
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
template<int N>
  requires (N == 4 && Dimension >= 4 && Usage == VectorUsage::Color)
T&
Vec<T, Dimension, Usage>::a()
{
  return m_data[N - 1];
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
template<int N>
  requires (N == 4 && Dimension >= 4 && Usage == VectorUsage::Color)
const T&
Vec<T, Dimension, Usage>::a() const
{
  return m_data[N - 1];
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
T*
Vec<T, Dimension, Usage>::data()
{
  return m_data.data();
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
const T*
Vec<T, Dimension, Usage>::data() const
{
  return m_data.data();
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
T
Vec<T, Dimension, Usage>::dot(const Vec& other) const
{
  T result = T();
  for (int i = 0; i < Dimension; ++i)
  {
    result += m_data[i] * other.m_data[i];
  }
  return result;
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
template<int N>
  requires (N == Dimension) && (Dimension == 3)
Vec<T, Dimension, Usage>
Vec<T, Dimension, Usage>::cross(const Vec& other) const
{
  // clang-format off
  return Vec({
    m_data[1] * other.m_data[2] - m_data[2] * other.m_data[1],
    m_data[2] * other.m_data[0] - m_data[0] * other.m_data[2],
    m_data[0] * other.m_data[1] - m_data[1] * other.m_data[0]
  });
  // clang-format on
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
T
Vec<T, Dimension, Usage>::length() const
{
  return std::sqrt(dot(*this));
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
template<typename U>
  requires std::is_same_v<U, T> && std::is_floating_point_v<U>
Vec<T, Dimension, Usage>
Vec<T, Dimension, Usage>::normalize() const
{
  Vec result = *this;
  T   len    = length();
  if (len == T(0))
  {
    throw InvalidOperationException("Cannot normalize a zero vector");
  }

  for (int i = 0; i < Dimension; ++i)
  {
    result.m_data[i] /= len;
  }

  return result;
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
Vec<T, Dimension, Usage>
Vec<T, Dimension, Usage>::rotate(const Quaternion<T>& rotation) const
{
  // TODO: Vec rotate(const Quaternion<T>& rotation) const
  throw NotImplementedException("Vec::rotate(const Quaternion)");
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
Vec<T, Dimension, Usage>&
Vec<T, Dimension, Usage>::operator+=(const Vec& other)
{
  for (int i = 0; i < Dimension; ++i)
  {
    m_data[i] += other.m_data[i];
  }
  return *this;
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
Vec<T, Dimension, Usage>&
Vec<T, Dimension, Usage>::operator-=(const Vec& other)
{
  for (int i = 0; i < Dimension; ++i)
  {
    m_data[i] -= other.m_data[i];
  }
  return *this;
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
Vec<T, Dimension, Usage>&
Vec<T, Dimension, Usage>::operator*=(T scalar)
{
  for (int i = 0; i < Dimension; ++i)
  {
    m_data[i] *= scalar;
  }
  return *this;
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
Vec<T, Dimension, Usage>&
Vec<T, Dimension, Usage>::operator/=(T scalar)
{
  for (int i = 0; i < Dimension; ++i)
  {
    m_data[i] /= scalar;
  }
  return *this;
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
bool
Vec<T, Dimension, Usage>::operator==(const Vec& other) const
{
  for (int i = 0; i < Dimension; ++i)
  {
    if (m_data[i] != other.m_data[i])
    {
      return false;
    }
  }
  return true;
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
bool
Vec<T, Dimension, Usage>::operator!=(const Vec& other) const
{
  return !(*this == other);
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
typename Vec<T, Dimension, Usage>::Iter
Vec<T, Dimension, Usage>::begin()
{
  return m_data.begin();
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
typename Vec<T, Dimension, Usage>::CIter
Vec<T, Dimension, Usage>::begin() const
{
  return m_data.begin();
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
typename Vec<T, Dimension, Usage>::Iter
Vec<T, Dimension, Usage>::end()
{
  return m_data.end();
}

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires (Dimension > 0)
typename Vec<T, Dimension, Usage>::CIter
Vec<T, Dimension, Usage>::end() const
{
  return m_data.end();
}
}

#include "./vector_typedef.inl"
