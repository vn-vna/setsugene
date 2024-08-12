#pragma once

#define SETSUGENE_VERSION_MAJOR 0
#define SETSUGENE_VERSION_MINOR 1
#define SETSUGENE_VERSION_PATCH 0

#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
#define SETSUGENE_WINDOWS
#endif

#if defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
#define SETSUGENE_LINUX
#endif

#if defined(__APPLE__) || defined(__MACH__)
#define SETSUGENE_MACOS
#endif

#if defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
#define SETSUGENE_FREEBSD
#endif

#if defined(SETSUGENE_MACOS) || defined(SETSUGENE_FREEBSD)
#error "Unsupported platform"
#endif

#include <algorithm>
#include <any>
#include <array>
#include <atomic>
#include <condition_variable>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <deque>
#include <format>
#include <forward_list>
#include <fstream>
#include <functional>
#include <future>
#include <iomanip>
#include <ios>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <numbers>
#include <optional>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <thread>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>
#include <source_location>

