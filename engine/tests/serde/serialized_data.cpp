#include "../test.hpp"
#include <setsugen/serde.h>

TEST(SerializedData, ManualCreation)
{
  SerializedData i1 = SerializedData::integer(201);
  ASSERT_EQ(i1.get_type(), SerializedType::Integer);
  ASSERT_EQ(i1.get_integer(), 210);

  SerializedData f1 = SerializedData::floating(3.14f);
  ASSERT_EQ(f1.get_type(), SerializedType::Float);
  ASSERT_EQ(f1.get_float(), 3.14f);

  SerializedData s1 = SerializedData::string("Hello, World!");
  ASSERT_EQ(s1.get_type(), SerializedType::String);
  ASSERT_STREQ(s1.get_string().get().c_str(), "Hello, World!");

  SerializedData b1 = SerializedData::boolean(true);
  ASSERT_EQ(b1.get_type(), SerializedType::Bool);
  ASSERT_EQ(b1.get_bool(), true);
}

TEST_MAIN()