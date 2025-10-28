include(FetchContent)

# Tell SDL to build as a shared library (must be set BEFORE FetchContent_Declare)
# set(SDL_SHARED ON CACHE BOOL "Build SDL as shared library" FORCE)
# set(SDL_STATIC OFF CACHE BOOL "Disable static SDL library" FORCE)

# Create your engine library

include(FetchContent)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/QuarkGame")

FetchContent_Declare(
  bx
  GIT_REPOSITORY https://github.com/bkaradzic/bx.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(bx)

FetchContent_Declare(
  bimg
  GIT_REPOSITORY https://github.com/bkaradzic/bimg.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(bimg)

FetchContent_Declare(
  bgfx
  GIT_REPOSITORY https://github.com/bkaradzic/bgfx.cmake.git
  GIT_TAG master
)
FetchContent_MakeAvailable(bgfx)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG main
)
FetchContent_MakeAvailable(SDL3)


add_library(QuarkEngine STATIC
    
    EngineCore.cpp
    EngineApp.cpp
    TimeManager.cpp
    Header/InterfaceRenderer.h
    Header/EngineApp.h
    Header/Renderer.h
    Header/TimeManager.h
    Header/EngineCore.h
 "Header/GameObject.h" "Header/Component.h" "Compenents/TransformComp.h" "Compenents/RendererComp.h" "Compenents/RendererComp.cpp" "Renderer.cpp" "TextureManager.cpp")

target_include_directories(QuarkEngine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Header
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
