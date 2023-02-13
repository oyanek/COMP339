cmake_minimum_required (VERSION 3.0.0)
project (main CXX)

SET(CMAKE_EXPORT_COMPILE_COMMANDS 1)
SET(CMAKE_CXX_COMPILER "clang++")
SET(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES  ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

#FetchContent_Declare(
#  googletest
 # GIT_REPOSITORY https://github.com.google.com/googletest.git
#  GIT_TAG    release-1.11.0
#)

enable_testing()

include_directories(include)
#file(GLOB SRC src/*.cpp)
add_executable(encoder src/encoder.cpp)
add_executable(decoder src/decoder.cpp)
#add_executable(tests src/tests.cpp)

add_custom_target(
	copy-compile-commands ALL
	${CMAKE_COMMAND} -E copy_if_different
	${CMAKE_BINARY_DIR}/compile_commands.json
	${CMAKE_CURRENT_LIST_DIR}
)
