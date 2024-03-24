#include <setsugen/format.h>

#include <setsugen/exception.h>

namespace setsugen
{
Formatter::Formatter(const String& fmt_template)
  : m_fmt_template(fmt_template)
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
        result << std::get<StringView>(token.details);
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

Void
Formatter::stringify(const FormatContext& context) const
{}

Void
Formatter::parse_template()
{
  Size auto_index = 0;

  auto iter        = m_fmt_template.begin();
  auto check_point = iter;
  auto end         = m_fmt_template.end();
  bool placeholder = false;

  while (iter != end)
  {
    if (*iter == '{')
    {
      auto next = iter + 1;
      if (next == end || *next == '{')
      {
        FormatToken token{};
        token.type    = TokenType::Text;
        token.details = StringView{check_point, iter};
        m_tokens.push_back(token);
        ++iter;
        continue;
      }

      placeholder = true;
      if (check_point != iter)
      {
        FormatToken token{};
        token.type    = TokenType::Text;
        token.details = StringView{check_point, iter};
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
    token.details = StringView{check_point, end};
    m_tokens.push_back(token);
  }
}

Void
parse_index(const String& index, Size& auto_index, FormatPlaceholder& placeholder)
{
  if (index.empty())
  {
    ++auto_index;
    placeholder.index = auto_index - 1;
  }
  else
  {
    try
    {
      placeholder.index = static_cast<Size>(std::stoi(index));
    }
    catch (const std::invalid_argument&)
    {
      placeholder.index = index;
    }
  }
}

FormatPlaceholder
Formatter::parse_placeholder(StringIter& start, StringIter end, Size& auto_index)
{
  FormatPlaceholder placeholder{};

  auto iter  = start;
  Bool colon = false;
  while (iter != end)
  {
    if (*iter == ':')
    {
      parse_index(String{start + 1, iter}, auto_index, placeholder);

      placeholder.format = StringView{iter + 1, end};
      placeholder.specs  = parse_specs(placeholder.format);
      colon              = true;
      break;
    }

    ++iter;
  }

  if (!colon)
  {
    parse_index(String{start + 1, iter}, auto_index, placeholder);
    placeholder.format = StringView{};
    placeholder.specs  = {};
  }

  return placeholder;
}

Void
Formatter::emplace_placeholder(StringStream&            ss, const FormatArgsStore& args,
                               const FormatPlaceholder& placeholder) const
{
  const auto& desc = args.get(placeholder.index);
  desc.fmt_call(ss, desc.data, placeholder);
}

UnorderedMap<Char, StringView>
Formatter::parse_specs(StringView format)
{
  UnorderedMap<Char, StringView> specs;

  auto iter        = format.begin();
  auto end         = format.end();
  auto check_point = iter;

  while (iter != end)
  {
    if (*iter == ',')
    {
      if (auto next = check_point + 1; next != end && *next == '=')
      {
        specs[*check_point] = StringView{check_point + 2, iter};
        check_point         = iter + 1;
      }
      else
      {
        throw InvalidFormatException("Invalid format specs");
      }
    }

    ++iter;
  }

  if (check_point != iter)
  {
    if (const auto next = check_point + 1; next != end && *next == '=')
    {
      specs[*check_point] = StringView{check_point + 2, iter};
    }
    else
    {
      throw InvalidFormatException("Invalid format specs");
    }
  }

  return specs;
}
} // namespace setsugen
