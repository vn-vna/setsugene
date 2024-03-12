# CMakeList.txt : CMake project for setsugen, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.8)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141rc)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif ()

project("setsugene")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if (WIN32)
    set(VOLK_STATIC_DEFINES VK_USE_PLATFORM_WIN32_KHR)
endif ()

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
