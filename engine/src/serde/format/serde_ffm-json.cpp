#include <setsugen/exception.h>
#include <setsugen/serde.h>

namespace setsugen
{
void
Json::serialize(std::ostream &stream, const SerializedData &data) const
{}


void
Json::deserialize(std::istream &stream, SerializedData &data) const
{
  this->skip_whitespace(stream);
  char c = stream.peek();
  if (c == '{')
  {
    this->parse_object(stream, data);
    return;
  }
  if (c == '[')
  {
    this->parse_array(stream, data);
    return;
  }
  if (c == '"')
  {
    this->parse_string(stream, data);
    return;
  }
  if (c == '-' || std::isdigit(c))
  {
    this->parse_number(stream, data);
    return;
  }
  if (c == 't' || c == 'f')
  {
    this->parse_bool(stream, data);
    return;
  }
  if (c == 'n')
  {
    this->parse_null(stream, data);
    return;
  }

  throw InvalidSyntaxException("Operation JSON parsing failed: invalid JSON data");
}


void
Json::parse_object(std::istream &stream, SerializedData &data) const
{
  data = SerializedData::object({});
  auto &obj = data.get_object();

  stream.get(); // Skip '{'
  while (true)
  {
    this->skip_whitespace(stream);
    if (stream.peek() == '}')
    {
      stream.get(); // Skip '}'
      return;
    }

    if (stream.peek() != '"')
    {
      throw InvalidSyntaxException("Invalid JSON object key");
    }

    SerializedData key;
    this->parse_string(stream, key);

    this->skip_whitespace(stream);

    if (stream.get() != ':')
    {
      throw InvalidSyntaxException("Invalid JSON object key-value pair");
    }

    this->skip_whitespace(stream);

    SerializedData value;
    this->deserialize(stream, value);

    obj[key.get_string().value()] = std::move(value);

    this->skip_whitespace(stream);

    if (stream.peek() == ',')
    {
      stream.get(); // Skip ','

      this->skip_whitespace(stream);

      if (stream.peek() == '}')
      {
        throw InvalidSyntaxException("Trailing ',' (comma) is not allowed in object");
      }

      continue;
    }
  }
}


void
Json::parse_array(std::istream &stream, SerializedData &data) const
{
  data = SerializedData::array({});
  auto &arr = data.get_array();

  stream.get(); // Skip '['
  while (true)
  {
    this->skip_whitespace(stream);
    if (stream.peek() == ']')
    {
      stream.get(); // Skip ']'
      return;
    }

    SerializedData value;
    this->deserialize(stream, value);
    arr.push_back(value);
    this->skip_whitespace(stream);

    if (stream.peek() == ',')
    {
      stream.get(); // Skip ','

      this->skip_whitespace(stream);

      if (stream.peek() == ']')
      {
        throw InvalidSyntaxException("Trailing ',' (comma) is not allowed in array");
      }

      continue;
    }
  }
}


void
Json::parse_string(std::istream &stream, SerializedData &data) const
{
  stream.get(); // Skip '"'
  std::string value;
  while (stream.peek() != '"')
  {
    if (stream.peek() == EOF)
    {
      throw InvalidSyntaxException("Invalid JSON string value (non closing double quote)");
    }
    value.push_back(stream.get());
  }
  stream.get(); // Skip '"'
  data = SerializedData::string(value);
}


void
Json::parse_number(std::istream &stream, SerializedData &data) const
{
  bool is_float = false;
  bool is_exponent = false;

  std::string value;

  while (true)
  {
    char c = stream.peek();

    if (std::isspace(c) || c == ',' || c == ']' || c == '}' || c == EOF)
    {
      break;
    }

    if (std::isdigit(c))
    {
      value.push_back(stream.get());
      continue;
    }

    switch (c)
    {
      case '-': // Minus sign can only be at the beginning to indicate negative
        // number
      {
        if (!value.empty())
        {
          throw InvalidSyntaxException("Invalid JSON number: Minus sign can only be at the beginning");
        }
        value.push_back(stream.get());
        break;
      }

      case '.': // Decimal point can only appear once
      {
        if (is_float || is_exponent)
        {
          throw InvalidSyntaxException("Invalid JSON number: Decimal point can only appear once");
        }
        is_float = true;
        value.push_back(stream.get());
        continue;
      }

      case 'e': // Exponental notation can only appear once
      case 'E': // But it can be both lower and upper case
      {
        if (is_exponent)
        {
          throw InvalidSyntaxException("Invalid JSON number: Expontental notation can only appear once");
        }
        is_exponent = true;
        value.push_back(stream.get());

        // Check if there is a sign after the exponental notation
        if (stream.peek() == '+' || stream.peek() == '-')
        {
          value.push_back(stream.get());
        }
        break;
      }

      default:
        throw InvalidSyntaxException( "Invalid JSON number: Invalid character {} in number", c);
    }
  }

  if (is_float)
  {
    data = SerializedData::floating(this->parse_floating(value));
  } else if (is_exponent)
  {
    data = SerializedData::floating(this->parse_exponental(value));
  } else
  {
    data = SerializedData::integer(this->parse_integer(value));
  }
}


void
Json::parse_bool(std::istream &stream, SerializedData &data) const
{
  if (stream.peek() == 't')
  {
    if (stream.get() == 't' && stream.get() == 'r' && stream.get() == 'u' &&
        stream.get() == 'e')
    {
      data = SerializedData::boolean(true);
      return;
    }
  }
  if (stream.peek() == 'f')
  {
    if (stream.get() == 'f' && stream.get() == 'a' && stream.get() == 'l' &&
        stream.get() == 's' && stream.get() == 'e')
    {
      data = SerializedData::boolean(false);
      return;
    }
  }

  throw InvalidSyntaxException("Invalid JSON boolean value");
}


void
Json::parse_null(std::istream &stream, SerializedData &data) const
{
  if (stream.get() == 'n' && stream.get() == 'u' && stream.get() == 'l' &&
      stream.get() == 'l')
  {
    data = SerializedData::null();
    return;
  }

  throw InvalidSyntaxException("Invalid JSON null value");
}


int64_t
Json::parse_integer(const std::string &str) const
{
  int64_t number;
  try
  {
    number = std::stoll(str);
  } catch (const std::exception &)
  {
    throw InvalidSyntaxException("Invalid JSON integer value");
  }
  return number;
}


double
Json::parse_floating(const std::string &str) const
{
  double number;
  try
  {
    number = std::stod(str);
  } catch (const std::exception &)
  {
    throw InvalidSyntaxException("Invalid JSON floating value");
  }
  return number;
}


double
Json::parse_exponental(const std::string &str) const
{
  double number;
  try
  {
    number = std::stod(str);
  } catch (const std::exception &)
  {
    throw InvalidSyntaxException("Invalid JSON exponental value");
  }
  return number;
}


void
Json::skip_whitespace(std::istream &stream) const
{
  while (std::isspace(stream.peek()))
  {
    stream.get();
  }
}
} // namespace setsugen
