#pragma once

#include <setsugen/pch.h>

// Setsugen headers
#include <setsugen/exception.h>
#include <setsugen/format.h>

// C++ standard library
#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <type_traits>

namespace setsugen
{

constexpr const Int32 NormalVector    = 0;
constexpr const Int32 DimensionVector = 1;
constexpr const Int32 ColorVector     = 2;

template <typename T, Int32 Dimension, Int32 Usage = NormalVector>
class Vec
{
  static_assert(std::is_arithmetic_v<T>, "Vec can only be used with arithmetic types");
  static_assert(Dimension > 0, "Vec dimension must be greater than 0");

public:
  /// @brief Default constructor - Creates a Vec with all elements initialized to 0
  Vec()
  {
    for (Int32 i = 0; i < Dimension; ++i)
    {
      m_data[i] = T();
    }
  }

  template <typename... Args, typename = std::enable_if_t<(sizeof...(Args) == Dimension)>>
  Vec(Args... args)
      : m_data {args...}
  {}

  Vec(const Vec& other) = default;

  Vec(Vec&& other) = default;

  ~Vec() = default;

  Vec& operator=(const Vec& other) = default;
  Vec& operator=(Vec&& other)      = default;

  /// @brief Access an element of the Vec
  /// @param index Element index (0-based)
  /// @return Value of the element at the given index
  T& get(Int32 index)
  {
    if (index < 0 || index >= Dimension)
    {
      throw InvalidArgumentException("Index is out of range");
    }
    return m_data[index];
  }

  /// @brief Access an element of the Vec
  /// @param index Element index (0-based)
  /// @return Value of the element at the given index
  const T& get(Int32 index) const
  {
    if (index < 0 || index >= Dimension)
    {
      throw InvalidArgumentException("Index is out of range");
    }
    return m_data[index];
  }

#pragma region NormalVectorComponents

  template <Int32 N = 1>
  std::enable_if_t<(N == 1 && Dimension >= 1 && Usage == 0), T&> x()
  {
    return m_data[0];
  }

  template <Int32 N = 1>
  std::enable_if_t<(N == 1 && Dimension >= 1 && Usage == 0), const T&> x() const
  {
    return m_data[0];
  }

  template <Int32 N = 2>
  std::enable_if_t<(N == 2 && Dimension >= 2 && Usage == 0), T&> y()
  {
    return m_data[1];
  }

  template <Int32 N = 2>
  std::enable_if_t<(N == 2 && Dimension >= 2 && Usage == 0), const T&> y() const
  {
    return m_data[1];
  }

  template <Int32 N = 3>
  std::enable_if_t<(N == 3 && Dimension >= 3 && Usage == 0), T&> z()
  {
    return m_data[2];
  }

  template <Int32 N = 3>
  std::enable_if_t<(N == 3 && Dimension >= 3 && Usage == 0), const T&> z() const
  {
    return m_data[2];
  }

  template <Int32 N = 4>
  std::enable_if_t<(N == 4 && Dimension >= 4 && Usage == 0), T&> w()
  {
    return m_data[3];
  }

  template <Int32 N = 4>
  std::enable_if_t<(N == 4 && Dimension >= 4 && Usage == 0), const T&> w() const
  {
    return m_data[3];
  }

#pragma endregion

#pragma region DimensionVectorComponents

  template <Int32 N = 1>
  std::enable_if_t<(N == 1 && Dimension >= 1 && Usage == 1), T&> width()
  {
    return m_data[0];
  }

  template <Int32 N = 1>
  std::enable_if_t<(N == 1 && Dimension >= 1 && Usage == 1), const T&> width() const
  {
    return m_data[0];
  }

  template <Int32 N = 2>
  std::enable_if_t<(N == 2 && Dimension >= 2 && Usage == 1), T&> height()
  {
    return m_data[1];
  }

  template <Int32 N = 2>
  std::enable_if_t<(N == 2 && Dimension >= 2 && Usage == 1), const T&> height() const
  {
    return m_data[1];
  }

  template <Int32 N = 3>
  std::enable_if_t<(N == 3 && Dimension >= 3 && Usage == 1), T&> depth()
  {
    return m_data[2];
  }

  template <Int32 N = 3>
  std::enable_if_t<(N == 3 && Dimension >= 3 && Usage == 1), const T&> depth() const
  {
    return m_data[2];
  }

#pragma endregion

#pragma region ColorVectorComponents

