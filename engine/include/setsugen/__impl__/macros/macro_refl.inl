#pragma once


#define DECLARE_REFLECTION(clazz, ...)                                                                    \
  template<>                                                                                              \
  class setsugen::Reflection<clazz> : public ::setsugen::ReflectionBase<::setsugen::Reflection<clazz>>    \
  {                                                                                                       \
  public:                                                                                                 \
    using target = clazz;                                                                                 \
    static std::vector<ReflectionField> register_fields()                                                 \
    {                                                                                                     \
      return {MACRO_EXPAND(FOR_EACH(REFLECTION_FIELD, __VA_ARGS__))};                                                   \
    }                                                                                                     \
  }

#define REFLECTION_FIELD_IMPL(name) setsugen::ReflectionField(#name, [] (target& o) -> auto& { return o.name; }),
#define REFLECTION_FIELD(name) REFLECTION_FIELD_IMPL(name)