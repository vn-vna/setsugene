include(FetchContent)
include(GNUInstallDirs)

FetchContent_Declare(
        libjson
        GIT_REPOSITORY https://github.com/vincenthz/libjson
        GIT_TAG 2bbe73f129ebf3eafd9b194f960536c146e680c2 # 0.8
)

FetchContent_MakeAvailable(libjson)

add_library(json STATIC
        ${libjson_SOURCE_DIR}/json.h
        ${libjson_SOURCE_DIR}/json.c
        ${libjson_SOURCE_DIR}/jsonlint.c
)

target_include_directories(json
        PUBLIC ${libjson_SOURCE_DIR})




