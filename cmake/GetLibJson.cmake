include(FetchContent)

FetchContent_Declare(
  libjson
  GIT_REPOSITORY https://github.com/vincenthz/libjson
  GIT_TAG        2bbe73f129ebf3eafd9b194f960536c146e680c2 # 0.8
  FIND_PACKAGE_ARGS NAMES json
)

message("Making libjson available")
FetchContent_MakeAvailable(libjson)