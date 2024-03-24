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
concept Formattable = requires(const FormatContext& context, Observer<const T> value)
{
  { Stringify<T>::stringify(context, value) } -> std::same_as<Void>;
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
  using FmtCall = Fn<Void(StringStream&, const Void*, const FormatPlaceholder&)>;
  using Deleter = Fn<Void(Void*)>;

  template <typename T>
  ArgDescription(const FmtCall& callback, const Observer<T> value)
    : data{value},
      fmt_call{callback}
  {}

  Deleter     deleter;
  const Void* data;
  FmtCall     fmt_call;
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

template <typename T>
class Stringify
{
public:
  static Void stringify(const FormatContext& context, Observer<const T> value)
  {
    context.result << *value;
  }
};


class FormatArgsStore final
{
public:
  FormatArgsStore();
  ~FormatArgsStore();

  template <typename K, Formattable V>
  Void set(K index, const V& value)
  {
    using ErasedType = std::remove_pointer_t<std::remove_cvref_t<V>>;

    Observer<const ErasedType> ptr = nullptr;

    if constexpr (std::is_pointer_v<V>)
    {
      // T *const
      ptr = value;
    }
    else
    {
      // T const
      ptr = &value;
    }

    UniquePtr<ArgDescription> arg_fn = std::make_unique<ArgDescription>(
      [](StringStream& ss, const Void* data, const FormatPlaceholder& placeholder)
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

        auto p = static_cast<Observer<const ErasedType>>(data);
        Stringify<ErasedType>::stringify(
          {
            .result = ss,
            .placeholder = placeholder
          },
          p);

        ss << std::setfill(' ');
        ss << std::setw(0);
      },
      ptr
    );

    const FormatIndex findex = erase_key_type(index);
    m_args[findex]           = std::move(arg_fn);
  }

  template <typename K, Formattable V>
  Void set(K index, const V* value)
  {
    set(index, *value);
  }


  const ArgDescription& get(const FormatIndex& index) const;

  Void stringify(const FormatContext& context) const;

private:
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

template <>
class Stringify<String>
{
public:
  static Void stringify(const FormatContext& context, Observer<const String> value)
  {
    context.result << *value;
  }
};

template <>
class Stringify<Char>
{
  static Void stringify(const FormatContext& context, Observer<const Char> value)
  {
    context.result << value;
  }
};
} // namespace setsugen
