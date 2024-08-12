#pragma once

namespace setsugen
{
#define DECLARE_VECTORTYPE_ALIAS(prefix, usage, typesym, type, dimsize) \
  using prefix##dimsize##typesym = Vec<type, dimsize, VectorUsage::usage>; \
  extern template class Vec<type, dimsize, VectorUsage::usage>;

#define DECLARE_VECTORTYPE_OF_TYPE(prefix, usage, typesym, type) \
  DECLARE_VECTORTYPE_ALIAS(prefix, usage, typesym, type, 2)      \
  DECLARE_VECTORTYPE_ALIAS(prefix, usage, typesym, type, 3)      \
  DECLARE_VECTORTYPE_ALIAS(prefix, usage, typesym, type, 4)

#define DECLARE_VECTORTYPE_OF_USAGE(prefix, usage) \
  DECLARE_VECTORTYPE_OF_TYPE(prefix, usage, F, float) \
  DECLARE_VECTORTYPE_OF_TYPE(prefix, usage, LF, double) \
  DECLARE_VECTORTYPE_OF_TYPE(prefix, usage, I, int) \
  DECLARE_VECTORTYPE_OF_TYPE(prefix, usage, U, unsigned int) \
  DECLARE_VECTORTYPE_OF_TYPE(prefix, usage, L, long long) \
  DECLARE_VECTORTYPE_OF_TYPE(prefix, usage, UL, unsigned long long)

DECLARE_VECTORTYPE_OF_USAGE(Vec, Math)
DECLARE_VECTORTYPE_OF_USAGE(Color, Color)
DECLARE_VECTORTYPE_OF_USAGE(Dim, Size)
DECLARE_VECTORTYPE_OF_USAGE(Size, Size)

#undef DECLARE_VECTORTYPE_OF_USAGE
#undef DECLARE_VECTORTYPE_OF_TYPE
#undef DECLARE_VECTORTYPE_ALIAS

using Color = Color4F;
}
