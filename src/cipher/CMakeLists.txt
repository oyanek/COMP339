FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(
  library
  encoder.cpp
  decoder.cpp
)

add_executable(
  encoder
  encoder_main.cpp
)

add_executable(
  decoder
  decoder_main.cpp
)

add_executable(
  cipher_tests
  encodetest.cpp
  decodetest.cpp
)

target_link_libraries(
  cipher_tests
  gtest_main
  library
)

target_link_libraries(
  decoder
  library
)

target_link_libraries(
  encoder
  library
)

include(GoogleTest)
gtest_discover_tests(cipher_tests)