#include "serde_ffm-json.h"

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
{
  emitter::JsonEmitter emitter(stream, data, m_config);
  emitter.emit();
}

void
Json::deserialize(std::istream& stream, SerializedData& data) const
{
  parser::JsonParser parser(stream, data);
  parser.parse();
}
}