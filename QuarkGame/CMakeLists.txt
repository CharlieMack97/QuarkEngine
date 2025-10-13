
add_executable(QuarkGame main.cpp)

target_link_libraries(QuarkGame PRIVATE QuarkEngine)


target_include_directories(QuarkGame PRIVATE
    ${CMAKE_SOURCE_DIR}/QuarkEngine
)
