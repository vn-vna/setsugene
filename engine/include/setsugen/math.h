#pragma once

#include <setsugen/pch.h>
#include <setsugen/types.h>
#include <setsugen/exception.h>

namespace setsugen
{
enum class VectorUsage
{
  Math,
  Size,
  Color
};

template<typename T>
concept Arithmetic = NumericType<T> || BooleanType<T>;

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
  using ValueType   = T;
  using Pointer     = ValueType*;
  using CPointer    = const ValueType*;
  using RefType     = ValueType&;
  using CRefType    = const ValueType&;
  using StorageType = std::array<ValueType, Dimension>;
  using Iter        = typename StorageType::iterator;
  using CIter       = typename StorageType::const_iterator;

  Vec();
  template<typename... Args>
    requires(sizeof...(Args) == Dimension) && (std::is_convertible_v<Args, T> && ...)
  Vec(Args... args);
  Vec(const Vec& other);
  Vec(Vec&& other) noexcept;
  ~Vec() noexcept;

  Vec& operator=(const Vec& other);
  Vec& operator=(Vec&& other) noexcept;

  /// @brief Access an element of the Vec
  /// @param index Element index (0-based)
  /// @return Value of the element at the given index
  RefType get(int index);

  /// @brief Access an element of the Vec
  /// @param index Element index (0-based)
  /// @return Value of the element at the given index
  CRefType get(int index) const;

#pragma region NormalVectorComponents

  template<int N = 1>
    requires(N == 1 && Dimension >= 1 && Usage == VectorUsage::Math)
  RefType x();

  template<int N = 1>
    requires(N == 1 && Dimension >= 1 && Usage == VectorUsage::Math)
  CRefType x() const;

  template<int N = 2>
    requires(N == 2 && Dimension >= 2 && Usage == VectorUsage::Math)
  RefType y();

  template<int N = 2>
    requires(N == 2 && Dimension >= 2 && Usage == VectorUsage::Math)
  CRefType y() const;

  template<int N = 3>
    requires(N == 3 && Dimension >= 3 && Usage == VectorUsage::Math)
  RefType z();

  template<int N = 3>
    requires(N == 3 && Dimension >= 3 && Usage == VectorUsage::Math)
  CRefType z() const;

  template<int N = 4>
    requires(N == 4 && Dimension >= 4 && Usage == VectorUsage::Math)
  RefType w();

  template<int N = 4>
    requires(N == 4 && Dimension >= 4 && Usage == VectorUsage::Math)
  CRefType w() const;
#pragma endregion

#pragma region DimensionVectorComponents

  template<int N = 1>
    requires(N == 1 && Dimension >= 1 && Usage == VectorUsage::Size)
  RefType width();

  template<int N = 1>
    requires(N == 1 && Dimension >= 1 && Usage == VectorUsage::Size)
  CRefType width() const;

  template<int N = 2>
    requires(N == 2 && Dimension >= 2 && Usage == VectorUsage::Size)
  RefType height();

  template<int N = 2>
    requires(N == 2 && Dimension >= 2 && Usage == VectorUsage::Size)
  CRefType height() const;

  template<int N = 3>
    requires(N == 3 && Dimension >= 3 && Usage == VectorUsage::Size)
  RefType depth();

  template<int N = 3>
    requires(N == 3 && Dimension >= 3 && Usage == VectorUsage::Size)
  CRefType depth() const;

#pragma endregion

#pragma region ColorVectorComponents

  template<int N = 1>
    requires(N == 1 && Dimension >= 1 && Usage == VectorUsage::Color)
  RefType r();

  template<int N = 1>
    requires(N == 1 && Dimension >= 1 && Usage == VectorUsage::Color)
  CRefType r() const;

  template<int N = 2>
    requires(N == 2 && Dimension >= 2 && Usage == VectorUsage::Color)
  RefType g();

  template<int N = 2>
    requires(N == 2 && Dimension >= 2 && Usage == VectorUsage::Color)
  CRefType g() const;

  template<int N = 3>
    requires(N == 3 && Dimension >= 3 && Usage == VectorUsage::Color)
  RefType b();

  template<int N = 3>
    requires(N == 3 && Dimension >= 3 && Usage == VectorUsage::Color)
  CRefType b() const;

  template<int N = 4>
    requires(N == 4 && Dimension >= 4 && Usage == VectorUsage::Color)
  RefType a();

  template<int N = 4>
    requires(N == 4 && Dimension >= 4 && Usage == VectorUsage::Color)
  CRefType a() const;

#pragma endregion

  Pointer  data();
  CPointer data() const;

  template<int N = 3>
    requires(N == Dimension) && (Dimension == 3)
  Vec cross(const Vec& other) const;

  template<typename U = T>
    requires std::is_same_v<U, T> && std::is_floating_point_v<U>
  Vec normalize() const;

  T   dot(const Vec& other) const;
  T   length() const;
  Vec rotate(const Quaternion<T>& rotation) const;

