#pragma once

#include "serde_fwd.inl"

namespace setsugen
{
template<IntegralType T>
DataStorage(T) -> DataStorage<SerializedType::Integer>;

template<BooleanType T>
DataStorage(T) -> DataStorage<SerializedType::Bool>;

template<StringType T>
DataStorage(T) -> DataStorage<SerializedType::String>;

template<FloatingPointType T>
DataStorage(T) -> DataStorage<SerializedType::Float>;

template<SerializedType Type>
DataStorage(DataStorage<Type>&&) -> DataStorage<Type>;

DataStorage(std::nullptr_t) -> DataStorage<SerializedType::Null>;

template<SerializedType Type>
DataStorage(const DataStorage<Type>&) -> DataStorage<Type>;

template<IterableType T>
requires ScalarType<typename T::value_type>
DataStorage(const T&) -> DataStorage<SerializedType::Array>;

} // namespace setsugen
