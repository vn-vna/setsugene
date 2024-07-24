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
  std::vector<JsonNode> children;
};

class JsonParser
{
public:
  JsonParser(std::istream& stream, SerializedData& data);
  ~JsonParser();

  void parse();

  static int json_event_callback(void* userdata, int type, const char* data, uint32_t len);

private:
  void handle_new_object();
  void handle_end_object();
  void handle_new_array();
  void handle_end_array();
  void handle_key(const char* data, uint32_t len);
  void handle_new_string(const char* data, uint32_t len);
  void handle_new_int(const char* data, uint32_t len);
  void handle_new_float(const char* data, uint32_t len);
  void handle_new_bool(bool b);
  void handle_new_null();

  std::istream&   m_stream;
  SerializedData& m_data;
  json_parser     m_parser;
  JsonNode        m_root;
  JsonNode*       m_current;
  std::optional<std::string> m_key;
};

}
