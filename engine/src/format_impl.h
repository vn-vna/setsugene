#pragma once

#include <setsugen/format.h>

// Setsugen headers
#include <setsugen/exception.h>
#include <setsugen/logger.h>

// Dependency headers
#include <fmt/args.h>
#include <fmt/chrono.h>
#include <fmt/format.h>

#define EXPLICIT_INSTANTIATE_SETSUGEN_FORMAT_FOR_NONCLS(_T)                              \
  template FormatArgsStore& FormatArgsStore::apply_arg<_T>(const String& key, _T value); \
  template FormatArgsStore& FormatArgsStore::push_arg<_T>(_T value)

#define EXPLICIT_INSTANTIATE_SETSUGEN_FORMAT_FOR_CLS(_T)                                        \
  template FormatArgsStore& FormatArgsStore::apply_arg<_T>(const String& key, const _T& value); \
  template FormatArgsStore& FormatArgsStore::push_arg<_T>(const _T& value)

namespace setsugen
{

using FmtArgStore = fmt::dynamic_format_arg_store<fmt::format_context>;

template <typename T>
std::enable_if_t<!std::is_class_v<T>, FormatArgsStore&> FormatArgsStore::apply_arg(
    const String& key, T value
)
{
  auto pargs = static_cast<FmtArgStore*>(this->mp_args);
  pargs->push_back(fmt::arg(key.c_str(), value));
  return *this;
}

template <typename T>
std::enable_if_t<std::is_class_v<T>, FormatArgsStore&> FormatArgsStore::apply_arg(
    const String& key, const T& value
)
{
  auto pargs = static_cast<FmtArgStore*>(this->mp_args);
  if constexpr (std::is_base_of_v<Formattable, T>)
  {
    pargs->push_back(fmt::arg(key.c_str(), value.to_string()));
  }
  else
  {
    pargs->push_back(fmt::arg(key.c_str(), value));
  }
  return *this;
}

template <typename T>
std::enable_if_t<!std::is_class_v<T>, FormatArgsStore&> FormatArgsStore::push_arg(T value)
{
  auto pargs = static_cast<FmtArgStore*>(this->mp_args);
  pargs->push_back(value);
  return *this;
}

template <typename T>
std::enable_if_t<std::is_class_v<T>, FormatArgsStore&> FormatArgsStore::push_arg(const T& value)
{
  auto pargs = static_cast<FmtArgStore*>(this->mp_args);
  if constexpr (std::is_base_of_v<Formattable, T>)
  {
    pargs->push_back(value.to_string());
  }
  else
  {
    pargs->push_back(value);
  }
  return *this;
}
}  // namespace setsugen