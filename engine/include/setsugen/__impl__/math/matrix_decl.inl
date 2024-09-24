#pragma once

#include "./math_fwd.inl"

namespace setsugen {

template <Arithmetic T, int DimM, int DimN>
  requires((DimM > 0) && (DimN > 0))
class Mat {
public:
  Mat();
  Mat(const std::array<T, DimM * DimN> &data);
  Mat(const Mat &other);
  Mat(Mat &&other) noexcept;
  ~Mat() = default;

  Mat &operator=(const Mat &other);
  Mat &operator=(Mat &&other) noexcept;

  template <int SubDimM, int SubDimN>
    requires((SubDimM > 0) && (SubDimM < DimM) && (SubDimN > 0) &&
             (SubDimN < DimN))
  Mat<T, SubDimM, SubDimN> submatrix(int row, int col) const;

  T *data();
  const T *data() const;

  template <int DimP>
  Mat<T, DimM, DimP> operator*(const Mat<T, DimN, DimP> &other) const;

  Vec<T, DimM> operator*(const Vec<T, DimN> &vec) const;

  T &get(int row, int col);
  T get(int row, int col) const;

  Mat &operator+=(const Mat &other);
  Mat &operator-=(const Mat &other);
  Mat &operator*=(T scalar);
  Mat &operator/=(T scalar);
  bool operator==(const Mat &other) const;
  bool operator!=(const Mat &other) const;

  T *begin();
  const T *begin() const;
  T *end();
  const T *end() const;

  Mat<T, DimN, DimM> transpose() const;

  template <int IDimM = DimM, int IDimN = DimN>
    requires((IDimM == DimN) && (IDimN == DimN) && (DimM == DimN))
  T minor(int row, int col) const;

  template <int IDimM = DimM, int IDimN = DimN>
    requires((IDimM == DimN) && (IDimN == DimN) && (DimM == DimN))
  T determinant();

  /// @brief Create an identity matrix
  /// @return The identity matrix
  template <int IDimM = DimM, int IDimN = DimN>
    requires((IDimM == DimM) && (IDimN == DimN))
  static Mat<T, IDimM, IDimN> identity();

  /// @brief Create a perspective projection matrix
  /// @param fov Field of view in degrees
  /// @param aspect Aspect ratio
  /// @param near Near plane
  /// @param far Far plane
  /// @return The perspective projection matrix
  template <int IDimM = DimM, int IDimN = DimN>
    requires(std::is_floating_point_v<T> && (IDimM == DimM) &&
             (IDimN == DimN) && (IDimM == 4))
  static Mat<T, IDimM, IDimN> perspective(T fov, T aspect, T near, T far);

  /// @brief Create an orthographic projection matrix
  /// @param left The minimum x-coordinate of the view volume
  /// @param right The maximum x-coordinate of the view volume
  /// @param bottom The minimum y-coordinate of the view volume
  /// @param top The maximum y-coordinate of the view volume
  /// @param near The minimum z-coordinate of the view volume
  /// @param far The maximum z-coordinate of the view volume
  /// @return The orthographic projection matrix
  template <int IDimM = DimM, int IDimN = DimN>
    requires(std::is_floating_point_v<T> && (IDimM == DimM) &&
             (IDimN == DimN) && (IDimM == 4))
  static Mat<T, IDimM, IDimN> orthographic(T left, T right, T bottom, T top,
                                           T near, T far);

  /// @brief Create a translation matrix
  /// @param translation The translation vector
  /// @return The translation matrix
  template <int IDimM = DimM, int IDimN = DimN>
    requires(std::is_arithmetic_v<T> && (IDimM == DimM) && (IDimN == DimN))
  static Mat<T, IDimM, IDimN> translation(const Vec<T, IDimM - 1> &translation);

  /// @brief Create a rotation matrix
  /// @param rotation The rotation vector
  /// @return The rotation matrix
  template <int IDimM = DimM, int IDimN = DimN>
    requires(std::is_arithmetic_v<T> && (IDimM == DimM) && (IDimN == DimN))
  static Mat<T, IDimM, IDimN> rotation(const Vec<T, 3> &rotation);

  /// @brief Create a scale matrix
  /// @param scale The scale vector
  /// @return The scale matrix
  template <int IDimM = DimM, int IDimN = DimN>
    requires(std::is_arithmetic_v<T> && (IDimM == DimM) && (IDimN == DimN))
  static Mat<T, IDimM, IDimN> scale(const Vec<T, 3> &scale);

  /// @brief Create a look-at matrix
  /// @param eye The eye position
  /// @param center The center position
  /// @param up The up vector
  /// @return The look-at matrix
  template <int IDimM = DimM, int IDimN = DimN>
    requires(std::is_arithmetic_v<T> && (IDimM == DimM) && (IDimN == DimN))
  static Mat<T, IDimM, IDimN>
  look_at(const Vec<T, 3> &eye, const Vec<T, 3> &center, const Vec<T, 3> &up);

private:
  std::array<T, DimM * DimN> m_data;
};

} // namespace setsugen
