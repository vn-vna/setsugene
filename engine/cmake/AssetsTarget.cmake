add_custom_target(user-assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${USER_ASSETS_DIR} ${USER_ASSETS_TARGET})
