#pragma once

#include <gtest/gtest.h>
#include <setsugen/engine.h>

using namespace setsugen;

#define TEST_MAIN()                           \
  Int32 main(Int32 argc, char** argv)             \
  {                                           \
    ::testing::InitGoogleTest(&argc, argv);   \
    return RUN_ALL_TESTS();                   \
  }
