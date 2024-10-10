#pragma once

#include "cli_fwd.inl"

namespace setsugen
{

class CliCommandParser
{
public:
  CliCommandParser();
  CliCommandParser(const String& cli_string);
  CliCommandParser(const DArray<String>& args);
  CliCommandParser(Int32 argc, char** argv);
  ~CliCommandParser();

  CliExecutionContext parse(CliCommandDescription& desc);

private:
  Void parse_recursive(CliExecutionContext& context, Int32& index);
  Void parse_flag(const String& token, CliExecutionContext& context, Int32& index);
  Void parse_argument(const String& token, CliExecutionContext& context, Int32& index);

  DArray<String> m_args;
};

} // namespace setsugen
