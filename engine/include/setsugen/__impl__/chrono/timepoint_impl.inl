#pragma once

#include "timepoint_decl.inl"

namespace setsugen
{

uint64_t
TimePoint::data() const
{
  return m_data;
}

} // namespace setsugen
