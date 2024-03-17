#include <setsugen/engine.h>

int
main()
{
  using namespace setsugen;
  ApplicationBuilder::create()
    ->set_name("Setsugen Application")
    ->set_window_config("Hello LMFAO", 800, 600)
    ->build()->run();
}
