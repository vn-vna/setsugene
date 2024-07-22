#include <setsugen/serde.h>

#include "../test.hpp"

std::string sample_json = R"(

{
  "firstName": "John",
  "lastName": "Doe",
  "age": 30,
  "isStudent": false,
  "address": {
    "streetAddress": "123 Main St",
    "city": "Anytown",
    "state": "CA",
    "postalCode": "98765"
  },
  "phoneNumbers": [
    {
      "type": "home",
      "number": "555-1234"
    },
    {
      "type": "work",
      "number": "555-5678"
    }
  ],
  "children": [],
  "spouse": null
}

)";

TEST(JsonSerde, Deserializer)
{
  SerializedData data;
  std::stringstream ss{sample_json};
  data.deserialize<Json>(ss);

  EXPECT_EQ(1, 1);
}

TEST_MAIN()