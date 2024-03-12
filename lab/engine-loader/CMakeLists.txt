project(setsugen-lab)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab-engine-loader
        "engine-loader.cpp"
        "engine-loader.h")

target_link_libraries(lab-engine-loader
        PRIVATE engine
        PRIVATE yaml-cpp::yaml-cpp
        PRIVATE fmt::fmt)
