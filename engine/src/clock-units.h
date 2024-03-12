#include <setsugen/clock.h>

// C++ Standard headers
#include <chrono>

namespace setsugen
{

using SystemClock       = std::chrono::system_clock;
using StdDuration       = std::chrono::system_clock::duration;
using StdTimePoint      = std::chrono::system_clock::time_point;
using DurationRepresent = UInt64;
using DurationRatio     = std::ratio<1L, 10'000'000>;  // 100ns precision
using DurationUnit      = std::chrono::duration<DurationRepresent, DurationRatio>;
using TimePointUnit     = std::chrono::time_point<SystemClock, DurationUnit>;

}  // namespace setsugen