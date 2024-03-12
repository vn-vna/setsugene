#include <setsugen/configuration.h>

namespace setsugen
{

NoSectionFoundException::NoSectionFoundException(const String& section)
    : SetsugenException("Section not found")
{}

}  // namespace setsugen