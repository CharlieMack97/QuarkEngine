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

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG main
)


FetchContent_MakeAvailable(SDL3)

add_subdirectory(QuarkEngine)
add_subdirectory(QuarkGame)
