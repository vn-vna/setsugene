#pragma once

#include "refl_fwd.inl"

namespace setsugen
{

class ReflectionField
{
public:
  template<typename Fn>
  ReflectionField(const String& name, Fn accessor);

  template<ClassType T, ScalarType TF>
  ReflectionField(const String& name, std::function<TF&(T&)> accessor);

  template<ClassType T, Serializable TF>
  ReflectionField(const String& name, std::function<TF&(T&)> accessor);

  template<ClassType T, IterableType TF>
  requires ScalarType<typename TF::value_type>
  ReflectionField(const String& name, std::function<TF&(T&)> accessor);

  template<ClassType T, IterableType TF>
  requires Serializable<typename TF::value_type>
  ReflectionField(const String& name, std::function<TF&(T&)> accessor);

  template<ClassType T, IterableType TF>
  requires IterableType<typename TF::value_type>
  ReflectionField(const String& name, std::function<TF&(T&)> accessor);

  const String& get_name() const;

  template<typename T>
  Void get_value(SerializedData& data, T& target) const;

  template<typename T>
  Void set_value(SerializedData& data, T& target) const;

private:
  String                                 m_name;
  std::function<Void(SerializedData&, Void*)> m_getter;
  std::function<Void(SerializedData&, Void*)> m_setter;
};

} // namespace setsugen
