#pragma once

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
#include <vector>

namespace setsugen
{
using Void   = void;
using Byte   = uint8_t;
using Int8   = int8_t;
using Int16  = int16_t;
using Int32  = int32_t;
using Int64  = int64_t;
using UInt8  = uint8_t;
using UInt16 = uint16_t;
using UInt32 = uint32_t;
using UInt64 = uint64_t;
using Float  = float;
using Double = double;
using Bool   = bool;
using Size   = size_t;

using Char  = char;
using WChar = wchar_t;

using String  = std::string;
using WString = std::wstring;

using Thread = std::thread;

template <typename T>
using SharedPtr = std::shared_ptr<T>;

template <typename T>
using UniquePtr = std::unique_ptr<T>;

template <typename T>
using WeakPtr = std::weak_ptr<T>;

template <typename T>
using Optional = std::optional<T>;

template <typename T>
using Fn = std::function<T>;

template <typename T>
using DArray = std::vector<T>;

template <typename T>
using Queue = std::queue<T>;

template <typename T>
using Stack = std::stack<T>;

template <typename T>
using Deque = std::deque<T>;

template <typename T, size_t N>
using Array = std::array<T, N>;

template <typename T>
using ForwardList = std::forward_list<T>;

template <typename T>
using List = std::list<T>;

template <typename K, typename V>
using Map = std::map<K, V>;

template <typename T>
using Set = std::set<T>;

template <typename K, typename V>
using UnorderedMap = std::unordered_map<K, V>;

template <typename T>
using UnorderedSet = std::unordered_set<T>;

template <typename... T>
using Tuple = std::tuple<T...>;

template <typename T>
using Atomic = std::atomic<T>;

template <typename T>
using AtomicPtr = std::atomic<T*>;

template <typename T>
using Future = std::future<T>;

template <typename T>
using Promise = std::promise<T>;

using StringView = std::string_view;

using Mutex               = std::mutex;
using MutexGuard          = std::lock_guard<Mutex>;
using UniqueLock          = std::unique_lock<Mutex>;
using ConditionalVariable = std::condition_variable;
using AtomicFlag          = std::atomic_flag;

using Stream        = std::iostream;
using IStream       = std::istream;
using OStream       = std::ostream;
using FileStream    = std::fstream;
using IFileStream   = std::ifstream;
using OFileStream   = std::ofstream;
using StringStream  = std::stringstream;
using IStringStream = std::istringstream;
using OStringStream = std::ostringstream;
using Path          = std::filesystem::path;

using TypeInfo = std::type_info;

template <typename T>
using EnableSelfShared = std::enable_shared_from_this<T>;

template <typename T = Void>
using Observer = T*;

using Handler = Observer<Void>;

} // namespace setsugen
