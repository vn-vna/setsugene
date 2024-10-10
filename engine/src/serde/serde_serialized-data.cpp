#include <setsugen/exception.h>
#include <setsugen/serde.h>
#include <utility>

namespace setsugen
{
SerializedData::
SerializedData() noexcept
{
  m_actual = DataStorage<SerializedType::Null>();
}


SerializedData::
SerializedData(const SerializedData& other) noexcept
    : m_actual(other.m_actual)
{}


SerializedData::
SerializedData(SerializedData&& other) noexcept
    : m_actual(std::move(other.m_actual))
{}

SerializedData::
SerializedData(Initializer<SerializedData> value, SerializedType type)
{
  switch (type)
  {
    case SerializedType::Auto:
    {
      if (check_object_initializer(value))
      {
        m_actual = DataStorage<SerializedType::Object>(value);
      }
      else
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
      }
      else
      {
        throw InvalidOperationException("Invalid initializer list for object");
      }
    }

    default: throw InvalidArgumentException("Invalid type for initializer list: {}", {type});
  }
}


SerializedData::~SerializedData() noexcept = default;

template<>
SerializedData&
SerializedData::operator=(std::nullptr_t value) noexcept
{
  m_actual = DataStorage<SerializedType::Null>();
  return *this;
}

template<>
SerializedData&
SerializedData::operator=(Bool value) noexcept
{
  m_actual = DataStorage(value);
  return *this;
}

template<>
SerializedData&
SerializedData::operator=(int64_t value) noexcept
{
  m_actual = DataStorage(value);
  return *this;
}

template<>
SerializedData&
SerializedData::operator=(int32_t value) noexcept
{
  return *this = static_cast<int64_t>(value);
}

template<>
SerializedData&
SerializedData::operator=(int16_t value) noexcept
{
  return *this = static_cast<int64_t>(value);
}

template<>
SerializedData&
SerializedData::operator=(int8_t value) noexcept
{
  return *this = static_cast<int64_t>(value);
}

template<>
SerializedData&
SerializedData::operator=(uint64_t value) noexcept
{
  return *this = static_cast<int64_t>(value);
}

template<>
SerializedData&
SerializedData::operator=(uint32_t value) noexcept
{
  return *this = static_cast<int64_t>(value);
}

template<>
SerializedData&
SerializedData::operator=(uint16_t value) noexcept
{
  return *this = static_cast<int64_t>(value);
}

template<>
SerializedData&
SerializedData::operator=(uint8_t value) noexcept
{
  return *this = static_cast<int64_t>(value);
}

template<>
SerializedData&
SerializedData::operator=(Float64 value) noexcept
{
  m_actual = DataStorage(value);
  return *this;
}

template<>
SerializedData&
SerializedData::operator=(Float32 value) noexcept
{
  return *this = static_cast<Float64>(value);
}

template<>
SerializedData&
SerializedData::operator=(String value) noexcept
{
  m_actual = DataStorage(std::move(value));
  return *this;
}

template<>
SerializedData&
SerializedData::operator=(const char* value) noexcept
{
  m_actual = DataStorage{value};
  return *this;
}

template<>
SerializedData&
SerializedData::operator=(char*& value) noexcept
{
  m_actual = DataStorage{value};
  return *this;
}


SerializedType
SerializedData::get_type() const noexcept
{
  return static_cast<SerializedType>(m_actual.index());
}


size_t
SerializedData::size() const
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
      throw InvalidOperationException("Cannot get size of non-iterable type: {}", {this->get_type()});
    }
  }
}


SerializedData::operator Bool() const noexcept
{
  return m_actual.index() != 0;
}


SerializedData&
SerializedData::operator=(const SerializedData& other) noexcept
{
  m_actual = other.m_actual;
  return *this;
}


SerializedData&
SerializedData::operator=(SerializedData&& other) noexcept
{
  m_actual = std::move(other.m_actual);
  other    = nullptr;
  return *this;
}


SerializedData&
SerializedData::operator=(Initializer<SerializedData> list)
{
  Bool is_object = check_object_initializer(list);

  if (is_object)
  {
    m_actual = DataStorage<SerializedType::Object>(list);
  }
  else
  {
    m_actual = DataStorage<SerializedType::Array>(list);
  }

  return *this;
}


SerializedData::CRefSerializedObject
SerializedData::get_object() const
{
  if (m_actual.index() == 5)
  {
    return std::get<DataStorage<SerializedType::Object>>(m_actual);
  }

  throw InvalidOperationException("Cannot get object from non-object");
}


SerializedData::RefSerializedObject
SerializedData::get_object()
{
  if (m_actual.index() == 5)
  {
    return std::get<DataStorage<SerializedType::Object>>(m_actual);
  }

  throw InvalidOperationException("Cannot get object from non-object");
}


