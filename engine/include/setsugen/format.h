#pragma once

#include <iomanip>
#include <setsugen/pch.h>
#include <setsugen/exception.h>

namespace setsugen
{
struct FormatContext;

template <typename T>
class Stringify;
class Formatter;
class FormatArgsStore;
class FormatArg;

template <typename T>
concept Formattable = requires(const FormatContext& context, const T& value)
{
  { Stringify<T>::stringify(context, value) } -> std::same_as<Void>;
};

template <typename T>
class Stringify
{
public:
  static Void stringify(const FormatContext&, const T&)
  {
    throw NotImplementedException("Stringify has not been implemented for type");
  }
};


using FormatIndex = Variant<Size, String>;

template <typename T>
struct NamedArg
{
  String name;
  T      value;
};


enum class TokenType
{
  Text,
  Placeholder
};


struct FormatPlaceholder
{
  FormatIndex                    index;
  StringView                     format;
  UnorderedMap<Char, StringView> specs;
};

struct ArgDescription
{
  using FmtCall = Fn<Void(StringStream&, Void*, const FormatPlaceholder&)>;
  using Deleter = Fn<Void(Void*)>;

  template <typename T>
  ArgDescription(const FmtCall& callback, const T& value)
    : fmt_call{callback}
  {
    using ErasedValueType = std::remove_cvref_t<T>;

    data    = new ErasedValueType(value);
    deleter = [](Void* data)
    {
      delete static_cast<ErasedValueType*>(data);
    };
  }

  ~ArgDescription()
  {
    deleter(data);
  }

  Deleter deleter;
  Void*   data;
  FmtCall fmt_call;
};

struct FormatToken
{
  TokenType                              type;
  Variant<FormatPlaceholder, StringView> details;
};

struct FormatContext
{
  StringStream&     result;
  FormatPlaceholder placeholder;
};

class FormatArgsStore final
{
public:
  FormatArgsStore();
  ~FormatArgsStore();

  template <typename K, typename V>
  Void set(K index, V value)
  {
    using ErasedValueType = std::remove_cvref_t<V>;

    UniquePtr<ArgDescription> arg_fn = std::make_unique<ArgDescription>(
      [](StringStream& ss, Void* data, const FormatPlaceholder& placeholder)
      {
        auto fill_width_ptr = placeholder.specs.find('w');
        if (fill_width_ptr != placeholder.specs.end())
        {
          const auto fill_width = get_int_spec(fill_width_ptr->second);
          ss << std::setw(fill_width);
        }

        auto fill_char_ptr = placeholder.specs.find('c');
        if (fill_char_ptr != placeholder.specs.end() && !fill_char_ptr->second.empty())
        {
          auto fill_char = fill_char_ptr->second[0];
          ss << std::setfill(fill_char);
        }

        auto p = static_cast<ErasedValueType*>(data);
        if constexpr (Formattable<ErasedValueType>)
        {
          Stringify<ErasedValueType>::stringify(
            {
              .result = ss,
              .placeholder = placeholder
            },
            *p);
        }

        ss << std::setfill(' ');
        ss << std::setw(0);
      },
      value
    );


    const FormatIndex findex = erase_key_type(index);
    m_args[findex]           = std::move(arg_fn);
  }

  const ArgDescription& get(const FormatIndex& index) const;

  Void stringify(const FormatContext& context) const;

private:
  template <typename T>
  static constexpr auto erase_type(T t)
  {
    if constexpr (std::is_enum_v<T>)
    {
      return Int32{t};
    }
    else if constexpr (StringConcept<std::remove_cv_t<T>>)
    {
      return String{t};
    }
    else
    {
      return t;
    }
  }

  template <typename T>
  static constexpr auto erase_key_type(T key)
  {
    if constexpr (StringConcept<T>)
    {
      return String{key};
    }
    else if constexpr (std::is_arithmetic_v<T>)
    {
      return static_cast<Size>(key);
    }
    else
    {
      throw InvalidArgumentException("Invalid key type");
    }
  }

  inline static auto get_int_spec(const StringView& view)
  {
    char buffer[128];
    auto size = view.end() - view.begin();
    std::memcpy(buffer, view.data(), size);
    buffer[size] = '\0';
    return std::stoi(buffer);
  }

  UnorderedMap<FormatIndex, UniquePtr<ArgDescription>> m_args;
};


class Formatter final
{
public:
  using StringIter = String::const_iterator;

  Formatter(const String& fmt_template);
  ~Formatter() = default;

  String format(const FormatArgsStore& args) const;

  Void stringify(const FormatContext& context) const;

  template <typename... Args>
  static String format(const String& fmt_template, Args&&... args)
  {
    Formatter       formatter(fmt_template);
    FormatArgsStore args_store;
    Size            s = 0;
    (args_store.set(s++, std::forward<Args>(args)), ...);
    return formatter.format(args_store);
  }

private:
  Void parse_template();
  FormatPlaceholder parse_placeholder(StringIter& start, StringIter end, Size& auto_index);
  Void emplace_placeholder(StringStream& ss, const FormatArgsStore& args, const FormatPlaceholder& placeholder) const;
  UnorderedMap<Char, StringView> parse_specs(StringView format);

  List<FormatToken> m_tokens;
  String            m_fmt_template;
};

// Implement the stringify function for all types that are formattable
template <StringConcept T>
class Stringify<T>
{
public:
  using ValueType = T;

  static Void stringify(const FormatContext& context, const ValueType& value)
  {
    context.result << value;
  }
};

template <Arithmetic T>
class Stringify<T>
{
public:
  using ValueType = T;

  static Void stringify(const FormatContext& context, const ValueType& value)
  {
    context.result << value;
  }
};
} // namespace setsugen
