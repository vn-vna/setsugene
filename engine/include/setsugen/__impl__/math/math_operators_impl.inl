#pragma once

#include "math_fwd.inl"
#include "matrix_decl.inl"
#include "vector_decl.inl"
#include "math_operators_decl.inl"

namespace setsugen
{

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
Vec<T, Dimension, Usage>
operator+(const Vec<T, Dimension, Usage>& lhs, const Vec<T, Dimension, Usage>& rhs)
{
  Vec<T, Dimension, Usage> result = lhs;
  for (Int32 i = 0; i < Dimension; ++i)
  {
    result.get(i) += rhs.get(i);
  }
  return result;
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
Vec<T, Dimension, Usage>
operator-(const Vec<T, Dimension, Usage>& lhs, const Vec<T, Dimension, Usage>& rhs)
{
  Vec<T, Dimension, Usage> result = lhs;
  for (Int32 i = 0; i < Dimension; ++i)
  {
    result.get(i) -= rhs.get(i);
  }
  return result;
}

template<Arithmetic T, Arithmetic U, unsigned Dimension, VectorUsage Usage>
Vec<T, Dimension, Usage>
operator*(const Vec<T, Dimension, Usage>& vec, U scalar)
{
  Vec<T, Dimension, Usage> result = vec;
  for (Int32 i = 0; i < Dimension; ++i)
  {
    result.get(i) *= scalar;
  }
  return result;
}

template<Arithmetic T, Arithmetic U, unsigned Dimension, VectorUsage Usage>
Vec<T, Dimension, Usage>
operator*(U scalar, const Vec<T, Dimension, Usage>& vec)
{
  return vec * scalar;
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
Vec<T, Dimension, Usage>
operator/(const Vec<T, Dimension, Usage>& vec, T scalar)
{
  Vec<T, Dimension, Usage> result = vec;
  for (Int32 i = 0; i < Dimension; ++i)
  {
    result.get(i) /= scalar;
  }
  return result;
}

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
Vec<T, Dimension, Usage>
operator^(const Vec<T, Dimension, Usage>& lhs, const Vec<T, Dimension, Usage>& rhs)
  requires((Dimension == 3) && (Usage == VectorUsage::Math))
{
  return Vec<T, Dimension, Usage>(           //
      lhs.y() * rhs.z() - lhs.z() * rhs.y(), //
      lhs.z() * rhs.x() - lhs.x() * rhs.z(), //
      lhs.x() * rhs.y() - lhs.y() * rhs.x()  //
  );                                         //
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
Mat<T, DimM, DimN>
operator+(const Mat<T, DimM, DimN>& lhs, const Mat<T, DimM, DimN>& rhs)
{
  Mat<T, DimM, DimN> result = lhs;
  for (Int32 i = 0; i < DimM * DimN; ++i)
  {
    result.data()[i] += rhs.data()[i];
  }
  return result;
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
Mat<T, DimM, DimN>
operator-(const Mat<T, DimM, DimN>& lhs, const Mat<T, DimM, DimN>& rhs)
{
  Mat<T, DimM, DimN> result = lhs;
  for (Int32 i = 0; i < DimM * DimN; ++i)
  {
    result.data()[i] -= rhs.data()[i];
  }
  return result;
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
Mat<T, DimM, DimN>
operator*(const Mat<T, DimM, DimN>& mat, T scalar)
{
  Mat<T, DimM, DimN> result = mat;
  for (Int32 i = 0; i < DimM * DimN; ++i)
  {
    result.data()[i] *= scalar;
  }
  return result;
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
Mat<T, DimM, DimN>
operator*(T scalar, const Mat<T, DimM, DimN>& mat)
{
  return mat * scalar;
}

template<Arithmetic T, unsigned DimM, unsigned DimN>
Mat<T, DimM, DimN>
operator/(const Mat<T, DimM, DimN>& mat, T scalar)
{
  Mat<T, DimM, DimN> result = mat;
  for (Int32 i = 0; i < DimM * DimN; ++i)
  {
    result.data()[i] /= scalar;
  }
  return result;
}


template<Arithmetic T, unsigned DimM, unsigned DimN, unsigned DimP>
Mat<T, DimM, DimP>
operator*(const Mat<T, DimM, DimN>& lhs, const Mat<T, DimN, DimP>& rhs)
{
  Mat<T, DimM, DimP> result;
  for (Int32 i = 0; i < DimM; ++i)
  {
    for (Int32 j = 0; j < DimP; ++j)
    {
      T sum = T();
      for (Int32 k = 0; k < DimN; ++k)
      {
        sum += lhs.get(i, k) * rhs.get(k, j);
      }
      result.get(i, j) = sum;
    }
  }
  return result;
}

} // namespace setsugen
