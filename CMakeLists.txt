# CMakeList.txt : CMake project for setsugen, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.8)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MINGW)
  add_definitions(-DPCL_ONLY_CORE_POINT_TYPES)
endif()

if (WIN32)
  set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  add_definitions(-D_SCL_SECURE_NO_WARNINGS)
  add_definitions(-DUNICODE)
  add_definitions(-D_UNICODE)
endif()

project("setsugene")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory("${CMAKE_SOURCE_DIR}/deps/googletest")
add_subdirectory("${CMAKE_SOURCE_DIR}/deps/date")
add_subdirectory("${CMAKE_SOURCE_DIR}/deps/yaml-cpp")
add_subdirectory("${CMAKE_SOURCE_DIR}/deps/nlohmann-json")
add_subdirectory("${CMAKE_SOURCE_DIR}/deps/tomlplusplus")
add_subdirectory("${CMAKE_SOURCE_DIR}/deps/fmt")
add_subdirectory("${CMAKE_SOURCE_DIR}/deps/assimp")
add_subdirectory("${CMAKE_SOURCE_DIR}/deps/glfw")

add_subdirectory("${CMAKE_SOURCE_DIR}/engine")
add_subdirectory("${CMAKE_SOURCE_DIR}/lab")
