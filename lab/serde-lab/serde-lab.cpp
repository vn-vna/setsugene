#include <ranges>
#include <setsugen/logger.h>
#include <setsugen/serde.h>


int
main(int, char **)
{
  using namespace setsugen;

  LoggerFactory logger_factory{};
  logger_factory.add_appender(std::make_shared<ConsoleLogAppender>("console", "{level} {message}"));
  auto logger = logger_factory.get("console");

  SerializedData data, data2;
  logger->info("Data is {}", data);

  data = false;
  std::cout << "Data is: " << data << std::endl;

  data = 150;
  std::cout << "Data is: " << data << std::endl;

  data = "OK DESUNE";
  std::cout << "Data is: " << data << std::endl;

  data = 3.14f;
  std::cout << "Data is: " << data << std::endl;

  data = SerializedData{{1}, 2, 3, 4, "Hell Nooooo", false};
  data2 = std::move(data);
  std::cout << "Data is: " << data << std::endl;

  std::cout << "Data2 is: " << data2 << std::endl;

  data = SerializedData({{"OK", "Cool"}, {"K", "V"}}, SerializedType::Array);
  std::cout << "Data is: " << data << std::endl;

  std::string json = R"(
  [
    {
      "vietnam": "I Love U",
      "japan": "I love U tooo
    }
  ]
  )";

  std::stringstream ss{json};

  try
  {
    data.deserialize<Json>(ss);
    std::cout << Formatter::format("Data is a {}: {}", data.get_type(), data);
  } catch (SetsugenException &ex)
  {
    logger->error("An exception occured while trying to deserialize data: {}", ex);
  }
}

