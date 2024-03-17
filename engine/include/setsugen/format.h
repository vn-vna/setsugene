#pragma once

#include <setsugen/pch.h>

// C++ standard headers
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>

namespace setsugen
{

class FormatArgsStore;
class Formatter;
class Formattable;

class Formattable
{
public:
  virtual        ~Formattable() = default;
  virtual String to_string() const = 0;
};

class FormatArgsStore
{
public:
  friend class Formatter;

public:
  FormatArgsStore();

  template <typename... Args>
  FormatArgsStore(Args... args)
      : FormatArgsStore()
  {
    (this->push_arg(args), ...);
  }

  virtual ~FormatArgsStore();

public:
  template <typename T>
  std::enable_if_t<!std::is_class_v<T>, FormatArgsStore&> apply_arg(const String& key, T value);

  template <typename T>
  std::enable_if_t<std::is_class_v<T>, FormatArgsStore&> apply_arg(
      const String& key, const T& value
  );

  template <typename T>
  std::enable_if_t<!std::is_class_v<T>, FormatArgsStore&> push_arg(T value);

  template <typename T>
  std::enable_if_t<std::is_class_v<T>, FormatArgsStore&> push_arg(const T& value);

public:
  static const FormatArgsStore NO_ARGS;

private:
  Void* mp_args;
};

class Formatter : public Formattable
{
public:
  Formatter(const String& fmt_template);
  ~Formatter() = default;

public:
  String format(const FormatArgsStore& args = FormatArgsStore::NO_ARGS) const;

  inline const String& get_template() const
  {
    return m_template;
  }

  String to_string() const override;

public:
  template <typename... Args>
  inline static String format(const String& fmt_template, Args&&... args)
  {
    FormatArgsStore store(std::forward<Args>(args)...);
    return Formatter(fmt_template).format(store);
  }

  template <typename... Args>
  inline static Void print(const String& fmt_template, Args&&... args)
  {
    std::cout << format(fmt_template, std::forward<Args>(args)...);
  }

private:
  String m_template;
};

}  // namespace setsugen
