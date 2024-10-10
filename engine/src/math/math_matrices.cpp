#include <setsugen/math.h>

namespace setsugen
{

#define GENERATE_DEFINITION_FOR_MATRIX(type, col, row) template class setsugen::Mat<type, col, row>;

#define GENERATE_DEFINITION_FOR_MATRIX_COL(type, col)                                                                  \
  GENERATE_DEFINITION_FOR_MATRIX(type, col, 2)                                                                         \
  GENERATE_DEFINITION_FOR_MATRIX(type, col, 3)                                                                         \
  GENERATE_DEFINITION_FOR_MATRIX(type, col, 4)

#define GENERATE_DEFINITION_FOR_MATRIX_TYPE(type)                                                                      \
  GENERATE_DEFINITION_FOR_MATRIX_COL(type, 2)                                                                          \
  GENERATE_DEFINITION_FOR_MATRIX_COL(type, 3)                                                                          \
  GENERATE_DEFINITION_FOR_MATRIX_COL(type, 4)

GENERATE_DEFINITION_FOR_MATRIX_TYPE(Bool)
GENERATE_DEFINITION_FOR_MATRIX_TYPE(Int8)
GENERATE_DEFINITION_FOR_MATRIX_TYPE(UInt8)
GENERATE_DEFINITION_FOR_MATRIX_TYPE(Int16)
GENERATE_DEFINITION_FOR_MATRIX_TYPE(UInt16)
GENERATE_DEFINITION_FOR_MATRIX_TYPE(Int32)
GENERATE_DEFINITION_FOR_MATRIX_TYPE(UInt32)
GENERATE_DEFINITION_FOR_MATRIX_TYPE(Int64)
GENERATE_DEFINITION_FOR_MATRIX_TYPE(UInt64)
GENERATE_DEFINITION_FOR_MATRIX_TYPE(Float32)
GENERATE_DEFINITION_FOR_MATRIX_TYPE(Float64)

} // namespace setsugen
