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
  Version(UInt32 version);
  Version(UInt32 major, UInt32 minor, UInt32 patch);

  ~Version();

  UInt32 get_major() const;
  UInt32 get_minor() const;
  UInt32 get_patch() const;
  UInt32 data() const;

  static Version create_version(UInt32 major, UInt32 minor, UInt32 patch);
  static Version from_string(const String& version);

private:
  UInt32 m_version;
};
} // namespace setsugen
