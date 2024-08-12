#pragma once

namespace setsugen
{
template<Arithmetic T, int DimM, int DimN>
  requires (DimM > 0) && (DimN > 0)
Mat<T, DimM, DimN>::Mat()
{
  for (int i = 0; i < DimM; ++i)
  {
    for (int j = 0; j < DimN; ++j)
    {
      m_data[i * DimN + j] = T();
    }
  }
}

template<Arithmetic T, int DimM, int DimN>
  requires (DimM > 0) && (DimN > 0)
Mat<T, DimM, DimN>::Mat(const std::array<T, DimM * DimN>& data)
{
  std::copy(data.begin(), data.end(), m_data);
}

template<Arithmetic T, int DimM, int DimN>
  requires (DimM > 0) && (DimN > 0)
Mat<T, DimM, DimN>::Mat(const Mat& other) = default;

template<Arithmetic T, int DimM, int DimN>
  requires (DimM > 0) && (DimN > 0)
Mat<T, DimM, DimN>::Mat(Mat&& other) noexcept = default;


template<Arithmetic T, int DimM, int DimN>
  requires (DimM > 0) && (DimN > 0)
Mat<T, DimM, DimN>& Mat<T, DimM, DimN>::operator=(const Mat& other) = default;

template<Arithmetic T, int DimM, int DimN>
  requires (DimM > 0) && (DimN > 0)
Mat<T, DimM, DimN>& Mat<T, DimM, DimN>::operator=(Mat&& other) noexcept = default;

template<Arithmetic T, int DimM, int DimN>
  requires (DimM > 0) && (DimN > 0)
template<int SubDimM, int SubDimN>
  requires (SubDimM > 0) && (SubDimM < DimM) && (SubDimN > 0) && (SubDimN < DimN)
Mat<T, SubDimM, SubDimN>
Mat<T, DimM, DimN>::submatrix(int row, int col) const
{
  Mat<T, SubDimM, SubDimN> result;
  for (int i = 0; i < SubDimM; ++i)
  {
    for (int j = 0; j < SubDimN; ++j)
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

template<Arithmetic T, int DimM, int DimN>
  requires (DimM > 0) && (DimN > 0)
T*
Mat<T, DimM, DimN>::data()
{
  return m_data;
}

template<Arithmetic T, int DimM, int DimN>
  requires (DimM > 0) && (DimN > 0)
const T*
Mat<T, DimM, DimN>::data() const
{
  return m_data;
}

template<Arithmetic T, int DimM, int DimN>
  requires (DimM > 0) && (DimN > 0)
template<int DimP>
Mat<T, DimM, DimP>
Mat<T, DimM, DimN>::operator*(const Mat<T, DimN, DimP>& other) const
{
  Mat<T, DimM, DimP> result;
  for (int i = 0; i < DimM; ++i)
  {
    for (int j = 0; j < DimP; ++j)
    {
      for (int k = 0; k < DimN; ++k)
      {
        result.m_data[i * DimP + j] += m_data[i * DimN + k] * other.m_data[k * DimP + j];
      }
    }
  }
  return result;
}

template<Arithmetic T, int DimM, int DimN>
  requires (DimM > 0) && (DimN > 0)
Vec<T, DimM>
Mat<T, DimM, DimN>::operator*(const Vec<T, DimN>& vec) const
{
  Vec<T, DimM> result;
  for (int i = 0; i < DimM; ++i)
  {
    for (int j = 0; j < DimN; ++j)
    {
      result.get(i) += m_data[i * DimN + j] * vec.get(j);
    }
  }
  return result;
}

template<Arithmetic T, int DimM, int DimN>
  requires (DimM > 0) && (DimN > 0)
T&
Mat<T, DimM, DimN>::get(int row, int col)
{
  return m_data[col * DimN + row];
}

template<Arithmetic T, int DimM, int DimN>
  requires (DimM > 0) && (DimN > 0)
T
Mat<T, DimM, DimN>::get(int row, int col) const
{
  return m_data[col * DimN + row];
}

template<Arithmetic T, int DimM, int DimN>
  requires (DimM > 0) && (DimN > 0)
Mat<T, DimM, DimN>&
Mat<T, DimM, DimN>::operator+=(const Mat& other)
{
  for (int i = 0; i < DimM * DimN; ++i)
  {
    m_data[i] += other.m_data[i];
  }
  return *this;
}

template<Arithmetic T, int DimM, int DimN>
  requires (DimM > 0) && (DimN > 0)
Mat<T, DimM, DimN>&
Mat<T, DimM, DimN>::operator-=(const Mat& other)
{
  for (int i = 0; i < DimM * DimN; ++i)
  {
    m_data[i] -= other.m_data[i];
  }
  return *this;
}

template<Arithmetic T, int DimM, int DimN>
  requires (DimM > 0) && (DimN > 0)
Mat<T, DimM, DimN>&
Mat<T, DimM, DimN>::operator*=(T scalar)
{
  for (int i = 0; i < DimM * DimN; ++i)
  {
    m_data[i] *= scalar;
  }
  return *this;
}

template<Arithmetic T, int DimM, int DimN>
  requires (DimM > 0) && (DimN > 0)
Mat<T, DimM, DimN>&
Mat<T, DimM, DimN>::operator/=(T scalar)
{
  for (int i = 0; i < DimM * DimN; ++i)
  {
    m_data[i] /= scalar;
  }
  return *this;
}

template<Arithmetic T, int DimM, int DimN>
  requires (DimM > 0) && (DimN > 0)
bool
Mat<T, DimM, DimN>::operator==(const Mat& other) const
{
  for (int i = 0; i < DimM * DimN; ++i)
  {
    if (m_data[i] != other.m_data[i])
    {
      return false;
    }
  }
  return true;
}

template<Arithmetic T, int DimM, int DimN>
  requires (DimM > 0) && (DimN > 0)
bool
Mat<T, DimM, DimN>::operator!=(const Mat& other) const
{
  return !(*this == other);
}

template<Arithmetic T, int DimM, int DimN>
  requires (DimM > 0) && (DimN > 0)
T*
Mat<T, DimM, DimN>::begin()
{
  return m_data;
}

template<Arithmetic T, int DimM, int DimN>
  requires (DimM > 0) && (DimN > 0)
const T*
Mat<T, DimM, DimN>::begin() const
{
  return m_data;
}

template<Arithmetic T, int DimM, int DimN>
  requires (DimM > 0) && (DimN > 0)
T*
Mat<T, DimM, DimN>::end()
{
  return m_data + DimM * DimN;
}

template<Arithmetic T, int DimM, int DimN>
  requires (DimM > 0) && (DimN > 0)
const T*
Mat<T, DimM, DimN>::end() const
{
  return m_data + DimM * DimN;
}

template<Arithmetic T, int DimM, int DimN>
  requires (DimM > 0) && (DimN > 0)
Mat<T, DimN, DimM>
Mat<T, DimM, DimN>::transpose() const
{
  Mat<T, DimN, DimM> result;
  for (int i = 0; i < DimM; ++i)
  {
    for (int j = 0; j < DimN; ++j)
    {
      result.get(j, i) = m_data[i * DimN + j];
    }
  }
  return result;
}

template<Arithmetic T, int DimM, int DimN>
  requires (DimM > 0) && (DimN > 0)
template<int IDimM, int IDimN>
  requires (IDimM == DimN) && (IDimN == DimN) && (DimM == DimN)
T
Mat<T, DimM, DimN>::minor(int row, int col) const
{
  static_assert(DimM > 1, "Matrix must be at least 2x2 to calculate minor");

  Mat<T, DimM - 1, DimN - 1> submatrix;
  for (int i = 0; i < DimM - 1; ++i)
  {
    for (int j = 0; j < DimN - 1; ++j)
    {
      submatrix.get(i, j) = m_data[(i < row ? i : i + 1) * DimN + (j < col ? j : j + 1)];
    }
  }

  return submatrix.determinant();
}

template<Arithmetic T, int DimM, int DimN>
  requires (DimM > 0) && (DimN > 0)
template<int IDimM, int IDimN>
  requires (IDimM == DimN) && (IDimN == DimN) && (DimM == DimN)
T
Mat<T, DimM, DimN>::determinant()
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
    for (int i = 0; i < DimM; ++i)
    {
      result += m_data[i] * minor(0, i) * (i % 2 == 0 ? 1 : -1);
    }
    return result;
  }
}

template<Arithmetic T, int DimM, int DimN>
  requires (DimM > 0) && (DimN > 0)
template<int IDimM, int IDimN>
  requires (IDimM == DimM) && (IDimN == DimN)
Mat<T, IDimM, IDimN>
Mat<T, DimM, DimN>::identity()
{
  static_assert(DimM == DimN, "Identity matrix must be square");

  Mat<T, IDimM, IDimN> result;
  for (int i = 0; i < IDimM; ++i)
  {
    result.get(i, i) = T(1);
  }
  return result;
}

template<Arithmetic T, int DimM, int DimN>
  requires (DimM > 0) && (DimN > 0)
template<int IDimM, int IDimN>
  requires std::is_floating_point_v<T> && (IDimM == DimM) && (IDimN == DimN) && (IDimM == 4)
Mat<T, IDimM, IDimN>
Mat<T, DimM, DimN>::perspective(T fov, T aspect, T near, T far)
{
  Mat<T, IDimM, IDimN> result;

  T f              = T(1) / std::tan(fov * T(0.5) * std::numbers::pi_v<float> / T(180));
  result.get(0, 0) = f / aspect;
  result.get(1, 1) = f;
  result.get(2, 2) = (far + near) / (near - far);
  result.get(2, 3) = T(-1);
  result.get(3, 2) = (T(2) * far * near) / (near - far);
  result.get(3, 3) = T(0);

  return result;
}

template<Arithmetic T, int DimM, int DimN>
  requires (DimM > 0) && (DimN > 0)
template<int IDimM, int IDimN>
  requires std::is_floating_point_v<T> && (IDimM == DimM) && (IDimN == DimN) && (IDimM == 4)
Mat<T, IDimM, IDimN>
Mat<T, DimM, DimN>::orthographic(T left, T right, T bottom, T top, T near, T far)
{
  Mat<T, IDimM, IDimN> result;
  result.get(0, 0) = T(2) / (right - left);
  result.get(1, 1) = T(2) / (top - bottom);
  result.get(2, 2) = T(-2) / (far - near);
  result.get(0, 3) = -(right + left) / (right - left);
  result.get(1, 3) = -(top + bottom) / (top - bottom);
  result.get(2, 3) = -(far + near) / (far - near);
  result.get(3, 3) = T(1);
  return result;
}

template<Arithmetic T, int DimM, int DimN>
  requires (DimM > 0) && (DimN > 0)
template<int IDimM, int IDimN>
  requires std::is_arithmetic_v<T> && (IDimM == DimM) && (IDimN == DimN)
Mat<T, IDimM, IDimN>
Mat<T, DimM, DimN>::translation(const Vec<T, IDimM - 1>& translation)
{
  static_assert(DimM == DimN && DimM >= 3, "Translation matrix must be square and at least 3x3");

  Mat<T, IDimM, IDimN> result = identity();
  for (int i = 0; i < IDimM - 1; ++i)
  {
    result.get(i, IDimN - 1) = translation.get(i);
  }
  return result;
}

template<Arithmetic T, int DimM, int DimN>
  requires (DimM > 0) && (DimN > 0)
template<int IDimM, int IDimN>
  requires std::is_arithmetic_v<T> && (IDimM == DimM) && (IDimN == DimN)
Mat<T, IDimM, IDimN>
Mat<T, DimM, DimN>::rotation(const Vec<T, 3>& rotation)
{
  static_assert(DimM == DimN && DimM == 4, "Rotation matrix must be square and 4x4");

  Mat<T, IDimM, IDimN> result = identity();

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

template<Arithmetic T, int DimM, int DimN>
  requires (DimM > 0) && (DimN > 0)
template<int IDimM, int IDimN>
  requires std::is_arithmetic_v<T> && (IDimM == DimM) && (IDimN == DimN)
Mat<T, IDimM, IDimN>
Mat<T, DimM, DimN>::scale(const Vec<T, 3>& scale)
{
  static_assert(DimM == DimN && DimM == 4, "Scale matrix must be square and 4x4");

  Mat<T, IDimM, IDimN> result = identity();
  result.get(0, 0)            = scale.x();
  result.get(1, 1)            = scale.y();
  result.get(2, 2)            = scale.z();
  return result;
}

template<Arithmetic T, int DimM, int DimN>
  requires (DimM > 0) && (DimN > 0)
template<int IDimM, int IDimN>
  requires std::is_arithmetic_v<T> && (IDimM == DimM) && (IDimN == DimN)
Mat<T, IDimM, IDimN>
Mat<T, DimM, DimN>::look_at(const Vec<T, 3>& eye, const Vec<T, 3>& center, const Vec<T, 3>& up)
{
  static_assert(DimM == DimN && DimM == 4, "Look-at matrix must be square and 4x4");

  Mat<T, IDimM, IDimN> result = identity();
  // Calculate view matrix look at center from eye with up direction being up

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
}

#include "./matrix_typedef.inl"
