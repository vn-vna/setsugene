#pragma once

#include <setsugen/pch.h>

#include <setsugen/format.h>
#include <setsugen/serde.h>

namespace setsugen
{

class CliCommand;
class CommandArgument;
class ExecutionData;

using CommandCallback = std::function<void(ExecutionData&)>;

class ExecutionData
{
public:
  friend class CliCommand;

  ExecutionData();

  SerializedData& get_argument(const std::string& name);

private:
  std::unordered_map<std::string, SerializedData> m_arguments;
};

class CommandArgument
{
public:
  friend class CliCommand;

  CommandArgument(const std::string& name, const std::string& description, SerializedType type = SerializedType::String,
                  const SerializedData& default_value = SerializedData::null());

private:
  std::string    m_name;
  std::string    m_description;
  SerializedType m_type;
  SerializedData m_default_value;
  SerializedData m_value;
};

class CliCommand
{
public:
  CliCommand(const std::string& name, const std::string& description, CommandCallback callback = nullptr);
  ~CliCommand();

  void add_argument(const std::string& name, const std::string& description,
                    SerializedType        type          = SerializedType::String,
                    const SerializedData& default_value = SerializedData::null());

  void parse(int argc, char** argv);

private:
  CommandCallback              m_callback;
  std::string                  m_name;
  std::string                  m_description;
  std::vector<CommandArgument> m_arguments;
  std::vector<CliCommand>      m_subcommands;
};

} // namespace setsugen
