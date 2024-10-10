#pragma once

#include "../serde/serde_fwd.inl"
#include "cli_command-desc.inl"

namespace setsugen
{

class CliCommandDescription::FlagDescription
{
public:
  using DataType = CliCommandDescription::DataType;

  FlagDescription(const String& name, const String& description, Bool required, DataType type);
  ~FlagDescription();

  const String& name() const;
  const String& description() const;
  Bool               required() const;
  DataType           type() const;

private:
  String m_name;
  String m_description;
  Bool        m_required;
  DataType    m_type;
};

} // namespace setsugen
