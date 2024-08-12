#include <setsugen/exception.h>
#include <setsugen/format.h>

namespace setsugen
{
ArgDescription::~ArgDescription() noexcept
{
  m_deleter(m_data);
}

FormatArgsStore::FormatArgsStore() : m_args{}
{}

FormatArgsStore::~FormatArgsStore() = default;

const ArgDescription&
FormatArgsStore::get(const FormatIndex& index) const
{
  auto iter = m_args.find(index);
  if (iter == m_args.end())
  {
    throw InvalidArgumentException("Place holder index not found");
  }

  return *iter->second.get();
}
} // namespace setsugen
