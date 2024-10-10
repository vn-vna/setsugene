#include <setsugen/application.h>
#include <setsugen/chrono.h>
#include <setsugen/conf.h>
#include <setsugen/exception.h>
#include <setsugen/format.h>
#include <setsugen/logger.h>
#include <setsugen/serde.h>
#include <setsugen/states.h>

using setsugen::Application;
using setsugen::ConfigurationLoader;
using setsugen::Date;
using setsugen::FileConfigurationSource;
using setsugen::Formatter;
using setsugen::SetsugenException;
using setsugen::TimeZoneOffset;

int
main()
{
  try
  {
    Application app;
    app.main_loop()->run();
  }
  catch (const SetsugenException& e)
  {
    std::cerr << "An exception occured while trying to run the application: " << e.what() << std::endl;
  }

  return 0;
}
