include(FetchContent)
include(GNUInstallDirs)

FetchContent_Declare(
        libjson
        GIT_REPOSITORY https://github.com/vincenthz/libjson
        GIT_TAG        a63d8823b492477cc10ccd5edc6d79d2a34be585 # latest
)

FetchContent_MakeAvailable(libjson)

add_library(json STATIC
        ${libjson_SOURCE_DIR}/json.h
        ${libjson_SOURCE_DIR}/json.c
)

set_property(
  TARGET json 
  PROPERTY C_STANDARD 11
)

target_include_directories(json
        PUBLIC ${libjson_SOURCE_DIR})

