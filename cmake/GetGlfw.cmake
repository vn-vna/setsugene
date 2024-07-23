include(FetchContent)


FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw
  GIT_TAG        7b6aead9fb88b3623e3b3725ebb42670cbe4c579 # release 3.4
  FIND_PACKAGE_ARGS NAMES glfw3
)
message("Making glfw available")
FetchContent_MakeAvailable(glfw)
