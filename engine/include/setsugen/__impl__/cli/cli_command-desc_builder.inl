#pragma once

#include "cli_command-desc.inl"

namespace setsugen
{

class CliCommandDescription::Builder
{
public:
  Builder();
  ~Builder();

  Builder& subcommand(const String& name, const String& description, ExecutionCallback&& callback);
  Builder& argument(const String& description, Bool required);
  Builder& flag(const String& name, const String& description, Bool required);

  CliCommandDescription build();

private:
  CliCommandDescription m_command;
};

} // namespace setsugen
