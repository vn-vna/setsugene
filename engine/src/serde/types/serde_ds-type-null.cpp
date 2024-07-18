#include <setsugen/serde.h>

namespace setsugen
{
DataStorage<SerializedType::Null>::DataStorage()
{}


DataStorage<SerializedType::Null>::DataStorage(std::nullptr_t value)
{}


DataStorage<SerializedType::Null>::DataStorage(const DataStorage &other)
{}


DataStorage<SerializedType::Null>::DataStorage(DataStorage &&other)
{}


DataStorage<SerializedType::Null>::~DataStorage()
{}


DataStorage<SerializedType::Null> &
DataStorage<SerializedType::Null>::operator=(const DataStorage &other)
{
  return *this;
}


DataStorage<SerializedType::Null> &
DataStorage<SerializedType::Null>::operator=(DataStorage &&other)
{
  return *this;
}
} // namespace setsugen
