#pragma once

#include <setsugen/pch.h>

namespace setsugen
{
struct FormatContext;

template<typename T>
class Stringify;

class SerializedData;

template<typename T>
concept FundamentalType = std::is_fundamental_v<T>;

template<typename T>
concept ClassType = std::is_class_v<T>;

template<typename T>
concept PointerType = std::is_pointer_v<T>;

template<typename T>
concept ReferenceType = std::is_reference_v<T>;

template<typename T>
concept NullType = std::is_same_v<T, std::nullptr_t>;

template<typename T>
concept BooleanType = std::is_same_v<T, bool>;

template<typename T, typename E>
concept InitializerType = std::is_same_v<T, std::initializer_list<E> >;

template<typename T>
concept FloatingPointType =
    std::is_same_v<T, float> ||
    std::is_same_v<T, double>;

template<typename T>
concept IntegralType =
    std::is_same_v<T, int8_t> ||
    std::is_same_v<T, int16_t> ||
    std::is_same_v<T, int32_t> ||
    std::is_same_v<T, int64_t> ||
    std::is_same_v<T, uint8_t> ||
    std::is_same_v<T, uint16_t> ||
    std::is_same_v<T, uint32_t> ||
    std::is_same_v<T, uint64_t>;

template<typename T>
concept NumericType = FloatingPointType<T> || IntegralType<T>;

template<typename T>
concept StringType =
    std::is_same_v<std::string, std::decay_t<T> > ||
    std::is_same_v<const char*, std::decay_t<T> > ||
    std::is_same_v<char*, std::decay_t<T> > ||
    std::is_same_v<std::string_view, T>;

template<typename T>
concept Formattable = requires(const FormatContext& context, const std::remove_cvref_t<T>& value)
{
  { Stringify<std::remove_cvref_t<T> >::stringify(context, value) };
};

template<typename T>
concept ScalarType = NumericType<T> || StringType<T> || BooleanType<T> || NullType<T>;

template<typename T>
concept SerializerFormat = requires(const SerializedData& data, std::istream& stream)
{
  { T{}.serialize(stream, data) };
};

template<typename T>
concept DeserializerFormat = requires(SerializedData& data, std::istream& stream)
{
  { T{}.deserialize(stream, data) };
};

template<typename T>
concept SerdeFormat = SerializerFormat<T> && DeserializerFormat<T>;

template<typename T>
struct AutoParam
{
  using ParamType = T;
};

} // namespace setsugen
