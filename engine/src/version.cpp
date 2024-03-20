#include <setsugen/version.h>

// C++ standard library
#include <sstream>

// Dependency headers
#include <fmt/format.h>

#define VERSION_MAJOR_MASK 4290772992U
#define VERSION_MINOR_MASK 4190208U
#define VERSION_PATCH_MASK 4095U

namespace setsugen
{

Version::Version()
    : Version(1, 0, 0)
{}

Version::Version(UInt32 major, UInt32 minor, UInt32 patch)
    : m_version((major << 22U) | (minor << 12U) | patch)
{}

Version::~Version() = default;

Version Version::create_version(unsigned major, unsigned minor, unsigned patch)
{
  return {major, minor, patch};
}

UInt32 Version::get_major() const
{
  return (m_version & VERSION_MAJOR_MASK) >> 22U;
}

UInt32 Version::get_minor() const
{
  return (m_version & VERSION_MINOR_MASK) >> 12U;
}

UInt32 Version::get_patch() const
{
  return (m_version & VERSION_PATCH_MASK);
}

Void
Version::stringify(const FormatContext& context) const
{}

}  // namespace setsugen