const DataStorage<SerializedType::Bool>&
SerializedData::get_bool() const
{
  if (this->get_type() != SerializedType::Bool)
  {
    throw InvalidOperationException("Cannot get Bool from non-Bool");
  }

  return std::get<DataStorage<SerializedType::Bool>>(m_actual);
}


const DataStorage<SerializedType::Integer>&
SerializedData::get_integer() const
{
  if (this->get_type() != SerializedType::Integer)
  {
    throw InvalidOperationException("Cannot get integer from non-integer");
  }

  return std::get<DataStorage<SerializedType::Integer>>(m_actual);
}


const DataStorage<SerializedType::Float>&
SerializedData::get_float() const
{
  if (this->get_type() != SerializedType::Float)
  {
    throw InvalidOperationException("Cannot get Float32 from non-Float32");
  }

  return std::get<DataStorage<SerializedType::Float>>(m_actual);
}


const DataStorage<SerializedType::String>&
SerializedData::get_string() const
{
  if (this->get_type() != SerializedType::String)
  {
    throw InvalidOperationException("Cannot get string from non-string");
  }

  return std::get<DataStorage<SerializedType::String>>(m_actual);
}


SerializedData::CRefSerialziedArray
SerializedData::get_array() const
{
  if (this->get_type() == SerializedType::Array)
  {
    return std::get<DataStorage<SerializedType::Array>>(m_actual);
  }

  throw InvalidOperationException("Cannot get array from non-array");
}


SerializedData::RefSerialziedArray
SerializedData::get_array()
{
  if (this->get_type() == SerializedType::Array)
  {
    return std::get<DataStorage<SerializedType::Array>>(m_actual);
  }

  throw InvalidOperationException("Cannot get array from non-array");
}


