#pragma once

#include <setsugen/pch.h>

// Setsugen headers
#include <setsugen/exception.h>

// C++ standard library
#include <algorithm>
#include <array>
#include <cmath>
#include <type_traits>

namespace setsugen
{

enum class VectorUsage
{
  Math,
  Size,
  Color
};

template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template<Arithmetic T, int Dimension, VectorUsage Usage = VectorUsage::Math>
  requires(Dimension > 0)
class Vec;

template<Arithmetic T, int DimM, int DimN>
  requires(DimM > 0) && (DimN > 0)
class Mat;

template<Arithmetic T>
class Quaternion;

template<Arithmetic T, int Dimension, VectorUsage Usage>
  requires(Dimension > 0)
class Vec
{
public:
  /// @brief Default constructor - Creates a Vec with all elements initialized to 0
  Vec()
  {
    for (int i = 0; i < Dimension; ++i)
    {
      m_data[i] = T();
    }
  }

  template<typename... Args>
    requires(sizeof...(Args) == Dimension) && (std::is_convertible_v<Args, T> && ...)
  Vec(Args... args) : m_data{static_cast<T>(args)...}
  {}

  Vec(const Vec& other) = default;

  Vec(Vec&& other) = default;

  ~Vec() = default;

  Vec& operator=(const Vec& other) = default;
  Vec& operator=(Vec&& other)      = default;

  /// @brief Access an element of the Vec
  /// @param index Element index (0-based)
  /// @return Value of the element at the given index
  T& get(int index)
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
  const T& get(int index) const
  {
    if (index < 0 || index >= Dimension)
    {
      throw InvalidArgumentException("Index is out of range");
    }
    return m_data[index];
  }

#pragma region NormalVectorComponents

  template<int N = 1>
    requires(N == 1 && Dimension >= 1 && Usage == VectorUsage::Math)
  T& x()
  {
    return m_data[N - 1];
  }

  template<int N = 1>
    requires(N == 1 && Dimension >= 1 && Usage == VectorUsage::Math)
  const T& x() const
  {
    return m_data[N - 1];
  }

  template<int N = 2>
    requires(N == 2 && Dimension >= 2 && Usage == VectorUsage::Math)
  T& y()
  {
    return m_data[N - 1];
  }

  template<int N = 2>
    requires(N == 2 && Dimension >= 2 && Usage == VectorUsage::Math)
  const T& y() const
  {
    return m_data[N - 1];
  }

  template<int N = 3>
    requires(N == 3 && Dimension >= 3 && Usage == VectorUsage::Math)
  T& z()
  {
    return m_data[N - 1];
  }

  template<int N = 3>
    requires(N == 3 && Dimension >= 3 && Usage == VectorUsage::Math)
  const T& z() const
  {
    return m_data[N - 1];
  }

  template<int N = 4>
    requires(N == 4 && Dimension >= 4 && Usage == VectorUsage::Math)
  T& w()
  {
    return m_data[N - 1];
  }

  template<int N = 4>
    requires(N == 4 && Dimension >= 4 && Usage == VectorUsage::Math)
  const T& w() const
  {
    return m_data[N - 1];
  }
#pragma endregion

#pragma region DimensionVectorComponents

  template<int N = 1>
    requires(N == 1 && Dimension >= 1 && Usage == VectorUsage::Size)
  T& width()
  {
    return m_data[N - 1];
  }

  template<int N = 1>
    requires(N == 1 && Dimension >= 1 && Usage == VectorUsage::Size)
  const T& width() const
  {
    return m_data[N - 1];
  }

  template<int N = 2>
    requires(N == 2 && Dimension >= 2 && Usage == VectorUsage::Size)
  T& height()
  {
    return m_data[N - 1];
  }

  template<int N = 2>
    requires(N == 2 && Dimension >= 2 && Usage == VectorUsage::Size)
  const T& height() const
  {
    return m_data[N - 1];
  }

  template<int N = 3>
    requires(N == 3 && Dimension >= 3 && Usage == VectorUsage::Size)
  T& depth()
  {
    return m_data[N - 1];
  }

  template<int N = 3>
    requires(N == 3 && Dimension >= 3 && Usage == VectorUsage::Size)
  const T& depth() const
  {
    return m_data[N - 1];
  }

#pragma endregion

#pragma region ColorVectorComponents

  template<int N = 1>
    requires(N == 1 && Dimension >= 1 && Usage == VectorUsage::Color)
  T& r()
  {
    return m_data[N - 1];
  }

  template<int N = 1>
    requires(N == 1 && Dimension >= 1 && Usage == VectorUsage::Color)
  const T& r() const
  {
    return m_data[N - 1];
  }

