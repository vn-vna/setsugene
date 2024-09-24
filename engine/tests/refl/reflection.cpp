#include "../test.hpp"

#include <setsugen/refl.h>

TEST_MAIN()

using namespace setsugen;

struct Person
{
  std::string name;
  int         age;
};

DECLARE_REFLECTION(Person, name, age);

TEST(Reflection, Serialization)
{
  SerializedData data;

  Person p = {.name = "John", .age = 30};

  data.serialize(p);

  Person p2;
  data.deserialize(p2);

  ASSERT_EQ(p.name, p2.name);
  ASSERT_EQ(p.age, p2.age);
}

struct Family
{
  Person father;
  Person mother;
  std::vector<Person> children;
};

DECLARE_REFLECTION(Family, father, mother, children);
