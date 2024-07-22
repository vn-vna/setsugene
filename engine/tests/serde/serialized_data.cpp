#include "../test.hpp"

#include <gtest/gtest.h>
#include <setsugen/serde.h>

TEST(SerializedData, ManualCreation_Integer)
{
  SerializedData i1 = SerializedData::integer(201);
  EXPECT_EQ(i1.get_type(), SerializedType::Integer);
  EXPECT_EQ(i1.get_integer().value(), 201);
}

TEST(SerializedData, ManualCreation_Float)
{
  SerializedData f1 = SerializedData::floating(3.14f);
  EXPECT_EQ(f1.get_type(), SerializedType::Float);
  EXPECT_EQ(f1.get_float().value(), 3.14f);
}

TEST(SerializedData, ManualCreation_String)
{
  SerializedData s1 = SerializedData::string("Hello, World!");
  EXPECT_EQ(s1.get_type(), SerializedType::String);
  EXPECT_EQ(s1.get_string().value(), "Hello, World!");
}

TEST(SerializedData, ManualCreation_Boolean)
{
  SerializedData b1 = SerializedData::boolean(true);
  EXPECT_EQ(b1.get_type(), SerializedType::Bool);
  EXPECT_EQ(b1.get_bool().value(), true);
}

TEST(SerializedData, ManualCreation_Array)
{
  SerializedData arr = SerializedData::array({1, 3.14, "Hello, World!", true});
  EXPECT_EQ(arr.get_type(), SerializedType::Array);
  EXPECT_EQ(arr.get_array().size(), 4);
  EXPECT_EQ(arr.get_array()[0].get_type(), SerializedType::Integer);
  EXPECT_EQ(arr.get_array()[0].get_integer().value(), 1);
  EXPECT_EQ(arr.get_array()[1].get_type(), SerializedType::Float);
  EXPECT_EQ(arr.get_array()[1].get_float().value(), 3.14);
  EXPECT_EQ(arr.get_array()[2].get_type(), SerializedType::String);
  EXPECT_EQ(arr.get_array()[2].get_string().value(), "Hello, World!");
  EXPECT_EQ(arr.get_array()[3].get_type(), SerializedType::Bool);
  EXPECT_EQ(arr.get_array()[3].get_bool().value(), true);
}

TEST(SerializedData, ManualCreation_Object_Success)
{
  SerializedData obj = {
    {"int", 100},
    {"float", 3.14},
    {"str", "Hello, World!"},
    {"bool", false},
  };
  EXPECT_EQ(obj.get_type(), SerializedType::Object);
  EXPECT_EQ(obj.get_object().size(), 4);
  EXPECT_EQ(obj["int"].get_type(), SerializedType::Integer);
  EXPECT_EQ(obj["int"].get_integer().value(), 100);
  EXPECT_EQ(obj["float"].get_type(), SerializedType::Float);
  EXPECT_EQ(obj["float"].get_float().value(), 3.14);
  EXPECT_EQ(obj["str"].get_type(), SerializedType::String);
  EXPECT_EQ(obj["str"].get_string().value(), "Hello, World!");
  EXPECT_EQ(obj["bool"].get_type(), SerializedType::Bool);
  EXPECT_EQ(obj["bool"].get_bool().value(), false);
}

TEST(SerializedData, ManualCreation_Object_Except)
{
  EXPECT_THROW(SerializedData::object({
                 {"int", 100, "hololo"},
                 {"float", 3.14},
                 {"str", "Hello, World!"},
                 {"bool", false},
                 }), SetsugenException);
}

TEST(SerializedData, TypeDeduction_Integer)
{
  SerializedData i1 = 100;
  EXPECT_EQ(i1.get_type(), SerializedType::Integer);
  EXPECT_EQ(i1.get_integer().value(), 100);
}

TEST(SerializedData, TypeDeduction_Float)
{
  SerializedData f1 = 3.14;
  EXPECT_EQ(f1.get_type(), SerializedType::Float);
  EXPECT_EQ(f1.get_float().value(), 3.14);
}

TEST(SerializedData, TypeDeduction_String)
{
  SerializedData s1 = "Hello, World!";
  EXPECT_EQ(s1.get_type(), SerializedType::String);
  EXPECT_EQ(s1.get_string().value(), "Hello, World!");
}

TEST(SerializedData, TypeDeduction_Boolean)
{
  SerializedData b1 = true;
  EXPECT_EQ(b1.get_type(), SerializedType::Bool);
  EXPECT_EQ(b1.get_bool().value(), true);
}

