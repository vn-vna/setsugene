// IWYU pragma: private, include "setsugen/math.h"

#pragma once

#include <setsugen/pch.h>

#include <setsugen/exception.h>
#include <setsugen/types.h>

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
  requires ((DimM > 0) && (DimN > 0))
class Mat;

template<Arithmetic T>
class Quaternion;

} // namespace setsugen
