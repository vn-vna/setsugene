include(FetchContent)

FetchContent_Declare(
  libyaml 
  GIT_REPOSITORY https://github.com/yaml/libyaml
  GIT_TAG        2c891fc7a770e8ba2fec34fc6b545c672beb37e6 # 0.2.5
  FIND_PACKAGE_ARGS NAMES yaml
)

message("Making libyaml available")
FetchContent_MakeAvailable(libyaml)