project(setsugen-lab)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/engine-loader")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/meta-programming")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/chrono-lab")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/serde-lab")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/state-lab")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/fmt-lab")
