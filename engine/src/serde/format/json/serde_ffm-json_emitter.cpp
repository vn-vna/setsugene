/**
 * FILE: serde_ffm-json_serializer.cpp
 *
 * Naming convention:
 * - Declaration header: serde.h
 * - Declaration part: json file format - serializer
 */

#include "serde_ffm-json.h"

namespace setsugen::emitter
{
inline Void
json_print_element(json_printer* p, Int32 el, const char* data, std::size_t len, Bool pretty)
{
  if (pretty)
  {
    json_print_pretty(p, el, data, len);
  }
  else
  {
    json_print_raw(p, el, data, len);
  }
}

JsonEmitter::JsonEmitter(OutputStream& stream, const SerializedData& data, const Json::Configurations& conf) noexcept
  : m_stream(stream),
    m_data(data),
    m_config(conf)
{
  StringStream ss;
  for (Int32 i = 0; i < conf.serializer_config.indent; ++i)
  {
    ss << conf.serializer_config.indent_char;
  }
  m_indent_str = ss.str();

  std::memset(&m_printer, 0, sizeof(m_printer));
  json_print_init(&m_printer, JsonEmitter::json_event_callback, this);
  m_printer.indentstr = m_indent_str.data();
}

JsonEmitter::~JsonEmitter() noexcept
{
  json_print_free(&m_printer);
}

Void
JsonEmitter::emit()
{
  this->emit(m_data);
}

Void
JsonEmitter::emit(const SerializedData& data)
{
  switch (data.get_type())
  {
    case SerializedType::Integer:
    {
      auto str = std::to_string(data.get_integer().value());
      json_print_element(&m_printer, JSON_INT, str.c_str(), str.size(),
                         m_config.serializer_config.pretty_print);
    }
    break;

    case SerializedType::Float:
    {
      auto str = std::to_string(data.get_float().value());
      json_print_element(&m_printer, JSON_FLOAT, str.c_str(), str.size(),
                         m_config.serializer_config.pretty_print);
    }

    case SerializedType::String:
    {
      json_print_element(&m_printer, JSON_STRING, data.get_string().value().c_str(), data.get_string().value().size(),
                         m_config.serializer_config.pretty_print);
    }
    break;

    case SerializedType::Bool:
    {
      json_print_element(&m_printer, data.get_bool().value() ? JSON_TRUE : JSON_FALSE, nullptr, 0,
                         m_config.serializer_config.pretty_print);
    }
    break;

    case SerializedType::Null:
    {
      json_print_element(&m_printer, JSON_NULL, nullptr, 0,
                         m_config.serializer_config.pretty_print);
    }
    break;

    case SerializedType::Array:
    {
      if (m_config.serializer_config.pretty_print)
      {
        json_print_pretty(&m_printer, JSON_ARRAY_BEGIN, nullptr, 0);
      }
      for (const auto& elem: data.get_array())
      {
        this->emit(elem);
      }
      if (m_config.serializer_config.pretty_print)
      {
        json_print_pretty(&m_printer, JSON_ARRAY_END, nullptr, 0);
      }
    }
    break;

    case SerializedType::Object:
    {
      json_print_pretty(&m_printer, JSON_OBJECT_BEGIN, nullptr, 0);
      for (const auto& [key, value]: data.get_object())
      {
        json_print_pretty(&m_printer, JSON_KEY, key.c_str(), key.size());
        this->emit(value);
      }
      json_print_pretty(&m_printer, JSON_OBJECT_END, nullptr, 0);
    }
    break;

    default:
    {
      throw InvalidArgumentException("Invalid data type");
    }
  }
}

Int32
JsonEmitter::json_event_callback(Void* userdata, const char* s, uint32_t length)
{
  auto* emitter = static_cast<JsonEmitter*>(userdata);
  emitter->m_stream.write(s, length);
  return 0;
}
}
