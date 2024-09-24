#pragma once

#include "format_fwd.inl"

namespace setsugen
{

enum class TokenType
{
  Text,
  Placeholder
};


struct FormatPlaceholder
{
  using SpecsMapping = std::unordered_map<char, std::string_view>;

  FormatIndex      index;
  std::string_view format;
  SpecsMapping     specs;
};


struct FormatToken
{
  using TokenDetail = std::variant<FormatPlaceholder, std::string_view>;

  TokenType   type;
  TokenDetail details;
};


struct FormatContext
{
  std::stringstream& result;
  FormatPlaceholder  placeholder;
};


class ArgDescription
{
public:
  using FmtCall = std::function<void(std::stringstream&, const void*, const FormatPlaceholder&)>;
  using Deleter = std::function<void(void*)>;

  template<typename T>
  ArgDescription(const FmtCall& callback, T&& value);

  ~ArgDescription() noexcept;

  constexpr void operator()(std::stringstream& ss, const FormatPlaceholder& placeholder) const;

private:
  Deleter m_deleter;
  void*   m_data;
  FmtCall m_fmt_call;
};


class FormatArgsStore final
{
public:
  FormatArgsStore();
  ~FormatArgsStore();

  template<typename K, Formattable V>
  void                  set(K index, V&& value);
  const ArgDescription& get(const FormatIndex& index) const;

private:
  template<typename T>
  static FormatIndex create_index(T&& index);
  inline static int  get_int_spec(const std::string_view& view);

  std::unordered_map<FormatIndex, std::unique_ptr<ArgDescription>> m_args;
};


class Formatter final
{
public:
  using SpecsMapping = FormatPlaceholder::SpecsMapping;
  using StringIter   = std::string::const_iterator;

  Formatter(const std::string& fmt_template);
  ~Formatter() = default;

  const std::string& get_template() const;
  std::string        format(const FormatArgsStore& args) const;
  void               stringify(const FormatContext& context) const;

  template<typename... Args>
  static std::string format(const std::string& fmt_template, Args&&... args);

private:
  void              parse_template();
  FormatPlaceholder parse_placeholder(StringIter start, StringIter end, size_t& auto_index);
  SpecsMapping      parse_specs(std::string_view format);
  void              emplace_placeholder(std::stringstream& ss, const FormatArgsStore& args,
                                        const FormatPlaceholder& placeholder) const;

  std::list<FormatToken> m_tokens;
  std::string            m_fmt_template;
};


template<typename T>
class Stringify
{
public:
  static void stringify(const FormatContext& context, const T& value)
  {
    context.result << value;
  }
};

} // namespace setsugen
