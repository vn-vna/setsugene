project(setsugen-engine)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif ()

find_package(Vulkan REQUIRED COMPONENTS glslc)
find_program(glslc_executable NAMES glslc HINTS Vulkan::glslc)

set(ENGINE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(ENGINE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(ENGINE_BUILD_COMPACT OFF)
set(SHADER_SOURCE_DIR "${CMAKE_SOURCE_DIR}/assets/shaders")
set(SHADER_BINARY_DIR "${CMAKE_BINARY_DIR}/assets/shaders")

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
            COMMAND
            ${glslc_executable}
            #      -MD -MF ${SHADER_BINARY_DIR}/${FILENAME}.d
            -o ${SHADER_BINARY_DIR}/${FILENAME}.spv
            ${source}
            OUTPUT ${SHADER_BINARY_DIR}/${FILENAME}.spv
            DEPENDS ${source} ${SHADER_BINARY_DIR}
            COMMENT "Compiling ${FILENAME}"
    )
    list(APPEND SPV_SHADERS ${SHADER_BINARY_DIR}/${FILENAME}.spv)
endforeach ()

add_custom_target(engine-shaders ALL DEPENDS ${SPV_SHADERS})

# Collect all the header files in the include directory
file(GLOB_RECURSE ENGINE_INCLUDE_FILES
        "${ENGINE_INCLUDE_DIR}/*.hpp"
        "${ENGINE_INCLUDE_DIR}/*.h")

foreach (file ${ENGINE_INCLUDE_FILES})
    # Print out the collected source files
    message(STATUS "Include file found: ${file}")
endforeach ()


# Collect all the source files in the src directory
file(GLOB_RECURSE ENGINE_SOURCE_FILES
        "${ENGINE_SOURCE_DIR}/*.cpp"
        "${ENGINE_SOURCE_DIR}/*.hpp"
        "${ENGINE_SOURCE_DIR}/*.h")

foreach (file ${ENGINE_SOURCE_FILES} ${ENGINE_INCLUDE_FILES})
    # Print out the collected source files
    message(STATUS "Source file found: ${file}")
endforeach ()

add_library(engine SHARED ${ENGINE_SOURCE_FILES})
target_include_directories(engine PUBLIC "${ENGINE_INCLUDE_DIR}")
target_precompile_headers(engine PRIVATE "${ENGINE_INCLUDE_DIR}/setsugen/pch.h")
target_link_libraries(engine
        PRIVATE glfw
        PRIVATE yaml-cpp::yaml-cpp
        PRIVATE fmt::fmt
        PRIVATE date::date
        PRIVATE Vulkan::Vulkan
)

add_library(setsugen::engine ALIAS engine)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/test")
