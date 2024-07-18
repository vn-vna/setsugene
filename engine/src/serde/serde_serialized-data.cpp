#include <ranges>
#include <setsugen/exception.h>
#include <setsugen/serde.h>

namespace setsugen
{
SerializedData::SerializedData() noexcept
{
  m_actual = DataStorage<SerializedType::Null>();
}


SerializedData::SerializedData(const SerializedData &other) noexcept
  : m_actual(other.m_actual)
{}


SerializedData::SerializedData(SerializedData &&other) noexcept
  : m_actual(std::move(other.m_actual))
{}


SerializedData::SerializedData(std::nullptr_t value, SerializedType type)
{
  switch (type)
  {
    case SerializedType::Auto:
    case SerializedType::Null:
    {
      m_actual = DataStorage(nullptr);
    }
    break;

    default:
      throw InvalidOperationException("Invalid type for null: {}", type);
  }
}


SerializedData::SerializedData(bool value, SerializedType type)
{
  switch (type)
  {
    case SerializedType::Auto:
    case SerializedType::Bool:
    {
      m_actual = DataStorage(value);
    }
    break;

    default:
      throw InvalidOperationException("Invalid type for boolean: {}", type);
  }
}


SerializedData::SerializedData(int64_t value, SerializedType type)
{
  switch (type)
  {
    case SerializedType::Integer:
    case SerializedType::Auto:
    {
      m_actual = DataStorage(value);
    }
    break;

    case SerializedType::Float:
    {
      m_actual = DataStorage(static_cast<double>(value));
    }
    break;

    case SerializedType::String:
    {
      m_actual = DataStorage(std::to_string(value));
    }
    break;

    default:
      throw InvalidOperationException("Invalid type for integer: {}", type);
  }
}


SerializedData::SerializedData(int32_t value, SerializedType type)
  : SerializedData(static_cast<int64_t>(value), type)
{}


SerializedData::SerializedData(int16_t value, SerializedType type)
  : SerializedData(static_cast<int64_t>(value), type)
{}


SerializedData::SerializedData(int8_t value, SerializedType type)
  : SerializedData(static_cast<int64_t>(value), type)
{}


SerializedData::SerializedData(uint64_t value, SerializedType type)
  : SerializedData(static_cast<int64_t>(value), type)
{}


SerializedData::SerializedData(uint32_t value, SerializedType type)
  : SerializedData(static_cast<int64_t>(value), type)
{}


SerializedData::SerializedData(uint16_t value, SerializedType type)
  : SerializedData(static_cast<int64_t>(value), type)
{}


SerializedData::SerializedData(uint8_t value, SerializedType type)
  : SerializedData(static_cast<int64_t>(value), type)
{}


SerializedData::SerializedData(double value, SerializedType type)
{
  switch (type)
  {
    case SerializedType::Auto:
    case SerializedType::Float:
    {
      m_actual = DataStorage(value);
    }
    break;

    case SerializedType::Integer:
    {
      m_actual = DataStorage(static_cast<int64_t>(value));
    }
    break;

    case SerializedType::String:
    {
      m_actual = DataStorage(std::to_string(value));
    }
    break;

    default:
      throw InvalidOperationException("Invalid type for float: {}", type);
  }
}


SerializedData::SerializedData(const std::string &value, SerializedType type)
{
  switch (type)
  {
    case SerializedType::Auto:
    case SerializedType::String:
    {
      m_actual = DataStorage(value);
    }
    break;

    default:
      throw InvalidOperationException("Invalid type for string: {}", type);
  }
}


SerializedData::SerializedData(const char *value, SerializedType type)
  : SerializedData(std::string{value}, type)
{}


SerializedData::SerializedData(char *value, SerializedType type)
  : SerializedData(std::string{value}, type)
{}


SerializedData::SerializedData(std::initializer_list<SerializedData> value, SerializedType type)
{
  switch (type)
  {
    case SerializedType::Auto:
    {
      if (check_object_initializer(value))
      {
        m_actual = DataStorage<SerializedType::Object>(value);
      } else
      {
        m_actual = DataStorage<SerializedType::Array>(value);
      }
    }
    break;
    case SerializedType::Array:
    {
      m_actual = DataStorage<SerializedType::Array>(value);
    }
    break;
    case SerializedType::Object:
    {
      if (check_object_initializer(value))
      {
        m_actual = DataStorage<SerializedType::Object>(value);
      } else
      {
        throw InvalidOperationException("Invalid initializer list for object");
      }
    }

    default:
      throw InvalidArgumentException("Invalid type for initializer list: {}", type);
  }
}


SerializedData::~SerializedData() noexcept = default;


SerializedData &SerializedData::operator=(std::nullptr_t value)
{
  m_actual = DataStorage<SerializedType::Null>();
  return *this;
}


SerializedData &SerializedData::operator=(bool value)
{
  m_actual = DataStorage(value);
  return *this;
}


SerializedData &SerializedData::operator=(int64_t value)
{
  m_actual = DataStorage(value);
  return *this;
}


SerializedData &SerializedData::operator=(int32_t value)
{
  return *this = static_cast<int64_t>(value);
}


SerializedData &SerializedData::operator=(int16_t value)
{
  return *this = static_cast<int64_t>(value);
}


SerializedData &SerializedData::operator=(int8_t value)
{
  return *this = static_cast<int64_t>(value);
}


SerializedData &SerializedData::operator=(uint64_t value)
{
  return *this = static_cast<int64_t>(value);
}


SerializedData &SerializedData::operator=(uint32_t value)
{
  return *this = static_cast<int64_t>(value);
}


SerializedData &SerializedData::operator=(uint16_t value)
{
  return *this = static_cast<int64_t>(value);
}


SerializedData &SerializedData::operator=(uint8_t value)
{
  return *this = static_cast<int64_t>(value);
}


SerializedData &SerializedData::operator=(double value)
{
  m_actual = DataStorage(value);
  return *this;
}


SerializedData &SerializedData::operator=(float value)
{
  return *this = static_cast<double>(value);
}


SerializedData &SerializedData::operator=(const std::string &value)
{
  m_actual = DataStorage(value);
  return *this;
}


SerializedData &SerializedData::operator=(const char *value)
{
  m_actual = DataStorage{value};
  return *this;
}


SerializedData &SerializedData::operator=(char *&value)
{
  m_actual = DataStorage{value};
  return *this;
}


SerializedType SerializedData::get_type() const noexcept
{
  return static_cast<SerializedType>(m_actual.index());
}


size_t SerializedData::size() const
{
  switch (this->get_type())
  {
    case SerializedType::Array:
    {
      return std::get<DataStorage<SerializedType::Array>>(m_actual).size();
    }

    case SerializedType::Object:
    {
      return std::get<DataStorage<SerializedType::Object>>(m_actual).size();
    }

    default:
    {
      throw InvalidOperationException("Cannot get size of non-iterable type: {}",
                                      this->get_type());
    }
  }
}


SerializedData::operator bool() const noexcept
{
  return m_actual.index() != 0;
}


SerializedData &
SerializedData::operator=(const SerializedData &other) noexcept
{
  m_actual = other.m_actual;
  return *this;
}


SerializedData &
SerializedData::operator=(SerializedData &&other) noexcept
{
  m_actual = std::move(other.m_actual);
  other = nullptr;
  return *this;
}


SerializedData &
SerializedData::operator=(std::initializer_list<SerializedData> list)
{
  bool is_object = check_object_initializer(list);

  if (is_object)
  {
    m_actual = DataStorage<SerializedType::Object>(list);
  } else
  {
    m_actual = DataStorage<SerializedType::Array>(list);
  }

  return *this;
}


SerializedData::CRefSerializedObject SerializedData::get_object() const
{
  if (m_actual.index() == 5)
  {
    return std::get<DataStorage<SerializedType::Object>>(m_actual);
  }

  throw InvalidOperationException("Cannot get object from non-object");
}


SerializedData::RefSerializedObject SerializedData::get_object()
{
  if (m_actual.index() == 5)
  {
    return std::get<DataStorage<SerializedType::Object>>(m_actual);
  }

  throw InvalidOperationException("Cannot get object from non-object");
}


const DataStorage<SerializedType::Bool> &SerializedData::get_bool() const
{
  if (this->get_type() != SerializedType::Bool)
  {
    throw InvalidOperationException("Cannot get bool from non-bool");
  }

  return std::get<DataStorage<SerializedType::Bool>>(m_actual);
}


const DataStorage<SerializedType::Integer> &SerializedData::get_integer() const
{
  if (this->get_type() != SerializedType::Integer)
  {
    throw InvalidOperationException("Cannot get integer from non-integer");
  }

  return std::get<DataStorage<SerializedType::Integer>>(m_actual);
}


const DataStorage<SerializedType::Float> &SerializedData::get_float() const
{
  if (this->get_type() != SerializedType::Float)
  {
    throw InvalidOperationException("Cannot get float from non-float");
  }

  return std::get<DataStorage<SerializedType::Float>>(m_actual);
}


const DataStorage<SerializedType::String> &SerializedData::get_string() const
{
  if (this->get_type() != SerializedType::String)
  {
    throw InvalidOperationException("Cannot get string from non-string");
  }

  return std::get<DataStorage<SerializedType::String>>(m_actual);
}


SerializedData::CRefSerialziedArray SerializedData::get_array() const
{
  if (this->get_type() == SerializedType::Array)
  {
    return std::get<DataStorage<SerializedType::Array>>(m_actual);
  }

  throw InvalidOperationException("Cannot get array from non-array");
}


SerializedData::RefSerialziedArray SerializedData::get_array()
{
  if (this->get_type() == SerializedType::Array)
  {
    return std::get<DataStorage<SerializedType::Array>>(m_actual);
  }

  throw InvalidOperationException("Cannot get array from non-array");
}


size_t SerializedData::hash() const
{
  switch (this->get_type())
  {
    case SerializedType::Integer:
    {
      return std::hash<int64_t>{}(
        std::get<DataStorage<SerializedType::Integer>>(m_actual).get());
    }

    case SerializedType::Float:
    {
      return std::hash<double>{}(
        std::get<DataStorage<SerializedType::Float>>(m_actual).get());
    }

    case SerializedType::String:
    {
      return std::hash<std::string>{}(
        std::get<DataStorage<SerializedType::String>>(m_actual).get());
    }

    case SerializedType::Bool:
    {
      return std::hash<bool>{}(
        std::get<DataStorage<SerializedType::Bool>>(m_actual).get());
    }

    case SerializedType::Array:
    {
      throw InvalidOperationException("Cannot hash an array");
    }

    case SerializedType::Object:
    {
      throw InvalidOperationException("Cannot hash an object");
    }

    case SerializedType::Null:
    {
      throw InvalidOperationException("Cannot hash a null");
    }

    default:
    {
      throw InvalidOperationException("Unknown type");
    }
  }
}


DataStorage<SerializedType::Bool> &SerializedData::get_bool()
{
  if (this->get_type() != SerializedType::Bool)
  {
    throw InvalidOperationException("Cannot get bool from non-bool");
  }

  return std::get<DataStorage<SerializedType::Bool>>(m_actual);
}


DataStorage<SerializedType::Integer> &SerializedData::get_integer()
{
  if (this->get_type() != SerializedType::Integer)
  {
    throw InvalidOperationException("Cannot get integer from non-integer");
  }

  return std::get<DataStorage<SerializedType::Integer>>(m_actual);
}


DataStorage<SerializedType::Float> &SerializedData::get_float()
{
  if (this->get_type() != SerializedType::Float)
  {
    throw InvalidOperationException("Cannot get float from non-float");
  }

  return std::get<DataStorage<SerializedType::Float>>(m_actual);
}


DataStorage<SerializedType::String> &SerializedData::get_string()
{
  if (this->get_type() != SerializedType::String)
  {
    throw InvalidOperationException("Cannot get string from non-string");
  }

  return std::get<DataStorage<SerializedType::String>>(m_actual);
}


bool SerializedData::operator==(const SerializedData &other) const
{
  if (this->get_type() != other.get_type())
  {
    return false;
  }

  switch (this->get_type())
  {
    case SerializedType::Integer:
    {
      return std::get<DataStorage<SerializedType::Integer>>(m_actual) ==
             std::get<DataStorage<SerializedType::Integer>>(other.m_actual);
    }

    case SerializedType::Float:
    {
      return std::get<DataStorage<SerializedType::Float>>(m_actual) ==
             std::get<DataStorage<SerializedType::Float>>(other.m_actual);
    }

    case SerializedType::String:
    {
      return std::get<DataStorage<SerializedType::String>>(m_actual) ==
             std::get<DataStorage<SerializedType::String>>(other.m_actual);
    }

    case SerializedType::Bool:
    {
      return std::get<DataStorage<SerializedType::Bool>>(m_actual) ==
             std::get<DataStorage<SerializedType::Bool>>(other.m_actual);
    }

    default:
    {
      return false;
    }
  }
}


bool SerializedData::operator!=(const SerializedData &other) const
{
  return !(*this == other);
}


bool SerializedData::operator<(const SerializedData &other) const
{
  std::variant<int64_t, double> p1, p2;

  switch (this->get_type())
  {
    case SerializedType::Integer:
    {
      p1 = std::get<DataStorage<SerializedType::Integer>>(m_actual).get();
      break;
    }

    case SerializedType::Float:
    {
      p1 = std::get<DataStorage<SerializedType::Float>>(m_actual).get();
      break;
    }

    default:
    {
      throw InvalidOperationException("Cannot use `<` on non-numeric types");
    }
  }

  switch (other.get_type())
  {
    case SerializedType::Integer:
    {
      p2 = std::get<DataStorage<SerializedType::Integer>>(other.m_actual).get();
      break;
    }

    case SerializedType::Float:
    {
      p2 = std::get<DataStorage<SerializedType::Float>>(other.m_actual).get();
      break;
    }

    default:
    {
      throw InvalidOperationException("Cannot use `<` on non-numeric types");
    }
  }

  if (p1.index() == 0 && p2.index() == 0)
  {
    return std::get<int64_t>(p1) < std::get<int64_t>(p2);
  }

  if (p1.index() == 1 && p2.index() == 1)
  {
    return std::get<double>(p1) < std::get<double>(p2);
  }

  if (p1.index() == 0 && p2.index() == 1)
  {
    return static_cast<double>(std::get<int64_t>(p1)) < std::get<double>(p2);
  }

  if (p1.index() == 1 && p2.index() == 0)
  {
    return std::get<double>(p1) < static_cast<double>(std::get<int64_t>(p2));
  }

  return false;
}


bool SerializedData::operator>(const SerializedData &other) const
{
  return other < *this;
}


bool SerializedData::operator<=(const SerializedData &other) const
{
  return !(*this > other);
}


bool SerializedData::operator>=(const SerializedData &other) const
{
  return !(*this < other);
}


SerializedData &SerializedData::operator[](size_t index)
{
  if (this->get_type() != SerializedType::Array)
  {
    throw InvalidOperationException("Cannot index non-array");
  }

  return std::get<DataStorage<SerializedType::Array>>(m_actual)[index];
}


const SerializedData &SerializedData::operator[](size_t index) const
{
  if (this->get_type() != SerializedType::Array)
  {
    throw InvalidOperationException("Cannot index non-array");
  }

  return std::get<DataStorage<SerializedType::Array>>(m_actual)[index];
}


SerializedData &SerializedData::operator[](const std::string &key)
{
  if (this->get_type() != SerializedType::Object)
  {
    throw InvalidOperationException("Cannot index non-object");
  }

  return std::get<DataStorage<SerializedType::Object>>(m_actual)[key];
}


const SerializedData &SerializedData::operator[](const std::string &key) const
{
  if (this->get_type() != SerializedType::Object)
  {
    throw InvalidOperationException("Cannot index non-object");
  }

  return std::get<DataStorage<SerializedType::Object>>(m_actual)[key];
}


std::ostream &operator<<(std::ostream &os, const SerializedData &data)
{
  switch (data.get_type())
  {
    case SerializedType::Integer:
    {
      os << data.get_integer().get();
      break;
    }

    case SerializedType::Float:
    {
      os << data.get_float().get();
      break;
    }

    case SerializedType::String:
    {
      os << "\"" << data.get_string().get() << "\"";
      break;
    }

    case SerializedType::Bool:
    {
      os << (data.get_bool().get() ? "true" : "false");
      break;
    }

    case SerializedType::Array:
    {
      os << "[";
      for (size_t i = 0; i < data.size(); ++i)
      {
        os << data[i];
        if (i != data.size() - 1)
        {
          os << ", ";
        }
      }
      os << "]";
      break;
    }

    case SerializedType::Object:
    {
      os << "{";
      auto &obj = data.get_object();

      for (auto it = obj.begin(); it != obj.end(); ++it)
      {
        os << "\"" << it->first << "\": " << it->second;
        if (it != std::prev(obj.end()))
        {
          os << ", ";
        }
      }

      os << "}";
      break;
    }

    case SerializedType::Null:
    {
      os << "null";
      break;
    }

    default:
    {
      os << "Unknown";
      break;
    }
  }

  return os;
}


SerializedData SerializedData::integer(int64_t value)
{
  return DataStorage{value};
}


SerializedData SerializedData::floating(double value)
{
  return DataStorage{value};
}


SerializedData SerializedData::string(const std::string &value)
{
  return DataStorage{value};
}


SerializedData SerializedData::boolean(bool value)
{
  return DataStorage{value};
}


SerializedData SerializedData::null()
{
  return DataStorage<SerializedType::Null>{};
}


SerializedData
SerializedData::array(std::initializer_list<SerializedData> list)
{
  return DataStorage<SerializedType::Array>{list};
}


SerializedData
SerializedData::object(std::initializer_list<SerializedData> value)
{
  return DataStorage<SerializedType::Object>{value};
}


bool SerializedData::check_object_initializer(
  const std::initializer_list<SerializedData> &list) const
{
  for (const auto &data: list)
  {
    if (data.get_type() == SerializedType::Array && data.size() == 2 &&
        data[0].get_type() == SerializedType::String)
    {
      continue;
    }

    return false;
  }

  return true;
}


void Stringify<SerializedType>::stringify(const FormatContext &context,
                                          const SerializedType &value)
{
  switch (value)
  {
    case SerializedType::Integer:
    {
      context.result << "Integer";
      break;
    }

    case SerializedType::Float:
    {
      context.result << "Float";
      break;
    }

    case SerializedType::String:
    {
      context.result << "String";
      break;
    }

    case SerializedType::Bool:
    {
      context.result << "Bool";
      break;
    }

    case SerializedType::Array:
    {
      context.result << "Array";
      break;
    }

    case SerializedType::Object:
    {
      context.result << "Object";
      break;
    }

    case SerializedType::Null:
    {
      context.result << "Null";
      break;
    }

    default:
    {
      context.result << "Unknown";
      break;
    }
  }
}
} // namespace setsugen
