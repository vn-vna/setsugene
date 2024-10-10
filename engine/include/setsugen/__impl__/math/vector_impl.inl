#pragma once

#include "./vector_decl.inl"

namespace setsugen
{
template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
Vec<T, Dimension, Usage>::Vec()
{
  for (Int32 i = 0; i < Dimension; ++i)
  {
    m_data[i] = T();
  }
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
template<typename... Args>
  requires(sizeof...(Args) == Dimension) && (std::is_convertible_v<Args, T> && ...)
Vec<T, Dimension, Usage>::Vec(Args... args) : m_data{T(args)...}
{}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
Vec<T, Dimension, Usage>::Vec(const Vec& other) = default;

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
Vec<T, Dimension, Usage>::Vec(Vec&& other) noexcept = default;

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
Vec<T, Dimension, Usage>::~Vec() noexcept = default;

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
Vec<T, Dimension, Usage>& Vec<T, Dimension, Usage>::operator=(const Vec& other) = default;

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
Vec<T, Dimension, Usage>& Vec<T, Dimension, Usage>::operator=(Vec&& other) noexcept = default;

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
T&
Vec<T, Dimension, Usage>::get(Int32 index)
{
  if (index < 0 || index >= Dimension)
  {
    throw InvalidArgumentException("Index is out of range");
  }
  return m_data[index];
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
const T&
Vec<T, Dimension, Usage>::get(Int32 index) const
{
  if (index < 0 || index >= Dimension)
  {
    throw InvalidArgumentException("Index is out of range");
  }
  return m_data[index];
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
T&
Vec<T, Dimension, Usage>::x()
  requires(Dimension >= 1 && Usage == VectorUsage::Math)
{
  return m_data[0];
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
const T&
Vec<T, Dimension, Usage>::x() const
  requires(Dimension >= 1 && Usage == VectorUsage::Math)
{
  return m_data[0];
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
T&
Vec<T, Dimension, Usage>::y()
  requires(Dimension >= 2 && Usage == VectorUsage::Math)
{
  return m_data[1];
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
const T&
Vec<T, Dimension, Usage>::y() const
  requires(Dimension >= 2 && Usage == VectorUsage::Math)
{
  return m_data[1];
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
T&
Vec<T, Dimension, Usage>::z()
  requires(Dimension >= 3 && Usage == VectorUsage::Math)
{
  return m_data[2];
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
const T&
Vec<T, Dimension, Usage>::z() const
  requires(Dimension >= 3 && Usage == VectorUsage::Math)
{
  return m_data[2];
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
T&
Vec<T, Dimension, Usage>::w()
  requires(Dimension >= 4 && Usage == VectorUsage::Math)
{
  return m_data[3];
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
const T&
Vec<T, Dimension, Usage>::w() const
  requires(Dimension >= 4 && Usage == VectorUsage::Math)
{
  return m_data[3];
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
T&
Vec<T, Dimension, Usage>::width()
  requires(Dimension >= 1 && Usage == VectorUsage::Size)
{
  return m_data[0];
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
const T&
Vec<T, Dimension, Usage>::width() const
  requires(Dimension >= 1 && Usage == VectorUsage::Size)
{
  return m_data[0];
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
T&
Vec<T, Dimension, Usage>::height()
  requires(Dimension >= 2 && Usage == VectorUsage::Size)
{
  return m_data[1];
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
const T&
Vec<T, Dimension, Usage>::height() const
  requires(Dimension >= 2 && Usage == VectorUsage::Size)
{
  return m_data[1];
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
T&
Vec<T, Dimension, Usage>::depth()
  requires(Dimension >= 3 && Usage == VectorUsage::Size)
{
  return m_data[2];
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
const T&
Vec<T, Dimension, Usage>::depth() const
  requires(Dimension >= 3 && Usage == VectorUsage::Size)
{
  return m_data[2];
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
T&
Vec<T, Dimension, Usage>::r()
  requires(Dimension >= 1 && Usage == VectorUsage::Color)
{
  return m_data[0];
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
const T&
Vec<T, Dimension, Usage>::r() const
  requires(Dimension >= 1 && Usage == VectorUsage::Color)
{
  return m_data[0];
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
T&
Vec<T, Dimension, Usage>::g()
  requires(Dimension >= 2 && Usage == VectorUsage::Color)
{
  return m_data[1];
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
const T&
Vec<T, Dimension, Usage>::g() const
  requires(Dimension >= 2 && Usage == VectorUsage::Color)
{
  return m_data[1];
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
T&
Vec<T, Dimension, Usage>::b()
  requires(Dimension >= 3 && Usage == VectorUsage::Color)
{
  return m_data[2];
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
const T&
Vec<T, Dimension, Usage>::b() const
  requires(Dimension >= 3 && Usage == VectorUsage::Color)
{
  return m_data[2];
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
T&
Vec<T, Dimension, Usage>::a()
  requires(Dimension >= 4 && Usage == VectorUsage::Color)
{
  return m_data[3];
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
const T&
Vec<T, Dimension, Usage>::a() const
  requires(Dimension >= 4 && Usage == VectorUsage::Color)
{
  return m_data[3];
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
T*
Vec<T, Dimension, Usage>::data()
{
  return m_data.data();
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
const T*
Vec<T, Dimension, Usage>::data() const
{
  return m_data.data();
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
T
Vec<T, Dimension, Usage>::dot(const Vec& other) const
{
  T result = T();
  for (Int32 i = 0; i < Dimension; ++i)
  {
    result += m_data[i] * other.m_data[i];
  }
  return result;
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
Vec<T, Dimension, Usage>
Vec<T, Dimension, Usage>::cross(const Vec& other) const
  requires(Dimension == 3)
{
  // clang-format off
  return Vec({
    m_data[1] * other.m_data[2] - m_data[2] * other.m_data[1],
    m_data[2] * other.m_data[0] - m_data[0] * other.m_data[2],
    m_data[0] * other.m_data[1] - m_data[1] * other.m_data[0]
  });
  // clang-format on
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
T
Vec<T, Dimension, Usage>::length() const
{
  return (T) std::sqrt(dot(*this));
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
Vec<T, Dimension, Usage>
Vec<T, Dimension, Usage>::normalize() const
  requires(FloatingPointType<T>)
{
  Vec result = *this;
  T   len    = length();
  if (len == T(0))
  {
    throw InvalidOperationException("Cannot normalize a zero vector");
  }

  for (Int32 i = 0; i < Dimension; ++i)
  {
    result.m_data[i] /= len;
  }

  return result;
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
Vec<T, Dimension, Usage>
Vec<T, Dimension, Usage>::rotate(const Quaternion<T>& rotation) const
{
  // TODO: Vec rotate(const Quaternion<T>& rotation) const
  throw NotImplementedException("Vec::rotate(const Quaternion)");
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
typename Vec<T, Dimension, Usage>::Iter
Vec<T, Dimension, Usage>::begin()
{
  return m_data.begin();
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
typename Vec<T, Dimension, Usage>::CIter
Vec<T, Dimension, Usage>::begin() const
{
  return m_data.begin();
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
typename Vec<T, Dimension, Usage>::Iter
Vec<T, Dimension, Usage>::end()
{
  return m_data.end();
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
typename Vec<T, Dimension, Usage>::CIter
Vec<T, Dimension, Usage>::end() const
{
  return m_data.end();
}
} // namespace setsugen
