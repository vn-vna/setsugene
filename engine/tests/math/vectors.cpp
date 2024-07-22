#include "../test.hpp"
#include <gtest/gtest.h>

TEST(Vector2I, Creation)
{
  Vec2I v1;
  EXPECT_EQ(v1.x(), 0);
  EXPECT_EQ(v1.y(), 0);

  Vec2I v2(1, 2);
  EXPECT_EQ(v2.x(), 1);
  EXPECT_EQ(v2.y(), 2);

  Vec2I v3(v2);
  EXPECT_EQ(v3.x(), 1);
  EXPECT_EQ(v3.y(), 2);
}

TEST(Vector2I, Addition)
{
  Vec2I v1 = Vec2I(1, 2) + Vec2I(3, 4);
  EXPECT_EQ(v1.x(), 4);
  EXPECT_EQ(v1.y(), 6);
}

TEST(Vector2I, Subtraction)
{
  Vec2I v1 = Vec2I(1, 2) - Vec2I(3, 4);
  EXPECT_EQ(v1.x(), -2);
  EXPECT_EQ(v1.y(), -2);
}

TEST(Vector2I, Multiplication)
{
  Vec2I v1 = Vec2I(1, 2) * 2;
  EXPECT_EQ(v1.x(), 2);
  EXPECT_EQ(v1.y(), 4);
}

TEST(Vector2F, Creation)
{
  Vec2F v1;
  EXPECT_EQ(v1.x(), 0.0f);
  EXPECT_EQ(v1.y(), 0.0f);

  Vec2F v2(1.0f, 2.0f);
  EXPECT_EQ(v2.x(), 1.0f);
  EXPECT_EQ(v2.y(), 2.0f);

  Vec2F v3(v2);
  EXPECT_EQ(v3.x(), 1.0f);
  EXPECT_EQ(v3.y(), 2.0f);
}

TEST(Vector2F, Addition)
{
  Vec2F v1 = Vec2F(1.0f, 2.0f) + Vec2F(3.0f, 4.0f);
  EXPECT_EQ(v1.x(), 4.0f);
  EXPECT_EQ(v1.y(), 6.0f);
}

TEST(Vector2F, Subtraction)
{
  Vec2F v1 = Vec2F(1.0f, 2.0f) - Vec2F(3.0f, 4.0f);
  EXPECT_EQ(v1.x(), -2.0f);
  EXPECT_EQ(v1.y(), -2.0f);
}

TEST(Vector2F, Multiplication)
{
  Vec2F v1 = Vec2F(1.0f, 2.0f) * 2.0f;
  EXPECT_EQ(v1.x(), 2.0f);
  EXPECT_EQ(v1.y(), 4.0f);
}

TEST(Vector3I, Creation)
{
  Vec3I v1;
  EXPECT_EQ(v1.x(), 0);
  EXPECT_EQ(v1.y(), 0);
  EXPECT_EQ(v1.z(), 0);

  Vec3I v2(1, 2, 3);
  EXPECT_EQ(v2.x(), 1);
  EXPECT_EQ(v2.y(), 2);
  EXPECT_EQ(v2.z(), 3);

  Vec3I v3(v2);
  EXPECT_EQ(v3.x(), 1);
  EXPECT_EQ(v3.y(), 2);
  EXPECT_EQ(v3.z(), 3);
}

TEST(Vector3I, Addition)
{
  Vec3I v1 = Vec3I(1, 2, 3) + Vec3I(4, 5, 6);
  EXPECT_EQ(v1.x(), 5);
  EXPECT_EQ(v1.y(), 7);
  EXPECT_EQ(v1.z(), 9);
}

TEST(Vector3I, Subtraction)
{
  Vec3I v1 = Vec3I(1, 2, 3) - Vec3I(4, 5, 6);
  EXPECT_EQ(v1.x(), -3);
  EXPECT_EQ(v1.y(), -3);
  EXPECT_EQ(v1.z(), -3);
}

TEST(Vector3I, Multiplication)
{
  Vec3I v1 = Vec3I(1, 2, 3) * 2;
  EXPECT_EQ(v1.x(), 2);
  EXPECT_EQ(v1.y(), 4);
  EXPECT_EQ(v1.z(), 6);
}

TEST(Vector3F, Creation)
{
  Vec3F v1;
  EXPECT_EQ(v1.x(), 0.0f);
  EXPECT_EQ(v1.y(), 0.0f);
  EXPECT_EQ(v1.z(), 0.0f);

  Vec3F v2(1.0f, 2.0f, 3.0f);
  EXPECT_EQ(v2.x(), 1.0f);
  EXPECT_EQ(v2.y(), 2.0f);
  EXPECT_EQ(v2.z(), 3.0f);

  Vec3F v3(v2);
  EXPECT_EQ(v3.x(), 1.0f);
  EXPECT_EQ(v3.y(), 2.0f);
  EXPECT_EQ(v3.z(), 3.0f);
}

