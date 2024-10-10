include(FetchContent)

FetchContent_Declare(
        volk
        GIT_REPOSITORY https://github.com/zeux/volk
        GIT_TAG b465507a1720ea32d65163153a53ffa136ca835f # 1.3.29
        FIND_PACKAGE_ARGS NAMES volk
)

message("Making Volk available")
FetchContent_MakeAvailable(volk)