#include <ranges>
#include <setsugen/format.h>

#include <setsugen/exception.h>
#include <string>
#include <string_view>
#include <tuple>

namespace setsugen
{
Formatter::Formatter(const String& fmt_template) : m_fmt_template(fmt_template)
{
  parse_template();
}

String
Formatter::format(const FormatArgsStore& args) const
{
  StringStream result;

  for (const auto& token: m_tokens)
  {
    switch (token.type)
    {
      case TokenType::Text:
      {
        result << std::get<std::string_view>(token.details);
      }
      break;
      case TokenType::Placeholder:
      {
        emplace_placeholder(result, args, std::get<FormatPlaceholder>(token.details));
      }
      break;
    }
  }

  return result.str();
}

String
Formatter::format(const String& fmt_template, Initializer<ArgDescription> args)
{
  Formatter       formatter(fmt_template);
  FormatArgsStore args_store(args);
  size_t          s = 0;
  return formatter.format(args_store);
}

Void
Formatter::parse_template()
{
  Int32 auto_index = 0;

  auto iter        = m_fmt_template.begin();
  auto check_point = iter;
  auto end         = m_fmt_template.end();
  Bool placeholder = false;

  while (iter != end)
  {
    if (*iter == '{')
    {
      auto next = iter + 1;
      if (next == end || *next == '{')
      {
        FormatToken token{};
        token.type    = TokenType::Text;
        token.details = std::string_view{check_point, iter};
        m_tokens.push_back(token);
        ++iter;
        continue;
      }

      placeholder = true;
      if (check_point != iter)
      {
        FormatToken token{};
        token.type    = TokenType::Text;
        token.details = std::string_view{check_point, iter};
        m_tokens.push_back(token);
      }

      check_point = iter;
    }
    else if (*iter == '}')
    {
      if (!placeholder)
      {
        throw InvalidFormatException("Place holder closed unmatched '}'");
      }

      FormatToken token{};
      token.type    = TokenType::Placeholder;
      token.details = parse_placeholder(check_point, iter, auto_index);
      m_tokens.push_back(token);

      placeholder = false;
      check_point = iter + 1;
    }

    ++iter;
  }

  if (check_point != iter)
  {
    FormatToken token{};
    token.type    = TokenType::Text;
    token.details = std::string_view{check_point, end};
    m_tokens.push_back(token);
  }
}

Void
parse_index(const String& index, Int32& auto_index, FormatPlaceholder& placeholder)
{
  if (index.empty())
  {
    placeholder.index = auto_index++;
  }
  else
  {
    try
    {
      placeholder.index = std::stoi(index);
    }
    catch (const std::invalid_argument&)
    {
      placeholder.index = index;
    }
  }
}

FormatPlaceholder
Formatter::parse_placeholder(StringIter start, StringIter end, Int32& auto_index)
{
  FormatPlaceholder placeholder{};

  auto iter  = start;
  Bool colon = false;
  while (iter != end)
  {
    if (*iter == ':')
    {
      parse_index(String{start + 1, iter}, auto_index, placeholder);

      placeholder.format = std::string_view{iter + 1, end};
      placeholder.specs  = parse_specs(placeholder.format);
      colon              = true;
      break;
    }

    ++iter;
  }

  if (!colon)
  {
    parse_index(String{start + 1, iter}, auto_index, placeholder);
    placeholder.format = std::string_view{};
    placeholder.specs  = {};
  }

  return placeholder;
}

Void
Formatter::emplace_placeholder(StringStream& ss, const FormatArgsStore& args,
                               const FormatPlaceholder& placeholder) const
{
  const auto& desc = args.get(placeholder.index);
  desc(ss, placeholder);
}

UnorderedMap<char, std::string_view>
Formatter::parse_specs(std::string_view format)
{
  UnorderedMap<char, std::string_view> specs;

  auto spec_view = //
      std::views::all(format) | std::views::split(',') |
      std::views::transform([](auto&& sv) { return std::views::all(sv) | std::views::split('='); }) |
      std::views::filter(
          [](auto kv) {
            return std::ranges::distance(kv) == 2 &&
                   std::ranges::distance((*kv.begin()).begin(), (*kv.begin()).end()) > 0;
          }) |
      std::views::transform(
          [](auto&& kv)
          {
            auto p = kv.begin();
            auto k = std::string_view((*p).begin(), (*p).end());
            ++p;
            auto v = std::string_view((*p).begin(), (*p).end());
            return std::make_tuple(k[0], v);
          });

  for (auto&& [k, v]: spec_view)
  {
    specs[k] = v;
  }

  return specs;
}

const String&
Formatter::get_template() const
{
  return m_fmt_template;
}

Void
Stringify<Formatter>::stringify(const FormatContext& context, const Formatter& value)
{
  context.result << "[[ Formatter: template = " << value.get_template() << " ]]";
}
} // namespace setsugen
