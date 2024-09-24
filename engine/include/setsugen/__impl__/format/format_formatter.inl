#pragma once

#include "format_decl.inl"

namespace setsugen
{
template<typename... Args>
std::string
Formatter::format(const std::string& fmt_template, Args&&... args)
{
  Formatter       formatter(fmt_template);
  FormatArgsStore args_store;
  size_t          s = 0;
  (args_store.set(s++, std::forward<Args>(args)), ...);
  return formatter.format(args_store);
}

template<>
class Stringify<Formatter>
{
public:
  static void stringify(const FormatContext& context, const Formatter& value)
  {
    context.result << "[[ Formatter: template = " << value.get_template() << " ]]";
  }
};
}
