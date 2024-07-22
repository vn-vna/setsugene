include(FetchContent)
set(gtest_force_shared_crt on)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        e39786088138f2749d64e9e90e0f9902daa77c40 # release-1.15.0
  FIND_PACKAGE_ARGS NAMES GTest
)

FetchContent_MakeAvailable(googletest)