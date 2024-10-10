#pragma once

#include "./math_fwd.inl"

namespace setsugen
{

/**
 * @brief The Mat class is a generic class for representing matrices of different dimensions.
 *
 * The Mat class is a generic class for representing matrices of different dimensions. The Mat class
 * is a fixed-size array of elements of type T. The Mat class provides methods for accessing the
 * elements of the matrix, performing matrix operations, and performing arithmetic operations on
 * the matrix.
 *
 * @tparam T The type of the elements in the matrix.
 * @tparam DimM The number of rows in the matrix.
 * @tparam DimN The number of columns in the matrix.
 */
template<Arithmetic T, unsigned DimM, unsigned DimN>
class Mat
{
public:
  using ValueType   = T;
  using Pointer     = ValueType*;
  using CPointer    = const ValueType*;
  using RefType     = ValueType&;
  using CRefType    = const ValueType&;
  using StorageType = Array<ValueType, DimM * DimN>;
  using Iter        = typename StorageType::iterator;
  using CIter       = typename StorageType::const_iterator;

  /**
   * @brief Construct a new empty Mat object.
   *
   * The default constructor initializes the matrix with zero values.
   */
  Mat();

  /**
   * @brief Construct a new Mat object with the given values.
   *
   * The constructor initializes the matrix with the given values. The number of values must match
   * the number of elements in the matrix.
   *
   * @param data The values to initialize the matrix with.
   */
  Mat(const Array<T, DimM * DimN>& data);

  /**
   * @brief Copy constructor.
   *
   * The copy constructor initializes the matrix with the values of another matrix.
   *
   * @param other The other matrix to copy.
   */
  Mat(const Mat& other);

  /**
   * @brief Move constructor.
   *
   * The move constructor initializes the matrix by moving the values of another matrix.
   *
   * @param other The other matrix to move.
   */
  Mat(Mat&& other) noexcept;

  /**
   * @brief Destructor.
   */
  ~Mat() = default;

  /**
   * @brief Copy assignment operator.
   *
   * The copy assignment operator assigns the values of another matrix to this matrix.
   *
   * @param other The other matrix to copy.
   * @return Mat& A reference to this matrix.
   */
  Mat& operator=(const Mat& other);

  /**
   * @brief Move assignment operator.
   *
   * The move assignment operator assigns the values of another matrix to this matrix by moving the
   * values of the other matrix.
   *
   * @param other The other matrix to move.
   * @return Mat& A reference to this matrix.
   */
  Mat& operator=(Mat&& other) noexcept;

  /**
   * @brief Get the number of rows in the matrix.
   *
   * @return unsigned The number of rows in the matrix.
   */
  template<unsigned SubDimM, unsigned SubDimN>
    requires((SubDimM < DimM) && (SubDimN < DimN))
  Mat<T, SubDimM, SubDimN> submatrix(Int32 row, Int32 col) const;

  T*       data();
  const T* data() const;

  T& get(Int32 row, Int32 col);
  T  get(Int32 row, Int32 col) const;

  Mat& operator+=(const Mat& other);
  Mat& operator-=(const Mat& other);
  Mat& operator*=(T scalar);
  Mat& operator/=(T scalar);
  Bool operator==(const Mat& other) const;
  Bool operator!=(const Mat& other) const;

  T*       begin();
  const T* begin() const;
  T*       end();
  const T* end() const;

  /**
   * @brief Get the transpose of the matrix.
   *
   * The transpose of a matrix is a new matrix where the rows of the original matrix are the columns
   * of the new matrix and the columns of the original matrix are the rows of the new matrix.
   *
   * @return Mat The transpose of the matrix.
   */
  Mat<T, DimN, DimM> transpose() const;

