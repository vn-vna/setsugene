#pragma once

#include <setsugen/pch.h>
#include <setsugen/types.h>

namespace setsugen
{
template<typename T>
class Stringify;

struct FormatContext;
class Formatter;
class FormatArgsStore;

using FormatIndex = std::variant<size_t, std::string>;

} // namespace setsugen
