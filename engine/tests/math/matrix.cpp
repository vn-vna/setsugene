#include "../test.hpp"

#include <setsugen/math.h>

TEST(Matrix, Creation)
{
  Mat4F m1;
  for (int row = 0; row < 4; ++row)
  {
    for (int col = 0; col < 4; ++col)
    {
      EXPECT_EQ(m1.get(row, col), 0.0);
    }
  }

  Mat4F m2 = Mat4F::identity();

  for (int row = 0; row < 4; ++row)
  {
    for (int col = 0; col < 4; ++col)
    {
      if (row == col)
      {
        EXPECT_EQ(m2.get(row, col), 1.0);
      }
      else
      {
        EXPECT_EQ(m2.get(row, col), 0.0);
      }
    }
  }

}

TEST(Matrix, Addition)
{
  Mat4F m1 = Mat4F::identity();
  Mat4F m2 = Mat4F::identity();
  Mat4F m3 = m1 + m2;

  for (int row = 0; row < 4; ++row)
  {
    for (int col = 0; col < 4; ++col)
    {
      if (row == col)
      {
        EXPECT_EQ(m3.get(row, col), 2.0);
      }
      else
      {
        EXPECT_EQ(m3.get(row, col), 0.0);
      }
    }
  }

  // Random matrices
  Mat4F m4 {{
    1.0, 2.0, 3.0, 4.0,
    5.0, 6.0, 7.0, 8.0,
    9.0, 10.0, 11.0, 12.0,
    13.0, 14.0, 15.0, 16.0
  }};

  Mat4F m5 {{
    16.0, 15.0, 14.0, 13.0,
    12.0, 11.0, 10.0, 9.0,
    8.0, 7.0, 6.0, 5.0,
    4.0, 3.0, 2.0, 1.0
  }};

  Mat4F m6 = m4 + m5;

  for (int row = 0; row < 4; ++row)
  {
    for (int col = 0; col < 4; ++col)
    {
      EXPECT_EQ(m6.get(row, col), 17.0);
    }
  }

}

TEST_MAIN()