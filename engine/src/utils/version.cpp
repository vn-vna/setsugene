#include <setsugen/version.h>

// C++ standard library
#include <sstream>

#define VERSION_MAJOR_MASK 4290772992U
#define VERSION_MINOR_MASK 4190208U
#define VERSION_PATCH_MASK 4095U

namespace setsugen
{

Version::Version() : Version(1, 0, 0)
{}

Version::Version(unsigned int major, unsigned int minor, unsigned int patch)
    : m_version((major << 22U) | (minor << 12U) | patch)
{}

Version::~Version() = default;

Version
Version::create_version(unsigned major, unsigned minor, unsigned patch)
{
  return {major, minor, patch};
}

unsigned int
Version::get_major() const
{
  return (m_version & VERSION_MAJOR_MASK) >> 22U;
}

unsigned int
Version::get_minor() const
{
  return (m_version & VERSION_MINOR_MASK) >> 12U;
}

unsigned int
Version::get_patch() const
{
  return (m_version & VERSION_PATCH_MASK);
}

void
Version::stringify(const FormatContext& context) const
{}

} // namespace setsugen