size_t
SerializedData::hash() const
{
  switch (this->get_type())
  {
    case SerializedType::Integer:
    {
      return std::hash<int64_t>{}(std::get<DataStorage<SerializedType::Integer>>(m_actual).value());
    }

    case SerializedType::Float:
    {
      return std::hash<Float64>{}(std::get<DataStorage<SerializedType::Float>>(m_actual).value());
    }

    case SerializedType::String:
    {
      return std::hash<String>{}(std::get<DataStorage<SerializedType::String>>(m_actual).value());
    }

    case SerializedType::Bool:
    {
      return std::hash<Bool>{}(std::get<DataStorage<SerializedType::Bool>>(m_actual).value());
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


DataStorage<SerializedType::Bool>&
SerializedData::get_bool()
{
  if (this->get_type() != SerializedType::Bool)
  {
    throw InvalidOperationException("Cannot get Bool from non-Bool");
  }

  return std::get<DataStorage<SerializedType::Bool>>(m_actual);
}


DataStorage<SerializedType::Integer>&
SerializedData::get_integer()
{
  if (this->get_type() != SerializedType::Integer)
  {
    throw InvalidOperationException("Cannot get integer from non-integer");
  }

  return std::get<DataStorage<SerializedType::Integer>>(m_actual);
}


DataStorage<SerializedType::Float>&
SerializedData::get_float()
{
  if (this->get_type() != SerializedType::Float)
  {
    throw InvalidOperationException("Cannot get Float32 from non-Float32");
  }

  return std::get<DataStorage<SerializedType::Float>>(m_actual);
}


DataStorage<SerializedType::String>&
SerializedData::get_string()
{
  if (this->get_type() != SerializedType::String)
  {
    throw InvalidOperationException("Cannot get string from non-string");
  }

  return std::get<DataStorage<SerializedType::String>>(m_actual);
}

Bool
SerializedData::operator<(const SerializedData& other) const
{
  std::variant<int64_t, Float64> p1, p2;

  switch (this->get_type())
  {
    case SerializedType::Integer:
    {
      p1 = std::get<DataStorage<SerializedType::Integer>>(m_actual).value();
      break;
    }

    case SerializedType::Float:
    {
      p1 = std::get<DataStorage<SerializedType::Float>>(m_actual).value();
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
      p2 = std::get<DataStorage<SerializedType::Integer>>(other.m_actual).value();
      break;
    }

    case SerializedType::Float:
    {
      p2 = std::get<DataStorage<SerializedType::Float>>(other.m_actual).value();
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
    return std::get<Float64>(p1) < std::get<Float64>(p2);
  }

  if (p1.index() == 0 && p2.index() == 1)
  {
    return static_cast<Float64>(std::get<int64_t>(p1)) < std::get<Float64>(p2);
  }

  if (p1.index() == 1 && p2.index() == 0)
  {
    return std::get<Float64>(p1) < static_cast<Float64>(std::get<int64_t>(p2));
  }

  return false;
}


Bool
SerializedData::operator>(const SerializedData& other) const
{
  return other < *this;
}


Bool
SerializedData::operator<=(const SerializedData& other) const
{
  return !(*this > other);
}


Bool
SerializedData::operator>=(const SerializedData& other) const
{
  return !(*this < other);
}


OutputStream&
operator<<(OutputStream& os, const SerializedData& data)
{
  switch (data.get_type())
  {
    case SerializedType::Integer:
    {
      os << data.get_integer().value();
      break;
    }

    case SerializedType::Float:
    {
      os << data.get_float().value();
      break;
    }

    case SerializedType::String:
    {
      os << "\"" << data.get_string().value() << "\"";
      break;
    }

    case SerializedType::Bool:
    {
      os << (data.get_bool().value() ? "true" : "false");
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
      auto& obj  = data.get_object();
      auto  idx  = 0;
      auto  size = obj.size();

      for (const auto& [k, v]: obj)
      {
        os << "\"" << k << "\""
           << ": " << v;
        if (idx < size - 1)
        {
          os << ",";
          ++idx;
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


SerializedData
SerializedData::integer(int64_t value)
{
  return SerializedData(DataStorage(value));
}


SerializedData
SerializedData::floating(Float64 value)
{
  return SerializedData(DataStorage(value));
}


SerializedData
SerializedData::string(const String& value)
{
  return SerializedData(DataStorage(value));
}


SerializedData
SerializedData::boolean(Bool value)
{
  return SerializedData(DataStorage(value));
}


SerializedData
SerializedData::null()
{
  return SerializedData(DataStorage(nullptr));
}


SerializedData
SerializedData::array(Initializer<SerializedData> list)
{
  return SerializedData(DataStorage<SerializedType::Array>(list));
}


SerializedData
SerializedData::object(Initializer<SerializedData> value)
{
  return SerializedData(DataStorage<SerializedType::Object>(value));
}


Bool
SerializedData::check_object_initializer(const Initializer<SerializedData>& list) const
{
  for (const auto& data: list)
  {
    if (data.get_type() == SerializedType::Array && data.size() == 2 && data[0].get_type() == SerializedType::String)
    {
      continue;
    }

    return false;
  }

  return true;
}

Bool
SerializedData::try_compare_object(const SerializedData& other) const
{
  if (this->get_type() == SerializedType::Object || other.get_type() == SerializedType::Object)
  {
    throw InvalidOperationException("Cannot perform comparison between two SerializedData with Object type");
  }
  return false;
}

Bool
SerializedData::try_compare_array(const SerializedData& other) const
{
  if (this->get_type() == SerializedType::Array || other.get_type() == SerializedType::Array)
  {
    throw InvalidOperationException("Cannot perform comparison between two SerializedData with Array type");
  }
  return false;
}

Bool
SerializedData::try_compare_number(const SerializedData& other) const
{
  if (this->get_type() == SerializedType::Integer && other.get_type() == SerializedType::Integer)
  {
    return this->get_integer().value() == other.get_integer().value();
  }

  if (this->get_type() == SerializedType::Float && other.get_type() == SerializedType::Float)
  {
    return this->get_float().value() == other.get_float().value();
  }

  if (this->get_type() == SerializedType::Integer && other.get_type() == SerializedType::Float)
  {
    return this->get_integer().value() == other.get_float().value();
  }

  if (this->get_type() == SerializedType::Float && other.get_type() == SerializedType::Integer)
  {
    return this->get_float().value() == other.get_integer().value();
  }

  return false;
}

Bool
SerializedData::try_compare_boolean(const SerializedData& other) const
{
  if (this->get_type() == SerializedType::Bool && other.get_type() == SerializedType::Bool)
  {
    return this->get_bool().value() == other.get_bool().value();
  }

  return false;
}

Bool
SerializedData::try_compare_string(const SerializedData& other) const
{
  if (this->get_type() == SerializedType::String && other.get_type() == SerializedType::String)
  {
    return this->get_string().value() == other.get_string().value();
  }

  return false;
}

Bool
SerializedData::try_compare_null(const SerializedData& other) const
{
  if (this->get_type() == SerializedType::Null && other.get_type() == SerializedType::Null)
  {
    return true;
  }

  return false;
}

} // namespace setsugen

namespace setsugen
{


Void
Stringify<SerializedType>::stringify(const FormatContext& context, const SerializedType& value)
{
  context.result << "SerializedType [[ Type = ";
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

  context.result << " ]]";
}
} // namespace setsugen

namespace setsugen
{


Void
Stringify<SerializedData>::stringify(const FormatContext& context, const SerializedData& value)
{
  context.result << "[[ SerializedData: type = ";
  switch (value.get_type())
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
  context.result << ", value = " << value << " ]]";
}
} // namespace setsugen
