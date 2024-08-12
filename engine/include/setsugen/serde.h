#pragma once

#include <setsugen/exception.h>
#include <setsugen/pch.h>
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

namespace setsugen
{
template<>
class DataStorage<SerializedType::Null>
{
public:
   DataStorage();
   DataStorage(std::nullptr_t value);
   DataStorage(const DataStorage& other);
   DataStorage(DataStorage&& other);
  ~DataStorage() noexcept;

  DataStorage& operator=(const DataStorage& other);
  DataStorage& operator=(DataStorage&& other);

  bool operator==(const DataStorage& other) const;
  bool operator!=(const DataStorage& other) const;

  operator bool() const noexcept;
};


template<>
class DataStorage<SerializedType::Bool>
{
public:
  DataStorage(bool b);
  DataStorage(const DataStorage& other);
  DataStorage(DataStorage&& other) noexcept;

  DataStorage& operator=(bool b);
  DataStorage& operator=(const DataStorage& other);
  DataStorage& operator=(DataStorage&& other) noexcept;

  bool operator==(const DataStorage& other) const;
  bool operator!=(const DataStorage& other) const;

  bool value() const noexcept;

  operator bool() const noexcept;

private:
  bool m_value;
};


template<>
class DataStorage<SerializedType::Integer>
{
public:
  DataStorage(int64_t value);
  DataStorage(const DataStorage& other);
  DataStorage(DataStorage&& other) noexcept;

  int64_t value() const noexcept;

  DataStorage& operator=(int64_t value);
  DataStorage& operator=(const DataStorage& other);
  DataStorage& operator=(DataStorage&& other) noexcept;

  bool operator==(const DataStorage& other) const;
  bool operator!=(const DataStorage& other) const;
  bool operator<(const DataStorage& other) const;
  bool operator>(const DataStorage& other) const;
  bool operator<=(const DataStorage& other) const;
  bool operator>=(const DataStorage& other) const;

  explicit operator bool() const noexcept;

private:
  int64_t m_value;
};


template<>
class DataStorage<SerializedType::String>
{
public:
  DataStorage(const char* value);
  DataStorage(const std::string& value);
  DataStorage(std::string&& value);
  DataStorage(std::string_view value);
  DataStorage(const DataStorage& other);
  DataStorage(DataStorage&& other) noexcept;

  template<typename T>
    requires StringType<T>
  DataStorage& operator=(T&& value);

  DataStorage& operator=(const DataStorage& other);

  DataStorage& operator=(DataStorage&& other) noexcept;

  bool operator==(const DataStorage& other) const;

  bool operator!=(const DataStorage& other) const;

  std::string value() const noexcept;

private:
  std::string m_value;
};


template<>
class DataStorage<SerializedType::Float>
{
public:
  DataStorage(double value);
  DataStorage(const DataStorage& other);
  DataStorage(DataStorage&& other) noexcept;

  DataStorage& operator=(double value);
  DataStorage& operator=(const DataStorage& other);
  DataStorage& operator=(DataStorage&& other);

  bool operator==(const DataStorage& other) const;
  bool operator!=(const DataStorage& other) const;
  bool operator<(const DataStorage& other) const;
  bool operator>(const DataStorage& other) const;
  bool operator<=(const DataStorage& other) const;
  bool operator>=(const DataStorage& other) const;

  double value() const noexcept;
  operator bool() const noexcept;

private:
  double m_value;
};


template<>
class DataStorage<SerializedType::Array>
{
public:
  using Iter   = std::vector<SerializedData>::iterator;
  using CIter  = std::vector<SerializedData>::const_iterator;
  using RIter  = std::vector<SerializedData>::reverse_iterator;
  using CRIter = std::vector<SerializedData>::const_reverse_iterator;

  DataStorage() noexcept;
  DataStorage(const DataStorage& other) noexcept;
  DataStorage(DataStorage&& other) noexcept;
  DataStorage(std::initializer_list<SerializedData> list);

  DataStorage& operator=(const DataStorage& other) noexcept;
  DataStorage& operator=(DataStorage&& other) noexcept;

  DataStorage& push_back(const SerializedData& data);
  DataStorage& push_back(SerializedData&& data);
  DataStorage& pop_back();
  DataStorage& clear();
  DataStorage& erase(size_t index);
  DataStorage& insert(size_t index, const SerializedData& data);
  DataStorage& insert(size_t index, SerializedData&& data);
  DataStorage& resize(size_t size);
  DataStorage& reserve(size_t size);
  DataStorage& swap(DataStorage& other) noexcept;
  DataStorage& shrink_to_fit();

  DataStorage& sort(std::function<int(const SerializedData&, const SerializedData&)> pred);

  bool   empty() const;
  size_t size() const;
  Iter   begin();
  Iter   end();
  CIter  begin() const;
  CIter  end() const;
  RIter  rbegin();
  RIter  rend();
  CRIter rbegin() const;
  CRIter rend() const;

  SerializedData&       operator[](size_t index);
  const SerializedData& operator[](size_t index) const;

  explicit operator bool() const noexcept;

private:
  std::vector<SerializedData> m_arrays;
};


template<>
class DataStorage<SerializedType::Object>
{
public:
  using Iter  = std::unordered_map<std::string, SerializedData>::iterator;
  using CIter = std::unordered_map<std::string, SerializedData>::const_iterator;

