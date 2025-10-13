cmake_minimum_required(VERSION 3.16)

project(QuarkGameEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  bgfx
  GIT_REPOSITORY https://github.com/bkaradzic/bgfx.cmake
  GIT_TAG master
)
FetchContent_MakeAvailable(bgfx)

add_subdirectory(QuarkEngine)
add_subdirectory(QuarkGame)
