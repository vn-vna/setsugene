#include <setsugen/logger.h>
#include <setsugen/refl.h>
#include <setsugen/serde.h>

struct Person
{
  std::string name;
  int         age;
};

DECLARE_REFLECTION(Person, name, age);

struct Family
{
  Person              father;
  Person              mother;
  std::vector<Person> children;
};

DECLARE_REFLECTION(Family, father, mother, children);

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

    data.parse<Json>(ss);
    std::cout << Formatter::format("Data is a {}: {}", data.get_type(), data);

    SerializedData obj = {
        {"firstName", "John"},
        {"lastName", "Doe"},
        {"age", 30},
        {"isStudent", false},
        {"address",
         {
             {"streetAddress", "123 Main St"},
             {"city", "Anytown"},
             {"state", "CA"},
             {"postalCode", "98765"},
         }},
        {"phoneNumbers",
         {
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
        {"stuffs", {1, 2, 3, 4, 5, "ABCDEFGHIJK"}},
        {"spouse", nullptr},
    };

    std::cout << "\n\n\n";

    auto start = std::chrono::system_clock::now();

    // Benchmark
    for (int i = 0; i < 100000; ++i)
    {
      std::stringstream ss;
      obj.dumps(ss, Json{Json::Configurations{
                        .serializer_config =
                            {
                                .pretty_print = true,
                                .indent       = 2,
                            },
                    }});
    }

    auto end = std::chrono::system_clock::now();

    std::cout << Formatter::format("Serialized {} times took {}ms", 100000,
                                   std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
  }
  catch (SetsugenException& ex)
  {
    logger->error("An exception occured while trying to deserialize data: {}", ex);
  }

  try
  {
    std::cout << "\n\n\n====================\n\n\n";

    Family f = {
        .father = {.name = "John", .age = 30},
        .mother = {.name = "Jane", .age = 28},
        .children =
            {
                {.name = "John Jr.", .age = 5},
                {.name = "Jane Jr.", .age = 3},
            },
    };

    SerializedData data;

    data.serialize(f);

    Family f2;

    data.deserialize(f2);

    data.serialize(f2);

    logger->info("Serialized data: {}", data);
  }
  catch (SetsugenException& ex)
  {
    logger->error("An exception occured while trying to deserialize data: {}", ex);
  }
}
