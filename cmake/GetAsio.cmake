include(FetchContent)

FetchContent_Declare(
  asio
  GIT_REPOSITORY https://github.com/chriskohlhoff/asio
  GIT_TAG        12e0ce9e0500bf0f247dbd1ae894272656456079 # asio-1-30.2
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  FIND_PACKAGE_ARGS NAMES asio
)

add_library(asio INTERFACE)
target_include_directories(asio INTERFACE ${asio_SOURCE_DIR}/asio/include)
find_package(Threads)
target_link_libraries(asio INTERFACE Threads::Threads)

install(TARGETS asio EXPORT asio
  INCLUDES DESTINATION include
)

FetchContent_MakeAvailable(asio)