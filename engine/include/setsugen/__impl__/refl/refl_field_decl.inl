#pragma once

#include "refl_fwd.inl"

namespace setsugen
{

class ReflectionField
{
public:
  template<typename Fn>
  ReflectionField(const std::string& name, Fn accessor);

  template<ClassType T, ScalarType TF>
  ReflectionField(const std::string& name, std::function<TF&(T&)> accessor);

  template<ClassType T, Serializable TF>
  ReflectionField(const std::string& name, std::function<TF&(T&)> accessor);

  template<ClassType T, IterableType TF>
  requires ScalarType<typename TF::value_type>
  ReflectionField(const std::string& name, std::function<TF&(T&)> accessor);

  template<ClassType T, IterableType TF>
  requires Serializable<typename TF::value_type>
  ReflectionField(const std::string& name, std::function<TF&(T&)> accessor);

  template<ClassType T, IterableType TF>
  requires IterableType<typename TF::value_type>
  ReflectionField(const std::string& name, std::function<TF&(T&)> accessor);

  const std::string& get_name() const;

  template<typename T>
  void get_value(SerializedData& data, T& target) const;

  template<typename T>
  void set_value(SerializedData& data, T& target) const;

private:
  std::string                                 m_name;
  std::function<void(SerializedData&, void*)> m_getter;
  std::function<void(SerializedData&, void*)> m_setter;
};

} // namespace setsugen