TEST(SerializedData, TypeDeduction_Array)
{
  SerializedData arr = {1, 3.14, "Hello, World!", true};
  EXPECT_EQ(arr.get_type(), SerializedType::Array);
  EXPECT_EQ(arr.get_array().size(), 4);
  EXPECT_EQ(arr.get_array()[0].get_type(), SerializedType::Integer);
  EXPECT_EQ(arr.get_array()[0].get_integer().value(), 1);
  EXPECT_EQ(arr.get_array()[1].get_type(), SerializedType::Float);
  EXPECT_EQ(arr.get_array()[1].get_float().value(), 3.14);
  EXPECT_EQ(arr.get_array()[2].get_type(), SerializedType::String);
  EXPECT_EQ(arr.get_array()[2].get_string().value(), "Hello, World!");
  EXPECT_EQ(arr.get_array()[3].get_type(), SerializedType::Bool);
  EXPECT_EQ(arr.get_array()[3].get_bool().value(), true);
}

TEST(SerializedData, TypeDeduction_Object_Success)
{
  SerializedData obj = {
    {"int", 100},
    {"float", 3.14},
    {"str", "Hello, World!"},
    {"bool", false},
  };

  EXPECT_EQ(obj.get_type(), SerializedType::Object);
  EXPECT_EQ(obj.get_object().size(), 4);
  EXPECT_EQ(obj["int"].get_type(), SerializedType::Integer);
  EXPECT_EQ(obj["int"].get_integer().value(), 100);
  EXPECT_EQ(obj["float"].get_type(), SerializedType::Float);
  EXPECT_EQ(obj["float"].get_float().value(), 3.14);
  EXPECT_EQ(obj["str"].get_type(), SerializedType::String);
  EXPECT_EQ(obj["str"].get_string().value(), "Hello, World!");
  EXPECT_EQ(obj["bool"].get_type(), SerializedType::Bool);
  EXPECT_EQ(obj["bool"].get_bool().value(), false);
}

TEST(SerializedData, TypeDeduction_Object_Failed)
{
  SerializedData obj = {
    {"int", 100, "hololo"},
    {"float", 3.14},
    {"str", "Hello, World!"},
    {"bool", false},
  };
  EXPECT_EQ(obj.get_type(), SerializedType::Array);
}

TEST(SerializedData, Comparison_Integer)
{
  SerializedData i1 = 100;
  SerializedData i2 = 100;

  EXPECT_EQ(i1, i2);
  EXPECT_EQ(i1, 100);
  EXPECT_EQ(i2, 100);
}

TEST(SerializedData, Comparison_Float)
{
  SerializedData f1 = 3.14;
  SerializedData f2 = 3.14;

  EXPECT_EQ(f1, f2);
  EXPECT_EQ(f1, 3.14);
  EXPECT_EQ(f2, 3.14);
}

TEST(SerializedData, Comparison_String)
{
  SerializedData s1 = "Hello, World!";
  SerializedData s2 = "Hello, World!";

  EXPECT_EQ(s1, s2);
  EXPECT_EQ(s1, "Hello, World!");
  EXPECT_EQ(s2, "Hello, World!");
}

TEST(SerializedData, Comparison_Boolean)
{
  SerializedData b1 = true;
  SerializedData b2 = true;

  EXPECT_EQ(b1, b2);
  EXPECT_EQ(b1, true);
  EXPECT_EQ(b2, true);
}

TEST(SerializedData, Modification_Integer)
{
  SerializedData i1 = 100;
  i1 = 200;
  EXPECT_EQ(i1, 200);
}

TEST(SerializedData, Modification_Float)
{
  SerializedData f1 = 3.14;
  f1 = 6.28;
  EXPECT_EQ(f1, 6.28);
}

TEST(SerializedData, Modification_String)
{
  SerializedData s1 = "Hello, World!";
  s1 = "Hello, Universe!";
  EXPECT_EQ(s1, "Hello, Universe!");
}

TEST(SerializedData, Modification_Boolean)
{
  SerializedData b1 = true;
  b1 = false;
  EXPECT_EQ(b1, false);
}

TEST(SerializedData, Modification_Array)
{
  SerializedData arr = {1, 3.14, "Hello, World!", true};
  arr = {2, 6.28, "Hello, Universe!", false};
  EXPECT_EQ(arr.get_array().size(), 4);
  EXPECT_EQ(arr.get_array()[0].get_integer().value(), 2);
  EXPECT_EQ(arr.get_array()[1].get_float().value(), 6.28);
  EXPECT_EQ(arr.get_array()[2].get_string().value(), "Hello, Universe!");
  EXPECT_EQ(arr.get_array()[3].get_bool().value(), false);

  arr[0] = 3;
  arr[1] = 9.42;

  EXPECT_EQ(arr.get_array().size(), 4);
  EXPECT_EQ(arr.get_array()[0].get_integer().value(), 3);
  EXPECT_EQ(arr.get_array()[1].get_float().value(), 9.42);
}

