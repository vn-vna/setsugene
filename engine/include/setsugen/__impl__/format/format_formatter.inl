#pragma once

#include "format_fwd.inl"

namespace setsugen
{

/**
 * @brief The Formatter class is used to format strings with placeholders.
 *
 * The Formatter class is used to format strings with placeholders. The placeholders are defined
 * by curly braces and can contain an optional index and format specifiers. The index is used to
 * specify the order of the arguments passed to the format method. If no index is specified, the
 * arguments are used in the order they are passed to the format method. The format specifiers are
 * used to format the argument value. The Formatter class is used to parse the template string and
 * replace the placeholders with the argument values.
 *
 * The code below show how to use the formatter
 * @code{cpp}
 * Formatter::format("Hello {}!", {"world", "moon"}); // Hello world!
 * @endcode
 */
class Formatter final
{
public:
  using SpecsMapping = FormatPlaceholder::SpecsMapping;
  using StringIter   = String::const_iterator;

  /**
   * @brief Construct a new Formatter object
   *
   * @param fmt_template The template string to use for formatting.
   */
  explicit Formatter(const String& fmt_template);

  ~Formatter() = default;

  /**
   * @brief Get the template string used for formatting.
   *
   * @return const String& The template string used for formatting.
   */
  const String& get_template() const;
  String        format(const FormatArgsStore& args) const;

  static String format(const String& fmt_template, Initializer<ArgDescription> args = {});

private:
  Void parse_template();

  FormatPlaceholder parse_placeholder(StringIter start, StringIter end, Int32& auto_index);

  SpecsMapping parse_specs(std::string_view format);

  Void emplace_placeholder(StringStream& ss, const FormatArgsStore& args,
                           const FormatPlaceholder& placeholder) const;

  std::list<FormatToken> m_tokens;
  String            m_fmt_template;
};


template<typename T>
class Stringify
{
public:
  static Void stringify(const FormatContext& context, const T& value)
  {
    context.result << value;
  }
};

template<>
class Stringify<Formatter>
{
public:
  static Void stringify(const FormatContext& context, const Formatter& value);
};

} // namespace setsugen
