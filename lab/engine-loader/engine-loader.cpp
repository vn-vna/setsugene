#include <setsugen/engine.h>

int
main()
{
  using namespace setsugen;
  ApplicationBuilder::create()
    ->build()
    ->run();
}