TEST(SerializedData, Modification_Object)
{
  SerializedData obj = {
    {"int", 100},
    {"float", 3.14},
    {"str", "Hello, World!"},
    {"bool", false},
  };

  obj = {
    {"int", 200},
    {"float", 6.28},
    {"str", "Hello, Universe!"},
    {"bool", true},
  };

  EXPECT_EQ(obj.get_object().size(), 4);
  EXPECT_EQ(obj["int"].get_integer().value(), 200);
  EXPECT_EQ(obj["float"].get_float().value(), 6.28);
  EXPECT_EQ(obj["str"].get_string().value(), "Hello, Universe!");
  EXPECT_EQ(obj["bool"].get_bool().value(), true);

  obj["int"] = 300;
  obj["float"] = 9.42;

  EXPECT_EQ(obj.get_object().size(), 4);
  EXPECT_EQ(obj["int"].get_integer().value(), 300);
  EXPECT_EQ(obj["float"].get_float().value(), 9.42);
}

TEST(SerializedData, Nested_ArrayInArray)
{
  SerializedData arr = {1, 3.14, "Hello, World!", true, {2, 6.28, "Hello, Universe!", false}};
  EXPECT_EQ(arr.get_array().size(), 5);
  EXPECT_EQ(arr.get_array()[4].get_array().size(), 4);
  EXPECT_EQ(arr.get_array()[4].get_array()[0].get_integer().value(), 2);
  EXPECT_EQ(arr.get_array()[4].get_array()[1].get_float().value(), 6.28);
  EXPECT_EQ(arr.get_array()[4].get_array()[2].get_string().value(), "Hello, Universe!");
  EXPECT_EQ(arr.get_array()[4].get_array()[3].get_bool().value(), false);
}

TEST(SerializedData, Nested_ArrayInObject)
{
  SerializedData obj = {
    {"int", 100},
    {"float", 3.14},
    {"str", "Hello, World!"},
    {"bool", false},
    {"arr", {1, 3.14, "Hello, World!", true}},
  };

  EXPECT_EQ(obj.get_object().size(), 5);
  EXPECT_EQ(obj["arr"].get_array().size(), 4);
  EXPECT_EQ(obj["arr"].get_array()[0].get_integer().value(), 1);
  EXPECT_EQ(obj["arr"].get_array()[1].get_float().value(), 3.14);
  EXPECT_EQ(obj["arr"].get_array()[2].get_string().value(), "Hello, World!");
  EXPECT_EQ(obj["arr"].get_array()[3].get_bool().value(), true);
}

TEST(SerializedData, Complex)
{
  SerializedData obj = {
    {"firstName", "John"},
    {"lastName", "Doe"},
    {"age", 30},
    {"isStudent", false},
    {"address", {
      {"streetAddress", "123 Main St"},
      {"city", "Anytown"},
      {"state", "CA"},
      {"postalCode", "98765"},
    }},
    {"phoneNumbers", {
      {
        {"type", "home"},
        {"number", "555-1234"},
      },
      {
        {"type", "work"},
        {"number", "555-5678"},
      },
    }},
    {"children", {
      {
        {"name", "Jane"},
        {"age", 5},
      },
      {
        {"name", "John Jr."},
        {"age", 2},
      },
    }}, 
    {"spouse", nullptr},
  };

  EXPECT_EQ(obj.size(), 8);
  EXPECT_EQ(obj["firstName"], "John");
  EXPECT_EQ(obj["lastName"], "Doe");
  EXPECT_EQ(obj["age"], 30);
  EXPECT_EQ(obj["isStudent"], false);
  EXPECT_EQ(obj["address"].size(), 4);
  EXPECT_EQ(obj["address"]["streetAddress"], "123 Main St");
  EXPECT_EQ(obj["address"]["city"], "Anytown");
  EXPECT_EQ(obj["address"]["state"], "CA");
  EXPECT_EQ(obj["address"]["postalCode"], "98765");
  EXPECT_EQ(obj["phoneNumbers"].get_type(), SerializedType::Array);
  EXPECT_EQ(obj["phoneNumbers"][0]["type"], "home");
  EXPECT_EQ(obj["phoneNumbers"][0]["number"], "555-1234");
  EXPECT_EQ(obj["phoneNumbers"][1]["type"], "work");
  EXPECT_EQ(obj["phoneNumbers"][1]["number"], "555-5678");
  EXPECT_EQ(obj["children"].size(), 2);
  EXPECT_EQ(obj["children"][0]["name"], "Jane");
  EXPECT_EQ(obj["children"][0]["age"], 5);
  EXPECT_EQ(obj["children"][1]["name"], "John Jr.");
  EXPECT_EQ(obj["children"][1]["age"], 2);
  EXPECT_EQ(obj["spouse"].get_type(), SerializedType::Null);
}

TEST_MAIN()
