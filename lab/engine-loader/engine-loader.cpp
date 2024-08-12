#include <setsugen/engine.h>
#include <setsugen/refl.h>
#include <setsugen/macros.h>

using namespace setsugen;

struct person
{
  int         age;
  std::string name;
};

DECLARE_REFLECTION(person, name, age);

struct identity
{
  int    id;
  person p;
};

DECLARE_REFLECTION(identity, id, p);

int
main()
{
  identity id = {1, {20, "John"}};

  SerializedData tmp;
  tmp.serialize(id);
  tmp.dumps(std::cout, Json{});
}
