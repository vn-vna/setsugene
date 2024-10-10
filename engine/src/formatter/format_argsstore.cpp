#include <setsugen/exception.h>
#include <setsugen/format.h>

namespace setsugen
{

FormatArgsStore::FormatArgsStore() : m_args{}
{}

FormatArgsStore::FormatArgsStore(Initializer<ArgDescription> args)
{
  Int32 index = 0;

  for (auto& arg: args)
  {
    if (std::holds_alternative<Int32>(arg.m_index) && std::get<Int32>(arg.m_index) == -1)
    {
      arg.m_index = index++;
    }

    m_args.emplace(arg.m_index, arg);
  }
}

FormatArgsStore::~FormatArgsStore() = default;

Void
FormatArgsStore::add(const ArgDescription& arg)
{
  auto cparg = arg;

  if (std::holds_alternative<Int32>(cparg.m_index) && std::get<Int32>(cparg.m_index) == -1)
  {
    cparg.m_index = (Int32) m_args.size();
  }

  m_args.emplace(cparg.m_index, cparg);
}

const ArgDescription&
FormatArgsStore::get(const FormatIndex& index) const
{
  auto iter = m_args.find(index);

  if (iter == m_args.end())
  {
    if (std::holds_alternative<Int32>(index))
    {
      throw InvalidArgumentException("Index '{}' is not in the argument list", {std::get<Int32>(index)});
    }
    else
    {
      throw InvalidArgumentException("Index '{}' is not in the argument list", {std::get<String>(index)});
    }
  }

  return iter->second;
}
} // namespace setsugen