  template <Int32 N = 1>
  std::enable_if_t<(N == 1 && Dimension >= 1 && Usage == 2), T&> r()
  {
    return m_data[0];
  }

  template <Int32 N = 1>
  std::enable_if_t<(N == 1 && Dimension >= 1 && Usage == 2), const T&> r() const
  {
    return m_data[0];
  }

  template <Int32 N = 2>
  std::enable_if_t<(N == 2 && Dimension >= 2 && Usage == 2), T&> g()
  {
    return m_data[1];
  }

  template <Int32 N = 2>
  std::enable_if_t<(N == 2 && Dimension >= 2 && Usage == 2), const T&> g() const
  {
    return m_data[1];
  }

  template <Int32 N = 3>
  std::enable_if_t<(N == 3 && Dimension >= 3 && Usage == 2), T&> b()
  {
    return m_data[2];
  }

  template <Int32 N = 3>
  std::enable_if_t<(N == 3 && Dimension >= 3 && Usage == 2), const T&> b() const
  {
    return m_data[2];
  }

  template <Int32 N = 4>
  std::enable_if_t<(N == 4 && Dimension >= 4 && Usage == 2), T&> a()
  {
    return m_data[3];
  }

  template <Int32 N = 4>
  std::enable_if_t<(N == 4 && Dimension >= 4 && Usage == 2), const T&> a() const
  {
    return m_data[3];
  }

#pragma endregion

  T* data()
  {
    return m_data;
  }

  const T* data() const
  {
    return m_data;
  }

  T dot(const Vec& other) const
  {
    T result = T();
    for (Int32 i = 0; i < Dimension; ++i)
    {
      result += m_data[i] * other.m_data[i];
    }
    return result;
  }

  template <Int32 N = 3>
  std::enable_if_t<(N == 3 && Dimension == 3), Vec> cross(const Vec& other) const
  {
    // clang-format off
    return Vec({
      m_data[1] * other.m_data[2] - m_data[2] * other.m_data[1], 
      m_data[2] * other.m_data[0] - m_data[0] * other.m_data[2], 
      m_data[0] * other.m_data[1] - m_data[1] * other.m_data[0]
    });
    // clang-format on
  }

  T length() const
  {
    return std::sqrt(dot(*this));
  }

  template <typename U = T>
  std::enable_if_t<(std::is_same_v<U, T> && std::is_floating_point_v<U>), Vec> normalized() const
  {
    static_assert(std::is_same_v<U, T>, "Template parameter U must be the same as T due to SFINAE");
    return *this / length();
  }

  Vec& operator+=(const Vec& other)
  {
    for (Int32 i = 0; i < Dimension; ++i)
    {
      m_data[i] += other.m_data[i];
    }
    return *this;
  }

  Vec& operator-=(const Vec& other)
  {
    for (Int32 i = 0; i < Dimension; ++i)
    {
      m_data[i] -= other.m_data[i];
    }
    return *this;
  }

  Vec& operator*=(T scalar)
  {
    for (Int32 i = 0; i < Dimension; ++i)
    {
      m_data[i] *= scalar;
    }
    return *this;
  }

  Vec& operator/=(T scalar)
  {
    for (Int32 i = 0; i < Dimension; ++i)
    {
      m_data[i] /= scalar;
    }
    return *this;
  }

  Vec operator-() const
  {
    Vec result;
    for (Int32 i = 0; i < Dimension; ++i)
    {
      result.m_data[i] = -m_data[i];
    }
    return result;
  }

  Vec operator+(const Vec& other) const
  {
    Vec result;
    for (Int32 i = 0; i < Dimension; ++i)
    {
      result.m_data[i] = m_data[i] + other.m_data[i];
    }
    return result;
  }

  Vec operator-(const Vec& other) const
  {
    Vec result;
    for (Int32 i = 0; i < Dimension; ++i)
    {
      result.m_data[i] = m_data[i] - other.m_data[i];
    }
    return result;
  }

  Vec operator*(T scalar) const
  {
    Vec result;
    for (Int32 i = 0; i < Dimension; ++i)
    {
      result.m_data[i] = m_data[i] * scalar;
    }
    return result;
  }

