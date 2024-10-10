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

add_custom_target(engine-shaders ALL DEPENDS ${SPV_SHADERS})

add_custom_command(
        TARGET engine-shaders
        COMMAND ${CMAKE_COMMAND} -E make_directory ${SHADER_BINARY_DIR}
        COMMENT "Creating ${SHADER_BINARY_DIR}"
)

foreach(source IN LISTS SHADERS)
        get_filename_component(FILENAME ${source} NAME)
        add_custom_command(
                TARGET engine-shaders
                COMMAND ${glslc_executable} -o ${SHADER_BINARY_DIR}/${FILENAME}.spv ${source}
                DEPENDS ${source} ${SHADER_BINARY_DIR}
                COMMENT "Compiling ${FILENAME}"
        )
        list(APPEND SPV_SHADERS ${SHADER_BINARY_DIR}/${FILENAME}.spv)
endforeach()