  template<int N = 2>
    requires(N == 2 && Dimension >= 2 && Usage == VectorUsage::Color)
  T& g()
  {
    return m_data[N - 1];
  }

  template<int N = 2>
    requires(N == 2 && Dimension >= 2 && Usage == VectorUsage::Color)
  const T& g() const
  {
    return m_data[N - 1];
  }

  template<int N = 3>
    requires(N == 3 && Dimension >= 3 && Usage == VectorUsage::Color)
  T& b()
  {
    return m_data[N - 1];
  }

  template<int N = 3>
    requires(N == 3 && Dimension >= 3 && Usage == VectorUsage::Color)
  const T& b() const
  {
    return m_data[N - 1];
  }

  template<int N = 4>
    requires(N == 4 && Dimension >= 4 && Usage == VectorUsage::Color)
  T& a()
  {
    return m_data[N - 1];
  }

  template<int N = 4>
    requires(N == 4 && Dimension >= 4 && Usage == VectorUsage::Color)
  const T& a() const
  {
    return m_data[N - 1];
  }

#pragma endregion

  T* data()
  {
    return m_data;
  }

  const T data() const
  {
    return m_data;
  }

  T dot(const Vec& other) const
  {
    T result = T();
    for (int i = 0; i < Dimension; ++i)
    {
      result += m_data[i] * other.m_data[i];
    }
    return result;
  }

  template<int N = 3>
    requires(N == Dimension) && (Dimension == 3)
  Vec cross(const Vec& other) const
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

  template<typename U = T>
    requires std::is_same_v<U, T> && std::is_floating_point_v<U>
  Vec normalize() const
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

  Vec rotate(const Quaternion<T>& rotation) const
  {
    Quaternion<T> q = rotation.normalized();
    Quaternion<T> p(0, m_data[0], m_data[1], m_data[2]);
    Quaternion<T> q_conjugate = q.conjugate();
    Quaternion<T> result      = q * p * q_conjugate;
    return Vec(result.y(), result.z(), result.w());
  }

  Vec& operator+=(const Vec& other)
  {
    for (int i = 0; i < Dimension; ++i)
    {
      m_data[i] += other.m_data[i];
    }
    return *this;
  }

  Vec& operator-=(const Vec& other)
  {
    for (int i = 0; i < Dimension; ++i)
    {
      m_data[i] -= other.m_data[i];
    }
    return *this;
  }

  Vec& operator*=(T scalar)
  {
    for (int i = 0; i < Dimension; ++i)
    {
      m_data[i] *= scalar;
    }
    return *this;
  }

  Vec& operator/=(T scalar)
  {
    for (int i = 0; i < Dimension; ++i)
    {
      m_data[i] /= scalar;
    }
    return *this;
  }


  bool operator==(const Vec& other) const
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
  std::array<T, Dimension> m_data;
};

template<Arithmetic T, int DimM, int DimN>
  requires(DimM > 0) && (DimN > 0)
class Mat
{
public:
  class RowIterator
  {
  public:
    RowIterator(T* ptr, T* begin, T* end) : m_ptr(ptr), m_begin(begin), m_end(end)
    {}

    T& operator*()
    {
      return *m_ptr;
    }

    const T& operator*() const
    {
      return *m_ptr;
    }

    RowIterator& operator++()
    {
      m_ptr += DimN;
      return *this;
    }

    RowIterator& operator--()
    {
      m_ptr -= DimN;
      return *this;
    }

    bool operator==(const RowIterator& other) const
    {
      return m_ptr == other.m_ptr;
    }

    bool operator!=(const RowIterator& other) const
    {
      return m_ptr != other.m_ptr;
    }

  private:
    T* m_ptr;
    T* m_begin;
    T* m_end;
  };

  class ColIterator
  {
  public:
    ColIterator(T* ptr) : m_ptr(ptr)
    {}

    T& operator*()
    {
      return *m_ptr;
    }

    ColIterator& operator++()
    {
      ++m_ptr;
      return *this;
    }

    ColIterator& operator--()
    {
      --m_ptr;
      return *this;
    }

    bool operator==(const ColIterator& other) const
    {
      return m_ptr == other.m_ptr;
    }

    bool operator!=(const ColIterator& other) const
    {
      return m_ptr != other.m_ptr;
    }

  private:
    T* m_ptr;
  };

  Mat()
  {
    for (int i = 0; i < DimM; ++i)
    {
      for (int j = 0; j < DimN; ++j)
      {
        m_data[i * DimN + j] = T();
      }
    }
  }

