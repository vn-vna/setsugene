#pragma once

#define SETSUGEN_CONCAT_IMPL(x, y) x##y
#define SETSUGEN_CONCAT(x, y) SETSUGEN_CONCAT_IMPL(x, y)

#define SETSUGEN_STRINGIFY_IMPL(x) #x
#define SETSUGEN_STRINGIFY(x) SETSUGEN_STRINGIFY_IMPL(x)

#define SETSUGEN_UNIQUE_NAME(base) SETSUGEN_CONCAT(base, __COUNTER__)

#define SETSUGEN_TRY_CATCH(expr)                            \
  try                                                       \
  {                                                         \
    expr;                                                   \
  }                                                         \
  catch (const ::setsugen::SetsugenException& e)            \
  {                                                         \
    std::cerr << "Exception: " << e.what() << std::endl;    \
  }                                                         \
  catch (const std::exception& e)                           \
  {                                                         \
    std::cerr << "Exception: " << e.what() << std::endl;    \
  }                                                         \
  catch (...)                                               \
  {                                                         \
    std::cerr << "An unknown error occurred" << std::endl;  \
  }
