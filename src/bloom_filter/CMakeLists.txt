FetchContent_MakeAvailable(googletest)

set(OPENSSL_ROOT_DIR "/home/runner/Caesar-Cipher-1-comp-339-439-ds-7/opensslInstall")
set(OPENSSL_INCLUDE_DIR "${OPENSSL_ROOT_DIR}/include")
set(OPENSSL_LIBRARY_DIR "${OPENSSL_ROOT_DIR}/lib64")

enable_testing()

add_library(
  lib
  bloom_filter.cpp
)

add_executable(
  bloom_filter
  bloom_main.cpp
)

add_executable(
  bloom_test
  bloom_test.cpp
)

target_link_libraries(
  bloom_test
  lib
  gtest_main
)

target_include_directories(lib PUBLIC ${OPENSSL_INCLUDE_DIR})

target_link_libraries(
  lib
  ${OPENSSL_LIBRARY_DIR}/libssl.so.3 ${OPENSSL_LIBRARY_DIR}/libcrypto.so.3
)

target_link_libraries(
  bloom_filter
  lib
)

include(GoogleTest)
gtest_discover_tests(bloom_test)