#pragma once

namespace setsugen
{
template<IntegralType T>
DataStorage(T)
  -> DataStorage<SerializedType::Integer>;

template<BooleanType T>
DataStorage(T)
  -> DataStorage<SerializedType::Bool>;

template<StringType T>
DataStorage(T)
  -> DataStorage<SerializedType::String>;

template<FloatingPointType T>
DataStorage(T)
  -> DataStorage<SerializedType::Float>;

template<SerializedType Type>
DataStorage(DataStorage<Type>&&)
  -> DataStorage<Type>;

DataStorage(std::nullptr_t)
  -> DataStorage<SerializedType::Null>;

template<SerializedType Type>
DataStorage(const DataStorage<Type>&)
  -> DataStorage<Type>;
}