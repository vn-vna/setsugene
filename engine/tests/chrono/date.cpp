#include "../test.hpp"

TEST_MAIN()

using namespace setsugen;

TEST(ChronoDate, CurrentDate)
{
  auto date = Date::now();
}
