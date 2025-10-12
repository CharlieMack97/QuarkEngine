cmake_minimum_required(VERSION 3.16)

project(QuarkGameEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add subdirectories where targets are defined
add_subdirectory(QuarkEngine)
add_subdirectory(QuarkGame)
