include(FetchContent)

FetchContent_Declare(
  libdeflate
  GIT_REPOSITORY https://github.com/ebiggers/libdeflate
  GIT_TAG        275aa5141db6eda3587214e0f1d3a134768f557d # release v1.20
  FIND_PACKAGE_ARGS NAMES libdeflate
)

message("Making libdeflate available")
FetchContent_MakeAvailable(libdeflate)
