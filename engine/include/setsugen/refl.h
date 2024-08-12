#pragma once

#include <setsugen/exception.h>
#include <setsugen/macros.h>
#include <setsugen/pch.h>
#include <setsugen/serde.h>
#include <setsugen/types.h>
#include <setsugen/utilities.h>

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

template<typename R>
class ReflectionBase
{
public:
  std::vector<ReflectionField>& get_fields() const;
};

template<typename T>
class Reflection;
} // namespace setsugen

#include "./__impl__/refl/reflection_base.inl"
#include "./__impl__/refl/reflection_field.inl"
