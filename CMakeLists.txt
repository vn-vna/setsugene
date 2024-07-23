cmake_minimum_required(VERSION 3.5)

project("setsugene" C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include("${CMAKE_SOURCE_DIR}/cmake/GetGoogleTest.cmake")
include("${CMAKE_SOURCE_DIR}/cmake/GetLibDeflate.cmake")
include("${CMAKE_SOURCE_DIR}/cmake/GetOpenFbx.cmake")
include("${CMAKE_SOURCE_DIR}/cmake/GetGlfw.cmake")
include("${CMAKE_SOURCE_DIR}/cmake/GetLibYaml.cmake")
include("${CMAKE_SOURCE_DIR}/cmake/GetLibJson.cmake")
#include("${CMAKE_SOURCE_DIR}/cmake/GetAsio.cmake")

if (MINGW)
    message("Detected MinGW compiler")
    add_definitions(-DPCL_ONLY_CORE_POINT_TYPES)
endif ()


if (WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_definitions(-DUNICODE)
    add_definitions(-D_UNICODE)
endif ()

enable_testing()

add_subdirectory("${CMAKE_SOURCE_DIR}/engine")
add_subdirectory("${CMAKE_SOURCE_DIR}/lab")