  Vec& operator+=(const Vec& other);
  Vec& operator-=(const Vec& other);
  Vec& operator*=(T scalar);
  Vec& operator/=(T scalar);
  bool operator==(const Vec& other) const;
  bool operator!=(const Vec& other) const;

  Iter  begin();
  CIter begin() const;
  Iter  end();
  CIter end() const;

private:
  std::array<T, Dimension> m_data;
};

template<Arithmetic T, int DimM, int DimN>
  requires(DimM > 0) && (DimN > 0)
class Mat
{
public:
  Mat();
  Mat(const std::array<T, DimM * DimN>& data);
  Mat(const Mat& other);
  Mat(Mat&& other) noexcept;
  ~Mat() = default;

  Mat& operator=(const Mat& other);
  Mat& operator=(Mat&& other) noexcept;

  template<int SubDimM, int SubDimN>
    requires(SubDimM > 0) && (SubDimM < DimM) && (SubDimN > 0) && (SubDimN < DimN)
  Mat<T, SubDimM, SubDimN> submatrix(int row, int col) const;

  T*       data();
  const T* data() const;

  template<int DimP>
  Mat<T, DimM, DimP> operator*(const Mat<T, DimN, DimP>& other) const;

  Vec<T, DimM> operator*(const Vec<T, DimN>& vec) const;

  T& get(int row, int col);
  T  get(int row, int col) const;

  Mat& operator+=(const Mat& other);
  Mat& operator-=(const Mat& other);
  Mat& operator*=(T scalar);
  Mat& operator/=(T scalar);
  bool operator==(const Mat& other) const;
  bool operator!=(const Mat& other) const;

  T*       begin();
  const T* begin() const;
  T*       end();
  const T* end() const;

  Mat<T, DimN, DimM> transpose() const;

  template<int IDimM = DimM, int IDimN = DimN>
    requires (IDimM == DimN) && (IDimN == DimN) && (DimM == DimN)
  T minor(int row, int col) const;

  template<int IDimM = DimM, int IDimN = DimN>
    requires (IDimM == DimN) && (IDimN == DimN) && (DimM == DimN)
  T determinant();

  /// @brief Create an identity matrix
  /// @return The identity matrix
  template<int IDimM = DimM, int IDimN = DimN>
    requires(IDimM == DimM) && (IDimN == DimN)
  static Mat<T, IDimM, IDimN> identity();

  /// @brief Create a perspective projection matrix
  /// @param fov Field of view in degrees
  /// @param aspect Aspect ratio
  /// @param near Near plane
  /// @param far Far plane
  /// @return The perspective projection matrix
  template<int IDimM = DimM, int IDimN = DimN>
    requires std::is_floating_point_v<T> && (IDimM == DimM) && (IDimN == DimN) && (IDimM == 4)
  static Mat<T, IDimM, IDimN> perspective(T fov, T aspect, T near, T far);

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
  static Mat<T, IDimM, IDimN> orthographic(T left, T right, T bottom, T top, T near, T far);

  /// @brief Create a translation matrix
  /// @param translation The translation vector
  /// @return The translation matrix
  template<int IDimM = DimM, int IDimN = DimN>
    requires std::is_arithmetic_v<T> && (IDimM == DimM) && (IDimN == DimN)
  static Mat<T, IDimM, IDimN> translation(const Vec<T, IDimM - 1>& translation);

  /// @brief Create a rotation matrix
  /// @param rotation The rotation vector
  /// @return The rotation matrix
  template<int IDimM = DimM, int IDimN = DimN>
    requires std::is_arithmetic_v<T> && (IDimM == DimM) && (IDimN == DimN)
  static Mat<T, IDimM, IDimN> rotation(const Vec<T, 3>& rotation);

  /// @brief Create a scale matrix
  /// @param scale The scale vector
  /// @return The scale matrix
  template<int IDimM = DimM, int IDimN = DimN>
    requires std::is_arithmetic_v<T> && (IDimM == DimM) && (IDimN == DimN)
  static Mat<T, IDimM, IDimN> scale(const Vec<T, 3>& scale);

  /// @brief Create a look-at matrix
  /// @param eye The eye position
  /// @param center The center position
  /// @param up The up vector
  /// @return The look-at matrix
  template<int IDimM = DimM, int IDimN = DimN>
    requires std::is_arithmetic_v<T> && (IDimM == DimM) && (IDimN == DimN)
  static Mat<T, IDimM, IDimN> look_at(const Vec<T, 3>& eye, const Vec<T, 3>& center, const Vec<T, 3>& up);

private:
  T m_data[DimM * DimN];
};

template<Arithmetic T>
class Quaternion
{
public:
  Quaternion()
    : m_data{0, 0, 0, 1}
  {}

  template<typename... Args>
    requires(sizeof...(Args) == 4) && (std::is_convertible_v<Args, T> && ...)
  Quaternion(Args... args)
    : m_data{std::forward<Args>(args)...}
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
} // namespace setsugen

#include "./__impl__/math/vector.inl"
#include "./__impl__/math/matrix.inl"
