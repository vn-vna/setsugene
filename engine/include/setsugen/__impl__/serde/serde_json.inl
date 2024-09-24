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
      bool pretty_print = false;
      int  indent       = 1;
      char indent_char  = ' ';
    } serializer_config;

    struct
    {
      bool allow_c_comments    = false;
      bool allow_yaml_comments = false;
    } deserializer_config;
  };

  Json() noexcept;
  Json(const Configurations& config) noexcept;

  void serialize(std::ostream& stream, const SerializedData& data) const;
  void deserialize(std::istream& stream, SerializedData& data) const;

private:
  Configurations m_config;
};

}
