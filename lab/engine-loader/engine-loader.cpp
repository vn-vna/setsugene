#include <setsugen/engine.h>

int
main()
{
  using namespace setsugen;
  try
  {
    auto factory = LoggerFactory();
    factory.add_appender(LogAppender::create_console_appender("console"));
    auto logger = factory.get("main");
    logger->info("Hello, world!");
  }
  catch (std::exception& e)
  {
    std::cout << e.what();
  }
}
