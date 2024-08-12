#include "main.h"

#include <iostream>
#include <source_location>


#include <algorithm>
#include <array>
#include <iostream>
#include <source_location>
#include <string>
#include <string_view>

#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) ||      \
    defined(__ghs__)

#define __CURRENT_FUNCTION_NAME__ __PRETTY_FUNCTION__

#elif defined(__DMC__) && (__DMC__ >= 0x810)

#define __CURRENT_FUNCTION_NAME__ __PRETTY_FUNCTION__

#elif defined(__FUNCSIG__)

#define __CURRENT_FUNCTION_NAME__ __FUNCSIG__

#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))

#define __CURRENT_FUNCTION_NAME__ __FUNCTION__

#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)

#define __CURRENT_FUNCTION_NAME__ __FUNC__

#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)

#define __CURRENT_FUNCTION_NAME__ __func__

#elif defined(__cplusplus) && (__cplusplus >= 201103)

#define __CURRENT_FUNCTION_NAME__ __func__

#else

#define __CURRENT_FUNCTION_NAME__ "(unknown)"

#endif

template<typename... Args>
  requires(!std::is_same<Args, std::source_location>::value && ...)
struct push_log
{
  push_log(std::string message, Args... args, std::source_location loc = std::source_location::current())
  {
    printf(message.c_str(), args...);
  }
};

int
main()
{
}
