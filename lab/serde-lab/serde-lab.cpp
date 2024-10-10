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
  logger_factory.add_appender(
      std::make_shared<ConsoleLogAppender>("console", "[{level:w=6}] {tag:w=40} ->> {message}"));
  auto logger = logger_factory.get("console");

  try
  {
    SerializedData data, data2;
    logger->info("Data is: {}", {data});

    data = false;
    logger->info("Data is: {}", {data});

    data = 150;
    logger->info("Data is: {}", {data});

    data = "OK";
    logger->info("Data is: {}", {data});

    data = 3.14f;
    logger->info("Data is: {}", {data});

    data  = SerializedData{{1}, 2, 3, 4, "Hell Nooooo", false};
    data2 = std::move(data);
    logger->info("Data is: {}", {data});
    logger->info("Data2 is: {}", {data2});

    data = SerializedData({{"OK", "Cool"}, {"K", "V"}}, SerializedType::Array);
    logger->info("Data is: {}", {data});

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
    std::cout << Formatter::format("Data is a {}: {}", {data.get_type(), data});

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

    constexpr const int N = 1'000;

    auto start = std::chrono::system_clock::now();

    auto serder = Json{{
        .serializer_config =
            {
                .pretty_print = true,
                .indent       = 2,
            },
    }};

    // Benchmark
    for (int i = 0; i < N; ++i)
    {
      std::stringstream ss;

      obj.dumps(ss, serder);
    }

    auto end = std::chrono::system_clock::now();

    logger->info("Serialized {} times took {}ms",
                {N, std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()});
  }
  catch (SetsugenException& ex)
  {
    logger->error("An exception occured while trying to deserialize data: {}", {ex});
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

    logger->info("Serialized data: {}", {data});
  }
  catch (SetsugenException& ex)
  {
    logger->error("An exception occured while trying to deserialize data: {}", {ex});
  }
}
