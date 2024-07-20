project(engine-test C CXX)

find_package(googletest REQUIRED)

file(GLOB_RECURSE TEST_SOURCES "*.cpp")

include(GoogleTest)
foreach (source IN LISTS TEST_SOURCES)
    message(STATUS "Test file found: ${source}")
    get_filename_component(FILENAME ${source} NAME_WE)
    add_executable(${FILENAME}_test ${source})
    target_link_libraries(${FILENAME}_test PRIVATE setsugen::engine gtest_main)
    gtest_discover_tests(${FILENAME}_test)
endforeach ()

