include(FetchContent)

# Tell SDL to build as a shared library (must be set BEFORE FetchContent_Declare)
set(SDL_SHARED ON CACHE BOOL "Build SDL as shared library" FORCE)
set(SDL_STATIC OFF CACHE BOOL "Disable static SDL library" FORCE)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG main
)


FetchContent_MakeAvailable(SDL3)

# Create your engine library
add_library(QuarkEngine STATIC
    EngineCore.cpp
    EngineCore.h  # Optional: for IDE visibility
)


# Link SDL3 shared library to your engine
target_link_libraries(QuarkEngine 
	PUBLIC 
	SDL3::SDL3
	bgfx
	bimg
	bx


)





# Required on Windows so SDL doesn't redefine main()
if(WIN32)
    target_compile_definitions(QuarkEngine PUBLIC SDL_MAIN_HANDLED)
endif()

# --- In your GAME CMakeLists.txt, after add_executable(QuarkGame ...) and target_link_libraries(...), add this to copy SDL3.dll automatically ---
# add_custom_command(TARGET QuarkGame POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#         "$<TARGET_FILE_DIR:SDL3>/SDL3.dll"
#         $<TARGET_FILE_DIR:QuarkGame>)


# Optional: Copy SDL3.dll automatically to your executable output dir (adjust target name as needed)
# Assuming your game executable target is QuarkGame, add this in the game's CMakeLists.txt:

# add_custom_command(TARGET QuarkGame POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#         "$<TARGET_FILE_DIR:SDL3>/SDL3.dll"
#         $<TARGET_FILE_DIR:QuarkGame>)
