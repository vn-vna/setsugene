cmake_minimum_required(VERSION 3.5)

project(StateMachineLab C CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab-state state-lab.cpp)

target_link_libraries (lab-state
  PRIVATE engine)

if (MSVC)
  SET_TARGET_PROPERTIES(lab-state PROPERTIES LINK_FLAGS "/PROFILE")
endif ()
