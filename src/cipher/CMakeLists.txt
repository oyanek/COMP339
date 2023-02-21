FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  encoder
  encoder.cpp
)

add_executable(
  decoder
  decoder.cpp
)

add_executable(
  cipher_tests
  encodetest.cpp
  decodetest.cpp
)

target_link_libraries(
  cipher_tests
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(cipher_tests)