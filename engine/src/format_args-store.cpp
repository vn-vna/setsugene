#include <setsugen/format.h>
#include <setsugen/exception.h>

namespace setsugen
{
FormatArgsStore::FormatArgsStore() = default;

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

Void
FormatArgsStore::stringify(const FormatContext& context) const
{
  context.result
      << typeid(FormatArgsStore).name()
      << "{"
      << "size=" << m_args.size() << ", "
      << "}";
}
}
