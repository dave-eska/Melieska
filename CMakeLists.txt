cmake_minimum_required(VERSION 3.31)
include(FetchContent)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory("thirdparty/raylib")
add_subdirectory("thirdparty/jsoncpp")

#project
project(main1)

set(CMAKE_CXX_STANDARD 20)

FetchContent_Declare(
	box2d
	GIT_REPOSITORY https://github.com/dave-eska/box2d.git
	GIT_TAG main
)
FetchContent_MakeAvailable(box2d)

add_subdirectory(melnet)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER gcc)

# Define MY_SOURCES to be a list of all the source files for my project
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

add_executable(main1 "${MY_SOURCES}")

target_include_directories(main1 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

target_link_libraries(main1 PRIVATE raylib jsoncpp_static box2d melnet)
