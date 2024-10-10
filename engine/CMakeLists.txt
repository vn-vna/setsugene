project(setsugen-engine)

set(CMAKE_CXX_STANDARD 20)

find_package(Doxygen REQUIRED)
find_package(Vulkan REQUIRED COMPONENTS glslc)
find_package(glfw REQUIRED)
find_program(glslc_executable NAMES glslc HINTS Vulkan::glslc)
find_package(libyaml REQUIRED)
find_package(volk REQUIRED)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/EngineVariables.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/ShaderTarget.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/AssetsTarget.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/EngineTarget.cmake")

add_subdirectory(tests)
