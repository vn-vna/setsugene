#pragma once

#include "cli_fwd.inl"

namespace setsugen
{

class CliExecutionContext
{
public:
  class Flag;
  class Argument;

  friend class CliCommandParser;

  using FlagList         = DArray<Flag>;
  using ArgumentList     = DArray<Argument>;
  using ChildContextList = DArray<CliExecutionContext>;

  CliExecutionContext(CliCommandDescription& command);
  ~CliExecutionContext();

  Bool has_flag(const String& name);
  Bool has_argument(Int32 index);
  Bool has_child_context(const String& name);

  Flag&                flag(const String& name);
  Argument&            argument(Int32 index);
  CliExecutionContext& child_context(const String& name);

  ChildContextList& child_contexts();

private:
  CliCommandDescription& m_command;
  FlagList               m_flags;
  ArgumentList           m_arguments;
  ChildContextList       m_child_contexts;
};

} // namespace setsugen
