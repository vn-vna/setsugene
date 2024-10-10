#pragma once

#include "cli_command-desc_flagdesc.inl"
#include "cli_exec-context.inl"

#include "../serde/serde_data.inl"

namespace setsugen
{

class CliExecutionContext::Flag
{
public:
  using Description = CliCommandDescription::FlagDescription;

  Flag(Description& desc);
  ~Flag();

  Description&    description();
  DArray<SerializedData>& value();

private:
  Description&                m_desc;
  DArray<SerializedData> m_values;
};

} // namespace setsugen
