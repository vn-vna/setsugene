#pragma once

#include <setsugen/pch.h>
#include <setsugen/types.h>

namespace setsugen
{
template<typename T>
class Stringify;

struct FormatContext;
class Formatter;
class FormatArgsStore;
class ArgDescription;

using FormatIndex = std::variant<Int32, String>;

enum class TokenType
{
  Text,
  Placeholder
};


struct FormatPlaceholder
{
  using SpecsMapping = UnorderedMap<char, std::string_view>;

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
  StringStream& result;
  FormatPlaceholder  placeholder;
};

using FormatArgument = std::variant<ArgDescription, std::pair<String, ArgDescription>>;

} // namespace setsugen
