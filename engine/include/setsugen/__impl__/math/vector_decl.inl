#pragma once

#include "./math_fwd.inl"

namespace setsugen
{

/**
 * @brief The Vec class is a generic class for representing vectors of different dimensions.
 *
 * The Vec class is a generic class for representing vectors of different dimensions. The Vec class
 * is a fixed-size array of elements of type T. The Vec class provides methods for accessing the
 * elements of the vector, performing vector operations, and performing arithmetic operations on
 * the vector.
 *
 * @tparam T The type of the elements in the vector.
 * @tparam Dimension The number of elements in the vector.
 * @tparam Usage The usage of the vector (e.g., math, size, color).
 */
template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
class Vec
{

public:
  using ValueType   = T;
  using Pointer     = ValueType*;
  using CPointer    = const ValueType*;
  using RefType     = ValueType&;
  using CRefType    = const ValueType&;
  using StorageType = Array<ValueType, Dimension>;
  using Iter        = typename StorageType::iterator;
  using CIter       = typename StorageType::const_iterator;

  /**
   * @brief Construct a new empty Vec object.
   *
   * The default constructor initializes the vector with zero values.
   */
  Vec();

  /**
   * @brief Construct a new Vec object with the given values.
   *
   * The constructor initializes the vector with the given values. The number of values must match
   * the dimension of the vector.
   *
   * @param args The values to initialize the vector with.
   */
  template<typename... Args>
    requires(sizeof...(Args) == Dimension) && (std::is_convertible_v<Args, T> && ...)
  Vec(Args... args);

  /**
   * @brief Copy constructor.
   *
   * The copy constructor initializes the vector with the values of another vector.
   *
   * @param other The other vector to copy.
   */
  Vec(const Vec& other);

  /**
   * @brief Move constructor.
   *
   * The move constructor initializes the vector by moving the values of another vector.
   *
   * @param other The other vector to move.
   */
  Vec(Vec&& other) noexcept;

  ~Vec() noexcept;

  /**
   * @brief Copy assignment operator.
   *
   * The copy assignment operator assigns the values of another vector to this vector.
   *
   * @param other The other vector to copy.
   * @return Vec& A reference to this vector.
   */
  Vec& operator=(const Vec& other);

  /**
   * @brief Move assignment operator.
   *
   * The move assignment operator assigns the values of another vector to this vector by moving the
   * values of the other vector.
   *
   * @param other The other vector to move.
   * @return Vec& A reference to this vector.
   */
  Vec& operator=(Vec&& other) noexcept;

  /**
   * @brief Access an element of the Vec
   *
   * @param index Element index (0-based)
   * @return Value of the element at the given index
   */
  RefType get(Int32 index);

  /**
   * @brief Access an element of the Vec
   *
   * @param index Element index (0-based)
   * @return Value of the element at the given index
   */
  CRefType get(Int32 index) const;

#pragma region NormalVectorComponents

  /**
   * @brief Get a reference to the x-component of the vector (1st element).
   *
   * The x-component of the vector is the first element of the vector. The x-component is used to
   * represent the horizontal component of the vector in a 2D or 3D space.
   *
   * @note This method is only available for vectors with a dimension of 1 or greater and a usage of
   * VectorUsage::Math.
   *
   * @return RefType A reference to the x-component of the vector.
   */
  RefType x()
    requires(Dimension >= 1 && Usage == VectorUsage::Math);

  /**
   * @brief Get a const reference to the x-component of the vector (1st element).
   *
   * The x-component of the vector is the first element of the vector. The x-component is used to
   * represent the horizontal component of the vector in a 2D or 3D space.
   *
   * @note This method is only available for vectors with a dimension of 1 or greater and a usage of
   * VectorUsage::Math.
   *
   * @return CRefType A const reference to the x-component of the vector.
   */
  CRefType x() const
    requires(Dimension >= 1 && Usage == VectorUsage::Math);

  /**
   * @brief Get a reference to the y-component of the vector (2nd element).
   *
   * The y-component of the vector is the second element of the vector. The y-component is used to
   * represent the vertical component of the vector in a 2D or 3D space.
   *
   * @note This method is only available for vectors with a dimension of 2 or greater and a usage of
   * VectorUsage::Math.
   *
   * @return RefType A reference to the y-component of the vector.
   */
  RefType y()
    requires(Dimension >= 2 && Usage == VectorUsage::Math);

  /**
   * @brief Get a const reference to the y-component of the vector (2nd element).
   *
   * The y-component of the vector is the second element of the vector. The y-component is used to
   * represent the vertical component of the vector in a 2D or 3D space.
   *
   * @note This method is only available for vectors with a dimension of 2 or greater and a usage of
   * VectorUsage::Math.
   *
   * @return CRefType A const reference to the y-component of the vector.
   */
  CRefType y() const
    requires(Dimension >= 2 && Usage == VectorUsage::Math);

  /**
   * @brief Get a reference to the z-component of the vector (3rd element).
   *
   * The z-component of the vector is the third element of the vector. The z-component is used to
   * represent the depth component of the vector in a 3D space.
   *
   * @note This method is only available for vectors with a dimension of 3 or greater and a usage of
   * VectorUsage::Math.
   *
   * @return RefType A reference to the z-component of the vector.
   */
  RefType z()
    requires(Dimension >= 3 && Usage == VectorUsage::Math);

