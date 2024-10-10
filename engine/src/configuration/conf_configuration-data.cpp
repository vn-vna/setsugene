#include <setsugen/conf.h>

namespace setsugen
{


Configuration::
Configuration()
{
  m_data = SerializedData::object({});
}

Configuration::
Configuration(const SerializedData& data)
{
  if (data.get_type() != SerializedType::Object)
  {
    throw InvalidArgumentException("Cannot create a configuration object from non-object SerializedData");
  }

  m_data = data;
}

Configuration::~Configuration() = default;

String
Configuration::get_string(const String& key, Optional<String> default_value) const
{
  auto data = dive(key);
  if (data && data->get_type() == SerializedType::String)
  {
    return data->get_string().value();
  }

  if (default_value.has_value())
  {
    return default_value.value();
  }

  throw InvalidArgumentException("Cannot find key {}", {key});
}

Int32
Configuration::get_int(const String& key, Optional<Int32> default_value) const
{
  auto data = dive(key);
  if (data && data->get_type() == SerializedType::Integer)
  {
    return data->get_integer().value();
  }

  if (default_value.has_value())
  {
    return default_value.value();
  }

  throw InvalidArgumentException("Cannot find key {}", {key});
}

Int64
Configuration::get_long(const String& key, Optional<Int64> default_value) const
{
  auto data = dive(key);
  if (data && data->get_type() == SerializedType::Integer)
  {
    return data->get_integer().value();
  }

  if (default_value.has_value())
  {
    return default_value.value();
  }

  throw InvalidArgumentException("Cannot find key {}", {key});
}

Float32
Configuration::get_float(const String& key, Optional<Float32> default_value) const
{
  auto data = dive(key);
  if (data && data->get_type() == SerializedType::Float)
  {
    return data->get_float().value();
  }

  if (default_value.has_value())
  {
    return default_value.value();
  }

  throw InvalidArgumentException("Cannot find key {}", {key});
}

Float64
Configuration::get_double(const String& key, Optional<Float64> default_value) const
{
  auto data = dive(key);
  if (data && data->get_type() == SerializedType::Float)
  {
    return data->get_float().value();
  }

  if (default_value.has_value())
  {
    return default_value.value();
  }

  throw InvalidArgumentException("Cannot find key {}", {key});
}

Configuration
Configuration::get_child(const String& key) const
{
  return Configuration{*dive(key)};
}


SerializedData*
Configuration::dive(const String& key) const
{
  auto key_view = key | std::views::split('.') |
                  std::views::transform(
                      [](auto&& sv) {
                        return String{sv.begin(), sv.end()};
                      }) |
                  std::views::common;

  auto* current = &m_data;
  for (const auto& key: key_view)
  {
    if (current->get_type() != SerializedType::Object)
    {
      return nullptr;
    }

    current = &(*current)[key];
  }

  return current;
}

SerializedData*
Configuration::dive_insert(const String& key) const
{
  auto key_view = key | std::views::split('.') |
                  std::views::transform(
                      [](auto&& sv) {
                        return String{sv.begin(), sv.end()};
                      }) |
                  std::views::common;

  auto* current   = &m_data;
  auto  key_depth = static_cast<UInt32>(std::distance(key_view.begin(), key_view.end()));
  auto  index     = 0;

  for (const auto& keystr: key_view)
  {
    if (current->get_type() != SerializedType::Object)
    {
      throw InvalidArgumentException("Invalid key {}", {key});
    }

    if (index != key_depth - 1 && !current->get_object().has_key(keystr))
    {
      (*current)[keystr] = SerializedData::object({});
    }

    current = &(*current)[keystr];
    ++index;
  }

  return current;
}

Void
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

Void
Configuration::change_value(const String& key, const SerializedData& value)
{
  auto key_view = key | std::views::split('.') |
                  std::views::transform(
                      [](auto&& sv) {
                        return String{sv.begin(), sv.end()};
                      }) |
                  std::views::common;

  auto* current = &m_data;
  for (const auto& key: key_view)
  {
    if (current->get_type() != SerializedType::Object)
    {
      throw InvalidArgumentException("Cannot change value of key {} due to invalid format", {key});
    }

    current = &(*current)[key];
  }
}

} // namespace setsugen
