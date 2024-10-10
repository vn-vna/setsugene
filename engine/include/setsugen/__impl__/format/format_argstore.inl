#pragma once

#include "format_argdesc.inl"
#include "format_fwd.inl"

namespace setsugen
{

class FormatArgsStore final
{
public:
  FormatArgsStore();
  FormatArgsStore(Initializer<ArgDescription> args);
  ~FormatArgsStore();

  Void add(const ArgDescription& arg);

  const ArgDescription& get(const FormatIndex& index) const;

private:
  template<typename T>
  static FormatIndex create_index(T&& index);
  inline static Int32  get_int_spec(const std::string_view& view);

  UnorderedMap<FormatIndex, ArgDescription> m_args;
};

} // namespace setsugen
