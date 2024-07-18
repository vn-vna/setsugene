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
concept BooleanType = std::is_same_v<T, bool>;

template<typename T, typename E>
concept InitializerType = std::is_same_v<T, std::initializer_list<E>>;

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
concept StringConstructable =
    std::is_same_v<std::string, std::decay_t<T>> ||
    std::is_same_v<const char*, std::decay_t<T>> ||
    std::is_same_v<char*, std::decay_t<T>> ||
    std::is_same_v<std::string_view, T>;

template<typename T>
concept Formattable = requires (const FormatContext &context, const std::remove_cvref_t<T> &value)
{
  { Stringify<std::remove_cvref_t<T>>::stringify(context, value) };
};

template<typename T>
concept ScalarType = std::is_same_v<std::nullptr_t, T> || std::is_integral_v<T> || std::is_floating_point_v<T> ||
                     std::is_same_v<bool, T> || StringConstructable<T>;

template<typename T>
concept SerializerFormat = requires (const SerializedData &data, std::istream &stream)
{
  { T{}.serialize(stream, data) };
};

template<typename T>
concept DeserializerFormat = requires (SerializedData &data, std::istream &stream)
{
  { T{}.deserialize(stream, data) };
};

template<typename T>
concept SerdeFormat = SerializerFormat<T> && DeserializerFormat<T>;
} // namespace setsugen
