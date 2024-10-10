#pragma once

#include "cli_command-desc_flagdesc.inl"
#include "cli_exec-context.inl"

#include "../serde/serde_data.inl"

namespace setsugen
{

class CliExecutionContext::Argument
{
public:
  using Description = CliCommandDescription::ArgumentDescription;

  Argument(Description& desc, SerializedData&& value);
  ~Argument();

  Description&    description();
  SerializedData& value();

private:
  Description&   m_desc;
  SerializedData m_value;
};

} // namespace setsugen
