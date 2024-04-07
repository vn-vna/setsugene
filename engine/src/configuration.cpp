#include <setsugen/configuration.h>

namespace setsugen
{

NoSectionFoundException::NoSectionFoundException(const std::string& section) : SetsugenException("Section not found")
{}

} // namespace setsugen