  DataStorage();
  DataStorage(const DataStorage& other);
  DataStorage(DataStorage&& other) noexcept;
  DataStorage(std::initializer_list<SerializedData> list);

  DataStorage& operator=(const DataStorage& other);
  DataStorage& operator=(DataStorage&& other) noexcept;

  SerializedData&       operator[](const std::string& key);
  const SerializedData& operator[](const std::string& key) const;

  bool has_key(const std::string& key) const;

  size_t size() const;
  Iter   begin();
  Iter   end();
  CIter  begin() const;
  CIter  end() const;

private:
  std::unordered_map<std::string, SerializedData> m_map;
};


class SerializedData
{
public:
  using RefSerialziedArray   = DataStorage<SerializedType::Array>&;
  using RefSerializedObject  = DataStorage<SerializedType::Object>&;
  using CRefSerialziedArray  = const DataStorage<SerializedType::Array>&;
  using CRefSerializedObject = const DataStorage<SerializedType::Object>&;

  using SerializedVariant = std::variant<DataStorage<SerializedType::Null>, DataStorage<SerializedType::Bool>,
                                         DataStorage<SerializedType::Array>, DataStorage<SerializedType::Float>,
                                         DataStorage<SerializedType::Integer>, DataStorage<SerializedType::Object>,
                                         DataStorage<SerializedType::String>>;

  SerializedData() noexcept;
  SerializedData(std::initializer_list<SerializedData> value, SerializedType type = SerializedType::Auto);
  SerializedData(const SerializedData& other) noexcept;
  SerializedData(SerializedData&& other) noexcept;

  template<ScalarType T>
  SerializedData(T value, SerializedType type = SerializedType::Auto);


  template<SerializedType Type>
  explicit SerializedData(DataStorage<Type>&& data) noexcept;


  ~SerializedData() noexcept;

  template<ScalarType T>
  SerializedData& operator=(T value) noexcept(ScalarType<T>);

  SerializedData& operator=(std::initializer_list<SerializedData> value);
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

  operator bool() const noexcept;

  template<typename T>
  bool operator==(T&& other) const;

  template<typename T>
  bool operator!=(T&& other) const;

  bool operator<(const SerializedData& other) const;
  bool operator>(const SerializedData& other) const;
  bool operator<=(const SerializedData& other) const;
  bool operator>=(const SerializedData& other) const;

  template<typename T>
  constexpr SerializedData& operator[](T&& key);

  template<typename T>
  constexpr const SerializedData& operator[](T&& key) const;

  static SerializedData null();
  static SerializedData boolean(bool value);
  static SerializedData integer(int64_t value);
  static SerializedData floating(double value);
  static SerializedData string(const std::string& value);
  static SerializedData array(std::initializer_list<SerializedData> value);
  static SerializedData object(std::initializer_list<SerializedData> value);

  template<ScalarType T>
  explicit operator T() const;

  template<SerializerFormat T>
  void dumps(std::ostream& stream, const T& serializer = T{}) const;

  template<DeserializerFormat T>
  void parse(std::istream& stream, const T& deserializer = T{});

  template<Serializable T>
  void serialize(T& value);

  template<Serializable T>
  void deserialize(T& value);

private:
  bool check_object_initializer(const std::initializer_list<SerializedData>& list) const;
  bool try_compare_object(const SerializedData& other) const;
  bool try_compare_array(const SerializedData& other) const;
  bool try_compare_number(const SerializedData& other) const;
  bool try_compare_boolean(const SerializedData& other) const;
  bool try_compare_string(const SerializedData& other) const;
  bool try_compare_null(const SerializedData& other) const;

  SerializedVariant m_actual;
};


class Json
{
public:
  struct Configurations
  {
    struct
    {
      bool pretty_print = false;
      int  indent       = 1;
      char indent_char  = ' ';
    } serializer_config;

    struct
    {
      bool allow_c_comments    = false;
      bool allow_yaml_comments = false;
    } deserializer_config;
  };

  Json() noexcept;
  Json(const Configurations& config) noexcept;

  void serialize(std::ostream& stream, const SerializedData& data) const;
  void deserialize(std::istream& stream, SerializedData& data) const;

private:
  Configurations m_config;
};


class Yaml
{
public:
  struct Configurations
  {};

  Yaml() noexcept;
  Yaml(const Configurations& conf) noexcept;

  void serialize(std::ostream& stream, const SerializedData& data) const;
  void deserialize(std::istream& stream, SerializedData& data) const;

private:
  Configurations m_config;
};


class Toml
{
public:
  void serialize(std::ostream& stream, const SerializedData& data);
  void deserialize(std::istream& stream, SerializedData& data);
};


class Feticnia
{
public:
  void serialize(std::ostream& stream, const SerializedData& data);
  void deserialize(std::istream& stream, SerializedData& data);
};

template<>
class Stringify<SerializedType>
{
public:
  static void stringify(const FormatContext& ctx, const SerializedType& value);
};

template<>
class Stringify<SerializedData>
{
public:
  static void stringify(const FormatContext& context, const SerializedData& value);
};

std::ostream& operator<<(std::ostream& os, const SerializedData& data);
} // namespace setsugen

#include "./__impl__/serde/serialized_field.inl"
#include "./__impl__/serde/storage_deduction_guide.inl"
