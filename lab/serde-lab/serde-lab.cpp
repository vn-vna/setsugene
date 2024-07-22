#include <ranges>
#include <setsugen/logger.h>
#include <setsugen/serde.h>


int
main(int, char**)
{
  using namespace setsugen;
  LoggerFactory logger_factory{};
  logger_factory.add_appender(std::make_shared<ConsoleLogAppender>("console", "{level} {message}"));
  auto logger = logger_factory.get("console");

  try
  {
    SerializedData data, data2;
    std::cout << data;

    data = false;
    std::cout << "Data is: " << data << std::endl;

    data = 150;
    std::cout << "Data is: " << data << std::endl;

    data = "OK";
    std::cout << "Data is: " << data << std::endl;

    data = 3.14f;
    std::cout << "Data is: " << data << std::endl;

    data  = SerializedData{{1}, 2, 3, 4, "Hell Nooooo", false};
    data2 = std::move(data);
    std::cout << "Data is: " << data << std::endl;

    std::cout << "Data2 is: " << data2 << std::endl;

    data = SerializedData({{"OK", "Cool"}, {"K", "V"}}, SerializedType::Array);
    std::cout << "Data is: " << data << std::endl;

    std::string json = R"(
  {
    "firstName": "John",
    "lastName": "Doe",
    "age": 30,
    "isStudent": false,
    "address": {
      "streetAddress": "123 Main St",
      "city": "Anytown",
      "state": "CA",
      "postalCode": "98765"
    },
    "phoneNumbers": [
      {
        "type": "home",
        "number": "555-1234"
      },
      {
        "type": "work",
        "number": "555-5678"
      }
    ],
    "children": [],
    "spouse": null
  }
  )";

    std::stringstream ss{json};

    data.deserialize<Json>(ss);
    std::cout << Formatter::format("Data is a {}: {}", data.get_type(), data);

    SerializedData obj = {
      {"firstName", "John"},
      {"lastName", "Doe"},
      {"age", 30},
      {"isStudent", false},
      {"address", {
        {"streetAddress", "123 Main St"},
        {"city", "Anytown"},
        {"state", "CA"},
        {"postalCode", "98765"},
      }},
      {"phoneNumbers", {
        {
          {"type", "home"},
          {"number", "555-1234"},
        },
        {
          {"type", "work"},
          {"number", "555-5678"},
        },
      }},
      {"children", {}},
      {"spouse", nullptr},
    };

    std::cout << Formatter::format("Data is a {}: {}", obj.get_type(), obj);
  }
  catch (SetsugenException& ex)
  {
    logger->error("An exception occured while trying to deserialize data: {}", ex);
  }
}

