project (serde-lab)

add_executable (lab-serde serde-lab.cpp)
target_link_libraries (lab-serde
  PRIVATE engine)

if (MSVC)
  SET_TARGET_PROPERTIES(lab-serde PROPERTIES LINK_FLAGS "/PROFILE")
endif ()