  Mat(const std::array<T, DimM * DimN>& data)
  {
    std::copy(data.begin(), data.end(), m_data);
  }

  Mat(const Mat& other) = default;
  Mat(Mat&& other)      = default;

  ~Mat() = default;

  Mat& operator=(const Mat& other) = default;
  Mat& operator=(Mat&& other)      = default;

  template<int SubDimM, int SubDimN>
    requires(SubDimM > 0) && (SubDimM < DimM) && (SubDimN > 0) && (SubDimN < DimN)
  Mat<T, SubDimM, SubDimN> submatrix(int row, int col) const
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

  T* data()
  {
    return m_data;
  }

  const T* data() const
  {
    return m_data;
  }

  template<int DimP>
  Mat<T, DimM, DimP> operator*(const Mat<T, DimN, DimP>& other) const
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

  Vec<T, DimM> operator*(const Vec<T, DimN>& vec) const
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

  T& get(int row, int col)
  {
    return m_data[col * DimN + row];
  }

  T get(int row, int col) const
  {
    return m_data[col * DimN + row];
  }

  Mat& operator+=(const Mat& other)
  {
    for (int i = 0; i < DimM * DimN; ++i)
    {
      m_data[i] += other.m_data[i];
    }
    return *this;
  }

  Mat& operator-=(const Mat& other)
  {
    for (int i = 0; i < DimM * DimN; ++i)
    {
      m_data[i] -= other.m_data[i];
    }
    return *this;
  }

  Mat& operator*=(T scalar)
  {
    for (int i = 0; i < DimM * DimN; ++i)
    {
      m_data[i] *= scalar;
    }
    return *this;
  }

  Mat& operator/=(T scalar)
  {
    for (int i = 0; i < DimM * DimN; ++i)
    {
      m_data[i] /= scalar;
    }
    return *this;
  }

  bool operator==(const Mat& other) const
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
    for (int i = 0; i < DimM; ++i)
    {
      for (int j = 0; j < DimN; ++j)
      {
        result.get(j, i) = m_data[i * DimN + j];
      }
    }
    return result;
  }

