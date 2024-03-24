#include <setsugen/engine.h>

int
main()
{
  using namespace setsugen;
  Scene s{"main scene"};

  auto e = s.create_entity("Entity 1");
  auto m = e->add_component<Mesh>("user/mesh/untitled.fbx");
  m->load();

  std::cout << Formatter::format("{}", m);
}