TEST(Vector3F, Addition)
{
  Vec3F v1 = Vec3F(1.0f, 2.0f, 3.0f) + Vec3F(4.0f, 5.0f, 6.0f);
  EXPECT_EQ(v1.x(), 5.0f);
  EXPECT_EQ(v1.y(), 7.0f);
  EXPECT_EQ(v1.z(), 9.0f);
}

TEST(Vector3F, Subtraction)
{
  Vec3F v1 = Vec3F(1.0f, 2.0f, 3.0f) - Vec3F(4.0f, 5.0f, 6.0f);
  EXPECT_EQ(v1.x(), -3.0f);
  EXPECT_EQ(v1.y(), -3.0f);
  EXPECT_EQ(v1.z(), -3.0f);
}

TEST(Vector3F, Multiplication)
{
  Vec3F v1 = Vec3F(1.0f, 2.0f, 3.0f) * 2.0f;
  EXPECT_EQ(v1.x(), 2.0f);
  EXPECT_EQ(v1.y(), 4.0f);
  EXPECT_EQ(v1.z(), 6.0f);
}

TEST(Vector4I, Creation)
{
  Vec4I v1;
  EXPECT_EQ(v1.x(), 0);
  EXPECT_EQ(v1.y(), 0);
  EXPECT_EQ(v1.z(), 0);
  EXPECT_EQ(v1.w(), 0);

  Vec4I v2(1, 2, 3, 4);
  EXPECT_EQ(v2.x(), 1);
  EXPECT_EQ(v2.y(), 2);
  EXPECT_EQ(v2.z(), 3);
  EXPECT_EQ(v2.w(), 4);

  Vec4I v3(v2);
  EXPECT_EQ(v3.x(), 1);
  EXPECT_EQ(v3.y(), 2);
  EXPECT_EQ(v3.z(), 3);
  EXPECT_EQ(v3.w(), 4);
}

TEST(Vector4I, Addition)
{
  Vec4I v1 = Vec4I(1, 2, 3, 4) + Vec4I(5, 6, 7, 8);
  EXPECT_EQ(v1.x(), 6);
  EXPECT_EQ(v1.y(), 8);
  EXPECT_EQ(v1.z(), 10);
  EXPECT_EQ(v1.w(), 12);
}

TEST(Vector4I, Subtraction)
{
  Vec4I v1 = Vec4I(1, 2, 3, 4) - Vec4I(5, 6, 7, 8);
  EXPECT_EQ(v1.x(), -4);
  EXPECT_EQ(v1.y(), -4);
  EXPECT_EQ(v1.z(), -4);
  EXPECT_EQ(v1.w(), -4);
}

TEST(Vector4I, Multiplication)
{
  Vec4I v1 = Vec4I(1, 2, 3, 4) * 2;
  EXPECT_EQ(v1.x(), 2);
  EXPECT_EQ(v1.y(), 4);
  EXPECT_EQ(v1.z(), 6);
  EXPECT_EQ(v1.w(), 8);
}

TEST(Vector4F, Creation)
{
  Vec4F v1;
  EXPECT_EQ(v1.x(), 0.0f);
  EXPECT_EQ(v1.y(), 0.0f);
  EXPECT_EQ(v1.z(), 0.0f);
  EXPECT_EQ(v1.w(), 0.0f);

  Vec4F v2(1.0f, 2.0f, 3.0f, 4.0f);
  EXPECT_EQ(v2.x(), 1.0f);
  EXPECT_EQ(v2.y(), 2.0f);
  EXPECT_EQ(v2.z(), 3.0f);
  EXPECT_EQ(v2.w(), 4.0f);

  Vec4F v3(v2);
  EXPECT_EQ(v3.x(), 1.0f);
  EXPECT_EQ(v3.y(), 2.0f);
  EXPECT_EQ(v3.z(), 3.0f);
  EXPECT_EQ(v3.w(), 4.0f);
}

TEST(Vector4F, Addition)
{
  Vec4F v1 = Vec4F(1.0f, 2.0f, 3.0f, 4.0f) + Vec4F(5.0f, 6.0f, 7.0f, 8.0f);
  EXPECT_EQ(v1.x(), 6.0f);
  EXPECT_EQ(v1.y(), 8.0f);
  EXPECT_EQ(v1.z(), 10.0f);
  EXPECT_EQ(v1.w(), 12.0f);
}

TEST(Vector4F, Subtraction)
{
  Vec4F v1 = Vec4F(1.0f, 2.0f, 3.0f, 4.0f) - Vec4F(5.0f, 6.0f, 7.0f, 8.0f);
  EXPECT_EQ(v1.x(), -4.0f);
  EXPECT_EQ(v1.y(), -4.0f);
  EXPECT_EQ(v1.z(), -4.0f);
  EXPECT_EQ(v1.w(), -4.0f);
}

TEST(Vector4F, Multiplication)
{
  Vec4F v1 = Vec4F(1.0f, 2.0f, 3.0f, 4.0f) * 2.0f;
  EXPECT_EQ(v1.x(), 2.0f);
  EXPECT_EQ(v1.y(), 4.0f);
  EXPECT_EQ(v1.z(), 6.0f);
  EXPECT_EQ(v1.w(), 8.0f);
}

TEST_MAIN();