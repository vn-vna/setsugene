#include "serde_ffm-json.h"
#include "json.h"
#include "setsugen/exception.h"
#include "setsugen/serde.h"
#include <cstring>

namespace setsugen::parser
{
JsonParser::JsonParser(std::istream& stream, SerializedData& data)
  : m_stream(stream),
    m_data(data)
{
  std::memset(&m_parser, 0, sizeof(m_parser));
  json_parser_init(&m_parser, nullptr, JsonParser::json_event_callback, static_cast<void*>(this));
}

JsonParser::~JsonParser()
{
  json_parser_free(&m_parser);
}

void
JsonParser::parse()
{
  constexpr const std::size_t buffer_size = 1024;
  char                        buffer[buffer_size];
  m_key     = std::nullopt;
  m_current = nullptr;

  while (m_stream.good())
  {
    m_stream.read(buffer, sizeof(buffer));

    if (m_stream.gcount() == 0)
    {
      break;
    }

    int ret = json_parser_string(&m_parser, buffer, m_stream.gcount(), nullptr);
    if (!ret)
    {
      continue;
    }

    switch (ret)
    {
      case JSON_ERROR_BAD_CHAR: throw InvalidSyntaxException("Bad character in JSON stream");

      case JSON_ERROR_NESTING_LIMIT: throw InvalidSyntaxException("Nesting limit reached in JSON stream");

      case JSON_ERROR_NO_MEMORY: throw OutOfMemoryException("Out of memory while parsing JSON stream");

      case JSON_ERROR_COMMENT_NOT_ALLOWED: throw InvalidSyntaxException("Comments are not allowed in JSON stream");

      case JSON_ERROR_DATA_LIMIT: throw OutOfMemoryException("Data limit reached in JSON stream");

      default: throw InvalidSyntaxException("Unknown error while parsing JSON stream");
    }
  }
}

int
JsonParser::json_event_callback(void* userdata, int type, const char* data, uint32_t len)
{
  auto parser = static_cast<JsonParser*>(userdata);

  switch (type)
  {
    case JSON_OBJECT_BEGIN:
    {
      parser->handle_new_object();
    }
    break;
    case JSON_ARRAY_BEGIN:
    {
      parser->handle_new_array();
    }
    break;
    case JSON_OBJECT_END:
    {
      parser->handle_end_object();
    }
    break;
    case JSON_ARRAY_END:
    {
      parser->handle_end_array();
    }
    break;
    case JSON_KEY:
    {
      parser->handle_key(data, len);
    }
    break;
    case JSON_STRING:
    {
      parser->handle_new_string(data, len);
    }
    break;
    case JSON_INT:
    {
      parser->handle_new_int(data, len);
    }
    break;
    case JSON_FLOAT:
    {
      parser->handle_new_float(data, len);
    }
    break;
    case JSON_NULL:
    {
      parser->handle_new_null();
    }
    break;
    case JSON_TRUE:
    {
      parser->handle_new_bool(true);
    }
    break;
    case JSON_FALSE:
    {
      parser->handle_new_bool(false);
    }
    break;
    default:
    {
      throw InvalidSyntaxException("Unknown JSON event type");
    }
    break;
  }

  return 0;
}

void
JsonParser::handle_new_object()
{
  // If current node is the root (no parent)
  if (m_current == nullptr)
  {
    m_data = SerializedData::object({});
    m_root = {
      .value = &m_data,
      .parent = nullptr,
    };
    m_current = &m_root;
    return;
  }

  // If current node is a child of an object
  if (m_current->value->get_type() == SerializedType::Object)
  {
    auto key = m_key.value();
    m_key    = std::nullopt;

    auto& obj = m_current->value->get_object();
    obj[key]  = SerializedData::object({});

    // Record the new object as the current node
    m_current->children.push_back({&obj[key], m_current});
    m_current = &m_current->children.back();
    return;
  }

  // If current node is a child of an array
  if (m_current->value->get_type() == SerializedType::Array)
  {
    auto& arr = m_current->value->get_array();
    arr.push_back(SerializedData::object({}));

    // Record the new object as the current node
    m_current->children.push_back({&arr[arr.size() - 1], m_current});
    m_current = &m_current->children.back();
    return;
  }

  throw InvalidSyntaxException("Unexpected object begin in JSON stream");
}

void
JsonParser::handle_end_object()
{
  m_current = m_current->parent;
}

void
JsonParser::handle_new_array()
{
  // If current node is the root (no parent)
  if (m_current == nullptr)
  {
    m_data = SerializedData::array({});
    m_root = {
      .value = &m_data,
      .parent = nullptr,
    };
    m_current = &m_root;
    return;
  }

  // If current node is a child of an object
  if (m_current->value->get_type() == SerializedType::Object)
  {
    auto key = m_key.value();
    m_key    = std::nullopt;

    auto& obj = m_current->value->get_object();
    obj[key]  = SerializedData::array({});

    // Record the new array as the current node
    m_current->children.push_back({&obj[key], m_current});
    m_current = &m_current->children.back();
    return;
  }

  // If current node is a child of an array
  if (m_current->parent->value->get_type() == SerializedType::Array)
  {
    auto& arr = m_current->parent->value->get_array();
    arr.push_back(SerializedData::array({}));

    // Record the new array as the current node
    m_current->children.push_back({&arr[arr.size() - 1], m_current});
    m_current = &m_current->children.back();
    return;
  }

  throw InvalidSyntaxException("Unexpected array begin in JSON stream");
}

void
JsonParser::handle_end_array()
{
  m_current = m_current->parent;
}

void
JsonParser::handle_key(const char* data, uint32_t len)
{
  m_key = std::string(data, len);
}

void
JsonParser::handle_new_string(const char* data, uint32_t len)
{
  if (m_current == nullptr)
  {
    throw InvalidSyntaxException("Unexpected string in JSON stream");
  }

  if (m_current->value->get_type() == SerializedType::Object)
  {
    auto key = m_key.value();
    m_key    = std::nullopt;

    auto& obj = m_current->value->get_object();
    obj[key]  = SerializedData::string(std::string(data, len));
    return;
  }

  if (m_current->value->get_type() == SerializedType::Array)
  {
    auto& arr = m_current->value->get_array();
    arr.push_back(SerializedData::string(std::string(data, len)));
    return;
  }

  throw InvalidSyntaxException("Unexpected string in JSON stream");
}

void
JsonParser::handle_new_int(const char* data, uint32_t len)
{
  if (m_current == nullptr)
  {
    throw InvalidSyntaxException("Unexpected integer in JSON stream");
  }

  if (m_current->value->get_type() == SerializedType::Object)
  {
    auto key = m_key.value();
    m_key    = std::nullopt;

    auto& obj = m_current->value->get_object();
    obj[key]  = SerializedData::integer(std::stoi(std::string(data, len)));
    return;
  }

  if (m_current->value->get_type() == SerializedType::Array)
  {
    auto& arr = m_current->parent->value->get_array();
    arr.push_back(SerializedData::integer(std::stoi(std::string(data, len))));
    return;
  }

  throw InvalidSyntaxException("Unexpected integer in JSON stream");
}

void
JsonParser::handle_new_float(const char* data, uint32_t len)
{
  if (m_current == nullptr)
  {
    throw InvalidSyntaxException("Unexpected float in JSON stream");
  }

  if (m_current->value->get_type() == SerializedType::Object)
  {
    auto key = m_key.value();
    m_key    = std::nullopt;

    auto& obj = m_current->value->get_object();
    obj[key]  = SerializedData::floating(std::stof(std::string(data, len)));
    return;
  }

  if (m_current->value->get_type() == SerializedType::Array)
  {
    auto& arr = m_current->value->get_array();
    arr.push_back(SerializedData::floating(std::stof(std::string(data, len))));
    return;
  }

  throw InvalidSyntaxException("Unexpected float in JSON stream");
}

void
JsonParser::handle_new_bool(bool b)
{
  if (m_current == nullptr)
  {
    throw InvalidSyntaxException("Unexpected boolean in JSON stream");
  }

  if (m_current->value->get_type() == SerializedType::Object)
  {
    auto key = m_key.value();
    m_key    = std::nullopt;

    auto& obj = m_current->value->get_object();
    obj[key]  = SerializedData::boolean(b);
    return;
  }

  if (m_current->value->get_type() == SerializedType::Array)
  {
    auto& arr = m_current->value->get_array();
    arr.push_back(SerializedData::boolean(b));
    return;
  }

  throw InvalidSyntaxException("Unexpected boolean in JSON stream");
}

void
JsonParser::handle_new_null()
{
  if (m_current == nullptr)
  {
    throw InvalidSyntaxException("Unexpected null in JSON stream");
  }

  if (m_current->value->get_type() == SerializedType::Object)
  {
    auto key = m_key.value();
    m_key    = std::nullopt;

    auto& obj = m_current->value->get_object();
    obj[key]  = SerializedData::null();
    return;
  }

  if (m_current->value->get_type() == SerializedType::Array)
  {
    auto& arr = m_current->value->get_array();
    arr.push_back(SerializedData::null());
    return;
  }

  throw InvalidSyntaxException("Unexpected null in JSON stream");
}
} // namespace setsugen

namespace setsugen
{

Json::Json() noexcept
  : m_config{}
{}

Json::Json(const Configurations& config) noexcept
  : m_config{config}
{}

void
Json::serialize(std::ostream& stream, const SerializedData& data) const
{}

void
Json::deserialize(std::istream& stream, SerializedData& data) const
{
  parser::JsonParser parser(stream, data);
  parser.parse();
}
}
