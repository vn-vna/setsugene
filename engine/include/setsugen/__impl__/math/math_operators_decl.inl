#pragma once

#include "math_fwd.inl"
#include "matrix_decl.inl"
#include "vector_decl.inl"

namespace setsugen
{

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
inline Vec<T, Dimension, Usage> operator+(const Vec<T, Dimension, Usage>& lhs, const Vec<T, Dimension, Usage>& rhs);

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
inline Vec<T, Dimension, Usage> operator-(const Vec<T, Dimension, Usage>& lhs, const Vec<T, Dimension, Usage>& rhs);

template<Arithmetic T, Arithmetic U, unsigned Dimension, VectorUsage Usage>
inline Vec<T, Dimension, Usage> operator*(const Vec<T, Dimension, Usage>& vec, U scalar);

template<Arithmetic T, Arithmetic U, unsigned Dimension, VectorUsage Usage>
inline Vec<T, Dimension, Usage> operator*(U scalar, const Vec<T, Dimension, Usage>& vec);

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
inline Vec<T, Dimension, Usage> operator/(const Vec<T, Dimension, Usage>& vec, T scalar);

template<Arithmetic T, unsigned Dimension, VectorUsage Usage>
inline Vec<T, Dimension, Usage> operator^(const Vec<T, Dimension, Usage>& lhs, const Vec<T, Dimension, Usage>& rhs)
  requires((Dimension == 3) && (Usage == VectorUsage::Math));

template<Arithmetic T, unsigned DimM, unsigned DimN>
Mat<T, DimM, DimN> operator+(const Mat<T, DimM, DimN>& lhs, const Mat<T, DimM, DimN>& rhs);

template<Arithmetic T, unsigned DimM, unsigned DimN>
Mat<T, DimM, DimN> operator-(const Mat<T, DimM, DimN>& lhs, const Mat<T, DimM, DimN>& rhs);

template<Arithmetic T, unsigned DimM, unsigned DimN>
Mat<T, DimM, DimN> operator*(const Mat<T, DimM, DimN>& mat, T scalar);

template<Arithmetic T, unsigned DimM, unsigned DimN>
Mat<T, DimM, DimN> operator*(T scalar, const Mat<T, DimM, DimN>& mat);

template<Arithmetic T, unsigned DimM, unsigned DimN>
Mat<T, DimM, DimN> operator/(const Mat<T, DimM, DimN>& mat, T scalar);

template<Arithmetic T, unsigned DimM, unsigned DimN, unsigned DimP>
Mat<T, DimM, DimP> operator*(const Mat<T, DimM, DimN>& lhs, const Mat<T, DimN, DimP>& rhs);

template<Arithmetic T, unsigned DimM, unsigned DimN>
Vec<T, DimM>
operator*(const Mat<T, DimM, DimN>& mat, const Vec<T, DimN>& vec);

} // namespace setsugen
