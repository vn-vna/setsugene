#pragma once

#include "serde_fwd.inl"

namespace setsugen
{

class Json
{
public:
  struct Configurations
  {
    struct
    {
      Bool pretty_print = false;
      Int32  indent       = 1;
      char indent_char  = ' ';
    } serializer_config;

    struct
    {
      Bool allow_c_comments    = false;
      Bool allow_yaml_comments = false;
    } deserializer_config;
  };

  Json() noexcept;
  Json(const Configurations& config) noexcept;

  Void serialize(OutputStream& stream, const SerializedData& data) const;
  Void deserialize(InputStream& stream, SerializedData& data) const;

private:
  Configurations m_config;
};

}
