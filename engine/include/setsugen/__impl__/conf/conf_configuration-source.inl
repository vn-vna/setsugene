#pragma once

#include "conf_decl.inl"

namespace setsugen
{

template<typename Source, typename... Args>
ConfigurationLoader&
ConfigurationLoader::add_source(Args... args)
{
  m_sources.emplace_back(std::make_unique<Source>(std::forward<Args>(args)...));
  return *this;
}

} // namespace setsugen