  /**
   * @brief Get the minor of the matrix.
   *
   * The minor of a matrix is the determinant of the submatrix obtained by removing the row and column
   * of the given element.
   *
   * @param row The row of the element.
   * @param col The column of the element.
   * @return T The minor of the matrix.
   */
  T minor(Int32 row, Int32 col) const
    requires((DimM == DimN) && (DimM > 1));

  /**
   * @brief Get the determinant of the matrix.
   *
   * The determinant of a matrix is a scalar value that is used to determine the invertibility of the
   * matrix. The determinant of a matrix is calculated using the Laplace expansion.
   *
   * @return T The determinant of the matrix.
   */
  T determinant() const
    requires(DimM == DimN);

  /**
   * @brief Get the identity matrix.
   *
   * The identity matrix is a square matrix where the diagonal elements are 1 and the off-diagonal
   * elements are 0.
   *
   * @return Mat The identity matrix.
   */
  static Mat identity()
    requires(DimM == DimN);

  /**
   * @brief Create a perspective projection matrix.
   *
   * @param fov The field of view angle in degrees.
   * @param aspect The aspect ratio of the view volume.
   * @param near The near clipping plane.
   * @param far The far clipping plane.
   * @return The perspective projection matrix.
   */
  static Mat perspective(T fov, T aspect, T near, T far)
    requires(FloatingPointType<T> && (DimM == 4) && (DimN == 4));

  /**
   * @brief Create an orthographic projection matrix.
   *
   * @param left The left clipping plane.
   * @param right The right clipping plane.
   * @param bottom The bottom clipping plane.
   * @param top The top clipping plane.
   * @param near The near clipping plane.
   * @param far The far clipping plane.
   * @return The orthographic projection matrix.
   */
  static Mat orthographic(T left, T right, T bottom, T top, T near, T far)
    requires(FloatingPointType<T> && (DimM == 4) && (DimN == 4));

  /**
   * @brief Create a 3D translation matrix.
   *
   * @param translation The translation vector.
   * @return The translation matrix.
   */
  static Mat translation(const Vec<T, 3>& translation)
    requires(FloatingPointType<T> && (DimM == 4) && (DimN == 4));

  /**
   * @brief Create a 2D translation matrix.
   */
  static Mat translation(const Vec<T, 2>& translation)
    requires(FloatingPointType<T> && (DimM == 3) && (DimN == 3));

  /**
   * @brief Create a 3D rotation matrix.
   *
   * @param rotation The rotation vector.
   * @return The rotation matrix.
   */
  static Mat rotation(const Vec<T, 3>& rotation)
    requires(FloatingPointType<T> && (DimM == 4) && (DimN == 4));

  /**
   * @brief Create a 2D rotation matrix.
   *
   * @param rotation The rotation vector.
   * @return The rotation matrix.
   */
  static Mat rotation(const Vec<T, 2>& rotation)
    requires(FloatingPointType<T> && (DimM == 3) && (DimN == 3));

  /**
   * @brief Create a 3D scale matrix.
   *
   * @param scale The scale vector.
   * @return The scale matrix.
   */
  static Mat scale(const Vec<T, 3>& scale)
    requires(FloatingPointType<T> && (DimM == 4) && (DimN == 4));

  /**
   * @brief Create a 2D scale matrix.
   */
  static Mat scale(const Vec<T, 2>& scale)
    requires(FloatingPointType<T> && (DimM == 3) && (DimN == 3));

  /**
   * @brief Create a look-at matrix
   *
   * The look-at matrix is used to create a view matrix that looks at a given center position from a
   * given eye position with a given up vector.
   *
   * @param eye The eye position.
   * @param center The center position.
   * @param up The up vector.
   * @return The look-at matrix.
   */
  static Mat<T, DimM, DimN> look_at(const Vec<T, 3>& eye, const Vec<T, 3>& center, const Vec<T, 3>& up)
    requires(FloatingPointType<T> && (DimM == 4) && (DimN == 4));

private:
  Array<T, DimM * DimN> m_data;
};

} // namespace setsugen
