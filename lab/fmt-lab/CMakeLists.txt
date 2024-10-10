project (fmt-lab)

add_executable (lab-fmt fmt-lab.cpp)
target_link_libraries (lab-fmt
        PRIVATE engine)

if (MSVC)
    SET_TARGET_PROPERTIES(lab-fmt PROPERTIES LINK_FLAGS "/PROFILE")
endif ()
