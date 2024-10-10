#pragma once

#include "cli_command-desc.inl"

namespace setsugen
{

class CliCommandDescription::ArgumentDescription
{
public:
  ArgumentDescription(const String& description, Bool required);
  ~ArgumentDescription();

  const String& description() const;
  Bool               required() const;

private:
  String m_description;
  Bool        m_required;
};

} // namespace setsugen
