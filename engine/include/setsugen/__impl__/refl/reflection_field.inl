#pragma once

namespace setsugen
{
#pragma region ReflectionField__Implementation

template<typename Fn>
ReflectionField::ReflectionField(const std::string& name, Fn accessor) : ReflectionField(name, std::function(accessor))
{}

template<ClassType T, ScalarType TF>
ReflectionField::ReflectionField(const std::string& name, std::function<TF&(T&)> accessor) : m_name(name)
{
  m_getter = [accessor](SerializedData& data, void* target)
  {
    auto& ref = accessor(*static_cast<T*>(target));
    data      = ref;
  };

  m_setter = [accessor](SerializedData& data, void* target)
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
ReflectionField::ReflectionField(const std::string& name, std::function<TF&(T&)> accessor) : m_name(name)
{
  m_getter = [accessor](SerializedData& data, void* target) { data.serialize(accessor(*static_cast<T*>(target))); };

  m_setter = [accessor](SerializedData& data, void* target) { data.deserialize(accessor(*static_cast<T*>(target))); };
}

template<typename T>
void
ReflectionField::get_value(SerializedData& data, T& target) const
{
  m_getter(data, &target);
}

template<typename T>
void
ReflectionField::set_value(SerializedData& data, T& target) const
{
  m_setter(data, &target);
}

#pragma endregion
} // namespace setsugen
