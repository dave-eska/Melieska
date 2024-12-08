cmake_minimum_required(VERSION 3.10)
include(FetchContent)

project(melnet)

set(CMAKE_CXX_STANDARD 20)

FetchContent_Declare(asio-cmake
  GIT_REPOSITORY https://github.com/kingsamchen/asio-cmake.git
  GIT_TAG        origin/master
)

# Specify asio version
set(ASIO_CMAKE_ASIO_TAG asio-1-12-2)
FetchContent_MakeAvailable(asio-cmake)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

# Add the static library
add_library(melnet STATIC "${MY_SOURCES}")

# Include directories for the library
target_include_directories(melnet PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(melnet PRIVATE asio)
