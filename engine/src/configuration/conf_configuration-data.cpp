#include <setsugen/conf.h>

namespace setsugen
{

Configuration::~Configuration() = default;

std::string
Configuration::get_string(const std::string& key) const
{
  return dive(key)->get_string().value();
}

int
Configuration::get_int(const std::string& key) const
{
  return dive(key)->get_integer().value();
}

long long
Configuration::get_long(const std::string& key) const
{
  return dive(key)->get_integer().value();
}

float
Configuration::get_float(const std::string& key) const
{
  return dive(key)->get_float().value();
}

double
Configuration::get_double(const std::string& key) const
{
  return dive(key)->get_float().value();
}

Configuration::Configuration()
{
  m_data = SerializedData::object({});
}

SerializedData*
Configuration::dive(const std::string& key) const
{
  auto key_view = key | std::views::split('.') |
                  std::views::transform([](auto&& sv) { return std::string{sv.begin(), sv.end()}; }) |
                  std::views::common;

  auto* current = &m_data;
  for (const auto& key: key_view)
  {
    if (current->get_type() != SerializedType::Object)
    {
      throw InvalidArgumentException("Configuration key '{}' is not an object", key);
    }

    current = &(*current)[key];
  }

  return current;
}

void
Configuration::merge(const SerializedData& other)
{
  if (other.get_type() != SerializedType::Object)
  {
    throw InvalidArgumentException("Cannot merge a non-object SerializedData into a Configuration");
  }

  for (const auto& [key, value]: other.get_object())
  {
    m_data[key] = value;
  }
}

void
Configuration::change_value(const std::string& key, const SerializedData& value)
{
  m_data[key] = value;
}

} // namespace setsugen
