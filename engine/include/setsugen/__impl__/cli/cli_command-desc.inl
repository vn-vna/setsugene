#pragma once

#include "cli_fwd.inl"

namespace setsugen
{

class CliCommandDescription
{
public:
  enum class DataType;

  class Builder;
  class ArgumentDescription;
  class FlagDescription;

  friend class CliExecutor;
  friend class Builder;

  using SubCommandList    = DArray<CliCommandDescription>;
  using ArgumentList      = DArray<ArgumentDescription>;
  using FlagList          = DArray<FlagDescription>;
  using ExecutionCallback = std::function<Void(CliExecutionContext&)>;

  CliCommandDescription(const String& name, const String& description, ExecutionCallback&& callback);
  ~CliCommandDescription();

  Void execute(CliExecutionContext& context);

private:
  String       m_name;
  String       m_description;
  SubCommandList    m_subcommands;
  ArgumentList      m_arguments;
  FlagList          m_flags;
  ExecutionCallback m_callback;
};

enum class CliCommandDescription::DataType
{
  Bool,
  Integer,
  Float,
  String
};

} // namespace setsugen
