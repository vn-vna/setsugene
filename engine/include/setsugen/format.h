#pragma once

#include <setsugen/pch.h>
#include <setsugen/types.h>


namespace setsugen
{
struct FormatContext;

template<typename T>
class Stringify;
class Formatter;
class FormatArgsStore;

using FormatIndex = std::variant<size_t, std::string>;


enum class TokenType
{
  Text,
  Placeholder
};


struct FormatPlaceholder
{
  using SpecsMapping = std::unordered_map<char, std::string_view>;

  FormatIndex index;
  std::string_view format;
  SpecsMapping specs;
};


struct FormatToken
{
  using TokenDetail = std::variant<FormatPlaceholder, std::string_view>;

  TokenType type;
  TokenDetail details;
};


struct FormatContext
{
  std::stringstream &result;
  FormatPlaceholder placeholder;
};


class ArgDescription
{
public:
  using FmtCall = std::function<void(std::stringstream &, const void *, const FormatPlaceholder &)>;
  using Deleter = std::function<void(void *)>;


  template<typename T>
  ArgDescription(const FmtCall &callback, T &&value) : m_fmt_call{callback}
  {
    using ErasedType = std::remove_cvref_t<T>;
    if constexpr (std::is_lvalue_reference_v<T>)
    {
      m_data = reinterpret_cast<void*>(const_cast<ErasedType*>(&value));
      m_deleter = [] (void *)
          {};
    } else
    {
      m_data = new ErasedType{std::forward<T>(value)};
      m_deleter = [] (void *data)
      {
        delete reinterpret_cast<ErasedType*>(data);
      };
    }
  }


  ~ArgDescription()
  {
    m_deleter(m_data);
  }


  constexpr void operator()(std::stringstream &ss, const FormatPlaceholder &placeholder) const
  {
    std::invoke(m_fmt_call, ss, m_data, placeholder);
  }

private:
  Deleter m_deleter;
  void *m_data;
  FmtCall m_fmt_call;
};


class FormatArgsStore final
{
public:
  FormatArgsStore();

  ~FormatArgsStore();


  template<typename K, Formattable V>
  void set(K index, V &&value)
  {
    using ErasedType = std::remove_cvref_t<V>;
    auto arg_fn = std::make_unique<ArgDescription>(
      [] (std::stringstream &ss, const void *data, const FormatPlaceholder &placeholder)
      {
        std::stringstream temp;

        if (placeholder.specs.contains('w'))
        {
          temp << std::setw(get_int_spec(placeholder.specs.at('w')));
        }

        if (placeholder.specs.contains('p'))
        {
          temp << std::setprecision(get_int_spec(placeholder.specs.at('p')));
        }

        Stringify<ErasedType>::stringify({temp, placeholder}, *reinterpret_cast<const ErasedType*>(data));
        ss << temp.str();
      },
      std::forward<V>(value));
    FormatIndex findex = create_index(index);
    m_args[findex] = std::move(arg_fn);
  }


  const ArgDescription &get(const FormatIndex &index) const;

private:
  template<typename T>
  inline static FormatIndex create_index(T &&index)
  {
    if constexpr (StringType<std::remove_cvref_t<T>>)
    {
      return std::string(index);
    } else
    {
      return std::forward<T>(index);
    }
  }


  inline static int get_int_spec(const std::string_view &view)
  {
    char buffer[128];
    auto size = view.end() - view.begin();
    std::memcpy(buffer, view.data(), size);
    buffer[size] = '\0';
    return std::stoi(buffer);
  }


  std::unordered_map<FormatIndex, std::unique_ptr<ArgDescription>> m_args;
};


class Formatter final
{
public:
  using SpecsMapping = FormatPlaceholder::SpecsMapping;
  using StringIter = std::string::const_iterator;

  Formatter(const std::string &fmt_template);

  ~Formatter() = default;

  const std::string &get_template() const;

  std::string format(const FormatArgsStore &args) const;

  void stringify(const FormatContext &context) const;


  template<typename... Args>
  static std::string format(const std::string &fmt_template, Args &&... args)
  {
    Formatter formatter(fmt_template);
    FormatArgsStore args_store;
    size_t s = 0;
    (args_store.set(s++, std::forward<Args>(args)), ...);
    return formatter.format(args_store);
  }

private:
  void parse_template();

  FormatPlaceholder parse_placeholder(StringIter start, StringIter end, size_t &auto_index);

  void emplace_placeholder(std::stringstream &ss, const FormatArgsStore &args,
                           const FormatPlaceholder &placeholder) const;

  SpecsMapping parse_specs(std::string_view format);

  std::list<FormatToken> m_tokens;
  std::string m_fmt_template;
};


template<typename T>
class Stringify
{
public:
  static void stringify(const FormatContext &context, const T &value)
  {
    context.result << value;
  }
};


template<>
class Stringify<Formatter>
{
public:
  static void stringify(const FormatContext &context, const Formatter &value)
  {
    context.result << "[[ Formatter: template = " << value.get_template() << " ]]";
  }
};
} // namespace setsugen