  T minor(int row, int col) const
  {
    static_assert(DimM == DimN, "Matrix must be square to calculate minor");
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

  /// @brief Create an identity matrix
  /// @return The identity matrix
  template<int IDimM = DimM, int IDimN = DimN>
    requires(IDimM == DimM) && (IDimN == DimN)
  static Mat<T, IDimM, IDimN> identity()
  {
    static_assert(DimM == DimN, "Identity matrix must be square");

    Mat<T, IDimM, IDimN> result;
    for (int i = 0; i < IDimM; ++i)
    {
      result.get(i, i) = T(1);
    }
    return result;
  }

  /// @brief Create a perspective projection matrix
  /// @param fov Field of view in degrees
  /// @param aspect Aspect ratio
  /// @param near Near plane
  /// @param far Far plane
  /// @return The perspective projection matrix
  template<int IDimM = DimM, int IDimN = DimN>
    requires std::is_floating_point_v<T> && (IDimM == DimM) && (IDimN == DimN) && (IDimM == 4)
  static Mat<T, IDimM, IDimN> perspective(T fov, T aspect, T near, T far)
  {
    Mat<T, IDimM, IDimN> result;

    T f = T(1) / std::tan(fov * T(0.5) * std::numbers::pi_v<float> / T(180));
    result.get(0, 0) = f / aspect;
    result.get(1, 1) = f;
    result.get(2, 2) = (far + near) / (near - far);
    result.get(2, 3) = T(-1);
    result.get(3, 2) = (T(2) * far * near) / (near - far);
    result.get(3, 3) = T(0);

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
  template<int IDimM = DimM, int IDimN = DimN>
    requires std::is_floating_point_v<T> && (IDimM == DimM) && (IDimN == DimN) && (IDimM == 4)
  static Mat<T, IDimM, IDimN> orthographic(T left, T right, T bottom, T top, T near, T far)
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

  /// @brief Create a translation matrix
  /// @param translation The translation vector
  /// @return The translation matrix
  template<int IDimM = DimM, int IDimN = DimN>
    requires std::is_arithmetic_v<T> && (IDimM == DimM) && (IDimN == DimN)
  static Mat<T, IDimM, IDimN> translation(const Vec<T, IDimM - 1>& translation)
  {
    static_assert(DimM == DimN && DimM >= 3, "Translation matrix must be square and at least 3x3");

    Mat<T, IDimM, IDimN> result = identity();
    for (int i = 0; i < IDimM - 1; ++i)
    {
      result.get(i, IDimN - 1) = translation.get(i);
    }
    return result;
  }

  /// @brief Create a rotation matrix
  /// @param rotation The rotation vector
  /// @return The rotation matrix
  template<int IDimM = DimM, int IDimN = DimN>
    requires std::is_arithmetic_v<T> && (IDimM == DimM) && (IDimN == DimN)
  static Mat<T, IDimM, IDimN> rotation(const Vec<T, 3>& rotation)
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

  /// @brief Create a scale matrix
  /// @param scale The scale vector
  /// @return The scale matrix
  template<int IDimM = DimM, int IDimN = DimN>
    requires std::is_arithmetic_v<T> && (IDimM == DimM) && (IDimN == DimN)
  static Mat<T, IDimM, IDimN> scale(const Vec<T, 3>& scale)
  {
    static_assert(DimM == DimN && DimM == 4, "Scale matrix must be square and 4x4");

    Mat<T, IDimM, IDimN> result = identity();
    result.get(0, 0)            = scale.x();
    result.get(1, 1)            = scale.y();
    result.get(2, 2)            = scale.z();
    return result;
  }

  /// @brief Create a look-at matrix
  /// @param eye The eye position
  /// @param center The center position
  /// @param up The up vector
  /// @return The look-at matrix
  template<int IDimM = DimM, int IDimN = DimN>
    requires std::is_arithmetic_v<T> && (IDimM == DimM) && (IDimN == DimN)
  static Mat<T, IDimM, IDimN> look_at(const Vec<T, 3>& eye, const Vec<T, 3>& center, const Vec<T, 3>& up)
  {
    static_assert(DimM == DimN && DimM == 4, "Look-at matrix must be square and 4x4");

    Mat<T, IDimM, IDimN> result = identity();
    // Calculate view matrix look at center from eye with up direction being up

    auto fwd = (center - eye).normalize();
    auto side = fwd.cross(up).normalize();
    auto upv = side.cross(fwd);

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


private:
  T m_data[DimM * DimN];
};

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

  bool operator==(const Quaternion& other) const
  {
    return x() == other.x() && y() == other.y() && z() == other.z() && w() == other.w();
  }

  bool operator!=(const Quaternion& other) const
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
  std::array<T, 4> m_data;
};

#pragma region Operators

template<Arithmetic T, int Dim>
Vec<T, Dim>
operator+(const Vec<T, Dim>& lhs, const Vec<T, Dim>& rhs)
{
  Vec<T, Dim> result = lhs;
  for (int i = 0; i < Dim; ++i)
  {
    result.get(i) += rhs.get(i);
  }
  return result;
}

template<Arithmetic T, int Dim>
Vec<T, Dim>
operator-(const Vec<T, Dim>& lhs, const Vec<T, Dim>& rhs)
{
  Vec<T, Dim> result = lhs;
  for (int i = 0; i < Dim; ++i)
  {
    result.get(i) -= rhs.get(i);
  }
  return result;
}

template<Arithmetic T, Arithmetic U, int Dim>
Vec<T, Dim>
operator*(const Vec<T, Dim>& vec, U scalar)
{
  Vec<T, Dim> result = vec;
  for (int i = 0; i < Dim; ++i)
  {
    result.get(i) *= scalar;
  }
  return result;
}

template<Arithmetic T, Arithmetic U, int Dim>
Vec<T, Dim>
operator*(U scalar, const Vec<T, Dim>& vec)
{
  return vec * scalar;
}

template<Arithmetic T, int DimM, int DimN>
Mat<T, DimM, DimN>
operator+(const Mat<T, DimM, DimN>& lhs, const Mat<T, DimM, DimN>& rhs)
{
  Mat<T, DimM, DimN> result = lhs;
  for (int i = 0; i < DimM * DimN; ++i)
  {
    result.data()[i] += rhs.data()[i];
  }
  return result;
}

template<Arithmetic T, int DimM, int DimN>
Mat<T, DimM, DimN>
operator-(const Mat<T, DimM, DimN>& lhs, const Mat<T, DimM, DimN>& rhs)
{
  Mat<T, DimM, DimN> result = lhs;
  for (int i = 0; i < DimM * DimN; ++i)
  {
    result.data()[i] -= rhs.data()[i];
  }
  return result;
}

template<Arithmetic T, Arithmetic U, int DimM, int DimN>
Mat<T, DimM, DimN>
operator*(const Mat<T, DimM, DimN>& mat, U scalar)
{
  Mat<T, DimM, DimN> result = mat;
  for (int i = 0; i < DimM * DimN; ++i)
  {
    result.data()[i] *= scalar;
  }
  return result;
}

template<Arithmetic T, Arithmetic U, int DimM, int DimN>
Mat<T, DimM, DimN>
operator*(U scalar, const Mat<T, DimM, DimN>& mat)
{
  return mat * scalar;
}

#pragma endregion

#pragma region TypeAliases

using Vec2I = Vec<int, 2, VectorUsage::Math>;
using Vec3I = Vec<int, 3, VectorUsage::Math>;
using Vec4I = Vec<int, 4, VectorUsage::Math>;
using Vec2U = Vec<unsigned int, 2, VectorUsage::Math>;
using Vec3U = Vec<unsigned int, 3, VectorUsage::Math>;
using Vec4U = Vec<unsigned int, 4, VectorUsage::Math>;
using Vec2F = Vec<float, 2, VectorUsage::Math>;
using Vec3F = Vec<float, 3, VectorUsage::Math>;
using Vec4F = Vec<float, 4, VectorUsage::Math>;
using Vec2D = Vec<double, 2, VectorUsage::Math>;
using Vec4D = Vec<double, 4, VectorUsage::Math>;
using Vec3D = Vec<double, 3, VectorUsage::Math>;

using Dim2I = Vec<int, 2, VectorUsage::Size>;
using Dim3I = Vec<int, 3, VectorUsage::Size>;
using Dim4I = Vec<int, 4, VectorUsage::Size>;
using Dim3U = Vec<unsigned int, 3, VectorUsage::Size>;
using Dim4U = Vec<unsigned int, 4, VectorUsage::Size>;
using Dim2U = Vec<unsigned int, 2, VectorUsage::Size>;
using Dim2F = Vec<float, 2, VectorUsage::Size>;
using Dim3F = Vec<float, 3, VectorUsage::Size>;
using Dim4F = Vec<float, 4, VectorUsage::Size>;
using Dim4D = Vec<double, 4, VectorUsage::Size>;
using Dim2D = Vec<double, 2, VectorUsage::Size>;
using Dim3D = Vec<double, 3, VectorUsage::Size>;

using Color1I = Vec<int, 1, VectorUsage::Color>;
using Color2I = Vec<int, 2, VectorUsage::Color>;
using Color3I = Vec<int, 3, VectorUsage::Color>;
using Color4I = Vec<int, 4, VectorUsage::Color>;
using Color1U = Vec<unsigned int, 1, VectorUsage::Color>;
using Color2U = Vec<unsigned int, 2, VectorUsage::Color>;
using Color3U = Vec<unsigned int, 3, VectorUsage::Color>;
using Color4U = Vec<unsigned int, 4, VectorUsage::Color>;
using Color1F = Vec<float, 1, VectorUsage::Color>;
using Color2F = Vec<float, 2, VectorUsage::Color>;
using Color3F = Vec<float, 3, VectorUsage::Color>;
using Color4F = Vec<float, 4, VectorUsage::Color>;
using Color1D = Vec<double, 1, VectorUsage::Color>;
using Color4D = Vec<double, 4, VectorUsage::Color>;
using Color2D = Vec<double, 2, VectorUsage::Color>;
using Color3D = Vec<double, 3, VectorUsage::Color>;

using Mat2F   = Mat<float, 2, 2>;
using Mat2x2F = Mat<float, 2, 2>;
using Mat2x3F = Mat<float, 2, 3>;
using Mat2x4F = Mat<float, 2, 4>;

using Mat3F   = Mat<float, 3, 3>;
using Mat3x2F = Mat<float, 3, 2>;
using Mat3x3F = Mat<float, 3, 3>;
using Mat3x4F = Mat<float, 3, 4>;

using Mat4F   = Mat<float, 4, 4>;
using Mat4x2F = Mat<float, 4, 2>;
using Mat4x3F = Mat<float, 4, 3>;
using Mat4x4F = Mat<float, 4, 4>;

using Mat2D   = Mat<double, 2, 2>;
using Mat2x2D = Mat<double, 2, 2>;
using Mat2x3D = Mat<double, 2, 3>;
using Mat2x4D = Mat<double, 2, 4>;

using Mat3D   = Mat<double, 3, 3>;
using Mat3x2D = Mat<double, 3, 2>;
using Mat3x3D = Mat<double, 3, 3>;
using Mat3x4D = Mat<double, 3, 4>;

using Mat4D   = Mat<double, 4, 4>;
using Mat4x2D = Mat<double, 4, 2>;
using Mat4x3D = Mat<double, 4, 3>;
using Mat4x4D = Mat<double, 4, 4>;

using Color = Color4F;

using QuatF = Quaternion<float>;
using QuatD = Quaternion<double>;

#pragma endregion

} // namespace setsugen
