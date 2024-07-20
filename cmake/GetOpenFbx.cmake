include(FetchContent)

FetchContent_Declare(
  openfbx
  GIT_REPOSITORY https://github.com/nem0/openfbx
  GIT_TAG        ef492927cefc16ad8733ec08bcc8df5434dbb1ae # release v0.9
  FIND_PACKAGE_ARGS NAMES openfbx
)

FetchContent_MakeAvailable(openfbx)