  Vec operator/(T scalar) const
  {
    Vec result;
    for (Int32 i = 0; i < Dimension; ++i)
    {
      result.m_data[i] = m_data[i] / scalar;
    }
    return result;
  }

  bool operator==(const Vec& other) const
  {
    for (Int32 i = 0; i < Dimension; ++i)
    {
      if (m_data[i] != other.m_data[i])
      {
        return false;
      }
    }
    return true;
  }

  bool operator!=(const Vec& other) const
  {
    return !(*this == other);
  }

  T* begin()
  {
    return m_data;
  }

  const T* begin() const
  {
    return m_data;
  }

  T* end()
  {
    return m_data + Dimension;
  }

  const T* end() const
  {
    return m_data + Dimension;
  }

private:
  T m_data[Dimension];
};

template <typename T, Int32 DimM, Int32 DimN>
class Mat
{
  static_assert(std::is_arithmetic_v<T>, "Mat can only be used with arithmetic types");
  static_assert(DimM > 0, "Mat dimension must be greater than 0");
  static_assert(DimN > 0, "Mat dimension must be greater than 0");

public:
  Mat()

  {
    for (Int32 i = 0; i < DimM; ++i)
    {
      for (Int32 j = 0; j < DimN; ++j)
      {
        m_data[i * DimN + j] = T();
      }
    }
  }

  Mat(const Array<T, DimM * DimN>& data)
  {
    std::copy(data.begin(), data.end(), m_data);
  }

  Mat(const Mat& other) = default;
  Mat(Mat&& other)      = default;

  ~Mat() = default;

  Mat& operator=(const Mat& other) = default;
  Mat& operator=(Mat&& other)      = default;

  template <Int32 SubDimM, Int32 SubDimN>
  Mat<T, SubDimM, SubDimN> submatrix(Int32 row, Int32 col) const
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

  T* data()
  {
    return m_data;
  }

  template <Int32 DimP>
  Mat<T, DimM, DimP> operator*(const Mat<T, DimN, DimP>& other) const
  {
    Mat<T, DimM, DimP> result;
    for (Int32 i = 0; i < DimM; ++i)
    {
      for (Int32 j = 0; j < DimP; ++j)
      {
        for (Int32 k = 0; k < DimN; ++k)
        {
          result.m_data[i * DimP + j] += m_data[i * DimN + k] * other.m_data[k * DimP + j];
        }
      }
    }
    return result;
  }

  Vec<T, DimM> operator*(const Vec<T, DimN>& vec) const
  {
    Vec<T, DimM> result;
    for (Int32 i = 0; i < DimM; ++i)
    {
      for (Int32 j = 0; j < DimN; ++j)
      {
        result.get(i) += m_data[i * DimN + j] * vec.get(j);
      }
    }
    return result;
  }

  T& get(Int32 row, Int32 col)
  {
    return m_data[row * DimN + col];
  }

  const T& get(Int32 row, Int32 col) const
  {
    return m_data[row * DimN + col];
  }

  Mat& operator+=(const Mat& other)
  {
    for (Int32 i = 0; i < DimM * DimN; ++i)
    {
      m_data[i] += other.m_data[i];
    }
    return *this;
  }

  Mat& operator-=(const Mat& other)
  {
    for (Int32 i = 0; i < DimM * DimN; ++i)
    {
      m_data[i] -= other.m_data[i];
    }
    return *this;
  }

  Mat& operator*=(T scalar)
  {
    for (Int32 i = 0; i < DimM * DimN; ++i)
    {
      m_data[i] *= scalar;
    }
    return *this;
  }

  Mat& operator/=(T scalar)
  {
    for (Int32 i = 0; i < DimM * DimN; ++i)
    {
      m_data[i] /= scalar;
    }
    return *this;
  }

  Mat operator-() const
  {
    Mat result;
    for (Int32 i = 0; i < DimM * DimN; ++i)
    {
      result.m_data[i] = -m_data[i];
    }
    return result;
  }

  Mat operator+(const Mat& other) const
  {
    Mat result;
    for (Int32 i = 0; i < DimM * DimN; ++i)
    {
      result.m_data[i] = m_data[i] + other.m_data[i];
    }
    return result;
  }

  Mat operator-(const Mat& other) const
  {
    Mat result;
    for (Int32 i = 0; i < DimM * DimN; ++i)
    {
      result.m_data[i] = m_data[i] - other.m_data[i];
    }
    return result;
  }

