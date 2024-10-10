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

// IWYU pragma: begin_exports

#include <algorithm>
#include <any>
#include <array>
#include <atomic>
#include <cmath>
#include <condition_variable>
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
#include <ranges>
#include <semaphore>
#include <set>
#include <source_location>
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

// IWYU pragma: end_exports

namespace setsugen
{

using Void               = void;
using Bool               = bool;
using Int8               = std::int8_t;
using Int16              = std::int16_t;
using Int32              = std::int32_t;
using Int64              = std::int64_t;
using UInt8              = std::uint8_t;
using UInt16             = std::uint16_t;
using UInt32             = std::uint32_t;
using UInt64             = std::uint64_t;
using PtrInt             = std::size_t;
using PtrDiff            = std::ptrdiff_t;
using Float32            = float;
using Float64            = double;
using Char               = char;
using Byte               = std::byte;
using WChar              = wchar_t;
using String             = std::string;
using WString            = std::wstring;
using StringView         = std::string_view;
using WStringView        = std::wstring_view;
using SourceLocation     = std::source_location;
using Stream             = std::iostream;
using InputStream        = std::istream;
using OutputStream       = std::ostream;
using StringStream       = std::stringstream;
using StringInputStream  = std::istringstream;
using StringOutputStream = std::ostringstream;
using FileStream         = std::fstream;
using FileInputStream    = std::ifstream;
using FileOutputStream   = std::ofstream;
using FileBuffer         = std::filebuf;

template<typename T, PtrInt Size>
using Array = std::array<T, Size>;

template<typename T, typename Aloc = std::allocator<T>>
using DArray = std::vector<T, Aloc>;

template<typename T, typename Aloc = std::allocator<T>>
using Deque = std::deque<T, Aloc>;

template<typename T, typename Cmp = std::less<T>, typename Aloc = std::allocator<T>>
using Set = std::set<T, Cmp, Aloc>;

template<typename T, typename Cmp = std::less<T>, typename Aloc = std::allocator<T>>
using Multiset = std::multiset<T, Cmp, Aloc>;

template<typename T, typename Hsh = std::hash<T>, typename Eq = std::equal_to<T>, typename Aloc = std::allocator<T>>
using UnorderedSet = std::unordered_set<T, Hsh, Eq, Aloc>;

template<typename T, typename Hsh = std::hash<T>, typename Eq = std::equal_to<T>, typename Aloc = std::allocator<T>>
using UnorderedMultiset = std::unordered_multiset<T, Hsh, Eq, Aloc>;

template<typename K, typename V, typename Cmp = std::less<K>, typename Aloc = std::allocator<std::pair<const K, V>>>
using Map = std::map<K, V, Cmp, Aloc>;

template<typename K, typename V, typename Cmp = std::less<K>, typename Aloc = std::allocator<std::pair<const K, V>>>
using Multimap = std::multimap<K, V, Cmp, Aloc>;

template<typename K, typename V, typename Hsh = std::hash<K>, typename Eq = std::equal_to<K>,
         typename Aloc = std::allocator<std::pair<const K, V>>>
using UnorderedMap = std::unordered_map<K, V, Hsh, Eq, Aloc>;

template<typename K, typename V, typename Hsh = std::hash<K>, typename Eq = std::equal_to<K>,
         typename Aloc = std::allocator<std::pair<const K, V>>>
using UnorderedMultimap = std::unordered_multimap<K, V, Hsh, Eq, Aloc>;

template<typename T, typename Cmp = std::less<T>, typename Aloc = std::allocator<T>>
using PriorityQueue = std::priority_queue<T, Deque<T, Aloc>, Cmp>;

template<typename T, typename Cmp = std::less<T>, typename Aloc = std::allocator<T>>
using Queue = std::queue<T, Deque<T, Aloc>>;

template<typename T, typename Cmp = std::less<T>, typename Ctnr = Deque<T>>
using Stack = std::stack<T, Ctnr>;

template<typename T, typename Aloc = std::allocator<T>>
using List = std::list<T, Aloc>;

template<typename T, typename Aloc = std::allocator<T>>
using ForwardList = std::forward_list<T, Aloc>;

template<typename T, PtrInt Extent = std::dynamic_extent>
using Span = std::span<T, Extent>;

template<typename T, typename Deleter = std::default_delete<T>>
using Owner = std::unique_ptr<T, Deleter>;

template<typename T>
using Shared = std::shared_ptr<T>;

template<typename T>
using Weak = std::weak_ptr<T>;

template<typename T>
using Initializer = std::initializer_list<T>;

template<typename T>
using Optional = std::optional<T>;

template<typename T>
using Fn = std::function<T>;

template<typename... Ts>
using Tuple = std::tuple<Ts...>;

template<typename... Ts>
using Variant = std::variant<Ts...>;

template<typename T>
using NumericLimits = std::numeric_limits<T>;

template<typename T>
using Atomic = std::atomic<T>;

using Thread              = std::thread;
using Mutex               = std::mutex;
using Lock                = std::lock_guard<Mutex>;
using ULock               = std::unique_lock<Mutex>;
using ConditionalVariable = std::condition_variable;

template<PtrDiff LeastMaxValue>
using Semaphore = std::counting_semaphore<LeastMaxValue>;

using BinarySemaphore = Semaphore<1>;

template<typename T>
using Ref = std::reference_wrapper<T>;

template<typename T>
using CRef = std::reference_wrapper<const T>;

template<typename T>
using Observer = T*;

} // namespace setsugen
