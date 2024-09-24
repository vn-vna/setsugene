#pragma once

#include "math_fwd.inl"
#include "matrix_decl.inl"
#include "vector_decl.inl"

namespace setsugen
{

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

} // namespace setsugen
