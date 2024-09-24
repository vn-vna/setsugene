# Collect all the header files in the include directory
file(GLOB_RECURSE ENGINE_INCLUDE_FILES
        "${ENGINE_INCLUDE_DIR}/*.hpp"
        "${ENGINE_INCLUDE_DIR}/*.h"
        "${ENGINE_INCLUDE_DIR}/*.inl")

# Collect all the source files in the src directory
file(GLOB_RECURSE ENGINE_SOURCE_FILES
        "${ENGINE_SOURCE_DIR}/*.cpp"
        "${ENGINE_SOURCE_DIR}/*.hpp"
        "${ENGINE_SOURCE_DIR}/*.h")

add_library(engine
        SHARED ${ENGINE_SOURCE_FILES} ${ENGINE_INCLUDE_FILES}
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
        PRIVATE yaml
        PRIVATE json
)

if(MSVC)
        set_target_properties(engine PROPERTIES LINK_FLAGS "/PROFILE")
        target_compile_definitions(engine
                PRIVATE WIN32_LEAN_AND_MEAN
                PRIVATE NOMINMAX)
endif()

target_compile_definitions(engine
        PRIVATE SETSUGEN_BUILD_LIBRARY
)

if(DOXYGEN_FOUND AND BUILD_DOCUMENTATIONS)
        doxygen_add_docs(engine-docs
                ${ENGINE_INCLUDE_DIR}
                ALL)
endif()

add_dependencies(engine engine-shaders user-assets)

add_library(setsugen::engine ALIAS engine)