  /**
   * @brief Get a const reference to the z-component of the vector (3rd element).
   *
   * The z-component of the vector is the third element of the vector. The z-component is used to
   * represent the depth component of the vector in a 3D space.
   *
   * @note This method is only available for vectors with a dimension of 3 or greater and a usage of
   * VectorUsage::Math.
   *
   * @return CRefType A const reference to the z-component of the vector.
   */
  CRefType z() const
    requires(Dimension >= 3 && Usage == VectorUsage::Math);

  /**
   * @brief Get a reference to the w-component of the vector (4th element).
   *
   * The w-component of the vector is the fourth element of the vector. The w-component is used to
   * represent the homogeneous component of the vector in a 3D space.
   *
   * @note This method is only available for vectors with a dimension of 4 or greater and a usage of
   * VectorUsage::Math.
   *
   * @return RefType A reference to the w-component of the vector.
   */
  RefType w()
    requires(Dimension >= 4 && Usage == VectorUsage::Math);

  /**
   * @brief Get a const reference to the w-component of the vector (4th element).
   *
   * The w-component of the vector is the fourth element of the vector. The w-component is used to
   * represent the homogeneous component of the vector in a 3D space.
   *
   * @note This method is only available for vectors with a dimension of 4 or greater and a usage of
   * VectorUsage::Math.
   *
   * @return CRefType A const reference to the w-component of the vector.
   */
  CRefType w() const
    requires(Dimension >= 4 && Usage == VectorUsage::Math);
#pragma endregion

#pragma region DimensionVectorComponents

  RefType width()
    requires(Dimension >= 1 && Usage == VectorUsage::Size);

  CRefType width() const
    requires(Dimension >= 1 && Usage == VectorUsage::Size);

  RefType height()
    requires(Dimension >= 2 && Usage == VectorUsage::Size);

  CRefType height() const
    requires(Dimension >= 2 && Usage == VectorUsage::Size);

  RefType depth()
    requires(Dimension >= 3 && Usage == VectorUsage::Size);

  CRefType depth() const
    requires(Dimension >= 3 && Usage == VectorUsage::Size);

#pragma endregion

#pragma region ColorVectorComponents

  RefType r()
    requires(Dimension >= 1 && Usage == VectorUsage::Color);

  CRefType r() const
    requires(Dimension >= 1 && Usage == VectorUsage::Color);

  RefType g()
    requires(Dimension >= 2 && Usage == VectorUsage::Color);

  CRefType g() const
    requires(Dimension >= 2 && Usage == VectorUsage::Color);

  RefType b()
    requires(Dimension >= 3 && Usage == VectorUsage::Color);

  CRefType b() const
    requires(Dimension >= 3 && Usage == VectorUsage::Color);

  RefType a()
    requires(Dimension >= 4 && Usage == VectorUsage::Color);

  CRefType a() const
    requires(Dimension >= 4 && Usage == VectorUsage::Color);

#pragma endregion

  /**
   * @brief Get a pointer to the data of the vector.
   *
   * @return Pointer A pointer to the data of the vector.
   */
  Pointer data();

  /**
   * @brief Get a const pointer to the data of the vector.
   *
   * @return CPointer A const pointer to the data of the vector.
   */
  CPointer data() const;

  Vec cross(const Vec& other) const
    requires(Dimension == 3);

  Vec normalize() const
    requires(FloatingPointType<T>);

  /**
   * @brief Calculate the dot product of this vector with another vector.
   *
   * The dot product of two vectors is the sum of the products of the corresponding elements of the
   * two vectors: dot(a, b) = a.x * b.x + a.y * b.y + a.z * b.z + ...
   *
   * @param other The other vector to calculate the dot product with.
   * @return T The dot product of this vector with the other vector.
   */
  T dot(const Vec& other) const;

  /**
   * @brief Calculate the length of the vector.
   *
   * The length of a vector is the square root of the sum of the squares of the elements of the vector.
   *
   * @note The result type is the same as the element type of the vector. If the element type is an integer
   * type, the result will be truncated to an integer, so it is recommended to use a floating-point type
   * for the element type of the vector.
   *
   * @return T The length of the vector.
   */
  T length() const;

  /**
   * @brief Rotate the vector by a quaternion.
   */
  Vec rotate(const Quaternion<T>& rotation) const;

  /**
   * @brief Get an iterator to the beginning of the vector data.
   *
   * This method is used to iterate over the elements of the vector using a range-based for loop.
   * Example:
   * @code
   * Vec<Float32, 3> vec(1.0f, 2.0f, 3.0f);
   * for (auto& value : vec)
   * {
   *   std::cout << value << std::endl;
   * }
   * @endcode
   *
   * @return Iter An iterator to the beginning of the vector data.
   */
  Iter begin();

  /**
   * @brief Get a const iterator to the beginning of the vector data.
   *
   * @return CIter A const iterator to the beginning of the vector data.
   */
  CIter begin() const;

  /**
   * @brief Get an iterator to the end of the vector data.
   *
   * @return Iter An iterator to the end of the vector data.
   */
  Iter end();

  /**
   * @brief Get a const iterator to the end of the vector data.
   *
   * @return CIter A const iterator to the end of the vector data.
   */
  CIter end() const;

private:
  Array<T, Dimension> m_data;
};

} // namespace setsugen
