#pragma once

#include "./math_fwd.inl"

namespace setsugen {

template <Arithmetic T, int Dimension, VectorUsage Usage>
  requires(Dimension > 0)
class Vec {
public:
  using ValueType = T;
  using Pointer = ValueType *;
  using CPointer = const ValueType *;
  using RefType = ValueType &;
  using CRefType = const ValueType &;
  using StorageType = std::array<ValueType, Dimension>;
  using Iter = typename StorageType::iterator;
  using CIter = typename StorageType::const_iterator;

  Vec();
  template <typename... Args>
    requires(sizeof...(Args) == Dimension) &&
            (std::is_convertible_v<Args, T> && ...)
  Vec(Args... args);
  Vec(const Vec &other);
  Vec(Vec &&other) noexcept;
  ~Vec() noexcept;

  Vec &operator=(const Vec &other);
  Vec &operator=(Vec &&other) noexcept;

  /// @brief Access an element of the Vec
  /// @param index Element index (0-based)
  /// @return Value of the element at the given index
  RefType get(int index);

  /// @brief Access an element of the Vec
  /// @param index Element index (0-based)
  /// @return Value of the element at the given index
  CRefType get(int index) const;

#pragma region NormalVectorComponents

  template <int N = 1>
    requires(N == 1 && Dimension >= 1 && Usage == VectorUsage::Math)
  RefType x();

  template <int N = 1>
    requires(N == 1 && Dimension >= 1 && Usage == VectorUsage::Math)
  CRefType x() const;

  template <int N = 2>
    requires(N == 2 && Dimension >= 2 && Usage == VectorUsage::Math)
  RefType y();

  template <int N = 2>
    requires(N == 2 && Dimension >= 2 && Usage == VectorUsage::Math)
  CRefType y() const;

  template <int N = 3>
    requires(N == 3 && Dimension >= 3 && Usage == VectorUsage::Math)
  RefType z();

  template <int N = 3>
    requires(N == 3 && Dimension >= 3 && Usage == VectorUsage::Math)
  CRefType z() const;

  template <int N = 4>
    requires(N == 4 && Dimension >= 4 && Usage == VectorUsage::Math)
  RefType w();

  template <int N = 4>
    requires(N == 4 && Dimension >= 4 && Usage == VectorUsage::Math)
  CRefType w() const;
#pragma endregion

#pragma region DimensionVectorComponents

  template <int N = 1>
    requires(N == 1 && Dimension >= 1 && Usage == VectorUsage::Size)
  RefType width();

  template <int N = 1>
    requires(N == 1 && Dimension >= 1 && Usage == VectorUsage::Size)
  CRefType width() const;

  template <int N = 2>
    requires(N == 2 && Dimension >= 2 && Usage == VectorUsage::Size)
  RefType height();

  template <int N = 2>
    requires(N == 2 && Dimension >= 2 && Usage == VectorUsage::Size)
  CRefType height() const;

  template <int N = 3>
    requires(N == 3 && Dimension >= 3 && Usage == VectorUsage::Size)
  RefType depth();

  template <int N = 3>
    requires(N == 3 && Dimension >= 3 && Usage == VectorUsage::Size)
  CRefType depth() const;

#pragma endregion

#pragma region ColorVectorComponents

  template <int N = 1>
    requires(N == 1 && Dimension >= 1 && Usage == VectorUsage::Color)
  RefType r();

  template <int N = 1>
    requires(N == 1 && Dimension >= 1 && Usage == VectorUsage::Color)
  CRefType r() const;

  template <int N = 2>
    requires(N == 2 && Dimension >= 2 && Usage == VectorUsage::Color)
  RefType g();

  template <int N = 2>
    requires(N == 2 && Dimension >= 2 && Usage == VectorUsage::Color)
  CRefType g() const;

  template <int N = 3>
    requires(N == 3 && Dimension >= 3 && Usage == VectorUsage::Color)
  RefType b();

  template <int N = 3>
    requires(N == 3 && Dimension >= 3 && Usage == VectorUsage::Color)
  CRefType b() const;

  template <int N = 4>
    requires(N == 4 && Dimension >= 4 && Usage == VectorUsage::Color)
  RefType a();

  template <int N = 4>
    requires(N == 4 && Dimension >= 4 && Usage == VectorUsage::Color)
  CRefType a() const;

#pragma endregion

  Pointer data();
  CPointer data() const;

  template <int N = 3>
    requires(N == Dimension) && (Dimension == 3)
  Vec cross(const Vec &other) const;

  template <typename U = T>
    requires std::is_same_v<U, T> && std::is_floating_point_v<U>
  Vec normalize() const;

  T dot(const Vec &other) const;
  T length() const;
  Vec rotate(const Quaternion<T> &rotation) const;

  Vec &operator+=(const Vec &other);
  Vec &operator-=(const Vec &other);
  Vec &operator*=(T scalar);
  Vec &operator/=(T scalar);
  bool operator==(const Vec &other) const;
  bool operator!=(const Vec &other) const;

  Iter begin();
  CIter begin() const;
  Iter end();
  CIter end() const;

private:
  std::array<T, Dimension> m_data;
};

} // namespace setsugen
