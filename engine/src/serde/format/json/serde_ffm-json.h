#pragma once

#include <setsugen/exception.h>
#include <setsugen/serde.h>

extern "C"
{
#include <json.h>
}

namespace setsugen::parser
{
struct JsonNode
{
  SerializedData*       value;
  JsonNode*             parent = nullptr;
  DArray<JsonNode> children;
};

class JsonParser
{
public:
  JsonParser(InputStream& stream, SerializedData& data);
  ~JsonParser();

  Void parse();

  static Int32 json_event_callback(Void* userdata, Int32 type, const char* data, uint32_t len);

private:
  Void handle_new_object();
  Void handle_end_object();
  Void handle_new_array();
  Void handle_end_array();
  Void handle_key(const char* data, uint32_t len);
  Void handle_new_string(const char* data, uint32_t len);
  Void handle_new_int(const char* data, uint32_t len);
  Void handle_new_float(const char* data, uint32_t len);
  Void handle_new_bool(Bool b);
  Void handle_new_null();

  InputStream&   m_stream;
  SerializedData& m_data;
  json_parser     m_parser;

  JsonNode                   m_root;
  JsonNode*                  m_current;
  std::optional<String> m_key;
};
}

namespace setsugen::emitter
{
class JsonEmitter
{
public:
  JsonEmitter(OutputStream& stream, const SerializedData& data, const Json::Configurations& conf) noexcept;
  ~JsonEmitter() noexcept;

  Void emit();
  Void emit(const SerializedData& data);

  static Int32 json_event_callback(Void* userdata, const char* s, uint32_t length);

private:
  OutputStream&               m_stream;
  const SerializedData&       m_data;
  json_printer                m_printer;
  String                 m_indent_str;
  const Json::Configurations& m_config;
};
}
