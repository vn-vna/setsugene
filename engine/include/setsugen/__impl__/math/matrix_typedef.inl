#pragma once

namespace setsugen
{
#define DECLARE_MATRIX_ALIAS(typesym, type, col, row) \
  using Mat##col##x##row##typesym = Mat<type, col, row>; \
  extern template class Mat<type, col, row>;

#define DECLARE_MATRIX_OF_TYPE(typesym, type) \
  DECLARE_MATRIX_ALIAS(typesym, type, 2, 2) \
  DECLARE_MATRIX_ALIAS(typesym, type, 2, 3) \
  DECLARE_MATRIX_ALIAS(typesym, type, 2, 4) \
  DECLARE_MATRIX_ALIAS(typesym, type, 3, 2) \
  DECLARE_MATRIX_ALIAS(typesym, type, 3, 3) \
  DECLARE_MATRIX_ALIAS(typesym, type, 3, 4) \
  DECLARE_MATRIX_ALIAS(typesym, type, 4, 2) \
  DECLARE_MATRIX_ALIAS(typesym, type, 4, 3) \
  DECLARE_MATRIX_ALIAS(typesym, type, 4, 4)

DECLARE_MATRIX_OF_TYPE(I, int)
DECLARE_MATRIX_OF_TYPE(U, unsigned int)
DECLARE_MATRIX_OF_TYPE(F, float)
DECLARE_MATRIX_OF_TYPE(L, long long)
DECLARE_MATRIX_OF_TYPE(UL, unsigned long long)
DECLARE_MATRIX_OF_TYPE(LF, double)

#undef DECLARE_MATRIX_OF_TYPE
#undef DECLARE_MATRIX_ALIAS

#define DECLARE_SQUARE_MATRIX_ALIAS(typesym, type, size) \
  using Mat##size##typesym = Mat<type, size, size>; \
  extern template class Mat<type, size, size>;

#define DECLARE_SQUARE_MATRIX_OF_TYPE(typesym, type) \
  DECLARE_SQUARE_MATRIX_ALIAS(typesym, type, 2) \
  DECLARE_SQUARE_MATRIX_ALIAS(typesym, type, 3) \
  DECLARE_SQUARE_MATRIX_ALIAS(typesym, type, 4)

DECLARE_SQUARE_MATRIX_OF_TYPE(I, int)
DECLARE_SQUARE_MATRIX_OF_TYPE(U, unsigned int)
DECLARE_SQUARE_MATRIX_OF_TYPE(F, float)
DECLARE_SQUARE_MATRIX_OF_TYPE(L, long long)
DECLARE_SQUARE_MATRIX_OF_TYPE(UL, unsigned long long)
DECLARE_SQUARE_MATRIX_OF_TYPE(LF, double)

#undef DECLARE_SQUARE_MATRIX_OF_TYPE
#undef DECLARE_SQUARE_MATRIX_ALIAS
}
