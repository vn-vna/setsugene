#pragma once

#include "refl_field_decl.inl"

#include <setsugen/serde.h>

namespace setsugen
{
#pragma region ReflectionField__Implementation

template<typename Fn>
ReflectionField::ReflectionField(const String& name, Fn accessor) : ReflectionField(name, std::function(accessor))
{}

template<ClassType T, ScalarType TF>
ReflectionField::ReflectionField(const String& name, std::function<TF&(T&)> accessor) : m_name(name)
{
  m_getter = [accessor](SerializedData& data, Void* target)
  {
    auto& ref = accessor(*static_cast<T*>(target));
    data      = ref;
  };

  m_setter = [accessor](SerializedData& data, Void* target)
  {
    auto& ref = accessor(*static_cast<T*>(target));
    if constexpr (StringType<TF>)
    {
      ref = data.get_string().value().c_str();
    }
    else if constexpr (IntegralType<TF>)
    {
      ref = static_cast<TF>(data.get_integer().value());
    }
    else if constexpr (FloatingPointType<TF>)
    {
      ref = static_cast<TF>(data.get_float().value());
    }
    else if constexpr (BooleanType<TF>)
    {
      ref = data.get_bool().value();
    }
    else
    {
      throw std::invalid_argument("Unknown type");
    }
  };
}

template<ClassType T, Serializable TF>
ReflectionField::ReflectionField(const String& name, std::function<TF&(T&)> accessor) : m_name(name)
{
  m_getter = [accessor](SerializedData& data, Void* target) { data.serialize(accessor(*static_cast<T*>(target))); };
  m_setter = [accessor](SerializedData& data, Void* target) { data.deserialize(accessor(*static_cast<T*>(target))); };
}

template<ClassType T, IterableType TF>
requires ScalarType<typename TF::value_type>
ReflectionField::ReflectionField(const String& name, std::function<TF&(T&)> accessor) : m_name(name)
{
  m_getter = [accessor](SerializedData& data, Void* target)
  {
    auto& ref = accessor(*static_cast<T*>(target));
    data      = ref;
  };

  m_setter = [accessor](SerializedData& data, Void* target)
  {
    using ValueType = typename TF::value_type;

    auto& ref = accessor(*static_cast<T*>(target));

    for (size_t i = 0; i < data.get_array().size(); ++i)
    {
      if constexpr (StringType<ValueType>)
      {
        ref[i] = data.get_array()[i].get_string().value().c_str();
      }
      else if constexpr (IntegralType<ValueType>)
      {
        ref[i] = static_cast<ValueType>(data.get_array()[i].get_integer().value());
      }
      else if constexpr (FloatingPointType<ValueType>)
      {
        ref[i] = static_cast<ValueType>(data.get_array()[i].get_float().value());
      }
      else if constexpr (BooleanType<ValueType>)
      {
        ref[i] = data.get_array()[i].get_bool().value();
      }
      else if constexpr (NullType<ValueType>)
      {
        ref[i] = nullptr;
      }
      else
      {
        throw std::invalid_argument("Unknown type");
      }
    }
  };
}

template<ClassType T, IterableType TF>
requires Serializable<typename TF::value_type>
ReflectionField::ReflectionField(const String& name, std::function<TF&(T&)> accessor) : m_name(name)
{
  m_getter = [accessor](SerializedData& data, Void* target)
  {
    auto& ref = accessor(*static_cast<T*>(target));
    auto tmp = SerializedData::array({});

    for (auto& item: ref) {
      SerializedData item_data;
      item_data.serialize(item);
      tmp.get_array().push_back(item_data);
    }

    data = tmp;
  };

  m_setter = [accessor](SerializedData& data, Void* target)
  {
    auto& ref = accessor(*static_cast<T*>(target));
    ref.resize(data.get_array().size());

    for (size_t i = 0; i < data.get_array().size(); ++i)
    {
      data.get_array()[i].deserialize(ref[i]);
    }
  };
}

template<ClassType T, IterableType TF>
requires IterableType<typename TF::value_type>
ReflectionField::ReflectionField(const String& name, std::function<TF&(T&)> accessor) : m_name(name)
{
  m_getter = [accessor](SerializedData& data, Void* target)
  {
    auto& ref = accessor(*static_cast<T*>(target));
    data      = ref;
  };

  m_setter = [accessor](SerializedData& data, Void* target)
  {
    auto& ref = accessor(*static_cast<T*>(target));
    data.deserialize(ref);
  };
}

template<typename T>
Void
ReflectionField::get_value(SerializedData& data, T& target) const
{
  m_getter(data, &target);
}

template<typename T>
Void
ReflectionField::set_value(SerializedData& data, T& target) const
{
  m_setter(data, &target);
}

#pragma endregion
} // namespace setsugen
