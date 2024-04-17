#pragma once

#include <setsugen/pch.h>

// Setsugen headers
#include <setsugen/format.h>

// C++ Standard Library
#include <string>

namespace setsugen
{
class Version
{
public:
  Version();
  Version(unsigned int major, unsigned int minor, unsigned int patch);
  ~Version();

public:
  static Version create_version(unsigned int major, unsigned int minor, unsigned int patch);

public:
  unsigned int get_major() const;
  unsigned int get_minor() const;
  unsigned int get_patch() const;

  void stringify(const FormatContext& context) const;

private:
  unsigned int m_version;
};
} // namespace setsugen
