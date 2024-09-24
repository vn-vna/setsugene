#pragma once

#include <setsugen/pch.h>

#include <setsugen/exception.h>
#include <setsugen/types.h>

namespace setsugen
{

enum class SerializedType : int8_t
{
  Null,
  Bool,
  Array,
  Float,
  Integer,
  Object,
  String,
  Auto = -1,
};

class Json;
class Toml;
class Yaml;

template<SerializedType T>
class DataStorage;
class SerializedData;
class SerializedField;

} // namespace setsugen
