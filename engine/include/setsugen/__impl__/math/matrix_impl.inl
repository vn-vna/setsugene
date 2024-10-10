#pragma once

#include "./matrix_decl.inl"

namespace setsugen
{

template<Arithmetic T, unsigned DimM, unsigned DimN>
Mat<T, DimM, DimN>::Mat()
{
  for (Int32 i = 0; i < DimM; ++i)
  {
    for (Int32 j = 0; j < DimN; ++j)
    {
      m_data[i * DimN + j] = T();
    }
  }
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
Mat<T, DimM, DimN>::Mat(const Array<T, DimM * DimN>& data)
{
  std::copy(data.begin(), data.end(), m_data.data());
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
Mat<T, DimM, DimN>::Mat(const Mat& other) : m_data(other.m_data)
{}

template<Arithmetic T, unsigned DimM, unsigned DimN>
Mat<T, DimM, DimN>::Mat(Mat&& other) noexcept : m_data(std::move(other.m_data))
{}

template<Arithmetic T, unsigned DimM, unsigned DimN>
Mat<T, DimM, DimN>&
Mat<T, DimM, DimN>::operator=(const Mat& other)
{
  m_data = other.m_data;
  return *this;
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
Mat<T, DimM, DimN>&
Mat<T, DimM, DimN>::operator=(Mat&& other) noexcept
{
  m_data = std::move(other.m_data);
  return *this;
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
template<unsigned SubDimM, unsigned SubDimN>
  requires((SubDimM < DimM) && (SubDimN < DimN))
Mat<T, SubDimM, SubDimN>
Mat<T, DimM, DimN>::submatrix(Int32 row, Int32 col) const
{
  Mat<T, SubDimM, SubDimN> result;
  for (Int32 i = 0; i < SubDimM; ++i)
  {
    for (Int32 j = 0; j < SubDimN; ++j)
    {
      if (row + i >= DimM || col + j >= DimN)
      {
        throw InvalidArgumentException("Submatrix is out of range");
      }

      result.get(i, j) = m_data[(row + i) * DimN + (col + j)];
    }
  }
  return result;
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
T*
Mat<T, DimM, DimN>::data()
{
  return m_data.data();
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
const T*
Mat<T, DimM, DimN>::data() const
{
  return m_data.data();
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
T&
Mat<T, DimM, DimN>::get(Int32 row, Int32 col)
{
  return m_data[col * DimN + row];
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
T
Mat<T, DimM, DimN>::get(Int32 row, Int32 col) const
{
  return m_data[col * DimN + row];
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
Mat<T, DimM, DimN>&
Mat<T, DimM, DimN>::operator+=(const Mat& other)
{
  for (Int32 i = 0; i < DimM * DimN; ++i)
  {
    m_data[i] += other.m_data[i];
  }
  return *this;
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
Mat<T, DimM, DimN>&
Mat<T, DimM, DimN>::operator-=(const Mat& other)
{
  for (Int32 i = 0; i < DimM * DimN; ++i)
  {
    m_data[i] -= other.m_data[i];
  }
  return *this;
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
Mat<T, DimM, DimN>&
Mat<T, DimM, DimN>::operator*=(T scalar)
{
  for (Int32 i = 0; i < DimM * DimN; ++i)
  {
    m_data[i] *= scalar;
  }
  return *this;
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
Mat<T, DimM, DimN>&
Mat<T, DimM, DimN>::operator/=(T scalar)
{
  for (Int32 i = 0; i < DimM * DimN; ++i)
  {
    m_data[i] /= scalar;
  }
  return *this;
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
Bool
Mat<T, DimM, DimN>::operator==(const Mat& other) const
{
  for (Int32 i = 0; i < DimM * DimN; ++i)
  {
    if (m_data[i] != other.m_data[i])
    {
      return false;
    }
  }
  return true;
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
Bool
Mat<T, DimM, DimN>::operator!=(const Mat& other) const
{
  return !(*this == other);
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
T*
Mat<T, DimM, DimN>::begin()
{
  return m_data.data();
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
const T*
Mat<T, DimM, DimN>::begin() const
{
  return m_data.data();
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
T*
Mat<T, DimM, DimN>::end()
{
  return m_data.data() + DimM * DimN;
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
const T*
Mat<T, DimM, DimN>::end() const
{
  return m_data.data() + DimM * DimN;
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
Mat<T, DimN, DimM>
Mat<T, DimM, DimN>::transpose() const
{
  Mat<T, DimN, DimM> result;
  for (Int32 i = 0; i < DimM; ++i)
  {
    for (Int32 j = 0; j < DimN; ++j)
    {
      result.get(j, i) = m_data[i * DimN + j];
    }
  }
  return result;
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
T
Mat<T, DimM, DimN>::minor(Int32 row, Int32 col) const
  requires((DimM == DimN) && (DimM > 1))
{
  Mat<T, DimM - 1, DimN - 1> submatrix;
  for (Int32 i = 0; i < DimM - 1; ++i)
  {
    for (Int32 j = 0; j < DimN - 1; ++j)
    {
      submatrix.get(i, j) = m_data[(i < row ? i : i + 1) * DimN + (j < col ? j : j + 1)];
    }
  }

  return submatrix.determinant();
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
T
Mat<T, DimM, DimN>::determinant() const
  requires(DimM == DimN)
{
  if constexpr (DimM == 1)
  {
    return m_data[0];
  }
  else if constexpr (DimM == 2)
  {
    return m_data[0] * m_data[3] - m_data[1] * m_data[2];
  }
  else if constexpr (DimM == 3)
  {
    return get(0, 0) * (get(1, 1) * get(2, 2) - get(1, 2) * get(2, 1)) -
           get(0, 1) * (get(1, 0) * get(2, 2) - get(1, 2) * get(2, 0)) +
           get(0, 2) * (get(1, 0) * get(2, 1) - get(1, 1) * get(2, 0));
  }
  else
  {
    T result = T();
    for (Int32 i = 0; i < DimM; ++i)
    {
      result += m_data[i] * minor(0, i) * (i % 2 == 0 ? 1 : -1);
    }
    return result;
  }
}


template<Arithmetic T, unsigned DimM, unsigned DimN>
Mat<T, DimM, DimN>
Mat<T, DimM, DimN>::identity()
  requires(DimM == DimN)
{
  Mat<T, DimM, DimN> result;
  for (Int32 i = 0; i < DimM; ++i)
  {
    result.get(i, i) = T(1);
  }
  return result;
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
Mat<T, DimM, DimN>
Mat<T, DimM, DimN>::perspective(T fov, T aspect, T near, T far)
  requires(FloatingPointType<T> && (DimM == 4) && (DimN == 4))
{
  Mat<T, DimM, DimN> result;

  T f = T(1) / std::tan(fov * T(0.5) * std::numbers::pi_v<Float32> / T(180));

  result.get(0, 0) = f / aspect;
  result.get(1, 1) = f;
  result.get(2, 2) = (far + near) / (near - far);
  result.get(2, 3) = T(-1);
  result.get(3, 2) = (T(2) * far * near) / (near - far);
  result.get(3, 3) = T(0);

  return result;
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
Mat<T, DimM, DimN>
Mat<T, DimM, DimN>::orthographic(T left, T right, T bottom, T top, T near, T far)
  requires(FloatingPointType<T> && (DimM == 4) && (DimN == 4))
{
  Mat<T, DimM, DimN> result;
  result.get(0, 0) = T(2) / (right - left);
  result.get(1, 1) = T(2) / (top - bottom);
  result.get(2, 2) = T(-2) / (far - near);
  result.get(0, 3) = -(right + left) / (right - left);
  result.get(1, 3) = -(top + bottom) / (top - bottom);
  result.get(2, 3) = -(far + near) / (far - near);
  result.get(3, 3) = T(1);
  return result;
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
Mat<T, DimM, DimN>
Mat<T, DimM, DimN>::translation(const Vec<T, 3>& translation)
  requires(FloatingPointType<T> && (DimM == 4) && (DimN == 4))
{
  Mat<T, DimM, DimN> result = identity();
  for (Int32 i = 0; i < DimM - 1; ++i)
  {
    result.get(i, DimN - 1) = translation.get(i);
  }
  return result;
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
Mat<T, DimM, DimN>
Mat<T, DimM, DimN>::translation(const Vec<T, 2>& translation)
  requires(FloatingPointType<T> && (DimM == 3) && (DimN == 3))
{
  Mat<T, DimM, DimN> result = identity();
  for (Int32 i = 0; i < DimM - 1; ++i)
  {
    result.get(i, DimN - 1) = translation.get(i);
  }
  return result;
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
Mat<T, DimM, DimN>
Mat<T, DimM, DimN>::rotation(const Vec<T, 3>& rotation)
  requires(FloatingPointType<T> && (DimM == 4) && (DimN == 4))
{
  Mat<T, DimM, DimN> result = identity();

  T rx  = rotation.x();
  T crx = std::cos(rx);
  T srx = std::sin(rx);
  T ry  = rotation.y();
  T cry = std::cos(ry);
  T sry = std::sin(ry);
  T rz  = rotation.z();
  T crz = std::cos(rz);
  T srz = std::sin(rz);

  result.get(0, 0) = crx * cry;
  result.get(0, 1) = crx * sry * srz - srx * crz;
  result.get(0, 2) = crx * sry * crz + srx * srz;

  result.get(1, 0) = srx * cry;
  result.get(1, 1) = srx * sry * srz + crx * crz;
  result.get(1, 2) = srx * sry * crz - crx * srz;

  result.get(2, 0) = -sry;
  result.get(2, 1) = cry * srz;
  result.get(2, 2) = cry * crz;

  return result;
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
Mat<T, DimM, DimN>
Mat<T, DimM, DimN>::rotation(const Vec<T, 2>& rotation)
  requires(FloatingPointType<T> && (DimM == 3) && (DimN == 3))
{
  Mat<T, DimM, DimN> result = identity();

  T rx  = rotation.x();
  T crx = std::cos(rx);
  T srx = std::sin(rx);
  T ry  = rotation.y();
  T cry = std::cos(ry);
  T sry = std::sin(ry);

  result.get(0, 0) = crx;
  result.get(0, 1) = -srx;
  result.get(1, 0) = srx;
  result.get(1, 1) = crx;

  return result;
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
Mat<T, DimM, DimN>
Mat<T, DimM, DimN>::scale(const Vec<T, 3>& scale)
  requires(FloatingPointType<T> && (DimM == 4) && (DimN == 4))
{
  Mat<T, DimM, DimN> result = identity();
  result.get(0, 0)          = scale.x();
  result.get(1, 1)          = scale.y();
  result.get(2, 2)          = scale.z();
  return result;
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
Mat<T, DimM, DimN>
Mat<T, DimM, DimN>::scale(const Vec<T, 2>& scale)
  requires(FloatingPointType<T> && (DimM == 3) && (DimN == 3))
{
  Mat<T, DimM, DimN> result = identity();
  result.get(0, 0)          = scale.x();
  result.get(1, 1)          = scale.y();
  return result;
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
Mat<T, DimM, DimN>
Mat<T, DimM, DimN>::look_at(const Vec<T, 3>& eye, const Vec<T, 3>& center, const Vec<T, 3>& up)
  requires(FloatingPointType<T> && (DimM == 4) && (DimN == 4))
{
  Mat<T, DimM, DimN> result = identity();

  auto fwd  = (center - eye).normalize();
  auto side = fwd.cross(up).normalize();
  auto upv  = side.cross(fwd);

  result.get(0, 0) = side.x();
  result.get(0, 1) = side.y();
  result.get(0, 2) = side.z();

  result.get(1, 0) = upv.x();
  result.get(1, 1) = upv.y();
  result.get(1, 2) = upv.z();

  result.get(2, 0) = -fwd.x();
  result.get(2, 1) = -fwd.y();
  result.get(2, 2) = -fwd.z();

  result.get(0, 3) = -side.dot(eye);
  result.get(1, 3) = -upv.dot(eye);
  result.get(2, 3) = fwd.dot(eye);

  return result;
}

} // namespace setsugen
