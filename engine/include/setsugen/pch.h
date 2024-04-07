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

// If we are on Windows, we need to include Windows.h before doing anything else.
#if defined(SETSUGENE_WINDOWS)

// Remove evil macro defined by Windows
#ifndef NOMINMAX
#define NOMINMAX
#endif // NOMINMAX

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

// Remove conflicting macros
#ifdef near
#undef near
#endif // near

#ifdef far
#undef far
#endif // far

#endif // SETSUGENE_WINDOWS

#include <any>
#include <array>
#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <deque>
#include <format>
#include <forward_list>
#include <fstream>
#include <functional>
#include <future>
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
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>
