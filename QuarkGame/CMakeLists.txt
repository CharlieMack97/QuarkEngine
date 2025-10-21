
add_executable(QuarkGame main.cpp)

target_link_libraries(QuarkGame PRIVATE QuarkEngine)


target_include_directories(QuarkGame PRIVATE
    ${CMAKE_SOURCE_DIR}/QuarkEngine
)

# Post-build: copy SDL3.dll
set(SDL3_DLL_PATH "${CMAKE_BINARY_DIR}/_deps/sdl3-build/$<CONFIG>/SDL3.dll")
set(TARGET_DLL_DIR "$<TARGET_FILE_DIR:QuarkGame>")

add_custom_command(TARGET QuarkGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL3_DLL_PATH}"
            "${TARGET_DLL_DIR}"
    COMMENT "Copying SDL3.dll to output directory"
)