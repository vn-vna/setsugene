#include <setsugen/format.h>

#include <setsugen/exception.h>

namespace setsugen
{
Formatter::Formatter(const std::string& fmt_template) : m_fmt_template(fmt_template)
{
  parse_template();
}

std::string
Formatter::format(const FormatArgsStore& args) const
{
  std::stringstream result;

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

void
Formatter::stringify(const FormatContext& context) const
{}

void
Formatter::parse_template()
{
  size_t auto_index = 0;

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

void
parse_index(const std::string& index, size_t& auto_index, FormatPlaceholder& placeholder)
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
      placeholder.index = static_cast<size_t>(std::stoi(index));
    }
    catch (const std::invalid_argument&)
    {
      placeholder.index = index;
    }
  }
}

FormatPlaceholder
Formatter::parse_placeholder(StringIter start, StringIter end, size_t& auto_index)
{
  FormatPlaceholder placeholder{};

  auto iter  = start;
  bool colon = false;
  while (iter != end)
  {
    if (*iter == ':')
    {
      parse_index(std::string{start + 1, iter}, auto_index, placeholder);

      placeholder.format = std::string_view{iter + 1, end};
      placeholder.specs  = parse_specs(placeholder.format);
      colon              = true;
      break;
    }

    ++iter;
  }

  if (!colon)
  {
    parse_index(std::string{start + 1, iter}, auto_index, placeholder);
    placeholder.format = std::string_view{};
    placeholder.specs  = {};
  }

  return placeholder;
}

void
Formatter::emplace_placeholder(std::stringstream& ss, const FormatArgsStore& args,
                               const FormatPlaceholder& placeholder) const
{
  const auto& desc = args.get(placeholder.index);
  desc(ss, placeholder);
}

std::unordered_map<char, std::string_view>
Formatter::parse_specs(std::string_view format)
{
  std::unordered_map<char, std::string_view> specs;

  auto iter        = format.begin();
  auto end         = format.end();
  auto check_point = iter;

  while (iter != end)
  {
    if (*iter == ',')
    {
      if (auto next = check_point + 1; next != end && *next == '=')
      {
        specs[*check_point] = std::string_view{check_point + 2, iter};
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
      specs[*check_point] = std::string_view{check_point + 2, iter};
    }
    else
    {
      throw InvalidFormatException("Invalid format specs");
    }
  }

  return specs;
}

const std::string&
Formatter::get_template() const
{
  return m_fmt_template;
}
} // namespace setsugen
