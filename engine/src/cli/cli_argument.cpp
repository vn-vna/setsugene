#include <setsugen/cli.h>

namespace setsugen
{

CommandArgument::CommandArgument(const std::string& name, const std::string& description, SerializedType type,
                                 const SerializedData& default_value)
    : m_name(name), m_description(description), m_type(type), m_default_value(default_value), m_value(default_value)
{}

} // namespace setsugen
