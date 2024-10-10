#include <setsugen/math.h>

namespace setsugen
{


#define GENERATE_DEFINITION_FOR_VECTOR(type, size, usage) template class Vec<type, size, usage>;

#define GENERATE_DEFINITION_FOR_VECTOR_SIZE(type, size)                                                                \
  GENERATE_DEFINITION_FOR_VECTOR(type, size, VectorUsage::Math)                                                        \
  GENERATE_DEFINITION_FOR_VECTOR(type, size, VectorUsage::Color)                                                       \
  GENERATE_DEFINITION_FOR_VECTOR(type, size, VectorUsage::Size)

#define GENERATE_DEFINITION_FOR_VECTOR_TYPE(type)                                                                      \
  GENERATE_DEFINITION_FOR_VECTOR_SIZE(type, 2)                                                                         \
  GENERATE_DEFINITION_FOR_VECTOR_SIZE(type, 3)                                                                         \
  GENERATE_DEFINITION_FOR_VECTOR_SIZE(type, 4)

GENERATE_DEFINITION_FOR_VECTOR_TYPE(Bool);
GENERATE_DEFINITION_FOR_VECTOR_TYPE(Int8);
GENERATE_DEFINITION_FOR_VECTOR_TYPE(UInt8);
GENERATE_DEFINITION_FOR_VECTOR_TYPE(Int16);
GENERATE_DEFINITION_FOR_VECTOR_TYPE(UInt16);
GENERATE_DEFINITION_FOR_VECTOR_TYPE(Int32);
GENERATE_DEFINITION_FOR_VECTOR_TYPE(UInt32);
GENERATE_DEFINITION_FOR_VECTOR_TYPE(Int64);
GENERATE_DEFINITION_FOR_VECTOR_TYPE(UInt64);
GENERATE_DEFINITION_FOR_VECTOR_TYPE(Float32);
GENERATE_DEFINITION_FOR_VECTOR_TYPE(Float64);

} // namespace setsugen
