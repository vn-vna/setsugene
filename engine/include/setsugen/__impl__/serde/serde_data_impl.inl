#pragma once

#include "serde_data.inl"

namespace setsugen
{
template<typename T>
constexpr SerializedData&
SerializedData::operator[](T&& key)
{
  using DecayedType = std::decay_t<T>;
  if constexpr (std::is_same_v<DecayedType, SerializedData>)
  {
    if (key.get_type() == SerializedType::Integer)
    {
      return (*this)[key.get_integer().value()];
    }

    if (key.get_type() == SerializedType::String)
    {
      return (*this)[key.get_string().value()];
    }

    throw InvalidArgumentException("SerializedData::operator[] do not accept SerializedData with type {}",
                                   key.get_type());
  }
  else if constexpr (IntegralType<DecayedType>)
  {
    return this->get_array()[std::forward<T>(key)];
  }
  else if constexpr (StringType<DecayedType>)
  {
    return this->get_object()[std::forward<T>(key)];
  }
  else
  {
    throw NotImplementedException("SerializedData::operator[] for type {}", {typeid(T).name()});
  }
}

template<typename T>
constexpr const setsugen::SerializedData&
setsugen::SerializedData::operator[](T&& key) const
{
  using DecayedType = std::decay_t<T>;
  if constexpr (std::is_same_v<DecayedType, SerializedData>)
  {
    if (key.get_type() == SerializedType::Integer)
    {
      return (*this)[key.get_integer().value()];
    }

    if (key.get_type() == SerializedType::String)
    {
      return (*this)[key.get_string().value()];
    }

    throw InvalidArgumentException("SerializedData::operator[] do not accept SerializedData with type {}",
                                   key.get_type());
  }
  else if constexpr (IntegralType<DecayedType>)
  {
    return this->get_array()[std::forward<T>(key)];
  }
  else if constexpr (StringType<DecayedType>)
  {
    return this->get_object()[std::forward<T>(key)];
  }
  else
  {
    throw NotImplementedException("SerializedData::operator[] for type {}", {typeid(DecayedType).name()});
  }
}


template<ScalarType T>
SerializedData::SerializedData(T value, SerializedType type)
{
  switch (type)
  {
    case SerializedType::Auto:
    {
      m_actual = DataStorage(value);
      break;
    }
    case SerializedType::Null:
    {
      m_actual = DataStorage<SerializedType::Null>();
      break;
    }
    case SerializedType::Bool:
    {
      if constexpr (BooleanType<T>)
      {
        m_actual = DataStorage<SerializedType::Bool>(value);
      }
      else
      {
        throw InvalidArgumentException("Cannot construct an Boolean SerializedData from a non-Bool value");
      }
      break;
    }
    case SerializedType::Integer:
    {
      if constexpr (IntegralType<T>)
      {
        m_actual = DataStorage<SerializedType::Integer>(value);
      }
      else
      {
        throw InvalidArgumentException("Cannot construct an Integer SerializedData from a non-integer value");
      }
      break;
    }
    case SerializedType::Float:
    {
      if constexpr (FloatingPointType<T>)
      {
        m_actual = DataStorage<SerializedType::Float>(value);
      }
      else
      {
        throw InvalidArgumentException("Cannot construct a Float SerializedData from a non-Float32 value");
      }
      break;
    }
    case SerializedType::String:
    {
      if constexpr (StringType<T>)
      {
        m_actual = DataStorage<SerializedType::String>(value);
      }
      else
      {
        throw InvalidArgumentException("Cannot construct a String SerializedData from a non-string value");
      }
      break;
    }
    case SerializedType::Object:
    {
      throw InvalidArgumentException("Cannot construct an Object SerializedData from a scalar value");
    }
    case SerializedType::Array:
    {
      throw InvalidArgumentException("Cannot construct an Array SerializedData from a scalar value");
    }
  }
}

template<SerializedType Type>
SerializedData::SerializedData(DataStorage<Type>&& data) noexcept
{
  m_actual = std::move(data);
}

template<typename T>
Bool
SerializedData::operator==(T&& other) const
{
  using DecayedType = std::decay<T>;
  using ErasedType  = std::remove_cv_t<std::remove_reference_t<T>>;

  if constexpr (std::is_same_v<SerializedData, ErasedType>)
  {
    return this->try_compare_object(other) || this->try_compare_array(other) || this->try_compare_number(other) ||
           this->try_compare_boolean(other) || this->try_compare_string(other) || this->try_compare_null(other);
  }
  else if constexpr (ScalarType<ErasedType>)
  {
    return *this == SerializedData(other);
  }
  else
  {
    return false;
  }
}

template<typename T>
Bool
SerializedData::operator!=(T&& other) const
{
  return !(*this == other);
}

template<ScalarType T>
SerializedData::operator T() const
{
  if constexpr (setsugen::BooleanType<T>)
  {
    return static_cast<T>(this->get_bool().value());
  }
  else if constexpr (setsugen::IntegralType<T>)
  {
    return static_cast<T>(this->get_integer().value());
  }
  else if constexpr (setsugen::FloatingPointType<T>)
  {
    return static_cast<T>(this->get_float().value());
  }
  else if constexpr (setsugen::StringType<T>)
  {
    return static_cast<T>(this->get_string().value());
  }
  else
  {
    throw InvalidOperationException("Cannot cast Serialized type to a non-scalar type");
  }
}

template<SerializerFormat T>
Void
SerializedData::dumps(OutputStream& stream, const T& serializer) const
{
  serializer.serialize(stream, *this);
}

template<DeserializerFormat T>
Void
SerializedData::parse(InputStream& stream, const T& deserializer)
{
  deserializer.deserialize(stream, *this);
}

template<Serializable T>
Void
SerializedData::serialize(T& value)
{
  *this = object({});

  for (auto& field: Reflection<T>{}.get_fields())
  {
    SerializedData tmp;
    field.get_value(tmp, value);
    (*this)[field.get_name()] = std::move(tmp);
  }
}

template<Serializable T>
Void
SerializedData::deserialize(T& value)
{
  if (this->get_type() != SerializedType::Object)
  {
    throw InvalidOperationException("Cannot deserialize a non-object SerializedData to a struct");
  }

  for (auto& field: Reflection<T>{}.get_fields())
  {
    try
    {
      auto& field_data = (*this)[field.get_name()];
      field.set_value(field_data, value);
    }
    catch (const std::exception& e)
    {
      throw InvalidOperationException("Error deserializing field {}: {}", {field.get_name(), e.what()});
    }
  }
}

template<IterableType T>
requires ScalarType<typename T::value_type>
SerializedData::SerializedData(const T& data)
{
  m_actual = DataStorage(data);
}

} // namespace setsugen
