project (serde-lab)

add_executable (lab-serde serde-lab.cpp)
target_link_libraries (lab-serde
  PRIVATE engine)