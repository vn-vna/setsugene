project(setsugen-lab)

add_executable(lab-engine-loader
        "engine-loader.cpp"
        "engine-loader.h")

target_link_libraries(lab-engine-loader
        PRIVATE engine
)
