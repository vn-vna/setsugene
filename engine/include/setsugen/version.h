#pragma once

#include <setsugen/pch.h>

// Setsugen headers
#include <setsugen/format.h>

// C++ Standard Library
#include <string>

namespace setsugen
{

class Version : public Formattable
{
public:
  Version();
  Version(UInt32 major, UInt32 minor, UInt32 patch);
  ~Version();

public:
  static Version create_version(UInt32 major, UInt32 minor, UInt32 patch);

public:
  UInt32 get_major() const;
  UInt32 get_minor() const;
  UInt32 get_patch() const;

  String to_string() const override;

private:
  UInt32 m_version;
};

}  // namespace setsugen