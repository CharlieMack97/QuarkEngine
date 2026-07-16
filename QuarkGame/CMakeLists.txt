
add_executable(QuarkGame "main.cpp" "GameScene.h")
target_link_libraries(QuarkGame PRIVATE QuarkEngine)
target_include_directories(QuarkGame PRIVATE
    ${CMAKE_SOURCE_DIR}/QuarkEngine
)

add_custom_command(TARGET QuarkGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/QuarkGame/assets"
        "$<TARGET_FILE_DIR:QuarkGame>/assets"
)
#
# Post-build: copy SDL3.dll
#set(SDL3_DLL_PATH "${CMAKE_BINARY_DIR}/_deps/sdl3-build//SDL3.dll")
#set(TARGET_DLL_DIR "${CMAKE_BINARY_DIR}/QuarkGame")

#add_custom_command(TARGET QuarkGame POST_BUILD
#    COMMAND ${CMAKE_COMMAND} 
#            "${SDL3_DLL_PATH}"
#            "${TARGET_DLL_DIR}"
 #   COMMENT "Copying SDL3.dll to output directory"
#)