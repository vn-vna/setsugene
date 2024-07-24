project(setsugen-engine)

set(CMAKE_CXX_STANDARD 20)

find_package(Vulkan REQUIRED COMPONENTS glslc)
find_package(OpenFBX REQUIRED)
find_package(glfw REQUIRED)
find_program(glslc_executable NAMES glslc HINTS Vulkan::glslc)
find_package(libyaml REQUIRED)

set(ENGINE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(ENGINE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(ENGINE_BUILD_COMPACT OFF)
set(ENGINE_ASSETS_DIR "${CMAKE_BINARY_DIR}/assets")
set(SHADER_SOURCE_DIR "${CMAKE_SOURCE_DIR}/assets/shaders")
set(SHADER_BINARY_DIR "${CMAKE_BINARY_DIR}/assets/shaders")
set(USER_ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets/user")
set(USER_ASSETS_TARGET "${CMAKE_BINARY_DIR}/assets/user")

file(GLOB SHADERS
        ${SHADER_SOURCE_DIR}/*.vert
        ${SHADER_SOURCE_DIR}/*.frag
        ${SHADER_SOURCE_DIR}/*.comp
        ${SHADER_SOURCE_DIR}/*.geom
        ${SHADER_SOURCE_DIR}/*.tesc
        ${SHADER_SOURCE_DIR}/*.tese
        ${SHADER_SOURCE_DIR}/*.mesh
        ${SHADER_SOURCE_DIR}/*.task
        ${SHADER_SOURCE_DIR}/*.rgen
        ${SHADER_SOURCE_DIR}/*.rchit
        ${SHADER_SOURCE_DIR}/*.rmiss)

add_custom_command(
        COMMAND
        ${CMAKE_COMMAND} -E make_directory ${SHADER_BINARY_DIR}
        OUTPUT ${SHADER_BINARY_DIR}
        COMMENT "Creating ${SHADER_BINARY_DIR}"
)

foreach (source IN LISTS SHADERS)
    get_filename_component(FILENAME ${source} NAME)
    add_custom_command(
            COMMAND ${glslc_executable}
            ARGS -o ${SHADER_BINARY_DIR}/${FILENAME}.spv ${source}
            OUTPUT ${SHADER_BINARY_DIR}/${FILENAME}.spv
            DEPENDS ${source} ${SHADER_BINARY_DIR}
            COMMENT "Compiling ${FILENAME}"
    )
    list(APPEND SPV_SHADERS ${SHADER_BINARY_DIR}/${FILENAME}.spv)
endforeach ()

add_custom_target(engine-shaders ALL DEPENDS ${SPV_SHADERS})

add_custom_command(
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy_directory ${USER_ASSETS_DIR} ${USER_ASSETS_TARGET}
        OUTPUT ${USER_ASSETS_TARGET}
)
add_custom_target(user-assets ALL DEPENDS ${USER_ASSETS_TARGET})

# Collect all the header files in the include directory
file(GLOB_RECURSE ENGINE_INCLUDE_FILES
        "${ENGINE_INCLUDE_DIR}/*.hpp"
        "${ENGINE_INCLUDE_DIR}/*.h")

# Collect all the source files in the src directory
file(GLOB_RECURSE ENGINE_SOURCE_FILES
        "${ENGINE_SOURCE_DIR}/*.cpp"
        "${ENGINE_SOURCE_DIR}/*.hpp"
        "${ENGINE_SOURCE_DIR}/*.h")

add_library(engine
        SHARED ${ENGINE_SOURCE_FILES}
)
target_compile_definitions(engine
        PRIVATE SETSUGEN_EXPORT_SIGNATURES
)
target_include_directories(engine
        PUBLIC "${ENGINE_INCLUDE_DIR}"
)
target_precompile_headers(engine
        PRIVATE "${ENGINE_INCLUDE_DIR}/setsugen/pch.h"
)
target_link_libraries(engine
        PRIVATE glfw
        PRIVATE Vulkan::Vulkan
        PRIVATE OpenFBX
        PRIVATE yaml
        PRIVATE json
#        INTERFACE asio
)
target_compile_definitions(engine
        PRIVATE SETSUGEN_BUILD_LIBRARY
)

add_dependencies(engine engine-shaders user-assets)

add_library(setsugen::engine ALIAS engine)

add_subdirectory(tests)
