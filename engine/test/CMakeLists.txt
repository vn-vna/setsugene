project(setsugene-engine-test)

add_executable(setsugene-engine-test-math math.cpp)

target_link_libraries(setsugene-engine-test-math engine gtest gtest_main)

add_test(NAME setsugene-engine-test-math COMMAND setsugene-engine-test-math)

set(CMAKE_CXX_STANDARD 17)