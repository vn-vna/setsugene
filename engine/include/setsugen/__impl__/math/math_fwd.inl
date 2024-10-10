// IWYU pragma: private, include "setsugen/math.h"

#pragma once

#include <setsugen/pch.h>

#include <setsugen/exception.h>
#include <setsugen/types.h>

namespace setsugen
{

/**
 * @brief The VectorUsage enum is used to specify the usage of a vector.
 *
 * The VectorUsage enum is used to specify the usage of a vector. The usage of a vector can be
 * math, size, or color. The math usage is used to represent vectors in mathematical operations. The
 * size usage is used to represent vectors that represent the size of an object. The color usage is
 * used to represent vectors that represent the color of an object.
 */
enum class VectorUsage
{
  /**
   * @brief The vector is used for mathematical operations.
   */
  Math,

  /**
   * @brief The vector is used to represent the size of an object.
   */
  Size,

  /**
   * @brief The vector is used to represent the color of an object.
   */
  Color
};

enum class AngleUnit
{
  Radian,
  Degree,
  Grad,
  Arcminute,
};

template<AngleUnit Repr>
class Angle;

template<typename T>
concept AngleType = std::is_same_v<T, Angle<AngleUnit::Radian>> || std::is_same_v<T, Angle<AngleUnit::Degree>> ||
                    std::is_same_v<T, Angle<AngleUnit::Grad>> || std::is_same_v<T, Angle<AngleUnit::Arcminute>>;
template<Arithmetic T, unsigned Dimension, VectorUsage Usage = VectorUsage::Math>
class Vec;

template<Arithmetic T, unsigned DimM, unsigned DimN>
class Mat;

template<Arithmetic T>
class Quaternion;

} // namespace setsugen
