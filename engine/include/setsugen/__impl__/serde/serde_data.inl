#pragma once

#include "serde_fwd.inl"

#include "serde_array.inl"
#include "serde_object.inl"
#include "serde_string.inl"
#include "serde_integer.inl"
#include "serde_bool.inl"
#include "serde_float.inl"
#include "serde_null.inl"

namespace setsugen
{

class SerializedData
{
public:
  using RefSerialziedArray   = DataStorage<SerializedType::Array>&;
  using RefSerializedObject  = DataStorage<SerializedType::Object>&;
  using CRefSerialziedArray  = const DataStorage<SerializedType::Array>&;
  using CRefSerializedObject = const DataStorage<SerializedType::Object>&;

  using SerializedVariant = std::variant<   //
      DataStorage<SerializedType::Null>,    // NULL
      DataStorage<SerializedType::Bool>,    // BOOL
      DataStorage<SerializedType::Array>,   // ARRAY
      DataStorage<SerializedType::Float>,   // FLOAT
      DataStorage<SerializedType::Integer>, // INTEGER
      DataStorage<SerializedType::Object>,  // OBJECT
      DataStorage<SerializedType::String>   // STRING
      >;

  SerializedData() noexcept;
  SerializedData(Initializer<SerializedData> value, SerializedType type = SerializedType::Auto);
  SerializedData(const SerializedData& other) noexcept;
  SerializedData(SerializedData&& other) noexcept;

  template<ScalarType T>
  SerializedData(T value, SerializedType type = SerializedType::Auto);

  template<IterableType T>
    requires ScalarType<typename T::value_type>
  SerializedData(const T& data);

  template<SerializedType Type>
  explicit SerializedData(DataStorage<Type>&& data) noexcept;


  ~SerializedData() noexcept;

  template<ScalarType T>
  SerializedData& operator=(T value) noexcept(ScalarType<T>);

  SerializedData& operator=(Initializer<SerializedData> value);
  SerializedData& operator=(const SerializedData& other) noexcept;
  SerializedData& operator=(SerializedData&& other) noexcept;

  SerializedType get_type() const noexcept;

  size_t size() const;
  size_t hash() const;

  DataStorage<SerializedType::Bool>&    get_bool();
  DataStorage<SerializedType::Integer>& get_integer();
  DataStorage<SerializedType::Float>&   get_float();
  DataStorage<SerializedType::String>&  get_string();
  DataStorage<SerializedType::Array>&   get_array();
  DataStorage<SerializedType::Object>&  get_object();

  const DataStorage<SerializedType::Bool>&    get_bool() const;
  const DataStorage<SerializedType::Integer>& get_integer() const;
  const DataStorage<SerializedType::Float>&   get_float() const;
  const DataStorage<SerializedType::String>&  get_string() const;
  const DataStorage<SerializedType::Array>&   get_array() const;
  const DataStorage<SerializedType::Object>&  get_object() const;

  operator Bool() const noexcept;

  template<typename T>
  Bool operator==(T&& other) const;

  template<typename T>
  Bool operator!=(T&& other) const;

  Bool operator<(const SerializedData& other) const;
  Bool operator>(const SerializedData& other) const;
  Bool operator<=(const SerializedData& other) const;
  Bool operator>=(const SerializedData& other) const;

  template<typename T>
  constexpr SerializedData& operator[](T&& key);

  template<typename T>
  constexpr const SerializedData& operator[](T&& key) const;

  static SerializedData null();
  static SerializedData boolean(Bool value);
  static SerializedData integer(int64_t value);
  static SerializedData floating(Float64 value);
  static SerializedData string(const String& value);
  static SerializedData array(Initializer<SerializedData> value);
  static SerializedData object(Initializer<SerializedData> value);

  template<ScalarType T>
  explicit operator T() const;

  template<SerializerFormat T>
  Void dumps(OutputStream& stream, const T& serializer = T{}) const;

  template<DeserializerFormat T>
  Void parse(InputStream& stream, const T& deserializer = T{});

  template<Serializable T>
  Void serialize(T& value);

  template<Serializable T>
  Void deserialize(T& value);

private:
  Bool check_object_initializer(const Initializer<SerializedData>& list) const;
  Bool try_compare_object(const SerializedData& other) const;
  Bool try_compare_array(const SerializedData& other) const;
  Bool try_compare_number(const SerializedData& other) const;
  Bool try_compare_boolean(const SerializedData& other) const;
  Bool try_compare_string(const SerializedData& other) const;
  Bool try_compare_null(const SerializedData& other) const;

  SerializedVariant m_actual;
};


} // namespace setsugen