  Mat operator*(T scalar) const
  {
    Mat result;
    for (Int32 i = 0; i < DimM * DimN; ++i)
    {
      result.m_data[i] = m_data[i] * scalar;
    }
    return result;
  }

  Mat operator/(T scalar) const
  {
    Mat result;
    for (Int32 i = 0; i < DimM * DimN; ++i)
    {
      result.m_data[i] = m_data[i] / scalar;
    }
    return result;
  }

  bool operator==(const Mat& other) const
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

  bool operator!=(const Mat& other) const
  {
    return !(*this == other);
  }

  T* begin()
  {
    return m_data;
  }

  const T* begin() const
  {
    return m_data;
  }

  T* end()
  {
    return m_data + DimM * DimN;
  }

  const T* end() const
  {
    return m_data + DimM * DimN;
  }

  Mat<T, DimN, DimM> transpose() const
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

  T minor(Int32 row, Int32 col) const
  {
    static_assert(DimM == DimN, "Matrix must be square to calculate minor");
    static_assert(DimM > 1, "Matrix must be at least 2x2 to calculate minor");

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

  T determinant()
  {
    static_assert(DimM == DimN, "Matrix must be square to calculate determinant");

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
      return m_data[0] * (m_data[4] * m_data[8] - m_data[5] * m_data[7]) - m_data[1] * (m_data[3] * m_data[8] - m_data[5] * m_data[6]) +
             m_data[2] * (m_data[3] * m_data[7] - m_data[4] * m_data[6]);
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

public:
  /// @brief Create an identity matrix
  /// @return The identity matrix
  template <Int32 IDimM = DimM, Int32 IDimN = DimN>
  static std::enable_if_t<(IDimM == DimM && IDimN == DimN), Mat<T, IDimM, IDimN>> identity()
  {
    static_assert(DimM == DimN, "Identity matrix must be square");

    Mat<T, IDimM, IDimN> result;
    for (Int32 i = 0; i < IDimM; ++i)
    {
      result.m_data[i * IDimN + i] = T(1);
    }
    return result;
  }

  /// @brief Create a perspective projection matrix
  /// @param fov Field of view in degrees
  /// @param aspect Aspect ratio
  /// @param near Near plane
  /// @param far Far plane
  /// @return The perspective projection matrix
  template <Int32 IDimM = DimM, Int32 IDimN = DimN>
  static std::enable_if_t<(std::is_floating_point_v<T> && IDimM == DimM && IDimN == DimN), Mat<T, IDimM, IDimN>> perspective(
      T fov, T aspect, T near, T far
  )
  {
    static_assert(DimM == DimN && DimM == 4, "Perspective projection matrix must be 4x4");

    Mat<T, IDimM, IDimN> result;

    T f              = T(1) / std::tan(fov / T(2));
    result.get(0, 0) = f / aspect;
    result.get(1, 1) = f;
    result.get(2, 2) = (far + near) / (near - far);
    result.get(2, 3) = (T(2) * far * near) / (near - far);
    result.get(3, 2) = T(-1);

    return result;
  }

  /// @brief Create an orthographic projection matrix
  /// @param left The minimum x-coordinate of the view volume
  /// @param right The maximum x-coordinate of the view volume
  /// @param bottom The minimum y-coordinate of the view volume
  /// @param top The maximum y-coordinate of the view volume
  /// @param near The minimum z-coordinate of the view volume
  /// @param far The maximum z-coordinate of the view volume
  /// @return The orthographic projection matrix
  template <Int32 IDimM = DimM, Int32 IDimN = DimN>
  static std::enable_if_t<(std::is_floating_point_v<T> && IDimM == DimM && IDimN == DimN), Mat<T, IDimM, IDimN>> orthographic(
      T left, T right, T bottom, T top, T near, T far
  )
  {
    static_assert(DimM == DimN && DimM == 4, "Orthographic projection matrix must be 4x4");

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

  /// @brief Create a translation matrix
  /// @param translation The translation vector
  /// @return The translation matrix
  template <Int32 IDimM = DimM, Int32 IDimN = DimN>
  static std::enable_if_t<(IDimM == DimM && IDimN == DimN), Mat<T, IDimM, IDimN>> translation(const Vec<T, IDimM - 1>& translation)
  {
    static_assert(DimM == DimN && DimM >= 3, "Translation matrix must be square and at least 3x3");

    Mat<T, IDimM, IDimN> result = identity();
    for (Int32 i = 0; i < IDimM - 1; ++i)
    {
      result.get(i, IDimN - 1) = translation.get(i);
    }
    return result;
  }

private:
  T m_data[DimM * DimN];
};

using Vec2I = Vec<Int32, 2, NormalVector>;
using Vec3I = Vec<Int32, 3, NormalVector>;
using Vec4I = Vec<Int32, 4, NormalVector>;
using Vec2U = Vec<UInt32, 2, NormalVector>;
using Vec3U = Vec<UInt32, 3, NormalVector>;
using Vec4U = Vec<UInt32, 4, NormalVector>;
using Vec2F = Vec<Float, 2, NormalVector>;
using Vec3F = Vec<Float, 3, NormalVector>;
using Vec4F = Vec<Float, 4, NormalVector>;
using Vec2D = Vec<Double, 2, NormalVector>;
using Vec4D = Vec<Double, 4, NormalVector>;
using Vec3D = Vec<Double, 3, NormalVector>;

using Dim2I = Vec<Int32, 2, DimensionVector>;
using Dim3I = Vec<Int32, 3, DimensionVector>;
using Dim4I = Vec<Int32, 4, DimensionVector>;
using Dim3U = Vec<UInt32, 3, DimensionVector>;
using Dim4U = Vec<UInt32, 4, DimensionVector>;
using Dim2U = Vec<UInt32, 2, DimensionVector>;
using Dim2F = Vec<Float, 2, DimensionVector>;
using Dim3F = Vec<Float, 3, DimensionVector>;
using Dim4F = Vec<Float, 4, DimensionVector>;
using Dim4D = Vec<Double, 4, DimensionVector>;
using Dim2D = Vec<Double, 2, DimensionVector>;
using Dim3D = Vec<Double, 3, DimensionVector>;

using Color1I = Vec<Int32, 1, 2>;
using Color2I = Vec<Int32, 2, 2>;
using Color3I = Vec<Int32, 3, 2>;
using Color4I = Vec<Int32, 4, 2>;
using Color1U = Vec<UInt32, 1, 2>;
using Color2U = Vec<UInt32, 2, 2>;
using Color3U = Vec<UInt32, 3, 2>;
using Color4U = Vec<UInt32, 4, 2>;
using Color1F = Vec<Float, 1, 2>;
using Color2F = Vec<Float, 2, 2>;
using Color3F = Vec<Float, 3, 2>;
using Color4F = Vec<Float, 4, 2>;
using Color1D = Vec<Double, 1, 2>;
using Color4D = Vec<Double, 4, 2>;
using Color2D = Vec<Double, 2, 2>;
using Color3D = Vec<Double, 3, 2>;

using Mat2F   = Mat<Float, 2, 2>;
using Mat2x2F = Mat<Float, 2, 2>;
using Mat2x3F = Mat<Float, 2, 3>;
using Mat2x4F = Mat<Float, 2, 4>;

using Mat3F   = Mat<Float, 3, 3>;
using Mat3x2F = Mat<Float, 3, 2>;
using Mat3x3F = Mat<Float, 3, 3>;
using Mat3x4F = Mat<Float, 3, 4>;

using Mat4F   = Mat<Float, 4, 4>;
using Mat4x2F = Mat<Float, 4, 2>;
using Mat4x3F = Mat<Float, 4, 3>;
using Mat4x4F = Mat<Float, 4, 4>;

using Mat2D   = Mat<Double, 2, 2>;
using Mat2x2D = Mat<Double, 2, 2>;
using Mat2x3D = Mat<Double, 2, 3>;
using Mat2x4D = Mat<Double, 2, 4>;

using Mat3D   = Mat<Double, 3, 3>;
using Mat3x2D = Mat<Double, 3, 2>;
using Mat3x3D = Mat<Double, 3, 3>;
using Mat3x4D = Mat<Double, 3, 4>;

using Mat4D   = Mat<Double, 4, 4>;
using Mat4x2D = Mat<Double, 4, 2>;
using Mat4x3D = Mat<Double, 4, 3>;
using Mat4x4D = Mat<Double, 4, 4>;

using Color = Color4F;

}  // namespace setsugen