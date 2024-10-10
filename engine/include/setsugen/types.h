#pragma once

#include <setsugen/pch.h>

namespace setsugen
{
struct FormatContext;

template<typename T>
class Stringify;

class SerializedData;

template<typename T>
class Reflection;

class ReflectionField;

template<typename T, typename B>
concept DeliveredFrom = std::is_base_of_v<B, T>;

template<typename T>
concept FundamentalType = std::is_fundamental_v<T>;

template<typename T>
concept ClassType = std::is_class_v<T>;

template<typename T>
concept TrivialType = std::is_trivial_v<T>;

template<typename T>
concept PointerType = std::is_pointer_v<T>;

template<typename T>
concept ReferenceType = std::is_reference_v<T>;

template<typename Fn>
concept FunctionType = std::is_function_v<Fn>;

template<typename Fn, typename... Args>
concept CallableType = std::is_invocable_v<Fn, Args...>;

template<typename T>
concept NullType = std::is_same_v<T, std::nullptr_t>;

template<typename T>
concept BooleanType = std::is_same_v<T, Bool>;

template<typename T, typename E>
concept InitializerType = std::is_same_v<T, Initializer<E>>;

template<typename T>
concept FloatingPointType = std::is_same_v<T, Float32> || std::is_same_v<T, Float64>;

template<typename T>
concept IntegralType = std::is_same_v<T, int8_t> || std::is_same_v<T, int16_t> || std::is_same_v<T, int32_t> ||
                       std::is_same_v<T, int64_t> || std::is_same_v<T, uint8_t> || std::is_same_v<T, uint16_t> ||
                       std::is_same_v<T, uint32_t> || std::is_same_v<T, uint64_t>;

template<typename T>
concept NumericType = FloatingPointType<T> || IntegralType<T>;

template<typename T>
concept StringType = std::is_same_v<String, std::decay_t<T>> || std::is_same_v<const char*, std::decay_t<T>> ||
                     std::is_same_v<char*, std::decay_t<T>> || std::is_same_v<std::string_view, T>;

template<typename T>
concept Formattable = requires(const FormatContext& context, const std::remove_cvref_t<T>& value) {
  { Stringify<std::remove_cvref_t<T>>::stringify(context, value) };
};

template<typename T>
concept ScalarType = NumericType<T> || StringType<T> || BooleanType<T> || NullType<T>;

template<typename T>
concept Arithmetic = NumericType<T> || BooleanType<T>;

template<typename T>
concept IterableType = requires(T& value) {
  { value.begin() } -> std::same_as<typename T::iterator>;
  { value.end() } -> std::same_as<typename T::iterator>;
};

template<typename T>
concept SerializerFormat = requires(const SerializedData& data, OutputStream& stream) {
  { T{}.serialize(stream, data) };
};

template<typename T>
concept DeserializerFormat = requires(SerializedData& data, InputStream& stream) {
  { T{}.deserialize(stream, data) };
};

template<typename T>
concept Serializable = requires(SerializedData& data, T& value) {
  { Reflection<T>{}.register_fields() } -> std::same_as<DArray<ReflectionField>>;
};

template<typename T>
concept SerdeFormat = SerializerFormat<T> && DeserializerFormat<T>;

template<typename T>
struct AutoParam
{
  using ParamType = T;
};

template<typename... Ts>
struct TypeSet
{
  static constexpr size_t size = sizeof...(Ts);

  template<typename T>
  static constexpr Bool contains = (std::is_same_v<T, Ts> || ...);
};

template<typename T>
struct PhantomTyope
{
  using Type = T;
};

} // namespace setsugen
